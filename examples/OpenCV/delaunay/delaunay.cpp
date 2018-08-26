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
@ingroup OpenCVExamplePrograms
@brief Obtains the Delaunay triangulation for a set of points.

This application detects a set of feature points on each frame of the input video sequence, and shows the corresponding <a href="http://en.wikipedia.org/wiki/Delaunay_triangulation">Delaunay triangulation</a> on an image canvas.

An example plot of that triangulation can be seen in the following image:

@image html opencv-delaunay.png

This application uses OpenCV functionality to obtain the triangulation.

@section Usage
Once compiled, the program should be used with this command line:
\code
	./delaunay --URL=<path or url to video>
\endcode

@param URL Video source identification string. See section @ref QVMPlayerURLFormat for further info about its format.

@author PARP Research Group. University of Murcia, Spain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include <QDebug>
#include <QThread>

#include <QVApplication>
#include <QVVideoReaderBlock>
#include <QVDefaultGUI>
#include <QVImageCanvas>
#include <QVPolylineF>

#include <QVHarrisPointDetector>
#include <qvip.h>
#include <qvimageio.h>

#ifndef DOXYGEN_IGNORE_THIS

#ifdef OPENCV
#include <QVDelaunayTriangulation>

QHash<QPointF, QPointF> openCVDelaunayTriangulation(const QList<QPointF> &selectedPoints)
	{
	// STORAGE AND STRUCTURE FOR DELAUNAY SUBDIVISION

	// Set boundaries for the Delaunay triangulation algorithm.
	double	minX = std::numeric_limits<double>::max(),
		minY = std::numeric_limits<double>::max(),
		maxX = std::numeric_limits<double>::min(),
		maxY = std::numeric_limits<double>::min();

	foreach(QPointF point, selectedPoints)
		{
		minX = MIN(minX, point.x());
		minY = MIN(minY, point.y());
		maxX = MAX(maxX, point.x());
		maxY = MAX(maxY, point.y());
		}

	QVDelaunayTriangulation delaunayTriangulation(QRect(minX, minY, maxX - minX, maxY - minY));

	// Add points to the Delaunay subdivision structure.
	foreach(QPointF point, selectedPoints)
		delaunayTriangulation.addPoint(point);
	return delaunayTriangulation.getLinks();
	}

class DelaunayBlock: public QVProcessingBlock
	{
	private:
		QList<QVPolylineF> map2polyline(const QHash<QPointF, QPointF> &map)
			{
			QList<QVPolylineF> polylines;
		
			QHashIterator<QPointF, QPointF> iterator(map);
		
			while (iterator.hasNext())
				{
				iterator.next();
				QVPolylineF polyline;
				polyline.append(iterator.key());
				polyline.append(iterator.value());
				polylines.append(polyline);
				}
		
			return polylines;
			}

	public:
		DelaunayBlock(const QString name): QVProcessingBlock(name)
			{
			addProperty< QList < QPointF > >("Feature locations", inputFlag|outputFlag);
			addProperty< QList<QVPolylineF> >("Delaunay edges", outputFlag);
			}

		void iterate()
			{
			// 0. Read input property values.
			const QList<QPointF> selectedPoints = getPropertyValue< QList< QPointF > >("Feature locations");
			timeFlag("Read data");

			// 1. Get Delaunay triangulation.
			const QHash<QPointF, QPointF> correspondences = openCVDelaunayTriangulation(selectedPoints);
			timeFlag("Generated edges");

			// 2. Generate the graph as a list of polylines for visualization.
			const QList<QVPolylineF> delaunayEdges = map2polyline(correspondences);
			timeFlag("From correspondences to polylines");

			setPropertyValue< QList<QVPolylineF> >("Delaunay edges", delaunayEdges);
			}
	};

#include <QVYUV4MPEG2WriterBlock>
#include <QVNumericPlot>
int main(int argc, char *argv[])
	{
	QVApplication app(argc, argv,
		"Example program for QVision library. Obtains intrinsic and extrinsic camera parameters."
		);

	QVVideoReaderBlock camera("Video");

	QVHarrisPointDetector pointDetector("Harris corners detector");
	camera.linkProperty(&pointDetector,"Input image");

	// Camera calibrator.
	DelaunayBlock delaunayBlock("Delaunay");
	pointDetector.linkProperty("Feature locations", delaunayBlock, QVProcessingBlock::SynchronousLink);

	// Image outputs
	QVImageCanvas imageCanvas("Delaunay regions");
	pointDetector.linkProperty("Input image", imageCanvas);
	delaunayBlock.linkProperty("Feature locations", imageCanvas);
	delaunayBlock.linkProperty("Delaunay edges", imageCanvas);
	imageCanvas.setColor("Delaunay edges", Qt::red);

        QVDefaultGUI gui;

	return app.exec();
	}
#else
int main(int argc, char *argv[])
	{
	std::cout << "ERROR: OpenCV compatibility was not activated in QVision compilation." << std::endl;
	return -1;
	}
#endif	// OPENCV
#endif	// DOXIGEN_IGNORE_THIS

