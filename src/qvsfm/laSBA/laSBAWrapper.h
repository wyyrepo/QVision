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

#ifndef LASBAWRAPPER_H
#define LASBAWRAPPER_H

#include <QVMatrix>
#include <QV3DPointF>
#include <qvsfm.h>
#include <QHash>
#include <qvmath.h>
#include <qvnumericalanalysis.h>

#ifndef DOXYGEN_IGNORE_THIS
extern double final_reprojection_error, initial_reprojection_error;
extern int sba_elapsed_milisecs, sba_iterations, sba_stop_condition;
extern int sba_damping_iters;
extern double sba_time_total, sba_time_solve, sba_time_system, last_mu_used;

#define SBA_INIT_MU       1E-03
#define SBA_STOP_THRESH   1E-12

/*!
@brief Apply SBA optimization on a SfM reconstruction.

This is a wrapper function for the <a href="http://www.ics.forth.gr/~lourakis/sba/">Bundle Adjustment implementation</a> of A. Argyros and M.I.A. Lourakis.

@param cameras Initial camera poses for the initial reconstruction.
@param points3D Initial 3D point locations.
@param pointProjections Projections for points in the reconstruction.
@param refinedCameras Camera poses after SBA optimization.
@param refinedPoints3D 3D point coordinates after the optimization.
@param numIterations Number of iterations to perform LM.
@param numFixedFrames Number of fixed frame poses in the reconstruction, to perform local bundle adjustment.
@param numFixedPoints Number of fixed 3D points in the reconstruction, to perform local bundle adjustment.
@param initialMuScaleFactor Initial damping factor for LM.
@param stoppingThresholdForJacobian Stop optimization if norm of Jacobian is smaller than this value.
@param stoppingThresholdForReprojectionError Stop optimization if reprojection error is smaller than this value.
@param stoppingThresholdForReprojectionErrorIncrement Stop optimization if reprojection error increment is smaller than this value in an iteration.

@ingroup qvsfm
@todo Document this.
*/
bool laSBAOptimization(	const QList<QVCameraPose> &cameras,
				const QList<QV3DPointF> &points3D,
				const QList< QHash<int, QPointF> > &pointProjections,
				QList<QVCameraPose> &refinedCameras,
				QList<QV3DPointF> &refinedPoints3D,
				const unsigned int numIterations = 100,
				const unsigned int numFixedFrames = 0,
				const unsigned int numFixedPoints = 0,
				const double initialMuScaleFactor = SBA_INIT_MU,
				const double stoppingThresholdForJacobian = SBA_STOP_THRESH,
				const double stoppingThresholdForProjections = SBA_STOP_THRESH,
				const double stoppingThresholdForReprojectionError = SBA_STOP_THRESH,
				const double stoppingThresholdForReprojectionErrorIncrement = 0.0);

#endif // DOXYGEN_IGNORE_THIS

#endif // LASBAWRAPPER_H

