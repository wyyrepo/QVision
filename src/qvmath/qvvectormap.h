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

#include <QMap>
#include <QList>
#include <QVVector>

#include <qvmath.h>

#ifndef QVVECTORMAP_H
#define QVVECTORMAP_H

/*!
@class QVVectorMap qvmath/qvvectormap.h QVVectorMap
@brief Fast nearest neigbour vector container

Vector maps are created from a list of QVVector objects, or initialized <i>manually</i>, inserting the points with the @ref add method:

@code
QList<QVVector> vectors;
QVVector v1, v2, ...;
[...]
points.append(v1);
points.append(v2);

[...]

QVVectorMap vectorMap1(vectors), vectorMap2;
vectorMap2.add(v4);
vectorMap2.add(v5);

[...]
@endcode

The method @ref getClosestVectors can be used to obtain the points registered in the container, which are closer to a given vector.

@ingroup qvmath
*/
class QVVectorMap: public QMap<double, QVVector>
	{
	public:
		/// @brief Adds a vector to the container.
		///
		/// @param point Vector to add to the container.
		void add(const QVVector &vector);

		/// @brief Default constructor
		///
		/// @param vectors Vectors to insert in the container.
		QVVectorMap(const QList<QVVector> & vectors = QList<QVVector>());

		/// @brief Get the closest vector to a given one from the container.
		///
		/// @return If the container is empty, return the default value for QVVector. Else returns the vector which is closer to the given one.
		QVVector getClosestVector(const QVVector &vector) const;

		/// @brief Get the closest vectors to a given one from the container.
		///
		/// @return If the container holds <i>n</i> vectors or less, the return value is a list containing those vectors. Else, returns
		/// the <i>n</i> vectors contained which are closer to the given one.
		QList<QVVector> getClosestVectors(const QVVector &vector, const int n) const;

		/// @brief function for debug purposes
		static QList<QVVector> getClosestVectors(const QVVector actualVector, const QList<QVVector> &vectors, const int n);
	};


#endif
