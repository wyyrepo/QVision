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

#include <math.h>
#include <iostream>
#include <qvdefines.h>

#include <QMouseEvent>
#include <QPainter>
#include <QScrollArea>
#include <QScrollBar>
#include <QGLWidget>
#include <QToolButton>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QGridLayout>

#include <math.h>

#include <QVImage>
#include "qvcanvas.h"

#ifdef QVQWT
#include <qwt_scale_widget.h>
#include <qwt_scale_engine.h>
#include <qwt_scale_div.h>
#endif

#include <GL/glu.h>

QList<QVImageArea *> image_areas;

// #ifndef DOXYGEN_IGNORE_THIS
void QVPainter::drawQVImage(QVGenericImage *image,bool adaptSize,float low,float high)
{
    imageArea->drawQVImage(image,adaptSize,low,high);
}


void QVPainter::drawTextUnscaled(const QPointF & position, const QString & text)
{
    save();
    resetMatrix();
    translate(-imageArea->topLeft);
    drawText(imageArea->zoom*position,text);
    restore();
}

void QVPainter::drawTextUnscaled(const QPoint & position, const QString & text)
{
    save();
    resetMatrix();
    translate(-imageArea->topLeft);
    drawText(imageArea->zoom*position,text);
    restore();
}

void QVPainter::drawTextUnscaled(const QRectF & rectangle, int flags,
                      const QString & text, QRectF * boundingRect)
{
    save();
    resetMatrix();
    translate(-imageArea->topLeft);
    drawText(QRectF(imageArea->zoom*rectangle.topLeft(),
                    imageArea->zoom*rectangle.size()),flags,text,boundingRect);
    if(boundingRect != 0)
        *boundingRect = QRectF(imageArea->zoom*boundingRect->topLeft(),
                               imageArea->zoom*boundingRect->size());
    restore();
}

void QVPainter::drawTextUnscaled(const QRect & rectangle, int flags,
                      const QString & text, QRect * boundingRect)
{
    save();
    resetMatrix();
    translate(-imageArea->topLeft);
    drawText(QRect(imageArea->zoom*rectangle.topLeft(),
                   imageArea->zoom*rectangle.size()),flags,text,boundingRect);
    if(boundingRect != 0)
        *boundingRect = QRect(imageArea->zoom*boundingRect->topLeft(),
                              imageArea->zoom*boundingRect->size());
    restore();
}

void QVPainter::drawTextUnscaled(int x, int y, const QString & text)
{
    save();
    resetMatrix();
    translate(-imageArea->topLeft);
    drawText(imageArea->zoom*x,imageArea->zoom*y,text);
    restore();
}

void QVPainter::drawTextUnscaled(int x, int y, int width, int height, int flags,
                      const QString & text, QRect * boundingRect)
{
    save();
    resetMatrix();
    translate(-imageArea->topLeft);
    drawText(imageArea->zoom*x,imageArea->zoom*y,imageArea->zoom*width,
             imageArea->zoom*height,flags,text,boundingRect);
    if(boundingRect != 0)
        *boundingRect = QRect(imageArea->zoom*boundingRect->topLeft(),
                              imageArea->zoom*boundingRect->size());
    restore();
}

void QVPainter::drawTextUnscaled(const QRectF & rectangle, const QString & text,
                      const QTextOption & option)
{
    save();
    resetMatrix();
    translate(-imageArea->topLeft);
    drawText(QRectF(imageArea->zoom*rectangle.topLeft(),
                    imageArea->zoom*rectangle.size()),text,option);
    restore();
}


void QVImageArea::initObject(int w, int h)
{
    zoom = 1;
    origwidth = w;
    origheight = h;
    topLeft = QPoint(0,0);
    selRect = QRect();
    zoomRect = QRect();
    selPoly = QVPolyline();
    setAttribute(Qt::WA_NoSystemBackground);
    setMouseTracking(TRUE);
    setMinimumSize(qMin(w,max_zoom),qMin(h,max_zoom));
    setMaximumSize(w,h);
    resize(w,h);
    mouseMode = NONE;
    polyMode = LIST;
    dragging = FALSE;
    drawSel= TRUE;
    emit newGeometry(origwidth,origheight,topLeft.x(),topLeft.y(),width(),height(),zoom);
}

QVImageArea::QVImageArea(int w, int h,QWidget *parent)
    : QGLWidget(QGLFormat(QGL::DoubleBuffer|QGL::NoDepthBuffer|
                QGL::DirectRendering|QGL::HasOverlay), parent), max_zoom(128)
{
    initObject(w,h);
}

QVImageArea::QVImageArea(int w, int h,QWidget *parent,QGLWidget *other)
    : QGLWidget(parent,other), max_zoom(128)
{
    initObject(w,h);
}

void QVImageArea::centerZoom(int zoom)
{
    if((zoom != this->zoom) and (zoom >= 1) and (zoom <= max_zoom)) {
        int old_zoom = this->zoom;
        this->zoom = zoom;
        setMaximumSize(zoom*origwidth,zoom*origheight);
        QPoint newTopLeft = zoom*(topLeft+QPoint(width(),height())/2)/old_zoom
                            - QPoint(width(),height())/2;
        if(newTopLeft.x() < 0)
            newTopLeft.setX(0);
        if(newTopLeft.y() < 0)
            newTopLeft.setY(0);
        if(newTopLeft.x()+width() > origwidth*zoom)
            newTopLeft.setX(origwidth*zoom-width());
        if(newTopLeft.y()+height() > origheight*zoom)
            newTopLeft.setY(origheight*zoom-height());
        topLeft = newTopLeft;
        makeCurrent();
        update();
        emit newGeometry(origwidth,origheight,topLeft.x(),topLeft.y(),width(),height(),zoom);
    }
}

void QVImageArea::resizeGL(int width, int height)
{
    QPoint newTopLeft = topLeft,newBottomRight = topLeft+QPoint(width,height);
    if(newBottomRight.x() > origwidth*zoom)
        newTopLeft.setX(origwidth*zoom-width);
    if(newBottomRight.y() > origheight*zoom)
        newTopLeft.setY(origheight*zoom-height);
    topLeft = newTopLeft;
    makeCurrent();
    update();
    emit newGeometry(origwidth,origheight,topLeft.x(),topLeft.y(),width,height,zoom);
}


void QVImageArea::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0) {
        centerZoom(2*zoom);
    } else {
        centerZoom(zoom/2);
    }
}

// Auxiliary function to draw 'intuitive' rectangles that draw themselves at the
// borders:
QRectF QVImageArea::intuitiveRect(QRect rect)
{
        /*return QRectF(rect.x(),rect.y()+1.0/zoom,
                                  rect.width()-1.0/zoom,rect.height()-1.0/zoom);*/
    return QRectF(rect.x(),rect.y(),rect.width()-1.0/zoom,rect.height()-1.0/zoom);
}


QRect QVImageArea::innerRect()
{
    QPoint q1(static_cast<int>(ceilf(static_cast<float>(topLeft.x())/zoom)),
                static_cast<int>(ceilf(static_cast<float>(topLeft.y())/zoom))),
            q2(static_cast<int>(floor(static_cast<float>((topLeft.x()+width()))/zoom)-1),
                (static_cast<int>(floor(static_cast<float>(topLeft.y()+height()))/zoom))-1);
    return QRect(q1,q2);
}

QRect QVImageArea::outerRect()
{
    QPoint q1(static_cast<int>(ceilf(static_cast<float>(topLeft.x())/zoom)-1),
                static_cast<int>(ceilf(static_cast<float>(topLeft.y())/zoom))-1),
           q2(static_cast<int>(floor(static_cast<float>((topLeft.x()+width()))/zoom)),
                (static_cast<int>(floor(static_cast<float>(topLeft.y()+height()))/zoom)));

    return QRect(q1,q2) & QRect(0,0,origwidth,origheight);
}

void QVImageArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    painter = new QVPainter(this);

    painter->begin(this);
    //painter->setRenderHint(QPainter::TextAntialiasing);

    painter->setViewport(0,0,width(),height());
    painter->resetMatrix();
    painter->translate(-topLeft);
    painter->scale(zoom,zoom);

    // Now we call the user painting function:
    QVCanvas *image_viewer = qobject_cast<QVCanvas *>(parent());
    if(image_viewer == 0) {
        qFatal("Internal error: parent of QVImageArea must be a QVCanvas.");
    } else {
        glClearColor(0,0,1,0);
        glClear(GL_COLOR_BUFFER_BIT); // Blue background
        image_viewer->viewer();
    }

    // Now, we render the selection (red) and zoom (blue) rectangles, and selected points/polyline (green):
    if(drawSel) {
        if(selRect != QRect()) {
            painter->setPen(QColor(Qt::red));
            // Dirty trick for more intuitive behavior of rectangle in the borders
            // of the window:
            painter->drawRect(intuitiveRect(selRect));
        }
        if(zoomRect != QRect()) {
            painter->setPen(QColor(Qt::blue));
            // Dirty trick for more intuitive behavior of rectangle in the borders
            // of the window:
            painter->drawRect(intuitiveRect(zoomRect));
        }
        if(selPoly != QVPolyline()) {
            painter->setPen(QColor(Qt::green));
            QPointF pointoffset = (zoom==1?QPointF(0.0,0.0):QPointF(+0.5,+0.5));
            for (int i = selPoly.size()-1; i>=0; i--){
                painter->drawLine(selPoly.at(i)+QPointF(-2.0,+0.0) + pointoffset,
                          selPoly.at(i)+QPointF(+2.0,+0.0) + pointoffset);
                painter->drawLine(selPoly.at(i)+QPointF(+0.0,-2.0) + pointoffset,
                          selPoly.at(i)+QPointF(+0.0,+2.0) + pointoffset);
                if( (polyMode == LINE or polyMode == CLOSED) and (i!=0) )
                painter->drawLine(selPoly.at(i-1) + pointoffset,selPoly.at(i) + pointoffset);
            }
            if (polyMode == CLOSED)
                painter->drawLine(selPoly.at(0) + pointoffset, selPoly.at(selPoly.size() -1) + pointoffset);
        }
    }
    // Finally, if zoom is big enough, draw numbers with pixel values:
    if(zoom >= 32) {
        painter->setPen(QColor(Qt::green));
        QRect outer = outerRect();
        for(int j=outer.y();j<outer.y()+outer.height();j++) {
            for(int i=outer.x();i<outer.x()+outer.width();i++) {
                if(not imageList.isEmpty()) {
                    QString value_string;
                    int k;
                    for(k=0;k<imageList.size();k++) {
                        QRect img_rect = QRect(imageList[k]->getAnchor()+imageList[k]->getROI().topLeft(),
                              QSize(imageList[k]->getROI().width(),imageList[k]->getROI().height()));
                        if(i>=img_rect.left() and i<=img_rect.right() and j>=img_rect.top() and j<=img_rect.bottom()) {
                            //value_string = QString("-%1-").arg(k);
                            ///@todo Parece ser que en este punto los valores de los píxeles llegan truncados, por ejemplo no consigo que al hacer zoom se muestren valores decimales para las imagenes sFloat. Buscar motivo.
                            if(imageList[k]->isCompatibleWith("QVImage<uChar,1>")) {
                                if(zoom >= 32) {
                                    value_string =  QString("%1").arg((*(QVImage<uChar,1>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y()));
                                }
                            }
                            else if(imageList[k]->isCompatibleWith("QVImage<uShort,1>")) {
                                if(zoom >= 64) {
                                    value_string =  QString("%1").arg((*(QVImage<uShort,1>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y()));
                                }
                            }
                            else if(imageList[k]->isCompatibleWith("QVImage<sShort,1>")) {
                                if(zoom >= 64) {
                                    value_string =  QString("%1").arg((*(QVImage<sShort,1>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y()));
                                }
                            }
                            else if(imageList[k]->isCompatibleWith("QVImage<sInt,1>")) {
                                if(zoom >= 64) {
                                    value_string =  QString("%1").arg((*(QVImage<sInt,1>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y()));
                                }
                            }
                            else if(imageList[k]->isCompatibleWith("QVImage<sFloat,1>")) {
                                if(zoom >= 64) {
                                    value_string =  QString("%1").arg((*(QVImage<sFloat,1>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y()));
                                }
                            }
                            else if(imageList[k]->isCompatibleWith("QVImage<uChar,3>")) {
                                int red,green,blue;
                                if(zoom >= 64) {
                                    red = (*(QVImage<uChar,3>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y(),0);
                                    green = (*(QVImage<uChar,3>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y(),1);
                                    blue = (*(QVImage<uChar,3>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y(),2);
                                    value_string =  QString("R:%1\nG:%2\nB:%3").arg(red).arg(green).arg(blue);
                                }
                            }
                            else if(imageList[k]->isCompatibleWith("QVImage<uShort,3>")) {
                                int red,green,blue;
                                if(zoom >= 64) {
                                    red = (*(QVImage<uShort,3>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y(),0);
                                    green = (*(QVImage<uShort,3>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y(),1);
                                    blue = (*(QVImage<uShort,3>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y(),2);
                                    value_string =  QString("R:%1\nG:%2\nB:%3").arg(red).arg(green).arg(blue);
                                }
                            }
                            else if(imageList[k]->isCompatibleWith("QVImage<sShort,3>")) {
                                int red,green,blue;
                                if(zoom >= 64) {
                                    red = (*(QVImage<sShort,3>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y(),0);
                                    green = (*(QVImage<sShort,3>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y(),1);
                                    blue = (*(QVImage<sShort,3>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y(),2);
                                    value_string =  QString("R:%1\nG:%2\nB:%3").arg(red).arg(green).arg(blue);
                                }
                            }
                            else if(imageList[k]->isCompatibleWith("QVImage<sInt,3>")) {
                                int red,green,blue;
                                if(zoom >= 64) {
                                    red = (*(QVImage<sInt,3>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y(),0);
                                    green = (*(QVImage<sInt,3>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y(),1);
                                    blue = (*(QVImage<sInt,3>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y(),2);
                                    value_string =  QString("R:%1\nG:%2\nB:%3").arg(red).arg(green).arg(blue);
                                }
                            }
                            else if(imageList[k]->isCompatibleWith("QVImage<sFloat,3>")) {
                                float red,green,blue;
                                if(zoom >= 64) {
                                    red = (*(QVImage<sFloat,3>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y(),0);
                                    green = (*(QVImage<sFloat,3>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y(),1);
                                    blue = (*(QVImage<sFloat,3>*)imageList[k])(i-img_rect.topLeft().x()+imageList[k]->getROI().topLeft().x(),j-img_rect.topLeft().y()+imageList[k]->getROI().topLeft().y(),2);
                                    value_string =  QString("R:%1\nG:%2\nB:%3").arg(red).arg(green).arg(blue);
                                }
                            }
                            else {
                                // alternate code for that type of image ...
                                qFatal("Type of QVGenericImage still not supported in paintEvent");
                            }
                            break;
                        }
                    }
                    if(k==imageList.size()) {
                        value_string = QString("X");
                    }

                    /* Alternative 1 (renderText):
                    renderText((i*zoom-topLeft.x()), ((j+1)*zoom-topLeft.y()),
                               value_string);*/

                    /* Alternative 2 (drawText with painter manipulation):*/
                    /*painter->resetMatrix();
                    painter->translate(-topLeft);
                    painter->drawText(
                        QRect(zoom*QPoint(i,j),zoom*QPoint(i+1,j+1)),
                                  Qt::AlignCenter|Qt::TextDontClip,value_string);
                    painter->scale(zoom,zoom);*/

                    /* Alternative 3 (drawTextUnscaled, with QRectF):*/
                    /*painter->drawTextUnscaled(
                        QRectF(QPointF(i,j),QSize(1,1)),
                              Qt::AlignCenter|Qt::TextDontClip,value_string);*/

                    /* Alternative 4 (drawTextUnscaled, with QRect): */
                    // OJO, (!) error de QT (poco importante) en construcción de
                    // rectangulos del tipo QRect(QPoint(x,y),QPoint(x+1,y+1)).
                    painter->drawTextUnscaled(
                        QRect(QPoint(i,j),QSize(1,1)),
                              Qt::AlignCenter|Qt::TextDontClip,value_string);
                }
            }
        }
    }

    // End of painting:
    painter->end();
    delete painter;

    //imageList.clear();
    while (!imageList.isEmpty())
         delete imageList.takeFirst();
}

void QVImageArea::resizeImageArea(int w,int h)
{
    if(w != origwidth or h != origheight) {
        zoom = 1;
        origwidth = w;
        origheight = h;
        topLeft = QPoint(0,0);
        selRect = QRect();
        zoomRect = QRect();
        selPoly = QVPolyline();
        setMinimumSize(qMin(w,max_zoom),qMin(h,max_zoom));
        setMaximumSize(w,h);
        resize(w,h);
        emit newGeometry(origwidth,origheight,topLeft.x(),topLeft.y(),width(),height(),zoom);
    }
}

void QVImageArea::drawQVImage(QVGenericImage *image,bool adaptSize,float low, float high)
{

    QVGenericImage *imagecopy=NULL;
    if(image->isCompatibleWith("QVImage<uChar,1>")) {
        imagecopy = new QVImage<uChar,1>;
        *(dynamic_cast<QVImage<uChar,1>*>(imagecopy)) = *(dynamic_cast<QVImage<uChar,1>*>(image));
    }
    else if(image->isCompatibleWith("QVImage<uShort,1>")) {
        imagecopy = new QVImage<uShort,1>;
        *(dynamic_cast<QVImage<uShort,1>*>(imagecopy)) = *(dynamic_cast<QVImage<uShort,1>*>(image));
    }
    else if(image->isCompatibleWith("QVImage<sShort,1>")) {
        imagecopy = new QVImage<sShort,1>;
        *(dynamic_cast<QVImage<sShort,1>*>(imagecopy)) = *(dynamic_cast<QVImage<sShort,1>*>(image));
    }
    else if(image->isCompatibleWith("QVImage<sInt,1>")) {
        imagecopy = new QVImage<sInt,1>;
        *(dynamic_cast<QVImage<sInt,1>*>(imagecopy)) = *(dynamic_cast<QVImage<sInt,1>*>(image));
    }
    else if(image->isCompatibleWith("QVImage<sFloat,1>")) {
        imagecopy = new QVImage<sFloat,1>;
        *(dynamic_cast<QVImage<sFloat,1>*>(imagecopy)) = *(dynamic_cast<QVImage<sFloat,1>*>(image));
    }
    else if(image->isCompatibleWith("QVImage<uChar,3>")) {
        imagecopy = new QVImage<uChar,3>;
        *(dynamic_cast<QVImage<uChar,3>*>(imagecopy)) = *(dynamic_cast<QVImage<uChar,3>*>(image));
    }
    else if(image->isCompatibleWith("QVImage<uShort,3>")) {
        imagecopy = new QVImage<uShort,3>;
        *(dynamic_cast<QVImage<uShort,3>*>(imagecopy)) = *(dynamic_cast<QVImage<uShort,3>*>(image));
    }
    else if(image->isCompatibleWith("QVImage<sShort,3>")) {
                imagecopy = new QVImage<sShort,3>;
        *(dynamic_cast<QVImage<sShort,3>*>(imagecopy)) = *(dynamic_cast<QVImage<sShort,3>*>(image));
    }
    else if(image->isCompatibleWith("QVImage<sInt,3>")) {
        imagecopy = new QVImage<sInt,3>;
        *(dynamic_cast<QVImage<sInt,3>*>(imagecopy)) = *(dynamic_cast<QVImage<sInt,3>*>(image));
    }
    else if(image->isCompatibleWith("QVImage<sFloat,3>")) {
        imagecopy = new QVImage<sFloat,3>;
        *(dynamic_cast<QVImage<sFloat,3>*>(imagecopy)) = *(dynamic_cast<QVImage<sFloat,3>*>(image));
    }
    else {
        // alternate code for that type of image ...
        qFatal("Type of QVGenericImage still not supported in drawQVImage");
    }

    // Image to the top of the stack (front of the list)
    imageList.push_front(imagecopy);


    ///@todo Actualmente el imagecanvas reescala la imagearea que muestra al ROI. Eso tiene el problema de que no se puede cambiar la posición del ROI una vez mostrado (solo se pueden seleccionar ROIs contenidos en el último ROI seleccionado), además si el ROI se sale de la imagen que se va a formar solo conteniendolo a él da problemas, esto puede solucionarse haciendo que el imagecanvas o el propio programador reseten el ROI. Otra opción es que el imagecanvas no se reescale al ROI, y otra es poder indicarle al imagecanvas que se comporte de una forma u otra.
    if(adaptSize) {
        this->resizeImageArea(image->getAnchor().x()+image->getROI().x()+image->getROI().width(),image->getAnchor().y()+image->getROI().y()+image->getROI().height());
    }

    // Push the current OpenGL projection and model-view matrices onto their
    // respective stacks:
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushClientAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // Set the correct viewport and perspective and model transformation
    // for native OpenGL calls:
    glViewport(0,0,width(),height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(topLeft.x(),topLeft.x()+width(),
            topLeft.y()+height(),topLeft.y(),-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Intersection of current window viewport and image rectangles:
    QRect final_rect,outer_rect = outerRect(),
          img_rect = QRect(imagecopy->getAnchor()+imagecopy->getROI().topLeft(),
                          QSize(imagecopy->getROI().width(),imagecopy->getROI().height()));
    final_rect = outer_rect & img_rect;

    // Now, render the image using OpenGL calls:

    // First, WHERE to draw...
    QPoint where,dirty; // Dirty trick for offset (bitmap trick).
    if(outer_rect.topLeft().x() >= img_rect.topLeft().x()) {
        where.setX(outer_rect.topLeft().x());
        dirty.setX(1);
    } else {
        where.setX(img_rect.topLeft().x());
        dirty.setX(0);
    }
    if(outer_rect.topLeft().y() >= img_rect.topLeft().y()) {
        where.setY(outer_rect.topLeft().y());
        dirty.setY(1);
    } else {
        where.setY(img_rect.topLeft().y());
        dirty.setY(0);
    }
    // Now the dirty trick for offset, using glBitmap:
    glRasterPos2f(zoom*(where.x()+dirty.x()+0.0001),zoom*(where.y()+dirty.y()+0.0001));
    glBitmap(0, 0, 0, 0, -zoom*dirty.x(), +zoom*dirty.y(), NULL);

    // ... and second, WHAT to draw:
    QRect what;
    int img_step = imagecopy->getStep();
    glPixelZoom(zoom,-zoom);
    if(outer_rect.topLeft().x() >= img_rect.topLeft().x()) {
        what.setX(outer_rect.topLeft().x() - img_rect.topLeft().x() + imagecopy->getROI().topLeft().x());
    } else {
        what.setX(imagecopy->getROI().topLeft().x());
    }
    what.setWidth(final_rect.width());
    if(outer_rect.topLeft().y() >= img_rect.topLeft().y()) {
        what.setY(outer_rect.topLeft().y() - img_rect.topLeft().y() + imagecopy->getROI().topLeft().y());
    } else {
        what.setY(imagecopy->getROI().topLeft().y());
    }
    what.setHeight(final_rect.height());

    if(image->isCompatibleWith("QVImage<uChar,1>")) {
        glPixelStorei(GL_UNPACK_ROW_LENGTH,img_step);
        glDrawPixels(what.width(),what.height(),
                     GL_LUMINANCE,GL_UNSIGNED_BYTE,
                     static_cast<QVImage<uchar,1> *>(imagecopy)->getReadData() +
                     what.y()*img_step+what.x());
    }
    else if(image->isCompatibleWith("QVImage<uShort,1>")) {
        glPixelStorei(GL_UNPACK_ROW_LENGTH,img_step/sizeof(uShort));
        glDrawPixels(what.width(),what.height(),
                     GL_LUMINANCE,GL_UNSIGNED_SHORT,
                     static_cast<QVImage<uShort,1> *>(imagecopy)->getReadData() +
                     what.y()*img_step/sizeof(uShort)+what.x());
    }
    else if(image->isCompatibleWith("QVImage<sShort,1>")) {
        glPixelStorei(GL_UNPACK_ROW_LENGTH,img_step/sizeof(sShort));

        float scale=1.0/(high-low),bias=-low*scale;
        glPixelTransferf(GL_RED_BIAS,bias);
        glPixelTransferf(GL_GREEN_BIAS,bias);
        glPixelTransferf(GL_BLUE_BIAS,bias);
        glPixelTransferf(GL_RED_SCALE,scale);
        glPixelTransferf(GL_GREEN_SCALE,scale);
        glPixelTransferf(GL_BLUE_SCALE,scale);

        glDrawPixels(what.width(),what.height(),
                     GL_LUMINANCE,GL_SHORT,
                     static_cast<QVImage<sShort,1> *>(imagecopy)->getReadData() +
                     what.y()*img_step/sizeof(sShort)+what.x());
    }
    else if(image->isCompatibleWith("QVImage<sInt,1>")) {
        glPixelStorei(GL_UNPACK_ROW_LENGTH,img_step/sizeof(sInt));

        float scale=1.0/(high-low),bias=-low*scale;
        glPixelTransferf(GL_RED_BIAS,bias);
        glPixelTransferf(GL_GREEN_BIAS,bias);
        glPixelTransferf(GL_BLUE_BIAS,bias);
        glPixelTransferf(GL_RED_SCALE,scale);
        glPixelTransferf(GL_GREEN_SCALE,scale);
        glPixelTransferf(GL_BLUE_SCALE,scale);

        glDrawPixels(what.width(),what.height(),
                     GL_LUMINANCE,GL_INT,
                     static_cast<QVImage<sInt,1> *>(imagecopy)->getReadData() +
                     what.y()*img_step/sizeof(sInt)+what.x());
    }
    else if(image->isCompatibleWith("QVImage<sFloat,1>")) {
        glPixelStorei(GL_UNPACK_ROW_LENGTH,img_step/sizeof(sFloat));

        float scale=1.0/(high-low),bias=-low*scale;
        //float scale = 1.0/ (high-low),bias=0;
        glPixelTransferf(GL_RED_BIAS,bias);
        glPixelTransferf(GL_GREEN_BIAS,bias);
        glPixelTransferf(GL_BLUE_BIAS,bias);
        glPixelTransferf(GL_RED_SCALE,scale);
        glPixelTransferf(GL_GREEN_SCALE,scale);
        glPixelTransferf(GL_BLUE_SCALE,scale);

/*		glPixelTransferf(GL_RED_SCALE,float(1.0)/(float)127.0);
        glPixelTransferf(GL_GREEN_SCALE,float(1.0)/(float)127.0);
        glPixelTransferf(GL_BLUE_SCALE,float(1.0)/(float)127.0);*/
        // Take care with last parameter (pointer) in this call: it works
        // because of the float* arithmetic:
        glDrawPixels(what.width(),what.height(),
                     GL_LUMINANCE,GL_FLOAT,
                     static_cast<QVImage<sFloat,1> *>(imagecopy)->getReadData() +
                     what.y()*img_step/sizeof(sFloat)+what.x());
    }
    else if(image->isCompatibleWith("QVImage<uChar,3>")) {
        glPixelStorei(GL_UNPACK_ROW_LENGTH,img_step/3);
        glDrawPixels(what.width(),what.height(),
                    GL_RGB,GL_UNSIGNED_BYTE,
                    static_cast<QVImage<uchar,3> *>(imagecopy)->getReadData() +
                    what.y()*img_step+3*what.x());
    }
    else if(image->isCompatibleWith("QVImage<uShort,3>")) {
        glPixelStorei(GL_UNPACK_ROW_LENGTH,img_step/(sizeof(uShort)*3));
        glDrawPixels(what.width(),what.height(),
                    GL_RGB,GL_UNSIGNED_SHORT,
                    static_cast<QVImage<uShort,3> *>(imagecopy)->getReadData() +
                    what.y()*img_step/sizeof(uShort)+3*what.x());
    }
    else if(image->isCompatibleWith("QVImage<sShort,3>")) {
        glPixelStorei(GL_UNPACK_ROW_LENGTH,img_step/(sizeof(sShort)*3));

        float scale=1.0/(high-low),bias=-low*scale;
        glPixelTransferf(GL_RED_BIAS,bias);
        glPixelTransferf(GL_GREEN_BIAS,bias);
        glPixelTransferf(GL_BLUE_BIAS,bias);
        glPixelTransferf(GL_RED_SCALE,scale);
        glPixelTransferf(GL_GREEN_SCALE,scale);
        glPixelTransferf(GL_BLUE_SCALE,scale);

        glDrawPixels(what.width(),what.height(),
                    GL_RGB,GL_SHORT,
                    static_cast<QVImage<sShort,3> *>(imagecopy)->getReadData() +
                    what.y()*img_step/sizeof(sShort)+3*what.x());
    }
    else if(image->isCompatibleWith("QVImage<sInt,3>")) {
        glPixelStorei(GL_UNPACK_ROW_LENGTH,img_step/(sizeof(sInt)*3));

        float scale=1.0/(high-low),bias=-low*scale;
        glPixelTransferf(GL_RED_BIAS,bias);
        glPixelTransferf(GL_GREEN_BIAS,bias);
        glPixelTransferf(GL_BLUE_BIAS,bias);
        glPixelTransferf(GL_RED_SCALE,scale);
        glPixelTransferf(GL_GREEN_SCALE,scale);
        glPixelTransferf(GL_BLUE_SCALE,scale);

        glDrawPixels(what.width(),what.height(),
                     GL_RGB,GL_INT,
                     static_cast<QVImage<sInt,3> *>(imagecopy)->getReadData() +
                     what.y()*img_step/sizeof(sInt)+3*what.x());
    }
    else if(image->isCompatibleWith("QVImage<sFloat,3>")) {
        glPixelStorei(GL_UNPACK_ROW_LENGTH,img_step/(sizeof(sFloat)*3));

        float scale=1.0/(high-low),bias=-low*scale;
        glPixelTransferf(GL_RED_BIAS,bias);
        glPixelTransferf(GL_GREEN_BIAS,bias);
        glPixelTransferf(GL_BLUE_BIAS,bias);
        glPixelTransferf(GL_RED_SCALE,scale);
        glPixelTransferf(GL_GREEN_SCALE,scale);
        glPixelTransferf(GL_BLUE_SCALE,scale);

        glDrawPixels(what.width(),what.height(),
                     GL_RGB,GL_FLOAT,
                     static_cast<QVImage<sFloat,3> *>(imagecopy)->getReadData() +
                     what.y()*img_step/sizeof(sFloat)+3*what.x());
    }
    else {
        // alternate code for that type of image ...
        qFatal("Type of QVGenericImage still not supported in drawQVImage");
    }

    // Pop the OpenGL projection and modelview matrices off their respective
    // stacks. Pop the OpenGL attributes off the attribute stack.
    glPopClientAttrib();
    glPopAttrib();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}


// Camera coordinate system: X grows to the right, Y grows downwards, Z grows towards scene.
// This way, coordinate system is right handed (X x Y = Z), Z corresponds to depth, and
// pixel coordinates grow following the conventions of traditional windows systems.
void QVImageArea::beginDrawWorldFromCamera(const double fx, const double fy, const QVCameraPose &cameraPosition)
{
    // Prepare QT widget for native OpenGL calls:
#ifdef QT_MIN_VERSION_4_6
    painter->beginNativePainting();
#else
    std::cerr << "[QVImageArea::beginDrawWorldFromCamera] Qt version >= 4.6 is required for augmented reality functionality" << std::endl;
#endif

    // Save current projection and model matrices:
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // Get current window zoom, top left position, width and height of viewport, field of view
    // angle corresponding to focal, and convert all the values to float:
    //float w_p = getSize().width(),h_p = getSize().height();
    //float zoom = getZoom();
    float w_p = origwidth,h_p = origheight, zm = zoom;
    float x = static_cast<float>(topLeft.x())/zm,y = static_cast<float>(topLeft.y())/zm;
    float w = width(), h = height();
    float fov = 2*atan2((float)h_p/2,(float)fy)*180/PI;
    float asp_rat = w_p/h_p;

    // First, adjust projection matrix:
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glTranslatef((w_p-w)/w,-(h_p-h)/h,0);
    glScalef(zm,zm,1);
    glScalef(w_p/w,h_p/h,1);
    glTranslatef(-(x-(w_p/2-(w_p/2)/zm))/(w_p/2),(y-(h_p/2-(h_p/2)/zm))/(h_p/2),0);
    qvGluPerspective(fov,asp_rat*fy/fx,0.1,15.0);

    // Now, get R, C and T from camera position, and put R in axis/angle form:
    QV3DPointF C = cameraPosition.getCenter();
    QVMatrix R = cameraPosition.getOrientation().toRotationMatrix();
    QV3DPointF T = -R * C;
    QV3DPointF rotVect = lnSO3(R);
    float angle = rotVect.norm2();
    QV3DPointF axis = rotVect/angle;

    //Finally, adjust model matrix accordingly:
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(T.x(),-T.y(),-T.z());
    glRotatef(angle*180/PI,axis.x(),-axis.y(),-axis.z());
    glScalef(1,-1,-1);
}


void QVImageArea::endDrawWorldFromCamera(void)
{
    // Recover old projection and model matrices:
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // And notice QT widget that native OpenGL calls have finished:
#ifdef QT_MIN_VERSION_4_6
    painter->endNativePainting();
#else
    std::cerr << "[QVImageArea::endDrawWorldFromCamera] Qt version >= 4.6 is required for augmented reality functionality" << std::endl;
#endif
}

void QVImageArea::mousePressEvent(QMouseEvent *event)
{
    firstPos = event->pos();
    dragging = TRUE;
    if(mouseMode == DRAG) {
        setCursor(Qt::ClosedHandCursor);
    }

    if ( (mouseMode == SEL) && (event->button() == Qt::RightButton) ) {
        selRect = QRect();
        emit rectSelected(QRect());
    }

    // add a new point to the polyline
    if (mouseMode == POLY) {
        if (event->button() == Qt::RightButton) {
            selPoly = QVPolyline();
            emit polySelected(QPoint(), true, polyMode);
        } else {
            QPoint pos = event->pos();
            QPoint point(qRound(-0.5+static_cast<float>(pos.x()+topLeft.x())/zoom), qRound(-0.5+static_cast<float>(pos.y()+topLeft.y())/zoom));
            selPoly.append(point);
            emit polySelected(point, false, polyMode);
        }
    }
    makeCurrent();
    update();
}

void QVImageArea::mouseMoveEvent(QMouseEvent *event)
{
    if(dragging) {
        lastPos = event->pos();
        switch(mouseMode) {
        case DRAG: {
            QPoint minDesp = -topLeft,
                maxDesp = QPoint(origwidth*zoom,origheight*zoom) -
                            (topLeft + QPoint(width(),height()));
            QPoint desp = firstPos-lastPos,
                boundDesp = QPoint(qBound(minDesp.x(),desp.x(),maxDesp.x()),
                                    qBound(minDesp.y(),desp.y(),maxDesp.y()));
            if(boundDesp != QPoint(0,0)) {
                topLeft = topLeft+boundDesp;
                makeCurrent();
                update();
                emit newGeometry(origwidth,origheight,topLeft.x(),topLeft.y(),width(),height(),zoom);
            }
            firstPos = lastPos;
            emit mouseLeavesImageArea(FALSE);
            emit newMousePosition(static_cast<float>(event->x()+topLeft.x())/zoom,static_cast<float>(event->y()+topLeft.y())/zoom);
            break;
            }
        case ZOOM: {
            QPoint p1(qRound(static_cast<float>(firstPos.x()+topLeft.x())/zoom),
                    qRound(static_cast<float>(firstPos.y()+topLeft.y())/zoom)),
                p2(qRound(static_cast<float>(lastPos.x()+topLeft.x())/zoom)-1,
                    qRound(static_cast<float>(lastPos.y()+topLeft.y())/zoom)-1);

            // Warning: QT (lesser) error when constructing rectangles of type QRect(QPoint(x,y),QPoint(x-1,y')),
            // as well QRect(QPoint(x,y),QPoint(x',y-1)). In practice, it is not important, so we won't
            // blur the code.
            zoomRect = QRect(p1,p2) & innerRect(); // Intersection
            emit mouseLeavesImageArea(FALSE);
            emit newMousePosition(lastPos.x()>firstPos.x()?zoomRect.right():zoomRect.left(), lastPos.y()>firstPos.y()?zoomRect.bottom():zoomRect.top());
            makeCurrent();
            update();
            break;
            }
        case SEL: {
            QPoint p1(qRound(static_cast<float>(firstPos.x()+topLeft.x())/zoom),
                    qRound(static_cast<float>(firstPos.y()+topLeft.y())/zoom)),
                p2(qRound(static_cast<float>(lastPos.x()+topLeft.x())/zoom)-1,
                    qRound(static_cast<float>(lastPos.y()+topLeft.y())/zoom)-1);

            selRect = QRect(p1,p2) & innerRect(); // Intersection
            emit rectSelected(selRect);
            emit mouseLeavesImageArea(FALSE);
            emit newMousePosition(lastPos.x()>firstPos.x()?selRect.right():selRect.left(), lastPos.y()>firstPos.y()?selRect.bottom():selRect.top());
            makeCurrent();
            update();
            break;
            }
        case POLY: {
            break;
            }
        case NONE: {
            break;
            }
        }
    } else {
        emit mouseLeavesImageArea(FALSE);
        emit newMousePosition(static_cast<float>(event->x()+topLeft.x())/zoom,static_cast<float>(event->y()+topLeft.y())/zoom);
    }
}


void QVImageArea::mouseReleaseEvent(QMouseEvent *event)
{
    //Q_UNUSED(event);
    if(mouseMode == DRAG) {
        setCursor(Qt::OpenHandCursor);
    }
    dragging = FALSE;
    lastPos = event->pos();
    switch(mouseMode) {
      case DRAG: {
        break;
      }
      case ZOOM: {
        int newzoom = zoom;

        if (zoomRect.width() < 1 or zoomRect.height() < 1) // if the rect is too small, the newzoom must be too great
            newzoom = max_zoom + 1;
        else {
            do {
                if (newzoom < 2) newzoom++; // in order to grown always
                else newzoom = 2*newzoom;
            }
            while(newzoom*zoomRect.width() < minimumWidth() or newzoom*zoomRect.height() < minimumHeight());
        }

        if(newzoom <= max_zoom) {
            zoom = newzoom;
            topLeft = zoom*zoomRect.topLeft();
            setMaximumSize(zoom*origwidth,zoom*origheight);
            resize(zoom*zoomRect.width(),zoom*zoomRect.height());
            zoomRect = QRect();
            makeCurrent();
            update();
            emit newGeometry(origwidth,origheight,topLeft.x(),topLeft.y(),width(),height(),zoom);
        } else {
            zoomRect = QRect();
            makeCurrent();
            update();
        }
        break;
      }
      case SEL: {
        if(event->button() == Qt::RightButton) {
            selRect = QRect();
            emit rectSelected(QRect());
            makeCurrent();
            update();
        }
        break;
      }
      case POLY: {
        break;
      }
      case NONE: {
        break;
      }
    }
}

void QVImageArea::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    emit mouseLeavesImageArea(TRUE);
}


/******************************************************************************/

void QVCanvas::resizeEvent(QResizeEvent *event)
{
    QFontMetrics fm(font());

    int w = event->size().width() - scaleWidgetsFixedWidth - 1;
    int h = event->size().height() - scaleWidgetsFixedWidth - statusBarWidgetFixedHeight - 1;
    imageArea->setGeometry(scaleWidgetsFixedWidth,scaleWidgetsFixedWidth,w,h);
}

QString QVCanvas::statusMessage()
{
    if(mouseIsOut) {
        return QString("z=%1").arg(imageArea->zoom);
    } else {
        return QString("(%1,%2) z=%3").arg(mousePosX).arg(mousePosY).arg(imageArea->zoom);
    }
}

QVCanvas::QVCanvas(QWidget *parent) : QWidget(parent)
{
    mouseIsOut = TRUE;
    int w = 1, h = 1;
    // Scale widgets fixed width proportional to font height:
    QFontMetrics fm(font());
    scaleWidgetsFixedWidth = 5*fm.height()/3;

    #ifdef QVQWT
    // Scale widgets creation:
    scaleWidgetX = new QwtScaleWidget(QwtScaleDraw::TopScale,this);
    //scaleWidgetX->setLabelRotation(0.0);
    scaleWidgetX->setLabelAlignment(Qt::AlignHCenter|Qt::AlignTop);
    scaleWidgetX->setMargin(1);
    // Left and right (top & bottom) scaleWidgetsFixedWidth for scale widgets
    // (Otherwise, setBorderDist does not work!);
    //scaleWidgetX->setBorderDist(scaleWidgetsFixedWidth,0);
    scaleWidgetX->setBorderDist(scaleWidgetsFixedWidth,scaleWidgetsFixedWidth);

    scaleWidgetY = new QwtScaleWidget(QwtScaleDraw::LeftScale,this);
    scaleWidgetY->setLabelRotation(-90.0);
    scaleWidgetY->setLabelAlignment(Qt::AlignVCenter|Qt::AlignTop);
    scaleWidgetY->setMargin(1);
    // Left and right (top & bottom) scaleWidgetsFixedWidth for scale widgets
    // (Otherwise, setBorderDist does not work!);
    //scaleWidgetY->setBorderDist(scaleWidgetsFixedWidth,0);
    scaleWidgetY->setBorderDist(scaleWidgetsFixedWidth,scaleWidgetsFixedWidth);

    // Scale engines creation:
    scaleEngineX = new QwtLinearScaleEngine;
    scaleEngineY = new QwtLinearScaleEngine;
    #endif

    // QVImageArea creation: if there are others image areas, the new image area will share its contex with the first, in order not to slow down the application
    if(image_areas.isEmpty()) {
        // If first instance, create widget with brand new context:
        imageArea = new QVImageArea(w,h,this);
    }
    else {
        // For the rest of instances, create with the initial context: first (not deleted) imageArea's context
        imageArea = new QVImageArea(w,h,this,image_areas.first());
    }
    // appends its reference, in the image_areas list (in case it becomes the first image area, the new imageAreas can shared its context)
    image_areas.append(imageArea);

    statusBar = new QStatusBar(this);
    statusBar->addPermanentWidget(buttonDrawSel = new QToolButton(statusBar));
    statusBar->addPermanentWidget(buttonZoomIn = new QToolButton(statusBar));
    statusBar->addPermanentWidget(buttonZoomOut = new QToolButton(statusBar));
    statusBar->addPermanentWidget(buttonZoomOriginal = new QToolButton(statusBar));
    statusBar->addPermanentWidget(buttonZoomRect = new QToolButton(statusBar));
    statusBar->addPermanentWidget(buttonselPoly = new QToolButton(statusBar));
    statusBar->addPermanentWidget(buttonSelRect = new QToolButton(statusBar));
    statusBar->addPermanentWidget(buttonDrag = new QToolButton(statusBar));
    buttonDrawSel->setCheckable(TRUE);
    buttonDrawSel->setIcon(QIcon(":/images/drawsel.png"));
    buttonDrawSel->setChecked(TRUE);
    buttonZoomIn->setCheckable(FALSE);
    buttonZoomIn->setIcon(QIcon(":/images/zoom-in.png"));
    buttonZoomOut->setCheckable(FALSE);
    buttonZoomOut->setIcon(QIcon(":/images/zoom-out.png"));
    buttonZoomOriginal->setCheckable(FALSE);
    buttonZoomOriginal->setIcon(QIcon(":/images/zoom-original.png"));
    buttonZoomRect->setCheckable(TRUE);
    buttonZoomRect->setIcon(QIcon(":/images/zoom-best-fit.png"));
    buttonselPoly->setCheckable(TRUE);
    buttonselPoly->setIcon(QIcon(":/images/list.png"));
    menuselPoly = new QMenu();
    menuselPoly->addAction(QIcon(":/images/list.png"), "points", this, SLOT(selPolyChangedToList()));
    menuselPoly->addAction(QIcon(":/images/poly.png"), "polyline", this, SLOT(selPolyChangedToLine()));
    menuselPoly->addAction(QIcon(":/images/polyclosed.png"), "closed polyline", this, SLOT(selPolyChangedToClosed()));
    buttonselPoly->setMenu(menuselPoly);
    polyMode = LIST;
    buttonSelRect->setCheckable(TRUE);
    buttonSelRect->setIcon(QIcon(":/images/select.png"));
    buttonDrag->setCheckable(TRUE);
    buttonDrag->setIcon(QIcon(":/images/hand.png"));

    statusBar->showMessage(statusMessage());
    statusBarWidgetFixedHeight = statusBar->height();

    setMinimumSize(scaleWidgetsFixedWidth + imageArea->minimumWidth() + 1,
                   scaleWidgetsFixedWidth + imageArea->minimumHeight() + 1 +
                   statusBarWidgetFixedHeight);
    setMaximumSize(scaleWidgetsFixedWidth + w + 1,
                   scaleWidgetsFixedWidth + h + 1 +
                   statusBarWidgetFixedHeight);
    resize(scaleWidgetsFixedWidth + w + 1,
           scaleWidgetsFixedWidth + h + 1 +
           statusBarWidgetFixedHeight);
    connect(imageArea,SIGNAL(newGeometry(int,int,int,int,int,int,int)),
            this,SLOT(setGeometry(int,int,int,int,int,int,int)));
    connect(imageArea,SIGNAL(newMousePosition(float,float)),
            this,SLOT(newMousePositionSlot(float,float)));
    connect(imageArea,SIGNAL(mouseLeavesImageArea(bool)),
            this,SLOT(mouseLeavesImageAreaSlot(bool)));
    connect(imageArea, SIGNAL(rectSelected(QRect)),
            this, SLOT(rectSelectedSlot(QRect)));
    connect(imageArea, SIGNAL(polySelected(QPoint,bool,TPolyMode)),
            this, SLOT(polySelectedSlot(QPoint,bool,TPolyMode)));
    connect(buttonDrawSel,SIGNAL(clicked(bool)),this,SLOT(drawSelClicked(bool)));
    connect(buttonZoomRect,SIGNAL(clicked(bool)),this,SLOT(zoomRectClicked(bool)));
    connect(buttonselPoly,SIGNAL(clicked(bool)),this,SLOT(selPolyClicked(bool)));
    connect(buttonSelRect,SIGNAL(clicked(bool)),this,SLOT(selRectClicked(bool)));
    connect(buttonDrag,SIGNAL(clicked(bool)),this,SLOT(dragClicked(bool)));
    connect(buttonZoomIn,SIGNAL(clicked()),this,SLOT(zoomInClicked()));
    connect(buttonZoomOut,SIGNAL(clicked()),this,SLOT(zoomOutClicked()));
    connect(buttonZoomOriginal,SIGNAL(clicked()),this,SLOT(zoomOriginalClicked()));

}

void QVCanvas::drawSelClicked(bool checked) {
    imageArea->drawSel = checked;
    refreshImageArea();
}

void QVCanvas::zoomInClicked() {
    imageArea->centerZoom(2*imageArea->zoom);
}

void QVCanvas::zoomOutClicked() {
    imageArea->centerZoom(imageArea->zoom/2);
}

void QVCanvas::zoomOriginalClicked() {
    // (Tricky) force redraw at initial size:
    int w = imageArea->origwidth, h = imageArea->origheight;
    imageArea->origwidth = imageArea->origheight = 0;
    QRect saveSelRect = imageArea->selRect;
    QVPolyline saveSelPoly = imageArea->selPoly;
    imageArea->resizeImageArea(w,h);
    imageArea->selRect = saveSelRect;
    imageArea->selPoly = saveSelPoly;
    refreshImageArea();
}


void QVCanvas::zoomRectClicked(bool checked) {
    if(checked)
        imageArea->setCursor(Qt::CrossCursor);
    else
        imageArea->setCursor(Qt::ArrowCursor);
    imageArea->mouseMode = (checked ? QVImageArea::ZOOM : QVImageArea::NONE);
    buttonselPoly->setChecked(false);
    buttonSelRect->setChecked(false);
    buttonDrag->setChecked(false);
}

void QVCanvas::selPolyClicked(bool checked) {
    if(checked)
        imageArea->setCursor(Qt::CrossCursor);
    else
        imageArea->setCursor(Qt::ArrowCursor);

    if (checked) {
        imageArea->mouseMode = QVImageArea::POLY;
        imageArea->polyMode = polyMode;
    } else {
        imageArea->mouseMode = QVImageArea::NONE;
    }
    buttonZoomRect->setChecked(false);
    buttonSelRect->setChecked(false);
    buttonDrag->setChecked(false);
}

void QVCanvas::selPolyChangedToList() {
    polyMode = LIST;
    if(imageArea->polyMode != LIST) {
        imageArea->polyMode = polyMode;
        imageArea->selPoly = QVPolyline();
        polySelectedSlot(QPoint(), true, polyMode);
        refreshImageArea();
    }
    buttonselPoly->setIcon(QIcon(":/images/list.png"));
    selPolyClicked(true);
    buttonselPoly->setChecked(true);
}

void QVCanvas::selPolyChangedToLine() {
    polyMode = LINE;
    if(imageArea->polyMode != LINE) {
        imageArea->polyMode = polyMode;
        imageArea->selPoly = QVPolyline();
        polySelectedSlot(QPoint(), true, polyMode);
        refreshImageArea();
    }
    buttonselPoly->setIcon(QIcon(":/images/poly.png"));
    selPolyClicked(true);
    buttonselPoly->setChecked(true);
}

void QVCanvas::selPolyChangedToClosed() {
    polyMode = CLOSED;
    if(imageArea->polyMode != CLOSED) {
        imageArea->polyMode = polyMode;
        imageArea->selPoly = QVPolyline();
        polySelectedSlot(QPoint(), true, polyMode);
        refreshImageArea();
    }
    buttonselPoly->setIcon(QIcon(":/images/polyclosed.png"));
    selPolyClicked(true);
    buttonselPoly->setChecked(true);
}

void QVCanvas::selRectClicked(bool checked) {
    if(checked)
        imageArea->setCursor(Qt::CrossCursor);
    else
        imageArea->setCursor(Qt::ArrowCursor);
    imageArea->mouseMode = (checked ? QVImageArea::SEL : QVImageArea::NONE);
    buttonZoomRect->setChecked(false);
    buttonselPoly->setChecked(false);
    buttonDrag->setChecked(false);
    if (!checked) {
        imageArea->selRect = QRect();
        refreshImageArea();
        emit imageArea->rectSelected(QRect());
    }
}

void QVCanvas::dragClicked(bool checked) {
    if(checked)
        imageArea->setCursor(Qt::OpenHandCursor);
    else
        imageArea->setCursor(Qt::ArrowCursor);

    imageArea->mouseMode = (checked ? QVImageArea::DRAG : QVImageArea::NONE);
    buttonselPoly->setChecked(false);
    buttonSelRect->setChecked(false);
    buttonZoomRect->setChecked(false);
}


void QVCanvas::newMousePositionSlot(float x,float y) {
    mousePosX = x;
    mousePosY = y;
    statusBar->showMessage(statusMessage());
}

void QVCanvas::mouseLeavesImageAreaSlot(bool leaves) {
/*	if(leaves)
        std::cout << "SALGO-----------------------------" << std::endl;
    else
        std::cout << "ENTRO-----------------------------" << std::endl;*/
    mouseIsOut = leaves;
    statusBar->showMessage(statusMessage());
}


QVCanvas::~QVCanvas()
{
    #ifdef QVQWT
    delete scaleEngineX;
    delete scaleEngineY;
    #endif

    // It remove its reference of the image areas list
    image_areas.removeAll(imageArea);

    delete imageArea;
}

void QVCanvas::refreshImageArea()
{
    imageArea->makeCurrent();
    imageArea->update();
}


void QVCanvas::setGeometry(int origwidth,int origheight,int topleftx,int toplefty,int width,int height, int zoom)
{
    Q_UNUSED(origwidth);
    Q_UNUSED(origheight);

    QFontMetrics fm(font());

    // virtual QwtScaleDiv divideScale(double x1, double x2,
    //     int numMajorSteps, int numMinorSteps, double stepSize=0.0) const
    #ifdef QVQWT
    QwtScaleDiv scaleDivX = scaleEngineX->divideScale(
                    ((double)topleftx)/zoom,((double)(topleftx+width))/zoom,
                    qMin(width/zoom+1,static_cast<int>(width/(fm.width("999")))),
                    10,0);
    scaleWidgetX->setScaleDiv(scaleEngineX->transformation(),scaleDivX);

    QwtScaleDiv scaleDivY = scaleEngineY->divideScale(
                    ((double)toplefty+height)/zoom,((double)(toplefty))/zoom,
                    qMin(height/zoom+1,static_cast<int>(height/(fm.width("999")))),
                    10,0);
    scaleWidgetY->setScaleDiv(scaleEngineY->transformation(),scaleDivY);

    // Left and right (top & bottom) scaleWidgetsFixedWidth for scale widgets
    // (Otherwise, setBorderDist does not work!);

    scaleWidgetX->setGeometry(0,0,
        2*scaleWidgetsFixedWidth+width+1,scaleWidgetsFixedWidth);
    scaleWidgetY->setGeometry(0,0,
        scaleWidgetsFixedWidth,2*scaleWidgetsFixedWidth+height+1);
    #endif

    setMinimumSize(scaleWidgetsFixedWidth + imageArea->minimumWidth() + 1,
                   scaleWidgetsFixedWidth + imageArea->minimumHeight() + 1 +
                   statusBarWidgetFixedHeight);

    setMaximumSize(scaleWidgetsFixedWidth+zoom*imageArea->origwidth + 1 +1,
                   scaleWidgetsFixedWidth+zoom*imageArea->origheight + 1 +
                   statusBarWidgetFixedHeight + 1);

    resize(scaleWidgetsFixedWidth+width+1,
            scaleWidgetsFixedWidth+height+1+statusBarWidgetFixedHeight);

    statusBar->setGeometry(
        0,scaleWidgetsFixedWidth+height+1,
        scaleWidgetsFixedWidth+width+1,statusBarWidgetFixedHeight);

    statusBar->showMessage(statusMessage());
}
// #endif //DOXYGEN_IGNORE_THIS

