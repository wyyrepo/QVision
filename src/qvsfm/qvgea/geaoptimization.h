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

#ifndef GEAOPTIMIZATION_H
#define GEAOPTIMIZATION_H

#include <QHash>
#include <QList>
#include <QVCameraPose>
#include <QVDirectedGraph>
#include <qvprojective.h>

#define SO3_PARAMETRIZATION

// After a call to 'globalEpipolarAdjustment', these variables will contain the time spent in milliseconds by the GEA algorithm on:
//	gea_time_eval: the evaluation of the components of the second level system: Hessian matrix and objective vector.
//	gea_time_solve: the resolution of the second level system.
extern int gea_time_eval, gea_time_solve;

//@deprecated Use functions @ref getSquaredDLTMatrix and @ref getDLTMatrix to obtain the reduced matrices, and @ref globalEpipolarAdjustment2 to perform GEA optimization.

/*!
@brief Refine the camera poses using epipolar geometry constraints

This is the main function for GEA.
Refines the set of camera poses, provided a directed graph containing the
reduced M matrices representing the epipolar relationship between each pair of views
in the reconstruction.

@ingroup qvsfm
@param numIterations			Number of iterations to optimize the camera poses.
@param initialCameraPoses		Initial camera poses. One for each view.
@param reducedMatricesGraph		Directed graph containing a reduced matrix for each pair of views.
@param freeCameras				Vector containing a boolean for each camera, indicating wether this camera is fixed, or not in the optimization. Useful for incremental optimization.
@param lambda					Lambda parameter to increase the diagonal of the Hessian matrix.
@param adaptativeLambda			If true, the lambda value to increment the diagonal of the second level system is scaled with the mean value of the trace. Useful with reconstructions containing large number of views.
@param solveMethod				Method to solve the second level system. You need to configure QVision to use MKL or CHOLMOD (see file 'config.pri') in order to use MKL and CHOLMOD versions of the sparse solver.
@param secondLevelIterations	Number of iterations in the second level resolution of the linear system. Applied only when the param @ref solveMethod is QVMKL_ISS or QVSCG.

@return list of optimized camera poses.
*/
QList<QVCameraPose> globalEpipolarAdjustment(
                                        const int numIterations,
                                        const QList<QVCameraPose> &initialCameraPoses,
                                        const QVDirectedGraph<QVMatrix> &reducedMatricesGraph,
                                        const QVector<bool> &freeCameras,
                                        const double lambda = 1e-3,
                                        const bool adaptativeLambda = true,
                                        const TQVSparseSolve_Method solveMethod = DEFAULT_TQVSPARSESOLVE_METHOD,
                                        const int secondLevelIterations = 10
                                        );

/*!
@brief Refine the camera poses using epipolar geometry constraints

This is an overloaded function provided by convenience.
Every camera is included in the optimization, so no camera is fixed.

@see globalEpipolarAdjustment

@ingroup qvsfm
@param numIterations			Number of iterations to optimize the camera poses.
@param initialCameraPoses		Initial camera poses. One for each view.
@param reducedMatricesGraph		Directed graph containing a reduced matrix for each pair of views.
@param lambda					Lambda parameter to increase the diagonal of the Hessian matrix.
@param adaptativeLambda			If true, the lambda value to increment the diagonal of the second level system is scaled with the mean value of the trace. Useful with reconstructions containing large number of views.
@param solveMethod				Method to solve the second level system. You need to configure QVision to use MKL or CHOLMOD (see file 'config.pri') in order to use MKL and CHOLMOD versions of the sparse solver.
@param secondLevelIterations	Number of iterations in the second level resolution of the linear system. Applied only when the param @ref solveMethod is QVMKL_ISS or QVSCG.

@return list of optimized camera poses.
*/
QList<QVCameraPose> globalEpipolarAdjustment(
                                        const int numIterations,
                                        const QList<QVCameraPose> &initialCameraPoses,
                                        const QVDirectedGraph<QVMatrix> &reducedMatricesGraph,
                                        const double lambda = 1e-3,
                                        const bool adaptativeLambda = true,
                                        const TQVSparseSolve_Method solveMethod = DEFAULT_TQVSPARSESOLVE_METHOD,
                                        const int secondLevelIterations = 10
                                        );


/*!
@brief Incremental GEA refinement

This function applies the GEA refinement on the view poses of a reconstruction.
Unlike @see globalEpipolarAdjustment this function optimizes the pose of a reduced set of the views in the reconstruction, leaving the rest of the poses unchanged.
It can be used to perform real-time camera tracking.
Optimizing the last views in the reconstruction (for example, the last 10 views added to the map) can be performed in real time, and prevents tracing failure significantly.

@ingroup qvsfm
@param numIterations Number of iterations to optimize the camera poses.
@param initialCameraPoses Initial camera poses. One for each view.
@param reducedMatricesGraph Directed graph containing a reduced matrix for each pair of views.
@param numFreeCameras Number of views to optimize. The optimized views are the last ones inserted in the reconstruction (tail of initialCameraPoses list).
@param lambda Lambda parameter to increase the diagonal of the Hessian matrix.
@param adaptativeLambda If true, the lambda value added to the diagonal of the Hessian at the second level system is scaled with the mean value of the trace. Useful with reconstructions containing large number of views.
@param solveMethod Method to solve the second level system. You need to configure QVision to use MKL or CHOLMOD (see file 'config.pri') in order to use MKL and CHOLMOD versions of the sparse solver.
@param secondLevelIterations Number of iterations in the second level resolution of the linear system. Applied only when the param @ref solveMethod is QVMKL_ISS or QVSCG.

@return list of optimized camera poses.
*/
QList<QVCameraPose> incrementalGEA(	const int numIterations,
                    const QList<QVCameraPose> &initialCameraPoses,
                    const QVDirectedGraph<QVMatrix> &reducedMatricesGraph,
                    const int numFreeCameras = 1,
                    const double lambda = 1e-3,
                    const bool adaptativeLambda = true,
                    const TQVSparseSolve_Method solveMethod = DEFAULT_TQVSPARSESOLVE_METHOD,
                    const int secondLevelIterations = 10
                    );

/*!
@brief Gets the reduced matrices for a reconstruction.

This function obtains the reduced matrices corresponding to each view pair in a reconstruction, provided the set of point correspondences between those view pairs.

@param pointLists Contains the lists of point correspondences.
@param normalize Perform pre-normalization of the point matchings.
@param decomposition_method Select which decomposition of the reduced matrices is performed.
@param gsl Select GSL to perform the decomposition. If false, LAPACK is used where available, which is a slower option for the size of the matrices to decompose (\f$ 9 \times 9 \f$).
@param choleskyLambda Adds this value to the diagonal elements of the reduced matrix before decomposing. Avoid decomposing singular matrices using cholesky.
@param minPointCorrespondences Only reduced measurement matrices estimated from a number of point correspondences equal or larger to this value are included in the resulting graph.

@return A directed graph containing the reduced matrices.
@ingroup qvsfm
*/
QVDirectedGraph<QVMatrix>  getReducedMatrices(	const QVDirectedGraph< QList<QPointFMatching> > &pointLists,
                        const bool normalize = true,
                        const TGEA_decomposition_method decomposition_method = GEA_CHOLESKY_DECOMPOSITION,
                        const bool gsl = true,
                        const double choleskyLambda = 0.0,
                        const int minPointCorrespondences = 0
                        );

/*!
@brief Gets the reduced matrices for a reconstruction from the list of point correspondences detected between each view-pair in a reconstruction.

This function obtains the reduced matrices corresponding to each view pair in a reconstruction, provided the set of point correspondences between those view pairs.

@param pointLists Contains the lists of point correspondences.
@param normalize Perform pre-normalization of the point matchings.
@param decomposition_method Select which decomposition of the reduced matrices is performed.
@param gsl Select GSL to perform the decomposition. If false, LAPACK is used where available, which is a slower option for the size of the matrices to decompose (\f$ 9 \times 9 \f$).
@param choleskyLambda Adds this value to the diagonal elements of the reduced matrix before decomposing. Avoid decomposing singular matrices using Cholesky decomposition.
@param minPointCorrespondences Only reduced measurement matrices estimated from a number of point correspondences equal or larger to this value are included in the resulting graph.

@return A directed graph containing the reduced matrices.
@ingroup qvsfm
*/
QVDirectedGraph<QVMatrix>  getReducedMatrices(	const QVDirectedGraph< QVector<QPointFMatching> > &pointLists,
                        const bool normalize = true,
                        const TGEA_decomposition_method decomposition_method = GEA_CHOLESKY_DECOMPOSITION,
                        const bool gsl = true,
                        const double choleskyLambda = 0.0,
                        const int minPointCorrespondences = 0
                        );


/*!
@brief Obtains the list of point correspondences detected between each view-pair in a reconstruction.

This function obtains the reduced matrices corresponding to each view pair in a reconstruction, provided the set of point correspondences between those view pairs.

@param pointProjections Data structure containing the point projections for each 3D point and view where it is visible.
@param numCams Number of total views in the reconstruction.
@param munPointCorrespondences Do not return point correspondence lists containing less than this quantity of point matchings.
@return A directed graph containing the lists of point correspondences.
@ingroup qvsfm
*/
QVDirectedGraph< QList<QPointFMatching> > getPointMatchingsLists(const QList<QHash<int, QPointF> > pointProjections, const int numCams, const int minPointCorrespondences = 0);

/*!
@brief Obtains the list of point correspondences detected between each view-pair in a reconstruction.

This function obtains the reduced matrices corresponding to each view pair in a reconstruction, provided the set of point correspondences between those view pairs.

@param pointProjections Data structure containing the point projections for each 3D point and view where it is visible.
@param numCams Number of total views in the reconstruction.
@param munPointCorrespondences Do not return point correspondence lists containing less than this quantity of point matchings.
@return A directed graph containing the lists of point correspondences.
@ingroup qvsfm
*/
QVDirectedGraph< QVector<QPointFMatching> > getPointMatchingsListsVec(const QList<QHash<int, QPointF> > pointProjections, const int numCams, const int minPointCorrespondences = 0);

#ifndef DOXYGEN_IGNORE_THIS
// For testing and debug only.
QVDirectedGraph< QList<QPointFMatching> > pointMatchingsListOld(const QList<QHash<int, QPointF> > pointProjections, const int numCams);

QList< QHash< int, QPointF > > storePointMatchingsInTrackingContainer(const QVDirectedGraph< QVector<QPointFMatching> > &matchingLists);

#endif // DOXYGEN_IGNORE_THIS

#endif // GEAOPTIMIZATION_H

