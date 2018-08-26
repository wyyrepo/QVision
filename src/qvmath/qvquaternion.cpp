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

#include <QString>
#include <QVMatrix>
#include <QVQuaternion>
#include <qvmath.h>

///////////////////////////////////
// Constructors
QVQuaternion::QVQuaternion(): QVVector(4)
	{
	set(0);
	operator[](3) = 1;
	Q_ASSERT(norm2() > 0);
	}

QVQuaternion::QVQuaternion(const QVVector a, const double phi):QVVector(4)
	{
	QVVector a_normal = a * (sin(phi/2.0) / a.norm2());

	operator[](0) = a_normal[0];
	operator[](1) = a_normal[1];
	operator[](2) = a_normal[2];
	operator[](3) = cos(phi/2.0);

	Q_WARNING(not containsNaN());
	Q_ASSERT(norm2() > 0);
	}

QVQuaternion::QVQuaternion(const QVMatrix &R): QVVector(4)
	{
	Q_ASSERT(not R.containsNaN());
	Q_ASSERT(R.norm2() > 0);

	int u, v, w;

	// Sort the elements of the trace of Q.
	if (R(0,0) > R(1,1))
		if (R(0,0) > R(2,2))
			if (R(1,1) > R(2,2))
				{ u = 0; v = 1; w = 2; }
			else
				{ u = 0; v = 2; w = 1; }
		else
			if (R(0,0) > R(2,2))
				{ u = 1; v = 0; w = 2; }
			else
				{ u = 1; v = 2; w = 0; }
	else
		if (R(1,1) > R(2,2))
			if (R(0,0) > R(2,2))
				{ u = 1; v = 0; w = 2; }
			else
				{ u = 1; v = 2; w = 0; }
		else
			if (R(0,0) > R(1,1))
				{ u = 2; v = 0; w = 1; }
			else
				{ u = 2; v = 1; w = 0; }

	Q_ASSERT(u != v);
	Q_ASSERT(v != w);
	Q_ASSERT(u != w);

	if (1.0 + R(u,u) - R(v,v) - R(w,w) < 0.0)
		{
		*this = QVQuaternion(-R);
		return;
		}

	Q_ASSERT(1.0 >= - R(u,u) + R(v,v) + R(w,w));
	const double r = sqrt(1.0 + R(u,u) - R(v,v) - R(w,w));

	// Estimate the values of the quaternion
	if (ABS(r) < 1e-100)
		{
		operator[](u) = 0.0; 
		operator[](v) = 0.0;
		operator[](w) = 0.0;
		operator[](3) = 1.0;
		}
	else	{
		operator[](u) = r / 2.0; 
		operator[](v) = (R(u,v) + R(v,u)) / (2.0*r);
		operator[](w) = (R(u,w) + R(w,u)) / (2.0*r);
		operator[](3) = (R(w,v) - R(v,w)) / (2.0*r);
		}

	Q_WARNING(not isnan(real()));
	Q_WARNING(not isnan(i()));
	Q_WARNING(not isnan(j()));
	Q_WARNING(not isnan(k()));

	// Obtain correct sign for 'w'. Knowing:
	//	R(2,1) - R(1,2) == 4*x*w
	// We know that:
	//	SIGN(R(2,1) - R(1,2)) == SIGN(4*x*w)
	// thus
	//	(R(2,1) - R(1,2))*x*w > 0;
	switch(u)
		{
		// R(2,1) - R(1,2) == 4*x*w	<=>	(R(2,1) - R(1,2))*x*w > 0;
		case 0:	if ( (R(2,1) - R(1,2))*operator[](0)*operator[](3) < 0)
				operator[](3) = -operator[](3);
			break;

		// R(0,2) - R(2,0) == 4*y*w	<=>	(R(0,2) - R(2,0))*y*w > 0;
		case 1:	if ( (R(0,2) - R(2,0))*operator[](1)*operator[](3) < 0)
				operator[](3) = -operator[](3);
			break;

		// R(1,0) - R(0,1) == 4*z*w	<=>	(R(1,0) - R(0,1))*z*w > 0;
		case 2:	if ( (R(1,0) - R(0,1))*operator[](2)*operator[](3) < 0)
				operator[](3) = -operator[](3);
			break;

		default:
			break;
		}

	Q_ASSERT(not containsNaN());
	Q_ASSERT(norm2() > 0);
	}

QVQuaternion::QVQuaternion(const double i, const double j, const double k, const double r): QVVector(4)
	{
	operator[](0) = i;
	operator[](1) = j;
	operator[](2) = k;
	operator[](3) = r;

	Q_WARNING(not containsNaN());
	Q_ASSERT(norm2() > 0);
	}

QVQuaternion::QVQuaternion(const double xAngle, const double yAngle, const double zAngle): QVVector(4)
	{
	const double	sinX = sinf(0.5*xAngle),
			sinY = sinf(0.5*yAngle),
			sinZ = sinf(0.5*zAngle),
			cosX = cosf(0.5*xAngle),
			cosY = cosf(0.5*yAngle),
			cosZ = cosf(0.5*zAngle);

	// and now compute quaternion
	operator[](0) = cosZ*cosY*sinX - sinZ*sinY*cosX;
	operator[](1) = cosZ*sinY*cosX + sinZ*cosY*sinX;
	operator[](2) = sinZ*cosY*cosX - cosZ*sinY*sinX;
	operator[](3) = cosZ*cosY*cosX + sinZ*sinY*sinX;

	Q_WARNING(not containsNaN());
	Q_ASSERT(norm2() > 0);
	}

///////////////////////////////

#define TRACKBALLSIZE  (0.8)
float pixelToSphere(const float r, const float x, const float y)
	{
	float d = sqrt(x*x + y*y);
	return (d < r * 0.70710678118654752440)? sqrt(r*r - d*d) : r*r / (2*d);
	}

QVQuaternion QVQuaternion::trackball(const float p1x, const float p1y, const float p2x, const float p2y)
	{
	// Zero rotation
	if (p1x == p2x && p1y == p2y)
		return QVQuaternion();
	
	// First, figure out z-coordinates for projection of P1 and P2 to deformed sphere
	QVVector p1(3), p2(3);
	p1[0] = p1x, p1[1] = p1y, p1[2] = pixelToSphere(TRACKBALLSIZE,p1x,p1y);
	p2[0] = p2x, p2[1] = p2y, p2[2] = pixelToSphere(TRACKBALLSIZE,p2x,p2y);

	// Figure out how much to rotate around that axis.
	float t = (p1 - p2).norm2() / (2.0*TRACKBALLSIZE);
	
	// Avoid problems with out-of-control values...
	if (t > 1.0) t = 1.0;
	if (t < -1.0) t = -1.0;

	return QVQuaternion(p2 ^ p1, 2.0 * asin(t));			
	}

QVQuaternion QVQuaternion::normalizeQuaternion() const
	{
	QVQuaternion q = *this;

	double size = q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3];
	for (int i = 0; i < 4; i++)
		q[i] /= size;

	return q;
	}

QVQuaternion QVQuaternion::quaternionProduct(const QVQuaternion &other) const
	{
	const double	x = operator[](0),	y = operator[](1),	z = operator[](2),	w = operator[](3),
			other_x = other[0],	other_y = other[1],	other_z = other[2],	other_w = other[3];

	const QVQuaternion result(	w * other_x + x * other_w + y * other_z - z * other_y,
								w * other_y + y * other_w + z * other_x - x * other_z,
								w * other_z + z * other_w + x * other_y - y * other_x,
								w * other_w - x * other_x - y * other_y - z * other_z);

	Q_WARNING(not result.containsNaN());
	Q_ASSERT(result.norm2() > 0);

	return result;
	}

void QVQuaternion::toEulerAngles(double &xAngle, double &yAngle, double &zAngle) const
	{
	Q_WARNING(not containsNaN());
	Q_ASSERT(norm2() > 0);

	const double	s = operator[](3),
			x = operator[](0),
			y = operator[](1),
			z = operator[](2),
			sqw = s*s,
			sqx = x*x,
			sqy = y*y,
			sqz = z*z;

	xAngle = atan2f(2.f * (x*y + z*s), sqx - sqy - sqz + sqw);
	yAngle = asinf(-2.f * (x*z - y*s));
	zAngle = atan2f(2.f * (y*z + x*s), -sqx - sqy + sqz + sqw);
	}

QVMatrix QVQuaternion::toRotationMatrix() const
	{
	Q_WARNING(not containsNaN());
	Q_ASSERT(norm2() > 0);

	const double	norm = norm2(),
			x = operator[](0) / norm,
			y = operator[](1) / norm,
			z = operator[](2) / norm,
			w = operator[](3) / norm;

	QVMatrix result(3,3);
	result(0,0) = 1.0 - 2.0 * (y*y + z*z);
	result(0,1) = 2.0 * (x*y - z*w);
	result(0,2) = 2.0 * (z*x + y*w);
	
	result(1,0) = 2.0 * (x*y + z*w);
	result(1,1) = 1.0 - 2.0 * (z*z + x*x);
	result(1,2) = 2.0 * (y*z - x*w);
	
	result(2,0) = 2.0 * (z*x - y*w);
	result(2,1) = 2.0 * (y*z + x*w);
	result(2,2) = 1.0 - 2.0 * (y*y + x*x);

	return result;
	}

QVQuaternion QVQuaternion::conjugate() const
	{
	const QVQuaternion result(-operator[](0), -operator[](1), -operator[](2), operator[](3));

	Q_WARNING(not result.containsNaN());
	Q_ASSERT(result.norm2() > 0);

	return result;
	}

QVQuaternion QVQuaternion::inverse() const
	{
	Q_ASSERT(norm2() > 0);

	const QVQuaternion result = conjugate();

	Q_WARNING(not result.containsNaN());
	Q_ASSERT(result.norm2() > 0);

	return result / result.norm2();
	}

double QVQuaternion::norm2() const
	{
	return QVVector::norm2();
	}

QV3DPointF QVQuaternion::rotate(const QV3DPointF &v) const
	{
	const double	norm = norm2(),
			x = operator[](0) / norm,
			y = operator[](1) / norm,
			z = operator[](2) / norm,
			w = operator[](3) / norm;

	if (v[0] == 0 and v[1] == 0 and v[2] == 0)
		return v;

//	std::cout << "q1" << std::endl;
	const QVQuaternion q(x, y, z, w);
//	std::cout << "q2" << std::endl;
	const QVQuaternion p(v[0], v[1], v[2], 0);
//	std::cout << "q3" << std::endl;
	const QVQuaternion product = q * p * q.conjugate();
//	std::cout << "q4" << std::endl;	

	QVVector result(3);
	result[0] = product[0];
	result[1] = product[1];
	result[2] = product[2];

	Q_WARNING(not result.containsNaN());

	return result;
	}

//////////////////////////////////////////////

std::ostream& operator << ( std::ostream &os, const QVQuaternion &quaternion )
	{
	const int size = quaternion.size();

	os << "QVQuaternion [";

	for (int i = 0; i < size; i++)
		os << qPrintable(QString("%1").arg(quaternion[i], -8, 'f', 6)) << " ";

	os << "]" << std::endl;
	return os;
	}

