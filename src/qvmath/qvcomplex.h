/*
 *	Copyright (C) 2011, 2012. PARP Research Group.
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

/// @file
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#include <math.h>
#include <iostream>
#include <QPointF>
#ifndef QVCOMPLEX_H
#define QVCOMPLEX_H

/*!
@class QVComplex qvmath/qvcomplex.h QVComplex
@brief Implementation of complex numbers

@ingroup qvmath
*/
class QVComplex
    {
    private:
        double _real, _imaginary;

    public:

        // ------------------
        // Constructors

        /// @brief Default constructor
        ///
        /// Constructs a complex number object equal to zero.
        ///
        QVComplex();

        /// @brief Copy constructor.
        ///
        /// Creates a complex object copying the content from a given one.
        /// @param complex complex to be copied.
        QVComplex(const QVComplex &complex);

        /// @brief Common constructor
        ///
        /// Creates a new complex number object, specifying the real and imaginary parts.
        ///
        /// @param real Real part of the complex number.
        /// @param imaginary Imaginary part of the complex number.
        QVComplex(const double real, const double imaginary = 0.0);

        /// @brief Constructor from a QPointF
        ///
        /// Creates a new complex number object, obtaining its components from a point object.
        /// The real part of the complex number will be obtained from the <i>x</i> component of the point, and
        /// the imaginary part from the <i>y</i> component.
        ///
        /// @param point Point containing the components of the new complex number.
        QVComplex(const QPointF &point);

        /// @brief Copy operator
        ///
        /// @param complex complex to be copied.
        QVComplex & operator=(const QVComplex &complex);

        // ------------------------------------
        // Complex-complex operators

        /// @brief Complex-complex equality operator
        ///
        /// @param complex term for the compare operation.
        /// @return true if the given complex has same dimensions and equal content of the data buffer, else false.
        bool operator==(const QVComplex &complex) const;

        /// @brief Complex-complex incremental operator
        ///
        /// @param complex addendum to the actual complex
        /// @return true if the given complex has same dimensions and equal content of the data buffer, else false.
        QVComplex & operator+=(const QVComplex &complex);

        /// @brief Complex-complex unequality operator
        ///
        /// @param complex term for the compare operation.
        /// @return false if the given complex has same dimensions and equal content of the data buffer, else true.
        bool operator!=(const QVComplex &complex) const;

        /// @brief Complex-complex product operator
        ///
        /// @param complex factor for the product operation.
        QVComplex operator*(const QVComplex &complex) const;

        /// @brief Complex-complex division
        ///
        /// @param complex factor for the operation.
        QVComplex operator/(const QVComplex &complex) const;

        /// @brief Complex-complex addition operator
        ///
        /// @param complex term for the operation.
        QVComplex operator+(const QVComplex &complex) const;

        /// @brief Complex-complex substraction operator
        ///
        /// @param complex subtrahend for the operation.
        QVComplex operator-(const QVComplex &complex) const;

        /// @brief Obtains the additive inverse of the complex
        ///
        /// Obtains a complex changing the sign of its elements.
        QVComplex operator-() const;

        // Complex-scalar operators

        /// @brief Complex-scalar product
        ///
        /// @param value factor for the operation.
        QVComplex operator*(const double value) const;

        /// @brief Complex-scalar division operator
        ///
        /// @param value divider for the operation.
        QVComplex operator/(const double value) const;

        /// @brief Complex-scalar addition
        ///
        /// @param value addendum for the operation.
        QVComplex operator+(const double value) const;

        /// @brief Complex-scalar substraction operator
        ///
        /// @param value value to substract.
        QVComplex operator-(const double value) const;

        /// @brief Gets the <a href="http://en.wikipedia.org/wiki/Norm_%28mathematics%29">norm<sub>2</sub></a> for complex.
        ///
        /// @return norm-2 of the complex.
        double norm2() const;

        /// @brief Get real component of complex value.
        inline double real() const			{ return _real; }

        /// @brief Get imaginary component of complex value.
        inline double imaginary() const		{ return _imaginary; }

        /// @brief Get reference to the real component of complex value.
        inline double &real()				{ return _real; }

        /// @brief Get reference to the imaginary component of complex value.
        inline double &imaginary()			{ return _imaginary; }

        /// @brief Creates the unit imaginary value
        ///
        /// @return complex number containing a unit value for the imaginary coordinate, and zero value for the real coordinate.
        static QVComplex i();
    };

/// @brief Prints the complex number contained in a complex number objecto to an output stream.
/// @ingroup qvmath
std::ostream& operator << ( std::ostream &os, const QVComplex &complex );

#endif

