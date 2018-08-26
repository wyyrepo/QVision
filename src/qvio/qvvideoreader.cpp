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

/// @file qvvideoreader.cpp
/// @brief Multisource video input implementation class in QVision.
/// @author PARP Research Group. University of Murcia, Spain.


#include <QUrl>
#include <QFile>
#include <QDir>
#include <QThread>
#include <QTime>

#ifdef QVIPP
#include <qvipp.h>
#endif // QVIPP

#include <QVImage>
#include <QVVideoReader>

#ifdef QVMPLAYER
#include <QVMPlayerReader>
#endif // QVMPLAYER

#ifdef QVOPENCV
#include <QVOpenCVReader>
#endif // QVOPENCV

#include <QVYUV4MPEG2Reader>
#include <QVDirReader>

// Auxiliary class and function for simulating a given delay (in msecs) between successive frames.
class SleeperThread : public QThread
{
public:
    static void msleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
};

void simulateDelay(int fps)
{
    static QTime last_time;

    int msecs_to_wait = (int)(1000/(double)fps) - last_time.elapsed();

    // std::cout << "last_time.elapsed()=" << last_time.elapsed() << "\n";
    // std::cout << "(int)(1000/(double)fps)=" << (int)(1000/(double)fps) << "\n";
    // std::cout << "msecs_to_wait =" << msecs_to_wait  << "\n";

    if((msecs_to_wait > 0) and (msecs_to_wait < (int)(1000/(double)fps)))
        SleeperThread::msleep(msecs_to_wait);

    last_time.start();
}

QVVideoReader::QVVideoReader():
    url(QString()), scheme(QString()),changing_size(false),cols(0), rows(0), fps(0), frames_grabbed(0),
    camera_opened(FALSE), live_camera(FALSE), end_of_video(FALSE),
    availableGray(false), availableRGB3(false), availableYUV(false), availableRGB(false),
    imgGray(QVImage<uChar>()), imgRGB(QVImage<uChar,3>()),
    imgY(QVImage<uChar>()), imgU(QVImage<uChar>()), imgV(QVImage<uChar>()),
    imgR(QVImage<uChar>()), imgG(QVImage<uChar>()), imgB(QVImage<uChar>()),
    open_options(QVVideoReader::Default), source_mode(QVVideoReader::YUVMode), base_reader(0)
    {
    };

QVVideoReader::~QVVideoReader()
    {
    if (camera_opened)
        close();

    if (base_reader != 0)
        delete base_reader;
    }


bool QVVideoReader::open(const QString & url_string, unsigned int & suggested_cols,
                         unsigned int & suggested_rows , unsigned int & suggested_fps,
                         QVVideoReader::OpenOptions & suggested_opts,
                         QVVideoReader::TSourceMode & suggested_source_mode)
    {
    if (base_reader != 0)
        delete base_reader;

    // Here we infer from the url the type of the base reader to read from:

    // First infer possible default schemes:
    QUrl URL(url_string);
    bool modify_url = true;
    QString mod_url_string;
    scheme = URL.scheme();
    if (scheme != "") {
        // scheme specified by the user
        modify_url = false;
    } else if (url_string.startsWith("/dev/video")) {
        // a v4l device
        scheme = "v4l2";
    } else if (url_string.startsWith("/dev/dv")) {
        // a dv device
        scheme = "dv";
    } else if (url_string.contains("*")) {
        // a multifile
        scheme = "dir";
    } else if (url_string.startsWith("www.")) {
        // a http file
        scheme = "http";
    } else if (url_string.startsWith("ftp.")) {
        // a ftp file
        scheme = "ftp";
        } else if (url_string.startsWith("#")) {
        // an OpenCV camera number
        scheme = "cvc";
    } else if (QDir(url_string).exists()) {
        // a local directory
        scheme = "dir";
    } else if (QFile::exists(url_string)) {
        // a local file
        if (url_string.endsWith(".yuv")) {
            // a yuv file
            scheme = "yuv4mpeg";
        } else if (url_string.endsWith(".jpg") or url_string.endsWith(".png") or url_string.endsWith(".bmp") or
                   url_string.endsWith(".pgm") or url_string.endsWith(".gif") or url_string.endsWith(".jpeg") or
                   url_string.endsWith(".pbm") or url_string.endsWith(".ppm") or url_string.endsWith(".tiff") or
                   url_string.endsWith(".xbm") or url_string.endsWith(".xpm") ) {
            // an image file
            scheme = "dir";
        } else {
            // possibly another types of video files
            scheme = "file";
        }
    } else {
        std::cout << "QVVideoReader::open(): Error: do not know how to open URL " << qPrintable (url_string) << std::endl;
        goto end_with_fail;
    }

    if(modify_url)
        mod_url_string = scheme + QString("://") + url_string;
    else
        mod_url_string = url_string;

    // std::cout << "USING URL=" << qPrintable (mod_url_string) << "\n";

    // Now treat here each scheme accordingly:
    if (scheme == "dir")
        {
        base_reader = new QVDirReader();
        live_camera = false;
        }
    else if (scheme == "yuv4mpeg")
        {
        base_reader = new QVYUV4MPEG2Reader();
        live_camera = false;
        }
   #ifdef QVMPLAYER
   else if(scheme == "file")
        {
        base_reader = new QVMPlayerReader();
        live_camera = false;
        }
    else if (scheme == "v4l2")
        {
        base_reader = new QVMPlayerReader();
        live_camera = true;
        }
    else if (scheme == "dvb")
        {
        base_reader = new QVMPlayerReader();
        live_camera = true;
        }
    else if (scheme == "rtsp")
        {
        base_reader = new QVMPlayerReader();
        live_camera = false;
        }
    else if (scheme == "http")
        {
        base_reader = new QVMPlayerReader();
        live_camera = false;
        }
    else if (scheme == "ftp")
        {
        base_reader = new QVMPlayerReader();
        live_camera = false;
        }
    else if (scheme == "dvd")
        {
        base_reader = new QVMPlayerReader();
        live_camera = false;
        }
    else if (scheme == "vcd")
        {
        base_reader = new QVMPlayerReader();
        live_camera = false;
        }
    else if (scheme == "mf")
        {
        base_reader = new QVMPlayerReader();
        live_camera = false;
        }
    #else
    else if (	(scheme == "file") or
                (scheme == "v4l2") or
                (scheme == "dvb") or
                (scheme == "rtsp") or
                (scheme == "http") or
                (scheme == "ftp") or
                (scheme == "dvd") or
                (scheme == "vcd") or
                (scheme == "mf") )
        {
        std::cout << "QVVideoReader::open(): Error: tried to open video with MPlayer, while QVision was not configured to use it. See file 'config.pri'." << std::endl;
        goto end_with_fail;
        }
    #endif // QVMPLAYER
    #ifdef QVOPENCV
    else if (scheme == "cvf")
        {
        base_reader = new QVOpenCVReader();
        live_camera = false;
        }
    else if (scheme == "cvc")
        {
        base_reader = new QVOpenCVReader();
        live_camera = true;
        }
    #else
    else if ( (scheme == "cvf") or (scheme == "cvc") )
        {
        std::cout << "QVVideoReader::open(): Error: tried to open video with OpenCV functionality, while QVision was not configured to use it. See file 'config.pri'." << std::endl;
        goto end_with_fail;
        }
    #endif // QVOPENCV

    cols = suggested_cols;
    rows = suggested_rows;

    if(base_reader != 0)
        {
        if(base_reader->open(mod_url_string,suggested_cols,suggested_rows,suggested_fps,
                         suggested_opts,suggested_source_mode))
            {
            url = mod_url_string;
            // scheme initialized before;

            // If input cols=0 or rows=0, set to default input values (as returned by corresponding open method):
            if ((cols == 0) or (rows == 0)) {
                cols = suggested_cols;
                rows = suggested_rows;
            }
            // Force even number of cols and rows (for possible YUV conversions, with U and V half-sized):
            cols = cols & 0xfffffffe;
            rows = rows & 0xfffffffe;
            changing_size = (cols == 0 or rows == 0);

            // std::cout << "suggested_cols = " << suggested_cols << "  suggested_rows = " << suggested_rows << "\n";
            // std::cout << "cols = " << cols << "  rows = " << rows << "\n";

            fps = suggested_fps;
            frames_grabbed = 0;
            camera_opened = true;
            // live_camera initialized before;
            end_of_video = false;
            availableGray = availableRGB3 = availableYUV = availableRGB = false;
            open_options = suggested_opts;
            source_mode = suggested_source_mode;
            // base_reader initialized before;
            emit sourceOpened();
            return true;
            }
        }
    else
        {
        std::cout << "Error:: do not know how to open " << qPrintable (mod_url_string) << " in QVVideoReader::open() method\n";
        }

end_with_fail:
    url = QString();
    scheme = QString();
    changing_size = false;
    cols = 0;
    rows = 0;
    fps = 0;
    frames_grabbed = 0;
    camera_opened = false;
    live_camera = false;
    end_of_video = true;
    availableGray = availableRGB3 = availableYUV = availableRGB = false;
    open_options = QVVideoReader::Default;
    source_mode = suggested_source_mode;
    delete base_reader;
    base_reader = 0;
    return false;
    }

bool QVVideoReader::grab()
    {
    availableGray = availableRGB3 = availableYUV = availableRGB = false;

    if(source_mode == QVVideoReader::GrayOnlyMode)
        {
        QVImage<uChar> imgDummy1,imgDummy2;
        if(base_reader->grab(imgGray, imgDummy1, imgDummy2))
            {
            availableGray = true;
            frames_grabbed++;
            emit newGrab();
            if(fps != 0) simulateDelay(fps);
            // Update cols and rows (as for some video sources this could change from frame to frame; i.e. when
            // reading image files from a directory). Force here even number of cols and rows too (for possible
            // YUV conversions, with U and V half-sized):
            if((imgGray.getCols()%2==1) or (imgGray.getRows()%2==1)) {
                QVImage<uChar> inter = QVImage<uChar>(imgGray.getCols() & 0xfffffffe,imgGray.getRows() & 0xfffffffe);
                Resize(imgGray,inter);
                imgGray = inter;
            }
            if(changing_size) {
                cols = imgGray.getCols();
                rows = imgGray.getRows();
            }
            return true;
            }
        else
            {
            end_of_video = true;
            if(fps != 0) simulateDelay(fps);
            return false;
            }
        }
    else if(source_mode == QVVideoReader::YUVMode)
        {
        if(base_reader->grab(imgY, imgU, imgV))
            {
            availableYUV = true;
            frames_grabbed++;
            emit newGrab();
            if(fps != 0) simulateDelay(fps);
            // Update cols and rows (as for some video sources this could change from frame to frame; i.e. when
            // reading image files from a directory). Force here even number of cols and rows too (for possible
            // YUV conversions, with U and V half-sized):
            if((imgY.getCols()%2==1) or (imgY.getRows()%2==1)) {
                QVImage<uChar> inter = QVImage<uChar>(imgY.getCols() & 0xfffffffe,imgY.getRows() & 0xfffffffe);
                Resize(imgY,inter);
                imgY = inter;
            }
            if(changing_size) {
                cols = imgY.getCols();
                rows = imgY.getRows();
            }
            if(imgU.getRows() != imgY.getRows()/2 or imgU.getCols() != imgY.getCols()/2 or
               imgV.getRows() != imgY.getRows()/2 or imgV.getCols() != imgY.getCols()/2 ) {
                std::cout << "ERROR in QVVideoReader::grab(): Y, U and U channels have not a correct size!\n";
                exit(1);
            }
            return true;
            }
        else
            {
            end_of_video = true;
            if(fps != 0) simulateDelay(fps);
            return false;
            }
        }
    else // source_mode == RGBMode
        {
        if(base_reader->grab(imgR, imgG, imgB))
            {
            availableRGB = true;
            frames_grabbed++;
            emit newGrab();
            if(fps != 0) simulateDelay(fps);
            // Update cols and rows (as for some video sources this could change from frame to frame; i.e. when
            // reading image files from a directory). Force here even number of cols and rows too (for possible
            // YUV conversions, with U and V half-sized):
            if((imgR.getCols()%2==1) or (imgR.getRows()%2==1)) {
                QVImage<uChar> inter = QVImage<uChar>(imgR.getCols() & 0xfffffffe,imgR.getRows() & 0xfffffffe);
                Resize(imgR,inter);
                imgR = inter;
                Resize(imgG,inter);
                imgG = inter;
                Resize(imgB,inter);
                imgB = inter;
            }
            if(changing_size) {
                cols = imgR.getCols();
                rows = imgR.getRows();
            }
            if(imgG.getRows() != imgR.getRows() or imgG.getCols() != imgR.getCols() or
               imgB.getRows() != imgR.getRows() or imgB.getCols() != imgR.getCols() ) {
                std::cout << "ERROR in QVVideoReader::grab(): R, G and B channels are not of the same size!\n";
                exit(1);
            }
            return true;
            }
        else
            {
            end_of_video = true;
            if(fps != 0) simulateDelay(fps);
            return false;
            }
        }
    }

void QVVideoReader::getGrayImage(QVImage<uChar> &imageGray)
    {
    if(not availableGray)
        {
        if(availableYUV) {
            imgGray = imgY;
            availableGray = true;
            }
        else if(availableRGB)
            {
            imgRGB = QVImage<uChar,3>(imgR,imgG,imgB);
            imgGray = QVImage<uChar>(imgRGB.getCols(),imgRGB.getRows());
            RGBToGray(imgRGB,imgGray);
            availableGray = true;
            availableRGB3 = true;
            }
        else if(availableRGB3)
            {
            imgGray = QVImage<uChar>(imgRGB.getCols(),imgRGB.getRows());
            RGBToGray(imgRGB,imgGray);
            availableGray = true;
            }
        }

    if( ( (imgGray.getRows() != rows) or (imgGray.getCols() != cols) ) )
        {
        imageGray = QVImage<uChar>(cols,rows);
        Resize(imgGray,imageGray);
        }
    else
        imageGray = imgGray;
    }

void QVVideoReader::getRGBImage(QVImage<uChar,3> & imageRGB)
    {
    if(not availableRGB3)
        {
        if(availableRGB)
            {
            imgRGB = QVImage<uChar,3>(imgR,imgG,imgB);
            availableRGB3 = true;
            }
        else if(availableYUV)
            {
            imgRGB = QVImage<uChar,3>(imgY.getCols(),imgY.getRows());
            YUV420ToRGB(imgY,imgU,imgV,imgRGB);
            availableRGB3 = true;
            }
        else if (availableGray)
            {
            imgRGB = QVImage<uChar,3>(imgGray,imgGray,imgGray);
            }
        }

    if( ( (imgRGB.getRows() != rows) or (imgRGB.getCols() != cols) ) )
        {
        imageRGB = QVImage<uChar,3>(cols,rows);
        Resize(imgRGB,imageRGB);
        }
    else
        imageRGB = imgRGB;
    }

void QVVideoReader::getRGBImage(QVImage<uChar> &imageR, QVImage<uChar> &imageG, QVImage<uChar> &imageB)
    {
    if(not availableRGB)
        {
        if(availableRGB3)
            {
            imgR = imgG = imgB = QVImage<uChar>(imgRGB.getCols(),imgRGB.getRows());
            Copy(imgRGB,0,imgR);
            Copy(imgRGB,1,imgG);
            Copy(imgRGB,2,imgB);
            availableRGB = true;
            }
        else if(availableYUV)
            {
            imgRGB = QVImage<uChar,3>(imgY.getCols(),imgY.getRows());
            YUV420ToRGB(imgY,imgU,imgV,imgRGB);
            imgR = imgG = imgB = QVImage<uChar>(imgRGB.getCols(),imgRGB.getRows());
            Copy(imgRGB,0,imgR);
            Copy(imgRGB,1,imgG);
            Copy(imgRGB,2,imgB);
            availableRGB = true;
            availableRGB3 = true;
            }
        else if (availableGray)
            {
            imgR = imgGray;
            imgG = imgGray;
            imgB = imgGray;
            availableRGB = true;
            }
        }

    if(  ( (imgR.getRows() != rows) or (imgR.getCols() != cols) or
           (imgG.getRows() != rows) or (imgG.getCols() != cols) or
           (imgB.getRows() != rows) or (imgB.getCols() != cols) ) )
        {
        imageR = QVImage<uChar>(cols,rows);
        imageG = QVImage<uChar>(cols,rows);
        imageB = QVImage<uChar>(cols,rows);
        Resize(imgR,imageR);
        Resize(imgG,imageG);
        Resize(imgB,imageB);
        }
    else
        {
        imageR = imgR;
        imageG = imgG;
        imageB = imgB;
        }
    }

void QVVideoReader::getYUVImage(QVImage<uChar> &imageY, QVImage<uChar> &imageU, QVImage<uChar> &imageV)
    {
    if(not availableYUV)
        {
        if(availableRGB3)
            {
            imgY = QVImage<uChar>(imgRGB.getCols(),imgRGB.getRows());
            imgU = imgV = QVImage<uChar>(imgRGB.getCols()/2,imgRGB.getRows()/2);
            RGBToYUV420(imgRGB,imgY,imgU,imgV);
            availableYUV = true;
            }
        else if(availableRGB)
            {
            imgRGB = QVImage<uChar,3>(imgR,imgG,imgB);
            imgY = QVImage<uChar>(imgRGB.getCols(),imgRGB.getRows());
            imgU = imgV = QVImage<uChar>(imgRGB.getCols()/2,imgRGB.getRows()/2);
            RGBToYUV420(imgRGB,imgY,imgU,imgV);
            availableYUV = true;
            availableRGB3 = true;
            }
        else if (availableGray)
            {
            imgRGB = QVImage<uChar,3>(imgGray,imgGray,imgGray);
            imgY = QVImage<uChar>(imgRGB.getCols(),imgRGB.getRows());
            imgU = imgV = QVImage<uChar>(imgRGB.getCols()/2,imgRGB.getRows()/2);
            RGBToYUV420(imgRGB,imgY,imgU,imgV);
            availableRGB3 = true;
            availableYUV = true;
            }
        }

    if( ( (imgY.getRows() != rows)   or (imgY.getCols() != cols)   or
          (imgU.getRows() != rows/2) or (imgU.getCols() != cols/2) or
          (imgV.getRows() != rows/2) or (imgV.getCols() != cols/2) ) )
        {
        imageY = QVImage<uChar>(cols,rows);
        imageU = QVImage<uChar>(cols/2,rows/2);
        imageV = QVImage<uChar>(cols/2,rows/2);
        Resize(imgY,imageY);
        Resize(imgU,imageU);
        Resize(imgV,imageV);
        }
    else
        {
        imageY = imgY;
        imageU = imgU;
        imageV = imgV;
        }
    }

bool QVVideoReader::close()
    {
    if(base_reader != 0)
        {
        if(base_reader->close())
            {
            url = QString();
            scheme = QString();
            cols = 0;
            rows = 0;
            fps = 0;
            frames_grabbed = 0;
            camera_opened = false;
            live_camera = false;
            end_of_video = true;
            availableGray = availableRGB3 = availableYUV = availableRGB = false;
            open_options = Default;
            source_mode = YUVMode;
            delete base_reader;
            base_reader = 0;
            emit sourceClosed();
            return true;
            }
        }
    return false;
    }

bool QVVideoReader::seek(int pos)
    {
    return base_reader->seek(pos);
    }

int QVVideoReader::getLength() const
    {
    return base_reader->getLength();
    }

int QVVideoReader::getPos() const
    {
    return base_reader->getPos();
    }

