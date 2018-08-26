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

#ifndef QVGENERICIMAGE_H
#define QVGENERICIMAGE_H

#include <iostream>

#include <qvdefines.h>
#include <QRect>
#include <QPoint>
#include <QSize>

/*! @class QVGenericImage qvip/qvgenericimage.h QVGenericImage
@brief Base class for @ref QVImage objects.

For instance, this class is useful to create code like this:

\code
int imageAreaSize(QVGenericImage *image)
	{
	return image->getCols() * image->getRows();
	}
\endcode

Where it doesn't matter the bit depth or number of channels of the image, but the number of cols and rows of it, as well as generic containers, that can hold a variety of image types, for example:

\code
class GenericImageContainer
	{
	public:
		int count;
		QVGenericImage *images;
		[...]
		void addImage(QVGenericImage *image)	{ images[count++] = &image; }
		QVGenericImage getImage(int index)	{ return images[index]; }
	}
\endcode

Thus, this class offers access methods for all kind of information about the image, like dimensions (see @ref getCols() and @ref getRows() methods), bit depth and number of planes (see @ref getTypeSize() and @ref getChannels() methods), ROI and anchor of the image (see @ref getROI() and @ref getAnchor() methods mainly), but pixel accessor methods, that are defined in the subclass @ref QVImage, and depends on the bit depth and number of planes of the image.

@todo eliminar el sufijo 'get' de todas las funciones. getCols -> cols, getRows -> rows
@see QVImage
@ingroup qvip
*/
class QVGenericImage
	{
	public:
		/// @brief Default constructor.
		///
		/// Initializes image ROI and anchor to zero offset and width, both.
		QVGenericImage (): roi(0,0,0,0), anchor(QPoint(0,0))					{ }

		/// @brief Copy constructor.
		///
		/// Initializes image ROI and anchor to ROI and anchor from image 'img'.
		QVGenericImage(QVGenericImage const &img): roi(img.getROI()), anchor(img.getAnchor())	{ }

		/// @brief Virtual destructor for QVGenericImage.
		virtual ~QVGenericImage ()								{ };

		/// @brief Virtual method for getting the number of columns of the image.
		///
		/// @returns number of columns for image,
		virtual uInt	getCols()	const	= 0;

		/// @brief Virtual method for getting the number of rows of the image.
		///
		/// @returns number of rows for image,
		virtual uInt	getRows()	const	= 0;

		/// @brief Virtual method for getting the row step of the image.
		///
		/// This functions returns the distance in bytes between starts of consecutive lines in the image.
		///
		/// This may be not equal to a multiple of the number of columns, so this value is necessary to normal access
		/// to the image.
		///
		/// @returns distance in bytes between two consecutive lines in the image.
		virtual uInt	getStep()	const	= 0;

		/// @brief Virtual method for getting the size of the image
		///
		/// This functions returns the distance in bytes between starts of consecutive lines in the image.
		///
		/// This may be not equal to a multiple of the number of columns, so this value is necessary to access
		/// the pixels in the image, using methods for raw image access.
		///
		/// @returns a QSize object, containing the image size.
		QSize	getSize()		const	{ return QSize(getCols(), getRows()); };

		/// @brief Virtual method for getting the number of channels of the image.
		///
		/// Returned value should be equal to template parameter 'Channels', for any QVImage. This is the number
		/// of channels that can be accessed in the image.
		///
		/// @returns number of channels of the image.
		virtual uInt	getChannels()	const	= 0;

		/// @brief Virtual method for getting bit depth of the image, in bytes.
		///
		/// Returned value should be equal to size of template parameter 'Type', for any QVImage. This is the size
		/// of any element of the data array that stores the image in memory.
		///
		/// @returns number of channels of the image.
		virtual	uInt	getTypeSize()	const	= 0;

		/// @brief Virtual method for getting data size for the image.
		///
		/// This functions, for any image, returns the following value:
		/// \verbatim dataSize = rows * step * planes \endverbatim
		///
		/// @returns size in bytes of data buffer for the image.
		virtual	uInt	getDataSize()	const	= 0;

		/// @brief Method for obtaining actual region of interest for image.
		///
		/// The region of interest of an image is used in many image processing and filtering operations.
		/// Check the section @ref TheIPPWrapperFunctions for further documentation about the ROI of an image.
		///
		/// @returns a QRect that contains the region of interest of the image.
		const QRect &	getROI()	const	{ return roi; }

		// ROI operations
		/// @brief Resets the region of interest of the image.
		///
		/// Sets the region of interest to the whole image.
		/// The ROI will be the rectangle from pixel (0,0), to pixel (image cols-1, image rows-1).
		///
		/// Check the section @ref TheIPPWrapperFunctions for further documentation about the ROI of an image.
		///
		void resetROI()				{ setROI(0,0,getCols(), getRows()); }

		/// @brief Reduces the region of interest of the image, in a given amount of pixels.
		///
		/// Reduces a given amount of columns and rows to the ROI of the image, equally on each side of the ROI.
		///
		/// Check the section @ref TheIPPWrapperFunctions for further documentation about the ROI of an image.
		///
		/// @param cols	columns to reduce the ROI.
		/// @param rows	rows to reduce the ROI.
		void erodeROI(uInt cols, uInt rows)
			{ setROI(getROI().x()+cols, getROI().y()+rows, getROI().width()-2*cols, getROI().height()-2*rows); }

		/// @brief Increments the region of interest of the image, in a given amount of pixels.
		///
		/// Increments a given amount of columns and rows to the ROI of the image, equally on each side of the ROI.
		///
		/// Check the section @ref TheIPPWrapperFunctions for further documentation about the ROI of an image.
		///
		/// @param cols	columns to increment the ROI.
		/// @param rows	rows to increment the ROI.
		void dilateROI(uInt cols, uInt rows)
			{ setROI(getROI().x()-cols, getROI().y()-rows, getROI().width()+2*cols, getROI().height()+2*rows); }

		/// @brief Set the region of interest of the image.
		///
		/// The region of interest for an image is a rectangle, significant to many operations. Pixels outside this
		/// rectangle may be ignored by many filtering and image processing functions.
		///
		/// Check the section @ref TheIPPWrapperFunctions for further documentation about the ROI of an image.
		///
		/// @param x column of the pixel at the top left corner of the region of interest.
		/// @param y row of the pixel at the top left corner of the region of interest.
		/// @param w width of the region of interest.
		/// @param h height of the region of interest.
		void setROI(int x, int y, uInt w, uInt h) { setROI(QRect(x,y,w,h)); }

		// @brief Sets the image ROI to contain the whole image, except a margin around the borders.
		//
		// Check the section @ref TheIPPWrapperFunctions for further documentation about the ROI of an image.
		//
		// @param margin size of the border.
		void setMargin(int margin)
			{ setROI(margin, margin, getCols() - 2*margin, getRows() -2*margin); }

		/// @brief Set the region of interest (ROI) for the image, from a rectangle.
		///
		/// This is an overloaded version of the method @ref setROI(int,int,uInt,uInt), provided for convenience.
		///
		/// Check the section @ref TheIPPWrapperFunctions for further documentation about the ROI of an image.
		///
		/// @param rect rectangle that represents region of interest.
		void setROI(const QRect &rect)
			{
			//std::cout << "-------------------------" << std::endl;
			//std::cout << "x = " << rect.x() << std::endl;
			//std::cout << "y = " << rect.y() << std::endl;
			//std::cout << "w = " << rect.width() << std::endl;
			//std::cout << "h = " << rect.height() << std::endl;

			//std::cout << "cols = " << getCols() << std::endl;
			//std::cout << "rows = " << getRows() << std::endl;

			Q_ASSERT_X(rect.x() >= 0,"QVGenericImage::setROI()","QRect.x() is less than zero");
			Q_ASSERT_X(rect.y() >= 0,"QVGenericImage::setROI()","QRect.y() is less than zero");
			Q_ASSERT_X(rect.x()+rect.width() <= (int) getCols(),"QVGenericImage::setROI()","x + width > columns");
			Q_ASSERT_X(rect.y()+rect.height() <= (int) getRows(),"QVGenericImage::setROI()","y + height > rows");
			roi = rect;
			}

		// Anchor operations

		/// @brief Obtains actual anchor point for the image.
		///
		/// The anchor of an image is used for some visualization operations.
		///
		/// @returns The anchor point of the image.
		const QPoint &	getAnchor()	const	{ return anchor; }


		/// @brief Set anchor point of the image to pixel (0,0).
		///
		void resetAnchor()			{ setAnchor(0,0); }

		/// @brief Set anchor point of the image.
		///
		/// @param col column of the pixel where the anchor is located.
		/// @param row row of the pixel where the anchor is located.
		void setAnchor(int col, int row)	{ setAnchor(QPoint(col,row)); }

		/// @brief Set anchor point of the image.
		///
		/// @param point QPoint where the anchor is located.
		void setAnchor(const QPoint &point)
			{
			Q_ASSERT_X(point.x()>=0,"QVGenericImage::setAnchor()","horizontal value for anchor is less than zero");
			Q_ASSERT_X(point.y()>=0,"QVGenericImage::setAnchor()","vertical value for anchor is less than zero");
			Q_ASSERT_X((getCols() == 0) or (point.x() < (int) getCols()),"QVGenericImage::setAnchor()","horizontal value exceeds cols");
			Q_ASSERT_X((getRows() == 0) or (point.y() < (int) getRows()),"QVGenericImage::setAnchor()","vertical value exceeds rows");
			anchor = point;
			}

		// Type operations
		/// @brief Obtain a char string identifying the type of the image.
		/// real image contained in the QVGenericImage.
		///
		/// @returns pointer to a constant char string identifying image type.
		virtual const char * getTypeQString() const = 0;

		/// @brief Check whether an image is compatible in type with another image, provided its type id string.
		///
		/// This functions checks if this image has the same bit depth and channel number, as another image, given
		/// its type identification string. This string can be obtained using the method @ref getTypeQString.
		///
		/// This function is used to determine the subclass of a QVGenericImage at execution time.
		/// An example code for this use is below:
		///
		/// \code [...]
		/// QVImage image;
		///
		/// [...]
		///
		/// if(image->isCompatibleWith("QVImage<uChar,1>"))
		///	// do stuff with the uChar bit depth, one channel image ...
		/// else if(image->isCompatibleWith("QVImage<uChar,3>"))
		///	// do stuff with the uChar bit depth, three channel image ...
		/// [...]
		/// else
		///	// alternate code for that type of image ...
		///
		/// [...] \endcode
		///
		/// @param qvimageClassName type id string identifying the type of another image.
		/// @returns true if this image is compatible in type with that represented by the string.
		bool isCompatibleWith(const char *qvImageClassName) const
			{
			Q_ASSERT_X(qvImageClassName!= NULL,"QVGenericImage::isCompatibleWith()","class name string is NULL");
			return (0 == strcmp(this->getTypeQString(),qvImageClassName));
			}

		/// @brief Check whether an image is compatible with this image.
		///
		/// This functions checks if this image is compatible with a given image. That is, it has same bit depth and
		/// same number of channels.
		///
		/// @param image image to check type compatibility with the actual image.
		/// @returns true if this image is compatible in type with the one provided by parameter.
		bool isCompatibleWith(const QVGenericImage *image) const
			{
			Q_ASSERT_X(image!= NULL,"QVGenericImage::isCompatibleWith()","NULL pointer");
			return this->isCompatibleWith(image->getTypeQString());
			}

	protected:
		QRect roi;
		QPoint anchor;
	};


#endif // QVGENERICIMAGE_H
