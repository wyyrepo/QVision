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

#include <qvmath.h>
#include <QVTensor>

bool QVTensor::equals(const QVTensor &tensor) const
	{
	Q_ASSERT(dims.size() == indexIds.size());
	Q_ASSERT(tensor.dims.size() == tensor.indexIds.size());

	/// @todo assert para comprobar que el tamaño del buffer de datos de ambos tensores se corresponde con su valencia

	// Check valences for both tensors are equivalent
	if (dims != tensor.dims)
		return false;

	for (int i = 0; i < indexIds.size(); i++)
		if (indexIds[i] * tensor.indexIds[i] < 0 )
			return false;

	// Check data in both tensors is equal
	const double	*data1 = getReadData(),
			*data2 = tensor.getReadData();

	for (int i = 0; i < getDataSize(); i++)
		if (data1[i] != data2[i])
			return false;

	return true;
	}

QVTensor QVTensor::tensorProduct(const QVTensor &tensor) const
	{
	Q_ASSERT(dims.size() == indexIds.size());

	QVTensorValence indexList;

	for (int i = 0; i < getValence().size(); i++)
		indexList.append(getValence()[i]);

	for (int i = 0; i < tensor.getValence().size(); i++)
		indexList.append(tensor.getValence()[i]);

	QVTensor result(indexList);

	const double 	*src1Data = getReadData();
	const double 	*src2Data = tensor.getReadData();
	double		*destData = result.getWriteData();
	const int	vectorSize = tensor.getDataSize();

	for (int i = 0, destIndex = 0; i < getDataSize(); i++, destIndex += vectorSize)
		{
		cblas_dcopy(vectorSize, src2Data, 1, &(destData[destIndex]), 1);
		cblas_dscal(vectorSize, src1Data[i], &(destData[destIndex]), 1);
		}

	return result;
	}

QVTensor QVTensor::add(const QVTensor &tensor) const
	{
	Q_ASSERT(dims.size() == indexIds.size());
	/// @todo check tensor valences are compatible

	QVTensor result = *this;

	const double 	*tensorData = tensor.getReadData();
	double		*resultData = result.getWriteData();
// 	const int	dataSize = tensor.getDataSize();

	/// @todo use blas function cblas_axpy for data add

	for (int i = 0; i < getDataSize(); i++)
		resultData[i] += tensorData[i];

	return result;
	}

QVTensor QVTensor::substract(const QVTensor &tensor) const
	{
	Q_ASSERT(dims.size() == indexIds.size());
	/// @todo check tensor valences are compatible
	/// @todo use blas function cblas_axpy for data substraction

	QVTensor result = *this;

	const double 	*tensorData = tensor.getReadData();
	double		*resultData = result.getWriteData();
// 	const int	dataSize = tensor.getDataSize();

	for (int i = 0; i < getDataSize(); i++)
		resultData[i] -= tensorData[i];

	return result;
	}

QVTensor QVTensor::innerProduct(const QVTensor &tensor) const
	{
	Q_ASSERT(dims.size() == indexIds.size());

	const QMap<int, QVector<int> >	indexesQVTensor1 = getValence().getIndexesPositions(),
					indexesQVTensor2 = tensor.getValence().getIndexesPositions();

	int actualIndexSize = 0, actualQVTensor1Position = -1, actualQVTensor2Position = -1;

	QMapIterator< int, QVector<int> > idx(indexesQVTensor1);

	while (idx.hasNext())
		{
		idx.next();
		const int key = idx.key();
		const QVector<int> positionsIndex1 = indexesQVTensor1[key], positionsIndex2 = indexesQVTensor2[key];

		if (positionsIndex1.size() > 1)
			std::cerr << "ERROR, índice repetido en primer tensor de producto *." << std::endl;
		else if (positionsIndex2.size() > 1)
			std::cerr << "ERROR, índice repetido en segundo tensor de producto *." << std::endl;

		else if (positionsIndex1.size() == 1 && positionsIndex2.size() == 1)
			{
			const int position1 = positionsIndex1[0], position2 = positionsIndex2[0];
			const int indexSize = dims[position1];

			if (indexIds[position1] == tensor.indexIds[position2])
				std::cerr << "ERROR, índices iguales en ambos tensores en producto *." << std::endl;
			else	// we have a candidate index.
				if (indexSize > actualIndexSize)
					{
					actualIndexSize = indexSize;
					actualQVTensor1Position = position1;
					actualQVTensor2Position = position2;
					}
			}
		}

	if (actualQVTensor1Position == -1 && actualQVTensor2Position == -1)
		return this->tensorProduct(tensor).contract();
	else	if (actualQVTensor1Position == -1 || actualQVTensor2Position == -1)
		std::cerr << "ERROR, posición para el índice dominante no definida en producto *." << std::endl;

	// Move dominant index to end and start of the tensors
	QVTensorValence indexList1 = this->getValence(), indexList2 = tensor.getValence();

	QVTensor	t1 = this->transpose(actualQVTensor1Position, dims.size()-1), t2 = tensor.transpose(actualQVTensor2Position, 0);

	indexList1.removeAt(actualQVTensor1Position);
	indexList2.removeAt(actualQVTensor2Position);

	QVTensorValence resultIndexList;
	resultIndexList << indexList1 << indexList2;
	QVTensor result(resultIndexList);

	const int k = t2.dims[0], m = t1.getDataSize() / k, n = t2.getDataSize() / k;
 
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
			m, n, k, 1.0,
			t1.getReadData(), k,
			t2.getReadData(), n, 0.0,
			result.getWriteData(), n);
	
	return result;
	};

QVTensor QVTensor::outerProduct(const QVTensor &/*tensor*/) const
	{
	/// @todo: to be done.
	return *this;
	}

QVTensor QVTensor::renameIndexes(const QVTensorValence &indexList) const
	{
	Q_ASSERT(dims.size() == indexIds.size());
	/// @todo Assert for valence (variance/covariance and size) of new and old indexes is equivalent
	/// really? no, just check dimensions are compatible.
	QVTensor result = *this;

	for (int i = 0; i < indexList.size(); i++)
		result.indexIds[i] = indexList.at(i).id;

	return result.contract();
	}

//////////////////////////////////////////////////

QVTensorValence QVTensor::getValence()	const
	{
	Q_ASSERT(dims.size() == indexIds.size());

	QVTensorValence result;
	for (int i = 0; i < dims.size(); i++)
		result.append(QVTensorIndex(dims[i], indexIds[i]));
	return result;
	}

QVTensor QVTensor::slice(const QVTensorIndexValues &indexRangeList) const
	{
	Q_ASSERT(dims.size() == indexIds.size());
	const int numDims = dims.size();

	QVTensorIterator tensorIterator(dims, indexIds, indexRangeList);
	QVTensorValence idxList;

	for (int i=0; i< numDims; i++)
		if (tensorIterator.numElementsDimension(i) > 1)
			idxList.append(QVTensorIndex(tensorIterator.numElementsDimension(i), indexIds[i]));

	QVTensor result(idxList);

	double const	*srcData = getReadData();
	double		*destData = result.getWriteData();
	int		destIndexValue = -tensorIterator.getVectorSize();

	do cblas_dcopy(tensorIterator.getVectorSize(), &(srcData[tensorIterator.getVectorIndex()]), 1, &(destData[destIndexValue += tensorIterator.getVectorSize()]),1);
	while (tensorIterator.nextVector());

	return result;
	}

QVTensor QVTensor::transpose(const QVTensorIndex &index1, const QVTensorIndex &index2) const
	{
	Q_ASSERT(dims.size() == indexIds.size());

	int index1Position = -1, index2Position = -1;

	if (index1.id == index2.id)
		return *this;

	for (int n = 0; n< dims.size(); n++)
		{
		if (indexIds[n] == index1.id)
			index1Position = n;
		if (indexIds[n] == index2.id)
			index2Position = n;
		}

	if (index1Position == -1 || index2Position == -1)
		std::cerr << "ERROR, index not found in transpose." << std::endl;

	return transpose(index1Position, index2Position);
	}

QVTensor QVTensor::transpose(const QVTensorValence &indexList) const
	{
	Q_ASSERT(dims.size() == indexIds.size());

	QMap<int, QVector<int> > indexes = indexList.getIndexesPositions();
	for (int i = 0; i < indexIds.size(); i++)
		if (!indexes.contains(ABS(indexIds[i])))
			std::cerr << "ERROR, index " << indexIds[i] << " not found in transpose." << std::endl;

	QVector< int > order(indexIds.size());
	for (int i = 0; i < order.size(); i++)
		order[i] = indexes[ABS(indexIds[i])][0];

	return transpose(order);
	}

QVector<int> getSorting(const QVector<int> &values)
	{
	QVector<int> result(values.size()-1), dupe = values;
	for (int i = 0; i < values.size() -1; i++)
		{
		int pivote = i;
		for (int j = i+1; j < values.size(); j++)
			if (dupe[pivote] > dupe[j])
				pivote = j;
		result[i] = pivote;

		// Swap value of the 'pivote'
		const int temp = dupe[i];
		dupe[i] = dupe[pivote];
		dupe[pivote] = temp;
		}
	return result;
	}

QVTensor QVTensor::transpose(const int index1Position, const int index2Position) const
	{
	Q_ASSERT(dims.size() == indexIds.size());

	// If both indexes are the same, return the actual tensor
	if (index1Position == index2Position)
		return *this;

	QVector <int> order(dims.size());
	for (int i = 0; i < order.size(); i++)
		order[i] = i;

	order[MIN(index1Position, index2Position)] = MAX(index1Position, index2Position);
	order[MAX(index1Position, index2Position)] = MIN(index1Position, index2Position);

	return transpose(order);
	}

QVTensor QVTensor::transpose(const QVector<int> &order) const
	{
	Q_ASSERT(dims.size() == indexIds.size());

	// TODO: si el orden es el identidad (1, 2, 3, 4, ......, n), devolver copia de este tensor.
	QVector<int> sorting = getSorting(order);

	QVTensorValence idxList = getValence();

	bool orderedIndexes = true;
	int maxIndexPosition = 0;
	for (int i = 0; i < sorting.size(); i++)
		if (i != sorting[i])
			{
			idxList.swap(i, maxIndexPosition = sorting[i]);
			orderedIndexes = false;
			}

	// If there are no indexes to move, return the actual tensor
	if (orderedIndexes)
		return *this;

	QVTensor result(idxList);

	QVTensorIndexator indexator(result.dims);
	const int	vectorSize = indexator.getStep(maxIndexPosition);
	for (int i = sorting.size()-1; i >=0; i--)
		if (i != sorting[i])
			indexator.swapIndexes(i, sorting[i]);

	QVTensorIterator tensorIterator(indexator, maxIndexPosition);

	const double 	*srcData = getReadData();
	double		*destData = result.getWriteData();
	int		destIndexValue = -vectorSize;

	do cblas_dcopy(vectorSize, &(srcData[destIndexValue += vectorSize]), 1, &(destData[tensorIterator.getVectorIndex()]),1);
	while (tensorIterator.nextVector());

	return result;
	}

QVTensor QVTensor::contract() const
	{
	Q_ASSERT(dims.size() == indexIds.size());

	const QMap< int, QVector<int> > map = getValence().getIndexesPositions();

	// Create ordering for indexes, and list of indexes for result tensor.
	QVector<int> variableIndexesPositions, fixedIndexesPositions;
	QVector<int> variableDims;
	QVTensorValence fixedIndexList;

	bool dupedIndexes = false;
	QMapIterator< int, QVector<int> > idx(map);
	while (idx.hasNext())
		{
		idx.next();
		QVector<int> v = idx.value();

		switch(v.size())
			{
			case 1:
				fixedIndexesPositions.append(v[0]);
				fixedIndexList.append(QVTensorIndex(dims[v[0]],indexIds[v[0]]));
				break;
			case 2:
				if (indexIds[v[0]] != -indexIds[v[1]])
					std::cerr	<< "ERROR: two index apperances are not covariant: "
							<< indexIds[v[0]] << ", " << indexIds[v[1]] << std::endl;
				variableIndexesPositions.append(v[0]);
				variableIndexesPositions.append(v[1]);
				variableDims.append(dims[v[0]]);
				dupedIndexes = true;
				break;
			default:
				std::cerr << "ERROR: more than two index apperances in a tensor" << std::endl;
				break;
			}
		}

	// If there are no indexes to contract, return the actual tensor
	if (!dupedIndexes)
		return *this;

	QVector<int> inverseOrder = variableIndexesPositions + fixedIndexesPositions;
	QVector<int> order(inverseOrder.size());
	for (int i = 0; i < inverseOrder.size(); i++)
		order[inverseOrder[i]] = i;

	// Transpose original tensor, and create result tensor.
	const QVTensor Transposed = transpose(order);
	QVTensor result(fixedIndexList);

	// Create iterator for variable indexes, and indexator for tensor Transposed
	QVTensorIterator tensorIterator(variableDims);
	QVTensorIndexator indexator(Transposed.dims);

	const double 	*srcData = Transposed.getReadData();
	double		*destData = result.getWriteData();
	const int	vectorSize = result.getDataSize();

	for (int i = 0; i < vectorSize; i++)
		destData[i] = 0;

	do	{
		for (int i = 0; i < variableDims.size(); i++)
			{
			indexator.setIndex(2*i, tensorIterator.getIndex(i));
			indexator.setIndex(2*i+1, tensorIterator.getIndex(i));
			}

		cblas_daxpy(vectorSize, 1, &(srcData[indexator.getMatrixIndex()]), 1, destData, 1);
		}
	while (tensorIterator.nextVector());

	return result;
	}

double QVTensor::norm2() const
	{
	return sqrt(cblas_dnrm2(getDataSize(), getReadData(), 1));
	};

///////////////////////////////////////////////////////////////////

void leviCivitaAux(double *data, QVTensorIndexator &indexator, int index, bool parity = true)
	{
	const int numIndex = indexator.getNumberOfDimensions();

	if (index+1 == numIndex)
		{
		/*std::cout << "leviCivitaAux: indexes " << std::endl;
		for (int n = 0; n < numIndex; n++)
			std::cout << "\t" << indexator.getIndex(n);
		std::cout << std::endl;
		std::cout << "leviCivitaAux: set data " << indexator.getMatrixIndex() << std::endl;*/

		/// @todo Esto debería ser innecesario.
		int accum = 0;
		for (int n = 0; n < numIndex; n++)
			accum = accum*numIndex +  indexator.getIndex(n);

		//std::cout << "leviCivitaAux: set data " << indexator.getMatrixIndex() << ", " << accum << std::endl;
		//data[indexator.getMatrixIndex()] = parity?1:-1;
		data[accum] = parity?1:-1;
		}
	else	{
		leviCivitaAux(data, indexator, index+1, parity);

		for (int i = index+1; i < numIndex; i++)
			{
			indexator.swapIndexes(index, i);
			leviCivitaAux(data, indexator, index+1, !parity);
			indexator.swapIndexes(index, i);
			}
		}
	}

QVTensor QVTensor::leviCivita(const int dimension)
	{
	QVTensorValence valence;

	for (int i = 0; i < dimension; i++)
		valence = valence * QVTensorIndex(dimension);

	QVTensor result(valence);

	double *data = result.getWriteData();
	const int dataSize = result.getDataSize();
	for (int i = 0; i < dataSize; i++)
		data[i] = 0;

	QVTensorIndexator indexator = result.getIndexator();
	for (int i = 0; i < dimension; i++)
		indexator.setIndex(i,i);

	leviCivitaAux(data, indexator, 0);

	return result;	
	}

///////////////////////////////////////////////////////////////////

#include <QString>
std::ostream& operator << ( std::ostream &os, const QVTensor &tensor )
	{
	const QVector<int> dims = tensor.dims, indexIds = tensor.indexIds;
	const int	numDims = dims.size();

	Q_ASSERT(dims.size() == indexIds.size());

	if (numDims == 0)
		{
		os << "QVTensor <> () [ " << tensor.getReadData()[0] << " ]";
		return os;
		}

	os << "QVTensor <" << ((indexIds[0]<0)?"cov ":"") << ABS(indexIds[0]);

	for (int i=1; i<numDims; i++)
		os << ", " << ((indexIds[i]<0)?"cov ":"") << ABS(indexIds[i]);

	os << "> (" << dims[0];

	for (int i=1; i<numDims; i++)
		os << " x " << dims[i];

	os << ")" << std::endl;

	const double *data = tensor.getReadData();
	QVTensorIterator tensorIterator(dims);

	do	{
		if (tensorIterator.getIndex(numDims-1) == 0)
			{
			int index = numDims-2;
			while(index >= 0 && tensorIterator.getIndex(index) == 0)
					index--;

			for (int i = index; i< numDims-2; i++)
				os << qPrintable(QString(4*(i+1), ' ')) << "[" << std::endl;

			os << qPrintable(QString(4*(numDims-1), ' ')) << "[ ";
			}

		os << qPrintable(QString("%1").arg(data[tensorIterator.getVectorIndex()], -8, 'f', 6)) << " ";

		if (tensorIterator.getIndex(numDims-1) == dims[numDims-1]-1)
			{
			os << "]" << std::endl;
			int index = numDims-2;
			while(index >= 0 && tensorIterator.getIndex(index) == dims[index]-1)
				index--;

			for (int i = numDims-3; i>=index ; i--)
				os << qPrintable(QString(4*(i+1), ' ')) << "]" << std::endl;
			}
		} while (tensorIterator.nextVector());

	return os;
	}

