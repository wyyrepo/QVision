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
/// @author Copyright (C) PARP Research Group. University of Murcia, Spain.

#ifndef QVIPP_H
#define QVIPP_H

#include <ipp.h>

#include <QMap>
#include <QSize>
#include <QPoint>
#include <QVImage>
#include <QVIndexedStringList>

class QVMatrix;
class QVVector;

#include <qvipp/qvippfunctions.h>

/*!
@todo Problema con las funciones IPP: al llamar a una función no inline con la misma imagen de entrada que de salida, por ejemplo:

@code
QVImage<uChar> image = ...;
FilterBox(image, image);
@endcode

Los bufferes que se le pasarán a la llamada de la ippiFilterBox serán los mismos. El código correcto, que sí funciona, sería este:

@code
QVImage<uChar> image = ... , temp = image;
FilterBox(temp, image);
@endcode
*/

/// @brief Composes color image from separate channel images
/// @ingroup qvippIDEAIF
///
/// This function copies data from a source 1-channel image ROI src, to each of the channels of the destination 3-channel image ROI 
/// dest.
///
/// @param src1 source image for first channel.
/// @param src2 source image for second channel.
/// @param src3 source image for third channel.
/// @param dest destination image.
void Copy(const QVImage<uChar, 1> &src1, const QVImage<uChar, 1> &src2, const QVImage<uChar, 1> &src3, QVImage<uChar, 3> &dest,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Composes color image from separate channel images
/// @ingroup qvippIDEAIF
/// @see Copy(const QVImage<uChar, 1> &, const QVImage<uChar, 1> &, const QVImage<uChar, 1> &, QVImage<uChar, 3> &)
void Copy(const QVImage<uShort, 1> &src1, const QVImage<uShort, 1> &src2, const QVImage<uShort, 1> &src3, QVImage<uShort, 3> &dest,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Composes color image from separate channel images
/// @ingroup qvippIDEAIF
/// @see Copy(const QVImage<uChar, 1> &, const QVImage<uChar, 1> &, const QVImage<uChar, 1> &, QVImage<uChar, 3> &)
void Copy(const QVImage<sShort, 1> &src1, const QVImage<sShort, 1> &src2, const QVImage<sShort, 1> &src3, QVImage<sShort, 3> &dest,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Composes color image from separate channel images
/// @ingroup qvippIDEAIF
/// @see Copy(const QVImage<uChar, 1> &, const QVImage<uChar, 1> &, const QVImage<uChar, 1> &, QVImage<uChar, 3> &)
void Copy(const QVImage<sInt, 1> &src1, const QVImage<sInt, 1> &src2, const QVImage<sInt, 1> &src3, QVImage<sInt, 3> &dest,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Composes color image from separate channel images
/// @ingroup qvippIDEAIF
/// @see Copy(const QVImage<uChar, 1> &, const QVImage<uChar, 1> &, const QVImage<uChar, 1> &, QVImage<uChar, 3> &)
void Copy(const QVImage<sFloat, 1> &src1, const QVImage<sFloat, 1> &src2, const QVImage<sFloat, 1> &src3, QVImage<sFloat, 3> &dest,  const QPoint &destROIOffset = QPoint(0,0));

/// @todo Document.
/// @ingroup qvippIDEAIF
void Copy(const QVImage<uChar, 3> &src, QVImage<uChar, 1> &dest1, QVImage<uChar, 1> &dest2, QVImage<uChar, 1> &dest3, const QPoint &destROIOffset = QPoint(0,0));

/// @todo Document.
/// @ingroup qvippIDEAIF
void Copy(const QVImage<sFloat, 3> &src, QVImage<sFloat, 1> &dest1, QVImage<sFloat, 1> &dest2, QVImage<sFloat, 1> &dest3, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Copy a selected channel from a 3-channel image to a 1-channel image
/// @ingroup qvippIDEAIF
///
/// This function converts an RGB image to gray scale.
///
/// @param src source image.
/// @param dest destination image.
/// @param channel number of channel to copy.
void Copy(const QVImage<uChar, 3> &src, const uChar channel, QVImage<uChar, 1> &dest,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Copy a selected channel from a 3-channel image to a 1-channel image
/// @ingroup qvippIDEAIF
/// @see Copy(const QVImage<uChar, 3> &, QVImage<uChar, 1> &, uChar)
void Copy(const QVImage<uShort, 3> &src, const uChar channel, QVImage<uShort, 1> &dest,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Copy a selected channel from a 3-channel image to a 1-channel image
/// @ingroup qvippIDEAIF
/// @see Copy(const QVImage<uChar, 3> &, QVImage<uChar, 1> &, uChar)
void Copy(const QVImage<sShort, 3> &src, const uChar channel, QVImage<sShort, 1> &dest,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Copy a selected channel from a 3-channel image to a 1-channel image
/// @ingroup qvippIDEAIF
/// @see Copy(const QVImage<uChar, 3> &, QVImage<uChar, 1> &, uChar)
void Copy(const QVImage<sInt, 3> &src, const uChar channel, QVImage<sInt, 1> &dest,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Copy a selected channel from a 3-channel image to a 1-channel image
/// @ingroup qvippIDEAIF
/// @see Copy(const QVImage<uChar, 3> &, QVImage<uChar, 1> &, uChar)
void Copy(const QVImage<sFloat, 3> &src, const uChar channel, QVImage<sFloat, 1> &dest,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Compares pixel values of two images using a specified compare operation.
/// @ingroup qvippIDEAIF
/// @see void Compare(const QVImage<uChar> &, const QVImage<uChar> &src2, QVImage<uChar> &, IppCmpOp)
void Compare(const QVImage<uChar,3> &src1, const QVImage<uChar,3> &src2, QVImage<uChar> &dest, IppCmpOp ippCmpOp = ippCmpEq,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Compares pixel values of two images using a specified compare operation.
/// @ingroup qvippTACO
/// @see void Compare(const QVImage<uChar> &, const QVImage<uChar> &src2, QVImage<uChar> &, IppCmpOp)
void Compare(const QVImage<uShort,3> &src1, const QVImage<uShort,3> &src2, QVImage<uChar> &dest, IppCmpOp ippCmpOp = ippCmpEq,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Compares pixel values of two images using a specified compare operation.
/// @ingroup qvippTACO
/// @see void Compare(const QVImage<uChar> &, const QVImage<uChar> &src2, QVImage<uChar> &, IppCmpOp)
void Compare(const QVImage<sShort,3> &src1, const QVImage<sShort,3> &src2, QVImage<uChar> &dest, IppCmpOp ippCmpOp = ippCmpEq,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Compares pixel values of two images using a specified compare operation.
/// @ingroup qvippTACO
/// @see void Compare(const QVImage<uChar> &, const QVImage<uChar> &src2, QVImage<uChar> &, IppCmpOp)
void Compare(const QVImage<sFloat,3> &src1, const QVImage<sFloat,3> &src2, QVImage<uChar> &dest, IppCmpOp ippCmpOp = ippCmpEq,  const QPoint &destROIOffset = QPoint(0,0));

/// @todo document this
/// @ingroup qvippICC
void YUV420ToRGB(const QVImage<uChar, 1> &srcY, const QVImage<uChar, 1> &srcU, const QVImage<uChar, 1> &srcV,
	QVImage<uChar, 3> &destRGB,  const QPoint &destROIOffset = QPoint(0,0));

/// @todo document this
/// @ingroup qvippICC
void RGBToYUV420(const QVImage<uChar, 3> &src, QVImage<uChar, 1> &dst1, QVImage<uChar, 1> &dst2, QVImage<uChar, 1> &dst3,
	const QPoint &destROIOffset = QPoint(0,0));

/// @brief This function uses the general square kernel defined in the matrix <i>kernel</i> to filter an image, using a convolution operation.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
/// @param kernel matrix containing filter kernel.
void Filter(const QVImage<sFloat> &src, QVImage<sFloat> &dest, const QVMatrix kernel, const QPoint &destROIOffset = QPoint(0,0));


/// @brief Filters an image using a spatial kernel that consists of a single column.
/// @ingroup qvippFF
///
/// This function uses the vertical column kernel contained in vector <i>kernel</i> to filter an image ROI.
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
/// @param kernel vector containing the kernel to filter.
void FilterColumn(const QVImage<sFloat> &src, QVImage<sFloat> &dest, const QVVector kernel, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Filters an image using a spatial kernel that consists of a single row.
/// @ingroup qvippFF
///
/// This function uses the vertical column kernel contained in vector <i>kernel</i> to filter an image ROI.
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
/// @param kernel vector containing the kernel to filter.
void FilterRow(const QVImage<sFloat> &src, QVImage<sFloat> &dest, const QVVector kernel, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Filters an image using a sharpening filter.
/// @ingroup qvippFF
///
/// This function applies a sharpening filter to an image ROI.
/// The corresponding kernel is the matrix of 3x3 size with the following values:
///
/// \f$ \left| \begin{array}{ccc} -1/8 & -1/8 & -1/8 \\ -1/8 & 16/8 & -1/8 \\ -1/8 & -1/8 & -1/8 \\ \end{array} \right| \f$
///
/// This filter enhances high-frequency components and thus sharpens an image.
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void FilterSharpen(const QVImage<uChar> &src, QVImage<uChar> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Filters an image using a sharpening filter.
/// @ingroup qvippFF
/// @see FilterSharpen(const QVImage<uChar> &, QVImage<uChar> &)
void FilterSharpen(const QVImage<sFloat> &src, QVImage<sFloat> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a morphological Erode3x3 filter.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void Erode3x3(const QVImage<uChar> &src, QVImage<uChar> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a morphological Erode3x3 filter.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void Erode3x3(const QVImage<uShort> &src, QVImage<uShort> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a morphological Erode3x3 filter.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void Erode3x3(const QVImage<sFloat> &src, QVImage<sFloat> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a morphological Erode3x3 filter.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void Erode3x3(const QVImage<uChar,3> &src, QVImage<uChar,3> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a morphological Erode3x3 filter.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void Erode3x3(const QVImage<uShort,3> &src, QVImage<uShort,3> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a morphological Erode3x3 filter.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void Erode3x3(const QVImage<sFloat,3> &src, QVImage<sFloat,3> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a morphological Dilate3x3 filter.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void Dilate3x3(const QVImage<uChar> &src, QVImage<uChar> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a morphological Dilate3x3 filter.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void Dilate3x3(const QVImage<uShort> &src, QVImage<uShort> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a morphological Dilate3x3 filter.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void Dilate3x3(const QVImage<sFloat> &src, QVImage<sFloat> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a morphological Dilate3x3 filter.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void Dilate3x3(const QVImage<uChar,3> &src, QVImage<uChar,3> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a morphological Dilate3x3 filter.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void Dilate3x3(const QVImage<uShort,3> &src, QVImage<uShort,3> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a morphological Dilate3x3 filter.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void Dilate3x3(const QVImage<sFloat,3> &src, QVImage<sFloat,3> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a horizontal Sobel derivative filter (3x3) to an image.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void FilterSobelHoriz(const QVImage<uChar> &src, QVImage<uChar> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a horizontal Sobel derivative filter (3x3) to an image.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void FilterSobelHoriz(const QVImage<sShort> &src, QVImage<sShort> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a horizontal Sobel derivative filter (3x3) to an image.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void FilterSobelHoriz(const QVImage<sFloat> &src, QVImage<sFloat> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a horizontal Sobel derivative filter (3x3) to an image.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void FilterSobelHoriz(const QVImage<uChar,3> &src, QVImage<uChar,3> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a horizontal Sobel derivative filter (3x3) to an image.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void FilterSobelHoriz(const QVImage<sShort,3> &src, QVImage<sShort,3> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a horizontal Sobel derivative filter (3x3) to an image.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void FilterSobelHoriz(const QVImage<sFloat,3> &src, QVImage<sFloat,3> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a vertical Sobel derivative filter (3x3) to an image.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void FilterSobelVert(const QVImage<uChar> &src, QVImage<uChar> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a vertical Sobel derivative filter (3x3) to an image.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void FilterSobelVert(const QVImage<sShort> &src, QVImage<sShort> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a vertical Sobel derivative filter (3x3) to an image.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void FilterSobelVert(const QVImage<sFloat> &src, QVImage<sFloat> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a vertical Sobel derivative filter (3x3) to an image.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void FilterSobelVert(const QVImage<uChar,3> &src, QVImage<uChar,3> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a vertical Sobel derivative filter (3x3) to an image.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void FilterSobelVert(const QVImage<sShort,3> &src, QVImage<sShort,3> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies a vertical Sobel derivative filter (3x3) to an image.
/// @ingroup qvippFF
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
void FilterSobelVert(const QVImage<sFloat,3> &src, QVImage<sFloat,3> &dest, const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies horizontal Sobel filter with border.
/// @ingroup qvippFF
///
/// This function is similar to FilterSobelHorizMask, but automatically creates a required border and
/// define appropriate pixel values.
///
/// Function FilterSobelHorizGetBufferSize should be used to initialize sizes for a buffer QVImage<uChar>
/// image, which will hold temporary data for the function operations.
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
/// @param buffer buffer image to hold temporal data during function operation.
/// @param maskSize size of mask. Should be 3 (for mask of size 3x3) or 5 (for mask of size 5x5).
/// @see FilterSobelHorizGetBufferSize
void FilterSobelHorizBorder(const QVImage<uChar> &src, QVImage<sShort> &dest, const IppiMaskSize maskSize,
	const IppiBorderType borderType, const uChar borderValue, QVImage<uChar> &buffer,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Applies vertical Sobel filter with border.
/// @ingroup qvippFF
///
/// This function is similar to FilterSobelVertMask, but uses negative values for the mask applied,
/// and automatically create a required border and define appropriate pixel values.
///
/// Function FilterSobelNegVertGetBufferSize should be used to initialize sizes for a buffer QVImage<uChar>
/// image, which will hold temporary data for the function operations.
///
/// @param src source image to filter.
/// @param dest destination image to hold the resulting image after filtering.
/// @param buffer buffer image to hold temporal data during function operation.
/// @param maskSize size of mask. Should be 3 (for mask of size 3x3) or 5 (for mask of size 5x5).
/// @see FilterSobelNegVertGetBufferSize
void FilterSobelNegVertBorder(const QVImage<uChar> &src, QVImage<sShort> &dest, const IppiMaskSize maskSize,
	const IppiBorderType borderType, const uChar borderValue, QVImage<uChar> &buffer,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Changes an image size.
/// @ingroup qvippIGT
///
/// This function copies the content of the ROI in the source image, to the ROI of the
/// destination image, adjusting it's original size to make it fit in the destination size
/// It has the effect of resizing the original image, to fit the destination image, if both ROI's
/// hold the whole of their respective images.
///
///	- IPPI_INTER_NN. Nearest neighbor interpolation
///	- IPPI_INTER_LINEAR. Linear interpolation
///	- IPPI_INTER_CUBIC. Cubic interpolation
///	- IPPI_INTER_SUPER. Supersampling interpolation, cannot be applied for image enlarging
///	- IPPI_INTER_LANCZOS. Interpolation with Lanczos window.
void Resize(const QVImage<uChar> &src, QVImage<uChar> &dest, int interpolation = IPPI_INTER_LINEAR);

/// @brief Changes an image size.
/// @ingroup qvippIGT
/// @see Resize(const QVImage<uChar> &, QVImage<uChar> &, int)
void Resize(const QVImage<sFloat> &src, QVImage<sFloat> &dest, int interpolation = IPPI_INTER_LINEAR);

/// @brief Changes an image size.
/// @ingroup qvippIGT
/// @see Resize(const QVImage<uShort> &, QVImage<uShort> &, int)
void Resize(const QVImage<uShort> &src, QVImage<uShort> &dest, int interpolation = IPPI_INTER_LINEAR);


/// @brief Changes an image size.
/// @ingroup qvippIGT
/// @see Resize(const QVImage<uChar> &, QVImage<uChar> &, int)
void Resize(const QVImage<uChar,3> &src, QVImage<uChar,3> &dest, int interpolation = IPPI_INTER_LINEAR);

/// @brief Allocates size in a buffer image for temporary data for function Canny.
/// @ingroup qvippCV
///
/// This function should be applied to any QVImage<uChar> image to be used as a buffer image for function
/// Canny. Initializes dimensions for that buffer image, appropriated for canny algorithm.
///
/// @param src source image to apply later Canny operator.
/// @param buffer buffer image to initialize for further operations.
/// @see Canny
void CannyGetSize(const QVGenericImage &src, QVImage<uChar> &buffer);

/// @brief Allocates size in a buffer image for temporary data for function FilterSobelHoriz.
/// @ingroup qvippFF
///
/// This function should be applied to any QVImage<uChar> image to be used as a buffer image for function
/// FilterSobelHoriz. Initializes dimensions for that buffer image, appropriated for that algorithm.
///
/// @param src source image to apply later filter.
/// @param buffer buffer image to initialize for further operations.
/// @param maskSize size of mask. Should be 3 (for mask of size 3x3) or 5 (for mask of size 5x5).
/// @see FilterSobelHoriz
void FilterSobelHorizGetBufferSize(const QVGenericImage &src, const IppiMaskSize maskSize, QVImage<uChar> &buffer);

/// @brief Allocates size in a buffer image for temporary data for function FilterSobelNegVert.
/// @ingroup qvippFF
///
/// This function should be applied to any QVImage<uChar> image to be used as a buffer image for function
/// FilterSobelNegVert. Initializes dimensions for that buffer image, appropriated for that algorithm.
///
/// @param src source image to apply later filter.
/// @param buffer buffer image to initialize for further operations.
/// @param maskSize size of mask. Should be 3 (for mask of size 3x3) or 5 (for mask of size 5x5).
/// @see FilterSobelNegVert
void FilterSobelNegVertGetBufferSize(const QVGenericImage &src, const IppiMaskSize maskSize, QVImage<uChar> &buffer);

/// @brief Allocates size in a buffer image for temporary data for function MinEigenValGet.
/// @ingroup qvippCV
///
/// This function should be applied to any QVImage<uChar> image to be used as a buffer image for function
/// MinEigenVal. Initializes dimensions for that buffer image, appropriated for that algorithm.
///
/// @param src source image to apply later MinEigenVal function.
/// @param buffer buffer image to initialize for further operations.
/// @param apertureSize Size (in pixels) of the derivative operator used by the function, possible values are 3 or 5.
/// @param avgWindow Size of the blurring window in pixels, possible values are 3 or 5.
/// @see MinEigenVal
void MinEigenValGetBufferSize( const QVGenericImage &src, QVImage<uChar> &buffer, uInt apertureSize = 5, uInt avgWindow = 5);

/// @brief Allocates size in a buffer image for temporary data for function family FloodFill.
/// @ingroup qvippCV
///
/// This function should be applied to any QVImage<uChar> image to be used as a buffer image for function
/// family FloodFill. Initializes dimensions for that buffer image, appropriated for that algorithm.
///
/// @param src source image to apply later flood fill function.
/// @param buffer buffer image to initialize for further operations.
/// @see FloodFillRange
void FloodFillGetSize(const QVGenericImage &src, QVImage<uChar> &buffer);

/// @brief Calculates the minimal eigen value of image blocks for corner detection.
/// @ingroup qvippCV
///
/// This function takes a block around the pixel and computes the first derivatives Dx and Dy.
///
/// This operation is performed for every pixel of the image using either Sobel or Scharr kernel
/// in accordance with the kernType parameter.
///
/// The size of the Sobel kernel may be specified the parameter apertureSize.
/// If this parameter is set to 3 - the function used 3x3 kernel, if it set to 5 - the function uses 5x5 kernel.
///
/// Only 3x3 size is available for the Scharr kernel, therefore the parameter apertureSize must be set to
/// 3 if the Scharr kernel is used.
///
/// @param src source image.
/// @param dest destination image to hold the minimal eigen values.
/// @param buffer image to hold temporary data during function operations.
/// @param apertureSize Size (in pixels) of the derivative operator used by the function, possible values are 3 or 5.
/// @param avgWindow Size of the blurring window in pixels, possible values are 3 (3x3 mask size) or 5 (5x5 mask size).
/// @param kernel Specifies the type of kernel used to compute derivatives, possible values are:
///	- ippKernelSobel. Values for aperture size can be 3, or 5.
///	- ippKernelScharr. Value for aperture size can only be 3.
/// @see MinEigenValGetBufferSize
void MinEigenVal(const QVImage<uChar> &src, QVImage<sFloat> &dest, QVImage<uChar> &buffer,
	uInt apertureSize = 3, uInt avgWindow = 5, IppiKernelType kernel = ippKernelSobel,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Allocates size in a buffer image for temporary data for function FastMarching.
/// @ingroup qvippCV
///
/// This function should be applied to any QVImage<uChar> image to be used as a buffer image for function
/// FastMarching. Initializes dimensions for that buffer image, appropriated for that algorithm.
///
/// @param image source image to apply Fast Marching algorithm.
/// @param buffer buffer image to initialize for further operations.
/// @see FastMarching
void FastMarchingGetBufferSize(const QVGenericImage &image, QVImage<uChar> &buffer);

/// @todo Document.
/// @ingroup qvippCV
void InpaintInitAllocC3(IppiInpaintState_8u_C3R **pState, const QVImage<sFloat> &distances, const QVImage<uChar> &mask,
	const sFloat radius, const IppiInpaintFlag flag);

/// @todo Document.
/// @ingroup qvippCV
void InpaintFreeC3(IppiInpaintState_8u_C3R *pState);

/// @todo Document.
/// @ingroup qvippCV
void InpaintInitAllocC1(IppiInpaintState_8u_C1R **pState, const QVImage<sFloat> &distances, const QVImage<uChar> &mask,
	const sFloat radius, const IppiInpaintFlag flag);

/// @todo Document.
/// @ingroup qvippCV
void InpaintFreeC1(IppiInpaintState_8u_C1R *pState);

/// @brief Calculates frequency histogram for a given set of values, for a QVImage
/// @ingroup qvipp
///
/// This function computes the intensity histogram of an image in the ranges specified by the QList 'values'.
/// Default value for this QList is empty list, indicating the set of integer which cover the group of valid values for
/// uChar type (from 0 to 255).
///
/// \todo fill pLevels array with values from QList 'values'
///
/// @param src source image to obtain histogram values.
/// @param values list of QVImage data type values, to obtain frequency in histogram.
/// @return  a QMap variable, that maps pixel values, with their frequency of depicting in the image.
QMap<sInt, int> HistogramRange(const QVImage<uChar, 1> &src, QList<uChar> values);

/// @brief Calculates frequency histogram for a given set of values, for a QVImage
/// @ingroup qvipp
///
/// This function computes the intensity histogram of an image in the ranges from 0 to 255.
///
/// @param src source image to obtain histogram values.
/// @returns a QVector list of 256 integer values, that maps pixel values, with their frequency of apperance
/// in the image.
QVector<int> HistogramRange(const QVImage<uChar, 1> &src);

/// @brief Performs flood filling of pixels with values in the specified range in the connected area on an image.
/// @ingroup qvippCV
///
/// This function performs flood filling of the group of connected pixels in the seed pixel
/// neighborhoods whose pixel values \f$ v_i \f$ satisfies the following condition:
///
/// \f$ v_i - minDelta \leq v_0 \leq v_i + maxDelta \f$
/// 
/// where \f$ v_0 \f$ is the pixel value of the seed point. Values of these pixel is set to the <i>newVal</i> value.
///
/// The function check 4-connected neighborhood of each pixel, i.e., side neighbors.
///
/// The function requires a temporary buffer whose size should be computed with the function
/// @ref FloodFillGetSize beforehand.
///
/// @param img image to flood fill.
/// @param buffer temporary buffer image previously initialized with @ref FloodFillGetSize.
/// @param seedX column coordinate for the seed.
/// @param seedY row coordinate for the seed.
/// @param newVal Value to fill with for one-channel data.
/// @param minDelta Minimum difference between neighbor pixels for one-channel data.
/// @param maxDelta Maximum difference between neighbor pixels for one-channel data.
/// @see FloodFillGetSize
void FloodFillRange4Connected(QVImage<uChar> &img, QVImage<uChar> &buffer,
	uInt seedX, uInt seedY, uChar newVal, uChar minDelta, uChar maxDelta);

/// @brief Performs gradient flood filling of connected area on an image.
/// @ingroup qvippCV
/// This function performs flood filling of the group of connected pixels in the seed pixel
/// neighborhoods whose pixel values v satisfies the following conditions:
///
/// \f$ v_0 – d_{lw} \leq v \leq v_0 + d_{up} \f$
///
/// where \f$ v_0 \f$ is the value of at least one of the current pixel neighbors, which already belongs
/// to the refilled area, and \f$ d_{lw} \f$, dup are minDelta, maxDelta, respectively. Values of these
/// pixel is set to the newVal value.
///
/// The function check 4-connected neighborhood of each pixel, i.e., side neighbors.
///
/// The function requires a temporary buffer whose size should be computed with the function
/// @ref FloodFillGetSize beforehand.
///
/// @param img image to flood fill.
/// @param buffer temporary buffer image previously initialized with @ref FloodFillGetSize.
/// @param seedX column coordinate for the seed.
/// @param seedY row coordinate for the seed.
/// @param newVal Value to fill with for one-channel data.
/// @param minDelta Minimum difference between neighbor pixels for one-channel data.
/// @param maxDelta Maximum difference between neighbor pixels for one-channel data.
/// @see FloodFillGetSize
void FloodFillGradient4Connected(QVImage<uChar> &img, QVImage<uChar> &buffer,
	uInt seedX, uInt seedY, uChar newVal, uChar minDelta, uChar maxDelta);

/// @brief Applies Gauss filter with border.
/// @ingroup qvippFF
///
/// This function applies the Gaussian filter to the source image ROI pSrc. The kernel of this filter
/// is the matrix of size \f$ kernelSize x kernelSize \f$ with the standard deviation \f$ sigma \f$. The values of the
/// elements of the Gaussian kernel are calculated according to the formula:
///
/// \f[ G(i,j) = e^{\displaystyle-\frac{\displaystyle(K/2-i)^2 + (K/2-j)^2}{\displaystyle2\sigma^2}} \f]
///
/// and then are normalized.
/// The function requires a working image buffer whose size should be computed by the function @ref FilterGaussGetBufferSize
/// beforehand.
/// @param src source image to apply filter
/// @param dest resulting image.
/// @param buffer buffer image initiated beforehand by the function @ref FilterGaussGetBufferSize.
/// @param kernelSize specifies the size of the Gaussian kernel, must be odd and greater than or equal to 3.
/// @param sigma standard deviation of the Gaussian kernel.
/// @param borderType type of border. Following values are possible:
///	- ippBorderConst. Values of all border pixels are set to constant.
///	- ippBorderRepl. Replicated border is used.
///	- ippBorderWrap. Wrapped border is used
///	- ippBorderMirror. Mirrored border is used
///	- ippBorderMirrorR. Mirrored border with replication is used
/// @param borderValue The constant value to assign to the pixels in the constant border (not applicable for other border’s type).
/// @see FilterGaussGetBufferSize
void FilterGaussBorder(const QVImage<sFloat, 1> &src, QVImage<sFloat, 1> &dest, QVImage<uChar> &buffer, sInt kernelSize, sFloat sigma, IppiBorderType borderType = ippBorderConst, sFloat borderValue = 0.0,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Computes the size of the external buffer for the Gaussian filter with border.
/// @ingroup qvippFF
///
/// This function computes the size of the external buffer that is required for the filter function
/// FilterGaussBorder. This buffer can be used to filter an image whose width and height are equal
/// to or less than param QVGenericImage image, and the kernel size is equal to or less than kernelSize.
///
/// @param src source image to apply later filter.
/// @param buffer buffer image to initialize for further operations.
/// @param kernelSize Size of the Gaussian kernel, odd, greater than or equal to 3.
/// @see FilterGaussBorder
void FilterGaussGetBufferSize(const QVGenericImage &image, QVImage<uChar> &buffer, uInt kernelSize);

/// @brief Finds coordinates of peaks (maximums or minimums) with absolute value exceeding threshold value.
/// @ingroup qvippCV
///
/// This function detects local maximum pixels in the source image, and stores their coordinates in
/// the <i>points</i> point list.
/// The neighborhood O(i, j) for the search is defined by the parameter norm. The
/// number of detected maximums is returned in pPeakCount[0]. The operation is stopped
/// The function requires a working image buffer whose size should be computed by the function
/// @ref FindPeaks3x3GetBufferSize beforehand.
///
/// @param img image to obtain from peaks.
/// @param buffer buffer image initiated beforehand by the function @ref FindPeaks3x3GetBufferSize.
/// @param points QPoint list to store the resulting point list.
/// @param threshold threshold value.
/// @param norm Specifies type of the norm to form the mask for maximum search:
///	- ippiNormInf. Infinity norm (8-connectivity, 3x3 rectangular mask);
///	- ippiNormL1. L1 norm (4-connectivity, 3x3 cross mask).
/// @param border Border value, only pixel with distance from the edge of the image greater than border are processed.
/// @param maxPeakCount Maximum number of peaks.
/// @see FindPeaks3x3GetBufferSize
void FindPeaks3x3(const QVImage<sInt, 1> &img, QVImage<uChar> &buffer, QList<QPoint> &points, sInt threshold, IppiNorm norm, uInt border, uInt maxPeakCount);

/// @brief Finds coordinates of peaks (maximums or minimums) with absolute value exceeding threshold value.
/// @ingroup qvippCV
/// @see FindPeaks3x3(const QVImage<sInt, 1> &, QVImage<uChar> &, QList<QPoint> &, sInt, IppiNorm, uInt, uInt)
void FindPeaks3x3(const QVImage<sFloat, 1> &img, QVImage<uChar> &buffer, QList<QPoint> &points, sFloat threshold, IppiNorm norm, uInt border, uInt maxPeakCount);


/// @brief Computes the size of the working buffer for the peak search.
/// @ingroup qvippCV
///
/// This function computes the size of the working image buffer required for the function
/// FindPeaks3x3. The image buffer can be used to filter images with ROI width that is less
/// than or equal to the image ROI width.
///
/// @param image source image to apply later filter.
/// @param buffer buffer image to initialize for further operations.
/// @see FindPeaks3x3(const QVImage<sInt, 1> &, QVImage<uChar> &, sInt, IppiNorm, uInt, QList<QPoint> &)
void FindPeaks3x3GetBufferSize(const QVImage<sInt,1> &image, QVImage<uChar> &buffer);

/// @brief Computes the size of the working buffer for the peak search.
/// @ingroup qvippCV
/// @see FindPeaks3x3GetBufferSize(const QVImage<sInt,1> &, QVImage<uChar> &)
/// @see FindPeaks3x3
void FindPeaks3x3GetBufferSize(const QVImage<sFloat,1> &image, QVImage<uChar> &buffer);

/// @brief Performs perspective warping of the source image using the given transform coefficients.
/// @ingroup qvippIGT
///
/// @todo Document this function
///
/// @param src source image to wrap.
/// @param dest destination image to contain wrapped image.
/// @param rectifyingHomography homography matrix corresponding to the wrapping.
/// @param interpolation interpolation type. Selects the algorithm for interpolate pixel values. Possible values for this parameter are:
///	- IPPI_INTER_NN. Nearest neighbor interpolation
///	- IPPI_INTER_LINEAR. Linear interpolation
///	- IPPI_INTER_CUBIC. Cubic interpolation
void	WarpPerspective(const QVImage<uChar> &src, QVImage<uChar> &dest, const QVMatrix &rectifyingHomography, int interpolation = IPPI_INTER_LINEAR,  const QPoint &destROIOffset = QPoint(0,0));

/// @brief Performs perspective warping of the source image using the given transform coefficients.
/// @ingroup qvippIGT
/// @see WarpPerspective(const QVImage<uChar> &, QVImage<uChar> &, const QVMatrix &, int, QPoint)
void	WarpPerspective(const QVImage<uChar,3> &src, QVImage<uChar,3> &dest, const QVMatrix &rectifyingHomography, int interpolation = IPPI_INTER_LINEAR,  const QPoint &destROIOffset = QPoint(0,0));

#endif
