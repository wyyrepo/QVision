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

/*!
@file videoReader.cpp

@brief Simple example of reading video sources and saving selected frames, using the generalized input video reader
       class in QVision.

This program will save a series of requested frames in individual image files, as captured from a generic video
source, which can be anything from a webcam or a firewire cam, to a video file, a TDT channel, a DVD, remote sources
(via @c http or @c rtsp protocols) or even directories containing sequences of images in individual frames. See
documentation on class @ref QVVideoReader for further information on this extremely versatile class.

@section Usage Usage of the program.

Once the QVision has been installed, compile using the <i>qmake</i> and <i>make</i> tools:
@code # qmake; make @endcode

Execute the application with the following line:
@code ./videoReader --URL=<source video identifier string> @endcode
For example:
@code ./videoReader --URL=file:///home/pedro/file.avi @endcode
or
@code ./videoReader --URL=http://perception.inf.um.es/public_data/videos/misc/minuto.avi @endcode
or
@code ./videoReader --URL=ocvc://#0 @endcode

(among many other possibilities; see section @ref VideoReaderURLFormat for further info about the formats and types
of source video identifier strings).

Execute with parameter @c --help to get help on additional available command line options:
@code ./videoPlayer --help @endcode

@ingroup ExamplePrograms

@author PARP Research Group. University of Murcia, Spain.
*/

#include <QVApplication>
#include <QVPropertyContainer>
#include <QVImage>
#include <QVVideoReader>

int main(int argc, char *argv[])
    {
    QVApplication app(argc,argv,
                      "This program will save a series of requested frames in individual image files, as captured \n"
                      "from a generic video source, which can be anything from a webcam or a firewire cam, to a video \n"
                      "file, a TDT channel, a DVD, remote sources (via http or rtsp protocols) to even directories \n"
                      "containing sequences of images in individual frames. See documentation on class QVVideoReader \n"
                      "for further information on about the format and types of accepted source video identifier \n"
                      "strings.\n"
                      "\nHere are some URL examples:\n"
                      "Reading directly an uncompressed yuv4mpeg file:\n"
                      "    ./videoReader --URL=yuv4mpeg:///home/pedroe/svnvideos/futbol.yuv\n"
                      "Reading directly a sequence of images in a given directory:\n"
                      "    ./videoReader --URL=dir:///home/pedroe/imagenes\n"
                      "Reading a video file through OpenCV (needs the OpenCV library):\n"
                      "    ./videoReader --URL=cvf:///home/pedroe/svnvideos/arrow.avi\n"
                      "Reading a webcam/firewire camera through OpenCV (needs the OpenCV library):\n"
                      "    ./videoReader --URL=cvc://#0\n"
                      "Reading a video file through mplayer (needs mplayer installed):\n"
                      "    ./videoReader --URL=file:///home/pedroe/svnvideos/penguin.dv\n"
                      "Reading remote sources using mplayer(needs mplayer installed):\n"
                      "    ./videoReader --URL=http://perception.inf.um.es/public_data/videos/misc/minuto.avi\n"
                      "    ./videoReader --URL=rtsp://v7.cache4.c.youtube.com/CjgLENy73wIaLwmNoYPdmgJFpRMYJCAkFEIJbXYtZ29vZ2xlSARSB3Jlc3VsdHNg-uzp15Dl_9FNDA==/0/0/0/video.3gp",
                      FALSE);

    // Property container for easy reading of command line arguments:
    QVPropertyContainer forArgs("videoReader");
    forArgs.addProperty<QString>("URL",QVPropertyContainer::inputFlag,"ocvc:#0",
                                 "URL to read video from (default OpenCV main camera)");
    forArgs.addProperty<int>("Rows",QVPropertyContainer::inputFlag,0,
                             "Number of rows of output image (0->same as input)",0,65536);
    forArgs.addProperty<int>("Cols",QVPropertyContainer::inputFlag,0,
                             "Number of columns of output image (0->same as input)",0,65536);
    forArgs.addProperty<int>("fps",QVPropertyContainer::inputFlag,0,
                             "(Requested) number of frames per second (0->same as input)",0,200);
    forArgs.addProperty<bool>("NoLoop",QVPropertyContainer::inputFlag,false,
                              "Whether the video should loop or not when reaching the end (only valid for non live sources)");
    forArgs.addProperty<bool>("Deinterlaced",QVPropertyContainer::inputFlag,false,
                              "Whether the video should be deinterlaced or not (only valid for mplayer sources)");
    forArgs.addProperty<bool>("RealTime",QVPropertyContainer::inputFlag,false,
                              "If the camera should be read in real time (at requested fps) or as fast as possible (not valid for live sources)");
    forArgs.addProperty<int>("skip",QVPropertyContainer::inputFlag,0,
                             "Number of frames to skip between dumped frames",0,65536);
    forArgs.addProperty<int>("frames",QVPropertyContainer::inputFlag,10,
                             "Number of frames to dump",1,65536);
    forArgs.addProperty<int>("initpos",QVPropertyContainer::inputFlag,0.0,
                             "Initial position of video (in number of frames)",0.0,100000.0);
    forArgs.addProperty<int>("mode",QVPropertyContainer::inputFlag,0,
                             "Read mode (0->RGB, 1->RGB (separate), 2->Gray, 3->YUV (separate))",0,3);
    forArgs.addProperty<QString>("ext",QVPropertyContainer::inputFlag,"jpg",
                                 "Image format for output images (selected by extension name)");

    QString URL          = forArgs.getPropertyValue<QString>("URL");
    unsigned int Rows    = forArgs.getPropertyValue<int>("Rows");
    unsigned int Cols    = forArgs.getPropertyValue<int>("Cols");
    unsigned int fps     = forArgs.getPropertyValue<int>("fps");
    bool NoLoop          = forArgs.getPropertyValue<bool>("NoLoop");
    bool Deinterlaced    = forArgs.getPropertyValue<bool>("Deinterlaced");
    bool RealTime        = forArgs.getPropertyValue<bool>("RealTime");
    QVVideoReader::OpenOptions options = QVVideoReader::Default;
    if(NoLoop)       options |= QVVideoReader::NoLoop;
    if(Deinterlaced) options |= QVVideoReader::Deinterlaced;
    if(RealTime)     options |= QVVideoReader::RealTime;
    unsigned int skip    = forArgs.getPropertyValue<int>("skip");
    unsigned int frames  = forArgs.getPropertyValue<int>("frames");
    unsigned int initpos = forArgs.getPropertyValue<int>("initpos");
    unsigned int mode    = forArgs.getPropertyValue<int>("mode");
    QString ext          = forArgs.getPropertyValue<QString>("ext");

    // If user just asked for help on the application, show it and exit:
    if(app.arguments().contains("--help"))
    {
        std::cout << qPrintable(app.getHelp());
        exit(0);
    }

    // Check output image format:
    QStringList extensions;
    extensions << "jpg" << "png" << "bmp" << "pgm" << "gif" << "jpeg" << "pbm" << "ppm" << "tiff" << "xbm" << "xpm";
    if(not extensions.contains(ext))
        {
            std::cout << "Error: output format " << qPrintable(ext) << " not supported.\n";
            exit(1);
        }

    // Open video and report relevant info:
    QVVideoReader videoReader;
    QVVideoReader::TSourceMode source_mode;
    if (!videoReader.open(URL,Cols,Rows,fps,options,source_mode))
        {
        std::cout << "Error opening requested video source (" << qPrintable(URL) << ").\n";
        exit(2);
        }
    std::cout << "Video source successfully opened. Info on source:\n";
    std::cout << "  Output cols: " << Cols << ".\n";
    std::cout << "  Output rows: " << Rows << ".\n";
    std::cout << "  Output fps: " << fps << ".\n";
    std::cout << "  Video preferred source mode (other outputs need conversion): ";
    if(source_mode == QVVideoReader::YUVMode)
        std::cout << "YUV mode.";
    else if(source_mode == QVVideoReader::RGBMode)
        std::cout << "RGB mode.";
    else if(source_mode == QVVideoReader::GrayOnlyMode)
        std::cout << "Gray only mode.";
    std::cout << "\n";

    // Seek for initial position:
    if(initpos != 0)
        videoReader.seek(initpos);

    // Start grabbing:
    QVImage<uChar,3> imageRGB;
    QVImage<uChar> image_planes[3];
    unsigned int count = 0;
    while(videoReader.grab())
        {
        QStringList imagenames;
        if(mode==0)
            {
            videoReader.getRGBImage(imageRGB);
            imagenames.append(QString("frame-RGB-%1.%2").arg((short int)count,4,10,QChar('0')).arg(ext));
            }
        else if(mode==1)
            {
            videoReader.getRGBImage(image_planes[0],image_planes[1],image_planes[2]);
            imagenames.append(QString("frame-R-%1.%2").arg((short int)count,4,10,QChar('0')).arg(ext));
            imagenames.append(QString("frame-G-%1.%2").arg((short int)count,4,10,QChar('0')).arg(ext));
            imagenames.append(QString("frame-B-%1.%2").arg((short int)count,4,10,QChar('0')).arg(ext));
            }
        else if(mode==2)
            {
            videoReader.getGrayImage(image_planes[0]);
            imagenames.append(QString("frame-gray-%1.%2").arg((short int)count,4,10,QChar('0')).arg(ext));
            }
        else // if(mode==3)
            {
            videoReader.getYUVImage(image_planes[0],image_planes[1],image_planes[2]);
            imagenames.append(QString("frame-Y-%1.%2").arg((short int)count,4,10,QChar('0')).arg(ext));
            imagenames.append(QString("frame-U-%1.%2").arg((short int)count,4,10,QChar('0')).arg(ext));
            imagenames.append(QString("frame-V-%1.%2").arg((short int)count,4,10,QChar('0')).arg(ext));
            }
        count++;
        if((count-1) % (skip+1) != 0)
            continue;
        for(int i=0;i<imagenames.size();i++)
            {
            QString imagename = imagenames[i];
            std::cout << "Saving image " << qPrintable(imagename) << ".\n";
            QImage qimage;
            if(mode==0)
                qimage = imageRGB;
            else
                qimage = QVImage<uchar,3>(image_planes[i],image_planes[i],image_planes[i]);
            qimage.save(imagename);
            }
        frames--;
        if(frames == 0)
            break;
        }

    // Print video reader information (for testing methods):
    std::cout << "Length of video source (in frames): " << videoReader.getLength() << "\n";
    std::cout << "Current position in video source (in frames): " << videoReader.getPos() << "\n";
    std::cout << "Complete URL of video source: " << qPrintable(videoReader.getURL()) << "\n";
    std::cout << "URL scheme of video source: " << qPrintable(videoReader.getScheme()) << "\n";
    std::cout << "Number of columns of video source: " << videoReader.getCols() << "\n";
    std::cout << "Number of rows of video source: " << videoReader.getRows() << "\n";
    std::cout << "FPS of video source: " << videoReader.getFPS() << "\n";

    // Close source:
    videoReader.close();
    std::cout << "Done!\n";
    }
