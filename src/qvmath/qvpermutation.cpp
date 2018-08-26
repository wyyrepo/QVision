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

/// @file
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#include <QString>
#include <QVVector>
#include <QVMatrix>

#include <QVPermutation>

bool QVPermutation::checkConsistency() const {
		QVector<bool> check(size(), false);
        //bool check[size()];
        //for(int i=0;i<size();i++)
        //        check[i] = false;
        for(int i=0;i<size();i++) {
                if( (operator[](i) < 0) or (operator[](i) >= size()) )
                        return FALSE;
                check[operator[](i)] = true;
        }
        for(int i=0;i<size();i++)
                if(not check[i])
                        return FALSE;
        return TRUE;
}


QVMatrix QVPermutation::toMatrix() const
{
    if(not checkConsistency())
        qFatal("Inconsistent QVPermutation in QVPermutation::toMatrix()");
    QVMatrix result(size(),size(),0.0);
    for(int i=0;i<size();i++)
        result(i,operator[](i)) = 1.0;
    return result;
}

int QVPermutation::signature() const
{
    int p=0, n=size();
	QVector<bool> v(n, false);
    //bool v[n];
    //for(int j=0;j<n;j++)
    //    v[j] = false;

    for(int j=0;j<n;j++) {
        if(v[j])
            ++p;
        else {
            int x = j;
            do {
                x = operator[](x);
                v[x] = true;
            } while (x != j);
        }
    }
    if(p&1)
        return -1;
    else
        return +1;
}

QVPermutation QVPermutation::fromMatrix(const QVMatrix &matrix)
{
    const int m=matrix.getRows();
#  ifndef QT_NO_DEBUG
    const int n=matrix.getCols();
#  endif
    Q_ASSERT(m == n);
    QVPermutation perm(m);
    for(int i=0;i<m;i++)
        perm[i] = matrix.getRow(i).maxIndex();

    if(not perm.checkConsistency())
        qFatal("QVPermutation::fromMatrix() called with matrix where the position of the maximum elements in each row do not generate a permutation matrix");

    return perm;
}

std::ostream& operator << ( std::ostream &os, const QVPermutation &vector )
    {
    const int size = vector.size();

        os << "QVPermutation (" << size << ") [ ";

    for (int i = 0; i < size; i++)
                os << qPrintable(QString("%1").arg(vector[i])) << " ";

    os << "]";
    return os;
    }
