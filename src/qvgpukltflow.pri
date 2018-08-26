#
#   Copyright (C) 2011, 2012. PARP Research Group.
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
#   File qvgpukltflow.pri
#

!qvgpukltflow_available {
    CONFIG += qvgpukltflow_available

    message(Included module: qvgpukltflow)

    DEFINES += QVGPUKLTFLOW

    # Adds the values of this variable as compiler C preprocessor macros
    DEFINES += V3DLIB_ENABLE_GPGPU V3DLIB_GPGPU_ENABLE_CG
    DEFINES += V3D_SHADER_PATH=\\\"$$V3D_SHADER_PATH\\\"

    # If OpenCV is available, configure GPU-KLT to use it.
    qvopencv_available:DEFINES += V3DLIB_ENABLE_OPENCV

    !exists($$GPU_KLT_PATH/libV3D.a)  error(In module qvgpukltflow: binary file for the library GPU_KLT not found at path $$GPU_KLT_PATH.)
    !exists($$V3D_SHADER_PATH):       error(In module qvgpukltflow: specified path to shader files does not exist.)

    INCLUDEPATH += $$GPU_KLT_PATH $$GPU_KLT_PATH/GL $$GPU_KLT_PATH/Base $$GPU_KLT_PATH/GL/Shaders

    LIBS += -L$$GPU_KLT_PATH -Wl,-rpath,$$GPU_KLT_PATH

    LIBS += -lCg -lCgGL -lGLEW -lV3D -lglut -lGLU -lpthread
    #QMAKE_CXXFLAGS += -DNDEBUG

    HEADERS +=  $$PWD/qvgpukltflow.h                      \
                $$PWD/qvgpukltflow/qvopticalflow.h        \
                $$PWD/qvgpukltflow/qvpyramid.h            \
                $$PWD/qvgpukltflow/qvklttracker.h         \
                $$PWD/qvgpukltflow/qvkltfeaturetracking.h

    SOURCES +=  $$PWD/qvgpukltflow.cpp                      \
                $$PWD/qvgpukltflow/qvopticalflow.cpp        \
                $$PWD/qvgpukltflow/qvpyramid.cpp            \
                $$PWD/qvgpukltflow/qvklttracker.cpp         \
                $$PWD/qvgpukltflow/qvkltfeaturetracking.cpp
}
