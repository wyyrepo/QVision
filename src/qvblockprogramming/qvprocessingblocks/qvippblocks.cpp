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

#include <qvippblocks.h>

const QMap<QString, QString> getQVIPPBlocksNames()
	{
	QMap<QString, QString> result;

	result.insertMulti("IPP: Image Data Exchange and Initialization Functions", "QVConvert_uCharsFloatC1Block");
	result.insertMulti("IPP: Image Data Exchange and Initialization Functions", "QVConvert_uCharsFloatC3Block");
	result.insertMulti("IPP: Image Data Exchange and Initialization Functions", "QVConvert_sFloatuCharC1Block");
	result.insertMulti("IPP: Image Data Exchange and Initialization Functions", "QVConvert_sFloatuCharC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAdd_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAdd_uCharC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAdd_sFloatC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAdd_sFloatC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAddC_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAddC_sFloatC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVMul_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVMul_uCharC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVMul_sFloatC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVMul_sFloatC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVMulC_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVMulC_sFloatC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVMulScale_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVMulScale_uCharC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVSub_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVSub_uCharC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVSub_sFloatC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVSub_sFloatC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVSubC_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVSubC_sFloatC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVDiv_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVDiv_uCharC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVDiv_sFloatC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVDiv_sFloatC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVDivC_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVDivC_sFloatC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAbs_sShortC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAbs_sFloatC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAbsDiff_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAbsDiff_sFloatC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVSqr_sFloatC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVLn_sFloatC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVLn_sFloatC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAnd_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAnd_uCharC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAnd_uShortC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAnd_uShortC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAnd_sIntC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAnd_sIntC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVOr_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVOr_uCharC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVOr_uShortC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVOr_uShortC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVOr_sIntC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVOr_sIntC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVXor_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVXor_uCharC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVXor_uShortC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVXor_uShortC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVXor_sIntC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVXor_sIntC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVNot_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVNot_uCharC3Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVAndC_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVOrC_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVXorC_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVLShiftC_uCharC1Block");
	result.insertMulti("IPP: Image Arithmetic and Logical Operations", "QVRShiftC_uCharC1Block");
	result.insertMulti("IPP: Image Color Conversion", "QVRGBToGray_uCharC3C1Block");
	result.insertMulti("IPP: Image Color Conversion", "QVRGBToGray_sFloatC3C1Block");
	result.insertMulti("IPP: Threshold and Compare Operations", "QVThreshold_uCharC1Block");
	result.insertMulti("IPP: Threshold and Compare Operations", "QVThreshold_sFloatC1Block");
	result.insertMulti("IPP: Threshold and Compare Operations", "QVComputeThreshold_Otsu_uCharC1Block");
	result.insertMulti("IPP: Threshold and Compare Operations", "QVCompare_uCharC1Block");
	result.insertMulti("IPP: Threshold and Compare Operations", "QVCompare_sFloatC1Block");
	result.insertMulti("IPP: Threshold and Compare Operations", "QVCompareC_uCharC1Block");
	result.insertMulti("IPP: Threshold and Compare Operations", "QVCompareC_sFloatC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterBox_uCharC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterBox_uCharC3Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterBox_sFloatC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterMin_uCharC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterMin_uCharC3Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterMin_sFloatC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterMax_uCharC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterMax_uCharC3Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterMax_sFloatC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterMedian_uCharC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterMedian_uCharC3Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterMedianHoriz_uCharC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterSobelHorizMask_sFloatC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterSobelVertMask_sFloatC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterLaplace_uCharC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterLaplace_sFloatC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterGauss_uCharC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterGauss_sFloatC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterGauss_uCharC3Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterGauss_sFloatC3Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterHipass_uCharC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterHipass_uCharC3Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterHipass_sFloatC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterHipass_sFloatC3Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterLowpass_uCharC1Block");
	result.insertMulti("IPP: Filtering Functions", "QVFilterLowpass_sFloatC1Block");
	result.insertMulti("IPP: Image Statistics Functions", "QVSum_uCharC1Block");
	result.insertMulti("IPP: Image Statistics Functions", "QVMean_uCharC1Block");
	result.insertMulti("IPP: Image Statistics Functions", "QVMin_uCharC1Block");
	result.insertMulti("IPP: Image Statistics Functions", "QVMin_sFloatC1Block");
	result.insertMulti("IPP: Image Statistics Functions", "QVMax_uCharC1Block");
	result.insertMulti("IPP: Image Statistics Functions", "QVMax_sFloatC1Block");

	return result;
	}

QVPropertyContainer *newQVIPPBlock(QString type, QString name)
	{
	if (type == "QVConvert_uCharsFloatC1Block")			return new QVConvert_uCharsFloatC1Block(name);
	else if (type == "QVConvert_uCharsFloatC3Block")			return new QVConvert_uCharsFloatC3Block(name);
	else if (type == "QVConvert_sFloatuCharC1Block")			return new QVConvert_sFloatuCharC1Block(name);
	else if (type == "QVConvert_sFloatuCharC3Block")			return new QVConvert_sFloatuCharC3Block(name);
	else if (type == "QVAdd_uCharC1Block")			return new QVAdd_uCharC1Block(name);
	else if (type == "QVAdd_uCharC3Block")			return new QVAdd_uCharC3Block(name);
	else if (type == "QVAdd_sFloatC1Block")			return new QVAdd_sFloatC1Block(name);
	else if (type == "QVAdd_sFloatC3Block")			return new QVAdd_sFloatC3Block(name);
	else if (type == "QVAddC_uCharC1Block")			return new QVAddC_uCharC1Block(name);
	else if (type == "QVAddC_sFloatC1Block")			return new QVAddC_sFloatC1Block(name);
	else if (type == "QVMul_uCharC1Block")			return new QVMul_uCharC1Block(name);
	else if (type == "QVMul_uCharC3Block")			return new QVMul_uCharC3Block(name);
	else if (type == "QVMul_sFloatC3Block")			return new QVMul_sFloatC3Block(name);
	else if (type == "QVMul_sFloatC1Block")			return new QVMul_sFloatC1Block(name);
	else if (type == "QVMulC_uCharC1Block")			return new QVMulC_uCharC1Block(name);
	else if (type == "QVMulC_sFloatC1Block")			return new QVMulC_sFloatC1Block(name);
	else if (type == "QVMulScale_uCharC1Block")			return new QVMulScale_uCharC1Block(name);
	else if (type == "QVMulScale_uCharC3Block")			return new QVMulScale_uCharC3Block(name);
	else if (type == "QVSub_uCharC1Block")			return new QVSub_uCharC1Block(name);
	else if (type == "QVSub_uCharC3Block")			return new QVSub_uCharC3Block(name);
	else if (type == "QVSub_sFloatC1Block")			return new QVSub_sFloatC1Block(name);
	else if (type == "QVSub_sFloatC3Block")			return new QVSub_sFloatC3Block(name);
	else if (type == "QVSubC_uCharC1Block")			return new QVSubC_uCharC1Block(name);
	else if (type == "QVSubC_sFloatC1Block")			return new QVSubC_sFloatC1Block(name);
	else if (type == "QVDiv_uCharC1Block")			return new QVDiv_uCharC1Block(name);
	else if (type == "QVDiv_uCharC3Block")			return new QVDiv_uCharC3Block(name);
	else if (type == "QVDiv_sFloatC3Block")			return new QVDiv_sFloatC3Block(name);
	else if (type == "QVDiv_sFloatC1Block")			return new QVDiv_sFloatC1Block(name);
	else if (type == "QVDivC_uCharC1Block")			return new QVDivC_uCharC1Block(name);
	else if (type == "QVDivC_sFloatC1Block")			return new QVDivC_sFloatC1Block(name);
	else if (type == "QVAbs_sShortC1Block")			return new QVAbs_sShortC1Block(name);
	else if (type == "QVAbs_sFloatC1Block")			return new QVAbs_sFloatC1Block(name);
	else if (type == "QVAbsDiff_uCharC1Block")			return new QVAbsDiff_uCharC1Block(name);
	else if (type == "QVAbsDiff_sFloatC1Block")			return new QVAbsDiff_sFloatC1Block(name);
	else if (type == "QVSqr_sFloatC1Block")			return new QVSqr_sFloatC1Block(name);
	else if (type == "QVLn_sFloatC1Block")			return new QVLn_sFloatC1Block(name);
	else if (type == "QVLn_sFloatC3Block")			return new QVLn_sFloatC3Block(name);
	else if (type == "QVAnd_uCharC1Block")			return new QVAnd_uCharC1Block(name);
	else if (type == "QVAnd_uCharC3Block")			return new QVAnd_uCharC3Block(name);
	else if (type == "QVAnd_uShortC1Block")			return new QVAnd_uShortC1Block(name);
	else if (type == "QVAnd_uShortC3Block")			return new QVAnd_uShortC3Block(name);
	else if (type == "QVAnd_sIntC1Block")			return new QVAnd_sIntC1Block(name);
	else if (type == "QVAnd_sIntC3Block")			return new QVAnd_sIntC3Block(name);
	else if (type == "QVOr_uCharC1Block")			return new QVOr_uCharC1Block(name);
	else if (type == "QVOr_uCharC3Block")			return new QVOr_uCharC3Block(name);
	else if (type == "QVOr_uShortC1Block")			return new QVOr_uShortC1Block(name);
	else if (type == "QVOr_uShortC3Block")			return new QVOr_uShortC3Block(name);
	else if (type == "QVOr_sIntC1Block")			return new QVOr_sIntC1Block(name);
	else if (type == "QVOr_sIntC3Block")			return new QVOr_sIntC3Block(name);
	else if (type == "QVXor_uCharC1Block")			return new QVXor_uCharC1Block(name);
	else if (type == "QVXor_uCharC3Block")			return new QVXor_uCharC3Block(name);
	else if (type == "QVXor_uShortC1Block")			return new QVXor_uShortC1Block(name);
	else if (type == "QVXor_uShortC3Block")			return new QVXor_uShortC3Block(name);
	else if (type == "QVXor_sIntC1Block")			return new QVXor_sIntC1Block(name);
	else if (type == "QVXor_sIntC3Block")			return new QVXor_sIntC3Block(name);
	else if (type == "QVNot_uCharC1Block")			return new QVNot_uCharC1Block(name);
	else if (type == "QVNot_uCharC3Block")			return new QVNot_uCharC3Block(name);
	else if (type == "QVAndC_uCharC1Block")			return new QVAndC_uCharC1Block(name);
	else if (type == "QVOrC_uCharC1Block")			return new QVOrC_uCharC1Block(name);
	else if (type == "QVXorC_uCharC1Block")			return new QVXorC_uCharC1Block(name);
	else if (type == "QVLShiftC_uCharC1Block")			return new QVLShiftC_uCharC1Block(name);
	else if (type == "QVRShiftC_uCharC1Block")			return new QVRShiftC_uCharC1Block(name);
	else if (type == "QVRGBToGray_uCharC3C1Block")			return new QVRGBToGray_uCharC3C1Block(name);
	else if (type == "QVRGBToGray_sFloatC3C1Block")			return new QVRGBToGray_sFloatC3C1Block(name);
	else if (type == "QVThreshold_uCharC1Block")			return new QVThreshold_uCharC1Block(name);
	else if (type == "QVThreshold_sFloatC1Block")			return new QVThreshold_sFloatC1Block(name);
	else if (type == "QVComputeThreshold_Otsu_uCharC1Block")			return new QVComputeThreshold_Otsu_uCharC1Block(name);
	else if (type == "QVCompare_uCharC1Block")			return new QVCompare_uCharC1Block(name);
	else if (type == "QVCompare_sFloatC1Block")			return new QVCompare_sFloatC1Block(name);
	else if (type == "QVCompareC_uCharC1Block")			return new QVCompareC_uCharC1Block(name);
	else if (type == "QVCompareC_sFloatC1Block")			return new QVCompareC_sFloatC1Block(name);
	else if (type == "QVFilterBox_uCharC1Block")			return new QVFilterBox_uCharC1Block(name);
	else if (type == "QVFilterBox_uCharC3Block")			return new QVFilterBox_uCharC3Block(name);
	else if (type == "QVFilterBox_sFloatC1Block")			return new QVFilterBox_sFloatC1Block(name);
	else if (type == "QVFilterMin_uCharC1Block")			return new QVFilterMin_uCharC1Block(name);
	else if (type == "QVFilterMin_uCharC3Block")			return new QVFilterMin_uCharC3Block(name);
	else if (type == "QVFilterMin_sFloatC1Block")			return new QVFilterMin_sFloatC1Block(name);
	else if (type == "QVFilterMax_uCharC1Block")			return new QVFilterMax_uCharC1Block(name);
	else if (type == "QVFilterMax_uCharC3Block")			return new QVFilterMax_uCharC3Block(name);
	else if (type == "QVFilterMax_sFloatC1Block")			return new QVFilterMax_sFloatC1Block(name);
	else if (type == "QVFilterMedian_uCharC1Block")			return new QVFilterMedian_uCharC1Block(name);
	else if (type == "QVFilterMedian_uCharC3Block")			return new QVFilterMedian_uCharC3Block(name);
	else if (type == "QVFilterMedianHoriz_uCharC1Block")			return new QVFilterMedianHoriz_uCharC1Block(name);
	else if (type == "QVFilterSobelHorizMask_sFloatC1Block")			return new QVFilterSobelHorizMask_sFloatC1Block(name);
	else if (type == "QVFilterSobelVertMask_sFloatC1Block")			return new QVFilterSobelVertMask_sFloatC1Block(name);
	else if (type == "QVFilterLaplace_uCharC1Block")			return new QVFilterLaplace_uCharC1Block(name);
	else if (type == "QVFilterLaplace_sFloatC1Block")			return new QVFilterLaplace_sFloatC1Block(name);
	else if (type == "QVFilterGauss_uCharC1Block")			return new QVFilterGauss_uCharC1Block(name);
	else if (type == "QVFilterGauss_sFloatC1Block")			return new QVFilterGauss_sFloatC1Block(name);
	else if (type == "QVFilterGauss_uCharC3Block")			return new QVFilterGauss_uCharC3Block(name);
	else if (type == "QVFilterGauss_sFloatC3Block")			return new QVFilterGauss_sFloatC3Block(name);
	else if (type == "QVFilterHipass_uCharC1Block")			return new QVFilterHipass_uCharC1Block(name);
	else if (type == "QVFilterHipass_uCharC3Block")			return new QVFilterHipass_uCharC3Block(name);
	else if (type == "QVFilterHipass_sFloatC1Block")			return new QVFilterHipass_sFloatC1Block(name);
	else if (type == "QVFilterHipass_sFloatC3Block")			return new QVFilterHipass_sFloatC3Block(name);
	else if (type == "QVFilterLowpass_uCharC1Block")			return new QVFilterLowpass_uCharC1Block(name);
	else if (type == "QVFilterLowpass_sFloatC1Block")			return new QVFilterLowpass_sFloatC1Block(name);
	else if (type == "QVSum_uCharC1Block")			return new QVSum_uCharC1Block(name);
	else if (type == "QVMean_uCharC1Block")			return new QVMean_uCharC1Block(name);
	else if (type == "QVMin_uCharC1Block")			return new QVMin_uCharC1Block(name);
	else if (type == "QVMin_sFloatC1Block")			return new QVMin_sFloatC1Block(name);
	else if (type == "QVMax_uCharC1Block")			return new QVMax_uCharC1Block(name);
	else if (type == "QVMax_sFloatC1Block")			return new QVMax_sFloatC1Block(name);
	else return NULL;
	}

// Block QVConvert_uCharsFloatC1Block for IPP function ippiConvert_8u32f_C1R
QVConvert_uCharsFloatC1Block::QVConvert_uCharsFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVConvert_uCharsFloatC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	Convert(qvimage_pSrc, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVConvert_uCharsFloatC3Block for IPP function ippiConvert_8u32f_C3R
QVConvert_uCharsFloatC3Block::QVConvert_uCharsFloatC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVConvert_uCharsFloatC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 3> qvimage_pDst;
	timeFlag("Create output data");

	Convert(qvimage_pSrc, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVConvert_sFloatuCharC1Block for IPP function ippiConvert_32f8u_C1R
QVConvert_sFloatuCharC1Block::QVConvert_sFloatuCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppRoundMode >("roundMode", inputFlag, ippRndNear);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVConvert_sFloatuCharC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const IppRoundMode roundMode = getPropertyValue< IppRoundMode > ("roundMode");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	Convert(qvimage_pSrc, qvimage_pDst, roundMode, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVConvert_sFloatuCharC3Block for IPP function ippiConvert_32f8u_C3R
QVConvert_sFloatuCharC3Block::QVConvert_sFloatuCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 3> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< IppRoundMode >("roundMode", inputFlag, ippRndNear);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVConvert_sFloatuCharC3Block::iterate()
	{
	const QVImage<sFloat, 3> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 3> > ("qvimage_pSrc");
	const IppRoundMode roundMode = getPropertyValue< IppRoundMode > ("roundMode");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	Convert(qvimage_pSrc, qvimage_pDst, roundMode, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAdd_uCharC1Block for IPP function ippiAdd_8u_C1RSfs
QVAdd_uCharC1Block::QVAdd_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< int >("scaleFactor", inputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAdd_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc1");
	const QVImage<uChar, 1> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc2");
	const int scaleFactor = getPropertyValue< int > ("scaleFactor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	Add(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, scaleFactor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAdd_uCharC3Block for IPP function ippiAdd_8u_C3RSfs
QVAdd_uCharC3Block::QVAdd_uCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< int >("scaleFactor", inputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAdd_uCharC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc1");
	const QVImage<uChar, 3> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc2");
	const int scaleFactor = getPropertyValue< int > ("scaleFactor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	Add(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, scaleFactor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAdd_sFloatC1Block for IPP function ippiAdd_32f_C1R
QVAdd_sFloatC1Block::QVAdd_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAdd_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc1 = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc1");
	const QVImage<sFloat, 1> qvimage_pSrc2 = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	Add(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAdd_sFloatC3Block for IPP function ippiAdd_32f_C3R
QVAdd_sFloatC3Block::QVAdd_sFloatC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sFloat, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<sFloat, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAdd_sFloatC3Block::iterate()
	{
	const QVImage<sFloat, 3> qvimage_pSrc1 = getPropertyValue< QVImage<sFloat, 3> > ("qvimage_pSrc1");
	const QVImage<sFloat, 3> qvimage_pSrc2 = getPropertyValue< QVImage<sFloat, 3> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 3> qvimage_pDst;
	timeFlag("Create output data");

	Add(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAddC_uCharC1Block for IPP function ippiAddC_8u_C1RSfs
QVAddC_uCharC1Block::QVAddC_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< uChar >("value", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< int >("scaleFactor", inputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAddC_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const uChar value = getPropertyValue< uChar > ("value");
	const int scaleFactor = getPropertyValue< int > ("scaleFactor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	AddC(qvimage_pSrc, value, qvimage_pDst, scaleFactor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAddC_sFloatC1Block for IPP function ippiAddC_32f_C1R
QVAddC_sFloatC1Block::QVAddC_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< sFloat >("value", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAddC_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const sFloat value = getPropertyValue< sFloat > ("value");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	AddC(qvimage_pSrc, value, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVMul_uCharC1Block for IPP function ippiMul_8u_C1RSfs
QVMul_uCharC1Block::QVMul_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< int >("scaleFactor", inputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVMul_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc1");
	const QVImage<uChar, 1> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc2");
	const int scaleFactor = getPropertyValue< int > ("scaleFactor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	Mul(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, scaleFactor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVMul_uCharC3Block for IPP function ippiMul_8u_C3RSfs
QVMul_uCharC3Block::QVMul_uCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< int >("scaleFactor", inputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVMul_uCharC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc1");
	const QVImage<uChar, 3> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc2");
	const int scaleFactor = getPropertyValue< int > ("scaleFactor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	Mul(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, scaleFactor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVMul_sFloatC3Block for IPP function ippiMul_32f_C3R
QVMul_sFloatC3Block::QVMul_sFloatC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sFloat, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<sFloat, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVMul_sFloatC3Block::iterate()
	{
	const QVImage<sFloat, 3> qvimage_pSrc1 = getPropertyValue< QVImage<sFloat, 3> > ("qvimage_pSrc1");
	const QVImage<sFloat, 3> qvimage_pSrc2 = getPropertyValue< QVImage<sFloat, 3> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 3> qvimage_pDst;
	timeFlag("Create output data");

	Mul(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVMul_sFloatC1Block for IPP function ippiMul_32f_C1R
QVMul_sFloatC1Block::QVMul_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVMul_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc1 = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc1");
	const QVImage<sFloat, 1> qvimage_pSrc2 = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	Mul(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVMulC_uCharC1Block for IPP function ippiMulC_8u_C1RSfs
QVMulC_uCharC1Block::QVMulC_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< uChar >("value", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< int >("scaleFactor", inputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVMulC_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const uChar value = getPropertyValue< uChar > ("value");
	const int scaleFactor = getPropertyValue< int > ("scaleFactor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	MulC(qvimage_pSrc, value, qvimage_pDst, scaleFactor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVMulC_sFloatC1Block for IPP function ippiMulC_32f_C1R
QVMulC_sFloatC1Block::QVMulC_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< sFloat >("value", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVMulC_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const sFloat value = getPropertyValue< sFloat > ("value");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	MulC(qvimage_pSrc, value, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVMulScale_uCharC1Block for IPP function ippiMulScale_8u_C1R
QVMulScale_uCharC1Block::QVMulScale_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVMulScale_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc1");
	const QVImage<uChar, 1> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	MulScale(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVMulScale_uCharC3Block for IPP function ippiMulScale_8u_C3R
QVMulScale_uCharC3Block::QVMulScale_uCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVMulScale_uCharC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc1");
	const QVImage<uChar, 3> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	MulScale(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVSub_uCharC1Block for IPP function ippiSub_8u_C1RSfs
QVSub_uCharC1Block::QVSub_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< int >("scaleFactor", inputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVSub_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc1");
	const QVImage<uChar, 1> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc2");
	const int scaleFactor = getPropertyValue< int > ("scaleFactor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	Sub(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, scaleFactor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVSub_uCharC3Block for IPP function ippiSub_8u_C3RSfs
QVSub_uCharC3Block::QVSub_uCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< int >("scaleFactor", inputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVSub_uCharC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc1");
	const QVImage<uChar, 3> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc2");
	const int scaleFactor = getPropertyValue< int > ("scaleFactor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	Sub(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, scaleFactor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVSub_sFloatC1Block for IPP function ippiSub_32f_C1R
QVSub_sFloatC1Block::QVSub_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVSub_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc1 = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc1");
	const QVImage<sFloat, 1> qvimage_pSrc2 = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	Sub(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVSub_sFloatC3Block for IPP function ippiSub_32f_C3R
QVSub_sFloatC3Block::QVSub_sFloatC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sFloat, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<sFloat, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVSub_sFloatC3Block::iterate()
	{
	const QVImage<sFloat, 3> qvimage_pSrc1 = getPropertyValue< QVImage<sFloat, 3> > ("qvimage_pSrc1");
	const QVImage<sFloat, 3> qvimage_pSrc2 = getPropertyValue< QVImage<sFloat, 3> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 3> qvimage_pDst;
	timeFlag("Create output data");

	Sub(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVSubC_uCharC1Block for IPP function ippiSubC_8u_C1RSfs
QVSubC_uCharC1Block::QVSubC_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< uChar >("value", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< int >("scaleFactor", inputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVSubC_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const uChar value = getPropertyValue< uChar > ("value");
	const int scaleFactor = getPropertyValue< int > ("scaleFactor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	SubC(qvimage_pSrc, value, qvimage_pDst, scaleFactor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVSubC_sFloatC1Block for IPP function ippiSubC_32f_C1R
QVSubC_sFloatC1Block::QVSubC_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< sFloat >("value", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVSubC_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const sFloat value = getPropertyValue< sFloat > ("value");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	SubC(qvimage_pSrc, value, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVDiv_uCharC1Block for IPP function ippiDiv_8u_C1RSfs
QVDiv_uCharC1Block::QVDiv_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< int >("scaleFactor", inputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVDiv_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc1");
	const QVImage<uChar, 1> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc2");
	const int scaleFactor = getPropertyValue< int > ("scaleFactor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	Div(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, scaleFactor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVDiv_uCharC3Block for IPP function ippiDiv_8u_C3RSfs
QVDiv_uCharC3Block::QVDiv_uCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< int >("scaleFactor", inputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVDiv_uCharC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc1");
	const QVImage<uChar, 3> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc2");
	const int scaleFactor = getPropertyValue< int > ("scaleFactor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	Div(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, scaleFactor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVDiv_sFloatC3Block for IPP function ippiDiv_32f_C3R
QVDiv_sFloatC3Block::QVDiv_sFloatC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sFloat, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<sFloat, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVDiv_sFloatC3Block::iterate()
	{
	const QVImage<sFloat, 3> qvimage_pSrc1 = getPropertyValue< QVImage<sFloat, 3> > ("qvimage_pSrc1");
	const QVImage<sFloat, 3> qvimage_pSrc2 = getPropertyValue< QVImage<sFloat, 3> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 3> qvimage_pDst;
	timeFlag("Create output data");

	Div(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVDiv_sFloatC1Block for IPP function ippiDiv_32f_C1R
QVDiv_sFloatC1Block::QVDiv_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVDiv_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc1 = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc1");
	const QVImage<sFloat, 1> qvimage_pSrc2 = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	Div(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVDivC_uCharC1Block for IPP function ippiDivC_8u_C1RSfs
QVDivC_uCharC1Block::QVDivC_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< uChar >("value", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< int >("scaleFactor", inputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVDivC_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const uChar value = getPropertyValue< uChar > ("value");
	const int scaleFactor = getPropertyValue< int > ("scaleFactor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	DivC(qvimage_pSrc, value, qvimage_pDst, scaleFactor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVDivC_sFloatC1Block for IPP function ippiDivC_32f_C1R
QVDivC_sFloatC1Block::QVDivC_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< sFloat >("value", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVDivC_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const sFloat value = getPropertyValue< sFloat > ("value");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	DivC(qvimage_pSrc, value, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAbs_sShortC1Block for IPP function ippiAbs_16s_C1R
QVAbs_sShortC1Block::QVAbs_sShortC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sShort, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sShort, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAbs_sShortC1Block::iterate()
	{
	const QVImage<sShort, 1> qvimage_pSrc = getPropertyValue< QVImage<sShort, 1> > ("qvimage_pSrc");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sShort, 1> qvimage_pDst;
	timeFlag("Create output data");

	Abs(qvimage_pSrc, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sShort, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAbs_sFloatC1Block for IPP function ippiAbs_32f_C1R
QVAbs_sFloatC1Block::QVAbs_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAbs_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	Abs(qvimage_pSrc, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAbsDiff_uCharC1Block for IPP function ippiAbsDiff_8u_C1R
QVAbsDiff_uCharC1Block::QVAbsDiff_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAbsDiff_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc1");
	const QVImage<uChar, 1> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	AbsDiff(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAbsDiff_sFloatC1Block for IPP function ippiAbsDiff_32f_C1R
QVAbsDiff_sFloatC1Block::QVAbsDiff_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAbsDiff_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc1 = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc1");
	const QVImage<sFloat, 1> qvimage_pSrc2 = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	AbsDiff(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVSqr_sFloatC1Block for IPP function ippiSqr_32f_C1R
QVSqr_sFloatC1Block::QVSqr_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVSqr_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	Sqr(qvimage_pSrc, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVLn_sFloatC1Block for IPP function ippiLn_32f_C1R
QVLn_sFloatC1Block::QVLn_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVLn_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	Ln(qvimage_pSrc, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVLn_sFloatC3Block for IPP function ippiLn_32f_C3R
QVLn_sFloatC3Block::QVLn_sFloatC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 3> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVLn_sFloatC3Block::iterate()
	{
	const QVImage<sFloat, 3> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 3> > ("qvimage_pSrc");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 3> qvimage_pDst;
	timeFlag("Create output data");

	Ln(qvimage_pSrc, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAnd_uCharC1Block for IPP function ippiAnd_8u_C1R
QVAnd_uCharC1Block::QVAnd_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAnd_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc1");
	const QVImage<uChar, 1> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	And(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAnd_uCharC3Block for IPP function ippiAnd_8u_C3R
QVAnd_uCharC3Block::QVAnd_uCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAnd_uCharC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc1");
	const QVImage<uChar, 3> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	And(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAnd_uShortC1Block for IPP function ippiAnd_16u_C1R
QVAnd_uShortC1Block::QVAnd_uShortC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uShort, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uShort, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uShort, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAnd_uShortC1Block::iterate()
	{
	const QVImage<uShort, 1> qvimage_pSrc1 = getPropertyValue< QVImage<uShort, 1> > ("qvimage_pSrc1");
	const QVImage<uShort, 1> qvimage_pSrc2 = getPropertyValue< QVImage<uShort, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uShort, 1> qvimage_pDst;
	timeFlag("Create output data");

	And(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uShort, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAnd_uShortC3Block for IPP function ippiAnd_16u_C3R
QVAnd_uShortC3Block::QVAnd_uShortC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uShort, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uShort, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uShort, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAnd_uShortC3Block::iterate()
	{
	const QVImage<uShort, 3> qvimage_pSrc1 = getPropertyValue< QVImage<uShort, 3> > ("qvimage_pSrc1");
	const QVImage<uShort, 3> qvimage_pSrc2 = getPropertyValue< QVImage<uShort, 3> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uShort, 3> qvimage_pDst;
	timeFlag("Create output data");

	And(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uShort, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAnd_sIntC1Block for IPP function ippiAnd_32s_C1R
QVAnd_sIntC1Block::QVAnd_sIntC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sInt, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sInt, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<sInt, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAnd_sIntC1Block::iterate()
	{
	const QVImage<sInt, 1> qvimage_pSrc1 = getPropertyValue< QVImage<sInt, 1> > ("qvimage_pSrc1");
	const QVImage<sInt, 1> qvimage_pSrc2 = getPropertyValue< QVImage<sInt, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sInt, 1> qvimage_pDst;
	timeFlag("Create output data");

	And(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sInt, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAnd_sIntC3Block for IPP function ippiAnd_32s_C3R
QVAnd_sIntC3Block::QVAnd_sIntC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sInt, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sInt, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<sInt, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAnd_sIntC3Block::iterate()
	{
	const QVImage<sInt, 3> qvimage_pSrc1 = getPropertyValue< QVImage<sInt, 3> > ("qvimage_pSrc1");
	const QVImage<sInt, 3> qvimage_pSrc2 = getPropertyValue< QVImage<sInt, 3> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sInt, 3> qvimage_pDst;
	timeFlag("Create output data");

	And(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sInt, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVOr_uCharC1Block for IPP function ippiOr_8u_C1R
QVOr_uCharC1Block::QVOr_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVOr_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc1");
	const QVImage<uChar, 1> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	Or(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVOr_uCharC3Block for IPP function ippiOr_8u_C3R
QVOr_uCharC3Block::QVOr_uCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVOr_uCharC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc1");
	const QVImage<uChar, 3> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	Or(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVOr_uShortC1Block for IPP function ippiOr_16u_C1R
QVOr_uShortC1Block::QVOr_uShortC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uShort, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uShort, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uShort, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVOr_uShortC1Block::iterate()
	{
	const QVImage<uShort, 1> qvimage_pSrc1 = getPropertyValue< QVImage<uShort, 1> > ("qvimage_pSrc1");
	const QVImage<uShort, 1> qvimage_pSrc2 = getPropertyValue< QVImage<uShort, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uShort, 1> qvimage_pDst;
	timeFlag("Create output data");

	Or(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uShort, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVOr_uShortC3Block for IPP function ippiOr_16u_C3R
QVOr_uShortC3Block::QVOr_uShortC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uShort, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uShort, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uShort, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVOr_uShortC3Block::iterate()
	{
	const QVImage<uShort, 3> qvimage_pSrc1 = getPropertyValue< QVImage<uShort, 3> > ("qvimage_pSrc1");
	const QVImage<uShort, 3> qvimage_pSrc2 = getPropertyValue< QVImage<uShort, 3> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uShort, 3> qvimage_pDst;
	timeFlag("Create output data");

	Or(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uShort, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVOr_sIntC1Block for IPP function ippiOr_32s_C1R
QVOr_sIntC1Block::QVOr_sIntC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sInt, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sInt, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<sInt, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVOr_sIntC1Block::iterate()
	{
	const QVImage<sInt, 1> qvimage_pSrc1 = getPropertyValue< QVImage<sInt, 1> > ("qvimage_pSrc1");
	const QVImage<sInt, 1> qvimage_pSrc2 = getPropertyValue< QVImage<sInt, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sInt, 1> qvimage_pDst;
	timeFlag("Create output data");

	Or(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sInt, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVOr_sIntC3Block for IPP function ippiOr_32s_C3R
QVOr_sIntC3Block::QVOr_sIntC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sInt, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sInt, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<sInt, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVOr_sIntC3Block::iterate()
	{
	const QVImage<sInt, 3> qvimage_pSrc1 = getPropertyValue< QVImage<sInt, 3> > ("qvimage_pSrc1");
	const QVImage<sInt, 3> qvimage_pSrc2 = getPropertyValue< QVImage<sInt, 3> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sInt, 3> qvimage_pDst;
	timeFlag("Create output data");

	Or(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sInt, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVXor_uCharC1Block for IPP function ippiXor_8u_C1R
QVXor_uCharC1Block::QVXor_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVXor_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc1");
	const QVImage<uChar, 1> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	Xor(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVXor_uCharC3Block for IPP function ippiXor_8u_C3R
QVXor_uCharC3Block::QVXor_uCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVXor_uCharC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc1");
	const QVImage<uChar, 3> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	Xor(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVXor_uShortC1Block for IPP function ippiXor_16u_C1R
QVXor_uShortC1Block::QVXor_uShortC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uShort, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uShort, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uShort, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVXor_uShortC1Block::iterate()
	{
	const QVImage<uShort, 1> qvimage_pSrc1 = getPropertyValue< QVImage<uShort, 1> > ("qvimage_pSrc1");
	const QVImage<uShort, 1> qvimage_pSrc2 = getPropertyValue< QVImage<uShort, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uShort, 1> qvimage_pDst;
	timeFlag("Create output data");

	Xor(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uShort, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVXor_uShortC3Block for IPP function ippiXor_16u_C3R
QVXor_uShortC3Block::QVXor_uShortC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uShort, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uShort, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uShort, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVXor_uShortC3Block::iterate()
	{
	const QVImage<uShort, 3> qvimage_pSrc1 = getPropertyValue< QVImage<uShort, 3> > ("qvimage_pSrc1");
	const QVImage<uShort, 3> qvimage_pSrc2 = getPropertyValue< QVImage<uShort, 3> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uShort, 3> qvimage_pDst;
	timeFlag("Create output data");

	Xor(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uShort, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVXor_sIntC1Block for IPP function ippiXor_32s_C1R
QVXor_sIntC1Block::QVXor_sIntC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sInt, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sInt, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<sInt, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVXor_sIntC1Block::iterate()
	{
	const QVImage<sInt, 1> qvimage_pSrc1 = getPropertyValue< QVImage<sInt, 1> > ("qvimage_pSrc1");
	const QVImage<sInt, 1> qvimage_pSrc2 = getPropertyValue< QVImage<sInt, 1> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sInt, 1> qvimage_pDst;
	timeFlag("Create output data");

	Xor(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sInt, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVXor_sIntC3Block for IPP function ippiXor_32s_C3R
QVXor_sIntC3Block::QVXor_sIntC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sInt, 3> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sInt, 3> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<sInt, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVXor_sIntC3Block::iterate()
	{
	const QVImage<sInt, 3> qvimage_pSrc1 = getPropertyValue< QVImage<sInt, 3> > ("qvimage_pSrc1");
	const QVImage<sInt, 3> qvimage_pSrc2 = getPropertyValue< QVImage<sInt, 3> > ("qvimage_pSrc2");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sInt, 3> qvimage_pDst;
	timeFlag("Create output data");

	Xor(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sInt, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVNot_uCharC1Block for IPP function ippiNot_8u_C1R
QVNot_uCharC1Block::QVNot_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVNot_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	Not(qvimage_pSrc, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVNot_uCharC3Block for IPP function ippiNot_8u_C3R
QVNot_uCharC3Block::QVNot_uCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVNot_uCharC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	Not(qvimage_pSrc, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVAndC_uCharC1Block for IPP function ippiAndC_8u_C1R
QVAndC_uCharC1Block::QVAndC_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< uChar >("value", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVAndC_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const uChar value = getPropertyValue< uChar > ("value");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	AndC(qvimage_pSrc, value, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVOrC_uCharC1Block for IPP function ippiOrC_8u_C1R
QVOrC_uCharC1Block::QVOrC_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< uChar >("value", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVOrC_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const uChar value = getPropertyValue< uChar > ("value");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	OrC(qvimage_pSrc, value, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVXorC_uCharC1Block for IPP function ippiXorC_8u_C1R
QVXorC_uCharC1Block::QVXorC_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< uChar >("value", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVXorC_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const uChar value = getPropertyValue< uChar > ("value");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	XorC(qvimage_pSrc, value, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVLShiftC_uCharC1Block for IPP function ippiLShiftC_8u_C1R
QVLShiftC_uCharC1Block::QVLShiftC_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< uInt >("value", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVLShiftC_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const uInt value = getPropertyValue< uInt > ("value");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	LShiftC(qvimage_pSrc, value, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVRShiftC_uCharC1Block for IPP function ippiRShiftC_8u_C1R
QVRShiftC_uCharC1Block::QVRShiftC_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< uInt >("value", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVRShiftC_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const uInt value = getPropertyValue< uInt > ("value");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	RShiftC(qvimage_pSrc, value, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVRGBToGray_uCharC3C1Block for IPP function ippiRGBToGray_8u_C3C1R
QVRGBToGray_uCharC3C1Block::QVRGBToGray_uCharC3C1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVRGBToGray_uCharC3C1Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	RGBToGray(qvimage_pSrc, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVRGBToGray_sFloatC3C1Block for IPP function ippiRGBToGray_32f_C3C1R
QVRGBToGray_sFloatC3C1Block::QVRGBToGray_sFloatC3C1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 3> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVRGBToGray_sFloatC3C1Block::iterate()
	{
	const QVImage<sFloat, 3> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 3> > ("qvimage_pSrc");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	RGBToGray(qvimage_pSrc, qvimage_pDst, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVThreshold_uCharC1Block for IPP function ippiThreshold_8u_C1R
QVThreshold_uCharC1Block::QVThreshold_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< uChar >("threshold", inputFlag);
	addProperty< IppCmpOp >("ippCmpOp", inputFlag, ippCmpEq);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVThreshold_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const uChar threshold = getPropertyValue< uChar > ("threshold");
	const IppCmpOp ippCmpOp = getPropertyValue< IppCmpOp > ("ippCmpOp");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	Threshold(qvimage_pSrc, qvimage_pDst, threshold, ippCmpOp, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVThreshold_sFloatC1Block for IPP function ippiThreshold_32f_C1R
QVThreshold_sFloatC1Block::QVThreshold_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< sFloat >("threshold", inputFlag);
	addProperty< IppCmpOp >("ippCmpOp", inputFlag, ippCmpEq);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVThreshold_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const sFloat threshold = getPropertyValue< sFloat > ("threshold");
	const IppCmpOp ippCmpOp = getPropertyValue< IppCmpOp > ("ippCmpOp");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	Threshold(qvimage_pSrc, qvimage_pDst, threshold, ippCmpOp, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVComputeThreshold_Otsu_uCharC1Block for IPP function ippiComputeThreshold_Otsu_8u_C1R
QVComputeThreshold_Otsu_uCharC1Block::QVComputeThreshold_Otsu_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< uChar >("pThreshold", outputFlag);
	}

void QVComputeThreshold_Otsu_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	timeFlag("Read input data");

	uChar pThreshold;
	timeFlag("Create output data");

	ComputeThreshold_Otsu(qvimage_pSrc, pThreshold);
	timeFlag("Process input data");

	setPropertyValue< uChar >("pThreshold", pThreshold);
	timeFlag("Store output data");
	}

// Block QVCompare_uCharC1Block for IPP function ippiCompare_8u_C1R
QVCompare_uCharC1Block::QVCompare_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppCmpOp >("ippCmpOp", inputFlag, ippCmpEq);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVCompare_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc1 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc1");
	const QVImage<uChar, 1> qvimage_pSrc2 = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc2");
	const IppCmpOp ippCmpOp = getPropertyValue< IppCmpOp > ("ippCmpOp");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	Compare(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, ippCmpOp, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVCompare_sFloatC1Block for IPP function ippiCompare_32f_C1R
QVCompare_sFloatC1Block::QVCompare_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc1", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc2", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppCmpOp >("ippCmpOp", inputFlag, ippCmpEq);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVCompare_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc1 = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc1");
	const QVImage<sFloat, 1> qvimage_pSrc2 = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc2");
	const IppCmpOp ippCmpOp = getPropertyValue< IppCmpOp > ("ippCmpOp");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	Compare(qvimage_pSrc1, qvimage_pSrc2, qvimage_pDst, ippCmpOp, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVCompareC_uCharC1Block for IPP function ippiCompareC_8u_C1R
QVCompareC_uCharC1Block::QVCompareC_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< uChar >("value", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppCmpOp >("ippCmpOp", inputFlag, ippCmpEq);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVCompareC_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const uChar value = getPropertyValue< uChar > ("value");
	const IppCmpOp ippCmpOp = getPropertyValue< IppCmpOp > ("ippCmpOp");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	CompareC(qvimage_pSrc, value, qvimage_pDst, ippCmpOp, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVCompareC_sFloatC1Block for IPP function ippiCompareC_32f_C1R
QVCompareC_sFloatC1Block::QVCompareC_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< sFloat >("value", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppCmpOp >("ippCmpOp", inputFlag, ippCmpEq);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVCompareC_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const sFloat value = getPropertyValue< sFloat > ("value");
	const IppCmpOp ippCmpOp = getPropertyValue< IppCmpOp > ("ippCmpOp");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	CompareC(qvimage_pSrc, value, qvimage_pDst, ippCmpOp, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterBox_uCharC1Block for IPP function ippiFilterBox_8u_C1R
QVFilterBox_uCharC1Block::QVFilterBox_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QSize >("maskSize", inputFlag, QSize(3,3));
	addProperty< QPoint >("anchor", inputFlag, QPoint(0,0));
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterBox_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const QSize maskSize = getPropertyValue< QSize > ("maskSize");
	const QPoint anchor = getPropertyValue< QPoint > ("anchor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterBox(qvimage_pSrc, qvimage_pDst, maskSize, anchor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterBox_uCharC3Block for IPP function ippiFilterBox_8u_C3R
QVFilterBox_uCharC3Block::QVFilterBox_uCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< QSize >("maskSize", inputFlag, QSize(3,3));
	addProperty< QPoint >("anchor", inputFlag, QPoint(0,0));
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterBox_uCharC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc");
	const QSize maskSize = getPropertyValue< QSize > ("maskSize");
	const QPoint anchor = getPropertyValue< QPoint > ("anchor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	FilterBox(qvimage_pSrc, qvimage_pDst, maskSize, anchor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterBox_sFloatC1Block for IPP function ippiFilterBox_32f_C1R
QVFilterBox_sFloatC1Block::QVFilterBox_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QSize >("maskSize", inputFlag, QSize(3,3));
	addProperty< QPoint >("anchor", inputFlag, QPoint(0,0));
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterBox_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const QSize maskSize = getPropertyValue< QSize > ("maskSize");
	const QPoint anchor = getPropertyValue< QPoint > ("anchor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterBox(qvimage_pSrc, qvimage_pDst, maskSize, anchor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterMin_uCharC1Block for IPP function ippiFilterMin_8u_C1R
QVFilterMin_uCharC1Block::QVFilterMin_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QSize >("maskSize", inputFlag, QSize(3,3));
	addProperty< QPoint >("anchor", inputFlag, QPoint(0,0));
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterMin_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const QSize maskSize = getPropertyValue< QSize > ("maskSize");
	const QPoint anchor = getPropertyValue< QPoint > ("anchor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterMin(qvimage_pSrc, qvimage_pDst, maskSize, anchor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterMin_uCharC3Block for IPP function ippiFilterMin_8u_C3R
QVFilterMin_uCharC3Block::QVFilterMin_uCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< QSize >("maskSize", inputFlag, QSize(3,3));
	addProperty< QPoint >("anchor", inputFlag, QPoint(0,0));
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterMin_uCharC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc");
	const QSize maskSize = getPropertyValue< QSize > ("maskSize");
	const QPoint anchor = getPropertyValue< QPoint > ("anchor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	FilterMin(qvimage_pSrc, qvimage_pDst, maskSize, anchor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterMin_sFloatC1Block for IPP function ippiFilterMin_32f_C1R
QVFilterMin_sFloatC1Block::QVFilterMin_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QSize >("maskSize", inputFlag, QSize(3,3));
	addProperty< QPoint >("anchor", inputFlag, QPoint(0,0));
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterMin_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const QSize maskSize = getPropertyValue< QSize > ("maskSize");
	const QPoint anchor = getPropertyValue< QPoint > ("anchor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterMin(qvimage_pSrc, qvimage_pDst, maskSize, anchor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterMax_uCharC1Block for IPP function ippiFilterMax_8u_C1R
QVFilterMax_uCharC1Block::QVFilterMax_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QSize >("maskSize", inputFlag, QSize(3,3));
	addProperty< QPoint >("anchor", inputFlag, QPoint(0,0));
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterMax_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const QSize maskSize = getPropertyValue< QSize > ("maskSize");
	const QPoint anchor = getPropertyValue< QPoint > ("anchor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterMax(qvimage_pSrc, qvimage_pDst, maskSize, anchor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterMax_uCharC3Block for IPP function ippiFilterMax_8u_C3R
QVFilterMax_uCharC3Block::QVFilterMax_uCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< QSize >("maskSize", inputFlag, QSize(3,3));
	addProperty< QPoint >("anchor", inputFlag, QPoint(0,0));
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterMax_uCharC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc");
	const QSize maskSize = getPropertyValue< QSize > ("maskSize");
	const QPoint anchor = getPropertyValue< QPoint > ("anchor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	FilterMax(qvimage_pSrc, qvimage_pDst, maskSize, anchor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterMax_sFloatC1Block for IPP function ippiFilterMax_32f_C1R
QVFilterMax_sFloatC1Block::QVFilterMax_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< QSize >("maskSize", inputFlag, QSize(3,3));
	addProperty< QPoint >("anchor", inputFlag, QPoint(0,0));
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterMax_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const QSize maskSize = getPropertyValue< QSize > ("maskSize");
	const QPoint anchor = getPropertyValue< QPoint > ("anchor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterMax(qvimage_pSrc, qvimage_pDst, maskSize, anchor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterMedian_uCharC1Block for IPP function ippiFilterMedian_8u_C1R
QVFilterMedian_uCharC1Block::QVFilterMedian_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< QSize >("maskSize", inputFlag, QSize(3,3));
	addProperty< QPoint >("anchor", inputFlag, QPoint(0,0));
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterMedian_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const QSize maskSize = getPropertyValue< QSize > ("maskSize");
	const QPoint anchor = getPropertyValue< QPoint > ("anchor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterMedian(qvimage_pSrc, qvimage_pDst, maskSize, anchor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterMedian_uCharC3Block for IPP function ippiFilterMedian_8u_C3R
QVFilterMedian_uCharC3Block::QVFilterMedian_uCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< QSize >("maskSize", inputFlag, QSize(3,3));
	addProperty< QPoint >("anchor", inputFlag, QPoint(0,0));
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterMedian_uCharC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc");
	const QSize maskSize = getPropertyValue< QSize > ("maskSize");
	const QPoint anchor = getPropertyValue< QPoint > ("anchor");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	FilterMedian(qvimage_pSrc, qvimage_pDst, maskSize, anchor, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterMedianHoriz_uCharC1Block for IPP function ippiFilterMedianHoriz_8u_C1R
QVFilterMedianHoriz_uCharC1Block::QVFilterMedianHoriz_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize3x3);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterMedianHoriz_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterMedianHoriz(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterSobelHorizMask_sFloatC1Block for IPP function ippiFilterSobelHorizMask_32f_C1R
QVFilterSobelHorizMask_sFloatC1Block::QVFilterSobelHorizMask_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize3x3);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterSobelHorizMask_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterSobelHorizMask(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterSobelVertMask_sFloatC1Block for IPP function ippiFilterSobelVertMask_32f_C1R
QVFilterSobelVertMask_sFloatC1Block::QVFilterSobelVertMask_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize3x3);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterSobelVertMask_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterSobelVertMask(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterLaplace_uCharC1Block for IPP function ippiFilterLaplace_8u_C1R
QVFilterLaplace_uCharC1Block::QVFilterLaplace_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize3x3);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterLaplace_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterLaplace(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterLaplace_sFloatC1Block for IPP function ippiFilterLaplace_32f_C1R
QVFilterLaplace_sFloatC1Block::QVFilterLaplace_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize3x3);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterLaplace_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterLaplace(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterGauss_uCharC1Block for IPP function ippiFilterGauss_8u_C1R
QVFilterGauss_uCharC1Block::QVFilterGauss_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize3x3);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterGauss_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterGauss(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterGauss_sFloatC1Block for IPP function ippiFilterGauss_32f_C1R
QVFilterGauss_sFloatC1Block::QVFilterGauss_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize3x3);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterGauss_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterGauss(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterGauss_uCharC3Block for IPP function ippiFilterGauss_8u_C3R
QVFilterGauss_uCharC3Block::QVFilterGauss_uCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize3x3);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterGauss_uCharC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc");
	const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	FilterGauss(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterGauss_sFloatC3Block for IPP function ippiFilterGauss_32f_C3R
QVFilterGauss_sFloatC3Block::QVFilterGauss_sFloatC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 3> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 3> >("qvimage_pDst", outputFlag);
	addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize3x3);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterGauss_sFloatC3Block::iterate()
	{
	const QVImage<sFloat, 3> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 3> > ("qvimage_pSrc");
	const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 3> qvimage_pDst;
	timeFlag("Create output data");

	FilterGauss(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterHipass_uCharC1Block for IPP function ippiFilterHipass_8u_C1R
QVFilterHipass_uCharC1Block::QVFilterHipass_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize3x3);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterHipass_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterHipass(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterHipass_uCharC3Block for IPP function ippiFilterHipass_8u_C3R
QVFilterHipass_uCharC3Block::QVFilterHipass_uCharC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 3> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 3> >("qvimage_pDst", outputFlag);
	addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize3x3);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterHipass_uCharC3Block::iterate()
	{
	const QVImage<uChar, 3> qvimage_pSrc = getPropertyValue< QVImage<uChar, 3> > ("qvimage_pSrc");
	const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 3> qvimage_pDst;
	timeFlag("Create output data");

	FilterHipass(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterHipass_sFloatC1Block for IPP function ippiFilterHipass_32f_C1R
QVFilterHipass_sFloatC1Block::QVFilterHipass_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize3x3);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterHipass_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterHipass(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterHipass_sFloatC3Block for IPP function ippiFilterHipass_32f_C3R
QVFilterHipass_sFloatC3Block::QVFilterHipass_sFloatC3Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 3> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 3> >("qvimage_pDst", outputFlag);
	addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize3x3);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterHipass_sFloatC3Block::iterate()
	{
	const QVImage<sFloat, 3> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 3> > ("qvimage_pSrc");
	const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 3> qvimage_pDst;
	timeFlag("Create output data");

	FilterHipass(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 3> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterLowpass_uCharC1Block for IPP function ippiFilterLowpass_8u_C1R
QVFilterLowpass_uCharC1Block::QVFilterLowpass_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<uChar, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize3x3);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterLowpass_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<uChar, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterLowpass(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<uChar, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVFilterLowpass_sFloatC1Block for IPP function ippiFilterLowpass_32f_C1R
QVFilterLowpass_sFloatC1Block::QVFilterLowpass_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< QVImage<sFloat, 1> >("qvimage_pDst", outputFlag);
	addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize3x3);
	addProperty< QPoint >("destROIOffset", inputFlag, QPoint(0,0));
	}

void QVFilterLowpass_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
	const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
	timeFlag("Read input data");

	QVImage<sFloat, 1> qvimage_pDst;
	timeFlag("Create output data");

	FilterLowpass(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
	timeFlag("Process input data");

	setPropertyValue< QVImage<sFloat, 1> >("qvimage_pDst", qvimage_pDst);
	timeFlag("Store output data");
	}

// Block QVSum_uCharC1Block for IPP function ippiSum_8u_C1R
QVSum_uCharC1Block::QVSum_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< sDouble >("pSum", outputFlag);
	}

void QVSum_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	timeFlag("Read input data");

	sDouble pSum;
	timeFlag("Create output data");

	Sum(qvimage_pSrc, pSum);
	timeFlag("Process input data");

	setPropertyValue< sDouble >("pSum", pSum);
	timeFlag("Store output data");
	}

// Block QVMean_uCharC1Block for IPP function ippiMean_8u_C1R
QVMean_uCharC1Block::QVMean_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< sDouble >("pMean", outputFlag);
	}

void QVMean_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	timeFlag("Read input data");

	sDouble pMean;
	timeFlag("Create output data");

	Mean(qvimage_pSrc, pMean);
	timeFlag("Process input data");

	setPropertyValue< sDouble >("pMean", pMean);
	timeFlag("Store output data");
	}

// Block QVMin_uCharC1Block for IPP function ippiMin_8u_C1R
QVMin_uCharC1Block::QVMin_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< uChar >("pMin", outputFlag);
	}

void QVMin_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	timeFlag("Read input data");

	uChar pMin;
	timeFlag("Create output data");

	Min(qvimage_pSrc, pMin);
	timeFlag("Process input data");

	setPropertyValue< uChar >("pMin", pMin);
	timeFlag("Store output data");
	}

// Block QVMin_sFloatC1Block for IPP function ippiMin_32f_C1R
QVMin_sFloatC1Block::QVMin_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< sFloat >("pMin", outputFlag);
	}

void QVMin_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	timeFlag("Read input data");

	sFloat pMin;
	timeFlag("Create output data");

	Min(qvimage_pSrc, pMin);
	timeFlag("Process input data");

	setPropertyValue< sFloat >("pMin", pMin);
	timeFlag("Store output data");
	}

// Block QVMax_uCharC1Block for IPP function ippiMax_8u_C1R
QVMax_uCharC1Block::QVMax_uCharC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<uChar, 1> >("qvimage_pSrc", inputFlag);
	addProperty< uChar >("pMax", outputFlag);
	}

void QVMax_uCharC1Block::iterate()
	{
	const QVImage<uChar, 1> qvimage_pSrc = getPropertyValue< QVImage<uChar, 1> > ("qvimage_pSrc");
	timeFlag("Read input data");

	uChar pMax;
	timeFlag("Create output data");

	Max(qvimage_pSrc, pMax);
	timeFlag("Process input data");

	setPropertyValue< uChar >("pMax", pMax);
	timeFlag("Store output data");
	}

// Block QVMax_sFloatC1Block for IPP function ippiMax_32f_C1R
QVMax_sFloatC1Block::QVMax_sFloatC1Block(QString name): QVProcessingBlock(name)
	{
	addProperty< QVImage<sFloat, 1> >("qvimage_pSrc", inputFlag);
	addProperty< sFloat >("pMax", outputFlag);
	}

void QVMax_sFloatC1Block::iterate()
	{
	const QVImage<sFloat, 1> qvimage_pSrc = getPropertyValue< QVImage<sFloat, 1> > ("qvimage_pSrc");
	timeFlag("Read input data");

	sFloat pMax;
	timeFlag("Create output data");

	Max(qvimage_pSrc, pMax);
	timeFlag("Process input data");

	setPropertyValue< sFloat >("pMax", pMax);
	timeFlag("Store output data");
	}


