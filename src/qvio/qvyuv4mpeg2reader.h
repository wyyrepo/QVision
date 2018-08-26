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

#ifndef QVYUV4MPEG2READER_H
#define QVYUV4MPEG2READER_H

#include <QFile>

#include <QVBaseReader>

class QVYUV4MPEG2Reader : public QVBaseReader
    {
    public:
        QVYUV4MPEG2Reader() : QVBaseReader() { };

        ~QVYUV4MPEG2Reader() { };

    private:
        QFile videoFile;
        int cols,rows,fps;
        bool noLoop,realTime;
        int header_size;

    protected:
        bool open(const QString & url_string,
                  unsigned int & suggested_cols, unsigned int & suggested_rows,
                  unsigned int & suggested_fps, QVVideoReader::OpenOptions & suggested_opts,
                  QVVideoReader::TSourceMode & source_mode);
        bool close();
        bool grab(QVImage<uChar,1> &imgY, QVImage<uChar,1> &imgU, QVImage<uChar,1> &imgV);
        int getLength();
        int getPos();
        bool seek(int pos);
    };
#endif // QVYUV4MPEG2READER_H
