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

#ifndef QVCANVAS_H
#define QVCANVAS_H

#include <QGLWidget>
#include <QPainter>
#include <QString>
#include <QMenu>

#include <QVImage>
#include <QVPolyline>
#include <QVCameraPose>

class QwtScaleWidget;
class QwtLinearScaleEngine;
class QwtScaleDiv;
class QToolButton;
class QStatusBar;
class QVImageArea;

/*!
@class QVPainter qvblockprogramming/qvguiblocks/qvcanvas.h QVPainter
@brief Inherits from QPainter to allow versatile drawing on a @ref QVImageCanvas object.

Nobody except internally the QVImageCanvas class should create or destroy QVPainters, so you do not need to construct this kind of objects. You will only need to use them through the QVImageCanvas::getQVPainter() method when subclassing QVImageCanvas (see documentation on this last class for coding examples).
*/
class QVPainter: public QPainter
{
friend class QVImageArea;

private:
	// Nobody except QVImageArea should create or destroy QVPainters:
	QVPainter(QVImageArea *imageArea): QPainter()
		{ this->imageArea = imageArea;};
	~QVPainter() { };
public:

	/// @brief Draws a @ref QVImage<T,n> of any type <i>T</i> and size <i>n</i> in the corresponding QVImageCanvas.
	///
	/// Draws a @ref QVImage<T,n> of any type <i>T</i> and size <i>n</i> in the corresponding QVImageCanvas. The
	/// image is drawn according to its current ROI (position and size).
	/// @param image QVImage to draw.
	/// @param adaptsize If true, the QVImageArea is rescaled according to the image drawn.
	/// @param low Float value which will correspond to darkest (black) colour.
	/// @param high Float value which will correspond to brightest (white) colour.
	void drawQVImage(QVGenericImage *image,bool adaptsize=TRUE,float low=0.0, float high=255.0);

	/// @brief Draws text in a given pixel position of the QVImageCanvas which does not scale with zooming.
	///
	/// See corresponding (scaled) method <a href="http://doc.qt.nokia.com/4.7/qpainter.html#drawText">QPainter::drawText()</a> for details on input parameters.
	void drawTextUnscaled(const QPointF & position, const QString & text);

	/// @brief Draws text in a given pixel position of the QVImageCanvas which does not scale with zooming.
	///
	/// See corresponding (scaled) method <a href="http://doc.qt.nokia.com/4.7/qpainter.html#drawText-9">QPainter::drawText()</a> for details on input parameters.
	void drawTextUnscaled(const QPoint & position, const QString & text);

	/// @brief Draws text in a given rectangle of the QVImageCanvas which does not scale with zooming.
	///
	/// See corresponding (scaled) method <a href="http://doc.qt.nokia.com/4.7/qpainter.html#drawText-10">QPainter::drawText()</a> for details on input parameters.
	void drawTextUnscaled(const QRectF & rectangle, int flags, const QString & text, QRectF * boundingRect = 0);

	/// @brief Draws text in a given rectangle of the QVImageCanvas which does not scale with zooming.
	///
	/// See corresponding (scaled) method <a href="http://doc.qt.nokia.com/4.7/qpainter.html#drawText-11">QPainter::drawText()</a> for details on input parameters.
	void drawTextUnscaled(const QRect & rectangle, int flags, const QString & text, QRect * boundingRect = 0);

	/// @brief Draws text in a given position of the QVImageCanvas which does not scale with zooming.
	///
	/// See corresponding (scaled) method <a href="http://doc.qt.nokia.com/4.7/qpainter.html#drawText-12">QPainter::drawText()</a> for details on input parameters.
	void drawTextUnscaled(int x, int y, const QString & text);

	/// @brief Draws text in a given position of the QVImageCanvas which does not scale with zooming.
	///
	/// See corresponding (scaled) method <a href="http://doc.qt.nokia.com/4.7/qpainter.html#drawText-13">QPainter::drawText()</a> for details on input parameters.
	void drawTextUnscaled(int x, int y, int width, int height, int flags, const QString & text, QRect * boundingRect = 0);

	/// @brief Draws text in a QVImageCanvas which does not scale with zooming, using the specified option to control its positioning and orientation.
	///
	/// See corresponding (scaled) method <a href="http://doc.qt.nokia.com/4.7/qpainter.html#drawText-14">QPainter::drawText()</a> for details on input parameters.
	void drawTextUnscaled(const QRectF & rectangle, const QString & text, const QTextOption & option = QTextOption());

private:
	// QVPainter keeps a private reference to its corresponding QVImageArea:
	QVImageArea *imageArea; 
};

// Not documented for now

//#ifndef DOXYGEN_IGNORE_THIS

enum TPolyMode {
	LIST = 0x01,
	LINE = 0x02,
	CLOSED = 0x03
};

/************************* QVImageArea auxiliary class ************************/

// Auxiliary class, not available to library users (only to be used by
// QVCanvas, which will be its friend). Thus, everything is private.
// Note.- Not declared as a nested class because of QT moc limitations
// with the Q_OBJECT macro.

class QVImageArea : public QGLWidget
{
	Q_OBJECT

friend class QVCanvas;
friend class QVPainter;

private:
	// static class list of pointers to nstances of QVImageArea. The new
	// imageAreas will share context with first, in order to be fast enough
	// (otherwise, use of multiple context can make the application very
	// slow on some graphic cards!).
	static QList<QVImageArea *> image_areas;
	
	void initObject(int w, int h); // Auxiliary function for constructors.

	// Nobody except QVCanvas should create or destroy QVImageArea's:
	// Constructor for first instance:
	QVImageArea(int w, int h,QWidget *parent);
	// Constructor for second and subsequent instances:
	QVImageArea(int w, int h,QWidget *parent,QGLWidget *other);
	~QVImageArea() {};
	
	enum TMouseMode {
		NONE = 0x01,
		DRAG = 0x02,
		SEL = 0x03,
		POLY = 0x04,
		ZOOM = 0x05
	};

signals:
	void newGeometry(int origheight,int origwidth,int topleftx,int toplefty,int width,int height, int zoom);
	void newMousePosition(float x,float y);
	void mouseLeavesImageArea(bool leaves);
	void rectSelected(QRect rect);
	void polySelected(QPoint point, bool reset, TPolyMode mode);

protected:
	// void initializeGL() {};
	void wheelEvent(QWheelEvent *event);
	void resizeGL(int width, int height);
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void leaveEvent(QEvent *event);
        void beginDrawWorldFromCamera(const double fx, const double fy, const QVCameraPose &cameraPosition);
        void endDrawWorldFromCamera();

private:
	const int max_zoom;
	void drawQVImage(QVGenericImage *image,bool adaptsize,float low,float high);
	void centerZoom(int zoom);
	void resizeImageArea(int w,int h);
	int zoom,origheight,origwidth;
	QPoint topLeft;
	QRect selRect,zoomRect;
	QVPolyline selPoly;
	QRect innerRect();
	QRect outerRect();
	TMouseMode mouseMode;
	TPolyMode polyMode;
	QPoint firstPos,lastPos;
	bool dragging,drawSel;
	QRectF intuitiveRect(QRect rect);
	QVPainter *painter;
	QList<QVGenericImage*> imageList;
};

class QVCanvas : public QWidget
{
friend class QVImageArea;
	Q_OBJECT
public:

	void qglColor(const QColor &color)
		{
		glColor3ub(color.red(), color.green(), color.blue());
		}

	QVCanvas(QWidget *parent = 0);
	~QVCanvas();
        int getZoom() const { return imageArea->zoom; }
        QRect getViewport() const { return QRect(imageArea->topLeft,QSize(imageArea->width(),imageArea->height())); } //OJO, document in the manual that all viewport is multiplied by actual zoom.
        QSize getSize() const { return QSize(imageArea->origwidth,imageArea->origheight); }
        QVPainter *getQVPainter() const { return imageArea->painter; };
        QRect getSelectionRectangle() const { return imageArea->selRect; }
        void beginDrawWorldFromCamera(const double fx, const double fy, const QVCameraPose &cameraPosition)
		{
		imageArea->beginDrawWorldFromCamera(fx,fy,cameraPosition);
		}
        void endDrawWorldFromCamera() {
            imageArea->endDrawWorldFromCamera();
        }
	const QVImage<uChar, 3> contentImage()	const	{ return QVImage<uChar, 3>(imageArea->renderPixmap().toImage()); }

protected:
	virtual void viewer() { /* Default is to paint nothing. */ };

signals:
	void newGeometry(int origwidth,int origheight,int topleftx,int toplefty,int width,int height, int zoom);
	//void refreshed();

public slots:
	void setGeometry(int origwidth,int origheight,int topleftx,int toplefty,int width,int height, int zoom);
	void refreshImageArea();
	virtual void rectSelectedSlot(QRect rect) = 0 ;
	virtual void polySelectedSlot(QPoint point, bool reset, TPolyMode mode) =0;

private slots:
	void drawSelClicked(bool checked);
	void zoomRectClicked(bool checked);
	void selPolyClicked(bool checked);
	void selPolyChangedToList();
	void selPolyChangedToLine();
	void selPolyChangedToClosed();
	void selRectClicked(bool checked);
	void dragClicked(bool checked);
	void zoomInClicked();
	void zoomOutClicked();
	void zoomOriginalClicked();
	void newMousePositionSlot(float x,float y);
	void mouseLeavesImageAreaSlot(bool leaves);

protected:
	QVImageArea *imageArea;

private:
	#ifdef QVQWT
	QwtScaleWidget *scaleWidgetX,*scaleWidgetY;
	QwtLinearScaleEngine *scaleEngineX,*scaleEngineY;
	#endif

	QToolButton *buttonDrawSel,*buttonZoomIn,*buttonZoomOut,*buttonZoomOriginal,*buttonZoomRect,
		    *buttonselPoly,*buttonSelRect,*buttonDrag;
	QMenu *menuselPoly;
	QStatusBar *statusBar;
	void resizeEvent(QResizeEvent *event);
	int scaleWidgetsFixedWidth,statusBarWidgetFixedHeight;
	float mousePosX,mousePosY;
	bool mouseIsOut;
	QString statusMessage();
	TPolyMode polyMode;
};
// #endif //DOXYGEN_IGNORE_THIS
#endif
