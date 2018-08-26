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
#   File qvlapack.pri
#

!qvlapack_available : !qvmkl {
    CONFIG += qvlapack_available

    message(Included module: qvlapack)

    message(* LAPACK version used: $$LAPACK_VERSION)

    DEFINES += LAPACK_AVAILABLE

    unix {
        contains(LAPACK_VERSION, DYNAMIC) {
            message( "* Using dynamic standard version of LAPACK" )

            !exists(/usr/lib/liblapack.so): \
                error(In module qvlapack: LAPACK dynamic standard library was not found in /usr/lib/liblapack.so)
            !exists(/usr/lib/libblas.so): \
                error(In module qvlapack: LAPACK dynamic standard library was not found in /usr/lib/libblas.so)

            LIBS += -llapack -lblas
        }

        contains(LAPACK_VERSION, STATIC-ATLAS) {
            message( "* Using static ATLAS version of LAPACK" )

            !exists($$ATLAS_LIBRARY_PATH/libatlas.a):        \
                error(In module qvlapack: file 'libatlas.a' was not found in base directory $$ATLAS_LIBRARY_PATH)
            !exists($$ATLAS_LIBRARY_PATH/libcblas.a):        \
                error(In module qvlapack: file 'libcblas.a' was not found in base directory $$ATLAS_LIBRARY_PATH)
            !exists($$ATLAS_LIBRARY_PATH/libf77blas.a):      \
                error(In module qvlapack: file 'libf77blas.a' was not found in base directory $$ATLAS_LIBRARY_PATH)
            !exists($$ATLAS_LIBRARY_PATH/atlas/libblas.a):   \
                error(In module qvlapack: file 'atlas/libblas.a' was not found in base directory $$ATLAS_LIBRARY_PATH)
            !exists($$ATLAS_LIBRARY_PATH/atlas/liblapack.a): \
                error(In module qvlapack: file 'atlas/liblapack.a' was not found in base directory $$ATLAS_LIBRARY_PATH)

            STATICLIBS +=   $$ATLAS_LIBRARY_PATH/atlas/liblapack.a \
                            $$ATLAS_LIBRARY_PATH/libatlas.a        \
                            $$ATLAS_LIBRARY_PATH/libcblas.a        \
                            $$ATLAS_LIBRARY_PATH/libf77blas.a      \
                            $$ATLAS_LIBRARY_PATH/liblapack_atlas.a \
                            $$ATLAS_LIBRARY_PATH/atlas/libblas.a

            LIBS += -lgfortran
        }

        !contains(LAPACK_VERSION, DYNAMIC):!contains(LAPACK_VERSION, STATIC-ATLAS) {
	error("In module qvlapack: no LAPACK version is selected. Uncomment one of the 'LAPACK_VERSION' definitions in the 'config.pri' file.)
	}
    }
}
