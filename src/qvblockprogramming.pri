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
#   File qvblockprogramming.pri
#

!qvblockprogramming_available {
    CONFIG += qvblockprogramming_available

    message(Included module: qvblockprogramming)

    # Forms
    RESOURCES = $$PWD/resources/qvision.qrc

    FORMS +=    $$PWD/ui/qvprocessingblockformsmall.ui    \
                $$PWD/ui/qvvideoreaderblockwidget.ui      \
                $$PWD/ui/qvvideoreaderblockwidgetsmall.ui

    # Main classes
    HEADERS +=  $$PWD/qvblockprogramming/qvguiblocks/qvimagecanvas.h \
                $$PWD/qvblockprogramming/qvapplication.h             \
                $$PWD/qvblockprogramming/qvprocessingblock.h         \
                $$PWD/qvblockprogramming/qvpropertycontainer.h       \
                $$PWD/qvblockprogramming/qvpropertycontainerchange.h \
                $$PWD/qvblockprogramming/qvcpustat.h                 \
                $$PWD/qvblockprogramming/qvcpustatcontroler.h

    SOURCES +=  $$PWD/qvblockprogramming/qvguiblocks/qvimagecanvas.cpp \
                $$PWD/qvblockprogramming/qvapplication.cpp             \
                $$PWD/qvblockprogramming/qvprocessingblock.cpp         \
                $$PWD/qvblockprogramming/qvpropertycontainer.cpp       \
                $$PWD/qvblockprogramming/qvpropertycontainerchange.cpp \
                $$PWD/qvblockprogramming/qvcpustat.cpp                 \
                $$PWD/qvblockprogramming/qvcpustatcontroler.cpp

    # GUI
    HEADERS +=  $$PWD/qvblockprogramming/qvguiblocks/qvvideoreaderblockwidget.h      \
                $$PWD/qvblockprogramming/qvguiblocks/qvvideoreaderblockwidgetsmall.h \
                $$PWD/qvblockprogramming/qvguiblocks/qvcanvas.h                      \
                $$PWD/qvblockprogramming/qvguiblocks/qvgui.h                         \
                $$PWD/qvblockprogramming/qvguiblocks/qvindexedstringlist.h           \
                $$PWD/qvblockprogramming/qvguiblocks/qv3dcanvas.h                    \
                $$PWD/qvblockprogramming/qvguiblocks/qv3dmodel.h

    SOURCES +=  $$PWD/qvblockprogramming/qvguiblocks/qvvideoreaderblockwidget.cpp      \
                $$PWD/qvblockprogramming/qvguiblocks/qvvideoreaderblockwidgetsmall.cpp \
                $$PWD/qvblockprogramming/qvguiblocks/qvcanvas.cpp                      \
                $$PWD/qvblockprogramming/qvguiblocks/qvgui.cpp                         \
                $$PWD/qvblockprogramming/qvguiblocks/qvindexedstringlist.cpp           \
                $$PWD/qvblockprogramming/qvguiblocks/qv3dcanvas.cpp                    \
                $$PWD/qvblockprogramming/qvguiblocks/qv3dmodel.cpp

    # IO blocks
    HEADERS +=  $$PWD/qvblockprogramming/qvioblocks/qvvideoreaderblock.h               #\
                #$$PWD/qvblockprogramming/qvioblocks/qvvideoreaderblock.h

    SOURCES +=  $$PWD/qvblockprogramming/qvioblocks/qvvideoreaderblock.cpp              #\
                #$$PWD/qvblockprogramming/qvioblocks/qvvideoreaderblock.cpp

    # Processing blocks
    SOURCES +=  $$PWD/qvblockprogramming/qvprocessingblocks/qvimageretarderblock.cpp    \
                $$PWD/qvblockprogramming/qvprocessingblocks/qvmserdetector.cpp          \
                $$PWD/qvblockprogramming/qvprocessingblocks/qvsynchronizerblock.cpp     \
                $$PWD/qvblockprogramming/qvprocessingblocks/qvpointblock.cpp

    HEADERS +=  $$PWD/qvblockprogramming/qvprocessingblocks/qvimageretarderblock.h \
                $$PWD/qvblockprogramming/qvprocessingblocks/qvmserdetector.h       \
                $$PWD/qvblockprogramming/qvprocessingblocks/qvsynchronizerblock.h  \
                $$PWD/qvblockprogramming/qvprocessingblocks/qvpointblock.h

    # IPP dependant blocks
    qvcomposer : exists($$COMPOSER_PATH/ipp) {
        CONFIG += qvippcomposer
    }
    qvipp | qvippcomposer {
        HEADERS +=  $$PWD/qvblockprogramming/qvprocessingblocks/qvimageresizerblock.h    \
#                    $$PWD/qvblockprogramming/qvioblocks/qvyuv4mpeg2readerblock.h         \
                    $$PWD/qvblockprogramming/qvioblocks/qvyuv4mpeg2writerblock.h         \
                    $$PWD/qvblockprogramming/qvprocessingblocks/qvippblocks.h            \
                    $$PWD/qvblockprogramming/qvprocessingblocks/qvimagemeansblock.h      \
                    $$PWD/qvblockprogramming/qvprocessingblocks/qvhessianpointdetector.h \
                    $$PWD/qvblockprogramming/qvprocessingblocks/qvharrispointdetector.h  \
                    $$PWD/qvblockprogramming/qvprocessingblocks/qvcannyedgedetector.h    \
#                    $$PWD/qvblockprogramming/qvioblocks/qvdirreaderblock.h

        SOURCES +=  $$PWD/qvblockprogramming/qvprocessingblocks/qvimageresizerblock.cpp    \
 #                   $$PWD/qvblockprogramming/qvioblocks/qvyuv4mpeg2readerblock.cpp         \
                    $$PWD/qvblockprogramming/qvioblocks/qvyuv4mpeg2writerblock.cpp         \
                    $$PWD/qvblockprogramming/qvprocessingblocks/qvippblocks.cpp            \
                    $$PWD/qvblockprogramming/qvprocessingblocks/qvimagemeansblock.cpp      \
                    $$PWD/qvblockprogramming/qvprocessingblocks/qvhessianpointdetector.cpp \
                    $$PWD/qvblockprogramming/qvprocessingblocks/qvharrispointdetector.cpp  \
                    $$PWD/qvblockprogramming/qvprocessingblocks/qvcannyedgedetector.cpp    \
#                    $$PWD/qvblockprogramming/qvioblocks/qvdirreaderblock.cpp
    }

    # MPlayer dependant blocks
#    qvmplayer {
#        HEADERS +=  $$PWD/qvblockprogramming/qvioblocks/qvmplayerreaderblock.h
#
#        SOURCES +=  $$PWD/qvblockprogramming/qvioblocks/qvmplayerreaderblock.cpp
#    }

    # GSL/LAPACK dependant blocks
    qvgsl|qvlapack {
        HEADERS +=    $$PWD/qvblockprogramming/qvprocessingblocks/qvplanarrectifierblock.h

        SOURCES +=    $$PWD/qvblockprogramming/qvprocessingblocks/qvplanarrectifierblock.cpp
    }

    # OpenCV dependant blocks
#    qvopencv {
#        HEADERS +=    $$PWD/qvblockprogramming/qvioblocks/qvopencvreaderblock.h
#
#        SOURCES +=    $$PWD/qvblockprogramming/qvioblocks/qvopencvreaderblock.cpp
#    }

}
