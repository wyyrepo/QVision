/*
 *   Copyright (C) 2007, 2008, 2009, 2010, 2011, 2012. PARP Research Group.
 *   <http://perception.inf.um.es>
 *   University of Murcia, Spain.
 *
 *   This file is part of the QVision library.
 *
 *   QVision is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as
 *   published by the Free Software Foundation, version 3 of the License.
 *
 *   QVision is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with QVision. If not, see <http://www.gnu.org/licenses/>.
 */

/// @file qvbasereader.h
/// @brief Pure virtual base class for every video input implementation class in QVision.
/// @author PARP Research Group. University of Murcia, Spain.

#ifndef QVBASEREADER_H
#define QVBASEREADER_H

#include<QVImage>

#include<QVVideoReader>

/*!
@class QVBaseReader src/qvio/qvbasereader.h QVBaseReader

@brief Pure virtual base class to create input video reader components for the QVision architecture.

@note Normal QVision users do not need to worry about this class and its derived classes, unless they want to
implement new video sources (apart from the wide range of video sources supported by QVision; see @ref
QVVideoReader for a comprehensive list of supported video sources).

This class is pure virtual, and should not be used by normal QVision users (except when implementing their own
video sources, such as, say, direct driver-based IEEE 1394 or V4L2 cameras; remember, though, that @ref
QVVideoReader can read almost any kind of video input source, including video files and live cameras, such as USB
webcams, IEEE 1394 cameras, remote streaming videos and even directories of image files, among many other
possibilities). Any derived classes of @ref QVBaseReader (currently @ref QVMPlayerReader, @ref QVOpenCVReader,
@ref QVDirReader and @ref QVYUV4MPEG2Reader) are the (internal) classes responsible for implementing all this
functionality. This classes are not documented because they will not be used directly by final users, though
taking a look at their sources could be useful for new video sources implementors.

Implementors of new kind of QVVideoReader classes should only have to redefine these six pure virtual methods:

@code
virtual bool open(const QString & url_string,
                  unsigned int & suggested_cols,unsigned int & suggested_rows, unsigned int & suggested_fps,
                  QVVideoReader::OpenOptions & suggested_opts, QVVideoReader::TSourceMode & source_mode) = 0;

virtual bool close() = 0;

virtual bool grab(QVImage<uChar,1> &imgY_R, QVImage<uChar,1> &imgU_G, QVImage<uChar,1> &imgV_B) = 0;

virtual int getLength() = 0;

virtual int getPos() = 0;

virtual bool seek(int pos) = 0;
@endcode

Whose desired behaviour is almost self-explanatory (if we are confident with the @ref QVVideoReader class program
interface):

- The first one (@ref QVBaseReader::open) should open the video source specified by the string @a url_string,
trying to open it with the suggested @a cols, @a rows and @a fps. The @a url_string is a generic QString that will
be used differenty by the diferent classes inheriting from QVBaseReader, according to their needs (see code source
for those classes and @ref QVVideoReader documentation for some examples). The same can be said for the rest of
suggested parameters (@a rows, @a cols, @a fps and @a opening options). Finally, the output parameter @a
source_mode (of type @ref QVVideoReader::TSourceMode) will return @ref QVVideoReader::YUVMode, @ref
QVVideoReader::RGBMode or @ref QVVideoReader::GrayOnlyMode if the capture method of the source returns YUV, RGB or
gray images, respectively, by default. If the video source allows to choose for any of these modes, this parameter
could also be used as input, taking into account that it is only a recomendation and, as is the case with @a
suggested_rows, @a suggested_cols and @a suggested_fps, the output value will be the mode that will be really
used. The method must indicate a successful opening by returning true (and updating the corresponding @a
suggested_cols, @a suggested_rows and @a suggested_fps output values to the really obtained ones, which could
coincide or not with the suggested input values), or false, if there was any problem opening the source.

- The second (@ref QVBaseReader::close) must close the video source, returning true on success.

- The third (@ref QVBaseReader::grab) must grab either the Y, U and V channel images in the corresponding variable
parameters, with respective sizes \f$ cols \times rows \f$, \f$ cols/2 \times rows/2 \f$ and \f$ cols/2 \times
rows/2 \f$ , or the R, G and B channel images, in this case the three of them with \f$ cols \times rows \f$ size.
If the YUV or RGB images are the ones that the method will fill is determined by the value @a source_mode returned
by the open method (see @ref QVVideoReader::TSourceMode). In all cases the values @a cols and @a rows (i.e., the
size of the output images) will correspond with the values @a suggested_cols and @a suggested_rows as returned by
the corresponding @ref open method. The @ref grab method should return true if grabbing was succesful, or false
otherwise (for example, if the video source was closed).

- The fourth method (@ref QVBaseReader::getLength) must return the length of the video, as an integer value. This
value is usually expressed in total number of frames, though it can also be 0 if it is not available (for example,
for live video cameras), or even in any other integer units (such as seconds, milliseconds, or whatever, depending
on the kind of video source).

- The fifth method (@ref QVBaseReader::getPos) must return the current position in the video, again as an integer
value (the same comments for units on the former method apply).

- Finally, the sixth method (@ref QVBaseReader::seek) must set, if possible, the current position on the video,
again in the same units as the former two methods, returning true if the seek operation was succesful.

\remarks

- Remember that each video source will have a preferred Gray, YUV or RGB output mode. Thus, if a given source has,
say, a YUV output preferred mode (such as in a @ref QVMPlayerReader, for example), there is no point in performing
a YUV to RGB conversion inside the corresponding inheriting class of @ref QVBaseReader, because this is
implemented for every video source in the more general class @ref QVVideoReader (which is itself client of this
@ref QVBaseReader class). An analogous argument holds for the converse case -preferred output mode RGB (as in a
@ref QVOpenCVReaderBlock), and desired YUV output-, as well as for image rescalings (resizing), which are also
implemented in @ref QVVideoReader, and thus should not be performed by the inheriting class. Thus, the suggested
@a cols and @a rows parameters should only be treated by the video source itself (for example, to suggest an
adequate opening size for a camera), and not as a rescaling after the capture (which is in any case performed by
the client class @ref QVVideoReader).

- Anyway, the QVision library currently only makes these conversions/resizings if the Intel IPP library module has
been enabled; otherwise, the user will be presented an according error message, and will be requested to use the
other set of three images, and then perform the conversion in its own program.

- When reimplementing this class for gray only sources, use @ref QVVideoReader::GrayOnlyMode (see @ref
QVVideoReader::TSourceMode) and fill the Y image in the reimplemented grab method with the gray image, and then
two 128 valued images downscaled to 1/2 of its size for the U and V channels.

- Of course, in every case the reimplemented @ref grab method for the @ref QVBaseReader subclass must return R, G
and B or Y, U and V images with corresponding correct sizes (i.e., same sizes for R, G, and B channels, and U and
V channels half sized with respect to the Y channel). Otherwise a fatal error will occur when trying to read from
the video source, and the application will immediately abort.

@see QVVideoReader QVVideoReaderBlock
*/

class QVBaseReader
    {
    public:
        /// @brief Constructs a QVBaseReader.
        QVBaseReader() {};

        /// @brief Destroys a QVBaseReader.
        ~QVBaseReader() {};

        /// @brief Pure virtual open method.
        ///
        /// Reimplementations of this method should open the video source specified by @a url_string, trying to
        /// open it with the suggested @a cols, @a rows and @a fps. The method must indicate a successful opening
        /// by returning true (and updating the corresponding @a suggested_cols, @a suggested_rows and @a
        /// suggested_fps output values to the really obtained ones, which could coincide or not with the
        /// suggested input values), or false, if there was any problem opening the source. The same can be said
        /// for the suggested opening options. Finally, the output parameter source_mode will return @ref
        /// QVVideoReader::YUVMode, @ref QVVideoReader::RGBMode or @ref QVVideoReader::GrayOnlyMode if the capture
        /// method of the source returns YUV, RGB or gray images, respectively, by default. If the video source
        /// allows to choose for any of three modes, this parameter could also be used as input, taking into
        /// account that it is only a recomendation and, as is the case with @a suggested_rows, @a suggested_cols
        /// and @a suggested_fps, the output value will be the mode that will be really used.
        ///
        /// @param url_string QString determining the video source.
        /// @param suggested_cols Suggested number of columns (as input). On return contains real number of columns (as output).
        /// @param suggested_rows Suggested number of rows (as input). On return contains real number of rows (as output).
        /// @param suggested_fps Suggested fps (as input). On return contains real fps (as output).
        /// @param suggested_opts Suggested options (as input).
        /// @param source_mode Set to suggested source mode (as input) and set to source preferred mode (on output).
        ///
        /// @return true if success, false in case of failure.
        virtual bool open(  const QString & url_string,
                            unsigned int & suggested_cols,
                            unsigned int & suggested_rows,
                            unsigned int & suggested_fps,
                            QVVideoReader::OpenOptions & suggested_opts,
                            QVVideoReader::TSourceMode & source_mode) = 0;

        /// @brief Pure virtual close method.
        ///
        /// Reimplementations of this method should close the video source.
        ///
        /// @return true if success, false in case of failure.
        virtual bool close() = 0;

        /// @brief Pure virtual grab method.
        ///
        /// Reimplementations of this method should grab Y, U and V channel images in the corresponding variable
        /// parameters, with respective sizes \f$ cols \times rows \f$ , \f$ cols/2 \times rows/2 \f$ and
        /// \f$ cols/2 \times rows/2 \f$ (with @a cols and @a rows as returned by the @ref open() method), if the
        /// preferred source mode as returned by @ref open was @ref QVVideoReader::GrayOnlyMode or @ref
        /// QVVideoReader::YUVMode, or the R, G and B channels all with sizes \f$ cols \times rows \f$, if the
        /// preferred source mode returned by @ref open was @ref QVVideoReader::RGBMode. In every case the method
        /// must return true if grabbing was succesful, or false otherwise (for example, if the camera was
        /// closed). When reimplementing this class for gray only sources (@ ref QVVideoReader::GrayOnlyMode),
        /// fill the Y image in the reimplemented grab method with the gray image, and then two 128 valued images
        /// downscaled to 1/2 of its size (@a cols and @a rows) for the U and V channels.
        ///
        /// @param imgY_R On return, contains the grabbed Y/R image.
        /// @param imgU_G On return, contains the grabbed U/G image.
        /// @param imgV_B On return, contains the grabbed V/B image.
        ///
        /// @return true if success, false in case of failure.
        virtual bool grab(QVImage<uChar,1> &imgY_R, QVImage<uChar,1> &imgU_G, QVImage<uChar,1> &imgV_B) = 0;

        /// @brief Pure virtual method to get the length of the video.
        ///
        /// Reimplementations of this method should inform of the length of the video, as an integer value. This
        /// value should preferrably be in total number of frames units, though it can also be in any other
        /// integer units (such as seconds, milliseconds, or whatever) if frames units are not managed by the
        /// corresponding video source. Also, a length equal to 0 should be returned if the information is not
        /// available (for example, for live cameras, remote streaming videos, and the like).
        ///
        /// @return Total number of frames (or any other length unit; see above) of video source.
        virtual int getLength() = 0;

        /// @brief Pure virtual method to get the current position in the video.
        ///
        /// Reimplementations of this method should inform of the current position in the video (usually in number
        /// of frames units, but could also be in other units, such as seconds or milliseconds; see comments on
        /// method @ref getLength above).
        ///
        /// @return Current position in video source.
        virtual int getPos() = 0;

        /// @brief Pure virtual method to set the current  position in the video.
        ///
        /// Reimplementations of this method should set the current position in the video (in number of
        /// frames units, but could also be in other units, such as seconds or milliseconds; see comments on
        /// method @ref getLength above).
        ///
        /// @param pos Desired position in video source.
        ///
        /// @return true if success, false in case of failure.
        virtual bool seek(int pos) = 0;
    };

#endif //QVBASEREADER_H

