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
@brief Does inpaint reconstruction over artificialy damaged frames from a video input source.

This program will artifically corrupt the input images of a video sequence with a binary mask image and reconstruct them using an <a href="http://en.wikipedia.org/wiki/Inpainting">image inpainting algorithm</a> implemented in the IPP library.

@section Usage
Simply compile, and execute the binary:
\code
	./inpaint --URL=<uri for input video> --Mask=<mask image file name>
\endcode

@param URL Video source identification string. See section @ref QVMPlayerURLFormat for further info about its format.
@param Mask Name for the image mask file. It must be a grayscale image, where pixels with a value different from zero will be considered corrupted from every frame
of the given input video. The mask image is scaled to the dimensions of each frame of the input video before applying the inpainting algorithm.

@author PARP Research Group. University of Murcia, Spain.
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QDebug>

#include <qvip.h>
#include <qvipp.h>

#include <QVApplication>
#include <QVVideoReaderBlock>
#include <QVDefaultGUI>
#include <QVImageCanvas>

#ifndef DOXYGEN_IGNORE_THIS
class MyBlock: public QVProcessingBlock
	{
	public:
		MyBlock(QString name): QVProcessingBlock(name)
			{
			addProperty< QVImage<uChar,1> >("Input image", inputFlag|outputFlag);
			addProperty< QVImage<uChar,1> >("Laplace image", outputFlag);
			addProperty< QList<QPointF> >("Laplace features", outputFlag);

			addProperty< bool >("Show Laplace features", inputFlag, true);
			addProperty< int >("Threshold", inputFlag, 32, "Maximal detection threshold", 0, 64);
			}

		void iterate()
			{
			const QVImage<uChar,1> image = getPropertyValue< QVImage<uChar,1> >("Input image");
			const bool showLaplaceFeatures = getPropertyValue< bool >("Show Laplace features");
			const int threshold = getPropertyValue< int >("Threshold");
			timeFlag("init");
		
			const QVImage<uChar, 1> laplaceImage = FastLaplaceFilter(image);
			timeFlag("Laplace filter");

			const QList<QPointF> points = FastLaplacePoints(image, threshold);
			timeFlag("Laplace points");

			setPropertyValue< QVImage<uChar,1> >("Laplace image", laplaceImage);

			if (showLaplaceFeatures)
				setPropertyValue< QList<QPointF> >("Laplace features", points);
			else
				setPropertyValue< QList<QPointF> >("Laplace features", QList<QPointF>());
			}
	};

int main(int argc, char *argv[])
	{
	QVApplication app(argc, argv,
		"Example program for QVision library. Shows Laplace response image and features.");

	QVVideoReaderBlock camera("Video");
	MyBlock block("Laplace block");
	camera.linkProperty(&block,"Input image");

	QVDefaultGUI interface;

	QVImageCanvas inputImage("Input image");
	block.linkProperty("Input image", inputImage);

	QVImageCanvas laplaceImage("Laplace image");
	block.linkProperty("Laplace image", laplaceImage);
	block.linkProperty("Laplace features", laplaceImage);
	laplaceImage.setRadius("Laplace features", 2);

	return app.exec();
	}

#endif

