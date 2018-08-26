/*
 *	Copyright (C) 2010, 2011, 2012. PARP Research Group.
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

#include <QVSparseBlockMatrix>

#ifdef MKL_AVAILABLE
  #include "mkl_dss.h"
#endif

QVSparseBlockMatrix QVSparseBlockMatrix::transpose() const
    {
    QVSparseBlockMatrix result(majorCols, majorRows, minorCols, minorRows);

    for(int i = 0; i < majorRows; i++)
        for(int j = 0; j < majorCols; j++)
            if (operator[](i)[j] != QVMatrix())
                result[j][i] = operator[](i)[j].transpose();

    return result;
    }

QVSparseBlockMatrix QVSparseBlockMatrix::dotProduct(const QVSparseBlockMatrix &other,
                    const bool transposeFirstOperand,
                    const bool transposeSecondOperand) const
    {
        /*if (majorCols != other.majorRows)
        {
        std::cout << "ERROR: tried to multiply sparse block matrices with incompatible number of blocks." << std::endl
                        << "\tMatrix 1 number of blocks:\t" << majorRows << "x" << majorCols << std::endl
                        << "\tMatrix 2 number of blocks:\t" << other.majorRows << "x" << other.majorCols << std::endl;
        exit(1);
        }

    if (minorCols != other.minorRows)
        {
        std::cout << "ERROR: tried to multiply sparse block matrices with incompatible block sizes." << std::endl
            << "\tMatrix 1 blocks sizes:\t" << minorRows << "x" << minorCols << std::endl
            << "\tMatrix 2 blocks sizes:\t" << other.minorRows << "x" << other.minorCols << std::endl;
        exit(1);
        }*/

    if (transposeSecondOperand)
        std::cout << "Warning: dotProduct method can't perform the multiplication transposing the second term matrix yet. " << std::endl;

        QVSparseBlockMatrix result(	transposeFirstOperand? majorCols : majorRows,
                            other.majorCols,
                            transposeFirstOperand? minorCols: minorRows,
                            other.minorCols);

    foreach(int index1r, keys())
        {
        const QMap<int, QVMatrix> & majorRowFirstOperand = operator[](index1r);

        foreach(int index1c, majorRowFirstOperand.keys())
                {
                const QVMatrix & actual = majorRowFirstOperand[index1c];

                const int	i_ = transposeFirstOperand? index1c : index1r,
                        k_ =transposeFirstOperand? index1r : index1c;

                const QMap<int, QVMatrix> & majorRowSecondOperand = other[k_];
                QMap<int, QVMatrix> & majorRowResult = result[i_];

                foreach(int j, majorRowSecondOperand.keys())
                    {
                    QVMatrix &res = majorRowResult[j];

                    if (res == QVMatrix())
                        res = actual.dotProduct(majorRowSecondOperand[j], transposeFirstOperand, false);
                    else
                        /// @todo mejorar operador de incremento para matrices
                        res += actual.dotProduct(majorRowSecondOperand[j], transposeFirstOperand, false);
                    }
                }
        }
    return result;
    }

QVVector QVSparseBlockMatrix::dotProduct(const QVVector &vector, const bool transposeMatrix) const
    {
    const int	majorSourceIndex = transposeMatrix? majorRows: majorCols,
            minorSourceIndex = transposeMatrix? minorRows: minorCols;

    const int	majorDestinationIndex = transposeMatrix? majorCols: majorRows,
            minorDestinationIndex = transposeMatrix? minorCols: minorRows;

    // Get sparse block vector
    QVector< QVVector > sparseBlockVector(majorSourceIndex);
    for(int i = 0; i < majorSourceIndex; i++)
        sparseBlockVector[i] = vector.mid(i*minorSourceIndex, minorSourceIndex);

    // Multiply sparse block vector by sparse block matrix
    QVector< QVVector > sparseBlockResult(majorDestinationIndex, QVVector(minorDestinationIndex, 0.0));
    foreach(int i, keys())
        {
        const QMap<int, QVMatrix> & majorRow = operator[](i);
        foreach(int j, majorRow.keys())
            if (not transposeMatrix)
                /// @todo mejorar operador de incremento para vectores
                sparseBlockResult[i] += majorRow[j].dotProduct(sparseBlockVector[j], transposeMatrix);
            else
                sparseBlockResult[j] += majorRow[j].dotProduct(sparseBlockVector[i], transposeMatrix);
        }

    // Get dense vector from sparse block vector
    QVVector result(majorDestinationIndex*minorDestinationIndex);
    double *resultPtr = result.data();

    int i = 0;
    foreach(QVVector v, sparseBlockResult)
        {
        const double *vPtr = v.constData();
        double *blockVectorPtr = resultPtr + minorDestinationIndex*i;

        for(int j = 0; j < minorDestinationIndex; j++)
            blockVectorPtr[j] = vPtr[j];
        i++;
        }

    return result;
    }

QVSparseBlockMatrix & QVSparseBlockMatrix::operator=(const QVSparseBlockMatrix &other)
    {
    majorRows = other.majorRows;
    majorCols = other.majorCols;
    minorRows = other.minorRows;
    minorCols = other.minorCols;

    //*(QMap<int, QMap<int, QVMatrix> > *)this = QMap<int, QMap<int, QVMatrix> >();
    //foreach(int ib, other.keys())
    //	{
    //	const QMap<int, QVMatrix> &majorRow = other[ib];
    //	foreach(int jb, majorRow.keys())
    //		this->setBlock(ib, jb, majorRow[jb]);
    //	}

    QMap<int, QMap<int, QVMatrix> >::operator=(other);
    return *this;
    }

// Generate random positive definite block matrix (NBxNB blocks, each NxN size), with given probability NZProb of off-diagonal
// nonzero blocks (by construction, diagonal is always nonzero):
QVSparseBlockMatrix QVSparseBlockMatrix::randomSquare(const int NB,const int N, const double NZProb, const bool symmetric, const bool positive)
{
    QVSparseBlockMatrix result(NB,NB,N,N);

    if(symmetric and positive) {
        QVSparseBlockMatrix inter(NB*(NB+1)/2,NB,N,N);

        int row = 0;
        for(int i=0;i<NB;i++) {
            for(int j=i;j<NB;j++) {
                double roulette=random(0.0,1.0);
                if( (i==j) or (roulette <= NZProb)) {
                    inter.setBlock(row,i,QVMatrix::random(N,N));
                    inter.setBlock(row,j,QVMatrix::random(N,N));
                }
                row++;
            }
        }

        result = inter.dotProduct(inter,true,false);
    } else if (symmetric and not positive) {
        for(int i=0;i<NB;i++) {
            for(int j=i;j<NB;j++) {
                double roulette=random(0.0,1.0);
                if( (i==j) or (roulette <= NZProb)) {
                    QVMatrix inter = QVMatrix::random(N,N);
                    if(i==j)
                        result.setBlock(i,j,(inter+inter.transpose())/2);
                    else {
                        result.setBlock(j,i,inter);
                        result.setBlock(i,j,inter.transpose());
                    }
                }
            }
        }
    } else if (not symmetric and not positive) {
        for(int i=0;i<NB;i++) {
            for(int j=0;j<NB;j++) {
                double roulette=random(0.0,1.0);
                if( (i==j) or (roulette <= NZProb)) {
                    QVMatrix inter = QVMatrix::random(N,N);
                    result.setBlock(i,j,inter);
                }
            }
        }
    } else { // not symmetric and positive: error
        qFatal("QVSparseBlockMatrix::randomSquare(): not symmetric and positive definite matrix requested");
    }

    return result;
}


//--------------------------

#ifdef MKL_AVAILABLE
MKLPardisoSparseFormat::MKLPardisoSparseFormat(const QVSparseBlockMatrix qvspmatrix, bool isSymmetric):
    majorRows(qvspmatrix.getMajorRows()), majorCols(qvspmatrix.getMajorCols()),
    minorRows(qvspmatrix.getMinorRows()), minorCols(qvspmatrix.getMinorCols())
    {
    // Subblock rows (sbm) and columns (sbn):
    int sbr = qvspmatrix.getMinorRows();
    int sbc = qvspmatrix.getMinorCols();
    // Block rows (br) and block columns (bc):
    int br = qvspmatrix.getMajorRows();
    int bc = qvspmatrix.getMajorCols();

    // Initialization:
    nRows = sbr*br;
    nCols = sbc*bc;

    // Compute total number of nonzero blocks (tb), as well as number of matrices in the diagonal (nmd):
    int tb = 0, nmd = 0;
    foreach(int ib, qvspmatrix.keys())
        foreach(int jb, qvspmatrix[ib].keys())
            {
            if(isSymmetric)
                {
                if(ib <= jb)
                    tb++;
                if(ib == jb)
                    nmd++;
                }
            else
                tb++;
            }

    // Total number of nonzero elements:
    nNonZeros = tb*sbr*sbc;
    if(isSymmetric)
        nNonZeros -= nmd*(sbr>sbc ? sbr*sbc-sbc*(sbc+1)/2 : sbr*(sbr-1)/2);

    // Create space and fill three PARDISO arrays:
    rowIndex = new _INTEGER_t [nRows+1];
    columns = (nNonZeros==0) ? NULL : new _INTEGER_t [nNonZeros];
    values = (nNonZeros==0) ? NULL : new _DOUBLE_PRECISION_t [nNonZeros];
    int indexvalues = 0, indexrows = 0;
    foreach(int ib, qvspmatrix.keys())
        {
        const QMap<int, QVMatrix> &majorRow = qvspmatrix[ib];

        for(int i=0;i<sbr;i++)
            {
            rowIndex[indexrows] = indexvalues + 1;
            foreach(int jb, majorRow.keys())
                {
                int increment = 0;
                for(int j=0;j<sbc;j++)
                    {
                    if(isSymmetric and ( (ib > jb) or ( (ib == jb) and (i > j) ) ) )
                        continue;
                    values[indexvalues] = majorRow[jb](i,j);
                    columns[indexvalues] = jb*sbc + j + 1;
                    indexvalues++;
                    increment++;
                    }

                //std::cout << "Increment = " << increment << std::endl;
                //std::cout << "estimated = " << ( isSymmetric?sbc: (sbc/2+1) )<< std::endl;
                }
            indexrows++;
            }
        }
    rowIndex[indexrows] = indexvalues + 1;

    /*for(int i=0;i<nRows+1;i++)
    std::cout << rowIndex[i] << " ";
    std::cout << "\n";
    for(int i=0;i<nNonZeros;i++)
    std::cout << columns[i] << " ";
    std::cout << "\n";
    for(int i=0;i<nNonZeros;i++)
    std::cout << values[i] << " ";
    std::cout << "\n";*/

    }

MKLPardisoSparseFormat::~MKLPardisoSparseFormat()
{
    if(rowIndex != NULL) delete [] rowIndex;
    if(columns != NULL) delete [] columns;
    if(values != NULL) delete [] values;
}

void squareSymmetricSparseMatrixToPardisoFormat(const QVSparseBlockMatrix &qvspmatrix, MKLPardisoSparseFormat &pardiso)
    {
    //std::cout << "[squareSymmetricSparseMatrixToPardisoFormat] xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl;
    pardiso.majorRows = qvspmatrix.getMajorRows();
    pardiso.majorCols = qvspmatrix.getMajorCols();
    pardiso.minorRows = qvspmatrix.getMinorRows();
    pardiso.minorCols = qvspmatrix.getMinorCols();

    // ---------------------------------------
    // Subblock rows (sbm) and columns (sbn):
    int sbr = qvspmatrix.getMinorRows();
    int sbc = qvspmatrix.getMinorCols();

    // Block rows (br) and block columns (bc):
    int br = qvspmatrix.getMajorRows();
    int bc = qvspmatrix.getMajorCols();

    if (br != bc)
        {
        std::cout << "ERROR 01" << std::endl;
        exit(0);
        }

    if (sbr != sbc)
        {
        std::cout << "ERROR 02" << std::endl;
        exit(0);
        }

    // Initialization:
    pardiso.nRows = sbr*br;
    pardiso.nCols = sbc*bc;

    // Compute total number of nonzero blocks (tb), as well as number of matrices in the diagonal (nmd):

    // Total number of nonzero elements:
    pardiso.nNonZeros = qvspmatrix.blockCount * sbc * sbr - bc * sbr*(sbr-1)/2;
    pardiso.rowIndex = new int [pardiso.nRows+2];
    pardiso.columns = new int [pardiso.nNonZeros];
    pardiso.values = new double [pardiso.nNonZeros];
    //std::cout << "Non-zeros = " << pardiso.nNonZeros << std::endl;

    int tempIndex = 0, tempCount = 1;
    foreach(int ib, qvspmatrix.keys())
        {
        const QMap<int, QVMatrix> &majorRow = qvspmatrix[ib];

        for(int i = 0; i < sbr; tempCount += sbc*majorRow.count() - i, i++)
            pardiso.rowIndex[tempIndex++] = tempCount;
        pardiso.rowIndex[tempIndex] = tempCount;

        int rowBlockCount = 0;
        foreach(int jb, majorRow.keys())
            {
            const double *matrixData = majorRow[jb].getReadData();
            for(int i=0;i<sbr;i++)
                {
                if (ib > jb)
                    {
                    std::cout << "------------------ ***** &&& Error 989577546435634 *********** -----------------" << std::endl;
                    continue;
                    }

                const double *rowData = matrixData + sbc*i;
                int indexvalues = pardiso.rowIndex[ib * sbr + i]-1 + rowBlockCount * sbc - ((ib != jb)?i:0);

                for(int j=0;j<sbc;j++)
                    {
                    if( (ib == jb) and (i > j) )
                        continue;

                    pardiso.values[indexvalues] = rowData[j];
                    pardiso.columns[indexvalues] = jb*sbc + j + 1;
                    indexvalues++;
                    }
                }
            rowBlockCount++;
            }
        }
    }
#endif
