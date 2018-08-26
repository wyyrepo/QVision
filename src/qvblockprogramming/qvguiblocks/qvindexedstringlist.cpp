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

#include <QVIndexedStringList>

QVIndexedStringList QVIndexedStringList::filter(const QString &str, Qt::CaseSensitivity cs) const
	{
	QVIndexedStringList isl = QStringList::filter(str, cs);
	if (isl.isEmpty()) isl.index = -1;
	else               isl.index = 0;
	return isl;
	}

QVIndexedStringList QVIndexedStringList::filter(const QRegExp &rx) const
	{
	QVIndexedStringList isl = QStringList::filter(rx);
	if (isl.isEmpty()) isl.index = -1;
	else               isl.index = 0;
	return isl;
	}

QVIndexedStringList QVIndexedStringList::operator+(const QVIndexedStringList &other) const
	{
	QVIndexedStringList n = *this;
	n += other;
	if (n.isEmpty()) n.index = -1;
	else             n.index = 0;
	return n;
	}

void QVIndexedStringList::sort()
	{
	QString st = value(index);
	QStringList::sort();
	index = indexOf(st);
	}

void QVIndexedStringList::append(const QString &str)
	{
	QStringList::append(str);
	if (index < 0) index = 0;
	}



QString QVIndexedStringList::getCurrent() const
	{
	if (index > -1) return QStringList::value(index);
	else return *(new QString());
	}

bool QVIndexedStringList::setIndex(int i)
	{
	if ((i > -2) && (i < QVIndexedStringList::size()))
		{
		index = i;
		return true;
		}
	return false;
	}

bool QVIndexedStringList::incIndex()
	{
	return setIndex(getIndex() + 1);
	}
bool QVIndexedStringList::decIndex()
	{
	return setIndex(getIndex() - 1);
	}
