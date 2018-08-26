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
#   File qvicc.pri
#

!qvicc_available {
    CONFIG += qvicc_available

    message(Included module: qvicc (Intel ICC compiler will be used))

    DEFINES += QVICC

    QMAKE_CXX = $$ICC_BINARY
    QMAKE_LINK = $$ICC_BINARY   # Undocumented variable.

    exists($$ICC_BINARY) {
        message(* icc binary found at: $$MPLAYER_BINARY_PATH)
    } else {
        error(icc binary was not found at: $$ICC_BINARY \
              Set a correct path in the ICC_BINARY variable at the config.pri file)
    }
}
