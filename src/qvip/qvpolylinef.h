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

#ifndef QVPOLYLINEF_H
#define QVPOLYLINEF_H

#include <QPointF>

//#include <qvipp.h>
#include <qvmath.h>
#include <QVImage>


class QVPolyline;

/*!
@class QVPolylineF qvip/qvpolylinef.h QVPolylineF
@brief Floating point polyline representation.

@ingroup qvip

A polyline is a continuous line composed of one or more straight line segments.
A QVPolylineF is a implementation of a polyline, specified by a list of the points located at the intersection of the segments.
Thus, any QVPolylineF object inherits from the class QList<QPointF>.

When a polyline is closed, then it is considered to be a polygon. In that case it is supposed to have an implicit final
straight line segment, that links the first and the last point in the polyline. The property @ref QVPolylineF::closed will
store the value <i>TRUE</i> if the polyline is a polygon, else storing <i>FALSE</i>.

A QVPolylineF has the property @ref QVPolylineF::direction, that will indicate if it is a direct polyline, or a reverse
polyline. It has only meaning for some algorithms, like @ref getConnectedSetBorderContoursThreshold.
*/
class QVPolylineF: public QList<QPointF>
	{
	public:
		bool closed, direction;

		QVPolylineF(const int estimatedSize = 0);
		QVPolylineF(const QList<QPointF> &pointList): QList<QPointF>(pointList) { };
		QVPolylineF(const QVPolyline &polyline);
		QVPolylineF(const QVPolylineF &polyline);

		static QVPolylineF ellipse(uInt n, float x, float y, float maxRadio, float minRadio, float ang);
		static QVPolylineF rectangle(float x1, float y1, float x2, float y2);

		operator QVPolyline() const;

		/// @brief Test if a point is contained inside the polygon.
		/// 
		/// The polygon is supposed to be closed in any case. The following image shows the result of
		/// applying this method with a polyline (drawn in red) over a set of points lying inside it
		/// (drawn in green) and outside it (drawn in red):
		/// 
		/// @image html pointslyinginsidepolyline.png

		/// The source of the algorithm is the following:

		/// <i>
		/// [...] Another solution forwarded by Philippe Reverdy is to compute the sum of the angles made between the test point
		/// and each pair of points making up the polygon. If this sum is 2pi then the point is an interior point, if 0 then
		/// the point is an exterior point. This also works for polygons with holes given the polygon is defined with a path
		/// made up of coincident edges into and out of the hole as is common practice in many CAD packages. [...]
		/// </i>

		/// <a href="http://local.wasp.uwa.edu.au/~pbourke/geometry/insidepoly/">http://local.wasp.uwa.edu.au/~pbourke/geometry/insidepoly/</a>
		/// @returns TRUE if the point lies inside the polygon, else FALSE.
		bool surrounds(const QPointF &p) const;
	};

std::ostream& operator << ( std::ostream &os, const QVPolylineF &polylinef);

Q_DECLARE_METATYPE(QVPolylineF)
Q_DECLARE_METATYPE(QList<QVPolylineF>);
#endif

