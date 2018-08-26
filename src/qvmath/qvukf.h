/*
 *	Copyright (C) 2010, 2011, 2012. PARP Research Group.
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

#ifndef QVUKF_H
#define QVUKF_H

#include <iostream>
#include <QVMatrix>
#include <qvmatrixalgebra.h>
#include <QVFunction>

/**
* @struct QVUKFstate
* @brief A structure that contains the mean and covariance matrix to represent a normal state.
*
* A structure that contains the mean (QVMatrix) and covariance matrix (QVMatrix) to represent a normal state.
*
* @ingroup qvsignalprocessing
*/
struct QVUKFstate
{
	/// Filter mean
	QVMatrix mean;
	/// Filter covariance matrix
	QVMatrix covariance;
};

/**
* @struct QVUKFweights	
* @brief An auxiliar structure that stores some necessary weights.
*
* An auxiliar structure that contains some necessary weights; read the code and you will understand it!
*
* @ingroup qvsignalprocessing
*/
struct QVUKFweights
{
	/// Weight matrix for the filter parameters corresponding to the mean
	QVMatrix Wm;
	/// Weight matrix for the filter parameters corresponding to the covariance.
	QVMatrix Wc;
};

/**
* @class QVUKF
* @brief Implementation of UKF filter.
*
* This is an implementation of the general Unscented Kalman Filter, useful for non-linear filtering.
*
* @ingroup qvsignalprocessing
*/
class QVUKF
	{
	private:
		int n;
		double k;
		double alpha;
		double beta;
		struct QVUKFstate currentState;
		struct QVUKFweights weights;
		double discrepance;

		/**
		* @brief Method that generates a set of sigma points from a given mean and a covariance matrix.
		* @param X state mean.
		* @param P state covariance.
		* @return a QVMatrix containing a set of 2N+1 sigma points, where N is the dimension of the state
		*/
		QVMatrix sigmaPoints(const QVMatrix &X, const QVMatrix &P) const;

		/**
		* @brief Method that computes a set of weights needed to calculate the mean and covariance of the state.
		*/
		void computeWeights();

		/**
		* @brief Method that computes the state mean from the transfered sigma points.
		* @param M transfered sigma points.
		* @return a QVMatrix containing the state mean.
		*/
		QVMatrix computeMean(const QVMatrix &M) const;

		/**
		* @bried Method that computes the state covariance from the state mean and the transfered sigma points.
		* @param mean the state mean.
		* @param FdeSigma the transfered sigma points.
		* @return a QVMatrix containing the state covariance.
		*/
		QVMatrix computeCovariance(const QVMatrix &mean, const QVMatrix &FdeSigma) const;

		/**
		* @brief Method that calculates the cross covariance between the system state and the acquired observation.
		* @param mean state mean.
		* @param FdeSigma transfered sigma points.
		* @param zt observation mean.
		* @param Zt acquired observation.
		* @return a QVMatrix containing the cross covariance between system state and a given observation.
		*/
		QVMatrix CrossCovariance (const QVMatrix &mean, const QVMatrix &FdeSigma, const QVMatrix &zt, const QVMatrix &Zt) const;

	public:
		/**
		* @brief QVUKF default constructor.
		* @param k.
		* @param alpha.
		* @param beta.
		*/
		QVUKF(double k=0.0, double alpha=0.5, double beta=2.0);

		/**
		* @brief QVUKF copy constructor.
		* @param state A QVUKFstate.
		*/
		QVUKF(const QVUKFstate &state);

		/**
		* @brief Method that fills the current state from a given QVUKFstate.
		* @param state QVUKFstate used to fill the current filter state (discrepancy is reset to 0).
		*/
		void setState(const QVUKFstate &state);

		/**
		* @brief Method that updates the current state, moving from X_k to X_k+1.
		* @param obs QVMatrix that contains an acquired observation.
		* @param g A functor that implements the dynamic model for a specific problem.
		* @param h A functor that implements how to propagate the observation according to the conditions of a specific problem.
		* @param Rt Multivariate Gaussian noise (0-mean) that will be added to the covariance matrix.
		* @param Qt Multivariate Gaussian noise (0-mean) that will be added to the predicted covariance matrix.
		*/
		void update(const QVMatrix &obs, QVFunction<QVVector, QVVector> &g, QVFunction<QVVector, QVVector> &h, const QVMatrix &Rt, const QVMatrix &Qt);

		/**
		* @brief Method that returns the current system state.
		* @return A QVMatrix that contains the current system state.
		*/
		QVMatrix getState() const;

		/**
		* @brief Method that returns the discrepancy.
		* @return The system discrepancy.
		*/
		double getDiscrepance() const;
	};

#endif // QVUKF_H

