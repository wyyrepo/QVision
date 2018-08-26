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

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <QSet>

#include <QV2DMap>
#include <qvmath.h>

#define	SQRT2			1.414213562
#define	SIGNATURE(Point)	( (Point.x() + Point.y()) / SQRT2)

void QV2DMap::add(const QPointF &point)
	{
	insertMulti(SIGNATURE(point), point);
	}

QV2DMap::QV2DMap(const QList<QPointF> & points): QMap<double, QPointF>()
	{
	foreach(QPointF point, points)
		add(point);	
	};

QPointF QV2DMap::getClosestPoint(const QPointF &point) const
	{
	const double point_signature = SIGNATURE(point);

	// Trivial cases
	//if (size() == 0)
	//	return QPointF(0,0);

	// Locate the pivot in the closest point
	QMap<double, QPointF>::const_iterator pivot = lowerBound(SIGNATURE(point));
	if (pivot == constEnd())
		--pivot;

	double best_distance = norm2(point - pivot.value());				// ----------- $$$
	QPointF best_point = pivot.value();						// ----------- $$$

	// Iterate to the left of the pivot element.
	if (pivot != constBegin())
		for (QMap<double, QPointF>::const_iterator i = pivot; i != constBegin(); --i)
			{
			if (ABS(i.key() - point_signature) >= best_distance)
				break;

			const double actualDistance = norm2(point - i.value());
			if (actualDistance < best_distance)
				{
				best_distance = actualDistance;
				best_point = i.value();
				}
			}

	// Iterate to the right of the pivot element.
	for (QMap<double, QPointF>::const_iterator i = pivot + 1; i != constEnd(); ++i)
		{
		if (ABS(i.key() - point_signature) >= best_distance)
			break;

		const double actualDistance = norm2(point - i.value());
		if (actualDistance < best_distance)
			{
			best_distance = actualDistance;
			best_point = i.value();
			}
		}

	return best_point;
	}

QList<QPointF> QV2DMap::getClosestPoints(const QPointF &point, const int maxPoints) const
	{
	const double point_signature = SIGNATURE(point);

	// Trivial cases
	if (size() == 0 || maxPoints <= 0)
		return QList<QPointF>();

	if (size() <= maxPoints)
		return values();
	
	// Special threatment of the first element
	int t = 0;
	QMap<double, QPointF> closestPoints;
	for(QMap<double, QPointF>::const_iterator i = constBegin(); t < maxPoints; ++t, ++i)
		closestPoints.insertMulti(norm2(point - i.value()), i.value());

	// Iterate to the left of the pivot element
	double last_key = (--(closestPoints.end())).key();

	// Locate the pivot in the closest point
	QMap<double, QPointF>::const_iterator pivot = lowerBound(SIGNATURE(point));
	if (pivot == constEnd())
		--pivot;

	// Iterate to the left of the pivot element.
	if (pivot != constBegin())
		for (QMap<double, QPointF>::const_iterator i = pivot; i != constBegin(); --i)
			{
			if (ABS(i.key() - point_signature) >= last_key)
				break;

			const double actualDistance = norm2(point - i.value());
			if (actualDistance < last_key)
				{
				closestPoints.take(last_key);
				closestPoints.insertMulti(actualDistance, i.value());
				last_key = (--(closestPoints.end())).key();
				}
			}

	// Iterate to the right of the pivot element.
	for (QMap<double, QPointF>::const_iterator i = pivot + 1; i != constEnd(); ++i)
		{
		if (ABS(i.key() - point_signature) >= last_key)
			break;

		const double actualDistance = norm2(point - i.value());
		if (actualDistance < last_key)
			{
			closestPoints.take(last_key);
			closestPoints.insertMulti(actualDistance, i.value());
			last_key = (--(closestPoints.end())).key();
			}
		}

	return closestPoints.values();
	}

QList<QPointF> QV2DMap::getClosestPoints2(const QPointF &point, const int n) const
	{
	// Trivial cases
	if (size() == 0 || n <= 0)
		return QList<QPointF>();

	if (size() <= n)
		return values();

	QMap<double, QPointF> closestPoints;

	// Add the first point of the list, and the closest one to the provided point
	foreach(QPointF actual, values())
		closestPoints.insertMulti(norm2(point - actual), actual);

	return closestPoints.values().mid(0,n);
	}

void QV2DMap::test()
	{
	QSet<QPointF> sourcePointsTemp, destinationPointsTemp;

	for (int i = 1; i <= 1000; i++)
		sourcePointsTemp.insert(QPointF(rand()%100, rand()%100));

	for (int i = 1; i < 1000; i++)
		destinationPointsTemp.insert(QPointF(rand()%100, rand()%100));

	QList<QPointF> sourcePoints = sourcePointsTemp.values(), destinationPoints = destinationPointsTemp.values();

	QV2DMap m = destinationPoints;

	for(int i = 0; i < sourcePoints.size(); i++)
		{
		const QPointF point = sourcePoints[i];
		const QList<QPointF> l1 = m.getClosestPoints(point, 50), l2 = m.getClosestPoints2(point, 50);
		const QSet<QPointF> temp1 = l1.toSet(), temp2 = l2.toSet();

		if (l1.size() != l2.size())
			std::cout << "ERROR: different sizes for obtained lists" << std::endl;

		bool cond = false;
		for(int j = 0; j < l1.size(); j++)
			if (ABS(norm2(l1[j] - point) - norm2(l2[j] - point)) > 0.00000001)
				cond = true;
			
		if (cond)
			{
			std::cout << "Error: distances are different" << std::endl;
			std::cout << "Point("<< point.x() << ", " << point.y() << ")" << std::endl;
			std::cout << "l1 = " << std::endl;
			foreach (QPointF p, l1)
				std::cout << "\tPoint("<< p.x() << ", " << p.y() << ")\tdistance = " << norm2(p - point) << std::endl;

			std::cout << "l2 = " << std::endl;
			foreach (QPointF p, l2)
				std::cout << "\tPoint("<< p.x() << ", " << p.y() << ")\tdistance = " << norm2(p - point) << std::endl;

			}
		}
	}

