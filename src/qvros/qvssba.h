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

#ifndef QVSSBA_H
#define QVSSBA_H

#include <qvprojective.h>

#define SBA_DENSE_CHOLESKY 0
#define SBA_SPARSE_CHOLESKY 1
#define SBA_GRADIENT 2
#define SBA_BLOCK_JACOBIAN_PCG 3


/*!
@brief Apply sSBA optimization on a SfM reconstruction.

This is a wrapper function for the sparse bundle adjustment functionality provided by the <a href="http://www.ros.org/wiki/Documentation">ROS package</a>.

@param cameras Initial camera poses for the initial reconstruction.
@param points3D Initial 3D point locations.
@param pointProjections Projections for points in the reconstruction.
@param refinedCameras Camera poses after SBA optimization.
@param refinedPoints3D 3D point coordinates after the optimization.
@param time_sSBA Time spend on the SBA optimization.
@param numIters Number of iterations to perform LM.
@param lambda Inital damping factor for LM.
@param numFixedPoints Number of fixed 3D points in the reconstruction, to perform local bundle adjustment.

@ingroup qvros
@todo Document this.
*/
int sSBAOptimization(	const QList<QVCameraPose> &cameraPoses,
			const QList<QV3DPointF> &points3D,
			const QList< QHash<int, QPointF> > &pointsProjections,
			QList<QVCameraPose> &refinedCameraPoses,
			QList<QV3DPointF> &refinedPoints3D,	
			int &time_sSBA,
			const int numIters = 1,
			const double lambda = 1e-3,
			const int useCSparse = SBA_SPARSE_CHOLESKY,
			const int numFixedCameras = 1,	// For incremental operation.
			double initTolCG = 1.0e-8,		// For conjugate gradient.
			const int maxItersCG = 100		// For conjugate gradient.
			);

#endif

