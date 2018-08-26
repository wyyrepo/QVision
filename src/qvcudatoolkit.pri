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
#   File qvcudatoolkit.pri
#

!qvcudatoolkit_available {
    CONFIG += qvcudatoolkit_available

    message(Included module: qvcudatoolkit)

    DEFINES += CUDA_TOOLKIT_AVAILABLE

    !exists($$CUDA_TOOLKIT_PATH): \
        error(In module qvcudatoolkit: Installation path to CUDA Toolkit does not exists: $$CUDA_TOOLKIT_PATH)

    message(* Path to CUDA Toolkit: $$CUDA_TOOLKIT_PATH)

    INCLUDEPATH += $$CUDA_TOOLKIT_PATH/include

    LIBS += -L$$CUDA_TOOLKIT_PATH/lib -Wl,-rpath=$$CUDA_TOOLKIT_PATH/lib -lcublas -lcurand -lcudart -lcusparse -lcufft

    # SIFTGPU. Additional CUDA include path:
    qvsiftgpu {
	    CONFIG += qvsiftgpu_available
        !exists($$SIFTGPU_HEADER_PATH): error(In module qvsiftgpu (depending on qvcudatoolkit): \
                                              path to SIFTGPU header specified but does not exists)
        !exists($$SIFTGPU_LIB_PATH): error(In module qvsiftgpu (depending on qvcudatoolkit): \
                                           path to SIFTGPU binary specified but does not exists)

        message(* Including SIFTGPU functionality.)
        message(* Path to SIFTGPU lib: $$SIFTGPU_LIB_PATH)
        message(* Path to SIFTGPU headers: $$SIFTGPU_HEADER_PATH)

        INCLUDEPATH += $$SIFTGPU_HEADER_PATH

        LIBS += -L$$SIFTGPU_LIB_PATH -Wl,-rpath $$SIFTGPU_LIB_PATH -lsiftgpu -lCg -lCgGL -lGLEW -lglut -lIL

        HEADERS += $$PWD/qvcuda/qvsiftgpu/qvsiftgpu.h

        SOURCES += $$PWD/qvcuda/qvsiftgpu/qvsiftgpu.cpp
    }
}
