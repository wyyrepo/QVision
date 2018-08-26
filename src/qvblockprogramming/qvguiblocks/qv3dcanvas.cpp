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

#include <QMouseEvent>

//#include <qvipp.h>
#include <qvdefines.h>
#include <qvmatrixalgebra.h>

#include "qv3dcanvas.h"
#include <QTimer>

#include <GL/glu.h>

#define GL_VIEW_ASPECT   1.333

#ifndef DOXYGEN_IGNORE_THIS
QV3DCanvas::QV3DCanvas(	const QString &title, const double zoom, bool dr_center, const QColor &backgroundColor, QWidget* parent): QGLWidget(parent),
            trackballQuat(QVQuaternion::trackball(0.0, 0.0, 0.0, 0.0)),
            cx(0), cy(0), cz(0), ambientLightR(1.0), ambientLightG(1.0), ambientLightB(1.0),
            dr_center(dr_center), zoom(zoom), fov(45), pressedleft(FALSE), pressedright(FALSE), colorCursor(0), backgroundColor(backgroundColor)
    {
    setName(title);

    resize(400,(int)(400/GL_VIEW_ASPECT));
    setWindowTitle(title);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(1000/24);

    show();
    }

QV3DCanvas::~QV3DCanvas ()
    {
    // FIXME: is it needed?: makeCurrent();
    }

void QV3DCanvas::initializeGL()
    {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_DITHER);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);

    init();
    }

void QV3DCanvas::draw_center_of_rotation()
    {
    /* Yellow cross: (center of rotation). */
    glBegin(GL_LINES);
        glColor3ub(255,255,0);

        glVertex3f(cx - 0.1,cy,cz);
        glVertex3f(cx + 0.1,cy,cz);

        glVertex3f(cx,cy- 0.1,cz);
        glVertex3f(cx,cy+ 0.1,cz);

        glVertex3f(cx,cy,cz- 0.1);
        glVertex3f(cx,cy,cz+ 0.1);
    glEnd();
    }

#define S	15
void QV3DCanvas::paintGL()
    {
    // Loads identity matrix in the projection stack
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set up a perspective projection matrix
    qvGluPerspective(fov, (float)size().width()/(float)size().height(), 0.25, 100*zoom);

    // Loads identity matrix in the model view stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Setup background color.
    qglClearColor(backgroundColor);

    // Clear the scene to the background color.
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Enable lightning.
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);                // Set up sunlight.
    glEnable(GL_COLOR_MATERIAL);        // Configure glColor().

    // Setup ambient light.
    const GLfloat ambientLight[4] = {ambientLightR, ambientLightG, ambientLightB, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,  ambientLight);

    // Draw images objects
    foreach(QString name, getPropertyList())
        if (getPropertyFlags(name) & inputFlag)
            {
            // Draw <uChar,1> images
            if (isType< QVImage<uChar,1> >(name)) {
                QVImage<uChar, 1> imageAux = getPropertyValue<QVImage<uChar,1> >(name);
                drawQVImage(&imageAux);
                }
            // Draw <uChar,3> images
            else if (isType< QVImage<uChar,3> >(name)) {
                QVImage<uChar,3> imageAux = getPropertyValue<QVImage<uChar,3> >(name);
                drawQVImage(&imageAux);
                }
            // Draw <sFloat,1> images
            /*else if (isType< QVImage<sFloat,1> >(name)) {
                QVImage<sFloat,1> imageAux = getPropertyValue<QVImage<sFloat,1> >(name);
                drawQVImage(&imageAux, TRUE, _low, _high);
                }
            // Draw <sFloat,3> images
            else if (isType< QVImage<sFloat,3> >(name)) {
                QVImage<sFloat,3> imageAux = getPropertyValue<QVImage<sFloat,3> >(name);
                drawQVImage(&imageAux, TRUE, _low, _high);
                }
            ///@todo El código en qvcanvas para que se representen las imagenes uShort, sShort y sInt está incluido, pero como genera
            /// una imagen negra (cuyo motivo desconozco), he añadido aqui una conversión de esos tipos de imagen a uChar,
            /// para su visualización. Lo cual no es lo más correcto, ya que este tipo de conversiones trunca los valores
            /// que exceden del rango de uChar (no lo he dejado sobre sFloat porque parece relentizar el proceso). Depurar esto.
            // Draw <sShort,1> images
            else if (isType< QVImage<uShort,1> >(name)) {
                QVImage<uChar, 1> imageAux = getPropertyValue<QVImage<uShort,1> >(name);
                drawQVImage(&imageAux);
                }
            // Draw <sShort,3> images
            else if (isType< QVImage<uShort,3> >(name)) {
                QVImage<uChar, 3> imageAux = getPropertyValue<QVImage<uShort,3> >(name);
                drawQVImage(&imageAux);
                }
            // Draw <sShort,1> images
            else if (isType< QVImage<sShort,1> >(name)) {
                QVImage<uChar, 1> imageAux = getPropertyValue<QVImage<sShort,1> >(name);
                drawQVImage(&imageAux);
                }
            // Draw <sShort,3> images
            else if (isType< QVImage<sShort,3> >(name)) {
                QVImage<uChar, 3> imageAux = getPropertyValue<QVImage<sShort,3> >(name);
                drawQVImage(&imageAux);
                }
            // Draw <sInt,1> images
            else if (isType< QVImage<sInt,1> >(name)) {
                QVImage<uChar, 1> imageAux = getPropertyValue<QVImage<sInt,1> >(name);
                drawQVImage(&imageAux);
                }
            // Draw <sInt,3> images
            else if (isType< QVImage<sInt,3> >(name)) {
                QVImage<uChar, 3> imageAux = getPropertyValue<QVImage<sInt,3> >(name);
                drawQVImage(&imageAux);
                }*/
            }

    glTranslatef(0,0,-8*zoom);
    //const QVMatrix R = QVMatrix(trackballQuat);
    const QVMatrix R = (trackballQuat.toRotationMatrix() | QVVector(3,0.0)) & (QVVector(3,0.0) << 1);

    glMultMatrixd(R.getReadData());

        glTranslatef(-cx,-cy,-cz);

    display();

    viewer();

    if(dr_center)
        draw_center_of_rotation();


    glFlush();
    }

void QV3DCanvas::resizeGL( int w, int h )
    {
    glViewport(0,0,w,h);
    reshape(w,h);

    glScaled((GLdouble)0.5,(GLdouble)0.5,(GLdouble)0.5);

    viewer();

    glFlush();
    }

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////   Mouse & keyboard:     ///////////////////////
////////////////////////////////////////////////////////////////////////////////

void QV3DCanvas::mousePressEvent(QMouseEvent *event)
{
    beginx = event->x();
    beginy = event->y();
    if(event->button() == Qt::LeftButton) {
        pressedleft = TRUE;
    } else if(event->button() == Qt::RightButton) {
        pressedright = TRUE;
    }
}

void QV3DCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        pressedleft = FALSE;
    } else if(event->button() == Qt::RightButton) {
        pressedright = FALSE;
    }
}

void QV3DCanvas::mouseMoveEvent(QMouseEvent *event)
{
    int x,y;

    x = (int) event->x();
    y = (int) event->y();

    if (pressedleft) {
    QVQuaternion spinQuat = QVQuaternion::trackball(
            (2.0*beginx - size().width())	/ size().width(),
            (size().height() - 2.0*beginy)	/ size().height(),
            (2.0*x - size().width())	/ size().width(),
            (size().height() - 2.0*y)	/ size().height());

        trackballQuat = trackballQuat * spinQuat;
        updateGL();
    }
/*
    if (pressedright) {
        //printf("MouseMove right button\n");
        zoom += ((y - beginy) / size().height()) * 100;

        //if (zoom < 5) zoom = 5;
        //if (zoom > 120) zoom = 120;
        updateGL();
    }*/
    beginx = x;
    beginy = y;
}

void QV3DCanvas::wheelEvent(QWheelEvent *event)
    {
    zoom *= pow(0.9995,event->delta());
    updateGL();
    }

void QV3DCanvas::keyPressEvent(QKeyEvent *event)
{
    //printf("KeyPress\n");
    switch(event->key()) {
      case Qt::Key_Left:
        cx -= 0.1; // maxwide/20;
        break;
      case Qt::Key_Right:
        cx += 0.1; // maxwide/20;
        break;
      case Qt::Key_Up:
        cy += 0.1; // maxwide/20;
        break;
      case Qt::Key_Down:
        cy -= 0.1; // maxwide/20;
        break;
      case Qt::Key_PageUp:
        cz += 0.1; // maxwide/20;
        break;
      case Qt::Key_PageDown:
        cz -= 0.1; // maxwide/20;
        break;
      case 'C':
        dr_center = not dr_center;
        break;
      //case 'B':
        //dr_box = not dr_box;
        //break;
    }
    /* Something changed; redraw: */
    updateGL();
}

void QV3DCanvas::closeEvent(QCloseEvent * event)
{
    Q_UNUSED(event);
    emit closed();
}

//////////////////////////////////////////////
#include <iostream>
void QV3DCanvas::viewer()
    {
    qDebug() << "QVImageCanvas::viewer()";
    readInputProperties();

    // Draw other objects
    foreach(QString name, getPropertyList())
        if (getPropertyFlags(name) & inputFlag)
            {
            // Draw QV3DPolylineF
            if (isType< QV3DPolylineF >(name))
                draw(	getPropertyValue< QV3DPolylineF >(name),
                    getPropertyValue<QColor>("Color for " + name),
                    getPropertyValue<double>("Size for " + name));
            // Draw QList<QV3DPointF>
            else if (isType< QList<QV3DPointF> >(name))
                draw(	getPropertyValue< QList<QV3DPointF> >(name),
                    getPropertyValue<QColor>("Color for " + name),
                    getPropertyValue<double>("Size for " + name));
            // Draw QList<QV3DPolylineF>
            else if (isType< QList<QV3DPolylineF> >(name))
                foreach(QV3DPolylineF polyline, getPropertyValue< QList<QV3DPolylineF> >(name))
                    draw(	polyline,
                        getPropertyValue<QColor>("Color for " + name));
            }

    foreach(QV3DModel *model, models)
        model->updatePaint(*this);

    qDebug() << "QVImageCanvas::viewer() -> return";
    }

void QV3DCanvas::draw(const QV3DPolylineF &qv3DPolyline, const QColor color, const double size)
    {
    glPointSize(size);
    glBegin(GL_LINES);
    qglColor(color);
    for (int i = 1; i < qv3DPolyline.size(); i++)
        {
        glVertex3f(qv3DPolyline[i].x(), qv3DPolyline[i].y(), qv3DPolyline[i].z());
        glVertex3f(qv3DPolyline[i-1].x(), qv3DPolyline[i-1].y(), qv3DPolyline[i-1].z());
        }
    glEnd();
    }

void QV3DCanvas::draw(const QList<QV3DPointF> &qv3DPointList, const QColor color, const double size)
    {
                glBegin(GL_POINTS);
                qglColor(color);
                glPointSize(size);
                foreach(QV3DPointF point, qv3DPointList) {
                    //QV3DEllipsoid(color, size, size, size, point.x(), point.y(), point.z(), 10, 10).updatePaint(*this);
                    glVertex3f(point.x(), point.y(), point.z());
                }
                glEnd();
         }

bool QV3DCanvas::linkUnspecifiedInputProperty(QVPropertyContainer *sourceContainer, QString sourcePropName, LinkType linkType)
    {
    if (linkType == SynchronousLink)
        {
        std::cerr	<< "ERROR: QVImageCanvas::linkUnspecifiedInputProperty():"
                << " the linkType must be AsynchronousLink, the link will not be done"
                << std::endl;
        return false;
        }

    QVProcessingBlock* block;
    if((block = dynamic_cast<QVProcessingBlock*>(sourceContainer)) != NULL)
        {
        std::cout << "QV3DCanvas: Adding property '" << qPrintable(sourcePropName) << "'" << std::endl;
        addPropertyFromQVariant(sourcePropName, inputFlag, block->getPropertyQVariantValue(sourcePropName), block->getPropertyInfo(sourcePropName));
        if (	block->isType< QV3DPolylineF >(sourcePropName)		||
            block->isType< QList<QV3DPointF> >(sourcePropName)	||
            block->isType< QList<QV3DPolylineF> >(sourcePropName)		)
            {
            addProperty<QColor>("Color for " + sourcePropName, inputFlag, getNextColor(), QString("Color for object ") + sourcePropName);
            addProperty<double>("Size for " + sourcePropName, inputFlag, 1, QString("Size for object ") + sourcePropName);
            std::cout << "QV3DCanvas: Added property 'Color for " << qPrintable(sourcePropName) << "'" << std::endl;
            std::cout << "QV3DCanvas: Added property 'Size for " << qPrintable(sourcePropName) << "'" << std::endl;
            }
        bool result = block->linkProperty(sourcePropName, this, sourcePropName ,QVProcessingBlock::AsynchronousLink);
        //QObject::connect(block, SIGNAL(endIteration(uint, int)), this, SLOT(refreshImageArea()));
        return result;
        }
    else
        {
        std::cerr << "ERROR: QVImageCanvas::linkUnspecifiedInputProperty(): the sourceContainer container must be a QVProcessingBlock, the link will not be done" << std::endl;
        return false;
        }
    }

void QV3DCanvas::drawQVImage(QVGenericImage *image)
{

    QVGenericImage *imagecopy=NULL;
    if(image->isCompatibleWith("QVImage<uChar,1>")) {
        imagecopy = new QVImage<uChar,1>;
        *(dynamic_cast<QVImage<uChar,1>*>(imagecopy)) = *(dynamic_cast<QVImage<uChar,1>*>(image));
    }
    else if(image->isCompatibleWith("QVImage<uChar,3>")) {
        imagecopy = new QVImage<uChar,3>;
        *(dynamic_cast<QVImage<uChar,3>*>(imagecopy)) = *(dynamic_cast<QVImage<uChar,3>*>(image));
    }
    else {
        // alternate code for that type of image ...
        qFatal("Type of QVGenericImage still not supported in drawQVImage");
    }

    ///@todo Actualmente el imagecanvas reescala la imagearea que muestra al ROI. Eso tiene el problema de que no se puede cambiar la posición del ROI una vez mostrado (solo se pueden seleccionar ROIs contenidos en el último ROI seleccionado), además si el ROI se sale de la imagen que se va a formar solo conteniendolo a él da problemas, esto puede solucionarse haciendo que el imagecanvas o el propio programador reseten el ROI. Otra opción es que el imagecanvas no se reescale al ROI, y otra es poder indicarle al imagecanvas que se comporte de una forma u otra.
    const int	cols = image->getCols(),
            rows = image->getRows();

    setMinimumSize(cols,rows);
    setMaximumSize(cols,rows);
    resize(cols,rows);

    // Push the current OpenGL projection and modelview matrices onto their
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

    glOrtho(0, cols, rows,0,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Intersection of current window viewport and image rectangles:
    const QRect final_rect =  QRect(imagecopy->getAnchor()+imagecopy->getROI().topLeft(),
                          QSize(imagecopy->getROI().width(),imagecopy->getROI().height()));

    // Now, render the image using OpenGL calls:

        /* const double zoom = 1.0;*/

    // Now the dirty trick for offset, using glBitmap:
    glRasterPos2f(0.0 , 0.0);
    glBitmap(0, 0, 0.0, 0.0, 0.0, 0.0, NULL);
    glPixelZoom(1.0,-1.0);

    // ... and second, WHAT to draw:
    //QRect what(0,0,cols, rows);
    int img_step = imagecopy->getStep();

    /*what.setX(imagecopy->getROI().topLeft().x());
    what.setWidth(final_rect.width());
    what.setY(imagecopy->getROI().topLeft().y());
    what.setHeight(final_rect.height());*/

    //std::cout << "what = " << what.x() << ", " << what.y() << "\t" << what.width() << ", " << what.height() << std::endl;

    if(image->isCompatibleWith("QVImage<uChar,1>"))
        {
        glPixelStorei(GL_UNPACK_ROW_LENGTH, img_step);
        glDrawPixels(cols, rows, GL_LUMINANCE, GL_UNSIGNED_BYTE, static_cast<QVImage<uchar,1> *>(imagecopy)->getReadData());
        }
    else if(image->isCompatibleWith("QVImage<uChar,3>"))
        {
        glPixelStorei(GL_UNPACK_ROW_LENGTH, img_step/3);
        glDrawPixels(cols, rows, GL_RGB, GL_UNSIGNED_BYTE, static_cast<QVImage<uchar,3> *>(imagecopy)->getReadData());
        }
    else
        qFatal("Type of QVGenericImage still not supported in drawQVImage");

    // Pop the OpenGL projection and modelview matrices off their respective
    // stacks. Pop the OpenGL attributes off the attribute stack.
    glPopClientAttrib();
    glPopAttrib();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    }

void QV3DEllipsoid::paint(QV3DCanvas &glWidget)
    {
    glWidget.qglColor(color);
    //glWidget.qglColor(Qt::yellow);
    for(int i = 0; i <= lats; i++)
        {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0 = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(int j = 0; j <= longs; j++)
            {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(rx * x * zr0 + cx, ry * y * zr0 + cy, rz * z0 + cz);
            glVertex3f(rx * x * zr0 + cx, ry * y * zr0 + cy, rz * z0 + cz);
            glNormal3f(rx * x * zr1 + cx, ry * y * zr1 + cy, rz * z1 + cz);
            glVertex3f(rx * x * zr1 + cx, ry * y * zr1 + cy, rz * z1 + cz);
            }
        glEnd();
        }
    };


#endif

