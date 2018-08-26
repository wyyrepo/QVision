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

/*!
@file ltmser.cpp
@ingroup ExamplePrograms
@brief Obtains the MSER (linear time MSER) from input video frames

This program obtains MSER regions from input video frames, using the linear time MSER algorithm by Nister and Stewanius ("Linear Time Maximally Stable Extremal Regions", ECCV 2008), as implemented by Eduardo Iniesta Soto (einiesta@ditec.um.es) and adapted for the QVision library.

@section Usage of the program
Once QVision has been correctly installed in your system, compile using the <i>qmake</i> and <i>make</i> tools:
@code # qmake; make @endcode
Execute the application with the following line:
@code ./ltmser --URL=<source video identifier string> --RealTime=true @endcode
For example:
@code ./ltmser --URL=/home/user/video.avi --RealTime=true @endcode

<p>The application shows on an image canvas the MSER features detected at the most recent input frame from the video sequence:</p>
@image html LTMSER-penguin.png
@image latex LTMSER-penguin.png

See section @ref QVMPlayerURLFormat for further info about the format and types of source video identifier strings.
*/

#ifndef DOXYGEN_IGNORE_THIS

#include <QVVideoReaderBlock>
#include <QVDefaultGUI>
#include <QVImageCanvas>
#include <QVPolyline>

#include <qvltmser/qvltmser.h>
#include <qvip.h>
#include <qvipp.h>

Q_DECLARE_METATYPE(QList<QVMSER>);

class MyImageCanvas : public QVImageCanvas {
    public:
        MyImageCanvas(QString name) : QVImageCanvas(name) {
            addProperty<QList<QVMSER> >("seeds", inputFlag);
            addProperty<bool>("draw_seeds_data", inputFlag);
        } ;
        void custom_viewer(){
            QList<QVMSER> msers = getPropertyValue< QList<QVMSER> >("seeds");
            bool draw_seeds_data = getPropertyValue<bool>("draw_seeds_data");

            getQVPainter()->setPen(Qt::yellow);
            QVMSER mser;
            foreach(mser,msers) {
                //QPointF point(seed.seedx+0.5,seed.seedy+0.5);
                QPointF point = mser.seed + QPointF(0.5,0.5);
                getQVPainter()->drawLine(point+QPointF(-2,0),point+QPointF(+2,0));
                getQVPainter()->drawLine(point+QPointF(0,-2),point+QPointF(0,+2));
                if(draw_seeds_data)
                    getQVPainter()->drawTextUnscaled(
                          point,
                          QString("th=%1 a=%2 m=%3").arg(mser.threshold).arg(mser.area).arg(mser.merit)
                    );
            }
        };
};

class QVLTMSERWorker: public QVProcessingBlock {
    public:
        QVLTMSERWorker(QString name): QVProcessingBlock(name) {
            // Parameters for MSER:
            addProperty<int>("minArea", inputFlag, 20, "Minimum area for MSER region", 1, 1000);
            addProperty<int>("maxArea", inputFlag, 100000, "Maximal area for MSER region", 1, 300000);
            addProperty<int>("delta", inputFlag, 15, "Delta value", 1, 75);
            addProperty<float>("delta_threshold", inputFlag, 0.3, "Delta threshold", 0.0, 1.0);
            addProperty<int>("downscale", inputFlag, 1, "Downscaling factor", 1, 4);
            addProperty<int>("MSER+(1)_MSER-(2)_Both(3)", inputFlag, 1,
                             "Countour detection: MSER+ (1), MSER- (2), both (3)", 1, 3);
            // Parameter for previous median filter:
            addProperty<int>("filter_median_mask", inputFlag, 1, "Mask radius for Median Filter", 0, 5);
            // If seeds data should be drawn:
            addProperty<bool>("draw_seeds_data", inputFlag|outputFlag);

            // Input image and output contours, values, etc.:
            addProperty< QVImage< uChar > >("input_image", inputFlag|outputFlag);
            addProperty< QList<QVMSER> >("seeds", outputFlag);
            addProperty< QList<QVPolyline> >("output_contours", outputFlag);
        }
    protected:
        void iterate() {
            // 0. Read input image and parameters:
            QVImage<uChar> input_image = getPropertyValue< QVImage<uChar> >("input_image");
            const uInt minArea = getPropertyValue<int>("minArea"),
                       maxArea = getPropertyValue<int>("maxArea"),
                       delta = getPropertyValue<int>("delta"),
                       MSERType = getPropertyValue<int>("MSER+(1)_MSER-(2)_Both(3)"),
                       medianFilterMask = getPropertyValue<int>("filter_median_mask");
            const float delta_threshold = getPropertyValue<float>("delta_threshold");
            const int downscale = getPropertyValue<int>("downscale");

            timeFlag("Read input parameters");

            // 1. (Possible) previous median filter:
            QVImage< uChar > input_image_preprocessed = input_image, not_input_image_preprocessed;
            if(medianFilterMask > 0) {
                FilterMedian(input_image, input_image_preprocessed,QSize(2*medianFilterMask+1, 2*medianFilterMask+1),
                             QPoint(0,0), QPoint(medianFilterMask,medianFilterMask));
                input_image_preprocessed.resetROI();
            }
            timeFlag("Median filter");

            // 2. Compute MSER regions:
            QList<QVPolyline> output_contours,output_contours2;
            QList<QVMSER> seed_list,seed_list2;
            switch (MSERType) {
                case 1: // MSER+
                    seed_list = getLTMSER(input_image_preprocessed, minArea, maxArea, delta,
                                          delta_threshold,downscale);
                    timeFlag("MSER seeds");
                    output_contours = getLTMSERContours(input_image_preprocessed,seed_list);
                    timeFlag("MSER contours");
                    // You could have also obtained directly the output contours, if you were not
                    // interested in the seeds data:
                    // output_contours = getLTMSER(input_image_preprocessed, minArea, maxArea,
                    //                             delta, delta_threshold,downscale);
                    break;
                case 2: // MSER-
                    Not(input_image_preprocessed,not_input_image_preprocessed);
                    seed_list = getLTMSER(not_input_image_preprocessed, minArea, maxArea, delta,
                                          delta_threshold,downscale);
                    timeFlag("MSER seeds");
                    output_contours = getLTMSERContours(not_input_image_preprocessed,seed_list);
                    timeFlag("MSER contours");
                    break;
                case 3: // MSER+ y MSER-
                    seed_list = getLTMSER(input_image_preprocessed, minArea, maxArea,
                                          delta, delta_threshold,downscale);
                    Not(input_image_preprocessed,not_input_image_preprocessed);
                    seed_list2 = getLTMSER(not_input_image_preprocessed, minArea, maxArea,
                                               delta, delta_threshold,downscale);
                    timeFlag("MSER seeds");
                    output_contours = getLTMSERContours(input_image_preprocessed,seed_list);
                    output_contours2 = getLTMSERContours(not_input_image_preprocessed,seed_list2);
                    timeFlag("MSER contours");
                    seed_list += seed_list2;
                    output_contours += output_contours2;
                    break;
            }

            // 3. Publish results:
            //Set(0,input_image_preprocessed);
            setPropertyValue< QVImage<uchar> >("input_image",input_image_preprocessed);
            setPropertyValue< QList<QVMSER> >("seeds",seed_list);
            setPropertyValue< QList< QVPolyline> >("output_contours",output_contours);
            timeFlag("Write output properties");
        }
};

int main(int argc, char *argv[])
{
    ippSetNumThreads(1);
    QVApplication app(argc, argv,
                      "Obtains MSER regions (using linear time MSER algorithm) from input video frames.");
    QVLTMSERWorker theQVLTMSERWorker("LTMSER Worker");
    QVVideoReaderBlock camera("Video input");
    camera.linkProperty(&theQVLTMSERWorker,"input_image");
    QVDefaultGUI interface;
    MyImageCanvas imageCanvas("LT-MSER contours on image");
    theQVLTMSERWorker.linkProperty("input_image", imageCanvas);
    theQVLTMSERWorker.linkProperty("output_contours", imageCanvas);
    theQVLTMSERWorker.linkProperty(imageCanvas,"seeds");
    theQVLTMSERWorker.linkProperty(imageCanvas,"draw_seeds_data");
    return app.exec();
}

#endif
