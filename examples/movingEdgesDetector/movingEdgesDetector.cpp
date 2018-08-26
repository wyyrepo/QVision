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
@brief A simple moving edge detector based on the Canny edge detector.

This is an example application which combines several blocks from the QVision, and a user-defined one, to perform detection of moving edges on an input video sequence.

@section Usage
Once compiled, the program should be used with this command line:
@code
	./movingEdgesDetector --URL=<path or url to video>
@endcode

@param URL Video source identification string. See section @ref QVMPlayerURLFormat for further info about its format.
@author PARP Research Group. University of Murcia, Spain.
*/

#ifndef DOXYGEN_IGNORE_THIS

#include <QVApplication>
#include <QVVideoReaderBlock>
#include <QVDefaultGUI>
#include <QVImageCanvas>
#include <QVCannyEdgeDetector>
#include <QVImageRetarderBlock>

#include <qvippblocks.h>


#include <qvip.h>
#include <QVPolyline>
class MovingEdgesDetector: public QVProcessingBlock
	{
	public:
		MovingEdgesDetector(QString name = QString());
		void iterate();
	};

MovingEdgesDetector::MovingEdgesDetector(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar,1> >("Edge response image", inputFlag);
	addProperty< QVImage<uChar,1> >("Movement response image", inputFlag);
	addProperty< QVImage<uChar,1> >("Moving borders image", outputFlag);
	addProperty< double >("Minimal pixel percentage", inputFlag, 0.5, "Minimal percentage of moving pixels for an edge", 0.0, 1.0);
	}

void MovingEdgesDetector::iterate()
	{
	// 1. Read the input values and algorithm parameters
	const QVImage<uChar,1>	movementResponseImage = getPropertyValue< QVImage<uChar,1> >("Movement response image"),
				edgeResponseImage = getPropertyValue< QVImage<uChar,1> >("Edge response image");
	const double minimalPixelPercentage = getPropertyValue< double >("Minimal pixel percentage");

	// 2. process the input values with the input parameter values.

	// 2.1. Obtain the list of moving edges as a polyline list.
	// 2.1.1. Get the list of edges from the edge response image, as a list of polylines:
	const QList< QVPolyline > edges = getLineContoursThreshold8Connectivity(edgeResponseImage, 128);

	// 2.1.2. For each edge, test if a percentage high enough of its pixels is active in the
	//	movement response image. If so, store it in the list of moving image borders.
	QList< QVPolyline > movingImageBorders;
	foreach(QVPolyline edge, edges)
		{
		int count = 0;
		foreach(QPoint edgePoint, edge)
			if (movementResponseImage(edgePoint) != 0)
				count++;

		if (count >= minimalPixelPercentage * edge.size())
			movingImageBorders << edge;
		}

	// 2.2. Create the moving edge response image from the list of moving edges.
	// 2.2.1. Create the image with the same size as the movement response image.
	QVImage<uChar,1 > movingBordersImage(movementResponseImage.getCols(), movementResponseImage.getRows());

	// 2.2.2. Initialize the pixels of the image to zero
	Set(0, movingBordersImage);

	// 2.2.3. Draw each polyline contained in the moving image edges at the output image.
	foreach(QVPolyline edge, movingImageBorders)
		foreach(QPoint edgePoint, edge)
			movingBordersImage(edgePoint) = 255;

	// 3. Store the resulting image in the output property
	setPropertyValue< QVImage<uChar,1> >("Moving borders image", movingBordersImage);
	timeFlag("Publish resulting images");
	}

// main function.
int main(int argc, char *argv[])
        {
        QVApplication app(argc, argv,
                "Example program for QVision library. Obtains several features from input video frames."
                );

	QVDefaultGUI interface;

        QVVideoReaderBlock videoReader("Video");

	// 1. Edge detection
        QVCannyEdgeDetector cannyBlock("Canny block");
        QVImageCanvas imageDisplayer("Original image");
        QVImageCanvas edgesDisplayer("Canny edges");

        videoReader.linkProperty(&cannyBlock,"Input image");
        cannyBlock.linkProperty("Input image",imageDisplayer);
        cannyBlock.linkProperty("Output image",edgesDisplayer);

	// 2. Movement detection
	QVImageRetarderBlock<uChar,1> retarderBlock("Image retarder block");
	QVAbsDiff_uCharC1Block absDiffBlock("Absolute difference block");
	QVCompareC_uCharC1Block compareCBlock("Threshold block");
	QVImageCanvas movementDisplayer("Movement detector");
	
	compareCBlock.setPropertyValue<IppCmpOp>("ippCmpOp", ippCmpGreater);
	compareCBlock.setPropertyValue<uChar>("value", 32);
	
	videoReader.linkProperty(&retarderBlock, "Input image");
	videoReader.linkProperty(&absDiffBlock, "qvimage_pSrc1");
	retarderBlock.linkProperty("Output image", &absDiffBlock, "qvimage_pSrc2", QVProcessingBlock::SynchronousLink);
	absDiffBlock.linkProperty("qvimage_pDst", &compareCBlock, "qvimage_pSrc", QVProcessingBlock::SynchronousLink);
	compareCBlock.linkProperty("qvimage_pDst", movementDisplayer);

	// 3. Edge and movement combination using one qvipp block
	QVMul_uCharC1Block multBlock("Product block");
	QVImageCanvas movingEdgesDisplayer("Detected moving edges");

	cannyBlock.linkProperty("Output image", &multBlock, "qvimage_pSrc1", QVProcessingBlock::SynchronousLink);
	compareCBlock.linkProperty("qvimage_pDst", &multBlock, "qvimage_pSrc2", QVProcessingBlock::SynchronousLink);
	multBlock.linkProperty("qvimage_pDst", movingEdgesDisplayer);

	// 4. Edge and movement combination using new block
	MovingEdgesDetector movingEdgesDetector("Edge & movement image composer");
	QVImageCanvas movingEdgesDisplayer2("Detected moving edges 2");

	cannyBlock.linkProperty("Output image", &movingEdgesDetector, "Edge response image", QVProcessingBlock::SynchronousLink);
	compareCBlock.linkProperty("qvimage_pDst", &movingEdgesDetector, "Movement response image", QVProcessingBlock::SynchronousLink);
	movingEdgesDetector.linkProperty("Moving borders image", movingEdgesDisplayer2);

        return app.exec();
        }

#endif
