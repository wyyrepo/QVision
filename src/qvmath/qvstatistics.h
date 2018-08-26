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

#ifndef STATISTICS_H
#define STATISTICS_H

/// @file
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#include <QVVector>
#include <QVMatrix>
#include <QVFunction>

/*!
@brief Obtains the <a href="http://en.wikipedia.org/wiki/Bhattacharyya_distance">Bhattacharyya distance</a> of two gaussian distributions.

Obtains the Bhattacharyya distance between two Gaussian distributions, given by their
mean vectors and covariance matrices.

@warning GSL compatibility must be enabled to use this function.
@param m1 first mean.
@param S1 first covariance matrix.
@param m2 second mean.
@param S2 second covariance matrix.
@return computed distance value
@ingroup qvstatistics
*/
#ifdef QVMATRIXALGEBRA_AVAILABLE
double BhattacharyyaDistance(const QVVector &m1, const QVMatrix &S1, const QVVector &m2, const QVMatrix &S2);
#endif

/*! @brief Estimates linear regression using <a href="http://en.wikipedia.org/wiki/Tikhonov_regularization">Tikhonov regularization</a>

This function solves an overdetermined system of linear equations, given as:

\f$ A\mathbf{x}=\mathbf{b} \f$

avoiding ill conditioned cases by minimizing the following regularized expression:

\f$ \|A\mathbf{x}-\mathbf{b}\|^2+ \|\Gamma \mathbf{x}\|^2 \f$

Where the \f$ \Gamma \f$ matrix is called the <i>Tikhonov matrix</i>. In many cases, it is convenient to use the identity matrix as the \f$ \Gamma \f$ matrix.

@warning GSL compatibility must be enabled to use this function.
@param A Coefficients matrix.
@param b Objective values vector.
@param Gamma Tikhonov Matrix. If no value is provided, an identity matrix with adequate dimensions will be used in the regularized expression.
@returns The \f$ \mathbf{x} \f$ vector which minimizes the regularized expression.
@ingroup qvstatistics
*/
#ifdef QVMATRIXALGEBRA_AVAILABLE
QVVector qvLinearRegularizedRegression(const QVMatrix &A, const QVVector &b, const QVMatrix &Gamma = QVMatrix());
#endif

/*! @brief Generate a normally distributed random number

This function uses the <a href="http://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform">Box-Muller</a> transform to generate independent samples of a normal distribution, provided its mean and variance parameters.

@param mean Mean of the normal distribution.
@param variance Variance of the normal distribution.
@ingroup qvstatistics
*/
double randomNormalValue(const double mean, const double variance);

#endif
