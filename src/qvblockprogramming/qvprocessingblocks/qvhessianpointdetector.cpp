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

#include <qvip.h>
#include <qvipp.h>

#include <QVMatrix>
#include <QVHessianPointDetector>

QVHessianPointDetector::QVHessianPointDetector(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar,3> >("Input image", inputFlag|outputFlag);
	addProperty< QVImage<uChar,1> >("Feature response image", outputFlag);
	addProperty< QList < QPointF > >("Feature locations", outputFlag);
	addProperty< int >("Max number of corners", inputFlag, 300, "Maximal number of points to detect", 10, 1000);
	}

void QVHessianPointDetector::iterate()
	{
	// 0. Read input property values.
	const QVImage<uChar>	image = getPropertyValue< QVImage<uChar,3> >("Input image");
	const int		maxNumberCorners = getPropertyValue< int >("Max number of corners");
	const int		rows = image.getRows(), cols = image.getCols();

	timeFlag("Read input properties");

	// 2. Get candidate points from corner response image.
	QVImage<sFloat>	cornerResponseImage(cols, rows);
	FilterHessianCornerResponseImage(image, cornerResponseImage);
	setPropertyValue< QVImage<uChar> >("Feature response image", cornerResponseImage);
	timeFlag("Feature response image");

	// 3. Store locations and intensities of points.
	const QList<QPointF> actualPoints = maximalPoints(cornerResponseImage).values();
	timeFlag("Get corners and intensity responses");

	const int size = actualPoints.size();
	setPropertyValue< QList<QPointF> >("Feature locations", actualPoints.mid(MAX(0,size-maxNumberCorners),maxNumberCorners) );
	timeFlag("Store properties values");
	}

