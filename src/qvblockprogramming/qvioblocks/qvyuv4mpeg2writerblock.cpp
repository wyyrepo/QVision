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

#include <QVYUV4MPEG2WriterBlock>
#include <qvimageio.h>

#ifdef QVIPP
#include <qvipp.h>
#endif

QVYUV4MPEG2WriterBlock::~QVYUV4MPEG2WriterBlock()
	{
	videoFile.close();
	}

QVYUV4MPEG2WriterBlock::QVYUV4MPEG2WriterBlock(QString name, const QString fileName, const int fps, const bool recording): QVProcessingBlock(name),
	initiated(false), rgbMode(true), recording(recording)
	{
	addProperty<int>("FPS", inputFlag, fps);
	addProperty<bool>("RealTime", inputFlag, FALSE, "If the recorder should work in real time mode");
	realTimeMode = getPropertyValue<bool>("RealTime");

	#ifdef QVIPP
	addProperty< QVImage<uChar,3> >("Input image RGB", inputFlag|outputFlag);
	#endif

	addProperty< QVImage<uChar,1> >("Input image Y", inputFlag|outputFlag);

	addTrigger("Start recording");
	addTrigger("Pause recording");
	addTrigger("Grab single frame");

	addProperty< QString >("File", inputFlag, fileName);

	// If the camera is in real time mode, set minimum delay sleep between iterations regarding the fps.
	if (realTimeMode)
		setMinimumDelay((int)(1000/(double) getPropertyValue<int>("FPS")));
	}
 
void QVYUV4MPEG2WriterBlock::processTrigger(QString name)
	{
	if (name == "Start recording")
		recording = true;
	else if (name == "Pause recording")
		recording = false;
	else if (name == "Grab single frame" && recording == false)
		grabFrame();
	}

bool QVYUV4MPEG2WriterBlock::linkUnspecifiedInputProperty(QVPropertyContainer *sourceContainer, QString sourceProperty, LinkType linkType)
	{
	LinkType actualLinkType = linkType;

	// Select actual linking type, regarding if the recorder is opened in real time mode.
	if (!realTimeMode && actualLinkType == AsynchronousLink)
		{
		std::cout << "Warning @ QVYUV4MPEG2WriterBlock: tried to establish an asynchronous link to a not real time recorder." << std::endl;
		actualLinkType = SynchronousLink;
		}
	else if (realTimeMode && actualLinkType == SynchronousLink)
		{
		std::cout << "Warning @ QVYUV4MPEG2WriterBlock: tried to establish a synchronous link to a real time recorder." << std::endl;
		actualLinkType = AsynchronousLink;
		}

	// Link the source image property, depending on the channel number
	if (sourceContainer->isType< QVImage<uChar, 1> >(sourceProperty))
		{
		rgbMode = false;
		return sourceContainer->linkProperty(sourceProperty, this, "Input image Y", linkType);
		}
	#ifdef QVIPP
	else if (sourceContainer->isType< QVImage<uChar, 3> >(sourceProperty))
		{
		rgbMode = true;
		return sourceContainer->linkProperty(sourceProperty, this, "Input image RGB", linkType);
		}
	#endif

	std::cout << "QVYUV4MPEG2WriterBlock::linkProperty(): error, can't link property " << qPrintable(sourceProperty) << "." << std::endl;
	return false;
	}

void QVYUV4MPEG2WriterBlock::iterate()
	{
	if (!recording)
		return;
	grabFrame();
	}

void QVYUV4MPEG2WriterBlock::grabFrame()
	{
	if (!initiated)
		{
		if (not rgbMode)
			{
			const QVImage<uChar, 1> imageY = getPropertyValue< QVImage<uChar, 1> >("Input image Y");
			cols = imageY.getCols();
			rows = imageY.getRows();
			}
		#ifdef QVIPP
		else	{
			const QVImage<uChar, 3> imageRGB = getPropertyValue< QVImage<uChar, 3> >("Input image RGB");
			cols = imageRGB.getCols();
			rows = imageRGB.getRows();
			}
		#endif

		if (cols > 1 && rows > 1)
			{
			videoFile.setFileName(getPropertyValue<QString>("File"));
			videoFile.open(QIODevice::WriteOnly|QIODevice::Truncate);
			writeYUV4MPEG2Header(videoFile, cols, rows, getPropertyValue<int>("FPS"));
			initiated = true;
			}
		}

	if (not rgbMode)
		{
		const QVImage<uChar, 1> imageY = getPropertyValue< QVImage<uChar, 1> >("Input image Y");

		if (imageY.getCols() > cols)
			std::cout	<< "QVYUV4MPEG2WriterBlock::grabFrame(): image has " << imageY.getCols()
					<< ", but video file is set to " << cols << " columns." << std::endl;
		if (imageY.getRows() > rows)
			std::cout	<< "QVYUV4MPEG2WriterBlock::grabFrame(): image has " << imageY.getRows()
					<< ", but video file is set to " << rows << " rows." << std::endl;

		QVImage<uChar, 1> storedImageY(cols, rows);

		Set(0, storedImageY);
		#ifdef QVIPP
		Copy(imageY, storedImageY);
		#else
		storedImageY = imageY;
		#endif

		writeYUV4MPEG2Frame(videoFile, imageY);
		}
	#ifdef QVIPP
	else	{
		const QVImage<uChar, 3> imageRGB = getPropertyValue< QVImage<uChar, 3> >("Input image RGB");

		if (imageRGB.getCols() > cols)
			std::cout	<< "QVYUV4MPEG2WriterBlock::grabFrame(): image has " << imageRGB.getCols()
					<< ", but video file is set to " << cols << " columns." << std::endl;
		if (imageRGB.getRows() > rows)
			std::cout	<< "QVYUV4MPEG2WriterBlock::grabFrame(): image has " << imageRGB.getRows()
					<< ", but video file is set to " << rows << " rows." << std::endl;

		QVImage<uChar, 3> storedImage(cols, rows);
		const uChar zero[3] = {0,0,0};

		Set(zero, storedImage);
		Copy(imageRGB, storedImage);

		writeYUV4MPEG2Frame(videoFile, storedImage);
		}
	#endif

	}
