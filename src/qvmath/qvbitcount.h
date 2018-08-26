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

#ifndef QVBITCOUNT_H
#define QVBITCOUNT_H

/*!
@brief Iterative bit counting routine

This method counts the number of bits set to 1 in the input integer.
It is the slower method for bit counting included in QVision, but can count bits on 64 bit integers.

@param N input unsigned integer
@returns the number of bits set to 1 in the input integer
@ingroup qvmath
*/
int qvIteratedBitCount(unsigned int n);

/*!
@brief Bit counting routine from the MIT HAKMEM 

This method counts the number of bits set to 1 in the input integer.
It is included in the <a href="http://en.wikipedia.org/wiki/HAKMEM">HAKMEM</a>, or AI Memo 239, which is a technical report from the MIT AI Lab.

@note This method can count only the 32 less significant bits.

@param N input unsigned integer
@returns the number of bits set to 1 in the input integer
@ingroup qvmath
*/
int qvMITHAKMEMBitCount(unsigned int n);

/*!
@brief Nifty parallel bit counting routine

This method counts the number of bits set to 1 in the input integer.
It is slightly faster than the @ref qvMITHAKMEMBitCount method, and much faster than @ref qvIteratedBitCount method.
@note This method can count only the 32 less significant bits.

@param n input unsigned integer
@returns the number of bits set to 1 in the input integer
@ingroup qvmath
*/
int qvNiftyParallelBitCount(unsigned int n);

#endif // QVBITCOUNT_H

