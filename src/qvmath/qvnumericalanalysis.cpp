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

#include <qvmath/qvnumericalanalysis.h>

const QVVector qvEstimateGradient(QVFunction<QVVector, double> &multivariateFunction, const QVVector &location, const double h)
    {
    const int dim = location.size();
    QVVector gradient(dim);
    const double actual = multivariateFunction(location);
    for (int i = 0; i < dim; i++)
        {
        QVVector stepLocation = location;
        stepLocation[i] += h;
        gradient[i] = (multivariateFunction(stepLocation) - actual)/h;
        }
    return gradient;
    }

const QVMatrix qvEstimateJacobian(QVFunction<QVVector, QVVector> &multivariateFunction, const QVVector &location, const double h)
    {
    const QVVector actual = multivariateFunction(location);

    QVMatrix jacobian(actual.size(), location.size());

    for (int i = 0; i < location.size(); i++)
        {
        QVVector stepLocation = location;
        stepLocation[i] += h;
        jacobian.setCol(i, (multivariateFunction(stepLocation) - actual)/h);
        }

    return jacobian;
    }

const QVMatrix qvEstimateHessian(	QVFunction<QVVector, double> &multivariateFunction,
                    const QVVector &location, const double h)
    {
    const int dim = location.size();
    const QVVector g = qvEstimateGradient(multivariateFunction, location, h);

    QVMatrix hessian(dim, dim);

    const double actual = multivariateFunction(location);
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
        {
        QVVector stepLocationIJ = location;
        stepLocationIJ[i] += h;
        stepLocationIJ[j] += h;
        hessian(i,j) = (multivariateFunction(stepLocationIJ) - actual)/(h*h) - (g[i] + g[j])/h;
        }
    return hessian;
    }

#ifdef GSL_AVAILABLE
//////////////////////////////////////////////////////////////////////////////////////////
// GSL minimization

double my_f (const gsl_vector *v, void *params)
    {
    return ((QVFunction<QVVector, double> *) params)->operator()(QVVector(v));
    }

/* The gradient of f, df = (df/dx, df/dy). */
void my_df (const gsl_vector *v, void *params, gsl_vector *df)
    {
    gsl_vector_memcpy(df, qvEstimateGradient( * (QVFunction<QVVector, double> *) params,QVVector(v)));
    }

/* Compute both f and df together. */
void my_fdf (const gsl_vector *x, void *params, double *f, gsl_vector *df)
    {
    *f = my_f(x, params);
    my_df(x, params, df);
    }

bool qvGSLMinimizeFDF (	const QVFunction<QVVector, double> & function, QVVector &point,
                const GSLMultiminFDFMinimizerType gslMinimizerAlgorithm,
                const int maxIterations, const double maxGradientNorm,
                const double step, const double tol)
    {
    const int dims = point.size();
    const gsl_multimin_fdfminimizer_type *minimizer_type = NULL;
    switch(gslMinimizerAlgorithm)
        {
        case ConjugateFR:	minimizer_type = gsl_multimin_fdfminimizer_conjugate_fr;	break;
        case ConjugatePR:	minimizer_type = gsl_multimin_fdfminimizer_conjugate_pr;	break;
        case VectorBFGS:	minimizer_type = gsl_multimin_fdfminimizer_vector_bfgs;		break;
        case SteepestDescent:	minimizer_type = gsl_multimin_fdfminimizer_steepest_descent;	break;
        }

    gsl_multimin_fdfminimizer *minimizer = gsl_multimin_fdfminimizer_alloc (minimizer_type, dims);

    gsl_multimin_function_fdf my_func;
    my_func.n = dims;
    my_func.f = &my_f;
    my_func.df = &my_df;
    my_func.fdf = &my_fdf;
    my_func.params = const_cast<QVFunction<QVVector, double> *>(&function);

    gsl_vector *x = point;

    gsl_multimin_fdfminimizer_set (minimizer, &my_func, x, step, tol);

    int status = GSL_CONTINUE;
    for (int i = 0; status == GSL_CONTINUE && i < maxIterations; i++)
        {
        if ((status = gsl_multimin_fdfminimizer_iterate (minimizer)))
            break;

        status = gsl_multimin_test_gradient (gsl_multimin_fdfminimizer_gradient(minimizer), maxGradientNorm);
        }

    // Store resulting value.
    point = QVVector(gsl_multimin_fdfminimizer_x(minimizer));

    gsl_multimin_fdfminimizer_free (minimizer);

    gsl_vector_free (x);

    return (status == GSL_SUCCESS);
    }

////////////////////////////////////

double my_f_gradient (const gsl_vector *v, void *params)
    {
    return ((QPair< QVFunction<QVVector, double> *, QVFunction<QVVector, QVVector> *> *) params)->first->operator()(QVVector(v));
    }

/* The gradient of f, df = (df/dx, df/dy). */
void my_df_gradient (const gsl_vector *v, void *params, gsl_vector *df)
    {
    gsl_vector_memcpy(df, ((QPair< QVFunction<QVVector, double> *, QVFunction<QVVector, QVVector> *> *) params)->second->operator()(QVVector(v)));
    }

/* Compute both f and df together. */
void my_fdf_gradient (const gsl_vector *x, void *params, double *f, gsl_vector *df)
    {
    *f = my_f_gradient(x, params);
    my_df_gradient(x, params, df);
    }

bool qvGSLMinimizeFDF (	const QVFunction<QVVector, double> & function, const QVFunction<QVVector, QVVector> & gradientFunction,
                QVVector &point, const GSLMultiminFDFMinimizerType gslMinimizerAlgorithm,
                const int maxIterations, const double maxGradientNorm,
                const double step, const double tol)
    {
    const int dims = point.size();
    const gsl_multimin_fdfminimizer_type *minimizer_type = NULL;
    switch(gslMinimizerAlgorithm)
        {
        case ConjugateFR:	minimizer_type = gsl_multimin_fdfminimizer_conjugate_fr;	break;
        case ConjugatePR:	minimizer_type = gsl_multimin_fdfminimizer_conjugate_pr;	break;
        case VectorBFGS:	minimizer_type = gsl_multimin_fdfminimizer_vector_bfgs;		break;
        case SteepestDescent:	minimizer_type = gsl_multimin_fdfminimizer_steepest_descent;	break;
        }

    gsl_multimin_fdfminimizer *minimizer = gsl_multimin_fdfminimizer_alloc (minimizer_type, dims);
    QPair< const QVFunction<QVVector, double> *, const QVFunction<QVVector, QVVector> *> functions(&function, &gradientFunction);

    gsl_multimin_function_fdf my_func;
    my_func.n = dims;
    my_func.f = &my_f_gradient;
    my_func.df = &my_df_gradient;
    my_func.fdf = &my_fdf_gradient;
    my_func.params = &functions;

    gsl_vector *x = point;

    gsl_multimin_fdfminimizer_set (minimizer, &my_func, x, step, tol);

    int status = GSL_CONTINUE;
    for (int i = 0; status == GSL_CONTINUE && i < maxIterations; i++)
        {
        if ((status = gsl_multimin_fdfminimizer_iterate (minimizer)))
            break;

        status = gsl_multimin_test_gradient (gsl_multimin_fdfminimizer_gradient(minimizer), maxGradientNorm);
        }

    // Store resulting value.
    point = QVVector(gsl_multimin_fdfminimizer_x(minimizer));

    gsl_multimin_fdfminimizer_free (minimizer);

    gsl_vector_free (x);

    return (status == GSL_SUCCESS);
    }

int multifit_f (const gsl_vector * x, void *params, gsl_vector * f)
    {
    const QVVector result = ((QPair< QVFunction<QVVector, QVVector> *, QVFunction<QVVector, QVMatrix> *> *)params)->first->operator()(QVVector(x));

    gsl_vector_memcpy(f, result);

    return GSL_SUCCESS;
    }

int multifit_df (const gsl_vector * x, void *params, gsl_matrix * J)
    {
    const QVMatrix result = ((QPair< QVFunction<QVVector, QVVector> *, QVFunction<QVVector, QVMatrix> *> *)params)->second->operator()(QVVector(x));

    gsl_matrix_memcpy(J, result);

    return GSL_SUCCESS;
    }

int multifit_fdf (const gsl_vector * x, void *params, gsl_vector * f, gsl_matrix * J)
    {
    multifit_f (x, params, f);
    multifit_df (x, params, J);

    return GSL_SUCCESS;
    }

bool qvGSLSolveFDF (	const QVFunction<QVVector, QVVector> & function, QVFunction<QVVector, QVMatrix> & functionJacobian,
                QVVector &x, const GSLMultiminFDFSolverType gslSolverAlgorithm,
                const int maxIterations, const double maxAbsErr, const double maxRelErr)
    {
    const gsl_multifit_fdfsolver_type *solver_type = NULL;
    switch(gslSolverAlgorithm)
        {
        case LMScaledDerivative:	solver_type = gsl_multifit_fdfsolver_lmsder;	break;
        case LMDerivative:		solver_type = gsl_multifit_fdfsolver_lmder;	break;
        }

    gsl_vector *x_gsl = x;

    QPair< const QVFunction<QVVector, QVVector> *, const QVFunction<QVVector, QVMatrix> *> functions(&function, &functionJacobian);

    // Just to get the input and output vectors sizes, for the function.
    const QVMatrix	jacobian = functionJacobian(x);
    const int	inputVectorSize = jacobian.getCols(),	// Size of input vector for function.
            outputVectorSize = jacobian.getRows();	// Size of output vector for function.

    // Generate minimization problem.
    gsl_multifit_function_fdf f;
    f.f = &multifit_f;
    f.df = &multifit_df;
    f.fdf = &multifit_fdf;
    f.n = outputVectorSize;
    f.p = inputVectorSize;
    f.params = &functions;

    gsl_multifit_fdfsolver *s = gsl_multifit_fdfsolver_alloc (solver_type, outputVectorSize, inputVectorSize);
    gsl_multifit_fdfsolver_set (s, &f, x_gsl);

    // Perform minimization.
    int iter = 0, status;
    do	{
        iter++;
        status = gsl_multifit_fdfsolver_iterate (s);

        if (status)
            break;

        status = gsl_multifit_test_delta (s->dx, s->x, maxAbsErr, maxRelErr);
        }
    while (status == GSL_CONTINUE && iter < maxIterations);

    // Print output data.
    x = s->x;

    gsl_multifit_fdfsolver_free (s);
    gsl_vector_free (x_gsl);

    return (status == GSL_SUCCESS);
    }

/////////////////////////////////////////////////////

double fn2 (double x, void * params)
    {
    return ((QVFunction<double, double> *) params)->operator()(x);
    }

bool qvGSLMinimize(const QVFunction<double, double> &function,
                         double &x, double &lower, double &upper,
                         const GSLMinFMinimizer gslMinimizerAlgorithm,
                         const int maxIterations,
                         const double absoluteError,
                         const double relativeError)
    {
    const gsl_min_fminimizer_type *minimizer_type =
            (gslMinimizerAlgorithm == GoldenSection)? gsl_min_fminimizer_goldensection : gsl_min_fminimizer_brent;

    gsl_function F;
    F.function = &fn2;
    F.params = (void *) &function;

    gsl_min_fminimizer *s = gsl_min_fminimizer_alloc (minimizer_type);
    gsl_min_fminimizer_set (s, &F, x, lower, upper);

    for (int i = 0; i <maxIterations; i++)
        {
        gsl_min_fminimizer_iterate(s);
        x = gsl_min_fminimizer_x_minimum (s);
        lower = gsl_min_fminimizer_x_lower (s);
        upper = gsl_min_fminimizer_x_upper (s);
        if (gsl_min_test_interval(lower, upper, absoluteError, relativeError) != GSL_CONTINUE)
            break;
        }

    gsl_min_fminimizer_free (s);

    return gsl_min_test_interval(lower, upper, absoluteError, relativeError) == GSL_SUCCESS;
    }
#endif
