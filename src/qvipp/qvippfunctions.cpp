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

#include <qvipp/macros.h>
#include <qvipp/qvippfunctions.h>

// QVision wrapper function for IPP's ippiConvert_8u16u_C1R
void Convert(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_8u16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_8u16s_C1R
void Convert(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_8u16s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_8u32s_C1R
void Convert(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_8u32s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_8u32f_C1R
void Convert(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_8u32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_8u16u_C3R
void Convert(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_8u16u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_8u16s_C3R
void Convert(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<sShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_8u16s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_8u32s_C3R
void Convert(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_8u32s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_8u32f_C3R
void Convert(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_8u32f_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_16u8u_C1R
void Convert(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_16u8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_16u32s_C1R
void Convert(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_16u32s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_16u32f_C1R
void Convert(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_16u32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_16u8u_C3R
void Convert(
		const QVImage<uShort, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_16u8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_16u32s_C3R
void Convert(
		const QVImage<uShort, 3> & qvimage_pSrc,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_16u32s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_16u32f_C3R
void Convert(
		const QVImage<uShort, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_16u32f_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_16s8u_C1R
void Convert(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_16s8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_16s32s_C1R
void Convert(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_16s32s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_16s32f_C1R
void Convert(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_16s32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_16s8u_C3R
void Convert(
		const QVImage<sShort, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_16s8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_16s32s_C3R
void Convert(
		const QVImage<sShort, 3> & qvimage_pSrc,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_16s32s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_16s32f_C3R
void Convert(
		const QVImage<sShort, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_16s32f_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_32s8u_C1R
void Convert(
		const QVImage<sInt, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_32s8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_32s8u_C3R
void Convert(
		const QVImage<sInt, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_32s8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiConvert_32f8u_C1R
void Convert(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppRoundMode roundMode,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_32f8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		roundMode);
	}

// QVision wrapper function for IPP's ippiConvert_32f16u_C1R
void Convert(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const IppRoundMode roundMode,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_32f16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		roundMode);
	}

// QVision wrapper function for IPP's ippiConvert_32f16s_C1R
void Convert(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const IppRoundMode roundMode,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_32f16s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		roundMode);
	}

// QVision wrapper function for IPP's ippiConvert_32f8u_C3R
void Convert(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const IppRoundMode roundMode,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_32f8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		roundMode);
	}

// QVision wrapper function for IPP's ippiConvert_32f16u_C3R
void Convert(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<uShort, 3> & qvimage_pDst,
		const IppRoundMode roundMode,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_32f16u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		roundMode);
	}

// QVision wrapper function for IPP's ippiConvert_32f16s_C3R
void Convert(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sShort, 3> & qvimage_pDst,
		const IppRoundMode roundMode,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Convert, ippiConvert_32f16s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		roundMode);
	}

// QVision wrapper function for IPP's ippiScale_8u16u_C1R
void Scale(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Scale, ippiScale_8u16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiScale_8u16s_C1R
void Scale(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Scale, ippiScale_8u16s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiScale_8u32s_C1R
void Scale(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Scale, ippiScale_8u32s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiScale_8u16u_C3R
void Scale(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Scale, ippiScale_8u16u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiScale_8u16s_C3R
void Scale(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<sShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Scale, ippiScale_8u16s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiScale_8u32s_C3R
void Scale(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Scale, ippiScale_8u32s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiSet_8u_C1R
void Set(
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst)
	{
	IPP_DEBUG(Set, ippiSet_8u_C1R,
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiSet_16u_C1R
void Set(
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst)
	{
	IPP_DEBUG(Set, ippiSet_16u_C1R,
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiSet_16s_C1R
void Set(
		const sShort value,
		QVImage<sShort, 1> & qvimage_pDst)
	{
	IPP_DEBUG(Set, ippiSet_16s_C1R,
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiSet_32s_C1R
void Set(
		const sInt value,
		QVImage<sInt, 1> & qvimage_pDst)
	{
	IPP_DEBUG(Set, ippiSet_32s_C1R,
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiSet_32f_C1R
void Set(
		const sFloat value,
		QVImage<sFloat, 1> & qvimage_pDst)
	{
	IPP_DEBUG(Set, ippiSet_32f_C1R,
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiSet_8u_C3R
void Set(
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst)
	{
	IPP_DEBUG(Set, ippiSet_8u_C3R,
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiSet_16u_C3R
void Set(
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst)
	{
	IPP_DEBUG(Set, ippiSet_16u_C3R,
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiSet_16s_C3R
void Set(
		const  sShort value[3],
		QVImage<sShort, 3> & qvimage_pDst)
	{
	IPP_DEBUG(Set, ippiSet_16s_C3R,
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiSet_32s_C3R
void Set(
		const  sInt value[3],
		QVImage<sInt, 3> & qvimage_pDst)
	{
	IPP_DEBUG(Set, ippiSet_32s_C3R,
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiSet_32f_C3R
void Set(
		const  sFloat value[3],
		QVImage<sFloat, 3> & qvimage_pDst)
	{
	IPP_DEBUG(Set, ippiSet_32f_C3R,
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiCopy_8u_C1R
void Copy(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Copy, ippiCopy_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiCopy_8u_C3R
void Copy(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Copy, ippiCopy_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiCopy_16u_C1R
void Copy(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Copy, ippiCopy_16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiCopy_16u_C3R
void Copy(
		const QVImage<uShort, 3> & qvimage_pSrc,
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Copy, ippiCopy_16u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiCopy_16s_C1R
void Copy(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Copy, ippiCopy_16s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiCopy_16s_C3R
void Copy(
		const QVImage<sShort, 3> & qvimage_pSrc,
		QVImage<sShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Copy, ippiCopy_16s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiCopy_32s_C1R
void Copy(
		const QVImage<sInt, 1> & qvimage_pSrc,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Copy, ippiCopy_32s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiCopy_32s_C3R
void Copy(
		const QVImage<sInt, 3> & qvimage_pSrc,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Copy, ippiCopy_32s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiCopy_32f_C1R
void Copy(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Copy, ippiCopy_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiCopy_32f_C3R
void Copy(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Copy, ippiCopy_32f_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAddRandUniform_Direct_8u_C1IR
void AddRandUniform_Direct(
		QVImage<uChar, 1> & qvimage_pSrcDst,
		const uChar low,
		const uChar high,
		 unsigned int & pSeed)
	{
	IPP_DEBUG(AddRandUniform_Direct, ippiAddRandUniform_Direct_8u_C1IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		low,
		high,
		& pSeed);
	}

// QVision wrapper function for IPP's ippiAddRandUniform_Direct_16u_C1IR
void AddRandUniform_Direct(
		QVImage<uShort, 1> & qvimage_pSrcDst,
		const uShort low,
		const uShort high,
		 unsigned int & pSeed)
	{
	IPP_DEBUG(AddRandUniform_Direct, ippiAddRandUniform_Direct_16u_C1IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		low,
		high,
		& pSeed);
	}

// QVision wrapper function for IPP's ippiAddRandUniform_Direct_16s_C1IR
void AddRandUniform_Direct(
		QVImage<sShort, 1> & qvimage_pSrcDst,
		const sShort low,
		const sShort high,
		 unsigned int & pSeed)
	{
	IPP_DEBUG(AddRandUniform_Direct, ippiAddRandUniform_Direct_16s_C1IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		low,
		high,
		& pSeed);
	}

// QVision wrapper function for IPP's ippiAddRandUniform_Direct_32f_C1IR
void AddRandUniform_Direct(
		QVImage<sFloat, 1> & qvimage_pSrcDst,
		const sFloat low,
		const sFloat high,
		 unsigned int & pSeed)
	{
	IPP_DEBUG(AddRandUniform_Direct, ippiAddRandUniform_Direct_32f_C1IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		low,
		high,
		& pSeed);
	}

// QVision wrapper function for IPP's ippiAddRandUniform_Direct_8u_C3IR
void AddRandUniform_Direct(
		QVImage<uChar, 3> & qvimage_pSrcDst,
		const uChar low,
		const uChar high,
		 unsigned int & pSeed)
	{
	IPP_DEBUG(AddRandUniform_Direct, ippiAddRandUniform_Direct_8u_C3IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		low,
		high,
		& pSeed);
	}

// QVision wrapper function for IPP's ippiAddRandUniform_Direct_16u_C3IR
void AddRandUniform_Direct(
		QVImage<uShort, 3> & qvimage_pSrcDst,
		const uShort low,
		const uShort high,
		 unsigned int & pSeed)
	{
	IPP_DEBUG(AddRandUniform_Direct, ippiAddRandUniform_Direct_16u_C3IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		low,
		high,
		& pSeed);
	}

// QVision wrapper function for IPP's ippiAddRandUniform_Direct_16s_C3IR
void AddRandUniform_Direct(
		QVImage<sShort, 3> & qvimage_pSrcDst,
		const sShort low,
		const sShort high,
		 unsigned int & pSeed)
	{
	IPP_DEBUG(AddRandUniform_Direct, ippiAddRandUniform_Direct_16s_C3IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		low,
		high,
		& pSeed);
	}

// QVision wrapper function for IPP's ippiAddRandUniform_Direct_32f_C3IR
void AddRandUniform_Direct(
		QVImage<sFloat, 3> & qvimage_pSrcDst,
		const sFloat low,
		const sFloat high,
		 unsigned int & pSeed)
	{
	IPP_DEBUG(AddRandUniform_Direct, ippiAddRandUniform_Direct_32f_C3IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		low,
		high,
		& pSeed);
	}

// QVision wrapper function for IPP's ippiAdd_8u_C1RSfs
void Add(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Add, ippiAdd_8u_C1RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiAdd_8u_C3RSfs
void Add(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Add, ippiAdd_8u_C3RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiAdd_16u_C1RSfs
void Add(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Add, ippiAdd_16u_C1RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiAdd_16u_C3RSfs
void Add(
		const QVImage<uShort, 3> & qvimage_pSrc1,
		const QVImage<uShort, 3> & qvimage_pSrc2,
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Add, ippiAdd_16u_C3RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiAdd_16s_C1RSfs
void Add(
		const QVImage<sShort, 1> & qvimage_pSrc1,
		const QVImage<sShort, 1> & qvimage_pSrc2,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Add, ippiAdd_16s_C1RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiAdd_16s_C3RSfs
void Add(
		const QVImage<sShort, 3> & qvimage_pSrc1,
		const QVImage<sShort, 3> & qvimage_pSrc2,
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Add, ippiAdd_16s_C3RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiAdd_32f_C1R
void Add(
		const QVImage<sFloat, 1> & qvimage_pSrc1,
		const QVImage<sFloat, 1> & qvimage_pSrc2,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Add, ippiAdd_32f_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAdd_32f_C3R
void Add(
		const QVImage<sFloat, 3> & qvimage_pSrc1,
		const QVImage<sFloat, 3> & qvimage_pSrc2,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Add, ippiAdd_32f_C3R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAddC_8u_C1RSfs
void AddC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(AddC, ippiAddC_8u_C1RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiAddC_8u_C3RSfs
void AddC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(AddC, ippiAddC_8u_C3RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiAddC_16u_C1RSfs
void AddC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(AddC, ippiAddC_16u_C1RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiAddC_16u_C3RSfs
void AddC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(AddC, ippiAddC_16u_C3RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiAddC_16s_C1RSfs
void AddC(
		const QVImage<sShort, 1> & qvimage_pSrc,
		const sShort value,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(AddC, ippiAddC_16s_C1RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiAddC_16s_C3RSfs
void AddC(
		const QVImage<sShort, 3> & qvimage_pSrc,
		const  sShort value[3],
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(AddC, ippiAddC_16s_C3RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiAddC_32f_C1R
void AddC(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		const sFloat value,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(AddC, ippiAddC_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAddC_32f_C3R
void AddC(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		const  sFloat value[3],
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(AddC, ippiAddC_32f_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiMul_8u_C1RSfs
void Mul(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Mul, ippiMul_8u_C1RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiMul_8u_C3RSfs
void Mul(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Mul, ippiMul_8u_C3RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiMul_16u_C1RSfs
void Mul(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Mul, ippiMul_16u_C1RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiMul_16u_C3RSfs
void Mul(
		const QVImage<uShort, 3> & qvimage_pSrc1,
		const QVImage<uShort, 3> & qvimage_pSrc2,
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Mul, ippiMul_16u_C3RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiMul_16s_C1RSfs
void Mul(
		const QVImage<sShort, 1> & qvimage_pSrc1,
		const QVImage<sShort, 1> & qvimage_pSrc2,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Mul, ippiMul_16s_C1RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiMul_16s_C3RSfs
void Mul(
		const QVImage<sShort, 3> & qvimage_pSrc1,
		const QVImage<sShort, 3> & qvimage_pSrc2,
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Mul, ippiMul_16s_C3RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiMul_32f_C3R
void Mul(
		const QVImage<sFloat, 3> & qvimage_pSrc1,
		const QVImage<sFloat, 3> & qvimage_pSrc2,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Mul, ippiMul_32f_C3R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiMul_32f_C1R
void Mul(
		const QVImage<sFloat, 1> & qvimage_pSrc1,
		const QVImage<sFloat, 1> & qvimage_pSrc2,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Mul, ippiMul_32f_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiMulC_8u_C1RSfs
void MulC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MulC, ippiMulC_8u_C1RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiMulC_8u_C3RSfs
void MulC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MulC, ippiMulC_8u_C3RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiMulC_16u_C1RSfs
void MulC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MulC, ippiMulC_16u_C1RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiMulC_16u_C3RSfs
void MulC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MulC, ippiMulC_16u_C3RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiMulC_16s_C1RSfs
void MulC(
		const QVImage<sShort, 1> & qvimage_pSrc,
		const sShort value,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MulC, ippiMulC_16s_C1RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiMulC_16s_C3RSfs
void MulC(
		const QVImage<sShort, 3> & qvimage_pSrc,
		const  sShort value[3],
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MulC, ippiMulC_16s_C3RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiMulC_32f_C1R
void MulC(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		const sFloat value,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MulC, ippiMulC_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiMulC_32f_C3R
void MulC(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		const  sFloat value[3],
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MulC, ippiMulC_32f_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiMulScale_8u_C1R
void MulScale(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(MulScale, ippiMulScale_8u_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiMulScale_8u_C3R
void MulScale(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(MulScale, ippiMulScale_8u_C3R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiSub_8u_C1RSfs
void Sub(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Sub, ippiSub_8u_C1RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiSub_8u_C3RSfs
void Sub(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Sub, ippiSub_8u_C3RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiSub_16u_C1RSfs
void Sub(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Sub, ippiSub_16u_C1RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiSub_16u_C3RSfs
void Sub(
		const QVImage<uShort, 3> & qvimage_pSrc1,
		const QVImage<uShort, 3> & qvimage_pSrc2,
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Sub, ippiSub_16u_C3RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiSub_16s_C1RSfs
void Sub(
		const QVImage<sShort, 1> & qvimage_pSrc1,
		const QVImage<sShort, 1> & qvimage_pSrc2,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Sub, ippiSub_16s_C1RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiSub_16s_C3RSfs
void Sub(
		const QVImage<sShort, 3> & qvimage_pSrc1,
		const QVImage<sShort, 3> & qvimage_pSrc2,
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Sub, ippiSub_16s_C3RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiSub_32f_C1R
void Sub(
		const QVImage<sFloat, 1> & qvimage_pSrc1,
		const QVImage<sFloat, 1> & qvimage_pSrc2,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Sub, ippiSub_32f_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiSub_32f_C3R
void Sub(
		const QVImage<sFloat, 3> & qvimage_pSrc1,
		const QVImage<sFloat, 3> & qvimage_pSrc2,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Sub, ippiSub_32f_C3R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiSubC_8u_C1RSfs
void SubC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(SubC, ippiSubC_8u_C1RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiSubC_8u_C3RSfs
void SubC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(SubC, ippiSubC_8u_C3RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiSubC_16u_C1RSfs
void SubC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(SubC, ippiSubC_16u_C1RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiSubC_16s_C1RSfs
void SubC(
		const QVImage<sShort, 1> & qvimage_pSrc,
		const sShort value,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(SubC, ippiSubC_16s_C1RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiSubC_16u_C3RSfs
void SubC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(SubC, ippiSubC_16u_C3RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiSubC_16s_C3RSfs
void SubC(
		const QVImage<sShort, 3> & qvimage_pSrc,
		const  sShort value[3],
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(SubC, ippiSubC_16s_C3RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiSubC_32f_C1R
void SubC(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		const sFloat value,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(SubC, ippiSubC_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiSubC_32f_C3R
void SubC(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		const  sFloat value[3],
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(SubC, ippiSubC_32f_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiDiv_8u_C1RSfs
void Div(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Div, ippiDiv_8u_C1RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiDiv_8u_C3RSfs
void Div(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Div, ippiDiv_8u_C3RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiDiv_16u_C1RSfs
void Div(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Div, ippiDiv_16u_C1RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiDiv_16u_C3RSfs
void Div(
		const QVImage<uShort, 3> & qvimage_pSrc1,
		const QVImage<uShort, 3> & qvimage_pSrc2,
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Div, ippiDiv_16u_C3RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiDiv_16s_C1RSfs
void Div(
		const QVImage<sShort, 1> & qvimage_pSrc1,
		const QVImage<sShort, 1> & qvimage_pSrc2,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Div, ippiDiv_16s_C1RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiDiv_16s_C3RSfs
void Div(
		const QVImage<sShort, 3> & qvimage_pSrc1,
		const QVImage<sShort, 3> & qvimage_pSrc2,
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Div, ippiDiv_16s_C3RSfs,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiDiv_32f_C3R
void Div(
		const QVImage<sFloat, 3> & qvimage_pSrc1,
		const QVImage<sFloat, 3> & qvimage_pSrc2,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Div, ippiDiv_32f_C3R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiDiv_32f_C1R
void Div(
		const QVImage<sFloat, 1> & qvimage_pSrc1,
		const QVImage<sFloat, 1> & qvimage_pSrc2,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Div, ippiDiv_32f_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiDivC_8u_C1RSfs
void DivC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(DivC, ippiDivC_8u_C1RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiDivC_8u_C3RSfs
void DivC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(DivC, ippiDivC_8u_C3RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiDivC_16u_C1RSfs
void DivC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(DivC, ippiDivC_16u_C1RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiDivC_16u_C3RSfs
void DivC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(DivC, ippiDivC_16u_C3RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiDivC_16s_C1RSfs
void DivC(
		const QVImage<sShort, 1> & qvimage_pSrc,
		const sShort value,
		QVImage<sShort, 1> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(DivC, ippiDivC_16s_C1RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiDivC_16s_C3RSfs
void DivC(
		const QVImage<sShort, 3> & qvimage_pSrc,
		const  sShort value[3],
		QVImage<sShort, 3> & qvimage_pDst,
		const int scaleFactor,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(DivC, ippiDivC_16s_C3RSfs,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		scaleFactor);
	}

// QVision wrapper function for IPP's ippiDivC_32f_C1R
void DivC(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		const sFloat value,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(DivC, ippiDivC_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiDivC_32f_C3R
void DivC(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		const  sFloat value[3],
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(DivC, ippiDivC_32f_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAbs_16s_C1R
void Abs(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Abs, ippiAbs_16s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAbs_32f_C1R
void Abs(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Abs, ippiAbs_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAbsDiff_8u_C1R
void AbsDiff(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(AbsDiff, ippiAbsDiff_8u_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAbsDiff_32f_C1R
// Calculate absolute difference between corresponding pixels of the two images or between image pixels and scalar.
void AbsDiff(
		const QVImage<sFloat, 1> & qvimage_pSrc1,
		const QVImage<sFloat, 1> & qvimage_pSrc2,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(AbsDiff, ippiAbsDiff_32f_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiSqr_32f_C1R
void Sqr(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Sqr, ippiSqr_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiLn_32f_C1R
void Ln(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Ln, ippiLn_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiLn_32f_C3R
void Ln(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Ln, ippiLn_32f_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAnd_8u_C1R
void And(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(And, ippiAnd_8u_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAnd_8u_C3R
void And(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(And, ippiAnd_8u_C3R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAnd_16u_C1R
void And(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(And, ippiAnd_16u_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAnd_16u_C3R
void And(
		const QVImage<uShort, 3> & qvimage_pSrc1,
		const QVImage<uShort, 3> & qvimage_pSrc2,
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(And, ippiAnd_16u_C3R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAnd_32s_C1R
void And(
		const QVImage<sInt, 1> & qvimage_pSrc1,
		const QVImage<sInt, 1> & qvimage_pSrc2,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(And, ippiAnd_32s_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAnd_32s_C3R
void And(
		const QVImage<sInt, 3> & qvimage_pSrc1,
		const QVImage<sInt, 3> & qvimage_pSrc2,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(And, ippiAnd_32s_C3R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiOr_8u_C1R
void Or(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Or, ippiOr_8u_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiOr_8u_C3R
void Or(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Or, ippiOr_8u_C3R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiOr_16u_C1R
void Or(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Or, ippiOr_16u_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiOr_16u_C3R
void Or(
		const QVImage<uShort, 3> & qvimage_pSrc1,
		const QVImage<uShort, 3> & qvimage_pSrc2,
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Or, ippiOr_16u_C3R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiOr_32s_C1R
void Or(
		const QVImage<sInt, 1> & qvimage_pSrc1,
		const QVImage<sInt, 1> & qvimage_pSrc2,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Or, ippiOr_32s_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiOr_32s_C3R
void Or(
		const QVImage<sInt, 3> & qvimage_pSrc1,
		const QVImage<sInt, 3> & qvimage_pSrc2,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Or, ippiOr_32s_C3R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiXor_8u_C1R
void Xor(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Xor, ippiXor_8u_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiXor_8u_C3R
void Xor(
		const QVImage<uChar, 3> & qvimage_pSrc1,
		const QVImage<uChar, 3> & qvimage_pSrc2,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Xor, ippiXor_8u_C3R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiXor_16u_C1R
void Xor(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Xor, ippiXor_16u_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiXor_16u_C3R
void Xor(
		const QVImage<uShort, 3> & qvimage_pSrc1,
		const QVImage<uShort, 3> & qvimage_pSrc2,
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Xor, ippiXor_16u_C3R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiXor_32s_C1R
void Xor(
		const QVImage<sInt, 1> & qvimage_pSrc1,
		const QVImage<sInt, 1> & qvimage_pSrc2,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Xor, ippiXor_32s_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiXor_32s_C3R
void Xor(
		const QVImage<sInt, 3> & qvimage_pSrc1,
		const QVImage<sInt, 3> & qvimage_pSrc2,
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Xor, ippiXor_32s_C3R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiNot_8u_C1R
void Not(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Not, ippiNot_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiNot_8u_C3R
void Not(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Not, ippiNot_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAndC_8u_C1R
void AndC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(AndC, ippiAndC_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAndC_8u_C3R
void AndC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(AndC, ippiAndC_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAndC_16u_C1R
void AndC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(AndC, ippiAndC_16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAndC_16u_C3R
void AndC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(AndC, ippiAndC_16u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAndC_32s_C1R
void AndC(
		const QVImage<sInt, 1> & qvimage_pSrc,
		const sInt value,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(AndC, ippiAndC_32s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiAndC_32s_C3R
void AndC(
		const QVImage<sInt, 3> & qvimage_pSrc,
		const  sInt value[3],
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(AndC, ippiAndC_32s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiOrC_8u_C1R
void OrC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(OrC, ippiOrC_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiOrC_8u_C3R
void OrC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(OrC, ippiOrC_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiOrC_16u_C1R
void OrC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(OrC, ippiOrC_16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiOrC_16u_C3R
void OrC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(OrC, ippiOrC_16u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiOrC_32s_C1R
void OrC(
		const QVImage<sInt, 1> & qvimage_pSrc,
		const sInt value,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(OrC, ippiOrC_32s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiOrC_32s_C3R
void OrC(
		const QVImage<sInt, 3> & qvimage_pSrc,
		const  sInt value[3],
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(OrC, ippiOrC_32s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiXorC_8u_C1R
void XorC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(XorC, ippiXorC_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiXorC_8u_C3R
void XorC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uChar value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(XorC, ippiXorC_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiXorC_16u_C1R
void XorC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uShort value,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(XorC, ippiXorC_16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiXorC_16u_C3R
void XorC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uShort value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(XorC, ippiXorC_16u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiXorC_32s_C1R
void XorC(
		const QVImage<sInt, 1> & qvimage_pSrc,
		const sInt value,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(XorC, ippiXorC_32s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiXorC_32s_C3R
void XorC(
		const QVImage<sInt, 3> & qvimage_pSrc,
		const  sInt value[3],
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(XorC, ippiXorC_32s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiLShiftC_8u_C1R
void LShiftC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uInt value,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(LShiftC, ippiLShiftC_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiLShiftC_8u_C3R
void LShiftC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uInt value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(LShiftC, ippiLShiftC_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiRShiftC_8u_C1R
void RShiftC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uInt value,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(RShiftC, ippiRShiftC_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiRShiftC_8u_C3R
void RShiftC(
		const QVImage<uChar, 3> & qvimage_pSrc,
		const  uInt value[3],
		QVImage<uChar, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(RShiftC, ippiRShiftC_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiLShiftC_16u_C1R
void LShiftC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uInt value,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(LShiftC, ippiLShiftC_16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiLShiftC_16u_C3R
void LShiftC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uInt value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(LShiftC, ippiLShiftC_16u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiRShiftC_16u_C1R
void RShiftC(
		const QVImage<uShort, 1> & qvimage_pSrc,
		const uInt value,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(RShiftC, ippiRShiftC_16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiRShiftC_16u_C3R
void RShiftC(
		const QVImage<uShort, 3> & qvimage_pSrc,
		const  uInt value[3],
		QVImage<uShort, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(RShiftC, ippiRShiftC_16u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiLShiftC_32s_C1R
void LShiftC(
		const QVImage<sInt, 1> & qvimage_pSrc,
		const uInt value,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(LShiftC, ippiLShiftC_32s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiLShiftC_32s_C3R
void LShiftC(
		const QVImage<sInt, 3> & qvimage_pSrc,
		const  uInt value[3],
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(LShiftC, ippiLShiftC_32s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiRShiftC_32s_C1R
void RShiftC(
		const QVImage<sInt, 1> & qvimage_pSrc,
		const uInt value,
		QVImage<sInt, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(RShiftC, ippiRShiftC_32s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiRShiftC_32s_C3R
void RShiftC(
		const QVImage<sInt, 3> & qvimage_pSrc,
		const  uInt value[3],
		QVImage<sInt, 3> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(RShiftC, ippiRShiftC_32s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiRGBToGray_8u_C3C1R
void RGBToGray(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(RGBToGray, ippiRGBToGray_8u_C3C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiRGBToGray_16u_C3C1R
void RGBToGray(
		const QVImage<uShort, 3> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(RGBToGray, ippiRGBToGray_16u_C3C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiRGBToGray_16s_C3C1R
void RGBToGray(
		const QVImage<sShort, 3> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(RGBToGray, ippiRGBToGray_16s_C3C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiRGBToGray_32f_C3C1R
void RGBToGray(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(RGBToGray, ippiRGBToGray_32f_C3C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst));
	}

// QVision wrapper function for IPP's ippiThreshold_8u_C1R
void Threshold(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const uChar threshold,
		const IppCmpOp ippCmpOp,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Threshold, ippiThreshold_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		threshold,
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiThreshold_8u_C1IR
void Threshold(
		QVImage<uChar, 1> & qvimage_pSrcDst,
		const uChar threshold,
		const IppCmpOp ippCmpOp)
	{
	IPP_DEBUG(Threshold, ippiThreshold_8u_C1IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		threshold,
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiThreshold_16s_C1R
void Threshold(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const sShort threshold,
		const IppCmpOp ippCmpOp,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Threshold, ippiThreshold_16s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		threshold,
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiThreshold_16s_C1IR
void Threshold(
		QVImage<sShort, 1> & qvimage_pSrcDst,
		const sShort threshold,
		const IppCmpOp ippCmpOp)
	{
	IPP_DEBUG(Threshold, ippiThreshold_16s_C1IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		threshold,
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiThreshold_32f_C1R
void Threshold(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const sFloat threshold,
		const IppCmpOp ippCmpOp,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Threshold, ippiThreshold_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		threshold,
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiThreshold_32f_C1IR
void Threshold(
		QVImage<sFloat, 1> & qvimage_pSrcDst,
		const sFloat threshold,
		const IppCmpOp ippCmpOp)
	{
	IPP_DEBUG(Threshold, ippiThreshold_32f_C1IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		threshold,
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiThreshold_Val_8u_C1R
void Threshold_Val(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const uChar threshold,
		const uChar value,
		const IppCmpOp ippCmpOp,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Threshold_Val, ippiThreshold_Val_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		threshold,
		value,
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiThreshold_Val_8u_C1IR
void Threshold_Val(
		QVImage<uChar, 1> & qvimage_pSrcDst,
		const uChar threshold,
		const uChar value,
		const IppCmpOp ippCmpOp)
	{
	IPP_DEBUG(Threshold_Val, ippiThreshold_Val_8u_C1IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		threshold,
		value,
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiThreshold_Val_16s_C1IR
void Threshold_Val(
		QVImage<sShort, 1> & qvimage_pSrcDst,
		const sShort threshold,
		const sShort value,
		const IppCmpOp ippCmpOp)
	{
	IPP_DEBUG(Threshold_Val, ippiThreshold_Val_16s_C1IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		threshold,
		value,
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiThreshold_Val_32f_C1R
void Threshold_Val(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const sFloat threshold,
		const sFloat value,
		const IppCmpOp ippCmpOp,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Threshold_Val, ippiThreshold_Val_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		threshold,
		value,
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiThreshold_Val_32f_C1IR
void Threshold_Val(
		QVImage<sFloat, 1> & qvimage_pSrcDst,
		const sFloat threshold,
		const sFloat value,
		const IppCmpOp ippCmpOp)
	{
	IPP_DEBUG(Threshold_Val, ippiThreshold_Val_32f_C1IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		threshold,
		value,
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiThreshold_LTValGTVal_8u_C1R
void Threshold_LTValGTVal(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const uChar thresholdLT,
		const uChar valueLT,
		const uChar thresholdGT,
		const uChar valueGT,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Threshold_LTValGTVal, ippiThreshold_LTValGTVal_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		thresholdLT,
		valueLT,
		thresholdGT,
		valueGT);
	}

// QVision wrapper function for IPP's ippiThreshold_LTValGTVal_32f_C1R
void Threshold_LTValGTVal(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const sFloat thresholdLT,
		const sFloat valueLT,
		const sFloat thresholdGT,
		const sFloat valueGT,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Threshold_LTValGTVal, ippiThreshold_LTValGTVal_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		thresholdLT,
		valueLT,
		thresholdGT,
		valueGT);
	}

// QVision wrapper function for IPP's ippiComputeThreshold_Otsu_8u_C1R
// Calculate Otsu theshold value of images.
void ComputeThreshold_Otsu(
		const QVImage<uChar, 1> & qvimage_pSrc,
		 uChar & pThreshold)
	{
	IPP_DEBUG(ComputeThreshold_Otsu, ippiComputeThreshold_Otsu_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		& pThreshold);
	}

// QVision wrapper function for IPP's ippiCompare_8u_C1R
void Compare(
		const QVImage<uChar, 1> & qvimage_pSrc1,
		const QVImage<uChar, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppCmpOp ippCmpOp,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Compare, ippiCompare_8u_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiCompare_16u_C1R
void Compare(
		const QVImage<uShort, 1> & qvimage_pSrc1,
		const QVImage<uShort, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppCmpOp ippCmpOp,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Compare, ippiCompare_16u_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiCompare_16s_C1R
void Compare(
		const QVImage<sShort, 1> & qvimage_pSrc1,
		const QVImage<sShort, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppCmpOp ippCmpOp,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Compare, ippiCompare_16s_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiCompare_32f_C1R
void Compare(
		const QVImage<sFloat, 1> & qvimage_pSrc1,
		const QVImage<sFloat, 1> & qvimage_pSrc2,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppCmpOp ippCmpOp,
		const QPoint &destROIOffset)
	{	CHECK_SAME_ROISIZE(qvimage_pSrc1, qvimage_pSrc2);

	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc1, destROIOffset, 0, 0);

	IPP_DEBUG(Compare, ippiCompare_32f_C1R,
		PDATA_READ(qvimage_pSrc1), qvimage_pSrc1.getStep(),
		PDATA_READ(qvimage_pSrc2), qvimage_pSrc2.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiCompareC_8u_C1R
void CompareC(
		const QVImage<uChar, 1> & qvimage_pSrc,
		const uChar value,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppCmpOp ippCmpOp,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(CompareC, ippiCompareC_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiCompareC_32f_C1R
void CompareC(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		const sFloat value,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppCmpOp ippCmpOp,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(CompareC, ippiCompareC_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		value,
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		ippCmpOp);
	}

// QVision wrapper function for IPP's ippiDilate_8u_C1R
void Dilate(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(Dilate, ippiDilate_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		& pMask,
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiDilate_8u_C3R
void Dilate(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(Dilate, ippiDilate_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		& pMask,
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiDilate_8u_C1IR
void Dilate(
		QVImage<uChar, 1> & qvimage_pSrcDst,
		 const uChar & pMask,
		const QSize &maskSize,
		const QPoint &anchor)
	{
	IPP_DEBUG(Dilate, ippiDilate_8u_C1IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		& pMask,
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiDilate_16u_C1R
void Dilate(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(Dilate, ippiDilate_16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		& pMask,
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiDilate_16u_C3R
void Dilate(
		const QVImage<uShort, 3> & qvimage_pSrc,
		QVImage<uShort, 3> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(Dilate, ippiDilate_16u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		& pMask,
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiDilate_32f_C1R
void Dilate(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(Dilate, ippiDilate_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		& pMask,
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiDilate_32f_C3R
void Dilate(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(Dilate, ippiDilate_32f_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		& pMask,
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiErode_8u_C1R
void Erode(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(Erode, ippiErode_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		& pMask,
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiErode_8u_C3R
void Erode(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(Erode, ippiErode_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		& pMask,
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiErode_8u_C1IR
void Erode(
		QVImage<uChar, 1> & qvimage_pSrcDst,
		 const uChar & pMask,
		const QSize &maskSize,
		const QPoint &anchor)
	{
	IPP_DEBUG(Erode, ippiErode_8u_C1IR,
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst),
		& pMask,
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiErode_16u_C1R
void Erode(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(Erode, ippiErode_16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		& pMask,
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiErode_16u_C3R
void Erode(
		const QVImage<uShort, 3> & qvimage_pSrc,
		QVImage<uShort, 3> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(Erode, ippiErode_16u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		& pMask,
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiErode_32f_C1R
void Erode(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(Erode, ippiErode_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		& pMask,
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiErode_32f_C3R
void Erode(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		 const uChar & pMask,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(Erode, ippiErode_32f_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		& pMask,
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterBox_8u_C1R
void FilterBox(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(FilterBox, ippiFilterBox_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterBox_8u_C3R
void FilterBox(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(FilterBox, ippiFilterBox_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterBox_16u_C1R
void FilterBox(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(FilterBox, ippiFilterBox_16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterBox_32f_C1R
void FilterBox(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(FilterBox, ippiFilterBox_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterMin_8u_C1R
void FilterMin(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(FilterMin, ippiFilterMin_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterMin_8u_C3R
void FilterMin(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(FilterMin, ippiFilterMin_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterMin_16u_C1R
void FilterMin(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(FilterMin, ippiFilterMin_16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterMin_32f_C1R
void FilterMin(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(FilterMin, ippiFilterMin_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterMax_8u_C1R
void FilterMax(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(FilterMax, ippiFilterMax_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterMax_8u_C3R
void FilterMax(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(FilterMax, ippiFilterMax_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterMax_16u_C1R
void FilterMax(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(FilterMax, ippiFilterMax_16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterMax_32f_C1R
void FilterMax(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(FilterMax, ippiFilterMax_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterMedian_8u_C1R
void FilterMedian(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(FilterMedian, ippiFilterMedian_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterMedian_8u_C3R
void FilterMedian(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(FilterMedian, ippiFilterMedian_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterMedian_16u_C1R
void FilterMedian(
		const QVImage<uShort, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		const QSize &maskSize,
		const QPoint &anchor,
		const QPoint &destROIOffset)
	{
	const int colMaskRadius = maskSize.width(), rowMaskRadius = maskSize.height();
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, colMaskRadius-1, rowMaskRadius-1);

	IPP_DEBUG(FilterMedian, ippiFilterMedian_16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		IPP_SIZE_FROM_QSIZE(maskSize),
		IPP_POINT_FROM_QPOINT(anchor));
	}

// QVision wrapper function for IPP's ippiFilterMedianHoriz_8u_C1R
void FilterMedianHoriz(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterMedianHoriz, ippiFilterMedianHoriz_8u_C1R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterMedianVert_8u_C1R
void FilterMedianVert(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterMedianVert, ippiFilterMedianVert_8u_C1R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterMedianCross_8u_C1R
void FilterMedianCross(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterMedianCross, ippiFilterMedianCross_8u_C1R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterMedianWeightedCenter3x3_8u_C1R
// Filter an image using a median filter with kernel size 3x3 and enlarged weight of central pixel.
void FilterMedianWeightedCenter3x3(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const int weight,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(FilterMedianWeightedCenter3x3, ippiFilterMedianWeightedCenter3x3_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		weight);
	}

// QVision wrapper function for IPP's ippiFilterMedianColor_8u_C3R
void FilterMedianColor(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterMedianColor, ippiFilterMedianColor_8u_C3R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterSobelHorizMask_32f_C1R
void FilterSobelHorizMask(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterSobelHorizMask, ippiFilterSobelHorizMask_32f_C1R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterSobelVertMask_32f_C1R
void FilterSobelVertMask(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterSobelVertMask, ippiFilterSobelVertMask_32f_C1R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterLaplace_8u_C1R
void FilterLaplace(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterLaplace, ippiFilterLaplace_8u_C1R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterLaplace_16s_C1R
void FilterLaplace(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterLaplace, ippiFilterLaplace_16s_C1R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterLaplace_32f_C1R
void FilterLaplace(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterLaplace, ippiFilterLaplace_32f_C1R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterGauss_8u_C1R
void FilterGauss(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterGauss, ippiFilterGauss_8u_C1R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterGauss_32f_C1R
void FilterGauss(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterGauss, ippiFilterGauss_32f_C1R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterGauss_8u_C3R
void FilterGauss(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterGauss, ippiFilterGauss_8u_C3R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterGauss_32f_C3R
void FilterGauss(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterGauss, ippiFilterGauss_32f_C3R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterHipass_8u_C1R
void FilterHipass(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterHipass, ippiFilterHipass_8u_C1R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterHipass_8u_C3R
void FilterHipass(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterHipass, ippiFilterHipass_8u_C3R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterHipass_32f_C1R
void FilterHipass(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterHipass, ippiFilterHipass_32f_C1R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterHipass_32f_C3R
void FilterHipass(
		const QVImage<sFloat, 3> & qvimage_pSrc,
		QVImage<sFloat, 3> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterHipass, ippiFilterHipass_32f_C3R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterLowpass_8u_C1R
void FilterLowpass(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterLowpass, ippiFilterLowpass_8u_C1R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiFilterLowpass_32f_C1R
void FilterLowpass(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const IppiMaskSize mask,
		const QPoint &destROIOffset)
	{
	const int maskCols = IPP_MASK_SIZE_COLS(mask)-1, maskRows = IPP_MASK_SIZE_ROWS(mask)-1;
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, maskCols, maskRows);

	IPP_DEBUG(FilterLowpass, ippiFilterLowpass_32f_C1R,
		PDATA_READ_MARGIN(qvimage_pSrc, maskCols/2, maskRows/2), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		mask);
	}

// QVision wrapper function for IPP's ippiSum_8u_C1R
void Sum(
		const QVImage<uChar, 1> & qvimage_pSrc,
		 sDouble & pSum)
	{
	IPP_DEBUG(Sum, ippiSum_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		& pSum);
	}

// QVision wrapper function for IPP's ippiSum_8u_C3R
void Sum(
		const QVImage<uChar, 3> & qvimage_pSrc,
		sDouble sum[3])
	{
	IPP_DEBUG(Sum, ippiSum_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		sum);
	}

// QVision wrapper function for IPP's ippiSum_16s_C1R
void Sum(
		const QVImage<sShort, 1> & qvimage_pSrc,
		 sDouble & pSum)
	{
	IPP_DEBUG(Sum, ippiSum_16s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		& pSum);
	}

// QVision wrapper function for IPP's ippiSum_16s_C3R
void Sum(
		const QVImage<sShort, 3> & qvimage_pSrc,
		sDouble sum[3])
	{
	IPP_DEBUG(Sum, ippiSum_16s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		sum);
	}

// QVision wrapper function for IPP's ippiIntegral_8u32s_C1R
void Integral(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sInt, 1> & qvimage_pDst,
		const sInt val,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Integral, ippiIntegral_8u32s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		val);
	}

// QVision wrapper function for IPP's ippiIntegral_8u32f_C1R
void Integral(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const sFloat val,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Integral, ippiIntegral_8u32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		val);
	}

// QVision wrapper function for IPP's ippiMean_8u_C1R
void Mean(
		const QVImage<uChar, 1> & qvimage_pSrc,
		 sDouble & pMean)
	{
	IPP_DEBUG(Mean, ippiMean_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		& pMean);
	}

// QVision wrapper function for IPP's ippiMean_8u_C3R
void Mean(
		const QVImage<uChar, 3> & qvimage_pSrc,
		sDouble mean[3])
	{
	IPP_DEBUG(Mean, ippiMean_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		mean);
	}

// QVision wrapper function for IPP's ippiMean_16s_C1R
void Mean(
		const QVImage<sShort, 1> & qvimage_pSrc,
		 sDouble & pMean)
	{
	IPP_DEBUG(Mean, ippiMean_16s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		& pMean);
	}

// QVision wrapper function for IPP's ippiMean_16s_C3R
void Mean(
		const QVImage<sShort, 3> & qvimage_pSrc,
		sDouble mean[3])
	{
	IPP_DEBUG(Mean, ippiMean_16s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		mean);
	}

// QVision wrapper function for IPP's ippiMin_8u_C1R
void Min(
		const QVImage<uChar, 1> & qvimage_pSrc,
		 uChar & pMin)
	{
	IPP_DEBUG(Min, ippiMin_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		& pMin);
	}

// QVision wrapper function for IPP's ippiMin_8u_C3R
void Min(
		const QVImage<uChar, 3> & qvimage_pSrc,
		uChar min[3])
	{
	IPP_DEBUG(Min, ippiMin_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		min);
	}

// QVision wrapper function for IPP's ippiMin_16s_C1R
void Min(
		const QVImage<sShort, 1> & qvimage_pSrc,
		 sShort & pMin)
	{
	IPP_DEBUG(Min, ippiMin_16s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		& pMin);
	}

// QVision wrapper function for IPP's ippiMin_16s_C3R
void Min(
		const QVImage<sShort, 3> & qvimage_pSrc,
		sShort min[3])
	{
	IPP_DEBUG(Min, ippiMin_16s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		min);
	}

// QVision wrapper function for IPP's ippiMin_32f_C1R
void Min(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		 sFloat & pMin)
	{
	IPP_DEBUG(Min, ippiMin_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		& pMin);
	}

// QVision wrapper function for IPP's ippiMax_8u_C1R
void Max(
		const QVImage<uChar, 1> & qvimage_pSrc,
		 uChar & pMax)
	{
	IPP_DEBUG(Max, ippiMax_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		& pMax);
	}

// QVision wrapper function for IPP's ippiMax_8u_C3R
void Max(
		const QVImage<uChar, 3> & qvimage_pSrc,
		uChar max[3])
	{
	IPP_DEBUG(Max, ippiMax_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		max);
	}

// QVision wrapper function for IPP's ippiMax_16s_C1R
void Max(
		const QVImage<sShort, 1> & qvimage_pSrc,
		 sShort & pMax)
	{
	IPP_DEBUG(Max, ippiMax_16s_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		& pMax);
	}

// QVision wrapper function for IPP's ippiMax_16s_C3R
void Max(
		const QVImage<sShort, 3> & qvimage_pSrc,
		sShort max[3])
	{
	IPP_DEBUG(Max, ippiMax_16s_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		max);
	}

// QVision wrapper function for IPP's ippiMax_32f_C1R
void Max(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		 sFloat & pMax)
	{
	IPP_DEBUG(Max, ippiMax_32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		IMAGE_ROISIZE(qvimage_pSrc),
		& pMax);
	}

// QVision wrapper function for IPP's ippiMinEvery_8u_C1IR
void MinEvery(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pSrcDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pSrcDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MinEvery, ippiMinEvery_8u_C1IR,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst));
	}

// QVision wrapper function for IPP's ippiMinEvery_8u_C3IR
void MinEvery(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pSrcDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pSrcDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MinEvery, ippiMinEvery_8u_C3IR,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst));
	}

// QVision wrapper function for IPP's ippiMinEvery_16s_C1IR
void MinEvery(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pSrcDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pSrcDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MinEvery, ippiMinEvery_16s_C1IR,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst));
	}

// QVision wrapper function for IPP's ippiMinEvery_16s_C3IR
void MinEvery(
		const QVImage<sShort, 3> & qvimage_pSrc,
		QVImage<sShort, 3> & qvimage_pSrcDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pSrcDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MinEvery, ippiMinEvery_16s_C3IR,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst));
	}

// QVision wrapper function for IPP's ippiMinEvery_32f_C1IR
void MinEvery(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pSrcDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pSrcDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MinEvery, ippiMinEvery_32f_C1IR,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst));
	}

// QVision wrapper function for IPP's ippiMaxEvery_8u_C1IR
void MaxEvery(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pSrcDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pSrcDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MaxEvery, ippiMaxEvery_8u_C1IR,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst));
	}

// QVision wrapper function for IPP's ippiMaxEvery_8u_C3IR
void MaxEvery(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pSrcDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pSrcDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MaxEvery, ippiMaxEvery_8u_C3IR,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst));
	}

// QVision wrapper function for IPP's ippiMaxEvery_16s_C1IR
void MaxEvery(
		const QVImage<sShort, 1> & qvimage_pSrc,
		QVImage<sShort, 1> & qvimage_pSrcDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pSrcDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MaxEvery, ippiMaxEvery_16s_C1IR,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst));
	}

// QVision wrapper function for IPP's ippiMaxEvery_16s_C3IR
void MaxEvery(
		const QVImage<sShort, 3> & qvimage_pSrc,
		QVImage<sShort, 3> & qvimage_pSrcDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pSrcDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MaxEvery, ippiMaxEvery_16s_C3IR,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst));
	}

// QVision wrapper function for IPP's ippiMaxEvery_32f_C1IR
void MaxEvery(
		const QVImage<sFloat, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pSrcDst,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pSrcDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MaxEvery, ippiMaxEvery_32f_C1IR,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pSrcDst), qvimage_pSrcDst.getStep(),
		IMAGE_ROISIZE(qvimage_pSrcDst));
	}

// QVision wrapper function for IPP's ippiCanny_16s8u_C1R
void Canny(
		QVImage<sShort, 1> & qvimage_pSrcDx,
		QVImage<sShort, 1> & qvimage_pSrcDy,
		QVImage<uChar, 1> & qvimage_pDstEdges,
		const sFloat lowThresh,
		const sFloat highThresh,
		QVImage<uChar, 1> & qvimage_pBuffer)
	{
	IPP_DEBUG(Canny, ippiCanny_16s8u_C1R,
		PDATA_WRITE(qvimage_pSrcDx), qvimage_pSrcDx.getStep(),
		PDATA_WRITE(qvimage_pSrcDy), qvimage_pSrcDy.getStep(),
		PDATA_WRITE(qvimage_pDstEdges), qvimage_pDstEdges.getStep(),
		IMAGE_ROISIZE(qvimage_pDstEdges),
		lowThresh,
		highThresh,
		qvimage_pBuffer.getWriteData());
	}

// QVision wrapper function for IPP's ippiCanny_32f8u_C1R
void Canny(
		QVImage<sFloat, 1> & qvimage_pSrcDx,
		QVImage<sFloat, 1> & qvimage_pSrcDy,
		QVImage<uChar, 1> & qvimage_pDstEdges,
		const sFloat lowThresh,
		const sFloat highThresh,
		QVImage<uChar, 1> & qvimage_pBuffer)
	{
	IPP_DEBUG(Canny, ippiCanny_32f8u_C1R,
		PDATA_WRITE(qvimage_pSrcDx), qvimage_pSrcDx.getStep(),
		PDATA_WRITE(qvimage_pSrcDy), qvimage_pSrcDy.getStep(),
		PDATA_WRITE(qvimage_pDstEdges), qvimage_pDstEdges.getStep(),
		IMAGE_ROISIZE(qvimage_pDstEdges),
		lowThresh,
		highThresh,
		qvimage_pBuffer.getWriteData());
	}

// QVision wrapper function for IPP's ippiMinEigenVal_8u32f_C1R
void MinEigenVal(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pMinEigenVal,
		const IppiKernelType kernType,
		const int apertureSize,
		const int avgWindow,
		QVImage<uChar, 1> & qvimage_pBuffer,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pMinEigenVal, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(MinEigenVal, ippiMinEigenVal_8u32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pMinEigenVal), qvimage_pMinEigenVal.getStep(),
		IMAGE_ROISIZE(qvimage_pMinEigenVal),
		kernType,
		apertureSize,
		avgWindow,
		qvimage_pBuffer.getWriteData());
	}

// QVision wrapper function for IPP's ippiDistanceTransform_5x5_8u16u_C1R
void DistanceTransform_5x5(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uShort, 1> & qvimage_pDst,
		 sInt & pMetrics,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(DistanceTransform_5x5, ippiDistanceTransform_5x5_8u16u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		& pMetrics);
	}

// QVision wrapper function for IPP's ippiFastMarching_8u32f_C1R
// Calculate distance transform by fast marching method.
void FastMarching(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<sFloat, 1> & qvimage_pDst,
		const sFloat radius,
		QVImage<uChar, 1> & qvimage_pBuffer,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(FastMarching, ippiFastMarching_8u32f_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		radius,
		qvimage_pBuffer.getWriteData());
	}

// QVision wrapper function for IPP's ippiInpaint_8u_C1R
void Inpaint(
		const QVImage<uChar, 1> & qvimage_pSrc,
		QVImage<uChar, 1> & qvimage_pDst,
		 IppiInpaintState_8u_C1R & pState,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Inpaint, ippiInpaint_8u_C1R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		& pState);
	}

// QVision wrapper function for IPP's ippiInpaint_8u_C3R
// Restores damaged image area by direct inpainting.
void Inpaint(
		const QVImage<uChar, 3> & qvimage_pSrc,
		QVImage<uChar, 3> & qvimage_pDst,
		 IppiInpaintState_8u_C1R & pState,
		const QPoint &destROIOffset)
	{
	COMPOSE_ROI(qvimage_pDst, qvimage_pSrc, destROIOffset, 0, 0);

	IPP_DEBUG(Inpaint, ippiInpaint_8u_C3R,
		PDATA_READ(qvimage_pSrc), qvimage_pSrc.getStep(),
		PDATA_WRITE(qvimage_pDst), qvimage_pDst.getStep(),
		IMAGE_ROISIZE(qvimage_pDst),
		& pState);
	}

