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

#ifndef QVEPIPOLAR_H
#define QVEPIPOLAR_H

#include <qvmath.h>
#include <QVMatrix>
#include <qvprojective.h>

#define	MIN_FUNDAMENTAL_MATRIX_NORM	1e-16

#ifndef DOXYGEN_IGNORE_THIS
// Alternative and faster function for 'get8PointsCoefficientMatrix'.
QVMatrix getDLTMatrix(const QVector<QPointFMatching> &matchings);

// Alternative and faster function for 'getTransposeProductOf8PointsCoefficientMatrix'.
QVMatrix getSquaredDLTMatrix(const QVector<QPointFMatching> &matchings,
											const QPointF &m0c = QPointF(0.0, 0.0),
											const QPointF &m1c = QPointF(0.0, 0.0),
											const double &scale0 = 1.0,
											const double &scale1 = 1.0);
#endif // DOXYGEN_IGNORE_THIS

/*!
@brief Obtains the fundamental matrix between two images using the <a href="http://en.wikipedia.org/wiki/Eight-point_algorithm">8-point algorithm</a>.

This function obtains the fundamental matrix between two images using the <a href="http://en.wikipedia.org/wiki/Eight-point_algorithm">8-point algorithm</a>.
It is faster than the overloaded version.

@param matchings list of 8 or more point matchings.
@param F output fundamental matrix.
@param svdMethod method used in several SVD internal decompositions of the algorithm.
@returns True if the fundamental matrix was found, false otherwise.
@ingroup qvprojectivegeometry
*/
bool computeFundamentalMatrix(const QVector<QPointFMatching> &matchings, QVMatrix &F, const TQVSVD_Method svdMethod = DEFAULT_TQVSVD_METHOD);

/*!
@brief Evaluate symmetric epipolar error for a fundamental matrix defined between two images and one image point correspondence.

This function returns the epipolar error defined for the image point correspondence with the following expression:

\f$ e = d(x, Fx') + d(x', xF) \f$

Where \f$ d(p,l) \f$ is the euclidean distance in the 2D plane between the point \f$ p \f$ and the line \f$ l \f$.

@param F Fundamental matrix.
@param matching Image point matching.
@returns The symmetric epipolar distance \f$ e \f$.
@ingroup qvprojectivegeometry
*/
double symmetricEpipolarDistance(const QVMatrix &F, const QPointFMatching &matching);


/*!
@brief Evaluate symmetric epipolar errors for a fundamental matrix defined between two images and a list of image point correspondences.

This function returns a vector containing the symmetric epipolar errors defined for the image point correspondences with the following expression:

\f$ e_i = d(x_i, Fx'_i) + d(x'_i, x_i F) \f$

Where \f$ d(p,l) \f$ is the euclidean distance in the 2D plane between the point \f$ p \f$ and the line \f$ l \f$.

@param F fundamental matrix.
@param matchings list of point matchings.
@returns A vector, containing the distance \f$ e_i \f$ for each matching.
@ingroup qvprojectivegeometry
*/
QVVector symmetricEpipolarDistance(const QVMatrix &F, const QVector<QPointFMatching> &matchings);

/*! @brief Iterative matching selection for local optimization in LO-RANSAC.

This algorithm implements the method used in LO-RANSAC, as described in [1], to eliminate iteratively the outliers of a set of image point matchings.

The procedure is as follows:
<ol>
<li>Estimate fundamental matrix \f$ F\f$, and the error for each point correspondence \f$ e_i \f$.</li>
<li>If the maximal error is below a threshold value <i>maxEE</i>, the algorithm is successful, and provides the remaining point matchings.</li>
<li>Else, the algorithm discards matchings with an error \f$ e_i \f$ above two times the median value of the errors, or above the threshold value <i>maxEE</i>.</li>
<li>If no matchings were discarded, the algorithm fails, else the algorithms returns to point 1.</li>
</ol>

<p>[1] <i>Locally optimized RANSAC</i>. O Chum, J Matas, J Kittler</p>

@param matchings list of input matchings
@param result remaining point matchings after selection.
@param maxEE threshold value for maximal admissible epipolar error.
@param minInliers minimal number of inliers admissible.
@returns true if successful, false if the algorithm failed.
*/
bool iterativeLocalOptimization(const QList<QPointFMatching> &matchings,  QList<QPointFMatching> &result, const double maxEE = 1.0, const int minInliers = 32);

#endif // QVEPIPOLAR_H

