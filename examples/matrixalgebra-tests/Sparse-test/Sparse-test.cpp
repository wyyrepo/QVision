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

/// @file Sparse-test.cpp
/// @brief Test for solving of sparse systems of equations based functions from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#include <iostream>

#include <QTime>

#include <QVApplication>
#include <QVPropertyContainer>
#include <QVSparseBlockMatrix>
#include <qvmatrixalgebra.h>

int main(int argc, char *argv[])
{
    // QVApplication object:
    QVApplication app(argc,argv,"Performance test for solving of sparse systems of equation methods in QVision",false);

    // Container with command line parameters:
    QVPropertyContainer arg_container(argv[0]);
    arg_container.addProperty<int>("Blocks",QVPropertyContainer::inputFlag,20,
                                   "# of row blocks (size for the square sparse block test matrix)",1,1000);
    arg_container.addProperty<int>("Rows",QVPropertyContainer::inputFlag,10,
                                   "# of rows per block (size for each square block of test matrix)",1,1000);
    arg_container.addProperty<int>("n_tests",QVPropertyContainer::inputFlag,1,
                                   "Number of tests to average execution time",1,100);
    arg_container.addProperty<QString>("method",QVPropertyContainer::inputFlag,"QVMKL_DSS",
                     "........Sparse solving method to use (available methods follow):\n"
                     "                                                                               "
                     "QVMKL_DSS | QVMKL_ISS");
    arg_container.addProperty<bool>("verbose",QVPropertyContainer::inputFlag,false,
                                   "If true, print involved matrices and vectors");
    arg_container.addProperty<bool>("symmetric",QVPropertyContainer::inputFlag,true,
                                   "If true, coefficient matrix will be symmetric");
    arg_container.addProperty<bool>("positive",QVPropertyContainer::inputFlag,true,
                                   "If true, coefficient matrix will be positive definite");
    arg_container.addProperty<double>("prob",QVPropertyContainer::inputFlag,0.5,
                                   "Probability of a block of being nonzero in the generated matrix",0.0,1.0);
    arg_container.addProperty<bool>("iters_or_resid",QVPropertyContainer::inputFlag,false,
                                   "(only ISS method) if true, use iters, otherwise resid");
    arg_container.addProperty<int>("iters",QVPropertyContainer::inputFlag,20,
                                   "(only ISS method) Number of iterations to be executed by method",1,500);
    arg_container.addProperty<double>("resid",QVPropertyContainer::inputFlag,1.0E-10,
                                   "(only ISS method) iterate until square of residual below this");
    arg_container.addProperty<bool>("progressive",QVPropertyContainer::inputFlag,false,
                                   ".....(only ISS method) If true, consecutively execute method \n"
                                   "                                  "
                                   "for 1, 2, 3, etc. iterations (in order to show rate of convergence, \n"
                                   "                                  "
                                   "combine with --show_residuals to print successive values)");
    arg_container.addProperty<bool>("grad_desc",QVPropertyContainer::inputFlag,false,
                                   "......(only ISS method) If true, repeatedly execute method for\n"
                                   "                                  "
                                   "only one iteration, starting in each step from the current solution\n"
                                   "                                    "
                                   "(this ammounts to a simple gradient descent method); combine with\n"
                                   "                                  "
                                   "show_residuals to print successive values in order to show (slower)\n"
                                   "                                  "
                                   "rate of convergence. Overrides progressive option");
    arg_container.addProperty<bool>("show_residuals",QVPropertyContainer::inputFlag,false,
                                   "If true, print test residuals");

    // Process command line (and check for help or incorrect input parameters):
    int ret_value = app.processArguments();
    if(ret_value != 1) exit(ret_value);

    // If parameters OK, read possible parameters from command line:
    const int Blocks = arg_container.getPropertyValue<int>("Blocks");
    const int Rows = arg_container.getPropertyValue<int>("Rows");
    const int n_tests = arg_container.getPropertyValue<int>("n_tests");
    const QString method = arg_container.getPropertyValue<QString>("method");
    const bool verbose = arg_container.getPropertyValue<bool>("verbose");
    const bool symmetric = arg_container.getPropertyValue<bool>("symmetric");
    const bool positive = arg_container.getPropertyValue<bool>("positive");
    const double prob = arg_container.getPropertyValue<double>("prob");
    const bool iters_or_resid = arg_container.getPropertyValue<bool>("iters_or_resid");
    const int iters = arg_container.getPropertyValue<int>("iters");
    const double resid = arg_container.getPropertyValue<double>("resid");
    const bool progressive = arg_container.getPropertyValue<bool>("progressive");
    const bool grad_desc = arg_container.getPropertyValue<bool>("grad_desc");
    const bool show_residuals = arg_container.getPropertyValue<bool>("show_residuals");

    TQVSparseSolve_Method sparse_method;
    if(method == "QVMKL_DSS")
        sparse_method = QVMKL_DSS;
    else if(method == "QVMKL_ISS")
        sparse_method = QVMKL_ISS;
    else {
        std::cout << "Incorrect sparse method. Use --help to see available methods.\n";
        exit(-1);
    }
    std::cout << "Using values: Blocks=" << Blocks << " Rows=" << Rows << " prob=" << prob;
    if(symmetric) {
        std::cout << " symmetric";
        if(positive)
            std::cout << " positive definite";
        else
            std::cout << " undefinite";
    } else {
        std::cout << " non-symmetric";
    }
    std::cout << " n_tests=" << n_tests << " Sparse method=" << qPrintable(method);
    if(sparse_method == QVMKL_ISS) {
        if(iters_or_resid)
            std::cout << " iters=" << iters;
        else
            std::cout << " resid=" << resid;
        if(grad_desc)
            std::cout << " grad_desc" ;
        else if(progressive)
            std::cout << " progressive" ;
    }
    std::cout << "\n";

    double total_ms = 0.0;

    for(int i=0;i<n_tests;i++) {

        QVSparseBlockMatrix M = QVSparseBlockMatrix::randomSquare(Blocks,Rows,prob,symmetric,positive);

        QVMatrix M_dense = M;

        QVVector x, b, x_sol;

        // We generate a random solution, and the corresponding right hand side (for testing):
        x_sol = QVVector::random(Blocks*Rows);
        b = M_dense * x_sol;

        QTime t;

        t.start();

        double returned_squared_residual = resid;
        QList<double> residual_list;
        int final_iters;

        if(sparse_method == QVMKL_ISS) {
            if(grad_desc or progressive) {
                // Iterative solving; stopping test based on #iterations or residual.
                int j;
                for(j=0;(iters_or_resid?(j<iters):(returned_squared_residual>=resid and (j<b.size() or grad_desc)));j++) {
                    if(grad_desc) {
                        // Iteratively solve for only one iteration, starting from previous solution (= gradient descent).
                        returned_squared_residual =
                            SparseSolve(M, x, b, symmetric, positive, QVMKL_ISS, (j==0)?false:true, true, 1);
                    } else if(progressive) {
                        // Iteratively solve for 1, 2, 3, ... iterations.
                        returned_squared_residual =
                            SparseSolve(M, x, b, symmetric, positive, QVMKL_ISS, false, true, j+1);
                    }
                    residual_list << sqrt(returned_squared_residual);
                }
                final_iters = j;
            } else {
                // Usual form of conjugate gradient method, stopping test based on #iterations or residual:
                SparseSolve(M, x, b, symmetric, positive, QVMKL_ISS, false, iters_or_resid, iters, resid, final_iters);
            }
        } else {
            // QVMKL_DSS closed form, non iterative method:
            SparseSolve(M, x, b, symmetric, positive, QVMKL_DSS);
        }

        total_ms += t.elapsed();

        if(verbose) {
            std::cout << "*****************************************\n";
            // std::cout << "M:" << M << "\n";
            std::cout << "M_dense:" << M_dense << "\n";
            if(symmetric) {
                QVVector lambda;
                EigenValues(M_dense, lambda, LAPACK_DSYEV_ONLY);
                std::cout << "Eigenvalues of M_dense: " << lambda << "\n";
            }
            std::cout << "b:" << b << "\n";
            std::cout << "x:" << x << "\n";
            std::cout << "x_sol:" << x_sol << "\n";
            std::cout << "*****************************************\n";
        }        

        if(show_residuals) {
            std::cout << "Test solve residual = " << SolveResidual(M_dense, x_sol, b) << "\n";
            double residual = SolveResidual(M_dense, x, b);
            std::cout << "Sparse solve residual = " << residual;
            if (sparse_method == QVMKL_ISS and not iters_or_resid)
                std::cout << " (square residual = " << residual*residual << ")";
            if (sparse_method == QVMKL_ISS)
                std::cout << " (final_iters = " << final_iters << ")";
            std::cout << "\n";
            if (sparse_method == QVMKL_ISS and (progressive or grad_desc)) {
                std::cout << "Residual list (" << residual_list.size() << " elems.):";
                for (int k=0; k<residual_list.size(); k++)
                    std::cout << " " << residual_list[k] ; // << std::endl;
                std::cout << "\n";
            }
            std::cout << "x - x_sol residual = " << (x-x_sol).norm2() << "\n";
            std::cout << "x norm = " << x.norm2() << "\n";
            std::cout << "x_sol norm = " << x_sol.norm2() << "\n";
        }
    }   

    total_ms /= n_tests;

    if(n_tests==1)
        std::cout << "Total time: " << total_ms << " ms.\n";
    else
        std::cout << "Average total time: " << total_ms << " ms.\n";

    std::cout << "Finished.\n";    
}
