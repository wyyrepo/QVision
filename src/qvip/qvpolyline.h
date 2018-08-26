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

#ifndef QVPOLYLINE_H
#define QVPOLYLINE_H

#include <QPointF>

//#include <qvipp.h>
#include <QVImage>

class QVPolylineF;

/*!
@class QVPolyline qvip/qvpolyline.h QVPolyline
@brief Polyline representation.

@ingroup qvip

A polyline is a continuous line composed of one or more straight line segments.
A QVPolyline is a implementation of a polyline, specified by a list of the points located at the intersection of the segments.
Thus, any QVPolyline object inherits from the class QList<QPoint>.

When a polyline is closed, then it is considered to be a polygon. In that case it is supposed to have an implicit final
straight line segment, that links the first and the last point in the polyline. The property @ref QVPolyline::closed will
store the value <i>TRUE</i> if the polyline is a polygon, else storing <i>FALSE</i>.

A QVPolyline has the property @ref QVPolyline::direction, that will indicate if it is a direct polyline, or a reverse
polyline. It has only meaning for some algorithms, like @ref getConnectedSetBorderContoursThreshold.
*/
class QVPolyline: public QList<QPoint>
	{
	public:
		bool closed, direction;

		QVPolyline(const int estimatedSize = 0);
		QVPolyline(const QList<QPoint> &pointList): QList<QPoint>(pointList) { };
		QVPolyline(const QVPolyline &polyline);
		QVPolyline(const QVPolylineF &polyline);

		static QVPolyline ellipse(uInt n, float x, float y, float maxRadio, float minRadio, float ang);
		static QVPolyline line(int x1, int y1, int x2, int y2);
		static QVPolyline rectangle(int x1, int y1, int x2, int y2);

		operator QVPolylineF() const;
	};

std::ostream& operator << ( std::ostream &os, const QVPolyline &polyline);

Q_DECLARE_METATYPE(QVPolyline)
Q_DECLARE_METATYPE(QList<QVPolyline>)

#endif

