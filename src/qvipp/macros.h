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

#include <iostream>
#include <qvipp.h>
#include <QVMatrix>

// Macro to call IPP functions
#define	IPP_DEBUG(function, ipp_function, ...)				\
	{								\
	IppStatus status = ipp_function(__VA_ARGS__);			\
	Q_ASSERT_X(	status == ippStsNoErr, #ipp_function,		\
			ippGetStatusString(status));			\
	Q_UNUSED(status);						\
	}								\

// To actualize ROI for output images
/// @todo quitar esa comprobación. La función IPP debería devolver error, caso de que no funcione correctamente.
#define	COMPOSE_ROI(DestImage, SrcImage, DestROIOffset, incW, incH)		\
	{									\
	const int	roiX = DestROIOffset.x(),				\
			roiY = DestROIOffset.y(),				\
			roiWidth = SrcImage.getROI().width() - (incW),		\
			roiHeight = SrcImage.getROI().height() - (incH);		\
	if( roiX + roiWidth < 0 ||  roiY + roiHeight < 0) return;		\
	DestImage.resize(roiX + roiWidth, roiY + roiHeight);			\
	DestImage.setROI(roiX, roiY, roiWidth, roiHeight);			\
	}

// Checks
#define	CHECK_SAME_STEP(Image1, Image2)			Q_ASSERT(Image1.getStep() == Image2.getStep())
#define	CHECK_SAME_ROISIZE(Image1, Image2)		Q_ASSERT(Image1.getROI().size() == Image2.getROI().size())
#define	CHECK_COMPATIBLE_IMAGES(NAME, Image1, Image2)	Q_ASSERT(Image1.getROI().size() == Image2.getROI().size())

// Reads a pointer to the image, counting the ROI
#define PDATA_READ(Image)	(&Image.getReadData()[Image.getROI().y()*Image.getStep()/Image.getTypeSize() + Image.getChannels()*Image.getROI().x()])
#define PDATA_WRITE(Image)	(&Image.getWriteData()[Image.getROI().y()*Image.getStep()/Image.getTypeSize() + Image.getChannels()*Image.getROI().x()])

#define PDATA_READ_MARGIN(Image, marginCols, marginRows)				\
	(&Image.getReadData()[								\
		(Image.getROI().y()+marginRows)*Image.getStep()/Image.getTypeSize()	\
		+ Image.getChannels()*(Image.getROI().x()+marginCols)]			\
		)

// Get the size of the image
#define	IMAGE_ROISIZE(Image)	((IppiSize){ Image.getROI().width(), Image.getROI().height() })
#define	IMAGE_ROIRECT(Image)	((IppiRect){ Image.getROI().x(), Image.getROI().y(), Image.getROI().width(), Image.getROI().height() })
#define	IMAGE_SIZE(Image)	((IppiSize){ Image.getCols(), Image.getRows() })
#define	IPP_SIZE(X,Y)		( (IppiSize) { (X), (Y) })
#define	IPP_POINT(X,Y)		( (IppiPoint) { (X), (Y) })
#define IPP_SIZE_FROM_QSIZE(MaskSize)	IPP_SIZE(MaskSize.width(), MaskSize.height())
#define	IPP_POINT_FROM_QPOINT(Point)	IPP_POINT(Point.x(), Point.y())

#define	IPP_MASK_SIZE_ROWS(Size)(	(Size == ippMskSize3x1	|| Size == ippMskSize5x1)? 1:	\
					(Size == ippMskSize1x3	|| Size == ippMskSize3x3)? 3: 5	)

#define	IPP_MASK_SIZE_COLS(Size)(	(Size == ippMskSize1x3	|| Size == ippMskSize1x5)? 1:	\
					(Size == ippMskSize3x1	|| Size == ippMskSize3x3)? 3: 5	)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// START OF MACROS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Funciones con una imagen de entrada y otra de salida, del mismo tipo.
// Filtros que aplican una máscara de tamaño 3x3. El ROI de destino es más pequeño que el ROI origen.
// Ejemplos: ippiFilterSharpen
#define DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(NAME, TYPE, C, SUBFIX)		\
void NAME(const QVImage<TYPE, C> &src, QVImage<TYPE, C> &dest, const QPoint &destROIOffset)			\
	{													\
	const int maskCols = 3, maskRows = 3;									\
														\
	COMPOSE_ROI(dest, src, destROIOffset, maskCols-1, maskRows-1);						\
														\
	IPP_DEBUG(NAME,		ippi ## NAME ## SUBFIX,								\
				PDATA_READ_MARGIN(src, (maskCols - 1)/2, (maskRows -1)/2), src.getStep(),	\
				PDATA_WRITE(dest), dest.getStep(),						\
				IMAGE_ROISIZE(dest)								\
				);										\
	}

// Tres imagenes de un canal de entrada, y una de varios canales de salida, todas del mismo tipo.
// Para operaciones de composición de varias imágenes de un solo canal en una de tres canales.
// Ejemplos: ippiCopy
//
// Comprobar: que las tres imagenes de entrada tienen el mismo step (sólo se le puede pasar uno
// a la función de las IPP) y el mismo tamaño para el ROI.
#define DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_C1_SRCIMAGE_Ti_C1_SRCIMAGE_Ti_C1_DESTIMAGE_Ti_Cj_ROIOFFSET(NAME, TYPE, C, SUBFIX)				\
void NAME(const QVImage<TYPE, 1> &src1, const QVImage<TYPE, 1> &src2, const QVImage<TYPE, 1> &src3, QVImage<TYPE, C> &dest, const QPoint &destROIOffset)	\
	{																		\
	CHECK_SAME_STEP(src1, src2);										\
	CHECK_SAME_STEP(src2, src3);										\
	CHECK_SAME_ROISIZE(src1, src2);										\
	CHECK_SAME_ROISIZE(src2, src3);										\
														\
	COMPOSE_ROI(dest, src1, destROIOffset, 0, 0);								\
	const TYPE	* pSrc[3] = { PDATA_READ(src1), PDATA_READ(src2), PDATA_READ(src3) };			\
														\
	IPP_DEBUG(NAME,		ippi ## NAME ## SUBFIX,								\
				pSrc, src1.getStep(),								\
				PDATA_WRITE(dest), dest.getStep(),						\
				IMAGE_ROISIZE(dest));								\
	}

// Una imagen de tres canales de entrada, y tres imagenes de un canal de entrada, todas del mismo tipo.
// Para operaciones de separación de los planos de una imagen en tres imágenes de un solo canal.
// Ejemplos: ippiCopy_8u_P3C3R
#define DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_C1_DESTIMAGE_Ti_C1_DESTIMAGE_Ti_C1_ROIOFFSET(NAME, TYPE, C, SUBFIX)			\
void NAME(const QVImage<TYPE, C> &src, QVImage<TYPE, 1> &dest1, QVImage<TYPE, 1> &dest2, QVImage<TYPE, 1> &dest3, const QPoint &destROIOffset)	\
	{																	\
	CHECK_SAME_STEP(dest1, dest2);									\
	CHECK_SAME_STEP(dest2, dest3);									\
													\
	COMPOSE_ROI(dest1, src, destROIOffset, 0, 0);							\
	COMPOSE_ROI(dest2, src, destROIOffset, 0, 0);							\
	COMPOSE_ROI(dest3, src, destROIOffset, 0, 0);							\
													\
	TYPE	* pDest[3] =	{ PDATA_WRITE(dest1), PDATA_WRITE(dest2), PDATA_WRITE(dest3) };		\
													\
	IPP_DEBUG(NAME,		ippi ## NAME ## SUBFIX,							\
				PDATA_READ(src), src.getStep(),						\
				pDest, dest1.getStep(),							\
				IMAGE_ROISIZE(dest3));							\
	}

// Imagen de entrada y de salida de distinto numero de canales, y mismo tipo,
// con selector de canal para la de entrada. Para funciones que extraigan un canal de una imagen de 3 canales.
// Ejemplos: ippiCopy_8u_C3C1R
#define DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Ck_CHANNELNUM_ROIOFFSET(NAME, TYPE, C1, C2, SUBFIX)		\
void NAME(const QVImage<TYPE, C1> &src, const uChar channel, QVImage<TYPE, C2> &dest, const QPoint &destROIOffset)	\
	{														\
	COMPOSE_ROI(dest, src, destROIOffset, 0, 0);									\
															\
	IPP_DEBUG(NAME,		ippi ## NAME ## SUBFIX,									\
				PDATA_READ(src) + channel, src.getStep(),						\
				PDATA_WRITE(dest), dest.getStep(),							\
				IMAGE_ROISIZE(dest));									\
	}

// Dos imagenes de entrada, de mismo tipo y canales, y una de salida, de tipo char y un canal. Con método de comparación.
// Para funciones de comparación.
// Ejemplos: ippiCompare_8u_C3R
#define DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_SRCIMAGE_Ti_Cj_DESTIMAGE_C1_Tuchar_IPPCMPOP_ROIOFFSET(NAME, TYPE, C, SUBFIX)				\
void NAME(const QVImage<TYPE,C> &src1, const QVImage<TYPE,C> &src2, QVImage<uChar> &dest, const IppCmpOp ippCmpOp, const QPoint &destROIOffset)	\
	{																	\
	CHECK_SAME_ROISIZE(src1, src2);														\
																		\
	COMPOSE_ROI(dest, src1, destROIOffset, 0, 0);												\
																		\
	IPP_DEBUG(NAME,		ippi ## NAME ## SUBFIX,												\
				PDATA_READ(src1), src1.getStep(),										\
				PDATA_READ(src2), src2.getStep(),										\
				PDATA_WRITE(dest), dest.getStep(),										\
				IMAGE_ROISIZE(dest),												\
				ippCmpOp);													\
	}

// Imagen de entrada y de salida con mismo tipo y canales. IPP_SIZE para tamaño de filtro.
// Por ejemplo, todas las funciones de filtrado, que pueden usar tamaños variables de filtro.
// Ejemplos: ippiFilterMax_8u_C1R, ippiFilterMin_8u_C1R
#define DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_MASKDIMENSION_ROIOFFSET(NAME, TYPE, C, SUBFIX)					\
void NAME(const QVImage<TYPE,C> &src, QVImage<TYPE,C> &dest, const QSize &maskSize, const QPoint &maskAnchor, const QPoint &destROIOffset)	\
	{																	\
	const uInt colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();								\
																		\
	COMPOSE_ROI(dest, src, destROIOffset, colMaskRadius-1, rowMaskRadius-1);								\
																		\
	IPP_DEBUG(NAME,		ippi ## NAME ## SUBFIX,												\
				PDATA_READ(src), src.getStep(),											\
				PDATA_WRITE(dest), dest.getStep(),										\
				IMAGE_ROISIZE(dest),												\
				IPP_SIZE(colMaskRadius, rowMaskRadius),										\
				IPP_POINT(maskAnchor.x(), maskAnchor.y()));									\
	}

// Imagen de entrada y de salida con mismo tipo y canales. IPP_MASK_SIZE para tamaño de filtro.
// Por ejemplo, todas las funciones de filtrado, que pueden usar tamaños fijos de filtro (3x3 o 5x5).
// Ejemplos: ippiFilterGauss_8u_C1R
#define DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_IPPMASKSIZE_ROIOFFSET(NAME, TYPE, C, SUBFIX)				\
void NAME(const QVImage<TYPE, C> &src, QVImage<TYPE, C> &dest, const IppiMaskSize maskSize, const QPoint &destROIOffset)	\
	{															\
	const int maskCols = IPP_MASK_SIZE_COLS(maskSize), maskRows = IPP_MASK_SIZE_ROWS(maskSize);		\
														\
	COMPOSE_ROI(dest, src, destROIOffset, maskCols-1, maskRows-1);						\
														\
	IPP_DEBUG(NAME,		ippi ## NAME ## SUBFIX,								\
				PDATA_READ_MARGIN(src, (maskCols - 1)/2, (maskRows -1)/2), src.getStep(),	\
				PDATA_WRITE(dest), dest.getStep(),						\
				IMAGE_ROISIZE(dest), maskSize							\
				);										\
	}

// Imagen de entrada y de salida con mismo tipo y canales. IPP_MASK_SIZE para tamaño de filtro. Uso de buffer de datos.
// Por ejemplo, todas las funciones de filtrado, que pueden usar tamaños fijos de filtro (3x3 o 5x5), que usan buffer de datos.
// Ejemplos: ippiFilterSobelNegVertBorder_8u16s_C1R
#define DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_BUFFERIMAGE_Ti_Cj_IPPMASKSIZE__ROIOFFSET(NAME, TYPE1, TYPE2, C, SUBFIX)	\
void NAME(const QVImage<TYPE1,C> &src, QVImage<TYPE2,C> &dest, const IppiMaskSize maskSize,						\
	const IppiBorderType borderType, const TYPE1 borderValue, QVImage<uChar,C> &buffer, const QPoint &destROIOffset)		\
	{																\
	const int maskCols = IPP_MASK_SIZE_COLS(maskSize), maskRows = IPP_MASK_SIZE_ROWS(maskSize);					\
																	\
	COMPOSE_ROI(dest, src, destROIOffset, maskCols-1, maskRows-1);									\
																	\
	IPP_DEBUG(NAME,		ippi ## NAME ## SUBFIX,											\
				PDATA_READ_MARGIN(src, (maskCols - 1)/2, (maskRows -1)/2), src.getStep(),				\
				PDATA_WRITE(dest), dest.getStep(),									\
				IMAGE_ROISIZE(dest), maskSize,										\
				borderType, borderValue, buffer.getWriteData());							\
	}

// Imagen genérica de entrada, y de salida de tipo y canales dado. Tamaño de máscara (5 ó 3)
// Para funciones que obtienen el buffer de trabajo de funciones de filtro que usan búfferes.
// Ejemplo: ippiFilterSobelNegVertGetBufferSize_8u16s_C1R
#define DEFINE_IPP_FUNCTION_SRCGENERICIMAGE_DESTBUFFERIMAGE_Ti_Cj_IPPMASKSIZE__ROIOFFSET(NAME, TYPE1, TYPE2, C, SUBFIX)		\
void NAME(const QVGenericImage &src, const IppiMaskSize maskSize, QVImage<TYPE1, C> &buffer)					\
	{															\
	int bufferSize;														\
																\
	IPP_DEBUG(NAME,		ippi ## NAME ## SUBFIX, IMAGE_ROISIZE(src),							\
				maskSize, &bufferSize);										\
	buffer = QVImage<uChar>(bufferSize,1);											\
	}
