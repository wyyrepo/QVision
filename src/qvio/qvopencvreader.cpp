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

/// @file qvopencvreader.cpp
/// @brief Implementation of the OpenCV video source reader for the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.


#include <QUrl>

#ifdef QVIPP
#include <qvipp.h>
#endif // QVIPP

#include <QVOpenCVReader>

bool QVOpenCVReader:: open(const QString & url_string,
                         unsigned int & suggested_cols, unsigned int & suggested_rows,
                         unsigned int & suggested_fps, QVVideoReader::OpenOptions & suggested_options,
                         QVVideoReader::TSourceMode & source_mode)
{
        // Preferred mode: RGB
        source_mode = QVVideoReader::RGBMode;

        isFile = isCamera = false;
        // File name:
        QUrl URL(url_string);
        if(URL.scheme() == "cvf") {
            isFile = true;
            QString fileName = URL.path();
            video_capture = new cv::VideoCapture(fileName.toStdString());
        } else if(URL.scheme() == "cvc") {
            isCamera = true;
            // URL.host should be the video device number passed to OpenCV:
            bool okDevice;
            //std::cout << "URL.fragment(): " << qPrintable(URL.fragment()) << "\n";
            int device = URL.fragment().toInt(&okDevice);
            if(okDevice)
                video_capture = new cv::VideoCapture(device);
        } else {
            std::cout << "Warning:: unknown scheme " << qPrintable (URL.scheme())
                      << "in QVOpenCVReader::open() method\n";
            return false;
        }

        // std::cout << "Video opened:" << (video_capture->isOpened()?1:0) << "\n";
        // std::cout.flush();

        // Try to adjust input size and fps (will not always succeed):
        if(suggested_rows != 0)
            if(not video_capture->set(CV_CAP_PROP_FRAME_HEIGHT,suggested_rows))
                {;} // std::cout << "Error setting CV_CAP_PROP_FRAME_HEIGHT.\n";
        if(suggested_cols != 0)
            if(not video_capture->set(CV_CAP_PROP_FRAME_WIDTH,suggested_cols))
                {;} // std::cout << "Error setting CV_CAP_PROP_FRAME_WIDTH.\n";
        if(suggested_fps != 0)
            if(not video_capture->set(CV_CAP_PROP_FPS,suggested_fps))
                {;} // std::cout << "Error setting CV_CAP_PROP_FPS.\n";

        double value;
        value = video_capture->get(CV_CAP_PROP_FRAME_WIDTH);
        suggested_cols = static_cast<int>(value);
        value = video_capture->get(CV_CAP_PROP_FRAME_HEIGHT);
        suggested_rows = static_cast<int>(value);
        value = video_capture->get(CV_CAP_PROP_FPS);
        suggested_fps = static_cast<int>(value);
        value = video_capture->get(CV_CAP_PROP_FRAME_COUNT);
        total_frames =  static_cast<int>(value);

        // RealTime & NoLoop flags:
        // realTime = (suggested_options & QVVideoReader::RealTime);
        noLoop = (suggested_options & QVVideoReader::NoLoop);

        // OpenCV will capture RGB frames:
        video_capture->set(CV_CAP_PROP_CONVERT_RGB,1);

        if(video_capture->isOpened())  // Check if we succeeded
            return TRUE;
        else
            return FALSE;
}

bool QVOpenCVReader::close()
{
    if(video_capture != 0)
        delete video_capture;
    return true;
}


bool QVOpenCVReader::grab(QVImage<uChar,1> &imgR, QVImage<uChar,1> &imgG, QVImage<uChar,1> &imgB)
{
        cv::Mat frame;

        bool grabbedframe = video_capture->grab();
        if(not noLoop & not grabbedframe) {
            seek(0);
            grabbedframe = video_capture->grab();
        }

        if(grabbedframe)
            video_capture->retrieve(frame);
        else
            return FALSE;

        IplImage ipl_image = frame;
        QVImage<uChar,3> ColorImage = QVImage<uChar,3>(&ipl_image);
        imgR = imgG = imgB = QVImage<uchar>(ColorImage.getCols(),ColorImage.getRows());
        // (OpenCV reads BGR instead of RGB):
        Copy(ColorImage,0,imgB);
        Copy(ColorImage,1,imgG);
        Copy(ColorImage,2,imgR);

        return TRUE;

}

int QVOpenCVReader::getLength()
{
    return total_frames;
}

int QVOpenCVReader::getPos()
{
    double value;
    if(isFile)
        value = video_capture->get(CV_CAP_PROP_POS_FRAMES);
    else // (isCamera)
        value = -1;
    //std::cout << "value=" << value << ";\n";
    //std::cout << "static_cast<int>(value)=" << static_cast<int>(value) << ";\n";
    return static_cast<int>(value);
}

bool QVOpenCVReader::seek(int pos)
{
    double value = static_cast<double>(pos);
    // std::cout << "pos=" << pos << ";\n";
    // std::cout << "video_capture->set(CV_CAP_PROP_POS_FRAMES," << value << ");\n";
    return video_capture->set(CV_CAP_PROP_POS_FRAMES,value);
}
