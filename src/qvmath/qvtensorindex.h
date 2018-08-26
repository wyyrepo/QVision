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

#ifndef QVTENSORINDEX_H
#define QVTENSORINDEX_H

#include <QMap>
#include <qvmath.h>
#include <qvdefines.h>

#ifndef DOXYGEN_IGNORE_THIS
class QVTensorIndexRange;
class QVTensorIndexValues: public QList<QVTensorIndexRange>
	{
	public:
		QVTensorIndexValues(): QList<QVTensorIndexRange>()	{}

		const QVTensorIndexValues operator&(const QVTensorIndexRange &indexRange) const
			{
			QVTensorIndexValues result = *this;
			result.append(indexRange);
			return result;
			}

		QMap<int, QVector<int> > getIndexesValues() const;
	};

class QVTensorIndexRange
	{
	friend class QVTensorIndex;

	public:
		int id, rangeMin, rangeMax;

		QVTensorIndexRange(const QVTensorIndexRange &tensorIndexRange):
			id(tensorIndexRange.id), rangeMin(tensorIndexRange.rangeMin), rangeMax(tensorIndexRange.rangeMax) { }

		const QVTensorIndexValues operator&(const QVTensorIndexRange &indexRange) const
			{
			QVTensorIndexValues result;
			result.append(*this);
			result.append(indexRange);
			return result;
			}

		operator QVTensorIndexValues() const
			{
			QVTensorIndexValues result;
			result.append(*this);
			return result;
			}
	private:
		QVTensorIndexRange(const int id, const int rangeMin, const int rangeMax):	id(id), rangeMin(rangeMin), rangeMax(rangeMax)	{ }
	};

//////////////////////////////////////////////
// NOTA: identificador = -1, o 1 indica que el índice no existe, no concuerda con ningún otro.
class QVTensorIndex;
class QVTensorValence: public QList<QVTensorIndex>
	{
	public:
		QVTensorValence(): QList<QVTensorIndex>()	{}

		const QVTensorValence operator*(const QVTensorIndex &index) const
			{
			QVTensorValence result = *this;
			result.append(index);
			return result;
			}

		const QVTensorValence operator&(const QVTensorIndex &index) const
			{
			QVTensorValence result = *this;
			result.append(index);
			return result;
			}

		const QVTensorValence operator+(const QVTensorValence &indexList) const
			{ return *this + indexList; }

		QMap<int, QVector<int> > getIndexesPositions() const;
	};

#endif

/*!
@class QVTensorIndex qvmath/qvtensorindex.h QVTensorIndex
@brief Indexes for tensors.

The valence of a particular tensor is the number and type of array indices.
QVTensorIndex class can be used to create index objects, and compose list of them to indicate the valence of a tensor, at construction.

See @ref QVTensor class for detailed usage.

@see QVTensor
@ingroup qvmath
*/
class QVTensorIndex
	{
	public:
		/// @brief Creates a new index name object.
		///
		QVTensorIndex(const int dimension): dim(dimension), id(nextIndexId++)							{ }

		/// @brief Copy constructor for tensor index name objects.
		///
		/// Copies an index.
		QVTensorIndex(const QVTensorIndex &tensorIndex): dim(tensorIndex.dim), id(tensorIndex.id)					{ }

		/// @brief Gets the covariant version of this index name
		/// @return a QVTensorIndex object, which is the covariant version of the original one
		QVTensorIndex cov()		const { return QVTensorIndex(*this, true); }

		/// @brief Gets the covariant version of this index name
		/// @return a QVTensorIndex object, which is the covariant version of the original one
		QVTensorIndex covariant()	const { return QVTensorIndex(*this, true); }

		/// @brief Gets a value state containing a range of integer values for the index name
		/// @return an object containing a range of values for the index name
		QVTensorIndexRange range(const int min, const int max)	const { return QVTensorIndexRange(ABS(id), min, max); }

		/// @brief Gets a value state containing an integer, for the index name
		/// @return an object containing the value for the index name
		const QVTensorIndexRange operator[](const int value)	const { return QVTensorIndexRange(ABS(id), value, value); }

		#ifndef DOXYGEN_IGNORE_THIS
		QVTensorIndex(): dim(0), id(1)												{ }
		QVTensorIndex(const int dimension, const int ident): dim(dimension), id(ident)						{ }
		QVTensorIndex(const QVTensorIndex &tensorIndex, bool variate): dim(tensorIndex.dim), id((variate?-1:1)*tensorIndex.id)	{ }

		int dim, id;
		const QVTensorValence operator*(const QVTensorIndex &index) const
			{
			QVTensorValence result;
			result.append(*this);
			result.append(index);
			return result;
			}

		bool operator==(const QVTensorIndex &/*index*/) const
			{ return true; }

		operator QVTensorValence() const
			{
			QVTensorValence result;
			result.append(*this);
			return result;
			}

		const QVTensorValence operator*(const QVTensorValence &indexList) const
			{
			QVTensorValence result = *this;
			result << indexList;
			return result;
			}
		#endif
	private:
		static int nextIndexId;
		static QVTensorIndex anyIndex;
	};
#endif
