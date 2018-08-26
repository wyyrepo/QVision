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

int qvIteratedBitCount(unsigned int n)
	{
	// Source for the code: http://gurmeet.net/puzzles/fast-bit-counting-routines/
	int count = 0;
	while (n)
		{
		count += n & 0x1u;
		n >>= 1;
		}
	return count;
	}

int qvMITHAKMEMBitCount(unsigned int n)
	{
	// Source for the code: http://gurmeet.net/puzzles/fast-bit-counting-routines/
	/* works for 32-bit numbers only    */
	/* fix last line for 64-bit numbers */
	register unsigned int tmp;
	tmp = n - ((n >> 1) & 0xdb6db6db) - ((n >> 2) & 0x49249249);
	return ((tmp + (tmp >> 3)) & 0xc71c71c7) % 63;
	}

int qvNiftyParallelBitCount(unsigned int n)
	{
	// Source for the code: http://gurmeet.net/puzzles/fast-bit-counting-routines/
	n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
	n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
	n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
	return n % 255;
	}

