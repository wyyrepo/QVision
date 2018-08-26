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

#ifndef QVMATH_H
#define QVMATH_H

#ifndef M_SQRT1_2
#define M_SQRT1_2 7.0710678118654752440E-1
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288   /* pi */
#endif

#ifndef M_PI_2
#define M_PI_2 1.5707963267948966192E0
#endif

#ifndef M_PI_4
#define M_PI_4 0.785398163397448309615660845819875721  /* pi/4 */
#endif

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#ifdef _MSC_VER
	#include <float.h>  // for _isnan() on VC++
	#define isnan(x) _isnan(x)  // VC++ uses _isnan() instead of isnan()
	#define isinf(x) _isinf(x)
#else
	#include <cmath> // for isnan() and isinf() everywhere else
	extern "C" int isnan(double);
	extern "C" int isinf(double);
#endif

#include <iostream>
#include <math.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include <qvdefines.h>

// Get BLAS version
#ifdef MKL_AVAILABLE
    #include <mkl.h>
    #include <mkl_lapack.h>
    #include <mkl_dss.h>
    #include <mkl_rci.h>
    #include <mkl_spblas.h>
#elif GSL_AVAILABLE
    // If the MKL is not available, use the BLAS implementation from the GSL.
    #include <gsl/gsl_blas.h>
//	#include <gsl/gsl_blas.h>
//	#include <gsl/gsl_math.h>
//	#include <gsl/gsl_eigen.h>
//	#include <gsl/gsl_linalg.h>

#endif

#ifdef GSL_AVAILABLE
    #include <gsl/gsl_math.h>
    #include <gsl/gsl_eigen.h>
    #include <gsl/gsl_linalg.h>
    #include <gsl/gsl_errno.h>
    #include <gsl/gsl_math.h>
    #include <gsl/gsl_min.h>
    #include <gsl/gsl_multimin.h>
    #include <gsl/gsl_multifit_nlin.h>
#endif

#include <QPair>
#include <QPointF>
#include <QVComplex>
#include <QVVector>

#include <qvmath/qvbitcount.h>

#ifndef POW2
#define	POW2(X)			((X)*(X))
#endif

#ifndef SIGN
#define SIGN(X)			(((X)>=0)?1:-1)
#endif

#ifndef ABS
#define	ABS(X)			(((X)>0)?(X):(-(X)))
#endif

#ifndef MIN
#define MIN(X,Y)		(((X)<(Y))?(X):(Y))
#endif

#ifndef MAX
#define MAX(X,Y)		(((X)>(Y))?(X):(Y))
#endif

#ifndef RANDOM
#define	RANDOM(MIN, MAX)	(rand()%((MAX)-(MIN)+1) + (MIN))
#endif

#ifndef PI
#define PI		(3.14159265358979323846)
#endif

#ifndef EPSILON
#define EPSILON		(10E-6)
#endif

/// @todo document
int qvFactorial(const int n);

/*! @brief Obtains the number of combinations of a fixed size over the elements of a set

Given a set size of <i>n</i>, this function returns the number of subsets of size <i>k</i>
within that set.

\f$ qvCombination(n,k) = {n \choose k} = \frac{n!}{k!(n-k)!} \f$
@ingroup qvmath
*/
double qvCombination(const int setRange, const int subsetRange);

/*! @brief Returns the angle between two 2D vectors.

This function returns the angle defined between two input points.

@param point1 First point.
@param point2 Second point.
@result A value in the range \f$ [ -\Pi, \Pi ] \f$ corresponding to the angle from the first point to the second.

@ingroup qvmath
*/
double qvAngle(const QPointF &point1, const QPointF &point2);

#ifndef DOXYGEN_IGNORE_THIS
/// @todo document
/// @ingroup qvmath
double qvAngle(const QPointF &);

/// @todo document
/// @ingroup qvmath
double qvClockWiseAngle(const QPointF &, const QPointF &);

/// @todo document
/// @ingroup qvmath
int qvRandom(const int minValue, const int maxValue);

/// @todo document
/// @ingroup qvmath
double norm2(const QPointF &p);

/// @todo document
/// @ingroup qvmath
double random(const double min, const double max);
#endif

//#ifndef DOXYGEN_IGNORE_THIS
//void qvSolveCubicPolynomialAux(const double a0, const double a1, const double a2, const double a3, double cg[6]);
//#endif

/*! @brief Obtains the three complex (or real) solutions for a third grade polynomial.

This function returns the three complex values which satisfy the following equation:

\f$ a_0 + a_1 x + a_2 x^2 + a_3 x^3 = 0 \f$

@note The value \f$ a_3 \f$ should not be zero, so the polynomial is bond to have three root values.
@param a0 coefficient \f$ a_0 \f$ of the polynomial.
@param a1 coefficient \f$ a_1 \f$ of the polynomial.
@param a2 coefficient \f$ a_2 \f$ of the polynomial.
@param a3 coefficient \f$ a_3 \f$ of the polynomial.
@ingroup qvmath
*/
QVector<QVComplex> qvSolveCubicPolynomial(const double a0, const double a1, const double a2, const double a3);

/*! @brief Obtains the geometric distance between a point and a line in the 2D plane.

Given a point

\f$ p \equiv (p_x, p_y) \f$

and a line

\f$l \equiv l_1 x + l_2 y + l_3 = 0 \f$

this function returns the geometric distance between the 2D point \f$ p \f$, and the closest point in the line \f$ l \f$.
This distance is evaluated with the following expression:

\f$ qvPointLineDistance(l, p) = \frac{|l_1 p_x + l_2 p_y + l_3|}{\sqrt{{l_1}^2+{l_2}^2}} \f$

@param l 3D vector, containing the line coefficients \f$(l_1, l_2, l_3)\f$.
@param p Point
@ingroup qvmath
*/
double qvPointLineDistance(const QVVector &, const QPointF &);

/*! @brief Returns the natural number closest to a given real value.

@param value Real value
@ingroup qvmath
*/
double qvSymmetricFloor( const double value );

#ifndef DOXYGEN_IGNORE_THIS
double relativeEuclideanDistance(const double &v1, const double &v2);
double relativeEuclideanDistance(const QVVector &v1, const QVVector &v2);
#endif // DOXYGEN_IGNORE_THIS

#endif // QVMATH_H
