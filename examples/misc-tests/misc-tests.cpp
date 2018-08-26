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
/// @brief Test for Cholesky decomposition based functions from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

/*!
@file
@ingroup ExamplePrograms
@brief Performs several validation tests.

This test performs several code validation tests.

@section UsageImageTests Usage of the program.
Compile and execute the application with the following line:
@code ./misc-tests @endcode
*/

#include <iostream>
#include <qvmath.h>

int main(int argc, char *argv[])
	{
	// Tests for the function 'qvPointLineDistance'.
	Q_ASSERT_X( ABS(pointLineDistance(QV3DPointF(2.0, 1.0, -8.0), QPointF(3.5, 1.0))) < 1e-10,				"qvPointLineDistance()", "test number 1");
	Q_ASSERT_X( ABS(pointLineDistance(QV3DPointF(2.0, 1.0, -8.0), QPointF(3.5, 1.0))) < 1e-10,				"qvPointLineDistance()", "test number 2");
	Q_ASSERT_X( ABS(pointLineDistance(QV3DPointF(2.0, 1.0, -8.0), QPointF(2, 4))) < 1e-10, 					"qvPointLineDistance()", "test number 3");
	Q_ASSERT_X( ABS(pointLineDistance(QV3DPointF(3, -1, 6), QPointF(5, 2)) - 19.0*sqrt(10)/10.0) < 1e-10,	"qvPointLineDistance()", "test number 4");
	Q_ASSERT_X( ABS(pointLineDistance(QV3DPointF(3, 4, -9), QPointF(-2, 5)) - 1.0) < 1e-10, 				"qvPointLineDistance()", "test number 5");
	Q_ASSERT_X( ABS(pointLineDistance(QV3DPointF(2, 1, 4), QPointF(3, -5)) - sqrt(5)) < 1e-10, 				"qvPointLineDistance()", "test number 6");
	Q_ASSERT_X( ABS(pointLineDistance(QV3DPointF(4, 3, -10), QPointF(3, -4)) - 2.0) < 1e-10, 				"qvPointLineDistance()", "test number 7");
	Q_ASSERT_X( ABS(pointLineDistance(QV3DPointF(2, -1, 4), QPointF(4, 1)) - ABS(8-1+4)/sqrt(4+1)) < 1e-10,	"qvPointLineDistance()", "test number 8");
	
	return 0;
	}

