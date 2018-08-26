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
@ingroup ExamplePrograms
@brief A simple augmented reality example application.

This application estimates the intrinsic calibration and camera pose for the frames of an input video sequence, in relation with a template pattern.

The application detects the following template on the input frames:

@image html template.png
@image latex template.png

Each frame, the planar homography which maps the original pose of the template to its location is estimated.
If successful, the application obtains the camera pose, and an estimation of the camera focal distance from this homography.
By averaging these focal values, a robust estimation for the camera calibration is obtained.

A standard image canvas augments the input frames with an artificial object using the estimated camera pose and intrinsic calibration:

@image html teapot.png
@image latex teapot.png

@section Usage
Once compiled, the program should be used with this command line:
@code
	./AugmentedReality --URL=<path or url to video>
@endcode

@param URL Video source identification string. See section @ref QVMPlayerURLFormat for further info about its format.
@author PARP Research Group. University of Murcia, Spain.
*/

#include <QVApplication>
#include <QVDefaultGUI>
#include <QVVideoReaderBlock>
#include <QVImageCanvas>
#include <QVNumericPlot>
#include <QVProcessingBlock>
#include <QVImage>
#include <QVPolyline>
#include <QVPolylineF>
#include <QVMatrix>

#include <qvipp.h>
#include <qvip.h>
#include <qvprojective.h>

#include <GL/glut.h>
#include <QVCameraPose>
#include <QV3DModel>

#include <qv3dobjects.h>

// Use Otsu threshold to detect contours around dark areas at the image.
QList<QVPolyline> detectContours(const QVImage<uChar,1> &imageIn)
	{
	uChar otsu_th;
	ComputeThreshold_Otsu(imageIn,otsu_th);

	return getConnectedSetBorderContoursThreshold(imageIn,otsu_th);
	}

// Detects in an image the contour of the largest dark region not touching the image boundaries.
QVPolyline selectBestContour(const QList<QVPolyline> &contours, const int templateCount, const int cols, const int rows, const int minCount = 30, const double maxError = 5.0)
	{
	double bestError = 1e15;
	QVPolyline bestContour;
	foreach(QVPolyline contour, contours)
		{
		// Discard contours shorter than a given value.
		if (contour.count() < minCount)
			continue;

		// Discard contours touching the image boundaries.
		//bool touchsBorder = false;
		foreach(QPoint point, contour)
			if(point.x()==0 or point.x()==cols-1 or point.y()==0 or point.y()==rows-1)
				continue;

		// Discard contours with a number of corners different than the template.
		double contourError;
		QVPolyline contourReduced;
		IterativePointElimination(contour, contourReduced, maxError, false, true, &contourError);

		if (contourReduced.count() != templateCount)
			continue;

		// Keep the contour with the lowest error.
		if (contourError >= bestError)
			continue;

		bestContour = contour;
		bestError = contourError;
		}
	return bestContour;
	}

// Matches the contour with the template. Returns the planar homography from the template to the image contour.
QVMatrix matchContourWithTemplate(const QVPolyline &contour, const QVPolylineF &templateL, const double maxError = 0.1)
	{
	// Reduces the number of elements in the contour with an IPE filter.
	QVPolyline contourReduced;
	IterativePointElimination(contour,contourReduced,templateL.length(),true,true);
	
	// Discard if the resulting contour does not have the same number of elements than the template.
	//bool fail = false;
	if(contourReduced.length() != templateL.length())
		return QVMatrix();

	// Find the correct orientation for the contour, and estimate the planar homography.
	double bestError = 1e15;
	QVMatrix H;
	for(int j=0;j<templateL.length();j++)
		{
		QList< QPair<QPointF, QPointF> > matchings;
		for(int i=0;i<templateL.length();i++)
			matchings << QPointFMatching(contourReduced[(i+j)%templateL.length()], templateL[i]);

		const QVMatrix temptativeH = computeProjectiveHomography(matchings);

		double err = 0;
		for(int i=0;i<templateL.length();i++)
			err += norm2(applyHomography(temptativeH,contourReduced[(i+j)%templateL.length()]) - templateL[i]);

		err /= double(templateL.count());

		if(err < bestError)
			{
			bestError = err;
			H = temptativeH;
			}
		}

	// If the planar reprojection error is below the maximal threshold, accept the alighment.
	if (bestError > maxError)
		return QVMatrix();
	else
		return H;
	}

// Main application processing block.
class ARProcessingBlock : public QVProcessingBlock
	{
	private:
		QVPolylineF templateL;
		QList<double> focals;

	public:
		// Main constructor
		ARProcessingBlock(QString name): QVProcessingBlock(name)
			{
			// Video input/output.
			addProperty<QVImage<uChar,3> >("imageIn",inputFlag|outputFlag);

			// Camera pose and calibration for the AR canvas.
			addProperty<QVMatrix>("Camera calibration matrix", outputFlag);
			addProperty<QVCameraPose>("Camera pose", outputFlag);

			// Template initialization.
			templateL	<< QPointF(0.0,0.0)
					<< QPointF(1.0,0.0)
					<< QPointF(1.0,0.5)
					<< QPointF(0.5,0.5)
					<< QPointF(0.5,1.0)
					<< QPointF(0.0,1.0);

			for(int i = 0; i < templateL.count(); i++)
				templateL[i] = templateL[i] - QPointF(0.5, 0.5);
			};

		// Resets the camera pose.
		void hidePose()
			{
			// If the calibration matrix is set to QVMatrix(), the AR window
			// will not show any augmented object.
			setPropertyValue<QVMatrix>("Camera calibration matrix", QVMatrix());
			setPropertyValue<QVCameraPose>("Camera pose", QVCameraPose());
			}

		// Main image-processing loop.
		void iterate()
			{
			// 1) Read image from input video source.
			const QVImage<uChar,1> imageIn = getPropertyValue<QVImage<uChar,3> >("imageIn");
			const int rows = imageIn.getRows(), cols = imageIn.getCols();			
			timeFlag("Read input data");

			// 2) Detect contours at the image
			const QList<QVPolyline> contours = detectContours(imageIn);
			timeFlag("Detect contours");

			// 3) Detect the contour of the template at the image.
			// 3.1) Detect the best contour at the image.
			const QVPolyline bestContour = selectBestContour(contours, templateL.count(), cols, rows);
			timeFlag("Detect best contour");

			// 3.2) Find the planar homography between the best contour and the template,
			// with the lowest reprojection error.
			const QVMatrix H = matchContourWithTemplate(bestContour, templateL, 0.05);

			// If not successful, reset pose and return.
			if (H == QVMatrix())
				{
				hidePose();
				return;
				}
			timeFlag("Find planar homography");

			// 4) Estimate camera focal.
			// 4.1) A list of estimated focals is updated at each frame. The application uses the median value
			// of those estimated focals as a robust estimation for the camera focal.
			const double actualEstimatedFocal = computeCameraFocalFromPlanarHomography(H, cols, rows, true);

			// 4.2) Update list of estimated focals with the actual estimated focal.
			if ( focals.count() < 200 and not isnan(actualEstimatedFocal) )
				focals << actualEstimatedFocal;

			// 4.3) If no estimated focals are available, reset camera pose and return.
			if (focals.count() == 0)
				{
				hidePose();
				return;
				}

			// 4.4) Robust estimation of the real focal from the median of previously estimated focals.
			const double focal = QVVector(focals).median();
			timeFlag("Estimate focal");

			// 5) Calibrate intrinsic camera matrix and camera pose.
			const QVMatrix K = QVMatrix::cameraCalibrationMatrix(focal, 4.0 * rows / (3.0 * cols), cols/2.0, rows/2.0);
			const QVCameraPose cameraPose = getCameraPoseFromCalibratedHomography(K,H);
			timeFlag("Estimate camera pose");

			// 6) Publish camera pose and intrinsic matrix.
			setPropertyValue<QVMatrix>("Camera calibration matrix", K);
			setPropertyValue<QVCameraPose>("Camera pose", cameraPose);
			}

	};

// Augmented reality canvas.
class ARCanvas : public QVImageCanvas
	{
	public:
		ARCanvas(QString name) : QVImageCanvas(name)	{ };

		void custom_viewer_3D()
			{
			glEnable(GL_LIGHTING);		// Enable lighting.
			glEnable(GL_LIGHT0);		// Enable light zero (note: uses default values).
			glEnable(GL_COLOR_MATERIAL);	// Configure glColor().
			glEnable(GL_DEPTH_TEST);	// Enable depth testing.
			glClear(GL_DEPTH_BUFFER_BIT);	// Clear depth buffers.

			// Draw a wire teapot at the origin of coordinates using GLUT primitives.
			glColor3ub(128,196,255);

			glRotatef(90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0,0.20,0.0);

			glutSolidTeapot(0.3);
			};
	};

int main(int argc,char **argv)
	{
	// GUI interface.
	QVApplication app(argc,argv);
	QVDefaultGUI gui;

	// Video reader.
	QVVideoReaderBlock camera("Camera");

	// Processing block.
	ARProcessingBlock processingBlock("My processing block");
	camera.linkProperty(&processingBlock,"imageIn");

	// Augmented reality canvas.
	ARCanvas imageCanvas("augmented objects");

	QV3DCoordinateCenter axis(1.0);
	imageCanvas.add3DModel(axis);

	processingBlock.linkProperty("imageIn",&imageCanvas);

	// Link camera calibration matrix and camera pose from the processing block to the AR window.
	// Note: if the calibration matrix is set to QVMatrix(), the AR window will not show any augmented object.
	processingBlock.linkProperty("Camera calibration matrix", &imageCanvas);
	processingBlock.linkProperty("Camera pose", &imageCanvas);

	// Needed for GLUT calls.
	glutInit(&argc,argv);

	// Execute application.
	return app.exec();
	}

