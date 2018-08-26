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

/// @file qvmplayerreader.h
/// @brief Implementation of MPlayer video source reader.
/// @author PARP Research Group. University of Murcia, Spain.

#ifndef QVMPLAYERREADER_H
#define QVMPLAYERREADER_H

#include <QVBaseReader>

#include <QFile>
#include <QProcess>
#include <QString>
#include <QThread>
#include <QUrl>

#include <QNamedPipe>
#include <QVImage>

#ifndef DOXYGEN_IGNORE_THIS
// Auxiliary QVCheckOKMPlayer Class:
// This is an internal convenience thread used only to unblock the open function
// when it is waiting for mplayer to write in the fifo, in the case when
// mplayer aborted when starting (due to bad URL, or wrong file format, for
// example).
class QVCheckOKMPlayer: public QThread
{
    friend class QVMPlayerReader; // Only QVMPlayerReader will have access to this class.

    Q_OBJECT
private:
    QVCheckOKMPlayer(QFile & fifo_file,int max_time_ms_to_wait_for_open);

    QFile & _fifo_file;
    int _max_time_ms_to_wait_for_open;

    void run();

private slots:
    void writeErrorInFifo();
};
#endif

class QVMPlayerReader : public QVBaseReader, public QObject
{
public:
    QVMPlayerReader():
        open_options(QVVideoReader::Default),
        path(QString()),
        schema(QString()),
        camera_opened(FALSE),
        frames_grabbed(0),
        live_camera(FALSE),
        imgY(QVImage<uChar>()),
        imgU(QVImage<uChar>()),
        imgV(QVImage<uChar>()),
        cols(0),
        rows(0),
        fps(0),
        time_length(0),
        time_pos(0),
        end_of_video(FALSE)
    { };

    ~QVMPlayerReader() { if (camera_opened) close(); };

    bool open(  const QString & url_string,
                        unsigned int & suggested_cols,
                        unsigned int & suggested_rows,
                        unsigned int & suggested_fps,
                        QVVideoReader::OpenOptions & suggested_opts,
                        QVVideoReader::TSourceMode & source_mode);

    int getLength()  { return fps*time_length; };

    int getPos()  { return fps*time_pos; };

    bool grab(QVImage<uChar> &imgY, QVImage<uChar> &imgU, QVImage<uChar> &imgV);

    bool close();

    bool seek(int pos);

private:
    QVVideoReader::OpenOptions open_options;
    QStringList mplayer_args;
    QProcess *mplayer;
    QString path, schema;
    QNamedPipe *namedPipe;
    QFile fifoInput;
    bool camera_opened;
    unsigned int frames_grabbed;
    bool live_camera;
    QVImage<uChar> imgY, imgU, imgV;
    int cols, rows, fps;
    double time_length, time_pos;
    bool end_of_video;

    void initMPlayerArgs(QString urlString, unsigned int suggested_cols, unsigned int suggested_rows);
    int interpretMPlayerOutput();
    bool performGrab();
};

#endif // QVMPLAYERREADER_H
