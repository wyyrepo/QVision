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

/// @file qvvideoreaderblock.h
/// @brief Video reader processing block.
/// @author PARP Research Group. University of Murcia, Spain.

#ifndef QVVIDEOREADERBLOCK_H
#define QVVIDEOREADERBLOCK_H

#include <QVProcessingBlock>
#include <QVImage>
#include <QVVideoReader>

/*!
@class QVVideoReaderBlock qvblockprogramming/qvioblocks/qvvideoreaderblock.h QVVideoReaderBlock

@brief This is a generic video input processing block for the QVision architecture.

This is a generic video input processing block (see @ref QVProcessingBlock) for the QVision architecture, which is
based on the corresponding generic video source reader class @ref QVVideoReader. You will find it very useful when
writing QVision programs which have to process a sequence of video images, as it provides you with a lot of
functionality by default, such as selecting from a wide range of video sources in runtime, rescaling input images,
grab YUV, gray or RGB images, pausing the video, or going directly to a desired position in it, among many other
possibilities. Compile and test example @ref videoReader.cpp in @ref ExamplePrograms section for a quick hands-on
introduction to its usage.

As any other @ref QVProcessingBlock, it has some custom input and output properties:

\par Input properties:

The user can set desired values for these properties directly through the command line, and the programmer through
the corresponding @ref QVProcessingBlock::setPropertyValue method:

- <i>NoLoop</i> (bool): If the source should be opened in no loop mode.
- <i>RealTime</i> (bool): If the source should be opened in real time mode.
- <i>URL</i> (QString): URL of the video source to read.
- <i>Cols</i> (int): Number of suggested columns for the video source.
- <i>Rows</i> (int): Number of suggested rows for the video source.

\b Note.- RealTime property is also input (and as such can be initialized using the command line), but
invisible to the GUI (because once the source has been linked, it cannot be relinked changing its synchronism).

\b Note.- Note also that you can open the camera in a different size of that specified in the real video source,
by setting the desired values of properties <i>Cols</i> and <i>Rows</i> (this class will automatically
rescale output images if needed).

\par Output properties:

These can be accessed using the corresponding @ref QVProcessingBlock::getPropertyValue method:

- <i>Opened</i> (bool): Tells if the camera is correctly opened and working.
- <i>FPS</i> (int): FPS of the video.
- <i>Frames</i> (int): Number of read frames up to now.
- <i>ColsR</i> (int): Actual number of columns of the video -not necessarily equal to the number of requested
columns, which will in any case be transparently rounded to the nearest upper even integer-.
- <i>RowsR</i> (int): Actual number of rows of the video -not necessarily equal to the number of requested rows,
which will in any case be transparently rounded to the nearest upper even integer-.
- <i>Pos</i> (double): Current position in the video, if available.
- <i>Length</i> (double): Length of the video, if available.

\a Note.- Remember again that you can open the camera in a different size of that specified in the real video
source file (this class will automatically rescale output images if needed); thus, <i>ColsR</i> and <i>RowsR</i>
will always contain the real size of the output images served by this block.

\par Output image properties:

Again, these can be accessed using the QVProcessingBlock::getPropertyValue method:

- <i>RGB image</i> (@ref QVImage<uChar,3>): Last grabbed RGB image.
- <i>Y channel image</i> (@ref QVImage<uChar,1>): Last grabbed Y channel image (gray level image).
- <i>U channel image</i> (@ref QVImage<uChar,1>): Last grabbed U channel image.
- <i>V channel image</i> (@ref QVImage<uChar,1>): Last grabbed V channel image.

\remarks

- Output image properties can (and should!) be linked automatically, without the need of naming them explicitly,
using any of the @ref QVVideoReaderBlock::linkProperty() available methods.

- When using QVVideoReaderBlock objets in your program, you can specify any of the input properties at the start
of the program, using the command line parameters; for example, the file to read the video from could be specified
by calling the program this way: <tt>./program --URL="/home/me/myfile.avi --Rows=300 --Cols=400" </tt>. But
modification of these properties can also be done directly in the corresponding graphical widgets when reopening
the camera during execution (though, of course, these new values will have no effect until the camera is
reopened).

- Two important properties worth a little more discussion are <i>RealTime</i> and <i>NoLoop</i>, both boolean. The
first one specifies if the camera will be read in real time mode -possibly leaving frames unprocessed, if
processing is slower than reading (RealTime=true)-, or at maximum speed -but without leaving any frame unprocessed
in any case (RealTime=false)-. The second one specifies if the camera will be closed when the end of the file is
reached (NoLoop=true), or will loop, starting from the first frame again and again (NoLoop=false).

@see QVVideoReader QVBaseReader

@ingroup qvblockprogramming
*/

class QVVideoReaderBlock: public QVProcessingBlock
{
Q_OBJECT
public:

    /// @brief Constructor for QVVideoReaderBlock class.
    ///
    /// @param name the (optional) name given to the camera block.
    QVVideoReaderBlock(QString name = QString(""));

    /// @brief Destructor for QVVideoReaderBlock class.
    ~QVVideoReaderBlock();

    /// @brief Links a @ref QVImage<uChar,3> (RGB image) or @ref QVImage<uChar,1> (gray image) from the camera
    /// to another block.
    ///
    /// This method will automatically link, using the adequate synchronism (Asynchronous for real time cameras
    /// and Synchronous for non real time cameras; see @ref QVPropertyContainer), a gray or an RGB image in the
    /// block to the corresponding output image property of the camera. An error (return value=false) will occur
    /// if dstProp is not of the adequate type (@ref QVImage<uChar,3> or @ref QVImage<uChar,1>).
    ///
    /// @param dstCont Pointer to the destination block.
    /// @param dstProp Name of the destination property.
    /// @return true if success, false otherwise.
    bool linkProperty(QVPropertyContainer *dstCont, QString dstProp);

    /// @brief Links 3 @ref QVImage<uChar,1> from the camera (YUV channels) to the corresponding ones of
    /// another block.
    ///
    /// This method will automatically link, using the adequate synchronism (Asynchronous for real time cameras
    /// and Synchronous for non real time cameras; see @ref QVPropertyContainer), a set of three one channel
    /// images in the block to the corresponding output image properties of the camera. An error (return
    /// value=false) will occur if any of the dstProp are not of the adequate @ref QVImage<uChar,1> type.
    ///
    /// @param dstCont Pointer to the destination block.
    /// @param dstProp1 Name of the destination property for image Y (or R; see YUV_RGB parameter).
    /// @param dstProp2 Name of the destination property for image U (or G; see YUV_RGB parameter).
    /// @param dstProp3 Name of the destination property for image V (or B; see YUV_RGB parameter).
    /// @param YUV_RGB if false (default), Y, U and V images are linked; otherwise, R, G, and B will be linked.
    /// @return true if success, false otherwise.
    bool linkProperty(QVPropertyContainer *dstCont, QString dstProp1, QString dstProp2, QString dstProp3, bool YUV_RGB=false);

protected:
    bool realTime, noLoop, deinterlaced;

    /*
    virtual bool open(QString urlName, int &cols, int &rows, int &fps, bool &YUV_RGB) = 0;
    virtual void close() = 0;
    virtual bool grab(QVImage<uChar,1> &imgY_R, QVImage<uChar,1> &imgU_G, QVImage<uChar,1> &imgV_B) = 0;
    virtual double lengthOfVideo() = 0;
    virtual double currentPos() = 0;*/

signals:
    /// @brief Emitted each time a new video source is opened.
    void opened();

    /// @brief Emitted each time the video source is closed.
    void closed();

    /// @brief Emitted each time a new frame is grabbed.
    void grabbed();

private:
    bool flush_pending_images;
    QString urlName;
    QVImage<uChar,1> imageY, imageU, imageV, imageR, imageG, imageB;
    QVImage<uChar,3> imageRGB;

    void tryOpeningCam();
    void iterate();
    void connectOrDisconnectLinkedBlocks(bool connect_disconnect);
    QVVideoReader video_reader;

private slots:
    /// @brief Slot to set a new time position in the video.
    ///
    /// Reimplementations of this method should set the current position in the video in seconds (if possible).
    void setPos(int pos) { video_reader.seek(pos) ;};

    /// @brief Reopens the camera, using possibly new input parameters.
    ///
    /// When this slot is called, the running camera is immediately closed, and the current values of the
    /// input properties are immediately used to reopen the camera source.
    void reopen();

    /// @brief Resets the camera block.
    ///
    /// When this slot is called, the running camera is immediately closed, and the block stopped.
    void reset();

    void grabFrame();

    void nothing() {/* Just to block connected blocks if in real time (using Qt::BlockingQueuedConnection) */};
};

#endif // QVVIDEOREADERBLOCK_H
