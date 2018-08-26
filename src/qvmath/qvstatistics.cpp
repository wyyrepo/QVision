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

#include <qvmath/qvstatistics.h>

#ifdef QVMATRIXALGEBRA_AVAILABLE
double BhattacharyyaDistance(const QVVector &m1, const QVMatrix &S1, const QVVector &m2, const QVMatrix &S2)
    {
    QVVector diff = m2-m1;
    QVMatrix mS = (S1+S2)/2;
    QVMatrix inv = mS.inverse();
    double value = (diff*(inv*diff))/8 + log(mS.det()/sqrt(S1.det()*S2.det()))/2;
    return value;
    }

QVVector qvLinearRegularizedRegression(const QVMatrix &A, const QVVector &b, const QVMatrix &Gamma)
    {
    const QVMatrix tikhonovMatrix = (Gamma == QVMatrix())? QVMatrix::identity(A.getCols()): Gamma;
    return pseudoInverse(A.transpose()*A + tikhonovMatrix)*A.transpose() * b;
    }
#endif

double randomNormalValue(const double mean, const double variance)
    {
        const double	U = double( rand() % (RAND_MAX) ) / double(RAND_MAX),
                                V = double( rand() % (RAND_MAX) ) / double(RAND_MAX);

    const double X = sqrt(-2*log(U))*sin(2*PI*V);

    return X * sqrt(variance) + mean;
    }
