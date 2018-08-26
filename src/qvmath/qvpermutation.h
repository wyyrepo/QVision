/*
 *	Copyright (C) 2007, 2008, 2009, 2010, 2011, 2012. PARP Research Group.
 *	<http://perception.inf.um.es>
 *	University of Murcia, Spain.
 *
 *	This file is part of the QVision library.
 *
 *	QVision is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as
 *	published by the Free Software Foundation, version 3 of the License.
 *
 *	QVision is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with QVision. If not, see <http://www.gnu.org/licenses/>.
 */

/// @file qvpermutation.h
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#ifndef QVPERMUTATION_H
#define QVPERMUTATION_H

#include <math.h>
#include <iostream>
#include <QVector>
#include <qvmath.h>

/*!
@class QVPermutation qvmath/qvpermutation.h QVPermutation
@brief Implementation of permutations.

@see @ref MatricesAndVectors

@ingroup qvmath
*/
class QVPermutation: public QVector<int> {
    public:
    /// @brief Default constructor for QVPermutation
    ///
    /// @param size size of the permutation
    /// @param initialize_with_identity if true, returns an identity permutation; if false, permutation will be uninitialized
    QVPermutation(const int n = 0, bool initialize_with_identity = false): QVector<int>(n) {
            if(initialize_with_identity)
                    for(int i=0;i<n;i++)
                            operator[](i) = i;
    }

    /// @brief Check consistency of permutation
    ///
    /// @returns True if a valid permutation, false otherwise
    bool checkConsistency() const;

    /// @brief Conversion to QVMatrix
    ///
    /// This function generates a QVMatrix from a QVPermutation, which will only
    /// contain ones and zeros, with exactly one nonzero element per row and per
    /// column.
    QVMatrix toMatrix() const;

    /// @brief Signature of a permutation
    ///
    /// Returns the signature of a permutation (-1 if it has odd parity, +1 otherwise).
    ///
    /// @returns signature of permutation
    int signature() const;

    /// @brief Conversion from QVMatrix
    ///
    /// This function generates a QVPermutation from a QVMatrix, where the
    /// maximum elements in each row, when substituted by ones, with the rest
    /// of elements in that row substituted by zeros, generate a permutation
    /// matrix. Otherwise it will fail and abort execution.
    ///
    /// @param matrix matrix to get permutation from.
    static QVPermutation fromMatrix(const QVMatrix &matrix);

    ///////////////////////////////

    /// @brief Element access operator
    ///
    /// @param index main index value for data access
    inline int &operator()(const int index)
            { return operator[](index); }

    /// @brief Overloaded version of element access operator
    ///
    /// @param index main index value for data access
    inline int operator()(const int index) const
            { return operator[](index); }

};

/// @brief Output stream operator for QVPermutaion
///
/// @ingroup qvmath
std::ostream& operator<<( std::ostream &os, const QVPermutation &vector );

#endif
