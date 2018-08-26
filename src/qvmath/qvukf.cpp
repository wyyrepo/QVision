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

#include <qvmath/qvukf.h>
QVUKF::QVUKF(const QVUKFstate &state)
{
	currentState = state;
	n = state.mean.getCols();

	//default values
	k = 0;
	alpha = 0.5;
	beta = 2;
	discrepance = 0;
}

void QVUKF::setState(const QVUKFstate &state)
{
	currentState = state;
	n = state.mean.getCols();
	discrepance = 0;
}

QVMatrix QVUKF::getState() const
{
	return currentState.mean;
}

double QVUKF::getDiscrepance() const
{
	return discrepance;
}

QVMatrix QVUKF::sigmaPoints(const QVMatrix &X, const QVMatrix &P) const
{
	double lambda = (alpha*alpha) * (n+k) - n;
	QVMatrix aux = P * (n + lambda);
	//Auxiliar matrix for Cholesky decomposition
	QVMatrix aux2 = QVMatrix();

	//Calling to Cholesky decomposition
	CholeskyDecomposition(aux, aux2);
	aux2 = aux2.transpose();
	QVMatrix Sigma = QVMatrix(2*n + 1, n, 0.0);
	QVVector Xvector = QVVector(X);
	for(int i=0; i<2*n+1; i++)
	{
		if(i==0)
			Sigma.setRow(i, Xvector);
		if (i>0 && i<=n)
			Sigma.setRow(i, X + aux2.getRow(i-1));
		if (i>n && i<2*n+1)
			Sigma.setRow(i, X - aux2.getRow(i-n-1));
	}

	return Sigma;
}

void QVUKF::computeWeights()
{
	double lambda = pow(alpha, 2)*(n+k)-n;
	QVMatrix Wm = QVMatrix(2*n+1, 1);
	QVMatrix Wc = QVMatrix(2*n+1, 1);

	for(int i=0; i<2*n+1; i++)
	{
		if(i==0)
		{
			QVVector x = QVVector(1,lambda/(n+lambda));
			QVVector y = QVVector(1,(lambda/(n+lambda))+(1.0-pow(alpha,2)+beta));
			Wm.setRow(i, x);
			Wc.setRow(i, y);
		}

		if (i>0)
		{
			QVVector z = QVVector(1,1.0/(2.0*(n+lambda)));
			Wm.setRow(i, z);
			Wc.setRow(i, z);
		}
	}

	this->weights.Wm = Wm;
	this->weights.Wc = Wc;
}

QVMatrix QVUKF::computeMean(const QVMatrix &M) const
{
	QVMatrix mean = QVMatrix(1, M.getCols(), 0.0);
	for(int j=0; j<M.getCols(); j++)
	{
		double accum =0;
		for(int i=0; i<2*n+1; i++)
			accum += weights.Wm(i,0)*M(i,j);
		QVVector v = QVVector(1, (accum));
		mean.setCol(j, v);
	}

	return mean;
}

QVMatrix QVUKF::computeCovariance(const QVMatrix &mean, const QVMatrix &FdeSigma) const
{
	QVMatrix covariance = QVMatrix(mean.getCols(), mean.getCols(), 0.0);

	for(int i=0; i<2*n+1; i++)
	{
		QVMatrix accum = QVMatrix(mean.getCols(), mean.getCols(), 0.0);
		QVMatrix YXprima = FdeSigma.getRow(i)-mean;
		QVMatrix YXprimaTrans = YXprima.transpose();
		accum = YXprimaTrans*YXprima;
		accum = accum.operator*(weights.Wc(i, 0));
		covariance = covariance + accum;
	}

	return covariance;
}

QVMatrix QVUKF::CrossCovariance (const QVMatrix &mean, const QVMatrix &FdeSigma, const QVMatrix &zt, const QVMatrix &Zt) const
{

	QVMatrix covariance = QVMatrix(n, zt.getCols(), 0.0);

	for(int i=0; i<2*n+1; i++)
	{
		QVMatrix accum = QVMatrix(n, zt.getRows(), 0.0);
		QVMatrix YXprima = FdeSigma.getRow(i) - mean;
		QVMatrix zZprima = Zt.getRow(i) - zt;

		accum = YXprima.transpose()*zZprima;
		accum = accum.operator*(weights.Wc(i,0));
		covariance = covariance + accum;
	}

	return covariance;

}

void QVUKF::update(const QVMatrix &obs, QVFunction<QVVector, QVVector> &g, QVFunction<QVVector, QVVector> &h, const QVMatrix &Rt, const QVMatrix &Qt)
{
	QVMatrix SigmaPoints = sigmaPoints(currentState.mean, currentState.covariance);
	QVMatrix FdeSigma = QVMatrix(2*n+1, n, 0.0);

	for (int i=0; i<2*n+1; i++)
	{
		//Applying the dynamic model function g()
		QVVector aux = SigmaPoints.getRow(i);
		FdeSigma.setRow(i, g.evaluate(aux));
	}

	computeWeights();
	QVMatrix mean_t = computeMean(FdeSigma);
	QVMatrix covar_t = computeCovariance(mean_t, FdeSigma) + Rt;
	QVMatrix SigmaPoints_t = sigmaPoints(mean_t, covar_t);

	QVMatrix Zt = QVMatrix(2*n+1, obs.getCols(), 0.0);
	for (int i=0; i<2*n+1; i++)
	{
		QVVector aux = SigmaPoints_t.getRow(i);
		Zt.setRow(i, h.evaluate(aux));
	}

	QVMatrix zt = computeMean(Zt);
	QVMatrix St = computeCovariance(zt, Zt) + Qt;
	QVMatrix CrossCov = CrossCovariance(mean_t, FdeSigma, zt, Zt);

	//Kalman gain
	QVMatrix St_inv(St.getRows(), St.getCols());
	SolveByCholeskyDecomposition(St, St_inv, QVMatrix::identity(St.getRows()));
	QVMatrix Kt = CrossCov * St_inv;
	//QVMatrix Kt = CrossCov * St.inverse();

	QVMatrix dis = obs - zt;
	QVMatrix final_mean = mean_t + (dis)*Kt.transpose();
	QVMatrix final_covariance = covar_t - Kt*St*Kt.transpose();

	//Updating current state (mu, sigma)
	this->currentState.mean = final_mean;
	this->currentState.covariance = final_covariance;
	this->discrepance = dis.norm2();
}
