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

/// @file
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#include <qvsfm.h>
#include <QSet>

#ifndef DOXYGEN_IGNORE_THIS
double reconstructionError(const QVMatrix &Rt1, const QVMatrix &Rt2, const QVector<QPointFMatching> &matchings)
	{
	QList<QV3DPointF> points3D;
	foreach(QPointFMatching matching, matchings)
		points3D << linear3DPointTriangulation(matching, Rt1, Rt2);

	return reconstructionError(Rt1, Rt2, points3D, matchings);
	}
#endif // DOXYGEN_IGNORE_THIS

bool linearCameraPairInitialization(const QVector<QPointFMatching> &matchings, QVMatrix &Rt1, QVMatrix &Rt2)
	{
	QVMatrix E;
	if (not computeFundamentalMatrix(matchings, E))
		{
		/*#ifdef DEBUG
		std::cout << "[linearCameraPairInitialization] ERROR: could not compute essential matrix." << std::endl; 
		#endif // DEBUG*/
		return false;
		}

	// Get camera poses from the epipolar geometry.
	QVMatrix R1, R2;
	QV3DPointF t;
	getCameraPosesFromEssentialMatrix(E, R1, R2, t);

	/*#ifdef DEBUG
	QVMatrix U, V;
	QVVector sv;
	singularValueDecomposition(E, U, sv, V);
	std::cout << "[linearCameraPairInitialization] s2 for essential matrix = " << (sv[1]/sv[0]) << std::endl; 
	#endif // DEBUG*/

	Q_ASSERT(not R1.containsNaN());
	Q_ASSERT(not R2.containsNaN());
	Q_ASSERT(not t.containsNaN());

	const QVMatrix	sourceRt = (QVMatrix::identity(3)|QVVector(3,0.0)),
					destRt1 = R1|t,
					destRt2 = R1|t*(-1.0),
					destRt3 = R2|t,
					destRt4 = R2|t*(-1.0);

	// Test for significant 3D structure
	/*#ifdef DEBUG
	const double	errorCorrect = reconstructionError(sourceRt, destRt1, matchings),
					errorIncorrect = reconstructionError(destRt1, sourceRt, matchings);

	std::cout << "[linearCameraPairInitialization] Reconstruction errors: " << errorCorrect << "\t" << errorIncorrect << std::endl; 
	#endif // DEBUG*/

	// Test cheirality for the different possible destination camera poses using the first point correspondence.
	const QPointFMatching matching = matchings[0];

	int R1Correct = 0, R2Correct = 0, tPossitive = 0, tNegative = 0;
	//bool R1IsCorrect, tIsPossitive;

	foreach(QPointFMatching matching, matchings)
		{
		const bool	// for camera poses (I|0) and (R1|t)
				cheiralityTest1 = testCheiralityForCameraPoses(sourceRt, matching.first, destRt1, matching.second ),
				// for camera poses (I|0) and (R1|-t)
				cheiralityTest2 = testCheiralityForCameraPoses(sourceRt, matching.first, destRt2, matching.second ),
				// for camera poses (I|0) and (R2|t)
				cheiralityTest3 = testCheiralityForCameraPoses(sourceRt, matching.first, destRt3, matching.second ),
				// for camera poses (I|0) and (R2|-t)
				cheiralityTest4 = testCheiralityForCameraPoses(sourceRt, matching.first, destRt4, matching.second );

		// Test if there is more than one configuration with the correct cheirality.
		if (cheiralityTest1 + cheiralityTest2 +  cheiralityTest3 + cheiralityTest4 != 1)
			{
			/*#ifdef DEBUG
			std::cout << "[linearCameraPairInitialization] ERROR: number of camera pose combinations with correct cheirality is "  << (cheiralityTest1 + cheiralityTest2 +  cheiralityTest3 + cheiralityTest4) << std::endl; 
			#endif // DEBUG*/
			return false;
			}

		// Set the destination camera pose depending on which of them satisfies the cheirality test.
		if (cheiralityTest1)
			// Cheirality is satisfied only for camera poses (I|0) and (R1|t)
			{ R1Correct ++; tPossitive++; }
		else if	(cheiralityTest2)
			// Cheirality is satisfied only for camera poses (I|0) and (R1|-t)
			{ R1Correct ++; tNegative++;  }
		else if (cheiralityTest3)
			// Cheirality is satisfied only for camera poses (I|0) and (R2|t)
			{ R2Correct ++; tPossitive++;  }
		else if (cheiralityTest4)
			// Cheirality is satisfied only for camera poses (I|0) and (R2|-t)
			{ R2Correct ++; tNegative++; }
		}

	if ( (MIN(R1Correct, R2Correct) > 0) or (MIN(tPossitive, tNegative) > 0) )
		{
		/*#ifdef DEBUG
		std::cout << "[linearCameraPairInitialization] WARNING: points with different cheirality found." << std::endl; 
		std::cout << "[linearCameraPairInitialization]\t|R1 correct| =\t" << R1Correct << std::endl;
		std::cout << "[linearCameraPairInitialization]\t|R2 correct| =\t" << R2Correct << std::endl;  
		std::cout << "[linearCameraPairInitialization]\t|t possitive| =\t" << tPossitive << std::endl;
		std::cout << "[linearCameraPairInitialization]\t|t negative| =\t" << tNegative << std::endl;  
		#endif // DEBUG*/
		//return false;
		}

	const bool	R1IsCorrect = (R1Correct > R2Correct),
				tIsPossitive = (tPossitive > tNegative);

	// Init camera poses.
	Rt1 = QVMatrix::identity(3)|QV3DPointF(0.0, 0.0, 0.0);
	Rt2 = (R1IsCorrect?R1:R2)|(tIsPossitive?t:(t*-1.0));

	return true;
	}

QList< QHash< int, QPointF> > correctIntrinsics(const QList< QVMatrix > &Ks, const QList< QHash< int, QPointF> > &pointsProjections)
	{
	QList<QVMatrix> KsInv;
	foreach(QVMatrix K, Ks)
		KsInv << pseudoInverse(K);

	QList< QHash< int, QPointF> > result;

	QHash< int, QPointF> pointProjections;
	foreach(pointProjections, pointsProjections)
		{
		QHash< int, QPointF> correctedPointProjections;
		foreach(int numCamera, pointProjections.keys())
			correctedPointProjections[numCamera] = applyHomography(KsInv[MIN(Ks.count()-1, numCamera)], pointProjections[numCamera]);
		result << correctedPointProjections;
		}

	return result;
	}

bool testCheirality(const QList<QVCameraPose> cameraPoses, const QList< QHash< int, QPointF> > calibratedPointsProjections)
	{
	// Get the correct sign for the camera centers with the cheirality condition.
	const QList<int> cameraIndexesForPoint1 = calibratedPointsProjections.first().keys();
	const int	frame1 = cameraIndexesForPoint1[0],
			frame2 = cameraIndexesForPoint1[1];
			
	// Compose the new camera poses from the optimal rotations and the estimated camera centers.
	const QVCameraPose cameraPose0 = cameraPoses[frame1], cameraPose1 = cameraPoses[frame2];

	const bool cheiralityTest = testCheiralityForCameraPoses(	cameraPose0.toProjectionMatrix().getSubmatrix(0,2,0,3), calibratedPointsProjections[0][frame1],
									cameraPose1.toProjectionMatrix().getSubmatrix(0,2,0,3), calibratedPointsProjections[0][frame2]);
	return cheiralityTest;
	}

void invertCheirality(QList<QVCameraPose> &cameraPoses, QList<QV3DPointF> &points3D)
	{
	for(int i = 0; i < cameraPoses.count(); i++)
		cameraPoses[i] = QVCameraPose(cameraPoses[i].getOrientation(), -cameraPoses[i].getCenter());

	for(int i = 0; i < points3D.count(); i++)
		points3D[i] = -points3D[i];
	}

double reconstructionError(	const QList<QVCameraPose> &cameraPoses, const QList< QHash<int, QPointF> > &pointProjections, const QVector<bool> &evaluateTracking)
	{
	return reconstructionError(cameraPoses, linear3DPointsTriangulation(cameraPoses, pointProjections), pointProjections, evaluateTracking);
	}

double reconstructionError(	const QList<QVCameraPose> &cameraPoses, const QList< QHash<int, QPointF> > &pointProjections)
	{
	return reconstructionError(cameraPoses, linear3DPointsTriangulation(cameraPoses, pointProjections), pointProjections);
	}

#ifdef DEBUG
double reconstructionError2(	const QList<QVCameraPose> &cameraPoses,
								const QList<QV3DPointF> &points3D,
								const QList< QHash<int, QPointF> > &pointProjections)
	{
	int count = 0;
	double error = 0.0;
	for(int i = 0; i < pointProjections.size(); i++)
		foreach(int j, pointProjections[i].keys())
			{
			const QPointF p = pointProjections[i][j] -  cameraPoses[j].project(points3D[i]);

			error += p.x()*p.x() + p.y()*p.y();
			count+=2;
			}

	return sqrt(error / double(count));
	}
#endif // DEBUG

QVVector squaredReprojectionErrorResidualsNew(	const QV3DPointF &point3D,
												const QList<QVCameraPose> &cameraPoses,
												const QHash<int, QPointF> &pointProjections)
	{
	QVVector result;
	result.reserve(pointProjections.count() * 2);

	int count = 0;
	double error = 0.0;
	foreach(int j, pointProjections.keys())
		{
		const QPointF p = pointProjections[j] -  cameraPoses[j].project(point3D);

		result << p.x()*p.x();
		result << p.y()*p.y();
		}

	Q_ASSERT(result.count() == 2 * pointProjections.count() );

	return result;// / double(count);
	}

double squaredReprojectionErrorResiduals(	const QV3DPointF &point3D,
											const QList<QVCameraPose> &cameraPoses,
											const QHash<int, QPointF> &pointProjections)
	{
	int count = 0;
	double error = 0.0;
	foreach(int j, pointProjections.keys())
		{
		const QPointF p = pointProjections[j] -  cameraPoses[j].project(point3D);

		error += p.x()*p.x() + p.y()*p.y();
		count+=2;
		}

	Q_ASSERT(count == 2 * pointProjections.count() );

	return error;// / double(count);
	}

double squaredReprojectionErrorResiduals(	const QV3DPointF &point3D,
											const QVCameraPose &cameraPose,
											const QPointF &pointProjection)
	{
	const QPointF p = pointProjection -  cameraPose.project(point3D);
	return p.x()*p.x() + p.y()*p.y();
	}

double reconstructionError(	const QList<QVCameraPose> &cameraPoses,
							const QList<QV3DPointF> &points3D,
							const QList< QHash<int, QPointF> > &pointProjections)
	{
	int count = 0;
	double error = 0.0;
	for(int i = 0; i < pointProjections.size(); i++)
		{
		error += squaredReprojectionErrorResiduals(points3D[i], cameraPoses, pointProjections[i]);
		count += 2 * pointProjections[i].count();
		}

	const double re = sqrt(error / double(count));

	/*#ifdef DEBUG
	const double re2 = reconstructionError2(cameraPoses, points3D, pointProjections);
	Q_ASSERT( ABS(re - re2) / (re + re2) < 1e-5 );
	#endif // DEBUG*/

	return re;
	}

double reconstructionError(	const QList<QVCameraPose> &cameraPoses,
							const QList<QV3DPointF> &points3D,
							const QList< QHash<int, QPointF> > &pointProjections,
							const QVector<bool> &evaluateTracking)
	{
	Q_ASSERT(pointProjections.count() == evaluateTracking.count());
	int count = 0;
	double error = 0.0;
	for(int i = 0; i < pointProjections.size(); i++)
		if (evaluateTracking[i])
			{
			error += squaredReprojectionErrorResiduals(points3D[i], cameraPoses, pointProjections[i]);
			count += 2 * pointProjections[i].count();
			}

	if (count > 0)
		return sqrt(error / double(count));
	else
		return 0.0;
	}

double reconstructionError(const QVMatrix &Rt1, const QVMatrix &Rt2, const QList<QV3DPointF> &points3D, const QVector<QPointFMatching> &matchings)
	{
	double error = 0.0;
	int count = 0;
	for(int i = 0; i < matchings.size(); i++)
		{
		const QV3DPointF &point = points3D[i];
		const QPointFMatching &matching = matchings[i];

		const QPointF	p1 = matchings[i].first - Rt1 * point.homogeneousCoordinates(),
						p2 = matchings[i].second - Rt2 * point.homogeneousCoordinates();

		error += p1.x()*p1.x() + p1.y()*p1.y() + p2.x()*p2.x() + p2.y()*p2.y();
		count+=4;
		}
	return sqrt(error / double(count));
	}

QVVector reconstructionErrorResiduals(	const QList<QVCameraPose> &cameraPoses,
										const QList<QV3DPointF> &points3D,
										const QList< QHash<int, QPointF> > &pointTrackings)
	{
	QList<double> residuals;
	for(int i = 0; i < pointTrackings.size(); i++)
		foreach(int j, pointTrackings[i].keys())
			{
			const QPointF p = pointTrackings[i][j] -  cameraPoses[j].project(points3D[i]);

			residuals << p.x();
			residuals << p.y();
			}

	return residuals.toVector();
	}

// Devuelve TRUE si las poses de cámara contienen un valor NaN
bool checkForNaNValues(const QList<QVCameraPose> &cameraPoses)
	{
	int camerasNaN = 0;

	foreach(QVCameraPose cameraPose, cameraPoses)
		if(cameraPose.containsNaN())
			camerasNaN ++;

	if (camerasNaN > 0)
		std::cout << "[checkReconstructionForNaN] Error: found " << camerasNaN << " camera poses containing NaN values" << std::endl;

	return (camerasNaN == 0);
	}		

// Devuelve TRUE si los puntos 3D contienen un valor NaN
bool checkForNaNValues(const QList<QV3DPointF> &points3D)
	{
	int pointsNaN = 0;

	foreach(QV3DPointF point, points3D)
		if(point.containsNaN())
			pointsNaN ++;
		
	if (pointsNaN > 0)
		std::cout << "[checkReconstructionForNaN] Error: found " << pointsNaN << " 3D points containing NaN values" << std::endl;

	return (pointsNaN == 0);
	}		

// Devuelve TRUE si las projecciones contienen un valor NaN
bool checkForNaNValues(const QList< QHash< int, QPointF > > &pointTrackings)
	{
	int projectionsNaN = 0;

	for(int i = 0; i < pointTrackings.count(); i++)
		foreach(int j, pointTrackings[i].keys())
			if (isnan(pointTrackings[i][j].x()) or isnan(pointTrackings[i][j].y()))
				projectionsNaN++;

	if (projectionsNaN > 0)
		std::cout << "[checkReconstructionForNaN] Error: found " << projectionsNaN << " projections containing NaN values" << std::endl;

	return (projectionsNaN == 0);
	}

// Returns matchings from A to C.
QVector<QVIndexPair> combineMatchingLists(const QVector<QVIndexPair> &matchingsAB, const QVector<QVIndexPair> &matchingsBC)
	{
	QMap<int, int> mapBC;
	foreach(QVIndexPair m, matchingsBC)
		mapBC[m.first] = m.second;

	QList<QVIndexPair> matchingsAC;
	foreach(QVIndexPair m, matchingsAB)
		if (mapBC.contains(m.second))
			matchingsAC << QVIndexPair(m.first, mapBC[m.second]);

	#ifdef DEBUG
	QSet<int> A, B, C;
	// Test for bijection in mapping A<->B
	foreach(QVIndexPair m, matchingsAB)
		{
		Q_ASSERT(not A.contains(m.first));
		Q_ASSERT(not B.contains(m.second));
		A << m.first;
		B << m.second;
		}

	// Test for bijection in mapping B<->C
	B.clear();
	C.clear();
	foreach(QVIndexPair m, matchingsBC)
		{
		Q_ASSERT(not B.contains(m.first));
		Q_ASSERT(not C.contains(m.second));
		B << m.first;
		C << m.second;
		}

	// Test for bijection in mapping A<->C
	A.clear();
	C.clear();
	foreach(QVIndexPair m, matchingsAC)
		{
		Q_ASSERT(not A.contains(m.first));
		Q_ASSERT(not C.contains(m.second));
		A << m.first;
		C << m.second;
		}
	#endif // DEBUG	

	return matchingsAC.toVector();
	}

void estimate3DPointsMeanAndVariance(const QList<QV3DPointF> &points3D, QV3DPointF &mean, double &variance)
	{
	mean = QV3DPointF(0.0, 0.0, 0.0);

	foreach(QV3DPointF point3D, points3D)
		mean = mean + point3D;

	mean = mean / points3D.count();

	variance = 0;
	foreach(QV3DPointF point3D, points3D)
		variance += (point3D - mean) * (point3D - mean);

	variance = sqrt(variance) / points3D.count();
	}

