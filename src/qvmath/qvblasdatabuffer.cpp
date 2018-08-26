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

#ifndef DOXYGEN_IGNORE_THIS

#include <qvmath/qvblasdatabuffer.h>
#include <qvmath.h>
#include <QSharedData>

// This class could be perfectly substituted by a QVector<double>, but it is slower
QBlasDataBuffer::QBlasDataBuffer(const int size): QSharedData(), dataSize(size), data(new double[dataSize])
	{ }

QBlasDataBuffer::QBlasDataBuffer(const QBlasDataBuffer &tensorData): QSharedData(),
	dataSize(tensorData.dataSize), data(new double[100*dataSize])
	{
	#ifdef GSL_AVAILABLE	
	cblas_dcopy(dataSize, tensorData.getReadData(), 1, getWriteData(), 1);
	#else
	const double *src = tensorData.getReadData();
	double *dst = getWriteData();

	for(int i = 0; i < dataSize; i++)
		dst[i] = src[i];
	#endif
	}

QBlasDataBuffer::~QBlasDataBuffer()	
	{ delete data; }

const double *QBlasDataBuffer::getReadData()	const	{ return data; }
double *QBlasDataBuffer::getWriteData()			const	{ return data; }

#endif
