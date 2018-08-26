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
	private:
		QVImage<uChar> mask;

	public:
		MyBlock(QString name): QVProcessingBlock(name)
			{
			addProperty<QString>("Mask", inputFlag,	"mask.gif", "Image file for mask");
			addProperty<double>("Radius", inputFlag, 4.0, "Mask radius", 1.0, 30.0);
			addProperty<bool>("Use Telea", inputFlag, false, "Use Telea versus NS");
			addProperty< QVImage<uChar,3> >("Input image", inputFlag|outputFlag);
			addProperty< QVImage<uChar,1> >("Mask image", outputFlag);
			addProperty< QVImage<uChar,3> >("Restored image", outputFlag);

			const QString maskFilePath = getPropertyValue<QString>("Mask");
			QVImage<uChar, 3> temp;
			// Here we try to open mask file. If it can't be opened, we finish.
			if(!readQVImageFromFile(maskFilePath, temp) )
				setLastError("Error, can't find mask image file");
			else
				mask = temp;
			}

		void iterate()
			{
			bool useTelea =	getPropertyValue<bool>("Use Telea");
			double radius = getPropertyValue<double>("Radius");
		
			QVImage<uChar,3> image = getPropertyValue< QVImage<uChar,3> >("Input image");
			timeFlag("init");
		
			///////////
			// Obtain mask image of size equal to image
			QVImage<uChar> maskForImage(image.getCols(), image.getRows());
			Resize(mask, maskForImage);
		
			for (uInt col = 0; col < image.getCols(); col++)
				for (uInt row = 0; row < image.getRows(); row++)
					if (maskForImage(col, row) < 128)
						maskForImage(col, row) = 0;
					else
						maskForImage(col, row) = 255;
		
			timeFlag("Obtain mask image of size equal to image");
		
			////////////
			// Get distances using fast marching algorithm
			QVImage<uChar> buffer;
			FastMarchingGetBufferSize(maskForImage, buffer);
		
			QVImage<sFloat> distances(image.getCols(), image.getRows());
			Set(0, distances);

			FastMarching(maskForImage, distances, radius, buffer);
			timeFlag("Get distances using fast marching algorithm");
		
			/////////////
			// Inpainting
			IppiInpaintState_8u_C3R * pState;
			InpaintInitAllocC3(&pState, distances, maskForImage, radius, useTelea?IPP_INPAINT_TELEA:IPP_INPAINT_NS);

			QVImage<uChar,3> inpaint(image.getCols(),image.getRows());
			Inpaint(image, inpaint, * pState, QPoint(0,0));

			InpaintFreeC3(pState);
			timeFlag("Inpainting");
						
			/////////////
			// Showing results
			setPropertyValue< QVImage<uChar,1> >("Mask image", maskForImage);
			setPropertyValue< QVImage<uChar,3> >("Restored image", inpaint);
			timeFlag("Showing results");
			}
	};

int main(int argc, char *argv[])
	{
	QVApplication app(argc, argv,
		"Example program for QVision library. Does inpaint reconstruction from an artificialy damaged source video.");

	QVVideoReaderBlock camera("Video");
	MyBlock block("Inpaint block");
	camera.linkProperty(&block,"Input image");

	QVDefaultGUI interface;

	QVImageCanvas inputImage("Input image");
	block.linkProperty("Input image", inputImage);

	QVImageCanvas maskImage("Mask image");
	block.linkProperty("Mask image", maskImage);

	QVImageCanvas restoredImage("Restored image");
	block.linkProperty("Restored image", restoredImage);

	return app.exec();
	}

#endif

