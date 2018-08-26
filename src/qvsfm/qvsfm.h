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

#ifndef QVSFM_H
#define QVSFM_H

#include <QVIndexPair>
#include <qvprojective.h>
#include <qvsfm/qvgea/geaoptimization.h>
#include <qvsfm/laSBA/laSBAWrapper.h>

/*!
@brief Corrects linear intrinsic calibration from a set of point projections.

@ingroup qvsfm
@todo Document this.
*/
QList< QHash< int, QPointF> > correctIntrinsics(const QList< QVMatrix > &Ks, const QList< QHash< int, QPointF> > &pointsProjections);


/*!
@brief Test correct camera cheirality.

@ingroup qvsfm
@todo Document this.
*/
bool testCheirality(const QList<QVCameraPose> cameraPoses, const QList< QHash< int, QPointF> > calibratedPointsProjections);

/*!
@brief Swaps the cheirality of the camera poses and 3D points contained in a SfM reconstruction.

@ingroup qvsfm
@todo Document this.
*/
void invertCheirality(QList<QVCameraPose> &cameraPoses, QList<QV3DPointF> &points3D);

/*!
@brief Evaluate the mean reprojection error of a reconstruction.

@ingroup qvsfm
@todo Document this.
*/
double reconstructionError(	const QList<QVCameraPose> &cameraPoses,
				const QList<QV3DPointF> &points3D,
				const QList< QHash<int, QPointF> > &pointProjections);


/*!
@brief Evaluate the mean reprojection error of a reconstruction.

This is an overloaded version of the function @ref reconstructionError which evaluates the reprojection error of a list of camera poses and a set of point trackings, estimating the point locations with a linear initialization.

@ingroup qvsfm
@todo Document this.
*/
double reconstructionError(	const QList<QVCameraPose> &cameraPoses, const QList< QHash<int, QPointF> > &pointProjections);
double reconstructionError(	const QList<QVCameraPose> &cameraPoses, const QList< QHash<int, QPointF> > &pointProjections, const QVector<bool> &evaluateTracking);

/*!
@brief Evaluate the mean reprojection error of a pair-wise reconstruction.

@ingroup qvsfm
@todo Document this.
*/
double reconstructionError(	const QList<QVCameraPose> &cameraPoses,
							const QList<QV3DPointF> &points3D,
							const QList< QHash<int, QPointF> > &pointProjections,
							const QVector<bool> &evaluateTracking);

/*!
@brief Evaluate the mean reprojection error of a pair-wise reconstruction.

@ingroup qvsfm
@todo Document this.
*/
double reconstructionError(const QVMatrix &Rt1, const QVMatrix &Rt2, const QList<QV3DPointF> &points3D, const QVector<QPointFMatching> &matchings);

/*!
@brief Evaluate the residuals of a reconstruction.

@ingroup qvsfm
@todo Document this.
*/
QVVector reconstructionErrorResiduals(	const QList<QVCameraPose> &cameraPoses,
										const QList<QV3DPointF> &points3D,
										const QList< QHash<int, QPointF> > &pointTrackings);

/*!
@brief Check for NaN values in a list of camera poses

@returns true if any of the parameters of one or more of the camera poses contains a NaN value, false otherwise.
@ingroup qvsfm
@todo Document this.
*/
bool checkForNaNValues(const QList<QVCameraPose> &cameraPoses);

/*!
@brief Check for NaN values in a list of 3D points.

@returns true if any of the parameters of one or more of the points contains a NaN value, false otherwise.
@ingroup qvsfm
@todo Document this.
*/
bool checkForNaNValues(const QList<QV3DPointF> &points3D);

/*!
@brief Check for NaN values in a list of point trackings.

@returns true if any of the projections in the tracks contains a NaN value, false otherwise.
@ingroup qvsfm
@todo Document this.
*/
bool checkForNaNValues(const QList< QHash< int, QPointF > > &pointTrackings);

/*!
@brief Initialize the projection matrices of two views in a reconstruction, provided a list of point matchings.

@param matchings List of point matchings detected between the two views.
@param Rt1	Estimated projection matrix for first image.
@param Rt2	Estimated projection matrix for second image.
@returns true if the estimation was successful, false otherwise.
@ingroup qvsfm
@todo Document this.
*/
bool linearCameraPairInitialization(const QVector<QPointFMatching> &matchings, QVMatrix &Rt1, QVMatrix &Rt2);

#ifndef DOXYGEN_IGNORE_THIS
//typedef QPair<int, int> QVIndexPair;
// Returns matchings from A to C.
QVector<QVIndexPair> combineMatchingLists(const QVector<QVIndexPair> &matchingsAB, const QVector<QVIndexPair> &matchingsBC);
void estimate3DPointsMeanAndVariance(const QList<QV3DPointF> &points3D, QV3DPointF &mean, double &variance);

double squaredReprojectionErrorResiduals(	const QV3DPointF &point3D,
											const QList<QVCameraPose> &cameraPoses,
											const QHash<int, QPointF> &pointProjections);

QVVector squaredReprojectionErrorResidualsNew(	const QV3DPointF &point3D,
												const QList<QVCameraPose> &cameraPoses,
												const QHash<int, QPointF> &pointProjections);

double squaredReprojectionErrorResiduals(	const QV3DPointF &point3D,
											const QVCameraPose &cameraPose,
											const QPointF &pointProjection);
#endif // DOXYGEN_IGNORE_THIS

#endif
