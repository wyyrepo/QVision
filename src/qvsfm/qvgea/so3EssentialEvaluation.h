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

#ifndef SO3ESSENTIALEVALUATION_H
#define SO3ESSENTIALEVALUATION_H
#ifndef DOXYGEN_IGNORE_THIS


#include<qvmath.h>
#include<QVFunction>
#include<QVVector>
#include<QVMatrix>
#include<qvnumericalanalysis.h>

void so3EssentialEvaluation(const double *pose1, const double *pose2, double *cg0, const double Epsi = 1e-32);
QVMatrix getRotation(const double r1, const double r2, const double r3, const double Epsi);

class QuadraticFunction2: public QVFunction<QVVector, QVVector>
        {
        private:
                QVVector evaluate(const QVVector &x)
                        {
			const QVVector	v1 = x.mid(0,3),
					c1 = x.mid(3,3),
					v2 = x.mid(6,3),
					c2 = x.mid(9,3);

			const QVMatrix	R1 = expSO3(v1), R2 = expSO3(v2);
			const QVMatrix	E = R2 * ( (c2-c1) / (c2-c1).norm2() ).crossProductMatrix() * R1.transpose();

			return QVVector(9, E.getReadData());
                        }

        public:
                QuadraticFunction2(): QVFunction<QVVector, QVVector>()
                        { }
        };

QVMatrix so3EssentialEvaluation_bis(const QVVector pose1, const QVVector pose2);
void test_so3EssentialEvaluation();

#endif // DOXYGEN_IGNORE_THIS
#endif // SO3ESSENTIALEVALUATION_H


