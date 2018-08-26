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
@brief Composes component tree image filtering and canny operator for making animation like images from real images.

\section About About the rotoscoper.
This example program performs image filtering over a video input, mixing component tree pruning and canny operator filtering, to get <a href="http://en.wikipedia.org/wiki/Rotoscoping">rotoscoped-like</a> effect over the frames of a real image input video:

\image html rotoscopedSolana.png

The program is designed using three different blocks, that share thread safe data and synchronize themselves, so all of them iterate one time over each input frame. Here is the data flow scheme for these blocks:

\image html rotoscoperDataFlow.png

@section Usage Usage of the program.
Once installed the QVision, compile using the <i>qmake</i> and <i>make</i> tools:
@code # qmake; make @endcode
Execute the application with the following line:
@code ./rotoscoper --URL=<source video identifier string> @endcode
For example:
@code ./rotoscoper --URL=http://perception.inf.um.es/public_data/videos/misc/minuto.avi @endcode
See section @ref QVMPlayerURLFormat for further info about the format and types of source video identifier strings.
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
#include <QVComponentTree>
#include <QVCPUPlot>

#ifndef DOXYGEN_IGNORE_THIS
class ComponentTreeBlock: public QVProcessingBlock
	{
	public:
		ComponentTreeBlock(QString name): QVProcessingBlock(name)
			{
			addProperty<int>("Maximal area to prune", inputFlag, 50,
				"Maximal size of the areas to be pruned in the image", 5, 10000);
			addProperty< QVImage<uChar,1> >("Input image", inputFlag|outputFlag);
			addProperty< QVImage<uChar,1> >("Pruned component tree image", outputFlag);
			}

		void iterate()
			{
			//////////////////
			// Read parameters
			QVImage<uChar> fromcamera = getPropertyValue< QVImage<uChar,1> >("Input image");
			QVImage<uChar> image = fromcamera;
			QVImage<uChar> temp = image;

			//const uInt	rows = image.getRows(), cols = image.getCols();
			const uInt minAreaThreshold = getPropertyValue<int>("Maximal area to prune");

			timeFlag("Read parameters");

			//////////////////////////////////////////////////
			// Prune low areas from image, with component tree
			QVComponentTree componentTreeLow(image,true);
			timeFlag("Call to getComponentTree for low areas");

			FilterPruneComponentTreeSmallRegions(image, componentTreeLow, minAreaThreshold);
			timeFlag("Prune low areas from image");

			///////////////////////////////////////////////////
			// Prune high areas from image, with component tree
			QVComponentTree componentTreeHigh(image);
			timeFlag("Call to getComponentTree for high areas");

			FilterPruneComponentTreeSmallRegions(image, componentTreeHigh, minAreaThreshold);
			timeFlag("Prune high areas from image");

			/////////////////
			// Publish resulting images
			setPropertyValue< QVImage<uChar,1> >("Pruned component tree image", image);
			timeFlag("Publish resulting images");
			}
	};

class CannyBlock: public QVProcessingBlock
	{
	public:
		CannyBlock(QString name): QVProcessingBlock(name)
			{
			addProperty<double>("Threshold high", inputFlag,	150,	"High threshold for Canny operator", 50, 1000);
			addProperty<double>("Threshold low", inputFlag,		50,	"Low threshold for Canny operator", 10, 500);
			addProperty< QVImage<uChar,1> >("Canny image", outputFlag);
			addProperty< QVImage<uChar,1> >("Input image", inputFlag|outputFlag);
			}

		void iterate()
			{
			//////////////////
			// Read input parameters
			QVImage<uChar,1> image = getPropertyValue< QVImage<uChar,1> >("Input image");
			uInt cols = image.getCols(), rows = image.getRows();
			QVImage<sFloat>	imageFloat(cols, rows), dX(cols, rows), dY(cols, rows), dXNeg(cols, rows);
			QVImage<uChar>	canny(cols, rows), buffer;
		
			//////////////////
			// Convert image from uChar to sShort
			Convert(image, imageFloat);
			timeFlag("Convert image from uChar to sShort");
		
			//////////////////
			// Obtain horizontal and vertical gradients from image
			FilterSobelHorizMask(imageFloat, dY, ippMskSize3x3);
			FilterSobelVertMask(imageFloat, dX, ippMskSize3x3);
			MulC(dX, -1, dXNeg);
			timeFlag("Obtain horizontal and vertical gradients from image");
		
			/////////////////
			// Apply Canny operator
			CannyGetSize(canny, buffer);
			Canny(dXNeg, dY, canny, getPropertyValue<double>("Threshold low"), getPropertyValue<double>("Threshold high"), buffer);
			timeFlag("Apply Canny operator");
		
			/////////////////
			// Publish resulting images
			setPropertyValue< QVImage<uChar,1> >("Canny image",canny);
			timeFlag("Publish resulting images");
			}
	};


class ContourPainter: public QVProcessingBlock
	{
	public:
		ContourPainter(QString name): QVProcessingBlock(name)
			{
			addProperty< QVImage<uChar,1> >("Borders image", inputFlag|outputFlag);
			addProperty< QVImage<uChar,1> >("Flat colors image", inputFlag|outputFlag);
			addProperty< QVImage<uChar,1> >("Output image", outputFlag);
			}

		void iterate()
			{
			//////////////////
			// Read parameters
			QVImage<uChar> bordersImage = getPropertyValue< QVImage<uChar,1> >("Borders image");
			QVImage<uChar> flatColorsImage = getPropertyValue< QVImage<uChar,1> >("Flat colors image");
			uInt	rows = bordersImage.getRows(), cols = bordersImage.getCols();
			timeFlag("Read parameters");
		
			//////////////////
			// Paint contours		
			for(uInt col = 0; col < cols; col++)
				for (uInt row = 0; row < rows; row++)
					if (bordersImage(col, row))
						flatColorsImage(col, row) = 0;

			/////////////////
			// Publish resulting images
			setPropertyValue< QVImage<uChar,1> >("Output image", flatColorsImage);
			timeFlag("Publish resulting images");
			}
	};

int main(int argc, char *argv[])
	{
	QVApplication app(argc, argv,
		"Composes component tree image filtering and canny operator for making animation like images from real images."
		);
	
	ComponentTreeBlock componentTreeBlock("Component Tree");
	CannyBlock cannyBlock("Canny operator");
	ContourPainter contourPainter("Contour painter");

	componentTreeBlock.linkProperty("Pruned component tree image", &cannyBlock, "Input image", QVProcessingBlock::SynchronousLink);
	componentTreeBlock.linkProperty("Pruned component tree image", &contourPainter, "Flat colors image", QVProcessingBlock::SynchronousLink);

	cannyBlock.linkProperty("Canny image", &contourPainter, "Borders image", QVProcessingBlock::SynchronousLink);

	QVVideoReaderBlock camera("Video");
	camera.linkProperty(&componentTreeBlock,"Input image");

	QVDefaultGUI interface;

	QVImageCanvas imageCanvas("Rotoscoped image");
	contourPainter.linkProperty("Output image", imageCanvas);

	return app.exec();
	}

#endif

