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
#include <QVPolyline>
#include <QVCannyEdgeDetector>

#ifndef DOXYGEN_IGNORE_THIS
QVCannyEdgeDetector::QVCannyEdgeDetector(QString name): QVProcessingBlock(name)
	{
	addProperty<double>("cannyHigh", inputFlag, 150, "High threshold for Canny operator", 50, 1000);
	addProperty<double>("cannyLow", inputFlag, 50, "Low threshold for Canny operator", 10, 500);
	addProperty<bool>("applyIPE", inputFlag, FALSE, "If we want to apply the IPE algorithm");
	addProperty<double>("paramIPE", inputFlag, 5.0, "IPE parameter (max. allowed distance to line)", 1.0, 25.0);
	addProperty<bool>("intersectLines", inputFlag, TRUE, "If we want IPE to postprocess polyline (intersecting lines)");
	addProperty<int>("minLengthContour", inputFlag, 25, "Minimal length of a contour to be considered", 1, 150);
	//addProperty<int>("showNothingCannyImage", inputFlag, 0, "If we want nothing|Canny|original image to be shown",0,2);
	//addProperty<bool>("showContours", inputFlag, TRUE, "If we want contours to be shown");

	addProperty< QVImage<uChar,1> >("Output image", outputFlag);
	addProperty< QVImage<uChar,3> >("Input image", inputFlag|outputFlag);
	addProperty< QList<QVPolyline> >("Output contours", outputFlag);
	}

void QVCannyEdgeDetector::iterate()
	{
	// 0. Read input parameters
	const double cannyHigh = getPropertyValue<double>("cannyHigh");
	const double cannyLow = getPropertyValue<double>("cannyLow");
	const bool applyIPE = getPropertyValue<bool>("applyIPE");
	const double paramIPE = getPropertyValue<double>("paramIPE");
	const bool intersectLines = getPropertyValue<bool>("intersectLines");
	const int minLengthContour = getPropertyValue<int>("minLengthContour");
	//const int showNothingCannyImage = getPropertyValue<int>("showNothingCannyImage");
	//const bool showContours = getPropertyValue<bool>("showContours");
	const QVImage<uChar,1> image = getPropertyValue< QVImage<uChar,3> >("Input image");
	const uInt cols = image.getCols(), rows = image.getRows();

	QVImage<sFloat> imageFloat(cols, rows), dX(cols, rows), dY(cols, rows), dXNeg(cols, rows);
	QVImage<uChar> canny(cols, rows), buffer;

	// 1. Convert image from uChar to sShort
	Convert(image, imageFloat);
	timeFlag("Convert image from uChar to sShort");

	// 2. Obtain horizontal and vertical gradients from image
	FilterSobelHorizMask(imageFloat,dY);
	FilterSobelVertMask(imageFloat,dX);
	MulC(dX, -1, dXNeg);
	timeFlag("Obtain horizontal and vertical gradients from image");

	// 3. Apply Canny operator
	CannyGetSize(canny, buffer);
	Canny(dXNeg, dY, canny, cannyLow,cannyHigh, buffer);
	timeFlag("Apply Canny operator");

	// 4. Get contours
	const QList<QVPolyline> contourList = getLineContoursThreshold8Connectivity(canny, 128);
	timeFlag("Get contours");

	QList<QVPolyline> outputList;
	foreach(QVPolyline contour,contourList)
		if(contour.size() > minLengthContour)
			{
			#ifdef QVMATRIXALGEBRA_AVAILABLE
			if(applyIPE)
				{
				QVPolyline IPEcontour;
				IterativePointElimination(contour, IPEcontour, paramIPE, FALSE, intersectLines);
				outputList.append(IPEcontour);
				}
			else
			#endif // QVMATRIXALGEBRA_AVAILABLE
				outputList.append(contour);
			}

	timeFlag("IPE on contours");

	// 5. Publish resulting data
	// Always show Canny image.
	//if(showNothingCannyImage == 1)
	setPropertyValue< QVImage<uChar,1> >("Output image",canny);

	//else if(showNothingCannyImage == 2)
	//	setPropertyValue< QVImage<uChar,1> >("Output image",image);
	/*else	{
		QVImage<uChar> whiteImage(cols, rows);
		Set(255, whiteImage);
		setPropertyValue< QVImage<uChar,1> >("Output image",whiteImage);
		}*/

	//if(showContours)
	// Always publish contour list
	setPropertyValue< QList< QVPolyline> >("Output contours",outputList);
	//else
	//setPropertyValue< QList< QVPolyline> >("Output contours",QList<QVPolyline>());

	timeFlag("Publish results");
	}

#endif
