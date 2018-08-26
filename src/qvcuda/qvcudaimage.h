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

#ifndef QVCUDAIMAGE_H
#define QVCUDAIMAGE_H

#include <cuda.h>
#include <cuda_runtime.h>
//#include "cutil.h"
#include <cutil.h>

//#include <qvcuda/qvcudautils.h>
//#include <qvcuda/qvcudaip.h>

#include <QVImage>

/*!
@class QVCUDAImage qvcuda/qvcudaimage.h QVCUDAImage
@brief Class to manage images stored in the GPU for the QVision framework.

This class is... //FIXME

@ingroup qvcuda
*/

template <typename Type, int Channels = 1> class QVCUDAImage
	{
	public:
		/// @brief Default constructor for QVCUDAImage.
		///
		/// Constructs an empty QVCUDAImage.
		QVCUDAImage() : cols(0), rows(0), step(0), device_data(NULL) { };

		/// @brief Constructor for QVCUDAImage class from QVImage.
		///
		/// Constructs a QVCUDAImage which copies the contents of a QVImage when built.
		/// @param qvimage Source QVImage.
		QVCUDAImage(QVImage<Type,Channels> qvimage) : device_data(NULL)
		{
		uploadToDevice(qvimage);
		};

		/// @brief Constructor for QVCUDAImage class from scratch.
		///
		/// Constructs a new, empty QVCUDAImage with a given size.
		/// @param c Number of requested cols.
		/// @param r Number of requested rows.
		QVCUDAImage(const int c, const int r) : device_data(NULL) { resize(c,r); };

		/// @brief Copy constructor for QVCUDAImage class.
		QVCUDAImage(const QVCUDAImage<Type,Channels> &src)
		{
		resize(src.getCols(),src.getRows());
		CUDA_SAFE_CALL(cudaMemcpy2D(device_data, step, src.getData(), src.getStep(), sizeof(Type)*src.getCols()*Channels, src.getRows(), cudaMemcpyDeviceToDevice));
		};

		/// @brief Assignment operator for QVCUDAImage class.
		QVCUDAImage& operator=(const QVCUDAImage<Type,Channels> &src)
		{
		resize(src.getCols(),src.getRows());
		CUDA_SAFE_CALL(cudaMemcpy2D(device_data, step, src.getData(), src.getStep(), sizeof(Type)*src.getCols()*Channels, src.getRows(), cudaMemcpyDeviceToDevice));
		return *this;
		};

		/// @brief Destructor for QVCUDAImage class.
		~QVCUDAImage() { if(device_data != NULL) CUDA_SAFE_CALL(cudaFree(device_data)); };

		/// @brief Returns the number of cols of the image.
		int getCols() const { return cols; }

		/// @brief Returns the number of rows of the image.
		int getRows() const { return rows; }

		/// @brief Returns the step of the image.
		int getStep() const { return step; }

		/// @brief Returns the pointer to the start of the device data for the image.
		Type *getData() const { return device_data; }

		/// @brief Resizes a QVCUDAImage.
		///
		/// The new image resizes to the new number of requested rows and cols (but completely discards the old image).
		/// @param c Number of requested cols.
		/// @param r Number of requested rows.
		void resize(const int c, const int r)
		{
		if(device_data != NULL) CUDA_SAFE_CALL(cudaFree(device_data));
		cols = c; rows = r;
		size_t step_size_t;
		CUDA_SAFE_CALL(cudaMallocPitch((void **)&device_data,&step_size_t,sizeof(Type)*cols*Channels,rows));
		step = step_size_t;
		}

		/// @brief Uploads a (host) QVImage to a (device) QVCUDAImage.
		void uploadToDevice(const QVImage<Type,Channels> qvimage)
		{
		resize(qvimage.getCols(),qvimage.getRows());
		CUDA_SAFE_CALL(cudaMemcpy2D(device_data, step, qvimage.getReadData(), qvimage.getStep(), sizeof(Type)*qvimage.getCols()*Channels, qvimage.getRows(), cudaMemcpyHostToDevice));
		};

		/// @brief Download a (device) QVCUDAImage to a (host) QVImage.
		void downloadFromDevice(QVImage<Type,Channels> &qvimage) const
		{
		qvimage = QVImage<Type,Channels>(cols,rows);
		CUDA_SAFE_CALL(cudaMemcpy2D(qvimage.getWriteData(), qvimage.getStep(), device_data, step,  sizeof(Type)*cols*Channels, rows, cudaMemcpyDeviceToHost));
		};

	private:
	int cols, rows, step;
	Type *device_data;
	// Type *texture_data;
	};

#endif
