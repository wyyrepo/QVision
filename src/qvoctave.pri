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
#   File qvoctave.pri
#

!qvoctave_available {
    CONFIG += qvoctave_available

    message(Included module: qvoctave)

    DEFINES += QVOCTAVE

    !exists($$OCTAVELIB_PATH_HEADERS/octave/oct.h): \
        error(In module qvoctave: File 'oct.h' not found in headers path '$$OCTAVELIB_PATH_HEADERS/octave'. Set a correct path in OCTAVELIB_PATH_HEADERS variable at config.pri file)

    !exists($$OCTAVELIB_PATH_BIN/liboctave.so): \
        error(In module qvoctave: File 'liboctave.so' not found in headers path '$$OCTAVELIB_PATH_BIN'. Set a correct path in OCTAVELIB_PATH_BIN variable at config.pri file)
	
    LIBS += -Wl,-rpath=$$OCTAVELIB_PATH_BIN -L$$OCTAVELIB_PATH_BIN -loctave
	INCLUDEPATH += $$OCTAVELIB_PATH_HEADERS

    message(* Path to Octave library headers: $$OCTAVELIB_PATH_HEADERS)
    message(* Path to Octave library binaries: $$OCTAVELIB_PATH_BIN)
}

