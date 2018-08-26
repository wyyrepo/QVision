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
#include <QVPolyline>

#include <QVMSER>
#include <QVMSERDetector>

#ifndef DOXYGEN_IGNORE_THIS
const QVImage<uChar> QVMSERDetector::negateImage(const QVImage<uChar> image) const
	{
	const uInt rows = image.getRows(), cols = image.getCols();
	QVImage<uChar> notImage(cols, rows);
	for (uInt col = 0; col < cols; col++)
		for (uInt row = 0; row < rows; row++)
			notImage(col, row) = 255 - image(col, row);

	return notImage;
	}

QVMSERDetector::QVMSERDetector(QString name): QVProcessingBlock(name)
	{
	addProperty<int>("Delta", inputFlag, 10, "MSER parameter, as described in the paper.", 1, 128);
	addProperty<int>("minAreaMSER", inputFlag, 10, "MSER with area lesser than this value are discarted.", 1, 100*100);
	addProperty<int>("maxAreaMSER", inputFlag, 10000, "MSER with area greater than this value are discarted.", 1, 1000*1000);
	addProperty<double>("diffAreaThreshold", inputFlag, 0.01, "Proportion of the difference in areas to be considered different", 0.0, 1.0);
	addProperty< QVImage<uChar,3> >("Input image", inputFlag|outputFlag);
	addProperty< QList<QVPolyline> >("MSER contours", outputFlag);
	}

void QVMSERDetector::iterate()
	{
	// 0. Read parameters
	const int delta = getPropertyValue<int>("Delta"),
		minArea = getPropertyValue<int>("minAreaMSER"),
		maxArea = getPropertyValue<int>("maxAreaMSER");
	const double diffAreaThreshold = getPropertyValue<double>("diffAreaThreshold");
	const QVImage<uChar> image = getPropertyValue< QVImage<uChar,3> >("Input image");
	const QVImage<uChar> notImage = negateImage(image);

	timeFlag("Read parameters");

	// 1. Apply MSER
	QList<QVMSER> MSERListLow, MSERListHigh;

	getMSER(image, MSERListLow, delta, minArea, maxArea, diffAreaThreshold);
	timeFlag("MSER Low");

	getMSER(notImage, MSERListHigh, delta, minArea, maxArea, diffAreaThreshold);
	timeFlag("MSER High");

	// 2. Publish resulting MSER's
	QList< QVPolyline > polylineMSERList;
	getMSERContours(image, MSERListLow, polylineMSERList);

	getMSERContours(notImage, MSERListHigh, polylineMSERList);

	setPropertyValue< QList<QVPolyline> >("MSER contours", polylineMSERList);
	timeFlag("Publish resulting images");
	}

#endif
