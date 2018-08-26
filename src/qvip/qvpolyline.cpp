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

#include <iostream>
#include <float.h>

#include <qvmath.h>
#include <qvdefines.h>
//#include <qvmatrixalgebra.h>

#include <QVPolyline>
#include <QVPolylineF>

QVPolyline::QVPolyline(const int estimatedSize): QList<QPoint>(),
	closed(false), direction(false)
	{
	qDebug() << "QVPolyline()";

	if (estimatedSize > 0)
		#ifdef QT_MIN_VERSION_4_7
		QList<QPoint>::reserve(estimatedSize);
		#else
		Q_WARNING("cannot reserve a size for Qt versions older than 4.7");
		#endif // QT_MIN_VERSION_4_7

	qDebug() << "QVPolyline() <~ return";
	};

QVPolyline::QVPolyline(const QVPolyline &polyline): QList<QPoint>(polyline),
	closed(polyline.closed), direction(polyline.direction)
	{
	qDebug() << "QVPolyline(const QVPolyline &)";
	qDebug() << "QVPolyline(const QVPolyline &) <~ return";
	};

QVPolyline::QVPolyline(const QVPolylineF &polyline): QList<QPoint>(),
	closed(polyline.closed), direction(polyline.direction)
	{
	foreach(QPointF pointf, polyline)
		{
		append( QPoint(pointf.toPoint()) );
		}
	qDebug() << "QVPolylineF(const QVPolylineF &)";
	qDebug() << "QVPolylineF(const QVPolylineF &) <~ return";
	};

QVPolyline QVPolyline::ellipse(uInt n, float x, float y, float maxRadio, float minRadio, float ang)
	{
	QVPolyline ellipse;
	float w = 2*PI/(n-1);
	float maxArg = (maxRadio+minRadio)/2;
	float minArg = (maxRadio-minRadio)/2;

	for (uInt t = 0; t < n; t++)
		ellipse.append(QPoint (	(uInt) (x + maxArg*cos(ang+w*t) + minArg*cos(ang-w*t)),
						(uInt) (y + maxArg*sin(ang+w*t) + minArg*sin(ang-w*t))
						));
	return ellipse;
	}

QVPolyline QVPolyline::rectangle(int x1, int y1, int x2, int y2)
	{
	QVPolyline rectangle;
	rectangle.append(QPoint( x1, y1 ));
	rectangle.append(QPoint( x1, y2 ));
	rectangle.append(QPoint( x2, y2 ));
	rectangle.append(QPoint( x2, y1 ));
	rectangle.append(QPoint( x1, y1 ));
	return rectangle;
	}

QVPolyline QVPolyline::line(int x1, int y1, int x2, int y2)
	{
	QVPolyline line;

	line.append(QPoint( x1, y1 ));

	if (x1 == x2 && y1 == y2)
		return line;

	int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;
	
	dx=x2-x1;      // the horizontal distance of the line
	dy=y2-y1;      // the vertical distance of the line
	dxabs=abs(dx);
	dyabs=abs(dy);
	sdx=SIGN(dx);
	sdy=SIGN(dy);
	x=dyabs>>1;
	y=dxabs>>1;
	px=x1;
	py=y1;
	
	if (dxabs>=dyabs) // the line is more horizontal than vertical
		for(i=0;i<dxabs;i++)
			{
			y+=dyabs;
			if (y>=dxabs)
				{
				y-=dxabs;
				py+=sdy;
				}
			px+=sdx;
			line.append(QPoint( px, py ));
			}
	else	// the line is more vertical than horizontal
		for(i=0;i<dyabs;i++)
			{
			x+=dxabs;
			if (x>=dyabs)
				{
				x-=dyabs;
				px+=sdx;
				}
			py+=sdy;
			line.append(QPoint( px, py ));
			}

	return line;
	}

QVPolyline::operator QVPolylineF() const
	{
	QVPolylineF polyline;
	foreach(QPoint point, *this)
		{
		polyline.append(QPointF(point));
		}
	return polyline;
	}

std::ostream& operator << ( std::ostream &os, const QVPolyline &polyline)
	{
	const int size = polyline.size();

	os << "QVPolyline (" << size << ")" ;

	os << " [" ;
	for (int i=0; i < size; i++)
		{
		os << " (" << polyline[i].x() << "," << polyline[i].y() << ")";
		if(i!=size-1)
		    os << ",";
		else
		    os << " ";
		}
	os << "]" ;
	return os;
	}
