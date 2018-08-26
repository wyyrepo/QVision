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
@ingroup CGALExamplePrograms
@brief Obtains the convex hull of a set of points.

This application detects a set of feature points on each frame of the input video sequence, and shows the corresponding <a href="http://en.wikipedia.org/wiki/Convex_hull">Convex hull</a> on an image canvas.

An example plot of that triangulation can be seen in the following image:

@image html cgal-convex-hull.png

This application uses CGAL functionality to obtain the triangulation.

@section Usage
Once compiled, the program should be used with this command line:
\code
	./convexhull --URL=<path or url to video>
\endcode

@param URL Video source identification string. See section @ref QVMPlayerURLFormat for further info about its format.

@author PARP Research Group. University of Murcia, Spain.
*/



#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

// Important: should include CGAL headers before QVision headers, to avoid a naming conflict.
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>

#include <QVApplication>
#include <QVVideoReaderBlock>
#include <QVDefaultGUI>
#include <QVImageCanvas>
#include <QVPolylineF>
#include <QVHarrisPointDetector>

#ifndef DOXYGEN_IGNORE_THIS
typedef CGAL::Exact_predicates_inexact_constructions_kernel::Point_2 Point_2;
QList<QPointF> cgalConvexHull(const QList<QPointF> &selectedPoints)
	{
	Point_2 points[selectedPoints.size()];
	for(int i = 0; i < selectedPoints.size(); i++)
		points[i] = Point_2(selectedPoints[i].x(), selectedPoints[i].y());

	Point_2 result[selectedPoints.size()];
	Point_2 *ptr = CGAL::convex_hull_2(points, points+selectedPoints.size(), result);
	std::cout << ptr - result << " points on the convex hull" << std::endl;

	QList<QPointF> convexHull;
	for (int i = 0; i < ptr - result; i++)
		convexHull << QPointF(result[i].x(), result[i].y());

	return convexHull;
	}

class ConvexHullBlock: public QVProcessingBlock
	{
	public:
		ConvexHullBlock(const QString name): QVProcessingBlock(name)
			{
			addProperty< QList < QPointF > >("Feature locations", inputFlag|outputFlag);
			addProperty< QVPolylineF >("Convex hull", outputFlag);
			}

		void iterate()
			{
			// 0. Read input property values.
			const QList<QPointF> selectedPoints = getPropertyValue< QList< QPointF > >("Feature locations");
			timeFlag("Read data");

			// 1. Get the convex hull.
			const QList<QPointF> convexHull = cgalConvexHull(selectedPoints);

			// 2. Store it as a polyline for visualization.
			setPropertyValue< QVPolylineF >("Convex hull", convexHull);
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
	ConvexHullBlock convexHullBlock("Convex hull");
	pointDetector.linkProperty("Feature locations", convexHullBlock, QVProcessingBlock::SynchronousLink);

	// Image outputs
	QVImageCanvas imageCanvas("Convex hull");
	pointDetector.linkProperty("Input image", imageCanvas);
	convexHullBlock.linkProperty("Feature locations", imageCanvas);
	convexHullBlock.linkProperty("Convex hull", imageCanvas);

	QVDefaultGUI interface;

	return app.exec();
	}

#endif	// DOXIGEN_IGNORE_THIS

