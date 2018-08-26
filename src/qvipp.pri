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

################################
#
#   File qvipp.pri
#

!qvipp_available {
    CONFIG += qvipp_available

    message(Included module: qvipp)

    DEFINES += QVIPP

    !qvcomposer{
        IPP_INCLUDE_PATH = $$IPP_PATH/include
        IPP_LIB_PATH = $$IPP_PATH/sharedlib
    }

    !exists($$IPP_INCLUDE_PATH): \
        error(In module qvipp: Include files directory was not found at the specified path \
              for the IPP library: $$IPP_INCLUDE_PATH . Perhaps it is not the installation \
              directory for the IPP?)

    !exists($$IPP_LIB_PATH): \
        error(In module qvipp: Library directory was not found at the specified path   \
              for the IPP library: $$IPP_LIB_PATH . Perhaps it is not the installation \
              directory for the IPP?)

    INCLUDEPATH += $$IPP_INCLUDE_PATH

    message(* Path to IPP include headers: $$IPP_INCLUDE_PATH)

    message(* Path to IPP library binaries: $$IPP_LIB_PATH)

    unix {
            LIBS += -L$$IPP_LIB_PATH -Wl,-rpath=$$IPP_LIB_PATH
            exists($$find(IPP_LIB_PATH, em64t)):   LIBS += -lippiem64t -lippcoreem64t -lippsem64t -lippccem64t -lippvcem64t -lippcvem64t
            exists($$find(IPP_LIB_PATH, ia32)):   LIBS += -lippi -lippcore -lipps -lippcc -lippvc -lippcv
            #LIBS += -lippi -lippcore -lipps -lippcc -lippvc -lippcv # Last versions of IPP 64 bits do not change name with respect to 32 bits
            # LIBS += -lguide   # really needed ?
    } else {
        error(IPP currently supported only in Linux systems)
    }

    HEADERS +=  $$PWD/qvipp/qvipp.h            \
                $$PWD/qvipp/qvippfunctions.h   \
                $$PWD/qvltmser/qvltmser_ds.h   \
                $$PWD/qvltmser/qvltmser.h

    SOURCES +=  $$PWD/qvipp/qvipp.cpp          \
                $$PWD/qvipp/qvippfunctions.cpp \
                $$PWD/qvltmser/qvltmser_ds.cpp \
                $$PWD/qvltmser/qvltmser.cpp
}
