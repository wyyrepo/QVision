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
#   File common.pri
#

DEFINES += QVISION_VERSION_0_8_0

######################################################################
#   Add Qt XML and OpenGL modules, & adequate include and depend paths

QT += xml opengl

DEPENDPATH += $$PWD/src
INCLUDEPATH += $$PWD/src

######################################################################
#   Include user configuration file

CONFIG -= release   # User will explicitly specify debug or release
CONFIG -= debug     # mode in config.pri (for the library) or in
                    # its own .pro project file (for applications)

! include(config.pri) {
    error("File config.pri not present. Read the INSTALL file, and modify config.pri.example to generate it.")
}

######################################################################
#   Compiler & linker flags

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

QMAKE_LFLAGS -= -Wl,--no-undefined
QMAKE_LFLAGS += -lglut -lGLU -pthread -Wl,--no-as-needed

######################################################################
#   Start console output of qmake

message(--------------------------)

# message("Defines = $$DEFINES")

######################################################################
#   Check Qt Version

contains(QT_VERSION, 4.[0-9].*):    DEFINES += QT_MIN_VERSION_4_0
contains(QT_VERSION, 4.[1-9].*):    DEFINES += QT_MIN_VERSION_4_1
contains(QT_VERSION, 4.[2-9].*):    DEFINES += QT_MIN_VERSION_4_2
contains(QT_VERSION, 4.[3-9].*):    DEFINES += QT_MIN_VERSION_4_3
contains(QT_VERSION, 4.[4-9].*):    DEFINES += QT_MIN_VERSION_4_4
contains(QT_VERSION, 4.[5-9].*):    DEFINES += QT_MIN_VERSION_4_5
contains(QT_VERSION, 4.[6-9].*):    DEFINES += QT_MIN_VERSION_4_6
contains(QT_VERSION, 4.[7-9].*):    DEFINES += QT_MIN_VERSION_4_7
contains(QT_VERSION, 4.[8-9].*):    DEFINES += QT_MIN_VERSION_4_8
contains(QT_VERSION, 4.9.*):        DEFINES += QT_MIN_VERSION_4_9

message(Qt version $$QT_VERSION)

######################################################################
#   Check debug/release mode

release {
    message(QVision configured for RELEASE mode)
} else {
    message(QVision configured for DEBUG mode)
    warning(Performance can increase significantly enabling RELEASE mode)

    CONFIG += debug
    DEFINES += DEBUG
}

######################################################################
#   Check operating system

linux-g++|unix: message(Target platform: Linux)
win32:          message(Target platform: Windows 32 bits)
win64:          message(Target platform: Windows 64 bits)
macx:           message(Target platform: Mac OS X)

######################################################################
# Intel high performance modules (IPP/MKL/ComposerXE) (optional)

# This include only configures IPP and MKL located at the composerxe
# installation, so it must go before 'qvipp.pri' and 'qvmkl.pri'
qvcomposer {
    qvipp: error(Incompatible options: 'qvcomposer' and 'qvipp'. Check your config.pri file.)
    qvmkl: error(Incompatible options: 'qvcomposer' and 'qvmkl'. Check your config.pri file.)
    include(src/qvcomposer.pri)
}
# qvipp.pri' and 'qvmkl.pri' should be included if they are installed
# separatedly, as well as if they are part of the ComposerXE suite
qvmkl: include(src/qvmkl.pri)
qvipp: include(src/qvipp.pri)

######################################################################
# Main QVision modules (mandatory)

include(src/qvip.pri)
include(src/qvmath.pri)
include(src/qvblockprogramming.pri)
include(src/qvsfm.pri)

######################################################################
# Additional 3d party math modules (optional)

qvoctave:   include(src/qvoctave.pri)
qvgsl:      include(src/qvgsl.pri)
qvlapack:   include(src/qvlapack.pri)
qvcholmod:  include(src/qvcholmod.pri)

######################################################################
# Additional 3d party modules (optional)

qvqwt:          include(src/qvqwt.pri)
qvopencv:       include(src/qvopencv.pri)
qvcgal:         include(src/qvcgal.pri)
qvcuda:         include(src/qvcuda.pri)
qvcudatoolkit:  include(src/qvcudatoolkit.pri)
qvsiftgpu:      !qvcudatoolkit: error('qvsiftgpu' needs 'qvcudatoolkit' module. Check your config.pri file.)
qvicc:          include(src/qvicc.pri)
qvgpukltflow:   include(src/qvgpukltflow.pri)
qvros {
    include(src/qvros.pri)
    CHOLMOD_PATH = $$ROS_PATH/stacks/vslam/suitesparse
    include(src/qvcholmod.pri)
}

######################################################################
# MPlayer video input module (optional)

qvmplayer	{
			qvipp_available	{
								include(src/qvmplayer.pri)
								}
					else		{
								warning('Tried to enable MPlayer functionality, but required IPP library is not available.')
								include(src/qvmplayer.pri)
								}
			}

################################################################
# Main module (depends on MPlayer and OpenCV)
# Input/output, image processing, math, block programming and structure
# from motion modules
include(src/qvio.pri)

message(--------------------------)
