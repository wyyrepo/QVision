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
#   File qvmath.pri
#

!qvmath_available {
    CONFIG += qvmath_available

    message(Included module: qvmath)

    LIBS += -lm

    HEADERS +=  $$PWD/qvmath/qvmath.h                \
                $$PWD/qvmath/qvdisjointset.h         \
                $$PWD/qvmath/qvrationalnumber.h      \
                $$PWD/qvmath/qvblasdatabuffer.h      \
                $$PWD/qvmath/qvmatrix.h              \
                $$PWD/qvmath/qvvector.h              \
                $$PWD/qvmath/qvcomplex.h             \
                $$PWD/qvmath/qvsparseblockmatrix.h   \
                $$PWD/qvmath/qvquaternion.h          \
                $$PWD/qvmath/qv2dmap.h               \
                $$PWD/qvmath/qvfunction.h            \
                $$PWD/qvmath/qvpermutation.h         \
                $$PWD/qvmath/qvcombinationiterator.h \
                $$PWD/qvmath/qvvectormap.h           \
                $$PWD/qvmath/qvsampleconsensus.h     \
                $$PWD/qvmath/qvnumericalanalysis.h   \
                $$PWD/qvmath/qv3dpointf.h            \
                $$PWD/qvmath/qv3dpolylinef.h         \
                $$PWD/qvmath/qvdirectedgraph.h       \
                $$PWD/qvmath/qvbitcount.h

    SOURCES +=  $$PWD/qvmath/qvmath.cpp                \
                $$PWD/qvmath/qvdisjointset.cpp         \
                $$PWD/qvmath/qvrationalnumber.cpp      \
                $$PWD/qvmath/qvblasdatabuffer.cpp      \
                $$PWD/qvmath/qvmatrix.cpp              \
                $$PWD/qvmath/qvvector.cpp              \
                $$PWD/qvmath/qvcomplex.cpp             \
                $$PWD/qvmath/qvsparseblockmatrix.cpp   \
                $$PWD/qvmath/qvquaternion.cpp          \
                $$PWD/qvmath/qv2dmap.cpp               \
                $$PWD/qvmath/qvfunction.cpp            \
                $$PWD/qvmath/qvpermutation.cpp         \
                $$PWD/qvmath/qvcombinationiterator.cpp \
                $$PWD/qvmath/qvvectormap.cpp           \
                $$PWD/qvmath/qvsampleconsensus.cpp     \
                $$PWD/qvmath/qvnumericalanalysis.cpp   \
                $$PWD/qvmath/qvdirectedgraph.cpp       \
                $$PWD/qvmath/qvbitcount.cpp

    # This functionality requires BLAS
    qvblas {
        HEADERS +=  $$PWD/qvmath/qvtensorindex.h     \
                    $$PWD/qvmath/qvtensorindexator.h \
                    $$PWD/qvmath/qvtensor.h

        SOURCES +=  $$PWD/qvmath/qvtensorindex.cpp     \
                    $$PWD/qvmath/qvtensorindexator.cpp \
                    $$PWD/qvmath/qvtensor.cpp
    }

    # This functionality requires either GSL, LAPACK or MKL present
    qvgsl | qvlapack | qvmkl {
        CONFIG  +=  qvmatrixalgebra_available

        DEFINES +=  QVMATRIXALGEBRA_AVAILABLE

        HEADERS +=  $$PWD/qvmath/qveuclideanmapping3.h      \
                    $$PWD/qvmath/qvmatrixalgebra.h          \
                    $$PWD/qvmath/qvprojective.h             \
                    $$PWD/qvmath/qvepipolar.h               \
                    $$PWD/qvmath/qvreprojectionerror.h      \
                    $$PWD/qvmath/qvstatistics.h             \
                    $$PWD/qvmath/qvukf.h

        SOURCES +=  $$PWD/qvmath/qveuclideanmapping3.cpp    \
                    $$PWD/qvmath/qvmatrixalgebra.cpp        \
                    $$PWD/qvmath/qvprojective.cpp           \
                    $$PWD/qvmath/qvepipolar.cpp             \
                    $$PWD/qvmath/qvreprojectionerror.cpp    \
                    $$PWD/qvmath/qvstatistics.cpp           \
                    $$PWD/qvmath/qvukf.cpp
    }
}
