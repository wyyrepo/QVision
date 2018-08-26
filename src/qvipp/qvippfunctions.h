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

#include <ipp.h>

#include <QSize>
#include <QPoint>
#include <QVImage>

#include <qvdefines.h>

#ifndef QVIPPFUNCTIONS_H
#define QVIPPFUNCTIONS_H

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_8u16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_8u16s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_8u32s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_8u32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_8u16u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_8u16s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<sShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_8u32s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_8u32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_16u8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_16u32s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_16u32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_16u8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<uShort, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_16u32s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<uShort, 3> & qvimage_pSrc,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_16u32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<uShort, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_16s8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_16s32s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_16s32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_16s8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<sShort, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_16s32s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<sShort, 3> & qvimage_pSrc,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_16s32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<sShort, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_32s8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<sInt, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_32s8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<sInt, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_32f8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param roundMode	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppRoundMode roundMode = ippRndNear,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_32f16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param roundMode	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const IppRoundMode roundMode = ippRndNear,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_32f16s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param roundMode	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const IppRoundMode roundMode = ippRndNear,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_32f8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param roundMode	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const IppRoundMode roundMode = ippRndNear,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_32f16u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param roundMode	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<uShort, 3> & qvimage_pDst,
		const IppRoundMode roundMode = ippRndNear,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision wrapper function for IPP's <b>ippiConvert_32f16s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param roundMode	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Convert(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sShort, 3> & qvimage_pDst,
		const IppRoundMode roundMode = ippRndNear,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Scales pixel values of an image and converts them to another bit depth dst = a + b * src; a = type_min_dst - b * type_min_src; b = (type_max_dst - type_min_dst) (type_max_src - type_min_src)

This is the QVision wrapper function for IPP's <b>ippiScale_8u16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Scale(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Scales pixel values of an image and converts them to another bit depth dst = a + b * src; a = type_min_dst - b * type_min_src; b = (type_max_dst - type_min_dst) (type_max_src - type_min_src)

This is the QVision wrapper function for IPP's <b>ippiScale_8u16s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Scale(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Scales pixel values of an image and converts them to another bit depth dst = a + b * src; a = type_min_dst - b * type_min_src; b = (type_max_dst - type_min_dst) (type_max_src - type_min_src)

This is the QVision wrapper function for IPP's <b>ippiScale_8u32s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Scale(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Scales pixel values of an image and converts them to another bit depth dst = a + b * src; a = type_min_dst - b * type_min_src; b = (type_max_dst - type_min_dst) (type_max_src - type_min_src)

This is the QVision wrapper function for IPP's <b>ippiScale_8u16u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Scale(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Scales pixel values of an image and converts them to another bit depth dst = a + b * src; a = type_min_dst - b * type_min_src; b = (type_max_dst - type_min_dst) (type_max_src - type_min_src)

This is the QVision wrapper function for IPP's <b>ippiScale_8u16s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Scale(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<sShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Scales pixel values of an image and converts them to another bit depth dst = a + b * src; a = type_min_dst - b * type_min_src; b = (type_max_dst - type_min_dst) (type_max_src - type_min_src)

This is the QVision wrapper function for IPP's <b>ippiScale_8u32s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Scale(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Sets pixels in the image buffer to a constant value

This is the QVision wrapper function for IPP's <b>ippiSet_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function

@ingroup qvippIDEAIF
*/
void Set(
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst);

/*!
@brief Sets pixels in the image buffer to a constant value

This is the QVision wrapper function for IPP's <b>ippiSet_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function

@ingroup qvippIDEAIF
*/
void Set(
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst);

/*!
@brief Sets pixels in the image buffer to a constant value

This is the QVision wrapper function for IPP's <b>ippiSet_16s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function

@ingroup qvippIDEAIF
*/
void Set(
		const sShort value,
		QVImage<sShort, 1> & qvimage_pDst);

/*!
@brief Sets pixels in the image buffer to a constant value

This is the QVision wrapper function for IPP's <b>ippiSet_32s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function

@ingroup qvippIDEAIF
*/
void Set(
		const sInt value,
		QVImage<sInt, 1> & qvimage_pDst);

/*!
@brief Sets pixels in the image buffer to a constant value

This is the QVision wrapper function for IPP's <b>ippiSet_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function

@ingroup qvippIDEAIF
*/
void Set(
		const sFloat value,
		QVImage<sFloat, 1> & qvimage_pDst);

/*!
@brief Sets pixels in the image buffer to a constant value

This is the QVision wrapper function for IPP's <b>ippiSet_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function

@ingroup qvippIDEAIF
*/
void Set(
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst);

/*!
@brief Sets pixels in the image buffer to a constant value

This is the QVision wrapper function for IPP's <b>ippiSet_16u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function

@ingroup qvippIDEAIF
*/
void Set(
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst);

/*!
@brief Sets pixels in the image buffer to a constant value

This is the QVision wrapper function for IPP's <b>ippiSet_16s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function

@ingroup qvippIDEAIF
*/
void Set(
		const  sShort value[3],
		QVImage<sShort, 3> & qvimage_pDst);

/*!
@brief Sets pixels in the image buffer to a constant value

This is the QVision wrapper function for IPP's <b>ippiSet_32s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function

@ingroup qvippIDEAIF
*/
void Set(
		const  sInt value[3],
		QVImage<sInt, 3> & qvimage_pDst);

/*!
@brief Sets pixels in the image buffer to a constant value

This is the QVision wrapper function for IPP's <b>ippiSet_32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function

@ingroup qvippIDEAIF
*/
void Set(
		const  sFloat value[3],
		QVImage<sFloat, 3> & qvimage_pDst);

/*!
@brief Copy pixel values from the source image to the destination image

This is the QVision wrapper function for IPP's <b>ippiCopy_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Copy(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Copy pixel values from the source image to the destination image

This is the QVision wrapper function for IPP's <b>ippiCopy_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Copy(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Copy pixel values from the source image to the destination image

This is the QVision wrapper function for IPP's <b>ippiCopy_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Copy(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Copy pixel values from the source image to the destination image

This is the QVision wrapper function for IPP's <b>ippiCopy_16u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Copy(
		const QVImage<uShort, 3> & qvimage_pSrc,
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Copy pixel values from the source image to the destination image

This is the QVision wrapper function for IPP's <b>ippiCopy_16s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Copy(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Copy pixel values from the source image to the destination image

This is the QVision wrapper function for IPP's <b>ippiCopy_16s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Copy(
		const QVImage<sShort, 3> & qvimage_pSrc,
		QVImage<sShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Copy pixel values from the source image to the destination image

This is the QVision wrapper function for IPP's <b>ippiCopy_32s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Copy(
		const QVImage<sInt, 1> & qvimage_pSrc,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Copy pixel values from the source image to the destination image

This is the QVision wrapper function for IPP's <b>ippiCopy_32s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Copy(
		const QVImage<sInt, 3> & qvimage_pSrc,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Copy pixel values from the source image to the destination image

This is the QVision wrapper function for IPP's <b>ippiCopy_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Copy(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Copy pixel values from the source image to the destination image

This is the QVision wrapper function for IPP's <b>ippiCopy_32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIDEAIF
*/
void Copy(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Generates pseudo-random samples with uniform distribution and adds them to an image

This is the QVision wrapper function for IPP's <b>ippiAddRandUniform_Direct_8u_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param low	Corresponds to the same parameter of type IppiSize in the IPP function.
@param high	Corresponds to the same parameter of type IppiSize in the IPP function.
@param pSeed	Corresponds to the same parameter in the IPP function.

@ingroup qvippIDEAIF
*/
void AddRandUniform_Direct(
		QVImage<uChar, 1> & qvimage_pSrcDst,
		const uChar low,
		const uChar high,
		 unsigned int & pSeed);

/*!
@brief Generates pseudo-random samples with uniform distribution and adds them to an image

This is the QVision wrapper function for IPP's <b>ippiAddRandUniform_Direct_16u_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param low	Corresponds to the same parameter of type IppiSize in the IPP function.
@param high	Corresponds to the same parameter of type IppiSize in the IPP function.
@param pSeed	Corresponds to the same parameter in the IPP function.

@ingroup qvippIDEAIF
*/
void AddRandUniform_Direct(
		QVImage<uShort, 1> & qvimage_pSrcDst,
		const uShort low,
		const uShort high,
		 unsigned int & pSeed);

/*!
@brief Generates pseudo-random samples with uniform distribution and adds them to an image

This is the QVision wrapper function for IPP's <b>ippiAddRandUniform_Direct_16s_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param low	Corresponds to the same parameter of type IppiSize in the IPP function.
@param high	Corresponds to the same parameter of type IppiSize in the IPP function.
@param pSeed	Corresponds to the same parameter in the IPP function.

@ingroup qvippIDEAIF
*/
void AddRandUniform_Direct(
		QVImage<sShort, 1> & qvimage_pSrcDst,
		const sShort low,
		const sShort high,
		 unsigned int & pSeed);

/*!
@brief Generates pseudo-random samples with uniform distribution and adds them to an image

This is the QVision wrapper function for IPP's <b>ippiAddRandUniform_Direct_32f_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param low	Corresponds to the same parameter of type IppiSize in the IPP function.
@param high	Corresponds to the same parameter of type IppiSize in the IPP function.
@param pSeed	Corresponds to the same parameter in the IPP function.

@ingroup qvippIDEAIF
*/
void AddRandUniform_Direct(
		QVImage<sFloat, 1> & qvimage_pSrcDst,
		const sFloat low,
		const sFloat high,
		 unsigned int & pSeed);

/*!
@brief Generates pseudo-random samples with uniform distribution and adds them to an image

This is the QVision wrapper function for IPP's <b>ippiAddRandUniform_Direct_8u_C3IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param low	Corresponds to the same parameter of type IppiSize in the IPP function.
@param high	Corresponds to the same parameter of type IppiSize in the IPP function.
@param pSeed	Corresponds to the same parameter in the IPP function.

@ingroup qvippIDEAIF
*/
void AddRandUniform_Direct(
		QVImage<uChar, 3> & qvimage_pSrcDst,
		const uChar low,
		const uChar high,
		 unsigned int & pSeed);

/*!
@brief Generates pseudo-random samples with uniform distribution and adds them to an image

This is the QVision wrapper function for IPP's <b>ippiAddRandUniform_Direct_16u_C3IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param low	Corresponds to the same parameter of type IppiSize in the IPP function.
@param high	Corresponds to the same parameter of type IppiSize in the IPP function.
@param pSeed	Corresponds to the same parameter in the IPP function.

@ingroup qvippIDEAIF
*/
void AddRandUniform_Direct(
		QVImage<uShort, 3> & qvimage_pSrcDst,
		const uShort low,
		const uShort high,
		 unsigned int & pSeed);

/*!
@brief Generates pseudo-random samples with uniform distribution and adds them to an image

This is the QVision wrapper function for IPP's <b>ippiAddRandUniform_Direct_16s_C3IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param low	Corresponds to the same parameter of type IppiSize in the IPP function.
@param high	Corresponds to the same parameter of type IppiSize in the IPP function.
@param pSeed	Corresponds to the same parameter in the IPP function.

@ingroup qvippIDEAIF
*/
void AddRandUniform_Direct(
		QVImage<sShort, 3> & qvimage_pSrcDst,
		const sShort low,
		const sShort high,
		 unsigned int & pSeed);

/*!
@brief Generates pseudo-random samples with uniform distribution and adds them to an image

This is the QVision wrapper function for IPP's <b>ippiAddRandUniform_Direct_32f_C3IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param low	Corresponds to the same parameter of type IppiSize in the IPP function.
@param high	Corresponds to the same parameter of type IppiSize in the IPP function.
@param pSeed	Corresponds to the same parameter in the IPP function.

@ingroup qvippIDEAIF
*/
void AddRandUniform_Direct(
		QVImage<sFloat, 3> & qvimage_pSrcDst,
		const sFloat low,
		const sFloat high,
		 unsigned int & pSeed);

/*!
@brief Add image to accumulator

This is the QVision wrapper function for IPP's <b>ippiAdd_8u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Add(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Add image to accumulator

This is the QVision wrapper function for IPP's <b>ippiAdd_8u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Add(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Add image to accumulator

This is the QVision wrapper function for IPP's <b>ippiAdd_16u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Add(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Add image to accumulator

This is the QVision wrapper function for IPP's <b>ippiAdd_16u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Add(
		const QVImage<uShort, 3> & qvimage_pSrc1,
		const QVImage<uShort, 3> & qvimage_pSrc2,
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Add image to accumulator

This is the QVision wrapper function for IPP's <b>ippiAdd_16s_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Add(
		const QVImage<sShort, 1> & qvimage_pSrc1,
		const QVImage<sShort, 1> & qvimage_pSrc2,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Add image to accumulator

This is the QVision wrapper function for IPP's <b>ippiAdd_16s_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Add(
		const QVImage<sShort, 3> & qvimage_pSrc1,
		const QVImage<sShort, 3> & qvimage_pSrc2,
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Add image to accumulator

This is the QVision wrapper function for IPP's <b>ippiAdd_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Add(
		const QVImage<sFloat, 1> & qvimage_pSrc1,
		const QVImage<sFloat, 1> & qvimage_pSrc2,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Add image to accumulator

This is the QVision wrapper function for IPP's <b>ippiAdd_32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Add(
		const QVImage<sFloat, 3> & qvimage_pSrc1,
		const QVImage<sFloat, 3> & qvimage_pSrc2,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAddC_8u_C1RSfs

This is the QVision wrapper function for IPP's <b>ippiAddC_8u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AddC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAddC_8u_C3RSfs

This is the QVision wrapper function for IPP's <b>ippiAddC_8u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AddC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAddC_16u_C1RSfs

This is the QVision wrapper function for IPP's <b>ippiAddC_16u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AddC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAddC_16u_C3RSfs

This is the QVision wrapper function for IPP's <b>ippiAddC_16u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AddC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAddC_16s_C1RSfs

This is the QVision wrapper function for IPP's <b>ippiAddC_16s_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AddC(
		const QVImage<sShort, 1> & qvimage_pSrc,
		const sShort value,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAddC_16s_C3RSfs

This is the QVision wrapper function for IPP's <b>ippiAddC_16s_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AddC(
		const QVImage<sShort, 3> & qvimage_pSrc,
		const  sShort value[3],
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAddC_32f_C1R

This is the QVision wrapper function for IPP's <b>ippiAddC_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AddC(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		const sFloat value,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAddC_32f_C3R

This is the QVision wrapper function for IPP's <b>ippiAddC_32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AddC(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		const  sFloat value[3],
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of two source images and places the results in a destination image

This is the QVision wrapper function for IPP's <b>ippiMul_8u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Mul(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of two source images and places the results in a destination image

This is the QVision wrapper function for IPP's <b>ippiMul_8u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Mul(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of two source images and places the results in a destination image

This is the QVision wrapper function for IPP's <b>ippiMul_16u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Mul(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of two source images and places the results in a destination image

This is the QVision wrapper function for IPP's <b>ippiMul_16u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Mul(
		const QVImage<uShort, 3> & qvimage_pSrc1,
		const QVImage<uShort, 3> & qvimage_pSrc2,
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of two source images and places the results in a destination image

This is the QVision wrapper function for IPP's <b>ippiMul_16s_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Mul(
		const QVImage<sShort, 1> & qvimage_pSrc1,
		const QVImage<sShort, 1> & qvimage_pSrc2,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of two source images and places the results in a destination image

This is the QVision wrapper function for IPP's <b>ippiMul_16s_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Mul(
		const QVImage<sShort, 3> & qvimage_pSrc1,
		const QVImage<sShort, 3> & qvimage_pSrc2,
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of two source images and places the results in a destination image

This is the QVision wrapper function for IPP's <b>ippiMul_32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Mul(
		const QVImage<sFloat, 3> & qvimage_pSrc1,
		const QVImage<sFloat, 3> & qvimage_pSrc2,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of two source images and places the results in a destination image

This is the QVision wrapper function for IPP's <b>ippiMul_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Mul(
		const QVImage<sFloat, 1> & qvimage_pSrc1,
		const QVImage<sFloat, 1> & qvimage_pSrc2,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of an image and a constant, and places the results in the same image

This is the QVision wrapper function for IPP's <b>ippiMulC_8u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void MulC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of an image and a constant, and places the results in the same image

This is the QVision wrapper function for IPP's <b>ippiMulC_8u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void MulC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of an image and a constant, and places the results in the same image

This is the QVision wrapper function for IPP's <b>ippiMulC_16u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void MulC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of an image and a constant, and places the results in the same image

This is the QVision wrapper function for IPP's <b>ippiMulC_16u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void MulC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of an image and a constant, and places the results in the same image

This is the QVision wrapper function for IPP's <b>ippiMulC_16s_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void MulC(
		const QVImage<sShort, 1> & qvimage_pSrc,
		const sShort value,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of an image and a constant, and places the results in the same image

This is the QVision wrapper function for IPP's <b>ippiMulC_16s_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void MulC(
		const QVImage<sShort, 3> & qvimage_pSrc,
		const  sShort value[3],
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of an image and a constant, and places the results in the same image

This is the QVision wrapper function for IPP's <b>ippiMulC_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void MulC(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		const sFloat value,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Adds, subtracts, or multiplies pixel values of an image and a constant, and places the results in the same image

This is the QVision wrapper function for IPP's <b>ippiMulC_32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void MulC(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		const  sFloat value[3],
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiMulScale_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiMulScale_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void MulScale(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiMulScale_8u_C3R

This is the QVision wrapper function for IPP's <b>ippiMulScale_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void MulScale(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSub_8u_C1RSfs

This is the QVision wrapper function for IPP's <b>ippiSub_8u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Sub(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSub_8u_C3RSfs

This is the QVision wrapper function for IPP's <b>ippiSub_8u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Sub(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSub_16u_C1RSfs

This is the QVision wrapper function for IPP's <b>ippiSub_16u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Sub(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSub_16u_C3RSfs

This is the QVision wrapper function for IPP's <b>ippiSub_16u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Sub(
		const QVImage<uShort, 3> & qvimage_pSrc1,
		const QVImage<uShort, 3> & qvimage_pSrc2,
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSub_16s_C1RSfs

This is the QVision wrapper function for IPP's <b>ippiSub_16s_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Sub(
		const QVImage<sShort, 1> & qvimage_pSrc1,
		const QVImage<sShort, 1> & qvimage_pSrc2,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSub_16s_C3RSfs

This is the QVision wrapper function for IPP's <b>ippiSub_16s_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Sub(
		const QVImage<sShort, 3> & qvimage_pSrc1,
		const QVImage<sShort, 3> & qvimage_pSrc2,
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSub_32f_C1R

This is the QVision wrapper function for IPP's <b>ippiSub_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Sub(
		const QVImage<sFloat, 1> & qvimage_pSrc1,
		const QVImage<sFloat, 1> & qvimage_pSrc2,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSub_32f_C3R

This is the QVision wrapper function for IPP's <b>ippiSub_32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Sub(
		const QVImage<sFloat, 3> & qvimage_pSrc1,
		const QVImage<sFloat, 3> & qvimage_pSrc2,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSubC_8u_C1RSfs

This is the QVision wrapper function for IPP's <b>ippiSubC_8u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void SubC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSubC_8u_C3RSfs

This is the QVision wrapper function for IPP's <b>ippiSubC_8u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void SubC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSubC_16u_C1RSfs

This is the QVision wrapper function for IPP's <b>ippiSubC_16u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void SubC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSubC_16s_C1RSfs

This is the QVision wrapper function for IPP's <b>ippiSubC_16s_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void SubC(
		const QVImage<sShort, 1> & qvimage_pSrc,
		const sShort value,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSubC_16u_C3RSfs

This is the QVision wrapper function for IPP's <b>ippiSubC_16u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void SubC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSubC_16s_C3RSfs

This is the QVision wrapper function for IPP's <b>ippiSubC_16s_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void SubC(
		const QVImage<sShort, 3> & qvimage_pSrc,
		const  sShort value[3],
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSubC_32f_C1R

This is the QVision wrapper function for IPP's <b>ippiSubC_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void SubC(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		const sFloat value,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiSubC_32f_C3R

This is the QVision wrapper function for IPP's <b>ippiSubC_32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void SubC(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		const  sFloat value[3],
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of an image by pixel values of another image and places the scaled results in the dividend source image

This is the QVision wrapper function for IPP's <b>ippiDiv_8u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Div(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of an image by pixel values of another image and places the scaled results in the dividend source image

This is the QVision wrapper function for IPP's <b>ippiDiv_8u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Div(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of an image by pixel values of another image and places the scaled results in the dividend source image

This is the QVision wrapper function for IPP's <b>ippiDiv_16u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Div(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of an image by pixel values of another image and places the scaled results in the dividend source image

This is the QVision wrapper function for IPP's <b>ippiDiv_16u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Div(
		const QVImage<uShort, 3> & qvimage_pSrc1,
		const QVImage<uShort, 3> & qvimage_pSrc2,
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of an image by pixel values of another image and places the scaled results in the dividend source image

This is the QVision wrapper function for IPP's <b>ippiDiv_16s_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Div(
		const QVImage<sShort, 1> & qvimage_pSrc1,
		const QVImage<sShort, 1> & qvimage_pSrc2,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of an image by pixel values of another image and places the scaled results in the dividend source image

This is the QVision wrapper function for IPP's <b>ippiDiv_16s_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Div(
		const QVImage<sShort, 3> & qvimage_pSrc1,
		const QVImage<sShort, 3> & qvimage_pSrc2,
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of an image by pixel values of another image and places the scaled results in the dividend source image

This is the QVision wrapper function for IPP's <b>ippiDiv_32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Div(
		const QVImage<sFloat, 3> & qvimage_pSrc1,
		const QVImage<sFloat, 3> & qvimage_pSrc2,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of an image by pixel values of another image and places the scaled results in the dividend source image

This is the QVision wrapper function for IPP's <b>ippiDiv_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Div(
		const QVImage<sFloat, 1> & qvimage_pSrc1,
		const QVImage<sFloat, 1> & qvimage_pSrc2,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of a source image by a constant and places the scaled results in the same image

This is the QVision wrapper function for IPP's <b>ippiDivC_8u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void DivC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of a source image by a constant and places the scaled results in the same image

This is the QVision wrapper function for IPP's <b>ippiDivC_8u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void DivC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of a source image by a constant and places the scaled results in the same image

This is the QVision wrapper function for IPP's <b>ippiDivC_16u_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void DivC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of a source image by a constant and places the scaled results in the same image

This is the QVision wrapper function for IPP's <b>ippiDivC_16u_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void DivC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of a source image by a constant and places the scaled results in the same image

This is the QVision wrapper function for IPP's <b>ippiDivC_16s_C1RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void DivC(
		const QVImage<sShort, 1> & qvimage_pSrc,
		const sShort value,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of a source image by a constant and places the scaled results in the same image

This is the QVision wrapper function for IPP's <b>ippiDivC_16s_C3RSfs</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void DivC(
		const QVImage<sShort, 3> & qvimage_pSrc,
		const  sShort value[3],
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor = 1,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of a source image by a constant and places the scaled results in the same image

This is the QVision wrapper function for IPP's <b>ippiDivC_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void DivC(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		const sFloat value,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Divides pixel values of a source image by a constant and places the scaled results in the same image

This is the QVision wrapper function for IPP's <b>ippiDivC_32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void DivC(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		const  sFloat value[3],
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Computes absolute value of each pixel of a source image and places results in the destination image; for in-place flavors - in the same source image

This is the QVision wrapper function for IPP's <b>ippiAbs_16s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Abs(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Computes absolute value of each pixel of a source image and places results in the destination image; for in-place flavors - in the same source image

This is the QVision wrapper function for IPP's <b>ippiAbs_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Abs(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Calculate absolute difference between corresponding pixels of the two images or between image pixels and scalar

This is the QVision wrapper function for IPP's <b>ippiAbsDiff_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AbsDiff(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Calculate absolute difference between corresponding pixels of the two images or between image pixels and scalar

This is the QVision wrapper function for IPP's <b>ippiAbsDiff_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AbsDiff(
		const QVImage<sFloat, 1> & qvimage_pSrc1,
		const QVImage<sFloat, 1> & qvimage_pSrc2,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Squares pixel values of an image and places results in the destination image; for in-place flavors - in the same image

This is the QVision wrapper function for IPP's <b>ippiSqr_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Sqr(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Computes the natural logarithm of each pixel values of a source image and places the results in the destination image; for in-place flavors - in the same image

This is the QVision wrapper function for IPP's <b>ippiLn_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Ln(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Computes the natural logarithm of each pixel values of a source image and places the results in the destination image; for in-place flavors - in the same image

This is the QVision wrapper function for IPP's <b>ippiLn_32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Ln(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAnd_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiAnd_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void And(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAnd_8u_C3R

This is the QVision wrapper function for IPP's <b>ippiAnd_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void And(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAnd_16u_C1R

This is the QVision wrapper function for IPP's <b>ippiAnd_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void And(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAnd_16u_C3R

This is the QVision wrapper function for IPP's <b>ippiAnd_16u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void And(
		const QVImage<uShort, 3> & qvimage_pSrc1,
		const QVImage<uShort, 3> & qvimage_pSrc2,
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAnd_32s_C1R

This is the QVision wrapper function for IPP's <b>ippiAnd_32s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void And(
		const QVImage<sInt, 1> & qvimage_pSrc1,
		const QVImage<sInt, 1> & qvimage_pSrc2,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAnd_32s_C3R

This is the QVision wrapper function for IPP's <b>ippiAnd_32s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void And(
		const QVImage<sInt, 3> & qvimage_pSrc1,
		const QVImage<sInt, 3> & qvimage_pSrc2,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiOr_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiOr_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Or(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiOr_8u_C3R

This is the QVision wrapper function for IPP's <b>ippiOr_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Or(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiOr_16u_C1R

This is the QVision wrapper function for IPP's <b>ippiOr_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Or(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiOr_16u_C3R

This is the QVision wrapper function for IPP's <b>ippiOr_16u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Or(
		const QVImage<uShort, 3> & qvimage_pSrc1,
		const QVImage<uShort, 3> & qvimage_pSrc2,
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiOr_32s_C1R

This is the QVision wrapper function for IPP's <b>ippiOr_32s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Or(
		const QVImage<sInt, 1> & qvimage_pSrc1,
		const QVImage<sInt, 1> & qvimage_pSrc2,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiOr_32s_C3R

This is the QVision wrapper function for IPP's <b>ippiOr_32s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Or(
		const QVImage<sInt, 3> & qvimage_pSrc1,
		const QVImage<sInt, 3> & qvimage_pSrc2,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiXor_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiXor_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Xor(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiXor_8u_C3R

This is the QVision wrapper function for IPP's <b>ippiXor_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Xor(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiXor_16u_C1R

This is the QVision wrapper function for IPP's <b>ippiXor_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Xor(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiXor_16u_C3R

This is the QVision wrapper function for IPP's <b>ippiXor_16u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Xor(
		const QVImage<uShort, 3> & qvimage_pSrc1,
		const QVImage<uShort, 3> & qvimage_pSrc2,
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiXor_32s_C1R

This is the QVision wrapper function for IPP's <b>ippiXor_32s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Xor(
		const QVImage<sInt, 1> & qvimage_pSrc1,
		const QVImage<sInt, 1> & qvimage_pSrc2,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiXor_32s_C3R

This is the QVision wrapper function for IPP's <b>ippiXor_32s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Xor(
		const QVImage<sInt, 3> & qvimage_pSrc1,
		const QVImage<sInt, 3> & qvimage_pSrc2,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs corresponding bitwise logical operation between pixels of two image (AndC OrC XorC - between pixel of the source image and a constant)

This is the QVision wrapper function for IPP's <b>ippiNot_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Not(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs corresponding bitwise logical operation between pixels of two image (AndC OrC XorC - between pixel of the source image and a constant)

This is the QVision wrapper function for IPP's <b>ippiNot_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void Not(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAndC_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiAndC_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AndC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAndC_8u_C3R

This is the QVision wrapper function for IPP's <b>ippiAndC_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AndC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAndC_16u_C1R

This is the QVision wrapper function for IPP's <b>ippiAndC_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AndC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAndC_16u_C3R

This is the QVision wrapper function for IPP's <b>ippiAndC_16u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AndC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAndC_32s_C1R

This is the QVision wrapper function for IPP's <b>ippiAndC_32s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AndC(
		const QVImage<sInt, 1> & qvimage_pSrc,
		const sInt value,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiAndC_32s_C3R

This is the QVision wrapper function for IPP's <b>ippiAndC_32s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void AndC(
		const QVImage<sInt, 3> & qvimage_pSrc,
		const  sInt value[3],
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiOrC_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiOrC_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void OrC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiOrC_8u_C3R

This is the QVision wrapper function for IPP's <b>ippiOrC_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void OrC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiOrC_16u_C1R

This is the QVision wrapper function for IPP's <b>ippiOrC_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void OrC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiOrC_16u_C3R

This is the QVision wrapper function for IPP's <b>ippiOrC_16u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void OrC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiOrC_32s_C1R

This is the QVision wrapper function for IPP's <b>ippiOrC_32s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void OrC(
		const QVImage<sInt, 1> & qvimage_pSrc,
		const sInt value,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiOrC_32s_C3R

This is the QVision wrapper function for IPP's <b>ippiOrC_32s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void OrC(
		const QVImage<sInt, 3> & qvimage_pSrc,
		const  sInt value[3],
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiXorC_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiXorC_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void XorC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiXorC_8u_C3R

This is the QVision wrapper function for IPP's <b>ippiXorC_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void XorC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiXorC_16u_C1R

This is the QVision wrapper function for IPP's <b>ippiXorC_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void XorC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiXorC_16u_C3R

This is the QVision wrapper function for IPP's <b>ippiXorC_16u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void XorC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiXorC_32s_C1R

This is the QVision wrapper function for IPP's <b>ippiXorC_32s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void XorC(
		const QVImage<sInt, 1> & qvimage_pSrc,
		const sInt value,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiXorC_32s_C3R

This is the QVision wrapper function for IPP's <b>ippiXorC_32s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void XorC(
		const QVImage<sInt, 3> & qvimage_pSrc,
		const  sInt value[3],
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiLShiftC_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiLShiftC_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void LShiftC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uInt value,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiLShiftC_8u_C3R

This is the QVision wrapper function for IPP's <b>ippiLShiftC_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void LShiftC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uInt value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiRShiftC_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiRShiftC_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void RShiftC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uInt value,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiRShiftC_8u_C3R

This is the QVision wrapper function for IPP's <b>ippiRShiftC_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void RShiftC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uInt value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiLShiftC_16u_C1R

This is the QVision wrapper function for IPP's <b>ippiLShiftC_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void LShiftC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uInt value,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiLShiftC_16u_C3R

This is the QVision wrapper function for IPP's <b>ippiLShiftC_16u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void LShiftC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uInt value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiRShiftC_16u_C1R

This is the QVision wrapper function for IPP's <b>ippiRShiftC_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void RShiftC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uInt value,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiRShiftC_16u_C3R

This is the QVision wrapper function for IPP's <b>ippiRShiftC_16u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void RShiftC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uInt value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiLShiftC_32s_C1R

This is the QVision wrapper function for IPP's <b>ippiLShiftC_32s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void LShiftC(
		const QVImage<sInt, 1> & qvimage_pSrc,
		const uInt value,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiLShiftC_32s_C3R

This is the QVision wrapper function for IPP's <b>ippiLShiftC_32s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void LShiftC(
		const QVImage<sInt, 3> & qvimage_pSrc,
		const  uInt value[3],
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiRShiftC_32s_C1R

This is the QVision wrapper function for IPP's <b>ippiRShiftC_32s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void RShiftC(
		const QVImage<sInt, 1> & qvimage_pSrc,
		const uInt value,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiRShiftC_32s_C3R

This is the QVision wrapper function for IPP's <b>ippiRShiftC_32s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippIAALO
*/
void RShiftC(
		const QVImage<sInt, 3> & qvimage_pSrc,
		const  uInt value[3],
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts an RGB image to gray scale (fixed coefficients)

This is the QVision wrapper function for IPP's <b>ippiRGBToGray_8u_C3C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippICC
*/
void RGBToGray(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts an RGB image to gray scale (fixed coefficients)

This is the QVision wrapper function for IPP's <b>ippiRGBToGray_16u_C3C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippICC
*/
void RGBToGray(
		const QVImage<uShort, 3> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts an RGB image to gray scale (fixed coefficients)

This is the QVision wrapper function for IPP's <b>ippiRGBToGray_16s_C3C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippICC
*/
void RGBToGray(
		const QVImage<sShort, 3> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Converts an RGB image to gray scale (fixed coefficients)

This is the QVision wrapper function for IPP's <b>ippiRGBToGray_32f_C3C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippICC
*/
void RGBToGray(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs thresholding of an image using the specified level

This is the QVision wrapper function for IPP's <b>ippiThreshold_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param threshold	Corresponds to the same parameter of type IppiSize in the IPP function.
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippTACO
*/
void Threshold(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const uChar threshold,
		const IppCmpOp ippCmpOp = ippCmpEq,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs thresholding of an image using the specified level

This is the QVision wrapper function for IPP's <b>ippiThreshold_8u_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param threshold	Corresponds to the same parameter of type IppiSize in the IPP function.
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.

@ingroup qvippTACO
*/
void Threshold(
		QVImage<uChar, 1> & qvimage_pSrcDst,
		const uChar threshold,
		const IppCmpOp ippCmpOp = ippCmpEq);

/*!
@brief Performs thresholding of an image using the specified level

This is the QVision wrapper function for IPP's <b>ippiThreshold_16s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param threshold	Corresponds to the same parameter of type IppiSize in the IPP function.
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippTACO
*/
void Threshold(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const sShort threshold,
		const IppCmpOp ippCmpOp = ippCmpEq,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs thresholding of an image using the specified level

This is the QVision wrapper function for IPP's <b>ippiThreshold_16s_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param threshold	Corresponds to the same parameter of type IppiSize in the IPP function.
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.

@ingroup qvippTACO
*/
void Threshold(
		QVImage<sShort, 1> & qvimage_pSrcDst,
		const sShort threshold,
		const IppCmpOp ippCmpOp = ippCmpEq);

/*!
@brief Performs thresholding of an image using the specified level

This is the QVision wrapper function for IPP's <b>ippiThreshold_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param threshold	Corresponds to the same parameter of type IppiSize in the IPP function.
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippTACO
*/
void Threshold(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const sFloat threshold,
		const IppCmpOp ippCmpOp = ippCmpEq,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs thresholding of an image using the specified level

This is the QVision wrapper function for IPP's <b>ippiThreshold_32f_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param threshold	Corresponds to the same parameter of type IppiSize in the IPP function.
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.

@ingroup qvippTACO
*/
void Threshold(
		QVImage<sFloat, 1> & qvimage_pSrcDst,
		const sFloat threshold,
		const IppCmpOp ippCmpOp = ippCmpEq);

/*!
@brief Performs thresholding of pixel values

This is the QVision wrapper function for IPP's <b>ippiThreshold_Val_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param threshold	Corresponds to the same parameter of type IppiSize in the IPP function.
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippTACO
*/
void Threshold_Val(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const uChar threshold,
		const uChar value,
		const IppCmpOp ippCmpOp = ippCmpEq,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs thresholding of pixel values

This is the QVision wrapper function for IPP's <b>ippiThreshold_Val_8u_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param threshold	Corresponds to the same parameter of type IppiSize in the IPP function.
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.

@ingroup qvippTACO
*/
void Threshold_Val(
		QVImage<uChar, 1> & qvimage_pSrcDst,
		const uChar threshold,
		const uChar value,
		const IppCmpOp ippCmpOp = ippCmpEq);

/*!
@brief Performs thresholding of pixel values

This is the QVision wrapper function for IPP's <b>ippiThreshold_Val_16s_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param threshold	Corresponds to the same parameter of type IppiSize in the IPP function.
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.

@ingroup qvippTACO
*/
void Threshold_Val(
		QVImage<sShort, 1> & qvimage_pSrcDst,
		const sShort threshold,
		const sShort value,
		const IppCmpOp ippCmpOp = ippCmpEq);

/*!
@brief Performs thresholding of pixel values

This is the QVision wrapper function for IPP's <b>ippiThreshold_Val_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param threshold	Corresponds to the same parameter of type IppiSize in the IPP function.
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippTACO
*/
void Threshold_Val(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const sFloat threshold,
		const sFloat value,
		const IppCmpOp ippCmpOp = ippCmpEq,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs thresholding of pixel values

This is the QVision wrapper function for IPP's <b>ippiThreshold_Val_32f_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param threshold	Corresponds to the same parameter of type IppiSize in the IPP function.
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.

@ingroup qvippTACO
*/
void Threshold_Val(
		QVImage<sFloat, 1> & qvimage_pSrcDst,
		const sFloat threshold,
		const sFloat value,
		const IppCmpOp ippCmpOp = ippCmpEq);

/*!
@brief Performs double thresholding of pixel values

This is the QVision wrapper function for IPP's <b>ippiThreshold_LTValGTVal_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param thresholdLT	Corresponds to the same parameter of type IppiSize in the IPP function.
@param valueLT	Corresponds to the same parameter of type IppiSize in the IPP function.
@param thresholdGT	Corresponds to the same parameter of type IppiSize in the IPP function.
@param valueGT	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippTACO
*/
void Threshold_LTValGTVal(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const uChar thresholdLT,
		const uChar valueLT,
		const uChar thresholdGT,
		const uChar valueGT,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs double thresholding of pixel values

This is the QVision wrapper function for IPP's <b>ippiThreshold_LTValGTVal_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param thresholdLT	Corresponds to the same parameter of type IppiSize in the IPP function.
@param valueLT	Corresponds to the same parameter of type IppiSize in the IPP function.
@param thresholdGT	Corresponds to the same parameter of type IppiSize in the IPP function.
@param valueGT	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippTACO
*/
void Threshold_LTValGTVal(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const sFloat thresholdLT,
		const sFloat valueLT,
		const sFloat thresholdGT,
		const sFloat valueGT,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Calculate Otsu theshold value of images

This is the QVision wrapper function for IPP's <b>ippiComputeThreshold_Otsu_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pThreshold	Corresponds to the same parameter in the IPP function.

@ingroup qvippTACO
*/
void ComputeThreshold_Otsu(
		const QVImage<uChar, 1> & qvimage_pSrc,
		 uChar & pThreshold);

/*!
@brief QVision wrapper function for IPP's ippiCompare_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiCompare_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippTACO
*/
void Compare(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppCmpOp ippCmpOp = ippCmpEq,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiCompare_16u_C1R

This is the QVision wrapper function for IPP's <b>ippiCompare_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippTACO
*/
void Compare(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppCmpOp ippCmpOp = ippCmpEq,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiCompare_16s_C1R

This is the QVision wrapper function for IPP's <b>ippiCompare_16s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippTACO
*/
void Compare(
		const QVImage<sShort, 1> & qvimage_pSrc1,
		const QVImage<sShort, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppCmpOp ippCmpOp = ippCmpEq,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiCompare_32f_C1R

This is the QVision wrapper function for IPP's <b>ippiCompare_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippTACO
*/
void Compare(
		const QVImage<sFloat, 1> & qvimage_pSrc1,
		const QVImage<sFloat, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppCmpOp ippCmpOp = ippCmpEq,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Compares pixel values of two images, or pixel values of an image to a constant value using the following compare conditions

This is the QVision wrapper function for IPP's <b>ippiCompareC_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippTACO
*/
void CompareC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppCmpOp ippCmpOp = ippCmpEq,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Compares pixel values of two images, or pixel values of an image to a constant value using the following compare conditions

This is the QVision wrapper function for IPP's <b>ippiCompareC_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippTACO
*/
void CompareC(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		const sFloat value,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppCmpOp ippCmpOp = ippCmpEq,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs in-place erosion dilation using an arbitrary mask

This is the QVision wrapper function for IPP's <b>ippiDilate_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param pMask	Corresponds to the same parameter in the IPP function.
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippMO
*/
void Dilate(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs in-place erosion dilation using an arbitrary mask

This is the QVision wrapper function for IPP's <b>ippiDilate_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param pMask	Corresponds to the same parameter in the IPP function.
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippMO
*/
void Dilate(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs in-place erosion dilation using an arbitrary mask

This is the QVision wrapper function for IPP's <b>ippiDilate_8u_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param pMask	Corresponds to the same parameter in the IPP function.
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.

@ingroup qvippMO
*/
void Dilate(
		QVImage<uChar, 1> & qvimage_pSrcDst,
		 const uChar & pMask,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0));

/*!
@brief Performs in-place erosion dilation using an arbitrary mask

This is the QVision wrapper function for IPP's <b>ippiDilate_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param pMask	Corresponds to the same parameter in the IPP function.
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippMO
*/
void Dilate(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs in-place erosion dilation using an arbitrary mask

This is the QVision wrapper function for IPP's <b>ippiDilate_16u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param pMask	Corresponds to the same parameter in the IPP function.
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippMO
*/
void Dilate(
		const QVImage<uShort, 3> & qvimage_pSrc,
		QVImage<uShort, 3> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs in-place erosion dilation using an arbitrary mask

This is the QVision wrapper function for IPP's <b>ippiDilate_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param pMask	Corresponds to the same parameter in the IPP function.
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippMO
*/
void Dilate(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs in-place erosion dilation using an arbitrary mask

This is the QVision wrapper function for IPP's <b>ippiDilate_32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param pMask	Corresponds to the same parameter in the IPP function.
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippMO
*/
void Dilate(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiErode_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiErode_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param pMask	Corresponds to the same parameter in the IPP function.
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippMO
*/
void Erode(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiErode_8u_C3R

This is the QVision wrapper function for IPP's <b>ippiErode_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param pMask	Corresponds to the same parameter in the IPP function.
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippMO
*/
void Erode(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiErode_8u_C1IR

This is the QVision wrapper function for IPP's <b>ippiErode_8u_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param pMask	Corresponds to the same parameter in the IPP function.
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.

@ingroup qvippMO
*/
void Erode(
		QVImage<uChar, 1> & qvimage_pSrcDst,
		 const uChar & pMask,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiErode_16u_C1R

This is the QVision wrapper function for IPP's <b>ippiErode_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param pMask	Corresponds to the same parameter in the IPP function.
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippMO
*/
void Erode(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiErode_16u_C3R

This is the QVision wrapper function for IPP's <b>ippiErode_16u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param pMask	Corresponds to the same parameter in the IPP function.
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippMO
*/
void Erode(
		const QVImage<uShort, 3> & qvimage_pSrc,
		QVImage<uShort, 3> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiErode_32f_C1R

This is the QVision wrapper function for IPP's <b>ippiErode_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param pMask	Corresponds to the same parameter in the IPP function.
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippMO
*/
void Erode(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiErode_32f_C3R

This is the QVision wrapper function for IPP's <b>ippiErode_32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param pMask	Corresponds to the same parameter in the IPP function.
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippMO
*/
void Erode(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterBox_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiFilterBox_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterBox(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterBox_8u_C3R

This is the QVision wrapper function for IPP's <b>ippiFilterBox_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterBox(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterBox_16u_C1R

This is the QVision wrapper function for IPP's <b>ippiFilterBox_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterBox(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterBox_32f_C1R

This is the QVision wrapper function for IPP's <b>ippiFilterBox_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterBox(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Applies the "min" filter to an image

This is the QVision wrapper function for IPP's <b>ippiFilterMin_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMin(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Applies the "min" filter to an image

This is the QVision wrapper function for IPP's <b>ippiFilterMin_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMin(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Applies the "min" filter to an image

This is the QVision wrapper function for IPP's <b>ippiFilterMin_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMin(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Applies the "min" filter to an image

This is the QVision wrapper function for IPP's <b>ippiFilterMin_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMin(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Applies the "max" filter to an image

This is the QVision wrapper function for IPP's <b>ippiFilterMax_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMax(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Applies the "max" filter to an image

This is the QVision wrapper function for IPP's <b>ippiFilterMax_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMax(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Applies the "max" filter to an image

This is the QVision wrapper function for IPP's <b>ippiFilterMax_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMax(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Applies the "max" filter to an image

This is the QVision wrapper function for IPP's <b>ippiFilterMax_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMax(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Filters an image using a box median filter

This is the QVision wrapper function for IPP's <b>ippiFilterMedian_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMedian(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Filters an image using a box median filter

This is the QVision wrapper function for IPP's <b>ippiFilterMedian_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMedian(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Filters an image using a box median filter

This is the QVision wrapper function for IPP's <b>ippiFilterMedian_16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMedian(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QSize &maskSize = QSize(3,3),
		const QPoint &anchor = QPoint(0,0),
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs horizontal median filtering

This is the QVision wrapper function for IPP's <b>ippiFilterMedianHoriz_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMedianHoriz(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Performs vertical median filtering

This is the QVision wrapper function for IPP's <b>ippiFilterMedianVert_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMedianVert(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Filters an image using a cross median filter

This is the QVision wrapper function for IPP's <b>ippiFilterMedianCross_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMedianCross(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Filter an image using a median filter with kernel size 3x3 and enlarged weight of central pixel

This is the QVision wrapper function for IPP's <b>ippiFilterMedianWeightedCenter3x3_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param weight	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMedianWeightedCenter3x3(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const int weight,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Filters an image using a box color median filter

This is the QVision wrapper function for IPP's <b>ippiFilterMedianColor_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterMedianColor(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterSobelHorizMask_32f_C1R

This is the QVision wrapper function for IPP's <b>ippiFilterSobelHorizMask_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterSobelHorizMask(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterSobelVertMask_32f_C1R

This is the QVision wrapper function for IPP's <b>ippiFilterSobelVertMask_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterSobelVertMask(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterLaplace_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiFilterLaplace_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterLaplace(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterLaplace_16s_C1R

This is the QVision wrapper function for IPP's <b>ippiFilterLaplace_16s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterLaplace(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterLaplace_32f_C1R

This is the QVision wrapper function for IPP's <b>ippiFilterLaplace_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterLaplace(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterGauss_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiFilterGauss_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterGauss(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterGauss_32f_C1R

This is the QVision wrapper function for IPP's <b>ippiFilterGauss_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterGauss(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterGauss_8u_C3R

This is the QVision wrapper function for IPP's <b>ippiFilterGauss_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterGauss(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterGauss_32f_C3R

This is the QVision wrapper function for IPP's <b>ippiFilterGauss_32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterGauss(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterHipass_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiFilterHipass_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterHipass(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterHipass_8u_C3R

This is the QVision wrapper function for IPP's <b>ippiFilterHipass_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterHipass(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterHipass_32f_C1R

This is the QVision wrapper function for IPP's <b>ippiFilterHipass_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterHipass(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterHipass_32f_C3R

This is the QVision wrapper function for IPP's <b>ippiFilterHipass_32f_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterHipass(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterLowpass_8u_C1R

This is the QVision wrapper function for IPP's <b>ippiFilterLowpass_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterLowpass(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiFilterLowpass_32f_C1R

This is the QVision wrapper function for IPP's <b>ippiFilterLowpass_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippFF
*/
void FilterLowpass(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const IppiMaskSize mask = ippMskSize3x3,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Computes the sum of image pixel values

This is the QVision wrapper function for IPP's <b>ippiSum_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pSum	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Sum(
		const QVImage<uChar, 1> & qvimage_pSrc,
		 sDouble & pSum);

/*!
@brief Computes the sum of image pixel values

This is the QVision wrapper function for IPP's <b>ippiSum_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param sum	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Sum(
		const QVImage<uChar, 3> & qvimage_pSrc,
		sDouble sum[3]);

/*!
@brief Computes the sum of image pixel values

This is the QVision wrapper function for IPP's <b>ippiSum_16s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pSum	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Sum(
		const QVImage<sShort, 1> & qvimage_pSrc,
		 sDouble & pSum);

/*!
@brief Computes the sum of image pixel values

This is the QVision wrapper function for IPP's <b>ippiSum_16s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param sum	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Sum(
		const QVImage<sShort, 3> & qvimage_pSrc,
		sDouble sum[3]);

/*!
@brief QVision wrapper function for IPP's ippiIntegral_8u32s_C1R

This is the QVision wrapper function for IPP's <b>ippiIntegral_8u32s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param val	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippISF
*/
void Integral(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sInt, 1> & qvimage_pDst,
		const sInt val,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiIntegral_8u32f_C1R

This is the QVision wrapper function for IPP's <b>ippiIntegral_8u32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param val	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippISF
*/
void Integral(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const sFloat val,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Computes the mean of image pixel values

This is the QVision wrapper function for IPP's <b>ippiMean_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pMean	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Mean(
		const QVImage<uChar, 1> & qvimage_pSrc,
		 sDouble & pMean);

/*!
@brief Computes the mean of image pixel values

This is the QVision wrapper function for IPP's <b>ippiMean_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param mean	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Mean(
		const QVImage<uChar, 3> & qvimage_pSrc,
		sDouble mean[3]);

/*!
@brief Computes the mean of image pixel values

This is the QVision wrapper function for IPP's <b>ippiMean_16s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pMean	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Mean(
		const QVImage<sShort, 1> & qvimage_pSrc,
		 sDouble & pMean);

/*!
@brief Computes the mean of image pixel values

This is the QVision wrapper function for IPP's <b>ippiMean_16s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param mean	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Mean(
		const QVImage<sShort, 3> & qvimage_pSrc,
		sDouble mean[3]);

/*!
@brief Computes the minimum of image pixel values

This is the QVision wrapper function for IPP's <b>ippiMin_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pMin	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Min(
		const QVImage<uChar, 1> & qvimage_pSrc,
		 uChar & pMin);

/*!
@brief Computes the minimum of image pixel values

This is the QVision wrapper function for IPP's <b>ippiMin_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param min	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Min(
		const QVImage<uChar, 3> & qvimage_pSrc,
		uChar min[3]);

/*!
@brief Computes the minimum of image pixel values

This is the QVision wrapper function for IPP's <b>ippiMin_16s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pMin	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Min(
		const QVImage<sShort, 1> & qvimage_pSrc,
		 sShort & pMin);

/*!
@brief Computes the minimum of image pixel values

This is the QVision wrapper function for IPP's <b>ippiMin_16s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param min	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Min(
		const QVImage<sShort, 3> & qvimage_pSrc,
		sShort min[3]);

/*!
@brief Computes the minimum of image pixel values

This is the QVision wrapper function for IPP's <b>ippiMin_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pMin	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Min(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		 sFloat & pMin);

/*!
@brief Computes the maximum of image pixel values

This is the QVision wrapper function for IPP's <b>ippiMax_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pMax	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Max(
		const QVImage<uChar, 1> & qvimage_pSrc,
		 uChar & pMax);

/*!
@brief Computes the maximum of image pixel values

This is the QVision wrapper function for IPP's <b>ippiMax_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param max	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Max(
		const QVImage<uChar, 3> & qvimage_pSrc,
		uChar max[3]);

/*!
@brief Computes the maximum of image pixel values

This is the QVision wrapper function for IPP's <b>ippiMax_16s_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pMax	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Max(
		const QVImage<sShort, 1> & qvimage_pSrc,
		 sShort & pMax);

/*!
@brief Computes the maximum of image pixel values

This is the QVision wrapper function for IPP's <b>ippiMax_16s_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param max	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Max(
		const QVImage<sShort, 3> & qvimage_pSrc,
		sShort max[3]);

/*!
@brief Computes the maximum of image pixel values

This is the QVision wrapper function for IPP's <b>ippiMax_32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pMax	Corresponds to the same parameter in the IPP function.

@ingroup qvippISF
*/
void Max(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		 sFloat & pMax);

/*!
@brief QVision wrapper function for IPP's ippiMinEvery_8u_C1IR

This is the QVision wrapper function for IPP's <b>ippiMinEvery_8u_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippISF
*/
void MinEvery(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pSrcDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiMinEvery_8u_C3IR

This is the QVision wrapper function for IPP's <b>ippiMinEvery_8u_C3IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippISF
*/
void MinEvery(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pSrcDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiMinEvery_16s_C1IR

This is the QVision wrapper function for IPP's <b>ippiMinEvery_16s_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippISF
*/
void MinEvery(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pSrcDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiMinEvery_16s_C3IR

This is the QVision wrapper function for IPP's <b>ippiMinEvery_16s_C3IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippISF
*/
void MinEvery(
		const QVImage<sShort, 3> & qvimage_pSrc,
		QVImage<sShort, 3> & qvimage_pSrcDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiMinEvery_32f_C1IR

This is the QVision wrapper function for IPP's <b>ippiMinEvery_32f_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippISF
*/
void MinEvery(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pSrcDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Calculation min max value for every element of two images

This is the QVision wrapper function for IPP's <b>ippiMaxEvery_8u_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippISF
*/
void MaxEvery(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pSrcDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Calculation min max value for every element of two images

This is the QVision wrapper function for IPP's <b>ippiMaxEvery_8u_C3IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippISF
*/
void MaxEvery(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pSrcDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Calculation min max value for every element of two images

This is the QVision wrapper function for IPP's <b>ippiMaxEvery_16s_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippISF
*/
void MaxEvery(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pSrcDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Calculation min max value for every element of two images

This is the QVision wrapper function for IPP's <b>ippiMaxEvery_16s_C3IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippISF
*/
void MaxEvery(
		const QVImage<sShort, 3> & qvimage_pSrc,
		QVImage<sShort, 3> & qvimage_pSrcDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Calculation min max value for every element of two images

This is the QVision wrapper function for IPP's <b>ippiMaxEvery_32f_C1IR</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pSrcDst	Image corresponding to the data buffer pointer <i>pSrcDst</i> and step number <i>srcDstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippISF
*/
void MaxEvery(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pSrcDst,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Creates binary image of source's image edges, using derivatives of the first order

This is the QVision wrapper function for IPP's <b>ippiCanny_16s8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDx	Image corresponding to the data buffer pointer <i>pSrcDx</i> and step number <i>srcDxStep</i> variables in the IPP function
@param qvimage_pSrcDy	Image corresponding to the data buffer pointer <i>pSrcDy</i> and step number <i>srcDyStep</i> variables in the IPP function
@param qvimage_pDstEdges	Image corresponding to the data buffer pointer <i>pDstEdges</i> and step number <i>dstEdgeStep</i> variables in the IPP function
@param lowThresh	Corresponds to the same parameter of type IppiSize in the IPP function.
@param highThresh	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pBuffer	Data buffer image, corresponding to parameter named <i>pBuffer</i> from the original IPP function

@ingroup qvippCV
*/
void Canny(
		QVImage<sShort, 1> & qvimage_pSrcDx,
		QVImage<sShort, 1> & qvimage_pSrcDy,
		QVImage<uChar, 1> & qvimage_pDstEdges,
		const sFloat lowThresh,
		const sFloat highThresh,
		QVImage<uChar, 1> & qvimage_pBuffer);

/*!
@brief Creates binary image of source's image edges, using derivatives of the first order

This is the QVision wrapper function for IPP's <b>ippiCanny_32f8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrcDx	Image corresponding to the data buffer pointer <i>pSrcDx</i> and step number <i>srcDxStep</i> variables in the IPP function
@param qvimage_pSrcDy	Image corresponding to the data buffer pointer <i>pSrcDy</i> and step number <i>srcDyStep</i> variables in the IPP function
@param qvimage_pDstEdges	Image corresponding to the data buffer pointer <i>pDstEdges</i> and step number <i>dstEdgeStep</i> variables in the IPP function
@param lowThresh	Corresponds to the same parameter of type IppiSize in the IPP function.
@param highThresh	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pBuffer	Data buffer image, corresponding to parameter named <i>pBuffer</i> from the original IPP function

@ingroup qvippCV
*/
void Canny(
		QVImage<sFloat, 1> & qvimage_pSrcDx,
		QVImage<sFloat, 1> & qvimage_pSrcDy,
		QVImage<uChar, 1> & qvimage_pDstEdges,
		const sFloat lowThresh,
		const sFloat highThresh,
		QVImage<uChar, 1> & qvimage_pBuffer);

/*!
@brief Calculate minimal eigen value of 2x2 autocorrelation gradient matrix for every pixel

This is the QVision wrapper function for IPP's <b>ippiMinEigenVal_8u32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pMinEigenVal	Image corresponding to the data buffer pointer <i>pMinEigenVal</i> and step number <i>minValStep</i> variables in the IPP function
@param kernType	Corresponds to the same parameter of type IppiSize in the IPP function.
@param apertureSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param avgWindow	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pBuffer	Data buffer image, corresponding to parameter named <i>pBuffer</i> from the original IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippCV
*/
void MinEigenVal(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pMinEigenVal,
		const IppiKernelType kernType,
		const int apertureSize,
		const int avgWindow,
		QVImage<uChar, 1> & qvimage_pBuffer,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief QVision wrapper function for IPP's ippiDistanceTransform_5x5_8u16u_C1R

This is the QVision wrapper function for IPP's <b>ippiDistanceTransform_5x5_8u16u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param pMetrics	Corresponds to the same parameter in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippCV
*/
void DistanceTransform_5x5(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		 sInt & pMetrics,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Calculate distance transform by fast marching method

This is the QVision wrapper function for IPP's <b>ippiFastMarching_8u32f_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param radius	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pBuffer	Data buffer image, corresponding to parameter named <i>pBuffer</i> from the original IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippCV
*/
void FastMarching(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const sFloat radius,
		QVImage<uChar, 1> & qvimage_pBuffer,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Restores damaged image area by direct inpainting

This is the QVision wrapper function for IPP's <b>ippiInpaint_8u_C1R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param pState	Corresponds to the same parameter in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippCV
*/
void Inpaint(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		 IppiInpaintState_8u_C1R & pState,
		const QPoint &destROIOffset = QPoint(0,0));

/*!
@brief Restores damaged image area by direct inpainting

This is the QVision wrapper function for IPP's <b>ippiInpaint_8u_C3R</b>.
See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for a deeper understanding of that function.
The parameters of this wrapper function are the following:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param pState	Corresponds to the same parameter in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippCV
*/
void Inpaint(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		 IppiInpaintState_8u_C1R & pState,
		const QPoint &destROIOffset = QPoint(0,0));

#endif
