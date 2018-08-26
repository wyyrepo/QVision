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

#ifndef QVIMAGECANVAS_H
#define QVIMAGECANVAS_H

#include "qvcanvas.h"

#include <QPointF>
#include <QVProcessingBlock>
#include <QVPolyline>
#include <QVPolylineF>
#include <QVCameraPose>
#include <QV3DPolylineF>
#include <qvblockprogramming/qvguiblocks/qv3dmodel.h>

/*!
@class QVImageCanvas qvblockprogramming/qvguiblocks/qvimagecanvas.h QVImageCanvas
@brief Display widget for @ref QVImage objects and other data types.

Class @ref QVImageCanvas can be used to create a very flexible and useful widget to show @ref QVImage objects. It can also be used as an input widget, which reads selection rectangles and/or lists of points as clicked by the user (see below). Finally, it is also prepared to draw 3D scenes on top of the image, using OpenGL, which is convenient for augmented reality applications.

This widget is in fact a property container, and as such it will read the image to be displayed from an output dynamic property contained in another property container (usually a @ref QVProcessingBlock object), and will also use output properties for the user to be able to read the aforementioned selection rectangles and point lists.

It is used as follows. First, the programmer must create the QVImageCanvas object in the <i>main()</i> function of a program; then, a link to a QVImage type property from a property holder must be created. For example:

\code
[...]

CannyBlock cannyBlock("Canny Block");

[...]

QVImageCanvas imageCanvas("Canny");
cannyBlock.linkProperty("Input Image",imageCanvas);

[...]
\endcode

When the application executes, it will automatically create a window like the following:

\image html qvimagecanvas_penguin.png

@note The nice horizontal and vertical scale rules are QWT widgets. The QWT library must be installed, and the QVision must be compiled to use it, for the @ref QVImageCanvas widget to display them. See section @ref OptionalLibraries for more info about this.

You can see it has a zoom number indicator (<i>z = 1</i>), horizontal and vertical rules (in pixels), and some buttons. These can be used to control zooming and moving around a zoomed area of the image. A detailed explanation of each one follows:

<table>
<tr><th><b>Zoom in button</b></th>
\image html qvimagecanvas_zoomin.png
<td>This button zooms the image in. Canvas window doesn't change size, but the area of the image displayed becomes smaller by a factor of 4 (width and height gets divided by 2). The label of the left bottom corner displays the text
\code
z=<zoom>
\endcode
where <i>&lt;zoom&gt;</i> is a number indicating the zoom factor that divides width and height in the actual zoom level.</td></tr>

<tr><th><b>Zoom out button</b></th>
\image html qvimagecanvas_zoomout.png
<td>This button divides zoom factor by 2, if it is equal or greater than 2. If the canvas window is bigger than the image at the final zoom, it is adjusted to the size of the latter.</td></tr>

<tr><th><b>Zoom restore button</b></th>
\image html qvimagecanvas_zoomrestore.png
<td>This button sets zoom factor by 1, and resizes canvas window to its original size.</td></tr>

<tr><th><b>Select zoom region button</b></th>
\image html qvimagecanvas_zoomregion.png
<td>This button lets you select a rectangle in the image to zoom, adjusting zoom factor and canvas window size to it.</td></tr>

<tr><th><b>Select polyline button</b></th>
\image html qvimagecanvas_polyline.png
<td>This button lets you select points in the image. The created points list can then be accessed to in the program by reading the "poly select" imageCanvas output property (a QVPolyline). You can expand this button by pushing it for a few seconds, and then you will be able to select a point list representation, a polyline representation, or a closed polyline representation. Right-clicking anywhere on the image with this button checked will reset the "poly select" ImageCanvas output property to an empty QVPolyline. </td></tr>

<tr><th><b>Select ROI button</b></th>
\image html qvimagecanvas_roi.png
<td>This button lets you select a rectangle in the image. That rectangle can be again accessed to using the "rect select" imageCanvas output property (a QRect). Right-clicking anywhere on the image with this button checked will reset the "rect select" ImageCanvas output property to an empty QRect.</td></tr>

<tr><th><b>Drag mode</b></th>
\image html qvimagecanvas_drag.png
<td>This button activates drag mode. With it you can move around the image displayed in the canvas window, if the zoom factor forces the canvas window to show only a sub-region of the image, by holding click and dragging on the shown image.</td></tr>
</table>

In the following figure you can see a zoomed canvas window showing a sub-region of the original image:

\image html qvimagecanvas_penguinpixels.png

Another interesting feature of this widget is that at a zoom factor equal or larger than 32, the canvas renders the gray-scale pixel value over every pixel if the image is gray-scale, or the three different values for each of the RGB channels over every pixel, if the image is RGB, as shown below:

\image html qvimagecanvas_penguinpixelnumbers.png

The canvas also knows how to show numeric float values, when showing images of type QVImage<sFloat,1> or QVImage<sFloat,3> (for these cases, see also method QVImageCanvas::setSaturationRange).

Other interesting features of QVImageCanvas:

- <b>User input</b>: you can read the user selected rectangle and/or selected list of points by adequately linking the QVImageCanvas predefined output properties "rect select" and "poly select" to your processing block(s) (see also QVImageCanvas::linkSelectedRectangle and QVImageCanvas::linkSelectedPolyline methods). For example:
\code

[...]

class MyWorker: public QVProcessingBlock
	{
	public:
		MyWorker(QString name = QString()): QVProcessingBlock(name)
			{
			addProperty< QVImage<uChar,1> >("Input image", inputFlag|outputFlag);
			addProperty< QVImage<uChar,1> >("Output image", outputFlag);
			addProperty<QRect>("in rect selec", inputFlag);
			addProperty<QVPolyline>("in points", inputFlag);
			}
		void iterate()
			{
			QVImage<uChar> image = getPropertyValue< QVImage<uChar,1> >("Input image");
			QRect rect = getPropertyValue<QRect>("in rect selec");
			QVPolyline poly = getPropertyValue<QVPolyline>("in points");
			QVImage<uChar> dest = image;

			// Darken the selected rectangle (ROI) area:
			if (rect != QRect()) image.setROI(rect);
			AddC(image, 10, dest, 1, QPoint(rect.x(), rect.y()));
			dest.resetROI();

			// Undo darkening on selected polyline's points:
			for (int i = 0; i < poly.size(); i++) {
				int x = poly[i].x(), y = poly[i].y();
				if ( (x >= 0) && (x < image.getCols()) && (y >= 0) && (y < image.getRows()) )
					dest(x, y) = image(x, y);
			}

			setPropertyValue< QVImage<uChar,1> >("Output image", dest);
			}
	};

int main(int argc, char *argv[])
	{
	QVApplication app(argc, argv, "Example program for QVision library." );

	MyWorker myWorker("Worker");
	QVMPlayerReaderBlock camera("Video");
	camera.linkProperty(&myWorker, "Input image");

	QVDefaultGUI interface;

	QVImageCanvas imageCanvas("Features");
	myWorker.linkProperty("Output image", imageCanvas);
	imageCanvas.linkProperty("rect select", myWorker, "in rect selec");
	imageCanvas.linkProperty("poly select", myWorker, "in points");
	// Alternatively, you could have also use the QVImageCanvas::linkSelectedPolyline and
	// QVImageCanvas::linkSelectedRectanglemethods:
	// imageCanvas.linkSelectedRectangle(myWorker, "in rect selec");
	// imageCanvas.linkSelectedPolyline(myWorker, "in points");

	return app.exec();
	}
\endcode

This would be an example output for this program:

\image html qvimagecanvas_selections.png

- <b>Drawing properties by default</b>:
User registered input properties of types QVPolyline, QVPolylineF, QList<QPoint>, QList<QPointF>, QList<QVPolyline> and QList<QVPolylineF> are adequately displayed by the canvas automatically, by the simple fact of linking them to it. For example:
\code
[...]
class MyWorker: public QVProcessingBlock {
	public:
		MyWorker(QString name = QString()): QVProcessingBlock(name) {
			[...]
			addProperty<QVPolyline>("out polyline", outputFlag);
		}

		void iterate() {
			[...]
			QVPolyline polyline;
			polyline.append(QPoint(10,10));
			polyline.append(QPoint(20,10));
			polyline.append(QPoint(20,20));
			polyline.append(QPoint(10,30));
			setPropertyValue< QVPolyline >("out polyline", polyline);
		}
	};

int main(int argc, char *argv[]) {
	[...]
	myWorker.linkProperty("out polyline",imageCanvas);
	[...]
}
\endcode

This would be the output for this program:

\image html qvimagecanvas_default_drawings.png

The user can also customize the output of each property using the methods QVImageCanvas::setColor and QVImageCanvas::setRadius  (see below).

- <b>Further customizing drawings</b>:

The user is also free to draw anything he desires by inheriting from the QVImageCanvas class and reimplementing the QVImageCanvas::custom_viewer method. This is a simple example:
\code
[...]
class MyImageCanvas : public QVImageCanvas {
        public:
        MyImageCanvas(QString name) : QVImageCanvas(name) {} ;
        void custom_viewer(){
                // For simplicity, here we will only draw some primitives at fixed locations. Of course, in a real
                // example it will be much more common to read the parameter of the primitives to draw from some
                // input properties of the canvas (do not forget that QVImageCanvas are also QVPropertyContainers),
                // which will themselves be linked to the output properties of other QVProcessingBlocks.
                getQVPainter()->setPen(Qt::yellow);
                getQVPainter()->setBrush(QBrush(Qt::magenta, Qt::DiagCrossPattern));
                getQVPainter()->drawEllipse(50, 50, 30, 40);
                getQVPainter()->drawEllipse(100, 100, 70, 25);
                getQVPainter()->drawEllipse(100, 100, 70, 25);
                getQVPainter()->drawTextUnscaled(QPointF(20.5,30.5), "Message");
                getQVPainter()->drawText(QPointF(40.5,10.5), "Message scaled");
                [...]
        }
};

int main(int argc, char *argv[]) {
	[...]
	MyImageCanvas imageCanvas("Features");
	[...]
}
\endcode

This would be the output for this program:

\image html qvimagecanvas_customized_drawings.png

It is important to note that you can use any of the many painting methods implemented in the powerful Qt <a href="http://doc.qt.nokia.com/4.7/qpainter.html">QPainter</a> class in your custom_viewer() reimplementation. You only have to use the <i>getQVPainter()->"original QPainter method"</i> technique as in the example. All the drawings will be done using pixel coordinates, and the QVImageCanvas zooming and measure rulers will behave accordingly as expected, without any special attention required from the programmer. The (pointer to) object returned by the getQVPainter() method is in fact a QVPainter object which directly inherits from <a href="http://doc.qt.nokia.com/4.7/qpainter.html">QPainter</a> and that, in addition to all the <a href="http://doc.qt.nokia.com/4.7/qpainter.html">QPainter</a> available methods, offers a few additional drawing methods, such as QVPainter::drawTextUnscaled() and QVPainter::drawQVImage(), which will also behave intuitively when zooming and moving around the QVImageCanvas.

- <b>Augmented reality</b>:

Finally, the programmer can also easily make augmented reality applications using the beginDrawWorldFromCamera() and
endDrawWorldFromCamera() methods. Here is a simple example (see documentation on those methods for a more detailed explanation):

\code
void MyImageCanvas::custom_viewer()
{
    // If you linked a QVImage to this QVImageCanvas, then it is shown yet
    // as background.

    // Now, given that you can compute your camera position and calibration, you can paint 3D
    // virtual objects in your canvas:
    QVEuclideanMapping3 cameraPosition;
    double focalx,focaly;
    computeCameraPositionAndCalibration(...whatever...,&cameraPosition,&focalx,&focaly);

    // Direct OpenGL calls in world coordinates go between beginDrawWorldFromCamera(...) and
    // endDrawWorldFromCamera():
    beginDrawWorldFromCamera(focalx,focaly,cameraPosition);
    // Colored axis X (Red), Y (Green) and Z (Blue):
    glBegin(GL_LINES);
      glColor3ub(255,0,0);
      glVertex3f(0,0,0);
      glVertex3f(0.25,0,0);
      glColor3ub(0,255,0);
      glVertex3f(0,0,0);
      glVertex3f(0,0.25,0);
      glColor3ub(0,0,255);
      glVertex3f(0,0,0);
      glVertex3f(0,0,0.25);
    glEnd();
    // Yellow sphere of 0.25 radius, centered in the world point (0.25,0.25,0.25):
    glColor3ub(255,255,0);
    glTranslatef(0.25,0.25,0.25);
    glutWireSphere(0.25,17,9);

    // You must always end with a call to endDrawWorldFromCamera() method, to
    // ensure adequate restore of things:
    endDrawWorldFromCamera();

    //... Other 2D painting stuff (again in image coordinates)...
}
\endcode

This would be an example of drawing an sphere on top of an image of a template, which has been used
to compute camera position and calibration. In this example, the long sides of the template have
a world length of exactly 1.0:

\image html qvimagecanvas_augmented_reality.png

A simpler method to display augmented objects in an image canvas is by overloading the method @ref custom_viewer_3D.
This method should paint the 3D objects, regarding a fixed coordinate reference system.

\code
class ARCanvas : public QVImageCanvas
	{
	public:
		ARCanvas(QString name) : QVImageCanvas(name)	{ };

		void custom_viewer_3D()
			{
			glEnable(GL_LIGHTING);		// Enable lighting.
			glEnable(GL_LIGHT0);		// Enable light zero (note: uses default values).
			glEnable(GL_COLOR_MATERIAL);	// Configure glColor().
			glEnable(GL_DEPTH_TEST);	// Enable depth testing.
			glClear(GL_DEPTH_BUFFER_BIT);	// Clear depth buffers.

			// Draw a wire teapot at the origin of coordinates using GLUT primitives.
			glColor3ub(128,196,255);

			glRotatef(90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0,0.20,0.0);

			glutSolidTeapot(0.3);
			};
	};
\endcode

In the <i>main</i> function, the camera pose and calibration is specified through the properties <i>Camera calibration matrix</i> and <i>Camera pose</i>, regarding the same fixed coordinate reference system:

\code
	ARCanvas imageCanvas("AR canvas");

	[...]

	processingBlock.linkProperty("imageIn",&imageCanvas);
	processingBlock.linkProperty("Camera calibration matrix", &imageCanvas);
	processingBlock.linkProperty("Camera pose", &imageCanvas);

\endcode

See example <a href="AugmentedReality_8cpp.html">AugmentedReality</a> for a complete example of an augmented reality application using this method.

@ingroup qvblockprogramming
*/
class QVImageCanvas: public QVCanvas, public QVPropertyContainer
	{
		Q_OBJECT

	protected:
		QList< QV3DModel *> models;

	public:

		void add3DModel(QV3DModel &model)
			{
			models.append(&model);
			//QObject::connect(model.getInformer(), SIGNAL(modelUpdated()), this, SLOT(updateGL()), Qt::QueuedConnection);
			}

		void draw(const QV3DPolylineF &qv3DPolyline, const QColor color = Qt::red, const double size = 1)
			{
			glPointSize(size);
			glBegin(GL_LINES);
			glColor3ub(color.red(), color.green(), color.blue());
			//qglColor(color);
			for (int i = 1; i < qv3DPolyline.size(); i++)
				{
				glVertex3f(qv3DPolyline[i].x(), qv3DPolyline[i].y(), qv3DPolyline[i].z());
				glVertex3f(qv3DPolyline[i-1].x(), qv3DPolyline[i-1].y(), qv3DPolyline[i-1].z());
				}
			glEnd();
			}

		void draw(const QList<QV3DPointF> &qv3DPointList, const QColor color = Qt::red, const double size = 1)
			{
			glBegin(GL_POINTS);
			glColor3ub(color.red(), color.green(), color.blue());
			//qglColor(color);
			glPointSize(size);
			foreach(QV3DPointF point, qv3DPointList)
			    glVertex3f(point.x(), point.y(), point.z());
			glEnd();
			}


		/// @brief Image canvas constructor
                ///
		/// @param name Name of the image canvas
		/// @param parent parent QObject of the canvas
		QVImageCanvas(const QString name = QString(), QWidget *parent=0);

		/// @brief Sets the display color for a registered input property of the canvas
                ///
		/// Registered properties of types QList<QPoint>, QList<QPointF>, QList<QVPolyline> and QList<QVPolylineF> are displayed in the canvas
		/// with a default color assigned by the link method. The user can specify a non-default color value using method @ref setColor.
                ///
		/// The following code registers an image property, and a QList<QPointF> property in an image canvas from a source block, and sets the
		/// display color of the points received from the block, through the <i>Detected points</i> property to be red.
                ///
		/// @code
		/// QVImageCanvas imageCanvas("Harris corners");
		/// harrisCornersDetector.linkProperty("Input image", imageCanvas);
 		/// // Property "Detected points" is of type QList<QpointF>
		/// harrisCornersDetector.linkProperty("Detected points", imageCanvas);
		/// imageCanvas.setColor("Detected points", Qt::red);
		/// @endcode
                ///
		/// @param name Name of the source property to set the color.
		/// @param QColor Color to display the elements contained in the property.
		bool setColor(const QString &name, const QColor &color)
			{ return setPropertyValue<QColor>("Color for " + name, color); }

		/// @todo document
		bool setPrintTags(const QString &name, const bool &printTags)
			{ return setPropertyValue<bool>("Print tags for " + name, printTags); }

		/// @brief Sets the display radius for a registered input property of the canvas
                ///
		/// Some registered properties, for example points, are displayed in the canvas with a default radius size of 3. 
		/// As the @ref setColor, this method can be used to specify a display radius size different than the default.
                ///
		/// @param name Name of the source property to set the radius.
		/// @param radius Radius size of the property.
		bool setRadius(const QString &name, const int &radius)
			{ return setPropertyValue<int>("Radius for " + name, radius); }

		/// @brief Sets the saturation range to display floating point images
                ///
		/// The default saturation range to display a floating point image (QVImage<sFloat, 1> or QVImage<sFloat, 3>) is [0, 255]. This means that
                /// pixel intensity values outside that range will be set to 0 or 255, whether the intensity is below or above that range.
		/// 
		/// This method can be used to specify a different saturation range.
                ///
		/// @param low Lower value for the saturation range.
		/// @param high Higher value for the saturation range.
		void setSaturationRange(const float low, const float high);

		/// @brief Link selected polyline property with a block's input property.
		/// @todo expand this documentation
		bool linkSelectedPolyline(QVPropertyContainer *destinationContainer, QString destinationPropName)
			{
			return linkProperty("poly select", destinationContainer, destinationPropName);
			}

		/// @brief Link selected rectangle property with a block's input property.
		/// @todo expand this documentation
		bool linkSelectedRectangle(QVPropertyContainer *destinationContainer, QString destinationPropName)
			{
			return linkProperty("rect select", destinationContainer, destinationPropName);
			}

		/// @brief Link selected polyline property with a block's input property.
                ///
		/// This is an overloaded function provided for convenience.
		/// @see linkSelectedPolyline(QVPropertyContainer *, QString)
		bool linkSelectedPolyline(QVPropertyContainer &destinationContainer, QString destinationPropName)
			{
			return linkSelectedPolyline(&destinationContainer, destinationPropName);
			}

		/// @brief Link selected rectangle property with a block's input property.
                ///
		/// This is an overloaded function provided for convenience.
		/// @see linkSelectedRectangle(QVPropertyContainer *, QString)
		bool linkSelectedRectangle(QVPropertyContainer &destinationContainer, QString destinationPropName)
			{
			return linkSelectedRectangle(&destinationContainer, destinationPropName);
			}

		/// @brief Display user defined data types method
                ///
		/// By reimplementing this method on @ref QVImageCanvas subclasses, the developer can modify the way the objects are displayed in the canvas, or
		/// specify the way new user data type objects must be displayed.
		/// 
		/// These subclasses can create image canvas objects which display registered objects the new way.
		/// 
		/// Method @ref custom_viewer is called whenever the canvas must be repainted, for example due to changes in the input properties or a
		/// canvas resizement. The reimplemented code for this method must read the user defined properties, and use @ref QVImageCanvas or QWidget
		/// functionality to correctly display them.
                ///
		/// An example @ref custom_viewer function reimplementation follows:
                ///
		/// @code
		/// void MyImageCanvas::custom_viewer()
		/// 	{
		///	foreach(QString propertyName, getPropertyListByType< QList< QVPolylineF > >())
		///		{
		///		QList< QVPolylineF > polylineList = getPropertyValue< QList< QVPolylineF > >(propertyName);
		///		foreach(QVPolylineF polyline, polylineList)
		///			{
		///			// Set the color of the polyline
		///			const int pointHash = qHash(polyline.first());
		///			draw(polyline, qvColors[pointHash % 10]);
                ///
		///			// Draw red dots on the end of the polyline
		///			getQVPainter()->setPen(Qt::red);
		///			getQVPainter()->setBrush(QBrush(Qt::red, Qt::SolidPattern));
		///			getQVPainter()->drawEllipse(polyline.first().x()-1, polyline.first().y()-1, 3, 3);
		///			getQVPainter()->drawEllipse(polyline.last().x()-1, polyline.last().y()-1, 3, 3);
		///			}
		///		}
		///	}
		/// @endcode
                ///
		/// Image canvas objects created from the class <i>MyImageCanvas</i>, which inherits from @ref QVImageCanvas will display polylines
		/// contained in input polyline lists with different colors, depending on the location of their first point, and red dots of radius 3 at the
		/// ends of each polyline.
		virtual void custom_viewer() { };

		virtual void custom_viewer_3D() { };

		/// @deprecated use @ref QVImageCanvas::setSaturationRange(const float,const float) instead.
		void setLowHigh(float low,float high)
			{
			std::cout << "DEPRECATED, use setSaturationRange instead" << std::endl;
			setSaturationRange(low, high);
			}

		/// @brief Returns a QVPainter object to perform custom drawings in the canvas.
                ///
		/// Returns a QVPainter object to perform custom drawings when reimplementing the
		/// QVImageCanvas::custom_viewer() method in QVImagecanvas subclasses.
		QVPainter *getQVPainter() { return QVCanvas::getQVPainter(); };


                /// @brief Returns current zoom of QVImagecanvas.
                ///
                /// Returns current zoom of QVImagecanvas, as currently defined by user. Possible
                /// return values are 1, 2, 4, 8, 16, 32, 64 or 128.
                int getZoom() const { return QVCanvas::getZoom(); };

                /// @brief Returns current viewport of QVImagecanvas.
                ///
                /// Returns a QRect containing the viewport which is currently visible in the
                /// QVImageCanvas. IMPORTANT: to avoid losing precission when zoomed in, the
                /// returned rectangle is in fact multiplied by the current zoom. Actual
                /// coordinates of top left corner, therefore, could be obtained with subpixel
                /// accuracy using the following expressions:
                /// @code
                /// float x_subp = (float)getViewport().topLeft().x()/(float)getZoom();
                /// float y_subp = (float)getViewport().topLeft().y()/(float)getZoom();
                /// @endcode
                /// The same applies for current height and width of the viewport:
                /// @code
                /// float w_subp = (float)getViewport().width()/(float)getZoom();
                /// float h_subp = (float)getViewport().height()/(float)getZoom();
                /// @endcode
                QRect getViewport() const { return QVCanvas::getViewport(); };

                /// @brief Returns the original image size of the QVImagecanvas.
                ///
                /// Returns the original image size of the QVImagecanvas (i.e. without taking into
                /// account zoom and viewport selected by user; just the original size in pixels
                /// of the main image of the QVImageCanvas).
                QSize getSize() const { return QVCanvas::getSize(); };


                /// @brief Prepares OpenGL to draw directly the world as seen from the camera.
                ///
                /// This function saves all the painting state of the QVImageCanvas, and pushes the
                /// adequate matrices in the OpenGL stack so that subsequent OpenGL drawing
                /// primitives can be directly drawn in world coordinates, and they will be shown
                /// in the canvas just as would be seen from the camera with the given intrinsic
                /// and extrinsic calibration. Useful for augmented reality applications, where
                /// the programmer wants to augment the input image with virtual objects, and he
                /// has managed to guess the current camera position and calibration. Its usage is
                /// very simple. For example, you could do the following in your custom_viewer()
                /// reimplementation:
                /// @code
                /// void MyImageCanvas::custom_viewer()
                /// 	{
                ///	// If you linked a QVImage to this QVImageCanvas, then it is shown yet
                ///     // as background.
                ///
                ///     // Then you can use some more QPainter methods to draw directly in the
                ///     // image plane...
                ///	getQVPainter()->setPen(Qt::red);
                ///	getQVPainter()->setBrush(QBrush(Qt::red, Qt::SolidPattern));
                ///	getQVPainter()->drawEllipse(...use image coordinates...);
                ///
                ///     // ... and now, given that you can compute your camera position and
                ///     // calibration, you can paint 3D virtual objects in your canvas this way:
                ///     QVEuclideanMapping3 cameraPosition;
                ///     double focalx,focaly;
                ///
                ///     computeCameraPositionAndCalibration(...whatever...,
                ///                                         &cameraPosition,&focalx,&focaly);
                ///
                ///     beginDrawWorldFromCamera(focalx,focaly,cameraPosition);
                ///     // Colored axis X (Red), Y (Green) and Z (Blue) in canonical positions:
                ///     glBegin(GL_LINES);
                ///       glColor3ub(255,0,0);
                ///       glVertex3f(0,0,0);
                ///       glVertex3f(1.0,0,0);
                ///       glColor3ub(0,255,0);
                ///       glVertex3f(0,0,0);
                ///       glVertex3f(0,1.0,0);
                ///       glColor3ub(0,0,255);
                ///       glVertex3f(0,0,0);
                ///       glVertex3f(0,0,1.0);
                ///     glEnd();
                ///
                ///     // You must always end with a call to endDrawWorldFromCamera() method, to
                ///     // ensure adequate restore of things:
                ///     endDrawWorldFromCamera();
                ///
                ///     // And, if you want, now you can continue drawing in the image plane
                ///	getQVPainter()->setPen(Qt::red);
                ///	getQVPainter()->drawEllipse(...use again image coordinates...);
                ///	}
                /// @endcode
                /// @param fx Camera focal length in the X axis (in pixels).
                /// @param fy Camera focal length in the X axis (in pixels).
                /// @param cameraPosition A QVEuclidenMapping3 containing current camera position
                ///        and rotation, in world coordinates.
                ///
                /// @see endDrawWorldFromCamera() custom_viewer()
                void beginDrawWorldFromCamera(const double fx, const double fy, const QVCameraPose &cameraPosition)
			{
			return QVCanvas::beginDrawWorldFromCamera(fx,fy,cameraPosition);
			};

                /// @brief Restores state of QVImageCanvas after augmented reality OpenGL drawing.
                ///
                /// @see beginDrawWorldFromCamera(double,double,QVEuclideanMapping3)
                void endDrawWorldFromCamera() { QVCanvas::endDrawWorldFromCamera(); };

                //QRect getSelectionRectangle() const { return QVCanvas::getSelectionRectangle(); };
                //const QVImage<uChar,3> contentImage()	const { return QVCanvas::contentImage() }

		void unlink();

		#ifndef DOXYGEN_IGNORE_THIS
		void viewer();
		#endif

	public slots:
		void rectSelectedSlot(QRect rect);
		void polySelectedSlot(QPoint point, bool reset, TPolyMode mode);

	protected:
		bool linkUnspecifiedInputProperty(QVPropertyContainer *sourceContainer, QString sourcePropName, LinkType linkType = AsynchronousLink);
		bool linkUnspecifiedOutputProperty(QVPropertyContainer *destContainer, QString destPropName, LinkType linkType = AsynchronousLink);
		bool treatUnlinkInputProperty(QString destPropName, QVPropertyContainer *sourceCont, QString sourcePropName);

		void draw(const QList<QPoint> &pointList, QColor color = Qt::red, bool printTags = false, int radius = 2);
		void draw(const QList<QPointF> &pointList, QColor color = Qt::red, bool printTags = false, double radius = 2);
		void draw(const QVPolyline &polyline, QColor color = Qt::red, bool printTags = false);
		void draw(const QVPolylineF &polylinef, QColor color = Qt::red, bool printTags = false);
		void draw(const QRect &rectangle, QColor color = Qt::red, bool printTags = false);
		void draw(const QPointFMatching &matching, const int radius = 2);

		void closeEvent(QCloseEvent *event) { Q_UNUSED(event); emit closed(); }

		const QColor	getNextColor()
			{
			QColor color = qvColors[colorCursor++];
			colorCursor %= 10;

			return color;
			}

		float _low,_high;
		int colorCursor, contentLinkedBlocks;

	signals:
		void closed();

	};

Q_DECLARE_METATYPE(TPolyMode);

#endif
