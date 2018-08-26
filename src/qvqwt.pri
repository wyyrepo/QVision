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
#   File qvqwt.pri
#

!qvqwt_available {
    CONFIG += qvqwt_available

    message(Included module: qvqwt)

    win32:DEFINES += QT_DLL QWT_DLL

    DEFINES +=  QVQWT

    # Eliminate suffixes and prefixes to obtain the library name
    QWT_LIB_DIR = $$dirname(QWT_LIB_BINARY)
    QWT_LIB_NAME = $$basename(QWT_LIB_BINARY)
    QWT_LIB_NAME = $$replace(QWT_LIB_NAME, .so$, )
    QWT_LIB_NAME = $$replace(QWT_LIB_NAME, .a$, )
    QWT_LIB_NAME = $$replace(QWT_LIB_NAME, ^lib, )

    !exists($$QWT_INCLUDE): \
            error(In module qvqwt: Specified QWT include directory ($$QWT_INCLUDE) does not exists. \
                  Set a correct path at the file 'config.pri'.)
    !exists($$QWT_LIB_BINARY): \
            error(In module qvqwt: Specified QWT library binary ($$QWT_LIB_BINARY) does not exists. \
                  Set a correct path at the file 'config.pri'.)

    message(* Path to QWT include directory: $$QWT_INCLUDE)
    message(* Path to QWT library binary: $$QWT_LIB_BINARY)

    INCLUDEPATH += $$QWT_INCLUDE

    LIBS += -L$$QWT_LIB_DIR -l$$QWT_LIB_NAME

    !icc:LIBS += -Wl,-rpath=$$QWT_LIB_DIR

    HEADERS +=  $$PWD/qvblockprogramming/qvguiblocks/qvplot.h                  \
                $$PWD/qvblockprogramming/qvguiblocks/qvcpuplot.h               \
                $$PWD/qvblockprogramming/qvguiblocks/qvnumericplot.h           \
                $$PWD/qvblockprogramming/qvguiblocks/qvhistogramplot.h         \
                $$PWD/qvblockprogramming/qvguiblocks/qvfunctionplot.h          \
                $$PWD/qvblockprogramming/qvguiblocks/qvdefaultgui.h            \
                $$PWD/qvblockprogramming/qvguiblocks/qvblockinterfacesmall.h   \
                $$PWD/qvblockprogramming/qvguiblocks/qvparamwidget.h           \
                $$PWD/qvblockprogramming/qvguiblocks/qvparamsinspectorwidget.h \
                $$PWD/qvblockprogramming/qvguiblocks/qvisioninterface.h        \
                $$PWD/qvblockprogramming/qvguiblocks/qvhistogram.h

    SOURCES +=  $$PWD/qvblockprogramming/qvguiblocks/qvplot.cpp                  \
                $$PWD/qvblockprogramming/qvguiblocks/qvcpuplot.cpp               \
                $$PWD/qvblockprogramming/qvguiblocks/qvnumericplot.cpp           \
                $$PWD/qvblockprogramming/qvguiblocks/qvhistogramplot.cpp         \
                $$PWD/qvblockprogramming/qvguiblocks/qvfunctionplot.cpp          \
                $$PWD/qvblockprogramming/qvguiblocks/qvdefaultgui.cpp            \
                $$PWD/qvblockprogramming/qvguiblocks/qvblockinterfacesmall.cpp   \
                $$PWD/qvblockprogramming/qvguiblocks/qvparamsinspectorwidget.cpp \
                $$PWD/qvblockprogramming/qvguiblocks/qvparamwidget.cpp           \
                $$PWD/qvblockprogramming/qvguiblocks/qvisioninterface.cpp        \
                $$PWD/qvblockprogramming/qvguiblocks/qvhistogram.cpp

    # Specific sources for QVision Designer:

    RESOURCES +=  $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/resources/resources.qrc

    HEADERS +=  $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/link.h               \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/asinclink.h          \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/sinclink.h           \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/grouplink.h          \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/sequenlink.h         \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/node.h               \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/groupnode.h          \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/middlenode.h         \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/inputnode.h          \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/outputnode.h         \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/slateview.h          \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/insertaction.h       \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/informer.h           \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/slatewindow.h        \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/qvdesignergui.h            \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/facade/itemproperties.h    \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/facade/itemfactory.h       \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/facade/blockdialog.h       \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/facade/imagecanvasdialog.h \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/facade/camerablockdialog.h

    SOURCES +=  $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/link.cpp               \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/asinclink.cpp          \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/sinclink.cpp           \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/grouplink.cpp          \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/sequenlink.cpp         \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/node.cpp               \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/groupnode.cpp          \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/middlenode.cpp         \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/inputnode.cpp          \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/outputnode.cpp         \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/slateview.cpp          \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/insertaction.cpp       \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/informer.cpp           \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/slate/slatewindow.cpp        \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/qvdesignergui.cpp            \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/facade/itemproperties.cpp    \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/facade/itemfactory.cpp       \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/facade/blockdialog.cpp       \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/facade/imagecanvasdialog.cpp \
                $$PWD/qvblockprogramming/qvguiblocks/qvdesigner/facade/camerablockdialog.cpp
}
