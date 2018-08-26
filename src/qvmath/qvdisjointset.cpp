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

#include <qvdefines.h>
#include <QVDisjointSet>

QVDisjointSet::QVDisjointSet(uInt elements): cols(0), rows(0), elements(elements), parent(elements), rank(elements), count(elements)
    {
    Q_ASSERT_X(elements > 0, "QVDisjointSet", "Number of elements equals 0 in constructor");
    //allocData();
    makeSet();
    }

QVDisjointSet::QVDisjointSet(const QVDisjointSet &other):
	cols(other.cols),
	rows(other.rows),
	elements(other.elements),
	parent(other.parent),
	rank(other.rank),
	count(other.count)
    {
    Q_ASSERT_X(elements > 0, "QVDisjointSet", "Number of elements equals 0 in constructor");
    //allocData();
    //makeSet();
    }

QVDisjointSet::QVDisjointSet(uInt cols, uInt rows): cols(cols), rows(rows), elements(cols*rows)
    {
    Q_ASSERT_X(cols > 0, "QVDisjointSet", "Number of columns equals 0 in constructor");
    Q_ASSERT_X(rows > 0, "QVDisjointSet", "Number of rows equals 0 in constructor");
    //allocData();
    makeSet();
    }

QVDisjointSet::QVDisjointSet(const QVGenericImage &image):	cols(image.getCols()), rows(image.getRows()), elements(cols*rows),
															parent(elements), rank(elements), count(elements)
    {
    Q_ASSERT_X(cols > 0, "QVDisjointSet", "Number of columns equals 0 in constructor");
    Q_ASSERT_X(rows > 0, "QVDisjointSet", "Number of rows equals 0 in constructor");
    //allocData();
    makeSet();
    }

//QVDisjointSet::~QVDisjointSet()
//    {
    //Q_ASSERT_X(parent != 0, "~QVDisjointSet", "Parent array not allocated");
    //Q_ASSERT_X(rank != 0, "~QVDisjointSet", "Rank array not allocated");
    //freeData();
//    }

uInt QVDisjointSet::unify(uInt index1, uInt index2)
    {
    Q_ASSERT_X(index1 < elements, "QVDisjointSet::unify", "First index exceeds number of elements");
    Q_ASSERT_X(index2 < elements, "QVDisjointSet::unify", "Second index exceeds number of elements");

    // Trivial case: elements are the same.
    if ( index1 == index2 )
        return index1;

    uInt root1 = find(index1), root2 = find(index2);

    // Trivial case: elements belong to the same set.
    if ( root1 == root2 )
        return root1;

    // Addon to union-find algorithm to keep count of number of sets with constant cost
    sets--;

    Q_ASSERT_X(sets > 0 , "QVDisjointSet::unify", "Number of sets reached 0");

    if (rank[root1] > rank[root2])
        {
        uInt temp = root1;
        root1 = root2;
        root2 = temp;
        }

    Q_ASSERT_X(rank[root1] == MIN(rank[root1], rank[root2]), "QVDisjointSet::unify", "first root is minimal");
    Q_ASSERT_X(rank[root2] == MAX(rank[root1], rank[root2]), "QVDisjointSet::unify", "first root is maximal");

    if (rank[root1] == rank[root2])
        rank[root2] = rank[root2] +1;

    parent[root1] = root2;

    // Addon to union-find algorithm to keep count of cardinality of sets with constant cost
    count[root2] += count[root1];

    Q_ASSERT_X(find(index1) == find(index2) , "QVDisjointSet::unify", "Parent for indexes don't coincide, after unify");
    Q_ASSERT_X(root2 == find(index1) , "QVDisjointSet::unify", "Root2 is not the root for elements.");

    return root2;
    }

void QVDisjointSet::makeSet()
    {
    sets = elements;
    for (uInt index = 0; index < elements; index++)
        {
        rank[index] = 0;
        count[index] = 1;
        parent[index] = index;
        }
    }

/*void QVDisjointSet::allocData()
    {
    parent = QVector<uInt>(elements);
    rank = QVector<uInt>(elements);
    count = QVector<uInt>(elements);
    }*/

//void QVDisjointSet::freeData()
//    {
  //  delete parent;
  //  delete rank;
  //  delete count;
//    }

