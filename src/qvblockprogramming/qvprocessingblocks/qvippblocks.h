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

#include <QMap>
#include <QSize>
#include <QPoint>
#include <QVImage>
#include <QVProcessingBlock>

#include <qvdefines.h>
#include <qvipp.h>

#ifndef QVIPPBLOCKS_H
#define QVIPPBLOCKS_H

/*!
@brief Provides a full list of the names of all IPP blocks

@returns a list of QString objects, corresponding to the names of the IPP blocks
@see newQVIPPBlock
@ingroup qvippblocks
*/
const QMap<QString, QString> getQVIPPBlocksNames();

/*!
@brief Creates an IPP block object, given its class name

This function can be used as a block object factory.
Given the class name of an IPP block included in the QVision framework, this function returns a pointer to a newly created block of that type.

Any QVision application can dynamically obtain the full list of class names of IPP blocks included in the framework with the function @ref getQVIPPBlocksNames.

@param type name of the type of the block
@param name name which will be asigned to the new block object
@returns a pointer to a new block object, or NULL if no ipp block class exists in the QVision
@ingroup qvippblocks
*/
QVPropertyContainer *newQVIPPBlock(QString type, QString name);

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision processing block for the IPP function <b>ippiConvert_8u32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVConvert_uCharsFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVConvert_uCharsFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision processing block for the IPP function <b>ippiConvert_8u32f_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVConvert_uCharsFloatC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVConvert_uCharsFloatC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision processing block for the IPP function <b>ippiConvert_32f8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param roundMode	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVConvert_sFloatuCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVConvert_sFloatuCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Converts pixel values of an image from one bit depth to another

This is the QVision processing block for the IPP function <b>ippiConvert_32f8u_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param roundMode	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVConvert_sFloatuCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVConvert_sFloatuCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Add image to accumulator

This is the QVision processing block for the IPP function <b>ippiAdd_8u_C1RSfs</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAdd_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAdd_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Add image to accumulator

This is the QVision processing block for the IPP function <b>ippiAdd_8u_C3RSfs</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAdd_uCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAdd_uCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Add image to accumulator

This is the QVision processing block for the IPP function <b>ippiAdd_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAdd_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAdd_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Add image to accumulator

This is the QVision processing block for the IPP function <b>ippiAdd_32f_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAdd_sFloatC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAdd_sFloatC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiAddC_8u_C1RSfs

This is the QVision processing block for the IPP function <b>ippiAddC_8u_C1RSfs</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAddC_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAddC_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiAddC_32f_C1R

This is the QVision processing block for the IPP function <b>ippiAddC_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAddC_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAddC_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Adds, subtracts, or multiplies pixel values of two source images and places the results in a destination image

This is the QVision processing block for the IPP function <b>ippiMul_8u_C1RSfs</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVMul_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVMul_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Adds, subtracts, or multiplies pixel values of two source images and places the results in a destination image

This is the QVision processing block for the IPP function <b>ippiMul_8u_C3RSfs</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVMul_uCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVMul_uCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Adds, subtracts, or multiplies pixel values of two source images and places the results in a destination image

This is the QVision processing block for the IPP function <b>ippiMul_32f_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVMul_sFloatC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVMul_sFloatC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Adds, subtracts, or multiplies pixel values of two source images and places the results in a destination image

This is the QVision processing block for the IPP function <b>ippiMul_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVMul_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVMul_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Adds, subtracts, or multiplies pixel values of an image and a constant, and places the results in the same image

This is the QVision processing block for the IPP function <b>ippiMulC_8u_C1RSfs</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVMulC_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVMulC_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Adds, subtracts, or multiplies pixel values of an image and a constant, and places the results in the same image

This is the QVision processing block for the IPP function <b>ippiMulC_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVMulC_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVMulC_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiMulScale_8u_C1R

This is the QVision processing block for the IPP function <b>ippiMulScale_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVMulScale_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVMulScale_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiMulScale_8u_C3R

This is the QVision processing block for the IPP function <b>ippiMulScale_8u_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVMulScale_uCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVMulScale_uCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiSub_8u_C1RSfs

This is the QVision processing block for the IPP function <b>ippiSub_8u_C1RSfs</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVSub_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVSub_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiSub_8u_C3RSfs

This is the QVision processing block for the IPP function <b>ippiSub_8u_C3RSfs</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVSub_uCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVSub_uCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiSub_32f_C1R

This is the QVision processing block for the IPP function <b>ippiSub_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVSub_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVSub_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiSub_32f_C3R

This is the QVision processing block for the IPP function <b>ippiSub_32f_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVSub_sFloatC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVSub_sFloatC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiSubC_8u_C1RSfs

This is the QVision processing block for the IPP function <b>ippiSubC_8u_C1RSfs</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVSubC_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVSubC_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiSubC_32f_C1R

This is the QVision processing block for the IPP function <b>ippiSubC_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVSubC_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVSubC_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Divides pixel values of an image by pixel values of another image and places the scaled results in the dividend source image

This is the QVision processing block for the IPP function <b>ippiDiv_8u_C1RSfs</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVDiv_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVDiv_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Divides pixel values of an image by pixel values of another image and places the scaled results in the dividend source image

This is the QVision processing block for the IPP function <b>ippiDiv_8u_C3RSfs</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVDiv_uCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVDiv_uCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Divides pixel values of an image by pixel values of another image and places the scaled results in the dividend source image

This is the QVision processing block for the IPP function <b>ippiDiv_32f_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVDiv_sFloatC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVDiv_sFloatC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Divides pixel values of an image by pixel values of another image and places the scaled results in the dividend source image

This is the QVision processing block for the IPP function <b>ippiDiv_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVDiv_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVDiv_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Divides pixel values of a source image by a constant and places the scaled results in the same image

This is the QVision processing block for the IPP function <b>ippiDivC_8u_C1RSfs</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param scaleFactor	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVDivC_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVDivC_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Divides pixel values of a source image by a constant and places the scaled results in the same image

This is the QVision processing block for the IPP function <b>ippiDivC_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVDivC_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVDivC_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Computes absolute value of each pixel of a source image and places results in the destination image; for in-place flavors - in the same source image

This is the QVision processing block for the IPP function <b>ippiAbs_16s_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAbs_sShortC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAbs_sShortC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Computes absolute value of each pixel of a source image and places results in the destination image; for in-place flavors - in the same source image

This is the QVision processing block for the IPP function <b>ippiAbs_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAbs_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAbs_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Calculate absolute difference between corresponding pixels of the two images or between image pixels and scalar

This is the QVision processing block for the IPP function <b>ippiAbsDiff_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAbsDiff_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAbsDiff_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Calculate absolute difference between corresponding pixels of the two images or between image pixels and scalar

This is the QVision processing block for the IPP function <b>ippiAbsDiff_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAbsDiff_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAbsDiff_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Squares pixel values of an image and places results in the destination image; for in-place flavors - in the same image

This is the QVision processing block for the IPP function <b>ippiSqr_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVSqr_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVSqr_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Computes the natural logarithm of each pixel values of a source image and places the results in the destination image; for in-place flavors - in the same image

This is the QVision processing block for the IPP function <b>ippiLn_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVLn_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVLn_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Computes the natural logarithm of each pixel values of a source image and places the results in the destination image; for in-place flavors - in the same image

This is the QVision processing block for the IPP function <b>ippiLn_32f_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVLn_sFloatC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVLn_sFloatC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiAnd_8u_C1R

This is the QVision processing block for the IPP function <b>ippiAnd_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAnd_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAnd_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiAnd_8u_C3R

This is the QVision processing block for the IPP function <b>ippiAnd_8u_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAnd_uCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAnd_uCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiAnd_16u_C1R

This is the QVision processing block for the IPP function <b>ippiAnd_16u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAnd_uShortC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAnd_uShortC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiAnd_16u_C3R

This is the QVision processing block for the IPP function <b>ippiAnd_16u_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAnd_uShortC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAnd_uShortC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiAnd_32s_C1R

This is the QVision processing block for the IPP function <b>ippiAnd_32s_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAnd_sIntC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAnd_sIntC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiAnd_32s_C3R

This is the QVision processing block for the IPP function <b>ippiAnd_32s_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAnd_sIntC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAnd_sIntC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiOr_8u_C1R

This is the QVision processing block for the IPP function <b>ippiOr_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVOr_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVOr_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiOr_8u_C3R

This is the QVision processing block for the IPP function <b>ippiOr_8u_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVOr_uCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVOr_uCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiOr_16u_C1R

This is the QVision processing block for the IPP function <b>ippiOr_16u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVOr_uShortC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVOr_uShortC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiOr_16u_C3R

This is the QVision processing block for the IPP function <b>ippiOr_16u_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVOr_uShortC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVOr_uShortC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiOr_32s_C1R

This is the QVision processing block for the IPP function <b>ippiOr_32s_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVOr_sIntC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVOr_sIntC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiOr_32s_C3R

This is the QVision processing block for the IPP function <b>ippiOr_32s_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVOr_sIntC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVOr_sIntC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiXor_8u_C1R

This is the QVision processing block for the IPP function <b>ippiXor_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVXor_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVXor_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiXor_8u_C3R

This is the QVision processing block for the IPP function <b>ippiXor_8u_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVXor_uCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVXor_uCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiXor_16u_C1R

This is the QVision processing block for the IPP function <b>ippiXor_16u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVXor_uShortC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVXor_uShortC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiXor_16u_C3R

This is the QVision processing block for the IPP function <b>ippiXor_16u_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVXor_uShortC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVXor_uShortC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiXor_32s_C1R

This is the QVision processing block for the IPP function <b>ippiXor_32s_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVXor_sIntC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVXor_sIntC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiXor_32s_C3R

This is the QVision processing block for the IPP function <b>ippiXor_32s_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVXor_sIntC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVXor_sIntC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Performs corresponding bitwise logical operation between pixels of two image (AndC OrC XorC - between pixel of the source image and a constant)

This is the QVision processing block for the IPP function <b>ippiNot_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVNot_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVNot_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Performs corresponding bitwise logical operation between pixels of two image (AndC OrC XorC - between pixel of the source image and a constant)

This is the QVision processing block for the IPP function <b>ippiNot_8u_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVNot_uCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVNot_uCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiAndC_8u_C1R

This is the QVision processing block for the IPP function <b>ippiAndC_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVAndC_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVAndC_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiOrC_8u_C1R

This is the QVision processing block for the IPP function <b>ippiOrC_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVOrC_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVOrC_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiXorC_8u_C1R

This is the QVision processing block for the IPP function <b>ippiXorC_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVXorC_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVXorC_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiLShiftC_8u_C1R

This is the QVision processing block for the IPP function <b>ippiLShiftC_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVLShiftC_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVLShiftC_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiRShiftC_8u_C1R

This is the QVision processing block for the IPP function <b>ippiRShiftC_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVRShiftC_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVRShiftC_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Converts an RGB image to gray scale (fixed coefficients)

This is the QVision processing block for the IPP function <b>ippiRGBToGray_8u_C3C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVRGBToGray_uCharC3C1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVRGBToGray_uCharC3C1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Converts an RGB image to gray scale (fixed coefficients)

This is the QVision processing block for the IPP function <b>ippiRGBToGray_32f_C3C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVRGBToGray_sFloatC3C1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVRGBToGray_sFloatC3C1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Performs thresholding of an image using the specified level

This is the QVision processing block for the IPP function <b>ippiThreshold_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param threshold	Corresponds to the same parameter of type IppiSize in the IPP function.
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVThreshold_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVThreshold_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Performs thresholding of an image using the specified level

This is the QVision processing block for the IPP function <b>ippiThreshold_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param threshold	Corresponds to the same parameter of type IppiSize in the IPP function.
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVThreshold_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVThreshold_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Calculate Otsu theshold value of images

This is the QVision processing block for the IPP function <b>ippiComputeThreshold_Otsu_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pThreshold	Corresponds to the same parameter in the IPP function.

@ingroup qvippblocks
*/
class QVComputeThreshold_Otsu_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVComputeThreshold_Otsu_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiCompare_8u_C1R

This is the QVision processing block for the IPP function <b>ippiCompare_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVCompare_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVCompare_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiCompare_32f_C1R

This is the QVision processing block for the IPP function <b>ippiCompare_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc1	Image corresponding to the data buffer pointer <i>pSrc1</i> and step number <i>src1Step</i> variables in the IPP function
@param qvimage_pSrc2	Image corresponding to the data buffer pointer <i>pSrc2</i> and step number <i>src2Step</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVCompare_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVCompare_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Compares pixel values of two images, or pixel values of an image to a constant value using the following compare conditions

This is the QVision processing block for the IPP function <b>ippiCompareC_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVCompareC_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVCompareC_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Compares pixel values of two images, or pixel values of an image to a constant value using the following compare conditions

This is the QVision processing block for the IPP function <b>ippiCompareC_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param value	Corresponds to the same parameter of type IppiSize in the IPP function.
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param ippCmpOp	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVCompareC_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVCompareC_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterBox_8u_C1R

This is the QVision processing block for the IPP function <b>ippiFilterBox_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterBox_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterBox_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterBox_8u_C3R

This is the QVision processing block for the IPP function <b>ippiFilterBox_8u_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterBox_uCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterBox_uCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterBox_32f_C1R

This is the QVision processing block for the IPP function <b>ippiFilterBox_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterBox_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterBox_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Applies the "min" filter to an image

This is the QVision processing block for the IPP function <b>ippiFilterMin_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterMin_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterMin_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Applies the "min" filter to an image

This is the QVision processing block for the IPP function <b>ippiFilterMin_8u_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterMin_uCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterMin_uCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Applies the "min" filter to an image

This is the QVision processing block for the IPP function <b>ippiFilterMin_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterMin_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterMin_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Applies the "max" filter to an image

This is the QVision processing block for the IPP function <b>ippiFilterMax_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterMax_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterMax_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Applies the "max" filter to an image

This is the QVision processing block for the IPP function <b>ippiFilterMax_8u_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterMax_uCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterMax_uCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Applies the "max" filter to an image

This is the QVision processing block for the IPP function <b>ippiFilterMax_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterMax_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterMax_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Filters an image using a box median filter

This is the QVision processing block for the IPP function <b>ippiFilterMedian_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterMedian_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterMedian_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Filters an image using a box median filter

This is the QVision processing block for the IPP function <b>ippiFilterMedian_8u_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param maskSize	Corresponds to the same parameter of type IppiSize in the IPP function.
@param anchor	Corresponds to the same parameter of type IppiPoint in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterMedian_uCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterMedian_uCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Performs horizontal median filtering

This is the QVision processing block for the IPP function <b>ippiFilterMedianHoriz_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterMedianHoriz_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterMedianHoriz_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterSobelHorizMask_32f_C1R

This is the QVision processing block for the IPP function <b>ippiFilterSobelHorizMask_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterSobelHorizMask_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterSobelHorizMask_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterSobelVertMask_32f_C1R

This is the QVision processing block for the IPP function <b>ippiFilterSobelVertMask_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterSobelVertMask_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterSobelVertMask_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterLaplace_8u_C1R

This is the QVision processing block for the IPP function <b>ippiFilterLaplace_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterLaplace_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterLaplace_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterLaplace_32f_C1R

This is the QVision processing block for the IPP function <b>ippiFilterLaplace_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterLaplace_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterLaplace_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterGauss_8u_C1R

This is the QVision processing block for the IPP function <b>ippiFilterGauss_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterGauss_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterGauss_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterGauss_32f_C1R

This is the QVision processing block for the IPP function <b>ippiFilterGauss_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterGauss_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterGauss_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterGauss_8u_C3R

This is the QVision processing block for the IPP function <b>ippiFilterGauss_8u_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterGauss_uCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterGauss_uCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterGauss_32f_C3R

This is the QVision processing block for the IPP function <b>ippiFilterGauss_32f_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterGauss_sFloatC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterGauss_sFloatC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterHipass_8u_C1R

This is the QVision processing block for the IPP function <b>ippiFilterHipass_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterHipass_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterHipass_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterHipass_8u_C3R

This is the QVision processing block for the IPP function <b>ippiFilterHipass_8u_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterHipass_uCharC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterHipass_uCharC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterHipass_32f_C1R

This is the QVision processing block for the IPP function <b>ippiFilterHipass_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterHipass_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterHipass_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterHipass_32f_C3R

This is the QVision processing block for the IPP function <b>ippiFilterHipass_32f_C3R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterHipass_sFloatC3Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterHipass_sFloatC3Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterLowpass_8u_C1R

This is the QVision processing block for the IPP function <b>ippiFilterLowpass_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterLowpass_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterLowpass_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief QVision wrapper function for IPP's ippiFilterLowpass_32f_C1R

This is the QVision processing block for the IPP function <b>ippiFilterLowpass_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param qvimage_pDst	Image corresponding to the data buffer pointer <i>pDst</i> and step number <i>dstStep</i> variables in the IPP function
@param mask	Corresponds to the same parameter of type IppiSize in the IPP function.
@param destROIOffset	Pointer to destination ROI. See section @ref DestinationROIPointer for more info about this parameter.

@ingroup qvippblocks
*/
class QVFilterLowpass_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVFilterLowpass_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Computes the sum of image pixel values

This is the QVision processing block for the IPP function <b>ippiSum_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pSum	Corresponds to the same parameter in the IPP function.

@ingroup qvippblocks
*/
class QVSum_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVSum_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Computes the mean of image pixel values

This is the QVision processing block for the IPP function <b>ippiMean_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pMean	Corresponds to the same parameter in the IPP function.

@ingroup qvippblocks
*/
class QVMean_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVMean_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Computes the minimum of image pixel values

This is the QVision processing block for the IPP function <b>ippiMin_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pMin	Corresponds to the same parameter in the IPP function.

@ingroup qvippblocks
*/
class QVMin_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVMin_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Computes the minimum of image pixel values

This is the QVision processing block for the IPP function <b>ippiMin_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pMin	Corresponds to the same parameter in the IPP function.

@ingroup qvippblocks
*/
class QVMin_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVMin_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Computes the maximum of image pixel values

This is the QVision processing block for the IPP function <b>ippiMax_8u_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pMax	Corresponds to the same parameter in the IPP function.

@ingroup qvippblocks
*/
class QVMax_uCharC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVMax_uCharC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

/*!
@brief Computes the maximum of image pixel values

This is the QVision processing block for the IPP function <b>ippiMax_32f_C1R</b>. The input and output properties of this block will correspond to the input and output parameters of that function. See <a href="http://www.intel.com/cd/software/products/asmo-na/eng/346532.htm">Intel's IPP documentation</a> for further info about them.

These are the input and output properties of this block:
@param qvimage_pSrc	Image corresponding to the data buffer pointer <i>pSrc</i> and step number <i>srcStep</i> variables in the IPP function
@param pMax	Corresponds to the same parameter in the IPP function.

@ingroup qvippblocks
*/
class QVMax_sFloatC1Block: public QVProcessingBlock
	{
	public:
		/// @brief Block constructor.
		QVMax_sFloatC1Block(QString name = QString());
		/// @brief Block iterate function.
		void iterate();
	};

#endif
