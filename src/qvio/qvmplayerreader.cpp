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

/// @file qvmplayerreader.cpp
/// @brief Implementation of the MPlayer video source reader for the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#include <iostream>

#include <QDebug>
#include <QStringList>
#include <QTimer>

#ifdef QVIPP
#include <qvipp.h>
#endif // QVIPP

#include <qvip.h>
#include <qvimageio.h>

#include <QVApplication>
#include <QVMPlayerReader>

/******************* Auxiliary QVCheckOKMPlayer class *******************/
QVCheckOKMPlayer::QVCheckOKMPlayer(QFile & fifo_file,int max_time_ms_to_wait_for_open) : QThread(), _fifo_file(fifo_file), _max_time_ms_to_wait_for_open(max_time_ms_to_wait_for_open)
       {
       qDebug() << "QVCheckOKMPlayer::QVCheckOKMPlayer() <- starting thread";
       moveToThread(this);
       start();
       }

void QVCheckOKMPlayer::run()
       {
       QTimer::singleShot(_max_time_ms_to_wait_for_open, this, SLOT(writeErrorInFifo()));
       qDebug() << "QVCheckOKMPlayer::run() <- entering event loop";
       exec();
       qDebug() << "QVCheckOKMPlayer::run() <- back from event loop";
       }

void QVCheckOKMPlayer::writeErrorInFifo()
       {
       qDebug() << "QVCheckOKMPlayerCamera::writeErrorInFifo()";
       _fifo_file.write("MPLAYER ERROR\n");
       qDebug() << "QVCheckOKMPlayerCamera::writeErrorInFifo() -> return";
       };

/***************************** QVMPlayerReader class **************************/

void QVMPlayerReader::initMPlayerArgs(QString urlString, unsigned int suggested_cols, unsigned int suggested_rows)
       {
       qDebug() << "QVMPlayerReader::initMPlayerArgs(" << urlString << "," << suggested_cols << "," << suggested_rows << ")";

       mplayer_args = QStringList();

       // Loop option and fixed-vo must go first:
       if(not (open_options & QVVideoReader::NoLoop)) mplayer_args << "-loop" << "0";

       mplayer_args << "-fixed-vo";

       QUrl url(urlString);

       path = QString();

       if (url.host() != "")
               path = url.host() + "/";

       path += url.path();

       // Here we infer the type of the video source from the url.
       // If it is not specified in the schema of it, certain match rules are
       // applied to guess it out.
       if (url.scheme() != "")				// schema specified by the user
               schema = url.scheme();
       else if (urlString.startsWith("/dev/video"))	// a v4l device
               schema = "v4l";
       else if (urlString.startsWith("/dev/dv"))	// a dv device
               schema = "dv";
       else if (urlString.contains("*"))		// a multifile
               schema = "mf";
       else if (urlString.startsWith("www."))		// a http file
               schema = "http";
       else if (urlString.startsWith("ftp."))		// a ftp file
               schema = "ftp";
       else
               schema = QString();

       live_camera = TRUE;	// Default configuration; later we set it to FALSE if it applies.

       // Different mplayer args for different kind of image sources:
       if ((schema == "v4l") or (schema == "v4l2") or (schema == "analog"))
               {
               // Video for Linux cameras:
               QString urlQueryValues = QString("driver=%1:device=%2").arg(schema).arg(path);

               QList<QPair<QString, QString> > queryItems = url.queryItems();
               for (int i = 0; i < queryItems.size(); ++i)
                       urlQueryValues += ":" + queryItems.at(i).first + "=" + queryItems.at(i).second;

               mplayer_args << "tv://" << "-tv" << urlQueryValues;
               }
       else if (schema == "dv")
               // DV cameras (connected through firewire):
               mplayer_args << path << "-demuxer" << "rawdv" << "-cache" << "400";
       else if (schema == "iidc")
               // IIDC cameras (connected through firewire):
               // For example, iidc:///dev/video1394/0?from=/dev/video0:to=/dev/video1
               qFatal("Currently this driver does not work (apparently with\n"
                       "vloopback writing and then reading from a fifo with mplayer\ndoes not work).\n");
       else if (schema == "tv")
               // Analog TV input:
               qFatal("tv URL: Still not implemented\n");
       else if (schema == "dvb") {
               // Digital TV input:
               live_camera = TRUE;
               mplayer_args << urlString; // dvb://CHANNEL goes to mplayer "as is".
       } else	// Format can be rtsp:// http://, ftp://, dvd://, vcd://, mf:// or file://
               {
               //  We pass the url it directly to mplayer:
               if(schema == "rtsp")
                       live_camera = TRUE;
               else
                       live_camera = FALSE;
               if (schema != "")
                       mplayer_args << urlString; //QString(schema + "://" + path);
               else
                       mplayer_args << path;
               }

       // IMPORTANT!! All -vf filters MUST be together, separated by commas, and in
       // the right order. By now, we only use deinterlacing and scale, and in that order:
       QString aux;

       // Deinterlace option:
       if(open_options & QVVideoReader::Deinterlaced) aux = "pp=md";

       // Scaling:
       if(suggested_cols != 0 and suggested_rows != 0)
               {
               if(aux != QString())
                       aux += QString(",scale=%1:%2").arg(suggested_cols).arg(suggested_rows);
               else
                       aux = QString("scale=%1:%2").arg(suggested_cols).arg(suggested_rows);
               }
       if (aux != QString()) mplayer_args << "-vf" << aux;

       // Real time option:
       if(not (open_options & QVVideoReader::RealTime))
               {
               if(not live_camera)
                       mplayer_args << "-benchmark";
               }

       // Additional arguments (slave, quiet, nosound & yuv4mpeg output):
       mplayer_args << "-slave" << "-quiet" << "-nosound" << "-vo" << QString("yuv4mpeg:file=%1").arg(namedPipe->getInputFilePath());

       qDebug() << "QVMPlayerReader::initMPlayerArgs(): MPlayer args = " << mplayer_args;
       qDebug() << "QVMPlayerReader::initMPlayerArgs() <- return";
       }

int QVMPlayerReader::interpretMPlayerOutput()
       {
       int length = -1;
       char buf[1024];

       length = mplayer->readLine(buf, sizeof(buf));

       if (length == -1)
               qDebug() << "QVMPlayerReader::interpretMPlayerOutput(): length == -1";
       else	{
               QString str(buf);
               QStringList variables = str.simplified().split("=");
               QStringList palabras = str.simplified().split(" ");

               if(variables[0] == "ANS_LENGTH")
                       {
                       time_length = variables[1].toDouble();
                       qDebug() << "QVMPlayerReader::interpretMPlayerOutput(): updating time_length =" << time_length;
                       }
               else if(variables[0] == "ANS_TIME_POSITION")
                       {
                       time_pos = variables[1].toDouble();
                       qDebug() << "QVMPlayerReader::interpretMPlayerOutput(): updating time_pos =" << time_pos;
                       }
               else
                       qDebug() << "QVMPlayerReader::interpretMPlayerOutput(): uninterpreted mplayer output:" << str;
               }
       qDebug() << "QVMPlayerReader::interpretMPlayerOutput() <- return " << length;
       return length;
       }

bool QVMPlayerReader::performGrab()
       {
       qDebug() << "QVMPlayerReader::performGrab()";

       if (not camera_opened)
               {
               qDebug() << "QVMPlayerReader::performGrab() returns FALSE (camera is closed)";
               return false;
               }

       qDebug() << "QVMPlayerReader::performGrab(): sending command get_time_pos to mplayer";
       mplayer->write("pausing_keep get_time_pos\n"); // pausing_keep in fact not needed...

       // New frame read:
       qDebug() << "QVMPlayerReader::performGrab: reading YUV frame: readYUV4MPEG2Frame()";
       if (!readYUV4MPEG2Frame(fifoInput, imgY, imgU, imgV))
               {
               qDebug() << "QVMPlayerReader::performGrab: No more frames left, closing camera";
               end_of_video = TRUE;
               close();
               qDebug() << "QVMPlayerReader::performGrab: No more frames left, camera closed, returning false";
               return FALSE;
               }

       frames_grabbed++;
       qDebug() << "QVMPlayerReader::performGrab: new frame read (" << frames_grabbed << ")";

       // Interpret mplayer output while it is writing something:
       qDebug() << "QVMPlayerReader::performGrab: now interpreting mplayer output";
       while(interpretMPlayerOutput() > 0);

       /*qDebug() << "QVMPlayerReader::performGrab: emitting newGrab() signal";
       emit newGrab();*/

       qDebug() << "QVMPlayerReader::performGrab() <- returning TRUE";
       return TRUE;
       }

static inline int iRoundUp(int a, int b) {
 return (a % b == 0) ? a : b*(a / b + 1) ;
}

bool QVMPlayerReader::open(  const QString & urlstring,
                    unsigned int & suggested_cols,
                    unsigned int & suggested_rows,
                    unsigned int & suggested_fps,
                    QVVideoReader::OpenOptions & suggested_opts,
                    QVVideoReader::TSourceMode & source_mode)
//bool QVMPlayerReader::open(const QString & urlstring, OpenOptions suggested_opts, unsigned int waitDelay, unsigned int suggested_cols, unsigned int suggested_rows)
       {
        open_options = suggested_opts;

        // By default, ignore input video fps, and force user value (unless realTime option flag is ON, in which
        // case we will set it to zero, as the mplayer process itself will force original fps):
        if(open_options & QVVideoReader::RealTime) {
            suggested_fps = 0;
        }

        // FIXME: review this on waitDelay; (formerly an input parameter).
        unsigned int waitDelay = 0;

        source_mode = QVVideoReader::YUVMode;
       qDebug() << "QVMPlayerReader::open(" << qPrintable(urlstring) << "," << static_cast<int>(suggested_opts) << ","
               << suggested_cols << "," << suggested_rows << "," << suggested_opts << ")";

       if(QVApplication::instance() == NULL) {
           std::cerr << "QVMPlayerReader class needs a QVApplication object to have been previously created in order to be used (simply declare one in your main function.)\n";
           return false;
       }

       if (camera_opened)
               {
               qDebug() << "QVMPlayerReader::open() <- closing previously opened camera";
               close();
               qDebug() << "QVMPlayerReader::open() <- previously opened camera closed";
               }

       // Pipe initialization
       namedPipe = new QNamedPipe(QString("mplayer"));
       qDebug() << "QVMPlayerReader::open(): Named pipe created" << namedPipe->getOutputFilePath();

       // Launching MPlayer:
       mplayer = new QProcess;
       mplayer->setParent(this);				// set the mplayerreader's parent = this, and move it to his thread.
       mplayer->moveToThread(this->thread());	// For QVMPlayerReader can send it signals, like waitForFinished in close
       initMPlayerArgs(urlstring, suggested_cols, suggested_rows);
       mplayer->start(MPLAYER_BINARY_PATH, mplayer_args);
       qDebug() << "QVMPlayerReader::open(): after mplayer->start()";
       if(not mplayer->waitForStarted(1000))
               qFatal("Mplayer failed to start in a second: Are you sure it is installed and in the correct PATH?");
       qDebug() << "QVMPlayerReader::open(): after mplayer->waitForstarted()";

       // Important to open fifo now in ReadWrite mode, to avoid infinite waiting if mplayer did
       // not start OK, and because perhaps the former guarding thread will write in the FIFO:
       qDebug() << "QVMPlayerReader::open(): opening fifo " << qPrintable(namedPipe->getOutputFilePath());
       fifoInput.setFileName(namedPipe->getOutputFilePath());
       if(fifoInput.open(QIODevice::ReadWrite|QIODevice::Unbuffered) == -1)
               qFatal("Error opening fifo %s\n", qPrintable(namedPipe->getOutputFilePath()));
       qDebug() << "QVMPlayerReader::open(): fifo opened";

       // We create a guarding thread that will unblock the subsequent readYUV4MPEG2Header in the
       // case that mplayer does not start OK (due, for example, to a wrong URL, an incorrect
       // file format, or whatever). If mplayer starts OK before two seconds (for local videos),
       // four seconds for cameras, or twelve seconds (for DVD, VCD and remote videos), this thread
       // silently stops and is deleted.
       uInt waitMilisecs;

       if (waitDelay > 0)
               waitMilisecs = waitDelay;
       else if(	schema == "http" or
                       schema == "ftp" or
                       schema == "rtsp" or
                       schema == "dvd" or
                       schema == "vcd" or
                       schema == "dvb")
               waitMilisecs = 15000;
       else if(	schema == "v4l" or
                       schema == "v4l2")
               waitMilisecs = 4000;
       else
               waitMilisecs = 2000;

       //std::cout << "QVMPlayerOpen: waitDelay = " << waitMilisecs << std::endl;

       QVCheckOKMPlayer check_thread(fifoInput, waitMilisecs);

       qDebug()<< "QVMPlayerReader::open(): going to read YUV header";
       // Now we read the YUV header:
       if (!readYUV4MPEG2Header(fifoInput, cols, rows, fps))
               {
               qWarning() << "QVMPlayerReader::open(): Warning: Mplayer could not open the requested video source ("
                          << qPrintable(urlstring) << ") of type " << qPrintable(schema);
               qDebug() << "QVMPlayerReader::open(): Terminating and killing mplayer";
               mplayer->terminate();
               if (not mplayer->waitForFinished(500)) mplayer->kill();
               qDebug() << "QVMPlayerReader::open(): Deleting pipe and mplayer";
               delete namedPipe;
               delete mplayer;
               qDebug() << "QVMPlayerReader::open(): closing fifo";
               fifoInput.close();
               // Finish guarding thread.
               /// Pedro: revisar esto.
               /*while(not check_thread.isFinished())
               {
                       qDebug() << "QVMPlayerReader::open(): quitting guarding thread (incorrect mplayer launch)";
                       check_thread.quit();
                       qDebug() << "QVMPlayerReader::open(): CheckOKMPlayerCamera thread quitted after correct launch of mplayer";
                       check_thread.wait(100);
               }*/
               qDebug() << "QVMPlayerReader::open(): quitting guarding thread";
               do check_thread.quit();
               while (not check_thread.wait(100));
               qDebug() << "QVMPlayerReader::open(): CheckOKMPlayerCamera thread quitted";
               qDebug() << "QVMPlayerReader::open(): Returning FALSE";
               cols = 0;
               rows = 0;
               fps = 0;
               frames_grabbed = 0;
               camera_opened = FALSE;
               return FALSE;
               }
       qDebug()<< "QVMPlayerReader::open(): back from read YUV header: cols = " << cols << " rows = " << rows << ", fps = " << fps;

       // Finish guarding thread.
       /// Pedro: revisar esto.
       /*while(not check_thread.wait(0))
       {
               qDebug() << "QVMPlayerReader::open(): quitting guarding thread  (correct mplayer launch)";
               check_thread.quit();
               qDebug() << "QVMPlayerReader::open(): CheckOKMPlayerCamera thread quitted after correct launch of mplayer";cvf
               check_thread.wait(100);
       }*/
       qDebug() << "QVMPlayerReader::open(): quitting guarding thread";
       do check_thread.quit();
       while (not check_thread.wait(100));
       qDebug() << "QVMPlayerReader::open(): CheckOKMPlayerCamera thread finished after correct launch of mplayer";

       // Now we close the fifo and open it again in ReadOnly mode (to avoid readYUV4MPEGFrame to block if we reach
       // the end of the mplayer video). There is also another "dirty trick" here: we must open an aux fifo (which we
       // close just a little bit later) in order not to leave at any moment the FIFO without readers (which could
       // provoke a race condition, because the mplayer process could decide to write in the FIFO just when there
       // are not any FIFO open for reading on it):
       QFile fifoAux;
       fifoAux.setFileName(namedPipe->getOutputFilePath());
       fifoAux.open(QIODevice::ReadOnly);
       fifoInput.close();
       // Here we open the "good" FIFO again, but now in ReadOnly mode:
       if(fifoInput.open(QIODevice::ReadOnly|QIODevice::Unbuffered) == -1)
               qFatal("Error opening fifo %s\n", qPrintable(namedPipe->getOutputFilePath()));
       fifoAux.close();

       qDebug() << "QVMPlayerReader::open(): Header correctly read: cols = "
                << cols << ", rows = " << rows << ", fps = " << fps;

       // If we get here, the header was correctly read, proceed to init MPlayer IO processing.
       frames_grabbed = 0;
       camera_opened = TRUE;

       // Create adequately sized images (observe 8 byte step alignment by rows):
       imgY = QVImage<uChar>(cols, rows, iRoundUp(cols,8));
       imgU = QVImage<uChar>(cols/2, rows/2, iRoundUp(cols/2,8));
       imgV = QVImage<uChar>(cols/2, rows/2, iRoundUp(cols/2,8));

       // THIS DOES NOT WORK (mplayer does not write anything until later... so we have to read from it in performGrab()):
       // while(mplayerIO->time_length == 0)
       //	mplayerIO->interpretMPlayerOutput();

       qDebug() << "QVMPlayerReader::open() <- sending get_time_length command to mplayer";
       mplayer->write("get_time_length\n");
       mplayer->waitForReadyRead();

       /*qDebug() << "QVMPlayerReader::open() <- emitting camOpened signal";
       emit camOpened();*/

       suggested_cols = cols;
       suggested_rows = rows;

       qDebug() << "QVMPlayerReader::open() <- return";
       return TRUE;
       }

bool QVMPlayerReader::close()
       {
       qDebug() << "QVMPlayerReader::close()";

       if (not camera_opened)
               {
               qDebug() << "QVMPlayerReader::close(): camera already closed. Returning";
               return false;
               }

       qDebug() << "QVMPlayerReader::close(): closing fifo";
       fifoInput.close();

       if(not end_of_video)
               {
               qDebug() << "QVMPlayerReader::close(): going to send quit command to mplayer";
               mplayer->write("quit\n");
               }
       qDebug() << "QVMPlayerReader::close(): going to terminate mplayer";
       mplayer->terminate();
       qDebug() << "QVMPlayerReader::close(): going to kill mplayer";
       mplayer->kill();
       qDebug() << "QVMPlayerReader::close(): going to wait for mplayer to finish";
       mplayer->waitForFinished();
       qDebug() << "QVMPlayerReader::close(): mplayer finished";

       qDebug() << "QVMPlayerReader::closecam(): deleting namedpipe";
       delete namedPipe;

       qDebug() << "QVMPlayerReader::closecam(): deleting QProcess mplayer";
       delete mplayer;

       // We reset all the members of the class:
       open_options = QVVideoReader::Default;
       path = QString();
       schema = QString();
       camera_opened = FALSE;
       frames_grabbed = 0;
       live_camera = FALSE;
       imgY = QVImage<uChar>();
       imgU = QVImage<uChar>();
       imgV = QVImage<uChar>();
       cols = 0;
       rows = 0;
       fps = 0;
       time_length = 0;
       time_pos = 0;
       end_of_video = FALSE;

       /*qDebug() << "QVMPlayerReader::close() <- emitting camClosed signal";
       emit camClosed();*/

       qDebug() << "QVMPlayerReader::close() <- return";
       return TRUE;
       }

/*bool QVMPlayerReader::grab(QVImage<uChar,1> & imageGray)
       {
       qDebug() << "QVMPlayerReader::grab(imageGray)";
       if (performGrab())
               {
               imageGray = imgY;
               return TRUE;
               }
       else
               return FALSE;
       }

#ifdef QVIPP
bool QVMPlayerReader::grab(QVImage<uChar,3> & imageRGB)
       {
       qDebug() << "QVMPlayerReader::grab(imageRGB)";
       if (performGrab())
               {
               imageRGB = QVImage<uChar,3>(imgY.getCols(),imgY.getRows());
               YUV420ToRGB(imgY, imgU, imgV, imageRGB);
               return TRUE;
               }
       else
               return FALSE;
       }
#endif
*/


bool QVMPlayerReader::grab(QVImage<uChar> &imageY, QVImage<uChar> &imageU, QVImage<uChar> &imageV)
       {
       qDebug() << "QVMPlayerReader::grab(imageY, imageU, imageV)";
       if (performGrab())
               {
               imageY = imgY;
               imageU = imgU;
               imageV = imgV;
               return TRUE;
               }
       else
               return FALSE;
       }

/*bool QVMPlayerReader::seek(TSeekType seek,double d)
       {
       qDebug() << "QVMPlayerReader::seekCam(" << static_cast<int>(seek) << "," << d << ")";
       if(not camera_opened) return false;
       QString command = QString("pausing_keep seek ") + QString::number(d) + " " + QString::number(seek) + "\n";
       mplayer->write(qPrintable(command)); // pausing keep in fact not needed...
       qDebug() << "QVMPlayerReader::seekCam() <~ return";
       return true;
       }*/

bool QVMPlayerReader::seek(int d)
       {
       if(not camera_opened) return false;
       QString command = QString("pausing_keep seek ") + QString::number(d/fps) + " 2" + "\n";
       std::cout << "command to mplayer = " << qPrintable(command) << "\n";
       mplayer->write(qPrintable(command)); // pausing keep in fact not needed...
       return true;
       }
