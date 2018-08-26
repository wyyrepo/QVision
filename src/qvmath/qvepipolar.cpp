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

#include <qvmath/qvepipolar.h>
#include <math.h>

// Returns M = DLT matrix
QVMatrix getDLTMatrix(const QVector<QPointFMatching> &matchings)
	{
	QVMatrix A(matchings.size(),9);
	double *aptr = A.getWriteData();

	foreach(QPointFMatching matching,matchings)
		{
		const QPointF	sourcePoint = matching.first,
						destPoint = matching.second;
		const double	x = sourcePoint.x(),
						y = sourcePoint.y(),
						x_p = destPoint.x(),
						y_p = destPoint.y();

		// Faster:
		aptr[0] = x*x_p;
		aptr[1] = y*x_p;
		aptr[2] = x_p;
		aptr[3] = x*y_p;
		aptr[4] = y*y_p;
		aptr[5] = y_p;
		aptr[6] = x;
		aptr[7] = y;
		aptr[8] = 1.0;
		aptr += 9;
		}
	return A;
	}

QVMatrix getSquaredDLTMatrix(const QVector<QPointFMatching> &matchings, const QPointF &m0c, const QPointF &m1c, const double &scale0, const double &scale1)
    {
	double accum[36];
	for(int i = 0; i < 36; i++)
		accum[i] = 0.0;

	const double	m0c_x = m0c.x(),	m0c_y = m0c.y(),
					m1c_x = m1c.x(),	m1c_y = m1c.y();

	for(int i = 0; i < matchings.count(); i++)
        {
		const QPointFMatching &matching = matchings[i];
        const QPointF	&sourcePoint = matching.first,
						&destPoint = matching.second;

        const double	x = scale0 * (sourcePoint.x() - m0c_x),
						y = scale0 * (sourcePoint.y() - m0c_y),
		                xp = scale1 * (destPoint.x() - m1c_x),
						yp = scale1 * (destPoint.y() - m1c_y);

		/*
		# MAPLE CODE
		with(VectorCalculus):
		with(LinearAlgebra):

		v:= Matrix([ [x xp], [y xp], [xp], [x yp], [y yp], [yp], [x], [y], [1]  ] );
		M := v.Transpose(v);
		V := Vector([M[1,1], M[1,2], M[1,3], M[1,4], M[1,5], M[1,6], M[1,7], M[1,8], M[1,9], M[2,2], M[2,3], M[2,5],
			M[2,6], M[2,8], M[2,9], M[3,3], M[3,6], M[3,9], M[4,4], M[4,5], M[4,6], M[4,7], M[4,8], M[4,9], M[5,5],
			M[5,6], M[5,8], M[5,9], M[6,6], M[6,9], M[7,7], M[7,8], M[7,9], M[8,8], M[8,9], M[9,9] ]);

		CodeGeneration[C](V, optimize = true);
		*/
		const double	t1 = x * x,
						t2 = xp * xp,
						t4 = x * t2,
						t6 = t1 * xp,
						t8 = x * xp,
						t9 = y * yp,
						t13 = y * y,
						t16 = t13 * xp,
						t18 = y * xp,
						t21 = yp * yp,
						t23 = x * t21,
						t26 = x * yp;

		accum[0] += t1 * t2;
		accum[1] += t4 * y;
		accum[2] += t4;
		accum[3] += t6 * yp;
		accum[4] += t8 * t9;
		accum[5] += t8 * yp;
		accum[6] += t6;
		accum[7] += t8 * y;
		accum[8] += t8;
		accum[9] += t13 * t2;
		accum[10] += y * t2;
		accum[11] += t16 * yp;
		accum[12] += t18 * yp;
		accum[13] += t16;
		accum[14] += t18;
		accum[15] += t2;
		accum[16] += xp * yp;
		accum[17] += xp;
		accum[18] += t1 * t21;
		accum[19] += t23 * y;
		accum[20] += t23;
		accum[21] += t1 * yp;
		accum[22] += t26 * y;
		accum[23] += t26;
		accum[24] += t13 * t21;
		accum[25] += y * t21;
		accum[26] += t13 * yp;
		accum[27] += t9;
		accum[28] += t21;
		accum[29] += yp;
		accum[30] += t1;
		accum[31] += x * y;
		accum[32] += x;
		accum[33] += t13;
		accum[34] += y;
		accum[35] += 1;
        }

	return QVMatrix(9,9, (double[9*9])	{
										accum[0], accum[1], accum[2], accum[3], accum[4], accum[5], accum[6], accum[7], accum[8],
										accum[1], accum[9], accum[10], accum[4], accum[11], accum[12], accum[7], accum[13], accum[14],
										accum[2], accum[10], accum[15], accum[5], accum[12], accum[16], accum[8], accum[14], accum[17],
										accum[3], accum[4], accum[5], accum[18], accum[19], accum[20], accum[21], accum[22], accum[23],
										accum[4], accum[11], accum[12], accum[19], accum[24], accum[25], accum[22], accum[26], accum[27],
										accum[5], accum[12], accum[16], accum[20], accum[25], accum[28], accum[23], accum[27], accum[29],
										accum[6], accum[7], accum[8], accum[21], accum[22], accum[23], accum[30], accum[31], accum[32],
										accum[7], accum[13], accum[14], accum[22], accum[26], accum[27], accum[31], accum[33], accum[34],
										accum[8], accum[14], accum[17], accum[23], accum[27], accum[29], accum[32], accum[34], accum[35]
										}
					);
	}

void normalizeMatchingsForEpipolarestimation(const QVector<QPointFMatching> &matchings, QPointF &m0c, QPointF &m1c, double &scale0, double &scale1, QVMatrix &Q1, QVMatrix &Q2)
	{
    // Compute centers and average distances for each of the two point sets
	m0c.rx() = 0.0;	m0c.ry() = 0.0;
	m1c.rx() = 0.0;	m1c.ry() = 0.0;

    foreach(QPointFMatching matching, matchings)
        {
        m0c += matching.first;
        m1c += matching.second;
        }

    const int count = matchings.count();
    m0c /= count;
    m1c /= count;

    scale0 = 0.0;
	scale1 = 0.0;
    foreach(QPointFMatching matching, matchings)
        {
        scale0 += norm2(matching.first - m0c);
        scale1 += norm2(matching.second - m1c);
        }

    scale0 = count * sqrt(2.) /scale0;
    scale1 = count * sqrt(2.) /scale1;

    // Re-compose F truncating the third singular value, and correcting the whitening of the point correspondences
    Q1 = QVMatrix::cameraCalibrationMatrix(scale0, 1.0, -scale0*m0c.x(), -scale0*m0c.y()),
	Q2 = QVMatrix::cameraCalibrationMatrix(scale1, 1.0, -scale1*m1c.x(), -scale1*m1c.y());
	}

bool solveForFundamentalMatrix(const QVMatrix &omega, QVMatrix &F, const TQVSVD_Method svdMethod = DEFAULT_TQVSVD_METHOD)
	{
    QVVector x;
    solveHomogeneous(omega, x, svdMethod);
	const QVMatrix preF = QVMatrix(3,3, x);

	// Decompose linear F with SVD.
	QVMatrix U, V;
	QVVector s;
	singularValueDecomposition(preF, U, s, V, svdMethod);

	double *dataU = U.getWriteData();
	for(int i = 0; i < 3; i++)
		{
		dataU[3*i+0] *= s[0];
		dataU[3*i+1] *= s[1];
		dataU[3*i+2] = 0.0;
		}

	F = U.dotProduct(V, false, true);

	return (F.norm2() > MIN_FUNDAMENTAL_MATRIX_NORM);
	}

bool computeFundamentalMatrix(const QVector<QPointFMatching> &matchings, QVMatrix &F, const TQVSVD_Method svdMethod)
    {
    if (matchings.count() < 8)
        return false;

	QPointF m0c, m1c;
	double scale0, scale1;
	QVMatrix Q1, Q2, preF;

	normalizeMatchingsForEpipolarestimation(matchings, m0c, m1c, scale0, scale1, Q1, Q2);

	// Coefficient matrix.
	const QVMatrix omega = getSquaredDLTMatrix(matchings, m0c, m1c, scale0, scale1);

	if (not solveForFundamentalMatrix(omega, preF, svdMethod))
		return false;

	F = Q2.transpose() * preF * Q1;

    // Todo: Some functions will not work properly if values are not cast to float. ¿Porqué?
    for(int j = 0; j < 3; j++ )
        for(int k = 0; k < 3; k++ )
            F(j,k) = float(F(j,k));

	return true;
    }

QVVector symmetricEpipolarDistance2(const QVMatrix &F, const QVector<QPointFMatching> &matchings)
	{
	//const double *f = F.getReadData();

	QVVector result(matchings.count());
	for(int i = 0; i < matchings.count(); i++)
		{
		const QPointF	&p1 = matchings[i].first,
						&p2 = matchings[i].second;
		const QVVector	l1 = F*QV3DPointF(p1.x(), p1.y(), 1.0),
						l2 = QV3DPointF(p2.x(), p2.y(), 1.0)*F;
		const double	distance =	qvPointLineDistance(l1, p2) + qvPointLineDistance(l2, p1);

		result[i] = distance;
		}
	return result;
	}

double symmetricEpipolarDistance(const QVMatrix &F, const QPointFMatching &matching)
	{
	const double *f = F.getReadData();

	const QPointF	&p1 = matching.first,
					&p2 = matching.second;
	const double	p1x = p1.x(), p1y = p1.y(),
					p2x = p2.x(), p2y = p2.y();

	/*
	# Maple code:
	with(VectorCalculus):
	with(LinearAlgebra):

	# Input
	f := vector(9):

	# F matrix
	P1 := Vector([p1x, p1y, 1]);
	P2 := Vector([p2x, p2y, 1]);
	F := Matrix([ [f[1], f[2], f[3]], [f[4], f[5], f[6]], [f[7], f[8], f[9]]]);

	l1 := F.P1:
	l2 := Transpose(P2).F:

	n1 := l1[1]*p2x + l1[2]*p2y + l1[3]:
	d1 := l1[1]*l1[1] + l1[2]*l1[2]:
	n2 := l2[1]*p1x + l2[2]*p1y + l2[3]:
	d2 := l2[1]*l2[1] + l2[2]*l2[2]:

	CodeGeneration[C](Vector([n1, d1, n2, d2]), optimize = true);
	*/
	const double	t3 = f[0] * p1x + f[1] * p1y + f[2],
					t7 = f[3] * p1x + f[4] * p1y + f[5],
					t12 = t3 * t3,
					t13 = t7 * t7,
					t17 = p2x * f[0] + p2y * f[3] + f[6],
					t21 = p2x * f[1] + p2y * f[4] + f[7],
					t26 = t17 * t17,
					t27 = t21 * t21,
					cg0 = t3 * p2x + t7 * p2y + f[6] * p1x + f[7] * p1y + f[8],
					cg1 = t12 + t13,
					cg2 = t17 * p1x + t21 * p1y + p2x * f[2] + p2y * f[5] + f[8],
					cg3 = t26 + t27;

	return ABS(cg0)/sqrt(cg1) + ABS(cg2)/sqrt(cg3);
	}

// 10-fold speed up compared to symmetricEpipolarDistance2
QVVector symmetricEpipolarDistance(const QVMatrix &F, const QVector<QPointFMatching> &matchings)
	{
	const double *f = F.getReadData();

	QVVector result(matchings.count());
	for(int i = 0; i < matchings.count(); i++)
		{
		const QPointF	&p1 = matchings[i].first,
						&p2 = matchings[i].second;
		const double	p1x = p1.x(), p1y = p1.y(),
						p2x = p2.x(), p2y = p2.y();

		/*
		# Maple code:
		with(VectorCalculus):
		with(LinearAlgebra):

		# Input
		f := vector(9):

		# F matrix
		P1 := Vector([p1x, p1y, 1]);
		P2 := Vector([p2x, p2y, 1]);
		F := Matrix([ [f[1], f[2], f[3]], [f[4], f[5], f[6]], [f[7], f[8], f[9]]]);

		l1 := F.P1:
		l2 := Transpose(P2).F:

		n1 := l1[1]*p2x + l1[2]*p2y + l1[3]:
		d1 := l1[1]*l1[1] + l1[2]*l1[2]:
		n2 := l2[1]*p1x + l2[2]*p1y + l2[3]:
		d2 := l2[1]*l2[1] + l2[2]*l2[2]:

		CodeGeneration[C](Vector([n1, d1, n2, d2]), optimize = true);
		*/
		const double	t3 = f[0] * p1x + f[1] * p1y + f[2],
						t7 = f[3] * p1x + f[4] * p1y + f[5],
						t12 = t3 * t3,
						t13 = t7 * t7,
						t17 = p2x * f[0] + p2y * f[3] + f[6],
						t21 = p2x * f[1] + p2y * f[4] + f[7],
						t26 = t17 * t17,
						t27 = t21 * t21,
						cg0 = t3 * p2x + t7 * p2y + f[6] * p1x + f[7] * p1y + f[8],
						cg1 = t12 + t13,
						cg2 = t17 * p1x + t21 * p1y + p2x * f[2] + p2y * f[5] + f[8],
						cg3 = t26 + t27;

		result[i] = ABS(cg0)/sqrt(cg1) + ABS(cg2)/sqrt(cg3);
		}

	#ifdef DEBUG
	for(int i = 0; i < result.count(); i++)
		{
		const double distance = ABS(result[i] - symmetricEpipolarDistance(F, matchings[i])) / (ABS(result[i]) + ABS(symmetricEpipolarDistance(F, matchings[i])));
		Q_WARNING(distance < 1e-6);
		}

	const QVVector result2 = symmetricEpipolarDistance2(F, matchings);
	Q_ASSERT_X(result.count() == matchings.count(), "symmetricEpipolarDistance()", "number of residuals differs from number of matchings");
	Q_ASSERT_X(result2.count() == result.count(), "symmetricEpipolarDistance()", "number of estimated residuals differs from number of ground-truth residuals");

	const double	max_residuals_norm = MAX(result.norm2(), result2.norm2()) / matchings.count(),
					relative_error = (result - result2).norm2() / max_residuals_norm;
	//std::cout << "||r - r||' = " << relative_error << "\t" << result.count() << "\t" << result2.count() << std::endl;
	//std::cout << "max ||r|| , ||r||' = " << max_residuals_norm << "\t" << result.count() << "\t" << result2.count() << std::endl;
	/*if(relative_error > 1e-10)
		{
		std::cout << result << std::endl;
		std::cout << result2 << std::endl;
		std::cout << (result-result2) << std::endl;
		}*/
	Q_WARNING_X( (relative_error < 1e-8) or (max_residuals_norm < 1e-8), "symmetricEpipolarDistance()", "relative error with ground-truth residuals is too high");
	#endif // DEBUG

	return result;
	}

// --------------------------------------------------------------------------

bool iterativeLocalOptimization2(const QList<QPointFMatching> &matchings,  QList<QPointFMatching> &result, const double maxEE, const int minInliers)
	{
	result = matchings;

	while(true)
		{
		//  1) Estimar fundamental 'estF'
		QVMatrix F = computeFundamentalMatrix(result);
		if (F == QVMatrix())
			return false;

		//  2) Evaluar error para todas las correspondencias
		const QVVector residuals = symmetricEpipolarDistance(F, result.toVector());

		//		2.0) Si el error para todas es menor de cierto umbral 'maxEE', parar y devolver fundamental 'estF'.
		const double actualMax = residuals.max();
		if (actualMax < maxEE)
			return true;

		//			-> si no se han eliminado matchings: FALLO. No se pueden descartar correspondencias con un error demasiado elevado.
		const double median = residuals.median();
		if (actualMax < 2.0*median)
			return false;

		//		2.1) Si no, evaluar mediana y filtar correspondencias con error mayor de MAX(2*median, maxEE)
		QList<QPointFMatching> newMatchings;
		for(int i = 0; i < residuals.count(); i++)
			if (residuals[i] < MAX(2*median, maxEE))
				newMatchings << result[i];

		//			-> si el número de puntos restante es inferior a cierto umbral: FALLO. Puntos insuficientes para robustez.
		if (newMatchings.count() < minInliers)
			return false;

		//			-> en otro caso, repetir punto 1) con nuevos conjunto de puntos filtrados.
		result = newMatchings;
		}

	return true;
	}

bool iterativeLocalOptimization(const QList<QPointFMatching> &matchings,  QList<QPointFMatching> &result, const double maxEE, const int minInliers)
	{
	result = matchings;

	while(true)
		{
		// Estimate fundamental matrix.
		QVMatrix F;
		if (not computeFundamentalMatrix(result.toVector(), F))
			return false;

		// Evaluate symmetric epipolar error for the matchings.
		const QVVector residuals = symmetricEpipolarDistance(F, result.toVector());

		// If the maximal error is below a threshold value 'maxEE', the algorithm successes and returns the fundamental matrix.
		const double actualMax = residuals.max();
		if (actualMax < maxEE)
			return true;

		// Evaluate median value of the errors.
		const double median = residuals.median();

		// If no one of the matchings has an error above two times the median, the algorithm fails.
		// The algorithm will not discard any new matchings, and there are matchings with an error above 'maxEE'.
		if (actualMax < 2.0*median)
			return false;

		// Otherwise, eliminate matchings with an error above a threshold value.
		// This value is the maximal of two times the median and 'maxEE'.
		QList<QPointFMatching> newMatchings;
		for(int i = 0; i < residuals.count(); i++)
			if (residuals[i] < MAX(2*median, maxEE))
				newMatchings << result[i];

		// If there are not enough remaining matchings, return fail.
		if (newMatchings.count() < minInliers)
			return false;

		// Otherwise start again the filtering process.
		result = newMatchings;
		}

	return true;
	}

