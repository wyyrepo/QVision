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

This program tests the performance and accuracy of the GEA optimization algorithm on a SfM reconstruction.

The performance of the GEA algorithm will vary largely depending on the selected method to solve the second level system on the Levenberg-Marquardt optimization.
Note that to use MKL or CHOLMOD sparse solvers with GEA (which offer good performance by exploiting the sparsity of the problem) QVision must be compiled and configured with MKL, CHOLMOD, and/or ROS libraries compatibility.
See 'config.pri' file for more details.

@section Usage
Simply compile, and execute the binary:
\code
	./testGEA <reconstruction_file_or_path> [iterations] [lambda_gea]
\endcode

See the documentation of function @ref readSfMReconstruction for more information about the possible SfM reconstruction file formats.

@author PARP Research Group. University of Murcia, Spain.
*/

// Uncomment the line below to show the initial and the optimized reconstruction.
#define SHOW_RECONSTRUCTION

#include <QVApplication>
#include <QTime>
#include <qvsfm.h>
#include <sfmviewer.h>

#ifndef QVSSBA_AVAILABLE
#undef TEST_sSBA
#endif

#ifdef QVSSBA_AVAILABLE
#include <qvros.h>
#endif

/*
GEA cost error simplification method for on-line camera pose optimization.

This function reduces the number of terms in the GEA cost error. This produces a large speed-up in the computational cost of each
Levenberg-Marquardt step, without a significant loss in the error correction obtained.

Params 'k_param' and 's_param' control the number of coefficient matrices (terms in the GEA cost error)
for each view that are included in the simplified version of the GEA cost error:

Coefficient matrices which relate two views that are closer in the video sequence than 's_param' are always included
in the simplified version of the GEA cost error. These are considered camera tracking pair-wise relationships.

The parameter 'k_param' is the maximal number of loop-closing terms (which are not camera tracking terms) for each view
that are included in the simplified version of the GEA error.

More information about this method can be found at:
	http://perception.inf.um.es/gea
*/
void onlineGEACostErrorSimplification(const int numCameras, QVDirectedGraph< QVector<QPointFMatching> > &pointLists,
				const int k_param = 10,
				const int s_param = 10)
	{
	QVector< QMap<int, int> > sortedUnusedCorrespondences(numCameras);

	// Keep the coefficient matrices relating views that are close in the video sequence.
	QVDirectedGraph< QVector<QPointFMatching> > newPointLists;
	foreach(QPoint link, pointLists.keys())
		{
		const int sourceView = link.x(), destView = link.y();

		const QVector<QPointFMatching> &pointList = pointLists[ link ];
		if (ABS(sourceView - destView) <= s_param)
			newPointLists [ QPoint(sourceView, destView) ] = pointList;
		else
 			sortedUnusedCorrespondences [ sourceView ].insertMulti(-pointList.count(), destView);
		}

	// Keep coefficient matrices corresponding to long-term/loop-closing matchings.
	for(int sourceView = 0; sourceView < numCameras; sourceView++)
		foreach(int destView, sortedUnusedCorrespondences[sourceView].values().mid(0, k_param))
			newPointLists[ QPoint(sourceView,destView) ] = pointLists[ QPoint(sourceView,destView) ];

	pointLists = newPointLists;
	}

int links = 0;
// Optimize a reconstruction using GEA.
// No initial 3D points are needed. Only initial camera poses and point projections.
int dull_time_gea = 0;
void GEAOptimization(	const QList<QVCameraPose> initialCameraPoses,
			const QList<QHash<int, QPointF> > pointProjections,
			const int iterations,
			const double lambda,
			const bool dynamicLambda,
			const int k_param,
			const int s_param,
			QList<QV3DPointF> &refinedPoints3D,
			QList<QVCameraPose> &refinedCameras,
			int &time_GEA = dull_time_gea,
			const TGEA_decomposition_method decomposition_method = GEA_CHOLESKY_DECOMPOSITION,
			const TQVSparseSolve_Method solveMethod = DEFAULT_TQVSPARSESOLVE_METHOD,
			const int secondLevelIterations = 10
			)
	{
	// MKL sparse solve routine usually spends some time warming-up in the first call. Calling this
	// function before starting the GEA optimization avoids including this small warming-up time in
	// the performance evaluation.
	#ifdef MKL_AVAILABLE
	cold_start_mkl_initialization();
	#endif

	QTime time, totalTime;

	// 1. Obtain a list of point matchings between each view-pair in the reconstruction, from the 3D point
	// projections container 'pointProjections'. Usually SfM systems obtain first the 2D point trackings,
	// and latter the 3D point projections from these lists of point matchings between the view pairs.
	// This is why this time is not included in the GEA total performance time.
	time.start();
	QVDirectedGraph< QVector<QPointFMatching> > pointLists = getPointMatchingsListsVec( pointProjections, initialCameraPoses.count() );
	int gea_time_pointlists = time.elapsed();

	totalTime.start();

	onlineGEACostErrorSimplification(initialCameraPoses.count(), pointLists, k_param, s_param);

	std::cout << "Number of terms in the GEA cost error = " << pointLists.count() << std::endl;

	// --------------------------------
	int countLink = 0;
	QVector<QPointFMatching> temp;
	foreach(temp, pointLists)
		if (temp.count() >= 9)
			countLink++;
	// --------------------------------

	//links = pointLists.count();
	links = countLink;

	// 2. Get reduced matrices from the point matchings lists.
	time.start();
	const QVDirectedGraph<QVMatrix> reducedMatricesgraph = getReducedMatrices(pointLists, false, decomposition_method, true, 1e-6);
	int gea_time_RMM = time.elapsed();

	// 3. Apply LM optimization with the reduced matrices and the initial camera poses.
	refinedCameras = globalEpipolarAdjustment(iterations, initialCameraPoses, reducedMatricesgraph, lambda, dynamicLambda, solveMethod, secondLevelIterations);

	// 4. Triangulate 3D points from the estimated camera poses.
	time.start();
	refinedPoints3D = linear3DPointsTriangulation(refinedCameras, pointProjections);
	const int gea_time_LT = time.elapsed();
	const int totalTime_GEA = totalTime.elapsed();

	// 5. Print performance times.
	std::cout	<< "[GEA] Time point matchings lists: " << gea_time_pointlists
			<< " ms\tRMM: " << gea_time_RMM
			<< " ms\tEvaluation: " << gea_time_eval
			<< " ms\tSolve: " << gea_time_solve
			<< " ms\tLT: " << gea_time_LT
			<< " ms" << std::endl;
	std::cout << "[GEA] Time total (RMM + Evaluation + Solve + LT) =\t" << totalTime_GEA << " ms." << std::endl;

	time_GEA = totalTime_GEA;
	}

// Print the number of cameras, 3D points, projections and some statistics from a SfM reconstruction.
void printReconstructionStats(	const QList<QVCameraPose> &cameraPoses,
				const QList<QV3DPointF> &points3D,
				const QList< QHash< int, QPointF> > &pointsProjections)
	{
	const int numCameras = cameraPoses.count(), numPoints = points3D.count();
	int numProjections = 0;
	QHash< int, QPointF> temp;
	foreach(temp, pointsProjections)
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
		std::cout << "Usage: " << std::endl << "\t" << argv[0] << " <data_set_path> [iterations] [lambda] [k param] [s param]"
			<< std::endl << std::endl;
		exit(0);
		}

	const QString path = app.getArgument(1);

	// 2. Set the number of iterations, and lambda values for the GEA and sSBA optimizations, if provided as parameters through the command line.
	bool iters_OK = true, lambda_gea_OK = true, k_param_OK = true, s_param_OK = true;

	const int iters =			(app.getNumberOfArguments() < 3)? 1 : app.getArgument(2).toInt(&iters_OK);
	const double lambda_gea =	(app.getNumberOfArguments() < 4)? 1.0 : app.getArgument(3).toDouble(&lambda_gea_OK);
	const double k_param =		(app.getNumberOfArguments() < 5)? 10000000 : app.getArgument(4).toInt(&k_param_OK);
	const double s_param =		(app.getNumberOfArguments() < 6)? 10000000 : app.getArgument(5).toInt(&s_param_OK);

	if (not iters_OK)
		{
		std::cout << "[main] Error reading number of iterations." << std::endl;
		exit(0);
		}
	else
		std::cout << "[main] Number of iterations = " << iters << std::endl;

	if (not lambda_gea_OK)
		{
		std::cout << "[main] Error reading lambda for GEA optimization" << std::endl;
		exit(0);
		}
	else
		std::cout << "[main] Lambda for GEA = " << lambda_gea << std::endl;

	if (not k_param_OK)
		{
		std::cout << "[main] Error reading 'k' param for GEA cost error simplification" << std::endl;
		exit(0);
		}
	else
		std::cout << "[main] Value for 'k' parameter = " << k_param << std::endl;

	if (not s_param_OK)
		{
		std::cout << "[main] Error reading 's' param for GEA cost error simplification" << std::endl;
		exit(0);
		}
	else
		std::cout << "[main] Value for 's' parameter = " << s_param << std::endl;

	// 3. Read SfM reconstruction from the specified path.
	QList<QV3DPointF> points3D;
	QList<QVCameraPose> cameraPoses;
	QList<QVMatrix> cameraCalibrations;
	QList< QHash< int, QPointF> > pointsProjections;

	if( not readSfMReconstruction(path, cameraCalibrations, cameraPoses, points3D, pointsProjections) )
		{
		std::cout << "[main] Error: could not read SfM reconstruction from path '" << qPrintable(path) << "'." << std::endl;
		return 0;
		}

	// 4. Correct camera intrinsic calibrations from point projections.
	const QList< QHash< int, QPointF> > calibratedPointsProjections = correctIntrinsics(cameraCalibrations, pointsProjections);

	// 5. Correct camera cheirality.
	if (testCheirality(cameraPoses, calibratedPointsProjections))
		invertCheirality(cameraPoses, points3D);

	// 6. Print SfM reconstruction stats.
	std::cout << "[main] Reconstruction loaded."<< std::endl;	
	printReconstructionStats(cameraPoses, points3D, calibratedPointsProjections);

	// 8. Perform GEA optimization on the reconstruction.
	// Uncomment one of the following lines, depending on the decomposition you want to use in the tests.
		//#define REDUCED_MATRIX_DECOMPOSITION	GEA_DO_NOT_DECOMPOSE		// Do not apply any decomposition. Use \f$ M^T M \f$ as is.
		#define REDUCED_MATRIX_DECOMPOSITION	GEA_CHOLESKY_DECOMPOSITION	// Use Cholesky decomposition.
		//#define REDUCED_MATRIX_DECOMPOSITION	GEA_EIGEN_DECOMPOSITION		// Use eigen decomposition.

	// Uncomment one of the following lines to select the method to solve the LM second level system.
		//#define	SPARSE_SOLVE_METHOD QVMKL_DSS		// Use MKL sparse direct solver
		//#define	SPARSE_SOLVE_METHOD QVCHOLMOD_DSS	// Use CHOLMOD sparse direct solver
		#define	SPARSE_SOLVE_METHOD QV_BJPCG			// Block-Jacobi preconditioned conjugate gradient
		//#define	SPARSE_SOLVE_METHOD QV_DENSE		// Solve using non-sparse method.

	int time_GEA;
	QList<QV3DPointF> points3D_GEA;
	QList<QVCameraPose> cameraPoses_GEA;
	GEAOptimization(cameraPoses, calibratedPointsProjections, iters, lambda_gea, false, k_param, s_param, points3D_GEA, cameraPoses_GEA,
			time_GEA, REDUCED_MATRIX_DECOMPOSITION, SPARSE_SOLVE_METHOD, 30);

	QHash< int, QPointF> temp;
	int count = 0;
	foreach(temp, pointsProjections)
		count += temp.count();
	std::cout << "Number of views = " << cameraPoses.count() << std::endl;
	std::cout << "Number of points = " << points3D.count() << std::endl;
	std::cout << "Number of projections = " << count << std::endl;

	// 9. Print errors and total performance times.
	std::cout << "[main] Initial error\t" << 1000.0 * reconstructionError(cameraPoses, points3D, calibratedPointsProjections) << std::endl;
	std::cout << "[main] GEA error/time\t" << 1000.0 * reconstructionError(cameraPoses_GEA, points3D_GEA, calibratedPointsProjections) << "\t" << double(time_GEA) / 1000.0 << " s" << std::endl;

	#ifdef SHOW_RECONSTRUCTION
	SfMViewer originalMap(cameraPoses, points3D, "Original reconstruction");
	SfMViewer geaOptimizedMap(cameraPoses_GEA, points3D_GEA, "Reconstruction optimized with GEA");
	return app.exec();
	#endif // SHOW_RECONSTRUCTION

	exit(0);
	}

