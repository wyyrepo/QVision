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
#   File qvcuda.pri
#

!qvcuda_available {
    CONFIG += qvcuda_available

    message(Included module: qvcuda)

    DEFINES += QVCUDA

    INCLUDEPATH += $$CUDA_DIR/include $$CUDA_UTIL_DIR/common/inc

    QMAKE_LIBDIR += $$CUDA_DIR/lib $$CUDA_UTIL_DIR/lib

    LIBS += -lcudart -lcutil -Wl,-rpath $$CUDA_DIR/lib

    cuda.output = ${OBJECTS_DIR}${QMAKE_FILE_BASE}_cuda.obj
    cuda.commands = $${CUDA_DIR}/bin/nvcc -c -Xcompiler       \
                    $$join(QMAKE_CXXFLAGS,",")                \
                    $$join(QMAKE_INCDIR,'" -I "','-I "','"')  \
                    $$join(INCLUDEPATH,'" -I "','-I "','"')   \
                    ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}
    cuda.dependcy_type = TYPE_C
    cuda.depend_command = nvcc -M -Xcompiler $$join(QMAKE_CXXFLAGS,",") \
                            $$join(INCLUDEPATH,'" -I "','-I "','"')     \
                            ${QMAKE_FILE_NAME} | sed "s,^.*: ,," | sed "s,^ *,," | tr -d '\\\n'
    cuda.input = CUDA_SOURCES
    QMAKE_EXTRA_UNIX_COMPILERS += cuda

    SOURCES +=  $$PWD/qvcuda/qvcudaip.cpp   \
                $$PWD/qvcuda/qvcudautils.cpp

    HEADERS +=  $$PWD/qvcuda/qvcudaip.h     \
                $$PWD/qvcuda/qvcudautils.h  \
                $$PWD/qvcuda/qvcudaimage.h  \
                $$PWD/qvcuda/qvcudaipD.h

    CUDA_SOURCES +=   $$PWD/qvcuda/qvcudaipD.cu

    #install_include_qvcuda.path = $$PWD/qvcuda
    #install_include_qvcuda.files = qvcuda/*.h
    #INSTALLS += install_include_qvcuda
}
