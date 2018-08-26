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

#ifndef QVVECTOR_H
#define QVVECTOR_H

#include <math.h>
#include <iostream>
#include <QVector>
#include <QPointF>
#include <qvdefines.h>

#ifdef GSL_AVAILABLE
#include <gsl/gsl_linalg.h>
#endif

#ifdef _MSC_VER
#ifdef max
#undef max
#endif // max

#ifdef min
#undef min
#endif // min
#endif // _MSC_VER

class QVMatrix;

/*!
@class QVVector qvmath/qvvector.h QVVector
@brief Implementation of numerical vectors.

@see @ref MatricesAndVectors

@ingroup qvmath
*/
class QVVector: public QVector<double>
    {
    public:
        /// @brief Default constructor for QVVector
        ///
        /// @param vector operand for the product
        QVVector(): QVector<double>()									{}

        /// @brief Constructor for QVVector
        ///
        /// @param int initializing size for the vector
        /// @param defaultValue default value to set all elements of the vector
        QVVector(const int size, const double defaultValue = 0): QVector<double>(size, defaultValue)	{}

        /// @brief Constructor for QVVector
        ///
        /// @param int initializing size for the vector
        /// @param defaultValues array of doubles, containing the inizialization data
        QVVector(const int size, const double *defaultValues): QVector<double>(size)
            {
            for (int i = 0; i < size; i++)
                operator[](i) = defaultValues[i];
            }

        /// @brief Copy constructor for QVVector
        ///
        /// @param vector vector to be copied
        QVVector(const QVVector &vector): QVector<double>(vector)					{}

        /// @brief Copy constructor for QVector
        ///
        /// @param vector vector to be copied
        QVVector(const QVector<double> &vector): QVector<double>(vector)				{}

        /// @brief Convert constructor from QList
        ///
        /// @param list List of double values to be converted to QVVector
        QVVector(const QList<double> &list): QVector<double>(list.toVector())				{}

        /// @brief Convert constructor from QVMatrix
        ///
        /// This function generates a vector containing the elements of a matrix
        /// in a row mayor order.
        ///
        /// @param matrix matrix to be converted.
        QVVector(const QVMatrix &matrix);

        /// @brief Copy constructor for gsl_vector
        ///
        /// @warning This constructor requires compatibility with the GSL library
        /// @param vector vector to be copied
        #ifdef GSL_AVAILABLE
        QVVector(const gsl_vector *vector): QVector<double>(vector->size)
                {
                for(int i = 0; i < size(); i++)
                    replace(i, gsl_vector_get(vector, i));
                }
        #endif

        /// @brief Convert constructor for QPoint
        ///
        /// @param vector vector to be copied
        QVVector(const QPoint &point): QVector<double>(2)	{ operator[](0) = point.x(); operator[](1) = point.y(); }

        /// @brief Convert constructor for QPointF
        ///
        /// @param vector vector to be copied
        QVVector(const QPointF &point): QVector<double>(2)	{ operator[](0) = point.x(); operator[](1) = point.y(); }

        ///////////////////////////////

        /// @brief Element access operator
        ///
                /// @param index main index value for data access
        inline double &operator()(const int index)
            { return operator[](index); }

        /// @brief Overloaded version of element access operator
        ///
        /// @param row main index value for data access
        /// @param col secondary index value for data access
        inline double operator()(const int index) const
            { return operator[](index); }

        /// @brief Vector dot product
        ///
        /// @param vector operand for the product
        /// @see dotProduct
        double operator*(const QVVector &vector) const		{ return dotProduct(vector); };

        /// @brief Vector cross product
        ///
        /// @param vector operand for the product
        /// @see crossProduct
        QVVector operator^(const QVVector &vector) const	{ return crossProduct(vector); };

        /// @brief Vector add
        ///
        /// @param vector term for the operation
        /// @see add
        QVVector operator+(const QVVector &vector) const	{ return add(vector); };

        /// @brief Vector substraction
        ///
        /// @param vector subtrahend for the operation
        /// @see substract
        QVVector operator-(const QVVector &vector) const	{ return substract(vector); };

        /// @brief Obtains the additive inverse of the vector
        ///
        /// Obtains a vector changing the sign of its elements.
        ///
        /// @see substract
        QVVector operator-() const					{ return operator*(-1.0); 	};


        /// @brief Scalar addition
        ///
        /// @param value value to multiply each component of the vector
        /// @see scalarAdd
        QVVector operator+(const double value) const		{ return scalarAdd(value); };

        /// @brief Scalar substraction
        ///
        /// @param value value to multiply each component of the vector
        /// @see scalarSubstract
        QVVector operator-(const double value) const		{ return scalarSubstract(value); };

        /// @brief Scalar multiplication
        ///
        /// @param value value to multiply each component of the vector
        /// @see scalarProduct
        QVVector operator*(const double value) const		{ return scalarProduct(value); };

        /// @brief Scalar division
        ///
        /// @param value value to divide each component of the vector
        /// @see scalarDivide
        QVVector operator/(const double value) const		{ return scalarDivision(value); };

        /// @brief Vector-matrix product
        ///
        /// @param matrix operand for the product
        QVVector operator*(const QVMatrix &matrix) const;

        /// @brief Compare operator
        ///
        /// @param vector vector to compare
        /// @see equals
        bool operator==(const QVVector &vector) const		{ return equals(vector); };

        /// @brief Add compound assignment operator
        ///
        /// @param vector vector to add
        QVVector & operator+=(const QVVector &vector)
            {
            const int size_ = size();
            const double *srcData = vector.constData();
            double *dstData = data();

            /// @todo use blas
            for (int i = 0; i < size_; i++)
                dstData[i] += srcData[i];

            return *this;
            }

        /// @brief Convert to QPointF operator
        ///
        /// Cast from homogeneous coordinates.
        ///
        operator QPointF() const
            {
            Q_ASSERT(size() > 1);
            Q_ASSERT(size() < 4);
            if (size() == 2)
                return QPointF(operator[](0), operator[](1));
            else
                return QPointF(operator[](0)/operator[](2), operator[](1)/operator[](2));
            }

        /// @brief Convert to gsl_vector * operator
        ///
        /// @warning This operator requires compatibility with the GSL library.
        /// @param value gsl_vector
        #ifdef GSL_AVAILABLE
        operator gsl_vector * () const
            {
            gsl_vector *result = gsl_vector_alloc(size());
            const double *data = this->data();
            for(uint i = 0; i < result->size; i++)
                gsl_vector_set (result, i, data[i]);
            return result;
            }
        #endif

        ////////////////

        /// @brief Gets the location of the element with the maximal value
        ///
        /// @returns -1 if the vector has zero elements, else the index of the largest element.
        int maxIndex() const;

        /// @brief Gets the location of the element with the minimal value
        ///
        /// @returns -1 if the vector has zero elements, else the index of the lowest element.
        int minIndex() const;

        /// @brief Gets the index of the element with the maximal absolute value
        ///
        /// @returns -1 if the vector has zero elements, else the index of the element with the greatest absolute value.
        int maxAbsIndex() const;

        /// @brief Gets the index of the element with the minimal absolute value
        ///
        /// @returns -1 if the vector has zero elements, else the index of the element with the lowest absolute value.
        int minAbsIndex() const;


        /// @brief Set vector elements to a value
        ///
        /// @param value value to set all the elements of the vector
        void set(const double value);

        /// @brief Obtains a sub-vector containing a given range of elements from the original vector.
        ///
        /// @param firstIndex First element in the value range for the resulting subvector.
        /// @param secondIndex Last element in the value range for the resulting subvector.
		/// @return A vector containing the elements from 'firstIndex' to 'lastIndex' of the original vector.
        QVVector subVector(const int firstIndex, const int lastIndex) const;

        /// @brief Scalar division
        ///
        /// @param value value to divide each component of the vector
        /// @see operator/(const double)
        QVVector scalarDivision(const double value) const;

        /// @brief Scalar addition
        ///
        /// @param value value to divide each component of the vector
        /// @see operator/(const double)
        QVVector scalarAdd(const double value) const;

        /// @brief Scalar substraction
        ///
        /// @param value value to divide each component of the vector
        /// @see operator/(const double)
        QVVector scalarSubstract(const double value) const;

        /// @brief Scalar multiplication
        ///
        /// @param value value to multiply each component of the vector
        /// @see operator*(const double)
        /// @deprecated use scalarProduct instead.
        QVVector scalarMultiplication(const double value) const;

        /// @brief Scalar multiplication
        ///
        /// @param value value to multiply each component of the vector
        /// @see operator*(const double)
        QVVector scalarProduct(const double value) const;

        /// @brief Norm 2 of the vector
        ///
        /// @see normalize
        double norm2() const;
            //{ return sqrt(*this * *this); }

        /// @brief Checks whether the vector contains a NaN value or not.
        ///
        /// @return true if any of the values contained in the vector is a NaN, false otherwise.
        bool containsNaN() const;


        /// @brief Normalize vector
        ///
                /// Divides each element of the vector by its euclidean norm.
        /// @see norm
        QVVector normalize() const;
            //{ return operator/(norm2()); }

        /// @brief Gets the absolute values of the vector elements.
        ///
        QVVector abs() const;

        /// @brief Maximal value contained in the vector
        ///
        double max() const;

        /// @brief Minimal value contained in the vector
        ///
        double min() const;

        /// @brief Accumulated value
        ///
        /// This function returns the sumatory of the elements of the vector.
        ///
        /// \f$ \bar{x} = \sum_{i=1}^n{x_i} \f$
        ///
        double sum() const;

        /// @brief Mean value
        ///
        /// This function returns the standard average value of the vector:
        ///
        /// \f$ \bar{x} = \frac{1}{n} \sum_{i=1}^n{x_i} \f$
        ///
        double mean() const;

        /// @brief Median value
        ///
        /// This function returns the middle element in the list of sorted elements of the vector:
        ///
        double median() const;

        /// @brief Standard deviation
        ///
        /// This function returns a variance estimation of the elements in the vector:
        ///
                /// \f$ s^2 = \frac{1}{n} \sum_{i=1}^n\left(x_i - \overline{x} \right)^ 2 \f$
        ///
        double variance() const;

        /// @brief Shannon's entropy of a probability state vector
        ///
        /// This function calculates the entropy of the elements of the vector. These elements
                /// are considered as the probabilities of a random variable.
        /// Thus the sum of the vector elements must be equal to \f$ 1 \f$. The entropy is
        /// computed with the following formula:
        ///
        /// \f$ H(X) = - \sum_{i=1}^n p(x_i) \log_b p(x_i) \f$
        ///
        /// If the sum of the elements of the vector is not \f$ 1 \f$, they are normalized before computing
        /// the entropy. In the case of \f$ x_i = 0 \f$ for some \f$ x_i \f$ element of the vector, the value
        /// of the corresponding summand \f$ 0 \cdot log_b(0) \f$ is taken to be \f$ 0 \f$, which is consistent with
        /// the limit
        ///
        /// \f$ \lim_{p\to0+}p\log p = 0 \f$
        ///
        /// @param base base of the logarithm in the entropy equation.
        double entropy(const double base = 2) const;

        /// @brief Vector dot product
        ///
        /// @param vector operand for the product
        /// @see operator*
        double dotProduct(const QVVector &vector) const;

        /// @brief Vector cross product
        ///
        /// Computes the cross product for two vectors of size 3
        /// @param vector operand for the product
        /// @see operator^
        QVVector crossProduct(const QVVector &vector) const;

                /// @brief Outer product with another vector (to obtain a matrix)
                ///
                /// Computes the matrix M which is the outer product \f$ M = v \otimes v_2\f$  with another vector \f$ v_2 \f$
                /// @param vector operand for the product
                QVMatrix outerProduct(const QVVector &vector) const;

        /// @brief Vector add
        ///
        /// @param vector term for the operation
        /// @see operator+
        QVVector add(const QVVector &vector) const;

        /// @brief Vector substraction
        ///
        /// @param vector subtrahend for the operation
        /// @see operator-
        QVVector substract(const QVVector &vector) const;

        /// @brief Compare operator
        ///
        /// @param vector vector to compare
        /// @see equals
        bool equals(const QVVector &vector) const;

        ///////////////////////////

        /// @brief Vector of Gaussian distributed values.
        ///
        /// This function generates a vector containing homogeneously sampled values of a gaussian distribution.
        /// The size of the vector will equal the double of the radius of the gaussian distribution plus one.
        /// The standart deviation must be explicitally provided.
        ///
        /// @image html gaussvector.png
        ///
        /// @param radius Radius of the gaussian distribution.
        /// @param sigma Sigma of the gaussian distribution.
        static const QVVector gaussianVector(const int radius, const double sigma);

        /// @brief Creates a vector of random values
        ///
        /// This function returns a vector containing random values, from a uniform distribution [0,1].
        ///
        /// @param elements size of the vector
        static QVVector random(const int elements);

        /// @brief Vector of mexican hat wavelet distributed values.
        ///
                /// This function generates a vector containing homogeneously sampled values of a mexican hat wavelet function.
                /// The size of the vector will equal the double of the radius plus one.
        /// The standart deviation must be explicitally provided.
        ///
        /// @image html mexicanhatvector.png
        ///
        /// @param radius Radius of the wavelet distribution.
        /// @param sigma Sigma of the wavelet distribution.
        static const QVVector mexicanHatWaveletVector(const int radius, const double sigma);

                /// @brief Creates vector corresponding to the homogeneous coordinates of a 2D point (appending a value 1.0 on an added dimension).
        ///
        /// @param point 2D input point.
        static const QVVector homogeneousCoordinates(const QPointF &point);

        /// @brief Obtains the vector in homogeneous coordinates.
        ///
        /// This method simply copies the actual vector and adds an extra element containing the value 1.
        ///
        /// @return The vector in homogeneous coordinates.
        QVVector homogeneousCoordinates() const;

        /// @brief Obtain the matrix corresponding to the matrix multiplication notation for the vector cross product.
        ///
        /// This function returns a matrix which can be used in the cross product multiplication rewritten as a matrix product.
        /// The cross product between two vectors:
        ///
        /// \f$ \mathbf{a} \times \mathbf{b} = \mathbf{c} \f$
        ///
        /// Can be rewritten as the following matrix multiplication:
        ///
        /// \f$ [\mathbf{a}]_\times \mathbf{b} = \mathbf{c} \f$
        ///
        /// Where \f$ [\mathbf{a}]_\times \f$ is the so called <i>cross product matrix for vector</i>  \f$ \mathbf{a} \f$, which
        /// has the following structure:
        ///
        /// \f$ [\mathbf{a}]_{\times} = \left( \begin{array}{ccc} 0 & -a_3 & a_2 \\ a_3 & 0 & -a_1 \\ -a_2 & a_1 & 0\end{array} \right)\f$
        ///
        /// This function only works on vectors of size 3.
        ///
        /// @param vector vector to compare
        /// @see equals
        QVMatrix crossProductMatrix() const;

        /// @brief Returns this vector in the form of a row matrix.
        QVMatrix toRowMatrix() const;

        /// @brief Returns this vector in the form of a column matrix.
        QVMatrix toColumnMatrix() const;
    };

/*! @brief Vector-scalar product

@param value factor for the operation.
@see scalarProduct
*/
QVVector operator*(const double value, const QVVector &);

/*! @brief Vector-scalar addition

@param value addendum for the operation.
@see scalarAddition
*/
QVVector operator+(const double value, const QVVector &);

/*! @brief Vector-scalar substraction operator

@param value value to substract.
@see scalarSubstraction
*/
QVVector operator-(const double value, const QVVector &);

/// @todo detailed description should follow
/// @ingroup qvmath
std::ostream& operator << ( std::ostream &os, const QVVector &vector );

/// @todo detailed description should follow
/// @ingroup qvmath
uint qHash(const QVVector &vector);

#endif

