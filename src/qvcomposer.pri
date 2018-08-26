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
#   File qvcomposer.pri
#

!qvcomposer_available {
    CONFIG += qvcomposer_available

    message(Included module: qvcomposer)

    !exists($$COMPOSER_PATH): error(Specified path for the Intel Composer does not exists: $$COMPOSER_PATH)

    exists($$COMPOSER_PATH/ipp) {
        message(* IPP found at $$COMPOSER_PATH/ipp)
        CONFIG += qvipp
    }

    exists($$COMPOSER_PATH/mkl) {
        message(* MKL found at $$COMPOSER_PATH/mkl)
        CONFIG += qvmkl
    }

    arch64 {
        message(* Linking to 64 bits library binaries)
        ARCH_PREFIX = intel64
    } else {
        message(* Linking to 32 bits library binaries)
        ARCH_PREFIX = ia32
    }

    COMPOSE_LIB_PATH = $$COMPOSER_PATH/lib/$$ARCH_PREFIX
    COMPOSE_LIB_PATH2 = $$COMPOSER_PATH/compiler/lib/$$ARCH_PREFIX
    IPP_INCLUDE_PATH = $$COMPOSER_PATH/ipp/include
    IPP_LIB_PATH     = $$COMPOSER_PATH/ipp/lib/$$ARCH_PREFIX
    MKL_INCLUDE_PATH = $$COMPOSER_PATH/mkl/include
    MKL_LIB_PATH     = $$COMPOSER_PATH/mkl/lib/$$ARCH_PREFIX

    LIBS +=	-L$$COMPOSE_LIB_PATH -Wl,-rpath=$$COMPOSE_LIB_PATH		\
			-L$$COMPOSE_LIB_PATH2 -Wl,-rpath=$$COMPOSE_LIB_PATH2	\
			-liomp5
}

