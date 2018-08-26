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

/// @file qvvideoreaderblock.cpp
/// @brief Video reader processing block.
/// @author PARP Research Group. University of Murcia, Spain.

#include <QTimer>

#ifdef QVIPP
#include <qvipp.h>
#endif

#ifdef QVOPENCV
#include <opencv/cv.h>
#endif

#include <QVImage>
#include <QVVideoReaderBlock>

#define DEFAULT_IMAGE_SIZE 128

QVVideoReaderBlock::QVVideoReaderBlock(QString name): QVProcessingBlock(name)
    {
    // Input properties:
    addProperty<bool>("NoLoop", inputFlag, FALSE,"If the camera should be opened in no loop mode");
    addProperty<bool>("Deinterlaced", inputFlag, FALSE,"If input image should be deinterlaced");
    addProperty<QString>("URL", inputFlag, QString("#0"),"URL of the video source to read");
    addProperty<int>("Cols", inputFlag, 0, "Suggested number of columns of the video");
    addProperty<int>("Rows", inputFlag, 0, "Suggested number of rows of the video");
    // RealTime property is also input (and as such can be initialized using the command line), but invisible to the GUI
    // (because once the camera has been linked, it cannot be relinked changing its synchronism):
    addProperty<bool>("RealTime", inputFlag|guiInvisible, FALSE, "If the camera should be opened in real time mode");

    // Output integer and boolean properties:
    addProperty<bool>("Opened", outputFlag, FALSE, "If the camera is correctly opened and working");
    addProperty<int>("FPS", outputFlag, 0, "FPS of the video");
    addProperty<int>("Frames", outputFlag, 0, "Number of read frames");
    addProperty<int>("ColsR", outputFlag, 0, "Actual number of columns of the video");
    addProperty<int>("RowsR", outputFlag, 0, "Actual number of rows of the video");
    addProperty<int>("Pos", outputFlag, 0.0, "Current position on the video");
    addProperty<int>("Length", outputFlag, 0.0, "Length of the video (0 if not available)");

    // Output image properties:
    addProperty< QVImage<uChar,3> >("RGB image", outputFlag, QVImage<uChar,3>(), "Last grabbed RGB image");
    addProperty< QVImage<uChar,1> >("Y channel image",outputFlag, QVImage<uChar,1>(), "Last grabbed Y channel image");
    addProperty< QVImage<uChar,1> >("U channel image",outputFlag, QVImage<uChar,1>(), "Last grabbed U channel image");
    addProperty< QVImage<uChar,1> >("V channel image",outputFlag, QVImage<uChar,1>(), "Last grabbed V channel image");
    addProperty< QVImage<uChar,1> >("R channel image",outputFlag, QVImage<uChar,1>(), "Last grabbed R channel image");
    addProperty< QVImage<uChar,1> >("G channel image",outputFlag, QVImage<uChar,1>(), "Last grabbed G channel image");
    addProperty< QVImage<uChar,1> >("B channel image",outputFlag, QVImage<uChar,1>(), "Last grabbed B channel image");

    // Initial images (only useful if first open fails, for a default set of images to be available...)
    imageR = QVImage<uChar>(DEFAULT_IMAGE_SIZE,DEFAULT_IMAGE_SIZE,DEFAULT_IMAGE_SIZE);
    imageG = QVImage<uChar>(DEFAULT_IMAGE_SIZE,DEFAULT_IMAGE_SIZE,DEFAULT_IMAGE_SIZE);
    imageB = QVImage<uChar>(DEFAULT_IMAGE_SIZE,DEFAULT_IMAGE_SIZE,DEFAULT_IMAGE_SIZE);
    imageY = QVImage<uChar>(DEFAULT_IMAGE_SIZE,DEFAULT_IMAGE_SIZE,DEFAULT_IMAGE_SIZE);
    imageU = QVImage<uChar>(DEFAULT_IMAGE_SIZE/2,DEFAULT_IMAGE_SIZE/2,DEFAULT_IMAGE_SIZE/2);
    imageV = QVImage<uChar>(DEFAULT_IMAGE_SIZE/2,DEFAULT_IMAGE_SIZE/2,DEFAULT_IMAGE_SIZE/2);
    Set(128,imageY);
    Set(128,imageU);
    Set(128,imageV);
    Set(128,imageR);
    Set(128,imageG);
    Set(128,imageB);
    setPropertyValue< QVImage<uChar, 1> >("Y channel image", imageY);
    setPropertyValue< QVImage<uChar, 1> >("U channel image", imageU);
    setPropertyValue< QVImage<uChar, 1> >("V channel image", imageV);
    setPropertyValue< QVImage<uChar, 1> >("R channel image", imageR);
    setPropertyValue< QVImage<uChar, 1> >("G channel image", imageG);
    setPropertyValue< QVImage<uChar, 1> >("B channel image", imageB);
    imageRGB = QVImage<uChar,3>(DEFAULT_IMAGE_SIZE,DEFAULT_IMAGE_SIZE);
    uchar value[3] = {128,128,128};
    Set(value,imageRGB);
    setPropertyValue< QVImage<uChar, 3> >("RGB image", imageRGB);

    // Flag needed later to flush out pending images in real time cameras when resetting the camera:
    flush_pending_images = FALSE;
    }

QVVideoReaderBlock::~QVVideoReaderBlock()
    {
    video_reader.close();
    }

static inline int iRoundUp(int a, int b)
    {
    return (a % b == 0) ? a : b*(a / b + 1) ;
    }

void QVVideoReaderBlock::tryOpeningCam()
{
    // We open the camera with the specified input properties, and update output properties accordingly:
    unsigned int cols, rows, fps;
    //bool yuv_rgb;

    // Read current input properties:
    realTime = getPropertyValue<bool>("RealTime");
    noLoop = getPropertyValue<bool>("NoLoop");
    deinterlaced = getPropertyValue<bool>("Deinterlaced");
    urlName = getPropertyValue<QString>("URL");
    cols =  getPropertyValue<int>("Cols");
    rows =  getPropertyValue<int>("Rows");

    // Virtual call; urlName is input parameter; cols and rows are input/output; fps and yuv_rgb are output.
    //if(this->open(urlName,cols,rows,fps,yuv_rgb))
    QVVideoReader::OpenOptions opts;
    QVVideoReader::TSourceMode source_mode;
    if(realTime) opts |= QVVideoReader::RealTime;
    if(noLoop) opts |= QVVideoReader::NoLoop;
    if(deinterlaced) opts |= QVVideoReader::Deinterlaced;
    if(video_reader.open(urlName,cols,rows,fps,opts,source_mode))
        {
        setPropertyValue<bool>("Opened",TRUE);
        setPropertyValue<int>("ColsR",cols);
        setPropertyValue<int>("RowsR",rows);
        setPropertyValue<int>("FPS",fps);
        setPropertyValue<int>("Frames",0);
        setPropertyValue<double>("Pos",video_reader.getPos());
        setPropertyValue<double>("Length",video_reader.getLength());

        const int default_size=128;
        imageY = QVImage<uChar>(default_size, default_size, iRoundUp(default_size,8));
        imageU = QVImage<uChar>(default_size/2, default_size/2, iRoundUp(default_size/2,8));
        imageV = QVImage<uChar>(default_size/2, default_size/2, iRoundUp(default_size/2,8));
        imageR = QVImage<uChar>(default_size, default_size, iRoundUp(default_size,8));
        imageG = QVImage<uChar>(default_size, default_size, iRoundUp(default_size,8));
        imageB = QVImage<uChar>(default_size, default_size, iRoundUp(default_size,8));
        imageRGB = QVImage<uChar,3>(default_size, default_size, iRoundUp(3*default_size,8));

        setPropertyValue< QVImage<uChar, 1> >("Y channel image", imageY);
        setPropertyValue< QVImage<uChar, 1> >("U channel image", imageU);
        setPropertyValue< QVImage<uChar, 1> >("V channel image", imageV);
        setPropertyValue< QVImage<uChar, 1> >("R channel image", imageR);
        setPropertyValue< QVImage<uChar, 1> >("G channel image", imageG);
        setPropertyValue< QVImage<uChar, 1> >("B channel image", imageB);
        setPropertyValue< QVImage<uChar, 3> >("RGB image", imageRGB);

        // If the camera is in real time mode, a single shot timer will do the grabbing job (this timer will
        // always be relaunched after each grab()). Otherwise, the QVVideoReaderBlock::iterate() will simply call
        // explicitly the grabFrame slot.
        if (realTime)
            QTimer::singleShot(0, this, SLOT(grabFrame()));  // Schedule first grabFrame()

        // Once opened, the block is ready to run (useful when reopening stopped cameras):
        unPause();

        // Trick to block too fast consumer blocks, if in real time:
        if (realTime)
            connectOrDisconnectLinkedBlocks(TRUE);

        emit opened();
        }
    else	// If something fails when opening, we reset using reset():
        reset();
}

void QVVideoReaderBlock::connectOrDisconnectLinkedBlocks(bool connect_disconnect)
    {
    QList<QVPropertyContainer*> list_linked_qvps = getDestinyContainers("RGB image");
    list_linked_qvps << getDestinyContainers("Y channel image");
    list_linked_qvps << getDestinyContainers("U channel image");
    list_linked_qvps << getDestinyContainers("V channel image");
    list_linked_qvps << getDestinyContainers("R channel image");
    list_linked_qvps << getDestinyContainers("G channel image");
    list_linked_qvps << getDestinyContainers("B channel image");
    QSet<QVPropertyContainer*> set_linked_qvps = list_linked_qvps.toSet();
    QVProcessingBlock *block;
    foreach (QVPropertyContainer *qvp, set_linked_qvps)
        if((block = dynamic_cast<QVProcessingBlock*>(qvp)) != NULL) {
            if(connect_disconnect)
                connect(block,SIGNAL(endIteration(uint,int)),this,SLOT(nothing()),Qt::BlockingQueuedConnection);
            else
                disconnect(block,SIGNAL(endIteration(uint,int)),this,SLOT(nothing()));
        }
    }

void QVVideoReaderBlock::reset()
    {
    // Disconnect consumer blocks, if in real time (trick for fast consumer blocks):
    if(realTime)
        connectOrDisconnectLinkedBlocks(FALSE);

    // Flush any possible timer event pending:
    flush_pending_images = TRUE;
    while(qApp->hasPendingEvents ()) qApp->processEvents();
    flush_pending_images = FALSE;

    // Close camera ...
    video_reader.close();

    // ... reset output properties (except images and RowsR/ColsR, that are left untouched), ...
    setPropertyValue<bool>("Opened",FALSE);
    setPropertyValue<int>("FPS",0);
    setPropertyValue<int>("Frames",0);
    setPropertyValue<int>("Pos",0);
    setPropertyValue<int>("Length",0);

    // ...and stop block:
    stop();

    emit closed();
    }


bool QVVideoReaderBlock::linkProperty(QVPropertyContainer *destinyContainer, QString destinyPropertyName)
    {
    // Asynchronous links for real time cameras, synchronous for non real time:
    LinkType linkType = getPropertyValue<bool>("RealTime") ? AsynchronousLink : SynchronousLink;

    // Link the destination image property, depending on the number of channels.
    if (destinyContainer->isType< QVImage<uChar, 3> >(destinyPropertyName))
        return QVProcessingBlock::linkProperty("RGB image", destinyContainer, destinyPropertyName, linkType);
    else if (destinyContainer->isType< QVImage<uChar, 1> >(destinyPropertyName))
        return QVProcessingBlock::linkProperty("Y channel image", destinyContainer, destinyPropertyName, linkType);
    else
        {
        qWarning() << "QVVideoReaderBlock::link(): error, can't link property " << qPrintable(destinyPropertyName) << ".";
        return false;
        }
    }

bool QVVideoReaderBlock::linkProperty(QVPropertyContainer *destinyContainer, QString destinyPropertyName1, QString destinyPropertyName2, QString destinyPropertyName3, bool YUV_RGB)
    {
    // Asynchronous links for real time cameras, synchronous for non real time:
    LinkType linkType = getPropertyValue<bool>("RealTime") ? AsynchronousLink : SynchronousLink;

    bool ok = TRUE;

    // Link the destination image properties (must be one channel each)
    if(YUV_RGB)
        {
        if (destinyContainer->isType< QVImage<uChar, 1> >(destinyPropertyName1))
            if(not QVProcessingBlock::linkProperty("R channel image", destinyContainer, destinyPropertyName1, linkType))
                {
                ok = FALSE;
                qWarning() << "QVVideoReaderBlock::linkProperty(): error, can't link R property " << qPrintable(destinyPropertyName1) ;
                }
        if (destinyContainer->isType< QVImage<uChar, 1> >(destinyPropertyName2))
            if(not QVProcessingBlock::linkProperty("G channel image", destinyContainer, destinyPropertyName2, linkType))
                {
                ok = FALSE;
                qWarning() << "QVVideoReaderBlock::linkProperty(): error, can't link G property " << qPrintable(destinyPropertyName2) ;
                }
        if (destinyContainer->isType< QVImage<uChar, 1> >(destinyPropertyName3))
            if(not QVProcessingBlock::linkProperty("B channel image", destinyContainer, destinyPropertyName3, linkType))
                {
                ok = FALSE;
                qWarning() << "QVVideoReaderBlock::linkProperty(): error, can't link B property " << qPrintable(destinyPropertyName3) ;
                }
        }
    else
        {
        if (destinyContainer->isType< QVImage<uChar, 1> >(destinyPropertyName1))
            if(not QVProcessingBlock::linkProperty("Y channel image", destinyContainer, destinyPropertyName1, linkType))
                {
                ok = FALSE;
                qWarning() << "QVVideoReaderBlock::linkProperty(): error, can't link Y property " << qPrintable(destinyPropertyName1) ;
                }
        if (destinyContainer->isType< QVImage<uChar, 1> >(destinyPropertyName2))
            if(not QVProcessingBlock::linkProperty("U channel image", destinyContainer, destinyPropertyName2, linkType))
                {
                ok = FALSE;
                qWarning() << "QVVideoReaderBlock::linkProperty(): error, can't link U property " << qPrintable(destinyPropertyName2) ;
                }
        if (destinyContainer->isType< QVImage<uChar, 1> >(destinyPropertyName3))
            if(not QVProcessingBlock::linkProperty("V channel image", destinyContainer, destinyPropertyName3, linkType))
                {
                ok = FALSE;
                qWarning() << "QVVideoReaderBlock::linkProperty(): error, can't link V property " << qPrintable(destinyPropertyName3) ;
                }
        }
        return ok;
    }

void QVVideoReaderBlock::grabFrame()
    {
    // Grab image.
    if(video_reader.grab())
        {
        if (isLinkedOutput("RGB image"))
            video_reader.getRGBImage(imageRGB);
        if (isLinkedOutput("Y channel image") and not isLinkedOutput("U channel image") and not isLinkedOutput("V channel image"))
            video_reader.getGrayImage(imageY);
        else if(isLinkedOutput("Y channel image") and (isLinkedOutput("U channel image") or isLinkedOutput("V channel image")))
            video_reader.getYUVImage(imageY,imageU,imageV);
        if (isLinkedOutput("R channel image") or isLinkedOutput("G channel image") or isLinkedOutput("B channel image"))
            video_reader.getRGBImage(imageR,imageG,imageB);
        setPropertyValue<int>("Frames",getPropertyValue<int>("Frames")+1);
        setPropertyValue<int>("Pos",video_reader.getPos());
        // Needed here because mplayer does not know the length of the video until it has played a few frames:
        setPropertyValue<int>("Length",video_reader.getLength());

        // Compute FPS:
        static QTime t;
            if(getPropertyValue<int>("Frames")==1)
            t.start();
        else
            {
            int ms = t.elapsed();
            if(ms>0) setPropertyValue<int>("FPS",1000/ms);
            t.restart();
            }

        setPropertyValue<int>("ColsR",video_reader.getCols());
        setPropertyValue<int>("RowsR",video_reader.getRows());

        if(realTime) writeOutputProperties();

        emit grabbed();

        // Post following timer event to schedule next grabbing (except if we are flushing images out for closing).
        if(realTime and not flush_pending_images)
            QTimer::singleShot(0, this, SLOT(grabFrame()));
        }
    else
        reset();
    }

void QVVideoReaderBlock::iterate()
    {
    // Try opening camera if first iteration (performed here, instead of the constructor, to assure
    // that open() is executed always in this thread.
    if(getIteration()==0)
        tryOpeningCam();

    // Needed for not try to grab from closed (stopped) cameras:
    if(isStopped()) return;

    // If the camera is in real time mode, the timer should have called the slot for us, so we do not have to do it
    // explicitly. Otherwise, we call grabFrame();
    if (not realTime)
        grabFrame();

    if (isLinkedOutput("RGB image"))
        setPropertyValue< QVImage<uChar,3> >("RGB image", imageRGB);
    if (isLinkedOutput("R channel image"))
        setPropertyValue< QVImage<uChar,1> >("R channel image", imageR);
    if (isLinkedOutput("G channel image"))
        setPropertyValue< QVImage<uChar,1> >("G channel image", imageG);
    if (isLinkedOutput("B channel image"))
        setPropertyValue< QVImage<uChar,1> >("B channel image", imageB);
    if (isLinkedOutput("Y channel image"))
        setPropertyValue< QVImage<uChar,1> >("Y channel image", imageY);
    if (isLinkedOutput("U channel image"))
        setPropertyValue< QVImage<uChar,1> >("U channel image", imageU);
    if (isLinkedOutput("V channel image"))
        setPropertyValue< QVImage<uChar,1> >("V channel image", imageV);

    }

void QVVideoReaderBlock::reopen()
    {
    // Do not try to reopen again if in the middle of a reopening process (could happen if the user presses the
    // "Reopen" camera widget button several times very quickly). This condition avoids it:
    if(flush_pending_images) return;

    // When reopening, we must reset the camera block ...
    reset();
    // ... and open the camera again using the new input properties.
    readInputProperties();
    tryOpeningCam();
    }
