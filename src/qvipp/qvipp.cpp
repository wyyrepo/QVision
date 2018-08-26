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
#include <qvipp/macros.h>

// Sharpen
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(FilterSharpen, uChar, 1, _8u_C1R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(FilterSharpen, sFloat, 1, _32f_C1R);

// FilterSobel
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(FilterSobelVert, uChar, 1, _8u_C1R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(FilterSobelVert, sShort, 1, _16s_C1R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(FilterSobelVert, sFloat, 1, _32f_C1R);

DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(FilterSobelVert, uChar, 3, _8u_C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(FilterSobelVert, sShort, 3, _16s_C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(FilterSobelVert, sFloat, 3, _32f_C3R);

DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(FilterSobelHoriz, uChar, 1, _8u_C1R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(FilterSobelHoriz, sShort, 1, _16s_C1R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(FilterSobelHoriz, sFloat, 1, _32f_C1R);

DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(FilterSobelHoriz, uChar, 3, _8u_C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(FilterSobelHoriz, sShort, 3, _16s_C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(FilterSobelHoriz, sFloat, 3, _32f_C3R);

// Erode
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(Erode3x3, uChar, 1, _8u_C1R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(Erode3x3, uShort, 1, _16u_C1R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(Erode3x3, sFloat, 1, _32f_C1R);

DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(Erode3x3, uChar, 3, _8u_C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(Erode3x3, uShort, 3, _16u_C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(Erode3x3, sFloat, 3, _32f_C3R);

// Dilate
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(Dilate3x3, uChar, 1, _8u_C1R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(Dilate3x3, uShort, 1, _16u_C1R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(Dilate3x3, sFloat, 1, _32f_C1R);

DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(Dilate3x3, uChar, 3, _8u_C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(Dilate3x3, uShort, 3, _16u_C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_ROIOFFSET_BORDER3x3(Dilate3x3, sFloat, 3, _32f_C3R);

DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_C1_SRCIMAGE_Ti_C1_SRCIMAGE_Ti_C1_DESTIMAGE_Ti_Cj_ROIOFFSET(Copy, uChar, 3, _8u_P3C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_C1_SRCIMAGE_Ti_C1_SRCIMAGE_Ti_C1_DESTIMAGE_Ti_Cj_ROIOFFSET(Copy, uShort, 3, _16u_P3C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_C1_SRCIMAGE_Ti_C1_SRCIMAGE_Ti_C1_DESTIMAGE_Ti_Cj_ROIOFFSET(Copy, sShort, 3, _16s_P3C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_C1_SRCIMAGE_Ti_C1_SRCIMAGE_Ti_C1_DESTIMAGE_Ti_Cj_ROIOFFSET(Copy, sInt, 3, _32s_P3C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_C1_SRCIMAGE_Ti_C1_SRCIMAGE_Ti_C1_DESTIMAGE_Ti_Cj_ROIOFFSET(Copy, sFloat, 3, _32f_P3C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_C1_DESTIMAGE_Ti_C1_DESTIMAGE_Ti_C1_ROIOFFSET(Copy, uChar, 3, _8u_C3P3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_C1_DESTIMAGE_Ti_C1_DESTIMAGE_Ti_C1_ROIOFFSET(Copy, uShort, 3, _16u_C3P3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_C1_DESTIMAGE_Ti_C1_DESTIMAGE_Ti_C1_ROIOFFSET(Copy, sShort, 3, _16s_C3P3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_C1_DESTIMAGE_Ti_C1_DESTIMAGE_Ti_C1_ROIOFFSET(Copy, sInt, 3, _32s_C3P3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_C1_DESTIMAGE_Ti_C1_DESTIMAGE_Ti_C1_ROIOFFSET(Copy, sFloat, 3, _32f_C3P3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Ck_CHANNELNUM_ROIOFFSET(Copy, uChar, 3, 1, _8u_C3C1R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Ck_CHANNELNUM_ROIOFFSET(Copy, uShort, 3, 1, _16u_C3C1R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Ck_CHANNELNUM_ROIOFFSET(Copy, sShort, 3, 1, _16s_C3C1R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Ck_CHANNELNUM_ROIOFFSET(Copy, sInt, 3, 1, _32s_C3C1R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Ck_CHANNELNUM_ROIOFFSET(Copy, sFloat, 3, 1, _32f_C3C1R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_SRCIMAGE_Ti_Cj_DESTIMAGE_C1_Tuchar_IPPCMPOP_ROIOFFSET(Compare, uChar, 3, _8u_C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_SRCIMAGE_Ti_Cj_DESTIMAGE_C1_Tuchar_IPPCMPOP_ROIOFFSET(Compare, uShort, 3, _16u_C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_SRCIMAGE_Ti_Cj_DESTIMAGE_C1_Tuchar_IPPCMPOP_ROIOFFSET(Compare, sShort, 3, _16s_C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_SRCIMAGE_Ti_Cj_DESTIMAGE_C1_Tuchar_IPPCMPOP_ROIOFFSET(Compare, sFloat, 3, _32f_C3R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_BUFFERIMAGE_Ti_Cj_IPPMASKSIZE__ROIOFFSET(FilterSobelNegVertBorder, uChar, sShort, 1, _8u16s_C1R);
DEFINE_IPP_FUNCTION_SRCIMAGE_Ti_Cj_DESTIMAGE_Ti_Cj_BUFFERIMAGE_Ti_Cj_IPPMASKSIZE__ROIOFFSET(FilterSobelHorizBorder, uChar, sShort, 1, _8u16s_C1R);
DEFINE_IPP_FUNCTION_SRCGENERICIMAGE_DESTBUFFERIMAGE_Ti_Cj_IPPMASKSIZE__ROIOFFSET(FilterSobelNegVertGetBufferSize, uChar, sShort, 1, _8u16s_C1R);
DEFINE_IPP_FUNCTION_SRCGENERICIMAGE_DESTBUFFERIMAGE_Ti_Cj_IPPMASKSIZE__ROIOFFSET(FilterSobelHorizGetBufferSize, uChar, sShort, 1, _8u16s_C1R);



#define DEFINE_IPP_FUNCTION_QVIMAGE_QVIMAGE_DOUBLE_DOUBLE_INTERPOLATION(NAME, TYPE, PLANES, SUBFIX)	\
void NAME(const QVImage<TYPE, PLANES> &src, QVImage<TYPE, PLANES> &dest, int interpolation)		\
	{												\
	double	factorX = (double) dest.getROI().width() / (double) src.getROI().width(),		\
		factorY = (double) dest.getROI().height() / (double) src.getROI().height();		\
													\
	IPP_DEBUG(NAME,		ippi ## NAME ## SUBFIX,							\
				src.getReadData(), IMAGE_SIZE(src), src.getStep(), IMAGE_ROIRECT(src),	\
				PDATA_WRITE(dest), dest.getStep(), IMAGE_ROISIZE(dest),			\
				factorX, factorY, interpolation);					\
	}

DEFINE_IPP_FUNCTION_QVIMAGE_QVIMAGE_DOUBLE_DOUBLE_INTERPOLATION(Resize, uChar, 1, _8u_C1R);
DEFINE_IPP_FUNCTION_QVIMAGE_QVIMAGE_DOUBLE_DOUBLE_INTERPOLATION(Resize, uChar, 3, _8u_C3R);
DEFINE_IPP_FUNCTION_QVIMAGE_QVIMAGE_DOUBLE_DOUBLE_INTERPOLATION(Resize, uShort, 1, _16u_C1R);
DEFINE_IPP_FUNCTION_QVIMAGE_QVIMAGE_DOUBLE_DOUBLE_INTERPOLATION(Resize, sFloat, 1, _32f_C1R);

#define DEFINE_IPP_FUNCTION_QVIMAGE_QVIMAGE_BUFFER_KERNELSIZE_SFLOAT_BORDERTYPE_BORDERVALUE(NAME, TYPE, C, SUBFIX)	\
void NAME(const QVImage<TYPE, C> &src, QVImage<TYPE, C> &dest, QVImage<uChar> &buffer, sInt kernelSize,			\
	sFloat sfloat, IppiBorderType borderType, sFloat borderValue, const QPoint &destROIOffset)			\
	{														\
	dest.setROI(destROIOffset.x(), destROIOffset.y(),					\
		src.getROI().width(), src.getROI().height());		\
												\
	IPP_DEBUG(NAME,		ippi ## NAME ## SUBFIX,						\
				PDATA_READ(src), src.getStep(),					\
				PDATA_WRITE(dest), dest.getStep(),				\
				IMAGE_ROISIZE(dest),						\
				kernelSize, sfloat, borderType, borderValue,			\
				buffer.getWriteData());						\
	}

DEFINE_IPP_FUNCTION_QVIMAGE_QVIMAGE_BUFFER_KERNELSIZE_SFLOAT_BORDERTYPE_BORDERVALUE(FilterGaussBorder, sFloat, 1, _32f_C1R);

#define DEFINE_IPP_FUNCTION_QVIMAGE_BUFFER_THRESHOLD_PIPPIPOINT_UINT_PUINT_IPPINORM_BORDER(NAME, TYPE, C, SUBFIX)					\
void NAME(const QVImage<TYPE, C> &img, QVImage<uChar> &buffer, QList<QPoint> &points, TYPE threshold, IppiNorm norm, uInt border, uInt maxPeakCount)	\
	{																		\
	int pPeakCount;									\
	IppiPoint *pPeak = new IppiPoint[maxPeakCount]();				\
											\
	IPP_DEBUG(NAME,		ippi ## NAME ## SUBFIX,					\
				PDATA_READ(img), img.getStep(), IMAGE_ROISIZE(img),	\
				threshold, pPeak, maxPeakCount, &pPeakCount,		\
				norm, border, buffer.getWriteData());			\
											\
	for (int n = 0; n < pPeakCount; n++)						\
		points.append(QPoint(pPeak[n].x, pPeak[n].y));				\
											\
	delete pPeak;									\
	}

DEFINE_IPP_FUNCTION_QVIMAGE_BUFFER_THRESHOLD_PIPPIPOINT_UINT_PUINT_IPPINORM_BORDER(FindPeaks3x3, sInt, 1, _32s_C1R);
DEFINE_IPP_FUNCTION_QVIMAGE_BUFFER_THRESHOLD_PIPPIPOINT_UINT_PUINT_IPPINORM_BORDER(FindPeaks3x3, sFloat, 1, _32f_C1R);

#define DEFINE_IPP_FUNCTION_QVIMAGE_BUFFER_ROIWIDTH(NAME, TYPE, C, SUBFIX)	\
void NAME(const QVImage<TYPE,C> &image, QVImage<uChar> &buffer)			\
	{									\
	int pBufferSize;							\
 										\
	IPP_DEBUG(Peaks3x3GetBufferSize,	ippi ## NAME ## SUBFIX,			\
						image.getROI().width(), &pBufferSize);	\
	buffer = QVImage<uChar>(2*pBufferSize,1);					\
	}

DEFINE_IPP_FUNCTION_QVIMAGE_BUFFER_ROIWIDTH(FindPeaks3x3GetBufferSize, sInt, 1, _32s_C1R);
DEFINE_IPP_FUNCTION_QVIMAGE_BUFFER_ROIWIDTH(FindPeaks3x3GetBufferSize, sFloat, 1, _32f_C1R);

/// @todo Comprobar que los tamaños de las imagenes de entrada y de salida son adecuados
void YUV420ToRGB(const QVImage<uChar, 1> &src1, const QVImage<uChar, 1> &src2, const QVImage<uChar, 1> &src3,
	QVImage<uChar, 3> &dest, const QPoint &destROIOffset)
	{
	const uChar * pSrc[3] = { PDATA_READ(src1), PDATA_READ(src2), PDATA_READ(src3) };
	int srcStep[3] = { src1.getStep(), src2.getStep(), src3.getStep() };

	dest.setROI(destROIOffset.x(), destROIOffset.y(), src1.getROI().width(), src1.getROI().height());

	IPP_DEBUG("YUV420ToRGB",	ippiYUV420ToRGB_8u_P3C3R,
					pSrc, srcStep,
					PDATA_WRITE(dest), dest.getStep(),
					IMAGE_ROISIZE(dest));
	}

/// @todo Comprobar que los tamaños de las imagenes de entrada y de salida son adecuados
void RGBToYUV420(const QVImage<uChar, 3> &src, QVImage<uChar, 1> &dst1, QVImage<uChar, 1> &dst2, QVImage<uChar, 1> &dst3, const QPoint &destROIOffset)
	{
	uChar * pDst[3] = { PDATA_WRITE(dst1), PDATA_WRITE(dst2), PDATA_WRITE(dst3) };
	int dstStep[3] = { dst1.getStep(), dst2.getStep(), dst3.getStep() };

	dst1.setROI(destROIOffset.x(), destROIOffset.y(), src.getROI().width(), src.getROI().height());
	dst2.setROI(destROIOffset.x()/2, destROIOffset.y()/2, src.getROI().width()/2, src.getROI().height()/2);
	dst3.setROI(destROIOffset.x()/2, destROIOffset.y()/2, src.getROI().width()/2, src.getROI().height()/2);

	IPP_DEBUG("RGBToTUV420",	ippiRGBToYUV420_8u_C3P3R,
					PDATA_READ(src), src.getStep(),
					pDst, dstStep,
					IMAGE_ROISIZE(dst1));
	}

void FilterGaussGetBufferSize(const QVGenericImage &image, QVImage<uChar> &buffer, uInt kernelSize)
	{
	int pBufferSize;
	IPP_DEBUG(FilterGaussGetBufferSize,	ippiFilterGaussGetBufferSize_32f_C1R, IMAGE_ROISIZE(image), kernelSize, &pBufferSize);
	buffer = QVImage<uChar>(pBufferSize,1);
	}

void MinEigenValGetBufferSize(const QVGenericImage &image, QVImage<uChar> &buffer, uInt apertureSize, uInt avgWindow)
	{
	int pBufferSize;
	IPP_DEBUG(MinEigenVal,	ippiMinEigenValGetBufferSize_8u32f_C1R, IMAGE_ROISIZE(image), apertureSize, avgWindow, &pBufferSize);
	buffer = QVImage<uChar>(pBufferSize,1);
	}

void CannyGetSize(const QVGenericImage &src, QVImage<uChar> &buffer)
	{
	int cannyBufferSize;
	IPP_DEBUG(CannyGetSize, ippiCannyGetSize, IMAGE_ROISIZE(src),&cannyBufferSize);
	buffer = QVImage<uChar>(cannyBufferSize,1);
	}

void FastMarchingGetBufferSize(const QVGenericImage &image, QVImage<uChar> &buffer)
	{
	int bufferSize;
	IPP_DEBUG(CannyGetSize, ippiFastMarchingGetBufferSize_8u32f_C1R, IMAGE_ROISIZE(image),&bufferSize);
	buffer = QVImage<uChar>(bufferSize,1);
	}

// Inpainting C3
void InpaintInitAllocC3(IppiInpaintState_8u_C3R **pState, const QVImage<sFloat> &distances, const QVImage<uChar> &mask,
	const sFloat radius, const IppiInpaintFlag flag)
	{
	IPP_DEBUG(	Inpaint, ippiInpaintInitAlloc_8u_C3R, pState, distances.getReadData(), distances.getStep(),
			mask.getReadData(), mask.getStep(), IMAGE_ROISIZE(mask), radius, flag);
	}

void InpaintFreeC3(IppiInpaintState_8u_C3R *pState)
	{
	IPP_DEBUG(Inpaint, ippiInpaintFree_8u_C3R,pState);
	}

void InpaintInitAllocC1(IppiInpaintState_8u_C1R **pState, const QVImage<sFloat> &distances, const QVImage<uChar> &mask,
	const sFloat radius, const IppiInpaintFlag flag)
	{
	IPP_DEBUG(	Inpaint, ippiInpaintInitAlloc_8u_C1R, pState, distances.getReadData(), distances.getStep(),
			mask.getReadData(), mask.getStep(), IMAGE_ROISIZE(mask), radius, flag);
	}

void InpaintFreeC1(IppiInpaintState_8u_C1R *pState)
	{
	IPP_DEBUG(Inpaint, ippiInpaintFree_8u_C1R,pState);
	}

// Histogram
QVector<int> HistogramRange(const QVImage<uChar, 1> &src)
	{
	// Bug: always computes last value wrong. So we use one more value, 257, instead of 256.
	int nLevels = 257;
	sInt pLevels[nLevels];
	int pHist[nLevels];
	
	for(sInt i=0; i<nLevels; i++)
		pLevels[i] = i;

	IPP_DEBUG(HistogramRange,	ippiHistogramRange_8u_C1R, // ippi ## NAME ## SUBFIX,
					PDATA_READ(src), src.getStep(), IMAGE_ROISIZE(src),
					pHist, pLevels, nLevels);

	////////////////////
	// compute cumulative histogram
	QVector< int > result(256);
	for (int i=0; i<result.size(); i++)
		result[i] = pHist[i];

	return result;
	}

QMap<sInt, int> HistogramRange(const QVImage<uChar, 1> &src, QList<uChar> values)
	{
	// Bug: always coputes last value wrong. So we use one more value, 257, instead of 256.
	int nLevels = values.size();
	sInt pLevels[nLevels];
	int pHist[nLevels];
	
	Q_ASSERT_X(false, "QMap<sInt, int> HistogramRange(QVImage<uChar, 1> &src, QList<uChar> values)",
			"Tried an user defined values QList. Functionality not implemented yet.");

	IPP_DEBUG(HistogramRange,	ippiHistogramRange_8u_C1R, // ippi ## NAME ## SUBFIX,
					PDATA_READ(src), src.getStep(), IMAGE_ROISIZE(src),
					pHist, pLevels, nLevels);

	////////////////////
	// compute cumulative histogram
	QMap<sInt, int> histogram;
	for (int i=0; i<nLevels; i++)
		histogram.insert(pLevels[i], pHist[i]);

	return histogram;
	}

// Flood fill
void	FloodFillGetSize(const QVGenericImage &src, QVImage<uChar> &buffer)
	{
	int floodFillBufferSize;
	IPP_DEBUG(FloodFillGetSize, ippiFloodFillGetSize, IMAGE_ROISIZE(src),&floodFillBufferSize);
	buffer = QVImage<uChar>(floodFillBufferSize,1);
	}

#define CREATE_IPP_FUNCTION_FLOOD_FILL(NAME, CONNECTIVITY, SUBFIX, TYPE)		\
void NAME(QVImage<TYPE> &img, QVImage<uChar> &buffer,					\
	uInt seedX, uInt seedY, TYPE newVal, TYPE minDelta, TYPE maxDelta)		\
	{										\
	IppiConnectedComp pRegion;							\
	IPP_DEBUG(NAME,		ippiFloodFill ## CONNECTIVITY ## SUBFIX,		\
				PDATA_WRITE(img), img.getStep(), IMAGE_ROISIZE(img),	\
				IPP_POINT(seedX, seedY), newVal, minDelta, maxDelta,	\
				&pRegion, buffer.getWriteData());			\
	}

CREATE_IPP_FUNCTION_FLOOD_FILL(FloodFillRange4Connected, _Range4Con, _8u_C1IR, uChar);
CREATE_IPP_FUNCTION_FLOOD_FILL(FloodFillGradient4Connected, _Grad4Con, _8u_C1IR, uChar);

#define CREATE_IPP_FUNCTION_WARP_PERSPECTIVE(NAME, SUBFIX, C, TYPE)									\
void	NAME(const QVImage<TYPE, C> &src, QVImage<TYPE, C> &dest, const QVMatrix &rectifyingHomography, int interpolation, const QPoint &/*destROIOffset*/)	\
	{																		\
	double coeffs[3][3];																\
	for (int i = 0; i < 3; i++)															\
		for (int j = 0; j < 3; j++)														\
			coeffs[i][j] = rectifyingHomography(i,j);											\
																			\
	IPP_DEBUG(NAME,		ippi ## NAME ## SUBFIX,													\
				src.getReadData(), IMAGE_SIZE(src), src.getStep(), IMAGE_ROIRECT(src),							\
				PDATA_WRITE(dest), dest.getStep(), IMAGE_ROIRECT(dest),									\
				coeffs, interpolation);													\
	}

CREATE_IPP_FUNCTION_WARP_PERSPECTIVE(WarpPerspective, _8u_C1R, 1, uChar);
CREATE_IPP_FUNCTION_WARP_PERSPECTIVE(WarpPerspective, _8u_C3R, 3, uChar);

#include <qvmath/qvmatrix.h>
void	Filter(const QVImage<sFloat> &src, QVImage<sFloat> &dest, const QVMatrix kernel, const QPoint &destROIOffset)
	{
	Q_ASSERT(kernel.getCols() == kernel.getRows());

	const int kernelSize = kernel.getCols();
	sFloat kernelValues[kernelSize*kernelSize];
	for(int i = 0; i < kernelSize; i++)
		for(int j = 0; j < kernelSize; j++)
			kernelValues[i+ kernelSize*j] = kernel(i,j);

	dest.setROI(destROIOffset.x(), destROIOffset.y(),
		src.getROI().width()-kernelSize+1, src.getROI().height()-kernelSize+1);

	/// @note ojo, quizás haya que indicar en IPP_POINT(0,0), el último elemento de la matriz 'kernel', tal y como pasa en las funciones
	/// FilterColumn y FilterRow.
	IPP_DEBUG(NAME,		ippiFilter_32f_C1R,
				PDATA_READ(src), src.getStep(),
				PDATA_WRITE(dest), dest.getStep(),
				IMAGE_ROISIZE(dest),
				kernelValues, IPP_SIZE(kernelSize, kernelSize), IPP_POINT(0,0)
				);
	}

/// @note Ojo: muerte, peligro. Hay que indicar como anchor, el tamaño del kernel (menos 1). La iteración irá desde el valor 'kernelSize', hacia abajo.
void	FilterColumn(const QVImage<sFloat> &src, QVImage<sFloat> &dest, const QVVector kernel, const QPoint &destROIOffset)
	{
	const int kernelSize = kernel.size();
	sFloat kernelValues[kernelSize];
	for(int i = 0; i < kernelSize; i++)
			kernelValues[i] = kernel[i];

	dest.setROI(destROIOffset.x(), destROIOffset.y(),
		src.getROI().width(), src.getROI().height()-kernelSize+1);

	IPP_DEBUG(NAME,		ippiFilterColumn_32f_C1R,
				PDATA_READ(src), src.getStep(),
				PDATA_WRITE(dest), dest.getStep(),
				IMAGE_ROISIZE(dest),
				kernelValues, kernelSize, kernelSize-1
				);
	}

/// @note Ojo: muerte, peligro. Hay que indicar como anchor, el tamaño del kernel (menos 1). La iteración irá desde el valor 'kernelSize', hacia abajo.
void	FilterRow(const QVImage<sFloat> &src, QVImage<sFloat> &dest, const QVVector kernel, const QPoint &destROIOffset)
	{
	const int kernelSize = kernel.size();

	sFloat kernelValues[kernelSize];
	for(int i = 0; i < kernelSize; i++)
			kernelValues[i] = kernel[i];

	dest.setROI(destROIOffset.x(), destROIOffset.y(),
		src.getROI().width()-kernelSize+1, src.getROI().height());

	IPP_DEBUG(NAME,		ippiFilterRow_32f_C1R,
				PDATA_READ(src), src.getStep(),
				PDATA_WRITE(dest), dest.getStep(),
				IMAGE_ROISIZE(dest),
				kernelValues, kernelSize, kernelSize-1
				);
	}
