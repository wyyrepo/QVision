/*
 *	Copyright (C) 2011, 2012. PARP Research Group.
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

#ifndef QVOPTICALFLOW_H
#define QVOPTICALFLOW_H

#include "v3d_gpubase.h"
#include "v3d_gpuflow.h"
#include "v3d_gpupyramid.h"
#include "v3d_utilities.h"
#include "v3d_image.h"
#include "v3d_timer.h"

#include <QVImage>
#include <QVPyramid>

using namespace V3D_GPU;
using namespace V3D;

typedef TVL1_FlowEstimator_Relaxed TVL1_FlowEstimator;

/*! @brief Initialize the dense flow estimator.
 
This function creates and configures the dense flow estimator with the configuration parameters below.
@param flowEstimator Dense flow estimator.
@param width Number of columns of the images.
@param height Number of rows of the images.
@param nLeves Number of levels of the image pyramids.
@param nIterations Number of inner iterations of the algorithm
@param nOuterIterations Number of outer iterations of the algorithm
@param lambda Parameter lambda
@param tau Parameter tau
@param theta Parameter theta

@ingroup qvgpukltflow
*/
void qvInitFlowGPU(TVL1_FlowEstimator * &flowEstimator, int width, int height, int nLevels, int nIterations, int nOuterIterations,
           double lambda, double tau, double theta);

/*! @brief Compute dense optical flow between two images.

This function computes dense optical flow between two images, using a preconfigured flow estimator.
@param flowEstimator Dense flow estimator created and configured.
@param leftPyramid Image pyramid of the first image
@param rightPyramid Image pyramid of the second image
@param x Image with x-coordenate of the flow vector for each pixel
@param y Image with y-coordenate of the flow vector for each pixel

@ingroup qvgpukltflow
*/
void qvOpticalFlowGPU(TVL1_FlowEstimator * flowEstimator, QVPyramid* p1, QVPyramid*p2 ,
   QVImage<sFloat, 1> &x, QVImage<sFloat, 1> &y);

#endif // QVOPTICALFLOW_H






