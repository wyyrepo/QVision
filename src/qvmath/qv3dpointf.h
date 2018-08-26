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

#ifndef QV3DPOINTF_H
#define QV3DPOINTF_H

#include <QVVector>

/*!
@class QV3DPointF qvblockprogramming/qvguiblocks/qv3dcanvas.h QV3DPointF
@brief 3D point representation

This class models a point in the 3D space.

@ingroup qvmath
*/
class QV3DPointF: public QVVector
	{
	//private:
	//	double _x, _y, _z;
	public:
		/// @brief Constructs a QV3DPointF object
		///
		/// @param x Value for the first coordinate of the point.
		/// @param y Value for the second coordinate of the point.
		/// @param z Value for the third coordinate of the point.
		QV3DPointF(const double x = 0.0, const double y = 0.0, const double z = 0.0): QVVector(3)
			{
			operator[](0) = x;
			operator[](1) = y;
			operator[](2) = z;
			}

		QV3DPointF(const QVVector &vector): QVVector(vector)
			{ }

		/// @brief Gets the value for the first coordinate of the 3D point
		inline double x() const	{ return operator[](0); }

		/// @brief Gets a reference to the first coordinate of the 3D point
		inline double &x()	{ return operator[](0); }

		/// @brief Gets the value for the second coordinate of the 3D point
		inline double y() const	{ return operator[](1); }

		/// @brief Gets a reference to the second coordinate of the 3D point
		inline double &y()	{ return operator[](1); }

		/// @brief Gets the value for the third coordinate of the 3D point
		inline double z() const	{ return operator[](2); }

		/// @brief Gets a reference to the third coordinate of the 3D point
		inline double &z()	{ return operator[](2); }
	};

#endif
