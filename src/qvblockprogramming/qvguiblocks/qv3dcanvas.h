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

#ifndef QVGLCANVAS_H
#define QVGLCANVAS_H

#include <QVProcessingBlock>
#include <QVQuaternion>
#include <QV3DPolylineF>

#include "qv3dmodel.h"

#ifndef DOXYGEN_IGNORE_THIS

/*!
@class QV3DEllipsoid qvblockprogramming/qvguiblocks/qv3dcanvas.h QV3DEllipsoid
@brief Ellipsoid 3D Object

This class models a 3D polyline.

@ingroup qvblockprogramming
@see QVPolyline
@see QVPolylineF
*/
class QV3DCanvas;

class QV3DEllipsoid: public QV3DModel
	{
	private:
		QColor color;
		double rx, ry, rz, cx, cy, cz;
		int lats, longs;
	public:
		QV3DEllipsoid(	const QColor color = Qt::yellow,
				const double rx = 0.5, const double ry = 0.5, const double rz = 0.5,
				const double cx = 0.0, const double cy = 0.0, const double cz = 0.0,
				const int lats = 100, const int longs = 100):QV3DModel(),
			color(color), rx(rx), ry(ry), rz(rz), cx(cx), cy(cy), cz(cz),
			lats(lats), longs(longs)
			{ }

		void paint(QV3DCanvas &glWidget);
	};

/*!
@class QV3DCanvas
@brief 3d scene representation widget.

This widget can be used to represent a 3D scene in a canvas window.

Like the @ref QVImageCanvas, properties of types QList<QV3DPointF>, QList<QV3DPolylineF> and QV3DPolylineF can be linked to objects derived from this class, and their contents (lists of 3D points and polylines) will be displayed in a 3D environment.

@todo Complete this documentation

@ingroup qvblockprogramming
*/
class QV3DCanvas : public QGLWidget, public QVPropertyContainer
	{
		Q_OBJECT
	
	public:
		QV3DCanvas(	const QString &title, const double zoom = 0.5, bool dr_center=FALSE,
				const QColor &backgroundColor = Qt::black, QWidget* parent=0);
	
		~QV3DCanvas ();
	
		virtual void init() {};
		virtual void display() {};
		virtual void reshape(int, int) {};
	
		/// @brief Sets the default background color for the canvas
		///
		/// @param color Color to be displayed in the background
		bool setBackgroundColor(const QColor &color)	{ backgroundColor = color; return true; };

		/// @brief Sets the default background color for the canvas
		///
		/// @param color Color to be displayed in the background
		void setAmbientLight(const double R, const double G, const double B)
			{
			ambientLightR = R;
			ambientLightG = G;
			ambientLightB = B;
			};
	
		/// @brief Sets the display color for a registered input property of the canvas
		///
		/// The points and line segments contained in properties of types QList<QPoint>, QList<QPointF>, QList<QVPolyline> and QList<QVPolylineF>
		/// are displayed in the canvas with a default color, assigned by the link method.
		/// The user can specify a non-default color value using this method.
		///
		/// @param color Color to be displayed in the background
		bool setDisplayColor(const QString &name, const QColor &color)	{ return setPropertyValue<QColor>("Color for " + name, color); }
		
		/// @brief Sets the display size for a registered input property of the canvas
		///
		/// Similarly to the @ref setDisplayColor, this method can be used to set the size of the line segments or the points to be displayed in the canvas.
		///
		/// @param size Point or line segment radius.
		bool setDisplaySize(const QString &name, const double size)	{ return setPropertyValue<double>("Size for " + name, size); }
	
		virtual bool linkUnspecifiedInputProperty(QVPropertyContainer *sourceContainer, QString sourcePropName, LinkType linkType);
	
		/// @brief Adds a 3D model object to be displayed in the canvas.
		///
		/// @todo Document better this method
		/// @param model 3D model object
		/// @see QV3DModel
		void add3DModel(QV3DModel &model)
			{
			models.append(&model);
			//QObject::connect(model.getInformer(), SIGNAL(modelUpdated()), this, SLOT(updateGL()), Qt::QueuedConnection);
			}
	
	
		void drawQVImage(QVGenericImage *image/*,bool adaptsize=TRUE,float low=0.0, float high=255.0*/);
	signals:
		void closed();
	
	protected:
	
		void draw(const QV3DPolylineF &qv3DPolyline, const QColor color = Qt::red, const double size = 1);
		void draw(const QList<QV3DPointF> &qv3DPointList, const QColor color = Qt::red, const double size = 1);
	
		void initializeGL();
		void paintGL();
		void resizeGL(int w, int h );
	
		void viewer();
	
		void mousePressEvent(QMouseEvent * event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void wheelEvent(QWheelEvent *event);
		void keyPressEvent(QKeyEvent *event);
		
		void closeEvent(QCloseEvent * event);

		const QColor	getNextColor()
			{
			QColor color = qvColors[colorCursor++];
			colorCursor %= 10;
			return color;
			}
	
	private:
		//QList<QVGenericImage*> imageList;

		void draw_center_of_rotation();
		
		int beginx, beginy;
		QVQuaternion trackballQuat;
		double cx,cy,cz;
		double ambientLightR, ambientLightG, ambientLightB;
		bool dr_center;
		double zoom, fov;
		bool pressedleft, pressedright;
		
		int colorCursor;
		QColor backgroundColor;
		QList< QV3DModel *> models;
	};

#endif

#endif
