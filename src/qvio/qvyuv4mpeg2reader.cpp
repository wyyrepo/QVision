/*
 *   Copyright (C) 2007, 2008, 2009, 2010, 2011, 2012. PARP Research Group.
 *   <http://perception.inf.um.es>
 *   University of Murcia, Spain.
 *
 *   This file is part of the QVision library.
 *
 *   QVision is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as
 *   published by the Free Software Foundation, version 3 of the License.
 *
 *   QVision is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with QVision. If not, see <http://www.gnu.org/licenses/>.
 */

/// @file qvyuv4mpeg2reader.h
/// @brief Implementation of uncompressed yuv2mpeg files video source reader.
/// @author PARP Research Group. University of Murcia, Spain.

#include <QString>
#include <QUrl>
#include <QTime>

#include <qvimageio.h>

#ifdef QVIPP
#include <qvipp.h>
#endif // QVIPP

#include <QVYUV4MPEG2Reader>

bool QVYUV4MPEG2Reader::open(const QString & url_string,
                              unsigned int & suggested_cols, unsigned int & suggested_rows,
                              unsigned int & suggested_fps, QVVideoReader::OpenOptions & suggested_options,
                              QVVideoReader::TSourceMode & source_mode)
    {
    // Preferred mode: YUV
    source_mode = QVVideoReader::YUVMode;

    // File name:
    QUrl URL(url_string);
    QString fileName = URL.path();

    // noLoop & realTime flags:
    noLoop = (suggested_options & QVVideoReader::NoLoop);
    realTime = (suggested_options & QVVideoReader::RealTime);

    // Try to open file, and read yuv4mpeg2 header.
    videoFile.setFileName(fileName);
    if (!videoFile.exists())
        {
        QString msg = QString("QVYUV4MPEG2Reader::open: File '") + fileName + "' doesn't seem to exist." ;
        qWarning() << msg;
        return FALSE;
        }
    else if (!videoFile.open(QIODevice::ReadOnly))
        {
        QString msg = QString("QVYUV4MPEG2Reader::open: Can't open file '") + fileName + "' in read mode." ;
        qWarning() << msg;
        return FALSE;
        }
    else if (!readYUV4MPEG2Header(videoFile, cols, rows, fps))
        {
        QString msg = QString("QVYUV4MPEG2Reader::open: File '") + fileName + "' doesn't seem to be a valid yuv4mpeg2 video file.";
        qWarning() << msg;
        return FALSE;
        }
    else // Everything correct.
        {
        // By default, ignore input video fps, and force user value (unless realTime option flag is ON):
        if(realTime) {
            suggested_fps = fps;
        }

        // Size of the header:
        header_size = videoFile.pos();

        // Output cols and rows. Even rounding of out_rows and out_cols:
        // cols = cols + (cols%2);
        // rows = rows + (rows%2);

        // Finally, output cols and rows are "returned" to the caller:
        suggested_cols = cols;
        suggested_rows = rows;

        return TRUE;
        }
    }

bool QVYUV4MPEG2Reader::close()
    {
    videoFile.close();
    return TRUE;
    }

bool QVYUV4MPEG2Reader::grab(QVImage<uChar,1> &imgY, QVImage<uChar,1> &imgU, QVImage<uChar,1> &imgV)
    {
    QVImage<uChar,1> inp_imgY(cols,rows), inp_imgU(cols/2,rows/2), inp_imgV(cols/2,rows/2);
    bool ret_value = FALSE;

    if (readYUV4MPEG2Frame(videoFile, inp_imgY, inp_imgU, inp_imgV))
        {
        ret_value = TRUE;
        }
    else if (videoFile.atEnd())
        {
        if (noLoop)
            return FALSE;
        else
            {
            // qDebug() << "QVYUV4MPEG2Reader::grabFrame(): Reseting the video at frame " << total_frames;
            videoFile.reset();
            readYUV4MPEG2Frame(videoFile, inp_imgY, inp_imgU, inp_imgV);
            ret_value = TRUE;
            }
        }
    else   {
        qFatal("QVYUV4MPEG2Reader::grab(): readYUV4MPEG2Frame() returned FALSE, and videoFile is not at end... aborting\n");
        }

    imgY = inp_imgY;
    imgU = inp_imgU;
    imgV = inp_imgV;

    return ret_value;
    }

int QVYUV4MPEG2Reader::getLength()
    {
    return (videoFile.size()-header_size)/(cols*rows + cols*rows/2 + 6);
    }

int QVYUV4MPEG2Reader::getPos()
    {
    return (videoFile.pos()-header_size)/(cols*rows + cols*rows/2 + 6);
    }

bool QVYUV4MPEG2Reader::seek(int pos)
    {
    videoFile.seek(header_size+pos*(cols*rows + cols*rows/2 + 6));
    return TRUE;
    }
