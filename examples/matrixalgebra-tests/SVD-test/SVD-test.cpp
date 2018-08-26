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

/// @file SVD-test.cpp
/// @brief Test for singular value decomposition based functions from the QVision library.
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
    QVApplication app(argc,argv,"Performance test for Singular Value Decomposition methods in QVision",false);

    // Container with command line parameters:
    QVPropertyContainer arg_container(argv[0]);
    arg_container.addProperty<int>("Rows",QVPropertyContainer::inputFlag,200,
                                   "Number of rows for the test matrix",1,100000);
    arg_container.addProperty<int>("Cols",QVPropertyContainer::inputFlag,100,
                                   "Number of columns for the test matrix",1,100000);
    arg_container.addProperty<int>("RHS_size",QVPropertyContainer::inputFlag,0,
                     "........................Number of right hand sides to solve for:\n"
                     "                                    "
                     "If 0, only decompose, if <0 solve and also return decomposition)",-1000,1000);
    arg_container.addProperty<int>("n_tests",QVPropertyContainer::inputFlag,1,
                                   "Number of tests to average execution time",1,100);
    arg_container.addProperty<QString>("method",QVPropertyContainer::inputFlag,"GSL_THIN_DECOMP_MOD",
                     ".............SVD/SV method (available methods follow):\n"
                     "                GSL_THIN_DECOMP_MOD | GSL_THIN_DECOMP | GSL_THIN_DECOMP_JACOBI |\n"
                     "                LAPACK_FULL_DGESVD | LAPACK_FULL_DGESDD | LAPACK_THIN_DGESVD | \n"
                     "                LAPACK_FULL_DGESDD ....................................(for SVD)\n"
                     "                GSL_ONLY_DECOMP_MOD | GSL_ONLY_DECOMP | GSL_ONLY_DECOMP_JACOBI |\n"
                     "                LAPACK_ONLY_DGESVD | LAPACK_ONLY_DGESDD ...........(for SV only)");
    arg_container.addProperty<bool>("verbose",QVPropertyContainer::inputFlag,false,
                                   "If true, print involved matrices and vectors");
    arg_container.addProperty<bool>("show_residuals",QVPropertyContainer::inputFlag,false,
                                   "If true, print test residuals");

    // Process command line (and check for help or incorrect input parameters):
    int ret_value = app.processArguments();
    if(ret_value != 1) exit(ret_value);

    // If parameters OK, read possible parameters from command line:
    const int Rows = arg_container.getPropertyValue<int>("Rows");
    const int Cols = arg_container.getPropertyValue<int>("Cols");
    int RHS_size = arg_container.getPropertyValue<int>("RHS_size");
    const int n_tests = arg_container.getPropertyValue<int>("n_tests");
    const int verbose = arg_container.getPropertyValue<bool>("verbose");
    int show_residuals = arg_container.getPropertyValue<bool>("show_residuals");
    const QString method = arg_container.getPropertyValue<QString>("method");
    TQVSVD_Method svd_method;
    TQVSV_Method sv_method;
    bool only_sv = false;
    if(method == "GSL_THIN_DECOMP_MOD")
        svd_method = GSL_THIN_DECOMP_MOD;
    else if(method == "GSL_THIN_DECOMP")
        svd_method = GSL_THIN_DECOMP;
    else if(method == "GSL_THIN_DECOMP_JACOBI")
        svd_method = GSL_THIN_DECOMP_JACOBI;
    else if(method == "LAPACK_FULL_DGESVD")
        svd_method = LAPACK_FULL_DGESVD;
    else if(method == "LAPACK_FULL_DGESDD")
        svd_method = LAPACK_FULL_DGESDD;
    else if(method == "LAPACK_THIN_DGESVD")
        svd_method = LAPACK_THIN_DGESVD;
    else if(method == "LAPACK_THIN_DGESDD")
        svd_method = LAPACK_THIN_DGESDD;
    else if(method == "LAPACK_ONLY_DGESVD") {
        sv_method = LAPACK_ONLY_DGESVD;
        only_sv = true;
    } else if(method == "GSL_ONLY_DECOMP_MOD") {
        sv_method = GSL_ONLY_DECOMP_MOD;
        only_sv = true;
    } else if(method == "GSL_ONLY_DECOMP") {
        sv_method = GSL_ONLY_DECOMP;
        only_sv = true;
    } else if(method == "GSL_ONLY_DECOMP_JACOBI") {
        sv_method = GSL_ONLY_DECOMP_JACOBI;
        only_sv = true;
    } else if(method == "LAPACK_ONLY_DGESVD") {
        sv_method = LAPACK_ONLY_DGESVD;
        only_sv = true;
    } else if(method == "LAPACK_ONLY_DGESDD") {
        sv_method = LAPACK_ONLY_DGESDD;
        only_sv = true;
    } else {
        std::cout << "Incorrect SVD/SV method. Use --help to see available methods.\n";
        exit(-1);
    }

    if(only_sv) {
        // Only singular values asked for; no solving or residuals computed:
        if(RHS_size != 0) {
            std::cout << "Only singular values asked for; RHS_size forced 0.\n";
            RHS_size = 0;
        }
    }

    std::cout << "Using values: Rows=" << Rows  << " Cols=" << Cols << " RHS_size=" << RHS_size
              << " n_tests=" << n_tests << " SVD method=" << qPrintable(method) << "\n";

    double total_ms = 0.0;

    for(int i=0;i<n_tests;i++) {

        QVMatrix M = QVMatrix::random(Rows,Cols), U, V, X, B, X_sol;
        QVVector s, x, b, x_sol;

        if(not only_sv) {
            // We generate RHS_size random solutions, and the corresponding right hand sides (for testing):
            if(qAbs(RHS_size) == 1) {
                x_sol = QVVector::random(Cols);
                b = M * x_sol;
            } else if (qAbs(RHS_size) > 1) {
                X_sol = QVMatrix::random(Cols,qAbs(RHS_size));
                B = M * X_sol;
            }
        }

        QTime t;

        t.start();

        if(only_sv)
            SingularValues(M, s, sv_method);
        else if(RHS_size == 0)
            SingularValueDecomposition(M, U, s, V, svd_method);
        else if(RHS_size == 1)
            SolveBySingularValueDecomposition(M, x, b, svd_method);
        else if(RHS_size > 1)
            SolveBySingularValueDecomposition(M, X, B, svd_method);
        else if (RHS_size == -1)
            SolveBySingularValueDecomposition(M, x, b, U, s, V, svd_method);
        else if (RHS_size < -1)
            SolveBySingularValueDecomposition(M, X, B, U, s, V, svd_method);

         total_ms += t.elapsed();

        if(verbose) {
            if(only_sv) {
                std::cout << "*****************************************\n";
                std::cout << "M:" << M << "\n";
                std::cout << "s:" << s << "\n";
                std::cout << "*****************************************\n";
            } else {
                if(RHS_size <= 0) {
                    std::cout << "*****************************************\n";
                    std::cout << "M:" << M << "\n";
                    std::cout << "U:" << U << "\n";
                    std::cout << "s:" << s << "\n";
                    std::cout << "V:" << V << "\n";
                    QVMatrix S = QVMatrix::diagonal(s);
                    const int m = U.getCols(), n = V.getCols();
                    if (m>n)
                        S = S & QVMatrix(m-n,n,0.0);
                    else if (m<n)
                        S = S | QVMatrix(m,n-m,0.0);
                    std::cout << "U diag(s) V^T:" << U*S*V.transpose() << "\n";
                    std::cout << "U^T U:" << U.transpose()*U << "\n";
                    std::cout << "V^T V:" << V.transpose()*V << "\n";
                    std::cout << "*****************************************\n";
                }
                if(qAbs(RHS_size) == 1) {
                    std::cout << "*****************************************\n";
                    std::cout << "M:" << M << "\n";
                    std::cout << "b:" << b << "\n";
                    std::cout << "x:" << x << "\n";
                    std::cout << "x_sol:" << x_sol << "\n";
                    std::cout << "*****************************************\n";
                }
                if(qAbs(RHS_size) > 1){
                    std::cout << "*****************************************\n";
                    std::cout << "M:" << M << "\n";
                    std::cout << "B:" << B << "\n";
                    std::cout << "X:" << X << "\n";
                    std::cout << "X_sol:" << X_sol << "\n";
                    std::cout << "*****************************************\n";
                }
            }
        }        

        if(show_residuals) {
            if(only_sv) {
                std::cout << "SV residual = " << SingularValuesResidual(M, s) << "\n";
            } else {
                if(RHS_size <= 0) {
                    std::cout << "SVD residual = " << SingularValueDecompositionResidual(M, U, s, V) << "\n";
                }
                if(qAbs(RHS_size) == 1) {
                    std::cout << "Test solve residual = " << SolveResidual(M, x_sol, b) << "\n";
                    std::cout << "SVD solve residual = " << SolveResidual(M, x, b) << "\n";
                    std::cout << "x - x_sol residual = " << (x-x_sol).norm2() << "\n";
                    std::cout << "x norm = " << x.norm2() << "\n";
                    std::cout << "x_sol norm = " << x_sol.norm2() << "\n";
                }
                if(qAbs(RHS_size) > 1) {
                    std::cout << "Test solve residual = " << SolveResidual(M, X_sol, B) << "\n";
                    std::cout << "SVD solve residual = " << SolveResidual(M, X, B) << "\n";
                }
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
