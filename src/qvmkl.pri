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
#   File qvmkl.pri
#

!qvmkl_available {
    CONFIG += qvmkl_available qvlapack_available

    message(Included module: qvmkl)

    DEFINES += MKL_AVAILABLE BLAS_AVAILABLE LAPACK_AVAILABLE

    !qvcomposer {
        MKL_INCLUDE_PATH = $$MKL_PATH/include
        # NOTE: MKL_LIB_PATH has to be specified directly in the config.pri file (see config.pri.example)
    }

    !exists($$MKL_INCLUDE_PATH): \
        error(In module qvmkl: Include files directory was not found at the specified path \
              for the MKL library: $$MKL_INCLUDE_PATH . Perhaps it is not the installation \
              directory for the MKL?)

    !exists($$MKL_LIB_PATH): \
        error(In module qvmkl: Library binaries directory was not found at the specified \
              path for the MKL library: $$MKL_LIB_PATH . Did you choose the 32/64/em64t \
              version correctly?)

    INCLUDEPATH += $$MKL_INCLUDE_PATH

    message(* Path to MKL include files: $$MKL_INCLUDE_PATH)

    message(* Path to MKL library binaries: $$MKL_LIB_PATH)

    unix {
	LIBS += -L$$MKL_LIB_PATH -Wl,-rpath=$$MKL_LIB_PATH

        # Depending on the architecture, we should link to different binaries.
        exists($$find(MKL_LIB_PATH, 64)):   LIBS += -lmkl_intel_ilp64
        exists($$find(MKL_LIB_PATH, 32)):   LIBS += -lmkl_intel

	LIBS += -lmkl_sequential -lmkl_core

        # Depending on the MKL version, the linked Lapack can be different.
	# Already included in 'libmkl_core':
        #exists($$MKL_LIB_PATH/libmkl_lapack.so):    LIBS += -lmkl_lapack
        #exists($$MKL_LIB_PATH/libmkl_lapack95.so):  LIBS += -lmkl_lapack95

        # Depending on the architecture, we should link to different binaries.
        exists($$find(MKL_LIB_PATH, 64)):   LIBS += -lmkl_solver_ilp64_sequential
        exists($$find(MKL_LIB_PATH, 32)):   LIBS += -lmkl_solver_sequential
    } else {
        error(MKL currently supported only in Linux systems)
    }
}
