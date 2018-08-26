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

/// @file qvdirreader.cpp
/// @brief Implementation of (images in a) directory video source reader.
/// @author PARP Research Group. University of Murcia, Spain.

#include <QVDirReader>

#include <QUrl>

#ifdef QVIPP
#include <qvipp.h>
#endif // QVIPP

bool QVDirReader:: open(const QString & url_string,
                         unsigned int & suggested_cols, unsigned int & suggested_rows,
                         unsigned int & suggested_fps, QVVideoReader::OpenOptions & suggested_options,
                         QVVideoReader::TSourceMode & source_mode)
{

        // Preferred mode: RGB
        source_mode = QVVideoReader::RGBMode;

        ended = false;

        // Treat both isolated directory names and path to files (with possible wildcards):
        QString dir_string = url_string;
        dir_string.remove("dir://");
        QStringList filters;
        QFileInfo info(dir_string);
        if(info.isDir()) { // Will read every image file in specified dir:
            dir = QDir(dir_string);
            filters << "*.jpg" << "*.png" << "*.bmp" << "*.pgm" << "*.gif" << "*.jpeg" << "*.pbm" << "*.ppm"
                    << "*.tiff" << "*.xbm" << "*.xpm";
        } else { // Will read only selected files (i.e. using wildcards) in specified dir:
            QString path = info.path(), files = info.fileName();
            QFileInfo info(path);
            if(not info.isDir())
                return false;
            dir = QDir(path);
            filters << files;
        }
        dir.setNameFilters(filters);
        dir.setSorting(QDir::Name);
        filenames = dir.entryList();

        if(filenames.isEmpty())
            return false;

        // NoLoop & realTime flags:
        noLoop = (suggested_options & QVVideoReader::NoLoop);
        realTime = (suggested_options & QVVideoReader::RealTime);

        if(realTime)
            suggested_fps = 25;

        // std::cout << qPrintable(dir.absolutePath()) << "\n";

        // Will not rescale, answer size (0,0)
        suggested_cols = suggested_rows = 0;

        if(filenames.size() > 0) {
            index = 0;
            return true;
        } else
            return false;
}

bool QVDirReader::close()
{
    return true;
}

bool QVDirReader::grab(QVImage<uChar,1> &imgR, QVImage<uChar,1> &imgG, QVImage<uChar,1> &imgB)
{
        if(ended)
            return false;

        QString fullpathtofile = dir.absolutePath() + "/" + filenames.at(index);

        //std::cout << "QVDirReader::grab: Read file " << qPrintable(fullpathtofile) << "\n";

        QVImage<uchar,3> ColorImage(fullpathtofile);

        /* Not needed yet (all resizing in qvvideoreader.cpp):
        if((cols_out != 0 and rows_out !=0) || (ColorImage.getRows()%2==1) || (ColorImage.getCols()%2==1)) {
            QVImage<uchar,3> InterImage;
            if(cols_out == 0 || rows_out == 0)
                InterImage.resize(ColorImage.getCols() & 0xfffffffe,ColorImage.getRows() & 0xfffffffe);
            else
                InterImage.resize(cols_out,rows_out);
            InterImage.resetROI();
            Resize(ColorImage,InterImage);
            ColorImage = InterImage;
        }*/

        imgR = QVImage<uChar>(ColorImage.getCols(),ColorImage.getRows());
        imgG = QVImage<uChar>(ColorImage.getCols(),ColorImage.getRows());
        imgB = QVImage<uChar>(ColorImage.getCols(),ColorImage.getRows());
        Copy(ColorImage,0,imgR);
        Copy(ColorImage,1,imgG);
        Copy(ColorImage,2,imgB);

        index = index + 1;
        if(index == filenames.size()) {
            if(noLoop) {
                ended = true;
                return false;
            } else
                index = 0;
        }
        return true;
}

int QVDirReader::getLength()
{
    return static_cast<double>(filenames.size());
}

int QVDirReader::getPos()
{
    return static_cast<double>(index);
}

bool QVDirReader::seek(int pos)
{
    index = pos;
    return true;
}
