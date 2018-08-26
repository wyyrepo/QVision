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

/// @file qvmatrix.h
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#ifndef QVMATRIX_H
#define QVMATRIX_H

#include <iostream>
#include <QVQuaternion>
#include <QV3DPointF>
#include <qvmath.h>
#include <qvmath/qvblasdatabuffer.h>

#ifdef QVOPENCV
#include <opencv/cv.h>
#endif

#ifdef QVOCTAVE
#include <octave/oct.h>
#endif

#ifdef _MSC_VER
#ifdef max
#undef max
#endif // max

#ifdef min
#undef min
#endif // min
#endif // _MSC_VER

/*class QVArrayIndex
    {
    public:
        const QVMatrix *matrix;
        int row, col;
        QVArrayIndex(const QVMatrix &matrix, const int col): matrix(&matrix), row(-1), col(col) { };
    };*/

/*!
@class QVMatrix qvmath/qvmatrix.h QVMatrix
@brief Implementation of numerical matrices.

@see @ref MatricesAndVectors

@ingroup qvmath
*/
class QVMatrix
    {
    public:

        /// @brief Matrix types
        enum MatrixType
            {
            /// General matrix.
            General = 0x00,
            /// Symmetrix matrices.
            Symmetric = 0x01,
            /// Upper triangular matrix.
            UpperTriangular = 0x2,
            /// Lower triangular matrix.
                        LowerTriangular = 0x03,
                        /// Diagonal matrix.
                        Diagonal = 0x04,
                        /// Permutation matrix.
                        PermutationMatrix = 0x05
                        };

        /* Dot product for triangular matrices
        void dotProductLowerTriangular(const QVMatrix &tr, QVMatrix &A)
            {
            const int	m = A.getRows(), n = A.getCols();
            QVMatrix result(m, n);
            cblas_dtrmm(CblasRowMajor, CblasLeft, CblasLower, CblasTrans, CblasNonUnit, m, n, 1.0, tr.getReadData(), tr.getCols(), A.getWriteData(), A.getCols());
            }*/

        // Constructors
        /// @brief Default constructor
        ///
        /// By default, it constructs a 1x1 matrix.
        ///
        QVMatrix();

        /// @brief Copy constructor.
        ///
        /// Creates a matrix object copying the content from a given one.
        /// @param matrix matrix to be copied.
        QVMatrix(const QVMatrix &matrix);

        /// @brief Dimensional constructor
        ///
        /// Creates a new matrix of the specified dimensions.
        ///
        /// @param rows number of rows for the new matrix.
        /// @param cols number of rows for the new matrix.
        /// @param data pointer to the data, stored in row mayor order. If no pointer, or the NULL value, is provided,
        QVMatrix(const int rows, const int cols, const double *data = NULL);

        /// @brief Dimensional constructor
        ///
        /// Creates a new matrix of the specified dimensions.
        ///
        /// @param rows number of rows for the new matrix.
        /// @param cols number of rows for the new matrix.
        /// @param data Vector containing the data, in row mayor order.
        QVMatrix(const int rows, const int cols, const QVVector &data);

        /// @brief Dimensional constructor with default value
        ///
        /// Creates a new matrix of the specified dimensions, and with each one of its cells containing a provided value.
        ///
        /// @param rows number of rows for the new matrix.
        /// @param cols number of rows for the new matrix.
        /// @param value default value to set the elements of the matrix.
        QVMatrix(const int rows, const int cols, const double value);

        /// @brief Rotation matrix constructor
        ///
        /// Creates a rotation matrix from a quaternion.
        ///
        /// @param quaternion quaternion containing the rotation.
        /// @see QVQuaternion::toRotationMatrix()
        QVMatrix(const QVQuaternion &quaternion);

        /// @brief Copy constructor for gsl_matrix
        ///
        /// @param matrix matrix to be copied
        /// @warning This constructor requires compatibility with the GSL library
        #ifdef GSL_AVAILABLE
        QVMatrix(const gsl_matrix *matrix);
        #endif

        /// @brief OpenCV matrix conversion constructor
        ///
        /// This function creates a matrix importing the contents of an OpenCV matrix.
        ///
        /// @warning The OpenCV compatibility option must be enabled at the QVision library compilation to use this constructor
        /// @param cvMatrix pointer to OpenCV matrix
        #ifdef QVOPENCV
        QVMatrix(const CvMat *cvMatrix);
        #endif

        /// @brief Converts the matrix to an OpenCV matrix structure
        ///
                /// This function creates a new CvMat object with the same dimensions and content of the actual matrix.
        ///
        /// @param cvMatType OpenCV type of the elements of the new matrix. Actually two types are valid as parameters:
        ///  - CV_32F
        ///  - CV_64F
        ///
        /// @note The OpenCV compatibility option must be enabled at the QVision library compilation to use this method
        /// @see operator CvMat *()
        #ifdef QVOPENCV
        CvMat *toCvMat(const int cvMatType = CV_64F) const;
        #endif

        /// @brief Converts the matrix to an OpenCV matrix structure
        ///
                /// This function creates a new CvMat object with the same dimensions and content than the actual matrix.
        /// @note The OpenCV compatibility option must be enabled at the QVision library compilation to use this operator
        /// @see toCvMat()
        #ifdef QVOPENCV
        operator CvMat *() const	{ return toCvMat(); }
        #endif

        /// @brief Octave matrix conversion constructor
        ///
        /// This function creates a matrix importing the contents of an Octave matrix.
        ///
        /// @warning The Octave compatibility option must be enabled at the QVision library compilation to use this constructor
        /// @param cvMatrix pointer to OpenCV matrix
        #ifdef QVOCTAVE
        QVMatrix(const Matrix octMatrix);
        #endif

        /// @brief Converts the matrix to an Octave library matrix structure
        ///
                /// This function creates a new Octave matrix object with the same dimensions and content than the actual matrix.
        ///
        /// @warning The Octave compatibility option must be enabled at the QVision library compilation to use this method
        /// @see operator Matrix ()
        #ifdef QVOCTAVE
        Matrix toOctaveMat() const;
        #endif

        /// @brief Converts the matrix to an Octave library matrix structure
        ///
                /// This function creates a new Octave matrix object with the same dimensions and content than the actual matrix.
        /// @warning The Octave compatibility option must be enabled at the QVision library compilation to use this operator
        /// @see toOctaveMat()
        #ifdef QVOCTAVE
        operator Matrix () const	{ return toOctaveMat(); }
        #endif

        /// @brief Vector to matrix constructor
        ///
        /// Creates a row or column matrix from a vector.
        ///
        /// @param vector vector to convert to matrix type.
        /// @param rowVector if true, creates a row matrix from the vector, else creates a column matrix from it.
        QVMatrix(const QVVector &vector, const bool rowVector = true);

        /// @brief Constructor from a list of QVVectors
        ///
        /// Creates a new matrix from a list of row QVVectors.
        ///
        /// @param vectorList list of row vectors.
        QVMatrix(const QList<QVVector> &vectorList);

        /// @brief Constructor from a list of QVectors
        ///
        /// Creates a new matrix from a list of row QVectors.
        ///
        /// @param vectorList list of row vectors.
        QVMatrix(const QList< QVector<double> > &vectorList);

        /// @brief Constructor from a list of QPointF
        ///
        /// Creates a new matrix from a list of points
        ///
        /// @param pointList list of points.
        QVMatrix(const QList<QPointF> &pointList);

        /// @brief Convert to a list of QVVectors operator
        ///
        // Creates a new list of row QVVectors from a matrix
        operator QList<QVVector> () const
            {
            QList<QVVector> list;
            for (int n = 0; n < getRows(); n++)
                list.append(getRow(n));
            return list;
            }

        /// @brief Convert to a list of QVectors operator
        ///
        // Creates a new list of row QVectors from a matrix
        operator QList< QVector<double> > () const
            {
            QList< QVector<double> > list;
            for (int n = 0; n < getRows(); n++)
                list.append(getRow(n));
            return list;
            }

        /// @brief Convert to a gsl_matrix * operator
        ///
        /// Creates a new gsl_matrix * from a matrix
        /// @warning This constructor requires compatibility with the GSL library
        #ifdef GSL_AVAILABLE
        operator gsl_matrix * () const;
            /*{
            gsl_matrix *result = gsl_matrix_alloc(rows, cols);
            for(int i = 0; i < rows; i++)
                for(int j = 0; j < cols; j++)
                    gsl_matrix_set(result, i, j, operator()(i, j));
            return result;
            }*/
        #endif

        /// @brief Copy operator
        ///
        /// @param matrix matrix to be copied.
        QVMatrix & operator=(const QVMatrix &matrix);

        // Matrix-matrix operators

        /// @brief Matrix-matrix equality operator
        ///
        /// @param matrix term for the compare operation.
        /// @return true if the given matrix has same dimensions and equal content of the data buffer, else false.
        /// @see equals
        bool operator==(const QVMatrix &matrix) const			{ return equals(matrix);	};

        /// @brief Matrix-matrix incremental operator
        ///
        /// @param matrix addendum to the actual matrix
        /// @return true if the given matrix has same dimensions and equal content of the data buffer, else false.
        /// @see equals
        QVMatrix & operator+=(const QVMatrix &matrix)
            {
            inlineAddition(matrix);
            return *this;
            };

        /// @brief Matrix-matrix unequality operator
        ///
        /// @param matrix term for the compare operation.
        /// @return false if the given matrix has same dimensions and equal content of the data buffer, else true.
        /// @see equals
        bool operator!=(const QVMatrix &matrix) const			{ return !equals(matrix);	};

        /// @brief Matrix-matrix product operator
        ///
        /// @param matrix factor for the product operation.
        /// @see matrixProduct
        QVMatrix operator*(const QVMatrix &matrix) const		{ return dotProduct(matrix, false, false); 	};

        /// @brief Matrix-matrix division
        ///
        /// The following expression:
        ///
        ///	X = A / B
        ///
        /// is equivalent to this one
        ///
        ///	X = A * pseudoInverse(B)
        ///
        /// With the difference that the pseudoinverse matrix for <i>B</i> is not directly computed. Instead, the
        /// matrix equation:
        ///
        ///	X * B = A
        ///
        /// is solved for the <i>X</i> term. This leads to more stable and efficient results than using the pseudo inverse.
        ///
        /// this operator gets X from:
        ///
        ///	X = A / B	->	X * B = A	->	B' * X' = A'
        ///
        /// using a linear system resolution based on a LU decomposition over A.
        ///
                /// @warning This operator requires compatibility with the GSL library.
        /// @param matrix factor for the operation.
                /// @see matrixDivide(const QVMatrix &) const
                #ifdef QVMATRIXALGEBRA_AVAILABLE
        QVMatrix operator/(const QVMatrix &matrix) const		{ return matrixDivide(matrix); 	};
                #endif

        /// @brief Matrix-matrix addition operator
        ///
        /// @param matrix term for the operation.
        /// @see addition
        QVMatrix operator+(const QVMatrix &matrix) const		{ return addition(matrix); 	};

        /// @brief Matrix-matrix substraction operator
        ///
        /// @param matrix subtrahend for the operation.
        /// @see substract
        QVMatrix operator-(const QVMatrix &matrix) const		{ return substract(matrix); 	};

        /// @brief Obtains the additive inverse of the matrix
        ///
        /// Obtains a matrix changing the sign of its elements.
        ///
        /// @see substract
        QVMatrix operator-() const					{ return operator*(-1.0); 	};

        // Matrix-scalar operators

        /// @brief Matrix-scalar product
        ///
        /// @param value factor for the operation.
        /// @see scalarProduct
        QVMatrix operator*(const double value) const			{ return scalarProduct(value); 	};

        /// @brief Matrix-scalar division operator
        ///
        /// @param value divider for the operation.
        /// @see scalarDivide
        QVMatrix operator/(const double value) const			{ return scalarDivide(value); 	};

        /// @brief Matrix-scalar addition
        ///
        /// @param value addendum for the operation.
        /// @see scalarAddition
        QVMatrix operator+(const double value) const			{ return scalarAdd(value); 	};

        /// @brief Matrix-scalar substraction operator
        ///
        /// @param value value to substract.
        /// @see scalarSubstraction
        QVMatrix operator-(const double value) const			{ return scalarSubstract(value); 	};

        // Matrix-vector operators

        /// @brief Matrix-vector product
        ///
        /// @param vector vector to multiply by.
        QVVector operator*(const QVVector &vector) const	{ return dotProduct(vector, false);	};

        // Composition operators

        /// @brief Appends matrices vertically
        ///
        /// Considering two matrix objects \f$ A \f$ and \f$ B \f$, this method returns the following matrix object:
        ///
        /// \f$ A.verticalAppend(B) = \left[ \begin{array}{c} A \\ B \end{array} \right] \f$
        ///
        /// @param matrix matrix to be appended
        /// @see operator&()
        QVMatrix verticalAppend(const QVMatrix &matrix) const;

        // Composition operators
        /// @brief Appends matrices horizontally
        ///
        /// Considering two matrix objects \f$ A \f$ and \f$ B \f$, this method returns the following matrix object:
        ///
        /// \f$ A.horizontalAppend(B) = \left[ A | B \right] \f$
        ///
        /// @param matrix matrix to be appended
        /// @see operator|()
        QVMatrix horizontalAppend(const QVMatrix &matrix) const;

        /// @brief Appends matrices vertically
        ///
        /// Considering two matrix objects \f$ A \f$ and \f$ B \f$, this operator returns the following matrix object:
        ///
        /// \f$ A \& B = \left[ \begin{array}{c} A \\ B \end{array} \right] \f$
        ///
        /// @param matrix matrix to be appended
        /// @see verticalAppend()
        QVMatrix operator&(const QVMatrix &matrix) const	{ return verticalAppend(matrix); };

        /// @brief Appends matrices horizontally
        ///
        /// Considering two matrix objects \f$ A \f$ and \f$ B \f$, this operator returns the following matrix object:
        ///
        /// \f$ A | B = \left[ A | B \right] \f$
        ///
        /// @param matrix matrix to be appended
        /// @see horizontalAppend()
        QVMatrix operator|(const QVMatrix &matrix) const	{ return horizontalAppend(matrix); };

        /// @brief Appends vector to matrix vertically
        ///
        /// Considering a matrix object \f$ A \f$ and a vector object \f$ \mathbf{v} \f$, this operator returns the following matrix object:
        ///
        /// \f$ A \& v = \left[ \begin{array}{c} A \\ \mathbf{v} \end{array} \right] \f$
        ///
        /// @param vector vector to be appended
        /// @see verticalAppend()
        QVMatrix operator&(const QVVector &vector) const	{ return verticalAppend(QVMatrix(vector)); };

        /// @brief Appends vector to matrix horizontally
        ///
        /// Considering a matrix object \f$ A \f$ and a vector object \f$ \mathbf{v} \f$, this operator returns the following matrix object:
        ///
        /// \f$ A | v = \left[ A | \mathbf{v} \right] \f$
        ///
        /// @param vector vector to be appended
        /// @see horizontalAppend()
        QVMatrix operator|(const QVVector &vector) const	{ return horizontalAppend(QVMatrix(vector).transpose()); };

        // Operation methods

        /// @brief Element access operator
        ///
        /// @param row main index value for data access
        /// @param col secondary index value for data access
        inline double &operator()(const int row, const int col)
            { return data->getWriteData()[row*cols + col]; }

        /// @brief Overloaded version of element access operator
        ///
        /// @param row main index value for data access
        /// @param col secondary index value for data access
        inline double operator()(const int row, const int col) const
            { return data->getReadData()[row*cols + col]; }

        /// @brief Gets the size of the data array.
        ///
        /// This returns the number of elements in the matrix.
        /// @return the product of the sizes of all the indexes in the matrix.
        int getDataSize()			const	{ return cols*rows; }

        /// @brief Gets a read-only reference to the data buffer of the matrix
        ///
        /// @return a constant pointer to the data buffer of the matrix
        const double *getReadData()		const	{ return data->getReadData(); }

        /// @brief Gets a reference of the data buffer of the matrix for read and write accesses
        ///
        /// @return a pointer to the data buffer of the matrix
        double *getWriteData()				{ return data->getWriteData(); }

        /// @brief Change the order of the indexes in the matrix.
        ///
        /// This function reorders the indexes of the matrix.
        QVMatrix transpose() const;

        /// @brief Sets every element of the matrix to a given value.
        ///
        /// @param value value to set elements in the matrix
        void set(const double value);

        // Matrix-matrix operations

        /// @brief Matrix-matrix equality operator
        ///
        /// @param matrix term for the compare operation.
        /// @return true if the given matrix has same dimensions and equal content of the data buffer, else false.
        /// @see operator==(const QVMatrix &) const
        /// @see operator!=(const QVMatrix &) const
        bool equals(const QVMatrix &matrix) const;

        /// @brief Matrix-matrix product
        ///
        /// @param matrix second operator for the multiplication.
        /// @see operator*(const QVMatrix &) const
        QVMatrix dotProduct(const QVMatrix &matrix, const bool transposeFirstOperand = false, const bool transposeSecondOperand = false) const;

        /// @brief Matrix-vector product
        ///
        /// @param vector second operator for the multiplication.
        /// @see operator*(const QVMatrix &) const
        QVVector dotProduct(const QVVector &vector, const bool transposeMatrix = false) const;

        /// @brief Matrix-matrix element product
        ///
        /// This method returns a matrix containing the product of the elements at the corresponding cells of the actual matrix and
        /// the one provided as the input parameter.
        ///
        /// @param matrix second operator for the multiplication.
        QVMatrix elementProduct(const QVMatrix &matrix) const;

        /// @brief Matrix-matrix division
        ///
        /// This function solves the <i>X</i> term from the following matrix equation:
        ///	<center>X A = B</center>
        /// where <i>A</i> and <i>B</i> are respectively the actual matrix, and the one given by parameter.
        /// This is equivalent to using the following expression for <i>X</i>:
        ///	<center>X = B A<sup>-1</sup></center>
        /// but with a faster method returning a more stable result.
        ///
		
        /// @param matrix factor for the operation.
        /// @see operator/(const QVMatrix &) const
                #ifdef QVMATRIXALGEBRA_AVAILABLE
        QVMatrix matrixDivide(const QVMatrix &matrix) const;
                #endif
		/// @brief Triangular system solving (vector of RHS)
		///
		/// This function solves the <i>x</i> term from the following equation:
		///	<center>L x = b</center>
		/// where <i>L</i> and <i>b</i> are respectively the actual matrix (which is triangular),
		/// and the rhs vector given by parameter.
		///
		/// @warning This method requires compatibility with the GSL library.
		/// @param b vector for the right hand side (input).
		/// @param x vector with the solution (output).
		void triangularSolve(const QVVector &b, QVVector &x, bool transposed = false,
				         bool unit_diagonal = false) const;

		/// @brief Triangular system solving (matrix of RHS)
		///
		/// This function solves the <i>X</i> term from the following matrix equation:
		///	<center>L X = B</center>
		/// where <i>L</i> and <i>B</i> are respectively the actual matrix (which is triangular),
		/// and the one given by parameter.
		///
		/// @warning This method requires compatibility with the GSL library.
		/// @param B vector for the right hand side (input).
		/// @param X vector with the solution (output).
		#ifdef BLAS_AVAILABLE
		void triangularSolve(const QVMatrix &B, QVMatrix &X, bool transposed = false,
				             bool unit_diagonal = false, bool left = true) const;
		#endif

        /// @brief Computes the inverse of the matrix.
		/// @warning This method requires compatibility with the GSL library.
		#ifdef QVMATRIXALGEBRA_AVAILABLE
		QVMatrix inverse() const;
		#endif

        /// @brief Computes the determinant of the matrix.
		/// @warning This method requires compatibility with the GSL library.
		#ifdef QVMATRIXALGEBRA_AVAILABLE
		double det() const;
		#endif

        /// @brief Obtains the mean vector for the column vectors in the matrix
        QVVector meanCol() const;

        /// @brief Matrix-matrix addition
        ///
        /// @param matrix operand for the add operation.
        /// @see operator+(const QVMatrix &) const
        QVMatrix addition(const QVMatrix &matrix) const;

        /// @brief Matrix-matrix addition
        ///
        /// @param matrix operand for the add operation.
        /// @see operator+=(const QVMatrix &) const
        void inlineAddition(const QVMatrix &matrix);

        /// @brief Matrix-matrix substraction
        ///
        /// @param matrix subtrahend for the operation.
        /// @see operator-(const QVMatrix &) const
        QVMatrix substract(const QVMatrix &matrix) const;

        // Matrix-scalar operations

        /// @brief Matrix-scalar division
        ///
        /// @param value scalar value to use in the operation.
        /// @see operator/(const double) const
        QVMatrix scalarDivide(const double value) const;

        /// @brief Matrix-scalar product
        ///
        /// @param value factor for the operation.
        /// @see operator*(const double) const
        QVMatrix scalarProduct(const double value) const;

        /// @brief Matrix-scalar addition
        ///
        /// @param value summand for the operation.
        /// @see operator+(const double) const
        QVMatrix scalarAdd(const double value) const;

        /// @brief Matrix-scalar substraction
        ///
        /// @param value value to substract.
        /// @see operator-(const double) const
        QVMatrix scalarSubstract(const double value) const;

        /// @brief Gets the <a href="http://en.wikipedia.org/wiki/Norm_%28mathematics%29">norm<sub>2</sub></a> for matrix.
        ///
        /// The resulting value will be the square root of the following sumatory:
        ///
        /// \f$ \|A\|_2 := \sqrt{ \sum |a_{ij}|^2 } \f$
        ///
        /// where \f$ a_{ij} \f$ are the elements of the matrix \f$ A \f$.
        /// @return norm-2 of the matrix.
        double norm2() const;

        /// @brief Gets the <a href="http://en.wikipedia.org/wiki/Trace_(linear_algebra)">trace</a> of the matrix.
        ///
        /// The trace of the matrix is the sum of the diagonal elements:
        ///
        /// \f$ \mathrm{tr}(A) = a_{11} + a_{22} + \dots + a_{nn}=\sum_{i=1}^{n} a_{i i} \f$
        ///
        /// where \f$ a_{ij} \f$ are the elements of the matrix \f$ A \f$.
        /// @return trace of the matrix.
        double trace() const;

        /// @brief Checks whether the matrix contains a NaN value or not.
        ///
        /// @return true if any of the values contained in the matrix is a NaN, false otherwise.
        bool containsNaN()	const;

        /// @brief Checks whether the matrix contains an infinite value or not.
        ///
        /// @return true if any of the values contained in the matrix is infinite, false otherwise.
        bool containsInf()	const;

        /// @brief Checks whether the matrix is a diagonal matrix or not.
        ///
        /// @return true if any of the values outside of the matrix diagonal differs from zero, false otherwise.
        bool isDiagonal()	const;

        /// @brief Homogeneous normalization for rows of the matrix
        ///
        /// @todo explain homogeneous normalization
        ///
        /// @return norm-2 of the matrix.
        QVMatrix rowHomogeneousNormalize() const;

        /// @brief Get width of the matrix.
        ///
        /// @return number of columns for the matrix.
        int getCols() const	{ return cols; }

        /// @brief Get height of the matrix.
        ///
        /// @return number of rows for the matrix.
        int getRows() const	{ return rows; }

        /// @brief Get type of the matrix.
        ///
        /// See documentation for enum @ref MatrixType. This matrix feature must nowadays be set <i>by handi</i>.
        /// In a future, the matrix type will be detected when certain matrix operations and decopositions will be performed.
        ///
        /// @return Matrix type. See documentation for enum @ref MatrixType.
        MatrixType getType() const	{ return type; }

        /// @brief Set type of the matrix.
        ///
        /// See documentation for enum @ref MatrixType. This matrix feature must nowadays be set <i>by handi</i>.
        /// In a future, the matrix type will be detected when certain matrix operations and decopositions will be performed.
        ///
        /// @return number of columns for the matrix.
        void setType(MatrixType type)	{ this->type = type; }

        /// @brief Get submatrix composed by given column range
        ///
        /// @param firstCol first column to be included in the submatrix.
        /// @param lastCol last column to be included in the submatrix.
        /// @return Submatrix containing the columns in the specificated range
        const QVMatrix getCols(const int firstCol, const int lastCol) const
            {
            Q_ASSERT(-1 < firstCol);
            Q_ASSERT(lastCol < getCols());
            Q_ASSERT(firstCol <= lastCol);

            QVMatrix result(getRows(), lastCol - firstCol + 1);
            for (int i = 0; i < getRows(); i++)
                for (int j = firstCol; j <= lastCol; j++)
                    result(i,j-firstCol) = operator()(i,j);
            return result;
            }

        /// @brief Get submatrix composed by given row range
        ///
        /// @param firstRow first row to be included in the submatrix.
        /// @param lastRow last row to be included in the submatrix.
        /// @return Submatrix containing the rows in the specificated range
        const QVMatrix getRows(const int firstRow, const int lastRow) const
            {
            Q_ASSERT(-1 < firstRow);
            Q_ASSERT(lastRow < getRows());
            Q_ASSERT(firstRow <= lastRow);

            QVMatrix result(lastRow - firstRow + 1, getCols());
            for (int i = firstRow; i <= lastRow; i++)
                for (int j = 0; j < getCols(); j++)
                    result(i-firstRow,j) = operator()(i,j);
            return result;
            }

        // Access operations

        /// @brief Gets a row of the matrix
        ///
        /// @param row row number, a value within [0, r-1], for a matrix with 'r' rows
        /// @returns a vector containing the values of the row
        const QVVector getRow(const int row) const;

        /// @brief Sets a row of the matrix
        ///
        /// @param row row number, a value within [0, r-1], for a matrix with 'r' rows
        /// @param vector a vector containing the values for the row
        void setRow(const int row, QVVector vector);

        /// @brief Sets a row of the matrix
        ///
        /// @param row row number, a value within [0, r-1], for a matrix with 'r' rows
        /// @param vector a vector containing the values for the row
        void setRow(const int row, QVector<double> vector);

        /// @brief Gets a column of the matrix
        ///
        /// @param col column number, a value within [0, c-1], for a matrix with 'c' columns
        /// @returns a vector containing the values of the column
        const QVVector getCol(const int col) const;

        /// @brief Sets a column of the matrix
        ///
        /// @param col column number, a value within [0, c-1], for a matrix with 'c' columns
        /// @param vector a vector containing the values for the column
        void setCol(const int col, QVVector vector);

        /// @brief Gets a submatrix from a matrix
        ///
        /// @param firstCol first column number for the submatrix
        /// @param firstRow first row number for the submatrix
        /// @param lastCol last column number for the submatrix
        /// @param lastRow last row number for the submatrix
        /// @returns a submatrix of size (lastRow - firstRow + 1)x(lastCol - firstCol + 1) containing the corresponding elements from the original matrix.
        const QVMatrix getSubmatrix(const int firstRow, const int lastRow, const int firstCol, const int lastCol) const;

        /// @brief Sets a submatrix from a matrix
        ///
        /// @param row first column number for the submatrix
        /// @param col first row number for the submatrix
        /// @param M Submatrix
        void setSubmatrix(const int row, const int col, const QVMatrix &M);

                /// @brief Gets a matrix with reversed rows (bottom to top).
                ///
                /// @returns reversed matrix.
                QVMatrix reversedRows() const;

                /// @brief Gets a matrix with reversed columns (right to left).
                ///
                /// @returns reversed matrix.
                QVMatrix reversedCols() const;

        /// @brief Gets the diagonal of the matrix
        ///
        /// @returns a vector containing the values of the diagonal
        const QVVector diagonal() const;

        // Misc matrices

        /// @brief Creates an identity matrix
        ///
        /// @param size number of cols and rows for the identity matrix
        static QVMatrix identity(const int size);

        /// @brief Creates an intrinsic camera calibration matrix
        ///
        /// This function returns the following \f$ 3 \times 3 \f$ matrix, corresponding to the intrinsic calibration matrix of a camera:
        ///
        /// \f$K = \left(\begin{array}{ccc} f & s & c_x \\ 0 & rf & c_y \\ 0 & 0 & 1 \end{array}\right)\f$
        ///
        /// provided the intrinsic parameters \f$ f \f$, \f$ r \f$, \f$ c_x \f$, \f$ c_y \f$ and \f$ s \f$ of that camera.
        ///
        /// @param f value for the camera focal
        /// @param r aspect ratio
        /// @param cx first coordinate for the principal point of the image
        /// @param cy second coordinate for the principal point of the image
        /// @param s camera skew
        static QVMatrix cameraCalibrationMatrix(const double f, const double r = 1.0, const double cx = 0.0, const double cy = 0.0, const double s = 0.0);

        /// @brief Creates a zero matrix
        ///
        /// @param rows number of cols and rows for the identity matrix
        /// @param cols number of cols and rows for the identity matrix
        static QVMatrix zeros(const int rows, const int cols);

        /// @brief Creates a matrix of random values
        ///
        /// This function returns a matrix containing random values, from a uniform distribution [0,1].
        ///
        /// @param rows rows of the matrix
        /// @param cols cols of the matrix
        static QVMatrix random(const int rows, const int cols);

                /// @brief Creates a diagonal matrix with given entries.
        ///
        /// @param diagonalVector vector containing the diagonal values
        static QVMatrix diagonal(const QVVector &diagonalVector);

        /// @brief Create a rotation matrix for points in the 2D plane.
        ///
        /// @param angle angle to rotate around coordinate center
        static QVMatrix rotationMatrix(const double angle);

        /// @brief Create a rotation matrix for points in the 2D plane.
        ///
        /// @param angle angle to rotate around coordinate center
        /// @param center point at the center of the rotation
        static QVMatrix rotationMatrix(const QPointF center, const double angle);

        /// @brief Create a 2D translation matrix.
        ///
        /// @param x increment in X axis
        /// @param y increment in Y axis
        static QVMatrix translationMatrix(const double x, const double y);

        /// @brief Create a 2D scale matrix.
        ///
        /// @param zoom scale
        static QVMatrix scaleMatrix(const double zoom);

        /// @brief Create a rotation matrix for 3D-X axis
        ///
        /// @param angle angle to rotate around X axis in radians
        static QVMatrix rotationMatrix3dXAxis(const double angle);

        /// @brief Create a rotation matrix for 3D-Y axis
        ///
        /// @param angle angle to rotate around Y axis in radians
        static QVMatrix rotationMatrix3dYAxis(const double angle);

        /// @brief Create a rotation matrix for 3D-Z axis
        ///
        /// @param angle angle to rotate around Z axis in radians
        static QVMatrix rotationMatrix3dZAxis(const double angle);

        /// @brief Create a 3D translation matrix.
        ///
        /// @param x increment in X axis
        /// @param y increment in Y axis
        /// @param z increment in Z axis
        static QVMatrix translationMatrix3d(const double x, const double y, const double z);

        /// @brief Create a new matrix with different size and the same content
        ///
                /// This method creates a matrix with the dimensions specified in the input arguments,
        /// keeping the elements of the actual matrix.
        ///
        /// @param rows
        /// @param cols
        QVMatrix reshape(const int newRows, const int newCols) const
            {
            QVMatrix result(newRows, newCols);
            result.data = this->data;
            return result;
            }

        /// @brief Compute the product of a list of matrices
        ///
        /// @param matrices matrice list
        /// @warning Either GSL or MLK compatibilty must be enabled for this function.
        static QVMatrix multiply(const QList<QVMatrix> &matrices)
            {
            QVMatrix product = QVMatrix::identity(3);
            foreach(QVMatrix matrix, matrices)
                product = product * matrix;
            return product;
            }

    private:
        int cols, rows;
        MatrixType type;
        bool transposed;
        QSharedDataPointer< QBlasDataBuffer > data;
    };

/*! @brief Matrix-scalar product

@param value factor for the operation.
@see scalarProduct
*/
QVMatrix operator*(const double value, const QVMatrix &matrix);

/*! @brief Matrix-scalar addition

@param value addendum for the operation.
@see scalarAddition
*/
QVMatrix operator+(const double value, const QVMatrix &matrix);

/*! @brief Matrix-scalar substraction operator

@param value value to substract.
@see scalarSubstraction
*/
QVMatrix operator-(const double value, const QVMatrix &matrix);

/// @todo detailed description should follow
/// @ingroup qvmath
std::ostream& operator << ( std::ostream &os, const QVMatrix &matrix );

/// @todo detailed description should follow
/// @ingroup qvmath
std::istream& operator >> ( std::istream &is, QVMatrix &matrix );

/// @todo detailed description should follow
/// @ingroup qvmath
uint qHash(const QVMatrix &matrix);

#include <QString>
/*!
@brief Writes the content of a QVMatrix object in an ASCII file

@param fileName The name of the file to create. It is overwritten if already exists.
                The matrix values are stored in text format.
@param matrix The matrix to store in the file.
@param precission Number of decimal digits to display for the matrix elements.
@returns TRUE if success, FALSE otherwise.
@ingroup qvmath
*/
bool writeQVMatrixToFile(const QString fileName, const QVMatrix &matrix, const int precission = 7);
/*!
@brief Reads the content of a QVMatrix object from an ASCII file

@param fileName The name of the file to read from.
@param matrix The image to store in the file.
@returns TRUE if success, FALSE otherwise.
@ingroup qvmath
*/
bool readQVMatrixFromFile(const QString fileName, QVMatrix &matrix);

/*! @brief Obtains the element from the Lie algebra so(3) corresponding to a rotation matrix.

The special orthogonal group in three dimensions SO(3), also known as the rotation group, is a Lie group that contains the possible rotation matrices.
This function converts a rotation matrix \f$ R\f$ (an element of the rotation group) to its corresponding element \f$ w \f$ on the Lie algebra so(3).
The Lie algebra so(3) is used commonly to represent rotations in a regular space using only 3 coordinates.

Both elements \f$w\f$ and \f$R\f$ will satisfy the following equation:

\f$ R = e^{\left[w\right]_\times}\f$

There the operator \f$ [\cdot]_\times\f$ maps a vector to its corresponding cross product matrix, and the operator \f$e^\cdot\f$ is the matrix exponential operator.

@param R The rotation matrix
@returns The vector \f$w\f$.
@see expSO3
@note This function is based on code from <a href="http://mi.eng.cam.ac.uk/~twd20/TooNhtml/">the TooN library</a>

@ingroup qvmath
*/
QV3DPointF lnSO3(const QVMatrix &R);

/*! @brief Obtains the rotation matrix corresponding to the element from the Lie algebra so(3)

The special orthogonal group in three dimensions SO(3), also known as the rotation group, is a Lie group that contains the possible rotation matrices.
This function converts an element \f$ w \f$ on the Lie algebra so(3) to its corresponding rotation matrix \f$ R\f$ on the rotation group SO(3).
The Lie algebra so(3) is used commonly to represent rotations in a regular space using only 3 coordinates.

Both elements \f$w\f$ and \f$R\f$ will satisfy the following equation:

\f$ R = e^{\left[w\right]_\times}\f$

Where the operator \f$ [\cdot]_\times\f$ maps a vector to its corresponding cross product matrix, and the operator \f$e^\cdot\f$ is the matrix exponential operator.

@param w The element from the Lie algebra so(3).
@returns The rotation matrix \f$R\f$.
@see lnSO3
@note This function is based on code from <a href="http://mi.eng.cam.ac.uk/~twd20/TooNhtml/">the TooN library</a>

@ingroup qvmath
*/
QVMatrix expSO3(const QV3DPointF& w);

#include <QMetaType>
Q_DECLARE_METATYPE(QVMatrix);

#endif

