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

#ifndef QVSIFTGPU_H
#define QVSIFTGPU_H

#include <QList>
#include <QVImage>
#include <QVSiftFeature>

/// @brief Available methods for CPU SIFT feature detection
/// @ingroup qvcuda
typedef enum {
    CUDA_METHOD = 0,	/// CUDA
    GLSL_METHOD = 1,	/// GLSL
    CG_METHOD = 2	/// CG
} nvidia_method;

bool resetSiftGPU();

/**
@brief Find SIFT features in an image using user-specified parameter values, using NVIDIA CUDA.

@param image The image in which to detect features.
@param method 0=CUDA, 1=GLSL, 2=CG
@param computeDescriptors Skip descriptor computation if TRUE (not modifiable after initialization)
@param filterWidthFactor Factor for filter width (2*factor*sigma+1).
@param orientationSampleWindow Factor for orientation sample window (2*factor*sigma).
@param descriptorGridSize Factor for descriptor grid size (4*factor*sigma).
@param firstOctave First octave to start detection.
@param thresholdDoG DoG threshold.
@param thresholdEdge Edge threshold.

@return Returns the list of obtained keypoints (with descriptors if sd is not TRUE).
@ingroup qvsiftgpu
*/
const QList<QVSiftFeature> getSiftGPUFeatures(const QVImage<uChar> &image,
				nvidia_method method = CUDA_METHOD,
				bool computeDescriptors = FALSE,
				double filterWidthFactor = 4.0,
				double orientationSampleWindow = 2.0,
				double descriptorGridSize = 3.0,
				int firstOctave = 0,
				double thresholdDoG = 0.02/3,
				double thresholdEdge = 10.0,
				int d = 3,
				int v = 0);

/**
@brief Match SIFT features between a pair of images using using NVIDIA CUDA.

@param img1features List of SIFT features from image 1.
@param img2features List of SIFT features from image 2.
@param distmax Maximum distance of SIFT descriptor.
@param ratiomax Maximum distance ratio.
@param mutualBestMatch Mutual best match or one way.

@return Returns set of matchings. Each matching contains two index references, one for the feature in each input feature list.
@ingroup qvsiftgpu
*/
QList< QPair<int, int> > matchSiftGPUFeatures(	const QList<QVSiftFeature> img1features,
												const QList<QVSiftFeature> img2features,
												const float distmax = 0.7,
												const float ratiomax = 0.8,
												const bool mutual_best_match = true
												);

#endif // QVSIFTGPU_H
