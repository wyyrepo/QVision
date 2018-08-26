/*
 *	Copyright (C) 2007, 2008, 2009, 2010, 2011, 2012. PARP Research Group.
 *	<http://perception.inf.um.es>
 *	University of Murcia, Spain.
 *
 *	This file is part of the QVision library.
 *
 *	QVision is free software: you can redistribute it and/or modify
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

#ifdef QVMATRIXALGEBRA_AVAILABLE

#define CHECK_MKL_DSS_ERROR \
    if (error != MKL_DSS_SUCCESS) { \
        std::cout << "Solver returned error code " << error << std::endl; \
        exit(1); \
    }

#ifndef QMATRIXALGEBRA_H
#define QMATRIXALGEBRA_H

#include <QV3DPointF>
#include <qvmath/qvmatrix.h>
#include <QVSparseBlockMatrix>

// Substituted default values.
//	#define DEFAULT_TQVSVD_METHOD			GSL_THIN_DECOMP_MOD
//	#define DEFAULT_TQVSV_METHOD			LAPACK_ONLY_DGESVD
//	#define DEFAULT_TQVCHOLESKY_METHOD		GSL_CHOLESKY
//	#define DEFAULT_TQVQR_METHOD			GSL_HOUSEHOLDER_THIN_QR
//	#define DEFAULT_TQVLU_METHOD			GSL_LU
//	#define DEFAULT_TQVEIGENDECOMPOSITION_METHOD	GSL_EIGENSYMM
//	#define DEFAULT_TQVEIGENVALUES_METHOD		GSL_EIGENSYMM_ONLY

// Set the default values for the matrix algebra functions to use GSL or LAPACK, whichever is available.
#ifdef LAPACK_AVAILABLE
	#define DEFAULT_TQVSVD_METHOD			LAPACK_FULL_DGESVD		
	#define DEFAULT_TQVSV_METHOD			LAPACK_ONLY_DGESVD
	#define DEFAULT_TQVCHOLESKY_METHOD		LAPACK_CHOLESKY_DPOTRF
	#define DEFAULT_TQVQR_METHOD			LAPACK_FULL_DGEQR2
	#define DEFAULT_TQVLU_METHOD			LAPACK_DGETRF
	#define DEFAULT_TQVEIGENDECOMPOSITION_METHOD    LAPACK_DSYEV
	#define DEFAULT_TQVEIGENVALUES_METHOD		LAPACK_DSYEV_ONLY
#elif GSL_AVAILABLE
	#define DEFAULT_TQVSVD_METHOD			GSL_THIN_DECOMP_MOD
	#define DEFAULT_TQVSV_METHOD			GSL_ONLY_DECOMP
	#define DEFAULT_TQVCHOLESKY_METHOD		GSL_CHOLESKY
	#define DEFAULT_TQVQR_METHOD			GSL_HOUSEHOLDER_THIN_QR
	#define DEFAULT_TQVLU_METHOD			GSL_LU
	#define DEFAULT_TQVEIGENDECOMPOSITION_METHOD	GSL_EIGENSYMM
	#define DEFAULT_TQVEIGENVALUES_METHOD		GSL_EIGENSYMM_ONLY
#endif

#ifdef MKL_AVAILABLE
	#define DEFAULT_TQVSPARSESOLVE_METHOD		QVMKL_DSS
#else
	#define DEFAULT_TQVSPARSESOLVE_METHOD		QV_DENSE
#endif

/// @brief Available methods for Singular Value Decomposition (SVD)
/// @ingroup qvmatrixalgebra
typedef enum {
    GSL_THIN_DECOMP_MOD,    /*!< GSL Golub-Reinsch modified algorithm (thin); faster for M >> N. */
    GSL_THIN_DECOMP,        /*!< GSL Golub-Reinsch default algorithm (thin) */
    GSL_THIN_DECOMP_JACOBI, /*!< GSL one sided Jacobi algorithm (thin); slower, but more accurate. */
    LAPACK_FULL_DGESVD,     /*!< Lapack DGESVD method (full); */
    LAPACK_FULL_DGESDD,     /*!< Lapack DGESDD divide and conquer method (full); */
    LAPACK_THIN_DGESVD,     /*!< Lapack DGESVD method (thin); */
    LAPACK_THIN_DGESDD      /*!< Lapack DGESDD divide and conquer method (thin); */
} TQVSVD_Method;

/// @brief Available methods for Singular Values only computation (SV)
/// @ingroup qvmatrixalgebra
typedef enum {
    GSL_ONLY_DECOMP_MOD,    /*!< Only returns singular values, but computes complete decomposition using GSL_THIN_DECOMP_MOD. */
    GSL_ONLY_DECOMP,        /*!< Only returns singular values, but computes complete decomposition using GSL_THIN_DECOMP. */
    GSL_ONLY_DECOMP_JACOBI, /*!< Only returns singular values, but computes complete decomposition using GSL_THIN_DECOMP_JACOBI. */
    LAPACK_ONLY_DGESVD,     /*!< Lapack DGESVD divide and conquer method (only compute singular values, more efficient than complete decomposition); */
    LAPACK_ONLY_DGESDD      /*!< Lapack DGESDD method (only compute singular values, more efficient than complete decomposition); */
} TQVSV_Method;

/// @brief Available methods for Cholesky Decomposition
/// @ingroup qvmatrixalgebra
typedef enum {
    GSL_CHOLESKY,           /*!< GSL Cholesky method; */
    LAPACK_CHOLESKY_DPOTRF  /*!< Lapack DPOTRF method ; */
} TQVCholesky_Method;

/// @brief Available methods for QR Decomposition
/// @ingroup qvmatrixalgebra
typedef enum {
    GSL_HOUSEHOLDER_THIN_QR,     /*!< GSL Householder QR method (thin); */
    GSL_HOUSEHOLDER_FULL_QR,     /*!< GSL Householder QR method (full); */
    LAPACK_THIN_DGEQR2,           /*!< Lapack DGEQR2 (unblocked QR) method (thin); */
    LAPACK_FULL_DGEQR2           /*!< Lapack DGEQR2 (unblocked QR) method (full); */
} TQVQR_Method;

/// @brief Available methods for LU Decomposition
/// @ingroup qvmatrixalgebra
typedef enum {
    GSL_LU,                 /*!< GSL (Gauss elimination with partial pivoting method); */
    LAPACK_DGETRF           /*!< Lapack DGETRF (Gauss elimination with partial pivoting); */
} TQVLU_Method;

/// @brief Available methods for EigenDecomposition
/// @ingroup qvmatrixalgebra
typedef enum {
    GSL_EIGENSYMM,         /*!< GSL eigendecomposition of a real symmetric matrix (eigenvalues and eigenvectors); */
    LAPACK_DSYEV           /*!< Lapack DSYEV eigendecomposition (eigenvalues and eigenvectors); */
} TQVEigenDecomposition_Method;

/// @brief Available methods for EigenValues only computation
/// @ingroup qvmatrixalgebra
typedef enum {
    GSL_EIGENSYMM_ONLY,    /*!< GSL eigendecomposition of a real symmetric matrix (eigenvalues only); */
    LAPACK_DSYEV_ONLY     /*!< Lapack DSYEV eigendecomposition (eigenvalues only); */
} TQVEigenValues_Method;

/// @brief Available methods for sparse linear system solving
/// @ingroup qvmatrixalgebra
typedef enum {
	/// Intel MKL direct sparse solver.
    QVMKL_DSS = 0,
	/// Intel MKL iterative sparse solver.
    QVMKL_ISS = 1,
	/// CHOLMOD direct sparse solver.
    QVCHOLMOD_DSS = 2,
	/// Iterative sparse conjugate gradient.
    QV_SCG = 3,
	/// Block Jacobian preconditioned conjugate gradient.
    QV_BJPCG = 4,
	/// Direct dense method.
    QV_DENSE = 5
} TQVSparseSolve_Method;


/*! @brief Obtains the <a href="http://en.wikipedia.org/wiki/Singular_value_decomposition">Singular Value Decomposition (SVD)</a> of a rectangular \f$ m \times n \f$ matrix M.

The SV decomposition obtains two matrices <i>U</i> and <i>V</i> and a vector <i>s</i> from an original matrix
<i>M</i> satisfying the following equation:

\f$ M = U diag(s) V^T \f$

If the decomposition method is 'full', both U and V are square matrices of sizes \f$ m \times m \f$ and \f$ n \times n \f$, respectively, while the \f$diag(s)\f$ matrix is of size \f$ m \times n \f$, with all values zero, except on values \f$s(i)\f$ on its main diagonal, which correspond to the singular values in decreasing order.

If the decomposition is 'thin', then U and V are only of sizes \f$ m \times \min(m,n) \f$ and \f$ \min(m,n) \times n \f$, while the \f$diag(s)\f$ matrix is square of size \f$ \min(m,n) \times \min(m,n) \f$, and containing the singular values in decreasing order in the elements of its diagonal.

In any case, both matrices <i>U</i> and <i>V</i> have always orthonormal columns (that is, \f$ U^T U = I \f$ and \f$ V^T V = I \f$ ), and if the decomposition method is 'full', are fully orthogonal square matrices.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input matrix to decompose
@param U param to store the matrix U from the SVD decomposition (overwritten on output)
@param s param to store the s vector of singular values from the SVD decomposition (overwritten on output)
@param V param to store the matrix V from the SVD decomposition (overwritten on output)
@param method method to use in the computation (see @ref TQVSVD_Method)

@see solveFromSingularValueDecomposition solveBySingularValueDecomposition

@ingroup qvmatrixalgebra
*/
void singularValueDecomposition(const QVMatrix &M, QVMatrix &U, QVVector &s, QVMatrix &V, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);

#ifndef DOXYGEN_IGNORE_THIS
// This function is deprecated, and should be substituted by the former one.
void SingularValueDecomposition(const QVMatrix &M, QVMatrix &U, QVMatrix &S, QVMatrix &V, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);
#endif

/*! @brief Solves the linear system \f$M X = B\f$ for the unknown matrix \f$X\f$, using the previously obtained singular value decomposition \f$M = U diag(s) V^T\f$.

The solution is obtained with the following expression:

\f$ X = V diag(s)^{-1} U^T B \f$.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param U input matrix U from the SVD decomposition of M
@param s input vector of singular values from the SVD decomposition of M
@param V input matrix V from the SVD decomposition of M
@param X unknown matrix (overwritten on output)
@param B input right hand side matrix

@see singularValueDecomposition solveBySingularValueDecomposition

@ingroup qvmatrixalgebra
*/
void solveFromSingularValueDecomposition(const QVMatrix &U, const QVVector &s, const QVMatrix &V, QVMatrix &X, const QVMatrix &B);

/*! @brief Solves the linear system \f$M x = b\f$ for the unknown vector \f$x\f$, using the previously obtained singular value decomposition \f$M = U diag(s) V^T\f$.

The solution is obtained with the following expression:

\f$ x =  V diag(s)^{-1} U^T b \f$.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param U input matrix U from the SVD decomposition of M
@param s input vector of singular values from the SVD decomposition of M
@param V input matrix V from the SVD decomposition of M
@param x unknown vector (overwritten on output)
@param b input right hand side vector

@see solveFromSingularValueDecomposition(const QVMatrix &, const QVVector &, const QVMatrix &, QVMatrix &, const QVMatrix &)

@ingroup qvmatrixalgebra
*/
void solveFromSingularValueDecomposition(const QVMatrix &U, const QVVector &s, const QVMatrix &V, QVVector &x, const QVVector &b);

/*! @brief Solves the linear system \f$M X = B\f$ for the unknown matrix \f$X\f$, using the singular value decomposition \f$M = U diag(s) V^T\f$.

The solution is obtained by computing the singular value decomposition of \f$M\f$:

\f$ M = U diag(s) V^T \f$

And then using the following expression

\f$ X = V diag(s)^{-1} U^T B \f$.

Being \f$m \times n\f$ the size of the coefficient matrix \f$M\f$:
 - For overdetermined systems (\f$m>n\f$), the obtained solution minimizes the sums of squares of the residuals of the \f$m\f$ equations.
 - For sub-determined systems (\f$m<n\f$), the obtained solution has minimum norm amongst all the valid solutions.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param X unknown matrix (overwritten on output)
@param B input right hand side matrix
@param method method to use in the SVD computation (see @ref TQVSVD_Method)

@see singularValueDecomposition solveFromSingularValueDecomposition

@ingroup qvmatrixalgebra
*/
void solveBySingularValueDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVSVD_Method method  = DEFAULT_TQVSVD_METHOD);

/*! @brief Solves the linear system \f$M x = b\f$ for the unknown vector \f$x\f$, using the singular value decomposition \f$M = U diag(s) V^T\f$.

The solution is obtained by computing the singular value decomposition of \f$M\f$:

\f$ M = U diag(s) V^T \f$

And then using the following expression

\f$ x = V diag(s)^{-1} U^T b \f$.

Being \f$m \times n\f$ the size of the coefficient matrix \f$M\f$:
 - For overdetermined systems (\f$m>n\f$), the obtained solution minimizes the sums of squares of the residuals of the \f$m\f$ equations.
 - For sub-determined systems (\f$m<n\f$), the obtained solution has minimum norm amongst all the valid solutions.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param x unknown vector (overwritten on output)
@param b input right hand side vector
@see void solveBySingularValueDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, TQVSVD_Method);

@ingroup qvmatrixalgebra
*/
void solveBySingularValueDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVSVD_Method method  = DEFAULT_TQVSVD_METHOD);

/*! @brief Solves the linear system \f$M X = B\f$ for the unknown matrix \f$X\f$, using the singular value decomposition \f$M = U diag(s) V^T\f$.

The solution is obtained by computing the singular value decomposition of \f$M\f$:

\f$ M = U diag(s) V^T \f$

And then using the following expression

\f$ X = V diag(s)^{-1} U^T B \f$.

The function also returns the matrices \f$ U\f$ and \f$ V\f$, and the vector \f$ s\f$ resulting from the singular value decomposition.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param X unknown matrix (overwritten on output)
@param B input right hand side matrix
@param U param to store the matrix U resulting from the singular value decomposition (overwritten on output)
@param s param to store the vector s resulting from the singular value decomposition (overwritten on output)
@param V param to store the matrix V resulting from the singular value decomposition (overwritten on output)

@see void solveBySingularValueDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, TQVSVD_Method)

@ingroup qvmatrixalgebra
*/
void solveBySingularValueDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B,
                                       QVMatrix &U, QVVector &s, QVMatrix &V, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);


/*! @brief Solves the linear system \f$M x = b\f$ for the unknown vector \f$x\f$, using the singular value decomposition \f$M = U diag(s) V^T\f$.

The solution is obtained by computing the singular value decomposition of \f$M\f$:

\f$ M = U diag(s) V^T \f$

And then using the following expression

\f$ x = V diag(s)^{-1} U^T b \f$.

The function also returns the matrices \f$ U\f$ and \f$ V\f$, and the vector \f$ s\f$ resulting from the singular value decomposition.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient vector
@param x unknown vector (overwritten on output)
@param b input right hand side vector
@param U param to store the matrix U resulting from the singular value decomposition (overwritten on output)
@param s param to store the vector s resulting from the singular value decomposition (overwritten on output)
@param V param to store the matrix V resulting from the singular value decomposition (overwritten on output)

@see void solveBySingularValueDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, TQVSVD_Method);

@ingroup qvmatrixalgebra
*/
void solveBySingularValueDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b,
                                       QVMatrix &U, QVVector &s, QVMatrix &V, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);

/*! @brief Checks for correctness of the SVD of a matrix.

This function computes the value \f$||U diag(s) V^T-M)||_{Frobenius} + ||V^T V - I||_{Frobenius} + ||U^T U - I||_{Frobenius}\f$, which should be close to zero if \f$ M = U diag(s) V^T \f$ is a correct SVD of matrix M.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input M matrix
@param U input U matrix from the SVD decomposition of M
@param s input vector of singular values from the SVD decomposition of M
@param V input V matrix from the SVD decomposition of M

@see singularValueDecomposition

@ingroup qvmatrixalgebra
*/
double singularValueDecompositionResidual(const QVMatrix &M, const QVMatrix &U, const QVVector &s, const QVMatrix &V);

/*! @brief Gets the singular values of a matrix.

This function computes only the singular values of a matrix (which, depending on the used method, will be much faster than performing a full decomposition).

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input M matrix
@param s vector of singular values from the SVD decomposition (overwritten on output)
@param method method to use in the SV computation (see @ref TQVSV_Method)

@see singularValueDecomposition

@ingroup qvmatrixalgebra
*/
void singularValues(const QVMatrix &M, QVVector &s, const TQVSV_Method method = DEFAULT_TQVSV_METHOD);

/*! @brief Checks for correctness of the singular values of a matrix.

This function computes the value \f$||M||^2_{Frobenius} - ||s||^2\f$, which should be close to zero if \f$s\f$ are the singular values of M.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input M matrix
@param s input vector of singular values from the SVD decomposition of M

@see SingularValues

@ingroup qvmatrixalgebra
*/
double singularValuesResidual(const QVMatrix &M, const QVVector &s);


/*!
@brief Obtains the <a href="http://en.wikipedia.org/wiki/Cholesky_decomposition">Cholesky decomposition</a> of a symmetric and positive definite matrix.

The Cholesky decomposition obtains a lower triangular matrix <i>L</i> with strictly positive diagonal entries from an original matrix <i>M</i>, satisfying the following equation:

\f$ M = L L^{T} \f$

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M param containing the matrix to decompose
@param L param to store the resulting matrix L from the Cholesky decomposition (overwritten on output)
@param method method to use in the computation (see @ref TQVCholesky_Method)

@note Matrix M must be symmetric. More precisely, the GSL_CHOLESKY method will only use the lower triangular part of M as input, while the LAPACK_CHOLESKY_DPOTRF method will only use the upper triangular part (the rest of the matrix will not be read in any of both cases, because M is supposed to be symmetric).

@note Matrix M must also be positive definite. Otherwise, problems will arise: the GSL_CHOLESKY will fail and abort the program, while the LAPACK_CHOLESKY_DPOTRF will have an undefined behavior.

@see solveFromCholeskyDecomposition solveByCholeskyDecomposition

@ingroup qvmatrixalgebra
*/
void CholeskyDecomposition(const QVMatrix &M, QVMatrix &L, const TQVCholesky_Method method = DEFAULT_TQVCHOLESKY_METHOD);

/*! @brief Solves the linear system \f$M X = B\f$ for the unknown matrix \f$X\f$, using the previously obtained Cholesky decomposition \f$ M = L L^{T} \f$

The matrix \f$ M \f$ must be a symmetric positive definite matrix. The two resultant triangular systems on \f$L\f$ and \f$L^T\f$ are solved by back-substitution to solve the linear system.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param L input matrix from the Cholesky decomposition of M
@param X unknown matrix (overwritten on output)
@param B input right hand side matrix

@see CholeskyDecomposition solveByCholeskyDecomposition

@ingroup qvmatrixalgebra
*/
void solveFromCholeskyDecomposition(const QVMatrix &L, QVMatrix &X, const QVMatrix &B);

/*! @brief Solves the linear system \f$M x = b\f$ for the unknown vector \f$x\f$, using the previously obtained Cholesky decomposition \f$ M = L L^{T} \f$

The matrix \f$ M \f$ must be a symmetric positive definite matrix. The two resultant triangular systems on \f$L\f$ and \f$L^T\f$ are solved by back-substitution to solve the linear system.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param L input matrix from the Cholesky decomposition of M
@param x unknown vector (overwritten on output)
@param b input right hand side vector
@see solveFromCholeskyDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &)

@ingroup qvmatrixalgebra
*/
void solveFromCholeskyDecomposition(const QVMatrix &L, QVVector &x, const QVVector &b);

/*! @brief Solves the linear system \f$M X = B\f$ for the unknown matrix \f$X\f$, using the Cholesky decomposition \f$ M = L L^{T} \f$

The matrix \f$ M \f$ must be a symmetric positive definite matrix.
The two resultant triangular systems on \f$L\f$ and \f$L^T\f$ are solved by back-substitution to obtain the unknown matrix X.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param X unknown matrix (overwritten on output)
@param B input right hand side matrix
@param method method to use in the SVD computation (see @ref TQVCholesky_Method)

@see CholeskyDecomposition solveFromCholeskyDecomposition

@ingroup qvmatrixalgebra
*/
void solveByCholeskyDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVCholesky_Method method = DEFAULT_TQVCHOLESKY_METHOD);

/*! @brief Solves the linear system \f$M x = b\f$ for the unknown vector \f$x\f$, using the Cholesky decomposition \f$ M = L L^{T} \f$

The matrix \f$ M \f$ must be a symmetric positive definite matrix.
The two resultant triangular systems on \f$L\f$ and \f$L^T\f$ are solved by back-substitution to obtain the unknown vector x.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param x unknown vector (overwritten on output)
@param b input right hand side vector
@see void solveByCholeskyDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, TQVCholesky_Method)

@ingroup qvmatrixalgebra
*/
void solveByCholeskyDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVCholesky_Method method = DEFAULT_TQVCHOLESKY_METHOD);

/*! @brief Solves the linear system \f$M X = B\f$ for the unknown matrix \f$X\f$, using the Cholesky decomposition \f$ M = L L^{T} \f$

The matrix \f$ M \f$ must be a symmetric positive definite matrix.
The two resultant triangular systems on \f$L\f$ and \f$L^T\f$ are solved by back-substitution to obtain the unknown matrix X.

The matrix \f$ L\f$ resulting from the Cholesky decomposition is also returned.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param X unknown matrix (overwritten on output)
@param B input right hand side matrix
@param L param to store the matrix L resulting from the Cholesky decomposition (overwritten on output)
@see void solveByCholeskyDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, TQVCholesky_Method)

@ingroup qvmatrixalgebra
*/
void solveByCholeskyDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, QVMatrix &L, const TQVCholesky_Method method = DEFAULT_TQVCHOLESKY_METHOD);

/*! @brief Solves the linear system \f$M x = b\f$ for the unknown vector \f$x\f$, using the Cholesky decomposition \f$ M = L L^{T} \f$

The matrix \f$ M \f$ must be a symmetric positive definite matrix.
The two resultant triangular systems on \f$L\f$ and \f$L^T\f$ are solved by back-substitution to obtain the unknown matrix X.

The matrix \f$ L\f$ resulting from the Cholesky decomposition is also returned.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param x unknown vector (overwritten on output)
@param b input right hand side vector
@param L param to store the matrix L resulting from the Cholesky decomposition (overwritten on output)
@see void solveByCholeskyDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, TQVCholesky_Method)

@ingroup qvmatrixalgebra
*/
void solveByCholeskyDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, QVMatrix &L, const TQVCholesky_Method method = DEFAULT_TQVCHOLESKY_METHOD);

/*! @brief Checks for correctness of the Cholesky decomposition of a matrix.

This function computes the value \f$||L L^T-M)||_{Frobenius}\f$, which should be close to zero if \f$ M = L L^T \f$ is a correct Cholesky decomposition of matrix M.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input matrix
@param L input matrix from the Cholesky decomposition of M

@see CholeskyDecomposition

@ingroup qvmatrixalgebra
*/
double CholeskyDecompositionResidual(const QVMatrix &M, const QVMatrix &L);


/*!
@brief Obtains the <a href="http://en.wikipedia.org/wiki/LU_decomposition">LU decomposition</a> of a rectangular \f$ m \times n \f$ matrix.

The LU decomposition obtains three matrices: <i>P</i> <i>L</i>, and <i>U</i> from an original matrix
<i>M</i>, satisfying the following equation:

\f$ M = P L U \f$

Being the original matrix M of size \f$ m \times n \f$, result matrices <i>L</i> and <i>U</i> are lower and upper triangular matrices of sizes \f$ m \times min(m,n) \f$ and \f$ min(m,n) \times n \f$ respectively, while <i>P</i> is a square \f$ m \times m \f$ permutation matrix (in which each row and column have one and only one value equal to one, the rest of values being zeros).

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M param containing the matrix to decompose
@param P param to store the matrix P resulting from the LU decomposition (overwritten on output)
@param L param to store the matrix L resulting from the LU decomposition (overwritten on output)
@param U param to store the matrix U resulting from the LU decomposition (overwritten on output)
@param method method to use in the computation (see @ref TQVLU_Method)

@note The GSL_LU method only accepts a square matrix (\f$ m = n\f$) as input, otherwise it will fail and abort the program showing an adequate message. The LAPACK_DGETRF is more general, and accepts general rectangular \f$ m \times n \f$ matrices.

@see solveFromLUDecomposition solveByLUDecomposition

@ingroup qvmatrixalgebra
*/
void LUDecomposition(const QVMatrix &M, QVMatrix &P, QVMatrix &L, QVMatrix &U, const TQVLU_Method method = DEFAULT_TQVLU_METHOD);

/*! @brief Solves the linear system \f$M X = B\f$ for the unknown matrix \f$X\f$, using the previously obtained LU decomposition of M:

\f$ M = P L U \f$

The solution for the linear system is obtained by solving the two resultant triangular systems on \f$L\f$ and \f$U\f$ by back-substitution, while permuting the elements according to \f$ P \f$.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param P input matrix from the LU decomposition of M
@param L input matrix from the LU decomposition of M
@param U input matrix from the LU decomposition of M
@param X unknown matrix (overwritten on output)
@param B input right hand side matrix

@see LUDecomposition solveByLUDecomposition

@ingroup qvmatrixalgebra
*/
void solveFromLUDecomposition(const QVMatrix &P, const QVMatrix &L, const QVMatrix &U, QVMatrix &X, const QVMatrix &B);

/*! @brief Solves the linear system \f$M x = b\f$ for the unknown vector \f$x\f$, using the previously obtained LU decomposition \f$ M = P L U \f$

The solution for the linear system is obtained by solving the two resultant triangular systems on \f$L\f$ and \f$U\f$ by back-substitution, while permuting the elements according to \f$ P \f$.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param P input matrix from the LU decomposition of M
@param L input matrix from the LU decomposition of M
@param U input matrix from the LU decomposition of M
@param x unknown vector (overwritten on output)
@param b input right hand side vector
@see void solveFromLUDecomposition(const QVMatrix &, const QVMatrix &, const QVMatrix &, QVMatrix &, const QVMatrix &)

@ingroup qvmatrixalgebra
*/
void solveFromLUDecomposition(const QVMatrix &P, const QVMatrix &L, const QVMatrix &U, QVVector &x, const QVVector &b);

/*! @brief Solves the linear system \f$M X = B\f$ for the unknown matrix \f$X\f$, using the LU decomposition \f$ M = P L U \f$

The solution for the linear system is obtained by solving the two resultant triangular systems on \f$L\f$ and \f$U\f$ by back-substitution, while permuting the elements according to \f$ P \f$.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param X unknown matrix (overwritten on output)
@param B input right hand side matrix
@param method method to use in the LU decomposition (see @ref TQVLU_Method)

@note The GSL_LU method only accepts a square system (\f$ m = n\f$) as input, otherwise it will fail and abort the program showing an adequate message. The LAPACK_DGETRF is more general, and accepts general rectangular \f$ m \times n \f$ system, if m<n (sub-determined). In this case, the solution vector obtained has n-m zeros in the last n-m positions. LU decomposition is not adequate in any case for solving overdetermined systems of equations (m>n). Use @ref solveBySingularValueDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, TQVSVD_Method) or @ref solveByQRDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, const TQVQR_Method) instead for solving this type of systems in the minimum squares sense.
@see LUDecomposition solveFromLUDecomposition

@ingroup qvmatrixalgebra
*/
void solveByLUDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVLU_Method method = DEFAULT_TQVLU_METHOD);

/*! @brief Solves the linear system \f$M x = b\f$ for the unknown vector \f$x\f$, using the LU decomposition \f$ M = P L U \f$

The solution for the linear system is obtained by solving the two resultant triangular systems on \f$L\f$ and \f$U\f$ by back-substitution, while permuting the elements according to \f$ P \f$.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param x unknown vector (overwritten on output)
@param b input right hand side vector
@param method method to use in the LU decomposition (see @ref TQVLU_Method)

@note The GSL_LU method only accepts a square system (\f$ m = n\f$) as input, otherwise it will fail and abort the program showing an adequate message. The LAPACK_DGETRF is more general, and accepts general rectangular \f$ m \times n \f$ system, if m<n (sub-determined). In this case, the solution vector obtained has n-m zeros in the last n-m positions. LU decomposition is not adequate in any case for solving overdetermined systems of equations (m>n). Use @ref solveBySingularValueDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, TQVSVD_Method) or @ref solveByQRDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, const TQVQR_Method) instead for solving this type of systems in the minimum squares sense.
@see void solveByLUDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, const TQVLU_Method)

@ingroup qvmatrixalgebra
*/
void solveByLUDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVLU_Method method = DEFAULT_TQVLU_METHOD);

/*! @brief Solves the linear system \f$M X = B\f$ for the unknown matrix \f$X\f$, using the LU decomposition \f$ M = P L U \f$

The solution for the linear system is obtained by solving the two resultant triangular systems on \f$L\f$ and \f$U\f$ by back-substitution, while permuting the elements according to \f$ P \f$.

The function also returns the matrices \f$ P\f$, \f$ L\f$, and \f$ U\f$ resulting from the LU decomposition.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param X unknown matrix (overwritten on output)
@param B input right hand side matrix
@param P param to store the matrix P resulting from the LU decomposition (overwritten on output)
@param L param to store the matrix L resulting from the LU decomposition (overwritten on output)
@param U param to store the matrix U resulting from the LU decomposition (overwritten on output)
@param method method to use in the LU decomposition (see @ref TQVLU_Method)

@note The GSL_LU method only accepts a square system (\f$ m = n\f$) as input, otherwise it will fail and abort the program showing an adequate message. The LAPACK_DGETRF is more general, and accepts general rectangular \f$ m \times n \f$ system, if m<n (sub-determined). In this case, the solution vector obtained has n-m zeros in the last n-m positions. LU decomposition is not adequate in any case for solving overdetermined systems of equations (m>n). Use @ref solveBySingularValueDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, TQVSVD_Method) or @ref solveByQRDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, const TQVQR_Method) instead for solving this type of systems in the minimum squares sense.
@see void solveByLUDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, const TQVLU_Method)

@ingroup qvmatrixalgebra
*/
void solveByLUDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, QVMatrix &P, QVMatrix &L, QVMatrix &U, const TQVLU_Method method = DEFAULT_TQVLU_METHOD);

/*! @brief Solves the linear system \f$M x = b\f$ for the unknown vector \f$x\f$, using the LU decomposition \f$ M = P L U \f$

The solution for the linear system is obtained by solving the two resultant triangular systems on \f$L\f$ and \f$U\f$ by back-substitution, while permuting the elements according to \f$ P \f$.

The function also returns the matrices \f$ P\f$, \f$ L\f$, and \f$ U\f$ resulting from the LU decomposition.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param x unknown vector (overwritten on output)
@param b input right hand side vector
@param P param to store the matrix P resulting from the LU decomposition (overwritten on output)
@param L param to store the matrix L resulting from the LU decomposition (overwritten on output)
@param U param to store the matrix U resulting from the LU decomposition (overwritten on output)

@note The GSL_LU method only accepts a square system (\f$ m = n\f$) as input, otherwise it will fail and abort the program showing an adequate message. The LAPACK_DGETRF is more general, and accepts general rectangular \f$ m \times n \f$ system, if m<n (sub-determined). In this case, the solution vector obtained has n-m zeros in the last n-m positions. LU decomposition is not adequate in any case for solving overdetermined systems of equations (m>n). Use @ref solveBySingularValueDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, TQVSVD_Method) or @ref solveByQRDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, const TQVQR_Method) instead for solving this type of systems in the minimum squares sense.
@see void solveByLUDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, const TQVLU_Method)

@ingroup qvmatrixalgebra
*/
void solveByLUDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b,QVMatrix &P, QVMatrix &L, QVMatrix &U, const TQVLU_Method method = DEFAULT_TQVLU_METHOD);

/*! @brief Checks for correctness of the LU decomposition of a matrix.

This function computes the value \f$||P L U - M)||_{Frobenius}\f$, which should be close to zero if \f$ M = P L U \f$ is a correct LU decomposition of matrix M.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input matrix
@param P input matrix from the LU decomposition of M
@param L input matrix from the LU decomposition of M
@param U input matrix from the LU decomposition of M

@see LUDecomposition

@ingroup qvmatrixalgebra
*/
double LUDecompositionResidual(const QVMatrix &M, const QVMatrix &P, const QVMatrix &L, const QVMatrix &U);


/*! @brief Obtains the <a href="http://en.wikipedia.org/wiki/QR_decomposition">QR decomposition</a> of a rectangular \f$ m \times n \f$ matrix.

The QR decomposition obtains two matrices <i>Q</i> and <i>R</i> from an original matrix <i>M</i> of size \f$ m \times n \f$ that satisfy the following equation:

\f$ M = Q R \f$

For a square matrix M (m=n), Q is orthogonal and R is upper triangular, both square of size \f$ m \times m\f$  = \f$ n \times n \f$.

For full decomposition methods, or if m<n, matrix <i>Q</i> is orthogonal of size \f$ m \times m \f$ and <i>R</i> is an upper triangular matrix of size \f$ m \times n \f$.

For thin decomposition methods, and if m>n, matrix <i>Q</i> has size \f$ m \times n \f$, with orthogonal columns, and <i>R</i> is an upper triangular matrix of size \f$ n \times n \f$.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M param containing the matrix to decompose
@param Q param to store the resulting matrix Q from the QR decomposition (overwritten on output)
@param R param to store the resulting matrix R from the QR decomposition (overwritten on output)
@param method method to use in the computation (see @ref TQVQR_Method)

@see QLDecomposition LQDecomposition RQDecomposition solveFromQRDecomposition solveByQRDecomposition

@ingroup qvmatrixalgebra
*/
void QRDecomposition(const QVMatrix &M, QVMatrix &Q, QVMatrix &R, const TQVQR_Method method = DEFAULT_TQVQR_METHOD);

/*! @brief Checks for correctness of the QR decomposition of a matrix.

This function computes the value \f$||Q R - M)||_{Frobenius} + ||Q^T Q - I)||_{Frobenius}\f$, which should be close to zero if \f$ M = Q R \f$ is a correct QR decomposition of matrix M.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input matrix
@param Q input matrix from the QR decomposition of M
@param R input matrix from the QR decomposition of M

@see QRDecomposition

@ingroup qvmatrixalgebra
*/
double QRDecompositionResidual(const QVMatrix &M, const QVMatrix &Q, const QVMatrix &R);

/*! @brief Obtains the <a href="http://en.wikipedia.org/wiki/QR_decomposition#QL.2C_RQ_and_LQ_decompositions">QL decomposition</a> of a rectangular \f$ m \times n \f$ matrix.

The QL decomposition obtains two matrices <i>Q</i> and <i>L</i> from an original matrix <i>M</i> of size \f$ m \times n \f$ that satisfy the following equation:

\f$ M = Q L \f$

For a square matrix M (m=n), Q is orthogonal and L is lower triangular,both square of size \f$ m \times m\f$  = \f$ n \times n \f$.

If m>n, then thin decomposition methods obtain a <i>Q</i> matrix of size \f$ m \times n \f$, with orthogonal columns, and a matrix <i>L</i> which is a lower triangular matrix of size \f$ n \times n \f$, while full decomposition methods obtain a matrix <i>Q</i> orthogonal of size \f$ m \times m \f$ and a matrix <i>L</i> of size \f$ m \times n \f$ whose first m-n rows are zero, and whose last n rows form a lower triangular matrix.

If m<n, then both full and thin decomposition methods obtain a matrix <i>Q</i> orthogonal of size \f$ m \times m \f$ and a matrix <i>L</i> of size \f$ m \times n \f$ whose first m-n  cols are in general not zero and whose last n columns form a lower triangular matrix.

This function uses the underlying function @ref QRDecomposition to perform the QL decomposition, so the available methods are the same than the ones used in the QR decomposition (see @ref TQVQR_Method).

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M param containing the matrix to decompose
@param Q param to store the matrix Q resulting from the QL decomposition (overwritten on output)
@param L param to store the matrix L resulting from the QL decomposition (overwritten on output)
@param method method to use in the computation (see @ref TQVQR_Method)

@see QRDecomposition LQDecomposition RQDecomposition

@ingroup qvmatrixalgebra
*/
void QLDecomposition(const QVMatrix &M, QVMatrix &Q, QVMatrix &L, const TQVQR_Method method = DEFAULT_TQVQR_METHOD);

/*! @brief Checks for correctness of the QL decomposition of a matrix.

This function computes the value \f$||Q L - M)||_{Frobenius} + ||Q^T Q - I)||_{Frobenius}\f$, which should be close to zero if \f$ M = Q L \f$ is a correct QL decomposition of matrix M.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input matrix
@param Q input matrix from the QL decomposition of M
@param L input matrix from the QL decomposition of M

@see QLDecomposition

@ingroup qvmatrixalgebra
*/
double QLDecompositionResidual(const QVMatrix &M, const QVMatrix &Q, const QVMatrix &L);

/*! @brief Obtains the <a href="http://en.wikipedia.org/wiki/QR_decomposition#QL.2C_RQ_and_LQ_decompositions">RQ decomposition</a> of a rectangular \f$ m \times n \f$ matrix.

The RQ decomposition obtains two matrices <i>R</i> and <i>Q</i> from an original matrix <i>M</i> of size \f$ m \times n \f$ that satisfy the following equation:

\f$ M = R Q \f$

For a square matrix M (m=n), R is upper triangular and Q orthogonal, both square of size \f$ m \times m\f$  = \f$ n \times n \f$.

If m>n, then both full and thin decomposition methods obtain a matrix <i>R</i> of size \f$ m \times n \f$ whose first m-n rows are in general not zero and whose last n rows form an upper triangular matrix, and a matrix <i>Q</i> which is orthogonal of size \f$ n \times n \f$.

If m<n, then thin decomposition methods obtain a matrix <i>R</i> which is an upper triangular matrix of size \f$ m \times m \f$ and a <i>Q</i> matrix of size \f$ m \times n \f$, with orthogonal rows, while full decomposition methods obtain a matrix <i>R</i> of size \f$ m \times n \f$ whose first n-m columns are zero, and whose last m columns form a lower triangular matrix, and a matrix <i>Q</i> orthogonal of size \f$ n \times n \f$.

This function uses the underlying function @ref QRDecomposition to perform the RQ decomposition, so the available methods are the same than the ones used in the QR decomposition (see @ref TQVQR_Method).

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M param containing the matrix to decompose
@param R param to store the matrix R resulting from the RQ decomposition (overwritten on output)
@param Q param to store the matrix Q resulting from the RQ decomposition (overwritten on output)
@param method method to use in the computation (see @ref TQVQR_Method)

@see QRDecomposition QLDecomposition LQDecomposition

@ingroup qvmatrixalgebra
*/
void RQDecomposition(const QVMatrix &M, QVMatrix &R, QVMatrix &Q, const TQVQR_Method method = DEFAULT_TQVQR_METHOD);

/*! @brief Checks for correctness of the RQ decomposition of a matrix.

This function computes the value \f$||R Q - M)||_{Frobenius} + ||Q Q^T - I)||_{Frobenius}\f$, which should be close to zero if \f$ M = R Q \f$ is a correct RQ decomposition of matrix M.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input matrix
@param R input matrix from the RQ decomposition of M
@param Q input matrix from the RQ decomposition of M

@see RQDecomposition

@ingroup qvmatrixalgebra
*/
double RQDecompositionResidual(const QVMatrix &M, const QVMatrix &R, const QVMatrix &Q);


/*! @brief Obtains the <a href="http://en.wikipedia.org/wiki/QR_decomposition#QL.2C_RQ_and_LQ_decompositions">LQ decomposition</a> of a rectangular \f$ m \times n \f$ matrix.

The LQ decomposition obtains two matrices <i>L</i> and <i>Q</i> from an original matrix <i>M</i> of size \f$ m \times n \f$ that satisfy the following equation:

\f$ M = L Q \f$

For a square matrix M (m=n), L is lower triangular and Q orthogonal, both square of size \f$ m \times m\f$  = \f$ n \times n \f$.

For full decomposition methods, or if m>n, <i>L</i> is a lower triangular matrix of size \f$ m \times n \f$ and matrix <i>Q</i> is orthogonal of size \f$ n \times n \f$ .

For thin decomposition methods, and if m<n, <i>L</i> is a lower triangular matrix of size \f$ m \times m \f$, and matrix <i>Q</i> has size \f$ m \times n \f$, with orthogonal rows.

This function uses the underlying function @ref QRDecomposition to perform the LQ decomposition, so the available methods are the same than the ones used in the QR decomposition (see @ref TQVQR_Method).

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M param containing the matrix to decompose
@param L param to store the matrix L resulting from the LQ decomposition (overwritten on output)
@param Q param to store the matrix Q resulting from the LQ decomposition (overwritten on output)
@param method method to use in the computation (see @ref TQVQR_Method)

@see QRDecomposition QLDecomposition RQDecomposition

@ingroup qvmatrixalgebra
*/
void LQDecomposition(const QVMatrix &M, QVMatrix &L, QVMatrix &Q, const TQVQR_Method method = DEFAULT_TQVQR_METHOD);

/*! @brief Checks for correctness of the LQ decomposition of a matrix.

This function computes the value \f$||L Q - M)||_{Frobenius} + ||Q Q^T - I)||_{Frobenius}\f$, which should be close to zero if \f$ M = L Q \f$ is a correct LQ decomposition of matrix M.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input matrix
@param L input matrix from the LQ decomposition of M
@param Q input matrix from the LQ decomposition of M

@see LQDecomposition

@ingroup qvmatrixalgebra
*/
double LQDecompositionResidual(const QVMatrix &M, const QVMatrix &L, const QVMatrix &Q);

/*! @brief Solves the linear system \f$M X = B\f$ for the unknown matrix \f$X\f$, using the previously obtained QR decomposition of M:

\f$ M X = Q R \f$

The solution is obtained by solving the triangular system \f$ R X = Q^T B \f$.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param Q input matrix Q from the QR decomposition of M
@param R input matrix R from the QR decomposition of M
@param X unknown matrix (overwritten on output)
@param B input right hand side matrix

@see QRDecomposition solveByQRDecomposition

@ingroup qvmatrixalgebra
*/
void solveFromQRDecomposition(const QVMatrix &Q, const QVMatrix &R, QVMatrix &X, const QVMatrix &B);

/*! @brief Solves the linear system \f$M x = b\f$ for the unknown vector \f$x\f$, using the previously obtained QR decomposition of M:

\f$ M = Q R \f$

The solution is obtained by solving the triangular system \f$ R X = Q^T B \f$.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param Q input matrix Q from the QR decomposition of M
@param R input matrix R from the QR decomposition of M
@param x unknown vector (overwritten on output)
@param b input right hand side vector
@see void solveFromQRDecomposition(const QVMatrix &, const QVMatrix &, QVMatrix &, const QVMatrix &)

@ingroup qvmatrixalgebra
*/
void solveFromQRDecomposition(const QVMatrix &Q, const QVMatrix &R, QVVector &x, const QVVector &b);

/*! @brief Solves the linear system \f$M X = B\f$ for the unknown matrix \f$X\f$, using the QR decomposition of M:

\f$ M = Q R \f$

The solution is obtained by solving the triangular system \f$ R X = Q^T B \f$.

@note For overdetermined systems (\f$m>n\f$, being \f$m \times n\f$ the size of the coefficient matrix \f$M\f$), the obtained solution minimizes the sums of squares of the residuals of the \f$m\f$ equations.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param X unknown matrix (overwritten on output)
@param B input right hand side matrix
@param method method to use in the QR computation (see @ref TQVQR_Method)

@see QRDecomposition solveFromQRDecomposition

@ingroup qvmatrixalgebra
*/
void solveByQRDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVQR_Method method = DEFAULT_TQVQR_METHOD);

/*! @brief Solves the linear system \f$M x = b\f$ for the unknown vector \f$x\f$, using the QR decomposition of M:

\f$ M = Q R \f$

The solution is obtained by solving the triangular system \f$ R X = Q^T B \f$.

@note For overdetermined systems (\f$m>n\f$, being \f$m \times n\f$ the size of the coefficient matrix \f$M\f$), the obtained solution minimizes the sums of squares of the residuals of the \f$m\f$ equations.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param x unknown vector (overwritten on output)
@param b input right hand side vector
@see void solveByQRDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, const TQVQR_Method)

@ingroup qvmatrixalgebra
*/
void solveByQRDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVQR_Method method = DEFAULT_TQVQR_METHOD);

/*! @brief Solves the linear system \f$M X = B\f$ for the unknown matrix \f$X\f$, using the QR decomposition of M:

\f$ M = Q R \f$

The solution is obtained by solving the triangular system \f$ R X = Q^T B \f$.
The function also returns the matrices \f$ Q\f$ and \f$ R\f$ resulting from the QR decomposition.

@note For overdetermined systems (\f$m>n\f$, being \f$m \times n\f$ the size of the coefficient matrix \f$M\f$), the obtained solution minimizes the sums of squares of the residuals of the \f$m\f$ equations.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param X unknown matrix (overwritten on output)
@param B input right hand side matrix
@param Q param to store the matrix Q resulting from the QR decomposition (overwritten on output)
@param R param to store the matrix R resulting from the QR decomposition (overwritten on output)

@see void solveByQRDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, const TQVQR_Method)

@ingroup qvmatrixalgebra
*/
void solveByQRDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B,
                            QVMatrix &Q, QVMatrix &R, const TQVQR_Method method = DEFAULT_TQVQR_METHOD);


/*! @brief Solves the linear system \f$M x = b\f$ for the unknown vector \f$x\f$, using the QR decomposition of M:

\f$ M = Q R \f$

The solution is obtained by solving the triangular system \f$ R X = Q^T B \f$.
The function also returns the matrices \f$ Q\f$ and \f$ R\f$ resulting from the QR decomposition.

@note For overdetermined systems (\f$m>n\f$, being \f$m \times n\f$ the size of the coefficient matrix \f$M\f$), the obtained solution minimizes the sums of squares of the residuals of the \f$m\f$ equations.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param x unknown vector (overwritten on output)
@param b input right hand side vector
@param Q param to store the matrix Q resulting from the QR decomposition (overwritten on output)
@param R param to store the matrix R resulting from the QR decomposition (overwritten on output)

@see void solveByQRDecomposition(const QVMatrix &, QVMatrix &, const QVMatrix &, const TQVQR_Method)

@ingroup qvmatrixalgebra
*/
void solveByQRDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b,
                            QVMatrix &Q, QVMatrix &R, const TQVQR_Method method = DEFAULT_TQVQR_METHOD);

/*! @brief Obtains the <a href="http://en.wikipedia.org/wiki/Eigendecomposition_of_a_matrix">eigen-decomposition</a> of a symmetric matrix.

The eigen-decomposition obtains the factorization of a symmetric matrix <i>M</i> into a canonical form, represented
in terms of a set of eigenvectors and their corresponding eigenvalues.

Each eigenvector \f$ \mathbf{v}_i \f$ and its corresponding eigenvalue \f$ \lambda_i \f$ satisfy the following equation.

\f$ M \mathbf{v}_i = \lambda_i \mathbf{v}_i \f$

This function returns the eigenvectors and their corresponding eigenvalues in a <i>Q</i> matrix and a <i>lambda</i> vector, respectively. Each eigenvector is stored as a row of the <i>Q</i> matrix. The <i>i</i>-th element of the vector <i>lambda</i> contains the eigenvalue corresponding to the eigenvector stored in the <i>i</i>-th row. Eigenvectors are mutually orthogonal, therefore, Q is an orthonormal matrix (i.e. \f$ Q Q^T = Q^T Q = I \f$)

Thus, the following equation holds, given that the matrix \f$ Q \f$ and the vector \f$ \vec{\lambda} \f$ contain respectively the eigen-vectors and the eigen-values of the symmetric matrix <i>M</i>:

\f$ M = Q  diag(\vec{\lambda}) Q^{T} \f$

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M symmetric matrix to obtain eigen-decomposition
@param lambda vector containing the eigenvalues from the eigen-decomposition (overwritten on output)
@param Q matrix containing the eigenvectors from the eigen-decomposition of M; eigenvectors are stored as row vectors (overwritten on output)
@param method method to use in the computation (see @ref TQVEigenDecomposition_Method)

@ingroup qvmatrixalgebra
*/
void eigenDecomposition(const QVMatrix &M, QVVector &lambda, QVMatrix &Q, const TQVEigenDecomposition_Method method = DEFAULT_TQVEIGENDECOMPOSITION_METHOD);

/*! @brief Checks for correctness of the eigendecomposition of a matrix.

This function computes the value \f$||Q diag(\lambda) Q^T-M)||_{Frobenius} + ||Q^T Q - I||_{Frobenius}\f$, which should be close to zero if \f$ M = Q diag(\lambda) Q^T \f$ is a correct eigendecomposition of symmetric matrix M.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input symmetric M matrix
@param lambda input vector of eigenvalues from the eigendecomposition of M
@param Q input Q matrix from the eigendecomposition of M

@see EigenDecomposition

@ingroup qvmatrixalgebra
*/
double eigenDecompositionResidual(const QVMatrix &M, const QVVector &lambda, const QVMatrix &Q);

/*! @brief Gets the eigenvalues of a matrix.

This function computes only the eigenvalues of a symmetric matrix (which, depending also on the used method, will be much faster than performing a full eigendecomposition).

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input symmetric M matrix
@param lambda vector of eigenvalues from the eigendecomposition (overwritten on output)
@param method method to use in the eigenvalues computation (see @ref TQVEigenValues_Method)

@see EigenDecomposition

@ingroup qvmatrixalgebra
*/
void eigenValues(const QVMatrix &M, QVVector &lambda, const TQVEigenValues_Method method = DEFAULT_TQVEIGENVALUES_METHOD);

/*! @brief Checks for correctness of the eigenvalues of a symmetric matrix.

This function returns the difference between the sum of diagonal elements of the matrix (i.e., its trace) and the sum of the elements of \f$\lambda\f$ (which are supposed to be its eigenvalues). This should be close to zero if the \f$\lambda\f$ are really the eigenvalues of M.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input M matrix
@param lambda input vector of eigenvalues from the eigendecomposition of M

@see EigenValues

@ingroup qvmatrixalgebra
*/
double eigenValuesResidual(const QVMatrix &M, const QVVector &lambda);


/*! @brief Obtains the <a href="http://en.wikipedia.org/wiki/Moore-Penrose_pseudoinverse">Moore–Penrose pseudoinverse</a> of a matrix.

The pseudoinverse is computed using the SVD of the input matrix, and then using the reciprocal of the obtained singular values.
The used formula is \f$ M^{+} = \sum_{i} (1/s_i) (v_i \otimes u_i) \f$, being \f$u_i\f$ and \f$v_i\f$ column vectors of the orthogonal U and V matrices obtained by SVD. Singular values which, when divided by the first singular value, are smaller than the epsilon parameter are discarded in the computation.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param A input matrix to obtain pseudoinverse
@param method method to use in the computation (see @ref TQVSVD_Method)
@param epsilon singular values with value smaller than epsilon will be discarded in computation
@ingroup qvmatrixalgebra
*/
QVMatrix pseudoInverse(const QVMatrix &M, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD, const double epsilon = 1.0E-10);

/*! @brief Obtains the <a href="http://en.wikipedia.org/wiki/Determinant">determinant</a> of a square matrix.

The determinant is obtained by first obtaining the LU decomposition of the matrix, then multiplying the values
in the diagonal of U, and finally multiplying the result by the signature of the permutation P in the decomposition
\f$ M = PLU \f$

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M matrix to obtain the determinant
@param method method to use in the LU decomposition (see @ref TQVLU_Method)

@returns the value of the determinant

@ingroup qvmatrixalgebra
*/
double determinant(const QVMatrix &M, const TQVLU_Method method = DEFAULT_TQVLU_METHOD);

/*! @brief Solves an <a href="http://en.wikipedia.org/wiki/System_of_linear_equations#Homogeneous_systems">homogeneous linear system of equations</a>.

Given a matrix <i>M</i>, this functions obtain the vector <i>x</i> satisfying the following equation:

\f$ M\mathbf{x} = \mathbf{0} \f$

The solution is based on the SVD decomposition of the matrix <i>A</i>. Vector <i>x</i> is set to the last column
of the matrix <i>V</i> from the SVD decomposition of <i>M</i>.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M coeficient matrix for the homogeneous equation system.
@param x vector to store the solution.
@param method method to use in the SVD decomposition (see @ref TQVSVD_Method)

@ingroup qvmatrixalgebra
*/
void solveHomogeneous(const QVMatrix &A, QVector<double> &x, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);

/*! @brief Returns the residual of the solution to a linear matrix equation.

This function computes the value \f$ ||M X - B||^2_{Frobenius} \f$, which should be close to zero if X is the solution to the matrix equation \f$ M X = B\f$, or should be minimized if the system was solved in the minimum squares sense.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param X input unknown matrix
@param B input right hand side matrix

@returns the computed residual

@see solveBySingularValueDecomposition solveByCholeskyDecomposition solveByLUDecomposition solveByQRDecomposition

@ingroup qvmatrixalgebra
*/
double solveResidual(const QVMatrix &M, const QVMatrix &X, const QVMatrix &B);

/*! @brief Returns the residual of the solution to a linear vector equation.

This function computes the value \f$||M x - B||^2 \f$, which should be close to zero if x is the solution to the equation \f$ M x = b\f$, or should be minimized if the system was solved in the minimum squares sense.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coefficient matrix
@param x input unknown vector
@param b input right hand side vector

@returns the computed residual

@see solveBySingularValueDecomposition solveByCholeskyDecomposition solveByLUDecomposition solveByQRDecomposition

@ingroup qvmatrixalgebra
*/
double solveResidual(const QVMatrix &M, const QVVector &x, const QVVector &b);

#ifndef DOXYGEN_IGNORE_THIS
extern int dummy; // For optional output parameter of next SparseSolve function:
#endif

/*! @brief Solves a <a href="http://en.wikipedia.org/wiki/Sparse_matrix">sparse system</a> of linear equations, taking advantage of sparseness to accelerate the computation.

Given a coefficient matrix <i>M</i> and an objective vector <i>b</i>, this functions obtains the vector <i>x</i> satisfying the following equation:

\f$ M\mathbf{x} = \mathbf{b} \f$

@warning Only upper-diagonal blocks should be defined in the input M matrix.

@warning Either GSL or MKL compatibility must be enabled to use this function.
@param M input coeficient sparse block matrix in the matrix equation form of the problem (must be square)
@param x vector to store the solution (overwritten on output)
@param b input right-hand side vector in the matrix equation form of the problem
@param isSymmetric indicates if M must be considered symmetric (in this case, only the upper triangular part is taken into account, which will speed up the computation).
@param isPosDefinite indicates if M is positive definite (in this case, the solver will take this into account to speed up the computation).
@param method method to use in the computation (see @ref TQVSparseSolve_Method)
@param start_from_x only for the QVMKL_ISS method, if true, start from the input value of x
@param iters_or_resid only for the QVMKL_ISS method, if true, use max iterations termination test (see param iters), otherwise use max residual (see param max_resid)
@param iters only for the incremental methods (QVMKL_ISS and QV_SCG). Number of iterations to execute (if zero, iterate until convergence or error)
@param max_resid only for the incremental methods (QVMKL_ISS and QV_SCG). Iterate until square of residual is below this parameter
@param iters only for the QVMKL_ISS method, final number of iterations really executed (overwritten on output)

@returns square norm of current residual, for  incremental methods (QVMKL_ISS and QV_SCG), always 0.0 for QVMKL_DSS

@see QVSparseBlockMatrix

@ingroup qvmatrixalgebra
*/
double sparseSolve(const QVSparseBlockMatrix &M, QVVector &x, const QVVector &b,
                 const bool isSymmetric = false, const bool isPosDefinite = false,
                 const TQVSparseSolve_Method method = DEFAULT_TQVSPARSESOLVE_METHOD, const bool start_from_x = false,
                 const bool iters_or_resid = true, const int iters = 0, const double resid = 1.0E-10,
                 int &final_iter_count = dummy);

/*! @brief Solves a sparse homogeneous linear system using the <a href="http://en.wikipedia.org/wiki/Inverse_iteration">inverse iteration</a> algorithm and the MKL sparse routines.

Given a matrix <i>M</i>, this function obtains the vector <i>x</i> satisfying the following equation:

\f$ M\mathbf{x} = \mathbf{0} \f$

An iterative process is used to converge from an initial random solution to the optimal solution of the equation.

@warning MKL compatibility must be enabled to use this function.
@param M input coeficient sparse block matrix in the matrix equation form of the problem (must be square)
@param x this vector will contain the solution to the homogeneous linear system in return. An initial approximation to the solution can be provided in this argument. 
@param maxIterations number of maximal iterations to perform in the algoritm.
@param minRelativeError the iteration process will stop if the value \f$ \|x_i - x_{i-1} \| \f$ (the difference between the solutions obtained in the last two iterations) is smaller than this value.
@param method method to use in the computation (see @ref TQVSparseSolve_Method). Only method @ref QVMKL_DSS is currently implemented for this function.

@see QVSparseBlockMatrix

@note This function works only with MKL.

@ingroup qvmatrixalgebra
*/
bool solveHomogeneous(const QVSparseBlockMatrix &A, QVVector &x, const int maxIterations = 10, const double minRelativeError = 0.0, const TQVSparseSolve_Method method=QVMKL_DSS);

#ifndef DOXYGEN_IGNORE_THIS
void cold_start_mkl_initialization(const int size = 2);

double solveConjugateGradient(const QVSparseBlockMatrix &A, QVVector &x, const QVVector &b, const int maxIters, const int minIters = 0, const double minAbsoluteError = 0.0);

double sparseSolve(const MKLPardisoSparseFormat &pardisomatrix, QVVector &x, const QVVector &b,
                 const bool isSymmetric = false, const bool isPosDefinite = false,
                 const TQVSparseSolve_Method method = DEFAULT_TQVSPARSESOLVE_METHOD, const bool start_from_x = false,
                 const bool iters_or_resid = true, const int iters = 0, const double resid = 1.0E-10,
                 int &final_iter_count = dummy);

// Internal use only. Fast function for homogeneous solving.
#ifdef GSL_AVAILABLE
void solveHomogeneousEig(const QVMatrix &M, QVVector &result);
#endif

/// @todo document this function
void solveLinear(const QVMatrix &A, QVVector &x, const QVVector &b);

/// @todo document this function
void solveLinear(const QVMatrix &A, QVMatrix &X, const QVMatrix &B);

/// @todo document this function
void solveOverDetermined(const QVMatrix &A, QVMatrix &X, const QVMatrix &B);

/// @todo document this function
void solveHomogeneousLinear(const QVMatrix &A, QVector<double> &x);

/// @todo document this function
double homogLineFromMoments(double x,double y,double xx,double xy,double yy,double &a,double &b,double &c);

/// @todo document and test this function
QVVector regressionLine(const QVMatrix &points);

// Deprecated.
void SingularValueDecomposition(const QVMatrix &M, QVMatrix &U, QVVector &s, QVMatrix &V, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);
void SolveFromSingularValueDecomposition(const QVMatrix &U, const QVVector &s, const QVMatrix &V, QVMatrix &X, const QVMatrix &B);
void SolveFromSingularValueDecomposition(const QVMatrix &U, const QVVector &s, const QVMatrix &V, QVVector &x, const QVVector &b);
void SolveBySingularValueDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVSVD_Method method  = DEFAULT_TQVSVD_METHOD);
void SolveBySingularValueDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVSVD_Method method  = DEFAULT_TQVSVD_METHOD);
void SolveBySingularValueDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, QVMatrix &U, QVVector &s, QVMatrix &V, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);
void SolveBySingularValueDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, QVMatrix &U, QVVector &s, QVMatrix &V, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);
double SingularValueDecompositionResidual(const QVMatrix &M, const QVMatrix &U, const QVVector &s, const QVMatrix &V);
void SingularValues(const QVMatrix &M, QVVector &s, const TQVSV_Method method = DEFAULT_TQVSV_METHOD);
double SingularValuesResidual(const QVMatrix &M, const QVVector &s);
void SolveFromCholeskyDecomposition(const QVMatrix &L, QVMatrix &X, const QVMatrix &B);
void SolveFromCholeskyDecomposition(const QVMatrix &L, QVVector &x, const QVVector &b);
void SolveByCholeskyDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVCholesky_Method method = DEFAULT_TQVCHOLESKY_METHOD);
void SolveByCholeskyDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVCholesky_Method method = DEFAULT_TQVCHOLESKY_METHOD);
void SolveByCholeskyDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, QVMatrix &L, const TQVCholesky_Method method = DEFAULT_TQVCHOLESKY_METHOD);
void SolveByCholeskyDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, QVMatrix &L, const TQVCholesky_Method method = DEFAULT_TQVCHOLESKY_METHOD);
void SolveFromLUDecomposition(const QVMatrix &P, const QVMatrix &L, const QVMatrix &U, QVMatrix &X, const QVMatrix &B);
void SolveFromLUDecomposition(const QVMatrix &P, const QVMatrix &L, const QVMatrix &U, QVVector &x, const QVVector &b);
void SolveByLUDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVLU_Method method = DEFAULT_TQVLU_METHOD);
void SolveByLUDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVLU_Method method = DEFAULT_TQVLU_METHOD);
void SolveByLUDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, QVMatrix &P, QVMatrix &L, QVMatrix &U, const TQVLU_Method method = DEFAULT_TQVLU_METHOD);
void SolveByLUDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b,QVMatrix &P, QVMatrix &L, QVMatrix &U, const TQVLU_Method method = DEFAULT_TQVLU_METHOD);
void SolveFromQRDecomposition(const QVMatrix &Q, const QVMatrix &R, QVMatrix &X, const QVMatrix &B);
void SolveFromQRDecomposition(const QVMatrix &Q, const QVMatrix &R, QVVector &x, const QVVector &b);
void SolveByQRDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVQR_Method method = DEFAULT_TQVQR_METHOD);
void SolveByQRDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVQR_Method method = DEFAULT_TQVQR_METHOD);
void SolveByQRDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, QVMatrix &Q, QVMatrix &R, const TQVQR_Method method = DEFAULT_TQVQR_METHOD);
void SolveByQRDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, QVMatrix &Q, QVMatrix &R, const TQVQR_Method method = DEFAULT_TQVQR_METHOD);
void EigenDecomposition(const QVMatrix &M, QVVector &lambda, QVMatrix &Q, const TQVEigenDecomposition_Method method = DEFAULT_TQVEIGENDECOMPOSITION_METHOD);
double EigenDecompositionResidual(const QVMatrix &M, const QVVector &lambda, const QVMatrix &Q);
void EigenValues(const QVMatrix &M, QVVector &lambda, const TQVEigenValues_Method method = DEFAULT_TQVEIGENVALUES_METHOD);
double EigenValuesResidual(const QVMatrix &M, const QVVector &lambda);
void SolveHomogeneous(const QVMatrix &A, QVector<double> &x, const TQVSVD_Method method = DEFAULT_TQVSVD_METHOD);
double SolveResidual(const QVMatrix &M, const QVMatrix &X, const QVMatrix &B);
double SolveResidual(const QVMatrix &M, const QVVector &x, const QVVector &b);
double SparseSolve(const QVSparseBlockMatrix M, QVVector &x, const QVVector b,
                 const bool isSymmetric = false, const bool isPosDefinite = false,
                 const TQVSparseSolve_Method method = DEFAULT_TQVSPARSESOLVE_METHOD, const bool start_from_x = false,
                 const bool iters_or_resid = true, const int iters = 0, const double resid = 1.0E-10,
                 int &final_iter_count = dummy);
void SolveHomogeneous(const QVSparseBlockMatrix &A, QVVector &x, const int maxIterations = 10, const double minRelativeError = 0.0, const TQVSparseSolve_Method method=QVMKL_DSS);
#endif

#endif // QMATRIXALGEBRA_H

#endif // QVMATRIXALGEBRA_AVAILABLE
