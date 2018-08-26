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

#ifndef NUMERICALANALYSIS_H
#define NUMERICALANALYSIS_H

/// @file
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#include <QVVector>
#include <QVMatrix>
#include <QVFunction>

/*! @brief Estimates the gradient vector for the function using the forward two-points rule for the derivative approximation.

This function obtains a numerical approximation of the gradient at a given point for a function. The forward derivative formula is used to estimate each partial derivative value, component of the gradient vector:

\f$ \frac{ \partial f}{ \partial x_i} \left( \textbf{x} \right) = \lim_{h\to 0}{f(x_1, \ldots, x_i + h, \ldots, x_n)-f(x_1, \ldots, x_i, \ldots, x_n)\over h}\f$

The function to estimate the gradient is provided as a @ref QVFunction object.

@param function object containing the function to estimate gradient.
@param point Point to evaluate the gradient vector.
@param h Increment coeficient for the derivative formula.
@ingroup qvnumericalanalysis
*/
const QVVector qvEstimateGradient(	QVFunction<QVVector, double> &function,
                    const QVVector &point, const double h = 1e-6);

/*! @brief Estimates the Jacobian matrix for the function using the forward two-points rule for the derivative approximation.

This function obtains a numerical approximation of the Jacobian of a \f$ R^n \to R^m \f$  function at a given point. The forward derivative formula is used to estimate each partial derivative value, component of the Jacobian:

\f$ \frac{ \partial f}{ \partial x_i} \left( \textbf{x} \right) = \lim_{h\to 0}{f(x_1, \ldots, x_i + h, \ldots, x_n)-f(x_1, \ldots, x_i, \ldots, x_n)\over h}\f$

The function to estimate the gradient is provided as a @ref QVFunction object.

@param function function object to estimate Jacobian.
@param point Point to evaluate the Jacobian matrix.
@param h Increment coeficient for the derivative formula.
@ingroup qvnumericalanalysis
*/
const QVMatrix qvEstimateJacobian(	QVFunction<QVVector, QVVector> &function,
                    const QVVector &point, const double h = 1e-6);

/*! @brief Estimates the hessian matrix for the function using the forward two-point rule for the derivative approximation.

This function obtains a numerical approximation of the hessian matrix at a given pointfor a function. The following formula is used to compute the components fo the hessian matrix:

\f$ H_{i, j}(f) = \frac{	f(x_1, \ldots, x_i + h, \ldots, x_j + h, \ldots, x_n) + f(x_1, \ldots, x_i, \ldots, x_j, \ldots, x_n)
                f(x_1, \ldots, x_i + h, \ldots, x_j, \ldots, x_n) + f(x_1, \ldots, x_i, \ldots, x_j + h, \ldots, x_n)
}{h^2}\f$

It is derived from the forward derivative formula used to estimate each partial derivative value:

\f$ \frac{ \partial f}{ \partial x_i} \left( \textbf{x} \right) = \lim_{h\to 0}{f(x_1, \ldots, x_i + h, \ldots, x_n)-f(x_1, \ldots, x_i, \ldots, x_n)\over h}\f$

The function to estimate the hessian is provided as a @ref QVFunction object.

@param function object containing the function to estimate hessian.
@param point Point to evaluate the hessian matrix.
@param h Increment coeficient for the derivative formula.
@ingroup qvnumericalanalysis
*/
const QVMatrix qvEstimateHessian(	QVFunction<QVVector, double> &function,
                    const QVVector &point, const double h = 1e-3);

/*!
@brief GSL Minimization algorithms.

@see qvGSLMinimize

@ingroup qvnumericalanalysis
*/
enum GSLMinFMinimizer
    {
    /// The golden section algorithm. The simplest method of bracketing the minimum of a function.
    GoldenSection = 0,
    /// The Brent minimization algorithm. Combines a parabolic interpolation with the golden section algorithm.
    BrentMinimization = 1
    };

/*!
@brief GSL multidimensional minimization algorithms using gradient information.

@see qvGSLMinimizeFDF

@ingroup qvnumericalanalysis
*/
enum GSLMultiminFDFMinimizerType
    {
    /// Fletcher-Reeves conjugate gradient algorithm.
    ConjugateFR = 0,
    /// Polak-Ribiere conjugate gradient algorithm.
    ConjugatePR = 1,
    /// Broyden-Fletcher-Goldfarb-Shanno (BFGS) algorithm.
    VectorBFGS = 2,
    /// The steepest descent algorithm.
    SteepestDescent = 3
    };

/*!
@brief GSL multidimensional solving.

@see qvGSLSolveFDF

@ingroup qvnumericalanalysis
*/
enum GSLMultiminFDFSolverType
    {
    /// Scaled Levenberg-Marquardt algorithm.
    LMScaledDerivative = 0,

    /// Non-scaled (faster) Levenberg-Marquardt algorithm.
    LMDerivative = 1
    };

/*!
@brief Wrapper to GSL multivariate function minimization using gradient information.

This function minimizes a multivariate function contained in a @ref QVFunction object, using the GSL functionality for that purpose. The gradient of that function is estimated using the @ref qvEstimateGradient function, and is used in the minimization process.

An usage example follows:
@code
#include <qvnumericalanalysis.h>

// Creation of a quadratic function class type
class QuadraticFunction: public QVFunction<QVVector, double>
    {
    private:
        const QVMatrix A;
        const QVVector b;
        const double c;

        double evaluate(const QVVector &x)
            {
            return x*A*x + b*x + c;
            }

    public:
        QuadraticFunction(const QVMatrix &A, const QVVector &b, const double c): QVFunction<QVVector, double>(),
            A(A), b(b), c(c)
            { }
    };

// Main code
int main()
    {
    // Example quadratic function object creation
    QVMatrix A = QVMatrix::zeros(3,3);
    QVVector b = QVVector(3,0);
    double c;

    A(0,0) = 70;	A(1,1) = 11;	A(2,2) = 130;
    b = QVVector(3); b[0] = -100; b[1] = 20; b[2] = -30;
    c = 100;

    QuadraticFunction f(A, b, c);

    // Function minimization
    QVVector minimum(3,0);
    qvGSLMinimizeFDF(f, minimum);

    std::cout << "Function minimum value = " << f(minimum) << std::endl;
    std::cout << "Reached at point = " << minimum << std::endl;;
    }
@endcode

@param function			Object containing the function to minimize.
@param point			Starting point for the minimization. This vector will contain the obtained minimum when the function returns.
@param gslMinimizerAlgorithm	Minimization algorithm. See enumeration @ref GSLMultiminFDFMinimizerType for possible values.
@param maxIterations		Maximum number of steps to perform by the minimization.
@param maxGradientNorm		Minimal value of the gradient size (norm 2) to stop the minimization when reached.
@param step			Corresponds to parameter <i>step</i> for the <i>gsl_multimin_fdfminimizer_set</i> function.
@param tol			Corresponds to parameter <i>tol</i> for the <i>gsl_multimin_fdfminimizer_set</i> function.

@warning The GSL compatibility must be enabled to use this function.
@return	True if the search was successful. False else.
@see GSLMultiminFDFMinimizerType

@ingroup qvnumericalanalysis
*/
#ifdef GSL_AVAILABLE
bool qvGSLMinimizeFDF (	const QVFunction<QVVector, double> & function, QVVector &point,
                const GSLMultiminFDFMinimizerType gslMinimizerAlgorithm = ConjugateFR,
                const int maxIterations = 100, const double maxGradientNorm = 1e-3,
                const double step = 0.01, const double tol = 1e-4);
#endif

/*!
@brief Wrapper to GSL multivariate function minimization using gradient information.

This is an overloaded version of the function @ref qvGSLMinimizeFDF(QVFunction<QVVector, double> &, QVVector &, const GSLMultiminFDFMinimizerType, const int, const double, const double, const double) provided for convenience.

The real gradient of the function is used in the form of a vector function object, instead of the numerical approximation @ref qvEstimateGradient to the gradient, which is less accurate and generally less efficient. An example code usage follows:

@code
#include <qvnumericalanalysis.h>

// Creation of a quadratic function class type
class QuadraticFunction: public QVFunction<QVVector, double>
    {
    private:
        const QVMatrix A;
        const QVVector b;
        const double c;

        double evaluate(const QVVector &x)
            {
            return x*A*x + b*x + c;
            }

    public:
        QuadraticFunction(const QVMatrix &A, const QVVector &b, const double c): QVFunction<QVVector, double>(),
            A(A), b(b), c(c)
            { }
    };

// Creation of a quadratic vector function class type, corresponding to the gradient of the previous function
class QuadraticFunctionGradient: public QVFunction<QVVector, QVVector>
    {
    private:
        const QVMatrix A;
        const QVVector b;
        const double c;

        QVVector evaluate(const QVVector &x)
            {
            return A*x*2 + b;
            }

    public:
        QuadraticFunctionGradient(const QVMatrix &A, const QVVector &b, const double c): QVFunction<QVVector, QVVector>(),
            A(A), b(b), c(c)
            { }
    };

// Main code
int main()
    {
    // Example quadratic function and corresponding gradient objects creation
    QVMatrix A = QVMatrix::zeros(3,3);
    QVVector b = QVVector(3,0);
    double c;

    A(0,0) = 70;	A(1,1) = 11;	A(2,2) = 130;
    b = QVVector(3); b[0] = -100; b[1] = 20; b[2] = -30;
    c = 100;

    QuadraticFunction		f(A, b, c);
    QuadraticFunctionGradient	g(A, b, c);

    // Function minimization
    QVVector minimum(3,0);
    qvGSLMinimizeFDF(f, g, minimum);

    std::cout << "Function minimum value = " << f(minimum) << std::endl;
    std::cout << "Reached at point = " << minimum << std::endl;
    }
@endcode

@param function			Object containing the function to minimize.
@param gradientFunction		Object containing the gradient vector function.
@param point			Starting point for the minimization. This vector will contain the obtained minimum when the function returns.
@param gslMinimizerAlgorithm	Minimization algorithm. See enumeration @ref GSLMultiminFDFMinimizerType for possible values.
@param maxIterations		Maximum number of steps to perform the minimization.
@param maxGradientNorm		Minimal value of the gradient size (norm 2) to stop the minimization when reached.
@param step			Corresponds to parameter <i>step</i> for the <i>gsl_multimin_fdfminimizer_set</i> function.
@param tol			Corresponds to parameter <i>tol</i> for the <i>gsl_multimin_fdfminimizer_set</i> function.

@warning The GSL compatibility must be enabled to use this function.
@return	True if the search was successful. False else.
@see qvGSLMinimizeFDF(QVFunction<QVVector, double> &, QVVector &, const GSLMultiminFDFMinimizerType, const int, const double, const double, const double)
@see GSLMultiminFDFMinimizerType

@ingroup qvnumericalanalysis
*/
#ifdef GSL_AVAILABLE
bool qvGSLMinimizeFDF (	const QVFunction<QVVector, double> & function,
                const QVFunction<QVVector, QVVector> & gradientFunction,
                QVVector &point, const GSLMultiminFDFMinimizerType gslMinimizerAlgorithm = ConjugateFR,
                const int maxIterations = 100, const double maxGradientNorm = 1e-3,
                const double step = 0.01, const double tol = 1e-4);
#endif

/*!
@brief Solves a non-linear system of equations

This function uses a nonlinear least-squares optimization procedure to obtain a solution for a system of equations. The input of this functions is a function object, containing a \f$ R^n \to R^m \f$ function, that maps the input variables for the system, to the vector of residual values of the system of equations.

The function uses the Levenberg-Marquardt optimization algoritm to find an aproximation to a valid solution, starting from an initial guess of the solution.

The optimization finishes when performing a fixed number of maximum iterations. Also, a stopping criteria is applied. The convergence is tested by comparing the last step <i>dx</i> with the absolute error <i>maxAbsErr</i> and relative error <i>maxRelErr</i> to the current position <i>x</i>. The test is true  if the following condition is achieved:

\f$  \|\partial x_i\| \leq maxAbsErr + maxRelErr \| x_i \|  \f$

In that case the function stops and returns the point where the function returns the minimum value.

The following code is an usage example of this function. It fits an exponential model on some input measurements:

@code
#include <qvnumericalanalysis.h>
class FittingErrorFunction: public QVFunction<QVVector, QVVector>
        {
        private:
        const QVVector x, y;

                QVVector evaluate(const QVVector &v)
                        {
            // Evaluate the function
            QVVector result(y.size(), 0.0);
            for (int i = 0; i < y.size(); i++)
                result[i] = v[0] * exp (-v[1] * double(x[i])) + v[2];

            // Return residuals
            return result - y;
            }

        public:
            FittingErrorFunction(const QVVector &x, const QVVector &y): QVFunction<QVVector, QVVector>(), x(x), y(y) { }
            };

class FittingErrorFunctionJacobian: public QVFunction<QVVector, QVMatrix>
        {
        private:
        const QVVector x, y;

                QVMatrix evaluate(const QVVector &v)
                        {
            FittingErrorFunction error(x, y);
            return qvEstimateJacobian(error, v);
            }

        public:
            FittingErrorFunctionJacobian(const QVVector &x, const QVVector &y): QVFunction<QVVector, QVMatrix>(), x(x), y(y) { }
            };

int main()
    {
    QVVector x, y;
    for (int i = 0; i < 40; i++)
        {
        x << double(i);
        y << 1.0 + 5 * exp (-0.1 * double(i));
        }

    // Create initial guess, and objective functions.
    QVVector v(3, 0.0);
    FittingErrorFunction function(x, y);
    FittingErrorFunctionJacobian functionJacobian(x, y);

    qvGSLSolveFDF (function, functionJacobian, v, LMScaledDerivative, 500);

    std::cout << "Solution for the system obtained at " << v << std::endl;
    }
@endcode

@warning The GSL compatibility must be enabled to use this function.
@param function Function representing the residuals of the system of equations.
@param functionJacobian Jacobian of the residual function.
@param x Initial guess of the solution. Also, the minimum value will be stored in this variable.
@param gslSolverAlgorithm The algorithm to perform minimization.
@param maxIterations Maximum number of iterations to perform optimization.
@param maxAbsErr Maximal absolute error in the optimization stop condition.
@param maxRelErr Maximal relative error in the optimization stop condition.

@ingroup qvnumericalanalysis
*/
#ifdef GSL_AVAILABLE
bool qvGSLSolveFDF (	const QVFunction<QVVector, QVVector> & function,
                const QVFunction<QVVector, QVMatrix> & functionJacobian,
                QVVector &x, const GSLMultiminFDFSolverType gslSolverAlgorithm = LMScaledDerivative,
                const int maxIterations = 100, const double maxAbsErr = 1e-4, const double maxRelErr = 1e-4
                );
#endif

/*!
@brief Wrapper to GSL function minimization.

This function uses the GSL to obtain the minimum of a function, provided in a QVFunction object. An example code usage follows:

@code
#include <qvnumericalanalysis.h>

// Creation of a sinoidal function class type
class SinoidalFunction: public QVFunction<double, double>
    {
    private:
        double evaluate(const double &x) const
            {
            return cos(x) + 1.0;
            }

    public:
        SinoidalFunction(): QVFunction<double, double>() { };
    };

int main(int argc, char *argv[])
    {
    const SinoidalFunction function;
    double x = 2.0, lower = 0.0, upper = 6.0;

    qvGSLMinimize(function, x, lower, upper);

    printf ("Minimum found at %.7f\n", x);

    exit(0);
    }
@endcode

@param function			Object containing the function to minimize.
@param x			Starting value for the minimization. This variable will contain the obtained minimum when the function returns.
@param gslMinimizerAlgorithm	Minimization algorithm. See enumeration @ref GSLMinFMinimizer for possible values.
@param lower			Minimal value for the search range.
@param upper			Maximum value for the search range.
@param maxIterations		Maximum number of steps to perform the minimization.
@param maxGradientNorm		Minimal value of the gradient size (norm 2) to stop the minimization when reached.
@param absoluteError		Corresponds to parameter <i>epsabs</i> for the <i>gsl_min_test_interval</i> function.
@param relativeError		Corresponds to parameter <i>epsrel</i> for the <i>gsl_min_test_interval</i> function.

@warning The GSL compatibility must be enabled to use this function.
@return	True if the search was successful. False else.
@see qvGSLMinimizeFDF
@see GSLMinFMinimizer

@ingroup qvnumericalanalysis
*/
#ifdef GSL_AVAILABLE
bool qvGSLMinimize(const QVFunction<double, double> &function,
                         double &x, double &lower, double &upper,
                         const GSLMinFMinimizer gslMinimizerAlgorithm = BrentMinimization,
                         const int maxIterations = 100,
                         const double absoluteError = 1e-3,
                         const double relativeError = 0.0);
#endif
#endif
