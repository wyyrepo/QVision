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

#include <QList>
#include <QPointF>

#include <qvip.h>
#include <QVPolylineF>

#include <QVHarrisPointDetector>

#ifndef DOXYGEN_IGNORE_THIS
QVHarrisPointDetector::QVHarrisPointDetector(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar,3> >("Input image", inputFlag|outputFlag);
	//addProperty< QVImage<uChar,1> >("Feature response image", outputFlag);
	addProperty< QList < QPointF > >("Feature locations", outputFlag);
	addProperty< int >("Max number of corners", inputFlag, 300, "Maximal number of corners to detect", 10, 1000);

	addProperty< double >("Threshold", inputFlag, 1.0, "window size ", 0.0, 256.0);
	}

void QVHarrisPointDetector::iterate()
	{
	// 0. Read input parameters
	const QVImage<uChar> image = getPropertyValue< QVImage<uChar,3> >("Input image");
	const double threshold = getPropertyValue<double>("Threshold");
	const int pointNumber = getPropertyValue<int>("Max number of corners");
	timeFlag("grab Frame");

	// 1. Obtain corner response image.
	QVImage<sFloat>	cornerResponseImage(image.getRows(), image.getCols());
	FilterHarrisCornerResponseImage(image, cornerResponseImage);
	timeFlag("Harris corner response image");

	// 2. Local maximal filter.
	const QList<QPointF> hotPoints = fastMaximalPoints(cornerResponseImage, threshold).values();
	timeFlag("Point detection");

	// 3. Output resulting data.
	//setPropertyValue< QVImage<uChar,1> >("Output image", image);
	setPropertyValue< QList<QPointF> >("Feature locations", hotPoints.mid(0,pointNumber));
	}
#endif
