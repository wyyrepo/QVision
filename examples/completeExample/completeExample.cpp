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
@file
@ingroup ExamplePrograms
@brief Shows the use of some of the most useful classes in the QVision framework.

@section Usage
Simply compile, execute the binary, and interact freely with the application GUI:
\code
        ./completeExample
\endcode

@author PARP Research Group. University of Murcia, Spain.
*/

#ifndef DOXYGEN_IGNORE_THIS // Do not generate any doxygen documentation from here on.

/************************************** INCLUDE SECTION **************************************/

// Main QVApplication class (always needed):
#include <QVApplication>

// Video source reader block (virtually always needed):
#include <QVVideoReaderBlock>

// Main GUI, image  and function plot windows:
#include <QVDefaultGUI>
#include <QVImageCanvas>
#include <QVFunctionPlot>

// Image processing and matrix functionality:
#include <qvipp.h>
#include <qvip.h>
#include <qvmatrixalgebra.h>

/************************************** CUSTOMIZED WINDOWS SECTION **************************************/

// First, you need to declare new types that are going to be used as properties:
typedef QMap<sFloat,QPointF> TMapFloatPoints;
Q_DECLARE_METATYPE(TMapFloatPoints);
typedef QList<QLineF> TListLines;
Q_DECLARE_METATYPE(TListLines);

// Two new customized QVImageCanvas subclasses: one to draw float corner response image, with corresponding maximum
// response points, and another to draw Canny image, with regression lines in selected squares:
class ResponseImageCanvas : public QVImageCanvas {
    public:
        ResponseImageCanvas(QString name) : QVImageCanvas(name) {
            // Add extra properties to draw in canvas:
            addProperty<QMap<sFloat,QPointF> >("Max points", inputFlag);
        } ;
        void custom_viewer() {
            // Read properties to draw in canvas:
            QMap<sFloat,QPointF> maxPoints = getPropertyValue< QMap<sFloat,QPointF> >("Max points");

            // Use getQVPainter() and standard QT QPainter class methods to draw in canvas:
            getQVPainter()->setPen(Qt::yellow);
            QMap<sFloat, QPointF>::iterator i = maxPoints.begin();
            int order = 1;
            while (i != maxPoints.end()) {
                QPointF point = i.value() + QPointF(0.5,0.5);
                sFloat response = i.key();
                getQVPainter()->drawLine(point+QPointF(-2,0),point+QPointF(+2,0));
                getQVPainter()->drawLine(point+QPointF(0,-2),point+QPointF(0,+2));
                getQVPainter()->drawTextUnscaled(point, QString("%1(%2)").arg(order).arg(-response));
                i++;
                order++;
            }
        };
};

class CannyImageCanvas : public QVImageCanvas {
    public:
        CannyImageCanvas(QString name) : QVImageCanvas(name) {
            addProperty<int>("lr", inputFlag);
            addProperty< QList<QLineF> >("Regression lines", inputFlag);
        } ;
        void custom_viewer(){
            QVPolyline poly = getPropertyValue<QVPolyline>("poly select");
            QList<QLineF> regLines = getPropertyValue< QList<QLineF> >("Regression lines");
            const int lr = getPropertyValue<int>("lr");
            getQVPainter()->setPen(Qt::green);
            foreach(QPoint point,poly)
                getQVPainter()->drawRect(point.x()-lr,point.y()-lr,2*lr+1,2*lr+1);
            getQVPainter()->setPen(Qt::red);
            foreach(QLineF line,regLines)
                getQVPainter()->drawLine(line.translated(0.5,0.5));
        };
};

/************************************** AUXILIARY FUNCTIONS **************************************/

// The following functions illustrate use of main data classes (QVImage, QVMatrix, QVVector, ...) and functions
// (Intel IPP image processing functions, matrix algebra, ...). Native QT classes (like QMap, QList, QPoint, ...) are
// also extensively used:

QMap<sFloat,QPointF>  findMaximalPoints(const QVImage<sFloat> &image, const double threshold, const int windowRadius)
{
    QVImage<sFloat> maxImage;
    FilterMax(image, maxImage,
              QSize(2*windowRadius+1,2*windowRadius+1), // Mask size
              QPoint(0,0), // Anchor
              image.getROI().topLeft() + QPoint(windowRadius, windowRadius) // Destination
              );

    const QRect	ROI = maxImage.getROI();
    const int maxStep = maxImage.getStep() / sizeof(sFloat),
              imageStep = image.getStep() / sizeof(sFloat);

    QMap<sFloat, QPointF> sortedPoints;

    sFloat *actualPtr = (sFloat *) image.getReadData() + (imageStep + 1) * windowRadius;
    sFloat *maxPtr = (sFloat *) maxImage.getReadData() + (maxStep + 1) * windowRadius;

    for(int j = 0; j < ROI.height(); j++, actualPtr += imageStep, maxPtr += maxStep)
        for(int i = 0; i < ROI.width(); i++)
            if ( (actualPtr[i] >= threshold) and (maxPtr[i] == actualPtr[i]) )
                // We store negative response (QMap sorted in ascending order):
                sortedPoints.insertMulti(-actualPtr[i], QPointF(i+ROI.x(), j+ROI.y()));

    return sortedPoints;
}

QVImage<uChar> getCannyImage(const QVImage<uChar> imageGray, QRect CannyROI, const double thrLow, const double thrHigh)
{
    uInt cols = imageGray.getCols(), rows = imageGray.getRows();
    QVImage<sFloat> imageFloat(imageGray),dX(cols,rows), dY(cols,rows), dXNeg(cols,rows);
    QVImage<uChar> imageCanny(cols,rows), buffer;

    QVImage<uChar> imageDest(imageGray);
    imageFloat.setROI(CannyROI);
    imageCanny.setROI(CannyROI);
    FilterSobelHorizMask(imageFloat, dY, ippMskSize3x3);
    FilterSobelVertMask(imageFloat, dX, ippMskSize3x3);
    MulC(dX, -1, dXNeg);
    CannyGetSize(imageCanny, buffer);
    Canny(dXNeg, dY, imageCanny, qMin(thrLow,thrHigh) /* IPP Canny fails if thrLow > thrHigh */, thrHigh, buffer);
    Copy(imageCanny, imageDest, QPoint(CannyROI.x(),CannyROI.y()));
    imageDest.resetROI();

    return imageDest;
}

QList<QLineF> getRegressionLines(const QVImage<uChar> &imageCanny, const QRect &CannyROI,
                                 const QVPolyline &CannySelPoints, int lr)
{
    QList<QLineF> regLines;
    for(int k=0;k<CannySelPoints.size();k++) {
        QPointF mean(0,0);
        QList<QPointF> listPoints;
        QPointF point = CannySelPoints[k];
        for(int j=point.y()-lr;j<=point.y()+lr;j++)
            for(int i=point.x()-lr;i<=point.x()+lr;i++)
                if(CannyROI.contains(i,j))
                    if(imageCanny(i,j) == 255) {
                        listPoints.append(QPointF(i,j));
                        mean += QPointF(i,j);
                    }
        const int n = listPoints.size();
        if(n >= 2) { // Two points minimum to estimate regression line.
            mean /= n;
            QVMatrix M(n,2); // n x 2 matrix;
            for(int k=0;k<n;k++) {
                M(k,0) = listPoints[k].x() - mean.x();
                M(k,1) = listPoints[k].y() - mean.y();
            }
            QVMatrix covMat = M.transpose()*M / n, Q;
            QVVector lambda;
            eigenDecomposition(covMat,lambda,Q);
            QVVector mainEigenvector = Q.getCol(0);
            QPointF pointEV(mainEigenvector(0),mainEigenvector(1));
            regLines.append(QLineF(mean+lr*pointEV,mean-lr*pointEV));
        }
    }
    return regLines;
}





/************************************** PROCESSING BLOCK(S) **************************************/

// Our customized processing blocks inherit form QVProcessingBlock class. If we are not interested in multithreading,
// we will normally use just one processing block:

class MyProcessingBlock: public QVProcessingBlock {
    private:
        QVIndexedStringList filterList; // To select from list of strings with automatically generated combobox in GUI.

    public:
        MyProcessingBlock(QString name = QString()): QVProcessingBlock(name) { // Constructor
            // Add input parameters (bools, ints, doubles, ...). For all of them, corresponding GUI widgets and
            // read from command lines are automatically included:
            addProperty<bool>("box", inputFlag, false, "Apply box filter");
            addProperty<int>("boxrows", inputFlag, 3, "Row box size", 1, 5);
            addProperty<int>("boxcols", inputFlag, 3, "Col box size", 1, 5);
            addProperty<double>("thhi", inputFlag, 150, "High threshold for Canny operator", 50, 1000);
            addProperty<double>("thlo", inputFlag, 50, "Low threshold for Canny operator", 10, 500);
            addProperty<double>("thMax", inputFlag, 50, "Max threshold for Hessian/Harris", 1.0, 255.0);
            addProperty<int>("lr", inputFlag|outputFlag, 5, "Radius for Canny regression lines", 2, 20);

            // Also comboboxes automatically generated in GUI from lists  of strings (QVIndexedStringList properties):
            filterList.append("None");
            filterList.append("Hessian");
            filterList.append("Harris");
            // firstFilter.append("...");
            addProperty<QVIndexedStringList>("Filter", inputFlag, filterList, "Apply corner response filter");

            // ROI rectangle and list of points to be linked as input from corresponding image window:
            addProperty<QRect>("CannyROI", inputFlag);
            addProperty<QVPolyline>("CannySelPoints", inputFlag);

            // One Input RGB image (3 channels), and two (one channel) output images (one of bytes, other of floats):
            addProperty< QVImage<uChar,3> >("Input RGB image", inputFlag|outputFlag);
            addProperty< QVImage<uChar,1> >("Output image byte", outputFlag);
            addProperty< QVImage<sFloat,1> >("Output image float", outputFlag);

            // One output property for list of maximum response points, regression lines and R, G, B histograms:
            addProperty< QMap<sFloat,QPointF> >("Max points", outputFlag);
            addProperty< QList<QLineF> >("Regression lines", outputFlag);
            addProperty< QList<double> >("R histogram", outputFlag);
            addProperty< QList<double> >("G histogram", outputFlag);
            addProperty< QList<double> >("B histogram", outputFlag);

            // An example trigger button to save a snapshot of current RGB image:
            addTrigger("Snapshot");
        }

        // Generic callback method for trigger buttons:
        void processTrigger(const QString triggerName) {
            if(triggerName == "Snapshot") {
                QVImage<uchar,3> imageRGB = getPropertyValue< QVImage<uChar,3> >("Input RGB image");
                QImage qimage = imageRGB;
                qimage.save("snapshot.jpg");
            } // else if (triggerName == "...")
        }

        // Main iteration method for main processing block:
        void iterate() {
            // Get input RGB image:
            QVImage<uchar,3> imageRGB = getPropertyValue< QVImage<uChar,3> >("Input RGB image");

            // Convert RGB image to gray:
            QVImage<uchar,1> imageGray = imageRGB;

            // Get current values of GUI parameters:
            const QVIndexedStringList selectedFilter = getPropertyValue<QVIndexedStringList>("Filter");
            const bool applyBox = getPropertyValue<bool>("box");
            const int boxRows = getPropertyValue<int>("boxrows");
            const int boxCols = getPropertyValue<int>("boxcols");
            const double thrLow = getPropertyValue<double>("thhi");
            const double thrHigh = getPropertyValue<double>("thlo");
            const double thMax = getPropertyValue<double>("thMax");
            const int lr = getPropertyValue<int>("lr");

            // Read GUI input linked from image windows:
            QRect CannyROI = getPropertyValue<QRect>("CannyROI");
            QVPolyline CannySelPoints = getPropertyValue<QVPolyline>("CannySelPoints");

            // Time statistics (put one after each stage of computation):
            timeFlag("Read input parameters");

            // First, we compute the Canny operator on the byte image (ouput will be binary, 0 or 255 values):
            uInt cols = imageGray.getCols(), rows = imageGray.getRows();

            // Define ROI for Canny:
            bool computeCanny = true;
            if (CannyROI == QRect()) {
                // User did not select rectangle: work in whole image:
                CannyROI = imageGray.getROI();
            } else if(CannyROI.height()>=5 and CannyROI.width()>=5) {
                // If rectangle by user is big enough, define ROI accordingly:
                if(CannyROI.bottom() == static_cast<int>(rows)-1)
                    CannyROI.setBottom(CannyROI.bottom()-1); // Solves IPP boundary problem in Canny function.
            } else {
                // Problematic ROI (too small ROI) for IPP Canny function: do not compute Canny image:
                computeCanny = false;
            }

            // Obtain Canny image (only in selected region of interest (ROI):
            QVImage<uChar> imageCanny;
            if(computeCanny)
                imageCanny = getCannyImage(imageGray,CannyROI,thrLow,thrHigh);
            else
                imageCanny = imageGray;

            timeFlag("Canny operator");

            // Get regression lines on every input square marked by user:
            QList<QLineF> regLines = getRegressionLines(imageCanny,CannyROI,CannySelPoints,lr);

            timeFlag("Regression lines");

            // If corresponding checkbox selected, previously apply box filter with requested box size values:
            if(applyBox) {
                // We need an auxiliary image, because IPP FilterBox is not an inplace operation:
                QVImage<uChar> imageGray2(cols,rows);
                FilterBox(imageGray, imageGray2, QSize(boxCols,boxRows),
                          /*anchor*/ QPoint(0,0),/* destROIOffset */ QPoint(boxCols/2,boxRows/2));
                imageGray = imageGray2;
                // Recover original ROI (which was reduced by FilterBox):
                imageGray.resetROI();
            }
            timeFlag("Box filter");

            // Apply selected response filter:
            QVImage<sFloat> imageFloat(cols,rows);
            int choice = selectedFilter.getIndex();
            switch (choice) {
                case 0: { // None
                    imageFloat = imageGray;
                    break;
                }
                case 1: { // Hessian
                    FilterHessianCornerResponseImage(imageGray, imageFloat, /* destROIOffset */ QPoint(2,2));
                    break;
                }
                case 2: { // Harris
                    FilterHarrisCornerResponseImage(imageGray, imageFloat);
                    // Underlying direct IPP call, no need for destROIoffset.
                    break;
                }
            }
            timeFlag("Corner response filter");

            // Recover original ROI (which was reduced by previous filters Hessian/Harris):
            imageFloat.resetROI();

            // Normalize float image to get values in [0..255]:
            FilterNormalize(imageFloat, imageFloat);

            timeFlag("Normalization");

            QMap<sFloat,QPointF> maxPoints;
            if(choice != 0) {
                const int radius = 3;
                maxPoints = findMaximalPoints(imageFloat, thMax, radius);
            }
            timeFlag("Get maximum response points");

            // Histograms of R, G, B channels:
            QVImage<uChar> selected;
            Copy(imageRGB,0,selected);
            const QVector<int> RHistogramInt = HistogramRange(selected);
            Copy(imageRGB,1,selected);
            const QVector<int> GHistogramInt = HistogramRange(selected);
            Copy(imageRGB,2,selected);
            const QVector<int> BHistogramInt = HistogramRange(selected);

            QList<double> RHistogram,GHistogram,BHistogram;
            foreach(int val,RHistogramInt)
                RHistogram.append(val);
            foreach(int val,GHistogramInt)
                GHistogram.append(val);
            foreach(int val,BHistogramInt)
                BHistogram.append(val);

            timeFlag("Obtain RGB histograms");

            // Finally, we set the output properties to their corresponding values:
            setPropertyValue< QVImage<uchar,1> >("Output image byte", imageCanny);
            setPropertyValue< QVImage<sFloat,1> >("Output image float", imageFloat);
            setPropertyValue< QMap<sFloat,QPointF> >("Max points", maxPoints);
            setPropertyValue< QList<QLineF> >("Regression lines", regLines);
            setPropertyValue< QList<double> >("R histogram", RHistogram);
            setPropertyValue< QList<double> >("G histogram", GHistogram);
            setPropertyValue< QList<double> >("B histogram", BHistogram);

            timeFlag("Write output parameters");
            }
        };

// Main function always has the same structure:
//   1. Create a QVApplication object.
//   2. Create image source block(s)
//   3. Create main processing block(s) (in our case, just one MyProcessingBlock).
//   4. Create main GUI (QVDefaultGUI) and extra GUI elements (QVImageCanvas and subclasses,QVFunctionPlot, ...),
//   5. Adequately link properties among objects of type 2-4.
//   6. Call exec method on QVApplication.
int main(int argc, char *argv[]) {
    // Application:
    QVApplication app(argc, argv, "Example program for QVision library.");

    // Image sources:
    QVVideoReaderBlock camera("Video");

    // Processing blocks:
    MyProcessingBlock filterBlock("Image filter block");

    // GUI elements:
    QVDefaultGUI interface;
    QVImageCanvas inputImage("Input RGB image");
    CannyImageCanvas outputImageByte("Output image byte");
    ResponseImageCanvas outputImageFloat("Output image float");
    QVFunctionPlot RGBHistogramPlot("RGB histogram");

    // Link properties:
    camera.linkProperty(&filterBlock,"Input RGB image");

    filterBlock.linkProperty("Input RGB image", inputImage);
    filterBlock.linkProperty("Output image byte", outputImageByte);
    filterBlock.linkProperty("Regression lines", outputImageByte, "Regression lines");
    filterBlock.linkProperty("Output image float", outputImageFloat);
    filterBlock.linkProperty("Max points", outputImageFloat,"Max points");
    filterBlock.linkProperty("lr",outputImageByte,"lr");
    filterBlock.linkProperty("R histogram",RGBHistogramPlot);
    filterBlock.linkProperty("G histogram",RGBHistogramPlot);
    filterBlock.linkProperty("B histogram",RGBHistogramPlot);
    outputImageByte.linkSelectedRectangle(filterBlock,"CannyROI");
    outputImageByte.linkSelectedPolyline(filterBlock,"CannySelPoints");

    // Execute application:
    return app.exec();
}

#endif


