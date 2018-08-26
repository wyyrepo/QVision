#
#   Copyright (C) 2007, 2008, 2009, 2010, 2011, 2012. PARP Research Group.
#   <http://perception.inf.um.es>
#   University of Murcia, Spain.
#
#   This file is part of the QVision library.
#
#   QVision is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Lesser General Public License as
#   published by the Free Software Foundation, version 3 of the License.
#
#   QVision is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with QVision. If not, see <http://www.gnu.org/licenses/>.
#

######################################################################
#
#   File qvio.pri
#

!qvio_available {
    CONFIG += qvio_available

    message(Included module: qvio)

    HEADERS +=  $$PWD/qvio/qvvideoreader.h     \
                $$PWD/qvio/qvbasereader.h      \
                $$PWD/qvio/qvdirreader.h       \
                $$PWD/qvio/qvyuv4mpeg2reader.h \
                $$PWD/qvio/qvyuv4mpeg2writer.h

    SOURCES +=  $$PWD/qvio/qvvideoreader.cpp     \
                $$PWD/qvio/qvbasereader.cpp      \
                $$PWD/qvio/qvdirreader.cpp       \
                $$PWD/qvio/qvyuv4mpeg2reader.cpp \
                $$PWD/qvio/qvyuv4mpeg2writer.cpp

    # MPlayer dependant blocks
    qvmplayer_available {
        HEADERS +=  $$PWD/qvio/qvmplayerreader.h

        SOURCES +=  $$PWD/qvio/qvmplayerreader.cpp
    }

    # OpenCV dependant blocks
    qvopencv_available {
        HEADERS +=  $$PWD/qvio/qvopencvreader.h

        SOURCES +=  $$PWD/qvio/qvopencvreader.cpp
    }
}
