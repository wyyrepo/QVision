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

#ifndef QVYUV4MPEG2RECORDER_H
#define QVYUV4MPEG2RECORDER_H

#include <QVProcessingBlock>
#include <QVImage>
#include <QFile>

/*!
@class QVYUV4MPEG2WriterBlock qvblockprogramming/qvioblocks/qvyuv4mpeg2writerblock.h QVYUV4MPEG2WriterBlock
@brief Video source class for reading many video file formats, webcams and digital cameras.

This block can be linked to a block object producing an output image, to store the flow of images in a video file in the uncompressed YUV4MPEG2 format.

To use it, create a QVYUV4MPEG2WriterBlock object in the <i>main function</i>, and link a RGB image from a block, to store each output image from the block in a video file.

@code
int main(int argc, char *argv[])
	{
	[...]
	// The following block should have a property named 'Output image' containing an RGB image.
	MyBlock myBlock("My block");
	[...]
	QVYUV4MPEG2WriterBlock recorder("Video recorder");
	player.linkProperty("Output image", recorder);
	[...]
	}
@endcode

You can tune the number of frames per second and the name of the file to store the video through the user command line, setting values for the properties <i>FPS</i> and <i>Record file name</i> in the video record object.

Once the object reads the first image frame changing those values will have no effect.

@ingroup qvblockprogramming
*/
class QVYUV4MPEG2WriterBlock: public QVProcessingBlock
	{
	public:
		QVYUV4MPEG2WriterBlock(QString name, const QString fileName = "pru.mpg", const int fps = 25, const bool recording = true);

		~QVYUV4MPEG2WriterBlock();

		bool linkUnspecifiedInputProperty(QVPropertyContainer *srcCont, QString srcProp, LinkType linkType);

		void iterate();

	public slots:
		void processTrigger(QString name);

	private:
		bool initiated, rgbMode, recording, realTimeMode;
		QFile videoFile;
		uint cols, rows;

		void grabFrame();
	};

#endif
