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

#############################
#
#   File qvsfm.pri
#

!qvsfm_available: qvmatrixalgebra_available {
    CONFIG += qvsfm_available

    message(Included module: qvsfm)

	#include($$PWD/qvsfm/laSBA/sba-1.6//sba.pri)

    DEFINES += QVSFM QVGEA_AVAILABLE QVLASBA_AVAILABLE

    HEADERS +=  $$PWD/qvsfm/qvsfm.h                              	\
				$$PWD/qvsfm/qvbundler.h                            	\
                $$PWD/qvsfm/readSfMReconstruction.h              	\
                $$PWD/qvsfm/qvgea/geaoptimization.h              	\
                $$PWD/qvsfm/qvgea/quaternionEssentialEvaluation.h	\
                $$PWD/qvsfm/qvgea/so3EssentialEvaluation.h			\
     #           $$PWD/qvsfm/laSBA/laSBAWrapper.h

    SOURCES +=  $$PWD/qvsfm/qvsfm.cpp                               \
				$$PWD/qvsfm/qvbundler.cpp                          	\
                $$PWD/qvsfm/readSfMReconstruction.cpp               \
                $$PWD/qvsfm/qvgea/geaoptimization.cpp               \
                $$PWD/qvsfm/qvgea/quaternionEssentialEvaluation.cpp \
                $$PWD/qvsfm/qvgea/so3EssentialEvaluation.cpp		\
      #          $$PWD/qvsfm/laSBA/laSBAWrapper.cpp

}
