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
/// @brief File from the QVision library. Contains operations on polylines.
/// @author PARP Research Group. University of Murcia, Spain.

#include <QVPolyline>
#include <QVPolylineF>

#include <qvmath.h>
#include <qvdefines.h>
//#include <qvmatrixalgebra.h>

#include <iostream>
#include <float.h>

QVPolylineF::QVPolylineF(const int estimatedSize): QList<QPointF>(),
	closed(false), direction(false)//, dir(0)
	{
	qDebug() << "QVPolylineF()";

	if (estimatedSize > 0)
		#ifdef QT_MIN_VERSION_4_7
		QList<QPointF>::reserve(estimatedSize);
		#else
		Q_WARNING("cannot reserve a size for Qt versions older than 4.7");
		#endif // QT_MIN_VERSION_4_7

	qDebug() << "QVPolylineF() <~ return";
	};

QVPolylineF::QVPolylineF(const QVPolyline &polyline): QList<QPointF>(),
	closed(polyline.closed), direction(polyline.direction)//, dir(polyline.dir)
	{
	foreach(QPoint point, polyline)
		{
		append(QPointF(point));
		}
	qDebug() << "QVPolylineF(const QVPolylineF &)";
	qDebug() << "QVPolylineF(const QVPolylineF &) <~ return";
	};

QVPolylineF::QVPolylineF(const QVPolylineF &polyline): QList<QPointF>(polyline),
	closed(polyline.closed), direction(polyline.direction)//, dir(polyline.dir)
	{
	qDebug() << "QVPolylineF(const QVPolylineF &)";
	qDebug() << "QVPolylineF(const QVPolylineF &) <~ return";
	};


// QPointF	linesIntersection(QPointF a, QPointF b, QPointF c, QPointF d)
// 	// gets the intersection point for lines ab and cd
// 	{
// 	double x1 = a.rx(), x2 = b.rx(), x3 = c.rx(), x4 = d.rx();
// 	double y1 = a.ry(), y2 = b.ry(), y3 = c.ry(), y4 = d.ry();
// 
// 	double denominador = (y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1);
// 	if (denominador == 0)
// 		return QPointF( (int)(b.rx() + c.rx())/2, (int)(b.ry() + c.ry())/2 );
// 
// 	double	ua = (x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3),
// 		ub = (x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3);
// 
// 	QPointF p = QPointF(
// 			(int) (x1 + ua*(x2 - x1) / denominador),
// 			(int) (y1 + ub*(y2 - y1) / denominador)
// 			);
// 	return p;
// 	}



/////////////////////////////////////////

QVPolylineF QVPolylineF::ellipse(uInt n, float x, float y, float maxRadio, float minRadio, float ang)
	{
	QVPolylineF ellipse;
	float w = 2*PI/(n-1);
	float maxArg = (maxRadio+minRadio)/2;
	float minArg = (maxRadio-minRadio)/2;

	for (uInt t = 0; t < n; t++)
                ellipse.append(QPointF (	(x + maxArg*cos(ang+w*t) + minArg*cos(ang-w*t)),
                                                (y + maxArg*sin(ang+w*t) + minArg*sin(ang-w*t))
						));
	return ellipse;
	}

QVPolylineF QVPolylineF::rectangle(float x1, float y1, float x2, float y2)
	{
	QVPolylineF rectangle;
	rectangle.append(QPointF( x1, y1 ));
	rectangle.append(QPointF( x1, y2 ));
	rectangle.append(QPointF( x2, y2 ));
	rectangle.append(QPointF( x2, y1 ));
	rectangle.append(QPointF( x1, y1 ));
	return rectangle;
	}

QVPolylineF::operator QVPolyline() const
	{
	QVPolyline polyline;
	foreach(QPointF pointf, *this)
		{
		polyline.append( QPoint(pointf.toPoint()) );
		}
	return polyline;
	}

bool QVPolylineF::surrounds(const QPointF &p) const
	{
	if (size() < 3)
		return false;

	double angle = qvClockWiseAngle(operator[](0) - p, operator[](1) - p);
	for (int i=1; i<size()-1; i++)
		angle += qvClockWiseAngle(operator[](i) - p, operator[](i+1) - p);

	return ABS(angle) >= PI;
	}

std::ostream& operator << ( std::ostream &os, const QVPolylineF &polylinef)
	{
	const int size = polylinef.size();

	os << "QVPolyline (" << size << ")" ;

	os << " [" ;
	for (int i=0; i < size; i++)
		{
		os << " (" << polylinef[i].x() << "," << polylinef[i].y() << ")";
		if(i!=size-1)
		    os << ",";
		else
		    os << " ";
		}
	os << "]" ;
	return os;
	}
