/*
 *	Copyright (C) 2011, 2012. PARP Research Group.
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

/*!
@file canvasInteract.cpp
@ingroup ExamplePrograms
@brief Example application showing how to interact with a QVImageCanvas object.

This example lets the user to play with the ROI selector of the QVImageCanvas widget, marking the selected region in the output image with a dark square in the image canvas. It also allows the program to get a list of points from user input clicks. In both cases the user must select the adequate buttons from the bottom row of the QVImageCanvas widget. Finally, this example also shows how to perform custom drawings in a QVImageCanvas by subclassing it and reimplementing the QVImageCanvas ::custom_viewer() method.

@section Usage Usage of the program.
Once installed the QVision, compile using the <i>qmake</i> and <i>make</i> tools:
@code # qmake; make @endcode
Execute the application with the following line:
@code ./canvasInteract --URL=<source video identifier string> @endcode
For example:
@code ./canvasInteract --URL=http://perception.inf.um.es/public_data/videos/misc/minuto.avi @endcode
See section @ref QVMPlayerURLFormat for further info about the format and types of source video identifier strings.

@author PARP Research Group. University of Murcia, Spain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QDebug>

#include <QVApplication>
#include <QVVideoReaderBlock>
#include <QVDefaultGUI>
#include <QVImageCanvas>

#include <qvipp.h>

/// \cond

class MyImageCanvas : public QVImageCanvas {
    public:
        MyImageCanvas(QString name) : QVImageCanvas(name) {} ;
        void custom_viewer(){        
            QVPolyline poly = getPropertyValue<QVPolyline>("poly select");
            getQVPainter()->setPen(Qt::yellow);
            getQVPainter()->setBrush(QBrush(Qt::magenta, Qt::DiagCrossPattern));
            for(int i=0; i<poly.size(); i++) {
                getQVPainter()->drawEllipse(poly[i].x()-10, poly[i].y()-10, 20, 20);
                getQVPainter()->drawTextUnscaled(poly[i], QString("Point %1").arg(i));
            }
            getQVPainter()->setBrush(QBrush(Qt::magenta, Qt::NoBrush));
        }
};

class MyWorker: public QVProcessingBlock {
    public:
        MyWorker(QString name = QString()): QVProcessingBlock(name) {
            addProperty< QVImage<uChar,1> >("Input image", inputFlag|outputFlag);
            addProperty< QVImage<uChar,1> >("Output image", outputFlag);
            addProperty<QRect>("input rectangle", inputFlag);
            addProperty<QVPolyline>("input polyline", inputFlag);
        }

        void iterate() {
            QVImage<uChar> image = getPropertyValue< QVImage<uChar,1> >("Input image");
            QRect rect = getPropertyValue<QRect>("input rectangle");
            QVPolyline poly = getPropertyValue<QVPolyline>("input polyline");
            QVImage<uChar> dest = image;

            // Darken ROI area (by adding 0 to each pixel, but scaling dividing by 2^1:
            if (rect != QRect()) image.setROI(rect);
            AddC(image, 0, dest, 1, QPoint(rect.x(), rect.y()));
            dest.resetROI();

            // Undo it arount input polyline's points:
            // std::cout << poly << std::endl;
            for (int i = 0; i < poly.size(); i++)
                for (int x = poly[i].x()-3; x <= poly[i].x()+3; x++)
                    for (int y = poly[i].y()-3; y <= poly[i].y()+3; y++)
                        if ( (x >= 0) && (x < static_cast<int>(image.getCols())) && (y >= 0) && 
                             (y < static_cast<int>(image.getRows())) )
                             dest(x, y) = image(x, y);

            setPropertyValue< QVImage<uChar,1> >("Output image", dest);
        };
};

int main(int argc, char *argv[]) {
    QVApplication app(argc, argv, "Example program for QVision library." );
    
    MyWorker myWorker("worker");
    QVVideoReaderBlock camera("Video");
    MyImageCanvas imageCanvas("Features");

    QVDefaultGUI interface;

    camera.linkProperty(&myWorker, "Input image");

    myWorker.linkProperty("Output image", imageCanvas);
    imageCanvas.linkSelectedRectangle(myWorker, "input rectangle");
    imageCanvas.linkSelectedPolyline(myWorker, "input polyline");

    return app.exec();
}

/// \endcond
	
