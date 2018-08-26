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
@brief A simple program to test the wrapping functions for the optical flow on the GPU.

This application performs dense optical flow on an input video sequence using the GPU implementation of the TV-L1 optical flow algorithm
provided by the <a href="http://www.inf.ethz.ch/personal/chzach/opensource.html">GPU-KLT+FLOW</a> software.

@section Usage
Once compiled, the program should be used with this command line:
@code
	./demoDense --URL=<path or url to video>
@endcode

@param URL Video source identifier. See section @ref QVMPlayerURLFormat for further info about its format.
@author PARP Research Group. University of Murcia, Spain.
*/

#include <GL/glew.h>

#include <qvimageio.h>
#include <qvipp.h>

#include <QVApplication>
#include <QVDefaultGUI>
#include <QVVideoReaderBlock>
#include <QVImageCanvas>
#include <QVProcessingBlock>
#include <QVImage>

#include <qvgpukltflow.h>

#ifdef Q_WS_X11
  #include <X11/Xlib.h> // For XInitThreads function (called in main())
#endif

// Object to estimate flow:
TVL1_FlowEstimator *flowEstimator = 0;

// Canvas to draw flow image:
class FlowImageCanvas: public QVImageCanvas {
  public:
    FlowImageCanvas(const QString name=QString(),QWidget *parent=0) : QVImageCanvas(name,parent) {
        addProperty<int>("flow grid size",inputFlag);
    };
    void custom_viewer() {
        QVImage<sFloat,1> flowX = getPropertyValue<QVImage<sFloat,1> >("flowX");
        QVImage<sFloat,1> flowY = getPropertyValue<QVImage<sFloat,1> >("flowY");
        int flow_grid_size = getPropertyValue<int>("flow grid size");

        getQVPainter()->setPen(Qt::white);

        for(int ix=0; ix<flowX.getCols(); ix+=flow_grid_size) {
            for(int iy=0; iy<flowX.getRows(); iy+=flow_grid_size) {
                getQVPainter()->drawLine(QPointF(ix,iy),
                                         QPointF(ix+flow_grid_size*flowX(ix,iy)/2,
                                                 iy+flow_grid_size*flowY(ix,iy)/2));
                getQVPainter()->drawEllipse(QPoint(ix,iy), 1, 1);
            }
        }
    }
};

// Canvas to draw wheel:
class gridCanvasCanvas: public QVImageCanvas {
  public:
    gridCanvasCanvas(const QString name=QString(),QWidget *parent=0) : QVImageCanvas(name,parent) {

    };
    void custom_viewer() {

        int move, span = 180;
        QVImage<uChar,1> imageIn = getPropertyValue<QVImage<uChar,1> >("image In");
        move = getPropertyValue<double> ("move");

        getQVPainter()->setPen(Qt::blue);
        QPen p = getQVPainter()->pen();
        p.setWidth(20);
        getQVPainter()->setPen(p);
        QRectF rectangle(imageIn.getCols()/2-imageIn.getRows()/4 , imageIn.getRows()/4, imageIn.getRows()/2, imageIn.getRows()/2);
        QRectF rectangle2(imageIn.getCols()/2-imageIn.getRows()/4 , imageIn.getRows()/4, imageIn.getRows()/2, imageIn.getRows()/2);

        //Parte abajo volante
        getQVPainter()->drawPie(rectangle, move *16, -span*16 );
        //Parte arriba volante
        getQVPainter()->drawPie(rectangle2, (move*16) , span*16);
    }
};



class MyProcessingBlock : public QVProcessingBlock {
  private:
    QVImage <uChar,1> oldImage;
  public:
    MyProcessingBlock(QString name): QVProcessingBlock(name) {
        addProperty<QVImage<uChar,1> >("image In",inputFlag|outputFlag);
        addProperty<double> ("move", outputFlag);
        addProperty<double> ("lambda",inputFlag, 10.0, "Lambda", 0.0, 20.0);
        addProperty<double> ("theta",inputFlag, 0.02, "Theta", 0.0, 1.0);
        addProperty<double> ("tau",inputFlag, 0.25, "Tau", 0.0, 1.0);
        addProperty<int> ("nIterations",inputFlag, 10, "nIterations", 1, 50);
        addProperty<int> ("nOuterIterations",inputFlag, 4, "nOuterIterations", 1, 30);
        addProperty<int> ("nLevels",inputFlag, 4, "Pyramid levels", 1, 8);
        addProperty<double> ("Sensitivity", inputFlag, 0.01, "Sensitivity", 0.0, 0.1);
        addProperty<int>("flow grid size",inputFlag|outputFlag,10 ,"Flow grid size",5,10);
        addProperty<QVImage<uChar,1> >("flowX",outputFlag);
        addProperty<QVImage<uChar,1> >("flowY",outputFlag);
    }

    void iterate() {
        QVImage<uChar,1> imageIn = getPropertyValue<QVImage<uChar,1> >("image In");
        QVImage<sFloat, 1> x = QVImage<sFloat, 1>(imageIn.getCols(), imageIn.getRows());
        QVImage<sFloat,1 > y = QVImage<sFloat, 1>(imageIn.getCols(), imageIn.getRows());
        static QVPyramid *p1,*p2;
        static double z = 0;
        bool reset = false;

        // Initialize only in first iteration (must be done here in the processing block thread):
         if(getIteration() == 0) {
             InitGLEWCg();
             reset = true;
         }

         // Read input properties:
         static int width = 0, height = 0, nLevels = 0, nIterations = 0, nOuterIterations = 0;
         static double lambda = 0.0, tau = 0.0, theta = 0.0;

         if(width != imageIn.getCols()) {
             width = imageIn.getCols();
             reset = true;
         }
         if(height != imageIn.getRows()) {
             height = imageIn.getRows();
             reset = true;
         }
         if(nLevels != getPropertyValue<int>("nLevels")) {
             nLevels = getPropertyValue<int>("nLevels");
             reset = true;
         }
         if(nIterations != getPropertyValue<int>("nIterations")) {
             nIterations = getPropertyValue<int>("nIterations");
             reset = true;
         }
         if(nOuterIterations != getPropertyValue<int>("nOuterIterations")) {
             nOuterIterations = getPropertyValue<int>("nOuterIterations");
             reset = true;
         }
         if(lambda != getPropertyValue<double>("lambda")) {
             lambda = getPropertyValue<double>("lambda");
             reset = true;
         }
         if(tau != getPropertyValue<double>("tau")) {
             tau = getPropertyValue<double>("tau");
             reset = true;
         }
         if(theta != getPropertyValue<double>("theta")) {
             theta = getPropertyValue<double>("theta");
             reset = true;
         }

        if(reset) {
            if(flowEstimator != 0)
                flowEstimator->deallocate();
            qvInitFlowGPU(flowEstimator, width, height, nLevels, nIterations, nOuterIterations, lambda, tau, theta);
            if(p1 != 0)
                delete p1;
            if(p2 != 0)
                delete p2;
            p1 = new QVPyramid(width, height, nLevels);
            p2 = new QVPyramid(width, height, nLevels);
        }
        timeFlag("Reset flow estimator");

        QVImage<uChar,1> left=oldImage, right=imageIn;
        if(not reset) {
            p1->buildPyramid(left);
            p2->buildPyramid(right);
        }
        timeFlag("Pyramids");
        if(not reset) {
            qvOpticalFlowGPU(flowEstimator, p1, p2, x, y);
        }
        timeFlag("Flow");
        if(not reset) {
            oldImage = imageIn;
            double vx, vy, px, py;
            for (int ix = 0; ix < x.getCols(); ix++) {
                for (int iy = 0; iy < x.getRows(); iy++){
                    vx = x(ix,iy);
                    vy = y(ix,iy);
                    px = ix - width/2;
                    py = iy - height/2;
                    if (ix != width/2 && iy != height/2)
                        z += (px * vy - py * vx) / (px*px + py*py);
                }
            }
        }
        timeFlag("Wheel");

        double sensitivity = getPropertyValue<double> ("Sensitivity");
        setPropertyValue<QVImage <uChar,1> >("image In", imageIn);
        setPropertyValue<QVImage <sFloat,1> >("flowX", x);
        setPropertyValue<QVImage <sFloat,1> >("flowY", y);
        setPropertyValue<double>("move",-z*sensitivity);
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
    QVImageCanvas videoCanvas ("Input video");
    FlowImageCanvas flowCanvas ("Flow image");
    gridCanvasCanvas gridCanvas ("Output grid");

    camera.linkProperty(&processingBlock,"image In");
    processingBlock.linkProperty("image In",&videoCanvas);
    processingBlock.linkProperty("flowX", &flowCanvas);
    processingBlock.linkProperty("flowY", &flowCanvas);
    processingBlock.linkProperty("flow grid size", &flowCanvas,"flow grid size");
    processingBlock.linkProperty("image In",&gridCanvas);
    processingBlock.linkProperty("move", &gridCanvas);

    return app.exec();
}
