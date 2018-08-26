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

/// @file QR-QL-RQ-LQ-test.cpp
/// @brief Test for QR, QL, RQ and LQ decomposition functions from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#include <iostream>

#include <QTime>

#include <QVApplication>
#include <QVPropertyContainer>
#include <QVMatrix>
#include <QVVector>

int main(int argc, char *argv[])
{
    // QVApplication object:
    QVApplication app(argc,argv,"Performance test for QR methods in QVision",false);

    // Container with command line parameters:
    QVPropertyContainer arg_container(argv[0]);
    arg_container.addProperty<int>("Rows",QVPropertyContainer::inputFlag,200,
                                   "Number of rows for the test matrix",1,100000);
    arg_container.addProperty<int>("Cols",QVPropertyContainer::inputFlag,100,
                                   "Number of columns for the test matrix",1,100000);
    arg_container.addProperty<int>("n_tests",QVPropertyContainer::inputFlag,1,
                                   "Number of tests to average execution time",1,100);
    arg_container.addProperty<QString>("method",QVPropertyContainer::inputFlag,"GSL_HOUSEHOLDER_THIN_QR",
                     ".............QR method (available methods follow):\n"
                     "         GSL_HOUSEHOLDER_THIN_QR | GSL_HOUSEHOLDER_FULL_QR | LAPACK_THIN_DGEQR2 | LAPACK_FULL_DGEQR2");
    arg_container.addProperty<QString>("decomposition",QVPropertyContainer::inputFlag,"QR",
                     ".................type of decomposition (QR,QL,RQ,LQ)");
    arg_container.addProperty<bool>("verbose",QVPropertyContainer::inputFlag,false,
                                   "If true, print involved matrices and vectors");
    arg_container.addProperty<bool>("show_residuals",QVPropertyContainer::inputFlag,false,
                                   "If true, print test residuals");

    // Process command line (and check for help or incorrect input parameters):
    int ret_value = app.processArguments();
    if(ret_value != 1) exit(ret_value);

    // If parameters OK, read possible parameters from command line:
     int Rows = arg_container.getPropertyValue<int>("Rows");
     int Cols = arg_container.getPropertyValue<int>("Cols");
    const int n_tests = arg_container.getPropertyValue<int>("n_tests");
    const int verbose = arg_container.getPropertyValue<bool>("verbose");
    const int show_residuals = arg_container.getPropertyValue<bool>("show_residuals");
    const QString method = arg_container.getPropertyValue<QString>("method");
    const QString decomposition = arg_container.getPropertyValue<QString>("decomposition");
    TQVQR_Method qr_method;
    if(method == "GSL_HOUSEHOLDER_THIN_QR")
        qr_method = GSL_HOUSEHOLDER_THIN_QR;
    else if(method == "GSL_HOUSEHOLDER_FULL_QR")
        qr_method = GSL_HOUSEHOLDER_FULL_QR;
    else if(method == "LAPACK_THIN_DGEQR2")
        qr_method = LAPACK_THIN_DGEQR2;
    else if(method == "LAPACK_FULL_DGEQR2")
        qr_method = LAPACK_FULL_DGEQR2;
    else {
        std::cout << "Incorrect QR method. Use --help to see available methods.\n";
        exit(-1);
    }

    std::cout << "Using values: Rows=" << Rows  << " Cols=" << Cols
              << " n_tests=" << n_tests << " QR method=" << qPrintable(method)
              << " type of decomposition=" << qPrintable(decomposition) << "\n";

    double total_ms = 0.0;

    for(int i=0;i<n_tests;i++) {

        QVMatrix M = QVMatrix::random(Rows,Cols), Q, R, L;

        QTime t;

        t.start();

        if(decomposition == "QR")
            QRDecomposition(M, Q, R, qr_method);
        else if(decomposition == "QL")
            QLDecomposition(M, Q, L, qr_method);
        else if(decomposition == "RQ")
            RQDecomposition(M, R, Q, qr_method);
        else if (decomposition == "LQ")
            LQDecomposition(M, L, Q, qr_method);
        else {
            std::cout << "Incorrect decomposition type. Use --help to see available decompositions.\n";
            exit(-1);
        }

        total_ms += t.elapsed();

        if(verbose) {
            if(decomposition == "QR") {
                std::cout << "*****************************************\n";
                std::cout << "M:" << M << "\n";
                std::cout << "Q:" << Q << "\n";
                std::cout << "R:" << R << "\n";
                std::cout << "Q R:" << Q*R << "\n";
                std::cout << "Q^T Q:" << Q.transpose()*Q << "\n";
                std::cout << "*****************************************\n";
            } else if(decomposition == "QL") {
                std::cout << "*****************************************\n";
                std::cout << "M:" << M << "\n";
                std::cout << "Q:" << Q << "\n";
                std::cout << "L:" << L << "\n";
                std::cout << "Q L:" << Q*L << "\n";
                std::cout << "Q^T Q:" << Q.transpose()*Q << "\n";
                std::cout << "*****************************************\n";
            } else if(decomposition == "RQ") {
                std::cout << "*****************************************\n";
                std::cout << "M:" << M << "\n";
                std::cout << "R:" << R << "\n";
                std::cout << "Q:" << Q << "\n";
                std::cout << "R Q:" << R*Q << "\n";
                std::cout << "Q^T Q:" << Q*Q.transpose() << "\n";
                std::cout << "*****************************************\n";
            } else if(decomposition == "LQ") {
                std::cout << "*****************************************\n";
                std::cout << "M:" << M << "\n";
                std::cout << "L:" << L << "\n";
                std::cout << "Q:" << Q << "\n";
                std::cout << "L Q:" << L*Q << "\n";
                std::cout << "Q^T Q:" << Q*Q.transpose() << "\n";
                std::cout << "*****************************************\n";
            }
        }        

        if(show_residuals) {
            if(decomposition == "QR") {
                std::cout << "QR residual = " << QRDecompositionResidual(M, Q, R) << "\n";
            } else if(decomposition == "QL") {
                std::cout << "QL residual = " << QLDecompositionResidual(M, Q, L) << "\n";
            } else if(decomposition == "RQ") {
                std::cout << "RQ residual = " << RQDecompositionResidual(M, R, Q) << "\n";
            } else if(decomposition == "LQ") {
                std::cout << "LQ residual = " << LQDecompositionResidual(M, L, Q) << "\n";
            }
        }
    }

    total_ms /= n_tests;

    if(n_tests==1)
        std::cout << "Total time: " << total_ms << " ms.\n";
    else
        std::cout << "Average total time: " << total_ms << " ms.\n";

    std::cout << "Finished.\n";    
}
