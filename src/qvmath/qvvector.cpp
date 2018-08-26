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

#include <QString>
#include <QVVector>
#include <QVMatrix>

QVVector::QVVector(const QVMatrix &matrix): QVector<double>(matrix.getCols() * matrix.getRows())
	{
	const int n = size();
	const double *matrixData = matrix.getReadData();

	for(int i = 0; i < n; i++)
		operator[](i) = matrixData[i];
	}

double QVVector::dotProduct(const QVVector &vector) const
	{
	Q_ASSERT(size() == vector.size());

	double accum = 0;
	for (int i = 0; i < size(); i++)
		accum += at(i) * vector[i];

	return accum;
	}

QVVector QVVector::crossProduct(const QVVector &vector) const
	{
	Q_ASSERT(size() == vector.size());
	Q_ASSERT(size() == 3);

	const double	*source1 = data(),
			*source2 = vector.data();

	const double	x1 = source1[0], y1 = source1[1], z1 = source1[2],
			x2 = source2[0], y2 = source2[1], z2 = source2[2];

	QVVector v(3);

	double	*destination = v.data();
	destination[0] = -y2*z1 + y1*z2;
	destination[1] = x2*z1 - x1*z2;
	destination[2] = -x2*y1 + x1*y2;

	return v;
	}

QVMatrix QVVector::outerProduct(const QVVector &vector) const
        {
        const int m = size(), n = vector.size();

        QVMatrix result(m,n);

        double *rptr = result.getWriteData();
        const double *v1ptr = this->data(), *v2ptr;

        for(int i=0; i<m; i++) {
            v2ptr = vector.data();
            for(int j=0; j<n; j++) {
                (*rptr) = (*v1ptr) * (*v2ptr); // result(i,j) = (*this)[i] * vector[j];
                rptr++;
                v2ptr++;
            }
            v1ptr++;
        }

        return result;
        }

QVVector QVVector::operator*(const QVMatrix &matrix) const
	{
	Q_ASSERT(size() == matrix.getRows());
	if (size() != matrix.getRows())
		{
		std::cout << "ERROR: tried to multiply matrices with incompatible sizes at QVMatrix::dotProduct(const QVMatrix &matrix)." << std::endl
			<< "\tVector size:\t" << size() << std::endl
                        << "\tMatrix dimensions:\t" << matrix.getRows() << "x" << matrix.getCols() << std::endl;
		exit(1);
		}

	return matrix.dotProduct(*this, true);
	}

QVVector QVVector::add(const QVVector &vector) const
	{
	Q_ASSERT(size() == vector.size());

	QVVector result(size());

	const double	*source1 = data(),
			*source2 = vector.data();
	double	*destination = result.data();
		
	for (int i = 0; i < size(); i++)
		destination[i] = source1[i] + source2[i];

	return result;
	}

QVVector QVVector::substract(const QVVector &vector) const
	{
	Q_ASSERT(size() == vector.size());

	QVVector result(size());

	const double	*source1 = data(),
			*source2 = vector.data();
	double	*destination = result.data();

	for (int i = 0; i < size(); i++)
		destination[i] = source1[i] - source2[i];

	return result;
	}

bool QVVector::equals(const QVVector &vector) const
	{
	if (size() != vector.size())
		return false;

	const double	*source1 = data(),
			*source2 = vector.data();

	for (int i = 0; i < size(); i++)
		if (source1[i] != source2[i])
			return false;

	return true;
	}

QVVector QVVector::homogeneousCoordinates() const
	{
	return QVVector(*this) << 1;
	};

QVMatrix QVVector::crossProductMatrix() const
	{
	Q_ASSERT(size() == 3);

	QVMatrix result(3,3);
	result(0,0) = 0;	result(0,1) = -at(2);	result(0,2) = at(1);
	result(1,0) = at(2);	result(1,1) = 0;	result(1,2) = -at(0);
	result(2,0) = -at(1);	result(2,1) = at(0);	result(2,2) = 0;

	return result;
	}

QVMatrix QVVector::toRowMatrix() const
	{
	QVMatrix result(1,size());
	result.setRow(0,*this);
	return result;
	}

QVMatrix QVVector::toColumnMatrix() const
	{
	QVMatrix result(size(),1);
	result.setCol(0,*this);
	return result;
	}


const QVVector QVVector::gaussianVector(const int radius, const double sigma)
	{
	const float sigma2 = sigma * sigma;
	QVVector result(2*radius+1);
	for (int j=-radius;j<=radius;j++)
		result[j+radius] = (float)expf(-((double)j*j)/(2.0*sigma2));

	const double regularizer = sqrt(2*PI*sigma2);
	for (int i=0; i< result.size();i++)
		result[i] /= regularizer;

	return result;
	}

QVVector QVVector::random(const int size)
	{
	QVVector result(size);
	for (int i = 0; i < size; i++)
		result[i] = (double)ABS(rand()) / (double)RAND_MAX;
	return result;
	}

const QVVector QVVector::mexicanHatWaveletVector(const int radius, const double sigma)
	{
	const float sigma2 = sigma * sigma;
	QVVector result(2*radius+1);
	for (int j=-radius;j<=radius;j++)
		result[j+radius] = (1-((double)j*j)/sigma2)*(float)expf(-((double)j*j)/(2.0*sigma2));

	const double regularizer = sqrt(2*PI*sigma2*sigma);
	for (int i=0; i< result.size();i++)
		result[i] /= regularizer;

	return result;
	}

const QVVector QVVector::homogeneousCoordinates(const QPointF &point)
	{
	QVVector result(3, 1);
	result[0] = point.x(); result[1] = point.y();
	return result;
	}

//////////////////////////////////////////////

double QVVector::norm2() const
	{
	return sqrt(*this * *this);
	}

bool QVVector::containsNaN() const
	{
	for (int i = 0;  i < size(); i++)
                if (isnan(operator[](i)))
			return true;

	return false;
	}

QVVector QVVector::normalize()	const
	{
	return operator/(norm2());
	}

QVVector QVVector::abs() const
	{
	QVVector result (size());
	
	for (int i = 0;  i < size(); i++)
		result[i] = ABS(operator[](i));
	return result;
	}

double QVVector::max() const
	{
	double result = operator[](0);
	for (int i = 0;  i < size(); i++)
		result = MAX(operator[](i), result);
	return result;
	}

double QVVector::min() const
	{
	double result = operator[](0);
	for (int i = 0;  i < size(); i++)
		result = MIN(operator[](i), result);
	return result;
	}

double QVVector::sum() const
	{
	double accum = 0;
	foreach(double value, *this)
		accum += value;
		
	return accum;
	}

double QVVector::mean() const
	{
	return sum() / (double) size();
	}

double QVVector::median() const
	{
	QVVector sortedV = *this;
	qSort(sortedV.begin(), sortedV.end());
	
	return sortedV[sortedV.size() / 2];
	}

double QVVector::variance() const
	{
	const double avg = mean();
	double accum = 0;
	foreach(double value, *this)
		accum += POW2(value - avg);
		
        return accum / (double) (size());
	}

double QVVector::entropy(const double base) const
	{
	const double s = sum();

	double e = 0;
	foreach(double value, *this)
		e += (value == 0)? 0 : value * log(value / s);

	return - e / (s * log(base));
	}

int QVVector::maxIndex() const
	{
	if (size() <= 0)
		return -1;

	int maxIndex = 0;
	for (int i = 1; i < size(); i++)
		if (operator[](i) > operator[](maxIndex))
			maxIndex = i;
	return maxIndex;
	}

int QVVector::minIndex() const
	{
	if (size() <= 0)
		return -1;

	int minIndex = 0;
	for (int i = 1; i < size(); i++)
		if (operator[](i) < operator[](minIndex))
			minIndex = i;
	return minIndex;
	}

int QVVector::maxAbsIndex() const
	{
	if (size() <= 0)
		return -1;
			
	int maxIndex = 0;
	for (int i = 1; i < size(); i++)
		if ( ABS(operator[](i)) > ABS(operator[](maxIndex)) )
			maxIndex = i;
		
	return maxIndex;
	}

int QVVector::minAbsIndex() const
	{
	if (size() <= 0)
		return -1;
			
	int minIndex = 0;
	for (int i = 1; i < size(); i++)
		if ( ABS(operator[](i)) < ABS(operator[](minIndex)) )
			minIndex = i;
	
	return minIndex;
	}

void QVVector::set(const double value)
	{
	for (int i = 0; i < size(); i++)
		operator[](i) =  value;
	};

QVVector QVVector::subVector(const int firstIndex, const int lastIndex) const
	{
	Q_ASSERT(0 <= firstIndex);
	Q_ASSERT(firstIndex <= lastIndex);
	Q_ASSERT(lastIndex < this->size());

	QVVector result(lastIndex - firstIndex +1);
	for (int r = 0, i = firstIndex; i <= lastIndex; i++, r++)
		result[r] = operator[](i);

	return result;
	};

QVVector QVVector::scalarDivision(const double value) const
	{
	QVVector result = *this;
	for (int i = 0; i < size(); i++)
		result[i] /= value;

	return result;
	};

QVVector QVVector::scalarAdd(const double value) const
	{
	QVVector result = *this;
	for (int i = 0; i < size(); i++)
		result[i] += value;

	return result;
	};

QVVector QVVector::scalarSubstract(const double value) const
	{
	QVVector result = *this;
	for (int i = 0; i < size(); i++)
		result[i] -= value;

	return result;
	};

QVVector QVVector::scalarMultiplication(const double value) const
	{
	std::cout << "DEPRECATED: QVVector::scalarMultiplication(). Use QVVector::scalarProduct() instead" << std::endl;
	return scalarProduct(value);
	}

QVVector QVVector::scalarProduct(const double value) const
	{
	QVVector result = *this;
	for (int i = 0; i < size(); i++)
		result[i] *= value;
	return result;
	};


std::ostream& operator << ( std::ostream &os, const QVVector &vector )
	{
	const int size = vector.size();

	os << "QVVector (" << size << ") [ ";

	for (int i = 0; i < size; i++)
		os << qPrintable(QString("%1").arg(vector[i], -8, 'f', 6)) << " ";

	os << "]";
	return os;
	}

uint qHash(const QVVector &vector)
	{
	const int size = vector.size();
	double accum = 0;
	for (int i = 0; i < size; i++)
		accum += vector[i] / vector[size-i-1];

	return (uint) ((100000 * accum) / ((double) size));
	}


QVVector operator*(const double value, const QVVector &vector)
	{
	return vector.scalarProduct(value);
	}

QVVector operator+(const double value, const QVVector &vector)
	{
	return vector.scalarAdd(value);
	}

QVVector operator-(const double value, const QVVector &vector)
	{
	return vector.scalarSubstract(value);
	}
