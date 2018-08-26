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

#include <QDebug>
#include <QVImage>

#include <iostream>

template <> const char * QVImage<uChar,1>::getTypeQString()		const	{ return "QVImage<uChar,1>"; }
template <> const char * QVImage<uChar,3>::getTypeQString()		const	{ return "QVImage<uChar,3>"; }
template <> const char * QVImage<sChar,1>::getTypeQString()		const	{ return "QVImage<sChar,1>"; }
template <> const char * QVImage<sChar,3>::getTypeQString()		const	{ return "QVImage<sChar,3>"; }
template <> const char * QVImage<uShort,1>::getTypeQString()	const	{ return "QVImage<uShort,1>"; }
template <> const char * QVImage<uShort,3>::getTypeQString()	const	{ return "QVImage<uShort,3>"; }
template <> const char * QVImage<sShort,1>::getTypeQString()	const	{ return "QVImage<sShort,1>"; }
template <> const char * QVImage<sShort,3>::getTypeQString()	const	{ return "QVImage<sShort,3>"; }
template <> const char * QVImage<sInt,1>::getTypeQString()		const	{ return "QVImage<sInt,1>"; }
template <> const char * QVImage<sInt,3>::getTypeQString()		const	{ return "QVImage<sInt,3>"; }
template <> const char * QVImage<uInt,1>::getTypeQString()		const	{ return "QVImage<uInt,1>"; }
template <> const char * QVImage<uInt,3>::getTypeQString()		const	{ return "QVImage<uInt,3>"; }
template <> const char * QVImage<sFloat,1>::getTypeQString()	const	{ return "QVImage<sFloat,1>"; }
template <> const char * QVImage<sFloat,3>::getTypeQString()	const	{ return "QVImage<sFloat,3>"; }

// Copy constructors
#define	CREATE_COPY_CONSTRUCTOR(TYPE, C)								\
template <> QVImage<TYPE, C>::QVImage(QVImage<TYPE, C> const &img):QVGenericImage(img)		\
	{																	\
	imageBuffer = img.imageBuffer;										\
	step_div_type_size = getStep()/sizeof(TYPE);						\
	}

CREATE_COPY_CONSTRUCTOR(uChar, 1);
CREATE_COPY_CONSTRUCTOR(uChar, 3);
CREATE_COPY_CONSTRUCTOR(sChar, 1);
CREATE_COPY_CONSTRUCTOR(sChar, 3);
CREATE_COPY_CONSTRUCTOR(uShort, 1);
CREATE_COPY_CONSTRUCTOR(uShort, 3);
CREATE_COPY_CONSTRUCTOR(sShort, 1);
CREATE_COPY_CONSTRUCTOR(sShort, 3);
CREATE_COPY_CONSTRUCTOR(uInt, 1);
CREATE_COPY_CONSTRUCTOR(uInt, 3);
CREATE_COPY_CONSTRUCTOR(sInt, 1);
CREATE_COPY_CONSTRUCTOR(sInt, 3);
CREATE_COPY_CONSTRUCTOR(sFloat, 1);
CREATE_COPY_CONSTRUCTOR(sFloat, 3);

// Copy operator
#define	CREATE_COPY_OPERATOR(TYPE, C)						\
template <> QVImage<TYPE,C> & QVImage<TYPE, C>::operator=(const QVImage<TYPE, C> &img) 	\
	{														\
	imageBuffer = img.imageBuffer;							\
	setROI(img.getROI()); setAnchor(img.getAnchor());		\
	step_div_type_size = getStep()/sizeof(TYPE);			\
	return *this;											\
	}

CREATE_COPY_OPERATOR(uChar, 1);
CREATE_COPY_OPERATOR(uChar, 3);
CREATE_COPY_OPERATOR(sChar, 1);
CREATE_COPY_OPERATOR(sChar, 3);
CREATE_COPY_OPERATOR(uShort, 1);
CREATE_COPY_OPERATOR(uShort, 3);
CREATE_COPY_OPERATOR(sShort, 1);
CREATE_COPY_OPERATOR(sShort, 3);
CREATE_COPY_OPERATOR(uInt, 1);
CREATE_COPY_OPERATOR(uInt, 3);
CREATE_COPY_OPERATOR(sInt, 1);
CREATE_COPY_OPERATOR(sInt, 3);
CREATE_COPY_OPERATOR(sFloat, 1);
CREATE_COPY_OPERATOR(sFloat, 3);

//////////////////////////////////////////////////////////////////
// QVIPP FUNCTIONS
#ifdef QVIPP
#include <qvipp.h>
#endif // QVIPP

// Compose copy constructors
#define	CREATE_COMPOSE_COPY_CONSTRUCTOR(TYPE)																										\
template <> QVImage<TYPE, 3>::QVImage(QVImage<TYPE,1> const &red, QVImage<TYPE,1> const &green, QVImage<TYPE,1> const &blue):QVGenericImage(red)	\
	{																																				\
	imageBuffer = new QVImageBuffer<TYPE>(3*red.getCols(), red.getRows());																			\
	Copy(red, green, blue, *this);																													\
	setROI(red.getROI()); setAnchor(red.getAnchor());																								\
	step_div_type_size = getStep()/sizeof(TYPE);																									\
	}

//#ifdef QVIPP
CREATE_COMPOSE_COPY_CONSTRUCTOR(uChar);
CREATE_COMPOSE_COPY_CONSTRUCTOR(uShort);
CREATE_COMPOSE_COPY_CONSTRUCTOR(sShort);
CREATE_COMPOSE_COPY_CONSTRUCTOR(sInt);
CREATE_COMPOSE_COPY_CONSTRUCTOR(sFloat);
//#endif

// Conversion constructors
#define	CREATE_CONVERT_CONSTRUCTOR(TYPE1, TYPE2, C)											\
template <> QVImage<TYPE2, C>::QVImage(QVImage<TYPE1, C> const &img):QVGenericImage(img)	\
	{																						\
	imageBuffer = new QVImageBuffer<TYPE2>(C*img.getCols(), img.getRows());					\
	setAnchor(img.getROI().x(),img.getROI().y());											\
	Convert(img, *this);																	\
	setROI(img.getROI()); setAnchor(img.getAnchor());										\
	step_div_type_size = getStep()/sizeof(TYPE2);											\
	}

//#ifdef QVIPP
// (ORIG, DEST, CHAN)
// sFloat
//CREATE_CONVERT_CONSTRUCTOR(sFloat,	sFloat, 1);
CREATE_CONVERT_CONSTRUCTOR(sFloat,	uChar, 1);
CREATE_CONVERT_CONSTRUCTOR(sFloat,	sChar, 1);
CREATE_CONVERT_CONSTRUCTOR(sFloat,	sInt, 1);
CREATE_CONVERT_CONSTRUCTOR(sFloat,	uInt, 1);
CREATE_CONVERT_CONSTRUCTOR(sFloat,	sShort, 1);
CREATE_CONVERT_CONSTRUCTOR(sFloat,	uShort, 1);

//CREATE_CONVERT_CONSTRUCTOR(sFloat,	sFloat, 3);
CREATE_CONVERT_CONSTRUCTOR(sFloat,	uChar, 3);
CREATE_CONVERT_CONSTRUCTOR(sFloat,	sChar, 3);
CREATE_CONVERT_CONSTRUCTOR(sFloat,	sInt, 3);
CREATE_CONVERT_CONSTRUCTOR(sFloat,	uInt, 3);
CREATE_CONVERT_CONSTRUCTOR(sFloat,	sShort, 3);
CREATE_CONVERT_CONSTRUCTOR(sFloat,	uShort, 3);

// uChar
CREATE_CONVERT_CONSTRUCTOR(uChar,	sFloat, 1);
//CREATE_CONVERT_CONSTRUCTOR(uChar,	uChar, 1);
CREATE_CONVERT_CONSTRUCTOR(uChar,	sChar, 1);
CREATE_CONVERT_CONSTRUCTOR(uChar,	sInt, 1);
CREATE_CONVERT_CONSTRUCTOR(uChar,	uInt, 1);
CREATE_CONVERT_CONSTRUCTOR(uChar,	sShort, 1);
CREATE_CONVERT_CONSTRUCTOR(uChar,	uShort, 1);

CREATE_CONVERT_CONSTRUCTOR(uChar,	sFloat, 3);
//CREATE_CONVERT_CONSTRUCTOR(uChar,	uChar, 3);
CREATE_CONVERT_CONSTRUCTOR(uChar,	sChar, 3);
CREATE_CONVERT_CONSTRUCTOR(uChar,	sInt, 3);
CREATE_CONVERT_CONSTRUCTOR(uChar,	uInt, 3);
CREATE_CONVERT_CONSTRUCTOR(uChar,	sShort, 3);
CREATE_CONVERT_CONSTRUCTOR(uChar,	uShort, 3);

// sChar
CREATE_CONVERT_CONSTRUCTOR(sChar,	sFloat, 1);
CREATE_CONVERT_CONSTRUCTOR(sChar,	uChar, 1);
//CREATE_CONVERT_CONSTRUCTOR(sChar,	sChar, 1);
CREATE_CONVERT_CONSTRUCTOR(sChar,	sInt, 1);
CREATE_CONVERT_CONSTRUCTOR(sChar,	uInt, 1);
CREATE_CONVERT_CONSTRUCTOR(sChar,	sShort, 1);
CREATE_CONVERT_CONSTRUCTOR(sChar,	uShort, 1);

CREATE_CONVERT_CONSTRUCTOR(sChar,	sFloat, 3);
CREATE_CONVERT_CONSTRUCTOR(sChar,	uChar, 3);
//CREATE_CONVERT_CONSTRUCTOR(sChar,	sChar, 3);
CREATE_CONVERT_CONSTRUCTOR(sChar,	sInt, 3);
CREATE_CONVERT_CONSTRUCTOR(sChar,	uInt, 3);
CREATE_CONVERT_CONSTRUCTOR(sChar,	sShort, 3);
CREATE_CONVERT_CONSTRUCTOR(sChar,	uShort, 3);

// sInt
CREATE_CONVERT_CONSTRUCTOR(sInt,	sFloat, 1);
CREATE_CONVERT_CONSTRUCTOR(sInt,	uChar, 1);
CREATE_CONVERT_CONSTRUCTOR(sInt,	sChar, 1);
//CREATE_CONVERT_CONSTRUCTOR(sInt,	sInt, 1);
CREATE_CONVERT_CONSTRUCTOR(sInt,	uInt, 1);
CREATE_CONVERT_CONSTRUCTOR(sInt,	sShort, 1);
CREATE_CONVERT_CONSTRUCTOR(sInt,	uShort, 1);

CREATE_CONVERT_CONSTRUCTOR(sInt,	sFloat, 3);
CREATE_CONVERT_CONSTRUCTOR(sInt,	uChar, 3);
CREATE_CONVERT_CONSTRUCTOR(sInt,	sChar, 3);
//CREATE_CONVERT_CONSTRUCTOR(sInt,	sInt, 3);
CREATE_CONVERT_CONSTRUCTOR(sInt,	uInt, 3);
CREATE_CONVERT_CONSTRUCTOR(sInt,	sShort, 3);
CREATE_CONVERT_CONSTRUCTOR(sInt,	uShort, 3);

// uInt
CREATE_CONVERT_CONSTRUCTOR(uInt,	sFloat, 1);
CREATE_CONVERT_CONSTRUCTOR(uInt,	uChar, 1);
CREATE_CONVERT_CONSTRUCTOR(uInt,	sChar, 1);
CREATE_CONVERT_CONSTRUCTOR(uInt,	sInt, 1);
//CREATE_CONVERT_CONSTRUCTOR(uInt,	uInt, 1);
CREATE_CONVERT_CONSTRUCTOR(uInt,	sShort, 1);
CREATE_CONVERT_CONSTRUCTOR(uInt,	uShort, 1);

CREATE_CONVERT_CONSTRUCTOR(uInt,	sFloat, 3);
CREATE_CONVERT_CONSTRUCTOR(uInt,	uChar, 3);
CREATE_CONVERT_CONSTRUCTOR(uInt,	sChar, 3);
CREATE_CONVERT_CONSTRUCTOR(uInt,	sInt, 3);
//CREATE_CONVERT_CONSTRUCTOR(uInt,	uInt, 3);
CREATE_CONVERT_CONSTRUCTOR(uInt,	sShort, 3);
CREATE_CONVERT_CONSTRUCTOR(uInt,	uShort, 3);

// sShort
CREATE_CONVERT_CONSTRUCTOR(sShort,	sFloat, 1);
CREATE_CONVERT_CONSTRUCTOR(sShort,	uChar, 1);
CREATE_CONVERT_CONSTRUCTOR(sShort,	sChar, 1);
CREATE_CONVERT_CONSTRUCTOR(sShort,	sInt, 1);
CREATE_CONVERT_CONSTRUCTOR(sShort,	uInt, 1);
//CREATE_CONVERT_CONSTRUCTOR(sShort,	sShort, 1);
CREATE_CONVERT_CONSTRUCTOR(sShort,	uShort, 1);

CREATE_CONVERT_CONSTRUCTOR(sShort,	sFloat, 3);
CREATE_CONVERT_CONSTRUCTOR(sShort,	uChar, 3);
CREATE_CONVERT_CONSTRUCTOR(sShort,	sChar, 3);
CREATE_CONVERT_CONSTRUCTOR(sShort,	sInt, 3);
CREATE_CONVERT_CONSTRUCTOR(sShort,	uInt, 3);
//CREATE_CONVERT_CONSTRUCTOR(sShort,	sShort, 3);
CREATE_CONVERT_CONSTRUCTOR(sShort,	uShort, 3);

// uShort
CREATE_CONVERT_CONSTRUCTOR(uShort,	sFloat, 1);
CREATE_CONVERT_CONSTRUCTOR(uShort,	uChar, 1);
CREATE_CONVERT_CONSTRUCTOR(uShort,	sChar, 1);
CREATE_CONVERT_CONSTRUCTOR(uShort,	sInt, 1);
CREATE_CONVERT_CONSTRUCTOR(uShort,	uInt, 1);
CREATE_CONVERT_CONSTRUCTOR(uShort,	sShort, 1);
//CREATE_CONVERT_CONSTRUCTOR(uShort,	uShort, 1);

CREATE_CONVERT_CONSTRUCTOR(uShort,	sFloat, 3);
CREATE_CONVERT_CONSTRUCTOR(uShort,	uChar, 3);
CREATE_CONVERT_CONSTRUCTOR(uShort,	sChar, 3);
CREATE_CONVERT_CONSTRUCTOR(uShort,	sInt, 3);
CREATE_CONVERT_CONSTRUCTOR(uShort,	uInt, 3);
CREATE_CONVERT_CONSTRUCTOR(uShort,	sShort, 3);
//CREATE_CONVERT_CONSTRUCTOR(uShort,	uShort, 3);

#define	CREATE_CONVERT_CONSTRUCTOR_C3_C1(TYPE)												\
template <> QVImage<TYPE, 1>::QVImage(QVImage<TYPE, 3> const &img):QVGenericImage(img)		\
	{																						\
	imageBuffer = new QVImageBuffer<TYPE>(img.getCols(), img.getRows());					\
	setAnchor(img.getROI().x(),img.getROI().y());											\
	RGBToGray(img, *this);																	\
	setROI(img.getROI()); setAnchor(img.getAnchor());										\
	step_div_type_size = getStep()/sizeof(TYPE);											\
	}

CREATE_CONVERT_CONSTRUCTOR_C3_C1(uChar);
CREATE_CONVERT_CONSTRUCTOR_C3_C1(sChar);
CREATE_CONVERT_CONSTRUCTOR_C3_C1(uInt);
CREATE_CONVERT_CONSTRUCTOR_C3_C1(sInt);
CREATE_CONVERT_CONSTRUCTOR_C3_C1(uShort);
CREATE_CONVERT_CONSTRUCTOR_C3_C1(sShort);
CREATE_CONVERT_CONSTRUCTOR_C3_C1(sFloat);

#define	CREATE_CONVERT_CONSTRUCTOR_C1_C3(TYPE)												\
template <> QVImage<TYPE, 3>::QVImage(QVImage<TYPE, 1> const &img):QVGenericImage(img)		\
	{																						\
	imageBuffer = new QVImageBuffer<TYPE>(3*img.getCols(), img.getRows());					\
	setAnchor(img.getROI().x(),img.getROI().y());											\
	Copy(img, img, img, *this);																\
	setROI(img.getROI()); setAnchor(img.getAnchor());										\
	step_div_type_size = getStep()/sizeof(TYPE);											\
	}

CREATE_CONVERT_CONSTRUCTOR_C1_C3(uChar);
CREATE_CONVERT_CONSTRUCTOR_C1_C3(sChar);
CREATE_CONVERT_CONSTRUCTOR_C1_C3(uShort);
CREATE_CONVERT_CONSTRUCTOR_C1_C3(sShort);
CREATE_CONVERT_CONSTRUCTOR_C1_C3(uInt);
CREATE_CONVERT_CONSTRUCTOR_C1_C3(sInt);
CREATE_CONVERT_CONSTRUCTOR_C1_C3(sFloat);

// Nota: las siguientes funciones dan error al compilar, ya que no existen versiones de la función wrapper Convert,
// para convertir de una imagen entera, a una imagen de tipo uShort, sShort, o sFloat.
//	CREATE_CONVERT_CONSTRUCTOR(uShort, sInt, 1);
//	CREATE_CONVERT_CONSTRUCTOR(sShort, sInt, 1);
//	CREATE_CONVERT_CONSTRUCTOR(uShort, sInt, 3);
//	CREATE_CONVERT_CONSTRUCTOR(sShort, sInt, 3);
//	CREATE_CONVERT_CONSTRUCTOR(sFloat, sInt, 3);
//	CREATE_CONVERT_CONSTRUCTOR(sFloat, sInt, 3);
//
// Por ello, estas funciones deben ser definidas con funciones de conversión Ad-hoc, así como las funciones de conversión
// de valores uShort a valores sShort, y viceversa, que tampoco están implementadas por las IPP, ni las funciones para convertir
// imagenes de distinto tipo y canal.
//
// Ojo: Para implementar las funciones de conversión entre imagenes de tipo sShort y uShort, hay que tener en cuenta la saturación
// (que hacen las IPP para todas las funciones de conversión que implementa):
// - Si se quiere convertir un valor sShort menor que cero a un valor uShort, se deja como el valor cero (0).
// - Si se quiere convertir un valor uShort mayor que IPP_MAX_16S a sShort, se debe dejar como el valor IPP_MAX_16S.

/*#define	CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(TYPE1, TYPE2)						\
template <> QVImage<TYPE2, 1>::QVImage(QVImage<TYPE1, 1> const &img):QVGenericImage(img)		\
	{												\
	imageBuffer = new QVImageBuffer<TYPE2>(img.getCols(), img.getRows());			\
	QVIMAGE_PTR_INIT_WRITE(TYPE2, this);								\
	QVIMAGE_INIT_READ(TYPE1, img);									\
	for (int col = img.getROI().left(); col < img.getROI().right(); col++)				\
		for (int row = img.getROI().top(); row < img.getROI().bottom(); row++)			\
			QVIMAGE_PIXEL(this, col, row, 0) = (TYPE2)QVIMAGE_PIXEL(img, col, row, 0);	\
 	setROI(img.getROI()); setAnchor(img.getAnchor());						\
	step_div_type_size = getStep()/sizeof(TYPE2);							\
	}

CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(uShort, sShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(sShort, uShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(sInt, uShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(sInt, sShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(sInt, sFloat);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(sFloat, sInt);
#ifndef QVIPP
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(uChar,	uShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(uChar,	sShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(uChar,	sInt);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(uChar,	sFloat);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(uShort,	uChar);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(uShort,	sInt);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(uShort,	sFloat);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(sShort,	uChar);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(sShort,	sInt);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(sShort,	sFloat);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(sInt,	uChar);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(sFloat,	uChar);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(sFloat,	uShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_1(sFloat,	sShort);
#endif

#define	CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(TYPE1, TYPE2)						\
template <> QVImage<TYPE2, 3>::QVImage(QVImage<TYPE1, 3> const &img):QVGenericImage(img)		\
	{												\
	imageBuffer = new QVImageBuffer<TYPE2>(3*img.getCols(), img.getRows());			\
	QVIMAGE_PTR_INIT_WRITE(TYPE2, this);								\
	QVIMAGE_INIT_READ(TYPE1, img);									\
	for (int col = img.getROI().left(); col < img.getROI().right(); col++)				\
		for (int row = img.getROI().top(); row < img.getROI().bottom(); row++)			\
			{										\
			QVIMAGE_PIXEL(this, col, row, 0) = (TYPE2)QVIMAGE_PIXEL(img, col, row, 0);	\
			QVIMAGE_PIXEL(this, col, row, 1) = (TYPE2)QVIMAGE_PIXEL(img, col, row, 1);	\
			QVIMAGE_PIXEL(this, col, row, 2) = (TYPE2)QVIMAGE_PIXEL(img, col, row, 2);	\
			}										\
 	setROI(img.getROI()); setAnchor(img.getAnchor());						\
	step_div_type_size = getStep()/sizeof(TYPE2);							\
	}

CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(uShort, sShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(sShort, uShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(sInt, uShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(sInt, sShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(sInt, sFloat);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(sFloat, sInt);
#ifndef QVIPP
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(uChar,	uShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(uChar,	sShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(uChar,	sInt);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(uChar,	sFloat);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(uShort,	uChar);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(uShort,	sInt);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(uShort,	sFloat);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(sShort,	uChar);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(sShort,	sInt);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(sShort,	sFloat);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(sInt,	uChar);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(sFloat,	uChar);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(sFloat,	uShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_3(sFloat,	sShort);
#endif*/

/*#define	CREATE_CONVERT_CONSTRUCTOR_NO_IPP_C3_C1(TYPE)								\
template <> QVImage<TYPE, 1>::QVImage(QVImage<TYPE, 3> const &img):QVGenericImage(img)				\
	{													\
	imageBuffer = new QVImageBuffer<TYPE>(img.getCols(), img.getRows());					\
	QVIMAGE_PTR_INIT_WRITE(TYPE, this);									\
	QVIMAGE_INIT_READ(TYPE, img);										\
	for (int col = img.getROI().left(); col < img.getROI().right(); col++)					\
 		for (int row = img.getROI().top(); row < img.getROI().bottom(); row++)				\
			{											\
 			QVIMAGE_PIXEL(this, col, row, 0) = (TYPE)(0.299 * QVIMAGE_PIXEL(img, col, row, 0));	\
 			QVIMAGE_PIXEL(this, col, row, 0) += (TYPE)(0.587 * QVIMAGE_PIXEL(img, col, row, 1));	\
 			QVIMAGE_PIXEL(this, col, row, 0) += (TYPE)(0.114 * QVIMAGE_PIXEL(img, col, row, 2));	\
			}											\
  	setROI(img.getROI()); setAnchor(img.getAnchor());							\
	step_div_type_size = getStep()/sizeof(TYPE);								\
	}

CREATE_CONVERT_CONSTRUCTOR_NO_IPP_C3_C1(sInt);
#ifndef QVIPP
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_C3_C1(uChar);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_C3_C1(uShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_C3_C1(sShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_C3_C1(sFloat);
#endif

#define	CREATE_CONVERT_CONSTRUCTOR_NO_IPP_C1_C3(TYPE)							\
template <> QVImage<TYPE, 3>::QVImage(QVImage<TYPE, 1> const &img):QVGenericImage(img)			\
	{												\
	imageBuffer = new QVImageBuffer<TYPE>(3*img.getCols(), img.getRows());				\
	QVIMAGE_PTR_INIT_WRITE(TYPE, this);								\
	QVIMAGE_INIT_READ(TYPE, img);									\
	for (int col = img.getROI().left(); col < img.getROI().right(); col++)				\
 		for (int row = img.getROI().top(); row < img.getROI().bottom(); row++)			\
			{										\
 			QVIMAGE_PIXEL(this, col, row, 0) = (TYPE)(QVIMAGE_PIXEL(img, col, row, 0));	\
 			QVIMAGE_PIXEL(this, col, row, 1) = (TYPE)(QVIMAGE_PIXEL(img, col, row, 0));	\
 			QVIMAGE_PIXEL(this, col, row, 2) = (TYPE)(QVIMAGE_PIXEL(img, col, row, 0));	\
			}										\
  	setROI(img.getROI()); setAnchor(img.getAnchor());						\
	step_div_type_size = getStep()/sizeof(TYPE);							\
	}

#ifndef QVIPP
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_C1_C3(uChar);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_C1_C3(uShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_C1_C3(sShort);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_C1_C3(sInt);
CREATE_CONVERT_CONSTRUCTOR_NO_IPP_C1_C3(sFloat);
#endif*/

template <> QVImage<uChar, 3>::QVImage(const QImage &qimg):QVGenericImage()
	{
	imageBuffer = new QVImageBuffer<uChar>(3*qimg.size().width(), qimg.size().height());
	setROI(0, 0, qimg.size().width(), qimg.size().height());
	setAnchor(getROI().x(), getROI().y());
	step_div_type_size = getStep()/sizeof(uChar);

	const int step = getStep();
	uChar *imagerawdata = getWriteData();
	for(uint row=0; row != getRows(); row++)
	       for(uint col=0; col != getCols(); col++)
			{
			imagerawdata[row*step + 3*col] = qRed(qimg.pixel(col,row));
			imagerawdata[row*step + 3*col + 1] = qGreen(qimg.pixel(col,row));
			imagerawdata[row*step + 3*col + 2] = qBlue(qimg.pixel(col,row));
			}
	}

template <> QVImage<uChar, 3>::operator QImage() const
	{
    QRect roi = getROI();
    const int x=roi.x(), y=roi.y(), w=roi.width(), h=roi.height(), step = getStep();
    QImage qImage(w, h, QImage::Format_RGB32);
	const uChar *imagerawdata = getReadData();
        for(int row = y; row < y+h; row++)
			for(int col = x; col < x+w; col++)
				{
				const int idx = row*step + 3*col;
				uChar	r = imagerawdata[idx + 0],
						g = imagerawdata[idx + 1],
						b = imagerawdata[idx + 2];
				qImage.setPixel(col-x, row-y, qRgb(r,g,b));
				}

	return qImage;
	}

// Convert operators for IplImage
/*template <> QVImage<uChar, 3>::QVImage(const IplImage *iplImage):QVGenericImage()
	{
	imageBuffer = new QVImageBuffer<uChar>(3*iplImage->width, iplImage->height, align(3*iplImage->width,4));
	setROI(0, 0, iplImage->width, iplImage->height);
	setAnchor(0, 0);

	const int lineSize = getCols() * 3;	// This depends on data size

	for (uInt y=0 ;y<getRows(); y++)
		memcpy(getWriteData() + getStep() * y, iplImage->imageData + iplImage->widthStep*y, lineSize);
	}*/

/*template <> QVImage<uChar, 3>::operator IplImage *() const
	{
	IplImage *imageDest = cvCreateImageHeader(cvSize(getCols(), getRows()), IPL_DEPTH_8U, 3);
	cvCreateImageData(imageDest);

	const int lineSize = getCols() * 3;	// This depends on data size

	for (uInt y=0 ;y<getRows(); y++)
		memcpy(imageDest->imageData + imageDest->widthStep*y, getReadData() + getStep() * y, lineSize);

	return imageDest;
	}*/

// IPL_DEPTH_8U
// IPL_DEPTH_8S
// IPL_DEPTH_16U
// IPL_DEPTH_16S
// IPL_DEPTH_32S
// IPL_DEPTH_32F
// IPL_DEPTH_64F

/// @todo Check IplImage is compatible with actual image
#define	CREATE_IPLIMAGE_CONSTRUCTOR(TYPE, C, DEPTH)									\
template <> QVImage<TYPE, C>::QVImage(const IplImage *iplImage):QVGenericImage()					\
	{														\
	if (iplImage->nChannels != C)											\
		qWarning("Conversion from incompatible OpenCV image: incompatible channel number");			\
	if (iplImage->depth != DEPTH)											\
		qWarning("Conversion from incompatible OpenCV image: incompatible depth");				\
															\
	/*std::cout << "BBB" << std::endl;*/ \
	imageBuffer = new QVImageBuffer<TYPE>(C*iplImage->width, iplImage->height /*align(C*iplImage->width,4)*/);	\
	setROI(0, 0, iplImage->width, iplImage->height);								\
	step_div_type_size = getStep()/sizeof(TYPE);									\
	setAnchor(0, 0);												\
															\
	const int lineSize = getCols() * C;	/* This depends on data size */						\
															\
	for (uInt y=0 ;y<getRows(); y++)										\
		memcpy(getWriteData() + getStep() * y, iplImage->imageData + iplImage->widthStep*y, lineSize);		\
	}

#ifdef QVOPENCV
CREATE_IPLIMAGE_CONSTRUCTOR(uChar, 1, IPL_DEPTH_8U);
CREATE_IPLIMAGE_CONSTRUCTOR(uChar, 3, IPL_DEPTH_8U);
CREATE_IPLIMAGE_CONSTRUCTOR(sFloat, 1, IPL_DEPTH_32F);
CREATE_IPLIMAGE_CONSTRUCTOR(sFloat, 3, IPL_DEPTH_32F);
#endif

#define	CREATE_IPLIMAGE_CONVERSION(TYPE, C, DEPTH)									\
template <> QVImage<TYPE, C>::operator IplImage *() const								\
	{														\
	IplImage *imageDest = cvCreateImageHeader(cvSize(getCols(), getRows()), DEPTH, C);				\
	cvCreateImageData(imageDest);											\
															\
	const int lineSize = getCols() * C;	/* This depends on data size */						\
															\
	for (uInt y=0 ;y<getRows(); y++)										\
		memcpy(imageDest->imageData + imageDest->widthStep*y, getReadData() + getStep() * y, lineSize);		\
															\
	return imageDest;												\
	}

#ifdef QVOPENCV
CREATE_IPLIMAGE_CONVERSION(uChar, 1, IPL_DEPTH_8U);
CREATE_IPLIMAGE_CONVERSION(uChar, 3, IPL_DEPTH_8U);
CREATE_IPLIMAGE_CONVERSION(sFloat, 1, IPL_DEPTH_32F);
CREATE_IPLIMAGE_CONVERSION(sFloat, 3, IPL_DEPTH_32F);
#endif

// Operators. Only with the IPP
#define CREATE_OPERATOR(NAME, OPERATOR, TYPE, C)						\
template <> QVImage<TYPE, C> QVImage<TYPE,C>::OPERATOR(const QVImage<TYPE, C> &img) const	\
	{											\
	QVImage<TYPE, C> result = *this;							\
	NAME(*this, img, result);								\
	return result;										\
	}

#ifdef QVIPP
CREATE_OPERATOR(Add, operator+, uChar, 1);
CREATE_OPERATOR(Mul, operator*, uChar, 1);
CREATE_OPERATOR(Sub, operator-, uChar, 1);
CREATE_OPERATOR(Div, operator/, uChar, 1);
CREATE_OPERATOR(Add, operator+, uChar, 3);
CREATE_OPERATOR(Mul, operator*, uChar, 3);
CREATE_OPERATOR(Sub, operator-, uChar, 3);
CREATE_OPERATOR(Div, operator/, uChar, 3);

CREATE_OPERATOR(Add, operator+, uShort, 1);
CREATE_OPERATOR(Mul, operator*, uShort, 1);
CREATE_OPERATOR(Sub, operator-, uShort, 1);
CREATE_OPERATOR(Div, operator/, uShort, 1);
CREATE_OPERATOR(Add, operator+, uShort, 3);
CREATE_OPERATOR(Mul, operator*, uShort, 3);
CREATE_OPERATOR(Sub, operator-, uShort, 3);
CREATE_OPERATOR(Div, operator/, uShort, 3);

CREATE_OPERATOR(Add, operator+, sShort, 1);
CREATE_OPERATOR(Mul, operator*, sShort, 1);
CREATE_OPERATOR(Sub, operator-, sShort, 1);
CREATE_OPERATOR(Div, operator/, sShort, 1);
CREATE_OPERATOR(Add, operator+, sShort, 3);
CREATE_OPERATOR(Mul, operator*, sShort, 3);
CREATE_OPERATOR(Sub, operator-, sShort, 3);
CREATE_OPERATOR(Div, operator/, sShort, 3);
#endif

#define CREATE_OPERATOR_INT_C1(OPERATOR, OPERATION, TYPE)											\
template <> QVImage<TYPE, 1> QVImage<TYPE, 1>::OPERATOR(const QVImage<TYPE, 1> &img) const							\
	{																	\
	QVImage<TYPE, 1> result = *this;													\
	QVIMAGE_PTR_INIT_READ(TYPE, this);													\
	QVIMAGE_INIT_READ(TYPE, img);														\
	QVIMAGE_INIT_WRITE(TYPE, result);													\
	for (int col = result.getROI().left(); col < result.getROI().right(); col++)								\
		for (int row = result.getROI().top(); row < result.getROI().bottom(); row++)							\
			QVIMAGE_PIXEL(result, col, row, 0) = QVIMAGE_PIXEL(img, col, row, 0) OPERATION QVIMAGE_PIXEL(this, col, row, 0);	\
	return result;																\
	}

#ifdef QVIPP
CREATE_OPERATOR_INT_C1(operator+, +, sInt);
CREATE_OPERATOR_INT_C1(operator*, *, sInt);
CREATE_OPERATOR_INT_C1(operator-, -, sInt);
CREATE_OPERATOR_INT_C1(operator/, /, sInt);
#endif

#define CREATE_OPERATOR_INT_C3(OPERATOR, OPERATION, TYPE)											\
template <> QVImage<TYPE, 3> QVImage<TYPE, 3>::OPERATOR(const QVImage<TYPE, 3> &img) const							\
	{																	\
	QVImage<TYPE, 3> result = *this;													\
	QVIMAGE_PTR_INIT_READ(TYPE, this);													\
	QVIMAGE_INIT_READ(TYPE, img);														\
	QVIMAGE_INIT_WRITE(TYPE, result);													\
	for (int col = result.getROI().left(); col < result.getROI().right(); col++)								\
		for (int row = result.getROI().top(); row < result.getROI().bottom(); row++)							\
			{															\
			QVIMAGE_PIXEL(result, col, row, 0) = QVIMAGE_PIXEL(img, col, row, 0) OPERATION QVIMAGE_PIXEL(this, col, row, 0);	\
			QVIMAGE_PIXEL(result, col, row, 1) = QVIMAGE_PIXEL(img, col, row, 1) OPERATION QVIMAGE_PIXEL(this, col, row, 1);	\
			QVIMAGE_PIXEL(result, col, row, 2) = QVIMAGE_PIXEL(img, col, row, 2) OPERATION QVIMAGE_PIXEL(this, col, row, 2);	\
			}															\
	return result;																\
	}

#ifdef QVIPP
CREATE_OPERATOR_INT_C3(operator+, +, sInt);
CREATE_OPERATOR_INT_C3(operator*, *, sInt);
CREATE_OPERATOR_INT_C3(operator-, -, sInt);
CREATE_OPERATOR_INT_C3(operator/, /, sInt);
#endif

#define CREATE_CONST_OPERATOR(NAME, OPERATOR, TYPE, C)				\
template <> QVImage<TYPE, C> QVImage<TYPE,C>::OPERATOR(const TYPE value) const	\
	{									\
	QVImage<TYPE, C> result = *this;					\
	NAME(*this, value, result);						\
	return result;								\
	}

#ifdef QVIPP
CREATE_CONST_OPERATOR(AddC, operator+, uChar, 1);
CREATE_CONST_OPERATOR(MulC, operator*, uChar, 1);
CREATE_CONST_OPERATOR(SubC, operator-, uChar, 1);
CREATE_CONST_OPERATOR(DivC, operator/, uChar, 1);
CREATE_CONST_OPERATOR(AddC, operator+, uShort, 1);
CREATE_CONST_OPERATOR(MulC, operator*, uShort, 1);
CREATE_CONST_OPERATOR(SubC, operator-, uShort, 1);
CREATE_CONST_OPERATOR(DivC, operator/, uShort, 1);
CREATE_CONST_OPERATOR(AddC, operator+, sShort, 1);
CREATE_CONST_OPERATOR(MulC, operator*, sShort, 1);
CREATE_CONST_OPERATOR(SubC, operator-, sShort, 1);
CREATE_CONST_OPERATOR(DivC, operator/, sShort, 1);
CREATE_CONST_OPERATOR(AddC, operator+, sFloat, 1);
CREATE_CONST_OPERATOR(MulC, operator*, sFloat, 1);
CREATE_CONST_OPERATOR(SubC, operator-, sFloat, 1);
CREATE_CONST_OPERATOR(DivC, operator/, sFloat, 1);
CREATE_CONST_OPERATOR(LShiftC, operator<<, uChar, 1);
CREATE_CONST_OPERATOR(RShiftC, operator>>, uChar, 1);
CREATE_CONST_OPERATOR(LShiftC, operator<<, uShort, 1);
CREATE_CONST_OPERATOR(RShiftC, operator>>, uShort, 1);
CREATE_CONST_OPERATOR(LShiftC, operator<<, sInt, 1);
CREATE_CONST_OPERATOR(RShiftC, operator>>, sInt, 1);
CREATE_CONST_OPERATOR(AndC, operator&, uChar, 1);
CREATE_CONST_OPERATOR(OrC, operator|, uChar, 1);
CREATE_CONST_OPERATOR(XorC, operator^, uChar, 1);
CREATE_CONST_OPERATOR(AndC, operator&, uShort, 1);
CREATE_CONST_OPERATOR(OrC, operator|, uShort, 1);
CREATE_CONST_OPERATOR(XorC, operator^, uShort, 1);
CREATE_CONST_OPERATOR(AndC, operator&, sInt, 1);
CREATE_CONST_OPERATOR(OrC, operator|, sInt, 1);
CREATE_CONST_OPERATOR(XorC, operator^, sInt, 1);
#endif

/////////////////////////

#define CREATE_CONST_OPERATOR_C3(NAME, OPERATOR, TYPE, C)			\
template <> QVImage<TYPE, C> QVImage<TYPE,C>::OPERATOR(const TYPE value) const	\
	{									\
	const TYPE values[3] = { value, value, value };				\
	QVImage<TYPE, C> result = *this;					\
	NAME(*this, values, result);						\
	return result;								\
	}

#ifdef QVIPP
CREATE_CONST_OPERATOR_C3(AddC, operator+, uChar, 3);
CREATE_CONST_OPERATOR_C3(MulC, operator*, uChar, 3);
CREATE_CONST_OPERATOR_C3(SubC, operator-, uChar, 3);
CREATE_CONST_OPERATOR_C3(DivC, operator/, uChar, 3);
CREATE_CONST_OPERATOR_C3(AddC, operator+, sShort, 3);
CREATE_CONST_OPERATOR_C3(MulC, operator*, sShort, 3);
CREATE_CONST_OPERATOR_C3(SubC, operator-, sShort, 3);
CREATE_CONST_OPERATOR_C3(DivC, operator/, sShort, 3);
CREATE_CONST_OPERATOR_C3(AddC, operator+, uShort, 3);
CREATE_CONST_OPERATOR_C3(MulC, operator*, uShort, 3);
CREATE_CONST_OPERATOR_C3(SubC, operator-, uShort, 3);
CREATE_CONST_OPERATOR_C3(DivC, operator/, uShort, 3);
CREATE_CONST_OPERATOR_C3(AddC, operator+, sFloat, 3);
CREATE_CONST_OPERATOR_C3(MulC, operator*, sFloat, 3);
CREATE_CONST_OPERATOR_C3(SubC, operator-, sFloat, 3);
CREATE_CONST_OPERATOR_C3(DivC, operator/, sFloat, 3);
CREATE_CONST_OPERATOR_C3(AndC, operator&, uChar, 3);
CREATE_CONST_OPERATOR_C3(OrC, operator|, uChar, 3);
CREATE_CONST_OPERATOR_C3(XorC, operator^, uChar, 3);
CREATE_CONST_OPERATOR_C3(AndC, operator&, uShort, 3);
CREATE_CONST_OPERATOR_C3(OrC, operator|, uShort, 3);
CREATE_CONST_OPERATOR_C3(XorC, operator^, uShort, 3);
CREATE_CONST_OPERATOR_C3(AndC, operator&, sInt, 3);
CREATE_CONST_OPERATOR_C3(OrC, operator|, sInt, 3);
CREATE_CONST_OPERATOR_C3(XorC, operator^, sInt, 3);
#endif

#define CREATE_CONST_OPERATOR_C4(NAME, OPERATOR, TYPE, C)			\
template <> QVImage<TYPE, C> QVImage<TYPE,C>::OPERATOR(const TYPE value) const	\
	{									\
	const uInt values[3] = { value, value, value };				\
	QVImage<TYPE, C> result = *this;					\
	NAME(*this, values, result);						\
	return result;								\
	}

#ifdef QVIPP
CREATE_CONST_OPERATOR_C4(LShiftC, operator<<, uChar, 3);
CREATE_CONST_OPERATOR_C4(RShiftC, operator>>, uChar, 3);
CREATE_CONST_OPERATOR_C4(LShiftC, operator<<, uShort, 3);
CREATE_CONST_OPERATOR_C4(RShiftC, operator>>, uShort, 3);
CREATE_CONST_OPERATOR_C4(LShiftC, operator<<, sInt, 3);
CREATE_CONST_OPERATOR_C4(RShiftC, operator>>, sInt, 3);
#endif

#define CREATE_CONST_OPERATOR_INT_C1(OPERATOR, OPERATION, TYPE)							\
template <> QVImage<TYPE, 1> QVImage<TYPE, 1>::OPERATOR(const TYPE value) const					\
	{													\
	QVImage<TYPE, 1> result = *this;									\
	QVIMAGE_PTR_INIT_READ(TYPE, this);									\
	QVIMAGE_INIT_WRITE(TYPE, result);									\
	for (int col = result.getROI().left(); col < result.getROI().right(); col++)				\
		for (int row = result.getROI().top(); row < result.getROI().bottom(); row++)			\
			QVIMAGE_PIXEL(result, col, row, 0) = QVIMAGE_PIXEL(this, col, row, 0) OPERATION value;	\
	return result;												\
	}

#ifdef QVIPP
CREATE_CONST_OPERATOR_INT_C1(operator+, +, sInt);
CREATE_CONST_OPERATOR_INT_C1(operator*, *, sInt);
CREATE_CONST_OPERATOR_INT_C1(operator-, -, sInt);
CREATE_CONST_OPERATOR_INT_C1(operator/, /, sInt);
#endif

#define CREATE_CONST_OPERATOR_INT_C3(OPERATOR, OPERATION, TYPE)							\
template <> QVImage<TYPE, 3> QVImage<TYPE, 3>::OPERATOR(const TYPE value) const					\
	{													\
	QVImage<TYPE, 3> result = *this;									\
	QVIMAGE_PTR_INIT_READ(TYPE, this);									\
	QVIMAGE_INIT_WRITE(TYPE, result);									\
	for (int col = result.getROI().left(); col < result.getROI().right(); col++)				\
		for (int row = result.getROI().top(); row < result.getROI().bottom(); row++)			\
			{											\
			QVIMAGE_PIXEL(result, col, row, 0) = QVIMAGE_PIXEL(this, col, row, 0) OPERATION value;	\
			QVIMAGE_PIXEL(result, col, row, 1) = QVIMAGE_PIXEL(this, col, row, 1) OPERATION value;	\
			QVIMAGE_PIXEL(result, col, row, 2) = QVIMAGE_PIXEL(this, col, row, 2) OPERATION value;	\
			}											\
	return result;												\
	}

#ifdef QVIPP
CREATE_CONST_OPERATOR_INT_C3(operator+, +, sInt);
CREATE_CONST_OPERATOR_INT_C3(operator*, *, sInt);
CREATE_CONST_OPERATOR_INT_C3(operator-, -, sInt);
CREATE_CONST_OPERATOR_INT_C3(operator/, /, sInt);
#endif

#define CREATE_NOT_OPERATOR(NAME, OPERATOR, TYPE, C)		\
template <> QVImage<TYPE, C> QVImage<TYPE,C>::OPERATOR() const	\
	{							\
	QVImage<TYPE, C> result = *this;			\
	NAME(*this, result);					\
	return result;						\
	}

#ifdef QVIPP
CREATE_NOT_OPERATOR(Not, operator!, uChar, 1);
CREATE_NOT_OPERATOR(Not, operator!, uChar, 3);
#endif

#define CREATE_COMPARE_OPERATOR(NAME, OPERATOR, CMP, TYPE, C)				\
template <> QVImage<uChar> QVImage<TYPE,C>::OPERATOR(const QVImage<TYPE, C> &img) const	\
	{										\
	QVImage<uChar> result(getCols(), getRows());					\
	NAME(*this, img, result, CMP);							\
	return result;									\
	}

#ifdef QVIPP
// ippcmpLess
CREATE_COMPARE_OPERATOR(Compare, operator<, ippCmpLess, uChar, 1);
CREATE_COMPARE_OPERATOR(Compare, operator<, ippCmpLess, uShort, 1);
CREATE_COMPARE_OPERATOR(Compare, operator<, ippCmpLess, sShort, 1);
CREATE_COMPARE_OPERATOR(Compare, operator<, ippCmpLess, sFloat, 1);

CREATE_COMPARE_OPERATOR(Compare, operator<, ippCmpLess, uChar, 3);
CREATE_COMPARE_OPERATOR(Compare, operator<, ippCmpLess, uShort, 3);
CREATE_COMPARE_OPERATOR(Compare, operator<, ippCmpLess, sShort, 3);
CREATE_COMPARE_OPERATOR(Compare, operator<, ippCmpLess, sFloat, 3);

// ippCmpGreater
CREATE_COMPARE_OPERATOR(Compare, operator>, ippCmpGreater, uChar, 1);
CREATE_COMPARE_OPERATOR(Compare, operator>, ippCmpGreater, uShort, 1);
CREATE_COMPARE_OPERATOR(Compare, operator>, ippCmpGreater, sShort, 1);
CREATE_COMPARE_OPERATOR(Compare, operator>, ippCmpGreater, sFloat, 1);

CREATE_COMPARE_OPERATOR(Compare, operator>, ippCmpGreater, uChar, 3);
CREATE_COMPARE_OPERATOR(Compare, operator>, ippCmpGreater, uShort, 3);
CREATE_COMPARE_OPERATOR(Compare, operator>, ippCmpGreater, sShort, 3);
CREATE_COMPARE_OPERATOR(Compare, operator>, ippCmpGreater, sFloat, 3);

// ippcmpLessEq
CREATE_COMPARE_OPERATOR(Compare, operator<=, ippCmpLessEq, uChar, 1);
CREATE_COMPARE_OPERATOR(Compare, operator<=, ippCmpLessEq, uShort, 1);
CREATE_COMPARE_OPERATOR(Compare, operator<=, ippCmpLessEq, sShort, 1);
CREATE_COMPARE_OPERATOR(Compare, operator<=, ippCmpLessEq, sFloat, 1);

CREATE_COMPARE_OPERATOR(Compare, operator<=, ippCmpLessEq, uChar, 3);
CREATE_COMPARE_OPERATOR(Compare, operator<=, ippCmpLessEq, uShort, 3);
CREATE_COMPARE_OPERATOR(Compare, operator<=, ippCmpLessEq, sShort, 3);
CREATE_COMPARE_OPERATOR(Compare, operator<=, ippCmpLessEq, sFloat, 3);

// ippCmpGreaterEq
CREATE_COMPARE_OPERATOR(Compare, operator>=, ippCmpGreaterEq, uChar, 1);
CREATE_COMPARE_OPERATOR(Compare, operator>=, ippCmpGreaterEq, uShort, 1);
CREATE_COMPARE_OPERATOR(Compare, operator>=, ippCmpGreaterEq, sShort, 1);
CREATE_COMPARE_OPERATOR(Compare, operator>=, ippCmpGreaterEq, sFloat, 1);

CREATE_COMPARE_OPERATOR(Compare, operator>=, ippCmpGreaterEq, uChar, 3);
CREATE_COMPARE_OPERATOR(Compare, operator>=, ippCmpGreaterEq, uShort, 3);
CREATE_COMPARE_OPERATOR(Compare, operator>=, ippCmpGreaterEq, sShort, 3);
CREATE_COMPARE_OPERATOR(Compare, operator>=, ippCmpGreaterEq, sFloat, 3);
#endif

#define CREATE_GENERIC_COMPARE_OPERATOR_C1(OPERATOR, OPERATION, TYPE1, TYPE2)				\
template <> QVImage<uChar> QVImage<TYPE1, 1>::OPERATOR(const QVImage<TYPE2, 1> &img) const		\
	{												\
	QVImage<uChar> result(getCols(), getRows());							\
	result.setROI(getROI()); result.setAnchor(getAnchor());						\
	QVIMAGE_PTR_INIT_READ(TYPE1, this);								\
	QVIMAGE_INIT_READ(TYPE2, img);									\
	QVIMAGE_INIT_WRITE(uChar, result);								\
	for (int col = result.getROI().left(); col < result.getROI().right(); col++)			\
		for (int row = result.getROI().top(); row < result.getROI().bottom(); row++)		\
			if (QVIMAGE_PIXEL(this, col, row, 0) OPERATION QVIMAGE_PIXEL(img, col, row, 0))	\
				QVIMAGE_PIXEL(result, col, row, 0) = IPP_MAX_8U;			\
			else	QVIMAGE_PIXEL(result, col, row, 0) = 0;					\
	return result;											\
	}

#ifdef QVIPP
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, uChar, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, uChar, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, uChar, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, uChar, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, uChar, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, uChar, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, uChar, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, uChar, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, uChar, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, uChar, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, uChar, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, uChar, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, uChar, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, uChar, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, uChar, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, uChar, sFloat);

CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, uShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, uShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, uShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, uShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, uShort, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, uShort, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, uShort, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, uShort, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, uShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, uShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, uShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, uShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, uShort, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, uShort, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, uShort, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, uShort, sFloat);

CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, sShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, sShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, sShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, sShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, sShort, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, sShort, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, sShort, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, sShort, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, sShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, sShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, sShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, sShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, sShort, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, sShort, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, sShort, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, sShort, sFloat);

CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, sInt, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, sInt, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, sInt, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, sInt, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, sInt, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, sInt, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, sInt, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, sInt, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, sInt, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, sInt, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, sInt, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, sInt, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, sInt, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, sInt, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, sInt, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, sInt, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, sInt, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, sInt, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, sInt, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, sInt, sFloat);

CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, sFloat, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, sFloat, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, sFloat, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, sFloat, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, sFloat, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, sFloat, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, sFloat, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, sFloat, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, sFloat, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, sFloat, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, sFloat, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, sFloat, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<, <, sFloat, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>, >, sFloat, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator<=, <=, sFloat, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C1(operator>=, >=, sFloat, sInt);
#endif

#define CREATE_GENERIC_COMPARE_OPERATOR_C3(OPERATOR, OPERATION, TYPE1, TYPE2)					\
template <> QVImage<uChar> QVImage<TYPE1, 3>::OPERATOR(const QVImage<TYPE2, 3> &img) const			\
	{													\
	QVImage<uChar> result(getCols(), getRows());								\
	result.setROI(getROI()); result.setAnchor(getAnchor());							\
	QVIMAGE_PTR_INIT_READ(TYPE1, this);									\
	QVIMAGE_INIT_READ(TYPE2, img);										\
	QVIMAGE_INIT_WRITE(uChar, result);									\
	for (int col = result.getROI().left(); col < result.getROI().right(); col++)				\
		for (int row = result.getROI().top(); row < result.getROI().bottom(); row++)			\
			{											\
			if( (QVIMAGE_PIXEL(this, col, row, 0) OPERATION QVIMAGE_PIXEL(img, col, row, 0)) &&	\
			    (QVIMAGE_PIXEL(this, col, row, 1) OPERATION QVIMAGE_PIXEL(img, col, row, 1)) &&	\
			    (QVIMAGE_PIXEL(this, col, row, 2) OPERATION QVIMAGE_PIXEL(img, col, row, 2))    )	\
				QVIMAGE_PIXEL(result, col, row, 0) = IPP_MAX_8U;				\
			else	QVIMAGE_PIXEL(result, col, row, 0) = 0;						\
			}											\
	return result;												\
	}

#ifdef QVIPP
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, uChar, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, uChar, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, uChar, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, uChar, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, uChar, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, uChar, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, uChar, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, uChar, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, uChar, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, uChar, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, uChar, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, uChar, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, uChar, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, uChar, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, uChar, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, uChar, sFloat);

CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, uShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, uShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, uShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, uShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, uShort, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, uShort, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, uShort, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, uShort, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, uShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, uShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, uShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, uShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, uShort, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, uShort, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, uShort, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, uShort, sFloat);

CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, sShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, sShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, sShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, sShort, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, sShort, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, sShort, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, sShort, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, sShort, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, sShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, sShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, sShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, sShort, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, sShort, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, sShort, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, sShort, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, sShort, sFloat);

CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, sInt, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, sInt, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, sInt, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, sInt, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, sInt, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, sInt, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, sInt, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, sInt, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, sInt, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, sInt, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, sInt, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, sInt, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, sInt, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, sInt, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, sInt, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, sInt, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, sInt, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, sInt, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, sInt, sFloat);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, sInt, sFloat);

CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, sFloat, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, sFloat, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, sFloat, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, sFloat, uChar);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, sFloat, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, sFloat, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, sFloat, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, sFloat, uShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, sFloat, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, sFloat, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, sFloat, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, sFloat, sShort);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<, <, sFloat, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>, >, sFloat, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator<=, <=, sFloat, sInt);
CREATE_GENERIC_COMPARE_OPERATOR_C3(operator>=, >=, sFloat, sInt);
#endif

// Set FUNCTION
#define	CREATE_SET_FUNCTION_C1(TYPE)				\
template <> void QVImage<TYPE>::set(TYPE c1, TYPE, TYPE)	\
	{ Set(c1, *this); }

CREATE_SET_FUNCTION_C1(uChar);
CREATE_SET_FUNCTION_C1(uShort);
CREATE_SET_FUNCTION_C1(sShort);
CREATE_SET_FUNCTION_C1(sInt);
CREATE_SET_FUNCTION_C1(sFloat);

#define	CREATE_SET_FUNCTION_C3(TYPE)					\
template <> void QVImage<TYPE,3>::set(TYPE c1, TYPE c2, TYPE c3)	\
	{								\
	const TYPE values[3] = { c1, c2, c3 };				\
	Set(values, *this);						\
	}

CREATE_SET_FUNCTION_C3(uChar);
CREATE_SET_FUNCTION_C3(uShort);
CREATE_SET_FUNCTION_C3(sShort);
CREATE_SET_FUNCTION_C3(sInt);
CREATE_SET_FUNCTION_C3(sFloat);

//////////////
// operator =
#define	CREATE_CONVERT_OPERATOR(TYPE1, TYPE2, C)						\
template <> QVImage<TYPE2, C> & QVImage<TYPE2, C>::operator=(const QVImage<TYPE1, C> &img)	\
	{											\
	imageBuffer = new QVImageBuffer<TYPE2>(C*img.getCols(), img.getRows());		\
	setAnchor(img.getROI().x(),img.getROI().y());						\
	Convert(img, *this);									\
	setROI(img.getROI()); setAnchor(img.getAnchor());					\
	step_div_type_size = getStep()/sizeof(TYPE2);						\
	return *this;										\
	}

//#ifdef QVIPP
CREATE_CONVERT_OPERATOR(uChar, uShort, 1);
CREATE_CONVERT_OPERATOR(uChar, sShort, 1);
CREATE_CONVERT_OPERATOR(uChar, sInt, 1);
CREATE_CONVERT_OPERATOR(uChar, sFloat, 1);
CREATE_CONVERT_OPERATOR(uChar, uShort, 3);
CREATE_CONVERT_OPERATOR(uChar, sShort, 3);
CREATE_CONVERT_OPERATOR(uChar, sInt, 3);
CREATE_CONVERT_OPERATOR(uChar, sFloat, 3);
CREATE_CONVERT_OPERATOR(uShort, uChar, 1);
CREATE_CONVERT_OPERATOR(uShort, sInt, 1);
CREATE_CONVERT_OPERATOR(uShort, sFloat, 1);
CREATE_CONVERT_OPERATOR(uShort, uChar, 3);
CREATE_CONVERT_OPERATOR(uShort, sInt, 3);
CREATE_CONVERT_OPERATOR(uShort, sFloat, 3);
CREATE_CONVERT_OPERATOR(sShort, uChar, 1);
CREATE_CONVERT_OPERATOR(sShort, sInt, 1);
CREATE_CONVERT_OPERATOR(sShort, sFloat, 1);
CREATE_CONVERT_OPERATOR(sShort, uChar, 3);
CREATE_CONVERT_OPERATOR(sShort, sInt, 3);
CREATE_CONVERT_OPERATOR(sShort, sFloat, 3);
CREATE_CONVERT_OPERATOR(sInt, uChar, 1);
CREATE_CONVERT_OPERATOR(sInt, uChar, 3);
CREATE_CONVERT_OPERATOR(sFloat, uChar, 1);
CREATE_CONVERT_OPERATOR(sFloat, uShort, 1);
CREATE_CONVERT_OPERATOR(sFloat, sShort, 1);
CREATE_CONVERT_OPERATOR(sFloat, uChar, 3);
CREATE_CONVERT_OPERATOR(sFloat, uShort, 3);
CREATE_CONVERT_OPERATOR(sFloat, sShort, 3);
//#endif

// Nota: las siguientes funciones dan error al compilar, ya que no existen versiones de la función wrapper Convert,
// para convertir de una imagen entera, a una imagen de tipo uShort, sShort, o sFloat.
//	CREATE_CONVERT_OPERATOR(uShort, sInt, 1);
//	CREATE_CONVERT_OPERATOR(sShort, sInt, 1);
//	CREATE_CONVERT_OPERATOR(uShort, sInt, 3);
//	CREATE_CONVERT_OPERATOR(sShort, sInt, 3);
//	CREATE_CONVERT_OPERATOR(sFloat, sInt, 3);
//	CREATE_CONVERT_OPERATOR(sFloat, sInt, 3);
//
// Por ello, estas funciones deben ser definidas con funciones de conversión Ad-hoc, así como las funciones de conversión
// de valores uShort a valores sShort, y viceversa, que tampoco están implementadas por las IPP, ni las funciones para convertir
// imagenes de distinto tipo y canal.
//
// Ojo: Para implementar las funciones de conversión entre imagenes de tipo sShort y uShort, hay que tener en cuenta la saturación
// (que hacen las IPP para todas las funciones de conversión que implementa):
// - Si se quiere convertir un valor sShort menor que cero a un valor uShort, se deja como el valor cero (0).
// - Si se quiere convertir un valor uShort mayor que IPP_MAX_16S a sShort, se debe dejar como el valor IPP_MAX_16S.

/*
#define	CREATE_CONVERT_OPERATOR_NO_IPP_1(TYPE1, TYPE2)							\
template <> QVImage<TYPE2, 1> & QVImage<TYPE2, 1>::operator=(const QVImage<TYPE1, 1> &img)		\
	{												\
	imageBuffer = new QVImageBuffer<TYPE2>(img.getCols(), img.getRows());			\
	QVIMAGE_PTR_INIT_WRITE(TYPE2, this);								\
	QVIMAGE_INIT_READ(TYPE1, img);									\
	for (int col = img.getROI().left(); col < img.getROI().right(); col++)				\
		for (int row = img.getROI().top(); row < img.getROI().bottom(); row++)			\
			QVIMAGE_PIXEL(this, col, row, 0) = (TYPE2)QVIMAGE_PIXEL(img, col, row, 0);	\
 	setROI(img.getROI()); setAnchor(img.getAnchor());						\
	step_div_type_size = getStep()/sizeof(TYPE2);							\
	return *this;											\
	}

CREATE_CONVERT_OPERATOR_NO_IPP_1(uShort, sShort);
CREATE_CONVERT_OPERATOR_NO_IPP_1(sShort, uShort);
CREATE_CONVERT_OPERATOR_NO_IPP_1(sInt, uShort);
CREATE_CONVERT_OPERATOR_NO_IPP_1(sInt, sShort);
CREATE_CONVERT_OPERATOR_NO_IPP_1(sInt, sFloat);
CREATE_CONVERT_OPERATOR_NO_IPP_1(sFloat, sInt);

#define	CREATE_CONVERT_OPERATOR_NO_IPP_3(TYPE1, TYPE2)							\
template <> QVImage<TYPE2, 3> & QVImage<TYPE2, 3>::operator=(const QVImage<TYPE1, 3> &img)		\
	{												\
	imageBuffer = new QVImageBuffer<TYPE2>(3*img.getCols(), img.getRows());			\
	QVIMAGE_PTR_INIT_WRITE(TYPE2, this);								\
	QVIMAGE_INIT_READ(TYPE1, img);									\
	for (int col = img.getROI().left(); col < img.getROI().right(); col++)				\
		for (int row = img.getROI().top(); row < img.getROI().bottom(); row++)			\
			{										\
			QVIMAGE_PIXEL(this, col, row, 0) = (TYPE2)QVIMAGE_PIXEL(img, col, row, 0);		\
			QVIMAGE_PIXEL(this, col, row, 1) = (TYPE2)QVIMAGE_PIXEL(img, col, row, 1);		\
			QVIMAGE_PIXEL(this, col, row, 2) = (TYPE2)QVIMAGE_PIXEL(img, col, row, 2);		\
			}										\
 	setROI(img.getROI()); setAnchor(img.getAnchor());						\
	step_div_type_size = getStep()/sizeof(TYPE2);							\
	return *this;											\
	}


CREATE_CONVERT_OPERATOR_NO_IPP_3(uShort, sShort);
CREATE_CONVERT_OPERATOR_NO_IPP_3(sShort, uShort);
CREATE_CONVERT_OPERATOR_NO_IPP_3(sInt, uShort);
CREATE_CONVERT_OPERATOR_NO_IPP_3(sInt, sShort);
CREATE_CONVERT_OPERATOR_NO_IPP_3(sInt, sFloat);
CREATE_CONVERT_OPERATOR_NO_IPP_3(sFloat, sInt);
*/

#define	CREATE_CONVERT_OPERATOR_C3_C1(TYPE)													\
template <> QVImage<TYPE, 1> & QVImage<TYPE, 1>::operator=(const QVImage<TYPE, 3> &img)		\
	{																						\
	imageBuffer = new QVImageBuffer<TYPE>(img.getCols(), img.getRows());					\
	setAnchor(img.getROI().x(),img.getROI().y());											\
	RGBToGray(img, *this);																	\
	setROI(img.getROI()); setAnchor(img.getAnchor());										\
	step_div_type_size = getStep()/sizeof(TYPE);											\
	return *this;																			\
	}

//#ifdef QVIPP
CREATE_CONVERT_OPERATOR_C3_C1(uChar);
CREATE_CONVERT_OPERATOR_C3_C1(sChar);
CREATE_CONVERT_OPERATOR_C3_C1(uInt);
CREATE_CONVERT_OPERATOR_C3_C1(sInt);
CREATE_CONVERT_OPERATOR_C3_C1(uShort);
CREATE_CONVERT_OPERATOR_C3_C1(sShort);
CREATE_CONVERT_OPERATOR_C3_C1(sFloat);
//#endif

/*#define	CREATE_CONVERT_OPERATOR_NO_IPP_C3_C1(TYPE)							\
template <> QVImage<TYPE, 1> & QVImage<TYPE, 1>::operator=(const QVImage<TYPE, 3> &img)			\
	{												\
	imageBuffer = new QVImageBuffer<TYPE>(img.getCols(), img.getRows());				\
	QVIMAGE_PTR_INIT_WRITE(TYPE, this);								\
	QVIMAGE_INIT_READ(TYPE, img);									\
	for (int col = img.getROI().left(); col < img.getROI().right(); col++)				\
 		for (int row = img.getROI().top(); row < img.getROI().bottom(); row++)			\
			{										\
 			QVIMAGE_PIXEL(this, col, row, 0) = (TYPE)(0.299 * QVIMAGE_PIXEL(img, col, row, 0));	\
 			QVIMAGE_PIXEL(this, col, row, 0) += (TYPE)(0.587 * QVIMAGE_PIXEL(img, col, row, 1));	\
 			QVIMAGE_PIXEL(this, col, row, 0) += (TYPE)(0.114 * QVIMAGE_PIXEL(img, col, row, 2));	\
			}										\
  	setROI(img.getROI()); setAnchor(img.getAnchor());						\
	step_div_type_size = getStep()/sizeof(TYPE);							\
	return *this;											\
	}

CREATE_CONVERT_OPERATOR_NO_IPP_C3_C1(sInt);
#ifndef QVIPP
CREATE_CONVERT_OPERATOR_NO_IPP_C3_C1(uChar);
CREATE_CONVERT_OPERATOR_NO_IPP_C3_C1(sChar);
CREATE_CONVERT_OPERATOR_NO_IPP_C3_C1(uShort);
CREATE_CONVERT_OPERATOR_NO_IPP_C3_C1(sShort);
CREATE_CONVERT_OPERATOR_NO_IPP_C3_C1(sFloat);
#endif*/

#define	CREATE_CONVERT_OPERATOR_C1_C3(TYPE)													\
template <> QVImage<TYPE, 3> & QVImage<TYPE, 3>::operator=(const QVImage<TYPE, 1> &img)		\
	{																						\
	imageBuffer = new QVImageBuffer<TYPE>(3*img.getCols(), img.getRows());					\
	setAnchor(img.getROI().x(),img.getROI().y());											\
	Copy(img, img, img, *this);																\
	setROI(img.getROI()); setAnchor(img.getAnchor());										\
	step_div_type_size = getStep()/sizeof(TYPE);											\
	return *this;																			\
	}

#ifdef QVIPP
CREATE_CONVERT_OPERATOR_C1_C3(uChar);
CREATE_CONVERT_OPERATOR_C1_C3(uShort);
CREATE_CONVERT_OPERATOR_C1_C3(sShort);
CREATE_CONVERT_OPERATOR_C1_C3(sInt);
CREATE_CONVERT_OPERATOR_C1_C3(sFloat);
#endif

//Convert constructors with double conversion (after operator= declaration)
#define	CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(TYPE1, TYPE2)								\
template <> QVImage<TYPE2, 1>::QVImage(QVImage<TYPE1, 3> const &img):QVGenericImage(img)	\
	{																						\
	QVImage<TYPE1, 1> temp1(img);															\
	QVImage<TYPE2, 1> temp2(temp1);															\
	*this = temp2;																			\
	}

CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(uChar, uShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(uChar, sShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(uChar, sInt);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(uChar, sFloat);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(uShort, uChar);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(uShort, sShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(uShort, sInt);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(uShort, sFloat);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(sShort, uChar);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(sShort, uShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(sShort, sInt);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(sShort, sFloat);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(sInt, uChar);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(sInt, uShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(sInt, sShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(sInt, sFloat);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(sFloat, uChar);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(sFloat, uShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(sFloat, sShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C3_C1(sFloat, sInt);

#define	CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(TYPE1, TYPE2)								\
template <> QVImage<TYPE2, 3>::QVImage(QVImage<TYPE1, 1> const &img):QVGenericImage(img)	\
	{																						\
	QVImage<TYPE1, 3> temp1(img);															\
	QVImage<TYPE2, 3> temp2(temp1);															\
	*this = temp2;																			\
	}

CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(uChar, uShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(uChar, sShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(uChar, sInt);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(uChar, sFloat);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(uShort, uChar);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(uShort, sShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(uShort, sInt);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(uShort, sFloat);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(sShort, uChar);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(sShort, uShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(sShort, sInt);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(sShort, sFloat);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(sInt, uChar);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(sInt, uShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(sInt, sShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(sInt, sFloat);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(sFloat, uChar);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(sFloat, uShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(sFloat, sShort);
CREATE_CONVERT_CONSTRUCTOR_DOUBLE_C1_C3(sFloat, sInt);


#define	CREATE_ACCESS_CONSTRUCTOR(OPERATOR, TYPE, C)									\
template <> QVImage<TYPE, 1> QVImage<TYPE, C>::OPERATOR(const uInt channel) const		\
	{																					\
	QVImage<TYPE, 1> result(getCols(), getRows());										\
	Copy(*this, channel, result);														\
	result.setROI(getROI()); result.setAnchor(getAnchor());								\
	return result;																		\
	}

CREATE_ACCESS_CONSTRUCTOR(operator(), uChar, 1);
CREATE_ACCESS_CONSTRUCTOR(operator(), uChar, 3);
CREATE_ACCESS_CONSTRUCTOR(operator(), uShort, 1);
CREATE_ACCESS_CONSTRUCTOR(operator(), uShort, 3);
CREATE_ACCESS_CONSTRUCTOR(operator(), sShort, 1);
CREATE_ACCESS_CONSTRUCTOR(operator(), sShort, 3);
CREATE_ACCESS_CONSTRUCTOR(operator(), sInt, 1);
CREATE_ACCESS_CONSTRUCTOR(operator(), sInt, 3);
CREATE_ACCESS_CONSTRUCTOR(operator(), sFloat, 1);
CREATE_ACCESS_CONSTRUCTOR(operator(), sFloat, 3);

// == Substitute functions for IPP wrapper functions ==


#ifndef DOXYGEN_IGNORE_THIS
template<typename Type> void CopyC1x3C3(	const QVImage<Type, 1> &src1,
											const QVImage<Type, 1> &src2,
											const QVImage<Type, 1> &src3,
											QVImage<Type, 3> &dst)
	{
	const uInt cols = src1.getCols(), rows = src1.getRows();

	Q_ASSERT_X(src2.getCols() == cols, "CopyC1x3C3", "Number of columns for images 1 and 2 do not match");
	Q_ASSERT_X(src2.getRows() == rows, "CopyC1x3C3", "Number of rows for images 1 and 2 do not match");
	Q_ASSERT_X(src3.getCols() == cols, "CopyC1x3C3", "Number of columns for images 1 and 3 do not match");
	Q_ASSERT_X(src3.getRows() == rows, "CopyC1x3C3", "Number of rows for images 1 and 3 do not match");

	dst = QVImage<Type, 3>(cols, rows);
	dst.setROI(src1.getROI());

	Type const	*src1Data = src1.getReadData(),
				*src2Data = src2.getReadData(),
				*src3Data = src3.getReadData();

	Type *dstData = dst.getWriteData();
	const uInt	src1Step = src1.getStep(),
				src2Step = src2.getStep(),
				src3Step = src3.getStep(),
				dstStep = dst.getStep();

	for(uInt i = 0; i < rows; i++)
		{
		for(uInt j = 0; j < cols; j++)
			{
			dstData[3*j+0] = src1Data[j];
			dstData[3*j+1] = src2Data[j];
			dstData[3*j+2] = src3Data[j];
			}

		src1Data += src1Step;
		src2Data += src2Step;
		src3Data += src3Step;
		dstData += dstStep;
		}
	}

template<typename Type> void ConvertC1C3(const QVImage<Type, 1> &src, QVImage<Type, 3> &dst)
	{
	const int cols = src.getCols(), rows = src.getRows();

	dst = QVImage<Type, 3>(cols, rows);
	dst.setROI(src.getROI());

	Type const *srcData = src.getReadData();
	Type *dstData = dst.getWriteData();
	const int	srcStep = src.getStep(),
				dstStep = dst.getStep();

	for(int i = 0; i < rows; i++)
		{
		for(int j = 0; j < cols; j++)
			dstData[3*j+0] = dstData[3*j+1] = dstData[3*j+2] = srcData[j];
		srcData += srcStep;
		dstData += dstStep;
		}
	}

template<typename Type> void ConvertC3C1(const QVImage<Type, 3> &src, QVImage<Type, 1> &dst)
	{
	const int cols = src.getCols(), rows = src.getRows();

	dst = QVImage<Type, 1>(cols, rows);
	dst.setROI(src.getROI());

	Type const *srcData = src.getReadData();
	Type *dstData = dst.getWriteData();
	const int	srcStep = src.getStep(),
				dstStep = dst.getStep();

	for(int i = 0; i < rows; i++)
		{
		for(int j = 0; j < cols; j++)
			dstData[j] = (srcData[3*j+0] + srcData[3*j+1] + srcData[3*j+2])/3;
		srcData += srcStep;
		dstData += dstStep;
		}
	}

template<typename Type1, typename Type2, int C> void ConvertType(const QVImage<Type1, C> &src, QVImage<Type2, C> &dst)
	{
	const int cols = src.getCols(), rows = src.getRows();

	dst = QVImage<Type2, C>(cols, rows);
	dst.setROI(src.getROI());

	Type1 const *srcData = src.getReadData();
	Type2 *dstData = dst.getWriteData();
	const int	srcStep = src.getStep(),
				dstStep = dst.getStep();

	for(int i = 0; i < rows; i++)
		{
		for(int j = 0; j < C*cols; j++)
			dstData[j] = srcData[j];
		srcData += srcStep;
		dstData += dstStep;
		}
	}

template<typename Type> void CopyC3C1(const QVImage<Type, 3> &src, const uChar channel, QVImage<Type, 1> &dst)
	{
	const int cols = src.getCols(), rows = src.getRows();

	dst = QVImage<Type, 1>(cols, rows);
	dst.setROI(src.getROI());

	Type const *srcData = src.getReadData();
	Type *dstData = dst.getWriteData();
	const int	srcStep = src.getStep(),
				dstStep = dst.getStep();

	for(int i = 0; i < rows; i++)
		{
		for(int j = 0; j < cols; j++)
			dstData[j] = srcData[3*j+channel];
		srcData += srcStep;
		dstData += dstStep;
		}
	}

#endif // DOXYGEN_IGNORE_THIS

#ifndef QVIPP
#define	CREATE_SET_NO_IPP_C1(TYPE)								\
void Set(const TYPE value, QVImage<TYPE, 1> &image)				\
	{															\
	const int cols = image.getCols(), rows = image.getRows();	\
																\
	QVIMAGE_INIT_WRITE(TYPE,image);								\
	for(int row = 0; row < rows; row++)							\
		for(int col = 0; col < cols; col++)						\
			QVIMAGE_PIXEL(image, col, row, 0) = value;			\
	}

CREATE_SET_NO_IPP_C1(uChar);
CREATE_SET_NO_IPP_C1(sFloat);
CREATE_SET_NO_IPP_C1(sInt);
CREATE_SET_NO_IPP_C1(uInt);
CREATE_SET_NO_IPP_C1(sShort);
CREATE_SET_NO_IPP_C1(uShort);

#define	CREATE_SET_NO_IPP_C3(TYPE)								\
void Set(const TYPE value[3], QVImage<TYPE, 3> &image)			\
	{															\
	const int cols = image.getCols(), rows = image.getRows();	\
																\
	QVIMAGE_INIT_WRITE(TYPE, image);							\
	for(int row = 0; row < rows; row++)							\
		for(int col = 0; col < cols; col++)						\
			{													\
			QVIMAGE_PIXEL(image, col, row, 0) = value[0];		\
			QVIMAGE_PIXEL(image, col, row, 1) = value[1];		\
			QVIMAGE_PIXEL(image, col, row, 2) = value[2];		\
			}													\
	}

CREATE_SET_NO_IPP_C3(uChar);
CREATE_SET_NO_IPP_C3(sFloat);
CREATE_SET_NO_IPP_C3(sInt);
CREATE_SET_NO_IPP_C3(uInt);
CREATE_SET_NO_IPP_C3(sShort);
CREATE_SET_NO_IPP_C3(uShort);

#define	CREATE_COPY_NO_IPP(TYPE, C)								\
void Copy(const QVImage<TYPE, C> &src, QVImage<TYPE, C> &dest)	\
	{															\
	dest = src;													\
	}

CREATE_COPY_NO_IPP(uChar, 1);
CREATE_COPY_NO_IPP(sFloat, 1);
CREATE_COPY_NO_IPP(sInt, 1);
CREATE_COPY_NO_IPP(uInt, 1);
CREATE_COPY_NO_IPP(sShort, 1);
CREATE_COPY_NO_IPP(uShort, 1);

CREATE_COPY_NO_IPP(uChar, 3);
CREATE_COPY_NO_IPP(sFloat, 3);
CREATE_COPY_NO_IPP(sInt, 3);
CREATE_COPY_NO_IPP(uInt, 3);
CREATE_COPY_NO_IPP(sShort, 3);
CREATE_COPY_NO_IPP(uShort, 3);

void Copy(const QVImage<sFloat, 3> &src, const uChar channel, QVImage<sFloat, 1> &dst)	{ CopyC3C1<sFloat>(src, channel, dst); }
void Copy(const QVImage<uChar, 3> &src, const uChar channel, QVImage<uChar, 1> &dst)	{ CopyC3C1<uChar>(src, channel, dst); }
void Copy(const QVImage<sChar, 3> &src, const uChar channel, QVImage<sChar, 1> &dst)	{ CopyC3C1<sChar>(src, channel, dst); }
void Copy(const QVImage<sInt, 3> &src, const uChar channel, QVImage<sInt, 1> &dst)		{ CopyC3C1<sInt>(src, channel, dst); }
void Copy(const QVImage<uInt, 3> &src, const uChar channel, QVImage<uInt, 1> &dst)		{ CopyC3C1<uInt>(src, channel, dst); }
void Copy(const QVImage<sShort, 3> &src, const uChar channel, QVImage<sShort, 1> &dst)	{ CopyC3C1<sShort>(src, channel, dst); }
void Copy(const QVImage<uShort, 3> &src, const uChar channel, QVImage<uShort, 1> &dst)	{ CopyC3C1<uShort>(src, channel, dst); }

// Convert method.
// sFloat
//void Convert(const QVImage<sFloat, 1> &src, QVImage<sFloat, 1> &dst)	{ ConvertType<sFloat, sFloat, 1>(src, dst); }
void Convert(const QVImage<sFloat, 1> &src, QVImage<uChar, 1> &dst)	{ ConvertType<sFloat, uChar, 1>(src, dst); }
void Convert(const QVImage<sFloat, 1> &src, QVImage<sChar, 1> &dst)	{ ConvertType<sFloat, sChar, 1>(src, dst); }
void Convert(const QVImage<sFloat, 1> &src, QVImage<sInt, 1> &dst)	{ ConvertType<sFloat, sInt, 1>(src, dst); }
void Convert(const QVImage<sFloat, 1> &src, QVImage<uInt, 1> &dst)	{ ConvertType<sFloat, uInt, 1>(src, dst); }
void Convert(const QVImage<sFloat, 1> &src, QVImage<sShort, 1> &dst)	{ ConvertType<sFloat, sShort, 1>(src, dst); }
void Convert(const QVImage<sFloat, 1> &src, QVImage<uShort, 1> &dst)	{ ConvertType<sFloat, uShort, 1>(src, dst); }

//void Convert(const QVImage<sFloat, 3> &src, QVImage<sFloat, 3> &dst)	{ ConvertType<sFloat, sFloat, 3>(src, dst); }
void Convert(const QVImage<sFloat, 3> &src, QVImage<uChar, 3> &dst)	{ ConvertType<sFloat, uChar, 3>(src, dst); }
void Convert(const QVImage<sFloat, 3> &src, QVImage<sChar, 3> &dst)	{ ConvertType<sFloat, sChar, 3>(src, dst); }
void Convert(const QVImage<sFloat, 3> &src, QVImage<sInt, 3> &dst)	{ ConvertType<sFloat, sInt, 3>(src, dst); }
void Convert(const QVImage<sFloat, 3> &src, QVImage<uInt, 3> &dst)	{ ConvertType<sFloat, uInt, 3>(src, dst); }
void Convert(const QVImage<sFloat, 3> &src, QVImage<sShort, 3> &dst)	{ ConvertType<sFloat, sShort, 3>(src, dst); }
void Convert(const QVImage<sFloat, 3> &src, QVImage<uShort, 3> &dst)	{ ConvertType<sFloat, uShort, 3>(src, dst); }

// uChar
void Convert(const QVImage<uChar, 1> &src, QVImage<sFloat, 1> &dst)	{ ConvertType<uChar, sFloat, 1>(src, dst); }
//void Convert(const QVImage<uChar, 1> &src, QVImage<uChar, 1> &dst)	{ ConvertType<uChar, uChar, 1>(src, dst); }
void Convert(const QVImage<uChar, 1> &src, QVImage<sChar, 1> &dst)	{ ConvertType<uChar, sChar, 1>(src, dst); }
void Convert(const QVImage<uChar, 1> &src, QVImage<sInt, 1> &dst)	{ ConvertType<uChar, sInt, 1>(src, dst); }
void Convert(const QVImage<uChar, 1> &src, QVImage<uInt, 1> &dst)	{ ConvertType<uChar, uInt, 1>(src, dst); }
void Convert(const QVImage<uChar, 1> &src, QVImage<sShort, 1> &dst)	{ ConvertType<uChar, sShort, 1>(src, dst); }
void Convert(const QVImage<uChar, 1> &src, QVImage<uShort, 1> &dst)	{ ConvertType<uChar, uShort, 1>(src, dst); }

void Convert(const QVImage<uChar, 3> &src, QVImage<sFloat, 3> &dst)	{ ConvertType<uChar, sFloat, 3>(src, dst); }
//void Convert(const QVImage<uChar, 3> &src, QVImage<uChar, 3> &dst)	{ ConvertType<uChar, uChar, 3>(src, dst); }
void Convert(const QVImage<uChar, 3> &src, QVImage<sChar, 3> &dst)	{ ConvertType<uChar, sChar, 3>(src, dst); }
void Convert(const QVImage<uChar, 3> &src, QVImage<sInt, 3> &dst)	{ ConvertType<uChar, sInt, 3>(src, dst); }
void Convert(const QVImage<uChar, 3> &src, QVImage<uInt, 3> &dst)	{ ConvertType<uChar, uInt, 3>(src, dst); }
void Convert(const QVImage<uChar, 3> &src, QVImage<sShort, 3> &dst)	{ ConvertType<uChar, sShort, 3>(src, dst); }
void Convert(const QVImage<uChar, 3> &src, QVImage<uShort, 3> &dst)	{ ConvertType<uChar, uShort, 3>(src, dst); }

// sChar
void Convert(const QVImage<sChar, 1> &src, QVImage<sFloat, 1> &dst)	{ ConvertType<sChar, sFloat, 1>(src, dst); }
void Convert(const QVImage<sChar, 1> &src, QVImage<uChar, 1> &dst)	{ ConvertType<sChar, uChar, 1>(src, dst); }
//void Convert(const QVImage<sChar, 1> &src, QVImage<sChar, 1> &dst)	{ ConvertType<uChar, sChar, 1>(src, dst); }
void Convert(const QVImage<sChar, 1> &src, QVImage<sInt, 1> &dst)	{ ConvertType<sChar, sInt, 1>(src, dst); }
void Convert(const QVImage<sChar, 1> &src, QVImage<uInt, 1> &dst)	{ ConvertType<sChar, uInt, 1>(src, dst); }
void Convert(const QVImage<sChar, 1> &src, QVImage<sShort, 1> &dst)	{ ConvertType<sChar, sShort, 1>(src, dst); }
void Convert(const QVImage<sChar, 1> &src, QVImage<uShort, 1> &dst)	{ ConvertType<sChar, uShort, 1>(src, dst); }

void Convert(const QVImage<sChar, 3> &src, QVImage<sFloat, 3> &dst)	{ ConvertType<sChar, sFloat, 3>(src, dst); }
void Convert(const QVImage<sChar, 3> &src, QVImage<uChar, 3> &dst)	{ ConvertType<sChar, uChar, 3>(src, dst); }
//void Convert(const QVImage<sChar, 3> &src, QVImage<sChar, 3> &dst)	{ ConvertType<uChar, sChar, 3>(src, dst); }
void Convert(const QVImage<sChar, 3> &src, QVImage<sInt, 3> &dst)	{ ConvertType<sChar, sInt, 3>(src, dst); }
void Convert(const QVImage<sChar, 3> &src, QVImage<uInt, 3> &dst)	{ ConvertType<sChar, uInt, 3>(src, dst); }
void Convert(const QVImage<sChar, 3> &src, QVImage<sShort, 3> &dst)	{ ConvertType<sChar, sShort, 3>(src, dst); }
void Convert(const QVImage<sChar, 3> &src, QVImage<uShort, 3> &dst)	{ ConvertType<sChar, uShort, 3>(src, dst); }

// sInt
void Convert(const QVImage<sInt, 1> &src, QVImage<sFloat, 1> &dst)	{ ConvertType<sInt, sFloat, 1>(src, dst); }
void Convert(const QVImage<sInt, 1> &src, QVImage<uChar, 1> &dst)	{ ConvertType<sInt, uChar, 1>(src, dst); }
void Convert(const QVImage<sInt, 1> &src, QVImage<sChar, 1> &dst)	{ ConvertType<sInt, sChar, 1>(src, dst); }
//void Convert(const QVImage<sInt, 1> &src, QVImage<sInt, 1> &dst)	{ ConvertType<sInt, sInt, 1>(src, dst); }
void Convert(const QVImage<sInt, 1> &src, QVImage<uInt, 1> &dst)	{ ConvertType<sInt, uInt, 1>(src, dst); }
void Convert(const QVImage<sInt, 1> &src, QVImage<sShort, 1> &dst)	{ ConvertType<sInt, sShort, 1>(src, dst); }
void Convert(const QVImage<sInt, 1> &src, QVImage<uShort, 1> &dst)	{ ConvertType<sInt, uShort, 1>(src, dst); }

void Convert(const QVImage<sInt, 3> &src, QVImage<sFloat, 3> &dst)	{ ConvertType<sInt, sFloat, 3>(src, dst); }
void Convert(const QVImage<sInt, 3> &src, QVImage<uChar, 3> &dst)	{ ConvertType<sInt, uChar, 3>(src, dst); }
void Convert(const QVImage<sInt, 3> &src, QVImage<sChar, 3> &dst)	{ ConvertType<sInt, sChar, 3>(src, dst); }
//void Convert(const QVImage<sInt, 3> &src, QVImage<sInt, 3> &dst)	{ ConvertType<sInt, sInt, 3>(src, dst); }
void Convert(const QVImage<sInt, 3> &src, QVImage<uInt, 3> &dst)	{ ConvertType<sInt, uInt, 3>(src, dst); }
void Convert(const QVImage<sInt, 3> &src, QVImage<sShort, 3> &dst)	{ ConvertType<sInt, sShort, 3>(src, dst); }
void Convert(const QVImage<sInt, 3> &src, QVImage<uShort, 3> &dst)	{ ConvertType<sInt, uShort, 3>(src, dst); }

// uInt
void Convert(const QVImage<uInt, 1> &src, QVImage<sFloat, 1> &dst)	{ ConvertType<uInt, sFloat, 1>(src, dst); }
void Convert(const QVImage<uInt, 1> &src, QVImage<uChar, 1> &dst)	{ ConvertType<uInt, uChar, 1>(src, dst); }
void Convert(const QVImage<uInt, 1> &src, QVImage<sChar, 1> &dst)	{ ConvertType<uInt, sChar, 1>(src, dst); }
void Convert(const QVImage<uInt, 1> &src, QVImage<sInt, 1> &dst)	{ ConvertType<uInt, sInt, 1>(src, dst); }
//void Convert(const QVImage<uInt, 1> &src, QVImage<uInt, 1> &dst)	{ ConvertType<uInt, uInt, 1>(src, dst); }
void Convert(const QVImage<uInt, 1> &src, QVImage<sShort, 1> &dst)	{ ConvertType<uInt, sShort, 1>(src, dst); }
void Convert(const QVImage<uInt, 1> &src, QVImage<uShort, 1> &dst)	{ ConvertType<uInt, uShort, 1>(src, dst); }

void Convert(const QVImage<uInt, 3> &src, QVImage<sFloat, 3> &dst)	{ ConvertType<uInt, sFloat, 3>(src, dst); }
void Convert(const QVImage<uInt, 3> &src, QVImage<uChar, 3> &dst)	{ ConvertType<uInt, uChar, 3>(src, dst); }
void Convert(const QVImage<uInt, 3> &src, QVImage<sChar, 3> &dst)	{ ConvertType<uInt, sChar, 3>(src, dst); }
void Convert(const QVImage<uInt, 3> &src, QVImage<sInt, 3> &dst)	{ ConvertType<uInt, sInt, 3>(src, dst); }
//void Convert(const QVImage<uInt, 3> &src, QVImage<uInt, 3> &dst)	{ ConvertType<uInt, uInt, 3>(src, dst); }
void Convert(const QVImage<uInt, 3> &src, QVImage<sShort, 3> &dst)	{ ConvertType<uInt, sShort, 3>(src, dst); }
void Convert(const QVImage<uInt, 3> &src, QVImage<uShort, 3> &dst)	{ ConvertType<uInt, uShort, 3>(src, dst); }

// sShort
void Convert(const QVImage<sShort, 1> &src, QVImage<sFloat, 1> &dst)	{ ConvertType<sShort, sFloat, 1>(src, dst); }
void Convert(const QVImage<sShort, 1> &src, QVImage<uChar, 1> &dst)	{ ConvertType<sShort, uChar, 1>(src, dst); }
void Convert(const QVImage<sShort, 1> &src, QVImage<sChar, 1> &dst)	{ ConvertType<sShort, sChar, 1>(src, dst); }
void Convert(const QVImage<sShort, 1> &src, QVImage<sInt, 1> &dst)	{ ConvertType<sShort, sInt, 1>(src, dst); }
void Convert(const QVImage<sShort, 1> &src, QVImage<uInt, 1> &dst)	{ ConvertType<sShort, uInt, 1>(src, dst); }
//void Convert(const QVImage<sShort, 1> &src, QVImage<sShort, 1> &dst)	{ ConvertType<sShort, sShort, 1>(src, dst); }
void Convert(const QVImage<sShort, 1> &src, QVImage<uShort, 1> &dst)	{ ConvertType<sShort, uShort, 1>(src, dst); }

void Convert(const QVImage<sShort, 3> &src, QVImage<sFloat, 3> &dst)	{ ConvertType<sShort, sFloat, 3>(src, dst); }
void Convert(const QVImage<sShort, 3> &src, QVImage<uChar, 3> &dst)	{ ConvertType<sShort, uChar, 3>(src, dst); }
void Convert(const QVImage<sShort, 3> &src, QVImage<sChar, 3> &dst)	{ ConvertType<sShort, sChar, 3>(src, dst); }
void Convert(const QVImage<sShort, 3> &src, QVImage<sInt, 3> &dst)	{ ConvertType<sShort, sInt, 3>(src, dst); }
void Convert(const QVImage<sShort, 3> &src, QVImage<uInt, 3> &dst)	{ ConvertType<sShort, uInt, 3>(src, dst); }
//void Convert(const QVImage<sShort, 3> &src, QVImage<sShort, 3> &dst)	{ ConvertType<sShort, sShort, 3>(src, dst); }
void Convert(const QVImage<sShort, 3> &src, QVImage<uShort, 3> &dst)	{ ConvertType<sShort, uShort, 3>(src, dst); }

// uShort
void Convert(const QVImage<uShort, 1> &src, QVImage<sFloat, 1> &dst)	{ ConvertType<uShort, sFloat, 1>(src, dst); }
void Convert(const QVImage<uShort, 1> &src, QVImage<uChar, 1> &dst)	{ ConvertType<uShort, uChar, 1>(src, dst); }
void Convert(const QVImage<uShort, 1> &src, QVImage<sChar, 1> &dst)	{ ConvertType<uShort, sChar, 1>(src, dst); }
void Convert(const QVImage<uShort, 1> &src, QVImage<sInt, 1> &dst)	{ ConvertType<uShort, sInt, 1>(src, dst); }
void Convert(const QVImage<uShort, 1> &src, QVImage<uInt, 1> &dst)	{ ConvertType<uShort, uInt, 1>(src, dst); }
void Convert(const QVImage<uShort, 1> &src, QVImage<sShort, 1> &dst)	{ ConvertType<uShort, sShort, 1>(src, dst); }
//void Convert(const QVImage<uShort, 1> &src, QVImage<uShort, 1> &dst)	{ ConvertType<uShort, uShort, 1>(src, dst); }

void Convert(const QVImage<uShort, 3> &src, QVImage<sFloat, 3> &dst)	{ ConvertType<uShort, sFloat, 3>(src, dst); }
void Convert(const QVImage<uShort, 3> &src, QVImage<uChar, 3> &dst)	{ ConvertType<uShort, uChar, 3>(src, dst); }
void Convert(const QVImage<uShort, 3> &src, QVImage<sChar, 3> &dst)	{ ConvertType<uShort, sChar, 3>(src, dst); }
void Convert(const QVImage<uShort, 3> &src, QVImage<sInt, 3> &dst)	{ ConvertType<uShort, sInt, 3>(src, dst); }
void Convert(const QVImage<uShort, 3> &src, QVImage<uInt, 3> &dst)	{ ConvertType<uShort, uInt, 3>(src, dst); }
void Convert(const QVImage<uShort, 3> &src, QVImage<sShort, 3> &dst)	{ ConvertType<uShort, sShort, 3>(src, dst); }
//void Convert(const QVImage<uShort, 3> &src, QVImage<uShort, 3> &dst)	{ ConvertType<uShort, uShort, 3>(src, dst); }

// Convert method.
void Convert(const QVImage<sFloat, 3> &src, QVImage<sFloat, 1> &dst)	{ ConvertC3C1<sFloat>(src, dst); }
void Convert(const QVImage<sChar, 3> &src, QVImage<sChar, 1> &dst)		{ ConvertC3C1<sChar>(src, dst); }
void Convert(const QVImage<uChar, 3> &src, QVImage<uChar, 1> &dst)		{ ConvertC3C1<uChar>(src, dst); }
void Convert(const QVImage<sInt, 3> &src, QVImage<sInt, 1> &dst)		{ ConvertC3C1<sInt>(src, dst); }
void Convert(const QVImage<uInt, 3> &src, QVImage<uInt, 1> &dst)		{ ConvertC3C1<uInt>(src, dst); }
void Convert(const QVImage<sShort, 3> &src, QVImage<sShort, 1> &dst)	{ ConvertC3C1<sShort>(src, dst); }
void Convert(const QVImage<uShort, 3> &src, QVImage<uShort, 1> &dst)	{ ConvertC3C1<uShort>(src, dst); }

void RGBToGray(const QVImage<sFloat, 3> &src, QVImage<sFloat, 1> &dst)	{ ConvertC3C1<sFloat>(src, dst); }
void RGBToGray(const QVImage<sChar, 3> &src, QVImage<sChar, 1> &dst)	{ ConvertC3C1<sChar>(src, dst); }
void RGBToGray(const QVImage<uChar, 3> &src, QVImage<uChar, 1> &dst)	{ ConvertC3C1<uChar>(src, dst); }
void RGBToGray(const QVImage<sInt, 3> &src, QVImage<sInt, 1> &dst)		{ ConvertC3C1<sInt>(src, dst); }
void RGBToGray(const QVImage<uInt, 3> &src, QVImage<uInt, 1> &dst)		{ ConvertC3C1<uInt>(src, dst); }
void RGBToGray(const QVImage<sShort, 3> &src, QVImage<sShort, 1> &dst)	{ ConvertC3C1<sShort>(src, dst); }
void RGBToGray(const QVImage<uShort, 3> &src, QVImage<uShort, 1> &dst)	{ ConvertC3C1<uShort>(src, dst); }

void Convert(const QVImage<sFloat, 1> &src, QVImage<sFloat, 3> &dst)	{ ConvertC1C3<sFloat>(src, dst); }
void Convert(const QVImage<sChar, 1> &src, QVImage<sChar, 3> &dst)		{ ConvertC1C3<sChar>(src, dst); }
void Convert(const QVImage<uChar, 1> &src, QVImage<uChar, 3> &dst)		{ ConvertC1C3<uChar>(src, dst); }
void Convert(const QVImage<sInt, 1> &src, QVImage<sInt, 3> &dst)		{ ConvertC1C3<sInt>(src, dst); }
void Convert(const QVImage<uInt, 1> &src, QVImage<uInt, 3> &dst)		{ ConvertC1C3<uInt>(src, dst); }
void Convert(const QVImage<sShort, 1> &src, QVImage<sShort, 3> &dst)	{ ConvertC1C3<sShort>(src, dst); }
void Convert(const QVImage<uShort, 1> &src, QVImage<uShort, 3> &dst)	{ ConvertC1C3<uShort>(src, dst); }

void Copy(const QVImage<sFloat, 1> &src1, const QVImage<sFloat, 1> &src2, const QVImage<sFloat, 1> &src3, QVImage<sFloat, 3> &dst)	{ CopyC1x3C3<sFloat>(src1, src2, src3, dst); }
void Copy(const QVImage<uChar, 1> &src1, const QVImage<uChar, 1> &src2, const QVImage<uChar, 1> &src3, QVImage<uChar, 3> &dst)		{ CopyC1x3C3<uChar>(src1, src2, src3, dst); }
void Copy(const QVImage<sChar, 1> &src1, const QVImage<sChar, 1> &src2, const QVImage<sChar, 1> &src3, QVImage<sChar, 3> &dst)		{ CopyC1x3C3<sChar>(src1, src2, src3, dst); }
void Copy(const QVImage<uInt, 1> &src1, const QVImage<uInt, 1> &src2, const QVImage<uInt, 1> &src3, QVImage<uInt, 3> &dst)			{ CopyC1x3C3<uInt>(src1, src2, src3, dst); }
void Copy(const QVImage<sInt, 1> &src1, const QVImage<sInt, 1> &src2, const QVImage<sInt, 1> &src3, QVImage<sInt, 3> &dst)			{ CopyC1x3C3<sInt>(src1, src2, src3, dst); }
void Copy(const QVImage<uShort, 1> &src1, const QVImage<uShort, 1> &src2, const QVImage<uShort, 1> &src3, QVImage<uShort, 3> &dst)	{ CopyC1x3C3<uShort>(src1, src2, src3, dst); }
void Copy(const QVImage<sShort, 1> &src1, const QVImage<sShort, 1> &src2, const QVImage<sShort, 1> &src3, QVImage<sShort, 3> &dst)	{ CopyC1x3C3<sShort>(src1, src2, src3, dst); }

// Unimplemented functions.
void Resize(const QVImage<uChar> &src, QVImage<uChar> &dest)
	{
	std::cout << "Warning: Resize function without IPP is to be implemented soon." << std::endl;
	dest = src;
	}

void Resize(const QVImage<uChar,3> &src, QVImage<uChar,3> &dest)
	{
	std::cout << "Warning: Resize function without IPP is to be implemented soon." << std::endl;
	dest = src;
	}

void YUV420ToRGB(const QVImage<uChar, 1> &srcY, const QVImage<uChar, 1> &srcU, const QVImage<uChar, 1> &srcV,
	QVImage<uChar, 3> &destRGB)
	{
	std::cout << "Warning: YUV420ToRGB function without IPP is to be implemented soon." << std::endl;
	/*const double y2 = y, u2 = u-128, v2 = v - 128;

	double	r =	+y2			+ 1.370705*v2,
		g =	+y2	- 0.337633*u2	- 0.698001*v2,
		b =	+y2	+ 1.732446*u2;
	
	// Even with proper conversion, some values still need clipping.
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	if (r < 0) r = 0;
	if (g < 0) g = 0;
	if (b < 0) b = 0;
	
	// Values only go from 0-220..  Why?
	pixel[0] = r * 220 / 256;
	pixel[1] = g * 220 / 256;
	pixel[2] = b * 220 / 256;*/

	/* Alternate formula. From http://msdn.microsoft.com/en-us/library/ms893078.aspx
	//clip denotes clipping the value to the range 0-255
	C = Y - 16
	D = U - 128
	E = V - 128
	R = clip(( 298 * C           + 409 * E + 128) >> 8)
	G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8)
	B = clip(( 298 * C + 516 * D           + 128) >> 8)
	*/
	Convert(srcY, destRGB);
	}

void RGBToYUV420(const QVImage<uChar, 3> &src, QVImage<uChar, 1> &dstY, QVImage<uChar, 1> &dstU, QVImage<uChar, 1> &dstV)
	{
	std::cout << "Warning: RGBToYUV420 function without IPP is to be implemented soon." << std::endl;
	/* From http://msdn.microsoft.com/en-us/library/ms893078.aspx
	Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16
	U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128
	V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128
	*/
	Convert(src, dstY);
	dstU = dstV = QVImage<uChar, 1>(src.getCols() / 2, src.getRows() / 2);
	Set(128, dstU);
	Set(128, dstV);
	}

#else
// Functions not provided by the IPP.
// sFloat
void Convert(const QVImage<sFloat, 1> &src, QVImage<sChar, 1> &dst)	{ ConvertType<sFloat, sChar, 1>(src, dst); }
void Convert(const QVImage<sFloat, 1> &src, QVImage<sInt, 1> &dst)	{ ConvertType<sFloat, sInt, 1>(src, dst); }
void Convert(const QVImage<sFloat, 1> &src, QVImage<uInt, 1> &dst)	{ ConvertType<sFloat, uInt, 1>(src, dst); }
void Convert(const QVImage<sFloat, 3> &src, QVImage<sChar, 3> &dst)	{ ConvertType<sFloat, sChar, 3>(src, dst); }
void Convert(const QVImage<sFloat, 3> &src, QVImage<sInt, 3> &dst)	{ ConvertType<sFloat, sInt, 3>(src, dst); }
void Convert(const QVImage<sFloat, 3> &src, QVImage<uInt, 3> &dst)	{ ConvertType<sFloat, uInt, 3>(src, dst); }

// uChar
void Convert(const QVImage<uChar, 1> &src, QVImage<sChar, 1> &dst)	{ ConvertType<uChar, sChar, 1>(src, dst); }
void Convert(const QVImage<uChar, 1> &src, QVImage<uInt, 1> &dst)	{ ConvertType<uChar, uInt, 1>(src, dst); }
void Convert(const QVImage<uChar, 3> &src, QVImage<sChar, 3> &dst)	{ ConvertType<uChar, sChar, 3>(src, dst); }
void Convert(const QVImage<uChar, 3> &src, QVImage<uInt, 3> &dst)	{ ConvertType<uChar, uInt, 3>(src, dst); }

// sChar
void Convert(const QVImage<sChar, 1> &src, QVImage<sFloat, 1> &dst)	{ ConvertType<sChar, sFloat, 1>(src, dst); }
void Convert(const QVImage<sChar, 1> &src, QVImage<uChar, 1> &dst)	{ ConvertType<sChar, uChar, 1>(src, dst); }
void Convert(const QVImage<sChar, 1> &src, QVImage<sInt, 1> &dst)	{ ConvertType<sChar, sInt, 1>(src, dst); }
void Convert(const QVImage<sChar, 1> &src, QVImage<uInt, 1> &dst)	{ ConvertType<sChar, uInt, 1>(src, dst); }
void Convert(const QVImage<sChar, 1> &src, QVImage<sShort, 1> &dst)	{ ConvertType<sChar, sShort, 1>(src, dst); }
void Convert(const QVImage<sChar, 1> &src, QVImage<uShort, 1> &dst)	{ ConvertType<sChar, uShort, 1>(src, dst); }
void Convert(const QVImage<sChar, 3> &src, QVImage<sFloat, 3> &dst)	{ ConvertType<sChar, sFloat, 3>(src, dst); }
void Convert(const QVImage<sChar, 3> &src, QVImage<uChar, 3> &dst)	{ ConvertType<sChar, uChar, 3>(src, dst); }
void Convert(const QVImage<sChar, 3> &src, QVImage<sInt, 3> &dst)	{ ConvertType<sChar, sInt, 3>(src, dst); }
void Convert(const QVImage<sChar, 3> &src, QVImage<uInt, 3> &dst)	{ ConvertType<sChar, uInt, 3>(src, dst); }
void Convert(const QVImage<sChar, 3> &src, QVImage<sShort, 3> &dst)	{ ConvertType<sChar, sShort, 3>(src, dst); }
void Convert(const QVImage<sChar, 3> &src, QVImage<uShort, 3> &dst)	{ ConvertType<sChar, uShort, 3>(src, dst); }

// sInt
void Convert(const QVImage<sInt, 1> &src, QVImage<sFloat, 1> &dst)	{ ConvertType<sInt, sFloat, 1>(src, dst); }
void Convert(const QVImage<sInt, 1> &src, QVImage<sChar, 1> &dst)	{ ConvertType<sInt, sChar, 1>(src, dst); }
void Convert(const QVImage<sInt, 1> &src, QVImage<uInt, 1> &dst)	{ ConvertType<sInt, uInt, 1>(src, dst); }
void Convert(const QVImage<sInt, 1> &src, QVImage<sShort, 1> &dst)	{ ConvertType<sInt, sShort, 1>(src, dst); }
void Convert(const QVImage<sInt, 1> &src, QVImage<uShort, 1> &dst)	{ ConvertType<sInt, uShort, 1>(src, dst); }
void Convert(const QVImage<sInt, 3> &src, QVImage<sFloat, 3> &dst)	{ ConvertType<sInt, sFloat, 3>(src, dst); }
void Convert(const QVImage<sInt, 3> &src, QVImage<sChar, 3> &dst)	{ ConvertType<sInt, sChar, 3>(src, dst); }
void Convert(const QVImage<sInt, 3> &src, QVImage<uInt, 3> &dst)	{ ConvertType<sInt, uInt, 3>(src, dst); }
void Convert(const QVImage<sInt, 3> &src, QVImage<sShort, 3> &dst)	{ ConvertType<sInt, sShort, 3>(src, dst); }
void Convert(const QVImage<sInt, 3> &src, QVImage<uShort, 3> &dst)	{ ConvertType<sInt, uShort, 3>(src, dst); }

// uInt
void Convert(const QVImage<uInt, 1> &src, QVImage<sFloat, 1> &dst)	{ ConvertType<uInt, sFloat, 1>(src, dst); }
void Convert(const QVImage<uInt, 1> &src, QVImage<uChar, 1> &dst)	{ ConvertType<uInt, uChar, 1>(src, dst); }
void Convert(const QVImage<uInt, 1> &src, QVImage<sChar, 1> &dst)	{ ConvertType<uInt, sChar, 1>(src, dst); }
void Convert(const QVImage<uInt, 1> &src, QVImage<sInt, 1> &dst)	{ ConvertType<uInt, sInt, 1>(src, dst); }
void Convert(const QVImage<uInt, 1> &src, QVImage<sShort, 1> &dst)	{ ConvertType<uInt, sShort, 1>(src, dst); }
void Convert(const QVImage<uInt, 1> &src, QVImage<uShort, 1> &dst)	{ ConvertType<uInt, uShort, 1>(src, dst); }
void Convert(const QVImage<uInt, 3> &src, QVImage<sFloat, 3> &dst)	{ ConvertType<uInt, sFloat, 3>(src, dst); }
void Convert(const QVImage<uInt, 3> &src, QVImage<uChar, 3> &dst)	{ ConvertType<uInt, uChar, 3>(src, dst); }
void Convert(const QVImage<uInt, 3> &src, QVImage<sChar, 3> &dst)	{ ConvertType<uInt, sChar, 3>(src, dst); }
void Convert(const QVImage<uInt, 3> &src, QVImage<sInt, 3> &dst)	{ ConvertType<uInt, sInt, 3>(src, dst); }
void Convert(const QVImage<uInt, 3> &src, QVImage<sShort, 3> &dst)	{ ConvertType<uInt, sShort, 3>(src, dst); }
void Convert(const QVImage<uInt, 3> &src, QVImage<uShort, 3> &dst)	{ ConvertType<uInt, uShort, 3>(src, dst); }

// sShort
void Convert(const QVImage<sShort, 1> &src, QVImage<sChar, 1> &dst)	{ ConvertType<sShort, sChar, 1>(src, dst); }
void Convert(const QVImage<sShort, 1> &src, QVImage<uInt, 1> &dst)	{ ConvertType<sShort, uInt, 1>(src, dst); }
void Convert(const QVImage<sShort, 1> &src, QVImage<uShort, 1> &dst)	{ ConvertType<sShort, uShort, 1>(src, dst); }
void Convert(const QVImage<sShort, 3> &src, QVImage<sChar, 3> &dst)	{ ConvertType<sShort, sChar, 3>(src, dst); }
void Convert(const QVImage<sShort, 3> &src, QVImage<uInt, 3> &dst)	{ ConvertType<sShort, uInt, 3>(src, dst); }
void Convert(const QVImage<sShort, 3> &src, QVImage<uShort, 3> &dst)	{ ConvertType<sShort, uShort, 3>(src, dst); }

// uShort
void Convert(const QVImage<uShort, 1> &src, QVImage<sChar, 1> &dst)	{ ConvertType<uShort, sChar, 1>(src, dst); }
void Convert(const QVImage<uShort, 1> &src, QVImage<uInt, 1> &dst)	{ ConvertType<uShort, uInt, 1>(src, dst); }
void Convert(const QVImage<uShort, 1> &src, QVImage<sShort, 1> &dst)	{ ConvertType<uShort, sShort, 1>(src, dst); }
void Convert(const QVImage<uShort, 3> &src, QVImage<sChar, 3> &dst)	{ ConvertType<uShort, sChar, 3>(src, dst); }
void Convert(const QVImage<uShort, 3> &src, QVImage<uInt, 3> &dst)	{ ConvertType<uShort, uInt, 3>(src, dst); }
void Convert(const QVImage<uShort, 3> &src, QVImage<sShort, 3> &dst)	{ ConvertType<uShort, sShort, 3>(src, dst); }

void RGBToGray(const QVImage<sChar, 3> &src, QVImage<sChar, 1> &dst)	{ ConvertC3C1<sChar>(src, dst); }
void RGBToGray(const QVImage<uInt, 3> &src, QVImage<uInt, 1> &dst)		{ ConvertC3C1<uInt>(src, dst); }
void RGBToGray(const QVImage<sInt, 3> &src, QVImage<sInt, 1> &dst)		{ ConvertC3C1<sInt>(src, dst); }

void Copy(const QVImage<sChar, 1> &src1, const QVImage<sChar, 1> &src2, const QVImage<sChar, 1> &src3, QVImage<sChar, 3> &dst)		{ CopyC1x3C3<sChar>(src1, src2, src3, dst); }
void Copy(const QVImage<uInt, 1> &src1, const QVImage<uInt, 1> &src2, const QVImage<uInt, 1> &src3, QVImage<uInt, 3> &dst)			{ CopyC1x3C3<uInt>(src1, src2, src3, dst); }

#endif // QVIPP
