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

#include <qvprojective.h>
#include <qvmatrixalgebra.h>
#include <qvdefines.h>
#include <qvmath.h>
#include <float.h>
#include <qvnumericalanalysis.h>

/// @file
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.
void homogenizePoints(const QList< QPointFMatching > &matchings, QVMatrix &premult, QVMatrix &postmult, QList< QPointFMatching > &homogeneizedPairs)
    {
    // 0. Fast normalization (similar to DLT, but based on min and max values
    // of X and Y, instead of mean value and normalized mean distance to
    // centroid equal to sqrt(2). Hartley-Zisserman 2nd ed. pag 109.
    float minXS=FLT_MAX, maxXS=-FLT_MAX, minYS=FLT_MAX, maxYS=-FLT_MAX,
          minXD=FLT_MAX, maxXD=-FLT_MAX, minYD=FLT_MAX, maxYD=-FLT_MAX;

    //QPair<QPointF, QPointF> matching;
    foreach(QPointFMatching matching, matchings)
        {
        minXS = MIN(matching.first.x(), minXS);
        maxXS = MAX(matching.first.x(), maxXS);
        minYS = MIN(matching.first.y(), minYS);
        maxYS = MAX(matching.first.y(), maxYS);

        minXD = MIN(matching.second.x(), minXD);
        maxXD = MAX(matching.second.x(), maxXD);
        minYD = MIN(matching.second.y(), minYD);
        maxYD = MAX(matching.second.y(), maxYD);
        }

    // This is to avoid possible div by zero in degenerate conditions:
    if(fabs(minXS-maxXS) < EPSILON)
        maxXS += 1.0;
    if(fabs(minYS-maxYS) < EPSILON)
        maxYS += 1.0;
    if(fabs(minXD-maxXD) < EPSILON)
        maxXD += 1.0;
    if(fabs(minYD-maxYD) < EPSILON)
        maxYD += 1.0;

    minXS = 0; maxXS = 320;
    minYS = 0; maxYS = 240;

    //QPair<QPointF, QPointF> matching;
    foreach(QPointFMatching matching, matchings)
        {
        const double	x = (matching.first.x()-(maxXS+minXS)/2)/(maxXS-minXS),
                y = (matching.first.y()-(maxYS+minYS)/2)/(maxYS-minYS),
                x_p = (matching.second.x()-(maxXD+minXD)/2)/(maxXD-minXD),
                y_p = (matching.second.y()-(maxYD+minYD)/2)/(maxYD-minYD);

        homogeneizedPairs.append(QPointFMatching(QPointF(x,y),QPointF(x_p,y_p)));
        }

    const double	dataPremult[9] = {
                    1/(maxXS-minXS),	0,			-(maxXS+minXS)/(2*(maxXS-minXS)),
                    0,			1/(maxYS-minYS),	-(maxYS+minYS)/(2*(maxYS-minYS)),
                    0,			0,			1
                    },
            dataPostmult[9] = {
                    maxXD-minXD,	0,		(maxXD+minXD)/2,
                    0,		maxYD-minYD,	(maxYD+minYD)/2,
                    0, 		0, 		1,
                    };

    premult = QVMatrix(3,3, dataPremult);
    postmult = QVMatrix(3,3, dataPostmult);
    }


QVMatrix getPlanarTransferDLTCoefficientMatrix(const QList<QPointFMatching> &matchings)
    {
	// 1. Obtain coeficient matrix for the system:
	//	Ax = 0
	QVMatrix A(3*matchings.size(),9);
	double *ptrA = A.getWriteData();

	for (int n = 0; n < matchings.size(); n++)
		{
		const QPointFMatching matching = matchings.at(n);
		const double	x = matching.first.x(),
						y = matching.first.y(),
						xp = matching.second.x(),
						yp = matching.second.y(),
						x_xp = x*xp,
						x_yp = x*yp,
						y_xp = y*xp,
						y_yp = y*yp;

		ptrA[0] = 0;		ptrA[1] = 0;		ptrA[2] = 0;
		ptrA[3] = -x;		ptrA[4] = -y;		ptrA[5] = -1;
		ptrA[6] = x_yp;		ptrA[7] = y_yp;		ptrA[8] = yp;

		ptrA[9] = x;		ptrA[10] = y;		ptrA[11] = 1;
		ptrA[12] = 0;		ptrA[13] = 0;		ptrA[14] = 0;
		ptrA[15] = -x_xp;	ptrA[16] = -y_xp;	ptrA[17] = -xp;

		ptrA[18] = -x_yp;	ptrA[19] = -y_yp;	ptrA[20] = -yp;
		ptrA[21] = x_xp;	ptrA[22] = y_xp;	ptrA[23] = xp;
		ptrA[24] = 0;		ptrA[25] = 0;		ptrA[26] = 0;

		ptrA += 27;
		}

	return A;
    }

// From section 4.1 of 'Multiple View Geometry in Computer Vision'.
bool computeProjectiveHomography(const QList< QPointFMatching > &matchings, QVMatrix &H)
	{
	if (matchings.size() < 4)
		return false;

	// 0. Fast normalization (similar to DLT, but based on min and max values
	// of X and Y, instead of mean value and normalized mean distance to
	// centroid equal to sqrt(2). Hartley-Zisserman 2nd ed. pag 109.
	QList< QPointFMatching > homogeneizedPairs;
	QVMatrix premult, postmult;

	homogenizePoints(matchings, premult, postmult, homogeneizedPairs);

	const QVMatrix A = getPlanarTransferDLTCoefficientMatrix(homogeneizedPairs);

	// 2. Solve the homogeneous system.
	const QVMatrix AtA = A.dotProduct(A, true, false);

	QVMatrix U, V;
	QVVector s;
	singularValueDecomposition(AtA, U, s, V, DEFAULT_TQVSVD_METHOD);

	// 3. Rearrange elements of vector 'x' in a 3x3 matrix.
	QVMatrix homography(3,3,  V.getCol(8));

	// 4. De-normalize homography back:
	homography = (postmult * homography) * premult;
	homography = homography / homography(2,2);

	H = homography;
	return true;
	}

// From section 4.1 of 'Multiple View Geometry in Computer Vision'.
bool computeProjectiveHomography2(const QList< QPointFMatching > &matchings, QVMatrix &H)
    {
    if (matchings.size() < 4)
		return false;

    // 0. Fast normalization (similar to DLT, but based on min and max values
    // of X and Y, instead of mean value and normalized mean distance to
    // centroid equal to sqrt(2). Hartley-Zisserman 2nd ed. pag 109.
    QList< QPointFMatching > homogeneizedPairs;
    QVMatrix premult, postmult;

    homogenizePoints(matchings, premult, postmult, homogeneizedPairs);

    // 1. Obtain coeficient matrix for the system:
    //	Ax = 0
    QVMatrix A(3*homogeneizedPairs.size(),9);
    for (int n = 0; n < homogeneizedPairs.size(); n++)
        {
        const QPointFMatching matching = homogeneizedPairs.at(n);
        const double	x = matching.first.x(),
                y = matching.first.y(),
                x_p = matching.second.x(),
                y_p = matching.second.y();

        const double coefsMatrixData[3 * 9] = {

                0,		0, 		0,
                -x,		-y, 		-1,
                x*y_p,		y*y_p, 		y_p,

                x,		y, 		1,
                0,		0, 		0,
                -x*x_p,		-y*x_p,		-x_p,

                -x*y_p,		-y*y_p,		-y_p,
                x*x_p,		y*x_p, 		x_p,
                0,		0, 		0
                };

        const QVMatrix coefsMatrix(3,9, coefsMatrixData);

        A.setRow(3*n+0, coefsMatrix.getRow(0));
        A.setRow(3*n+1, coefsMatrix.getRow(1));
        A.setRow(3*n+2, coefsMatrix.getRow(2));
        }

    // 2. Solve the homogeneous system.
    QVVector x(9);

    solveHomogeneous(A, x);

    // 3. Rearrange elements of vector 'x' in a 3x3 matrix.
    QVMatrix homography = QVMatrix(x.mid(0,3)) & QVMatrix(x.mid(3,3)) & QVMatrix(x.mid(6,3));

    // 4. De-normalize homography back:
    homography = (postmult * homography) * premult;
    homography = homography / homography(2,2);

    H = homography;
	return true;
    }

QVMatrix computeAffineHomography(const QList< QPointFMatching > &matchings)
    {
    Q_ASSERT(matchings.size() >= 3);

    // 0. Fast normalization (similar to DLT, but based on min and max values
    // of X and Y, instead of mean value and normalized mean distance to
    // centroid equal to sqrt(2). Hartley-Zisserman 2nd ed. pag 109.
    QList< QPointFMatching > homogeneizedPairs;
    QVMatrix premult, postmult;

    homogenizePoints(matchings, premult, postmult, homogeneizedPairs);

    // 1. Obtain coeficient matrix for the system:
    //	Ax = b
    QVMatrix A(2*homogeneizedPairs.size(),6);
    QVVector b(2*homogeneizedPairs.size());

    for (int n = 0; n < homogeneizedPairs.size(); n++)
        {
        const QPointFMatching matching = homogeneizedPairs.at(n);
        const double	x = matching.first.x(),
                y = matching.first.y(),
                x_p = matching.second.x(),
                y_p = matching.second.y();

        const double coefsMatrixData[2 * 6] = {
                x,	y, 	1,	0,	0, 	0,
                0,	0,	0,	x,	y,	1
                };

        const QVMatrix coefsMatrix(2,6, coefsMatrixData);

        A.setRow(2*n+0, coefsMatrix.getRow(0));
        A.setRow(2*n+1, coefsMatrix.getRow(1));
        b[2*n+0] = x_p;
        b[2*n+1] = y_p;
        }

    // 2. Solve the linear system.
    const QVVector x = pseudoInverse(A)*b;

    // 3. Rearrange elements of vector 'x' in a 3x3 matrix.
    const QVMatrix M = QVMatrix(x.mid(0,3)) & QVMatrix(x.mid(3,3)) & (QVVector(2,0.0) << 1);

    // 4. De-normalize homography back:
    return (postmult * M) * premult;
    }

QVMatrix computeSimilarHomography(const QList< QPointFMatching > &matchings)
    {
    if (matchings.size() < 2)
        return QVMatrix::identity(3);

    QPointF meanSource(0.0, 0.0), meanDestination(0.0, 0.0);
    foreach(QPointFMatching matching, matchings)
        {
        meanSource = meanSource + matching.first;
        meanDestination = meanDestination + matching.second;
        }

    meanSource = meanSource / double(matchings.size());
    meanDestination = meanDestination / double(matchings.size());

    QVVector angles, scales;
    foreach(QPointFMatching matching, matchings)
        {
        const QPointF	source = matching.first - meanSource,
                destination = matching.second - meanDestination;

        angles << qvAngle(destination, source);
        scales << norm2(destination) / norm2(source);
        }

    return	QVMatrix::translationMatrix(meanDestination.x(), meanDestination.y()) *
        QVMatrix::rotationMatrix(angles.median()) * QVMatrix::scaleMatrix(scales.median()) *
        QVMatrix::translationMatrix(-meanSource.x(), -meanSource.y());
    }

/* Funciona, pero da matrices distintas a cvFindFundamentalMat
QVMatrix ComputeFundamentalMatrix(const QList< QPair<QPointF, QPointF> > &matchings)
    {
    Q_ASSERT(matchings.size() >= 8);
    const int num_points = matchings.size();

    // 1. Obtain coeficient matrix for the system:
    //	Ax = 0
    QVMatrix A(matchings.size(),9);

    for (int n=0; n<matchings.size(); n++)
        {
        const QPointFMatching matching = matchings[n];
        const double	x = matching.first.x(), y = matching.first.y(),
                x_p = matching.second.x(), y_p = matching.second.y();

        A.setRow(n, QVVector(9, (double [9]){ x*x_p, y*x_p, x_p, x*y_p, y*y_p, y_p, x, y, 1 }));
        }

    // 2. Solve the homogeneous system.
    QVVector x(9);
    solveHomogeneous(A, x);

    // 3. Rearrange elements of vector 'x' in a 3x3 matrix.
    QVMatrix homography(3,3);
    homography(0,0) = x[0];	homography(0,1) = x[1];	homography(0,2) = x[2];
    homography(1,0) = x[3];	homography(1,1) = x[4];	homography(1,2) = x[5];
    homography(2,0) = x[6];	homography(2,1) = x[7];	homography(2,2) = x[8];

    return homography;
    }*/

// Returns M = DLT matrix
QVMatrix get8PointsCoefficientMatrix(const QList<QPointFMatching> &matchings, const bool normalize)
        {
        QVMatrix A(matchings.size(),9);
        double *aptr = A.getWriteData();

        foreach(QPointFMatching matching,matchings)
                {
                //const QPointF sourcePoint = matchings[i].first, destPoint = matchings[i].second;
                //const QPointF sourcePoint = matching.first, destPoint = matching.second;
                //double	x = sourcePoint.x(), y = sourcePoint.y(),
        //	x_p = destPoint.x(), y_p = destPoint.y(),
        //	normalizer = 1.0/sqrt((x*x + y*y +1)*(x_p*x_p+y_p*y_p+1)),
        //	x_ = x * normalizer, y_ = y * normalizer;

                const QPointF sourcePoint = matching.first, destPoint = matching.second;
        const double	x = sourcePoint.x(), y = sourcePoint.y(),
                x_p = destPoint.x(), y_p = destPoint.y(),
                normalizer = normalize?1.0/sqrt((x*x + y*y +1)*(x_p*x_p+y_p*y_p+1)):1.0,
                x_ = x * normalizer, y_ = y * normalizer;
                // Faster:
                *aptr = x_*x_p;		aptr++;
                *aptr = y_*x_p;		aptr++;
                *aptr = normalizer*x_p;	aptr++;
                *aptr = x_*y_p;		aptr++;
                *aptr = y_*y_p;		aptr++;
                *aptr = normalizer*y_p;	aptr++;
                *aptr = x_;		aptr++;
                *aptr = y_;		aptr++;
                *aptr = normalizer;	aptr++;
                }
        return A;
        }

QVMatrix getTransposeProductOf8PointsCoefficientMatrix(const QList<QPointFMatching> &matchings, const bool normalize)
        {
		QVMatrix A(9,9, 0.0);
		double *ptrA = A.getWriteData();

        foreach(QPointFMatching matching,matchings)
                {
		        double v[9];
                const QPointF sourcePoint = matching.first, destPoint = matching.second;
		        const double	x = sourcePoint.x(), y = sourcePoint.y(),
				                x_p = destPoint.x(), y_p = destPoint.y(),
     				           normalizer = normalize?1.0/sqrt((x*x + y*y +1)*(x_p*x_p+y_p*y_p+1)):1.0,
				                x_ = x * normalizer, y_ = y * normalizer;

                // Faster:
		        v[0] = x_*x_p;
                v[1] = y_*x_p;
                v[2] = normalizer * x_p;
                v[3] = x_*y_p;
                v[4] = y_*y_p;
                v[5] = normalizer * y_p;
                v[6] = x_;
                v[7] = y_;
                v[8] = normalizer;

				for(int i = 0; i < 9; i++)
				    for(int j = 0; j <= i; j++)
				        ptrA[9*i+j] += v[i] * v[j];
                }

		// Only store lower diagonal values
		for(int i = 0; i < 9; i++)
			for(int j = i+1; j < 9; j++)
			        ptrA[9*i+j] = ptrA[9*j+i];

        return A;
        }

QVMatrix getReduced8PointsCoefficientsMatrix(	const QList<QPointFMatching> &matchingsList,
                        const TGEA_decomposition_method decomposition_method,
                        const bool normalize,
                        const bool use_gsl,
                        const double choleskyLambda)
    {
    if (matchingsList.count() > 9)
        {
        QVMatrix MtM = getTransposeProductOf8PointsCoefficientMatrix(matchingsList, normalize);

        switch(decomposition_method)
            {
            case GEA_DO_NOT_DECOMPOSE:
                return MtM;
                break;

            case GEA_CHOLESKY_DECOMPOSITION:
                {
                QVMatrix L;

                // Add lambda to MtM diagonal values to avoid
                // non-positive definite matrix errors.
                if (choleskyLambda != 0.0)
                    {
                    const int n = MtM.getCols();
                    double *data = MtM.getWriteData();
                    for(int i = 0, idx = 0; i < n; i++, idx += n+1)
                        data[idx] += choleskyLambda;
                    }

                CholeskyDecomposition(MtM, L, use_gsl?GSL_CHOLESKY:LAPACK_CHOLESKY_DPOTRF);

                return L;
                }
                break;

            case GEA_EIGEN_DECOMPOSITION:
                {
                QVMatrix Q;
                QVVector lambda;

                eigenDecomposition(MtM, lambda, Q, use_gsl?GSL_EIGENSYMM:LAPACK_DSYEV);

                // Square of the elements for vector Lambda.
                double	*dataLambda = lambda.data();
                for(int i=0; i<lambda.size(); i++)
                    dataLambda[i] = sqrt(fabs(dataLambda[i]));

                // Este código obtiene la matriz 'Q*diag(lambda)', en la variable 'Q'.
                double	*dataQ = Q.getWriteData();
                const int cols = Q.getCols(), rows = Q.getRows();
                for(int i = 0, idx = 0; i < rows; i++)
                    for(int j = 0; j < cols; j++, idx++)
                        dataQ[idx] *= dataLambda[j];

                return Q;
                }
                break;
            }
        }
    return get8PointsCoefficientMatrix(matchingsList, normalize).transpose();
    }

QVMatrix computeFundamentalMatrix(const QList<QPointFMatching> &matchings, const bool normalize)
    {
    std::cout << "WARNING: 'QVMatrix computeFundamentalMatrix(const QList<QPointFMatching> &, const bool)' deprecated. Use 'bool computeFundamentalMatrix(const QVector<QPointFMatching> &, QVMatrix &, const TQVSVD_Method)' instead." << std::endl;
    if (matchings.count() < 8)
        return QVMatrix();

    // Compute centers and average distances for each of the two point sets
    QPointF m0c(0.0, 0.0), m1c(0.0, 0.0);
    foreach(QPointFMatching matching, matchings)
        {
        m0c += matching.first;
        m1c += matching.second;
        }

    const int count = matchings.count();
    m0c /= count;
    m1c /= count;

    double scale0 = 0.0, scale1 = 0.0;
    foreach(QPointFMatching matching, matchings)
        {
        scale0 += norm2(matching.first - m0c);
        scale1 += norm2(matching.second - m1c);
        }

    // Check if the projections scales is significantly greater than zero.
    //if( scale0 < DBL_EPSILON or scale1 < DBL_EPSILON )
    //	return QVMatrix();

    scale0 = count * sqrt(2.) /scale0;
    scale1 = count * sqrt(2.) /scale1;

    // Correct point correspondences centers and average distances.
    QList<QPointFMatching> correctedMatchings;
    foreach(QPointFMatching matching, matchings)
        correctedMatchings << QPointFMatching( (matching.first - m0c)*scale0, (matching.second - m1c)*scale1);

    // Solve MtM x = 0 to get a linear F.
    QVMatrix U, V;
    QVVector s;

    singularValueDecomposition(getTransposeProductOf8PointsCoefficientMatrix(correctedMatchings, normalize), U, s, V, DEFAULT_TQVSVD_METHOD);

    // Check that first seven singular values differ from zero.
    //for(int i = 0; i < 7; i++)
    //	if (s[i] < DBL_EPSILON)
    //		return QVMatrix();

    // Decompose linear F with SVD.
    singularValueDecomposition(QVMatrix(3,3, V.getCol(8)), U, s, V, DEFAULT_TQVSVD_METHOD);

    // Re-compose F truncating the third singular value, and correcting the whitening of the point correspondences
    const QVMatrix	Q1 = QVMatrix::cameraCalibrationMatrix(scale0, 1.0, -scale0*m0c.x(), -scale0*m0c.y()),
		            Q2 = QVMatrix::cameraCalibrationMatrix(scale1, 1.0, -scale1*m1c.x(), -scale1*m1c.y());

    s[2] = 0.0;

    QVMatrix result = Q2.transpose() * U * QVMatrix::diagonal(s) * V.transpose() * Q1;

    // Todo: Some functions will not work properly if values are not cast to float. ¿Porqué?
    for(int j = 0; j < 3; j++ )
        for(int k = 0; k < 3; k++ )
            result(j,k) = float(result(j,k));

    return result;
    }

#ifdef QVOPENCV
QVMatrix cvFindFundamentalMat(const QList<QPointFMatching> &matchings)
    {
    const int point_count = matchings.size();

    CvMat	*points1 = cvCreateMat(1,point_count,CV_32FC2),
        *points2 = cvCreateMat(1,point_count,CV_32FC2);

    for(int i = 0; i < point_count; i++)
        {
        points1->data.fl[i*2] = matchings[i].first.x();
        points1->data.fl[i*2+1] = matchings[i].first.y();
        points2->data.fl[i*2] = matchings[i].second.x();
        points2->data.fl[i*2+1] = matchings[i].second.y();
        }

    CvMat *fundamental_matrix = cvCreateMat(3,3,CV_32FC1);

    const int fm_count = cvFindFundamentalMat(points1, points2, fundamental_matrix, CV_FM_8POINT);
    const QVMatrix result = fundamental_matrix;

    // delete points1 matrix, points2 matrix.
    cvReleaseMat(&points1);
    cvReleaseMat(&points2);

    // delete fundamental_matrix
    cvReleaseMat(&fundamental_matrix);

    return (fm_count == 1)?result:QVMatrix();
    }
#endif

/*void getMeanDirection(const QVMatrix m, QVVector &mean, QVVector &direction)
    {
    mean = m.meanCol();
    QVMatrix centeredM = m;
    for (int i = 0; i < centeredM.getCols(); i++)
        centeredM.setCol(i, centeredM.getCol(i) - mean);

    // 1. Compute main direction vector.
    QVMatrix eigVecs;
    QVVector eigVals;
        EigenDecomposition(centeredM * centeredM.transpose(), eigVals, eigVecs);

    direction = QVVector(eigVecs.getCols());
    for (int i = 0; i < eigVecs.getCols(); i++)
        direction[i] = eigVecs(0,i);
    direction = direction * eigVals[0];
    }

QVMatrix ComputeEuclideanHomography(const QList< QPointFMatching > &matchings)
    {
    // 1. Get source and destination mean point and direction.
    QList<QPointF> sourcePointList, destPointList;
    //QPair<QPointF, QPointF> matching;
    foreach(QPointFMatching matching, matchings)
        {
        sourcePointList.append(matching.first);
        destPointList.append(matching.second);
        }

    const QVMatrix sources = sourcePointList, destinations = destPointList;

    QVVector sourcesMean, destinationsMean, sourcesDirection, destinationsDirection;
    getMeanDirection(sources.transpose(), sourcesMean, sourcesDirection);
    getMeanDirection(destinations.transpose(), destinationsMean, destinationsDirection);

    const QPointF C1 = sourcesMean, C2 = destinationsMean, D1 = sourcesDirection, D2 = destinationsDirection;

    // 2. Get zoom and angle
    double zoom = 0;
    int switchD1Direction = 0, zoomCount = 0;
    for(int i = 0; i < sourcePointList.size(); i ++)
        {
        const QPointF sourceCenteredPoint = sourcePointList.at(i) - sourcesMean, destCenteredPoint = destPointList.at(i) - destinationsMean;

        if (norm2(sourceCenteredPoint) > 1e-10)
            {
            zoom += norm2(destCenteredPoint) / norm2(sourceCenteredPoint);
            zoomCount ++;
            }

        if (	(norm2(destCenteredPoint - D2) - norm2(destCenteredPoint + D2)) * (norm2(sourceCenteredPoint + D1)
                - norm2(sourceCenteredPoint - D1)) > 0	||
            (norm2(destCenteredPoint - D2) - norm2(destCenteredPoint + D2)) * (norm2(sourceCenteredPoint + D1)
                - norm2(sourceCenteredPoint - D1)) > 0	)
            switchD1Direction++;
        else
            switchD1Direction--;
        }

    zoom /= sourcePointList.size();

    const double delta = qvClockWiseAngle((switchD1Direction > 0)?-D1:D1, D2);

    // 3. Get the euclidean homography matrix, derived from the following code for Mathematica:
    //	Rotation[delta_] := { {Cos[delta], Sin[delta], 0}, {-Sin[delta], Cos[delta], 0}, {0, 0, 1} };
    //	Translation[x_, y_] := { {1, 0, x}, {0, 1, y}, {0, 0, 1} };
    //	Zoom[z_] := { {z, 0, 0}, {0, z, 0}, {0, 0, 1} };
    //	result = Translation[C2_x, C2_y].Zoom[zoom].Rotation[delta].Translation[C1_x, C1_y] // MatrixForm
    QVMatrix result = QVMatrix::identity(3);
    result(0,0) = zoom*cos(delta);	result(0,1) = zoom*sin(delta);	result(0,2) = C2.x() - zoom*cos(delta)*C1.x() - zoom*C1.y()*sin(delta);
    result(1,0) = -zoom*sin(delta);	result(1,1) = zoom*cos(delta);	result(1,2) = C2.y() - zoom*cos(delta)*C1.y() + zoom*C1.x()*sin(delta);

    return result;
    }*/

QPointF applyHomography(const QVMatrix &H, const QPointF &point)
    {
    const double	h11 = H(0,0), h12 = H(0,1), h13 = H(0,2),
            h21 = H(1,0), h22 = H(1,1), h23 = H(1,2),
            h31 = H(2,0), h32 = H(2,1), h33 = H(2,2),
            x = point.x(), y = point.y(),
            homogenizer = h31*x + h32*y + h33;

    return QPointF(h11*x + h12*y + h13, h21*x + h22*y + h23)/homogenizer;
    }

QList<QPointF> applyHomography(const QVMatrix &homography, const QList<QPointF> &sourcePoints)
    {
    QList<QPointF> result;
    foreach(QPointF point, sourcePoints)
        result.append(applyHomography(homography, point));
    return result;
    }

#ifdef QVIPP
QVImage<uChar, 1> applyHomography(const QVMatrix &homography, const QVImage<uChar, 1> &image, const int interpolation)
    {
    QVImage<uChar, 1> result(image.getCols(), image.getRows());
    WarpPerspective(image, result, homography, interpolation);
    return result;
    }

QVImage<uChar, 3> applyHomography(const QVMatrix &homography, const QVImage<uChar, 3> &image, const int interpolation)
    {
    QVImage<uChar, 3> result(image.getCols(), image.getRows());
    WarpPerspective(image, result, homography, interpolation);
    return result;
    }
#endif

double HomographyTestError(const QVMatrix &homography)
    {
    const QVVector v1 = homography.getCol(0), v2 = homography.getCol(1);
    return	ABS(v1.norm2() - v2.norm2()) / (v1.norm2() + v2.norm2())
        + ABS(v1 * v2) / (v1.norm2() * v2.norm2());
    }

////////////////////////////////////////////////////////////////
// Focal calibration from homography
//

// To get direct focal distance formula:
//
//	K = {{f, 0, 0}, {0, f, 0}, {0, 0, 1}};
//	Hvar = {{h1, h2, h3}, {h4, h5, h6}, {h7, h8, h9}};
//	ErrorMat[H_, K_] := Transpose[H].Inverse[K].Inverse[K].H;
//	Error[ErrorM_] := ((ErrorM[[1, 1]] - ErrorM[[2, 2]])^2 + ErrorM[[1, 2]]^2) / ErrorM[[1, 1]]^2;
//	ErrorFunction[H_, K_] := Error[ErrorMat[H, K]];
//	P = Dt[ErrorFunction[Hvar, K], f, Constants -> {h1, h2, h3, h4, h5, h6, h7, h8, h9}] ;
//	focalDistance  = Solve[P == 0, f][[2]][[1]] // FullSimplify
//	CForm[focalDistance]
//
/*void GetDirectIntrinsicCameraMatrixFromHomography(const QVMatrix &H, QVMatrix &K)
    {
    const double h1 = H(0,0), h2 = H(0,1), h4 = H(1,0), h5 = H(1,1), h7 = H(2,0), h8 = H(2,1);
    const double focalNumerator =	+ (h2*(h2 + h4) - h1*h5 + pow(h5,2))*(pow(h2,2) - h2*h4 + h5*(h1 + h5))*pow(h7,2)
                    - (pow(h1,2) + pow(h4,2))*(h1*h2 + h4*h5)*h7*h8
                    + (pow(h1,2) + pow(h4,2))*(pow(h1,2) - pow(h2,2) + pow(h4,2) - pow(h5,2))*pow(h8,2);
    const double focalDenominator = + (pow(h2,2) + pow(h5,2))*pow(h7,4)
                    - (h1*h2 + h4*h5)*pow(h7,3)*h8
                    - (pow(h2,2) + pow(h5,2))*pow(h7,2)*pow(h8,2)
                    + (pow(h1,2) + pow(h4,2))*pow(h8,4);
    const double finv = sqrt(ABS(focalNumerator / focalDenominator))/2;

    K = QVMatrix::identity(3) * finv;
    K(2,2) = 1;
    }*/

/*void CalibrateCameraFromPlanarHomography(const QVMatrix &H, QVMatrix &K, QVMatrix &Rt)
    {
    // 3.2. Compute intrinsic camera matrix
    // K is such that:
    // H = K*Rt
    GetDirectIntrinsicCameraMatrixFromHomography(H, K);

    // ----------------------------------------------------
    // 3.3. Compute extrinsic camera matrix
    // 3.3.1. Eliminate K matrix from H
    QVMatrix R12t = pseudoInverse(K)*H;

    // 3.3.2. Tricky: homogenize M3x3 such as the lenght of rotation vectors is the unit.
    // Divide M3x3 by the mean of the square values for first two elements
    // of the diagonal of matrix M3x3^t * M3x3
    Rt = QVMatrix(4,4);
    R12t = R12t * 2 / (R12t.getCol(0).norm2() + R12t.getCol(1).norm2());

    // 3.3.3. Compose matrix R and -R*C vector in final matrix M
    Rt.setCol(0, R12t.getCol(0));
    Rt.setCol(1, R12t.getCol(1));
    Rt.setCol(2, R12t.getCol(0) ^ R12t.getCol(1));
    Rt.setCol(3, R12t.getCol(2));
    Rt(3,3) = 1;
    }*/

//
// This function decomposes the matrix for an homography, obtaining matrix R and vector T from the decomposition:
//	H = K*M3x3
// where
//	M3x3 = [ R1 | R2 | -R^t*C ]
// obtaining the essencial matrix M of size 3x4:
//		[	|	 ]
//	M4x4 =	[  Rot  | -R^t*C ]
//		[ _____	| ______ ]
//		[ 0 0 0	|    1   ]
//
void GetExtrinsicCameraMatrixFromHomography(const QVMatrix &K, const QVMatrix &H, QVMatrix &Rt)
    {
    // 1. Eliminate K matrix from H
    QVMatrix R12_t = pseudoInverse(K)*pseudoInverse(H);

    // 2. Tricky: homogenize M3x3 such as the lenght of rotation vectors is the unit.
    //	2.2 Divide M3x3 by the mean of the square values for first two elements
    //	of the diagonal of matrix M3x3^t * M3x3
    R12_t = R12_t * 2 / (R12_t.getCol(0).norm2() + R12_t.getCol(1).norm2());

    // 3. Compose matrix R and -R*C vector in final matrix M
    Rt = QVMatrix(4,4);

    Rt.setCol(0, R12_t.getCol(0));
    Rt.setCol(1, R12_t.getCol(1));
    Rt.setCol(2, R12_t.getCol(0) ^ R12_t.getCol(1));
    Rt.setCol(3, R12_t.getCol(2));
    Rt(3,3) = 1;
    }

void GetPinholeCameraIntrinsicsFromPlanarHomography(const QVMatrix &H, QVMatrix &K, const int iterations,
                        const double maxGradientNorm, const double step, const double tol)
    {
    Q_UNUSED(H);
    Q_UNUSED(K);
    Q_UNUSED(iterations);
    Q_UNUSED(maxGradientNorm);
    Q_UNUSED(step);
    Q_UNUSED(tol);
    std::cout << "WARNING: Function 'GetPinholeCameraIntrinsicsFromPlanarHomography' is not supported anymore." << std::endl;
    exit(0);
    }

// From section 9.6.1 of 'Multiple View Geometry in Computer Vision'.
QList<QVMatrix> getCanonicalCameraMatricesFromEssentialMatrix(const QVMatrix &E)
    {
    std::cout << "WARNING: getCanonicalCameraMatricesFromEssentialMatrix deprecated. Use getCameraPosesFromEssentialMatrix instead." << std::endl;
    QVVector S;
    QVMatrix U, V;
    singularValueDecomposition(E, U, S, V);

    QVMatrix W(3, 3, 0.0);//, Z(3, 3, 0.0);
    W(1,0) = 1; W(0,1) = -1; W(2,2) = 1;
    //Z(1,0) = -1; Z(0,1) = 1;

    const QVVector	u3 = U.getCol(2);
    const QVMatrix	UWVt = U * W * V.transpose(),
            UWtVt = U * W.transpose() * V.transpose();


    return QList<QVMatrix>() << ( UWVt | u3 ) << ( UWtVt | u3 ) << ( UWVt | u3*(-1) ) << ( UWtVt | u3*(-1) );
    }

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------

/*QVMatrix getCameraMatrixFrom2D3DPointCorrespondences(const QList<QPointF> &points2d, const QList<QV3DPointF> &points3d)
    {
    const int n = points2d.size();
    QVMatrix A(3 * n, 12);
    for(int i = 0; i < n; i++)
        {
        const double	xp = points2d[i].x(), yp = points2d[i].y(),
                x =  points3d[i].x(), y =  points3d[i].y(), z =  points3d[i].z();

        const double dataCoefs[3*12] =	{
                        0,	0,	0,	0,	-x,	-y,	-z,	-1,	+x*yp,	+y*yp,	+yp*z,	+yp,
                        +x,	+y,	+z,	+1,	0,	0,	0,	0,	-x*xp,	-xp*y,	-xp*z,	-xp,
                        -x*yp,	-y*yp,	-yp*z,	-yp,	+x*xp,	+xp*y,	+xp*z,	+xp,	0,	0,	0,	0
                        };

        const QVMatrix coefs(3, 12, dataCoefs);

        A.setRow(3*i+0, coefs.getRow(0));
        A.setRow(3*i+1, coefs.getRow(1));
        A.setRow(3*i+2, coefs.getRow(2));
        }

    QVVector vectorP;
    SolveHomogeneous(A, vectorP);

    const QVMatrix P = QVMatrix(vectorP.mid(0,4)) & QVMatrix(vectorP.mid(4,4)) & QVMatrix(vectorP.mid(8,4));

    // The obtained matrix is up to scale. It should be normalized to make it a correct euclidean transformation matrix.
    const QVMatrix PNormalizer = P.transpose() * P;
    return P / sqrt((PNormalizer(0,0) + PNormalizer(1,1) + PNormalizer(2,2)) / 3.0);
    }*/

/*QVMatrix refineExtrinsicCameraMatrixWithQRDecomposition(const QVMatrix &P)
    {
    const QVMatrix M = P.getSubmatrix(0,2,0,2), Mt = M.transpose();

    QVMatrix Q, R;
    QRDecomposition(Mt, Q, R);

    QVMatrix I_1 = QVMatrix::identity(3);

    I_1(0,0) = SIGN(R(0,0));
    I_1(1,1) = SIGN(R(1,1));
    I_1(2,2) = SIGN(R(2,2));

    return pseudoInverse(R.transpose()*I_1) * P;
    }*/

QVMatrix refineExtrinsicCameraMatrixWithPolarDecomposition(const QVMatrix &P)
    {
    const QVMatrix M = P.getSubmatrix(0,2,0,2), Mt = M.transpose();

    QVMatrix W,V;
    QVVector S;
    singularValueDecomposition(Mt, W, S, V);

    // Polar decomposition of a matrix: given square matrix A, and its SVD decomposition:
    //	A = WSV*
    // The polar decomposition is the following:
    //	A = UP
    // With:
    //	U = WV*
    //	P = VSV*
    // U is a rotation matrix and P is a positive-semidefinite Hermitian matrix.
    QVMatrix matS(3,3,0.0);
    matS(0,0) = S[0];
    matS(1,1) = S[1];
    matS(2,2) = S[2];

    const QVMatrix	//U = W*V.transpose(),
            Pp = V * matS * V.transpose();

    QVMatrix I_Pp = QVMatrix::identity(3);

    I_Pp(0,0) = SIGN(Pp(0,0));
    I_Pp(1,1) = SIGN(Pp(1,1));
    I_Pp(2,2) = SIGN(Pp(2,2));

    return pseudoInverse(Pp.transpose()*I_Pp) * P;
    }


// -------------------------------------------------------------------------------------------------------------------------------------------------------

QVMatrix linearCameraResection(const QList<QPointF> &points2d, const QList<QV3DPointF> &points3d)
    {
    QVMatrix A(3 * points2d.size(), 12);
    double *dataA = A.getWriteData();

    QListIterator<QPointF> iterator2D(points2d);
    QListIterator<QV3DPointF> iterator3D(points3d);

    int i = 0;
    while (iterator2D.hasNext())
        {
        const QPointF p2d = iterator2D.next();
        const QV3DPointF p3d = iterator3D.next();

        const double	xp = p2d.x(), yp = p2d.y(),
               			x = p3d.x(), y =  p3d.y(), z =  p3d.z();

        double *data = dataA + (3*12*i);
        data[0] = 0.0;		data[1] = 0.0;		data[2] = 0.0;		data[3] = 0.0;
        data[4] = -x;		data[5] = -y;		data[6] = -z;		data[7] = -1;
        data[8] = +x*yp;	data[9] = +y*yp;	data[10] = +z*yp;	data[11] = +yp;

        data[12] = +x;		data[13] = +y;		data[14] = +z;		data[15] = +1;
        data[16] = 0.0;		data[17] = 0.0;		data[18] = 0.0;		data[19] = 0.0;
        data[20] = -x*xp;	data[21] = -y*xp;	data[22] = -z*xp;	data[23] = -xp;

        data[24] = -x*yp;	data[25] = -y*yp;	data[26] = -z*yp;	data[27] = -yp;
        data[28] = +x*xp;	data[29] = +y*xp;	data[30] = +z*xp;	data[31] = +xp;
        data[32] = 0.0;		data[33] = 0.0;		data[34] = 0.0;		data[35] = 0.0;

        i++;
        }

    QVVector vectorP;
    solveHomogeneous(A, vectorP);
    const QVMatrix P(3, 4, vectorP);

    // -----------------------
    // Use cheirality to identify correct camera matrix sign.
    const double *dataP = P.getReadData();
    const QV3DPointF p3d = points3d.first();
    return P * SIGN(dataP[8] * p3d.x() + dataP[9] * p3d.y() + dataP[10]*p3d.z() + dataP[11]);
    }

QVVector linearCameraCenterResection(const QVMatrix &R, const QList<QPointF> &points2D, const QList<QV3DPointF> &points3D)
    {
    const int n = points2D.size();
    QVMatrix A(3*n,3);
    QVVector b(3*n);

    const double *dataR = R.getReadData();

    for(int i = 0; i < n; i++)
        {
        const QPointF p2d = points2D[i];
        const QV3DPointF p3d = points3D[i];
        const double p_x = p2d.x(), p_y = p2d.y(), x = p3d.x(), y = p3d.y(), z = p3d.z();

        double *dataA = &(A(3*i, 0));

        dataA[0] = 0.0;		dataA[1] = -1.0;	dataA[2] = p_y;
        dataA[3] = 1.0;		dataA[4] = 0.0;		dataA[5] = -p_x;
        dataA[6] = -p_y;	dataA[7] = p_x;		dataA[8] = 0.0;

        b[3*i+0] = p_x - ((-dataR[3] + p_y * dataR[6]) * x + (-dataR[4] + p_y * dataR[7]) * y + (-dataR[5] + p_y * dataR[8]) * z);
        b[3*i+1] = p_y - ((dataR[0] - p_x * dataR[6]) * x + (dataR[1] - p_x * dataR[7]) * y + (dataR[2] - p_x * dataR[8]) * z);
        b[3*i+2] = 1 - ((-p_y * dataR[0] + p_x * dataR[3]) * x + (-p_y * dataR[1] + p_x * dataR[4]) * y + (-p_y * dataR[2] + p_x * dataR[5]) * z);
        }

    /// @todo Resolver el sistema linear de forma más eficiente.
    return pseudoInverse(A)*b;
    }

QV3DPointF linear3DPointTriangulation(const QList<QVMatrix> &cameraMatrices, const QList<QPointF> &projectionsOfAPoint, const TQVSVD_Method method)
    {
    if (projectionsOfAPoint.count() < 2)
        return QV3DPointF(0.0, 0.0, 0.0);

    const QV3DPointF p;

    QVMatrix A(2 * projectionsOfAPoint.size(),4);

    QListIterator<QPointF> iteratorProjections(projectionsOfAPoint);
    QListIterator<QVMatrix> iteratorMatrices(cameraMatrices);

    int i = 0;
    while (iteratorProjections.hasNext())
        {
        const QPointF p2d = iteratorProjections.next();
        const QVMatrix P = iteratorMatrices.next();

        double	*a = &(A(2*i,0)), p_x = p2d.x(), p_y = p2d.y();
        const double *p = P.getReadData();
        a[0] = p[8] * p_x - p[0];
        a[1] = p[9] * p_x - p[1];
        a[2] = p[10] * p_x - p[2];
        a[3] = p[11] * p_x - p[3];
        a[4] = p[8] * p_y - p[4];
        a[5] = p[9] * p_y - p[5];
        a[6] = p[10] * p_y - p[6];
        a[7] = p[11] * p_y - p[7];
        i++;
        }

    QVVector x;
    #ifdef GSL_AVAILABLE
        solveHomogeneousEig(A, x);
        Q_UNUSED(method);
    #else
        solveHomogeneous(A, x, method);
    #endif

    return QV3DPointF(x[0] / x[3], x[1] / x[3], x[2] / x[3]);
    }

QV3DPointF linear3DPointTriangulation(const QVector<QVMatrix> &cameraMatrices, const QHash<int, QPointF> &projectionsOfAPoint, const TQVSVD_Method method)
    {
    if (projectionsOfAPoint.count() < 2)
        return QV3DPointF(0.0, 0.0, 0.0);

    QVMatrix A(2 * projectionsOfAPoint.size(),4);

    QHashIterator<int, QPointF> it(projectionsOfAPoint);
    int i=0;
    while (it.hasNext())
        {
        it.next();
        const QPointF p2d = it.value();
        const QVMatrix P = cameraMatrices[it.key()];

        double	*a = &(A(2*i,0));
        const double *p = P.getReadData(), p_x = p2d.x(), p_y = p2d.y();
        a[0] = p[8] * p_x - p[0];
        a[1] = p[9] * p_x - p[1];
        a[2] = p[10] * p_x - p[2];
        a[3] = p[11] * p_x - p[3];
        a[4] = p[8] * p_y - p[4];
        a[5] = p[9] * p_y - p[5];
        a[6] = p[10] * p_y - p[6];
        a[7] = p[11] * p_y - p[7];
        i++;
        }

    QVVector x;
    #ifdef GSL_AVAILABLE
        solveHomogeneousEig(A, x);
        Q_UNUSED(method);
    #else
        solveHomogeneous(A, x, method);
    #endif

    return QV3DPointF(x[0] / x[3], x[1] / x[3], x[2] / x[3]);
    }

QV3DPointF linear3DPointTriangulation(const QPointFMatching &matching, const QVMatrix &P1, const QVMatrix &P2, const TQVSVD_Method method)
    {
    QVMatrix A(4,4);
    double	*a = A.getWriteData();
    const double	*p1 = P1.getReadData(),
            *p2 = P2.getReadData(),
            p_x1 = matching.first.x(),	p_y1 = matching.first.y(),
            p_x2 = matching.second.x(),	p_y2 = matching.second.y();

    a[0] = p1[8] * p_x1 - p1[0];
    a[1] = p1[9] * p_x1 - p1[1];
    a[2] = p1[10] * p_x1 - p1[2];
    a[3] = p1[11] * p_x1 - p1[3];
    a[4] = p1[8] * p_y1 - p1[4];
    a[5] = p1[9] * p_y1 - p1[5];
    a[6] = p1[10] * p_y1 - p1[6];
    a[7] = p1[11] * p_y1 - p1[7];

    a[8] = p2[8] * p_x2 - p2[0];
    a[9] = p2[9] * p_x2 - p2[1];
    a[10] = p2[10] * p_x2 - p2[2];
    a[11] = p2[11] * p_x2 - p2[3];
    a[12] = p2[8] * p_y2 - p2[4];
    a[13] = p2[9] * p_y2 - p2[5];
    a[14] = p2[10] * p_y2 - p2[6];
    a[15] = p2[11] * p_y2 - p2[7];

    QVVector x;
    #ifdef GSL_AVAILABLE
        solveHomogeneousEig(A, x);
        Q_UNUSED(method);
    #else
        solveHomogeneous(A, x, method);
    #endif

    return QV3DPointF(x[0] / x[3], x[1] / x[3], x[2] / x[3]);
    }

QV3DPointF linear3DPointTriangulation(const QPointFMatching &matching, const QVCameraPose &pose1, const QVCameraPose &pose2, const TQVSVD_Method method)
    {
	return linear3DPointTriangulation(matching, pose1.toProjectionMatrix(), pose2.toProjectionMatrix()	);
    }

QVector<QVMatrix> cameraPosesToProjectionMatrices(const QList<QVCameraPose> &cameraPoses)
	{
    QList<QVMatrix> cameraMatrices;
    foreach(QVCameraPose cameraPose, cameraPoses)
        cameraMatrices << cameraPose.toProjectionMatrix();

	return cameraMatrices.toVector();
	}

QVector<QVMatrix> cameraPosesToProjectionMatrices(const QList<QVEuclideanMapping3> &cameras)
	{
    QList<QVMatrix> cameraMatrices;
    foreach(QVEuclideanMapping3 E3, cameras)
        cameraMatrices << E3.toRotationTranslationMatrix();

	return cameraMatrices.toVector();
	}

QList<QV3DPointF> linear3DPointsTriangulation(const QList<QVEuclideanMapping3> &cameras, const QList<QHash<int, QPointF> > &pointTrackings, const TQVSVD_Method method)
    {
   /* QList<QVMatrix> cameraMatrices;
    foreach(QVEuclideanMapping3 E3, cameras)
        cameraMatrices << E3.toRotationTranslationMatrix();*/

    const QVector<QVMatrix> cameraMatricesVector = cameraPosesToProjectionMatrices(cameras);

    QList<QV3DPointF> result;
    QHash<int, QPointF> projectionsOfAPoint;
    foreach(projectionsOfAPoint, pointTrackings)
        result << linear3DPointTriangulation(cameraMatricesVector, projectionsOfAPoint, method);

    return result;
    }

QList<QV3DPointF> linear3DPointsTriangulation(const QList<QVEuclideanMapping3> &cameras, const QVector<QHash<int, QPointF> > &pointTrackings, const TQVSVD_Method method)
    {
   /* QList<QVMatrix> cameraMatrices;
    foreach(QVEuclideanMapping3 E3, cameras)
        cameraMatrices << E3.toRotationTranslationMatrix();*/

    const QVector<QVMatrix> cameraMatricesVector = cameraPosesToProjectionMatrices(cameras);

    QList<QV3DPointF> result;
    QHash<int, QPointF> projectionsOfAPoint;
    foreach(projectionsOfAPoint, pointTrackings)
        result << linear3DPointTriangulation(cameraMatricesVector, projectionsOfAPoint, method);

    return result;
    }

QList<QV3DPointF> linear3DPointsTriangulation(const QList<QVCameraPose> &cameraPoses, const QList<QHash<int, QPointF> > &pointTrackings, const TQVSVD_Method method)
    {
   /* QList<QVMatrix> cameraMatrices;
    foreach(QVCameraPose cameraPose, cameraPoses)
        cameraMatrices << cameraPose.toProjectionMatrix();*/

    const QVector<QVMatrix> cameraMatricesVector = cameraPosesToProjectionMatrices(cameraPoses);

    QList<QV3DPointF> result;
    QHash<int, QPointF> projectionsOfAPoint;
    foreach(projectionsOfAPoint, pointTrackings)
        result << linear3DPointTriangulation(cameraMatricesVector, projectionsOfAPoint, method);

    return result;
    }

QList<QV3DPointF> linear3DPointsTriangulation(const QList<QVCameraPose> &cameraPoses, const QVector<QHash<int, QPointF> > &pointTrackings, const TQVSVD_Method method)
    {
   /* QList<QVMatrix> cameraMatrices;
    foreach(QVCameraPose cameraPose, cameraPoses)
        cameraMatrices << cameraPose.toProjectionMatrix();*/

    const QVector<QVMatrix> cameraMatricesVector = cameraPosesToProjectionMatrices(cameraPoses);

    QList<QV3DPointF> result;
    QHash<int, QPointF> projectionsOfAPoint;
    foreach(projectionsOfAPoint, pointTrackings)
        result << linear3DPointTriangulation(cameraMatricesVector, projectionsOfAPoint, method);

    return result;
    }

#ifndef DOXYGEN_IGNORE_THIS
bool getCorrectCameraPoseTestingCheirality(const QPointFMatching matching, const QVMatrix &R1, const QVMatrix &R2, const QV3DPointF t, bool &R1IsCorrect, bool &tIsPossitive)
	{
	// Set the initial camera pose to identity, and initialize the four possible destination camera poses.
	const QVMatrix	sourceRt = (QVMatrix::identity(3)|QVVector(3,0.0)),
			destRt1 = R1|t,
			destRt2 = R1|t*(-1.0),
			destRt3 = R2|t,
			destRt4 = R2|t*(-1.0);

	// Test cheirality for the different possible destination camera poses using the first point correspondence.
	const bool	// for camera poses (I|0) and (R1|t)
			cheiralityTest1 = testCheiralityForCameraPoses(sourceRt, matching.first, destRt1, matching.second ),
			// for camera poses (I|0) and (R1|-t)
			cheiralityTest2 = testCheiralityForCameraPoses(sourceRt, matching.first, destRt2, matching.second ),
			// for camera poses (I|0) and (R2|t)
			cheiralityTest3 = testCheiralityForCameraPoses(sourceRt, matching.first, destRt3, matching.second ),
			// for camera poses (I|0) and (R2|-t)
			cheiralityTest4 = testCheiralityForCameraPoses(sourceRt, matching.first, destRt4, matching.second );

	// Set the destination camera pose depending on which of them satisfies the cheirality test.
	if (cheiralityTest1 and not (cheiralityTest2 or cheiralityTest3 or cheiralityTest4) )
		// Cheirality is satisfied only for camera poses (I|0) and (R1|t)
		{ R1IsCorrect = true; tIsPossitive = true; }
		//destRt = destRt1;
	else if	( cheiralityTest2 and not (cheiralityTest1 or cheiralityTest3 or cheiralityTest4) )
		// Cheirality is satisfied only for camera poses (I|0) and (R1|-t)
		{ R1IsCorrect = true; tIsPossitive = false; }
		//destRt = destRt2;
	else if (cheiralityTest3 and not (cheiralityTest1 or cheiralityTest2 or cheiralityTest4) )
		// Cheirality is satisfied only for camera poses (I|0) and (R2|t)
		{ R1IsCorrect = false; tIsPossitive = true; }
		//destRt = destRt3;
	else if ( cheiralityTest4 and not (cheiralityTest1 or cheiralityTest2 or cheiralityTest3) )
		// Cheirality is satisfied only for camera poses (I|0) and (R2|-t)
		{ R1IsCorrect = false; tIsPossitive = false; }
		//destRt = destRt4;
	else	// Two or more camera poses satisfy the cheirality test simultaneously. Ambiguous configuration.
		return false;

	return true;
	}
#endif // DOXYGEN_IGNORE_THIS

void getCameraPosesFromEssentialMatrix(const QVMatrix &originalE, QVMatrix &R1, QVMatrix &R2, QV3DPointF &t)
    {
    // Caution: Force the determinant value of the essential to be possitive.
    const QVMatrix E = originalE * ( (determinant(originalE) < 0.0)? -1.0: 1.0);

    QVVector S;
    QVMatrix U, V;
    singularValueDecomposition(E, U, S, V);

    QVMatrix W(3, 3, 0.0);
    W(1,0) = 1; W(0,1) = -1; W(2,2) = 1;

    R1 = U * W * V.transpose();
    R2 = U * W.transpose() * V.transpose();

    // Note: the real expression for [t] should be:
    //	[t]_x = U*QVMatrix::diagonal(S)*W*U.transpose()
    // But it is not a real skew-symmetric matrix.
    // The following expression assumes that [t]_x is actually skew-symmetric.
    t = U.getCol(2);
    }

bool testCheiralityForCameraPoses(const QVMatrix &sourceRt, const QPointF &sourceProjection, const QVMatrix &destRt, const QPointF &destProjection)
    {
    // Comprueba la lateralidad con uno de los puntos. Nos quedamos con una de las cámaras.
    const QVVector homogeneousP3D = QVVector() << linear3DPointTriangulation( QPointFMatching(sourceProjection, destProjection), sourceRt, destRt) << 1;
    return ((sourceRt*homogeneousP3D)[2] > 0) and ((destRt*homogeneousP3D)[2] > 0);
    }

QList<QPointFMatching> applyHomographies(const QVMatrix &H1, const QVMatrix &H2, const QList<QPointFMatching> &matchings)
    {
    QList<QPointFMatching> correctedMatchings;
    foreach(QPointFMatching matching, matchings)
        correctedMatchings << QPointFMatching(	applyHomography(H1, matching.first), applyHomography(H2, matching.second));
    return correctedMatchings;
    }

QList<QPointFMatching> correctIntrinsics(const QVMatrix &K1, const QVMatrix &K2, const QList<QPointFMatching> &matchings)
    {
    const QVMatrix	invK1 = pseudoInverse(K1),
            invK2 = pseudoInverse(K2);

    QList<QPointFMatching> correctedMatchings;
    foreach(QPointFMatching matching, matchings)
        correctedMatchings << QPointFMatching(	applyHomography(invK1, matching.first),
                            applyHomography(invK2, matching.second)
                            );
    return correctedMatchings;
    }

QList< QHash< int, QPointF> > correctIntrinsics(const QVMatrix &K, const QList< QHash< int, QPointF> > &pointsProjections)
    {
    QList< QHash< int, QPointF> > calibratedProjections;

    const QVMatrix invK = pseudoInverse(K);
    for(int i = 0; i < pointsProjections.size(); i++)
        {
        calibratedProjections << QHash<int, QPointF>();
        foreach(int j, pointsProjections[i].keys())
            calibratedProjections[i][j] = applyHomography(invK, pointsProjections[i][j]);
        }
    return calibratedProjections;
    }

double computeCameraFocalFromPlanarHomography(const QVMatrix &H, int w, int h, bool byzero)
    {
    const QVMatrix transl = QVMatrix::cameraCalibrationMatrix(1.0, 1.0, w/2.0, h/2.0);
    const QVMatrix Ht = (H*transl).inverse();
    const double ww = byzero?	(-Ht(2,0)*Ht(2,1)) / ( Ht(0,0)*Ht(0,1) + Ht(1,0)*Ht(1,1) ) :
                    (-Ht(2,0)*Ht(2,0) + Ht(2,1)*Ht(2,1)) / (Ht(0,0)*Ht(0,0) - Ht(0,1)*Ht(0,1) + Ht(1,0)*Ht(1,0) - Ht(1,1)*Ht(1,1));
    return sqrt(1/ww);
    }

QVCameraPose getCameraPoseFromCalibratedHomography(const QVMatrix & K, const QVMatrix & H)
    {
    if(K.getCols()!=3 or K.getRows()!=3 or H.getCols()!=3 or H.getRows()!=3)
        {
        std::cerr << "[getCameraPoseFromCalibratedHomography] Warning: homography and calibration matrices are not of size 3x3.";
        return QVEuclideanMapping3();
        }

    const QVMatrix Hc = K.inverse()*H.inverse();
    QVVector r0,r1,r2,aux;

    r0 = Hc.getCol(0);
    r0 = r0/r0.norm2();
    aux = Hc.getCol(1);
    aux = aux/aux.norm2();
    r2 = r0^aux;
    r2 = r2/r2.norm2();
    r1 = -r0^r2;

    QVMatrix R(3,3);
    R.setCol(0,r0);
    R.setCol(1,r1);
    R.setCol(2,r2);

    const QVVector C = /*-(R.transpose()*/ Hc.getCol(2) / (Hc.getCol(0).norm2());

    return QVEuclideanMapping3(QVQuaternion(R),QV3DPointF(C));
    }


// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
// DEPRECATED

QVMatrix computeProjectiveHomography(const QList< QPointFMatching > &matchings)
	{
    std::cout << "WARNING: this version of 'computeProjectiveHomography' is deprecated." << std::endl;
	QVMatrix H;
	computeProjectiveHomography(matchings, H);
	return H;
	}

QV3DPointF linear3DPointTriangulation(const QPointF &point1, const QVMatrix &P1, const QPointF &point2, const QVMatrix &P2, const TQVSVD_Method method)
    {
    std::cout << "WARNING: this version of 'linear3DPointTriangulation' for two views is deprecated." << std::endl;
    return linear3DPointTriangulation(QPointFMatching(point1, point2), P1, P2, method);
    }

QVMatrix getCameraMatrixFrom2D3DPointCorrespondences(const QList<QPointF> &points2d, const QList<QV3DPointF> &points3d)
    {
    std::cout << "WARNING: getCameraMatrixFrom2D3DPointCorrespondences deprecated. Use linearCameraResection instead." << std::endl;

    const int n = points2d.size();
    QVMatrix A(3 * n, 12);
    for(int i = 0; i < n; i++)
        {
        const double	xp = points2d[i].x(), yp = points2d[i].y(),
                x =  points3d[i].x(), y =  points3d[i].y(), z =  points3d[i].z();

        const double dataCoefs[3*12] =	{
                        0,	0,	0,	0,	-x,	-y,	-z,	-1,	+x*yp,	+y*yp,	+yp*z,	+yp,
                        +x,	+y,	+z,	+1,	0,	0,	0,	0,	-x*xp,	-xp*y,	-xp*z,	-xp,
                        -x*yp,	-y*yp,	-yp*z,	-yp,	+x*xp,	+xp*y,	+xp*z,	+xp,	0,	0,	0,	0
                        };

        const QVMatrix coefs(3, 12, dataCoefs);

        A.setRow(3*i+0, coefs.getRow(0));
        A.setRow(3*i+1, coefs.getRow(1));
        A.setRow(3*i+2, coefs.getRow(2));
        }

    QVVector vectorP;
    solveHomogeneous(A, vectorP);

    const QVMatrix	P = QVMatrix(vectorP.mid(0,4)) & QVMatrix(vectorP.mid(4,4)) & QVMatrix(vectorP.mid(8,4));
            // The obtained matrix is up to scale. It should be normalized to make it a correct euclidean transformation matrix.

    // Use cheirality to identify correct camera matrix sign.
    return P * SIGN((P*(QVVector(points3d.first()) << 1))[2]);
    }

QV3DPointF triangulate3DPointFrom2Views(const QPointF &point1, const QVMatrix &P1, const QPointF &point2, const QVMatrix &P2)
    {
    std::cout << "WARNING: triangulate3DPointFrom2Views deprecated. Use linear3DPointTriangulation instead." << std::endl;
    QVMatrix A(4,4);

    A.setRow(0, P1.getRow(2) * point1.x() - P1.getRow(0));
    A.setRow(1, P1.getRow(2) * point1.y() - P1.getRow(1));
    A.setRow(2, P2.getRow(2) * point2.x() - P2.getRow(0));
    A.setRow(3, P2.getRow(2) * point2.y() - P2.getRow(1));

    QVVector x;

    solveHomogeneous(A, x);

    // Cheiral condition. All points must lie in front of the camera.
    // See Zisserman, section 21.7.
    //if (x[2] / x[3] >= 0)
    return QV3DPointF(x[0] / x[3], x[1] / x[3], x[2] / x[3]);
    //else
    //	return QV3DPointF( - x[0] / x[3], - x[1] / x[3], - x[2] / x[3]);
    }

QV3DPointF triangulate3DPointFromNViews(const QList<QPointF> &points, const QList<QVMatrix> &Plist)
    {
    std::cout << "WARNING: triangulate3DPointFromNViews deprecated. Use linear3DPointTriangulation instead." << std::endl;
    QVMatrix A(2 * points.size(),4);
    for(int i = 0; i < points.size(); i++)
        {
        double	*a = &(A(2*i,0)),
                                p_x = points[i].x(), p_y = points[i].y();

                const double *p = Plist[i].getReadData();


        a[0] = p[8] * p_x - p[0];
        a[1] = p[9] * p_x - p[1];
        a[2] = p[10] * p_x - p[2];
        a[3] = p[11] * p_x - p[3];
        a[4] = p[8] * p_y - p[4];
        a[5] = p[9] * p_y - p[5];
        a[6] = p[10] * p_y - p[6];
        a[7] = p[11] * p_y - p[7];
        }

        QVVector x;

        solveHomogeneous(A, x);
        return QV3DPointF(x[0] / x[3], x[1] / x[3], x[2] / x[3]);
    }

QVMatrix ComputeProjectiveHomography(const QList< QPointFMatching > &matchings)
    {
    std::cout << "WARNING: ComputeProjectiveHomography deprecated. Use 'computeProjectiveHomography' instead." << std::endl;
    return computeProjectiveHomography(matchings);
    }

QVMatrix ComputeAffineHomography(const QList< QPointFMatching > &matchings)
    {
    std::cout << "WARNING: ComputeAffineHomography deprecated. Use 'computeAffineHomography' instead." << std::endl;
    return ComputeAffineHomography(matchings);
    }

QVMatrix ComputeSimilarHomography(const QList< QPointFMatching > &matchings)
    {
    std::cout << "WARNING: ComputeSimilarHomography deprecated. Use 'computeSimilarHomography' instead." << std::endl;
    return computeSimilarHomography(matchings);
    }

QVMatrix ComputeEuclideanHomography(const QList< QPointFMatching > &matchings)
    {
    std::cout << "WARNING: ComputeEuclideanHomography deprecated. Use computeSimilarHomography instead." << std::endl;
    return ComputeSimilarHomography(matchings);
    }

QPointF ApplyHomography(const QVMatrix &H, const QPointF &point)
    {
    std::cout << "WARNING: ApplyHomography deprecated. Use 'applyHomography' instead." << std::endl;
    return applyHomography(H, point);
    }

QList<QPointF> ApplyHomography(const QVMatrix &H, const QList<QPointF> &sourcePoints)
    {
    std::cout << "WARNING: ApplyHomography deprecated. Use 'applyHomography' instead." << std::endl;
    return applyHomography(H, sourcePoints);
    }

#ifdef QVIPP
QVImage<uChar, 1> ApplyHomography(const QVMatrix &H, const QVImage<uChar, 1> &image, const int interpolation)
    {
    std::cout << "WARNING: ApplyHomography deprecated. Use 'applyHomography' instead." << std::endl;
    return applyHomography(H, image, interpolation);
    }

QVImage<uChar, 3> ApplyHomography(const QVMatrix &H, const QVImage<uChar, 3> &image, const int interpolation)
    {
    std::cout << "WARNING: ApplyHomography deprecated. Use 'applyHomography' instead." << std::endl;
    return applyHomography(H, image, interpolation);
    }
#endif


