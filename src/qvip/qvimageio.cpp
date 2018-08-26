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

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <iostream>

#include <qvip.h>
#include <qvmath.h>
#include <qvdefines.h>
//#include <qvmatrixalgebra.h>
#include <QVPolyline>
#include <QVPolylineF>
#include <QList>

#ifdef QVIPP
#include <qvipp.h>
#endif

template<int Channels> void writeUCharImageToFile(QFile &file, const QVImage<uChar, Channels> &image)
	{
	for (uInt i = 0; i < image.getRows(); i++)
		file.write((char *) image.getReadData() + i*image.getStep(), Channels * image.getCols());
	}

bool writeYUV4MPEG2Header(QFile &file, const int cols, const int rows, const int fps)
	{
	file.write(QString("YUV4MPEG2 W%1 H%2 F%3:1 Ip A0:0\x0a").arg(cols).arg(rows).arg(fps).toAscii());

	return true;
	}

bool writeYUV4MPEG2Frame(QFile &file, const QVImage<uChar,1> imageY, const QVImage<uChar,1> imageU, const QVImage<uChar,1> imageV)
	{
	// Write 'FRAME' keyword.
	file.write(QString("FRAME\x0a").toAscii());

	// Write image data buffers
	writeUCharImageToFile<1>(file, imageY);
	writeUCharImageToFile<1>(file, imageU);
	writeUCharImageToFile<1>(file, imageV);

	file.flush();

	return true;
	}

bool writeYUV4MPEG2Frame(QFile &file, const QVImage<uChar,1> imageGray)
	{
	const int cols = imageGray.getCols(), rows = imageGray.getRows();
	QVImage<uChar, 1> imageU(cols/2, rows/2);
	QVImage<uChar, 1> imageV(cols/2, rows/2);
	Set(128, imageU);
	Set(128, imageV);

	return writeYUV4MPEG2Frame(file, imageGray, imageU, imageV);
	}

#ifdef QVIPP
bool writeYUV4MPEG2Frame(QFile &file, const QVImage<uChar,3> imageRGB)
	{
	const int cols = imageRGB.getCols(), rows = imageRGB.getRows();
	QVImage<uChar, 1> imageY(cols, rows);
	QVImage<uChar, 1> imageU(cols/2, rows/2);
	QVImage<uChar, 1> imageV(cols/2, rows/2);

	RGBToYUV420(imageRGB, imageY, imageU, imageV);

	return writeYUV4MPEG2Frame(file, imageY, imageU, imageV);
	}
#endif

bool writeQVImageToFile(const QString fileName, const QVImage<uChar, 3> &image)
	{ return ((QImage) image).save(fileName); }

bool readQVImageFromFile(const QString fileName, QVImage<uChar, 3> &image)
	{
	QImage qimg;

	if(not qimg.load(fileName)) return FALSE;
	
	image = QVImage<uChar, 3>(qimg);

	return TRUE;
	}


//////////////////////////////////////////////////////////////////

bool readToBuffer(QFile &file, QVImage<uChar, 1> &image)
	{
	bool finished = false;
	uChar *buf_img_aux = image.getWriteData();

	int nbytes=0;
	for(unsigned int i=0;i<image.getRows();i++)
		{
		nbytes = file.read((char *)(buf_img_aux), image.getCols());

		if(nbytes==0 or nbytes==-1)
			{
			finished = TRUE;
			break;
			}		
		buf_img_aux += image.getStep();
		}

	return !finished;
	}

#include <QStringList>
#include <QRegExp>

bool readYUV4MPEG2Header(QFile &file, int &cols, int &rows, int &fps)
	{
	const QString readedLine = file.readLine();

	if (readedLine == NULL || readedLine == QString("MPLAYER ERROR\n"))
		{
		return false;
		}

	QRegExp rx;
	QStringList widthTokens;

	// Parse for special identifier
	rx.setPattern("YUV4MPEG2");
	if (rx.indexIn(readedLine) == -1)
		return false;

	// Parse for width (cols)
	rx.setPattern("(W)([0-9]+)");
	if (rx.indexIn(readedLine) == -1)
		return false;
	widthTokens = rx.capturedTexts();
	cols = widthTokens.at(2).toInt();

	// Parse for height (rows)
	rx.setPattern("(H)([0-9]+)");
	if (rx.indexIn(readedLine) == -1)
		return false;
	widthTokens = rx.capturedTexts();
	rows = widthTokens.at(2).toInt();

	// Parse for fps
	rx.setPattern("(F)([0-9]+):([0-9]+)");
	if (rx.indexIn(readedLine) == -1)
		return false;
	widthTokens = rx.capturedTexts();
	fps = widthTokens.at(2).toInt() / widthTokens.at(3).toInt();

	return true;
	}

bool readYUV4MPEG2Frame(QFile &file, QVImage<uChar> &imageY, QVImage<uChar> &imageU, QVImage<uChar> &imageV)
	{
	const QString yuv4mpeg2header = file.readLine();

	if (	readToBuffer(file, imageY)	&&
		readToBuffer(file, imageU)	&&
		readToBuffer(file, imageV)	)
		return true;
	else
		return false;
	}
