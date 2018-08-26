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

/// @file
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#include <iostream>

#include "qvcudaip.h"

#include "qvcudaipD.h"

bool QVCUDASubtract(const QVCUDAImage<float,1> &src1, const QVCUDAImage<float,1> &src2, QVCUDAImage<float,1> &dest)
	{
	if ( (src1.getCols() != src2.getCols()) or (src1.getRows() != src2.getRows()) or (src1.getStep() != src2.getStep()) ) {
		std::cerr << "QVCUDAIP module: QVCUDASubtract function: src1 and src2 image sizes do not coincide.\n";
		return FALSE;
	}

	int w = src1.getCols();
	int h = src1.getRows();
	int step = src1.getStep(); // We know here that src2's step is the same (as forced by QVCUDAImage resize method).

	dest.resize(w,h);

	Subtract_kernel(src1.getData(),src2.getData(),dest.getData(),w,h,step);

	CUT_CHECK_ERROR("QVCUDAIP module: QVCUDASubtract function: execution failed\n");
	CUDA_SAFE_CALL(cudaThreadSynchronize());

	return TRUE;

	}

bool QVCUDAScaleDown(const QVCUDAImage<float,1> &src, QVCUDAImage<float,1> &dest, float sigma)
{
	if ( (src.getCols() < 2) or (src.getRows() < 2) or (src.getCols()%2 != 0) or (src.getRows()%2 != 0)) {
		std::cerr << "QVCUDAIP module: QVCUDAScaleDown function: src image is not even sized.\n";
		return FALSE;
	}

	int w = src.getCols();
	int h = src.getRows();
	int step_s = src.getStep();

	dest.resize(w/2,h/2);
	int step_d = dest.getStep();


	float h_Kernel[5];
	float kernelSum = 0.0f;
	for (int j=0;j<5;j++) {
		h_Kernel[j] = (float)expf(-(double)(j-2)*(j-2)/2.0/sigma/sigma);
		kernelSum += h_Kernel[j];
	}
	for (int j=0;j<5;j++)
		h_Kernel[j] /= kernelSum;

	ScaleDown_kernel(src.getData(),dest.getData(),h_Kernel,w,h,step_s,step_d);

	CUT_CHECK_ERROR("QVCUDAIP module: QVCUDAScaleDown() execution failed\n");
	CUDA_SAFE_CALL(cudaThreadSynchronize());

	return TRUE;

}


bool QVCUDAFilterGauss(const QVCUDAImage<float,1> &src, QVCUDAImage<float,1> &dest, int kernelSize, float sigma)
{
	int w = src.getCols();
	int h = src.getRows();
	int step = src.getStep();

	dest.resize(w,h);

	if ( (src.getCols() < 1) or (src.getRows() < 1) ) {
		std::cerr << "QVCUDAIP module: QVCUDAFilterGauss function: src image is not OK.\n";
		return FALSE;
	}

	int RADIUS = static_cast<int>(round(2.5*sigma));
	std::cout << "USING RADIUS=" << RADIUS << ".\n";

	if(2*RADIUS+1>CUDA_MAX_MASK_SIZE) {
		std::cerr << "QVCUDAIP module: QVCUDAFilterGauss function: 2*RADIUS+1 exceeds CUDA_MAX_MASK_SIZE.\n";
		return FALSE;
	}

	QVCUDAImage<float,1> tempimg(w,h);
	
	// We know here that dest and temp steps are the same (as forced by QVCUDAImage resize method).

	float h_Kernel[CUDA_MAX_MASK_SIZE];
	float kernelSum = 0.0f;
	for (int j=-RADIUS;j<=RADIUS;j++) {
		h_Kernel[j+RADIUS] = (float)expf(-(double)j*j/2.0/sigma/sigma);
		kernelSum += h_Kernel[j+RADIUS];
	}
	for (int j=-RADIUS;j<=RADIUS;j++)
		h_Kernel[j+RADIUS] /= kernelSum;

	SeparableFilter_kernel(src.getData(),dest.getData(),tempimg.getData(),h_Kernel,RADIUS,w,h,step);

	CUT_CHECK_ERROR("QVCUDAIP module: QVCUDAFilterGauss() execution failed\n");
	CUDA_SAFE_CALL(cudaThreadSynchronize());

	return TRUE;

}

bool QVCUDATest(const QVCUDAImage<float,1> &src, QVCUDAImage<float,1> &dest, int radius, int iters)
{
	int w = src.getCols();
	int h = src.getRows();
	int step = src.getStep();

	dest.resize(w,h);

	if ( (src.getCols() < 1) or (src.getRows() < 1) ) {
		std::cerr << "QVCUDAIP module: QVCUDATest function: src image is not OK.\n";
		return FALSE;
	}

	Test_kernel(src.getData(),dest.getData(),radius,iters,w,h,step);

	CUT_CHECK_ERROR("QVCUDAIP module: QVCUDATest() execution failed\n");
	CUDA_SAFE_CALL(cudaThreadSynchronize());

	return TRUE;


}
