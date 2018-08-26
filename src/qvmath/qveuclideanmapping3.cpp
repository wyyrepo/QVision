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

#include <QVEuclideanMapping3>

#include <qvprojective.h>
QVEuclideanMapping3::QVEuclideanMapping3(const QVMatrix &Rt)
	{
	// 1. Ensure that the rotation matrix is an orthogonal basis. This is: det(R) = 1.
	// 1.1. Ensure that Rt^t*Rt = I
	QVMatrix refinedRt = refineExtrinsicCameraMatrixWithPolarDecomposition(Rt);

	// 1.2. Still, det(R) can be <= 0. Warn the user and try to fix it up in that case.
	const double determinantR = determinant(refinedRt.getSubmatrix(0,2,0,2));
	if (determinantR == 0.0)
		std::cout << "[QVEuclideanMapping3::QVEuclideanMapping3] Warning: determinant of the rotation matrix in the provided camera matrix is equal to zero." << std::endl;
	else if (determinantR < 0.0)
		//{
		//std::cout << "[QVEuclideanMapping3::QVEuclideanMapping3] Warning: determinant of the rotation matrix in the provided camera matrix is lesser than zero." << std::endl;
		refinedRt = refinedRt * (-1);
		//}

	// 2. Get Quaterion and translation vector from the refined Rt.
	q = refinedRt.getSubmatrix(0,2,0,2);
	t = QV3DPointF(refinedRt(0,3), refinedRt(1,3), refinedRt(2,3));
	}

