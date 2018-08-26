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

#ifndef QVIMAGE_H
#define QVIMAGE_H

#include <QMetaType>
#include <QVGenericImage>
#include <qvip/qvimagebuffer.h>
#include <QImage>

#include <qvmath/qvmath.h>

#ifdef QVOPENCV
#include <opencv/cv.h>
#endif

#ifndef QVIPP
#define	IPP_MAX_8U	std::numeric_limits<unsigned char>::max()
#define	IPP_MIN_8U	std::numeric_limits<unsigned char>::min()
#endif
/*!
@brief Initializes image to be read with macro QVIMAGE_PIXEL.

This macro initializes an image to inspect or modify its contents using a set of pixel access macros.
See section @ref QVImagePixelAccess for detailed usage of this macro.

@param TYPE Type of the image. It should be the value of first template parameter specified for the image.
@param IMAGE Image name.
@see QVIMAGE_PIXEL
@see QVIMAGE_PIXEL_PTR
@ingroup qvip
*/
#define	QVIMAGE_INIT_READ(TYPE, IMAGE)						\
    const TYPE * __qv_data_##IMAGE##__ = IMAGE.getReadData();		\
    const uInt __qv_step_##IMAGE##__ = IMAGE.getStep()/sizeof(TYPE);	\
    const uChar __qv_planes_##IMAGE##__  = IMAGE.getChannels();		\
    const uInt __qv_next_line_inc_##IMAGE##__ = __qv_step_##IMAGE##__ - IMAGE.getCols(); \
    Q_UNUSED (__qv_next_line_inc_##IMAGE##__) ;

/*!
@brief Initializes image to be written or read with macro QVIMAGE_PIXEL.

This macro initializes an image to inspect or modify its contents using a set of pixel access macros.
See section @ref QVImagePixelAccess for detailed usage of this macro.

@param TYPE Type of the image. It should be the value of first template parameter specified for the image.
@param IMAGE Image name.
@see QVIMAGE_PIXEL
@see QVIMAGE_PIXEL_PTR
@ingroup qvip
*/
#define	QVIMAGE_INIT_WRITE(TYPE, IMAGE)						\
    TYPE * __qv_data_##IMAGE##__ = IMAGE.getWriteData();			\
    const uInt __qv_step_##IMAGE##__ = IMAGE.getStep()/sizeof(TYPE);	\
    const uChar __qv_planes_##IMAGE##__  = IMAGE.getChannels();		\
    const uInt __qv_next_line_inc_##IMAGE##__ = __qv_step_##IMAGE##__ - IMAGE.getCols(); \
    Q_UNUSED (__qv_next_line_inc_##IMAGE##__) ;

/*!
@brief Initializes pointed image to be read with macro QVIMAGE_PIXEL.

This macro initializes a pointed image to inspect its contents using a set of pixel access macros.
See section @ref QVImagePixelAccess for detailed usage of this macro.

@param TYPE Type of the image. It should be the value of first template parameter specified for the image.
@param IMAGE Name of the pointer variable that points to the image.
@see QVIMAGE_PIXEL
@see QVIMAGE_PIXEL_PTR
@ingroup qvip
*/
#define	QVIMAGE_PTR_INIT_READ(TYPE, IMAGE)					\
    const TYPE * __qv_data_##IMAGE##__ = IMAGE->getReadData();		\
    const uInt __qv_step_##IMAGE##__ = IMAGE->getStep()/sizeof(TYPE);	\
    const uChar __qv_planes_##IMAGE##__  = IMAGE->getChannels();		\
    const uInt __qv_next_line_inc_##IMAGE##__ = __qv_step_##IMAGE##__ - IMAGE->getCols(); \
    Q_UNUSED (__qv_next_line_inc_##IMAGE##__) ;

/*!
@brief Initializes pointed image to be written or read with macro QVIMAGE_PIXEL.

This macro initializes a pointed image to inspect or modify its contents using a set of pixel access macros.
See section @ref QVImagePixelAccess for detailed usage of this macro.

@param TYPE Type of the image. It should be the value of first template parameter specified for the image.
@param IMAGE Name of the pointer variable that points to the image.
@see QVIMAGE_PIXEL
@see QVIMAGE_PIXEL_PTR
@ingroup qvip
*/
#define	QVIMAGE_PTR_INIT_WRITE(TYPE, IMAGE)										\
    TYPE * __qv_data_##IMAGE##__ = IMAGE->getWriteData();								\
    const uInt __qv_step_##IMAGE##__ = IMAGE->getStep()/sizeof(TYPE);						\
    const uChar __qv_planes_##IMAGE##__  = IMAGE->getChannels();							\
    const uInt __qv_next_line_inc_##IMAGE##__ = __qv_step_##IMAGE##__ - __qv_planes_##IMAGE##__ * IMAGE->getCols(); \
    Q_UNUSED (__qv_next_line_inc_##IMAGE##__) ;

/*!
@brief Access an image pixel for inspection or modification.

This macro can be used to access arbitrary pixels in an image, with a good time performance.
See section @ref QVImagePixelAccess for detailed usage of this macro.

@see QVIMAGE_INIT_READ
@see QVIMAGE_INIT_WRITE
@see QVIMAGE_PTR_INIT_READ
@see QVIMAGE_PTR_INIT_WRITE
@ingroup qvip
*/
#define QVIMAGE_PIXEL(IMAGE, Col, Row, Channel)	\
    (__qv_data_##IMAGE##__ [(Row)* __qv_step_##IMAGE##__ + __qv_planes_##IMAGE##__ *(Col)+(Channel)])

/*!
@brief Obtains a reference to the memory location of a pixel.

This macro can be used to obtain the location of arbitrary pixels in an image, with a good time performance.
See section @ref QVImagePixelAccess for detailed usage of this macro.

@see QVIMAGE_INIT_READ
@see QVIMAGE_INIT_WRITE
@see QVIMAGE_PTR_INIT_READ
@see QVIMAGE_PTR_INIT_WRITE
@ingroup qvip
*/
#define QVIMAGE_PIXEL_PTR(IMAGE, Col, Row, Channel)	\
    (& (__qv_data_##IMAGE##__ [(Row)* __qv_step_##IMAGE##__ + __qv_planes_##IMAGE##__ *(Col)+(Channel)]))

/*!
@brief Obtains the increment for a row movement of a pixel.

This macro can be used to navigate through the contents of an image given an initial pointer to its contents.
See section @ref QVImagePixelAccess for detailed usage of this macro.

@see QVIMAGE_PIXEL_PTR
@ingroup qvip
*/
#define QVIMAGE_ROW_INCREMENT_PTR(IMAGE)	( __qv_step_##IMAGE##__ )

/*!
@todo Las macros de acceso a pixel secuenciales no funcionan. Revisar.
@brief Obtains the increment for a column movement of a pixel.

This macro can be used to navigate through the contents of an image given an initial pointer to its contents.
See section @ref QVImagePixelAccess for detailed usage of this macro.

@see QVIMAGE_PIXEL_PTR
@ingroup qvip
*/
#define QVIMAGE_COL_INCREMENT_PTR(IMAGE)	( __qv_planes_##IMAGE##__ )

/*!
@brief Obtains the location of the first pixel in a row, given the location of the last pixel in the upper row.

This macro can be used to navigate through the contents of an image given an initial pointer to its contents.
See section @ref QVImagePixelAccess for detailed usage of this macro.

@see QVIMAGE_PIXEL_PTR
@ingroup qvip
*/
#define QVIMAGE_NEXT_LINE_INCREMENT_PTR(IMAGE)	( __qv_next_line_inc_##IMAGE##__ )

/*!
@class QVImage qvip/qvimage.h QVImage
@brief Image representation class for the QVision.

QVImage class extends @ref QVGenericImage, and wraps the data buffer and other values related to an image in a simple and lightweight structure, easy to use.

For further info about image objects and image usage, see section @ref BasicImageProcessing of the manual.

@tparam Type		Pixel storage type. Can be <i>uChar</i>, <i>sChar</i>, <i>uShort</i>, <i>sShort</i>, <i>uLong</i>, <i>sLong</i>, <i>sFloat</i> or <i>sDouble</i>.
            For further info see section @ref TheQVImageClass.
@tparam Channels	Number of channels in the image. Usually 1 or 3.

@ingroup qvip
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

template <typename Type = uChar, int Channels = 1> class QVImage: public QVGenericImage
    {
    protected:
        uInt step_div_type_size;
        QSharedDataPointer< QVImageBuffer<Type> > imageBuffer;

    public:
/*        /// @brief Default constructor.
        ///
        /// Initializes image with a data buffer of size 1x1. Sets anchor to pixel (0,0), and region of interest
        /// to a rectangle containing the only pixel of the image.
        ///
        QVImage():QVGenericImage()
            {
            this->imageBuffer = new QVImageBuffer<Type, Channels>(1, 1);
            setROI(0,0, this->imageBuffer->getCols(), this->imageBuffer->getRows());
            setAnchor(0,0);
            this->step_div_type_size = getStep()/sizeof(Type);
            }*/

		#ifndef DOXYGEN_IGNORE_THIS
		// Buffer copy constructor. Only for internal QVision usage.
        QVImage(uInt cols, uInt rows, uInt step, const Type * buffer = NULL):QVGenericImage()
            {
            this->imageBuffer = new QVImageBuffer<Type>(Channels*cols, rows, step, buffer);
            setROI(0,0, cols, rows);
            setAnchor(0,0);
            this->step_div_type_size = getStep()/sizeof(Type);
            }
		#endif

        /// @brief Default constructor.
        ///
        /// @param cols number of columns for the image.
        /// @param rows number of rows for the image.
        QVImage(uInt cols = 1, uInt rows = 1):QVGenericImage()
            {
            this->imageBuffer = new QVImageBuffer<Type>(Channels*cols, rows);
            setROI(0,0, cols, rows);
            setAnchor(0,0);
            this->step_div_type_size = getStep()/sizeof(Type);
            }

        /// @brief Copy constructor
        ///
        /// This constructor can be used to construct an image from another one with same bit depth and channel number,
        /// or from an image differing in type or number of channels.
        ///
        /// In the former case, this constructor will do a copy-on-write, duplicating the pointer to the data buffer of
        /// the image, and effectively copying the data only when modifying it if shared by more than one QVImage
        /// object.
        ///
        /// In the latter case, it will always allocate a new data buffer for the image, and make a conversion from
        /// different bit depth or channel number. Note that you can never convert from an image that differs in
        /// data type and bit-depth with the constructed image.
        ///
        /// This constructor will copy the ROI and anchor of the parameter image.
        ///
        /// @param img image to be copied.
        QVImage(QVImage<uChar,1> const &img);

        /// @brief Overloaded copy constructor.
        QVImage(QVImage<uChar,3> const &img);

        /// @param img image to be copied.
        QVImage(QVImage<sChar,1> const &img);

        /// @brief Overloaded copy constructor.
        QVImage(QVImage<sChar,3> const &img);

        /// @brief Overloaded copy constructor.
        QVImage(QVImage<uShort,1> const &img);

        /// @brief Overloaded copy constructor.
        QVImage(QVImage<uShort,3> const &img);

        /// @brief Overloaded copy constructor.
        QVImage(QVImage<sShort,1> const &img);

        /// @brief Overloaded copy constructor.
        QVImage(QVImage<sShort,3> const &img);

        /// @brief Overloaded copy constructor.
        QVImage(QVImage<uInt,1> const &img);

        /// @brief Overloaded copy constructor.
        QVImage(QVImage<uInt,3> const &img);

        /// @brief Overloaded copy constructor.
        QVImage(QVImage<sInt,1> const &img);

        /// @brief Overloaded copy constructor.
        QVImage(QVImage<sInt,3> const &img);

        /// @brief Overloaded copy constructor.
        QVImage(QVImage<sFloat,1> const &img);

        /// @brief Overloaded copy constructor.
        QVImage(QVImage<sFloat,3> const &img);

        /// @todo document this function
        QVImage(const QString &filename)
            {
            QImage qimg;
            qimg.load(filename);
            *this = QVImage<uChar, 3>(qimg);
            };

        /// @brief Compose copy constructor
        ///
        /// This constructor can be used to construct a 3-channels image from 3 1-channel images.
        ///
        /// This constructor will copy the ROI and anchor of the first parameter image.
        ///
        /// @param red image to be copied to the first channel.
        /// @param green image to be copied to the second channel.
        /// @param blue image to be copied to the third channel.
        QVImage(QVImage<uChar,1> const &red, QVImage<uChar,1> const &green, QVImage<uChar,1> const &blue);

        /// @brief Overloaded compose copy constructor
        QVImage(QVImage<uShort,1> const &red, QVImage<uShort,1> const &green, QVImage<uShort,1> const &blue);

        /// @brief Overloaded compose copy constructor
        QVImage(QVImage<sShort,1> const &red, QVImage<sShort,1> const &green, QVImage<sShort,1> const &blue);

        /// @brief Overloaded compose copy constructor
        QVImage(QVImage<sInt,1> const &red, QVImage<sInt,1> const &green, QVImage<sInt,1> const &blue);

        /// @brief Overloaded compose copy constructor
        QVImage(QVImage<sFloat,1> const &red, QVImage<sFloat,1> const &green, QVImage<sFloat,1> const &blue);

        // Convert operators for QImage
        /// @brief Convert constructor for QImage objects
        QVImage(const QImage &qImage);

        /// @brief Converts the QVImage to a QImage object
        operator QImage() const;

        // Convert operators for IplImage
        #ifdef QVOPENCV
        /// @brief Convert constructor from OpenCV image objects (IplImage)
        ///
        /// This function creates an image object importing the data from an OpenCV image (IplImage).
        ///
        /// @note OpenCV compatibility option must be enabled at the QVision library compilation to use this constructor
        /// @param iplImage pointer to the IplImage
        /// @see operator IplImage *() const
        QVImage(const IplImage *iplImage);

        /// @brief Converts the QVImage to an OpenCV image object (IplImage)
        ///
                /// This function creates a new IplImage object with the same dimensions and content of the actual image.
        ///
        /// @note OpenCV compatibility option must be enabled at the QVision library compilation to use this constructor
        /// @see QVImage(const IplImage *)
        operator IplImage *() const;
        #endif

        // Misc data.
        /// @brief Overloaded function from QVGenericImage::getTypeQString()
        const char * getTypeQString() const;

        /// @brief Overloaded function from QVGenericImage::getRows()
        uInt getRows()		const	{ return imageBuffer->getRows(); }

        /// @brief Overloaded function from QVGenericImage::getCols()
        uInt getCols()		const	{ return imageBuffer->getCols() / Channels; }

        /// @brief Overloaded function from QVGenericImage::getStep()
        inline uInt getStep()	const	{ return imageBuffer->getStep(); }

        /// @brief Overloaded function from QVGenericImage::getChannels()
        inline uInt getChannels()	const	{ return Channels; }

        /// @brief Overloaded function from QVGenericImage::getDataSize()
        uInt getDataSize()	const	{ return imageBuffer->getDataSize(); }

        /// @brief Overloaded function from QVGenericImage::getTypeSize()
        uInt getTypeSize()	const	{ return sizeof(Type); }

        /// @brief Method to obtain image data buffer, in read mode
        ///
        /// This method can be used to program fast access algorithms to pixel values in an image.
        ///
        /// It is intended to be used only to read pixels in an image, thus getWriteData() method should be used
        /// when access to write or read/write is intended to be done.
        ///
        /// This function will generally be faster than getWriteData(), because it will not need to realize copy on write,
        /// in the case that the image data buffer where shared with other QVImage.
        ///
        const Type * getReadData()	const	{ return imageBuffer->getReadData(); }

        /// @brief Method to obtain image data buffer, in read/write mode
        ///
        /// This method can be used to program fast access algorithms to pixel values in an image.
        ///
        /// This function will perform copy on write in the case that the data buffer for this image where shared with
        /// other QVImage's.
        ///
        /// Thus can be slower than getReadData() method to access image pixels, but will ensure avoiding side
        /// effects on modifying shared buffers with other images.
        ///
        Type * getWriteData()		{ return imageBuffer->getWriteData(); }

        /// @brief Sets pixel values for an image, to a given value.
        ///
        /// This method  uses the region of interest of the image, to set pixels inside it to a given value.
        /// It can be used either for one channel, or several channel images.
        ///
        /// In the former case, it should be used with one parameter, only specifying value for the first channel,
        /// otherwise, values for other channels will be ignored.
        /// If no parameters are given, the image region of interest will be set to zero value pixels.
        ///
        /// In the latter case, default values of 0 will be used if there are unspecified channel values.
        ///
        /// @param c1 value to set pixel's first channel in the region of interest of the image.
        /// @param c2 value to set pixel's second channel in the region of interest of the image.
        /// @param c3 value to set pixel's third channel in the region of interest of the image.
        void set(Type c1 = 0, Type c2 = 0, Type c3 = 0);


        /// @brief Check if the image is empty
        ///
        /// @returns true if the image contains no data, false otherwise.
        bool isEmpty() const
			{
			return (getDataSize() == 0);
			}

        /// @brief Resizes the image
        ///
        /// This method reserves extra space for a larger image.
        ///
        /// @param cols new columns number.
        /// @param rows new row number.
        void resize(const int cols, const int rows)
            {
            if (((int)getCols()) >= cols && ((int)getRows()) >= rows)
                return;

            QVImage<Type, Channels> temp(MAX(cols, (int)getCols()), MAX(rows, (int)getRows()));
            Copy(*this, temp);

            *this = temp;
            }

        /// @brief Operator to access pixel values for a pixel channel, given it's coordinates.
        ///
        /// This operator can be used either with one channel or multichannel images.
        /// In the first case, it shouldn't be given a channel number, to use the default zero value.
        ///
        /// @param col column number of pixel to be accessed.
        /// @param row row number of pixel to be accessed.
        /// @param channel channel number of pixel to be accessed.
        inline Type &operator()(const uInt col, const uInt row, const uInt channel = 0)
            {
            Q_ASSERT_X(step_div_type_size == getStep()/sizeof(Type), "QVImage::operator()", "step/size(Type) incorrect");
            Q_ASSERT_X(col < getCols(),"QVImage::operator()","col beyond upper bound");
            Q_ASSERT_X(row < getRows(),"QVImage::operator()","row beyond upper bound");
            const int idx = step_div_type_size*row + Channels*col + channel;
            Q_ASSERT_X(idx >= 0,"QVImage::operator()","accessing below data");
            Q_ASSERT_X((uint)idx < getDataSize(),"QVImage::operator()","accessing above data");

            return imageBuffer->getWriteData()[idx];
            }

        inline Type operator()(const uInt col, const uInt row, const uInt channel = 0) const
            {
            Q_ASSERT_X(step_div_type_size == getStep()/sizeof(Type), "QVImage::operator()", "step/size(Type) incorrect");
            Q_ASSERT_X(col < getCols(),"QVImage::operator()","col further upper bound");
            Q_ASSERT_X(row < getRows(),"QVImage::operator()","row further upper bound");
            const int idx = step_div_type_size*row + Channels*col + channel;
            Q_ASSERT_X(idx >= 0,"QVImage::operator()","accessing below data");
            Q_ASSERT_X((uint)idx < getDataSize(),"QVImage::operator()","accessing above data");

            return imageBuffer->getReadData()[idx];
            }

        /// @brief Overload of operator (), to access pixel values for a pixel channel, given a QVPoint and a
        /// channel number.
        ///
        /// This overload is like the previous, but can be used with a QPoint, to access a concrete pixel in the image.
        /// @param point QPoint indicating location of the pixel to be accessed.
        /// @param channel channel number of pixel to be accessed.
        inline Type &operator()(const QPoint point, const uInt channel = 0)
            {
            Q_ASSERT_X(step_div_type_size == getStep()/sizeof(Type), "QVImage::operator()", "step/size(Type) incorrect");
            Q_ASSERT_X((uInt) point.x() < getCols(),"QVImage::operator()","col further upper bound");
            Q_ASSERT_X((uInt) point.y() < getRows(),"QVImage::operator()","row further upper bound");
            const int idx = step_div_type_size*point.y() + Channels*point.x() + channel;
            Q_ASSERT_X(idx >= 0,"QVImage::operator()","accessing below data");
            Q_ASSERT_X((uint)idx < getDataSize(),"QVImage::operator()","accessing above data");

            return imageBuffer->getWriteData()[idx];
            }

        inline Type operator()(const QPoint point, const uInt channel = 0) const
            {
            Q_ASSERT_X(step_div_type_size == getStep()/sizeof(Type), "QVImage::operator()", "step/size(Type) incorrect");
            Q_ASSERT_X((uInt) point.x() < getCols(),"QVImage::operator()","col further upper bound");
            Q_ASSERT_X((uInt) point.y() < getRows(),"QVImage::operator()","row further upper bound");
            const int idx = step_div_type_size*point.y() + Channels*point.x() + channel;
            Q_ASSERT_X(idx >= 0,"QVImage::operator()","accessing below data");
            Q_ASSERT_X((uint)idx < getDataSize(),"QVImage::operator()","accessing above data");

            return imageBuffer->getReadData()[idx];
            }

        /// @brief Operator to access pixel values for a pixel channel, given it's coordinates.
        ///
        /// This operator can be used either with one channel or multichannel images.
        /// In the first case, it shouldn't be given a channel number, to use the default zero value.
        ///
        /// @param col column number of pixel to be accessed.
        /// @param row row number of pixel to be accessed.
        /// @param channel channel number of pixel to be accessed.
        QVImage<Type, 1> operator()(const uInt channel = 0) const;

        /// @brief Copy operator
        ///
        /// Like the copy constructor, this operator can be used to copy an image from another one with same bit depth
        /// and channel number, or from an image differing in type or number of channels.
        ///
        /// In the former case, this operator will do a copy-on-write, duplicating the pointer to the data buffer of
        /// the image, and effectively copying the data only when modifying it if shared by more than one QVImage
        /// object.
        ///
        /// In the latter case, it will always allocate a new data buffer for the image, and make a conversion from
        /// different bit depth or channel number. Note that you can never convert from an image that differs in
        /// data type and bit-depth with the constructed image.
        ///
        /// The copy operator will copy the ROI and anchor of the parameter image.
        ///
        /// @param img image to be copied.
        QVImage<Type, Channels> & operator=(const QVImage<uChar, 1> &sourceImage);

        /// @brief Overloaded copy operator.
        QVImage<Type, Channels> & operator=(const QVImage<uChar, 3> &sourceImage);

        /// @param img image to be copied.
        QVImage<Type, Channels> & operator=(const QVImage<sChar, 1> &sourceImage);

        /// @brief Overloaded copy operator.
        QVImage<Type, Channels> & operator=(const QVImage<sChar, 3> &sourceImage);

        /// @brief Overloaded copy operator.
        QVImage<Type, Channels> & operator=(const QVImage<uShort, 1> &sourceImage);

        /// @brief Overloaded copy operator.
        QVImage<Type, Channels> & operator=(const QVImage<uShort, 3> &sourceImage);

        /// @brief Overloaded copy operator.
        QVImage<Type, Channels> & operator=(const QVImage<sShort, 1> &sourceImage);

        /// @brief Overloaded copy operator.
        QVImage<Type, Channels> & operator=(const QVImage<sShort, 3> &sourceImage);

        /// @brief Overloaded copy operator.
        QVImage<Type, Channels> & operator=(const QVImage<uInt, 1> &sourceImage);

        /// @brief Overloaded copy operator.
        QVImage<Type, Channels> & operator=(const QVImage<uInt, 3> &sourceImage);

        /// @brief Overloaded copy operator.
        QVImage<Type, Channels> & operator=(const QVImage<sInt, 1> &sourceImage);

        /// @brief Overloaded copy operator.
        QVImage<Type, Channels> & operator=(const QVImage<sInt, 3> &sourceImage);

        /// @brief Overloaded copy operator.
        QVImage<Type, Channels> & operator=(const QVImage<sFloat, 1> &sourceImage);

        /// @brief Overloaded copy operator.
        QVImage<Type, Channels> & operator=(const QVImage<sFloat, 3> &sourceImage);

        /// @brief Equality compare operator
        ///
        /// This operator will compare two images of same bit depth and channel number, and will return true if
        /// images are equal in all of these:
        ///	- dimensions (cols and rows).
        ///	- region of interest.
        ///	- content of region of interest.
        /// returning false otherwise.
        ///
        /// @param img image to compare with this image.
        bool operator==(const QVImage<Type, Channels> &img) const;

        /// @brief Inequality compare operator
        ///
        /// This operator will compare two images of same bit depth and channel number, and will return true if
        /// images differ in any of:
        ///	- dimensions (cols and rows).
        ///	- region of interest.
        ///	- content of region of interest.
        /// returning false otherwise.
        ///
        /// \todo Shouldn't ignore dimensions in caparisons, and only check if region of interest content are the same?
        ///
        /// @param img image to compare with this image.
        /// @returns true if images are practically equal (same content of region of interest and dimensions).
        bool operator!=(const QVImage<Type, Channels> &img) const { return !(*this == img); }

        #ifdef QVIPP
        /// @brief Pixel wise 'less than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is less than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator<(const QVImage<uChar, Channels> &img) const;

        /// @brief Pixel wise 'less than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is less than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator<(const QVImage<uShort, Channels> &img) const;

        /// @brief Pixel wise 'less than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is less than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator<(const QVImage<sShort, Channels> &img) const;

        /// @brief Pixel wise 'less than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is less than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator<(const QVImage<sInt, Channels> &img) const;

        /// @brief Pixel wise 'less than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is less than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator<(const QVImage<sFloat, Channels> &img) const;

        /// @brief Pixel wise 'greater than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is greater than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator>(const QVImage<uChar, Channels> &img) const;

        /// @brief Pixel wise 'greater than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is greater than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator>(const QVImage<uShort, Channels> &img) const;

        /// @brief Pixel wise 'greater than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is greater than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator>(const QVImage<sShort, Channels> &img) const;

        /// @brief Pixel wise 'greater than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is greater than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator>(const QVImage<sInt, Channels> &img) const;

        /// @brief Pixel wise 'greater than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is greater than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator>(const QVImage<sFloat, Channels> &img) const;

        /// @brief Pixel wise 'less or equal than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is less or equal than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator<=(const QVImage<uChar, Channels> &img) const;

        /// @brief Pixel wise 'less or equal than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is less or equal than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator<=(const QVImage<uShort, Channels> &img) const;

        /// @brief Pixel wise 'less or equal than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is less or equal than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator<=(const QVImage<sShort, Channels> &img) const;

        /// @brief Pixel wise 'less or equal than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is less or equal than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator<=(const QVImage<sInt, Channels> &img) const;

        /// @brief Pixel wise 'less or equal than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is less or equal than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator<=(const QVImage<sFloat, Channels> &img) const;

        /// @brief Pixel wise 'greater or equal than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is greater or equal than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator>=(const QVImage<uChar, Channels> &img) const;

        /// @brief Pixel wise 'greater or equal than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is greater or equal than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator>=(const QVImage<uShort, Channels> &img) const;

        /// @brief Pixel wise 'greater or equal than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is greater or equal than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator>=(const QVImage<sShort, Channels> &img) const;

        /// @brief Pixel wise 'greater or equal than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is greater or equal than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator>=(const QVImage<sInt, Channels> &img) const;

        /// @brief Pixel wise 'greater or equal than' compare operator
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img image to compare with this image.
        /// @returns 1-channel uChar bit depth image containing non-zero values for pixels which value for corresponding
        /// pixel in this image is greater or equal than value for corresponding pixel in given image.
        QVImage<uChar, 1> operator>=(const QVImage<sFloat, Channels> &img) const;

        /// @brief Pixel wise constant add operator.
        ///
        /// Uses as the second operand a constant value for every pixel computed.
        ///
        /// Saturation is used for integer bit depth data (any except sFloat bit depth).
        /// Regions of interests, and anchors are applied in this operator.
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param constant second operand value.
        /// @returns resulting image for the operation.
        QVImage<Type, Channels> operator+(const Type constant) const;

        /// @brief Pixel wise constant product operator.
        ///
        /// Uses as the second operand a constant value for every pixel computed.
        ///
        /// Saturation is used for integer bit depth data (any except sFloat bit depth).
        /// Regions of interests, and anchors are applied in this operator.
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param constant second operand value.
        /// @returns resulting image for the operation.
        QVImage<Type, Channels> operator*(const Type constant) const;

        /// @brief Pixel wise constant subtraction operator.
        ///
        /// Uses as the second operand a constant value for every pixel computed.
        ///
        /// Saturation is used for integer bit depth data (any except sFloat bit depth).
        /// Regions of interests, and anchors are applied in this operator.
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param constant second operand value.
        /// @returns resulting image for the operation.
        QVImage<Type, Channels> operator-(const Type constant) const;

        /// @brief Pixel wise constant division operator.
        ///
        /// Uses as the second operand a constant value for every pixel computed.
        ///
        /// Saturation is used for integer bit depth data (any except sFloat bit depth).
        /// Regions of interests, and anchors are applied in this operator.
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param constant second operand value.
        /// @returns resulting image for the operation.
        QVImage<Type, Channels> operator/(const Type constant) const;

        /// @brief Pixel wise bit-wise left shift operator.
        ///
        /// Uses as the value to shift a constant value for every pixel computed.
        ///
        /// Saturation is used for integer bit depth data (any except sFloat bit depth).
        /// Regions of interests, and anchors are applied in this operator.
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param constant second operand value.
        /// @returns resulting image for the operation.
        QVImage<Type, Channels> operator<<(const Type constant) const;

        /// @brief Pixel wise bit-wise right shift operator.
        ///
        /// Uses as the value to shift a constant value for every pixel computed.
        ///
        /// Saturation is used for integer bit depth data (any except sFloat bit depth).
        /// Regions of interests, and anchors are applied in this operator.
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param constant second operand value.
        /// @returns resulting image for the operation.
        QVImage<Type, Channels> operator>>(const Type constant) const;

        /// @brief Pixel wise bit-wise NOT operation.
        ///
        /// Regions of interests, and anchors are applied in this operator.
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @returns resulting image for the operation.
        QVImage<Type, Channels> operator!() const;

        /// @brief Pixel wise bit-wise boolean and operator.
        ///
        /// Regions of interests, and anchors are applied in this operator.
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param constant second operand value.
        /// @returns resulting image for the operation.
        QVImage<Type, Channels> operator&(const Type constant) const;

        /// @brief Pixel wise bit-wise boolean or operator.
        ///
        /// Regions of interests, and anchors are applied in this operator.
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param constant second operand value.
        /// @returns resulting image for the operation.
        QVImage<Type, Channels> operator|(const Type constant) const;

        /// @brief Pixel wise bit-wise boolean xor operator.
        ///
        /// Regions of interests, and anchors are applied in this operator.
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param constant second operand value.
        /// @returns resulting image for the operation.
        QVImage<Type, Channels> operator^(const Type constant) const;

        /// @brief Pixel wise add operator.
        ///
        /// Saturation is used for integer bit depth data (any except sFloat bit depth).
        /// Regions of interests, and anchors are applied in this operator.
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img operand image.
        /// @returns resulting image for the operation.
        QVImage<Type, Channels> operator+(const QVImage<Type, Channels> &img) const;

        /// @brief Pixel wise mult operator.
        ///
        /// Saturation is used for integer bit depth data (any except sFloat bit depth).
        /// Regions of interests, and anchors are applied in this operator.
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img operand image.
        /// @returns resulting image for the operation.
        QVImage<Type, Channels> operator*(const QVImage<Type, Channels> &img) const;

        /// @brief Pixel wise subtraction operator.
        ///
        /// Saturation is used for integer bit depth data (any except sFloat bit depth).
        /// Regions of interests, and anchors are applied in this operator.
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img operand image.
        /// @returns resulting image for the operation.
        QVImage<Type, Channels> operator-(const QVImage<Type, Channels> &img) const;

        /// @brief Pixel wise division operator.
        ///
        /// Saturation is used for integer bit depth data (any except sFloat bit depth).
        /// Regions of interests, and anchors are applied in this operator.
        ///
        /// @note This operator is based on functionality from the Intel IPP library. Thus, compatibility
        /// with that library must be enabled to be available.
        ///
        /// @param img operand image.
        /// @returns resulting image for the operation.
        QVImage<Type, Channels> operator/(const QVImage<Type, Channels> &img) const;
        #endif
    };

/*!
@brief Comparison operator for @ref QVImage objects.
@ingroup qvip
*/
template <typename Type, int C> bool QVImage<Type, C>::operator==(const QVImage<Type, C> &img) const
    {
    Q_ASSERT_X(img.getChannels() == this->getChannels(), "QVImage::operator==", "different number of planes");
    if (this->getCols() != img.getCols()) return false;
    if (this->getRows() != img.getRows()) return false;
    if (this->getChannels() != img.getChannels()) return false;
    if (this->getROI() != img.getROI()) return false;
    QVIMAGE_INIT_READ(Type,img);
    QVIMAGE_PTR_INIT_READ(Type,this);

    uInt x0 = (uInt) img.getROI().x(), y0 = (uInt) img.getROI().y();
    uInt x1 = (uInt) img.getROI().width(), y1 = (uInt) img.getROI().height();

    uInt lineSize = x1 * img.getChannels();
    for(uInt row = y0; row < y1; row++)
        if (memcmp(&QVIMAGE_PIXEL(img, x0, row, 0),&QVIMAGE_PIXEL(this, x0, row, 0), lineSize) != 0)
            return false;
    return true;
    };

typedef QVImage<uChar,1> QVImageUCharC1;
typedef QVImage<uChar,3> QVImageUCharC3;
typedef QVImage<uShort,1> QVImageUShortC1;
typedef QVImage<uShort,3> QVImageUShortC3;
typedef QVImage<sShort,1> QVImageSShortC1;
typedef QVImage<sShort,3> QVImageSShortC3;
typedef QVImage<sInt,1> QVImageSIntC1;
typedef QVImage<sInt,3> QVImageSIntC3;
typedef QVImage<sFloat,1> QVImageSFloatC1;
typedef QVImage<sFloat,3> QVImageSFloatC3;

Q_DECLARE_METATYPE(QVImageUCharC1);
Q_DECLARE_METATYPE(QVImageUCharC3);
Q_DECLARE_METATYPE(QVImageUShortC1);
Q_DECLARE_METATYPE(QVImageUShortC3);
Q_DECLARE_METATYPE(QVImageSShortC1);
Q_DECLARE_METATYPE(QVImageSShortC3);
Q_DECLARE_METATYPE(QVImageSIntC1);
Q_DECLARE_METATYPE(QVImageSIntC3);
Q_DECLARE_METATYPE(QVImageSFloatC1);
Q_DECLARE_METATYPE(QVImageSFloatC3);

#ifndef QVIPP
void Set(const uChar value, QVImage<uChar, 1> &image);
void Set(const sFloat value, QVImage<sFloat, 1> &image);
void Set(const sInt value, QVImage<sInt, 1> &image);
void Set(const uInt value, QVImage<uInt, 1> &image);
void Set(const sShort value, QVImage<sShort, 1> &image);
void Set(const uShort value, QVImage<uShort, 1> &image);

void Set(const uChar value[3], QVImage<uChar, 3> &image);
void Set(const sFloat value[3], QVImage<sFloat, 3> &image);
void Set(const sInt value[3], QVImage<sInt, 3> &image);
void Set(const uInt value[3], QVImage<uInt, 3> &image);
void Set(const sShort value[3], QVImage<sShort, 3> &image);
void Set(const uShort value[3], QVImage<uShort, 3> &image);

void Copy(const QVImage<sFloat, 1> &, QVImage<sFloat, 1> &);
void Copy(const QVImage<sInt, 1> &, QVImage<sInt, 1> &);
void Copy(const QVImage<uInt, 1> &, QVImage<uInt, 1> &);
void Copy(const QVImage<sShort, 1> &, QVImage<sShort, 1> &);
void Copy(const QVImage<uShort, 1> &, QVImage<uShort, 1> &);

void Copy(const QVImage<sFloat, 3> &, const uChar channel, QVImage<sFloat, 1> &);
void Copy(const QVImage<sChar, 3> &, const uChar channel, QVImage<sChar, 1> &);
void Copy(const QVImage<uChar, 3> &, const uChar channel, QVImage<uChar, 1> &);
void Copy(const QVImage<sInt, 3> &, const uChar channel, QVImage<sInt, 1> &);
void Copy(const QVImage<uInt, 3> &, const uChar channel, QVImage<uInt, 1> &);
void Copy(const QVImage<sShort, 3> &, const uChar channel, QVImage<sShort, 1> &);
void Copy(const QVImage<uShort, 3> &, const uChar channel, QVImage<uShort, 1> &);

void Copy(const QVImage<sFloat, 1> &src1, const QVImage<sFloat, 1> &src2, const QVImage<sFloat, 1> &src3, QVImage<sFloat, 3> &dst);
void Copy(const QVImage<uChar, 1> &src1, const QVImage<uChar, 1> &src2, const QVImage<uChar, 1> &src3, QVImage<uChar, 3> &dst);
void Copy(const QVImage<sChar, 1> &src1, const QVImage<sChar, 1> &src2, const QVImage<sChar, 1> &src3, QVImage<sChar, 3> &dst);
void Copy(const QVImage<uInt, 1> &src1, const QVImage<uInt, 1> &src2, const QVImage<uInt, 1> &src3, QVImage<uInt, 3> &dst);
void Copy(const QVImage<sInt, 1> &src1, const QVImage<sInt, 1> &src2, const QVImage<sInt, 1> &src3, QVImage<sInt, 3> &dst);
void Copy(const QVImage<uShort, 1> &src1, const QVImage<uShort, 1> &src2, const QVImage<uShort, 1> &src3, QVImage<uShort, 3> &dst);
void Copy(const QVImage<sShort, 1> &src1, const QVImage<sShort, 1> &src2, const QVImage<sShort, 1> &src3, QVImage<sShort, 3> &dst);

// Pixel type convertions
// sFloat
//void Convert(const QVImage<sFloat, 1> &src, QVImage<sFloat, 1> &dst);	
void Convert(const QVImage<sFloat, 1> &src, QVImage<uChar, 1> &dst);	
void Convert(const QVImage<sFloat, 1> &src, QVImage<sChar, 1> &dst);	
void Convert(const QVImage<sFloat, 1> &src, QVImage<sInt, 1> &dst);	
void Convert(const QVImage<sFloat, 1> &src, QVImage<uInt, 1> &dst);	
void Convert(const QVImage<sFloat, 1> &src, QVImage<sShort, 1> &dst);	
void Convert(const QVImage<sFloat, 1> &src, QVImage<uShort, 1> &dst);	

//void Convert(const QVImage<sFloat, 3> &src, QVImage<sFloat, 3> &dst);	
void Convert(const QVImage<sFloat, 3> &src, QVImage<uChar, 3> &dst);	
void Convert(const QVImage<sFloat, 3> &src, QVImage<sChar, 3> &dst);	
void Convert(const QVImage<sFloat, 3> &src, QVImage<sInt, 3> &dst);	
void Convert(const QVImage<sFloat, 3> &src, QVImage<uInt, 3> &dst);	
void Convert(const QVImage<sFloat, 3> &src, QVImage<sShort, 3> &dst);	
void Convert(const QVImage<sFloat, 3> &src, QVImage<uShort, 3> &dst);	

// uChar
void Convert(const QVImage<uChar, 1> &src, QVImage<sFloat, 1> &dst);	
//void Convert(const QVImage<uChar, 1> &src, QVImage<uChar, 1> &dst);	
void Convert(const QVImage<uChar, 1> &src, QVImage<sChar, 1> &dst);	
void Convert(const QVImage<uChar, 1> &src, QVImage<sInt, 1> &dst);	
void Convert(const QVImage<uChar, 1> &src, QVImage<uInt, 1> &dst);	
void Convert(const QVImage<uChar, 1> &src, QVImage<sShort, 1> &dst);	
void Convert(const QVImage<uChar, 1> &src, QVImage<uShort, 1> &dst);	

void Convert(const QVImage<uChar, 3> &src, QVImage<sFloat, 3> &dst);	
//void Convert(const QVImage<uChar, 3> &src, QVImage<uChar, 3> &dst);	
void Convert(const QVImage<uChar, 3> &src, QVImage<sChar, 3> &dst);	
void Convert(const QVImage<uChar, 3> &src, QVImage<sInt, 3> &dst);	
void Convert(const QVImage<uChar, 3> &src, QVImage<uInt, 3> &dst);	
void Convert(const QVImage<uChar, 3> &src, QVImage<sShort, 3> &dst);	
void Convert(const QVImage<uChar, 3> &src, QVImage<uShort, 3> &dst);	

// sChar
void Convert(const QVImage<sChar, 1> &src, QVImage<sFloat, 1> &dst);	
void Convert(const QVImage<sChar, 1> &src, QVImage<uChar, 1> &dst);	
//void Convert(const QVImage<sChar, 1> &src, QVImage<sChar, 1> &dst);	
void Convert(const QVImage<sChar, 1> &src, QVImage<sInt, 1> &dst);	
void Convert(const QVImage<sChar, 1> &src, QVImage<uInt, 1> &dst);	
void Convert(const QVImage<sChar, 1> &src, QVImage<sShort, 1> &dst);	
void Convert(const QVImage<sChar, 1> &src, QVImage<uShort, 1> &dst);	

void Convert(const QVImage<sChar, 3> &src, QVImage<sFloat, 3> &dst);	
void Convert(const QVImage<sChar, 3> &src, QVImage<uChar, 3> &dst);	
//void Convert(const QVImage<sChar, 3> &src, QVImage<sChar, 3> &dst);	
void Convert(const QVImage<sChar, 3> &src, QVImage<sInt, 3> &dst);	
void Convert(const QVImage<sChar, 3> &src, QVImage<uInt, 3> &dst);	
void Convert(const QVImage<sChar, 3> &src, QVImage<sShort, 3> &dst);	
void Convert(const QVImage<sChar, 3> &src, QVImage<uShort, 3> &dst);	

// sInt
void Convert(const QVImage<sInt, 1> &src, QVImage<sFloat, 1> &dst);	
void Convert(const QVImage<sInt, 1> &src, QVImage<uChar, 1> &dst);	
void Convert(const QVImage<sInt, 1> &src, QVImage<sChar, 1> &dst);	
//void Convert(const QVImage<sInt, 1> &src, QVImage<sInt, 1> &dst);	
void Convert(const QVImage<sInt, 1> &src, QVImage<uInt, 1> &dst);	
void Convert(const QVImage<sInt, 1> &src, QVImage<sShort, 1> &dst);	
void Convert(const QVImage<sInt, 1> &src, QVImage<uShort, 1> &dst);	

void Convert(const QVImage<sInt, 3> &src, QVImage<sFloat, 3> &dst);	
void Convert(const QVImage<sInt, 3> &src, QVImage<uChar, 3> &dst);	
void Convert(const QVImage<sInt, 3> &src, QVImage<sChar, 3> &dst);	
//void Convert(const QVImage<sInt, 3> &src, QVImage<sInt, 3> &dst);	
void Convert(const QVImage<sInt, 3> &src, QVImage<uInt, 3> &dst);	
void Convert(const QVImage<sInt, 3> &src, QVImage<sShort, 3> &dst);	
void Convert(const QVImage<sInt, 3> &src, QVImage<uShort, 3> &dst);	

// uInt
void Convert(const QVImage<uInt, 1> &src, QVImage<sFloat, 1> &dst);	
void Convert(const QVImage<uInt, 1> &src, QVImage<uChar, 1> &dst);	
void Convert(const QVImage<uInt, 1> &src, QVImage<sChar, 1> &dst);	
void Convert(const QVImage<uInt, 1> &src, QVImage<sInt, 1> &dst);	
//void Convert(const QVImage<uInt, 1> &src, QVImage<uInt, 1> &dst);	
void Convert(const QVImage<uInt, 1> &src, QVImage<sShort, 1> &dst);	
void Convert(const QVImage<uInt, 1> &src, QVImage<uShort, 1> &dst);	

void Convert(const QVImage<uInt, 3> &src, QVImage<sFloat, 3> &dst);	
void Convert(const QVImage<uInt, 3> &src, QVImage<uChar, 3> &dst);	
void Convert(const QVImage<uInt, 3> &src, QVImage<sChar, 3> &dst);	
void Convert(const QVImage<uInt, 3> &src, QVImage<sInt, 3> &dst);	
//void Convert(const QVImage<uInt, 3> &src, QVImage<uInt, 3> &dst);	
void Convert(const QVImage<uInt, 3> &src, QVImage<sShort, 3> &dst);	
void Convert(const QVImage<uInt, 3> &src, QVImage<uShort, 3> &dst);	

// sShort
void Convert(const QVImage<sShort, 1> &src, QVImage<sFloat, 1> &dst);	
void Convert(const QVImage<sShort, 1> &src, QVImage<uChar, 1> &dst);	
void Convert(const QVImage<sShort, 1> &src, QVImage<sChar, 1> &dst);	
void Convert(const QVImage<sShort, 1> &src, QVImage<sInt, 1> &dst);	
void Convert(const QVImage<sShort, 1> &src, QVImage<uInt, 1> &dst);	
//void Convert(const QVImage<sShort, 1> &src, QVImage<sShort, 1> &dst);	
void Convert(const QVImage<sShort, 1> &src, QVImage<uShort, 1> &dst);	

void Convert(const QVImage<sShort, 3> &src, QVImage<sFloat, 3> &dst);	
void Convert(const QVImage<sShort, 3> &src, QVImage<uChar, 3> &dst);	
void Convert(const QVImage<sShort, 3> &src, QVImage<sChar, 3> &dst);	
void Convert(const QVImage<sShort, 3> &src, QVImage<sInt, 3> &dst);	
void Convert(const QVImage<sShort, 3> &src, QVImage<uInt, 3> &dst);	
//void Convert(const QVImage<sShort, 3> &src, QVImage<sShort, 3> &dst);	
void Convert(const QVImage<sShort, 3> &src, QVImage<uShort, 3> &dst);	

// uShort
void Convert(const QVImage<uShort, 1> &src, QVImage<sFloat, 1> &dst);	
void Convert(const QVImage<uShort, 1> &src, QVImage<uChar, 1> &dst);	
void Convert(const QVImage<uShort, 1> &src, QVImage<sChar, 1> &dst);	
void Convert(const QVImage<uShort, 1> &src, QVImage<sInt, 1> &dst);	
void Convert(const QVImage<uShort, 1> &src, QVImage<uInt, 1> &dst);	
void Convert(const QVImage<uShort, 1> &src, QVImage<sShort, 1> &dst);	
//void Convert(const QVImage<uShort, 1> &src, QVImage<uShort, 1> &dst);	

void Convert(const QVImage<uShort, 3> &src, QVImage<sFloat, 3> &dst);	
void Convert(const QVImage<uShort, 3> &src, QVImage<uChar, 3> &dst);	
void Convert(const QVImage<uShort, 3> &src, QVImage<sChar, 3> &dst);	
void Convert(const QVImage<uShort, 3> &src, QVImage<sInt, 3> &dst);	
void Convert(const QVImage<uShort, 3> &src, QVImage<uInt, 3> &dst);	
void Convert(const QVImage<uShort, 3> &src, QVImage<sShort, 3> &dst);	
//void Convert(const QVImage<uShort, 3> &src, QVImage<uShort, 3> &dst);	

// 3 channels to 1 channel convertions
void Convert(const QVImage<sFloat, 3> &, QVImage<sFloat, 1> &);
void Convert(const QVImage<sChar, 3> &, QVImage<sChar, 1> &);
void Convert(const QVImage<uChar, 3> &, QVImage<uChar, 1> &);
void Convert(const QVImage<sInt, 3> &, QVImage<sInt, 1> &);
void Convert(const QVImage<uInt, 3> &, QVImage<uInt, 1> &);
void Convert(const QVImage<sShort, 3> &, QVImage<sShort, 1> &);
void Convert(const QVImage<uShort, 3> &, QVImage<uShort, 1> &);

// 1 channel to 3 channels convertions
void RGBToGray(const QVImage<sFloat, 3> &, QVImage<sFloat, 1> &);
void RGBToGray(const QVImage<sChar, 3> &, QVImage<sChar, 1> &);
void RGBToGray(const QVImage<uChar, 3> &, QVImage<uChar, 1> &);
void RGBToGray(const QVImage<sInt, 3> &, QVImage<sInt, 1> &);
void RGBToGray(const QVImage<uInt, 3> &, QVImage<uInt, 1> &);
void RGBToGray(const QVImage<sShort, 3> &, QVImage<sShort, 1> &);
void RGBToGray(const QVImage<uShort, 3> &, QVImage<uShort, 1> &);

// 1 channel to 3 channels convertions
void Convert(const QVImage<sFloat, 1> &, QVImage<sFloat, 3> &);
void Convert(const QVImage<sChar, 1> &, QVImage<sChar, 3> &);
void Convert(const QVImage<uChar, 1> &, QVImage<uChar, 3> &);
void Convert(const QVImage<sInt, 1> &, QVImage<sInt, 3> &);
void Convert(const QVImage<uInt, 1> &, QVImage<uInt, 3> &);
void Convert(const QVImage<sShort, 1> &, QVImage<sShort, 3> &);
void Convert(const QVImage<uShort, 1> &, QVImage<uShort, 3> &);

#ifndef DOXYGEN_IGNORE_THIS
// Unimplemented functions
void Resize(const QVImage<uChar> &src, QVImage<uChar> &dest);
void Resize(const QVImage<uChar, 3> &src, QVImage<uChar, 3> &dest);
void YUV420ToRGB(const QVImage<uChar, 1> &srcY, const QVImage<uChar, 1> &srcU, const QVImage<uChar, 1> &srcV, QVImage<uChar, 3> &destRGB);
void RGBToYUV420(const QVImage<uChar, 3> &src, QVImage<uChar, 1> &dstY, QVImage<uChar, 1> &dstU, QVImage<uChar, 1> &dstV);
#endif // DOXYGEN_IGNORE_THIS
#else // QVIPP

// Functions not provided by the IPP.
// sFloat
void Convert(const QVImage<sFloat, 1> &src, QVImage<sChar, 1> &dst);
void Convert(const QVImage<sFloat, 1> &src, QVImage<sInt, 1> &dst);
void Convert(const QVImage<sFloat, 1> &src, QVImage<uInt, 1> &dst);
void Convert(const QVImage<sFloat, 3> &src, QVImage<sChar, 3> &dst);
void Convert(const QVImage<sFloat, 3> &src, QVImage<sInt, 3> &dst);
void Convert(const QVImage<sFloat, 3> &src, QVImage<uInt, 3> &dst);

// uChar
void Convert(const QVImage<uChar, 1> &src, QVImage<sChar, 1> &dst);
void Convert(const QVImage<uChar, 1> &src, QVImage<uInt, 1> &dst);
void Convert(const QVImage<uChar, 3> &src, QVImage<sChar, 3> &dst);
void Convert(const QVImage<uChar, 3> &src, QVImage<uInt, 3> &dst);

// sChar
void Convert(const QVImage<sChar, 1> &src, QVImage<sFloat, 1> &dst);
void Convert(const QVImage<sChar, 1> &src, QVImage<uChar, 1> &dst);
void Convert(const QVImage<sChar, 1> &src, QVImage<sInt, 1> &dst);
void Convert(const QVImage<sChar, 1> &src, QVImage<uInt, 1> &dst);
void Convert(const QVImage<sChar, 1> &src, QVImage<sShort, 1> &dst);
void Convert(const QVImage<sChar, 1> &src, QVImage<uShort, 1> &dst);
void Convert(const QVImage<sChar, 3> &src, QVImage<sFloat, 3> &dst);
void Convert(const QVImage<sChar, 3> &src, QVImage<uChar, 3> &dst);
void Convert(const QVImage<sChar, 3> &src, QVImage<sInt, 3> &dst);
void Convert(const QVImage<sChar, 3> &src, QVImage<uInt, 3> &dst);
void Convert(const QVImage<sChar, 3> &src, QVImage<sShort, 3> &dst);
void Convert(const QVImage<sChar, 3> &src, QVImage<uShort, 3> &dst);

// sInt
void Convert(const QVImage<sInt, 1> &src, QVImage<sFloat, 1> &dst);
void Convert(const QVImage<sInt, 1> &src, QVImage<sChar, 1> &dst);
void Convert(const QVImage<sInt, 1> &src, QVImage<uInt, 1> &dst);
void Convert(const QVImage<sInt, 1> &src, QVImage<sShort, 1> &dst);
void Convert(const QVImage<sInt, 1> &src, QVImage<uShort, 1> &dst);
void Convert(const QVImage<sInt, 3> &src, QVImage<sFloat, 3> &dst);
void Convert(const QVImage<sInt, 3> &src, QVImage<sChar, 3> &dst);
void Convert(const QVImage<sInt, 3> &src, QVImage<uInt, 3> &dst);
void Convert(const QVImage<sInt, 3> &src, QVImage<sShort, 3> &dst);
void Convert(const QVImage<sInt, 3> &src, QVImage<uShort, 3> &dst);

// uInt
void Convert(const QVImage<uInt, 1> &src, QVImage<sFloat, 1> &dst);
void Convert(const QVImage<uInt, 1> &src, QVImage<uChar, 1> &dst);
void Convert(const QVImage<uInt, 1> &src, QVImage<sChar, 1> &dst);
void Convert(const QVImage<uInt, 1> &src, QVImage<sInt, 1> &dst);
void Convert(const QVImage<uInt, 1> &src, QVImage<sShort, 1> &dst);
void Convert(const QVImage<uInt, 1> &src, QVImage<uShort, 1> &dst);
void Convert(const QVImage<uInt, 3> &src, QVImage<sFloat, 3> &dst);
void Convert(const QVImage<uInt, 3> &src, QVImage<uChar, 3> &dst);
void Convert(const QVImage<uInt, 3> &src, QVImage<sChar, 3> &dst);
void Convert(const QVImage<uInt, 3> &src, QVImage<sInt, 3> &dst);
void Convert(const QVImage<uInt, 3> &src, QVImage<sShort, 3> &dst);
void Convert(const QVImage<uInt, 3> &src, QVImage<uShort, 3> &dst);

// sShort
void Convert(const QVImage<sShort, 1> &src, QVImage<sChar, 1> &dst);
void Convert(const QVImage<sShort, 1> &src, QVImage<uInt, 1> &dst);
void Convert(const QVImage<sShort, 1> &src, QVImage<uShort, 1> &dst);
void Convert(const QVImage<sShort, 3> &src, QVImage<sChar, 3> &dst);
void Convert(const QVImage<sShort, 3> &src, QVImage<uInt, 3> &dst);
void Convert(const QVImage<sShort, 3> &src, QVImage<uShort, 3> &dst);

// uShort
void Convert(const QVImage<uShort, 1> &src, QVImage<sChar, 1> &dst);
void Convert(const QVImage<uShort, 1> &src, QVImage<uInt, 1> &dst);
void Convert(const QVImage<uShort, 1> &src, QVImage<sShort, 1> &dst);
void Convert(const QVImage<uShort, 3> &src, QVImage<sChar, 3> &dst);
void Convert(const QVImage<uShort, 3> &src, QVImage<uInt, 3> &dst);
void Convert(const QVImage<uShort, 3> &src, QVImage<sShort, 3> &dst);

void RGBToGray(const QVImage<sChar, 3> &src, QVImage<sChar, 1> &dst);
void RGBToGray(const QVImage<uInt, 3> &src, QVImage<uInt, 1> &dst);
void RGBToGray(const QVImage<sInt, 3> &src, QVImage<sInt, 1> &dst);

void Copy(const QVImage<sChar, 1> &src1, const QVImage<sChar, 1> &src2, const QVImage<sChar, 1> &src3, QVImage<sChar, 3> &dst);
void Copy(const QVImage<uInt, 1> &src1, const QVImage<uInt, 1> &src2, const QVImage<uInt, 1> &src3, QVImage<uInt, 3> &dst);

#endif // QVIPP

#endif // QVIMAGE_H
