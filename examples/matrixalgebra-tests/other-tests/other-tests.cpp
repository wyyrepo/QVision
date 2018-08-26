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

/// @file other-tests.cpp
/// @brief Several miscellaneous tests for additional functions of the matrix algebra module of the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#include <iostream>

#include <QTime>

#include <QVApplication>
#include <QVPropertyContainer>
#include <QVMatrix>
#include <QVVector>
#include <QVPermutation>

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    std::cout << "************PSEUDOINVERSE*************\n";

    QVMatrix A = QVMatrix(4,3, QVVector()
                          <<  1 << -2 <<  4
                          << -1 <<  0 <<  7
                          << -4 <<  6 <<  4
                          <<  0 <<  5 <<  3 );

    std::cout << "A:" << A << "\n";
    std::cout << "pseudoInverse(A):" << pseudoInverse(A) << "\n";
    std::cout << "pseudoInverse(A^T):" << pseudoInverse(A.transpose()) << "\n";
    std::cout << "A*pseudoInverse(A)*A:" << A*pseudoInverse(A)*A << "\n";
    std::cout << "pseudoInverse(A)*A*pseudoInverse(A):" << pseudoInverse(A)*A*pseudoInverse(A) << "\n";

    QVVector u[2],v[2],values,s;
    u[0] << 1 << -2 <<  2;
    u[0] = u[0] / u[0].norm2();
    u[1] << 2 <<  1 <<  0;
    u[1] = u[1] / u[1].norm2(); // u[0] and u[1] orthogonal.
    v[0] << 3 << -1 << -2 << 0 << -2;
    v[0] = v[0] / v[0].norm2();
    v[1] << 0 << 2  << -2 << 0 << 1;
    v[1] = v[1] / v[1].norm2(); // v[0] and v[1] orthogonal.

    values << 3.25 << 0.75;

    QVMatrix B, U, V;
    B = values[0]*(u[0].outerProduct(v[0])) + values[1]*(u[1].outerProduct(v[1]));
    
    SingularValueDecomposition(B,U,s,V);
    std::cout << "u[0]:" << u[0] << "\n";
    std::cout << "u[1]:" << u[1] << "\n";
    std::cout << "v[0]:" << v[0] << "\n";
    std::cout << "v[1]:" << v[1] << "\n";
    std::cout << "values:" << values << "\n";    
    std::cout << "B:" << B << "\n";
    std::cout << "U:" << U << "\n";
    std::cout << "s:" << s << "\n";
    std::cout << "V:" << V << "\n";
    std::cout << "SVD residual = " << SingularValueDecompositionResidual(B,U,s,V) << "\n";

    std::cout << "************DETERMINANT**************\n";

    QVMatrix C = QVMatrix(4,4, QVVector()
                          <<  1 << -2 <<   4 << 5
                          << -1 <<  0 <<  -7 << 4
                          << -4 <<  6 <<   4 << -2
                          <<  0 <<  5 <<   3 << 3);
    std::cout << "C: " << C << "\n";
    std::cout << "determinant(C): " << determinant(C) << "\n";

    std::cout << "**********SOLVE HOMOGENEOUS**********\n";
    QVector<double> x;
    SolveHomogeneous(B, x, LAPACK_THIN_DGESVD);
    std::cout << "B: " << B << "\n";
    std::cout << "x: " << x << "\n";
    std::cout << "B*x: " << B*x << "\n";

    return 0;
}
