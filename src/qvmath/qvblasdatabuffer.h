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

#ifndef QVBLASDATABUFFER_H
#define QVBLASDATABUFFER_H

#ifndef DOXYGEN_IGNORE_THIS
#include <QSharedData>

// This class could be perfectly substituted by a QVector<double>, but it is slower
class QBlasDataBuffer: public QSharedData
	{
	public:
		QBlasDataBuffer(const int size);

		QBlasDataBuffer(const QBlasDataBuffer &tensorData);

		~QBlasDataBuffer();

		const double *getReadData() const;
		double *getWriteData() const;

	private:
		int dataSize;
		double *data;
	};
#endif
#endif
