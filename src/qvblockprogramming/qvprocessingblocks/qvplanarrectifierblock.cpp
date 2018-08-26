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

//#include <qvipp.h>
#include <qvprojective.h>

#include <QVMatrix>
#include <QVPlanarRectifierBlock>

QVPlanarRectifierBlock::QVPlanarRectifierBlock(QString name): QVProcessingBlock(name)
	{
	addProperty<double>("Zoom", inputFlag, 100, "Size of the rectified template", 10, 250);
	addProperty<int>("Canvas size", inputFlag, 1, "Size of the rectified template", 1, 5);
	addProperty< QVMatrix >("Homography", inputFlag, QVMatrix::identity(3));

	addProperty< QVImage<uChar,3> >("Input image", inputFlag|outputFlag);
	addProperty< QVImage<uChar,3> >("Warped image", outputFlag);
	}

void QVPlanarRectifierBlock::iterate()
	{
	// 0. Read input property values.
	const QVImage<uChar,3> image = getPropertyValue< QVImage<uChar,3> >("Input image");
	const int	rows = image.getRows(), cols = image.getCols(),
			canvasSize = getPropertyValue<int>("Canvas size"),
			warpedRows = canvasSize*rows, warpedCols = canvasSize*cols;
	const double	zoom = getPropertyValue<double>("Zoom");
	const QVMatrix	H = getPropertyValue< QVMatrix>("Homography");

	if (H.getCols() != 3 || H.getRows() != 3)
		return;

	timeFlag("Read input properties");

	// 1. Store and show results.
	// 1.1. Obtain planar rectification homography, adecuate for ippWarpPerspective
	QVMatrix scaleMatrix = QVMatrix::identity(3);
	scaleMatrix(0,0) = 2/cols;
	scaleMatrix(1,1) = -2/cols;

	QVMatrix	traslateMatrix = QVMatrix::translationMatrix(-cols/2, -rows/2),
			detraslateMatrix = QVMatrix::translationMatrix(warpedCols/2, warpedRows/2);

	QVMatrix zoomMatrix = QVMatrix::identity(3);
	zoomMatrix(0,0) = zoom;
	zoomMatrix(1,1) = -zoom;

	const QVMatrix rectifyingHomography = detraslateMatrix * zoomMatrix * H * scaleMatrix * traslateMatrix;

	// 1.2. Draw warped image by homography.
	QVImage<uChar,3> warped(warpedCols, warpedRows);
	Set(((uChar [3]){0,0,0}), warped);

	// Hacer con las IPP
	//myWarpPerspective(image, warped, rectifyingHomography);
        //WarpPerspective(image, warped, rectifyingHomography);

	setPropertyValue< QVImage<uChar,3> >("Warped image", warped);
	timeFlag("Image wrapping");
	}
