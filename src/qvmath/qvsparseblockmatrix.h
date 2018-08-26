/*
 *	Copyright (C) 2010, 2011, 2012. PARP Research Group.
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

#ifndef QVSPARSEBLOCKMATRIX_H
#define QVSPARSEBLOCKMATRIX_H

#include <QMap>
#include <qvmath/qvmatrix.h>

#ifdef MKL_AVAILABLE
  #include "mkl_dss.h"
#endif

/*!
@class QVSparseBlockMatrix qvmath/qvsparseblockmatrix.h QVSparseBlockMatrix
@brief Implementation of sparse block matrices.

Each sparse block matrix is implemented as a bidimensional array of @ref QVMatrix objects. The sparse matrices have two kind of indexes: major indexes, that access the bidimensional array, and minor indexes, that access elements in the matrix objects inside the cells of the array.

The following is an example sparse matrix of size \f$ 15 \times 12 \f$. It contains 12 blocks (or submatrices) of size \f$ 3 \times 5 \f$ (minor dimensions), arranged in an array of size \f$ 4 \times 3 \f$ (major dimensions):

@image html sparse-matrix.png

Such matrix can be created with the following code:

@code
QVSparseBlockMatrix sparseM(4,3,3,5);
@endcode

Initially, the matrix is created empty. To initialize the blocks that contain elements different from zero, we can use the method @ref setBlock:

@code
sparseM.setBlock(0, 0, QVMatrix::random(3,5));
sparseM.setBlock(0, 2, QVMatrix::random(3,5));
sparseM.setBlock(1, 1, QVMatrix::random(3,5));
sparseM.setBlock(2, 0, QVMatrix::random(3,5));
sparseM.setBlock(2, 2, QVMatrix::random(3,5));
sparseM.setBlock(3, 0, QVMatrix::random(3,5));
@endcode

The [] operator can substitute the @ref setBlock method. The previous code is equivalent to the following code:

@code
sparseM[0][0] = QVMatrix::random(3,5);
sparseM[0][2] = QVMatrix::random(3,5);
sparseM[1][1] = QVMatrix::random(3,5);
sparseM[2][0] = QVMatrix::random(3,5);
sparseM[2][2] = QVMatrix::random(3,5);
sparseM[3][0] = QVMatrix::random(3,5);
@endcode

However, it is recomendable to use the method @ref setBlock to initialize the contents of the blocks in the sparse matrices. The latter method performs several checks on the dimensions of the input matrices, and the ranges of the sparse matrix, to avoid invalid matrix assignments.

The previous code example initializes the non-zero blocks of the sparse matrix with matrices containing random values, but other matrices with compatible dimensions could of course be used as well.

We can convert the sparse matrix to a dense @ref QVMatrix and print it on the console:

@code
QVMatrix M = sparseM;
std::cout << "M = " << M << std::endl;
@endcode

The console output of the previous code will be the following:

@code
M = QVMatrix (12, 15)
[
    [ 0.3943 0.7682 0.5134 0.6069 0.4009 0.0000 0.0000 0.0000 0.0000 0.0000 0.8391 0.9727 0.8915 0.9493 0.3488 ]
    [ 0.7984 0.5539 0.9161 0.2428 0.1088 0.0000 0.0000 0.0000 0.0000 0.0000 0.2960 0.7713 0.3524 0.0860 0.0200 ]
    [ 0.1975 0.6288 0.7172 0.8041 0.2182 0.0000 0.0000 0.0000 0.0000 0.0000 0.5242 0.7699 0.9190 0.6632 0.0630 ]
    [ 0.0000 0.0000 0.0000 0.0000 0.0000 0.9706 0.7602 0.9318 0.3540 0.3303 0.0000 0.0000 0.0000 0.0000 0.0000 ]
    [ 0.0000 0.0000 0.0000 0.0000 0.0000 0.8509 0.6677 0.7209 0.1659 0.8933 0.0000 0.0000 0.0000 0.0000 0.0000 ]
    [ 0.0000 0.0000 0.0000 0.0000 0.0000 0.5397 0.0392 0.7385 0.8800 0.6866 0.0000 0.0000 0.0000 0.0000 0.0000 ]
    [ 0.5886 0.8147 0.9201 0.2810 0.2762 0.0000 0.0000 0.0000 0.0000 0.0000 0.1260 0.3831 0.2444 0.7450 0.2400 ]
    [ 0.8586 0.9109 0.8810 0.3074 0.4165 0.0000 0.0000 0.0000 0.0000 0.0000 0.7604 0.3686 0.7321 0.9501 0.7326 ]
    [ 0.9239 0.2158 0.4319 0.2261 0.9068 0.0000 0.0000 0.0000 0.0000 0.0000 0.9350 0.2322 0.7934 0.5215 0.9674 ]
    [ 0.7597 0.2046 0.1578 0.0540 0.1803 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 ]
    [ 0.1349 0.8196 0.2043 0.0723 0.3916 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 ]
    [ 0.0782 0.7555 0.1254 0.9230 0.8196 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 ]
]
@endcode

One very interesting thing to do with sparse matrices is, of course, solving (sparse) linear systems of equations involving a sparse matrix of coefficients. You can do that using the @ref SparseSolve function from the matrix algebra module of QVision. Here is an example, which solves the system \f$ C x = b \f$, with:

\f$ C = \left( \begin{array}{ccccc}
                9    & 1.5 & 6.0  & 0.75  & 3.0  \\
                1.5  & 0.5 & 0.0  & 0.0   & 0.0  \\
                6.0  & 0.0 & 12.0 & 0.0   & 0.0  \\
                0.75 & 0.0 & 0.0  & 0.625 & 0.0  \\
                3.0  & 0.0 & 0.0  & 0.0   & 16.0 \\
               \end{array} \right) \f$

and

\f$ b = \left( \begin{array}{c}
                1.0    \\
                2.0  \\
                3.0  \\
                4.0 \\
                5.0  \\
               \end{array} \right) \f$

Observe that the C matrix is symmetric and positive definite, in this example.

Here is the corresponding code (in this simple example, each individual subblock matrix is simply of size 1x1):

@code
#include <iostream>
#include <QVMatrix>
#include <QVVector>
#include <QVSparseBlockMatrix>

int main(int argc, char *argv[])
{
        QVSparseBlockMatrix C(5,5,1,1);

        C.setBlock(0,0,QVMatrix(1,1,9.0));
        C.setBlock(0,1,QVMatrix(1,1,1.5));
        C.setBlock(0,2,QVMatrix(1,1,6.0));
        C.setBlock(0,3,QVMatrix(1,1,0.75));
        C.setBlock(0,4,QVMatrix(1,1,3.0));
        C.setBlock(1,1,QVMatrix(1,1,0.5));
        C.setBlock(2,2,QVMatrix(1,1,12.0));
        C.setBlock(3,3,QVMatrix(1,1,0.625));
        C.setBlock(4,4,QVMatrix(1,1,16.0));

        QVVector x , b = QVVector() << 1.0 << 2.0 << 3.0 << 4.0 << 5.0 ;

        // First true stands for symmetric, second for positive definite matrix:
        sparseSolve(C, x, b, true , true, QVMKL_DSS);

        std::cout << "Vector b:" << b << "\n";
        std::cout << "Matrix C:" << C << "\n";
        std::cout << "Vector x:" << x << "\n";
}
@endcode

The solution vector x for this example is:

\f$ x = \left( \begin{array}{c}
                -326.333 \\
                983.0    \\
                163.417  \\
                398.0    \\
                61.5     \\
               \end{array} \right) \f$

Note that in this case only the upper triangular part of the C matrix has to be initialized (because it is symmetric, as indicated by the 'true' second argument to the @ref sparseSolve function). Also, the 'true' in the third argument indicates to the underlying solver that the C matrix is positive definite, a fact which can be used to accelerate computation.
@ingroup qvmath
*/
class QVSparseBlockMatrix: public QMap<int, QMap<int, QVMatrix> >
    {
    protected:
        int majorRows, majorCols, minorRows, minorCols;

    public:
        int blockCount;
        /// @brief Default constructor for the @ref QVSparseBlockMatrix class
                QVSparseBlockMatrix(): QMap<int, QMap<int, QVMatrix> >(),
                        majorRows(0), majorCols(0), minorRows(0), minorCols(0), blockCount(0)
                {

                }

        QVSparseBlockMatrix (const QVSparseBlockMatrix &other): QMap<int, QMap<int, QVMatrix> >(other),
                        majorRows(other.majorRows), majorCols(other.majorCols), minorRows(other.minorRows), minorCols(other.minorCols), blockCount(other.blockCount)
                {

                }

        /// @brief Create a sparse block matrix of a given size.
                ///
                /// This constructor creates a sparse matrix of size \f$ majorRows minorRows \times majorCols minorCols \f$. Every element of the matrix will
        /// contain the \f$ 0 \f$ value.
                ///
                /// @param majorRows Number of rows of block matrices.
                /// @param majorCols Number of columns of block matrices.
        /// @param minorRows Number of rows of the block matrices.
        /// @param minorCols Number of columns of the block matrices.
                QVSparseBlockMatrix(const int majorRows, const int majorCols, const int minorRows, const int minorCols): QMap<int, QMap<int, QVMatrix> >(),
                        majorRows(majorRows), majorCols(majorCols), minorRows(minorRows), minorCols(minorCols), blockCount(0)
                { }

        /// @brief Create a sparse block matrix from a dense matrix
                ///
                /// This constructor creates a sparse matrix of size \f$ (majorRows * minorRows) \times (majorCols * minorCols) \f$.
                /// The elements of the sparse matrix will be initialized with the contents of the matrix passed by
                /// parameter (adequately partitioned in blocks of the given size, and with any zero submatrix of the
                /// input matrix conveniently "supressed" from the internal representation).
                ///
                /// The following two identities must hold when calling this method (otherwise, it will fail):
                ///  - (other.getRows() / majorRows) * majorRows == other.getRows()
                ///  - (other.getCols() / majorCols) * majorCols == other.getCols()
                ///
                /// @param majorRows Number of rows of block matrices.
                /// @param majorCols Number of columns of block matrices.
        /// @param minorRows Number of rows of the block matrices.
        /// @param minorCols Number of columns of the block matrices.
                /// @param other Dense matrix containing the values to initialize the sparse matrix.
                QVSparseBlockMatrix(const int majorRows, const int majorCols, const QVMatrix &other): QMap<int, QMap<int, QVMatrix> >(),
                        majorRows(majorRows), majorCols(majorCols), minorRows(other.getRows() / majorRows), minorCols(other.getCols() / majorCols)
                {

                                if( (minorRows*majorRows != other.getRows()) || (minorCols*majorCols != other.getCols()) )
                                    {
                                    std::cout << "[QVSparseBlockMatrix] Error: tried to construct a sparse block matrix of incompatible sizes with original dense matrix." << std::endl
                                              << "\tSparse matrix number of blocks:\t" << majorRows << "x" << majorCols << std::endl
                                              << "\tDense matrix number of blocks:\t" << other.getRows() << "x" << other.getCols() << std::endl;
                                    exit(1);
                                    }

                                for(int i = 0; i < majorRows; i++)
                                        for(int j = 0; j < majorCols; j++)
                        {
                        QVMatrix M = other.getSubmatrix(i*minorRows, (i+1)*minorRows-1, j*minorCols, (j+1)*minorCols-1);
                        if (M != QVMatrix(minorRows, minorCols, 0.0))
                            operator[](i)[j] = M;
                        }
                }

                /// @brief Get majorRows from a sparse block matrix
                inline int getMajorRows() const {return majorRows;};

                /// @brief Get majorCols from a sparse block matrix
                inline int getMajorCols() const {return majorCols;};

                /// @brief Get minorRows from a sparse block matrix
                inline int getMinorRows() const {return minorRows;};

                /// @brief Get minorCols from a sparse block matrix
                inline int getMinorCols() const {return minorCols;};

        /// @brief Convert a sparse block matrix into an ordinary matrix
        operator QVMatrix () const
            {
                        QVMatrix result(majorRows * minorRows, majorCols * minorCols, 0.0);
                        /*for(int i = 0; i < majorRows; i++)
                                for(int j = 0; j < majorCols; j++)
                    if (operator[](i).contains(j))
                                                result.setSubmatrix(i*minorRows, j*minorCols, operator[](i)[j]);*/
                        foreach(int i, keys())
                            foreach(int j, operator[](i).keys())
                                result.setSubmatrix(i*minorRows, j*minorCols, operator[](i)[j]);
            return result;
            }

        QVSparseBlockMatrix transpose() const;

        /// @brief Set a data block
        ///
        /// You can set a block submatrix in the sparse matrix with this method.
                /// The following two lines of code are equivalent:
        ///
        /// @code
        /// QVSparseBlockMatrix M(10,20, 3, 3);
        /// [...]
        /// M[7][10] = QVMatrix::identity(3);
        /// M.setBlock(7,10, QVMatrix::identity(3));
        /// @endcode
        ///
                /// Setting the block of a sparse matrix using this method is safer than with the [] operators.
                /// This method will check the index ranges, and the correct size of the input matrix for the block.
        ///
                /// @param majorRow Row index of the block, inside the sparse matrix.
                /// @param majorCol Column index of the block, inside the sparse matrix.
        /// @param M Matrix with the contents of the block.
                void setBlock(const int majorRow, const int majorCol, const QVMatrix &M)
            {
                        if (majorRow < 0 || majorRow >= majorRows || majorCol < 0 || majorCol >= majorCols)
                {
                std::cout << "[QVSparseBlockMatrix::setBlock]: accessing a block outside the sparse matrix." << std::endl
                                        << "\tProvided block index:\t" << majorRow << "," << majorCol << std::endl
                                        << "\tValid block ranges for the matrix:\t" << majorRows << "x" << majorCols << std::endl;
                exit(1);
                }

            if (minorRows != M.getRows() || minorCols != M.getCols())
                {
                                std::cout << "[QVSparseBlockMatrix::setBlock] Error: tried to assing a matrix of incorrect dimensions to a block." << std::endl
                    << "\tMatrix size:\t" << M.getRows() << "x" << M.getCols() << std::endl
                    << "\tSparse matrix block size:\t" << minorRows << "x" << minorCols << std::endl;
                exit(1);
                }

            QMap<int, QVMatrix> & row = operator[](majorRow);
            if (!row.contains(majorCol))
                blockCount ++;

                        operator[](majorRow)[majorCol] = M;
            }

        /// @brief Gets a data block
        QVMatrix & getBlock(const int majorRow, const int majorCol)
            {
                        if (majorRow < 0 || majorRow >= majorRows || majorCol < 0 || majorCol >= majorCols)
                {
                std::cout << "[QVSparseBlockMatrix::getBlock] Error: accessing a block outside the sparse matrix." << std::endl
                                        << "\tProvided block index:\t" << majorRow << "," << majorCol << std::endl
                                        << "\tValid block ranges for the matrix:\t" << majorRows << "x" << majorCols << std::endl;
                exit(1);
                }

            QMap<int, QVMatrix> & row = operator[](majorRow);

            // If no submatrix is at the indexed block, create one filled with NULL values.
            if (!row.contains(majorCol))
                row[majorCol] = QVMatrix(minorRows, minorCols, 0.0);

            return row[majorCol];
            }

        /// @brief Evaluate if a block contains zero values.
        ///
        /// This function can be used to evaluate if a block is undefined in the block-sparse matrix.
        ///
        /// @return true if the block matrix is Null. This implies that every element of the block matrix is zero.
        ///	A false value on the output does not imply that the elements of the block matrix differ from zero in any case.
        bool isNullBlock(const int majorRow, const int majorCol) const
            {
                        if (majorRow < 0 || majorRow >= majorRows || majorCol < 0 || majorCol >= majorCols)
                {
                std::cout << "[QVSparseBlockMatrix::isNullBlock] Error: accessing a block outside the sparse matrix." << std::endl
                                        << "\tProvided block index:\t" << majorRow << "," << majorCol << std::endl
                                        << "\tValid block ranges for the matrix:\t" << majorRows << "x" << majorCols << std::endl;
                exit(1);
                }

            return !operator[](majorRow).contains(majorCol);
            }

        /*const QVMatrix & getBlock(const int majorRow, const int majorCol) const
            {
                        if (majorRow < 0 || majorRow >= majorRows || majorCol < 0 || majorCol >= majorCols)
                {
                std::cout << "ERROR: accessing a block outside the sparse matrix." << std::endl
                                        << "\tProvided block index:\t" << majorRow << "," << majorCol << std::endl
                                        << "\tValid block ranges for the matrix:\t" << majorRows << "x" << majorCols << std::endl;
                exit(1);
                }

            const QMap<int, QVMatrix> & row = operator[](majorRow);
            // @todo This operation should create a block of adequate dimensions in the sparse matrix if no block is found.
            if (!row.contains(majorCol))
                {
                std::cout << "ERROR: accessing a block which is NULL in the sparse matrix." << std::endl;
                exit(1);
                }

            return row[majorCol];
            }*/

        void printBlocks() const
            {
            std::cout << "Blocks for sparse matrix:" << std::endl;
                        for(int i = 0; i < majorRows; i++)
                {
                std::cout << "\t";
                                for(int j = 0; j < majorCols; j++)
                    if (operator[](i).contains(j))
                        std::cout << "[]";
                    else
                        std::cout << "<>";
                std::cout << std::endl;
                }
            }

                /// @brief List of non-zero blocks in a block-row
        ///
                /// This function returns a list of the blocks in a block-row of the sparse matrix which are non-zero.
        ///
        /// @param majorRow block-row index.
        QList<int> getBlockRowIndexes(const int majorRow) const
            {
            return operator[](majorRow).keys();
            }

                /// @brief Product operator for sparse block matrices
        ///
                /// The sparse block matrices must have compatible block sizes, and major sizes.
        ///
        /// @param other factor for the product operator.
        QVSparseBlockMatrix operator*(const QVSparseBlockMatrix &other) const		{ return dotProduct(other, false, false); };

        /// @brief Sparse block matrix-vector product
        ///
        /// @param vector vector to multiply by.
        QVVector operator*(const QVVector &vector) const	{ return dotProduct(vector, false); }

                /// @brief Dot product for sparse block matrices
        ///
                /// The sparse block matrices must have compatible block sizes, and major sizes.
        ///
        /// @param other factor for the product operator.
        QVSparseBlockMatrix dotProduct(const QVSparseBlockMatrix &other,
                    const bool transposeFirstOperand = false,
                    const bool transposeSecondOperand = false) const;

                /// @brief Dot product for sparse block matrices with vectors
        ///
                /// The sparse block matrix must have compatible block sizes, and major sizes, with the vecto size
        ///
        /// @param vector factor for the product operator.
        QVVector dotProduct(const QVVector &vector, const bool transposeMatrix = false) const;

        /// @brief Copy operator
        QVSparseBlockMatrix & operator=(const QVSparseBlockMatrix &other);

        /// @brief Set matrix to zero.
        void clear()		{ QMap<int, QMap<int, QVMatrix> >::clear(); }

        // @brief Gets the trace of the matrix.
        // @note this function works only on sparse matrices with square blocks.
        #ifndef DOXYGEN_IGNORE_THIS
        double trace()
            {
            // Evaluate the trace.
            double trace = 0.0;
            int count = 0;
            for(int k = 0; k < MIN(getMajorRows(),getMajorCols()); k++)
                {
                if (isNullBlock(k,k))
                    continue;

                const QVMatrix M = getBlock(k,k);
                if (M.getCols() < getMinorCols() || M.getRows() < getMinorRows())
                    {
                    std::cout << "ERROR: block in the diagonal is NULL." << std::endl;
                    exit(1);
                    }

                for (int j = 0; j < MIN(getMinorRows(), getMinorCols()); j++)
                    {
                    trace += M(j,j);
                    count++;
                    }
                }

            return trace;
            }
        #endif

                /// @brief Generates a random square sparse block matrix
                /// The sparse block matrix must have compatible block sizes, and major sizes, with the vecto size
                ///
                /// @param NB number of row (=column) blocks
                /// @param NB number of rows (=columns) by block
                /// @param NZProb probability of a block of being of different from zero (out of diagonal) in generated matrix
                /// @param symmetric if the matrix to be generated should be symmetric
                /// @param positive if the matrix to be generated should be positive definite
                /// @returns the generated sparse square block matrix
                static QVSparseBlockMatrix randomSquare(const int NB,const int N, const double NZProb,const bool symmetric=true,const bool positive=true);
    };

#ifndef DOXYGEN_IGNORE_THIS
// Internal class: Pardiso sparse matrix format (for solving sparse systems using MKL DSS):
class MKLPardisoSparseFormat
    {
    public:
        MKLPardisoSparseFormat(const QVSparseBlockMatrix qvspmatrix, bool isSymmetric);
        MKLPardisoSparseFormat(): majorRows(0), majorCols(0), minorRows(0), minorCols(0), nRows(0), nCols(0), nNonZeros(0), rowIndex(NULL), columns(NULL), values(NULL)
            {};

        ~MKLPardisoSparseFormat();
        int majorRows, majorCols, minorRows, minorCols;
        int nRows; // Total number of rows.
        int nCols; // Total number of cols.
        int nNonZeros; // Total number of non zero elements.
                #ifdef MKL_AVAILABLE
            _INTEGER_t *rowIndex; // rowIndex array (see MKL Pardiso sparse format).
            _INTEGER_t *columns;  // columns arrays (see MKL Pardiso sparse format).
            _DOUBLE_PRECISION_t *values;// values arrays (see MKL Pardiso sparse format).
        #else
            int *rowIndex; // rowIndex array (see MKL Pardiso sparse format).
            int *columns;  // columns arrays (see MKL Pardiso sparse format).
            double *values;// values arrays (see MKL Parddiso sparse format).
        #endif

                /// @brief Get majorRows from a sparse block matrix
                inline int getMajorRows() const {return majorRows;};

                /// @brief Get majorCols from a sparse block matrix
                inline int getMajorCols() const {return majorCols;};

                /// @brief Get minorRows from a sparse block matrix
                inline int getMinorRows() const {return minorRows;};

                /// @brief Get minorCols from a sparse block matrix
                inline int getMinorCols() const {return minorCols;};
    };

#ifdef MKL_AVAILABLE
void squareSymmetricSparseMatrixToPardisoFormat(const QVSparseBlockMatrix &qvspmatrix, MKLPardisoSparseFormat &pardiso);
#endif

#endif


#endif
