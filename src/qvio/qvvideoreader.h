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

/// @file qvvideoreader.h
/// @brief Multisource video input implementation class in QVision.
/// @author PARP Research Group. University of Murcia, Spain.

#ifndef QVVIDEOREADER_H
#define QVVIDEOREADER_H

#include <QString>
#include <QVImage>

class QVBaseReader;

/*!
@class QVVideoReader src/qvio/qvvideoreader.h QVVideoReader

@brief Extremely versatile class to read from multiple video devices and video/image file formats.

This class implements a generic video reader interface to read images from different video sources. Currently, it
uses one of the following underlying mechanisms to read from them (though programmers could also easily extend
this functionality by inheriting from the @ref QVBaseReader class; see documentation on that class for details):

- Qt native read of several image formats (possibly read in sequence from a given directory).
- QVision implemented read of raw (uncompressed) YUV4MPEG2 video format.
- <a href="http://opencv.willowgarage.com/wiki/">OpenCV</a> library as a backend for reading video files and
locally connected cameras (USB or firewire).
- <a href="http://www.mplayerhq.hu/">MPlayer</a> as a backend application, to open and read frames
from a wide variety of video sources, including video files encoded with very different media formats, webcams,
digital cameras, internet video streams, or even DVB/TDT devices.

The class internally implements scaling and RGB/YUV/gray color conversions, so that the programmer can
transparently ask for the desired image size and color format when grabbing images.

\section VideoReaderURLFormat Video source identifiers
Any video source (video files, webcams, remote videos, etc...) is identified by a URL string, with the following
<b>available formats</b>:
<i>(Notation: [] means optional, {} means alternative)</i>:

 - <b>Local directory of images</b>: \verbatim dir://path-to-dir-of-images/ \endverbatim Reads every file in the
 given directory with one of the supported image file formats (@c jpg, @c png, @c bmp, @c pgm, @c gif, @c pbm,
 @c ppm, @c tiff, @c xbm, @c xpm). Path can be relative, or absolute. Absolute paths begin with an extra slash.
 Example: \verbatim dir:///home/user/images/ \endverbatim

 - <b>Local directory of images filtered by name pattern</b>:
   \verbatim dir://path-to-dir-of-images/glob-pattern \endverbatim
   Again, path can be relative, or absolute, and absolute paths begin with an extra slash. The @c glob-pattern can
   include the typical * and ? wildcard characters. Example:
   \verbatim dir:///home/user/images/p*-???.jpg \endverbatim

 - <b>Reading directly an uncompressed yuv4mpeg file</b>:
   \verbatim yuv4mpeg://[path-to-dir-of-videos/]video.yuv \endverbatim
   Again, path can be relative, or absolute, and absolute paths begin with an extra slash. Example:
   \verbatim yuv4mpeg:///home/user/videos/football.yuv \endverbatim

 - <b>Reading a local video file through OpenCV (needs the OpenCV library)</b>:
   \verbatim cvf://[path-to-dir-of-videos/]video.{avi, mpg, dv, ...} \endverbatim
   Again, path can be relative, or absolute, and absolute paths begin with an extra slash. Example:
   \verbatim cvf:///home/user/videos/sequence.avi \endverbatim

 - <b>Reading a webcam/firewire camera through OpenCV (needs the OpenCV library)</b>:
   \verbatim cvc://#number_of_camera \endverbatim
   Example:
   \verbatim cvc://#0 \endverbatim

 - <b>Reading a local video file compatible with mplayer (needs mplayer compatibility enabled)</b>:
   \verbatim file://[path-to-file/]file-name.{avi, mpg, dv, ...} \endverbatim
   Again, path can be relative, or absolute, and absolute paths begin with an extra slash. Examples:
   \verbatim file:///home/vision/penguin.dv \endverbatim
   \verbatim file://../videos/football.avi \endverbatim

 - <b>Remote video file (via http, rtsp, ftp) (needs mplayer compatibility enabled)</b>:
   \verbatim {http,rtsp,ftp}://domain-name/path-to-file/file.{avi, mpg, dv, ...} \endverbatim
   Examples:
   \verbatim rtsp://ficheros.7rm.es/7RM/7rm06-01-071430.rm \endverbatim
   \verbatim http://perception.inf.um.es/public_data/videos/misc/minuto.avi \endverbatim
   \verbatim ftp://user:passwd@server.dom/data/video.avi \endverbatim

 - <b>DVD | VCD video track: (needs mplayer compatibility enabled)</b>:
   \verbatim {dvd,vcd}://{video track}\endverbatim
   See mplayer system man page for correct URL formation for a specific title, track, device, etc. Examples:
   \verbatim dvd://2 \endverbatim
   \verbatim vcd://1 \endverbatim

 - <b>Video 4 linux, video 4 linux 2 camera through mplayer (needs mplayer compatibility enabled)</b>:
   \verbatim {v4l,v4l2}://{device file} \endverbatim
   Needs mplayer compatibility enabled. Example:
   \verbatim v4l2:///dev/video0 \endverbatim

 - <b>TDT channels (needs mplayer compatibility enabled)</b>:
   \verbatim dvb://CHANNEL-NAME \endverbatim
   Of course, valid only for systems with adequate DVB hardware and Mplayer DVB subsystem correctly configured
   (i.e., @c mplayer/channels.conf must have been configured before, using the corresponding channel scan utility;
   for example, the @c scan utility from the package @c dvd-apps, in the case of Ubuntu Linux). Example:
   \verbatim dvb://TVE1 \endverbatim

\subsection AbbreviatedVideoReaderURLFormat Abbreviated video source identifiers

If you do not explicitly specify any of the former URL schemes (@c dir://, @c yuv4mpeg://, ...), the following
<b>simplified formats</b> are used by default:

    - If it is specified just the path to a video file, by default @c #file:// is used, except if the file has .yuv
    extension, in which case @c yuv4mpeg:// is used by default.

    - If it is specified just the path to a directory, @c dir:// is used by default. The same is valid if the user
    specifies a file pattern with a relative or absolute path (i.e. <c>/home/user/dir/imag*.jpg</c> or
    <c>./img?.bmp</c>, for example).

    - If it is specified just the path to a video device, for example, @c /dev/video0 (only in linux), @c v4l2://
    is used by default.

    - If it is specified a number preceded by @c # (i.e. @c #0, @c #1), @c cvc:// is used by default.

    - If it is specified a string starting with @c ftp. or @c www., the corresponding schemes @c #ftp:// and
    @c #http:// will be used by default.

@subsection SpecialVideoReaderURLFormat Additional source-specific parameters

In some cases, the URL string can be used to specify additional source-specific parameters. For example,
specifying a frame-rate is commonly required to open <i>v4l2</i> webcams through mplayer. Both extended and
simplified formats can include special parameters for tuning device input options. Some additional examples of
these parameters include:

 - <b>width=&lt;value&gt;</b>   <br>sets the width of the image frames to be read from the video device.
 - <b>height=&lt;value&gt;</b>   <br>sets the height of the image frames to be read from the video device.
 - <b>fps=&lt;value&gt;</b>   <br>sets the number of frames per second to be read from the video device.
 - <b>[brightness|contrast|hue|saturation]=[-100, 100]</b>
     <br>sets the brightness, contrast, hue or saturation for the device.

You can get a complete list of these options in the MPlayer documentation (option <i>-tv</i>). All these options
work only for video 4 Linux, video 4 Linux 2 cameras. They can be included appending a <i>?</i> sign
after the URL for the device, and separated with <i>&</i> signs. Some example usages of these URL options follow:

 - URL to open a V4L2 device specifying 25 frames per second, image size of 640x480, and minimum brightness:
  \verbatim v4l2:///dev/video0?height=480&width=640&brightness=-100&fps=25 \endverbatim
 - The same device and configuration using a simplified URL:
  \verbatim /dev/video0?height=480&width=640&brightness=-100&fps=25 \endverbatim

@remarks Please take into account that setting the width and height for the images read from the input device using
parameters <i>width</i> and <i>height</i> differs from using rows and cols parameters of the open() method. The
former tries to configure the device to capture images using a higher or lesser resolution, while the latter
simply (post-)scale the images as MPlayer reads them from the input device in their original sizes.

@see QVVideoReaderBlock QVBaseReader
*/
class QVVideoReader : public QObject
    {
    Q_OBJECT
    public:
        /// @brief Open options for a video source. Combine them using OR (|) to form a valid QVVideoReader::OpenOptions value.
        ///
        /// (Note that not all source types support all options).
        enum OpenOption {
            /// Default options: don't include any of the other options.
            Default = 0x0,
            /// Do not try to ignore frame duration (i.e., do not use @c -benchmark when calling mplayer, or
            /// simulate requested fps in other sources such as dir://, yuv4mpeg://, etc.).
            RealTime = 0x1,
            /// (Mplayer only) Make mplayer deinterlace the image (odd lines).
            Deinterlaced = 0x2,
            /// Continue from the beginning of the video source when it reaches the end.
            NoLoop = 0x4
        };
        /// @brief Open options for a video source.
        /// @see QVVideoReader::OpenOption
        typedef QFlags<OpenOption> OpenOptions;
        //Q_DECLARE_FLAGS(OpenOptions,OpenOption);

        /// @brief Possible preferred modes for video sources.
        typedef enum {
            /// Source outputs YUV images by default.
            YUVMode= 0,
            /// Source outputs RGB images by default.
            RGBMode = 1,
            /// Source outputs gray only (BW) images by default.
            GrayOnlyMode = 2
        } TSourceMode;

        /// @brief Constructs a QVVideoReader.
        QVVideoReader();

        /// @brief Destroys a QVVideoReader.
        ~QVVideoReader();

        /// @brief Opens a video source given by its URL, trying to use requested options, mode, speed and output
        ///  scale sizes.
        ///
        /// \b Note: Please observe that though this class has image scaling capabilities, and thus it always
        /// tries to fulfill the user size request, the method could still slightly change the suggested size when
        /// opening the video (for example, an odd number of cols is not allowed, due to YUV422 format
        /// restrictions). On output, the suggested_rows and suggested_cols parameters will contain the correct
        /// values. This is specially useful when suggested_cols = suggested_rows = 0, which is interpreted as
        /// asking the grabbed frames to be in its original resolution (i.e. no scaling is performed). Of course,
        /// you can also use methods getCols() and getRows() on the subsequent grabbed frames to confirm these
        /// output values.
        ///
        /// @param url_string Video source identifying URL string. See above for availabe URL formats.
        /// @param suggested_cols Number of requested output cols (0 => ask for default width of video; otherwise
        /// scale).
        /// @param suggested_rows Number of requested output rows (0 => ask for default height of video; otherwise
        /// scale).
        /// @param suggested_fps Number of requested output fps (0 => default value of source; otherwise simulate delay).
        /// @param opts Camera opening options (see QVVideoReader::OpenOptions).
        /// @param source_mode On output, mode preferred by the video source (see QVVideoReader::TSourceMode).
        /// @return True if the video source was opened successfully, false otherwise.
        bool open(  const QString & url_string,
                    unsigned int & suggested_cols,
                    unsigned int & suggested_rows,
                    unsigned int & suggested_fps,
                    OpenOptions & opts,
                    TSourceMode & source_mode);

        /// @brief Opens a video source given by its URL, using default opening values.
        ///
        /// This is an overloaded form of the former method, provided by convenience. It will open the requested
        /// video source using default values of for the rest of input parameters (i.e. suggested_cols =
        /// suggested_rows = suggested_fps = 0, suggested_opts = Default, source_mode = YUVMode).
        ///
        /// @param url_string Video source identifying URL string. See above for availabe URL formats.
        /// @return True if the video source was successfully opened, false otherwise.
        bool open(const QString & url_string)
            {
            unsigned int suggested_cols = 0, suggested_rows = 0, suggested_fps = 0;
            OpenOptions suggested_opts = Default;
            TSourceMode source_mode = YUVMode;
            return open(url_string,suggested_cols,suggested_rows,suggested_fps,suggested_opts,source_mode);
            }

        /// @brief Grabs next frame in video source, saving corresponding image(s) in class internal state.
        ///
        /// This is the only method which makes the video source to advance to the next frame. Use any of the
        /// QVVideoReader::getGrayImage(), QVVideoReader::getRGBImage(), or QVVideoReader::getYUVImage() methods
        /// after grabbing to get the corresponding grabbed image(s).
        ///
        /// @return True if the video frame was successfully captured, false otherwise.
        bool grab();

        /// @brief Gets current frame in the form of a gray image.
        ///
        /// This method does NOT captures a new image; instead, it returns the last captured one. Use the
        /// QVVideoReader::grab() to advance to the next frame.
        ///
        /// @param imageGray captured gray image.
        void getGrayImage(QVImage<uChar> &imageGray);

        /// @brief Gets current frame in the form of a 3 channel RGB image.
        ///
        /// This method does NOT captures a new image; instead, it returns the last captured one. Use the
        /// QVVideoReader::grab() to advance to the next frame.
        ///
        /// @param imageRGB captured RGB image.
        void getRGBImage(QVImage<uChar,3> & imageRGB);

        /// @brief Gets current frame in the form of three separated Red, Green and Blue channel images.
        ///
        /// This method does NOT captures a new image; instead, it returns the last captured one. Use the
        /// QVVideoReader::grab() to advance to the next frame.
        ///
        /// @param imageR captured Red image.
        /// @param imageG captured Green image.
        /// @param imageB captured Blue image.
        void getRGBImage(QVImage<uChar> &imageR, QVImage<uChar> &imageG, QVImage<uChar> &imageB);

        /// @brief Gets current frame in the form of a gray image channel (Y) and two chrominance image channels
        /// (U and V).
        ///
        /// The U and V images will be at half the resolution (\f$ rows/2 \times cols/2 \f$) with respect to the Y
        /// image. This method does NOT captures a new image; instead, it returns the last captured one. Use the
        /// QVVideoReader::grab() to advance to the next frame.
        ///
        /// @param imageY captured Y image.
        /// @param imageU captured U image.
        /// @param imageV captured V image.
        void getYUVImage(QVImage<uChar> &imageY, QVImage<uChar> &imageU, QVImage<uChar> &imageV);

        /// @brief Gets the length of the video source.
        ///
        /// @return Gets the length of the video source (if possible), usually in number of frames (though,
        /// depending on the type of source, it could be in any othe unit, such as seconds or milliseconds, for
        /// example). It returns 0 if the value is not available.
        int getLength() const;

        /// @brief Gets the current position in the video source.
        ///
        /// @return Gets the current position in the video source length of the video source (if possible), usually
        /// in number of frames (though, depending on the type of source, it could be in any othe unit, such as
        /// seconds or milliseconds, for example). It returns 0 if the value is not available.
        int getPos() const;

    public slots:
        /// @brief Closes the video source.
        ///
        /// @return True if the video source was successfully closed, false otherwise.
        bool close();


        /// @brief Tries to move to a given position in the video source (if possible).
        ///
        /// @param pos Position to move to (usually in number of frames, but other units, such as seconds or
        /// milliseconds are also possible, depending on the specific source).
        /// @return True on success, false otherwise.
        bool seek(int pos);

    signals:
        /// @brief Signal emitted when video source has been opened.
        void sourceOpened();

        /// @brief Signal emitted when video source has been closed.
        void sourceClosed();

        /// @brief Signal emitted when a new frame has been grabbed.
        void newGrab();

    public:
        /// @brief Returns the complete URL of the video source.
        ///
        /// @return Complete URL of the video source.
        const QString getURL() const            { return url; };

        /// @brief Returns the scheme of the video source.
        ///
        /// @return Scheme (file, @c dir, @c yuv4mpeg, @c cvc, @c cvf, ...; see above) of the video source.
        const QString getScheme() const         { return scheme; };

        /// @brief Returns the number of cols for current frame in the video source.
        ///
        /// @return Number of cols for current frame in video source.
        unsigned int getCols() const            { return cols; };

        /// @brief Returns the number of rows for current frame in the video source.
        ///
        /// @return Number of rows for current frame in video source.
        unsigned int getRows() const            { return rows; };

        /// @brief Returns the number of frames per second of the video source.
        ///
        /// @return Number of fps in video source.
        unsigned int getFPS() const             { return fps; };

    private:
        QString url, scheme;
        bool changing_size;
        unsigned int cols, rows, fps, frames_grabbed;
        bool camera_opened, live_camera, end_of_video;
        bool availableGray,availableRGB3,availableYUV,availableRGB;

        QVImage<uChar> imgGray;
        QVImage<uChar, 3> imgRGB;
        QVImage<uChar> imgY, imgU, imgV;
        QVImage<uChar> imgR, imgG, imgB;

        OpenOptions open_options;
        TSourceMode source_mode;
        QVBaseReader *base_reader;
    };

// Opening flags | operator:
Q_DECLARE_OPERATORS_FOR_FLAGS(QVVideoReader::OpenOptions);

#endif //QVVIDEOREADER
