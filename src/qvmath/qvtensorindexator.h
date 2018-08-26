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

#ifndef QVTENSORINDEXATOR_H
#define QVTENSORINDEXATOR_H

#include <qvmath/qvtensorindex.h>
#include <iostream>

#ifndef DOXYGEN_IGNORE_THIS
class QVTensorIndexator
    {
    public:
        int matrixIndex;
        QVector <int> indexes, steps, dims;

        QVTensorIndexator(const QVTensorIndexator &indexator):
            matrixIndex(indexator.matrixIndex), indexes(indexator.indexes), steps(indexator.steps), dims(indexator.dims)
            {};

        QVTensorIndexator(const QVector<int> &dims):
            matrixIndex(0), indexes(dims.size(),0), steps(dims.size()), dims(dims)
            {
            for (int i = dims.size() -1, accum = 1; i>=0; accum *= dims[i--])
                steps[i] = accum;
            }

        const QVector<int> getIndexes()		const	{ return indexes; }
        int getIndex(const int position)	const	{ return indexes[position]; }
        int getStep(const int position)	const	{ return steps[position]; }
        int getDim(const int position)	const	{ return dims[position]; }
        int getMatrixIndex()		const	{ return matrixIndex; }
        int getNumberOfDimensions()	const	{ Q_ASSERT(indexes.size() == steps.size() && steps.size() == dims.size()); return dims.size(); }

        void swapIndexes(const int position1, const int position2)
            {
            if (position1 == position2)
                return;

            const int temp1 = indexes[position1];
            indexes[position1] = indexes[position2];
            indexes[position2] = temp1;

            const int temp2 = steps[position1];
            steps[position1] = steps[position2];
            steps[position2] = temp2;

            const int temp3 = dims[position1];
            dims[position1] = dims[position2];
            dims[position2] = temp3;
            }

        void setIndex(const int position, const int value)
            {
            const int oldValue = indexes[position];
            indexes[position] = value;
            matrixIndex += (value - oldValue)*steps[position];
            }

        void setMatrixIndex(const int matIndex)
            {
            indexes[0] = matIndex / steps[0];
            for (int i = 1; i < indexes.size(); i++)
                indexes[i] = (matIndex/steps[i])%(steps[i-1]/steps[i]);
            }
    };

class QVTensorIterator
    {
    private:
        QVector< int > numIndexes, indexes;
        QVector < QVector < int > > elementIndexes;
        int maxPartialIndex;
        QVTensorIndexator indexator;

    public:
        QVTensorIterator(const QVector<int> &dims, const QList<int> orderList = QList<int>()):
            numIndexes(dims), indexes(dims.size(),0), elementIndexes(dims.size()), maxPartialIndex(dims.size()-1), indexator(dims)
            { Q_UNUSED(orderList); }

        QVTensorIterator(const QVTensorIndexator &indexator, const int maxPartialIndex):
            numIndexes(indexator.dims), indexes(indexator.dims.size(),0), elementIndexes(indexator.dims.size()),
            maxPartialIndex(maxPartialIndex), indexator(indexator)
            { }

        QVTensorIterator(const QVector<int> &dims, const QVector<int> &indexId, const QVTensorIndexValues &indexRangeList):
            numIndexes(dims), indexes(dims.size(),0), elementIndexes(dims.size()), maxPartialIndex(dims.size()-1), indexator(dims)
            {
            const int numDims = dims.size();
            const QMap<int, QVector<int> > map = indexRangeList.getIndexesValues();

            for (int i = 0; i < numDims; i++)
                {
                elementIndexes[i] = map[indexId[i]];

                const int size = elementIndexes[i].size();
                if (size > 0)
                    {
                    numIndexes[i] = -size;
                    maxPartialIndex = i;
                    }
                }

            for (int i = 0; i < numDims; i++)
                indexator.setIndex(i,(numIndexes[i] >= 1)?indexes[i]:elementIndexes[i][indexes[i]]);
            }

        int getVectorIndex()				const	{ return indexator.matrixIndex; }
        int getVectorSize()				const	{ return indexator.steps[maxPartialIndex]; }
        const QVector<int> getIndexes()				const	{ return indexator.getIndexes(); }
        int getIndex(const int position)			const	{ return indexator.getIndex(position); }
        int numElementsDimension(const int indexPos)	const	{ return ABS(numIndexes[indexPos]); }

        bool nextVector()
            {
            int actualIndex = maxPartialIndex+1;

            while(--actualIndex >= 0)
                if (++indexes[actualIndex] < ABS(numIndexes[actualIndex]))
                    {
                    const int newIndexValue1 = (numIndexes[actualIndex] >= 1)?indexes[actualIndex]:elementIndexes[actualIndex][indexes[actualIndex]];
                    indexator.setIndex(actualIndex, newIndexValue1);
                    break;
                    }
                else	{
                    indexes[actualIndex] = 0;
                    const int newIndexValue2 = (numIndexes[actualIndex] >= 1)?indexes[actualIndex]:elementIndexes[actualIndex][indexes[actualIndex]];
                    indexator.setIndex(actualIndex, newIndexValue2);
                    }

            if (actualIndex < 0)
                return false;

            return true;
            }
    };

#endif

#endif
