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
#   File qvcholmod.pri
#

!qvcholmod_available {
    CONFIG += qvcholmod_available

    message(Included module: qvcholmod)

    DEFINES += QVCHOLMOD

    !exists($$CHOLMOD_PATH/include): \
        error(In module qvcholmod: Include files directory was not found at the specified path: $$CHOLMOD_PATH/include)
    !exists($$CHOLMOD_PATH/lib): \
        error(In module qvcholmod: Library binaries were not found at the specified path: $$CHOLMOD_PATH/lib)

    message(* Path to CHOLMOD include headers: $$CHOLMOD_PATH/include)

    message(* Path to CHOLMOD library binaries: $$CHOLMOD_PATH/lib)

    INCLUDEPATH += $$CHOLMOD_PATH/include

    LIBS += -Wl,-rpath=$$CHOLMOD_PATH/lib -L$$CHOLMOD_PATH/lib   \
            -lamd -lcamd -lccolamd -lcholmod -lcolamd -lcsparse

    HEADERS +=   $$PWD/qvmath/qvcholmodsolver.h

    SOURCES +=   $$PWD/qvmath/qvcholmodsolver.cpp
}
