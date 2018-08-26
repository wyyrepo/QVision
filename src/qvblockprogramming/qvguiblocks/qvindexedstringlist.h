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

#ifndef QVINDEXEDSTRINGLIST_H
#define QVINDEXEDSTRINGLIST_H

#include <QStringList>
#include <QMetaType>

/*!
@class QVIndexedStringList qvblockprogramming/qvguiblocks/qvindexedstringlist.h QVIndexedStringList
@brief String List with a current string index.

This class represents a string list with an index, the index marks the current string in the list. The index values are:
	-1, there are no items in the list.
	0 ... n-1, the strings of the list.

@ingroup qvdta
*/
class QVIndexedStringList: public QStringList
	{
	private:
		int index;

	public:
		/// @brief Constructs a void QVIndexedStringList.
		/// Its index must be -1.
		///
		QVIndexedStringList() : QStringList(), index(-1) { }

		/// @brief Copy constructor from a QVIndexedStringList.
		///
		QVIndexedStringList( const QVIndexedStringList& l ) : QStringList(l), index(l.index) { }

		/// @brief Copy constructor from a QStringList.
		/// Its index must be 0 or -1 if is empty.
		///
		QVIndexedStringList( const QStringList& l ) : QStringList(l), index(l.isEmpty()? -1 : 0) { }

		/// @brief Copy constructor from a QString.
		/// Creates a new QVIndexedStringList that contains the gives string an its index is 0 (the first item of the list).
		///
		QVIndexedStringList( const QString& i ) { append(i); index = 0; }

	#ifndef DOXYGEN_IGNORE_THIS
		//redefiniciones (los que devuelven listas y los que cambian ordenes)
		// quedan algunos métodos heredados que modifican la lista: erase, insert, removeAll, removeFirst, removeLast, Swap
		void sort();
		QVIndexedStringList filter(const QString &str, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;
		#ifndef QT_NO_REGEXP
		QVIndexedStringList filter(const QRegExp &rx) const;
		#endif
		QVIndexedStringList operator+(const QVIndexedStringList &other) const;
	#endif

		/// @brief Return the index.
		///
		int getIndex() const { return index; }

		/// @brief Return the current string, marked by the index.
		///
		QString getCurrent() const;

		/// @brief Sets the index to i.
		/// @param i the new index.
		///
		/// if  (i < -1) or (i >= list size), do nothing and return false.
		///
		/// @return if the change has been done.
		///
		bool setIndex(int i);

		/// @brief Increment the index.
		/// if (i >= list size -1), do nothing and return false.
		///
		/// @return if the change has been done.
		///
		bool incIndex();

		/// @brief Decrement the index.
		/// if (i < 0), do nothing and return false.
		///
		/// @return if the change has been done.
		///
		bool decIndex();

		/// @brief Inserts a string as the last element of the list.
		/// if there are no elements in the list, i becomes 0.
		///
		void append(const QString &str);
	};

Q_DECLARE_METATYPE(QVIndexedStringList);
#endif

