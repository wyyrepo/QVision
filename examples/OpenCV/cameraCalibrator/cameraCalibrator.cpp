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
@ingroup OpenCVExamplePrograms
@brief Obtains intrinsic camera matrix and distortion coefficients for a camera.

This example is based on the example 11-1 from the book:

@code
Learning OpenCV: Computer Vision with the OpenCV Library
     by Gary Bradski and Adrian Kaehler
     Published by O'Reilly Media, October 3, 2008
@endcode

It uses the chessboard template image <i>OpenCV_Chessboard.png</i> attacked to the source code to obtain the camera calibration parameters.

@section Usage
Once compiled, the program should be used with this command line:
\code
	./cameraCalibrator --URL=<video source>
\endcode

10 images containing the chessboard must be captured using the <i>Grab chessboard</i> button of the graphical user interface. Then the application will calibrate the intrinsic camera parameters when the button <i>Calibrate</i> is pressed.

@param URL Video source identification string. See section @ref QVMPlayerURLFormat for further info about its format.

@author PARP Research Group. University of Murcia, Spain.
*/
#include <iostream>
#include <fstream>

#include <QVMatrix>
#include <QVApplication>
#include <QVImageCanvas>
#include <QVVideoReaderBlock>
#include <QVDefaultGUI>

#include <qvip.h>
#include <qvimageio.h>
#include <qvprojective.h>

#ifndef DOXYGEN_IGNORE_THIS
#include <cv.h>
#include <highgui.h>

#define	NUM_CHESSBOARDS	16
/* *************** License:**************************
   Oct. 3, 2008
   Right to use this code in any way you want without warrenty, support or any guarentee of it working.

   BOOK: It would be nice if you cited it:
   Learning OpenCV: Computer Vision with the OpenCV Library
     by Gary Bradski and Adrian Kaehler
     Published by O'Reilly Media, October 3, 2008
 
   AVAILABLE AT: 
     http://www.amazon.com/Learning-OpenCV-Computer-Vision-Library/dp/0596516134
     Or: http://oreilly.com/catalog/9780596516130/
     ISBN-10: 0596516134 or: ISBN-13: 978-0596516130    

   OTHER OPENCV SITES:
   * The source code is on sourceforge at:
     http://sourceforge.net/projects/opencvlibrary/
   * The OpenCV wiki page (As of Oct 1, 2008 this is down for changing over servers, but should come back):
     http://opencvlibrary.sourceforge.net/
   * An active user group is at:
     http://tech.groups.yahoo.com/group/OpenCV/
   * The minutes of weekly OpenCV development meetings are at:
     http://pr.willowgarage.com/wiki/OpenCV
   ************************************************** */

/*void help()
	{
	std::cout << "\n\n"
	" Calling convention:\n"
	" ./cameraCalibratorOpenCV  <board_w>  <board_h>  <number_of_boards>  <skip_frames>\n"
	"\n"
	"   WHERE:\n"
	"     board_w, board_h   -- are the number of corners along the row and columns respectively\n"
	"     number_of_boards   -- are the number of chessboard views to collect before calibration\n"
	"     skip_frames        -- are the number of frames to skip before trying to collect another\n"
	"                           good chessboard.  This allows you time to move the chessboard.  \n"
	"                           Move it to many different locations and angles so that calibration \n"
	"                           space will be well covered. \n"
	"\n"
	" Hit ‘p’ to pause/unpause, ESC to quit\n"
	"\n";
	}*/

double	error(const double u, const double v, const double x, const double y, const QVVector k)
	{
	const double	r2 = x*x+y*y, r4 = r2*r2, r6 = r4*r2, r8 = r4*r4,
			d = 1 + k[0] * r2 + k[1] * r4 + k[2] * r6 + k[3] * r8;
	const double 	errorU = u - x * d, errorV = v - y * d;

	return errorU * errorU + errorV * errorV;
	}

QPointF	findMinimum(const QPointF &orig, const QVVector k)
	{
	const int	u = orig.x(), v = orig.y();
	QPointF actual = orig;

	while(true)
		{
		QPointF best = actual;
		double bestError = std::numeric_limits<double>::max();
	
		for (double i = -0.01; i <= 0.01; i+=0.0025)
			for (double j = -0.01; j <= 0.01; j+=0.0025)
				if (error(u, v, actual.x()+i, actual.y()+j, k) < bestError)
					best = actual + QPoint(i, j);
		if (actual == best)
			break;

		actual = best;
		}
	return actual;
	}

class CameraCalibration
	{
	public:
		int cols, rows;
		QVMatrix K, distortionCoeffs;

		QVMatrix Kinv;
		IplImage *dx, *dy;

		bool initCacheMap(IplImage *&dx_, IplImage *&dy_, const QVMatrix &A2 = QVMatrix::identity(3))
			{
			Kinv = pseudoInverse(K);

			CvMat	* camera_matrix = K.toCvMat(CV_32F),
				* dist_coeffs = distortionCoeffs.toCvMat(CV_32FC1),
				* new_camera_matrix = A2.toCvMat(CV_32F);

			if (dx_ != NULL)
				cvReleaseImage(&dx);
			if (dy_ != NULL)
				cvReleaseImage(&dy);

			if (cols == 0 or rows == 0)
				return false;

			dx_ = cvCreateImage(cvSize(cols, rows), IPL_DEPTH_32F, 1);
			dy_ = cvCreateImage(cvSize(cols, rows), IPL_DEPTH_32F, 1);

			cvInitUndistortRectifyMap(camera_matrix, dist_coeffs, NULL /* R */, new_camera_matrix, dx_, dy_);

			cvReleaseMat(&camera_matrix);
			cvReleaseMat(&dist_coeffs);
			cvReleaseMat(&new_camera_matrix);

			return true;
			}

	public:
		CameraCalibration(const CameraCalibration &other):
			cols(other.cols), rows(other.rows), K(other.K), distortionCoeffs(other.distortionCoeffs), dx(NULL), dy(NULL)
			{
			initCacheMap(dx, dy);
			}

		CameraCalibration(	const int cols = 0, const int rows = 0,
					const QVMatrix &K = QVMatrix::identity(3),
					const QVMatrix &distortionCoeffs = QVMatrix(4, 1, 0.0)):
			cols(cols), rows(rows), K(K), distortionCoeffs(distortionCoeffs), dx(NULL), dy(NULL)
			{
			initCacheMap(dx,dy);
			}

		~CameraCalibration()
			{
			if (dx != NULL)
				cvReleaseImage(&dx);
			if (dy != NULL)
				cvReleaseImage(&dy);
			}

		CameraCalibration & operator = (const CameraCalibration &other)
			{
			cols = other.cols;
			rows = other.rows;
			K = other.K;
			distortionCoeffs = other.distortionCoeffs;
			initCacheMap(dx,dy);
			return (*this);
			}

		bool inited() const
			{
			return (cols != 0 and rows != 0);
			}

		bool loadFromFile(const QString &fileName)
			{
			std::ifstream stream;
			stream.open(qPrintable(fileName));

			if ( stream.fail() )
				return false;

			stream >> cols;
			stream >> rows;
			stream >> K;
			stream >> distortionCoeffs;

			stream.close();

			return initCacheMap(dx,dy);
			}

		bool saveToFile(const QString &fileName) const
			{
			std::ofstream stream;
			stream.open(qPrintable(fileName));

			if ( stream.fail() )
				return false;

			stream << cols << std::endl;
			stream << rows << std::endl;
			stream << K;
			stream << distortionCoeffs;

			stream.close();

			return true;
			}

		QPointF map(const int i, const int j) const
			{
			// applyHomography(Kinv,QPointF(i,j))  da mejores resultados que esto. ¿Porqué?
			return QPointF(CV_IMAGE_ELEM(dx, float, j, i), CV_IMAGE_ELEM(dy, float, j, i));
			}

		QVImage<uChar, 1> radialUndistort(const QVImage<uChar, 1> &image)
			{
			if (cols == 0 or rows == 0)
				return QVImage<uChar, 1>();

			// --------------
			QVMatrix A2 = K;
			A2(0,0) = 0.75*A2(0,0);
			A2(1,1) = 0.75*A2(1,1);
			A2(0,2) = 160.0;
			A2(1,2) = 100.0;

			IplImage *dx_ = NULL, *dy_ = NULL;

			initCacheMap(dx_, dy_, A2);

			// --------------
			IplImage *src = image, *dst = image;
 
			cvRemap(src, dst, dx_, dy_, CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
			QVImage<uChar, 1> outputImage = QVImage<uChar, 1>(dst);

			cvReleaseImage(&dx_);
			cvReleaseImage(&dy_);
			cvReleaseImage(&src);
			cvReleaseImage(&dst);

			return outputImage;
			}
	};

QHash<QV3DPointF, QPointF> detectBoard(const QVImage<uChar, 3> &actualImage, const int board_w = 6, const int board_h = 9)
	{
	const int board_n = board_w * board_h;
	const CvSize board_sz = cvSize(board_w, board_h);
	CvPoint2D32f* corners = new CvPoint2D32f[ board_n ];

	IplImage *image = actualImage;
	IplImage *gray_image = cvCreateImage(cvGetSize(image), 8, 1);

	CvSize image_sz = cvGetSize(image);

	int corner_count, found = cvFindChessboardCorners(
						image, board_sz, corners, &corner_count,
						CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
	
	//Get Subpixel accuracy on those corners
	cvCvtColor(image, gray_image, CV_BGR2GRAY);
	cvFindCornerSubPix(	gray_image, corners, corner_count, cvSize(11,11),cvSize(-1,-1),
				cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1));

	cvReleaseImage(&image);
	cvReleaseImage(&gray_image);

	QHash<QV3DPointF, QPointF> boardCorners;
	if(corner_count == board_n)
		for(int j=0; j<board_n; ++j)
			boardCorners[QV3DPointF(j/board_w, j%board_w, 0.0f)] = QPointF(corners[j].x, corners[j].y);

	delete corners;
	return boardCorners;
	}

CameraCalibration calibrateIntrinsicsFrom3DTo2DCorrespondences(const QList< QHash<QV3DPointF, QPointF> > &pointCorrespondences, const int cols, const int rows)
	{
	// Get total number of points
	int num_points = 0;
	for(int i = 0, index = 0; i < pointCorrespondences.size(); i++)
		num_points += pointCorrespondences[index].count();

	// Create 3D and 2D point lists
	CvMat* object_points  = cvCreateMat(num_points,3,CV_32FC1);
	CvMat* image_points   = cvCreateMat(num_points,2,CV_32FC1);
	CvMat* point_counts   = cvCreateMat(pointCorrespondences.size(),1,CV_32SC1);

	// TRANSFER THE POINTS INTO THE CORRECT SIZE MATRICES
	for(int i = 0, index = 0; i < pointCorrespondences.size(); i++)
		{
		foreach(QV3DPointF point3D, pointCorrespondences[i].keys())
			{
			CV_MAT_ELEM( *image_points, float, index, 0)	= pointCorrespondences[i][point3D].x();
			CV_MAT_ELEM( *image_points, float, index, 1)	= pointCorrespondences[i][point3D].y();
			CV_MAT_ELEM( *object_points, float, index, 0)	= point3D.x();
			CV_MAT_ELEM( *object_points, float, index, 1)	= point3D.y();
			CV_MAT_ELEM( *object_points, float, index, 2)	= point3D.z();

			index++;
			}
		CV_MAT_ELEM(*point_counts, int, i, 0) = pointCorrespondences[i].count();
		}

	// Create intrinsic and distortion coefficient matrices
	CvMat* intrinsic_matrix  = cvCreateMat(3,3,CV_32FC1);
	CvMat* distortion_coeffs = cvCreateMat(4,1,CV_32FC1);

	CV_MAT_ELEM( *intrinsic_matrix, float, 0, 0 ) = 1.0f;
	CV_MAT_ELEM( *intrinsic_matrix, float, 1, 1 ) = 1.0f;

	// Calibrate
	cvCalibrateCamera2(object_points, image_points, point_counts, cvSize(cols,rows), intrinsic_matrix, distortion_coeffs, NULL, NULL,0);

	// Create calibration object
	CameraCalibration result = CameraCalibration(cols, rows, intrinsic_matrix, distortion_coeffs);

	// Release data
	cvReleaseMat(&object_points);
	cvReleaseMat(&image_points);
	cvReleaseMat(&point_counts);
	cvReleaseMat(&intrinsic_matrix);
	cvReleaseMat(&distortion_coeffs);

	return result;
	}

class CameraCalibratorBlock: public QVProcessingBlock
	{
	private:
		QVImage<uChar, 3> actualImage;

		QList< QHash<QV3DPointF, QPointF> > grabbedBoards;

		CameraCalibration calibration;

	public:
		CameraCalibratorBlock(QString name): QVProcessingBlock(name)
			{
			addProperty< QVImage<uChar,3> >("Input image", inputFlag|outputFlag);
			addProperty< QVImage<uChar,3> >("Output image", outputFlag);
			addProperty< QString >("Camera file name", inputFlag|outputFlag, "calibrated.camera");

			addProperty< QList<QPointF> >("Board corners", outputFlag);
			addTrigger("Grab chessboard");
			addTrigger("Calibrate");

			if (calibration.loadFromFile(getPropertyValue< QString >("Camera file name")))
				std::cout << "Camera loaded" << std::endl;
			else
				std::cout << "Could not load camera" << std::endl;
			}

		void processTrigger(const QString triggerName)
			{
			if (triggerName == "Grab chessboard")
				{
				const QHash<QV3DPointF, QPointF> grabbedBoard = detectBoard(actualImage);
				if (grabbedBoard.count() > 0)
					{
					grabbedBoards << grabbedBoard;
					writeQVImageToFile(	QString("temp/frame-") + QString::number(getIteration()).QString::rightJustified(8, '0') + ".png",
								actualImage);
					}
				std::cout << "Captured " << grabbedBoards.size() << " boards"<< std::endl;
				}
			else if (triggerName == "Calibrate")
				{
				std::cout << "Proceeding to camera calibration." << std::endl;
				calibration = calibrateIntrinsicsFrom3DTo2DCorrespondences(grabbedBoards, 320, 240);

				// ---------------------------------
				/*for(int i = 0; i < grabbedBoards.size(); i++)
					foreach(QV3DPointF point3D, grabbedBoards[i].keys())
						{
						const QPointF p = grabbedBoards[i][point3D];
						grabbedBoards[i][point3D] = calibration.map(p.x(), p.y());
						}

				CameraCalibration calibration2 = calibrateIntrinsicsFrom3DTo2DCorrespondences(grabbedBoards, 320, 240);

				std::cout << "K 1 = " << calibration.K << std::endl;
				std::cout << "dist 1 = " << calibration.distortionCoeffs << std::endl;
				std::cout << "K 2 = " << calibration2.K << std::endl;
				std::cout << "dist 2 = " << calibration2.distortionCoeffs << std::endl;*/

				// ---------------------------------

				if (calibration.saveToFile("calibrated.camera"))
					std::cout << "Camera calibrated and stored." << std::endl;
				else
					std::cout << "Error storing camera." << std::endl;
				}
			std::cout << "End of trigger processing" << std::endl;
			}

		void iterate()
			{
			actualImage = getPropertyValue<QVImage<uChar, 3> >("Input image");

			const QHash<QV3DPointF, QPointF> boardCorners = detectBoard(actualImage);
			setPropertyValue< QList<QPointF> >("Board corners", boardCorners.values());

			if (not calibration.inited())
				return;

			if (boardCorners.count() > 0)
				{
				QList<QPointFMatching> matchings;
				foreach(QV3DPointF point3D, boardCorners.keys())
					{
					const QPointF p = boardCorners[point3D];
					matchings << QPointFMatching(QPointF(point3D.x(), point3D.y()), applyHomography(calibration.Kinv,p));
					}
				const QVMatrix	H = computeProjectiveHomography(matchings),
						errorM = H.transpose()*H,
						normalizedErrorM = errorM * (2.0 / (errorM(0,0) + errorM(1,1)));

				const double a = errorM(0,0), b = errorM(0,1), c = errorM(1,0), d = errorM(1,1);

				std::cout << ( ABS(1-normalizedErrorM(0,0)) + ABS(1- normalizedErrorM(1,1)) + 2*ABS(normalizedErrorM(1,0)) ) << std::endl;
				std::cout << "H^t * H = " << normalizedErrorM << std::endl;
				}

			//setPropertyValue< QVImage<uChar, 3> >("Output image", calibration.radialUndistort(actualImage));
			}
	};

#include <QVVector>
#include <QVMatrix>
int main(int argc, char *argv[])
	{
	QVApplication app(argc, argv, "Example program for QVision library. Displays the contents of a video source.");

	QVVideoReaderBlock camera("Video");

	CameraCalibratorBlock player("Video player");
	camera.linkProperty(&player,"Input image");

	QVDefaultGUI interface;

	QVImageCanvas inputImageCanvas("Input image");
	player.linkProperty("Input image", inputImageCanvas);
	player.linkProperty("Board corners", inputImageCanvas);

	QVImageCanvas outputImageCanvas("Output image");
	player.linkProperty("Output image", outputImageCanvas);


	return app.exec();
	}
#endif	// DOXYGEN_IGNORE_THIS

