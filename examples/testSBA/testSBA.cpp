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
@brief Tests the GEA optimization on a SfM reconstruction.

This program performs a Bundle Adjustment optimization on an input SfM reconstruction using the <a href="http://www.ics.forth.gr/~lourakis/sba/">implementation by A. Argyros and M.I.A. Lourakis</a>.

@section Usage
Simply compile, and execute the binary:
\code
	./testSBA <reconstruction_file_or_path> [iterations] [lambda]
\endcode

See the documentation of function @ref readSfMReconstruction for more information about the possible SfM reconstruction input file formats.

@author PARP Research Group. University of Murcia, Spain.
*/

// Uncomment the line below to show the initial and the optimized reconstruction.
#define SHOW_RECONSTRUCTION

#include <QVApplication>
#include <QTime>
#include <qvsfm.h>
#include <sfmviewer.h>

// Print the number of cameras, 3D points, projections and some statistics from a SfM reconstruction.
void printReconstructionStats(	const QList<QVCameraPose> &cameraPoses,
				const QList<QV3DPointF> &points3D,
				const QList< QHash< int, QPointF> > &pointsTrackings)
	{
	const int numCameras = cameraPoses.count(), numPoints = points3D.count();
	int numProjections = 0;
	QHash< int, QPointF> temp;
	foreach(temp, pointsTrackings)
		numProjections += temp.count();

	std::cout << "[main] Readed "	<< numPoints << " points, "
					<< numCameras << " cameras, "
					<< numProjections << " projections, "
					<< double(numProjections)/double(numCameras) << " projections/camera, "
					<< double(numProjections)/double(numPoints) << " projections/point."
					<< std::endl;
	}

int main(int argc, char *argv[])
	{
	#ifdef SHOW_RECONSTRUCTION
	QVApplication app(argc, argv, "Example application for QVision.", true);
	#else
	QVApplication app(argc, argv, "Example application for QVision.", false);
	#endif

	// 1. Get the data-set files path from the first command line parameter.
	if (app.getNumberOfArguments() < 2)
		{
		std::cout << "Usage: " << std::endl << "\t" << argv[0] << " <data_set_path> [iterations] [lambda_sba]"
			<< std::endl << std::endl;
		exit(0);
		}

	const QString path = app.getArgument(1);

	// 2. Set the number of iterations, and lambda values for the GEA and sSBA optimizations, if provided as parameters through the command line.
	bool iters_OK = true, lambda_sba_OK = true;

	const int iters =			(app.getNumberOfArguments() < 3)? 1 : app.getArgument(2).toInt(&iters_OK);
	const double lambda_sba =	(app.getNumberOfArguments() < 4)? 1.0 : app.getArgument(3).toDouble(&lambda_sba_OK);

	if (not iters_OK)
		{
		std::cout << "[main] Error reading number of iterations." << std::endl;
		exit(0);
		}
	else
		std::cout << "[main] Number of iterations = " << iters << std::endl;

	if (not lambda_sba_OK)
		{
		std::cout << "[main] Error reading lambda for SBA optimization" << std::endl;
		exit(0);
		}
	else
		std::cout << "[main] Lambda for SBA = " << lambda_sba << std::endl;

	// 3. Read SfM reconstruction from the specified path.
	QList<QV3DPointF> points3D;
	QList<QVCameraPose> cameraPoses;
	QList<QVMatrix> cameraCalibrations;
	QList< QHash< int, QPointF> > pointsTrackings;

	if( not readSfMReconstruction(path, cameraCalibrations, cameraPoses, points3D, pointsTrackings) )
		{
		std::cout << "[main] Error: could not read SfM reconstruction from path '" << qPrintable(path) << "'." << std::endl;
		return 0;
		}

	// 4. Correct camera intrinsic calibrations from point projections.
	const QList< QHash< int, QPointF> > calibratedPointsTrackings = correctIntrinsics(cameraCalibrations, pointsTrackings);

	// 5. Correct camera cheirality. This is required for the sSBA routines to work properly.
	if (testCheirality(cameraPoses, calibratedPointsTrackings))
		invertCheirality(cameraPoses, points3D);

	// 6. Print SfM reconstruction stats.
	std::cout << "[main] Reconstruction loaded."<< std::endl;	
	printReconstructionStats(cameraPoses, points3D, calibratedPointsTrackings);

	// 7. Perform sSBA optimization on the reconstruction.
	QList<QV3DPointF> points3D_SBA;
	QList<QVCameraPose> cameraPoses_SBA;
	laSBAOptimization(cameraPoses, points3D, calibratedPointsTrackings, cameraPoses_SBA, points3D_SBA, iters, 0, 0, lambda_sba);

	// 9. Print errors and total performance times.
	std::cout << "[main] Initial error\t" << 1000.0 * reconstructionError(cameraPoses, points3D, calibratedPointsTrackings) << std::endl;
	std::cout << "[main] SBA error/time\t" << 1000.0 * reconstructionError(cameraPoses_SBA, points3D_SBA, calibratedPointsTrackings) << std::endl;
	std::cout << "[main] SBA2 error/time\t" << 1000.0 * reconstructionError(cameraPoses_SBA, linear3DPointsTriangulation(cameraPoses_SBA, calibratedPointsTrackings), calibratedPointsTrackings) << std::endl;

	#ifdef SHOW_RECONSTRUCTION
	SfMViewer originalMap(cameraPoses, points3D, "Original reconstruction");
	SfMViewer sbaOptimizedMap(cameraPoses_SBA, points3D_SBA, "Reconstruction optimized with SBA");
	SfMViewer sbaOptimizedMap2(cameraPoses_SBA, linear3DPointsTriangulation(cameraPoses_SBA, calibratedPointsTrackings), "Reconstruction optimized with SBA 2");
	return app.exec();
	#endif // SHOW_RECONSTRUCTION

	exit(0);
	}

