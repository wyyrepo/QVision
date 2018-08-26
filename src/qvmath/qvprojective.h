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

#ifndef QVPROJECTIVE_H
#define QVPROJECTIVE_H

#include <qvmath.h>
#include <QVMatrix>
#include <QHash>
#include <QVEuclideanMapping3>
#include <QV3DPointF>
#include <QVCameraPose>

#ifdef QVIPP
#include <QVImage>
#include <qvipp.h>
#endif // QVIPP

#include <qvmath/qvepipolar.h>
#include <qvmath/qvreprojectionerror.h>

/// @file
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// HOMOGRAPHY CALIBRATION FUNCTION ///////////////////////////////////////////////

void homogenizePoints(const QList< QPointFMatching > &matchings,
	QVMatrix &premult, QVMatrix &postmult,
	QList< QPair<QPointF, QPointF> > &homogeneizedPairs);

/*
@brief Obtains an homography from two lists of corresponding points.
@ingroup qvprojectivegeometry

This function returns the homography that maps the points from a source position to a
destination position, according to a projective transformation.

@deprecated Use @ref ComputeProjectiveHomography instead
@param sourcePoints list of source points.
@param destinationPoints list of destination points.
*/
//QVMatrix ComputeHomography(const QList<QPointF> &sourcePoints, const QList<QPointF> &destPoints);

/*!
@brief Obtains a planar homography from a list of point correspondences.

This function obtains the homography matrix \f$ H \f$ corresponding to the <a href="http://en.wikipedia.org/wiki/Projective_transformation">projective transformation</a> which most closely map a set of four or more point correspondences.

These projective homographies can be used to obtain a frontal view of any planar figure appearing in an image.
The following is an example of planar rectification:

@image html rectification_homography.png

Image on the left is the original picture obtained with a pin-hole camera.
Image on the right was obtained mapping the pixels in the original image with the planar homography obtained using the function @ref ComputeProjectiveHomography.

The homography \f$ H^* \f$is obtained identifying the four corners of the chessboard, and their corresponding coordinates in the plane of the chessboard:

@code
QList< QPair<QPointF, QPointF> > matchings;
matchings.append(QPair<QPointF, QPointF>(QPointF(-171,109),	QPointF(-100,+100)));
matchings.append(QPair<QPointF, QPointF>(QPointF(-120,31),	QPointF(-100,-100)));
matchings.append(QPair<QPointF, QPointF>(QPointF(117,53),	QPointF(+100,-100)));
matchings.append(QPair<QPointF, QPointF>(QPointF(11,115),	QPointF(+100,+100)));

const QVMatrix H = ComputeProjectiveHomography(matchings);
@endcode

by solving the following inequation:

\f$ p' \propto H p \f$

maximizing the average of the algebraic reprojection error for the point matchings \f$ \left\{ p_i \mapsto p_i' \right\} _{i=1..n} \f$ contained in the <i>matchings</i> list:

\f$  H^* =  \arg\max \displaystyle\sum\limits_{i=0}^n \left[ p_i' \right] _\times H p_i \f$

The points in the original image can be mapped with the homography matrix \f$ H \f$ using the @ref ApplyHomography functions.

@see ApplyHomography(const QVMatrix &, const QPointF &)
@see ApplyHomography(const QVMatrix &, const QList<QPointF> &)

@param matchings list of point matchings from the original location, to the destination location.
@param H output homography matrix
@returns false if the number of matchings is less than 4. True otherwise.
@ingroup qvprojectivegeometry
*/
bool computeProjectiveHomography(const QList< QPointFMatching > &matchings, QVMatrix &H);

#ifndef DOXYGEN_IGNORE_THIS
bool computeProjectiveHomography2(const QList< QPointFMatching > &matchings, QVMatrix &H);
#endif // DOXYGEN_IGNORE_THIS

/*!
@brief Obtains a planar homography from a list of point correspondences.

@deprecated This version of @ref computeProjectiveHomography is deprecated. Use @ref computeProjectiveHomography(const QList<QPointFMatching>&,QVMatrix&) instead

@param matchings list of point matchings from the original location, to the destination location.
@ingroup qvprojectivegeometry
*/
QVMatrix computeProjectiveHomography(const QList< QPointFMatching > &matchings);

/*!
@brief Obtains an affine homography from a list of point correspondences.

This function obtains the homography matrix \f$ M \f$ which most closely maps the source points to their destination, in the input point matching list.
This homography matrix corresponds to an <a href="http://en.wikipedia.org/wiki/Affine_transformation">affine transformation</a>.

The function returns the matrix corresponding to the planar homography, from a list of three or more point correspondences between the location of those points at the source plane and their location in the destination plane.

Usage:
@code
QList< QPair<QPointF, QPointF> > matchings;
matchings.append(QPair<QPointF, QPointF>(QPointF(-171,109),	QPointF(-100,+100)));
matchings.append(QPair<QPointF, QPointF>(QPointF(-120,31),	QPointF(-100,-100)));
matchings.append(QPair<QPointF, QPointF>(QPointF(117,53),	QPointF(+100,-100)));

const QVMatrix M = ComputeAffineHomography(matchings);
@endcode

Any point \f$ p \f$ from the 2D plane can be mapped to another point in the plane \f$ q \f$ with an affine matrix \f$ M \f$ using the following C++ code:

@code
QPointF q = M * QVVector::homogeneousCoordinates(p);
@endcode

Or by using the @ref ApplyHomography functions.

@see ApplyHomography(const QVMatrix &, const QPointF &)
@see ApplyHomography(const QVMatrix &, const QList<QPointF> &)

@param matchings list of point matchings from the original location, to the destination location.
@ingroup qvprojectivegeometry
*/
QVMatrix computeAffineHomography(const QList< QPointFMatching > &matchings);

/*!
@brief Obtains a similar homography from a set of inter-image point matchings.

A similar transformation is obtained by composing an euclidean transformation with a scaling.

This function obtains a similar mapping between the source an destination locations of a set of point matchings.
The mapping is returned as a \f$ 3 \times 3 \f$ matrix which can be multiplied to the source location of each mapping point in homogeneous coordinates, to obtain the location of the mapped point.

The returned matrix has the following structure:

\f$	H = \left( \begin{array}{ccc}
	s \cos(\theta)	& -s \sin (\theta)	& t_x	\\
	s \sin(\theta)	& s \cos (\theta)	& t_y	\\
	0		& 0			& 1 \end{array}
	\right)
\f$

Where \f$ s \f$ is the scale factor, and \f$ \theta \f$ and \f$ (t_x, t_y) \f$ are the rotation angle and translation vector of the euclidean mapping respectively.

@ingroup qvprojectivegeometry
*/
QVMatrix computeSimilarHomography(const QList< QPointFMatching > &matchings);

/*
@brief Obtains the fundamental matrix between two images using the <a href="http://en.wikipedia.org/wiki/Eight-point_algorithm">8-point algorithm</a>.

This function obtains the fundamental matrix that models the epipolar geometry between two images from a set of point correspondences.

This function performs a prior normalization of the point projections, to obtain valid and better fundamental matrices.
This normalization includes a correction to move the mean of the point projections to the origin of coordinates, and a posterior whitening.

The code for this function is based on the 8-point algorithm implementation contained in the function <i>cvFindfundamentalMat</i> from the OpenCV.

@param matchings list of 8 or more point matchings
@param normalize perform normalization of the coefficient matrix rows independently
@ingroup qvprojectivegeometry
*/
#ifndef DOXYGEN_IGNORE_THIS
QVMatrix computeFundamentalMatrix(const QList<QPointFMatching> &matchings, const bool normalize = false);
#endif // DOXYGEN_IGNORE_THIS

/*!
@brief Obtains the fundamental matrix between two images, using the 8 point algorithm.

This function performs point normalization to robustly obtain the F matrix.

@note This function is based on functionality from the OpenCV library. Thus compatibility
with that library must be enabled to be available.
@param matchings list containing at least 8 image point correspondences.

@deprecated Use @ref computeFundamentalMatrix to estimate the fundamental matrix using the 8 point algorithm, or call directly to the OpenCV cvFindFundamentalMat function.
@ingroup qvprojectivegeometry
*/
#ifdef QVOPENCV
QVMatrix cvFindFundamentalMat(const QList< QPointFMatching > &matchings);
#endif // QVOPENCV

/*!
@brief Maps a point using an homography

This function maps a point \f$ (x, y) \f$ in the 2D plane, using a planar homography. The homography is represented as a \f$ H_{3 \times 3} \f$ matrix. These matrices can be obtained using methods like @ref ComputeSimilarHomography, @ref ComputeProjectiveHomography, or @ref ComputeAffineHomography from a set of point correspondences between the original 2D plane, and the mapped plane.

The output of the function is a point \f$ (x', y') \f$ which satisfies the following equation:

\f$ \left(\begin{array}{c} x' \\ y' \\ 1 \end{array}\right) \propto H \left(\begin{array}{c} x \\ y \\ 1 \end{array}\right) \f$

@see ComputeSimilarHomography
@see ComputeAffineHomography
@see ComputeProjectiveHomography

@param homography The homography transformation matrix
@param point Point to apply the homography transformation
@ingroup qvprojectivegeometry
*/
QPointF applyHomography(const QVMatrix &homography, const QPointF &point);


/*!
@brief Maps a set of points using an homography

This is an overloaded version of the @ref ApplyHomography(const QVMatrix &, const QPointF &) function provided by convenience. This function takes a list of points from the 2D plane, and an homography matrix as inputs. The output will be a list of points obtained by mapping the points from the input list, using the homography.

@see ApplyHomography(const QVMatrix &, const QPointF &)
@see ComputeSimilarHomography
@see ComputeAffineHomography
@see ComputeProjectiveHomography

@param homography The homography transformation matrix
@param sourcePoints Points to apply the homography transformation
@ingroup qvprojectivegeometry
*/
QList<QPointF> applyHomography(const QVMatrix &homography, const QList<QPointF> &sourcePoints);

/*!
@brief Performs an homography distortion on an image

The homography is represented as a \f$ H_{3 \times 3} \f$ matrix. These matrices can be obtained using methods like @ref ComputeSimilarHomography, @ref ComputeProjectiveHomography, or @ref ComputeAffineHomography.

This function takes a single channel image, and an homography matrix as inputs. Each point  \f$ (x, y) \f$ in the input image is mapped to its location in the resulting image  \f$ (x', y') \f$  using the homography \f$ H \f$ as follows:

\f$ \left(\begin{array}{c} x' \\ y' \\ 1 \end{array}\right) \propto H \left(\begin{array}{c} x \\ y \\ 1 \end{array}\right) \f$

@see ComputeSimilarHomography
@see ComputeAffineHomography
@see ComputeProjectiveHomography

@param homography The homography transformation matrix
@param image The input image to distort
@param interpolation Type of interpolation. Possible values for this parameter are:
	- IPPI_INTER_NN. Nearest neighbor interpolation
	- IPPI_INTER_LINEAR. Linear interpolation
	- IPPI_INTER_CUBIC. Cubic interpolation

@note This function is based on functionality from the Intel IPP library. Thus compatibility
with that library must be enabled to be available.

@ingroup qvprojectivegeometry
*/
#ifdef QVIPP
QVImage<uChar, 1> applyHomography(const QVMatrix &homography, const QVImage<uChar, 1> &image, const int interpolation = IPPI_INTER_CUBIC);
#endif // QVIPP

/*!
@brief Performs an homography distortion on an image

The homography is represented as a \f$ H_{3 \times 3} \f$ matrix. These matrices can be obtained using methods like @ref ComputeSimilarHomography, @ref ComputeProjectiveHomography, or @ref ComputeAffineHomography.

This function takes a three channel image, and an homography matrix as inputs. Each point \f$ (x, y) \f$ in the input image is mapped to its location in the resulting image  \f$ (x', y') \f$  using the homography \f$ H \f$ as follows:

\f$ \left(\begin{array}{c} x' \\ y' \\ 1 \end{array}\right) \propto H \left(\begin{array}{c} x \\ y \\ 1 \end{array}\right) \f$

@see ComputeSimilarHomography
@see ComputeAffineHomography
@see ComputeProjectiveHomography

@param homography The homography transformation matrix
@param image The input image to distort
@param interpolation Type of interpolation. Possible values for this parameter are:
	- IPPI_INTER_NN. Nearest neighbor interpolation
	- IPPI_INTER_LINEAR. Linear interpolation
	- IPPI_INTER_CUBIC. Cubic interpolation

@note This function is based on functionality from the Intel IPP library. Thus compatibility
with that library must be enabled to be available.
@ingroup qvprojectivegeometry
*/
#ifdef QVIPP
QVImage<uChar, 3> applyHomography(const QVMatrix &homography, const QVImage<uChar, 3> &image, const int interpolation = IPPI_INTER_CUBIC);
#endif // QVIPP

/*
@brief Function to test if a 3x3 matrix corresponds to an homography.

Every homography matrix corresponding to a perspective deformation from one plane to another should satisfy some constrains. The most important is that its two first columns
should be perpendicular, and with a similar size, because for the matrix to correspond to an homography, they should be contained in a base of a rotated coordinate system.
Given the following homography matrix:

\f$ H = \left[ R_1 R_2 -CR^t \right] \f$

The error value returned by this function for it will be:

\f$ error = \left| \frac{ \|R_1\| - \|R_2\| }{ \|R_1\| + \|R_2\| } \right| + \left| \frac{ R_1 \cdot R_2}{ \|R_1\| \|R_2\| } \right| \f$

That error is a measure of the difference of sizes between the norm of the two column vectors of the homography, corresponding to the two first columns of the rotation matrix, and their dot product. When both values are close to zero, the matrix corresponds to an homography, and it won't otherwise.

A good method to prove that a matrix corresponds to an homography using this function, can be done testing the return value with a threshold of approximately 0.3. If the return value of this function for a matrix is lower than this threshold, that matrix is likely to correspond to an homography, and is not likely to correspond otherwise.

@param homography a possible homography matrix.
@return a value close to 1 when the matrix does not corresponds to an homography, and close to 0 when it is close to be an homography.
@ingroup qvprojectivegeometry
*/
#ifndef DOXYGEN_IGNORE_THIS
double HomographyTestError(const QVMatrix &homography);
#endif // DOXYGEN_IGNORE_THIS

/*
@todo write documentation for this function

@ingroup qvprojectivegeometry
*/
#ifndef DOXYGEN_IGNORE_THIS
void GetExtrinsicCameraMatrixFromHomography(const QVMatrix &K, const QVMatrix &H, QVMatrix &M4x4);
#endif // DOXYGEN_IGNORE_THIS

/*
@brief Diagonal intrinsic camera matrix calibration


This function obtains a diagonal intrinsic camera matrix, consisting on the focal distance only. This matrix is such that

\f$ H = K \left[ R | t\right]	\f$

Where \f$ R \f$ is a rotation matrix. This function returns a direct approximation for the \f$ K \f$ matrix.

@todo rename to GetDirectCameraIntrinsicsFromPlanarHomography
@see GetIntrinsicCameraMatrixFromHomography
@ingroup qvprojectivegeometry
*/
//void GetDirectIntrinsicCameraMatrixFromHomography(const QVMatrix &H, QVMatrix &K);

/*
@brief Diagonal intrinsic camera matrix calibration

This function obtains a diagonal intrinsic camera matrix, consisting on the focal distance only. This matrix is such that

\f$ H = K \left[ R | t\right]	\f$

Where \f$ R \f$ is a rotation matrix. This matrix is obtained with a minimization process, so its result is more precise than that obtained with @ref GetDirectIntrinsicCameraMatrixFromHomography function.

@see GetDirectIntrinsicCameraMatrixFromHomography
@ingroup qvprojectivegeometry
*/
//void GetIntrinsicCameraMatrixFromHomography(const QVMatrix &H, QVMatrix &K,
//	double focal = 3, const double maxFocal = 50, const int maxIterations = 100, const double maxError = 0.00001);

/*
@ingroup qvprojectivegeometry
@todo write documentation for this function
*/
//void CalibrateCameraFromPlanarHomography(const QVMatrix &H, QVMatrix &K, QVMatrix &Rt);

/*
@brief Obtains the intrinsic camera matrix from a planar homography

This functions obtains the intrinsic calibration matrix \f$ K \f$ corresponding to a simple pinhole camera model. The intrinsic camera matrix has only one free parameter, related to the focal distance of the camera:

\f$
K = \left(\begin{array}{ccc}
f	& 0	& 0	\\
0	& f	& 0	\\
0	& 0	& 1	\\
\end{array}\right)
\f$

This function should receive a planar homography corresponding to the mapping of a set of know template points, to an image frame captured with the camera containing a view of that template.

The following is an example of a full intrinsic camera calibration, knowing a set of point matchings between the template image and the input image read from the camera:

@code
[...]
QList< QPointFMatching > matchings;
matchings.append(QPointFMatching(QPointF(-171,109),	QPointF(-100,+100)));
matchings.append(QPointFMatching(QPointF(-120,31),	QPointF(-100,-100)));
matchings.append(QPointFMatching(QPointF(117,53),	QPointF(+100,-100)));
matchings.append(QPointFMatching(QPointF(11,115),	QPointF(+100,+100)));

QVMatrix H, K;
H = ComputeProjectiveHomography(matchings);
GetPinholeCameraIntrinsicsFromPlanarHomography(H, K);
[...]
@endcode

For further understanding of the planar homography calibration process, see @ref ComputeProjectiveHomography function documentation.

@param H			Input planar homography.
@param K			Matrix to store the intrinsic camera matrix
@param iterations		Cumber of iterations to perform camera calibration
@param maxGradientNorm		Minimal value of the gradient size (norm 2) to stop the minimization when reached.
@param step			Corresponds to parameter <i>step</i> for the <i>gsl_multimin_fdfminimizer_set</i> function.
@param tol			Corresponds to parameter <i>tol</i> for the <i>gsl_multimin_fdfminimizer_set</i> function.

@return a value close to 1 when the matrix does not correspond to an homography, and close to 0 when it is close to be an homography.
@see ComputeProjectiveHomography
@ingroup qvprojectivegeometry
*/
//void GetPinholeCameraIntrinsicsFromPlanarHomography(	const QVMatrix &H, QVMatrix &K, const int iterations = 100,
//							const double maxGradientNorm = 1e-3, const double step = 0.01, const double tol = 1e-4);

/*
@brief Obtains the canonical matrices corresponding to an essential matrix

See section 9.6.2 from <i>Multiple View Geometry in Computer Vision</i>.

@param E The input essential matrix.
@return A list containing the possible canonical camera matrices.
@ingroup qvprojectivegeometry

@deprecated Use @ref getCameraPosesFromEssentialMatrix instead.
*/
#ifndef DOXYGEN_IGNORE_THIS
QList<QVMatrix> getCanonicalCameraMatricesFromEssentialMatrix(const QVMatrix &E);
#endif // DOXYGEN_IGNORE_THIS

// TODO: document this function.
#ifndef DOXYGEN_IGNORE_THIS
bool getCorrectCameraPoseTestingCheirality(const QPointFMatching matching, const QVMatrix &R1, const QVMatrix &R2, const QV3DPointF t, bool &R1IsCorrect, bool &tIsPossitive);
#endif // DOXYGEN_IGNORE_THIS

/*!
@brief Decomposes an essential matrix and obtains the corresponding pair of camera poses.

This function obtains the four possible pairs of valid camera poses from an essential matrix:

 - \f$ \left( I_3|0 \right) \f$ and \f$ \left( R_1|t \right) \f$
 - \f$ \left( I_3|0 \right) \f$ and \f$ \left( R_1|-t \right) \f$
 - \f$ \left( I_3|0 \right) \f$ and \f$ \left( R_2|t \right) \f$
 - \f$ \left( I_3|0 \right) \f$ and \f$ \left( R_2|-t \right) \f$

These camera poses satisfy the following equation:

\f$ E \propto \left[ t \right] _\times R_i \f$

This function returns the two rotation matrices (\f$ R_1 \f$ and \f$ R_2 \f$) and the vector \f$ t \f$ from those expressions.

See section 9.6.2 from <i>Multiple View Geometry in Computer Vision</i> for more info on decomposing the essential matrix to obtain the camera poses.

\note The function @ref testCheiralityForCameraPoses can be used to test which one of these configurations corresponds to a valid 3D reconstruction.

@param E The input essential matrix.
@param R1 Output param containing the first possible rotation matrix.
@param R2 Output param containing the second possible rotation matrix.
@param t Output param containing the translation vector.

@ingroup qvprojectivegeometry
*/
void getCameraPosesFromEssentialMatrix(const QVMatrix &E, QVMatrix &R1, QVMatrix &R2, QV3DPointF &t);

/*!
@brief Tests if two camera poses satisfy the cheirality condition for the reconstruction of a 3D point.

This function reconstructs a 3D point from its projections on two image views, and test whether the triangulated location is in front or behind of the cameras.
If the point is not in front of both cameras, the 3D reconstruction obtained from these camera poses will be incorrect.

See chapter 20 from <i>Multiple View Geometry in Computer Vision</i> for more info on cheirality.

@param sourceRt Camera pose for the first view.
@param sourceProjection Projection of the point used to test cheirality on the first view.
@param destRt Camera pose for the second view.
@param destProjection Projection of the point used to test cheirality on the second view.

@returns True if the point reconstruction is in front of both camera poses, false otherwise.
@ingroup qvprojectivegeometry
@see getCameraPosesFromEssentialMatrix
*/
bool testCheiralityForCameraPoses(const QVMatrix &sourceRt, const QPointF &sourceProjection, const QVMatrix &destRt, const QPointF &destProjection);

/*
@brief Obtains the essential matrix corresponding to a canonical camera matrix

This method estimates the essential matrix of a two view scenario, provided the second camera matrix \f$ P_2 \f$, considering the first camera matrix as the identity: \f$ P_1 = \left[ I | 0 \right] \f$
See section 9.6.1 from <i>Multiple View Geometry in Computer Vision</i>.

@param P The input canonical matrix.
@return The essential matrix corresponding to P.
@ingroup qvprojectivegeometry
*/
//QVMatrix getEssentialMatrixFromCanonicalCameraMatrix(const QVMatrix &P);

#ifndef DOXYGEN_IGNORE_THIS
QVMatrix getCameraMatrixFrom2D3DPointCorrespondences(const QList<QPointF> &points2d, const QList<QV3DPointF> &points3d);
#endif // DOXYGEN_IGNORE_THIS

#ifndef DOXYGEN_IGNORE_THIS
QV3DPointF triangulate3DPointFromNViews(const QList<QPointF> &points, const QList<QVMatrix> &Plist);
#endif // DOXYGEN_IGNORE_THIS

#ifndef DOXYGEN_IGNORE_THIS
QV3DPointF triangulate3DPointFrom2Views(const QPointF &point1, const QVMatrix &P1, const QPointF &point2, const QVMatrix &P2);
#endif // DOXYGEN_IGNORE_THIS

/*
@brief Eliminates errors in the rotation component of a canonical camera matrix using a QR decomposition

Function @ref refineExtrinsicCameraMatrixWithPolarDecomposition(const QVMatrix &) obtains a valid canonical camera
matrix <i>P = [R|t]</i> from a given initial approximation <i>P* = [R*|t*]</i>, using the Polar decomposition.

This function obtains a computationally more efficient approximation of the <i>P</i> matrix using a QR decomposition.
The rotation matrix <i>R</i> of the resulting <i>P</i> is not the closest rotation matrix to the initial <i>R*</i>
regarding the Frobenius norm \f$ ||R-R*||_F \f$.

Despite of that, this function can be used when a faster and slightly less accurate version of the best <i>P</i> is wanted.

@ingroup qvprojectivegeometry
*/
//QVMatrix refineExtrinsicCameraMatrixWithQRDecomposition(const QVMatrix &P);

/*
@brief Eliminates errors in the rotation component of a canonical camera matrix using a Polar decomposition

Given a matrix <i>P* = [R*|t*]</i> which approximates a canonical camera matrix, this function obtains the closest
valid canonical matrix \f$ P = [R|t]\f$. The rotation matrix of this valid canonical matrix must be an orthogonal matrix.
Thus it must fulfill:

	\f$ R^T R = I \f$

This function uses a correcting square 3x3 matrix <i>E<sup>-1</sup></i> that satisfies the following equation:

	\f$ E^-1 P* = P (1) \f$

This matrix <i>E<sup>-1</sup></i> also satisfies that the matrix <i>R</i> is the rotation matrix closest to <i>R*</i>
in a certain sense. Using the polar decomposition of <i>R*</i>, the function obtains the <i>E</i> which corrects it
to the closest valid rotation matrix <i>R</i> regarding the Frobenius norm \f$ ||R-R*||_F \f$.

The polar decomposition of the transpose of matrix <i>R*</i> is the following:

	\f$ R* = D^T U^T \f$

Where <i>U</i> is a rotation matrix and <i>D</i> is a positive-semidefinite Hermitian matrix. The matrix
<i>D<sup>T</sup></i> is used as the matrix <i>E</i>.

@ingroup qvprojectivegeometry
*/
#ifndef DOXYGEN_IGNORE_THIS
QVMatrix refineExtrinsicCameraMatrixWithPolarDecomposition(const QVMatrix &P);
#endif // DOXYGEN_IGNORE_THIS

// ---------------------------------------------------------------------------

/*!
@brief Obtains the camera matrix from a set of correspondences between 3D points and their respective image projections

The following formula models the relation between a set of points from the 3D world \f$ \{ X_i \}_{i=1..n} \f$ and their projections \f$ \{ x_i \}_{i=1..n} \f$ on an image:

\f$ x_i \propto P X_i \f$

This function uses a <a href="http://en.wikipedia.org/wiki/Direct_linear_transformation">direct linear transformation (DLT)</a> to obtain the camera matrix \f$ P \f$ from a given set of 3D points and their corresponding image points.

For more information about the linear camera resection, check chapter 7 of 'Multiple View Geometry in Computer Vision', section 7.1.

@param points2d List containing the points from the image.
@param points3d List containing the 3D points.
@return The camera matrix \f$ P \f$.
@ingroup qvprojectivegeometry
*/
QVMatrix linearCameraResection(const QList<QPointF> &points2d, const QList<QV3DPointF> &points3d);

/*
@brief Obtains the center of the camera from its rotation and a set of correspondences between 3D points and their respective image projections

This method provides a full camera resection by estimating the camera center, provided its as a rotation matrix \f$ R \f$. 

@param R Rotation matrix for the camera orientation.
@param points2d List containing the points from the image.
@param points3d List containing the 3D points.
@return The camera center.
@ingroup qvprojectivegeometry
*/
#ifndef DOXYGEN_IGNORE_THIS
QVVector linearCameraCenterResection(const QVMatrix &R, const QList<QPointF> &points2D, const QList<QV3DPointF> &points3D);
#endif // DOXYGEN_IGNORE_THIS

/*!
@brief Recovers the location of a 3D point from its projection on several views, and their corresponding camera matrices.

This is an overloaded version of the function @ref linear3DPointTriangulation(const QList<QVMatrix> &, const QList<QPointF> &), provided for convenience.

This version does not require that the point were visible from every camera in the input camera list. The point projections are provided in a QHash structure. Each
key in that structure is the index at the camera list of the camera corresponding to the point projection.

@see linear3DPointTriangulation(const QList<QVMatrix> &, const QList<QPointF> &);
@ingroup qvprojectivegeometry
*/
QV3DPointF linear3DPointTriangulation(const QVector<QVMatrix> &cameraMatrices, const QHash<int, QPointF> &projectionsOfAPoint, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);

/*!
@brief Recovers the location of a 3D point from its projection on several views, and their corresponding camera matrices.

Using the projection formula:

\f$ x \propto P X \f$

This function triangulates the location of the 3D point \f$ X \f$, provided the projections \f$ \{x_i\}_{i=1..n}\f$ on several views, and the camera matrices \f$ \{P_i\}_{i=1..n}\f$ for those
views.

The method used is described at section 12.2 from <i>Multiple View Geometry in Computer Vision</i>.

@param cameraMatrices list of camera matrices for the different views.
@param projectionsOfAPoint list of projections of the 3D point for the different views.
@return The triangulated location for the point.
@ingroup qvprojectivegeometry
*/
QV3DPointF linear3DPointTriangulation(const QList<QVMatrix> &cameraMatrices, const QList<QPointF> &projectionsOfAPoint, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);

/*!
@brief Recovers the location of a 3D point from its projection on two images, and their corresponding camera matrices.

Using the projection formula:

\f$ x \propto P X \f$

This function triangulates the location of the 3D point \f$ X \f$, provided the projections \f$ x_i\f$ and \f$ x_j\f$ on two views, and the camera matrices \f$ P_i\f$ and \f$ P_j\f$ for those
views.

The method used is described at section 12.2 from <i>Multiple View Geometry in Computer Vision</i>.

@param point1 The projected location of the 3D point in the first image.
@param P1 The camera matrix for the first image.
@param point2 The projected location of the 3D point in the second image.
@param P2 The camera matrix for the second image.
@return The triangulated location for the point.
@ingroup qvprojectivegeometry
@deprecated use @ref linear3DPointTriangulation(const QPointFMatching &, const QVMatrix &, const QVMatrix &, const TQVSVD_Method) instead.
*/
QV3DPointF linear3DPointTriangulation(const QPointF &point1, const QVMatrix &P1, const QPointF &point2, const QVMatrix &P2, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);

/*!
@brief Recovers the location of a 3D point from its projection on two images, and their corresponding camera matrices.

Using the projection formula:

\f$ x \propto P X \f$

This function triangulates the location of the 3D point \f$ X \f$, provided the point matchings \f$ x_i \mapsto x_j \f$ between two views, and the camera matrices \f$ P_i\f$ and \f$ P_j\f$ for those views.

The method used is described at section 12.2 from <i>Multiple View Geometry in Computer Vision</i>.

@param matching Point matching containing the projections of each 3D point at both cameras.
@param P1 The camera matrix for the first image.
@param P2 The camera matrix for the second image.
@param method The method to solve the linear system.
@return The triangulated location for the point.
@ingroup qvprojectivegeometry
*/
QV3DPointF linear3DPointTriangulation(const QPointFMatching &matching, const QVMatrix &P1, const QVMatrix &P2, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);

/*!
@brief Recovers the location of a 3D point from its projection on two images, and their corresponding camera matrices.

Using the projection formula:

\f$ x \propto P X \f$

This function triangulates the location of the 3D point \f$ X \f$, provided the point matchings \f$ x_i \mapsto x_j \f$ between two views, and the camera matrices \f$ P_i\f$ and \f$ P_j\f$ for those views.

The method used is described at section 12.2 from <i>Multiple View Geometry in Computer Vision</i>.

@param matching Point matching containing the projections of each 3D point at both cameras.
@param pose1 The camera pose for the first image.
@param pose2 The camera pose for the second image.
@param method The method to solve the linear system.
@return The triangulated location for the point.
@ingroup qvprojectivegeometry
*/
QV3DPointF linear3DPointTriangulation(const QPointFMatching &matching, const QVCameraPose &pose1, const QVCameraPose &pose2, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);

/*!
@brief Recovers the location of several 3D points from their projections on different views, and the corresponding camera matrices.

Using function @ref linear3DPointTriangulation, the locations of several 3D points are triangulated with this function.

@param cameras List of cameras.
@param pointProjections Container for the point projections. Each element in this list corresponds to a 3D point. These elements are hash tables,
containing the point image projections, indexed by the number of the camera.

@return The triangulated locations for the points.
@ingroup qvprojectivegeometry
*/
QList<QV3DPointF> linear3DPointsTriangulation(const QList<QVEuclideanMapping3> &cameras, const QList<QHash<int, QPointF> > &pointProjections, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);

/*!
@brief Recovers the location of several 3D points from their projections on different views, and the corresponding camera matrices.

This is an overloaded version of the previous function.

@param cameras List of cameras.
@param pointProjections Container for the point projections. Each element in this list corresponds to a 3D point. These elements are hash tables,
containing the point image projections, indexed by the number of the camera.

@return The triangulated locations for the points.
@ingroup qvprojectivegeometry
*/
QList<QV3DPointF> linear3DPointsTriangulation(const QList<QVEuclideanMapping3> &cameras, const QVector<QHash<int, QPointF> > &pointProjections, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);

/*!
@brief Recovers the location of several 3D points from their projections on different views, and the corresponding camera matrices.

Using function @ref linear3DPointTriangulation, the locations of several 3D points are triangulated with this function.

@param cameras List of cameras.
@param pointProjections Container for the point projections. Each element in this list corresponds to a 3D point. These elements are hash tables,
containing the point image projections, indexed by the number of the camera.

@return The triangulated locations for the points.
@ingroup qvprojectivegeometry
*/
QList<QV3DPointF> linear3DPointsTriangulation(const QList<QVCameraPose> &cameras, const QList<QHash<int, QPointF> > &pointProjections, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);

/*!
@brief Recovers the location of several 3D points from their projections on different views, and the corresponding camera matrices.

This is an overloaded version of the previous function.

@param cameras List of cameras.
@param pointProjections Container for the point projections. Each element in this list corresponds to a 3D point. These elements are hash tables,
containing the point image projections, indexed by the number of the camera.

@return The triangulated locations for the points.
@ingroup qvprojectivegeometry
*/
QList<QV3DPointF> linear3DPointsTriangulation(const QList<QVCameraPose> &cameras, const QVector<QHash<int, QPointF> > &pointProjections, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);

/*!
@brief Estimates the focal lengths for two cameras, 

This function can be used to calibrate two cameras, provided a rough approximation of their principal point locations, and a list of point correspondences between two images.

It first obtains two initial estimations for the focal lengths \f$ f_1 \f$ and \f$ f_2 \f$ of the cameras using the procedure described in [1].
These focal distances are refined by optimizing the following calibration error function:

\f$ error(f_1, f_2) = 1 - s_2 / s_1 \f$

where the values \f$ s_1 \f$ and \f$ s_2 \f$ correspond to the first and second singular values of the following matrix:

\f$
\left(\begin{array}{ccc}
f_1	& 0	& cx_1	\\
0	& f_1	& cy_1	\\
0	& 0	& 1	\\
\end{array}\right)
F
\left(\begin{array}{ccc}
f_2	& 0	& cx_2	\\
0	& f_2	& cy_2	\\
0	& 0	& 1	\\
\end{array}\right)
\f$

where \f$ (cx_1, cy_1) \f$ and \f$ (cx_2, cy_2) \f$ are the provided rough approximations for the principal points of the first and second camera respectively, and \f$ F \f$ is the fundamental matrix obtained from the list of point correspondences.

[1] <i>Estimation of Relative Camera Positions for Uncalibrated Cameras</i>. R. Hartley. Proceedings of the Second European Conference on Computer Vision, 1992.

@param matchings List of point matchings between the two images.
@param focal1 This variable will contain the focal for the first camera in return.
@param focal2 This variable will contain the focal for the second camera in return.
@param principalPoint1 Rough approximation for the principal point of the first camera.
@param principalPoint2 Rough approximation for the principal point of the second camera.
@param gslMinimizerAlgorithm Algorithm to use in the optimization step of the focal calibration.
@param optimizationIterations Number of iterations to perform at the optimization step.

@note This function requires GSL compatibility.

@return false if a numerical error was found, and the focal lengths could not be estimated, true otherwise.
@ingroup qvprojectivegeometry
*/
#include <qvnumericalanalysis.h>
#ifdef GSL_AVAILABLE
bool getCameraFocals(	const QList<QPointFMatching> &matchings,
			double &focal1, double &focal2,
			const QPointF principalPoint1 = QPointF(0.0, 0.0),
			const QPointF principalPoint2 = QPointF(0.0, 0.0),
			const GSLMultiminFDFMinimizerType gslMinimizerAlgorithm = VectorBFGS,
			const int optimizationIterations = 50);
#endif // GSL_AVAILABLE


/*!
@brief Compute camera focal from a planar homography

This function computes the camera focal by solving for diagonal matrix IAC \f$ W=K^{-T}.K^{-1} \f$,
taking into account that
\f$ H^T W H = 
\left(
	\begin{array}{ccc}
	a	& 0	& r	\\
	0	& a	& s	\\
	t	& u	& v
	\end{array}
\right)
\f$

This is equivalent to two different constraints in the entries of H, one of them to force

(1) \f$ (H^T W H)(0,0) = (H^T W H)(1,1) \f$

and the other to force

(2) \f$ (H^T.W.H)(0,1)=0 \f$

If we want to use the first condition, we set byzero to false; if we want to use de second, we set byzero to true.
(Of course, we could have also used both conditions at the same time, and solve by minimum squares).

@param H planar homography matrix
@param w horizontal coordinate for the principal point of the image
@param h vertical coordinate for the principal point of the image
@param byzero If true, use equation (1) to solve for the focal value. Otherwise, use equation (2)

@ingroup qvprojectivegeometry
*/
double computeCameraFocalFromPlanarHomography(const QVMatrix &H, int w, int h, bool byzero = false);

/*!
@brief Estimates the camera pose form the intrinsic calibration and a planar homography.

@param K Intrinsic calibration matrix for the camera.
@param H Planar homography.

@ingroup qvprojectivegeometry
*/
QVCameraPose getCameraPoseFromCalibratedHomography(const QVMatrix & K, const QVMatrix & H);

#ifndef DOXYGEN_IGNORE_THIS
/// @brief Available methods for coefficient matrix reduction.
typedef enum {
	GEA_DO_NOT_DECOMPOSE,		/// Do not apply any decomposition. Use \f$ M^T M \f$ as is.
	GEA_CHOLESKY_DECOMPOSITION,	/// Use Cholesky decomposition.
	GEA_EIGEN_DECOMPOSITION		/// Use eigen decomposition.
	} TGEA_decomposition_method;

QVMatrix get8PointsCoefficientMatrix(const QList<QPointFMatching> &matchings, const bool normalize = true);
QVMatrix getTransposeProductOf8PointsCoefficientMatrix(const QList<QPointFMatching> &matchings, const bool normalize = true);
QVMatrix getReduced8PointsCoefficientsMatrix(	// Input matching list.
						const QList<QPointFMatching> &matchingsList,
						// Method for decomposition.
						const TGEA_decomposition_method decomposition_method = GEA_CHOLESKY_DECOMPOSITION,
						// Perform pre-normalization of the point matchings
						const bool normalize = true,
						// GSL should be faster, but more prone to errors.
						const bool gsl= true,
						// Value to increase diagonal elements prior to Cholesky decomposition.
						// Important to avoid non-positive definite matrix errors.
						const double choleskyLambda = 0.0);

QList<QPointFMatching> applyHomographies(const QVMatrix &H1, const QVMatrix &H2, const QList<QPointFMatching> &matchings);
QList<QPointFMatching> correctIntrinsics(const QVMatrix &K1, const QVMatrix &K2, const QList<QPointFMatching> &matchings);
QList< QHash< int, QPointF> > correctIntrinsics(const QVMatrix &K, const QList< QHash< int, QPointF> > &pointsProjections);

class QVCalibrationErrorFunction: public QVFunction<QVVector, double>
        {
        private:
                const QVMatrix F;
                double evaluate(const QVVector &x);

        public:
                QVCalibrationErrorFunction(const QVMatrix &F);
        };
#endif // DOXYGEN_IGNORE_THIS

// Deprecated functions
#ifndef DOXYGEN_IGNORE_THIS
QPointF ApplyHomography(const QVMatrix &homography, const QPointF &point);
QList<QPointF> ApplyHomography(const QVMatrix &homography, const QList<QPointF> &sourcePoints);

#ifdef QVIPP
QVImage<uChar, 1> ApplyHomography(const QVMatrix &homography, const QVImage<uChar, 1> &image, const int interpolation = IPPI_INTER_CUBIC);
QVImage<uChar, 3> ApplyHomography(const QVMatrix &homography, const QVImage<uChar, 3> &image, const int interpolation = IPPI_INTER_CUBIC);
#endif

QVMatrix ComputeSimilarHomography(const QList< QPointFMatching > &matchings);
QVMatrix ComputeAffineHomography(const QList< QPointFMatching > &matchings);
QVMatrix ComputeProjectiveHomography(const QList< QPointFMatching > &matchings);
QVMatrix ComputeEuclideanHomography(const QList< QPointFMatching > &matchings);
#endif // QVIPP

#endif //  QVPROJECTIVE_H
