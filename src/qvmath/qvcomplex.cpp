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

#include <qvmath.h>
#include <QVComplex>

//////////////////////////
// Constructors

QVComplex::QVComplex():_real(0.0), _imaginary(0.0)							{ }
QVComplex::QVComplex(const QVComplex &complex): _real(complex._real), _imaginary(complex._imaginary)	{ }
QVComplex::QVComplex(const double real, const double imaginary): _real(real), _imaginary(imaginary)	{ }
QVComplex::QVComplex(const QPointF &point): _real(point.x()), _imaginary(point.y())			{ }

QVComplex & QVComplex::operator=(const QVComplex &complex)
    {
    _real = complex._real;
    _imaginary = complex._imaginary;
    return *this;
    }

bool QVComplex::operator==(const QVComplex &complex)		const	{ return (_real == complex._real) and (_imaginary == complex._imaginary);	};
QVComplex & QVComplex::operator+=(const QVComplex &complex)		{ _real += complex._real; _imaginary += complex._imaginary; return *this; }
bool QVComplex::operator!=(const QVComplex &complex)		const	{ return (_real != complex._real) or (_imaginary != complex._imaginary);	};

QVComplex QVComplex::operator*(const QVComplex &complex)	const
    {
    /* Maple code
    n := (r1 + i1*I) * (r2 + i2*I):
    evalc(Re(n));
    evalc(Im(n));
    */
    return QVComplex(	_real * complex._real - _imaginary * complex._imaginary,
                _real * complex._imaginary + _imaginary * complex._real);
    };

QVComplex QVComplex::operator/(const QVComplex &complex)	const
    {
    /* Maple code
    n := (r1 + i1*I) / (r2 + i2*I):
    evalc(Re(n));
    evalc(Im(n));
    */
    const double denominator = POW2(complex._real) + POW2(complex._imaginary);
    return QVComplex(	(_real * complex._real + _imaginary * complex._imaginary) / denominator,
            (_imaginary * complex._real - _real * complex._imaginary) / denominator);
    }

QVComplex QVComplex::operator+(const QVComplex &complex)	const	{ return QVComplex(_real + complex._real, _imaginary + complex._imaginary);	};
QVComplex QVComplex::operator-(const QVComplex &complex)	const	{ return QVComplex(_real - complex._real, _imaginary - complex._imaginary);	};
QVComplex QVComplex::operator-() 				const	{ return QVComplex(-_real, -_imaginary); 	};
QVComplex QVComplex::operator*(const double value)		const	{ return QVComplex(value * _real, value * _imaginary); 	};
QVComplex QVComplex::operator/(const double value) 		const	{ return QVComplex(_real / value, _imaginary / value); 	};
QVComplex QVComplex::operator+(const double value) 		const	{ return QVComplex(_real + value, _imaginary); 	};
QVComplex QVComplex::operator-(const double value) 		const	{ return QVComplex(_real - value, _imaginary); 	};
double QVComplex::norm2()					const	{ return sqrt( POW2(_real) + POW2(_imaginary) ); }
QVComplex QVComplex::i()						{ return QVComplex( 0.0, 1.0); }


//////////////////////////
std::ostream& operator << ( std::ostream &os, const QVComplex &complex )
    {
    if (complex.imaginary() == 0.0)
        os << complex.real();
    else if (complex.real() == 0.0)
        {
        if (complex.imaginary() == 1.0)
            os << "i";
        else if (complex.imaginary() == -1.0)
            os << "-i";
        else
            os << complex.imaginary() << "i";
        }
    else	{
        os << complex.real();

        if (complex.imaginary() < 0)
            os << " - ";
        else
            os << " + ";
        if (complex.imaginary() == 1.0)
            os << "i";
        else
            os << ABS(complex.imaginary()) << "i";
        }

    return os;
    }


