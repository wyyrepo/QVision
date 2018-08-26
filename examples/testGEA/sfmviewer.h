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

#include <QV3DCanvas>

QV3DPolylineF cameraWireModel(const QVEuclideanMapping3 &E3, const double base_side_length, const double height)
	{
	QV3DPolylineF p;
	p << QV3DPointF(0,0,0);
	p << QV3DPointF(-base_side_length,      -base_side_length,      height);
	p << QV3DPointF(-base_side_length,      base_side_length,       height);
	p << QV3DPointF(0,0,0);

	p << QV3DPointF(-base_side_length,      base_side_length,       height);
	p << QV3DPointF(base_side_length,       base_side_length,       height);
	p << QV3DPointF(0,0,0);
	p << QV3DPointF(base_side_length,       base_side_length,       height);
	p << QV3DPointF(base_side_length,       -base_side_length,      height);
	p << QV3DPointF(0,0,0);

	p << QV3DPointF(base_side_length,       -base_side_length,      height);
	p << QV3DPointF(-base_side_length,      -base_side_length,      height);
	p << QV3DPointF(0,0,0);

	const QVEuclideanMapping3 E3inv = E3.inverse();

	QV3DPolylineF result;
	foreach(QV3DPointF point, p)
		result << E3inv.apply(point);

	return result;
	}

class SfMViewer: public QV3DCanvas
	{
	public:
		QList<QV3DPointF> points3D;
		QList<QVCameraPose> cameras;

		void setPoints3D(const QList<QV3DPointF> &p3D)
			{
			points3D = p3D;
			}

		void setCameras(const QList<QVCameraPose> &cams)
			{
			cameras = cams;
			}

		SfMViewer(const QList<QVCameraPose> &cameras, const QList<QV3DPointF> &points3D, const QString &name = QString()):
			QV3DCanvas(name, 0.5, true),
			points3D(points3D), cameras(cameras)
			{
			}

		void display()
			{
			//std::cout << "[display] Start." << std::endl;
			glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
			
			glShadeModel(GL_FLAT);

			// Display points
			draw2(points3D, 0.025);

			// Display cameras
			QV3DPolylineF centers;
			foreach(QVCameraPose cameraPose, cameras)
				{
				const QV3DPolylineF polyline = cameraWireModel(cameraPose, 0.15, 0.3);
				draw(polyline, Qt::red);
				centers << cameraPose.getCenter();
				}
			draw(centers, Qt::yellow);
			}

		void draw2(const QList<QV3DPointF> &qv3DPointList, const double size)
			{
			glBegin(GL_POINTS);

			glPointSize(size);
			int i = 0; 

			foreach(QV3DPointF point, qv3DPointList)
				{
				qglColor(QColor(196,196,196));
				glVertex3f(point.x(), point.y(), point.z());
				i++;
				}
			glEnd();
			}

	};

