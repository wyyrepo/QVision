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

#include <limits>
#include <iostream>

#include <qvmath.h>
#include <qvdefines.h>
#include <qvmath/qvmatrixalgebra.h>

/*#define dgesvd dgesvd
#define dgesdd dgesdd
#define dpotrf dpotrf
#define dgeqrf cblas_dgeqrf
#define dgetrf cblas_dgetrf
#define dorgqr cblas_dorgqr
#define dsyev  dsyev*/

#ifdef MKL_AVAILABLE
// #include <mkl_lapack.h>
// #include <mkl_blas.h>
// #include <mkl_dss.h>
// #include <mkl_rci.h>
// #include <mkl_spblas.h>

#define CHECK_MKL_DSS_ERROR \
    if (error != MKL_DSS_SUCCESS) { \
        std::cout << "Solver returned error code " << error << std::endl; \
        exit(1); \
    }

#elif LAPACK_AVAILABLE	// Only with non-MKL LAPACK
 #define dgesvd dgesvd_
 #define dgesdd dgesdd_
 #define dpotrf dpotrf_
 #define dgeqrf dgeqrf_
 #define dgetrf dgetrf_
 #define dorgqr dorgqr_
 #define dsyev  dsyev_
extern "C" {
   void dgesvd(char *jobu,char *jobvt, int *m, int *n, double *a, int *lda, double *s, double *u, int *ldu,
               double *vt, int *ldvt, double *work, int *lwork, int *info );
   void dgesdd(char *jobz, int *m, int *n, double *a, int *lda, double *s, double *u, int *ldu, double *vt,
               int *ldvt, double *work, int *lwork, int *iwork, int *info );
   void dpotrf(char *uplo, int *n, double *a, int *lda, int *info );
   void dgeqrf(int *m, int *n, double *a, int *lda, double *tau, double *work, int *lwork, int *info );
   void dgetrf(int *m, int *n, double *a, int *lda, int *ipiv, int *info );
   void dorgqr(int *m, int *n, int *k, double *a, int *lda, double *tau, double *work, int *lwork, int *info );
   void dsyev(char *jobz, char *uplo, int *n, double *a, int *lda, double *w, double *work, int *lwork, int *info );
}
#endif

#ifdef QVCHOLMOD
#include <QVCholmodSolver>
#endif

#include <QVPermutation>

void singularValueDecomposition_internal(const QVMatrix &M, QVMatrix &U, QVVector &s, QVMatrix &V,
                                         const TQVSVD_Method method, bool only_singular_values = false)
{
    int m = M.getRows(), n = M.getCols();
    if(method == GSL_THIN_DECOMP_MOD or method == GSL_THIN_DECOMP or method == GSL_THIN_DECOMP_JACOBI) {
#ifdef GSL_AVAILABLE
        bool transposed = FALSE;
        gsl_matrix *u, *v;
        gsl_vector *ss;

        if(M.getCols() > M.getRows())
            transposed = TRUE;
        const int dim2 = (transposed ? M.getRows():M.getCols());

        // First, we must decompose M, using GSL structures.
        u = (transposed ? M.transpose() : M);
        ss = gsl_vector_alloc (dim2);
        v = gsl_matrix_alloc (dim2, dim2);

        if(method == GSL_THIN_DECOMP_MOD) {
            gsl_vector *work = gsl_vector_alloc (dim2);
            gsl_matrix *XX = gsl_matrix_alloc (dim2,dim2);

            gsl_linalg_SV_decomp_mod(u, XX, v, ss, work);

            gsl_vector_free(work);
            gsl_matrix_free(XX);
        } else if(method == GSL_THIN_DECOMP) {
            gsl_vector *work = gsl_vector_alloc (dim2);

            gsl_linalg_SV_decomp(u, v, ss, work);

            gsl_vector_free(work);
        } else { // method == GSL_THIN_DECOMP_JACOBI)
            gsl_linalg_SV_decomp_jacobi(u, v, ss);
        }

        // We must assign GSL structures to output s vector and U, V matrices:
        if (not only_singular_values) U = u;
        s = ss;
        if (not only_singular_values) V = v;

        if(not only_singular_values and transposed) {
            QVMatrix inter = U;
            U = V;
            V = inter;
        }

        // Finally, we free u, s and v GSL structures:
        gsl_matrix_free(u);
        gsl_vector_free(ss);
        gsl_matrix_free(v);
#else
        qFatal("SVD decomposition: cannot use GSL methods if GSL library is not available.");
#endif
    } else if (method == LAPACK_FULL_DGESVD or method == LAPACK_FULL_DGESDD or
               method == LAPACK_THIN_DGESVD or method == LAPACK_THIN_DGESDD) {
#ifdef LAPACK_AVAILABLE
        // First, we must decompose M, using LAPACK structures.
        const char *jobu = "A",*jobvt = "A";
        // Copy M matrix, because LAPACK routines destroy original matrix, and
        // transpose it, because of FORTRAN way of store matrices in memory.
        QVMatrix MM = M.transpose();
        int ldu, ldvt, lwork, res;
        QVector<int> iwork(8*qMin(m,n));
        double *mptr = MM.getWriteData();
        int *iworkptr = iwork.data();

        if (only_singular_values) {
             jobu = "N";
             jobvt = "N";
             U = QVMatrix(1,1);
             V = QVMatrix(1,1);
             ldu = 1;
             ldvt = 1;
        } else if(method == LAPACK_FULL_DGESVD or method == LAPACK_FULL_DGESDD) {
            jobu = "A";
            jobvt = "A";
            U = QVMatrix(m,m);
            V = QVMatrix(n,n);
            ldu = m;
            ldvt = n;
        } else if (method == LAPACK_THIN_DGESVD or method == LAPACK_THIN_DGESDD) {
            jobu = "S";
            jobvt = "S";
            // Because of FORTRAN transposition:
            U = QVMatrix(qMin(m,n),m);
            V = QVMatrix(n,qMin(m,n));
            ldu = m ;
            ldvt = qMin(m,n);
        }

        s = QVVector(qMin(m,n));
        double *sptr=s.data(), *uptr=U.getWriteData(), *vptr=V.getWriteData(), *workptr, ans;

        // Ask for optimal lwork:
        lwork = -1;
        if (method == LAPACK_FULL_DGESVD or method == LAPACK_THIN_DGESVD)
            dgesvd(const_cast<char*>(jobu),const_cast<char*>(jobvt),
                   &m,&n,mptr,&m,sptr,uptr,&ldu,vptr,&ldvt,&ans,&lwork,&res);
        else if (method == LAPACK_FULL_DGESDD or method == LAPACK_THIN_DGESDD)
            dgesdd(const_cast<char*>(jobu),
                   &m,&n,mptr,&m,sptr,uptr,&ldu,vptr,&ldvt,&ans,&lwork,iworkptr,&res);
        lwork = static_cast<int>(ceil(ans));
        QVVector work(lwork);
        workptr = work.data();

        // Compute SVD:
        if (method == LAPACK_FULL_DGESVD or method == LAPACK_THIN_DGESVD)
            dgesvd(const_cast<char*>(jobu),const_cast<char*>(jobvt),
                   &m,&n,mptr,&m,sptr,uptr,&ldu,vptr,&ldvt,workptr,&lwork,&res);
        else if (method == LAPACK_FULL_DGESDD or method == LAPACK_THIN_DGESDD)
            dgesdd(const_cast<char*>(jobu),
                   &m,&n,mptr,&m,sptr,uptr,&ldu,vptr,&ldvt,workptr,&lwork,iworkptr,&res);

        // Finally, we transpose U (but not V):
        if(not only_singular_values)
            U = U.transpose();
#else
        qFatal("SVD decomposition: cannot use LAPACK methods if MKL, ATLAS or LAPACK BASE are not available.");
#endif
    }
}

void singularValueDecomposition(const QVMatrix &M, QVMatrix &U, QVVector &s, QVMatrix &V, const TQVSVD_Method method)
{
    singularValueDecomposition_internal(M, U, s, V, method);
}

void SingularValueDecomposition(const QVMatrix &M, QVMatrix &U, QVMatrix &S, QVMatrix &V, const TQVSVD_Method method)
{
    QVVector s;

    std::cout << "WARNING: 'SingularValueDecomposition' DEPRECATED, use 'singularValueDecomposition' instead\n";

    singularValueDecomposition_internal(M, U, s, V, method);
    S = QVMatrix::diagonal(s);
    const int m = U.getCols(), n = V.getCols();
    if (m>n)
        S = S & QVMatrix(m-n,n,0.0);
    else if (m<n)
        S = S | QVMatrix(m,n-m,0.0);
}

void solveFromSingularValueDecomposition(const QVMatrix &U, const QVVector &s, const QVMatrix &V, QVMatrix &X, const QVMatrix &B)
{
    X = U.dotProduct(B,true,false);
    for(int i=0;i<s.size();i++)
        for(int j=0;j<X.getCols();j++)
            X(i,j) /= s[i];

    const int m = U.getRows(), n = V.getRows();
    if (U.getRows() == U.getCols() and U.getRows() == U.getCols()) // Full decomposition.
        if (m>n)
            X = V.dotProduct(X.getRows(0,n-1),false,false);
        else
            X = V.getCols(0,m-1).dotProduct(X,false,false);
    else // Thin decomposition.
        X = V.dotProduct(X,false,false);
}

void solveFromSingularValueDecomposition(const QVMatrix &U, const QVVector &s, const QVMatrix &V, QVVector &x, const QVVector &b)
{
    QVMatrix X /*= x.toColumnMatrix()*/, B = b.toColumnMatrix();

    solveFromSingularValueDecomposition(U, s, V, X, B);

    x = X;
}

void solveBySingularValueDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVSVD_Method method)
{
    QVMatrix U_dummy, V_dummy, X, B = b.toColumnMatrix();
    QVVector s_dummy;

    singularValueDecomposition_internal(M, U_dummy, s_dummy, V_dummy, method);
    solveFromSingularValueDecomposition(U_dummy, s_dummy, V_dummy, X, B);
    x = X;
}

void solveBySingularValueDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVSVD_Method method)
{
    QVMatrix U_dummy, V_dummy;
    QVVector s_dummy;

    singularValueDecomposition_internal(M, U_dummy, s_dummy, V_dummy, method);
    solveFromSingularValueDecomposition(U_dummy, s_dummy, V_dummy, X, B);
}

void solveBySingularValueDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b,
                                       QVMatrix &U, QVVector &s, QVMatrix &V, const TQVSVD_Method method)
{
    QVMatrix X, B = b.toColumnMatrix();

    singularValueDecomposition_internal(M, U, s, V, method);
    solveFromSingularValueDecomposition(U, s, V, X, B);

    x = X;
}

void solveBySingularValueDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B,
                                       QVMatrix &U, QVVector &s, QVMatrix &V, const TQVSVD_Method method)
{
    singularValueDecomposition_internal(M, U, s, V, method);
    solveFromSingularValueDecomposition(U, s, V, X, B);
}

double singularValueDecompositionResidual(const QVMatrix &M, const QVMatrix &U, const QVVector &s, const QVMatrix &V)
{
    // Create diagonal matrix from singular values (adding rows or columns of additional zeros if needed):
    QVMatrix S = QVMatrix::diagonal(s);
    int m = U.getCols(), n = V.getCols();
    if (m>n)
        S = S & QVMatrix(m-n,n,0.0);
    else if (m<n)
        S = S | QVMatrix(m,n-m,0.0);

    double res1 = (U*S*V.transpose()-M).norm2();
    double res2 = (U.transpose()*U - QVMatrix::identity(U.getCols())).norm2();
    double res3 = (V.transpose()*V - QVMatrix::identity(V.getCols())).norm2();

    return res1 + res2 + res3;
}

void singularValues(const QVMatrix &M, QVVector &s, const TQVSV_Method method)
{
    QVMatrix U_dummy, V_dummy;

    if(method == GSL_ONLY_DECOMP_MOD)
        singularValueDecomposition_internal(M, U_dummy, s, V_dummy,
                                            GSL_THIN_DECOMP_MOD, true);
    else if(method == GSL_ONLY_DECOMP)
        singularValueDecomposition_internal(M, U_dummy, s, V_dummy, GSL_THIN_DECOMP, true);
    else if(method == GSL_ONLY_DECOMP_JACOBI)
        singularValueDecomposition_internal(M, U_dummy, s, V_dummy, GSL_THIN_DECOMP_JACOBI, true);
    else if(method == LAPACK_ONLY_DGESVD)
        singularValueDecomposition_internal(M, U_dummy, s, V_dummy, LAPACK_THIN_DGESVD, true);
    else if(method == LAPACK_ONLY_DGESDD)
        singularValueDecomposition_internal(M, U_dummy, s, V_dummy, LAPACK_THIN_DGESDD, true);
}

double singularValuesResidual(const QVMatrix &M, const QVVector &s)
{
    double acum1 = 0.0, acum2 = 0.0;

    // Squared Frobenius norm of matrix should be equal to sum of squared singular values:

    for(int i=0;i<M.getRows();i++)
        for(int j=0;j<M.getCols();j++)
        acum1 += M(i,j)*M(i,j);

    for(int i=0;i<s.size();i++)
        acum2 += s[i]*s[i];

    return qAbs(acum1-acum2);
}


void CholeskyDecomposition_internal(const QVMatrix &M, QVMatrix &L, const TQVCholesky_Method method)
{
    Q_ASSERT(M.getCols() == M.getRows());

    if(method == GSL_CHOLESKY) {
    #ifdef GSL_AVAILABLE
        const int n = M.getRows();

        gsl_matrix *a = M;

        gsl_linalg_cholesky_decomp(a);

        L = QVMatrix(n,n);
        double	*dataL = L.getWriteData();

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (j <= i)
                    dataL[i*n+j] = a->data[i*n+j];
                else
                    dataL[i*n+j] = 0;

        gsl_matrix_free(a);
    #else
            qFatal("Cholesky decomposition: cannot use GSL methods if GSL library is not available.");
    #endif
    } else if(method == LAPACK_CHOLESKY_DPOTRF) {
    #ifdef LAPACK_AVAILABLE
        const char *uplo = "L";
        int n = M.getRows(), lda = n, res;
        L = M;
        double *lptr = L.getWriteData();
        dpotrf(const_cast<char*>(uplo),&n,lptr,&lda,&res);
        for(int i=1;i<n;i++)
            for(int j=0;j<i;j++)
                L(i,j) = 0.0;
        L = L.transpose();
    #else
            qFatal("Cholesky decomposition: cannot use LAPACK methods if MKL, ATLAS of LAPACK BASE not available.");
    #endif
    }
    L.setType(QVMatrix::LowerTriangular);
}

void CholeskyDecomposition(const QVMatrix &M, QVMatrix &L, const TQVCholesky_Method method)
{
    CholeskyDecomposition_internal(M, L, method);
}

void solveFromCholeskyDecomposition(const QVMatrix &L, QVMatrix &X, const QVMatrix &B)
{
    QVMatrix X_inter;
    L.triangularSolve(B,X_inter,false);
    L.triangularSolve(X_inter,X,true);
}

void solveFromCholeskyDecomposition(const QVMatrix &L, QVVector &x, const QVVector &b)
{
    QVMatrix X /*= x.toColumnMatrix()*/, B = b.toColumnMatrix();

    solveFromCholeskyDecomposition(L, X, B);

    x = X;
}

void solveByCholeskyDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVCholesky_Method method)
{
    QVMatrix L_dummy;

    CholeskyDecomposition_internal(M, L_dummy, method);
    solveFromCholeskyDecomposition(L_dummy, X, B);

}

void solveByCholeskyDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVCholesky_Method method)
{
    QVMatrix L_dummy, X, B = b.toColumnMatrix();

    CholeskyDecomposition_internal(M, L_dummy, method);
    solveFromCholeskyDecomposition(L_dummy, X, B);

    x = X;
}

void solveByCholeskyDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B,
                                QVMatrix &L, const TQVCholesky_Method method)
{
    CholeskyDecomposition_internal(M, L, method);
    solveFromCholeskyDecomposition(L, X, B);

}

void solveByCholeskyDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b,
                                QVMatrix &L, const TQVCholesky_Method method)
{
    QVMatrix X, B = b.toColumnMatrix();

    CholeskyDecomposition_internal(M, L, method);
    solveFromCholeskyDecomposition(L, X, B);

    x = X;
}

double CholeskyDecompositionResidual(const QVMatrix &M, const QVMatrix &L)
{
    Q_ASSERT(M.getCols() == M.getRows());
    Q_ASSERT(L.getCols() == L.getRows());
    Q_ASSERT(M.getRows() == L.getRows());

    return (L * L.transpose() - M).norm2();
}


void LUDecomposition_internal(const QVMatrix &M, QVMatrix &P, QVMatrix &L, QVMatrix &U, const TQVLU_Method method)
{
    int m = M.getRows(), n = M.getCols();

    if(method == GSL_LU) {
#ifdef GSL_AVAILABLE
        if(m != n)
            qFatal("LU decomposition: GSL_LU method works only on square matrices.");

        gsl_matrix *a = M;
        gsl_permutation *p = gsl_permutation_alloc(m);

        int signum;

        gsl_linalg_LU_decomp(a, p, &signum);

        P = QVMatrix(m, m, 0.0);
        L = QVMatrix(m, m);
        U = QVMatrix(m, m);

        double  *dataL = L.getWriteData(),
                *dataU = U.getWriteData(),
                *dataP = P.getWriteData();

        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                if (j > i) {
                    dataU[i*m + j] = a->data[i*m+j];
                    dataL[i*m + j] = 0;
                } else if (j < i) {
                    dataU[i*m + j] = 0;
                    dataL[i*m + j] = a->data[i*m+j];
                } else { // Diagonal:
                    dataU[i*m + j] = a->data[i*m+j];
                    dataL[i*m + j] = 1;
                }

        for (int j = 0; j < m; j++)
                dataP[(p->data[j])*m + j] = 1;

        gsl_matrix_free(a);
        gsl_permutation_free(p);
#else
    qFatal("LU decomposition: cannot use GSL methods if GSL library is not available.");
#endif
    } else if(method == LAPACK_DGETRF) {
#ifdef LAPACK_AVAILABLE
        int lda = m, res;
        QVMatrix MT = M.transpose(); // Because of FORTRAN transposition.
        double *mtptr = MT.getWriteData();
        QVector<int> ipiv(m);
        int *ipivptr = ipiv.data();

        dgetrf(&m,&n,mtptr,&lda,ipivptr,&res);

        P = QVMatrix(m, m, 0.0);
        L = QVMatrix(m, m>n?n:m, 0.0);
        U = QVMatrix(m>n?n:m, n, 0.0);
        const int lm = L.getRows(), ln = L.getCols(), um = U.getRows(), un=U.getCols();

        double  *dataL = L.getWriteData(),
                *dataU = U.getWriteData();

        // Extraction of L matrix from (overwritten) result:
        for(int i = 0; i < lm; i++)
            for (int j = 0; j < ln; j++)
                if (j < i)
                    dataL[i*ln + j] = mtptr[j*m+i];
                else if (j==i) // Diagonal:
                    dataL[i*ln + j] = 1;

        // Extraction of U matrix:
        for(int i = 0; i < um; i++)
            for (int j = 0; j < un; j++)
                if (j > i)
                    dataU[i*un + j] = mtptr[j*m+i];
                else if (j==i) // Diagonal:
                    dataU[i*un + j] = mtptr[j*m+i];

        // Permutation, as returned by LAPACK:
        QVector<int> perm(m);
        for (int i = 0; i < m; i++)
            perm[i] = i;
        for (int i = 0; i < m; i++)
            if(ipivptr[i] != 0) {
                int inter = perm[i];
                perm[i] = perm[ipivptr[i]-1]; // FORTRAN indexes arrays from 1..n, not 0..n-1
                perm[ipivptr[i]-1] = inter;
            }
        for (int i = 0; i < m; i++)
            P(perm[i],i) = 1;
#else
        qFatal("LU decomposition: cannot use LAPACK methods if MKL, ATLAS of LAPACK BASE not available.");
#endif
        }

        L.setType(QVMatrix::LowerTriangular);
        U.setType(QVMatrix::UpperTriangular);
        P.setType(QVMatrix::PermutationMatrix);
}

void LUDecomposition(const QVMatrix &M, QVMatrix &P, QVMatrix &L, QVMatrix &U, const TQVLU_Method method)
{
    LUDecomposition_internal(M, P, L, U, method);
}

void solveFromLUDecomposition(const QVMatrix &P, const QVMatrix &L, const QVMatrix &U, QVMatrix &X, const QVMatrix &B)
{
    const int m = L.getRows(), n = U.getCols();
    if(m>n)
        qFatal("LU decomposition: cannot be used to solve overdetermined (m>n) systems of equations.");

    QVMatrix X_inter, B_inter;
    B_inter = P.transpose() * B;
    L.triangularSolve(B_inter,X_inter,false,true);
    // Also works: L.triangularSolve(B_inter,X_inter,false,true);

    if(m==n) {
        U.triangularSolve(X_inter,X,false);
    } else if (m < n) {
        QVMatrix U_inter = U.getCols(0,m-1);
        U_inter.setType(QVMatrix::UpperTriangular);
        U_inter.triangularSolve(X_inter,X,false);
        X = X & QVMatrix(n-m,X.getCols(),0.0); // Adds rows of zeros in unused variables.
    }
}

void solveFromLUDecomposition(const QVMatrix &P, const QVMatrix &L, const QVMatrix &U, QVVector &x, const QVVector &b)
{
    QVMatrix X /*= x.toColumnMatrix()*/, B = b.toColumnMatrix();

    solveFromLUDecomposition(P, L, U, X, B);

    x = X;
}

void solveByLUDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVLU_Method method)
{
    QVMatrix P_dummy, L_dummy, U_dummy;

    LUDecomposition_internal(M, P_dummy, L_dummy, U_dummy, method);
    solveFromLUDecomposition(P_dummy, L_dummy, U_dummy, X, B);
}

void solveByLUDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVLU_Method method)
{
    QVMatrix P_dummy, L_dummy, U_dummy, X, B = b.toColumnMatrix();

    LUDecomposition_internal(M, P_dummy, L_dummy, U_dummy, method);
    solveFromLUDecomposition(P_dummy, L_dummy, U_dummy, X, B);

    x = X;
}

void solveByLUDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B,
                                QVMatrix &P, QVMatrix &L, QVMatrix &U, const TQVLU_Method method)
{
    LUDecomposition_internal(M, P, L, U, method);
    solveFromLUDecomposition(P, L, U, X, B);
}


void solveByLUDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b,
                                QVMatrix &P, QVMatrix &L, QVMatrix &U, const TQVLU_Method method)
{
    QVMatrix X, B = b.toColumnMatrix();

    LUDecomposition_internal(M, P, L, U, method);
    solveFromLUDecomposition(P, L, U, X, B);

    x = X;
}

double LUDecompositionResidual(const QVMatrix &M, const QVMatrix &P, const QVMatrix &L, const QVMatrix &U)
{
    return (P*L*U - M).norm2();
}


void QRDecomposition_internal(const QVMatrix &M, QVMatrix &Q, QVMatrix &R, const TQVQR_Method method)
{
    int m = M.getRows(), n = M.getCols();

    if(method == GSL_HOUSEHOLDER_THIN_QR or method == GSL_HOUSEHOLDER_FULL_QR) {
#ifdef GSL_AVAILABLE
        const int min = (m<n ? m:n);

        gsl_matrix *a = M;
        gsl_matrix *q, *r;
        if(m<n or method == GSL_HOUSEHOLDER_FULL_QR) {
            q = gsl_matrix_alloc(m, m);
            r = gsl_matrix_alloc(m, n);
        } else { // m>=n and method == GSL_HOUSEHOLDER_THIN_QR
            q = gsl_matrix_alloc(m, n);
            r = gsl_matrix_alloc(n, n);
        }
        gsl_vector *tau = gsl_vector_alloc(min);

        gsl_linalg_QR_decomp(a, tau);

        if(m<n or method == GSL_HOUSEHOLDER_FULL_QR) {
            gsl_linalg_QR_unpack (a, tau, q, r);
        } else { // m>=n and method == GSL_HOUSEHOLDER_THIN_QR
            for(int i=0; i<m; i++)
                for(int j=0; j<n; j++)
                    if(i == j)
                        q->data[i*n+j] = 1.0; //gsl_matrix_set(q, i, j, 1.0);
                    else
                        q->data[i*n+j] = 0.0; //gsl_matrix_set(q, i, j, 0.0);
            gsl_vector *v = gsl_vector_alloc(m);
            for(int j=0; j<n; j++) {
                gsl_matrix_get_col(v, q, j);
                gsl_linalg_QR_Qvec(a, tau, v);
                gsl_matrix_set_col(q, j, v);
            }
            gsl_vector_free(v);
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    if(j>=i)
                        r->data[i*n+j] = gsl_matrix_get(a, i, j); //gsl_matrix_set(r, i, j, gsl_matrix_get(a, i, j));
                    else
                        r->data[i*n+j] = 0.0; //gsl_matrix_set(r, i, j, 0.0);
        }

        Q = q;
        R = r;

        gsl_matrix_free(a);
        gsl_matrix_free(q);
        gsl_matrix_free(r);
        gsl_vector_free(tau);
#else
        qFatal("QR decomposition: cannot use GSL methods if GSL library is not available.");
#endif
    } else if(method == LAPACK_THIN_DGEQR2 or method == LAPACK_FULL_DGEQR2) {
#ifdef LAPACK_AVAILABLE
        int lda = m, res, lwork = -1;
        QVMatrix MT = M.transpose(); // Because of FORTRAN transposition.
        QVVector tau(qMax(m,n));
        double *mtptr = MT.getWriteData(), *workptr, *tauptr = tau.data(), ans;

        //dgeqr2(&m,&n,mtptr,&lda,tauptr,workptr,&res); // Deprecated, we use now dgeqrf.

        // Ask for workspace:
        if(m>=n and method == LAPACK_FULL_DGEQR2)
            dgeqrf(&m,&m,mtptr,&lda,tauptr,&ans,&lwork,&res);
        else
            dgeqrf(&m,&n,mtptr,&lda,tauptr,&ans,&lwork,&res);
        lwork = static_cast<int>(ceil(ans));
        QVVector work(lwork);
        workptr = work.data();

        // Decomposition:
        dgeqrf(&m,&n,mtptr,&lda,tauptr,workptr,&lwork,&res);

        // Undoing FORTRAN transposition:
        if(m<n or method == LAPACK_FULL_DGEQR2)
            R = MT.transpose();
        else
            R = MT.transpose().getRows(0,n-1);

        // We overwrite v vectors on R with 0's, to create lower triangular matrix.
        for(int i=1;i<R.getRows();i++)
            for(int j=0;j<qMin(i,R.getCols());j++)
                R(i,j) = 0.0;

        // The matrix Q is now represented as a product of elementary reflectors
        //       Q = H(1) H(2) . . . H(k), where k = min(m,n).
        // Each H(i) has the form
        //       H(i) = I - tau * v * v'
        // where tau is a real scalar, and v is a real vector with v(1:i-1) = 0
        // and v(i) = 1; v(i+1:m) is stored on exit in A(i+1:m,i), and tau in TAU(i).

        /* OLD:
        QVMatrix I = QVMatrix::identity(m);
        Q = I;
        for(int i=0;i<m;i++) {
            QVVector v(m);
            for(int j=0;j<i;j++)
                v(j) = 0.0;
            v(i) = 1.0;
            for(int j=i+1;j<m;j++)
                v(j) = R(j,i);
            Q = Q*(I-tau(i)*(v.toColumnMatrix()*v.toRowMatrix()));
        }*/

        // Reconstruction of Q matrix:
        if(m<n and method == LAPACK_FULL_DGEQR2) {
            dorgqr(&m,&m,&m,mtptr,&lda,tauptr,workptr,&lwork,&res);
            MT = MT.getRows(0,m-1);
        } else if(m<n and method == LAPACK_THIN_DGEQR2) {
            dorgqr(&m,&m,&m,mtptr,&lda,tauptr,workptr,&lwork,&res);
            MT = MT.getRows(0,m-1);
        } else if(m>=n and method == LAPACK_FULL_DGEQR2) {
            MT = MT & QVMatrix(m-n,m,0.0);
            mtptr = MT.getWriteData();
            dorgqr(&m,&m,&n,mtptr,&lda,tauptr,workptr,&lwork,&res);
        } else if(m>=n and method == LAPACK_THIN_DGEQR2) {
            dorgqr(&m,&n,&n,mtptr,&lda,tauptr,workptr,&lwork,&res);
        }

        Q = MT.transpose();
#else
        qFatal("QR decomposition: cannot use LAPACK methods if MKL, ATLAS of LAPACK BASE not available.");
#endif
    }

    R.setType(QVMatrix::UpperTriangular);
}

void QRDecomposition(const QVMatrix &M, QVMatrix &Q, QVMatrix &R, const TQVQR_Method method)
{
    QRDecomposition_internal(M, Q, R, method);
}

double QRDecompositionResidual(const QVMatrix &M, const QVMatrix &Q, const QVMatrix &R)
{
    return (Q*R - M).norm2() + (Q.transpose()*Q - QVMatrix::identity(Q.getCols())).norm2();
}

void QLDecomposition(const QVMatrix &M, QVMatrix &Q, QVMatrix &L, const TQVQR_Method method)
{
    QVMatrix M_inter,Q_inter,R_inter;

    M_inter = M.transpose().reversedRows().transpose();

    QRDecomposition_internal(M_inter, Q_inter, R_inter, method);

    Q = Q_inter.transpose().reversedRows().transpose();
    L = R_inter.transpose().reversedRows().reversedCols().transpose();
    L.setType(QVMatrix::LowerTriangular);
}

double QLDecompositionResidual(const QVMatrix &M, const QVMatrix &Q, const QVMatrix &L)
{
    return (Q*L - M).norm2() + (Q.transpose()*Q - QVMatrix::identity(Q.getCols())).norm2();
}

void RQDecomposition(const QVMatrix &M, QVMatrix &R, QVMatrix &Q, const TQVQR_Method method)
{
    QVMatrix M_inter,Q_inter,R_inter;

    M_inter = M.reversedRows().transpose();

    QRDecomposition_internal(M_inter, Q_inter, R_inter, method);

    Q = Q_inter.transpose().reversedRows();
    R = R_inter.transpose().reversedRows().reversedCols();
    R.setType(QVMatrix::UpperTriangular);
}

double RQDecompositionResidual(const QVMatrix &M, const QVMatrix &R, const QVMatrix &Q)
{
    return (R*Q - M).norm2() + (Q*Q.transpose() - QVMatrix::identity(Q.getRows())).norm2();
}

void LQDecomposition(const QVMatrix &M, QVMatrix &L, QVMatrix &Q, const TQVQR_Method method)
{
    QVMatrix M_inter,Q_inter,R_inter;

    M_inter = M.transpose();

    QRDecomposition_internal(M_inter, Q_inter, R_inter, method);

    Q = Q_inter.transpose();
    L = R_inter.transpose();
    L.setType(QVMatrix::LowerTriangular);
}

double LQDecompositionResidual(const QVMatrix &M, const QVMatrix &L, const QVMatrix &Q)
{
    return (L*Q - M).norm2() + (Q*Q.transpose() - QVMatrix::identity(Q.getRows())).norm2();
}

void solveFromQRDecomposition(const QVMatrix &Q, const QVMatrix &R, QVMatrix &X, const QVMatrix &B)
{
    const int m = Q.getRows(), n = R.getCols();

    QVMatrix X_inter = Q.dotProduct(B,true,false);

    if(m == n)
        R.triangularSolve(X_inter,X,false);
    else if(m > n) {
        QVMatrix R_inter = R.getRows(0,n-1);
        R_inter.setType(QVMatrix::UpperTriangular);
        R_inter.triangularSolve(X_inter.getRows(0,n-1),X,false);
        //X = X & QVMatrix(n-m,X.getCols(),0.0); // Adds rows of zeros in unused variables.
    } else { // m < n
        QVMatrix R_inter = R.getCols(0,m-1);
        R_inter.setType(QVMatrix::UpperTriangular);
        R_inter.triangularSolve(X_inter,X,false);
        X = X & QVMatrix(n-m,X.getCols(),0.0); // Adds rows of zeros in unused variables.
    }
}

void solveFromQRDecomposition(const QVMatrix &Q, const QVMatrix &R, QVVector &x, const QVVector &b)
{
    QVMatrix X /*= x.toColumnMatrix()*/, B = b.toColumnMatrix();

    solveFromQRDecomposition(Q, R, X, B);

    x = X;
}

 void solveByQRDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVQR_Method method)
{
    QVMatrix Q_dummy, R_dummy, X, B = b.toColumnMatrix();

    QRDecomposition_internal(M, Q_dummy, R_dummy, method);
    solveFromQRDecomposition(Q_dummy, R_dummy, X, B);
    x = X;
}

void solveByQRDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVQR_Method method)
{
    QVMatrix Q_dummy, R_dummy;

    QRDecomposition_internal(M, Q_dummy, R_dummy, method);
    solveFromQRDecomposition(Q_dummy, R_dummy, X, B);
}

void solveByQRDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, QVMatrix &Q, QVMatrix &R, const TQVQR_Method method)
{
    QVMatrix X, B = b.toColumnMatrix();

    QRDecomposition_internal(M, Q, R, method);
    solveFromQRDecomposition(Q, R, X, B);

    x = X;
}

void solveByQRDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, QVMatrix &Q, QVMatrix &R, const TQVQR_Method method)
{
    QRDecomposition_internal(M, Q, R, method);
    solveFromQRDecomposition(Q, R, X, B);
}


void eigenDecomposition_internal(const QVMatrix &M, QVVector &eigVals, QVMatrix &eigVecs, const TQVEigenDecomposition_Method method, bool only_ev = false)
                                 // bool solve, QVMatrix &X, const QVMatrix &B)
{
    // Check matrix M is symmetric
    Q_ASSERT(M.getCols() == M.getRows());

    if(method == GSL_EIGENSYMM) {
#ifdef GSL_AVAILABLE
    //std::cout << "----------- B --------------" << std::endl;
        const int n = M.getCols();
        gsl_matrix *m = M;
        gsl_vector *eval = gsl_vector_alloc (n);
        gsl_matrix *evec = gsl_matrix_alloc (n, n);

        if(only_ev) {
            gsl_eigen_symm_workspace *w = gsl_eigen_symm_alloc (n);

            gsl_eigen_symm (m, eval, w);
            // evec does not contain here anything useful, but there GSL does not provide a "gsl_eigen_symm_sort" function:
            gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_VAL_DESC);

            gsl_eigen_symm_free (w);
        } else { // method == GSL_EIGENSYMM_ONLY
            gsl_eigen_symmv_workspace *w = gsl_eigen_symmv_alloc (n);

            gsl_eigen_symmv (m, eval, evec, w);
            gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_VAL_DESC);

            eigVecs = evec;
            //eigVecs = eigVecs.transpose();

            gsl_eigen_symmv_free (w);
        }
        eigVals = eval;

        gsl_matrix_free (m);
        gsl_vector_free (eval);
        gsl_matrix_free (evec);
#else
        qFatal("EigenDecomposition: cannot use GSL methods if GSL library is not available.");
#endif
    } else if(method == LAPACK_DSYEV) {
#ifdef LAPACK_AVAILABLE
    //std::cout << "----------- A --------------" << std::endl;
        int n = M.getCols(), lda = n, lwork = -1, res;
        const char *jobz, *uplo = "L";
        QVMatrix oldEigVecs;
        if(only_ev) {
            jobz = "N";
            oldEigVecs = eigVecs;
        } else {
            jobz = "V";
        }

        eigVecs = M;
        eigVals = QVVector(n, 0.0);
        double *eigvecsptr = eigVecs.getWriteData(), *w = eigVals.data(), *workptr, ans;

        // Ask for adequate quantity of space:
        dsyev(const_cast<char*>(jobz),const_cast<char*>(uplo),
              &n, eigvecsptr, &lda, w, &ans, &lwork, &res);
        lwork = static_cast<int>(ceil(ans));
        QVVector work(lwork, 0.0);
        workptr = work.data();
        // Compute:
        dsyev(const_cast<char*>(jobz),const_cast<char*>(uplo),
              &n, eigvecsptr, &lda, w, workptr, &lwork, &res);

        // Eigenvalues (and corresponding eigenvectors) in decreasing order:
        for(int i=0;i<n/2;i++) {
            double inter;
            inter = eigVals[i];
            eigVals[i] = eigVals[n-i-1];
            eigVals[n-i-1] = inter;
            for(int j=0;j<n;j++) {
                inter = eigVecs(i,j);
                eigVecs(i,j) = eigVecs(n-i-1,j);
                eigVecs(n-i-1,j) = inter;
            }
        }

        // We restore "unused" input eigenvectors (if only eigenvalues were asked for)...
        if(only_ev)
            eigVecs = oldEigVecs;
        else
            // ... or we transpose result to give eigenvectors as rows (undo FORTRAN storing):
            eigVecs = eigVecs.transpose();
#else
    qFatal("EigenDecomposition: cannot use LAPACK methods if LAPACK, ATLAS or MKL libraries are not available.");
#endif
    }
    /* if(solve) {
        X = eigVecs.dotProduct(B,true,false);
        for(int i=0;i<M.getCols();i++)
            for(int j=0;j<X.getCols();j++)
                X(i,j) /= eigVals[i];

        X = eigVecs.dotProduct(X,false,false);
    }*/
}

void eigenDecomposition(const QVMatrix &M, QVVector &lambda, QVMatrix &Q, const TQVEigenDecomposition_Method method)
{
    eigenDecomposition_internal(M, lambda, Q, method);
}

double eigenDecompositionResidual(const QVMatrix &M, const QVVector &lambda, const QVMatrix &Q)
{
    Q_ASSERT(M.getCols() == M.getRows());
    Q_ASSERT(M.getCols() == lambda.size());
    Q_ASSERT(Q.getCols() == Q.getRows());
    Q_ASSERT(Q.getCols() == lambda.size());

    double res1 = (Q*QVMatrix::diagonal(lambda)*Q.transpose()-M).norm2();
    double res2 = (Q.transpose()*Q - QVMatrix::identity(Q.getCols())).norm2();

    return res1 + res2;
}

void eigenValues(const QVMatrix &M, QVVector &lambda, const TQVEigenValues_Method method)
{
    QVMatrix Q_dummy;

    Q_ASSERT(M.getCols() == M.getRows());

    if(method == GSL_EIGENSYMM_ONLY)
        eigenDecomposition_internal(M, lambda, Q_dummy, GSL_EIGENSYMM, true);
    else if(method == LAPACK_DSYEV_ONLY)
        eigenDecomposition_internal(M, lambda, Q_dummy, LAPACK_DSYEV, true);
}

double eigenValuesResidual(const QVMatrix &M, const QVVector &lambda)
{
    double acum = 0.0;

    Q_ASSERT(M.getCols() == M.getRows());
    Q_ASSERT(M.getCols() == lambda.size());

    // Sum of diagonal elements of matrix (trace) should be equal to sum of eigenvalues:
    for(int i=0;i<M.getRows();i++)
        acum += M(i,i);
    for(int i=0;i<lambda.size();i++)
        acum -= lambda[i];

    return qAbs(acum);
}


QVMatrix pseudoInverse(const QVMatrix &M, const TQVSVD_Method method, double epsilon)
{
    QVMatrix U, V;
    QVVector s;

    singularValueDecomposition(M, U, s, V, method);

    // Pseudo-inverse by sum of outer product of corresponding left and right singular vectors, weighted with corresponding
    // reciprocals of singular values:
    const int m = M.getRows(), n = M.getCols();
    QVMatrix result(n,m,0.0);
    if(s[0] > 0.0)
        for(int i=0;i<s.size();i++)
            if(s[i]/s[0] > epsilon)
                result += (1/s[i]) * (V.getCol(i).outerProduct(U.getCol(i)));

    return result;
}


double determinant(const QVMatrix &M, const TQVLU_Method method)
{
    Q_ASSERT(M.getRows() == M.getCols());
    const int n = M.getRows();

    /* gsl_matrix *m = M;

    int sign;

    gsl_permutation *p = gsl_permutation_alloc(3);
    gsl_linalg_LU_decomp (m, p, &sign);
    const double det = gsl_linalg_LU_det (m, sign);

    gsl_matrix_free(m);
    gsl_permutation_free (p); */

    if(n == 1)
        return M(0,0);

    double det=1.0;

    QVMatrix P,L,U;

    LUDecomposition(M,P,L,U,method);

    for(int i=0;i<n;i++)
        det *= U(i,i);

    QVPermutation perm = QVPermutation::fromMatrix(P);

    det *= perm.signature();

    return det;
}

void solveHomogeneous(const QVMatrix &A, QVector<double> &x, const TQVSVD_Method method)
{
        QVMatrix U, V;
        QVVector s;
        singularValueDecomposition(A, U, s, V, method);

        x = V.getCol(V.getCols()-1);
}

double solveResidual(const QVMatrix &M, const QVMatrix &X, const QVMatrix &B)
{
    double res = (M*X-B).norm2();

    return res;
}

double solveResidual(const QVMatrix &M, const QVVector &x, const QVVector &b)
{
    double res = (M*x-b).norm2();

    return res;
}

#ifndef DOXYGEN_IGNORE_THIS
double solveConjugateGradient(const QVSparseBlockMatrix &A, QVVector &x, const QVVector &b, const int maxIters, const int minIters, const double minAbsoluteError)
    {				
    QVVector	r = b - A.dotProduct(x),
				p = r;
    double rsold = r.dotProduct(r);

	int i;
    for (i = 0; i < maxIters; i++)
        {
		const QVVector Ap = A * p;
        const double alpha = rsold / p.dotProduct(Ap);
        x = x + alpha * p;
        r = r - alpha * Ap;

		// -----------------------------------------------------------
		//std::cout << "Conjugate gradient! " << (A.dotProduct(x) - b).norm2() << std::endl;
		// -----------------------------------------------------------
		const double rsnew = r.dotProduct(r);
		if ( (rsnew < minAbsoluteError) and (i > minIters) )
			break;

		p = r + (rsnew / rsold )* p;
		rsold = rsnew;
        }
	//std::cout << "********************************* max iters = " << i << std::endl;

    return sqrt(rsold);
    }


double solvePreconditionedConjugateGradient(const QVSparseBlockMatrix &A, const QVSparseBlockMatrix &invM, QVVector &x, const QVVector &b, const int maxIters, const int minIters, const double minAbsoluteError)
    {				
    QVVector	r = b - A.dotProduct(x),
				z = invM*r,
				p = z;

	int i;
    for (i = 0; i < maxIters; i++)
        {
		const double rk_zk = r.dotProduct(z);
		Q_ASSERT(rk_zk == z.dotProduct(r));

        const double alpha = rk_zk / (p.dotProduct(A*p));
        x = x + alpha * p;
        r = r - alpha * A*p;
		z = invM * r;

		const double rsnew = r.dotProduct(r);
		if ( (rsnew < minAbsoluteError) and (i > minIters) )
			break;

		// -----------------------------------------------------------
		//std::cout << "Conjugate gradient! " << (A.dotProduct(x) - b).norm2() << std::endl;
		// -----------------------------------------------------------

		const double beta = r.dotProduct(z) / rk_zk;
		p = z + beta * p;
        }
	//std::cout << "********************************* max iters = " << i << std::endl;

    return 1.0;
    }
#endif

bool blockJacobiPreconditionMatrix(const QVSparseBlockMatrix &A, const QVVector &b, QVSparseBlockMatrix &invM)
	{
	const int	majorRows = A.getMajorRows(),	majorCols = A.getMajorCols(),
				minorRows = A.getMinorRows(),	minorCols = A.getMinorCols();

	if ( (majorRows != majorCols) or (minorRows != minorCols) )
		return false;

	invM = QVSparseBlockMatrix(majorRows, majorRows, minorRows, minorRows);

	for(int i = 0; i < majorRows; i++)
		invM.setBlock(i, i, A[i][i].inverse());

	return true;
	}

bool blockJacobiPreconditioning(QVSparseBlockMatrix &A, QVVector &b)
	{
	const int	majorRows = A.getMajorRows(),	majorCols = A.getMajorCols(),
				minorRows = A.getMinorRows(),	minorCols = A.getMinorCols();

	if ( (majorRows != majorCols) or (minorRows != minorCols) )
		return false;

	QVSparseBlockMatrix precond(majorRows, majorRows, minorRows, minorRows);
	for(int i = 0; i < majorRows; i++)
		precond.setBlock(i, i, A[i][i].inverse());

	A = precond * A;
	b = precond * b;

	return true;
	}

int dummy;

double sparseSolve(const QVSparseBlockMatrix &qvspmatrixPre, QVVector &x, const QVVector &bPre,
                 const bool isSymmetric, const bool isPosDefinite, const TQVSparseSolve_Method method,
                 const bool start_from_x, const bool iters_or_resid,
                 const int iters, const double resid, int &final_iter_count)
    {
	QVSparseBlockMatrix qvspmatrix = qvspmatrixPre;
	QVVector b = bPre;

    if (b.size() != qvspmatrix.getMajorRows()*qvspmatrix.getMinorRows())
        {
        std::cout << "[sparseSolve] Error: tried to solve sparse linear system with incompatible sizes of rhs vector and "
        << "coefficient matrix." << std::endl
        << "\tSparse matrix number of blocks:\t"
        << qvspmatrix.getMajorRows() << "x" << qvspmatrix.getMajorCols() << std::endl
        << "\tSparse matrix size of each block:\t"
        << qvspmatrix.getMinorRows() << "x" << qvspmatrix.getMinorCols() << std::endl
        << "\tRight hand side vector size:\t" << b.size() << std::endl;
        exit(1);
        }

    const bool isSquare =	(qvspmatrix.getMajorRows() == qvspmatrix.getMajorCols()) and
			                (qvspmatrix.getMinorRows() == qvspmatrix.getMinorCols());

    switch (method)
        {
        case QVCHOLMOD_DSS:
            {
            #ifdef QVCHOLMOD
            if ( not isSymmetric )
                qFatal("[sparseSolve] Cannot use CHOLMOD method to solve a non-symmetric matrix.");

            QVVector mutableB = b;
            QVCholmodSolver solver(qvspmatrix);
            solver.init();
            solver.solve(x, mutableB);
            #else
            qFatal("[sparseSolve] Cannot use CHOLMOD methods if CHOLMOD is not available.");
            #endif
            break;
            }

        case QVMKL_DSS:
            {
            #ifdef MKL_AVAILABLE
            // Set size for solution vector X:
            x = QVVector(qvspmatrix.getMajorCols()*qvspmatrix.getMinorCols());

            // Convert sparse matrix to PARDISO format:
            MKLPardisoSparseFormat pardisomatrix;
            if (isSquare and isSymmetric)
                squareSymmetricSparseMatrixToPardisoFormat(qvspmatrix, pardisomatrix);
            else
                pardisomatrix = MKLPardisoSparseFormat(qvspmatrix,isSymmetric);

            // Allocate space for handle and associated variables (see MKL examples/solver/source/dss_sym_c.c):
            _MKL_DSS_HANDLE_t handle;
            _INTEGER_t error;
            int opt = MKL_DSS_DEFAULTS;
            int sym = isSymmetric ? MKL_DSS_SYMMETRIC : MKL_DSS_NON_SYMMETRIC;
            int type = isPosDefinite ? MKL_DSS_POSITIVE_DEFINITE : MKL_DSS_INDEFINITE;

            // Initialize solver:
            error = dss_create(handle,opt);
            CHECK_MKL_DSS_ERROR

            // Define the non-zero structure of the matrix:
            error = dss_define_structure(handle,sym,pardisomatrix.rowIndex,pardisomatrix.nRows,pardisomatrix.nCols, pardisomatrix.columns,pardisomatrix.nNonZeros);
            CHECK_MKL_DSS_ERROR

            // Reorder the matrix:
            error = dss_reorder(handle,opt,0);
            CHECK_MKL_DSS_ERROR

            // Factor the matrix:
            error = dss_factor_real(handle,type,pardisomatrix.values);
            CHECK_MKL_DSS_ERROR

            // Get the solution vector:
            int nrhs = 1;
            error = dss_solve_real(handle,opt,b.data(),nrhs,x.data());
            CHECK_MKL_DSS_ERROR

            // Deallocate solver storage:
            error = dss_delete(handle,opt);
            CHECK_MKL_DSS_ERROR

            // Always returns zero:
            return 0.0;
            #else
            qFatal("[sparseSolve] Cannot use MKL methods if MKL is not available.");
            #endif
            break;
            }

        case QVMKL_ISS:
            {
            #ifdef MKL_AVAILABLE
            // Only for solving symmetric positive definite system of equations, simplest case:
            // no preconditioning and no user-defined stopping tests.
            if(not isSymmetric or not isPosDefinite)
                qFatal("[sparseSolve] QVMKL_ISS method only admits a symmetric and positive definite coefficient matrix.");

            // MKL ISS parameters:
            MKL_INT n=b.size(), rci_request, itercount, i;
            MKL_INT ipar[128];
            double dpar[128],*tmp;
            QVVector temp(4*n);
            tmp = temp.data();
            char tr='u';

            // Convert sparse matrix to PARDISO format:
            MKLPardisoSparseFormat pardisomatrix;
            if (isSquare and isSymmetric)
                squareSymmetricSparseMatrixToPardisoFormat(qvspmatrix, pardisomatrix);
            else
                pardisomatrix = MKLPardisoSparseFormat(qvspmatrix,isSymmetric);
            //MKLPardisoSparseFormat pardisomatrix(qvspmatrix,isSymmetric);

            // Initial solution guess (vector of ones, if completely unknown, previous value of x otherwise):
            if(start_from_x)
                {
                if(x.size() != qvspmatrix.getMajorCols()*qvspmatrix.getMinorCols())
                    {
                    std::cout << "[sparseSolve] (QVMKL_ISS): error, tried to reuse unknowns x vector with incompatible size with "
                    << "coefficient matrix." << std::endl
                    << "\tSparse matrix number of blocks:\t"
                    << qvspmatrix.getMajorRows() << "x" << qvspmatrix.getMajorCols() << std::endl
                    << "\tSparse matrix size of each block:\t"
                    << qvspmatrix.getMinorRows() << "x" << qvspmatrix.getMinorCols() << std::endl
                    << "\tunknowns x vector size:\t" << x.size() << std::endl;
                    exit(1);
                    }
                }
            else {
                // Set size for solution vector x, and initialize with ones (for example):
                x = QVVector(qvspmatrix.getMajorCols()*qvspmatrix.getMinorCols());
                for(i=0;i<n;i++) x[i]=1.E0;
                }

            // Initialize the solver:
            dcg_init(&n,x.data(),const_cast<double*>(b.data()),&rci_request,ipar,dpar,tmp);
            if (rci_request!=0) goto failure;

            // Set the desired parameters:
            if(iters_or_resid)
                {
                // Set maximum number of iterations:
                if(iters > qvspmatrix.getMajorCols()*qvspmatrix.getMinorCols())
                    {
                    std::cout << "[sparseSolve] (QVMKL_ISS): error, iters must be less than or equal to the dimension of the problem.\n"
                    << "\tSparse matrix number of blocks:\t"
                    << qvspmatrix.getMajorRows() << "x" << qvspmatrix.getMajorCols() << std::endl
                    << "\tSparse matrix size of each block: "
                    << qvspmatrix.getMinorRows() << "x" << qvspmatrix.getMinorCols() << std::endl
                    << "\tdimension: " << qvspmatrix.getMajorCols()*qvspmatrix.getMinorCols() << std::endl
                    << "\titers requested: " << iters << std::endl;
                    exit(1);
                    }

                ipar[4]=iters;
                ipar[7]=1;
                ipar[8]=0;
                ipar[9]=0;
                }
            else	{
                // Absolute norm of residual:
                ipar[8]=1;
                ipar[9]=0;
                dpar[0]=0.0;
                dpar[1]=resid;
                }

            // Check the correctness and consistency of the newly set parameters.
            dcg_check(&n,x.data(),const_cast<double*>(b.data()),&rci_request,ipar,dpar,tmp);
            if (rci_request!=0) goto failure;

            // Compute the solution by RCI (P)CG solver without preconditioning
            // (Reverse Communications starts here).
            rci:
            dcg(&n,x.data(),const_cast<double*>(b.data()),&rci_request,ipar,dpar,tmp);
            // If rci_request=0, then the solution was found with the required precision.
            if (rci_request==0) goto getsln;
            // If rci_request=1, then compute the vector A*tmp[0] and put the result in vector tmp[n]:
            if (rci_request==1)
                {
                mkl_dcsrsymv(&tr, &n, pardisomatrix.values, pardisomatrix.rowIndex, pardisomatrix.columns, tmp, &tmp[n]);
                goto rci;
                }
            // If rci_request=anything else, then dcg subroutine failed to compute the solution vector: solution[n]
            // goto failure;
            std::cerr << "[sparseSolve] WARNING: failed to complete requested convergence\n";
            // (Reverse Communication ends here).

            // Get the current iteration number into itercount.
            getsln:
            dcg_get(&n,x.data(),const_cast<double*>(b.data()),&rci_request,ipar,dpar,tmp,&itercount);

            final_iter_count = itercount;
            //printf("ISS: Number of iterations: %d\n",itercount);
            goto end;
            failure:
            std::cout << "RCI CG solver failed to complete computations. Error code " << rci_request << std::endl;
            qFatal("[sparseSolve] QVMKL_ISS method failed.");
            end:
            return dpar[4];
            #else
            qFatal("[sparseSolve] cannot use MKL methods if MKL not available.");
            #endif
            break;
            }

		case QV_BJPCG:
			{
			if ( not isSymmetric )
				qFatal("[sparseSolve] Cannot use block Jacobi preconditioner on a non-symmetric coefficient matrix.");

			QVSparseBlockMatrix invM;
			if (not blockJacobiPreconditionMatrix(qvspmatrix, b, invM))
				return false;

			return solvePreconditionedConjugateGradient(qvspmatrix, invM, x, b, iters, 0, resid);
			break;
			}

        case QV_SCG:
            {
			foreach(int ib, qvspmatrix.keys())
				{
				const QMap<int, QVMatrix> &majorRow = qvspmatrix[ib];
				foreach(int jb, majorRow.keys())
					if (ib != jb)
						qvspmatrix[jb][ib] = majorRow[jb].transpose();
				}

            return solveConjugateGradient(qvspmatrix, x, b, iters, 0, resid);
            break;
            }

        case QV_DENSE:
            {
            solveByCholeskyDecomposition(QVMatrix(qvspmatrix), x, b);
            return true;
            break;
            }

        default:
            {
            return 0.0;
            break;
            }
        }
    return -1.0;
    }

// -----------------------------------------------------------------------------------------------------------------------------------
#ifdef MKL_AVAILABLE
double sparseSolve(const MKLPardisoSparseFormat &pardisomatrix, QVVector &x, const QVVector &b,
                 const bool isSymmetric, const bool isPosDefinite, const TQVSparseSolve_Method method,
                 const bool start_from_x, const bool iters_or_resid,
                 const int iters, const double resid, int &final_iter_count)
{

    // Check correctness of input:
    if(b.size() != pardisomatrix.getMajorRows()*pardisomatrix.getMinorRows()) {
        std::cout << "[sparseSolve] Error: tried to solve sparse linear system with incompatible sizes of rhs vector and "
                  << "coefficient matrix." << std::endl
                  << "\tSparse matrix number of blocks:\t"
                       << pardisomatrix.getMajorRows() << "x" << pardisomatrix.getMajorCols() << std::endl
                  << "\tSparse matrix size of each block:\t"
                       << pardisomatrix.getMinorRows() << "x" << pardisomatrix.getMinorCols() << std::endl
                       << "\tRight hand side vector size:\t" << b.size() << std::endl;
        exit(1);
    }

    if(method == QVMKL_DSS) {
        // Set size for solution vector X:
        x = QVVector(pardisomatrix.getMajorCols()*pardisomatrix.getMinorCols());

        // Allocate space for handle and associated variables (see MKL examples/solver/source/dss_sym_c.c):
        _MKL_DSS_HANDLE_t handle;
        _INTEGER_t error;
        int opt = MKL_DSS_DEFAULTS;
        int sym = isSymmetric ? MKL_DSS_SYMMETRIC : MKL_DSS_NON_SYMMETRIC;
        int type = isPosDefinite ? MKL_DSS_POSITIVE_DEFINITE : MKL_DSS_INDEFINITE;

        // Initialize solver:
        error = dss_create(handle,opt);
        CHECK_MKL_DSS_ERROR

        // Define the non-zero structure of the matrix:
        error = dss_define_structure(handle,sym,pardisomatrix.rowIndex,pardisomatrix.nRows,pardisomatrix.nCols,
                                     pardisomatrix.columns,pardisomatrix.nNonZeros);
        CHECK_MKL_DSS_ERROR

        // Reorder the matrix:
        error = dss_reorder(handle,opt,0);
        CHECK_MKL_DSS_ERROR

        // Factor the matrix:
        error = dss_factor_real(handle,type,pardisomatrix.values);
        CHECK_MKL_DSS_ERROR

        // Get the solution vector:
        int nrhs = 1;
        error = dss_solve_real(handle,opt,b.data(),nrhs,x.data());
        CHECK_MKL_DSS_ERROR

        // Deallocate solver storage:
        error = dss_delete(handle,opt);
        CHECK_MKL_DSS_ERROR

        // Always returns zero:
        return 0.0;
    } else if(method == QVMKL_ISS) {
        // Only for solving symmetric positive definite system of equations, simplest case:
        // no preconditioning and no user-defined stopping tests.
        if(not isSymmetric or not isPosDefinite) {
            qFatal("[sparseSolve] QVMKL_ISS method only admits a symmetric and positive definite coefficient matrix.");
        }
        // MKL ISS parameters:
        MKL_INT n=b.size(), rci_request, itercount, i;
        MKL_INT ipar[128];
        double dpar[128],*tmp;
        QVVector temp(4*n);
        tmp = temp.data();
        char tr='u';

        // Initial solution guess (vector of ones, if completely unknown, previous value of x otherwise):
        if(start_from_x) {
            if(x.size() != pardisomatrix.getMajorCols()*pardisomatrix.getMinorCols()) {
                std::cout << "[sparseSolve] (QVMKL_ISS): error, tried to reuse unknowns x vector with incompatible size with "
                          << "coefficient matrix." << std::endl
                          << "\tSparse matrix number of blocks:\t"
                          << pardisomatrix.getMajorRows() << "x" << pardisomatrix.getMajorCols() << std::endl
                          << "\tSparse matrix size of each block:\t"
                          << pardisomatrix.getMinorRows() << "x" << pardisomatrix.getMinorCols() << std::endl
                          << "\tunknowns x vector size:\t" << x.size() << std::endl;
                exit(1);
            }
        } else {
            // Set size for solution vector x, and initialize with ones (for example):
            x = QVVector(pardisomatrix.getMajorCols()*pardisomatrix.getMinorCols());
            for(i=0;i<n;i++)
                x[i]=1.E0;
        }

        // Initialize the solver:
        dcg_init(&n,x.data(),const_cast<double*>(b.data()),&rci_request,ipar,dpar,tmp);
        if (rci_request!=0) goto failure;

        // Set the desired parameters:
        if(iters_or_resid) {
            // Set maximum number of iterations:
            if(iters > pardisomatrix.getMajorCols()*pardisomatrix.getMinorCols()) {
                std::cout << "[sparseSolve] (QVMKL_ISS): error, iters must be less than or equal to the dimension of the problem.\n"
                          << "\tSparse matrix number of blocks:\t"
                          << pardisomatrix.getMajorRows() << "x" << pardisomatrix.getMajorCols() << std::endl
                          << "\tSparse matrix size of each block: "
                          << pardisomatrix.getMinorRows() << "x" << pardisomatrix.getMinorCols() << std::endl
                          << "\tdimension: " << pardisomatrix.getMajorCols()*pardisomatrix.getMinorCols() << std::endl
                          << "\titers requested: " << iters << std::endl;
                exit(1);
            }
            ipar[4]=iters;
            ipar[7]=1;
            ipar[8]=0;
            ipar[9]=0;
        } else {
            // Absolute norm of residual:
            ipar[8]=1;
            ipar[9]=0;
            dpar[0]=0.0;
            dpar[1]=resid;
        }

        // Check the correctness and consistency of the newly set parameters.
        dcg_check(&n,x.data(),const_cast<double*>(b.data()),&rci_request,ipar,dpar,tmp);
        if (rci_request!=0) goto failure;

        // Compute the solution by RCI (P)CG solver without preconditioning
        // (Reverse Communications starts here).
    rci:
        dcg(&n,x.data(),const_cast<double*>(b.data()),&rci_request,ipar,dpar,tmp);
        // If rci_request=0, then the solution was found with the required precision.
        if (rci_request==0) goto getsln;
        // If rci_request=1, then compute the vector A*tmp[0] and put the result in vector tmp[n]:
        if (rci_request==1) {
                mkl_dcsrsymv(&tr, &n, pardisomatrix.values, pardisomatrix.rowIndex, pardisomatrix.columns, tmp, &tmp[n]);
                goto rci;
        }
        // If rci_request=anything else, then dcg subroutine failed to compute the solution vector: solution[n]
        // goto failure;
        std::cerr << "[sparseSolve] WARNING: failed to complete requested convergence\n";
        // (Reverse Communication ends here).

        // Get the current iteration number into itercount.
    getsln:
        dcg_get(&n,x.data(),const_cast<double*>(b.data()),&rci_request,ipar,dpar,tmp,&itercount);

        final_iter_count = itercount;
        //printf("ISS: Number of iterations: %d\n",itercount);
        goto end;
    failure:
    std::cout <<  "RCI CG solver failed to complete computations. Error code " << rci_request << std::endl;
        qFatal("[sparseSolve] QVMKL_ISS method failed.");
    end:
        return dpar[4];
    }
    return 0.0;
}
#endif

// Solves an homogeneous system using the inverse iteration algorithm.
bool solveHomogeneous(const QVSparseBlockMatrix &A, QVVector &x, const int maxIterations, const double minRelativeError, const TQVSparseSolve_Method method)
    {
    #ifdef MKL_AVAILABLE
    if(method != QVMKL_DSS) {
        std::cerr << "[solveHomogeneous] Warning: this function for sparse matrices only supports QVMKL_DSS method." << std::endl;
    }

    const QVSparseBlockMatrix AtA = A.transpose() * A;

    //std::cout << "A rows cols = " << QVMatrix(A).getRows() << "\t" << QVMatrix(A).getCols() << std::endl;
    const int totalCols = AtA.getMajorCols() * AtA.getMinorCols();

    if (x.count() != totalCols)
        x = QVVector::random(totalCols);

    // -- Init MKL solver ------------------------------------------
    // Convert sparse matrix to Pardiso format.
    const int	opt = MKL_DSS_DEFAULTS,
            sym = MKL_DSS_SYMMETRIC,
            type = MKL_DSS_POSITIVE_DEFINITE;

    MKLPardisoSparseFormat pardisomatrix(AtA, true);

        // Initialize solver:
    _MKL_DSS_HANDLE_t handle;
    _INTEGER_t error = dss_create(handle,opt);
    CHECK_MKL_DSS_ERROR;

        // Define the non-zero structure of the matrix:
    error = dss_define_structure(handle, sym, pardisomatrix.rowIndex, pardisomatrix.nRows, pardisomatrix.nCols, pardisomatrix.columns, pardisomatrix.nNonZeros);
    CHECK_MKL_DSS_ERROR;

        // Reorder the matrix:
    error = dss_reorder(handle,opt,0);
    CHECK_MKL_DSS_ERROR;

        // Factor the matrix:
    error = dss_factor_real(handle, type, pardisomatrix.values);
    CHECK_MKL_DSS_ERROR;
    // ------------------------------------------------------------

    bool success = false;
    // Iterate to obtain the solution.
    for(int i = 0; i < maxIterations; i++)
        {
        QVVector xNew = x;

        //SparseSolve(AtA, xNew, x, true, true, QVMKL_DSS, true, true, 10);

        int nrhs = 1;
        error = dss_solve_real(handle, opt, x.data(), nrhs, xNew.data());
        CHECK_MKL_DSS_ERROR;

        xNew = xNew / xNew.norm2();
        const double relativeError = (x-xNew).norm2();

        x = xNew;

        if (relativeError <= minRelativeError)
            {
            success = true;
            break;
            }
        }

    // -- Release MKL data ---
        // Deallocate solver storage:
    error = dss_delete(handle,opt);
    CHECK_MKL_DSS_ERROR;

    return success;

    #else
    std::cerr << "[solveHomogeneous] Warning: this function requires the MKL library." << std::endl;
    #endif
    }


// -----------------------------------------------------------------------------------------------------------------------------------
void solveLinear(const QVMatrix &A, QVVector &x, const QVVector &b)
    {
        std::cout << "solveLinear DEPRECATED, use any of the following functions instead, depending on your needs:\n"
                     "solveBySingularValueDecomposition\n"
                     "solveByCholeskyDecomposition\n"
                     "solveByLUDecomposition\n"
                     "solveByQRDecomposition\n"
                     "(see QVision documentation for details):\n";

        Q_ASSERT(A.getCols() == A.getRows());
    Q_ASSERT(A.getCols() == x.size());
    Q_ASSERT(A.getCols() == b.size());

#ifdef GSL_AVAILABLE
        gsl_matrix *gA = A;
    gsl_vector *gB = b;

    gsl_linalg_HH_svx(gA, gB);
    x = gB;

    gsl_matrix_free(gA);
    gsl_vector_free(gB);
#else
        qFatal("solveLinear: cannot use GSL methods if GSL library is not available.");
#endif
        }

void solveLinear(const QVMatrix &A, QVMatrix &X, const QVMatrix &B)
    {
        std::cout << "solveLinear DEPRECATED, use any of the following functions instead, depending on your needs:\n"
                     "solveBySingularValueDecomposition\n"
                     "solveByCholeskyDecomposition\n"
                     "solveByLUDecomposition\n"
                     "solveByQRDecomposition\n"
                     "(see QVision documentation for details):\n";

        Q_ASSERT(A.getCols() == A.getRows());
    Q_ASSERT(A.getCols() == X.getRows());
    Q_ASSERT(A.getCols() == B.getRows());

#ifdef GSL_AVAILABLE
    const int dimN = A.getRows();
    const int numS = X.getCols();
    int signum;

    double *dataX = X.getWriteData();
    const double *dataB = B.getReadData();

    gsl_matrix *a = A;
    gsl_permutation *p = gsl_permutation_alloc(dimN);
    gsl_vector *b = gsl_vector_alloc(dimN);
    gsl_vector *x = gsl_vector_alloc(dimN);

    gsl_linalg_LU_decomp(a, p, &signum);

    for(int sist = 0; sist < numS; sist++)
        {
        for(int i = 0; i < dimN; i++)
            b->data[i] = dataB[i*numS + sist];

        gsl_linalg_LU_solve(a, p, b, x);

        for(int i = 0; i < dimN; i++)
            dataX[i*numS + sist] = x->data[i];
        }

    gsl_matrix_free(a);
    gsl_permutation_free(p);
    gsl_vector_free(b);
    gsl_vector_free(x);
#else
        qFatal("solveLinear: cannot use GSL methods if GSL library is not available.");
#endif
        }

void solveOverDetermined(const QVMatrix &A, QVMatrix &X, const QVMatrix &B)
    {
        std::cout << "solveOverDetermined DEPRECATED, use any of the following functions instead:\n"
                     "solveBySingularValueDecomposition\n"
                     "solveByQRDecomposition\n"
                     "(see QVision documentation for details):\n";

        Q_ASSERT(A.getCols() <= A.getRows());
    Q_ASSERT(A.getCols() == X.getRows());
    Q_ASSERT(A.getRows() == B.getRows());

#ifdef GSL_AVAILABLE
    const int dim1 = A.getRows();
    const int dim2 = A.getCols();
    const int numS = X.getCols();

    double *dataX = X.getWriteData();
    const double *dataB = B.getReadData();

    gsl_matrix *u = A;
    gsl_vector *s = gsl_vector_alloc(dim2);
    gsl_matrix *v = gsl_matrix_alloc(dim2, dim2);
    gsl_vector *workV = gsl_vector_alloc(dim2);
    gsl_matrix *workM = gsl_matrix_alloc(dim2,dim2);
    gsl_vector *b = gsl_vector_alloc(dim1);
    gsl_vector *x = gsl_vector_alloc(dim2);

    gsl_linalg_SV_decomp_mod(u, workM, v, s, workV);

    for(int sist = 0; sist < numS; sist++)
        {
        for(int i = 0; i < dim1; i++)
            b->data[i] = dataB[i*numS + sist];

        gsl_linalg_SV_solve(u, v, s, b, x);

        for(int i = 0; i < dim2; i++)
            dataX[i*numS + sist] = x->data[i];
        }

    gsl_matrix_free(u);
    gsl_vector_free(s);
    gsl_matrix_free(v);
    gsl_vector_free(workV);
    gsl_matrix_free(workM);
    gsl_vector_free(b);
    gsl_vector_free(x);
#else
        qFatal("solveLinear: cannot use GSL methods if GSL library is not available.");
#endif
        }

void solveHomogeneousLinear(const QVMatrix &A, QVector<double> &x)
    {
        std::cout << "solveHomogeneousLinear DEPRECATED, use solveHomogeneous function instead (see QVision documentation)."
                  << std::endl;

    QVMatrix U, V, S;
        SingularValueDecomposition(A, U, S, V/*, LAPACK_THIN_DGESDD*/);
        /* LAPACK_FULL_DGESDD, LAPACK_THIN_DGESVD, LAPACK_THIN_DGESDD */

    x = V.getCol(V.getCols()-1);
    }

// Adjust a line to given first and second order moments, and returns ratio of eigenvalues:
double homogLineFromMoments(double x,double y,double xx,double xy,double yy,double &a,double &b,double &c)
        {
    double a11=xx-x*x, a12=xy-x*y, a22=yy-y*y, temp, e1, e2, angle, cosangle, sinangle;

    // Validity check:
    temp = sqrt(a11*a11+4*a12*a12-2*a11*a22+a22*a22);
    e1 = a11+a22-temp;
    e2 = a11+a22+temp;
    if(e2<EPSILON)
        {
        /*std::cerr << " a11=" << a11 << " a12=" << a12 << " a22=" << a22
        << " x=" << x << " y=" << y << " xx=" << xx << " xy=" << xy << " yy=" << yy
        << ": Impossible moments in homogLineFromMoments!\n";*/
        return 1.0;
        }
    if(fabs(e1)/e2 > 0.9)
        {
        /*std::cerr << "Too high ratio of eigenvalues e1=" << e1 << "e2=" << e2 <<": No principal direction in homogLineFromMoments!\n";
        std::cerr << " a11=" << a11 << " a12=" << a12 << " a22=" << a22 << "\n";*/
        return fabs(e1)/e2;
        }

    if(fabs(a12)>EPSILON)
        angle = atan2(2*a12,a11-a22+temp);
    else
    if(a11>=a22)
        angle = 0;
    else
        angle = PI/2;
    if(angle < 0)
        angle += PI;
    cosangle = cos(angle); sinangle = sin(angle);

    //Standard deviation in perpendicular direction:
    //desv_perp = sqrt(fabs(a11+a22-temp)/2.0);
    a = -sinangle; b = cosangle; c = x*sinangle-y*cosangle;
    return fabs(e1)/e2;
    }

QVVector regressionLine(const QVMatrix &points)
    {
    /// @todo esto no funciona.
    double x = 0, y = 0, xx = 0, yy = 0, xy = 0;
    const int rows = points.getRows();

    for (int i = 0; i < rows; i++)
        {
        double xActual = points(i,0), yActual = points(i,1);
        x += xActual;
        y += yActual;
        xx += xActual*xActual;
        xy += xActual*yActual;
        yy += yActual*yActual;
        }

    x /= rows; y /= rows; xx /= rows; xy /= rows; yy /= rows;

    double a, b, c;
    if (homogLineFromMoments(x,y,xx,xy,yy,a,b,c))
        {
        QVVector result(3);
        result[0] = a; result[1] = b; result[2] = c;
        return result;
        }
    else
        return QVVector();
    }

// Initialization for the MKL DSS method requires some milliseconds.
// Avoid that 'cold-start' time in your code calling to this function
void cold_start_mkl_initialization(const int size)
    {
    // COLD START FOR MKL DSS ROUTINE
    #define COLD_START_MATRIX_SIZE	size
    QVMatrix A = QVMatrix::random(COLD_START_MATRIX_SIZE,COLD_START_MATRIX_SIZE);
    QVSparseBlockMatrix sparseM(1, 1, COLD_START_MATRIX_SIZE, COLD_START_MATRIX_SIZE);
    sparseM.setBlock(0, 0, A.transpose() * A);
    QVVector xInc(COLD_START_MATRIX_SIZE, 0.0), b = QVVector::random(COLD_START_MATRIX_SIZE);
    sparseSolve(sparseM, xInc, b, true, true, QVMKL_DSS, true, true, 10);
    }

// ---------------------------------------------------------------------------------------------------
// Deprecated

void SingularValueDecomposition(const QVMatrix &M, QVMatrix &U, QVVector &s, QVMatrix &V, const TQVSVD_Method method)
    {
    std::cout << "WARNING: 'SingularValueDecomposition' deprecated. Use 'singularValueDecomposition' instead." << std::endl;
    singularValueDecomposition(M, U, s, V, method);
    }

void SolveFromSingularValueDecomposition(const QVMatrix &U, const QVVector &s, const QVMatrix &V, QVMatrix &X, const QVMatrix &B)
    {
    std::cout << "WARNING: 'SolveFromSingularValueDecomposition' deprecated. Use 'solveFromSingularValueDecomposition' instead." << std::endl;
    solveFromSingularValueDecomposition(U, s, V, X, B);
    }

void SolveFromSingularValueDecomposition(const QVMatrix &U, const QVVector &s, const QVMatrix &V, QVVector &x, const QVVector &b)
    {
    std::cout << "WARNING: 'SolveFromSingularValueDecomposition' deprecated. Use 'solveFromSingularValueDecomposition' instead." << std::endl;
    solveFromSingularValueDecomposition(U, s, V, x, b);
    }

void SolveBySingularValueDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVSVD_Method method )
    {
    std::cout << "WARNING: 'SolveBySingularValueDecomposition' deprecated. Use 'solveBySingularValueDecomposition' instead." << std::endl;
    solveBySingularValueDecomposition(M, X, B, method);
    }

void SolveBySingularValueDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVSVD_Method method )
    {
    std::cout << "WARNING: 'SolveBySingularValueDecomposition' deprecated. Use 'solveBySingularValueDecomposition' instead." << std::endl;
    solveBySingularValueDecomposition(M, x, b, method);
    }

void SolveBySingularValueDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, QVMatrix &U, QVVector &s, QVMatrix &V, const TQVSVD_Method method)
    {
    std::cout << "WARNING: 'SolveBySingularValueDecomposition' deprecated. Use 'solveBySingularValueDecomposition' instead." << std::endl;
    solveBySingularValueDecomposition(M, X, B, U, s, V, method);
    }

void SolveBySingularValueDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, QVMatrix &U, QVVector &s, QVMatrix &V, const TQVSVD_Method method)
    {
    std::cout << "WARNING: 'SolveBySingularValueDecomposition' deprecated. Use 'solveBySingularValueDecomposition' instead." << std::endl;
    solveBySingularValueDecomposition(M, x, b, U, s, V, method);
    }

double SingularValueDecompositionResidual(const QVMatrix &M, const QVMatrix &U, const QVVector &s, const QVMatrix &V)
    {
    std::cout << "WARNING: 'SingularValueDecompositionResidual' deprecated. Use 'singularValueDecompositionResidual' instead." << std::endl;
    return singularValueDecompositionResidual(M, U, s, V);
    }

void SingularValues(const QVMatrix &M, QVVector &s, const TQVSV_Method method)
    {
    std::cout << "WARNING: 'SingularValues' deprecated. Use 'singularValues' instead." << std::endl;
    singularValues(M, s, method);
    }

double SingularValuesResidual(const QVMatrix &M, const QVVector &s)
    {
    std::cout << "WARNING: 'SingularValuesResidual' deprecated. Use 'singularValuesResidual' instead." << std::endl;
    return singularValuesResidual(M, s);
    }

void SolveFromCholeskyDecomposition(const QVMatrix &L, QVMatrix &X, const QVMatrix &B)
    {
    std::cout << "WARNING: 'SolveFromCholeskyDecomposition' deprecated. Use 'solveFromCholeskyDecomposition' instead." << std::endl;
    solveFromCholeskyDecomposition(L, X, B);
    }

void SolveFromCholeskyDecomposition(const QVMatrix &L, QVVector &x, const QVVector &b)
    {
    std::cout << "WARNING: 'SolveFromCholeskyDecomposition' deprecated. Use 'solveFromCholeskyDecomposition' instead." << std::endl;
    solveFromCholeskyDecomposition(L, x, b);
    }

void SolveByCholeskyDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVCholesky_Method method)
    {
    std::cout << "WARNING: 'SolveByCholeskyDecomposition' deprecated. Use 'solveByCholeskyDecomposition' instead." << std::endl;
    solveByCholeskyDecomposition(M, X, B, method);
    }

void SolveByCholeskyDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVCholesky_Method method)
    {
    std::cout << "WARNING: 'SolveByCholeskyDecomposition' deprecated. Use 'solveByCholeskyDecomposition' instead." << std::endl;
    solveByCholeskyDecomposition(M, x, b, method);
    }

void SolveByCholeskyDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, QVMatrix &L, const TQVCholesky_Method method)
    {
    std::cout << "WARNING: 'SolveByCholeskyDecomposition' deprecated. Use 'solveByCholeskyDecomposition' instead." << std::endl;
    solveByCholeskyDecomposition(M, X, B, L, method);
    }

void SolveByCholeskyDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, QVMatrix &L, const TQVCholesky_Method method)
    {
    std::cout << "WARNING: 'SolveByCholeskyDecomposition' deprecated. Use 'solveByCholeskyDecomposition' instead." << std::endl;
    solveByCholeskyDecomposition(M, x, b, L, method);
    }

void SolveFromLUDecomposition(const QVMatrix &P, const QVMatrix &L, const QVMatrix &U, QVMatrix &X, const QVMatrix &B)
    {
    std::cout << "WARNING: 'SolveFromLUDecomposition' deprecated. Use 'solveFromLUDecomposition' instead." << std::endl;
    solveFromLUDecomposition(P, L, U, X, B);
    }

void SolveFromLUDecomposition(const QVMatrix &P, const QVMatrix &L, const QVMatrix &U, QVVector &x, const QVVector &b)
    {
    std::cout << "WARNING: 'SolveFromLUDecomposition' deprecated. Use 'solveFromLUDecomposition' instead." << std::endl;
    solveFromLUDecomposition(P, L, U, x, b);
    }

void SolveByLUDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVLU_Method method)
    {
    std::cout << "WARNING: 'SolveByLUDecomposition' deprecated. Use 'solveByLUDecomposition' instead." << std::endl;
    solveByLUDecomposition(M, X, B, method);
    }

void SolveByLUDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVLU_Method method)
    {
    std::cout << "WARNING: 'SolveByLUDecomposition' deprecated. Use 'solveByLUDecomposition' instead." << std::endl;
    solveByLUDecomposition(M, x, b, method);
    }

void SolveByLUDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, QVMatrix &P, QVMatrix &L, QVMatrix &U, const TQVLU_Method method)
    {
    std::cout << "WARNING: 'SolveByLUDecomposition' deprecated. Use 'solveByLUDecomposition' instead." << std::endl;
    solveByLUDecomposition(M, X, B, P, L, U, method);
    }

void SolveByLUDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b,QVMatrix &P, QVMatrix &L, QVMatrix &U, const TQVLU_Method method)
    {
    std::cout << "WARNING: 'SolveByLUDecomposition' deprecated. Use 'solveByLUDecomposition' instead." << std::endl;
    solveByLUDecomposition(M, x, b, P, L, U, method);
    }

void SolveFromQRDecomposition(const QVMatrix &Q, const QVMatrix &R, QVMatrix &X, const QVMatrix &B)
    {
    std::cout << "WARNING: 'SolveFromQRDecomposition' deprecated. Use 'solveFromQRDecomposition' instead." << std::endl;
    solveFromQRDecomposition(Q, R, X, B);
    }

void SolveFromQRDecomposition(const QVMatrix &Q, const QVMatrix &R, QVVector &x, const QVVector &b)
    {
    std::cout << "WARNING: 'SolveFromQRDecomposition' deprecated. Use 'solveFromQRDecomposition' instead." << std::endl;
    solveFromQRDecomposition(Q, R, x, b);
    }

void SolveByQRDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, const TQVQR_Method method)
    {
    std::cout << "WARNING: 'SolveByQRDecomposition' deprecated. Use 'solveByQRDecomposition' instead." << std::endl;
    solveByQRDecomposition(M, X, B, method);
    }

void SolveByQRDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, const TQVQR_Method method)
    {
    std::cout << "WARNING: 'SolveByQRDecomposition' deprecated. Use 'solveByQRDecomposition' instead." << std::endl;
    solveByQRDecomposition(M, x, b, method);
    }

void SolveByQRDecomposition(const QVMatrix &M, QVMatrix &X, const QVMatrix &B, QVMatrix &Q, QVMatrix &R, const TQVQR_Method method)
    {
    std::cout << "WARNING: 'SolveByQRDecomposition' deprecated. Use 'solveByQRDecomposition' instead." << std::endl;
    solveByQRDecomposition(M, X, B, Q, R, method);
    }

void SolveByQRDecomposition(const QVMatrix &M, QVVector &x, const QVVector &b, QVMatrix &Q, QVMatrix &R, const TQVQR_Method method)
    {
    std::cout << "WARNING: 'SolveByQRDecomposition' deprecated. Use 'solveByQRDecomposition' instead." << std::endl;
    solveByQRDecomposition(M, x, b, Q, R, method);
    }

void EigenDecomposition(const QVMatrix &M, QVVector &lambda, QVMatrix &Q, const TQVEigenDecomposition_Method method)
    {
    std::cout << "WARNING: 'EigenDecomposition' deprecated. Use 'eigenDecomposition' instead." << std::endl;
    eigenDecomposition(M, lambda, Q, method);
    }

double EigenDecompositionResidual(const QVMatrix &M, const QVVector &lambda, const QVMatrix &Q)
    {
    std::cout << "WARNING: 'EigenDecompositionResidual' deprecated. Use 'eigenDecompositionResidual' instead." << std::endl;
    return eigenDecompositionResidual(M, lambda, Q);
    }

void EigenValues(const QVMatrix &M, QVVector &lambda, const TQVEigenValues_Method method)
    {
    std::cout << "WARNING: 'EigenValues' deprecated. Use 'eigenValues' instead." << std::endl;
    eigenValues(M, lambda, method);
    }

double EigenValuesResidual(const QVMatrix &M, const QVVector &lambda)
    {
    std::cout << "WARNING: 'EigenValuesResidual' deprecated. Use 'eigenValuesResidual' instead." << std::endl;
    return eigenValuesResidual(M, lambda);
    }

void SolveHomogeneous(const QVMatrix &A, QVector<double> &x, const TQVSVD_Method method)
    {
    std::cout << "WARNING: 'SolveHomogeneous' deprecated. Use 'solveHomogeneous' instead." << std::endl;
    solveHomogeneous(A, x, method);
    }

double SolveResidual(const QVMatrix &M, const QVMatrix &X, const QVMatrix &B)
    {
    std::cout << "WARNING: 'SolveResidual' deprecated. Use 'solveResidual' instead." << std::endl;
    return solveResidual(M, X, B);
    }

double SolveResidual(const QVMatrix &M, const QVVector &x, const QVVector &b)
    {
    std::cout << "WARNING: 'SolveResidual' deprecated. Use 'solveResidual' instead." << std::endl;
    return solveResidual(M, x, b);
    }

double SparseSolve(	const QVSparseBlockMatrix M, QVVector &x, const QVVector b, const bool isSymmetric, const bool isPosDefinite, const TQVSparseSolve_Method method,
            const bool start_from_x, const bool iters_or_resid, const int iters, const double resid, int &final_iter_count)
    {
    std::cout << "WARNING: 'SparseSolve' deprecated. Use 'sparseSolve' instead." << std::endl;
    return sparseSolve(M, x, b, isSymmetric, isPosDefinite, method, start_from_x, iters_or_resid, iters, resid, final_iter_count);
    }

void SolveHomogeneous(const QVSparseBlockMatrix &A, QVVector &x, const int maxIterations, const double minRelativeError, const TQVSparseSolve_Method method)
    {
    std::cout << "WARNING: 'SolveHomogeneous' deprecated. Use 'solveHomogeneous' instead." << std::endl;
    solveHomogeneous(A, x, maxIterations, minRelativeError, method);
    }

#ifdef GSL_AVAILABLE
// Internal use only. Fast function for homogeneous solving.
void solveHomogeneousEig(const QVMatrix &M, QVVector &result)
    {
    QVMatrix A = M.dotProduct(M,true,false);
    const int n = A.getCols();
    gsl_matrix m;
    m.size1 = m.size2 = m.tda = n;
    m.data = A.getWriteData();
    m.block = NULL;
    m.owner = 1;

    gsl_vector *eval = gsl_vector_alloc (n);
    gsl_matrix *evec = gsl_matrix_alloc (n, n);
    gsl_eigen_symmv_workspace *w = gsl_eigen_symmv_alloc (n);
    gsl_eigen_symmv (&m, eval, evec, w);
    gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_VAL_DESC);
    gsl_eigen_symmv_free (w);
    gsl_vector_free (eval);

    result = QVVector(n);
    for(int i = 0; i < n; i++)
        result[i] = gsl_matrix_get(evec,i,n-1);

    gsl_matrix_free (evec);
    }
#endif

