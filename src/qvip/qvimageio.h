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

#ifndef QVIMAGEIO_H
#define QVIMAGEIO_H

#include <iostream>

#include <qvdefines.h>
#include <QVImage>
#include <QVPolyline>

#include <QVImage>
#include <QFile>

/*!
@brief Create a yuv4mpeg2 video file.

This function stores the header for a video sequence in YUV4MPEG2 format in a newly created file.
It can be used in conjunction with any of the versions of the @ref writeYUV4MPEG2Frame functions to store
a flow of images in a video file.

See section @ref WriteYUV4MPEGVideoFiles for further info about the usage of this function.

@param file The input file object. It must be already opened when received as argument by this function.
@param cols The number of columns that the video in the file should have.
@param rows The number of rows that the video in the file should have.
@param fps The number of frames per second that the video sequence will have.
@see writeYUV4MPEG2Frame(QFile &, const QVImage<uChar,1>, const QVImage<uChar,1>, const QVImage<uChar,1>);
@see writeYUV4MPEG2Frame(QFile &, const QVImage<uChar,3>);
@ingroup qvip
*/
bool writeYUV4MPEG2Header(QFile &file, const int cols, const int rows, const int fps);

/*!
@brief Write YUV image frames to a yuv4mpeg2 video file.

This function stores a YUV frame in a YUV4MPEG2 video file.
The parameters of this function must be three images containing the three channels for the YUV image.
For further information about its usage, see documentation for function @ref writeYUV4MPEG2Header.

See section @ref WriteYUV4MPEGVideoFiles for further info about the usage of this function.

@param file The input file object. It must be already opened when received as argument by this function.
@param imageY Image object containing the Y channel for the YUV image, to store in the video file.
@param imageU Image object containing the Y channel for the YUV image, to store in the video file.
@param imageV Image object containing the Y channel for the YUV image, to store in the video file.
@see writeYUV4MPEG2Header
@ingroup qvip
*/
bool writeYUV4MPEG2Frame(QFile &file, const QVImage<uChar,1> imageY, const QVImage<uChar,1> imageU, const QVImage<uChar,1> imageV);

/*!
@brief Write YUV image frames to a yuv4mpeg2 video file.

This function stores a gray scale frame in a YUV4MPEG2 video file.
The parameter of this function is a single 1-channel image, containing the gray scale image.
For further information about its usage, see documentation for function @ref writeYUV4MPEG2Header.

See section @ref WriteYUV4MPEGVideoFiles for further info about the usage of this function.

@param file The input file object. It must be already opened when received as argument by this function.
@param imageGray Gray scale image to store in the video file.
@see writeYUV4MPEG2Header
@ingroup qvip
*/
bool writeYUV4MPEG2Frame(QFile &file, const QVImage<uChar,1> imageGray);

/*!
@brief Write RGB image frames to a yuv4mpeg2 video file.

This is an overloaded version of the function  @ref writeYUV4MPEG2Frame(QFile &, const QVImage<uChar,3>) provided for convenience.
This version stores a RGB frame in a YUV4MPEG2 video file.
The parameter of this function is a single 3-channel image containing the RGB image.
For further information about its usage, see documentation for function @ref writeYUV4MPEG2Header.

See section @ref WriteYUV4MPEGVideoFiles for further info about the usage of this function.

@note This function is based on functionality from the Intel IPP library. Thus compatibility
with that library must be enabled to be available.

@param file The input file object. It must be already opened when received as argument by this function.
@param imageRGB RGB image object, to store in the video file.
@see writeYUV4MPEG2Header
@ingroup qvip
*/
#ifdef QVIPP
bool writeYUV4MPEG2Frame(QFile &file, const QVImage<uChar,3> imageRGB);
#endif

/*!
@brief Write the content of a QVImage (RGB) object in an image file

@param fileName The name of the image file to create. It is overwritten if already exists.
                File format is inferred from fileName suffix. Supported formats:
                BMP,JPG,PNG,PPM,TIFF,XBM,XPM.
@param image The image to store in the file.
@returns TRUE if success, FALSE otherwise.
@ingroup qvip
*/
bool writeQVImageToFile(const QString fileName, const QVImage<uChar, 3> &image);

/*!
@brief Reads the content of a QVImage (RGB) object from an image file

@param fileName The name of the image file to read from. File format is inferred from fileName suffix.
                Supported formats: BMP,JPG,PNG,PPM,TIFF,XBM,XPM,GIF,PBM,PGM.
@param image The image to store in the file.
@returns TRUE if success, FALSE otherwise.
@ingroup qvip
*/
bool readQVImageFromFile(const QString fileName, QVImage<uChar, 3> &image);

/*!
@brief Read YUV image frames from a yuv4mpeg2 video file.

This function retrieves a frame from a video file coded in YUV format. The parameters of this function must be three images to store the three channels for the YUV image.

See section @ref ReadingYUV4MPEGVideoFiles for further info about the usage of this function.

@param file The input file object. It must be already opened when received as argument by this function.
@param imageY Image object to contain the Y channel for the YUV image, to store in the video file.
@param imageU Image object to contain the U channel for the YUV image, to store in the video file.
@param imageV Image object to contain the V channel for the YUV image, to store in the video file.
@see readYUV4MPEG2Header
@ingroup qvip
*/
bool readYUV4MPEG2Frame(QFile &file, QVImage<uChar> &imageY, QVImage<uChar> &imageU, QVImage<uChar> &imageV);

/*!
@brief Read yuv4mpeg2 header from a video file.

This function reads the header of a video file encoded in yuv4mpeg2 format. This header contains information about the size of the frames in the video file, as well as the number of frames per second of the video sequence.

See section @ref ReadingYUV4MPEGVideoFiles for further info about the usage of this function.

@param file The input file object. It must be already opened when received as argument by this function.
@param cols (output parameter) Number of cols read in the header
@param rows (output parameter) Number of rows read in the header
@param fps (output parameter) Video fps read in the header
@see readYUV4MPEG2Frame
@ingroup qvip
*/
bool readYUV4MPEG2Header(QFile &file, int &cols, int &rows, int &fps);

#endif

