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

#include <qvmath/qvtensorindex.h>

int QVTensorIndex::nextIndexId = 2;

std::ostream& operator<<( std::ostream &os, const QVTensorIndex &tensorIndex)
	{
	os << ((tensorIndex.id<0)?"cov ":"") << tensorIndex.dim;
	return os;
	}

QMap<int, QVector<int> > QVTensorIndexValues::getIndexesValues() const
	{
	QMap<int, QVector<int> > result;
	for (int i = 0; i < size(); i++)
		for (int j = at(i).rangeMin; j <= at(i).rangeMax; j++)
			result[ABS(at(i).id)].append(j);

	return result;
	}

QMap<int, QVector<int> > QVTensorValence::getIndexesPositions() const
	{
	QMap<int, QVector<int> > result;
	for (int i = 0, position = 0; i < size(); i++)
		result[ABS(at(i).id)].append(position++);

	return result;
	}

