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
#   File qvip.pri
#

!qvip_available {
    CONFIG += qvip_available

    message(Included module: qvip)

    HEADERS +=  $$PWD/qvip/qvip.h            		\
                $$PWD/qvip/qvimageio.h       		\
                $$PWD/qvip/qvimagebuffer.h   		\
                $$PWD/qvip/qvgenericimage.h  		\
                $$PWD/qvip/qvimage.h         		\
                $$PWD/qvip/qvpolyline.h      		\
                $$PWD/qvip/qvpolylinef.h     		\
                $$PWD/qvip/qvcomponenttree.h 		\
                $$PWD/qvip/qvkeypoint.h      		\
                $$PWD/qvip/qvsiftfeature.h   		\
                $$PWD/qvip/qvmser.h					\
                $$PWD/qvip/qvbriefdetector.h		\
				$$PWD/qvip/fast-C-src-2.1/fast.h

    SOURCES +=  $$PWD/qvip/qvip.cpp            			\
                $$PWD/qvip/qvimageio.cpp       			\
                $$PWD/qvip/qvimagebuffer.cpp   			\
                $$PWD/qvip/qvgenericimage.cpp  			\
                $$PWD/qvip/qvimage.cpp         			\
                $$PWD/qvip/qvpolyline.cpp      			\
                $$PWD/qvip/qvpolylinef.cpp     			\
                $$PWD/qvip/qvcomponenttree.cpp 			\
                $$PWD/qvip/qvsiftfeature.cpp   			\
                $$PWD/qvip/qvmser.cpp					\
                $$PWD/qvip/qvbriefdetector.cpp			\
				$$PWD/qvip/fast-C-src-2.1/fast_10.cpp	\
				$$PWD/qvip/fast-C-src-2.1/fast_11.cpp	\
				$$PWD/qvip/fast-C-src-2.1/fast_12.cpp	\
				$$PWD/qvip/fast-C-src-2.1/fast_9.cpp	\
				$$PWD/qvip/fast-C-src-2.1/fast.cpp		\
				$$PWD/qvip/fast-C-src-2.1/nonmax.cpp	

}
