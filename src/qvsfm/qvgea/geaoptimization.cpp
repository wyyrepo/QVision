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

#include <QTime>
#include <qvsfm/qvgea/geaoptimization.h>
#include <QVSparseBlockMatrix>
#include <qvsfm/qvgea/so3EssentialEvaluation.h>
#include <qvsfm/qvgea/quaternionEssentialEvaluation.h>

QList< QHash< int, QPointF > > storePointMatchingsInTrackingContainer(const QVDirectedGraph< QVector<QPointFMatching> > &matchingLists)
	{
	QList< QHash< int, QPointF > > result;

	foreach(QVGraphLink link, matchingLists.keys())
		{
		const QVector<QPointFMatching> &matchings = matchingLists[link];
		for(int i = 0; i < matchings.count(); i++)
			{
			QHash< int, QPointF > tracking;
			tracking[link.x()] = matchings[i].first;
			tracking[link.y()] = matchings[i].second;
			result << tracking;
			}
		}
	return result;
	}

QVDirectedGraph< QList<QPointFMatching> > getPointMatchingsLists(const QList<QHash<int, QPointF> > pointProjections, const int numCams, const int minPointCorrespondences)
    {
    QTime time;
    QHash<int, QPointF> projections;

    // Transversing the structure 'pointProjections' is not computationally expensive.
    // Precompute number of correspondences between each view pair.
    time.start();
    QVector< int > count(numCams*numCams, 0);
    //if (minPointCorrespondences > 0)
    foreach(projections, pointProjections)			// 3D points
        {
        const QVector<int> indexes = projections.keys().toVector();
        foreach(int i, indexes)
            foreach(int j, indexes)
                count[i * numCams + j]++;
        }
    // int time1 = time.elapsed();

    // ---------------------------------------------------

    // Gets the lists of point matchings.
    // Main performance bottleneck of function 'getPointMatchingsLists'.
    //time.start();
    QVector< QList<QPointFMatching> > v(numCams*numCams);
    foreach(projections, pointProjections)
        {
        const QVector<int> indexes = projections.keys().toVector();

        // The most computationally costly part in this process is copying QPoint objects
        // to QPointFMatching data structures, and storing them at their corresponding lists.
        foreach(int i, indexes)
            foreach(int j, indexes)
                if ( (i < j) and (count[i*numCams+j] >= minPointCorrespondences) )
                    v[i * numCams + j] << QPointFMatching(projections[i], projections[j]);
        }
    //int time5 = time.elapsed();

    // Gets the lists of point matchings.
    // Main performance bottleneck of function 'getPointMatchingsLists'.
    /*time.start();
    QList<QPointFMatching> v2;
    //QVector< QList<QPoint> > v2(numCams*numCams);
    foreach(projections, pointProjections)
        {
        const QVector<int> indexes = projections.keys().toVector();

        // The most computationally costly part in this process is copying QPoint objects
        // to QPointFMatching data structures, and storing them at their corresponding lists.
        foreach(int i, indexes)
            foreach(int j, indexes)
                if ( (i < j) and (count[i*numCams+j] >= minPointCorrespondences) )
                    v2 << QPointFMatching(projections[i], projections[j]);
        }
    int time6 = time.elapsed();*/

    // Then, compose the directed graph with them.
    //time.start();
    QVDirectedGraph< QList<QPointFMatching> > result;
    for(int i = 0; i < numCams; i++)
        for(int j = 0; j < numCams; j++)
            {
            const QList<QPointFMatching> & list = v[i*numCams+j];
            if (list.count() > 0)
                result[ QVGraphLink(i,j) ] = list;
            }
    //int time6 = time.elapsed();

    //std::cout << "*** time1 = " << time1 << std::endl;
    //std::cout << "*** time2 = " << time2 << std::endl;
    //std::cout << "*** time3 = " << time3 << std::endl;
    //std::cout << "*** time4 = " << time4 << std::endl;
    //std::cout << "*** time5 = " << time5 << std::endl;
    //std::cout << "*** time6 = " << time6 << std::endl;
    //std::cout << "*** time7 = " << time7 << std::endl;
    return result;
    }

QVDirectedGraph< QList<QPointFMatching> > pointMatchingsListOld(const QList<QHash<int, QPointF> > pointProjections, const int numCams)
    {
    Q_UNUSED(numCams);

    QVDirectedGraph< QList<QPointFMatching> > result;

    QHash<int, QPointF> projections;
    foreach(projections, pointProjections)			// 3D points
        foreach(int i, projections.keys())		// views
            foreach(int j, projections.keys())
                if (i < j)
                    result[ QVGraphLink(i,j) ] << QPointFMatching(projections[i], projections[j]);
    return result;
    }

QVDirectedGraph<QVMatrix>  getReducedMatrices(	const QVDirectedGraph< QList<QPointFMatching> > &pointLists,
                            const bool normalize,
                            const TGEA_decomposition_method decomposition_method,
                            const bool gsl,
                            const double choleskyLambda,
                            const int minPointCorrespondences)
    {
    //std::cout << "WARNING: 'getReducedMatrices' deprecated. Use functions 'getSquaredDLTMatrix' and 'getDLTMatrix' to obtain the reduced matrices, and 'globalEpipolarAdjustment2' to perform GEA optimization." << std::endl;
    QVDirectedGraph<QVMatrix> reducedMatricesGraph;

    // For each pair of views linked with point correspondences...
    foreach(QPoint p, pointLists.keys())
        {
        const QList<QPointFMatching> &pointList = pointLists[p];
        if (pointList.count() < minPointCorrespondences)
            continue;

        // Evaluate reduced coefficient matrix.
        reducedMatricesGraph[p] = getReduced8PointsCoefficientsMatrix(pointList, decomposition_method, normalize, gsl, choleskyLambda);
        }

    return reducedMatricesGraph;
    }

QVDirectedGraph<QVMatrix>  getReducedMatrices(	const QVDirectedGraph< QVector<QPointFMatching> > &pointLists,
                        const bool normalize,
                        const TGEA_decomposition_method decomposition_method,
                        const bool gsl,
                        const double choleskyLambda,
                        const int minPointCorrespondences)
    {
    //std::cout << "WARNING: 'getReducedMatrices' deprecated. Use functions 'getSquaredDLTMatrix' and 'getDLTMatrix' to obtain the reduced matrices, and 'globalEpipolarAdjustment2' to perform GEA optimization." << std::endl;
    QVDirectedGraph<QVMatrix> reducedMatricesGraph;

    // For each pair of views linked with point correspondences...
    foreach(QPoint p, pointLists.keys())
        {
        const QVector<QPointFMatching> &pointList = pointLists[p];
        if (pointList.count() < minPointCorrespondences)
            continue;

        // Evaluate reduced coefficient matrix.
        reducedMatricesGraph[p] = getReduced8PointsCoefficientsMatrix(pointList.toList(), decomposition_method, normalize, gsl, choleskyLambda);
        }

    return reducedMatricesGraph;
    }


// -------------------------------------------------------------------------

// Returns M = DLT matrix
QVMatrix get8PointsCoefficientMatrix(const QVector<QPointFMatching> &matchings, const bool normalize)
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

QVMatrix getTransposeProductOf8PointsCoefficientMatrix(const QVector<QPointFMatching> &matchings, const bool normalize)
        {
    QVMatrix A(9,9, 0.0);
    double *ptrA = A.getWriteData();

        foreach(QPointFMatching matching, matchings)
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


QVMatrix getReduced8PointsCoefficientsMatrix(	const QVector<QPointFMatching> &matchingsList,
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

QVDirectedGraph< QVector<QPointFMatching> > getPointMatchingsListsVec(const QList<QHash<int, QPointF> > pointProjections, const int numCams, const int minPointCorrespondences)
    {
    QTime time;
    QHash<int, QPointF> projections;

    // Transversing the structure 'pointProjections' is not computationally expensive.
    // Precompute number of correspondences between each view pair.
    // time.start();
    QVector< int > count(numCams*numCams, 0);
    foreach(projections, pointProjections)			// 3D points
        {
        const QVector<int> indexes = projections.keys().toVector();
        foreach(int i, indexes)
            foreach(int j, indexes)
                count[i * numCams + j]++;
        }
    // int time1 = time.elapsed();

    // time.start();
    QVector< QVector<QPointFMatching> > vX(numCams*numCams);
    for(int i = 0; i < numCams; i++)
        for(int j = 0; j < numCams; j++)
            {
            const int c = count[i*numCams+j];
            if (c > 0)
                vX[i*numCams+j].reserve(c);
            }
    // int time2 = time.elapsed();

    // Gets the lists of point matchings.
    // Main performance bottleneck of function 'getPointMatchingsLists'.
    time.start();
    foreach(projections, pointProjections)
        {
        const QVector<int> indexes = projections.keys().toVector();

        // The most computationally costly part in this process is copying QPoint objects
        // to QPointFMatching data structures, and storing them at their corresponding lists.
        foreach(int i, indexes)
            foreach(int j, indexes)
                if ( (i < j) and (count[i*numCams+j] >= minPointCorrespondences) )
                    {
                    QVector<QPointFMatching> &vector = vX[i * numCams + j];
                    vector << QPointFMatching(projections[i], projections[j]);
                    //const int size = vector.size();
                    //vector.resize(size +1);
                    //QPointFMatching &p = vector[size];
                    //p.first = projections[i];
                    //p.second = projections[j];
                    }
        }
    // int time3 = time.elapsed();

    // time.start();
    QVDirectedGraph< QVector<QPointFMatching> > result2;
    for(int i = 0; i < numCams; i++)
        for(int j = 0; j < numCams; j++)
            {
            const QVector<QPointFMatching> & list = vX[i*numCams+j];
            if (list.count() > 0)
                result2.insert(i,j,list);
            }
    // int time4 = time.elapsed();


    //std::cout << "*** time1 = " << time1 << std::endl;
    //std::cout << "*** time2 = " << time2 << std::endl;
    //std::cout << "*** time3 = " << time3 << std::endl;
    //std::cout << "*** time4 = " << time4 << std::endl;
    //std::cout << "*** time5 = " << time5 << std::endl;
    //std::cout << "*** time6 = " << time6 << std::endl;
    //std::cout << "*** time7 = " << time7 << std::endl;
    return result2;
    }


// -----------------------------------------------------------------------------

// Thist function obtains the Jacobian matrix, and the residual vector
// for the GEA cost error.
// This is an internal function, used by 'incrementalGEA'.
bool evaluateGEAJacobianAndResidual(	// Number of cameras.
                    const int numCameras,
                    // Degrees of freedom for each camera (DOF): size of each camera in the vector 'x'.
                    const int DOF,
                    // Graph containing the reduced matrix, for each view link.
                    const QVDirectedGraph<QVMatrix> &reducedMatricesGraph,
                    // List of pair-views included in the cost error.
                    const QList<QVGraphLink> &links,
                    // Vector containing the components of the cameras.
                    const QVVector &x,
                    // Overriden on output with the Hessian matrix.
                    QVSparseBlockMatrix &estimatedJ,
                    // Overriden on output with the objective vector.
                    QVVector &residuals
                    )
    {
    const int numLinks = links.count();
    estimatedJ = QVSparseBlockMatrix(numLinks, numCameras, 9, DOF);
    residuals = QVVector(numLinks*9, 0.0);

    // Pointers to the data of the vectors 'x' and 'objectives'.
    const double	*xData = x.constData();

    #ifdef DEBUG
    if (x.containsNaN())
        {
        std::cout << "[evaluateGEAJacobianAndResidual] Error: NaN value found in reconstruction" << std::endl;
        return false;
        }
    #endif

    // Loop 1. Evaluate the block-jacobians for each pair of views
    // related by a reduced measurement matrix M.
    int linkIndex = 0;
    foreach(QVGraphLink link, links)
        {
        // Indexes for the pair of views in the adjacency graph.
        const int	xIndex = link.x(),	// Index 'x' for the first camera.
                yIndex = link.y();	// Index 'y' for the second camera.

        // Sanity check.
        if (xIndex > yIndex)
            {
            std::cout << "[evaluateGEAHessianAndObjectiveVector] Error: provided invalid order for indexes 'x' and 'y'." << std::endl;
            exit(0);
            }

        if (xIndex >= numCameras)
            {
            std::cout << "[evaluateGEAHessianAndObjectiveVector] Error: malformed coefficient matrices graph: index 'x' out of bounds." << std::endl;
            exit(0);
            }

        if (yIndex >= numCameras)
            {
            std::cout << "[evaluateGEAHessianAndObjectiveVector] Error: malformed coefficient matrices graph: index 'y' out of bounds." << std::endl;
            exit(0);
            }

        // jacRows	Rows for the matrix [D1|D2|v] explained below.
        // jacCols	Cols for the matrix [D1|D2|v] explained below.
        const int jacRows = 9, jacCols = DOF*2+1;

        // Evaluate partial jacobians (D1 and D2) and partial objective function vector (v).
        // These elements are such:
        //	[J1|J2|e] = M * [D1|D2|v]
        double	D1D2v[jacRows*jacCols];

        // Use a different function, depending on the parametrization used for the rotations.
        #ifdef SO3_PARAMETRIZATION
            so3EssentialEvaluation(xData + DOF*xIndex, xData + DOF*yIndex, D1D2v, 1e-32);
        #else
            quaternionEssentialEvaluation(xData + DOF*xIndex, xData + DOF*yIndex, D1D2v);
        #endif

        // Get reduced matrix M for the pair of views 'x,y'
        //const QVMatrix &reducedM = reducedMatricesGraph[index];
        const QVMatrix &reducedM = reducedMatricesGraph.value(xIndex, yIndex);
        const int reducedMCols = reducedM.getCols();

        #ifdef DEBUG
        if (reducedM.containsNaN())
            {
            std::cout << "[evaluateGEAJacobianAndResidual] Error: NaN value found in reduced matrix for views " << xIndex << ", " << yIndex << std::endl;
            return false;
            }
        #endif

        // Get the matrix of jacobians and evaluation vector with the following operation:
        //	[J1|J2|e] = M x [D1|D2|v]
        //
        double	J1J2e[jacRows*jacCols]; 	// [J1|J2|e]
        cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, reducedMCols, jacCols, jacRows, 1.0, reducedM.getReadData(), reducedMCols, D1D2v, jacCols, 0.0, J1J2e, jacCols);
        const QVMatrix mJ1J2e(jacRows, jacCols, J1J2e);

        #ifdef DEBUG
        if (mJ1J2e.containsNaN())
            {
            std::cout << "[evaluateGEAJacobianAndResidual] Error: NaN value found in block jacobian for views " << xIndex << ", " << yIndex << std::endl;
            return false;
            }
        #endif

        QVMatrix mJ1(9, DOF, 0.0), mJ2(9, DOF, 0.0);
        QVVector r(9, 0.0);
        for(int i = 0; i < reducedMCols; i++)
            {
            r[i] = mJ1J2e(i, DOF*2);
            for(int j = 0; j < DOF; j++)
                {
                mJ1(i,j) = mJ1J2e(i,j);
                mJ2(i,j) = mJ1J2e(i,DOF+j);
                }
            }

        estimatedJ.setBlock(linkIndex, xIndex, mJ1);				// Hessian block 'x,y' = J1^T*J2
        estimatedJ.setBlock(linkIndex, yIndex, mJ2);				// Hessian block 'x,y' = J1^T*J2
        for(int i = 0; i < 9; i++)
            residuals[linkIndex*9+i] = mJ1J2e(i, jacCols-1);

        linkIndex++;
        }

    return true;
    }

// Thist function obtains the Hessian matrix, and the objective vector
// for the second level system in each Levenger-Marquardt iteration
// of the GEA optimization.
// This is an internal function, used by 'globalEpipolarAdjustment'.
bool evaluateGEAHessianAndObjectiveVector(
						// Number of cameras.
                        const int numCameras,
                        // Degrees of freedom for each camera (DOF): size of each camera in the vector 'x'.
                        const int DOF,
                        // Graph containing the reduced matrix, for each view link.
                        const QVDirectedGraph<QVMatrix> &reducedMatricesGraph,
                        // A vector of booleans, one for each camera, indicating whether it is fixed or not.
						const QVector<bool> &freeCamera,
                        // Vector containing the components of the cameras.
                        const QVVector &x,
                        // Overriden on output with the Hessian matrix.
                        QVSparseBlockMatrix &estimatedH,
                        // Overriden on output with the objective vector.
                        QVVector &objectives
                        )
    {
	Q_ASSERT_X(not x.containsNaN(),					"[evaluateGEAHessianAndObjectiveVector2]", "NaN value found in state vector");

    // Clear objective vector and Hessian matrix.
    objectives = QVVector(DOF*numCameras, 0.0);
    estimatedH = QVSparseBlockMatrix(numCameras, numCameras, DOF, DOF);

    // Block elements at the diagonal of the sparse matrix 'estimatedH' will not be updated in the loop 1.
    // Instead, the values of these blocks will be accumulated on the vector 'diags'.
    // They will be translated to the Hessian matrix diagonal block elements in a final step,
    // posterior to the loop 1.
    double diags[numCameras*DOF*DOF];
    for(int i = 0; i < numCameras*DOF*DOF; i++)
        diags[i] = 0.0;

    // Pointers to the data of the vectors 'x' and 'objectives'.
    const double	*xData = x.constData();
    double			*objectivesData = objectives.data();

    #ifdef DEBUG // -----------------------------------------------------------------
    bool errorFound = false;
	int jacobianEvaluations = 0;
    #endif // ------------------------ DEBUG -----------------------------------------

    // Loop 1. Evaluate the block-jacobians for each pair of views
    // related by a reduced measurement matrix M.
	QMapIterator<QVGraphLink, QVMatrix> iterator(reducedMatricesGraph);
	while (iterator.hasNext())
		{
		iterator.next();

        // Indexes for the pair of views in the adjacency graph.
        const int	xIndex = iterator.key().x(),	// Index 'x' for the first camera.
               		yIndex = iterator.key().y();	// Index 'y' for the second camera.

		if (not freeCamera[xIndex] and not freeCamera[yIndex])
			continue;

        // Sanity check.
        if (xIndex > yIndex)
            {
            std::cout << "[evaluateGEAHessianAndObjectiveVector] Error: provided invalid order for indexes 'x' and 'y'." << std::endl;
            exit(0);
            }

        if (xIndex >= numCameras)
            {
            std::cout << "[evaluateGEAHessianAndObjectiveVector] Error: malformed coefficient matrices graph: index 'x' out of bounds." << std::endl;
            exit(0);
            }

        if (yIndex >= numCameras)
            {
            std::cout << "[evaluateGEAHessianAndObjectiveVector] Error: malformed coefficient matrices graph: index 'y' out of bounds." << std::endl;
            exit(0);
            }

        // Main data elements:
        //	M	Reduced coefficient matrix.
        //	e	Vectorization of essential matrix E.
        //	J1	Jacobian of vector e, for the components of the first camera.
        //	J2	Jacobian of vector e, for the components of the second camera.
        //
        QVMatrix J1J2(DOF,DOF);
        double temp1[DOF], temp2[DOF];
        double J1J1Data[DOF*DOF], J2J2Data[DOF*DOF];

        // jacRows	Rows for the matrix [D1|D2|v] explained below.
        // jacCols	Cols for the matrix [D1|D2|v] explained below.
        const int	jacRows = 9,
          		    jacCols = DOF*2+1;

        // Evaluate partial jacobians (D1 and D2) and partial objective function vector (v).
        // These elements are such:
        //	J1 = M * D1
        //	J2 = M * D2
        //	e = M * v
        //
        double	D1D2v[jacRows*jacCols];

        // Use a different function, depending on the parametrization used for the rotations.
        #ifdef SO3_PARAMETRIZATION
            so3EssentialEvaluation(xData + DOF*xIndex, xData + DOF*yIndex, D1D2v, 1e-32);
        #else
            quaternionEssentialEvaluation(xData + DOF*xIndex, xData + DOF*yIndex, D1D2v);
        #endif

        // Get reduced matrix M for the pair of views 'x,y'
        //const QVMatrix &reducedM = reducedMatricesGraph[index];
        const QVMatrix &reducedM = iterator.value();
        const int reducedMCols = reducedM.getCols();
		Q_ASSERT(reducedM.getRows() == 9);
		Q_ASSERT(reducedM.getCols() <= 9);
		Q_ASSERT(reducedM.getCols() > 0);

        // Get the matrix of jacobians and evaluation vector with the following operation:
        //	[J1|J2|e] = M x [D1|D2|v]
        //
        double	J1J2e[jacRows*jacCols]; 	// [J1|J2|e]
        cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, reducedMCols, jacCols, jacRows, 1.0, reducedM.getReadData(), reducedMCols, D1D2v, jacCols, 0.0, J1J2e, jacCols);

		if (freeCamera[xIndex])
			{
	        // Update elements of the objective vector
		    cblas_dgemv(CblasRowMajor, CblasTrans, reducedMCols, DOF, 1.0, J1J2e, jacCols, J1J2e+jacCols-1, jacCols, 0.0, temp1, 1);	// J1^T * e
		    cblas_daxpy(DOF, 1.0, temp1, 1, objectivesData + DOF*xIndex, 1);	// objective element 'x' += J1^T * e
	        // Update diagonal block (xIndex, xIndex) of the Hessian matrix.
			//std::cout << " A2 " << std::endl;
		    cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, DOF, DOF, reducedMCols, 1.0, J1J2e,	jacCols, J1J2e, jacCols, 0.0, J1J1Data, DOF);			// J1^T * J1
			//std::cout << " A3 " << std::endl;
		    cblas_daxpy(DOF*DOF, 1.0, J1J1Data, 1, diags + xIndex*DOF*DOF, 1);	// Diagonal block 'x' += J1^T*J1
			}

		if (freeCamera[yIndex])
			{
	        // Update elements of the objective vector.
		    cblas_dgemv(CblasRowMajor, CblasTrans, reducedMCols, DOF, 1.0, J1J2e+DOF, jacCols, J1J2e+jacCols-1, jacCols, 0.0, temp2, 1);	// J2^T * e
		    cblas_daxpy(DOF, 1.0, temp2, 1, objectivesData + DOF*yIndex, 1);	// objective element 'y' += J2^T * e
	        // Update diagonal block (yIndex, yIndex) of the Hessian matrix.
			//std::cout << " A4 " << std::endl;
		    cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, DOF, DOF, reducedMCols, 1.0, J1J2e+DOF,	jacCols, J1J2e+DOF,	jacCols, 0.0, J2J2Data, DOF);			// J2^T * J2
			//std::cout << " A5 " << std::endl;
		    cblas_daxpy(DOF*DOF, 1.0, J2J2Data, 1, diags + yIndex*DOF*DOF, 1);	// Diagonal block 'y' += J2^T*J2
			}

		if (freeCamera[xIndex] and freeCamera[yIndex])
			{
	        // Update off-diagonal block (xIndex, yIndex) of the Hessian matrix.
			//std::cout << " A6 " << std::endl;
	        cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, DOF, DOF, reducedMCols, 1.0, J1J2e, 	jacCols, J1J2e+DOF, 	jacCols, 0.0, J1J2.getWriteData(), DOF);	// J1^T * J2
			//std::cout << " A7 " << std::endl;
	        estimatedH.setBlock(xIndex, yIndex, J1J2);				// Hessian block 'x,y' = J1^T*J2
			}

        #ifdef DEBUG // -----------------------------------------------------------------
		jacobianEvaluations++;

        // The following lines check for NaN values in the Jacobian matrices.

        // A NaN value can appear at:
        //	- The input reduced matrix.
        //	- The input view pose parameters.
        //	- The estimated matrix 'D1D2v', containing the Jacobian matrices and the objective vector.
       /* if (QVVector(DOF*DOF, xData + DOF*xIndex).containsNaN())
            {
            errorFound = true;
            std::cout << "[globalEpipolarAdjustment] Error: NaN value found in the vector for view pose " << xIndex << std::endl;
            }

        if (QVVector(DOF*DOF, xData + DOF*yIndex).containsNaN())
            {
            errorFound = true;
            std::cout << "[globalEpipolarAdjustment] Error: NaN value found in the vector for view pose " << yIndex << std::endl;
            }*/

        // Do not check for NaN values in the 'D1D2v' matrix if a NaN value was found at the view pose vectors.
        if (QVVector(jacRows*jacCols, D1D2v).containsNaN() and not errorFound)
            {
            errorFound = true;

            std::cout << "[globalEpipolarAdjustment] Error: NaN value found in Jacobian matrix for views (" << xIndex << ", " << yIndex << ")." << std::endl;

            // Try a simple diagnose of the reason why a NaN value was found at matrix 'D1D2v'.
            const QVVector view1(DOF, xData + DOF*xIndex), view2(DOF, xData + DOF*yIndex);

            if (view1 == view2)
                	std::cout << "[globalEpipolarAdjustment] Reason: poses for views " << xIndex << " and " << yIndex << " are numerically EQUAL." << std::endl;
            else	{
		            std::cout << "[globalEpipolarAdjustment] View 1 pose vector:" << std::endl << QVEuclideanMapping3(view1).toRotationTranslationMatrix() << std::endl;
		            std::cout << "[globalEpipolarAdjustment] View 2 pose vector:" << std::endl << QVEuclideanMapping3(view2).toRotationTranslationMatrix() << std::endl;
		            std::cout << "[globalEpipolarAdjustment] Values for Jacobian matrix:" << std::endl << QVVector(jacRows*jacCols, D1D2v) << std::endl;
		            }
            }

        if (reducedM.containsNaN())
            {
            errorFound = true;
            std::cout << "[globalEpipolarAdjustment] Error: NaN value found in reduced matrix for views (" << xIndex << ", " << yIndex << ")." << std::endl;
            }

        // If an error was found, try a diagnose in some cases.
        if (errorFound)
            // Error diagnose.
            break;
        #endif // ------------------------ DEBUG -----------------------------------------
        }

    // Set the diagonal elements of the Hessian matrix corresponding to free cameras, from the vector 'diags'.
    for(int i = 0; i < numCameras; i++)
        {
        const QVMatrix diagMatrix(DOF, DOF, diags + i*DOF*DOF);
        estimatedH.setBlock(i,i, diagMatrix);
        }

    #ifdef DEBUG // -----------------------------------------------------------------
   // std::cout << "[globalEpipolarAdjustment] Number of Jacobian evaluations = " << jacobianEvaluations << std::endl;
	if (errorFound)
		return false;
    #endif // ------------------------ DEBUG -----------------------------------------

    return true;
    }

// --------------------------------------------------------------------------------------

// Adds the value 'value' to the diagonal elements of an input sparse matrix.
void addTrace(const double value, QVSparseBlockMatrix &H)
    {
    for(int k = 0; k < H.getMajorRows(); k++)
        {
        QVMatrix &M = H[k][k];
        for (int j = 0; j < M.getCols(); j++)
            M(j,j) += value;
        }
    }

// --------------------------------------------------------------------------------------

QList<QVCameraPose> globalEpipolarAdjustment(
										const int numIterations,
									    const QList<QVCameraPose> &initialCameraPoses,
									    const QVDirectedGraph<QVMatrix> &reducedMatricesGraph,
									    const double lambda,
									    const bool adaptativeLambda,
										const TQVSparseSolve_Method solveMethod,
									    const int secondLevelIterations
									    )
	{
	QVector<bool> freeCameras(initialCameraPoses.count(), true);
	freeCameras[0] = false;

	return globalEpipolarAdjustment(numIterations, initialCameraPoses, reducedMatricesGraph, freeCameras, lambda, adaptativeLambda, solveMethod, secondLevelIterations);
	}

int gea_time_eval = 0, gea_time_solve = 0;
QList<QVCameraPose> globalEpipolarAdjustment(
						const int numIterations,
                        const QList<QVCameraPose> &initialCameraPoses,
                        const QVDirectedGraph<QVMatrix> &reducedMatricesGraph,
						const QVector<bool> &freeCameras,
                        const double lambda,
                        const bool adaptativeLambda,
						const TQVSparseSolve_Method solveMethod,
                        const int secondLevelIterations
                        )
    {
	#ifdef DEBUG
    std::cout << "[globalEpipolarAdjustment] Number of terms in the GEA cost error function = " << reducedMatricesGraph.count() << std::endl;
	#endif // DEBUG

    const int numCameras = initialCameraPoses.count();

    // Degrees of freedom for each camera (DOF): size of each camera in the vector 'x' obtained below.
    // Depending on the parametrization of the rotations in the camera poses, this value will be 3+3
    // (for a so3 rotation vector) or 4+3 (for quaternion rotation parametrization):
    #ifdef SO3_PARAMETRIZATION
        const int DOF = 6;
    #else
        const int DOF = 7;
    #endif

    QTime time;

    // Create vector 'x', containing the coordinates of each camera pose (orientations and centers) in the corresponding parametrization.
    // @note Esta parte con el data-set dubrovnik, y números de vistas de 88 o más, se lleva un tiempo significativamente alto.
    time.start();
    QVVector x;
    foreach(QVCameraPose cameraPose, initialCameraPoses)
        #ifdef SO3_PARAMETRIZATION
            x << lnSO3(cameraPose.getOrientation()) << cameraPose.getCenter();
        #else
            x << QVVector(cameraPose);
        #endif

    // Variables to accumulate the time spend on the main stages of the function.
    gea_time_eval = 0;
    gea_time_solve = 0;

    // Main optimization loop.
    // Apply for a fixed number of iterations.
    // In the near future: also stop when a maximal residual error is reached.
    QVVector xInc(numCameras * DOF, 0.0);
    for(int iteration = 0; iteration < numIterations; iteration++)
        {
        // Evaluate function and Hessian estimation.
        time.start();
        QVSparseBlockMatrix	H;
        QVVector b;
        if ( not evaluateGEAHessianAndObjectiveVector(numCameras, DOF, reducedMatricesGraph, freeCameras, x, H, b) )
            {
            std::cout << "[globalEpipolarAdjustment] Stopping optimization at iteration " << iteration << std::endl;
            break;
            }

        // Evaluate the trace of the matrix H.
        // Add a lambda value modified by the trace to the diagonal elements of the Hessian matrix
        const double factor = adaptativeLambda? lambda * H.trace() / (numCameras*DOF): lambda;
        addTrace(factor, H);

        gea_time_eval += time.elapsed();

        // Solve for 'xInc' the linear system:
        //	H xInc = b
        time.start();
        sparseSolve(H, xInc, b, true, true, solveMethod, true, true, secondLevelIterations);
        gea_time_solve += time.elapsed();

        // Update vector 'x'
        x = x - xInc;

        #ifdef DEBUG // -----------------------------------------------------------------
		if (iteration == 0)
	        std::cout << "[globalEpipolarAdjustment] Increment for diagonal of H at iteration " << iteration << " is " << factor << std::endl;

        // Check that increment vector does not contains NaN values.
        if (xInc.containsNaN())
            {
            std::cout << "[globalEpipolarAdjustment] Error: NaN value found in increment vector at iteration " << iteration << ". Stopping." << std::endl;
            break;
            }

		// Check that Hessian rows and cols corresponding to fixed cameras contain 'zero' valued blocks.
        foreach(int ib, H.keys())
            {
            const QMap<int, QVMatrix> &majorRow = H[ib];
            foreach(int jb, majorRow.keys())
				{
				// Permit diagonal blocks corresponding to fixed cameras to contain a diagonal matrix.
				if (ib == jb)
					{
					if (not majorRow[ib].isDiagonal() and not freeCameras[ib])
				        std::cout << "[globalEpipolarAdjustment] Error: Diagonal Hessian block " << ib << " is not diagonal." << std::endl;
					continue;
					}
				if ( not freeCameras[ib] and majorRow.contains(jb) )
			        std::cout << "[globalEpipolarAdjustment] Error: Hessian block " << ib << ", " << jb << " is not zero: " << majorRow[jb] << " while camera " << ib << " is fixed." << std::endl;
				if ( not freeCameras[jb] and majorRow.contains(jb) )
			        std::cout << "[globalEpipolarAdjustment] Error: Hessian block " << ib << ", " << jb << " is not zero: " << majorRow[jb] << " while camera " << jb << " is fixed." << std::endl;
				}
            }

		// Check that the size of the increment vector is correct.
		if (xInc.count() != numCameras * DOF)
			std::cout << "[globalEpipolarAdjustment] Error: size of increment vector should be " << (numCameras * DOF) << "(" << numCameras << " cameras, and " << DOF << " DOF's) but is " << xInc.count() << std::endl;

		// Check that the increment obtained for parameters corresponding to fixed cameras is zero.
		for(int i = 0, idx = 0; i < numCameras; i++)
			for(int j = 0; j < DOF; j++, idx++)
				if (not freeCameras[i] and xInc[idx] != 0.0)
					std::cout << "[globalEpipolarAdjustment] Error: increment " << j << " for fixed camera " << i << " is not zero." << std::endl;

        #endif // ------------------------ DEBUG -----------------------------------------
        }

    // Compose the list of optimized camera poses, from the vector 'x'.
    QList<QVCameraPose> optimizedCameraPoses;
    for(int i = 0; i < numCameras; i++)
        #ifdef SO3_PARAMETRIZATION
            optimizedCameraPoses << QVCameraPose(QVQuaternion(expSO3(QV3DPointF(x.mid(DOF*i, 3)))), QV3DPointF(x.mid(DOF*i+3,3)));
        #else
            optimizedCameraPoses << QVCameraPose(QVQuaternion(x.mid(DOF*i, 4)), QV3DPointF(x.mid(DOF*i+4,3)) );
        #endif

    // Return the list of optimized camera poses.
    return optimizedCameraPoses;
    }

QList<QVCameraPose> incrementalGEA(	const int numIterations,
                    const QList<QVCameraPose> &initialCameraPoses,
                    const QVDirectedGraph<QVMatrix> &reducedMatricesGraph,
                    const int numFreeCameras,
                    const double lambda,
                    const bool adaptativeLambda,
                    const TQVSparseSolve_Method solveMethod,
                    const int secondLevelIterations
                    )
    {
    std::cout << "WARNING: 'incrementalGEA' deprecated. Use function 'globalEpipolarAdjustment' to perform incremental GEA optimization." << std::endl;
    // Number of cameras.
    const int	numCameras = initialCameraPoses.count(),
            freeCameras = MIN(numFreeCameras, numCameras),
            fixedCameras = numCameras - freeCameras,
            firstFreeCameraIndex = fixedCameras;

    // Evaluate GEA Jacobian and residual only for terms involving one or two free cameras.
    QList<QPoint> incrementalLinks;
    foreach(QPoint link, reducedMatricesGraph.keys())
        if (link.x() >= firstFreeCameraIndex or link.y() >= firstFreeCameraIndex)
            incrementalLinks << link;

    // Degrees of freedom for each camera (DOF): size of each camera in the vector 'x' obtained below.
    // Depending on the parametrization of the rotations in the camera poses, this value will be 3+3
    // (for a so3 rotation vector) or 4+3 (for quaternion rotation parametrization):
    #ifdef SO3_PARAMETRIZATION
        const int DOF = 6;
    #else
        const int DOF = 7;
    #endif

    QTime time;

    // Create vector 'x', containing the coordinates of each camera pose (orientations and centers) in the corresponding parametrization.
    // @note Esta parte con el data-set dubrovnik, y números de vistas de 88 o más, se lleva un tiempo significativamente alto.
    time.start();
    QVVector x;
    foreach(QVCameraPose cameraPose, initialCameraPoses)
        #ifdef SO3_PARAMETRIZATION
            x << lnSO3(cameraPose.getOrientation()) << cameraPose.getCenter();
        #else
            x << QVVector(cameraPose);
        #endif
    // const int time_data_initialization = time.elapsed();

    // Variables to accumulate the time spend on the main stages of the function.
    gea_time_eval = 0;
    gea_time_solve = 0;

    // Main optimization loop.
    // Apply for a fixed number of iterations.
    // In the near future: also stop when a maximal residual error is reached.
    //QVVector xInc(numCameras * DOF, 0.0);
    for(int i = 0; i < numIterations; i++)
        {
        // Evaluate Hessian and objective vector.
        time.start();
        QVSparseBlockMatrix J;
        QVVector r;
        evaluateGEAJacobianAndResidual(numCameras, DOF, reducedMatricesGraph, incrementalLinks, x, J, r);
        QVSparseBlockMatrix H = J.dotProduct(J, true, false);
        QVVector b = J.dotProduct(r, true);

        // Eliminate columns for the Jacobian corresponding to fixed cameras.
        QVSparseBlockMatrix simplifiedJ = QVSparseBlockMatrix(J.getMajorRows(), freeCameras, J.getMinorRows(), J.getMinorCols());
        foreach(int ib, J.keys())
            {
            const QMap<int, QVMatrix> &majorRow = J[ib];
            foreach(int jb, majorRow.keys())
                if (jb >= firstFreeCameraIndex)
                    simplifiedJ.setBlock(ib, jb - firstFreeCameraIndex, majorRow[jb]);
            }

        H = simplifiedJ.dotProduct(simplifiedJ, true, false);
        b = simplifiedJ.dotProduct(r, true);
        gea_time_eval += time.elapsed();

        // When using the 'sparseSolve' function assuming symmetric non-singular matrix,
        // the lower triangular area of the coefficient matrix should be zero.
        QVSparseBlockMatrix H2(H.getMajorRows(), H.getMajorCols(), H.getMinorRows(), H.getMinorCols());
        foreach(int ib, H.keys())
            {
            QMap<int, QVMatrix> &majorRow = H[ib];
            foreach(int jb, majorRow.keys())
                if (ib <= jb)
                    H2.setBlock(ib, jb, majorRow[jb]);
            }

        // Program fails when using MKL to solve with H instead of H2?. It shouldn't.
        //H = H2;
        //std::cout << "[incrementalGEA] Debug: ||H - H2|| = " << (QVMatrix(H) - QVMatrix(H2)).norm2() / ( QVMatrix(H).norm2() + QVMatrix(H2).norm2() ) << std::endl;

        // Evaluate the trace of the matrix H.
        // Add a lambda value modified by the trace to the diagonal elements of the Hessian matrix
        const double factor = adaptativeLambda? lambda * H2.trace() / (numCameras*DOF): lambda;

        #ifdef DEBUG
        std::cout << "[globalEpipolarAdjustment] Increment for diagonal of H at iteration " << i << " is " << factor << std::endl;
        #endif

        addTrace(factor, H2);

        time.start();
        QVVector xIncPartial;
        sparseSolve(H2, xIncPartial, b, true, true, solveMethod, true, true, secondLevelIterations);

        QVVector xInc(fixedCameras * DOF, 0.0);
        xInc << xIncPartial;
        gea_time_solve += time.elapsed();

        // Sanity check.
        if (xInc.containsNaN())
            {
            std::cout << "[globalEpipolarAdjustment] Error: NaN value found in 'x' increment at iteration " << i << ". Stopping." << std::endl;
            break;
            }

        // Update vector 'x'
        x = x - xInc;
        }

    #ifdef DEBUG
    std::cout << "[globalEpipolarAdjustment] Number of Jacobian evaluations = " << reducedMatricesGraph.getLinks().count() << std::endl;
    #endif

    // Compose the list of optimized camera poses, from the vector 'x'.
    QList<QVCameraPose> optimizedCameraPoses;
    for(int i = 0; i < numCameras; i++)
        #ifdef SO3_PARAMETRIZATION
            optimizedCameraPoses << QVCameraPose(QVQuaternion(expSO3(QV3DPointF(x.mid(DOF*i, 3)))), QV3DPointF(x.mid(DOF*i+3,3)));
        #else
            optimizedCameraPoses << QVCameraPose(QVQuaternion(x.mid(DOF*i, 4)), QV3DPointF(x.mid(DOF*i+4,3)) );
        #endif

    // Return the list of optimized camera poses.
    return optimizedCameraPoses;
    }

