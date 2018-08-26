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

/// @file Eigen-test.cpp
/// @brief Test for eigendecomposition based functions from the QVision library.
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
    QVApplication app(argc,argv,"Performance test for eigendecomposition methods in QVision",false);

    // Container with command line parameters:
    QVPropertyContainer arg_container(argv[0]);
    arg_container.addProperty<int>("Rows",QVPropertyContainer::inputFlag,200,
                                   "Number of rows (=cols) for the square test matrix",1,100000);
    arg_container.addProperty<int>("n_tests",QVPropertyContainer::inputFlag,1,
                                   "Number of tests to average execution time",1,100);
    arg_container.addProperty<QString>("method",QVPropertyContainer::inputFlag,"GSL_EIGENSYMM",
                     ".......Eigendecomposition method (available methods follow):\n"
                     "                               GSL_EIGENSYMM | GSL_EIGENSYMM_ONLY | LAPACK_DSYEV | LAPACK_DSYEV_ONLY");
    arg_container.addProperty<bool>("verbose",QVPropertyContainer::inputFlag,false,
                                   "If true, print involved matrices and vectors");
    arg_container.addProperty<bool>("show_residuals",QVPropertyContainer::inputFlag,false,
                                   "If true, print test residuals");

    // Process command line (and check for help or incorrect input parameters):
    int ret_value = app.processArguments();
    if(ret_value != 1) exit(ret_value);

    // If parameters OK, read possible parameters from command line:
    const int Rows = arg_container.getPropertyValue<int>("Rows");
    const int n_tests = arg_container.getPropertyValue<int>("n_tests");
    const int verbose = arg_container.getPropertyValue<bool>("verbose");
    const int show_residuals = arg_container.getPropertyValue<bool>("show_residuals");
    const QString method = arg_container.getPropertyValue<QString>("method");
    TQVEigenDecomposition_Method eigen_method = GSL_EIGENSYMM;
    TQVEigenValues_Method eigenonly_method = GSL_EIGENSYMM_ONLY;
    bool only_ev = false;
    if(method == "GSL_EIGENSYMM")
        eigen_method = GSL_EIGENSYMM;
    else if(method == "LAPACK_DSYEV")
        eigen_method = LAPACK_DSYEV;
    else if(method == "GSL_EIGENSYMM_ONLY") {
        eigenonly_method = GSL_EIGENSYMM_ONLY;
        only_ev = true;
    } else if(method == "LAPACK_DSYEV_ONLY") {
        eigenonly_method = LAPACK_DSYEV_ONLY;
        only_ev = true;
    } else {
        std::cout << "Incorrect eigendecomposition method. Use --help to see available methods.\n";
        exit(-1);
    }

    std::cout << "Using values: Rows=" << Rows
              << " n_tests=" << n_tests << " eigendecomposition method=" << qPrintable(method) << "\n";

    double total_ms = 0.0;

    for(int i=0;i<n_tests;i++) {

        QVMatrix M = QVMatrix::random(Rows,Rows), Q;
        M = M + M.transpose(); // Force symmetric matrix.
        QVVector lambda;

        QTime t;

        t.start();

        if(only_ev)
            EigenValues(M, lambda, eigenonly_method);
        else
            EigenDecomposition(M, lambda, Q, eigen_method);

        total_ms += t.elapsed();

        if(verbose) {
            if(only_ev) {
                std::cout << "*****************************************\n";
                std::cout << "M:" << M << "\n";
                std::cout << "lambda:" << lambda << "\n";
                std::cout << "*****************************************\n";
            } else {
                std::cout << "*****************************************\n";
                std::cout << "M:" << M << "\n";
                std::cout << "lambda:" << lambda << "\n";
                std::cout << "Q:" << Q << "\n";
                std::cout << "Q diag(lambda) Q^T:" << Q*QVMatrix::diagonal(lambda)*Q.transpose() << "\n";
                std::cout << "Q^T Q:" << Q.transpose()*Q << "\n";
                std::cout << "*****************************************\n";
            }
        }        

        if(show_residuals) {
            if(only_ev) {
                std::cout << "EigenValues residual = " << EigenValuesResidual(M, lambda) << "\n";
            } else {
                std::cout << "EigenDecomposition residual = " << EigenDecompositionResidual(M, lambda, Q) << "\n";
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
