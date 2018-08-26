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

#include <QVEuclideanMapping3>
#include <QV3DPointF>
#include <QVCameraPose>
#include <QHash>

#ifndef QVREPROJECTIONERROR_H
#define QVREPROJECTIONERROR_H

/*!
@brief Improves the estimated location of a camera pose by refining its reprojection error.

Provided a set of 3D points and their estimated projections on an image, this function improves the pose for that view, by refining the \f$ norm_2 \f$ of the reprojection error using the Levenberg-Marquardt optimization.

@param cameraPose Initial camera pose.
@param points2D List of image projections for the points
@param points3D List of 3D coordinates for the points
@param iterations Number of Levenberg-Marquard iterations to perform

@return An improved camera pose.
@ingroup qvprojectivegeometry
*/
QVEuclideanMapping3 optimizeReprojectionErrorForCameraPose(const QVEuclideanMapping3 &camera0, const QList<QPointF> &points2D, const QList<QV3DPointF> &points3D, const int iterations = 5);

/*!
@brief Improves the estimated location of a 3D point by refining its reprojection error.

Provided the estimated projections of a 3D point on a set of views, and the estimated camera poses for those views, this function improves the estimated location of the 3D point by refining the \f$ norm_2 \f$ of the reprojection error using the Levenberg-Marquardt optimization.

@param initialPoint3D Initial 3D point location.
@param cameraPoses List of the views camera poses.
@param projectionsOfAPoint List of projections of the 3D point on the views.
@param iterations Number of iterations to refine reprojection error.
@param lambda Value to increase the diagonal of the Hessian matrix in the Levenberg-Marquardt algorithm.

@return An improved location for the 3D point.
@ingroup qvprojectivegeometry
*/
QV3DPointF optimizeReprojectionErrorFor3DPoint(const QV3DPointF &initialPoint3D, const QList<QVEuclideanMapping3> &cameraPoses, const QHash<int, QPointF> &projectionsOfAPoint,
						const int iterations = 5,
						const double lambda = 1e+0);

/*!
@brief Improves the estimated location of a camera pose by refining its reprojection error robustified by a Cauchy distribution.

This function optimizes the pose of a view using the Levenberg-Marquardt optimization, provided the image projections of a set of 3D points.

This method assumes a Cauchy distribution for the reprojection residuals, to reduce the impact of outliers in the cost error, and improve the obtained camera pose.

@param cameraPose Initial camera pose.
@param points2D List of image projections for the points
@param points3D List of 3D coordinates for the points
@param iterations Number of Levenberg-Marquard iterations to perform
@param lambda Increment of the diagonal elements for the estimated Hessian matrix
@param sigma standard deviation to the cost function (negative log-likelihood)

@return An improved camera pose.
@ingroup qvprojectivegeometry
*/
QVCameraPose optimizeReprojectionErrorForCameraPoseCauchy(const QVCameraPose &cameraPose, const QList<QPointF> &points2D, const QList<QV3DPointF> &points3D, const int iterations, const double lambda = 1e-5, const double sigma = 3.0);

#endif // QVREPROJECTIONERROR_H

