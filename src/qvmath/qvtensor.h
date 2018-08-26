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

#ifndef QTENSOR_H
#define QTENSOR_H

#include <iostream>

#include <qvmath/qvblasdatabuffer.h>
#include <qvmath/qvtensorindexator.h>

/*!
@class QVTensor qvmath/qvtensor.h QVTensor
@brief Implementation of <a href="http://en.wikipedia.org/wiki/Classical_treatment_of_tensors">tensors</a>, a generalization for matrices and vectors.

Opossed to scalar values, vector and matrices contain numeric values indexed by one and two index values respectively. <em>A</em> tensor is a generalization of these concepts, that can contain numeric values indexed by a set of fixed indexes.

@section TensorCreation Tensor creation

Tensors are created using index objects. These index objects are created using the class @ref QVTensorIndex , indicating their size. An example of tensor creation follows:

\code
QVTensorIndex i = 10, j = 20, k = 7;
QVTensor A( i * j * k );

[...]
\endcode

Indexes <em>i</em>, <em>j</em> and <em>k</em> have respectively sizes 10, 20, and 7, so tensor <em>A</em> will have 10x20x7 elements, and tree dimensions, of sizes 10, 20 and 7 each one. It is shown that @ref QVTensorIndex objects are composed using * operator, to express the <a href="http://en.wikipedia.org/wiki/Tensor#Tensor_valence">valence of the tensor</a>.

Method @ref cov() from the @ref QVTensorIndex class can be used to get a covariant version of an index. So, for example, we can create a second tensor <em>B</em>, similar to <em>A</em>, but with covariant index <em>j</em>, like this:

\code
QVTensorIndex i = 10, j = 20, k = 7;
QVTensor A( i * j * k );

[...]

QVTensor B( i * j.cov() * k );
\endcode

An index can be copied to another one, both becoming interchangeable and indistinguishable. For example, with the following code:

\code
QVTensorIndex i = 10, j = 20, k = 7, i2 = i, j2 = j.cov().cov(), k2 = k, jCov = j.cov();
QVTensor A( i * j * k ), B( i2 * j2.cov() * k2 ), C( i2 * jCov * k );
\endcode

Tensors <em>A</em>, <em>B</em> and <em>C</em> will have the same valence, and will behave the same for tensor product, and contraction operations. Also notice that index <em>j</em> is equivalent to index <em>j.cov().cov()</em>, because applying double covariance to an index returns the original index.

@section TensorSlice Slice operation
Method @ref slice is the equivalent to a <a href ="http://en.wikipedia.org/wiki/Submatrix">submatrix</a> extractor, for tensors. It can be used to extract sub-tensors from tensors, specifying a value, or a list of values, for the indexes. For example, in this code:

\code
QVTensorIndex i = 10, j = 20, k = 7, l = 10;
QVTensor A( i * j.cov() * k.cov() * l);

[...]

QVTensor B = A(i[10]);
\endcode

tensor <em>B</em> will contain all the values of tensor <em>A</em>, for which index <em>i</em> equals the value 10. So, tensor B will have only tree indexes, covariated <em>j</em>, covariated <em>k</em>, and <em>l</em>. It can be specified several values for the same index, using operator <em>&</em>, like this:

\code
QVTensorIndex i = 10, j = 20, k = 7, l = 10;
QVTensor A( i * j.cov() * k.cov() * l);

[...]

QVTensor B = A(i[10] & i[5] & i[0]);
\endcode

in this case, tensor <em>B</em> will be a fourth-dimensional tensor, with same valence as tensor <em>A</em>, only that it will have three elements for index <em>i</em>. For multiple value slicing, it can be useful the method @ref range from the class QVTensorIndex:

\code
QVTensorIndex i = 10, j = 20, k = 7, l = 10;
QVTensor A( i * j.cov() * k.cov() * l);

[...]

QVTensor B = A(i.range(2,5));
\endcode

it selects in the slice operation all the values from 2 to 5, for the index <em>i</em>. Also, slicing for multiple indexes can be done, combining values for the different indexes in the same slice operation, for example, in the following code:

\code
QVTensorIndex i = 10, j = 20, k = 7;
QVTensor A( i * j.cov() * k ), B;

[...]

B = A(i[10] & i.range(3,5) & j[3] & j[1] & j.range(0,1));
\endcode

tensor <em>B</em> will keep all the values from tensor <em>A</em>, for which index <em>i</em> equals 10, 3, 4 and 5, index <em>j</em> equals 3, 1, 0, and 1.

@section TensorTranspose Transpose operation
Method @ref transpose works like a <a href="http://en.wikipedia.org/wiki/Transpose">transpose operation for matrices</a>, over tensors. It can swap the location for two indexes in the valence of the tensor, or re-order their locations at will. Two versions of method transpose are provided: the first one takes as argument the valence for the resulting tensor, as it is specified in the constructor, as commented in the @ref TensorCreation section:

\code
QVTensorIndex i = 10, j = 20, k = 10;
QVTensor A( i * j * k ), B;

[...]

B = A.transpose( k * j * i.cov() );
\endcode

This can transpose indexes in the tensor in any order, depending on the order in the valence. The second version is used as follows:

\code
QVTensorIndex i = 10, j = 20, k = 10;
QVTensor A( i * j * k ), B;

[...]

B = A.transpose( i, k );
\endcode

It takes two indexes, and swap their positions, leaving the rest of the indexes at the same place.

@section TensorContraction Tensor contraction
The operator () defined in tensors can be used to obtain the <a href="http://en.wikipedia.org/wiki/Tensor_contraction">contraction of a tensor</a>. The tensor should have two indexes with same size and one of them should be covariant, and the other one contravariant. The following code is an example of the use of this operator:

\code
QVTensorIndex i = 10, j = 20, k = 10;
QVTensor A( i * j * k.cov() ), B;

[...]

B = A( i * j * i.cov() );
\endcode

This makes <em>B</em> a tensor with one dimension of size 20 (corresponding to index <em>j</em>), which is obtained contracting indexes <em>i</em> and <em>k</em> from tensor <em>A</em>. Contraction can be done over multiple indexes at a time. For example, the following code will be correct:

\code
QVTensorIndex i = 10, j = 20, k = 10, l = 7, m = 20;
QVTensor A( i * j * k.cov() * l * m.cov() ), B;

[...]

B = A( i * j * i.cov() * l * j.cov() );
\endcode

This contracts indexes <em>i</em> and <em>k</em>, <em>j</em> and <em>m</em> from tensor <em>A</em>, and store the result in tensor <em>B</em>.

@section TensorProduct Tensor product

<a href="http://en.wikipedia.org/wiki/Tensor_product">Tensor product</a> can be commonly done with operator *. It performs an inner product between both operand tensors, and contracts the indexes of the resulting tensor:

\code
QVTensorIndex i = 10, j = 20, k = 10, l = 14;
QVTensor A( i * j * k.cov() ), B(l * i.cov() * k);

[...]

QVTensor C = A( i * j * k.cov() ) * B(l * i.cov() * k);
\endcode

The operator () can be used to specify the contracting indexes in the operation <em>ex professo</em>, if both tensors were constructed with different indexes. For example, the following code would create a tensor contracting the same indexes as the previous code did:

\code
QVTensorIndex i = 10, j = 20, k = 10, l = 14, m = 20, n = 10;
QVTensor A( i * j * k.cov() ), B(l * m.cov() * n);

[...]

QVTensorIndex i1 = 10, i2 = 20, i3 = 10, i4;
QVTensor C = A( i1 * i2 * i3.cov() ) * B(i4 * i1.cov() * i3);
\endcode

@section DataAccesing Data accessing
Tensor copying uses <em>copy-on-write</em> policy for its data buffer. This means that when performed a copy from one vector object over another, both objects will share the same data buffer, until a write operation is attempted over the data of one of them. In that case it is necesary to dupe the data, and let each tensor object to have its own copy of the data before the write operation takes place, to avoid writing operations to replicate changes at tensors supposedly different.

So, tensors have two operations to access to their data. One gets the data buffer for read accesses, not duplicating the data buffer if it is shared, and the other one allows writing on the data of the tensor, duping the data buffer if it is shared beforehand.

Method @ref getReadData returns a read only pointer to the data buffer. It can be used to read values on the elements of the tensor. Method @ref getDataSize returns the number of elements contained in the tensor. An example usage of both methods:

\code
QVTensorIndex i = 10, j = 20, k = 10, l = 14, m = 20, n = 10;
QVTensor A( i * j * k.cov() );

[...]

// gets the sum of all the elements on tensor A
const double sum = 0, *data = A.getReadData();
for (int n = 0; n < A.getDataSize(); n++)
    sum += data[i];

[...]

\endcode

Method @ref getWriteData can be used to get a writable pointer to the data buffer. An example usage:

\code
QVTensorIndex i = 10, j = 20, k = 10, l = 14, m = 20, n = 10;
QVTensor A( i * j * k.cov() );

[...]

// multiplies by a factor, and decrements it by one unit, each element of the tensor A.
double *data = A.getWriteData();
for (int n = 0; n < A.getDataSize(); n++)
    data[i] = 2*data[i] + 1;

[...]

\endcode
@ingroup qvmath
*/
class QVTensor
    {
    public:
        // Constructors

        /// @brief Copy constructor.
        ///
        /// Creates a tensor object and copy the <a href="http://en.wikipedia.org/wiki/Tensor#Tensor_valence">valence</a> and data from a given one.
        QVTensor(const QVTensor &tensor): dataSize(tensor.dataSize), dims(tensor.dims), indexIds(tensor.indexIds), data(tensor.data)	{ }

        /*! @brief Index list constructor.

        Creates a new tensor from a given valence, represented by a QVTensorIndex list. See @ref TensorUsage section for a detailed description about its usage.
        @param indexList a QVTensorValence, created from a list of QVTensorIndex objects.
        @todo check that no indexes are repeated in the indexList, even covariated ones
        */
        QVTensor(const QVTensorValence &indexList = QVTensorValence()):
            dataSize(1), dims(indexList.size()), indexIds(indexList.size())
            {
            for (int n = 0; n < indexList.size(); n++)
                {
                indexIds[n] = indexList.at(n).id;
                dataSize *= (dims[n] = indexList.at(n).dim);
                }

            // In the case of an empty valence, the tensor will be a scalar
            data = new QBlasDataBuffer(dataSize);
            }

        // Operators

        /// @brief Compare operator for tensors
        ///
        /// @param tensor operand for the compare operation.
        /// @return true if <a href="http://en.wikipedia.org/wiki/Tensor#Tensor_valence">valence</a> and data are equal of both tensors, else false.
        bool operator==(const QVTensor &tensor) const			{ return equals(tensor);		};

        /// @brief Compare operator for tensors
        ///
        /// @param tensor operand for the compare operation.
        /// @return false if <a href="http://en.wikipedia.org/wiki/Tensor#Tensor_valence">valence</a> and data are equal of both tensors, else true.
        bool operator!=(const QVTensor &tensor) const			{ return !equals(tensor);		};

        /// @brief Tensor product
        ///
        /// @param tensor operand for the product operation.
        /// @see tensorProduct
        QVTensor operator*(const QVTensor &tensor) const			{ return innerProduct(tensor); 	};

        /// @brief Tensor add
        ///
        /// @param tensor operand for the add operation.
        /// @see add
        QVTensor operator+(const QVTensor &tensor) const			{ return add(tensor); 	};

        /// @brief Tensor substraction
        ///
        /// @param tensor subtrahend for the operation.
        /// @see substract
        QVTensor operator-(const QVTensor &tensor) const			{ return substract(tensor); 	};

        /// @brief Outer product
        ///
        /// @see outerProduct(const QVTensor &tensor) const
        QVTensor operator^(const QVTensor &tensor) const			{ return outerProduct(tensor);		};

        /// @brief Index renaming and contracting operator
        ///
        /// See sections @ref TensorContraction and @ref TensorProduct for usage of this operator.
        /// @see renameIndexes
        QVTensor operator()(const QVTensorValence &indexList) const	{ return renameIndexes(indexList);	};

        // Operation methods

        /// @brief Gets the size of the data array.
        ///
        /// This returns the number of elements in the tensor.
        /// @return the product of the sizes of all the indexes in the tensor.
        int getDataSize()			const	{ return dataSize; }

        /// @brief Gets a read-only reference to the data buffer of the tensor
        ///
        /// @return a constant pointer to the data buffer of the tensor
        const double *getReadData()		const	{ return data->getReadData(); }

        /// @brief Gets a reference of the data buffer of the tensor for read and write accesses
        ///
        /// @return a pointer to the data buffer of the tensor
        double *getWriteData()				{ return data->getWriteData(); }

        /// @brief Gets <a href="http://en.wikipedia.org/wiki/Tensor#Tensor_valence">valence</a> of the tensor.
        ///
        /// This function can be used to obtain a list of the QVTensorIndex objects that represente the valence of the tensor.
        /// @return a QList<QVTensorIndex> object, containing the QVTensorIndex objects corresponding to the indexes of the tensor.
        QVTensorValence getValence() const;

        /// @brief Get a subtensor from a tensor
        ///
        /// Like with matrices, it is possible to extract a part of a tensor, given a list of values
        /// for some of its indexes.
        /// For further details about the use of this function, see section @ref TensorSlice.
        /// @param indexRangeList list of range values for indexes.
        /// @see transpose(const QVTensorIndex &, const QVTensorIndex &) const;
        QVTensor slice(const QVTensorIndexValues &indexRangeList) const;

        /// @brief Change the order of the indexes in the tensor.
        ///
        /// This function reorders the indexes of the tensor.
        /// For further details about the use of this function, see section @ref TensorTranspose.
        /// @param indexList new valence for the tensor, expressed as a list of indexes.
        /// @see transpose(const QVTensorIndex &, const QVTensorIndex &) const;
        QVTensor transpose(const QVTensorValence &indexList) const;

        /// @brief Overloaded version of transpose function
        ///
        /// This overloaded version of transpose method swaps the location of two given indexes in the tensor.
        /// For further details about the use of this function, see section @ref TensorTranspose.
        /// @see transpose(const QVTensorValence &) const
        QVTensor transpose(const QVTensorIndex &i, const QVTensorIndex &j) const;

        /// @brief Tensor add
        ///
        /// @param tensor operand for the add operation.
        /// @see operator+
        QVTensor add(const QVTensor &tensor) const;

        /// @brief Tensor substraction
        ///
        /// @param tensor subtrahend for the operation.
        /// @see operator-
        QVTensor substract(const QVTensor &tensor) const;

        /// @brief Obtains the tensor product of two tensors
        ///
        /// @param tensor operand for the tensor product.
        /// For further details about the use of this function, see section @ref TensorProduct.
        /// @return the contracted tensor resulting from the inner product of the actual tensor and the one given through the parameter.
        /// @see operator*(const QVTensorValence &) const
        QVTensor tensorProduct(const QVTensor &tensor) const;

        /// @brief Obtains the inner product of two tensors
        ///
        /// @param tensor operand for the inner product.
        /// @return the contracted tensor resulting from the tensor product of the actual tensor and the one given through the parameter.
        /// @see operator*(const QVTensorValence &) const
        QVTensor innerProduct(const QVTensor &tensor) const;

        /// @brief Obtains the outer product of two tensors
        ///
        /// @param tensor operand for the outer product.
        /// @return outer product of actual tensor and
        /// @see operator^(const QVTensorValence &) const
        QVTensor outerProduct(const QVTensor &tensor) const;

        /// @brief Check equivalence between tensors
        ///
        /// @param tensor operand for the compare operation.
        /// @return true if the given tensor has equivalent valence and equal content of the data buffer.
        /// @see operator==(const QVTensorValence &) const
        bool equals(const QVTensor &tensor) const;

        /// @brief Index renaming and contracting
        ///
        /// This method is equivalent to using operator().
        /// See sections @ref TensorContraction and @ref TensorProduct for usage of that operator.
        /// @param indexList new indexes for the tensor.
        /// @see operator()(const QVTensorValence &indexList) const
        QVTensor renameIndexes(const QVTensorValence &indexList) const;

        /// @brief Gets tensor indexator
        ///
        /// This functions copies content of the data buffer, valence, and index names on this vector, over a given one.
        /// @param tensor tensor to be copied.
        /// @return a reference to this vector
        /// @see operator=(const QVTensorValence &)
        QVTensorIndexator getIndexator()	{ return QVTensorIndexator(dims); };

        /// @brief Gets the <a href="http://en.wikipedia.org/wiki/Norm_%28mathematics%29">norm<sup>2</sup></a> for tensor.
        ///
        /// @return norm-2 of the tensor.
        double norm2() const;

        /// @brief Gets <a href="http://en.wikipedia.org/wiki/Levi-Civita_symbol">Levi Civita</a> symbol tensor.
        ///
        /// @param dimension number of dimensions of the tensor
        /// @return a tensor containing the Levi Civita symbol.
        static QVTensor leviCivita(const int dimension);

        #ifndef DOXYGEN_IGNORE_THIS
        // These methods won't be documented, but will be available for testing purposes
        QVTensor contract() const;
        #endif

    private:
        friend std::ostream& operator << ( std::ostream &os, const QVTensor &tensor );

        // These should be private
        QVTensor transpose(const QVector<int> &sorting) const;
        QVTensor transpose(const int index1Position, const int index2Position) const;
        QVTensor antisymmetrization(const QVTensor &tensor) const;

        // Tensor data
        int dataSize;
        QVector <int> dims;
        QVector <int> indexIds;
        QSharedDataPointer< QBlasDataBuffer > data;
    };

std::ostream& operator << ( std::ostream &os, const QVTensor &tensor );

//Q_DECLARE_METATYPE(QVTensor);

#endif
