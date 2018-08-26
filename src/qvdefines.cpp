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

#include <qvdefines.h>
#include <QHash>
std::ostream& operator << ( std::ostream &os, const QPointF &point )
	{
	os << "QPointF (" << point.x() << ", " << point.y() << ")";
	return os;
	}

std::ostream& operator << ( std::ostream &os, const QPoint &point )
	{
	os << "QPoint (" << point.x() << ", " << point.y() << ")";
	return os;	
	}

std::ostream& operator << ( std::ostream &os, const QPointFMatching &matching )
	{
	os << "QPointFMatching [" << matching.first << "\t<->\t" << matching.second << "]";
	return os;	
	}

uint qHash(const double &value)
	{
	const uint *i = (uint *) &value;
	const uchar *c = (uchar *) &value;

	return i[0] + i[1] + c[0] + c[1] + c[2] + c[3] + c[4] + c[5] + c[6] + c[7];
	}

uint qHash(const QPointF &point)
	{
	return qHash(point.x() + point.y());
	}

uint qHash(const QPoint &point)
	{
	return qHash(point.x() + point.y());
	}

#include <sys/time.h>
long long getMicroseconds()
	{
	timeval tv;
	gettimeofday(&tv,NULL);
	long long ts = tv.tv_sec;
	ts *= 1000000;
	ts += tv.tv_usec;
	return ts;
	}

#ifdef GLUPERSPECTIVE_SUBSTITUTE
#include <qvmath.h>
void qvGluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
	{
	GLdouble xmin, xmax, ymin, ymax;

	ymax = zNear * tan(fovy * M_PI / 360.0);
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;


	glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
	}
#endif // GLUPERSPECTIVE_SUBSTITUTE

