/*
 *	Copyright (C) 2007, 2008, 2009, 2010, 2011, 2012. PARP Research Group.
 *	<http://perception.inf.um.es>
 *	University of Murcia, Spain.
 *
 *	This file is part of the QVision library.
 *
 *	QVision is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as
 *	published by the Free Software Foundation, version 3 of the License.
 *
 *	QVision is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with QVision. If not, see <http://www.gnu.org/licenses/>.
 */

/// @file qvcudaipD.cu
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#include <iostream>

#include <cuda.h>
#include <cuda_runtime.h>
#include <cutil.h>

#include "qvcudaipD.h"
#include "qvcudautils.h"

#define WARP_SIZE	16

#define LOWPASS5_DX	160
#define LOWPASS5_DY	16

#define ROW_TILE_W	160
#define COLUMN_TILE_W	16
#define COLUMN_TILE_H	48

__device__ __constant__ float d_Kernel[CUDA_MAX_MASK_SIZE];

///////////////////////////////////////////////////////////////////////////////
// Kernel function for subtracting two images:
///////////////////////////////////////////////////////////////////////////////
template<typename T> __global__ void Subtract(T *d_Data1, T *d_Data2, T *d_Result, int width, int height,int step)
{
  const int x = __mul24(blockIdx.x, 16) + threadIdx.x;
  const int y = __mul24(blockIdx.y, 16) + threadIdx.y;
  int p = __mul24(y, step/sizeof(T)) + x;
  if (x<width && y<height)
    d_Result[p] = d_Data1[p] - d_Data2[p];
  __syncthreads();
}

void Subtract_kernel(float *src1, float *src2, float *dst, int w, int h, int step)
{
	dim3 blocks(iDivUp(w,16),iDivUp(h,16));
	dim3 threads(16,16);
	Subtract<float><<<blocks,threads>>>(src1, src2, dst, w, h, step);
}

/*void Subtract_kernel(int *src1, int *src2, int *dst, int w, int h)
{
	dim3 blocks(iDivUp(w,16),iDivUp(h,16));
	dim3 threads(16,16);
	Subtract<int><<<blocks,threads>>>(src1, src2, dst, w, h);
}*/

///////////////////////////////////////////////////////////////////////////////
// Kernel function to lowpass filter and subsample image
///////////////////////////////////////////////////////////////////////////////
__global__ void ScaleDown(const float *d_Data, float *d_Result, int width, int height, int step_s, int step_d)
{
	__shared__ float inrow[LOWPASS5_DX+4]; // 164 elements, for 160(bloq_siz_X) + 2 margin on each
						// side; here we read rows from original image.
	__shared__ float brow[5*(LOWPASS5_DX/2)]; // 400 elements, 5 rows of 80 columns each;
						// here we store intermediate results of row filtering.
	__shared__ int yRead[LOWPASS5_DY+4], yWrite[LOWPASS5_DY+4];
						// To store indexes for each thread to read from source
						// and write to destination.
	#define dx2 (LOWPASS5_DX/2)
	const int tx = threadIdx.x;
	const int tx0 = tx+0*dx2;
	const int tx1 = tx+1*dx2;
	const int tx2 = tx+2*dx2;
	const int tx3 = tx+3*dx2;
	const int tx4 = tx+4*dx2;
	const int xStart = __mul24(blockIdx.x, LOWPASS5_DX);
	const int yStart = __mul24(blockIdx.y, LOWPASS5_DY);
	const int xWrite = xStart/2 + tx;
	const float *k = d_Kernel;
	if (tx<LOWPASS5_DY+4)
		{ // Threads 0-19 initialize arrays yRead e yWrite, of 20 positions each
		int y = yStart + tx - 2; // corrected by pedroe; Borjkman: int y = yStart + tx - 1;
		y = (y<0 ? 0 : y);
		y = (y>=height ? height-1 : y);
		yRead[tx] = __mul24(y, step_s/sizeof(float));
		yWrite[tx] = __mul24((yStart + tx - 4)/2, step_d/sizeof(float));
		}
	__syncthreads();

	int xRead = xStart + tx - WARP_SIZE;
	xRead = (xRead<0 ? 0 : xRead);
	xRead = (xRead>=width ? width-1 : xRead);
	for (int dy=0;dy<LOWPASS5_DY+4;dy+=5)
		{
		// dy=0,5,10,15 (unrolled loop, with 5 different steps by iteration):

		if (tx>=WARP_SIZE-2)
			{
			// Threads 14-177 (total 164) write 164 elements of inrow[]
			inrow[tx-WARP_SIZE+2] = d_Data[yRead[dy+0] + xRead];
			// We read in inrow 164 consecutive elements from rows 0 (1º for step), 5 (2º step),
			// 10 (3º step), 15 (4º step).
			}
		__syncthreads();
		if (tx<dx2)
		// Threads 0-79 compute row filter on first 80 elements of brow[]:
      			brow[tx0] = __fmul_rz(k[0],(inrow[2*tx]+inrow[2*tx+4])) + __fmul_rz(k[1],(inrow[2*tx+1]+inrow[2*tx+3])) + __fmul_rz(k[2],inrow[2*tx+2]);
		__syncthreads();
		if (tx<dx2 && dy>=4 && !(dy&1) && (xWrite<width/2) && (yWrite[dy+0]<height*step_d/2/sizeof(float)) )
			{
			// Finally, threads 0-79 compute column filter on 400 elements of brow[]
			// (which correspond to 5 rows of 80 elements each). But this is a little bit tricky!
			// It uses a segmentation technique: in fact we get into here only from the second step of
			// the for, when a complete brow[] packet of 400 has been computed yet:
			d_Result[yWrite[dy+0] + xWrite] = __fmul_rz(k[2],brow[tx3]) + __fmul_rz(k[0],brow[tx1]+brow[tx0]) + __fmul_rz(k[1],brow[tx2]+brow[tx4]);
			}

		// From here on, it is always the same. The only important difference is always in the third
		// if: observe that the alternate !(dy&1) and (dy&1) conditions are used to perform the row
		// writings in the destination image in a "one step yes, one step no" way:
		if (dy<(LOWPASS5_DY+3))
			{
			if (tx>=WARP_SIZE-2)
				inrow[tx-WARP_SIZE+2] = d_Data[yRead[dy+1] + xRead];
			__syncthreads();
			if (tx<dx2)
				brow[tx1] = __fmul_rz(k[0],(inrow[2*tx]+inrow[2*tx+4])) + __fmul_rz(k[1],(inrow[2*tx+1]+inrow[2*tx+3])) + __fmul_rz(k[2],inrow[2*tx+2]);
			__syncthreads();
			if (tx<dx2 && dy>=3 && (dy&1) && (xWrite<width/2) && (yWrite[dy+1]<height*step_d/2/sizeof(float)))
				d_Result[yWrite[dy+1] + xWrite] = __fmul_rz(k[2],brow[tx4]) + __fmul_rz(k[0],brow[tx2]+brow[tx1]) + __fmul_rz(k[1],brow[tx3]+brow[tx0]);
			}

		if (dy<(LOWPASS5_DY+2))
			{
			if (tx>=WARP_SIZE-2)
				inrow[tx-WARP_SIZE+2] = d_Data[yRead[dy+2] + xRead];
			__syncthreads();
			if (tx<dx2)
				brow[tx2] = __fmul_rz(k[0],(inrow[2*tx]+inrow[2*tx+4])) + __fmul_rz(k[1],(inrow[2*tx+1]+inrow[2*tx+3])) + __fmul_rz(k[2],inrow[2*tx+2]);
			__syncthreads();
			if (tx<dx2 && dy>=2 && !(dy&1) && (xWrite<width/2) && (yWrite[dy+2]<height*step_d/2/sizeof(float)))
				d_Result[yWrite[dy+2] + xWrite] = __fmul_rz(k[2],brow[tx0]) + __fmul_rz(k[0],brow[tx3]+brow[tx2]) + __fmul_rz(k[1],brow[tx4]+brow[tx1]);
			}

		if (dy<(LOWPASS5_DY+1))
			{
			if (tx>=WARP_SIZE-2)
				inrow[tx-WARP_SIZE+2] = d_Data[yRead[dy+3] + xRead];
			__syncthreads();
			if (tx<dx2)
				brow[tx3] = __fmul_rz(k[0],(inrow[2*tx]+inrow[2*tx+4])) +  __fmul_rz(k[1],(inrow[2*tx+1]+inrow[2*tx+3])) + __fmul_rz(k[2],inrow[2*tx+2]);
			__syncthreads();
			if (tx<dx2 && dy>=1 && (dy&1) && (xWrite<width/2) && (yWrite[dy+3]<height*step_d/2/sizeof(float)))
				d_Result[yWrite[dy+3] + xWrite] = __fmul_rz(k[2],brow[tx1]) + __fmul_rz(k[0],brow[tx4]+brow[tx3]) + __fmul_rz(k[1],brow[tx0]+brow[tx2]);
			}

		if (dy<LOWPASS5_DY)
			{
			if (tx>=WARP_SIZE-2)
				inrow[tx-WARP_SIZE+2] = d_Data[yRead[dy+4] + xRead];
			__syncthreads();
			if (tx<dx2)
				brow[tx4] = __fmul_rz(k[0],(inrow[2*tx]+inrow[2*tx+4])) + __fmul_rz(k[1],(inrow[2*tx+1]+inrow[2*tx+3])) + __fmul_rz(k[2],inrow[2*tx+2]);
			__syncthreads();
			if (tx<dx2 && !(dy&1) && (xWrite<width/2) && (yWrite[dy+4]<height*step_d/2/sizeof(float)))
				d_Result[yWrite[dy+4] + xWrite] = __fmul_rz(k[2],brow[tx2]) + __fmul_rz(k[0],brow[tx0]+brow[tx4]) + __fmul_rz(k[1],brow[tx1]+brow[tx3]);
			}
		__syncthreads();

	} // for(dy)
}

void ScaleDown_kernel(const float *src, float *dest, float* h_Kernel, int w, int h, int step_s, int step_d)
{
	CUDA_SAFE_CALL(cudaMemcpyToSymbol(d_Kernel, h_Kernel, 5*sizeof(float)));
	dim3 blocks(iDivUp(w, LOWPASS5_DX), iDivUp(h, LOWPASS5_DY));
	dim3 threads(LOWPASS5_DX + WARP_SIZE + 2);
	ScaleDown<<<blocks, threads>>>(src,dest,w,h,step_s,step_d);
}

// Loop unrolling templates for convolution, needed for best performance (according to Bjorkman):
//template<int i> __device__ float ConvRow(float *data) { return data[i]*d_Kernel[i] + ConvRow<i-1>(data); }
//template<> __device__ float ConvRow<-1>(float *data) { return 0; }
//template<int i> __device__ float ConvCol(float *data) { return data[i*COLUMN_TILE_W]*d_Kernel[i] + ConvCol<i-1>(data); }
//template<> __device__ float ConvCol<-1>(float *data) { return 0; }

// Substituted by pedroe by simple __device_ function (slightly slower, but with parametrizable radius, 
// changeable in execution time):
__device__ float ConvRow(float *data, int cont)
{
	float acum = 0.0;
	for(int i=0;i<cont;i++)
		acum += data[i]*d_Kernel[i];
	return acum;
}

__device__ float ConvCol(float *data, int cont)
{
	float acum = 0.0;
	for(int i=0;i<cont;i++)
		acum += data[i*COLUMN_TILE_W]*d_Kernel[i];
	return acum;
}

///////////////////////////////////////////////////////////////////////////////
// Row convolution filter
///////////////////////////////////////////////////////////////////////////////
__global__ void ConvRowGPU(const float *d_Data, float *d_Result, int RADIUS, int width, int height)
{
	//Data cache
	//__shared__ float data[RADIUS+ROW_TILE_W+RADIUS+1];
	__shared__ float data[2*CUDA_MAX_MASK_SIZE+ROW_TILE_W+1];

	//Current tile and apron limits, relative to row start:
	const int tileStart = __mul24(blockIdx.x, ROW_TILE_W);

	//Row start index in d_Data[]:
	const int rowStart = __mul24(blockIdx.y, width);
	const int rowEnd = rowStart + width - 1;
	const int loadPos = threadIdx.x - WARP_SIZE + tileStart;
	const int smemPos = threadIdx.x - WARP_SIZE + RADIUS;

	//Set the entire data cache contents
	if (smemPos>=0) 
		{
		if (loadPos<0)
			data[smemPos] = d_Data[rowStart];
		else if (loadPos>=width) 
			data[smemPos] = d_Data[rowEnd];
		else
			data[smemPos] = d_Data[rowStart + loadPos];
		}

	__syncthreads();

	//Clamp tile and apron limits by image borders
	const int tileEnd = tileStart + ROW_TILE_W - 1;
	const int tileEndClamped = min(tileEnd, width - 1);
	const int writePos = tileStart + threadIdx.x;


	if (writePos <= tileEndClamped)
		{
		const int smemPos = threadIdx.x + RADIUS;
		d_Result[rowStart + writePos] = ConvRow(data + smemPos - RADIUS,2*RADIUS+1);
		}

	__syncthreads();
}

///////////////////////////////////////////////////////////////////////////////
// Column convolution filter
///////////////////////////////////////////////////////////////////////////////
__global__ void ConvColGPU(const float *d_Data, float *d_Result, int RADIUS, int width, int height, int smemStride, int gmemStride)
{
	// Data cache
	//__shared__ float data[COLUMN_TILE_W*(RADIUS + COLUMN_TILE_H + RADIUS+1)];
	__shared__ float data[COLUMN_TILE_W*(2*CUDA_MAX_MASK_SIZE+COLUMN_TILE_H+1)];

	// Current tile and apron limits, in rows
	const int tileStart = __mul24(blockIdx.y, COLUMN_TILE_H);
	const int tileEnd = tileStart + COLUMN_TILE_H - 1;
	const int apronStart = tileStart - RADIUS;
	const int apronEnd = tileEnd + RADIUS;
	
	// Current column index
	const int columnStart = __mul24(blockIdx.x, COLUMN_TILE_W) + threadIdx.x;
	const int columnEnd = columnStart + __mul24(height-1, width);

	if (columnStart<width)
		{
		// Shared and global memory indices for current column
		int smemPos = __mul24(threadIdx.y, COLUMN_TILE_W) + threadIdx.x;
		int gmemPos = __mul24(apronStart + threadIdx.y, width) + columnStart;
		// Cycle through the entire data cache
		for (int y = apronStart + threadIdx.y; y <= apronEnd; y += blockDim.y)
			{
			if (y<0)
				data[smemPos] = d_Data[columnStart];
			else if (y>=height)
				data[smemPos] = d_Data[columnEnd];
			else 
				data[smemPos] = d_Data[gmemPos];
			smemPos += smemStride;
			gmemPos += gmemStride;
			}
		}

	__syncthreads();

	if (columnStart<width)
		{
		// Shared and global memory indices for current column
		// Clamp tile and apron limits by image borders
		const int tileEndClamped = min(tileEnd, height - 1);
		int smemPos = __mul24(threadIdx.y + RADIUS, COLUMN_TILE_W) + threadIdx.x;
		int gmemPos = __mul24(tileStart + threadIdx.y , width) + columnStart;
		// Cycle through the tile body, clamped by image borders
		// Calculate and output the results
		for (int y=tileStart+threadIdx.y;y<=tileEndClamped;y+=blockDim.y)
			{
			d_Result[gmemPos] = ConvCol(data + smemPos - RADIUS*COLUMN_TILE_W,2*RADIUS+1);
			smemPos += smemStride;
			gmemPos += gmemStride;
			}
		}

	__syncthreads();
}

void SeparableFilter_kernel(const float *src, float *dest, float *temp, float *h_Kernel, int radius, int w, int h, int step)
{
	const unsigned int kernelSize = (2*radius+1);
	if(kernelSize > CUDA_MAX_MASK_SIZE) {
		std::cerr << "QVCUDAIP module: SeparableFilter_kernel function: kernelSize > CUDA_MAX_MASK_SIZE.\n";
		return;
	}
	CUDA_SAFE_CALL(cudaMemcpyToSymbol(d_Kernel, h_Kernel, kernelSize*sizeof(float)));

	dim3 blockGridRows(iDivUp(w, ROW_TILE_W), h);
	dim3 threadBlockRows(WARP_SIZE + ROW_TILE_W + radius);

	ConvRowGPU<<<blockGridRows, threadBlockRows>>>(src,temp,radius,w,h);

	CUT_CHECK_ERROR("ConvRowGPU() execution failed\n");
	CUDA_SAFE_CALL(cudaThreadSynchronize());

	dim3 blockGridColumns(iDivUp(w, COLUMN_TILE_W),iDivUp(h, COLUMN_TILE_H));
	dim3 threadBlockColumns(COLUMN_TILE_W, 8);

	ConvColGPU<<<blockGridColumns, threadBlockColumns>>>(temp,dest,radius,w,h,COLUMN_TILE_W*8,w*8);

	CUT_CHECK_ERROR("ConvColGPU() execution failed\n");
	CUDA_SAFE_CALL(cudaThreadSynchronize());
}


#define TEST_TILE_W 16
#define TEST_TILE_H 16
#define TEST_THREADS_W 16
#define TEST_THREADS_H 16

__global__ void TestGPU(const float *src, float *dest, int radius, int iters, int width, int height, int step)
{
	__shared__ float pp[4000];
	const int x = __mul24(blockIdx.x,TEST_TILE_W) + threadIdx.x;
	const int y = __mul24(blockIdx.y,TEST_TILE_H) + threadIdx.y;
	int p = __mul24(y, step/sizeof(float)) + x;
	if (x<width-1 && y<height-1 && x>=1 && y>=1)
		{
		float s = src[p],d=s,d2=src[p+1],d3=src[p-1];
		for(int i=0;i<iters;i++)
			if(i%10)
				d = d+d2+d3;
			else 
				for(int j=0;j<10;j++)
					d = (d+d2+d3)/20;
		    //t[pos] += 0.001;
		dest[p] = d;
		}
	__syncthreads();
}

void Test_kernel(const float *src, float *dest, int radius, int iters, int w, int h, int step)
{
	dim3 blockGrid(iDivUp(w,TEST_TILE_W), iDivUp(h,TEST_TILE_H));
	dim3 threadBlock(TEST_THREADS_W,TEST_THREADS_H);

	TestGPU<<<blockGrid, threadBlock>>>(src,dest,radius,iters,w,h,step);

	CUT_CHECK_ERROR("TestGPU() execution failed\n");
	CUDA_SAFE_CALL(cudaThreadSynchronize());
}

