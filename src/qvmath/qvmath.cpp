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

#include <iostream>
#include <qvmath.h>
#include <qvmath/qvrationalnumber.h>

double norm2(const QPointF &p)
    {
    return sqrt(p.x() * p.x() + p.y() * p.y());
    }

int qvFactorial(const int n)
    {
    int result = 1;
    for (int i = 2; i <= n; i++)
        result *= i;

    return result;
    };

double qvFactorialDivisionDouble(const int numerator, const int denominator)
    {
    double result = 1;
    for (int i = denominator+1; i <= numerator; i++)
        result *= i;

    return result;
    }

double qvCombination(const int setRange, const int subsetRange)
    {
    Q_ASSERT(setRange > subsetRange);

    QVRationalNumber subSetFactorial, divisionFactorial;

    for (int i = 2; i <= subsetRange; i++)
        subSetFactorial.mult(i);

    for (int i = setRange - subsetRange + 1; i <= setRange; i++)
        divisionFactorial.mult(i);

    return divisionFactorial/subSetFactorial;
    }

double qvAngle(const QPointF &point)
    {
    const double x = point.x(), y = point.y();

    if (x>0)
        if (y>=0)
            return atan(y/x);
        else
            return atan(y/x) + 2*PI;
    else if (x == 0.0)
        if (y>0)
            return PI/2;
        else
            return 3*PI/2;
    else // x < 0
        return atan(y/x)+PI;
    }

double qvAngle(const QPointF &point1, const QPointF &point2)
    {
    double dtheta = atan2(point2.y(), point2.x()) - atan2(point1.y(), point1.x());

    while (dtheta >= 2*PI)
        dtheta -= 2*PI;

    while (dtheta < -2*PI)
        dtheta += 2*PI;

	Q_ASSERT(dtheta >= -2*PI);
	Q_ASSERT(dtheta <= 2*PI);

    return dtheta;
    }

int qvRandom(const int minValue, const int maxValue)
    { return rand()%(maxValue-minValue+1) + minValue; }

// This function returns the positive degrees for a given angle
double qvClockWiseAngle(const QPointF &point1, const QPointF &point2)
    {
	return qvAngle(point1, point2);
    }

// Min value granted for RAND_MAX
#define RANDOM_PRECISSION	32767
double random(const double min, const double max)
    {
    return ABS(max-min) * double(rand()%RANDOM_PRECISSION)/double(RANDOM_PRECISSION-1) + MIN(min, max);
    }

double relativeEuclideanDistance(const double &v1, const double &v2)
	{
	if ( (v1 == 0) or (v2 == 0) )
		return 0.5;

	return 0.5 * ABS(v1-v2) / (ABS(v1) + ABS(v2));
	}

double relativeEuclideanDistance(const QVVector &v1, const QVVector &v2)
	{
	if ( (v1.sum() == 0) or (v2.sum() == 0) )
		return 0.5;

	return 0.5 * (v1-v2).norm2() / (v1.norm2() + v2.norm2());
	}

// ----------------------
QVector<QVComplex> qvSolveCubicPolynomial(const double coeff0, const double coeff1, const double coeff2, const double coeff3)
	{
	/*
	# Maple code
	with(VectorCalculus):
	with(LinearAlgebra):
	with(linalg):

	y := coeff3 x^3 + coeff2 x^2 + coeff1 x + coeff0:
	s := solve(y = 0, x):

	CodeGeneration[C](Matrix([
	[evalc(Re(s[1])), evalc(Im(s[1]))],
	[evalc(Re(s[2])), evalc(Im(s[2]))],
	[evalc(Re(s[3])), evalc(Im(s[3]))]
	]), optimize = true);
	*/
	const double 
		t1 = 0.1e1 / coeff3,
		t2 =  ( coeff1 * coeff2),
		t5 =  ( coeff3 *  coeff3),
		t8 =  (coeff2 * coeff2),
		t9 =  ( t8 * coeff2),
		t11 = sqrt(0.3e1),
		t12 =  ( coeff1 *  coeff1),
		t20 =  ( coeff0 *  coeff0),
		t25 = 4 * t12 * coeff1 * coeff3 - t12 * t8 - 18 * t2 * coeff3 * coeff0 + 27 * t20 * t5 + 4 * coeff0 * t9,
		t26 = abs(t25),
		t27 = sqrt( t26),
		t28 = t11 * t27,
		t29 = ( t25>0 ? 1 : ( t25<0 ? -1 : 0)),
		t34 =  (36 * t2 * coeff3) -  (108 * coeff0 * t5) -  (8 * t9) + 0.6e1 * t28 *  (1 + t29) *  coeff3,
		t35 = t34 * t34,
		t36 = 1 - t29,
		t37 = t36 * t36,
		t42 = pow(t35 +  (108 * t26 * t37 * t5), 0.1e1 / 0.6e1),
		t43 = t1 * t42,
		t47 = atan2(0.6e1 * t28 *  t36 *  coeff3, t34),
		t48 = t47 / 0.3e1,
		t49 = cos(t48),
		t50 = t43 * t49,
		t51 = t50 / 0.6e1,
		t52 = coeff1 * coeff3,
		t55 = -12 * t52 + 4 * t8,
		t56 =  t55 * t1,
		t57 = 0.1e1 / t42,
		t58 = t57 * t49,
		t62 = coeff2 * t1 / 0.3e1,
		t64 = sin(t48),
		t65 = t43 * t64,
		t66 = t57 * t64,
		t69 = t50 / 0.12e2,
		t70 = - t55 * t1,
		t72 = t70 * t58 / 0.12e2,
		t77 = ( (2 * t52) - 0.2e1 / 0.3e1 *  t8) * t1,
		t81 = t11 * (t65 / 0.6e1 - t77 * t66) / 0.2e1,
		t83 = t65 / 0.12e2,
		t85 = t70 * t66 / 0.12e2,
		t89 = t11 * (t51 + t77 * t58) / 0.2e1;

	double cg[3][2];
	cg[0][0] = t51 + t56 * t58 / 0.6e1 - t62;
	cg[0][1] = t65 / 0.6e1 - t56 * t66 / 0.6e1;
	cg[1][0] = -t69 + t72 - t62 - t81;
	cg[1][1] = -t83 - t85 + t89;
	cg[2][0] = -t69 + t72 - t62 + t81;
	cg[2][1] = -t83 - t85 - t89;

	QVector<QVComplex> result(3);
	result[0].real() = cg[0][0];	result[0].imaginary() = cg[0][1];
	result[1].real() = cg[1][0];	result[1].imaginary() = cg[1][1];
	result[2].real() = cg[2][0];	result[2].imaginary() = cg[2][1];

	return result;
	}


// ----------------------
/*QList<QVComplex> qvSolveCubicPolynomial(const double a0, const double a1, const double a2, const double a3)
    {
    double cg[6];
    qvSolveCubicPolynomialAux(a0, a1, a2, a3, cg);

    QList<QVComplex> result;
    result << QVComplex(cg[0], cg[1]);
    result << QVComplex(cg[2], cg[3]);
    result << QVComplex(cg[4], cg[5]);

    return result;
    }

# Solve third grade polinomy:
s := solve(a3 x ^3 + a2 x^2 + a1 x + a0, x);
S := Vector([	evalc(Re(s[1])), evalc(Im(s[1])),
        evalc(Re(s[2])), evalc(Im(s[2])),
        evalc(Re(s[3])), evalc(Im(s[3]))
        ]);
CodeGeneration[C](S, optimize = true);

void qvSolveCubicPolynomialAux(const double a0, const double a1, const double a2, const double a3, double cg[6])
    {
    const double t1 = 0.1e1 / a3;
    const double t2 = (a1 * a2);
    const double t5 = (a3 * a3);
    const double t8 = (a2 * a2);
    const double t9 = (t8 * a2);
    const double t11 = sqrt(0.3e1);
    const double t12 = (a1 * a1);
    const double t20 = (a0 * a0);
    const double t25 = 4 * t12 * a1 * a3 - t12 * t8 - 18 * t2 * a3 * a0 + 27 * t20 * t5 + 4 * a0 * t9;
    const double t26 = abs(t25);
    const double t27 = sqrt(t26);
    const double t28 = t11 * t27;
    const double t29 = (t25>0 ? 1 : (t25<0 ? -1 : 0));
    const double t34 = (36 * t2 * a3) - (108 * a0 * t5) - (8 * t9) + 0.6e1 * t28 * (1 + t29) * a3;
    const double t35 = t34 * t34;
    const double t36 = 1 - t29;
    const double t37 = t36 * t36;
    const double t42 = pow(t35 + (108 * t26 * t37 * t5), 0.1e1 / 0.6e1);
    const double t43 = t1 * t42;
    const double t47 = atan2(0.6e1 * t28 * t36 * a3, t34);
    const double t48 = t47 / 0.3e1;
    const double t49 = cos(t48);
    const double t50 = t43 * t49;
    const double t51 = t50 / 0.6e1;
    const double t52 = a1 * a3;
    const double t56 = (12 * t52 - 4 * t8) * t1;
    const double t57 = 0.1e1 / t42;
    const double t58 = t57 * t49;
    const double t59 = t56 * t58;
    const double t62 = a2 * t1 / 0.3e1;
    const double t64 = sin(t48);
    const double t65 = t43 * t64;
    const double t66 = t57 * t64;
    const double t67 = t56 * t66;
    const double t69 = t50 / 0.12e2;
    const double t70 = t59 / 0.12e2;
    const double t75 = ((2 * t52) - 0.2e1 / 0.3e1 * t8) * t1;
    const double t79 = t11 * (t65 / 0.6e1 - t75 * t66) / 0.2e1;
    const double t81 = t65 / 0.12e2;
    const double t82 = t67 / 0.12e2;
    const double t86 = t11 * (t51 + t75 * t58) / 0.2e1;

    cg[0] = t51 - t59 / 0.6e1 - t62;
    cg[1] = t65 / 0.6e1 + t67 / 0.6e1;
    cg[2] = -t69 + t70 - t62 - t79;
    cg[3] = -t81 - t82 + t86;
    cg[4] = -t69 + t70 - t62 + t79;
    cg[5] = -t81 - t82 - t86;
    }
*/

double qvPointLineDistance(const QVVector &l, const QPointF &p)
	{
	return ABS(l[0] * p.x() + l[1] * p.y() + l[2]) / sqrt(POW2(l[0]) + POW2(l[1]));
	}

double qvSymmetricFloor( const double value )
  {
  if (value < 0.0)
    return ceil( value );
  else
    return floor( value );
  }


