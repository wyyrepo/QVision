/*
 *	Copyright (C) 2009, 2010, 2011, 2012. PARP Research Group.
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
@file
@ingroup ExamplePrograms
@brief Example application showing how to let the user interact with the application, through the GUI.

This example lets the user to play with the ROI selector of the QVImageCanvas widget, marking the selected region in the output image with a dark square in the image canvas. Also the user can select a set of points in the image with the canvas, which will be linked by the block in a QVPolyline object.

At last, the GUI includes a button to show how to create a trigger in the block.

You must specify a valid input video source to execute the application. Then, clicking on the ROI selector button:

@image html qvimagecanvas_roi.png

You can select a ROI that will be painted darker in the output image by the application.

@section Usage Usage of the program.
Once installed the QVision, compile using the <i>qmake</i> and <i>make</i> tools:
@code # qmake; make @endcode
Execute the application with the following line:
@code ./userIO --URL=<source video identifier string> @endcode
For example:
@code ./userIO --URL=http://perception.inf.um.es/public_data/videos/misc/minuto.avi @endcode

@param URL Video source identification string. See section @ref QVMPlayerURLFormat for further info about its format.

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

#ifndef DOXYGEN_IGNORE_THIS
class UserInteract: public QVProcessingBlock
	{
	public:
		UserInteract(QString name = QString()): QVProcessingBlock(name)
			{
			addProperty< QVImage<uChar,1> >("Input image", inputFlag|outputFlag);
			addProperty< QVImage<uChar,1> >("Output image", outputFlag);
			addProperty<QRect>("in rect selec", inputFlag);
			addProperty<QVPolyline>("in polyline", inputFlag);
			addProperty<int>("Radius", inputFlag, 4, "Radius of the selected pixel area", 0, 32);

			addTrigger("Click me");
			}

		void processTrigger(const QString triggerName)
			{
			std::cout << triggerName.toStdString() << ", block's iteration " << getIteration() << std::endl;
			}

		void iterate()
			{
			QVImage<uChar> image = getPropertyValue< QVImage<uChar,1> >("Input image");
			QRect selectedRectangle = getPropertyValue<QRect>("in rect selec");
			const QVPolylineF selectedPoints = getPropertyValue<QVPolylineF>("in polyline");
			const int radius = getPropertyValue<int>("Radius");
			QVImage<uChar> dest = image;

			// Set dark in the ROI area
			if (selectedRectangle == QRect())
				selectedRectangle = image.getROI();

			image.setROI(selectedRectangle);
				
			AddC(image, 10, dest, 1, QPoint(selectedRectangle.x(), selectedRectangle.y()));
			dest.resetROI();

			// Revert darkness near the polyline's points
			foreach(QPointF pointF, selectedPoints)
				{
				QPoint point(pointF.x(), pointF.y());
				const QRect restoreRegion = QRect(point - QPoint(radius,radius), QSize(1+2*radius,1+2*radius));
				if (selectedRectangle.contains(restoreRegion, true))
					{
					image.setROI(restoreRegion);
					Copy(image, dest, point - QPoint(radius,radius));
					dest.resetROI();
					}
				}
			setPropertyValue< QVImage<uChar,1> >("Output image", dest);
			}
	};

int main(int argc, char *argv[])
	{
	QVApplication app(argc, argv, "Example program for QVision library." );
	
	QVVideoReaderBlock camera("Video");
	UserInteract userInteract("User interact");

	camera.linkProperty(&userInteract, "Input image");

	QVDefaultGUI interface;

	QVImageCanvas imageCanvas("image");
	userInteract.linkProperty("Output image", imageCanvas);
	imageCanvas.linkSelectedRectangle(userInteract, "in rect selec");
	imageCanvas.linkSelectedPolyline(userInteract, "in polyline");

	return app.exec();
	}

#endif
	
