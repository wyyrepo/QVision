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
#   File qvopencv.pri
#

!qvopencv_available {
    CONFIG += qvopencv_available

    message(Included module: qvopencv)

    DEFINES += QVOPENCV

    HEADERS += $$PWD/qvopencv/qvdelaunaytriangulation.h

    isEmpty(OPENCV_PATH) {
        CONFIG += link_pkgconfig   # Enable pkg-config usage through the PKGCONFIG variable.

        PKGCONFIG += opencv      # Include necessary directories and binary files for OpenCV.

        message(* OPENCV_PATH variable is empty. Autoconfiguring with pkg-config)
    } else {
        LIBS += -L$$OPENCV_LIB_PATH -Wl,-rpath $$OPENCV_LIB_PATH

        # Linux case: look for '.so' files first.
        # If no such file is found at the library binary path, look for '.a' files.
        linux-g++|unix {
            LIB_FILES = $$files($$OPENCV_LIB_PATH\lib*.so)
            isEmpty(LIB_FILES):LIB_FILES = $$files($$OPENCV_LIB_PATH\lib*.a)

            # Obtain binary file names by deleting extension and 'lib' prefix from full library file names.
            for(LIB_FILE, LIB_FILES)  {
                LIB_NAME = $$basename(LIB_FILE)
                LIB_NAME = $$replace(LIB_NAME, \.so$, )
                LIB_NAME = $$replace(LIB_NAME, \.a$, )
                LIB_NAME = $$replace(LIB_NAME, ^lib, )
                LIBS += -l$$LIB_NAME
            }
        }

        message(* Path to OpenCV library binaries: $$OPENCV_LIB_PATH)

        message(* Path to OpenCV header files: $$OPENCV_PATH)

        # Windows case: look for '.dev' files first.
        # If no such file is found at the library binary path, look for '.lib' files.
        win32|win64 {
            LIB_FILES += $$files($$OPENCV_LIB_PATH\*.dll)
            isEmpty(LIB_FILES):LIB_FILES += $$files($$OPENCV_LIB_PATH\*.lib)

            # Obtain binary file names by deleting extension from full library file names.
            for(LIB_FILE, LIB_FILES) {
                LIB_NAME = $$basename(LIB_FILE)
                LIB_NAME = $$replace(LIB_NAME, d\.lib$, )
                LIB_NAME = $$replace(LIB_NAME, d\.dll$, )
                LIB_NAME = $$replace(LIB_NAME, \.lib$, )
                LIB_NAME = $$replace(LIB_NAME, \.dll$, )
                LIBS += -l$$LIB_NAME
            }
        }

        isEmpty(LIB_FILES): error(In module qvopencv: no library binary file found at path \
                                  '$$OPENCV_LIB_PATH' specified at variable OPENCV_LIB_PATH)

        # Check that there are header files in the 'include' directory.
        !exists($$OPENCV_PATH\include): error(In module qvopencv: path '$$OPENCV_PATH' specified \
                                              at variable OPENCV_PATH does not exists)
        #INC_FILES=$$files($$OPENCV_PATH\include\*.h)
        #isEmpty(INC_FILES): error(In module qvopencv: no header file found at path '$$OPENCV_PATH/include' specified at variable OPENCV_PATH)

        # Including path to main headers
        INCLUDEPATH += $$OPENCV_PATH\include

        # Including path to modules headers, if they exist
        MODULES = calib3d contrib core features2d ffmpeg flann gpu haartraining highgui imgproc legacy \
                  ml objdetect python traincascade video

        for(module, MODULES) {
            INCLUDEPATH += $$OPENCV_PATH/modules/$${module}/include
        }
    }
}

