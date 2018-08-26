/*
 *	Copyright (C) 2009, 2010, 2011, 2012. PARP Research Group.
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

#include <QMap>
#include <QList>
#include <QPointF>

#ifndef QV2DMAP_H
#define QV2DMAP_H

//#define	SIGNATURE(Point)	(Point.x())

/*!
@class QV2DMap qvmath/qv2dmap.h QV2DMap
@brief Fast 2D nearest neigbour access data container

This class represents a container for 2D points on the real plane.

Such containers are created from a list of QPointF objects, or initialized <i>manually</i>, inserting the points with the @ref add method:

@code
QList<QPointF> points;
points.append(QPointF(10.7,20.1));
points.append(QPointF(15.5,9.2));

[...]

QV2DMap pointMap1(points), pointMap2;
pointMap2.add(QPointF(34.7, 12.9));
pointMap2.add(QPointF(99.0, 1.2));

[...]
@endcode

The method @ref getClosestPoints can be used to obtain the points registered in the container, which are closer to a given point.

@ingroup qvmath
*/
//#define	SIGNATURE(Point)	(Point.x())
class QV2DMap: public QMap<double, QPointF>
	{
	private:
		#ifndef DOXYGEN_IGNORE_THIS
		QList<QPointF> getClosestPoints2(const QPointF &point, const int n) const;
		#endif

	public:
		/// @brief Adds a 2D point to the container.
		///
		/// @param point Point to add to the container.
		void add(const QPointF &point);

		/// @brief Default constructor
		///
		/// @param points Points to insert in the container.
		QV2DMap(const QList<QPointF> & points = QList<QPointF>());

		/// @brief Get the closest point to a given one from the container.
		///
		/// @return If the container is empty, return the default value for QPointF. Else returns the point which is closer to the given one.
		QPointF getClosestPoint(const QPointF &point) const;

		/// @brief Get the closest points to a given one from the container.
		///
		/// @return If the container holds <i>n</i> points or less, the return value is a list containing those points. Else, returns
		/// the <i>n</i> points contained which are closer to the given one.
		QList<QPointF> getClosestPoints(const QPointF &point, const int n) const;

		#ifndef DOXYGEN_IGNORE_THIS
		static void test();
		#endif
	};
#endif
