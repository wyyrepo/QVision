/*
 *	Copyright (C) 2011, 2012. PARP Research Group.
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
@file
@ingroup GPUKLTFLOWExamplePrograms
@brief A simple program to test the wrapping functions for the feature tracking on the GPU.

This application performs point tracking on an input video sequence using the GPU implementation
of the gain-adaptive KLT feature tracker provided by the <a href="http://www.inf.ethz.ch/personal/chzach/opensource.html">GPU-KLT+FLOW</a> software.

@section Usage
Once compiled, the program should be used with this command line:
@code
	./demoSparse --URL=<path or url to video>
@endcode

@param URL Video source identifier. See section @ref QVMPlayerURLFormat for further info about its format.
@author PARP Research Group. University of Murcia, Spain.
*/

#include <GL/glew.h>

#include<QVApplication>
#include<QVDefaultGUI>
#include<QVVideoReaderBlock>
#include<QVImageCanvas>
#include<QVProcessingBlock>
#include<QVImage>
#include<qvipp.h>

#include <qvgpukltflow.h>
#include <QVKLTFeatureTracking>

#ifdef Q_WS_X11
  #include <X11/Xlib.h> // For XInitThreads function (called in main())
#endif

// Needed to treat new types as QVision properties:
typedef QHash< int, QVKLTFeatureTracking> TrackingHash;
Q_DECLARE_METATYPE(TrackingHash);
//typedef QHash<int,QVKLTTrackerFeature> FeatureHash;
//Q_DECLARE_METATYPE(FeatureHash);

// Canvas to draw left and right images, and matchings:
/*class MatchingCanvas: public QVImageCanvas {
public:
    MatchingCanvas(const QString name=QString(),QWidget *parent=0) : QVImageCanvas(name,parent) {
        addProperty<QHash<int,QVKLTTrackerFeature> >("featuresInput", inputFlag);
        addProperty<QHash<int,QVKLTTrackerFeature> >("featuresKeyframe", inputFlag);
    };
    QColor hashColor(float value) {
        return( QColor( (int) (123456*value)%255,
                        (int) (23456*value)%255,
                        (int) (3456*value)%255) );
    }
    void custom_viewer() {
        QHash<int,QVKLTTrackerFeature>
            featuresInput = getPropertyValue<QHash<int,QVKLTTrackerFeature> >("featuresInput"),
            featuresKeyframe = getPropertyValue<QHash<int,QVKLTTrackerFeature> >("featuresKeyframe");
        getQVPainter()->setBackgroundMode(Qt::OpaqueMode);

        int width = this->getSize().width()/2;
        getQVPainter()->setPen(Qt::red);
        getQVPainter()->drawText(25,25,QString("%1 matchings").arg(featuresInput.size()));
        QHash<int, QVKLTTrackerFeature>::iterator i;
        for(i = featuresInput.begin(); i != featuresInput.end(); i++) {
            QVKLTTrackerFeature ftInput = i.value();
            QVKLTTrackerFeature ftKey = featuresKeyframe.value(i.key());
            getQVPainter()->setPen(hashColor(ftKey.getPosition().x()/width));
            getQVPainter()->drawLine(ftKey.getPosition(),ftInput.getPosition()+QPointF(width,0));
        }
    };
};*/

class MyQVImageCanvas: public QVImageCanvas {
  public:
    MyQVImageCanvas(const QString name=QString(),QWidget *parent=0) : QVImageCanvas(name,parent) {
        addProperty<TrackingHash>("Trackings", inputFlag);
    };

    // Draw tracked features:
    void custom_viewer() {
        QHash<int, QVKLTFeatureTracking>  trackings = getPropertyValue<TrackingHash>("Trackings");
        getQVPainter()->setBackgroundMode(Qt::OpaqueMode);
        foreach(QVKLTFeatureTracking ft, trackings) {
            QList<QVKLTTrackerFeature> tracking = ft.getFeatureList();
            // Draw current position:
            if(tracking.size()==1) // New feature
                getQVPainter()->setPen(Qt::red);
            else
                getQVPainter()->setPen(Qt::green); // Tracked feature
            getQVPainter()->drawEllipse(tracking.last().getPosition(), 2.0, 2.0);
            // Draw trajectory:
            getQVPainter()->setPen(Qt::blue);
            for(int j=0; j < tracking.size()-1; j++) {
                getQVPainter()->drawLine(tracking[j].getPosition(), tracking[j+1].getPosition());
            }
        }
        getQVPainter()->drawText(25,25,QString("%1 features").arg(trackings.size()));
    };
};

class MyProcessingBlock : public QVProcessingBlock {
  private:
    QVKLTTracker *tracker,*matchTracker;
    QVTrackingManager* trackingManager;
    QHash<int,QVKLTTrackerFeature> features;
    QVImage<uChar,1> imageIn,keyImage;
public:
    MyProcessingBlock(QString name): QVProcessingBlock(name) {
        tracker = 0;
        matchTracker = 0;
        trackingManager = 0;
        addProperty<QVImage<uChar,1> >("imageIn",inputFlag|outputFlag);
        addProperty<int>("nTrackedFrames",inputFlag,10,"Number of frames before redetection",1,30);
        addProperty<bool>("trackWithGain",inputFlag,true,"Wether track using gain or not");
        addProperty<int>("featuresWidth",inputFlag,64,"Features width",8,128);
        addProperty<int>("featuresHeight",inputFlag,64,"Features height",8,128);
        addProperty<int>("nIterations",inputFlag,10,"number of KLT iterations",10,30);
        addProperty<int>("nLevels",inputFlag,4,"Number of levels of pyramid",1,4);
        addProperty<int>("levelSkip",inputFlag,1,"Levels of pyramid to skip",1,3);
        addProperty<int>("windowWidth",inputFlag,7,"Window width used by KLT",1,21);
        addProperty<float>("trackBorderMargin",inputFlag,20.0,"Border margin for tracking features",10.0,50.0);
        addProperty<float>("detectBorderMargin",inputFlag,20.0,"Border margin for detecting features",1.0,100.0);
        addProperty<float>("convergenceThreshold",inputFlag,0.1,"Convergence threshold for KLT",0.01,0.5);
        addProperty<float>("SSD_Threshold",inputFlag,5000.0,"SSD threshold for KLT",1000.0,10000.0);
        addProperty<int>("minDistance",inputFlag,7,"Minimum distance between features",3,25);
        addProperty<float>("minCornerness",inputFlag,50.0,"Minimum value for cornerness",20.0,100.0);
        addProperty<QHash<int,QVKLTFeatureTracking> > ("Trackings",outputFlag);

        addProperty<QVImage<uChar,1> >("Matching images",outputFlag);
		addProperty< QList<QPointFMatching> >("Matching correspondences", outputFlag);		

		// ------------------------
        //addProperty<QHash<int,QVKLTTrackerFeature> >("featuresInput",outputFlag);
        //addProperty<QHash<int,QVKLTTrackerFeature> >("featuresKeyframe",outputFlag);
        addTrigger("Follow from key frame");
    };

    void processTrigger(QString name) {
        if(name == QString("Follow from key frame")) {
            keyImage = imageIn;
        }
    }

    // Function to reset tracker when any parameter changed:
    void ResetTracker(int width, int height, bool trackWithGain, int featuresWidth, int featuresHeight,
                      int nIterations, int nLevels, int levelSkip,int windowWidth,
                      float trackBorderMargin, float detectBorderMargin, float convergenceThreshold,
                      float SSD_Threshold, int minDistance, float minCornerness) {
        // If it is not the first time, delete former tracker, and then create new one:
        if(tracker != 0) {
            delete tracker;
        }
        tracker = new QVKLTTracker(width, height, trackWithGain, featuresWidth, featuresHeight,
                     nIterations, nLevels, levelSkip, windowWidth,
                     trackBorderMargin, detectBorderMargin, convergenceThreshold,
                     SSD_Threshold, minDistance, minCornerness);
        if(matchTracker != 0) {
            delete matchTracker;
        }
        matchTracker = new QVKLTTracker(width, height, trackWithGain, featuresWidth, featuresHeight,
                     nIterations, nLevels, levelSkip, windowWidth,
                     trackBorderMargin, detectBorderMargin, convergenceThreshold,
                     SSD_Threshold, minDistance, minCornerness);

        // Same for tracking manager:
        if (trackingManager != 0){
            delete trackingManager;
        }
        trackingManager = new QVTrackingManager(true);
    }

    void iterate() {
        bool reset = false;

        // Initialize only in first iteration (must be done here in the processing block thread):
        if(getIteration() == 0)
			{
            InitGLEWCg();
            reset = true;
			}

        // Read input properties:va
        static bool		trackWithGain;
        static int		width = 0, height = 0, featuresWidth = 0,
						featuresHeight = 0, nIterations = 0, nLevels = 0,
						levelSkip = 0, windowWidth = 0, minDistance = 0;
        static float	trackBorderMargin = 0.0, detectBorderMargin = 0.0,
						convergenceThreshold = 0.0, SSD_Threshold = 0.0,
						minCornerness = 0.0;

        int nTrackedFrames = getPropertyValue<float>("nTrackedFrames");
        imageIn = getPropertyValue<QVImage<uChar,1> >("imageIn");

        if (	(width != imageIn.getCols()) or (height != imageIn.getRows())				or
				(trackWithGain != getPropertyValue<bool>("trackWithGain"))					or
				(featuresWidth != getPropertyValue<int>("featuresWidth"))					or
				(featuresHeight != getPropertyValue<int>("featuresHeight"))					or
				(nIterations != getPropertyValue<int>("nIterations"))						or
				(nLevels != getPropertyValue<int>("nLevels"))								or
				(levelSkip != getPropertyValue<int>("levelSkip"))							or
				(windowWidth != getPropertyValue<int>("windowWidth"))						or
				(trackBorderMargin != getPropertyValue<float>("trackBorderMargin"))			or
				(detectBorderMargin != getPropertyValue<float>("detectBorderMargin"))		or
				(convergenceThreshold != getPropertyValue<float>("convergenceThreshold"))	or
				(SSD_Threshold != getPropertyValue<float>("SSD_Threshold"))					or
				(minDistance != getPropertyValue<int>("minDistance"))						or
				(minCornerness != getPropertyValue<float>("minCornerness"))					)
			{
            width = imageIn.getCols();
            height = imageIn.getRows();
			trackWithGain = getPropertyValue<bool>("trackWithGain");
			featuresWidth = getPropertyValue<int>("featuresWidth");
			featuresHeight = getPropertyValue<int>("featuresHeight");
			nIterations = getPropertyValue<int>("nIterations");
			nLevels = getPropertyValue<int>("nLevels");
			levelSkip = getPropertyValue<int>("levelSkip");
			windowWidth = getPropertyValue<int>("windowWidth");
			trackBorderMargin = getPropertyValue<float>("trackBorderMargin");
			detectBorderMargin = getPropertyValue<float>("detectBorderMargin");
			convergenceThreshold = getPropertyValue<float>("convergenceThreshold");
			SSD_Threshold = getPropertyValue<float>("SSD_Threshold");
			minDistance = getPropertyValue<int>("minDistance");
			minCornerness = getPropertyValue<float>("minCornerness");
			reset = true;
			}

		/*
        if(width != imageIn.getCols())
			{
            width = imageIn.getCols();
            reset = true;
	        }
        if(height != imageIn.getRows())
			{
            height = imageIn.getRows();
            reset = true;
	        }
        if(trackWithGain != getPropertyValue<bool>("trackWithGain")) {
            trackWithGain = getPropertyValue<bool>("trackWithGain");
            reset = true;
        }
        if(featuresWidth != getPropertyValue<int>("featuresWidth")) {
            featuresWidth = getPropertyValue<int>("featuresWidth");
            reset = true;
        }
        if(featuresHeight != getPropertyValue<int>("featuresHeight")) {
            featuresHeight = getPropertyValue<int>("featuresHeight");
            reset = true;
        }
        if(nIterations != getPropertyValue<int>("nIterations")) {
            nIterations = getPropertyValue<int>("nIterations");
            reset = true;
        }
        if(nLevels != getPropertyValue<int>("nLevels")) {
            nLevels = getPropertyValue<int>("nLevels");
            reset = true;
        }
        if(levelSkip != getPropertyValue<int>("levelSkip")) {
            levelSkip = getPropertyValue<int>("levelSkip");
            reset = true;
        }
        if(windowWidth != getPropertyValue<int>("windowWidth")) {
            windowWidth = getPropertyValue<int>("windowWidth");
            reset = true;
        }
        if(trackBorderMargin != getPropertyValue<float>("trackBorderMargin")) {
            trackBorderMargin = getPropertyValue<float>("trackBorderMargin");
            reset = true;
        }
        if(detectBorderMargin != getPropertyValue<float>("detectBorderMargin")) {
            detectBorderMargin = getPropertyValue<float>("detectBorderMargin");
            reset = true;
        }
        if(convergenceThreshold != getPropertyValue<float>("convergenceThreshold")) {
            convergenceThreshold = getPropertyValue<float>("convergenceThreshold");
            reset = true;
        }
        if(SSD_Threshold != getPropertyValue<float>("SSD_Threshold")) {
            SSD_Threshold = getPropertyValue<float>("SSD_Threshold");
            reset = true;
        }
        if(minDistance != getPropertyValue<int>("minDistance")) {
            minDistance = getPropertyValue<int>("minDistance");
            reset = true;
        }
        if(minCornerness != getPropertyValue<float>("minCornerness")) {
            minCornerness = getPropertyValue<float>("minCornerness");
            reset = true;
        }*/
        timeFlag("Read properties");

        // Reset tracker if needed (some configuration parameter of the tracker changed):
        if(reset)
			{
            ResetTracker(width, height, trackWithGain, featuresWidth, featuresHeight,
                         nIterations, nLevels, levelSkip, windowWidth,
                         trackBorderMargin, detectBorderMargin, convergenceThreshold,
                         SSD_Threshold, minDistance, minCornerness);
            features.clear();
            tracker->detect(imageIn, features);
	        }

        timeFlag("Reset tracker");

        // Otherwise, track features (redetecting new ones every nTrackedFrames):
        if(not reset)
			{
            if (getIteration() % nTrackedFrames == 0)
				//{
                // Redetect every nTrackedFrames frames:
                tracker->redetect(imageIn, features);
	            //}
			else
				//{
		        // Simply track set of features in rest of frames:
		        tracker->track(imageIn, features);
		        //}
		    }
        timeFlag("GPU tracking");

        // Update tracking manager with features:
        trackingManager->updateTrackings(&features);
        timeFlag("Tracking manager update");

        // Publish results:
        setPropertyValue<TrackingHash>("Trackings", trackingManager->getTrackings());
        timeFlag("Write properties");

        if(keyImage.getSize() == imageIn.getSize())
			{
            QVImage<uChar,1> imagesLeftAndRight;
            imagesLeftAndRight = QVImage<uChar,1>(imageIn.getCols()*2,imageIn.getRows());
            Copy(keyImage,imagesLeftAndRight,QPoint(0, 0));
            Copy(imageIn,imagesLeftAndRight,QPoint(imageIn.getCols(),0));
            imagesLeftAndRight.resetROI();

            QHash<int,QVKLTTrackerFeature> featuresKeyframe, featuresInput;
            matchTracker->detect(keyImage, featuresKeyframe);
            featuresInput = featuresKeyframe;
            matchTracker->track(imageIn, featuresInput);

			// -----------------------
			QList<QPointFMatching> correspondences;
			const QPointF offset(keyImage.getCols(), 0);

		    for(QHash<int, QVKLTTrackerFeature>::iterator i = featuresInput.begin(); i != featuresInput.end(); i++)
				{
		        QVKLTTrackerFeature ftInput = i.value();
		        QVKLTTrackerFeature ftKey = featuresKeyframe.value(i.key());
				correspondences << QPointFMatching(ftKey.getPosition(), ftInput.getPosition()+offset);
			    }
			// -----------------------

			setPropertyValue< QList<QPointFMatching> >("Matching correspondences", correspondences);
            setPropertyValue<QVImage<uChar,1> >("Matching images", imagesLeftAndRight);
            //setPropertyValue<QHash<int,QVKLTTrackerFeature> >("featuresKeyframe", featuresKeyframe);
            //setPropertyValue<QHash<int,QVKLTTrackerFeature> >("featuresInput", featuresInput);
			}
    }
};

int main( int argc, char** argv)
{

initShadersEnvironment();

#ifdef Q_WS_X11
    // Needed to make X11 calls thread-safe.
    // (Explanation in http://doc.qt.nokia.com/qq/qq06-glimpsing.html#writingmultithreadedglapplications)
    XInitThreads();
#endif

    QVApplication app(argc,argv);
    QVDefaultGUI gui;
    QVVideoReaderBlock camera("Camera");

    MyProcessingBlock processingBlock("My processing block");
    camera.linkProperty(&processingBlock,"imageIn");

    MyQVImageCanvas imageCanvas("Canvas");
    processingBlock.linkProperty("imageIn",&imageCanvas);
    processingBlock.linkProperty("Trackings", &imageCanvas, "Trackings");

	QVImageCanvas referenceFrame("Matchings");
	processingBlock.linkProperty("Matching images", referenceFrame);
	processingBlock.linkProperty("Matching correspondences", referenceFrame);
	referenceFrame.setRadius("Matching correspondences", 2);

    return app.exec();
}
