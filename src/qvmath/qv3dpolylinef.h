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

#ifndef QV3DPOLYLINEF_H
#define QV3DPOLYLINEF_H

#include <QV3DPointF>

/*!
@class QV3DPolylineF qvblockprogramming/qvguiblocks/qv3dcanvas.h QV3DPolylineF
@brief 3D polyline representation

This class models a 3D polyline.

@ingroup qvmath
@see QVPolyline
@see QVPolylineF
*/
class QV3DPolylineF: public QList<QV3DPointF>
	{
	public:
		QV3DPolylineF(): QList<QV3DPointF>()					{ }
		QV3DPolylineF(const QV3DPolylineF &other): QList<QV3DPointF>(other)	{ }
		QV3DPolylineF(const QList<QV3DPointF> &list): QList<QV3DPointF>(list)	{ }
	};

Q_DECLARE_METATYPE(QV3DPolylineF);
Q_DECLARE_METATYPE(QList<QV3DPointF>);
Q_DECLARE_METATYPE(QList<QV3DPolylineF>);

#endif
