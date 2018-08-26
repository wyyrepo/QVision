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
#include <qvmatrixalgebra.h>

#include <QString>
#include <QVMatrix>

//////////////////////////
// Constructors

QVMatrix::QVMatrix():
	cols(1), rows(1), type(General), transposed(false), data(new QBlasDataBuffer(cols*rows))
	{
	operator()(0,0) = 1;
	}

QVMatrix::QVMatrix(const QVMatrix &matrix):
	cols(matrix.cols), rows(matrix.rows), type(matrix.type), transposed(matrix.type), data(matrix.data)
	{ }

QVMatrix::QVMatrix(const int rows, const int cols, const double *data):
	cols(cols), rows(rows), type(General), transposed(false), data(new QBlasDataBuffer(cols*rows))
	{
	if (data != NULL)
		{
		const int n = cols*rows;
		double *matrixData = getWriteData();
		for(int i = 0; i < n; i++)
			matrixData[i] = data[i];
		}
		//for (int r = 0; r < rows; r++)
		//	for (int c = 0; c < cols; c++)
		//		operator()(r, c) = data[r*cols + c];
	}

QVMatrix::QVMatrix(const int rows, const int cols, const QVVector &data):
	cols(cols), rows(rows), type(General), transposed(false), data(new QBlasDataBuffer(cols*rows))
	{
	const int n = cols*rows;
	double *matrixData = getWriteData();
	for(int i = 0; i < n; i++)
		matrixData[i] = data[i];
	}


QVMatrix::QVMatrix(const int rows, const int cols, const double value):
	cols(cols), rows(rows), type(General), transposed(false), data(new QBlasDataBuffer(cols*rows))
	{
	set(value);
	}

QVMatrix::QVMatrix(const QVQuaternion &quaternion)
	{
	*this = quaternion.toRotationMatrix();
	}

QVMatrix::QVMatrix(const QVVector &vector, const bool rowVector):
	cols(rowVector?vector.size():1), rows(rowVector?1:vector.size()), type(General), transposed(false), data(new QBlasDataBuffer(cols*rows))
	{
	if (rowVector)
		setRow(0, vector);
	else
		setCol(0, vector);
	}

QVMatrix::QVMatrix(const QList<QVVector> &vectorList): cols(vectorList.at(0).size()), rows(vectorList.size()), type(General), transposed(false), data(new QBlasDataBuffer(cols*rows))
	{
	for (int n = 0; n < getRows(); n++)
		{
		Q_ASSERT(vectorList.at(n).size() == getCols());
		setRow(n, vectorList.at(n));
		}
	}

QVMatrix::QVMatrix(const QList< QVector<double> > &vectorList): cols(vectorList.at(0).size()), rows(vectorList.size()), type(General), transposed(false), data(new QBlasDataBuffer(cols*rows))
	{
	for (int n = 0; n < getRows(); n++)
		{
		Q_ASSERT(vectorList.at(n).size() == getCols());
		setRow(n, vectorList.at(n));
		}
	}

#ifdef GSL_AVAILABLE
QVMatrix::QVMatrix(const gsl_matrix *matrix): cols(matrix->size2), rows(matrix->size1), type(General), transposed(false), data(new QBlasDataBuffer(cols*rows))
	{
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			operator()(i, j) = gsl_matrix_get(matrix, i, j);
	}

QVMatrix::operator gsl_matrix * () const
	{
	gsl_matrix *result = gsl_matrix_alloc(rows, cols);
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			gsl_matrix_set(result, i, j, operator()(i, j));
	return result;
	}
#endif

QVMatrix::QVMatrix(const QList<QPointF> &pointList): cols(2), rows(pointList.size()), type(General), transposed(false), data(new QBlasDataBuffer(cols*rows))
	{
	for (int n = 0; n < getRows(); n++)
		setRow(n, pointList.at(n));
	}

#ifdef QVOPENCV
QVMatrix::QVMatrix(const CvMat *cvMatrix): cols(cvMatrix->cols), rows(cvMatrix->rows), type(General), transposed(false), data(new QBlasDataBuffer(cols*rows))
	{
	for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				this->operator()(i,j) = cvmGet(cvMatrix, i, j);
	}

CvMat *QVMatrix::toCvMat(const int cvMatType) const
	{
	Q_ASSERT( (cvMatType == CV_32F) || (cvMatType == CV_64F) );

	CvMat *result = cvCreateMat(rows, cols, cvMatType);

	for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				cvmSet(result, i, j, this->operator()(i,j));
	return result;
	}
#endif

#ifdef QVOCTAVE
QVMatrix::QVMatrix(const Matrix octMatrix): cols(octMatrix.columns()), rows(octMatrix.rows()), type(General), transposed(false), data(new QBlasDataBuffer(cols*rows))
	{
	for (int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			operator()(i,j) = octMatrix(i,j);
	}

Matrix QVMatrix::toOctaveMat() const
	{
	Matrix result(rows, cols);

	for (int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			result(i,j) = operator()(i,j);
	return result;
	}
#endif

/////////////////////////
QVMatrix & QVMatrix::operator=(const QVMatrix &matrix)
	{
	cols = matrix.cols;
	rows = matrix.rows;
	type = matrix.type;
	transposed = matrix.transposed;
	data = matrix.data;

	return *this;
	}

/////////////////////////

/*QVVector QVMatrix::operator*(const QVVector &vector) const
	{
	Q_ASSERT(vector.size() == getCols());
	// Todo: use blas for this function
	return dotProduct(vector.toColumnMatrix()).getCol(0);
	}*/

/////////////////////////

bool QVMatrix::equals(const QVMatrix &matrix) const
	{
	// Check valences for both matrixs are equivalent
	if (cols != matrix.cols || rows != matrix.rows)
		return false;

	// Check data in both matrixs is equal
	const double	*data1 = getReadData(),
				*data2 = matrix.getReadData();

	for (int i = 0; i < getDataSize(); i++)
		if (data1[i] != data2[i])
			return false;

	return true;
	}

#ifdef BLAS_AVAILABLE
QVVector QVMatrix::dotProduct(const QVVector &vector, const bool transposeMatrix) const
	{
	const int	m = transposeMatrix? cols: rows,
			n = transposeMatrix? rows: cols,
			n_ = vector.size();

	if (n != n_)
		{
		std::cout << "ERROR: tried to multiply a matrix with a vector of incompatible sizes at QVMatrix::dotProduct(const QVVector &v)." << std::endl
                        << "\tMatrix dimensions:\t" << m << "x" << n << std::endl
                        << "\tVector dimension:\t" << n_ << std::endl;
		exit(1);
		}

	QVVector result(m);
	cblas_dgemv(CblasRowMajor, transposeMatrix?CblasTrans:CblasNoTrans, rows, cols, 1.0, getReadData(), cols, vector.data(), 1, 0.0, result.data(), 1);
	return result;
	}

QVMatrix QVMatrix::dotProduct(const QVMatrix &matrix, const bool transposeFirstOperand, const bool transposeSecondOperand) const
	{
	//std::cout << "** gsl" << std::endl;
	const int cols1 = cols, rows1 = rows, cols2 = matrix.cols, rows2 = matrix.rows;

	// C_mxn = A_mxk * B_kxn
	const int	m = transposeFirstOperand? cols1: rows1,
			k = transposeFirstOperand? rows1: cols1,
			k_ = transposeSecondOperand? cols2: rows2,
			n = transposeSecondOperand? rows2: cols2;

	QVMatrix result(m, n);

	// Ensure k == k_
	Q_ASSERT(k == k_);

	if (k != k_)
		{
		std::cout << "ERROR: tried to multiply matrices with incompatible sizes at QVMatrix::dotProduct(const QVMatrix &matrix)." << std::endl
                        << "\tMatrix 1 dimensions:\t" << m << "x" << k << std::endl
                        << "\tMatrix 2 dimensions:\t" << k_ << "x" << n << std::endl;
		exit(1);
		}
 
	cblas_dgemm(CblasRowMajor,
			transposeFirstOperand?CblasTrans:CblasNoTrans,
			transposeSecondOperand?CblasTrans:CblasNoTrans,
			m, n, k, 1.0,
			getReadData(), cols1,
			matrix.getReadData(), cols2, 0.0,
			result.getWriteData(), n);

	return result;
	}
#else
QVMatrix QVMatrix::dotProduct(const QVMatrix &matrix, const bool transposeFirstOperand, const bool transposeSecondOperand) const
	{
	std::cout << "[QVMatrix::dotProduct] --------------------------------- Not blas! --------------------" << std::endl;
	const QVMatrix	op1 = transposeFirstOperand? this->transpose():(*this),
			op2 = transposeSecondOperand? matrix.transpose():matrix;

	const int m = op1.getRows(), o = op1.getCols(), o_ = op2.getRows(), n = op2.getCols();

	// Ensure k == k_
	Q_ASSERT(o == o_);

	if (o != o_)
		{
		std::cout << "ERROR: tried to multiply matrices with incompatible sizes at QVMatrix::dotProduct(const QVMatrix &matrix)." << std::endl
                        << "\tMatrix 1 dimensions:\t" << m << "x" << o << std::endl
                        << "\tMatrix 2 dimensions:\t" << o_ << "x" << n << std::endl;
		exit(1);
		}

	QVMatrix result(m, n, 0.0);

	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			for(int k = 0; k < o; k++)
				result(i,j) += op1(i,k) * op2(k, j);
	return result;
	}

QVVector QVMatrix::dotProduct(const QVVector &vector, const bool transposeMatrix) const
	{
	std::cout << "[QVMatrix::dotProduct] --------------------------------- Not blas! --------------------" << std::endl;
	//std::cout << "not gsl" << std::endl;
	const QVMatrix	op1 = transposeMatrix? this->transpose() : (*this);
	const int m = op1.getRows(), o = op1.getCols(), o_ = vector.size();

	if (o != o_)
		{
		std::cout << "ERROR: tried to multiply a matrix with a vector of incompatible sizes at QVMatrix::dotProduct(const QVVector &v)." << std::endl
                        << "\tMatrix dimensions:\t" << m << "x" << o << std::endl
                        << "\tVector dimension:\t" << o_ << std::endl;
		exit(1);
		}

	QVVector result(m, 0.0);

	for(int i = 0; i < m; i++)
		for(int k = 0; k < o; k++)
			result[i] += op1(i,k) * vector[k];

	return result;
	}
#endif

QVMatrix QVMatrix::elementProduct(const QVMatrix &matrix) const
	{
	const int cols1 = cols, rows1 = rows, cols2 = matrix.cols, rows2 = matrix.rows;

	Q_ASSERT(rows1 == rows2);
	Q_ASSERT(cols1 == cols2);

	if (cols1 != cols2 || rows1 != rows2)
		{
		std::cout << "ERROR: tried to multiply matrices with incompatible sizes at QVMatrix::dotProduct(const QVMatrix &matrix)." << std::endl
                        << "\tMatrix 1 dimensions:\t" << rows1 << "x" << cols1 << std::endl
                        << "\tMatrix 2 dimensions:\t" << rows2 << "x" << cols2 << std::endl;
		exit(1);
		}

	QVMatrix result(rows1, cols2);

	/// @todo use Blas
	for (int i = 0; i < cols1; i++)
		for (int j = 0; j < cols1; j++)
			result(i,j) = this->operator()(i,j) * matrix(i,j);

	return result;
	}

#ifdef QVMATRIXALGEBRA_AVAILABLE
QVMatrix QVMatrix::matrixDivide(const QVMatrix &matrix) const
	{
	Q_ASSERT(matrix.getCols() >= matrix.getRows());
	Q_ASSERT(matrix.getCols() == (*this).getCols());

	QVMatrix result(matrix.getRows(), (*this).getRows());

	//if (matrix.getCols() == matrix.getRows())
	//	solveByLUDecomposition(matrix.transpose(), result, (*this).transpose());
	//else
	solveBySingularValueDecomposition(matrix.transpose(), result, (*this).transpose());

	return result.transpose();
	}

void QVMatrix::triangularSolve(const QVVector &b, QVVector &x, bool transposed, bool unit_diagonal) const
{
    x = b;

//    enum CBLAS_UPLO Uplo = CblasUpper;

    switch(this->getType()) {
	case UpperTriangular:
//            Uplo = CblasUpper;
		cblas_dtrsv(CblasRowMajor, CblasUpper,transposed?CblasTrans:CblasNoTrans,unit_diagonal?CblasUnit:CblasNonUnit,
			this->getRows(),this->getReadData(),this->getRows(),x.data(),1);
		break;
	case LowerTriangular:
  //          Uplo = CblasLower;
		cblas_dtrsv(CblasRowMajor, CblasLower,transposed?CblasTrans:CblasNoTrans,unit_diagonal?CblasUnit:CblasNonUnit,
			this->getRows(),this->getReadData(),this->getRows(),x.data(),1);
		break;
	default:
            qFatal("QVMatrix::triangularSolve() method called with non-triangular matrix\n");            
    }

    /*cblas_dtrsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo, const enum
    CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag, const int N,const double *A, const int
    lda, double *X, const int incX);*/


}

void QVMatrix::triangularSolve(const QVMatrix &B, QVMatrix &X, bool transposed, bool unit_diagonal, bool left) const
{
    X = B;

//    enum CBLAS_UPLO Uplo = CblasUpper;

    switch(this->getType()) {
        case UpperTriangular:
  //          Uplo = ;
	    cblas_dtrsm(CblasRowMajor, left?CblasLeft:CblasRight, CblasUpper, transposed?CblasTrans:CblasNoTrans,
		        unit_diagonal?CblasUnit:CblasNonUnit,
		        this->getRows(),X.getCols(),1.0,this->getReadData(),this->getRows(),X.getWriteData(),X.getCols());
            break;
        case LowerTriangular:
//            Uplo = ;
	    cblas_dtrsm(CblasRowMajor, left?CblasLeft:CblasRight, CblasLower, transposed?CblasTrans:CblasNoTrans,
		        unit_diagonal?CblasUnit:CblasNonUnit,
		        this->getRows(),X.getCols(),1.0,this->getReadData(),this->getRows(),X.getWriteData(),X.getCols());
            break;
        default:
            qFatal("QVMatrix::triangularSolve() method called with non-triangular matrix\n");
    }

    /*void cblas_dtrsm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side, const enum
    CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag, const int
    M, const int N, const double alpha, const double *A, const int lda, double *B, const int
    ldb);*/
}

QVMatrix QVMatrix::inverse() const
	{
	/// @TODO Por ahora con la misma pseudoinversa, sería mejor de otro modo...
	return pseudoInverse(*this);
	}

double QVMatrix::det() const
	{
	return determinant(*this);
	}
#endif

QVMatrix QVMatrix::transpose() const
	{
	const int rows = getRows(), cols = getCols();

	QVMatrix result(cols, rows);

	const double 	*matrixData = getReadData();
	double		*resultData = result.getWriteData();

	/// @todo use blas function cblas_axpy for this
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			resultData[j*rows+i] = matrixData[i*cols+j];

	return result;
	}

void QVMatrix::set(const double value)
	{
	double		*resultData = getWriteData();
	const int	dataSize = getDataSize();

	/// @todo use blas function cblas_axpy for data add
	for (int i = 0; i < dataSize; i++)
		resultData[i] = value;
	}

QVMatrix QVMatrix::addition(const QVMatrix &matrix) const
	{
	Q_ASSERT(cols == matrix.cols || rows == matrix.rows);

	QVMatrix result = *this;

	const double 	*matrixData = matrix.getReadData();
	double		*resultData = result.getWriteData();
	const int	dataSize = matrix.getDataSize();

	/// @todo use blas function cblas_axpy for data add
	for (int i = 0; i < dataSize; i++)
		resultData[i] += matrixData[i];

	return result;
	}

// @todo use daxpy for inline addition.
void	QVMatrix::inlineAddition(const QVMatrix &matrix)
	{
	Q_ASSERT(cols == matrix.cols || rows == matrix.rows);

	QVMatrix result = *this;

	const double 	*matrixData = matrix.getReadData();
	double		*resultData = getWriteData();
	const int		dataSize = matrix.getDataSize();

	/// @todo use blas function cblas_axpy for data add
	for (int i = 0; i < dataSize; i++)
		resultData[i] += matrixData[i];
	}

QVMatrix QVMatrix::substract(const QVMatrix &matrix) const
	{
	// Check valences for both matrixs are equivalent
	Q_ASSERT(cols == matrix.cols || rows == matrix.rows);

	QVMatrix result = *this;

	const double 	*matrixData = matrix.getReadData();
	double		*resultData = result.getWriteData();
	const int	dataSize = matrix.getDataSize();

	/// @todo use blas function cblas_axpy for data add

	for (int i = 0; i < dataSize; i++)
		resultData[i] -= matrixData[i];

	return result;
	}

QVMatrix QVMatrix::scalarProduct(const double value) const
	{
	QVMatrix result = *this;

	double		*resultData = result.getWriteData();
	const int	dataSize = getDataSize();

	/// @todo use blas function?

	for (int i = 0; i < dataSize; i++)
		resultData[i] *= value;

	return result;
	}

QVMatrix QVMatrix::scalarDivide(const double value) const
	{
	QVMatrix result = *this;

	double		*resultData = result.getWriteData();
	const int	dataSize = getDataSize();

	/// @todo use blas function?

	for (int i = 0; i < dataSize; i++)
		resultData[i] /= value;

	return result;
	}

QVMatrix QVMatrix::scalarAdd(const double value) const
	{
	QVMatrix result = *this;

	double		*resultData = result.getWriteData();
	const int	dataSize = getDataSize();

	/// @todo use blas function?

	for (int i = 0; i < dataSize; i++)
		resultData[i] += value;

	return result;
	}

QVMatrix QVMatrix::scalarSubstract(const double value) const
	{
	QVMatrix result = *this;

	double		*resultData = result.getWriteData();
	const int	dataSize = getDataSize();

	/// @todo use blas function?

	for (int i = 0; i < dataSize; i++)
		resultData[i] -= value;

	return result;
	}

QVMatrix QVMatrix::horizontalAppend(const QVMatrix &matrix) const
	{
	const int cols1 = cols, rows1 = rows, cols2 = matrix.cols, rows2 = matrix.rows;

	Q_ASSERT(rows1 == rows2);

	if (rows1 != rows2)
		{
		std::cout << "ERROR: tried to append horizontally matrices with different row number at QVMatrix::horizontalAppend(const QVMatrix &matrix)."
			<< std::endl
                        << "\tMatrix 1 dimensions:\t" << rows1 << "x" << cols1 << std::endl
                        << "\tMatrix 2 dimensions:\t" << rows2 << "x" << cols2 << std::endl;
		exit(1);
		}

	QVMatrix result(rows1, cols1 + cols2);

	for (int i = 0; i < cols1; i++)
		result.setCol(i, getCol(i));

	for (int i = 0; i < cols2; i++)
		result.setCol(cols1 + i, matrix.getCol(i));

	return result;
	}

QVMatrix QVMatrix::verticalAppend(const QVMatrix &matrix) const
	{
	const int cols1 = cols, rows1 = rows, cols2 = matrix.cols, rows2 = matrix.rows;

	Q_ASSERT(cols1 == cols2);

	if (cols1 != cols2)
		{
		std::cout << "ERROR: tried to append vertically matrices with different row number at QVMatrix::horizontalAppend(const QVMatrix &matrix)."
			<< std::endl
                        << "\tMatrix 1 dimensions:\t" << rows1 << "x" << cols1 << std::endl
                        << "\tMatrix 2 dimensions:\t" << rows2 << "x" << cols2 << std::endl;
		exit(1);
		}

	QVMatrix result(rows1 + rows2, cols2);

	for (int i = 0; i < rows1; i++)
		result.setRow(i, getRow(i));

	for (int i = 0; i < rows2; i++)
		result.setRow(rows1 + i, matrix.getRow(i));

	return result;
	}

/////////////////////////////////////////////////////////

double QVMatrix::norm2() const
	{
	#ifdef BLAS_AVAILABLE
	return cblas_dnrm2(getDataSize(), getReadData(), 1);
	#else
	std::cout << "[QVMatrix::dotProduct] --------------------------------- Not blas! --------------------" << std::endl;
	double accum = 0.0;
	const int cols = getCols(), rows = getRows();

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			{
			const double actualValue = operator()(i,j);
			accum += actualValue * actualValue;
			}
	return sqrt(accum);
	#endif
	};

double QVMatrix::trace() const
	{
	const int n = MIN(getCols(), getRows());
	double accum = 0.0;
	for (int i = 0; i < n; i++)
		accum += operator()(i,i);
	return accum;
	}

bool QVMatrix::isDiagonal() const
	{
	const double	*data = getReadData();
	//const int		dataSize = getDataSize();

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if ( (i != j) and (data[i*cols+j] != 0.0) )
				return false;

	return true;
	}

bool QVMatrix::containsNaN() const
	{
	const double	*data = getReadData();
	const int	dataSize = getDataSize();

	for (int i = 0; i < dataSize; i++)
                if (isnan(data[i]))
			return true;

	return false;
	}

bool QVMatrix::containsInf() const
	{
	const double	*data = getReadData();
	const int	dataSize = getDataSize();

	for (int i = 0; i < dataSize; i++)
                if (isinf(data[i]))
			return true;

	return false;
	}

QVMatrix QVMatrix::rowHomogeneousNormalize() const
	{
	const int cols = getCols(), rows = getRows();
	QVMatrix result(rows, cols);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			result(i,j) = operator()(i,j) / operator()(i,cols-1);
	return result;
	}

const QVVector QVMatrix::getRow(const int row) const
	{
	Q_ASSERT(row < getRows());

	const int cols = getCols();
	QVVector result(cols);
	for (int col= 0; col < cols; col++)
		result[col] = operator()(row,col);

	return result;
	}

void QVMatrix::setRow(const int row, QVVector vector)
	{
	Q_ASSERT(row < getRows());
	Q_ASSERT(getCols() == vector.size());

	const int cols = getCols();
	for (int col= 0; col < cols; col++)
		operator()(row,col) = vector[col];
	}

void QVMatrix::setRow(const int row, QVector<double> vector)
	{
	Q_ASSERT(row < getRows());
	Q_ASSERT(getCols() == vector.size());

	const int cols = getCols();
	for (int col= 0; col < cols; col++)
		operator()(row,col) = vector[col];
	}

const QVVector QVMatrix::getCol(const int col) const
	{
	Q_ASSERT(col < getCols());

	const int rows = getRows();
	QVVector result(rows);
	for (int row= 0; row < rows; row++)
		result[row] = operator()(row,col);

	return result;
	}

void QVMatrix::setCol(const int col, QVVector vector)
	{
	Q_ASSERT(col < getCols());
	Q_ASSERT(getRows() == vector.size());

	const int rows = getRows();
	for (int row= 0; row < rows; row++)
		operator()(row,col) = vector[row];
	}


const QVVector QVMatrix::diagonal() const
	{
	Q_ASSERT(getRows() == getCols());
	QVVector result(getRows());
	for(int i = 0; i < getRows(); i++)
		result[i] = operator()(i,i);

	return result;
	}

/// @todo This method is very slow. Optimize it with blas code.
const QVMatrix QVMatrix::getSubmatrix(const int firstRow, const int lastRow, const int firstCol, const int lastCol) const
	{
	Q_ASSERT(firstRow >= 0);
	Q_ASSERT(firstCol >= 0);
	Q_ASSERT(firstRow <= lastRow);
	Q_ASSERT(firstCol <= lastCol);
	Q_ASSERT(lastRow < getRows());
	Q_ASSERT(lastCol < getCols());

	QVMatrix result(lastRow - firstRow +1, lastCol - firstCol +1);

	for (int row = firstRow; row <= lastRow; row++)
		result.setRow(row-firstRow, getRow(row).mid(firstCol, lastCol - firstCol +1));

	return result;
	}

void QVMatrix::setSubmatrix(const int row, const int col, const QVMatrix &M)
	{
	Q_ASSERT(col >= 0);
	Q_ASSERT(row >= 0);
        Q_ASSERT(M.getCols() + col <= getCols());
        Q_ASSERT(M.getRows() + row <= getRows());

	for (int r = 0; r < M.getRows(); r++)
		for (int c = 0; c < M.getCols(); c++)
			operator()(r + row, c + col) = M(r, c);
	}

QVMatrix QVMatrix::reversedRows() const
{
    int m = getRows(), n = getCols();
    QVMatrix result(m,n);

    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            result(i,j) = operator()(m-1-i,j);

    return result;
}

QVMatrix QVMatrix::reversedCols() const
{
    int m = getRows(), n = getCols();
    QVMatrix result(m,n);

    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            result(i,j) = operator()(i,n-1-j);

    return result;
}

///////////////////////////////////////////////////
// Misc matrices

QVMatrix QVMatrix::identity(const int size)
	{
	QVMatrix result(size, size);
	result.set(0);
	for (int i= 0; i < size; i++)
		result(i,i) = 1;
	return result;
	}

QVMatrix QVMatrix::cameraCalibrationMatrix(const double focal, const double aspectRatio, const double cx, const double cy, const double skew)
	{
	const double dataK[9] = { focal, skew, cx, 0.0, aspectRatio*focal, cy, 0.0, 0.0, 1.0 };
	return QVMatrix(3,3, dataK);
	}

QVMatrix QVMatrix::zeros(const int rows, const int cols)
	{
	QVMatrix result(rows, cols);
	result.set(0);
	return result;
	}

QVMatrix QVMatrix::random(const int rows, const int cols)
	{
	QVMatrix result(rows, cols);
	for (int col = 0; col < cols; col++)
		for (int row = 0; row < rows; row++)
			result(row,col) = (double)ABS(rand()) / (double)RAND_MAX;
	return result;
	}

QVMatrix QVMatrix::diagonal(const QVVector &diagonalVector)
	{
	const int size = diagonalVector.size();
	QVMatrix result(size, size);
	result.set(0);
	for (int i= 0; i < size; i++)
		result(i,i) = diagonalVector[i];
	return result;
	}

QVMatrix QVMatrix::rotationMatrix(const double delta)
	{
	// Rotation[delta_] := {{Cos[delta], Sin[delta], 0}, {-Sin[delta], Cos[delta], 0}, {0, 0, 1}};
	QVMatrix result = QVMatrix::identity(3);

	result(0,0) = cos(delta);	result(0,1) = sin(delta);
	result(1,0) = -sin(delta);	result(1,1) = cos(delta);

	return result;
	}

QVMatrix QVMatrix::rotationMatrix(const QPointF center, const double angle)
	{
	return QVMatrix::translationMatrix(center.x(), center.y()) * QVMatrix::rotationMatrix(angle) *
		QVMatrix::translationMatrix(-center.x(), -center.y());
	}

QVMatrix QVMatrix::translationMatrix(const double x, const double y)
	// Translation[x_, y_] := {{1, 0, x}, {0, 1, y}, {0, 0, 1}};
	{
	QVMatrix result = QVMatrix::identity(3);

	result(0,2) = x;
	result(1,2) = y;

	return result;
	}

QVMatrix QVMatrix::scaleMatrix(const double zoom)
	{
	QVMatrix result = QVMatrix::identity(3);

	result(0,0) = zoom;
	result(1,1) = zoom;

	return result;
	}

QVMatrix QVMatrix::rotationMatrix3dZAxis(const double angle)
	{
	QVMatrix result = identity(4);

	result(0,0) = cos(angle);
	result(0,1) = sin(angle);

	result(1,0) = -sin(angle);
	result(1,1) = cos(angle);

	return result;
	}

QVMatrix QVMatrix::rotationMatrix3dXAxis(const double angle)
	{
	QVMatrix result = identity(4);

	result(1,1) = cos(angle);
	result(1,2) = sin(angle);

	result(2,1) = -sin(angle);
	result(2,2) = cos(angle);

	return result;
	}

QVMatrix QVMatrix::rotationMatrix3dYAxis(const double angle)
	{
	QVMatrix result = identity(4);

	result(0,0) = cos(angle);
	result(0,2) = -sin(angle);

	result(2,0) = sin(angle);
	result(2,2) = cos(angle);

	return result;
	}

QVMatrix QVMatrix::translationMatrix3d(const double x, const double y, const double z)
	{
	QVMatrix result = identity(4);

	result(0,3) = x;
	result(1,3) = y;
	result(2,3) = z;

	return result;
	}

QVVector QVMatrix::meanCol() const
	{
	QVVector result = getCol(0);
	for (int i = 1; i < getCols(); i++)
		result += getCol(i);
	return result / getCols();
	}

////////////////////////////////////////////////////

std::ostream& operator << ( std::ostream &os, const QVMatrix &matrix )
	{
	const int cols = matrix.getCols(), rows = matrix.getRows(), precision = os.precision();

	os << "QVMatrix (" << rows << ", " << cols << ")" << std::endl;

	const double *data = matrix.getReadData();
	os << "[" << std::endl;
	for (int i=0; i < rows; i++)
		{
		os << "    [ ";
		for (int j = 0; j < cols; j++)
			{
			const double value = data[i*cols + j];
			os << qPrintable(QString("%1").arg(value, -(2+precision), 'f', precision)) << " ";
			}
		os << "]" << std::endl;
		}
	os << "]" << std::endl;
	return os;
	}

std::istream& operator >> ( std::istream &is, QVMatrix &matrix )
	{
	matrix = QVMatrix();

	int cols, rows;
	double value;

	is.ignore(256, '(');
	if (is.eof())
		return is;

	is >> rows;

	is.ignore(256, ',');
	if (is.eof())
		return is;

	is >> cols;

	is.ignore(256, '[');
	if (is.eof())
		return is;

	QVMatrix maux(rows, cols);

	for (int i = 0; i < rows; i++)
		{
		is.ignore(256, '[');
		if (is.eof())
			return is;

		for (int j = 0; j < cols; j++)
			{
			is >> value;
			maux(i, j) = value;
			}
		}

	matrix = maux;

	return is;
	}


uint qHash(const QVMatrix &matrix)
	{
	const int cols = matrix.getCols(), rows = matrix.getRows();

	double accum = 0;
	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows; j++)
			accum += matrix(i,j) / matrix(cols-i-1, rows-j-1);

	return (uint) ((100000 * accum) / ((double) (cols + rows)));
	}


#include <iostream>
#include <fstream>
#include <iomanip>

bool writeQVMatrixToFile(const QString fileName, const QVMatrix &matrix, const int precission)
	{
	std::ofstream stream;
	stream.open(qPrintable(fileName));

	if ( stream.fail() )
		return false;

	stream << std::setprecision (precission);
	stream << matrix;
	stream.close();
	return true;
	}

bool readQVMatrixFromFile(const QString fileName, QVMatrix &matrix)
	{
	std::ifstream stream;
	stream.open(qPrintable(fileName));

	if ( stream.fail() )
		return false;

	stream >> matrix;
	stream.close();
	return true;
	}

QVMatrix operator*(const double value, const QVMatrix &matrix)
	{
	return matrix.scalarProduct(value);
	}

QVMatrix operator+(const double value, const QVMatrix &matrix)
	{
	return matrix.scalarAdd(value);
	}

QVMatrix operator-(const double value, const QVMatrix &matrix)
	{
	return matrix.scalarSubstract(value);
	}


#ifndef DOXYGEN_IGNORE_THIS
// This function is based on code from the TooN library:
//	http://mi.eng.cam.ac.uk/~twd20/TooNhtml/
void rodrigues_so3_exp(const QV3DPointF &w, const double A, const double B, QVMatrix &R)
        {
        const double	wx2 = w[0]*w[0],
                        wy2 = w[1]*w[1],
                        wz2 = w[2]*w[2],
                        a1 = A*w[2],
                        a2 = A*w[1],
                        a3 = A*w[0],
                        b1 = B*(w[0]*w[1]),
                        b2 = B*(w[0]*w[2]),
                        b3 = B*(w[1]*w[2]);

        R(0,0) = 1.0 - B*(wy2 + wz2);
        R(1,1) = 1.0 - B*(wx2 + wz2);
        R(2,2) = 1.0 - B*(wx2 + wy2);
        R(0,1) = b1 - a1;
        R(1,0) = b1 + a1;
        R(0,2) = b2 + a2;
        R(2,0) = b2 - a2;
        R(1,2) = b3 - a3;
        R(2,1) = b3 + a3;
        }
#endif // DOXYGEN_IGNORE_THIS
// This function is based on code from the TooN library:
//	http://mi.eng.cam.ac.uk/~twd20/TooNhtml/
QVMatrix expSO3(const QV3DPointF& w)
        {
        static const double one_6th = 1.0/6.0, one_20th = 1.0/20.0;
        const double	theta_sq = w*w,
                        theta = sqrt(theta_sq),
                        inv_theta = 1.0/theta;

        QVMatrix result(3,3,0.0);
        if (theta_sq < 1e-8)
                rodrigues_so3_exp(w, 1.0 - one_6th * theta_sq, 0.5, result);
        else	{
                if (theta_sq < 1e-6)
                        rodrigues_so3_exp(w,	1.0 - theta_sq * one_6th*(1.0 - one_20th * theta_sq),
                                                0.5 - 0.25 * one_6th * theta_sq, result);
                else
                        rodrigues_so3_exp(w,	sin(theta) * inv_theta,
                                                (1 - cos(theta)) * (inv_theta * inv_theta),
                                                result);
                }
        return result;
        }

// This function is based on code from the TooN library:
//	http://mi.eng.cam.ac.uk/~twd20/TooNhtml/
QV3DPointF lnSO3(const QVMatrix &R)
        {
        QV3DPointF result( (R(2,1)-R(1,2))/2, (R(0,2)-R(2,0))/2, (R(1,0)-R(0,1))/2 );

        const double cos_angle = (R(0,0) + R(1,1) + R(2,2) - 1.0) * 0.5;

        double sin_angle_abs = result.norm2();
        if (cos_angle > M_SQRT1_2)
                // [0 - Pi/4[ use asin
                {
                if(sin_angle_abs > 0)
                        result = result * asin(sin_angle_abs) / sin_angle_abs;
                }
        else if( cos_angle > -M_SQRT1_2)
                // [Pi/4 - 3Pi/4[ use acos, but antisymmetric part
                result = result * acos(cos_angle) / sin_angle_abs;
        else	// Rest use symmetric part
                {
                // Antisymmetric part vanishes, but still large rotation, need information from symmetric part
                const double	d0 = R(0,0) - cos_angle,
                                d1 = R(1,1) - cos_angle,
                                d2 = R(2,2) - cos_angle;

                const QV3DPointF r2 = (fabs(d0) > fabs(d1) && fabs(d0) > fabs(d2))?
                                        // first is largest, fill with first column
                                        QV3DPointF(d0, (R(1,0)+R(0,1))/2, (R(0,2)+R(2,0))/2):
                                        (fabs(d1) > fabs(d2))?
                                                // second is largest, fill with second column
                                                QV3DPointF((R(1,0)+R(0,1))/2, d1, (R(2,1)+R(1,2))/2):
                                                // third is largest, fill with third column
                                                QV3DPointF((R(0,2)+R(2,0))/2, (R(2,1)+R(1,2))/2, d2);

                // Flip if we point in the wrong direction! Also, norm of result vector = angle.
                result = r2 * ((r2 * result < 0)?-1.0:1.0) * (M_PI - asin(sin_angle_abs)) / r2.norm2();
                }
        return result;
        }
