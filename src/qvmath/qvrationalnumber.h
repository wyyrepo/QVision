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

/// @file
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#ifndef QVRATIONALNUMBER_H
#define QVRATIONALNUMBER_H

#include <math.h>

#include <QMap>
#include <qvdefines.h>

#ifndef DOXYGEN_IGNORE_THIS
/*!
@class QVRationalNumber qvmath/qvrationalnumber.h QVRationalNumber
@brief Rational number datatype
@ingroup qvmath

Useful for:
- Factorization.
- Long integer precise multiplication and division.
*/

class QVRationalNumber: public QMap<int, int>
	{
	public:
		QVRationalNumber():QMap<int,int>()							{ }
		QVRationalNumber(const QVRationalNumber &rationalNumber):QMap<int,int>(rationalNumber)	{ }
		QVRationalNumber(const int integer):QMap<int,int>()					{ mult(integer); }

		QVRationalNumber operator*(const QVRationalNumber &factInteger) const;
		QVRationalNumber operator/(const QVRationalNumber &factInteger) const;
		operator double() const;

		void mult(const int integer);
	};

#include <iostream>
std::ostream & operator<< (std::ostream &os, const QVRationalNumber &factInteger );
#endif
#endif
