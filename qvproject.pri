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
#   File qvproject.pri
#

!qvproject_included {
    CONFIG += qvproject_included

    message("Configuring to compile a QVision application...")

    TEMPLATE = app

    win32:CONFIG += console

    # No need to include the headers and sources of the QVision.
    # Only the path to them:
    HEADERS_BACKUP = $$HEADERS
    SOURCES_BACKUP = $$SOURCES
    FORMS_BACKUP = $$FORMS
    RESOURCES_BACKUP = $$RESOURCES

    include(common.pri)

    HEADERS = $$HEADERS_BACKUP
    SOURCES = $$SOURCES_BACKUP
    FORMS = $$FORMS_BACKUP
    RESOURCES = $$RESOURCES_BACKUP

    # These configs specify the directory where QVision
    # library binary is, with '-L' option for the compiler,
    # and option '-Wl,rpath', for the linker
    unix:LIBS += -L$$PWD/lib/ -lqvision $$STATICLIBS
    win32:LIBS += -L$$PWD/lib/ -lqvision0 $$STATICLIBS
    !qvicc: LIBS += -Wl,-rpath=$$PWD/lib

    message(... configuration complete!)
}

