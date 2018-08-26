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
#   File qvision.pro
#

######################################################################
# Include main configuration file (common to library and applications)

include(common.pri)

######################################################################
# Basic configuration for the library

CONFIG += QVISION

VERSION = 0.8.1

message(QVision library version: $$VERSION)

message(Install path set to: $$INSTALL_PATH)

TEMPLATE = lib
TARGET = qvision

HEADERS += src/qvdefines.h
SOURCES += src/qvdefines.cpp

win32 : CONFIG += console # Windows console output

######################################################################
# Directories

RCC_DIR = build/rcc/
MOC_DIR = build/moc/
OBJECTS_DIR = build/obj/
DESTDIR = lib/
UI_DIR = src/ui/

#####################################################################
# Documentation

api_doc.target = doc/html
api_doc.commands = doxygen Doxyfile;

QMAKE_EXTRA_TARGETS += api_doc

OTHER_FILES += src/doxygen/GSL-interoperability.dox                         \
               src/doxygen/manual.0.0.mainpage.dox                          \
               src/doxygen/manual.0.1.qvision-overview.dox                  \
               src/doxygen/manual.0.2.download-and-setup.dox                \
               src/doxygen/manual.0.3.manual-walkthrough.dox                \
               src/doxygen/manual.1.hello-world.dox                         \
               src/doxygen/manual.1.image-io.dox                            \
               src/doxygen/manual.1.image-processing.dox                    \
               src/doxygen/manual.1.matrices-and-vectors.dox                \
               src/doxygen/manual.1.the-image-class.dox                     \
               src/doxygen/manual.2.GSL-interoperability.dox                \
               src/doxygen/manual.2.Intel-IPP-interoperability.dox          \
               src/doxygen/manual.2.Octave-interoperability.dox             \
               src/doxygen/manual.2.OpenCV-interoperability.dox             \
               src/doxygen/manual.3.1.introduction-to-block-programming.dox \
               src/doxygen/manual.3.2.advanced-example-block-programming.dox\
               src/doxygen/manual.3.3.creating-custom-blocks.dox            \
               src/doxygen/manual.3.4.block-synchronization.dox             \
               src/doxygen/manual.3.5.the-gui.dox                           \
               src/doxygen/manual.3.6.bis.command-line-parameters.dox       \
               src/doxygen/manual.3.8.the-designer-gui.dox                  \
               src/doxygen/qvblockprogramming.dox                           \
               src/doxygen/qvcuda.dox                                       \
               src/doxygen/qvip.dox                                         \
               src/doxygen/qvipp.dox                                        \
               src/doxygen/qvltmser.dox                                     \
               src/doxygen/qvmath.dox                                       \
               src/doxygen/qvmplayer.dox                                    \
               src/doxygen/qvprojective.dox                                 \
               src/doxygen/qvqwt.dox                                        \
               src/doxygen/qvros.dox                                        \
               src/doxygen/qvsiftgpu.dox                                    \
               src/doxygen/qvsfm.dox

OTHER_FILES += config.pri.example qvproject.pri

######################################################################
# Installation (path, include files, additional files and install directive)

install_base.path = $$INSTALL_PATH
install_base.files = *.pri README COPYING COPYING.LESSER lib

install_include.path = $$INSTALL_PATH/src/
install_include.files = src/q*

INSTALLS += install_base install_include


