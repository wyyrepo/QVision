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

#ifndef QVIMAGE_BUFFER_H
#define QVIMAGE_BUFFER_H

#include <math.h>
#include <QObject>
#include <QDebug>
#include <QSharedData>
#include <qvdefines.h>

//#include <stdlib.h>
#include <malloc.h>

#ifndef DOXYGEN_IGNORE_THIS
template <typename Type = uChar> class QVImageBuffer: public QSharedData
    {
    public:
        // Default constructor
        QVImageBuffer(uInt cols = 0, uInt rows = 0, uInt stepPadding = 8);

        // Buffer constructor
        QVImageBuffer(uInt cols, uInt rows, uInt step, const Type * buffer = NULL);

        // Copy constructor
        QVImageBuffer(const QVImageBuffer<Type> &);

        // Destructor
        ~QVImageBuffer()	{ if (_data != NULL) delete _data; }

        uInt getRows()				const	{ return rows; }
        uInt getCols()				const	{ return cols; }
        uInt getStep()				const	{ return step; }
        int getDataSize()			const	{ return dataSize; }
        const Type *getReadData()	const	{ return _data; }
        Type * getWriteData()		const	{ return _data; }

    private:
        const uInt cols, rows, step, dataSize;
        Type * _data;
    };

// Gets the closest value to 'size' that is also:
//	- Equal or larger than 'size' value.
//	- Multiple of 'padding' value.
uInt paddedStep(const uInt size, const uInt padding);

// Default constructor
template <typename Type>
QVImageBuffer<Type>::QVImageBuffer(uInt cols, uInt rows, uInt stepPadding): QSharedData(),
    cols(cols), rows(rows), step( stepPadding*(uInt)ceil((double)(sizeof(Type) * cols)/stepPadding) ),
    dataSize(rows * step),
	_data( (dataSize > 0)? new Type[dataSize]: NULL )
    {
	// Check 32-byte aligned memory allocation
	//Q_WARNING( ((unsigned int *)_data % 16u) == 0 );

    Q_ASSERT_X(step % stepPadding == 0, "QVImageBuffer::QVImageBuffer()","step % stepPadding != 0");
    Q_ASSERT_X(step >= cols, "QVImageBuffer::allocData()", "0 < step < cols");
    Q_ASSERT_X(step == paddedStep(sizeof(Type) * cols, stepPadding), "QVImageBuffer::allocData()", "Debug error 31145X");
    }

// Buffer constructor
template <typename Type>
QVImageBuffer<Type>::QVImageBuffer(uInt cols, uInt rows, uInt step, const Type *buffer): QSharedData(),
    cols(cols), rows(rows), step(step), dataSize(rows * step),
    _data( (dataSize > 0)? new Type[dataSize]: NULL )
    {
	// Check 32-byte aligned memory allocation
	//Q_WARNING( ((uintptr_t)_data % 16u) == 0 );

    if ( (buffer != NULL) and (dataSize > 0) )
        memcpy(_data,buffer, dataSize);

    Q_ASSERT_X(step >= cols, "QVImageBuffer::allocData()", "0 < step < cols");
    }

// Copy constructor
template <typename Type>
QVImageBuffer<Type>::QVImageBuffer(const QVImageBuffer<Type> &imageBuffer): QSharedData(imageBuffer),
    cols(imageBuffer.cols), rows(imageBuffer.rows), step(imageBuffer.step), dataSize(imageBuffer.dataSize),
    _data( (dataSize > 0)? new Type[dataSize]: NULL )
    {
	// Check 32-byte aligned memory allocation
	//Q_WARNING( ((uintptr_t)_data % 16u) == 0 );

    if (dataSize > 0)
        memcpy(_data, imageBuffer.getReadData(), dataSize);
    }

#endif // DOXYGEN_IGNORE_THIS
#endif // QVIMAGE_BUFFER_H
