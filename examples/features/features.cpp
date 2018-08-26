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

/*!
@file
@ingroup ExamplePrograms
@brief Obtains several image features from input video frames

This application different blocks which obtain four different image features, depicting on four respective image canvas the resulting features. These obtained image features are:
 - Canny edges.
 - Harris corners.
 - Maximal stable extremal regions (MSER).
 - Thresholded contours.

@section Usage Usage of the program.
Once QVision has been correctly installed in your system, compile using the <i>qmake</i> and <i>make</i> tools:
@code # qmake; make @endcode
Execute the application with the following line:
@code ./features --URL=<source video identifier string> --RealTime=true @endcode
For example:
@code ./features --URL=http://perception.inf.um.es/public_data/videos/misc/minuto.avi --RealTime=true @endcode
See section @ref QVMPlayerURLFormat for further info about the format and types of source video identifier strings.

@author PARP Research Group. University of Murcia, Spain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QDebug>

#include <qvip.h>

#include <QVApplication>
#include <QVVideoReaderBlock>
#include <QVDefaultGUI>
#include <QVImageCanvas>
#include <QVPolyline>
#include <QVHarrisPointDetector>
#include <QVCannyEdgeDetector>
#include <QVMSERDetector>
#include <QVNumericPlot>
#include <QVHistogramPlot>

#ifndef DOXYGEN_IGNORE_THIS

class ContourExtractorBlock: public QVProcessingBlock
	{
	public:
		ContourExtractorBlock(QString name = QString()): QVProcessingBlock(name)
			{
			addProperty<int>("Threshold", inputFlag,	128, "Threshold for a point to count as pertaining to a region", 0, 255);
			addProperty<int>("MinAreaIPE", inputFlag,	0, "Minimal area to keep points in the IPE algorithm", 0, 50);
			addProperty< QVImage<uChar,3> >("Input image", inputFlag|outputFlag);
			addProperty< QList<QVPolyline> >("Internal contours", outputFlag);
			addProperty< QList<QVPolyline> >("External contours", outputFlag);
			}

		void iterate()
			{
			// 0. Read input parameters
			const QVImage<uChar,1> image = getPropertyValue< QVImage<uChar,3> >("Input image");
			const uInt	rows = image.getRows(), cols = image.getCols(),
					threshold = getPropertyValue< int >("Threshold"),
					minAreaIPE = getPropertyValue< int >("MinAreaIPE");

			timeFlag("Read input parameters");
		
			// 1. Get contours from image
			const QList<QVPolyline> contours = getConnectedSetBorderContoursThreshold(image, threshold);
			timeFlag("Get contours from image");

			// 2. Apply IPE
			QList<QVPolyline> ipeContours;

			foreach(QVPolyline polyline, contours)
				{
				QVPolyline ipePolyline;
				IterativePointElimination(polyline, ipePolyline, minAreaIPE);
				if (ipePolyline.size() > 0)
					ipeContours.append(ipePolyline);
				}

			timeFlag("IPE filtering");

			// 3. Export contours to output property
			QList<QVPolyline> internalContours, externalContours;

			foreach(QVPolyline polyline, ipeContours)
				if (polyline.direction)
					internalContours.append(polyline);
				else
					externalContours.append(polyline);

			setPropertyValue< QList< QVPolyline> >("Internal contours",internalContours);
			setPropertyValue< QList< QVPolyline> >("External contours",externalContours);
			timeFlag("Computed output contours");
			}
	};

int main(int argc, char *argv[])
	{
	ippSetNumThreads(1);

	QVApplication app(argc, argv,
		"Example program for QVision library. Obtains several features from input video frames."
		);

	ContourExtractorBlock contoursBlock("Contours Extractor Block");
	QVCannyEdgeDetector cannyBlock("Canny Operator Block");
	QVHarrisPointDetector cornersBlock("Harris Block");
	QVMSERDetector mserBlock("MSER Block");

	QVVideoReaderBlock videoReader("Video reader");

	videoReader.linkProperty(&contoursBlock,"Input image");
	videoReader.linkProperty(&cannyBlock,"Input image");
	videoReader.linkProperty(&cornersBlock,"Input image");
	videoReader.linkProperty(&mserBlock,"Input image");

	QVDefaultGUI interface;

	QVImageCanvas contourCanvas("Contours");
	contoursBlock.linkProperty("Input image", contourCanvas);
	contoursBlock.linkProperty("Internal contours", contourCanvas);
	contoursBlock.linkProperty("External contours", contourCanvas);
	contourCanvas.setPropertyValue<QColor>("Color for External contours", Qt::blue);

	QVImageCanvas cannyCanvas("Canny");
	cannyBlock.linkProperty("Output image", cannyCanvas);

	QVImageCanvas cornersCanvas("Harris corners displayer");
	cornersBlock.linkProperty("Input image", cornersCanvas);
	cornersBlock.linkProperty("Feature locations", cornersCanvas);

	QVImageCanvas mserCanvas("MSER Regions displayer");
	mserBlock.linkProperty("Input image", mserCanvas);
	mserBlock.linkProperty("MSER contours", mserCanvas);
	return app.exec();
	}

#endif
