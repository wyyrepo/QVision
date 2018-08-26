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

#ifndef QVCUDAIP_H
#define QVCUDAIP_H

#include <QVCUDAImage>

/// @brief Subtracts two QVCUDAImage<float,1> in the CUDA device, and puts the result in a third one.
/// 
/// Both src1 and src2 must be of the same size. The dest image will have this same size on return (independently of
/// its original size).
/// @param src1 First QVCUDAImage<float,1> (input)
/// @param src2 Second QVCUDAImage<float,1> (input)
/// @param dest Destination QVCUDAImage<float,1> (output)
bool QVCUDASubtract(const QVCUDAImage<float,1> &src1, const QVCUDAImage<float,1> &src2, QVCUDAImage<float,1> &dest);

/// @brief FIXME pending...
bool QVCUDAScaleDown(const QVCUDAImage<float,1> &src, QVCUDAImage<float,1> &dest, float sigma);

/// @brief Applies a Gauss filter to ... 
bool QVCUDAFilterGauss(const QVCUDAImage<float,1> &src, QVCUDAImage<float,1> &dest, int kernelSize, float sigma);


/// @brief To make CUDA tests...
bool QVCUDATest(const QVCUDAImage<float,1> &src, QVCUDAImage<float,1> &dest, int radius, int iters);

#endif
