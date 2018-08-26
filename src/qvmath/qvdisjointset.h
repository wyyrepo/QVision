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

#ifndef QVDISJOINTSET_H
#define QVDISJOINTSET_H

#include <QVImage>

#define	INDEX(Col, Row)	(Row*cols + Col)

/*!
@class QVDisjointSet qvmath/qvdisjointset.h QVDisjointSet
@brief Implementation of a disjoint set data type, based on the <a href="http://en.wikipedia.org/wiki/Disjoint-set_data_structure">union-find algorithm</a>.

@ingroup qvmath

This implementation makes use of \htmlonly <a href="http://en.wikipedia.org/wiki/Disjoint-set_data_structure#Disjoint-set_forests">union-find</a>\endhtmlonly
algorithms to maintain partitions efficiently. It is essentially built for maintaining disjoint sets of unsigned integer elements, in the rank from 0 to a given maximum element.

QVDisjointSet objects created with the constructor @ref QVDisjointSet(uInt) partition the set \f$ S_{maxElement} \in \aleph, S_{maxElement} = \{0 .. maxElement\} \f$ in <i>maxElement</i> different sets, each one containing one of the elements of the set \f$ S_{maxElement} \f$. Given 'maxElement' will be pass to the constructor
to allocate data for the disjoint set.

Later, @ref unify(uInt,uInt) and @ref find(uInt) functions can be used respectively to join subsets of the partition, and to find which elements of the set \f$ S_{maxElement} \f$ are in the same subset.

Internally, all elements contained in the same subset in a partition are linked with one of those elements. That element will be the canonical element of the subset, and @ref find(uInt) function retrieves that integer value.

Join two subsets is as simple as using @ref unify(uInt,uInt) passing as parameters an element from each subset. After joining, using @ref find(uInt) with any of those elements, or any contained in the original two sets joined, will return the same
canonical element.

The class QVDisjointSet can be used to maintain partitions of general sets, as long as there is a bijection mapping between the set to be partitioned, and a set \f$ S_{maxElement} \f$. An example of use of the class QVDisjointSet, for a general set \f$ G \f$ given <i>G_MAX_ELEMENT</i> being the element to which corresponds the maximal integer value, could be this:

@code
// Create disjoint set, with at least as many elements as the set G.
QVDisjointSet disjointSet(G_MAX_ELEMENT.toInt());

[...]

// Let element1, element2, ... be elements contained in the set G.
// Configure structure of the disjoint set using unify function:
disjointSet.unify(element1.toInt(), element2.toInt());
disjointSet.unify(element3.toInt(), element4.toInt());
[...]

// Let elementA and elementB be elements contained in the set G.
// Test whether elementA and elementB are contained in the same subset of the partition:
if (disjointSet.find(elementA.toInt()) == disjointSet.find(elementB.toInt()))
    // case elements belong to the same subset in the disjoint set.
else
    // elementA and elementB are not in the same subset of the disjoint set.

[...]
@endcode

This class however is specially design for dealing with sets of points in an image. Constructors @ref QVDisjointSet(uInt,uInt) and @ref QVDisjointSet(const QVGenericImage&) can be used to create disjoint sets prepared to represent a partition of the set of pixels contained in an image, without the need of converting points in the image, to integer values.

For that matter, functions union and find were overloaded to receive points in QPoint format (see @ref find(QPoint) and @ref unify(QPoint,QPoint) functions), and in coordinate pair format (see @ref find(uInt,uInt) and @ref unify(uInt,uInt,uInt,uInt) functions). The previous example, using QVDisjointSet to partitionate the points in a QVImage, could be rewritten like this:

@code
// The QVImage to partition:
QVImage<uChar> image(cols, rows);

// Create disjoint set, from
QVDisjointSet disjointSet(image);

[...]

// Configure structure of the disjoint set using unify function:
disjointSet.unify(QPoint(1,2), QPoint(2,1));
disjointSet.unify(QPoint(4,5), QPoint(3,4));
[...]

// Test whether points (10,9) and (8,8) are contained in the same subset of the partition:
if (disjointSet.find(QPoint(10,9)) == disjointSet.find(QPoint(8,8)))
    // case points belong to the same subset in the disjoint set.
else
    // given points are not in the same subset of the disjoint set.

[...]
@endcode

It can also be rewritten using @ref find(uInt,uInt), @ref unify(uInt,uInt,uInt,uInt), and @ref QVDisjointSet(uInt,uInt), coordinate pair format overloaded versions of those functions:

@code
// The QVImage to partition:
QVImage<uChar> image(cols, rows);

// Create disjoint set, from
QVDisjointSet disjointSet(cols, rows);

[...]

// Configure structure of the disjoint set using unify function:
disjointSet.unify(1, 2, 2, 1));
disjointSet.unify(4, 5, 3, 4));
[...]

// Test whether points (10,9) and (8,8) are contained in the same subset of the partition:
if (disjointSet.find(10,9) == disjointSet.find(8,8))
    // case points belong to the same subset in the disjoint set.
else
    // given points are not in the same subset of the disjoint set.

[...]
@endcode
*/

class QVDisjointSet
    {
    public:
        /// @brief Constructs a disjoint set.
        ///
        /// This constructor creates a QVDisjointSet object that will maintain a partition over the set of integers
        /// in the range 0..numElements.
        ///
        /// @param numElements maximal element contained in the disjoint set.
        QVDisjointSet(uInt numElements);

        /// @brief Constructs a QVDisjointSet object, that will maintain a partition of the set of pixels in
        /// an image.
        ///
        /// You can only use functions @ref find(QPoint p), @ref find(uInt col, uInt row),
        /// @ref unify(QPoint p1, QPoint p2), and @ref unify(uInt c1, uInt r1, uInt c2, uInt r2)
        /// if the QVDisjointSet were created with this constructor, or the constructor
        /// @ref QVDisjointSet(const QVGenericImage&).
        ///
        /// @param cols number of cols of the image to be partitionated.
        /// @param rows number of rows of the image to be partitionated.
        /// @see QVDisjointSet(QVGenericImage &image)
        /// @see find(QPoint p)
        /// @see find(uInt col, uInt row)
        /// @see unify(QPoint p1, QPoint p2)
        /// @see unify(uInt c1, uInt r1, uInt c2, uInt r2)
        QVDisjointSet(uInt cols, uInt rows);

        /// @brief Constructs a QVDisjointSet object, that will maintain a partition of the set of pixels in a given image.
        ///
        /// You can only use functions @ref find(QPoint p), @ref find(uInt col, uInt row),
        /// @ref unify(QPoint p1, QPoint p2), and @ref unify(uInt c1, uInt r1, uInt c2, uInt r2)
        /// if the QVDisjointSet were created with this constructor, or the constructor
        /// @ref QVDisjointSet(uInt cols, uInt rows).
        ///
        /// @param image image containing the pixels to partition.
        /// @see QVDisjointSet(uInt cols, uInt rows)
        /// @see find(QPoint p)
        /// @see find(uInt col, uInt row)
        /// @see unify(QPoint p1, QPoint p2)
        /// @see unify(uInt c1, uInt r1, uInt c2, uInt r2)
        QVDisjointSet(const QVGenericImage &image);

        /// @brief Copy constructor.
		QVDisjointSet(const QVDisjointSet &other);

        //~QVDisjointSet();

        /// @brief Overloaded version of find, for partitions over the set of points contained in an image.
        ///
        /// The function takes a point (QPoint <i>p</i>) as parameter, and converts it into an integer automatically.
        /// Then calls @ref find(uInt) to obtain the canonical element (uInt) of the group that holds the integer
        /// corresponding to the point <i>p</i>.
        ///
        /// This method can only be used if the disjoint set was constructed with the constructors
        /// @ref QVDisjointSet(uInt,uInt) or @ref QVDisjointSet(const QVGenericImage&). Otherwise the class
        /// can not convert the image point into an integer number.
        ///
        /// @see QVDisjointSet(uInt cols, uInt rows)
        /// @see QVDisjointSet(const QVGenericImage&)
        /// @see find(uInt)
        ///
        /// @param p point contained in the image.
        /// @returns canonical element of the subset from the partition, that contains point <i>p</i>
        inline uInt find(QPoint p)
            {
            Q_ASSERT_X(cols > 0, "QVDisjointSet::find", "Number of columns equals 0");
            Q_ASSERT_X(rows > 0, "QVDisjointSet::find", "Number of rows equals 0");

            /// ASSERT: point belongs to rectangle (0,0), (cols, rows)
            Q_ASSERT_X(QRect(0,0,cols, rows).contains(p), "QVDisjointSet::find", "QPoint out of image bounds");
            return find(INDEX(p.x(), p.y()));
            }

        /// @brief Overloaded version of find, for partitions over the set of points contained in an image.
        ///
        /// The function takes the coordinates of a point (col, row) as parameter, and converts it into an integer
        /// automatically.
        /// Then calls @ref find(uInt) to obtain the canonical element (uInt) of the group that holds the integer
        /// corresponding to the point <i>p</i>.
        ///
        /// This method can only be used if the disjoint set was constructed with the constructors
        /// @ref QVDisjointSet(uInt,uInt) or @ref QVDisjointSet(const QVGenericImage&). Otherwise the class
        /// can not convert the image point into an integer number.
        ///
        /// @see QVDisjointSet(uInt cols, uInt rows)
        /// @see QVDisjointSet(const QVGenericImage&)
        /// @see find(uInt)
        ///
        /// @param col first coordinate of the point.
        /// @param row second coordinate of the point.
        /// @returns canonical element of the subset from the partition that contains point of coordinates (col, row).
        inline uInt find(uInt col, uInt row)
            {
            Q_ASSERT_X(cols > 0, "QVDisjointSet::find", "Number of columns equals 0");
            Q_ASSERT_X(rows > 0, "QVDisjointSet::find", "Number of rows equals 0");
            Q_ASSERT_X(QRect(0,0,cols, rows).contains(QPoint(col, row)),
                    "QVDisjointSet::find", "QPoint out of image bounds");
            return find(INDEX(col, row));
            }

        /// @brief Retrieves a common integer identifier, for any element in the same subset of the partition.
        ///
        /// @param index number identifying the element.
        /// @see find(QPoint p)
        /// @see find(uInt col, uInt row)
        inline uInt find(uInt index)
            {
            Q_ASSERT_X(index < elements, "QVDisjointSet::find", "Index exceeds number of elements");

            if (parent[index] == index)
                return index;

            if (parent[parent[index]] != parent[index])
                parent[index] = find(parent[index]);

            return parent[index];
            }

        /// @brief Joins two subsets of points.
        ///
        /// This is an overloaded version of unify, for partitions over the set of points contained in an image.
        /// The function converts automatically both elements of the points of an image, represented with QPoints
        /// <i>p1</i> and <i>p2</i>, into integers, to apply later the function @ref unify(uInt,uInt) to join both
        /// subsets containing the corresponding integer elements for <i>p1</i> and <i>p2</i>.
        ///
        /// This method can only be used if the disjoint set was constructed with the constructors
        /// @ref QVDisjointSet(uInt,uInt) or @ref QVDisjointSet(const QVGenericImage&). Otherwise the class
        /// can not convert the image point into an integer number.
        ///
        /// @see QVDisjointSet(uInt cols, uInt rows)
        /// @see QVDisjointSet(const QVGenericImage&)
        /// @see unify(uInt,uInt)
        ///
        /// @param p1 element contained in the first set to be join.
        /// @param p2 element contained in the second set to be join.
        /// @returns canonical element of the subset resulting from the union of both subsets.
        inline uInt unify(QPoint p1, QPoint p2)
            {
            Q_ASSERT_X(cols > 0, "QVDisjointSet::unify", "Number of columns equals 0");
            Q_ASSERT_X(rows > 0, "QVDisjointSet::unify", "Number of rows equals 0");
            Q_ASSERT_X(QRect(0,0,cols, rows).contains(p1), "QVDisjointSet::unify", "First QPoint out of image bounds");
            Q_ASSERT_X(QRect(0,0,cols, rows).contains(p2), "QVDisjointSet::unify", "Second QPoint out of image bounds");

            return unify(INDEX(p1.x(),p1.y()),INDEX(p2.x(),p2.y()));
            }

        /// @brief Overloaded version of unify, for partitions over the set of points contained in an image.
        ///
        /// The function converts automatically both elements of the points of an image, represented with QPoints
        /// <i>p1</i> and <i>p2</i>, into integers, to apply later the function @ref unify(uInt,uInt) to join both
        /// subsets containing elements <i>p1</i> and <i>p2</i>.
        ///
        /// This method can only be used if the disjoint set was constructed with the constructors
        /// @ref QVDisjointSet(uInt,uInt) or @ref QVDisjointSet(const QVGenericImage&). Otherwise the class
        /// can not convert the image point into an integer number.
        ///
        /// @see QVDisjointSet(uInt cols, uInt rows)
        /// @see QVDisjointSet(const QVGenericImage&)
        /// @see unify(uInt,uInt)
        ///
        /// @param c1 first coordinate of a point from the first set.
        /// @param r1 second coordinate of a point front the first set.
        /// @param c2 first coordinate of a point frond the second set.
        /// @param r2 second coordinate of a point frown the second set.
        /// @returns canonical element of the subset resulting from the union of both subsets.
        inline uInt unify(uInt c1, uInt r1, uInt c2, uInt r2)
            {
            Q_ASSERT_X(cols > 0, "QVDisjointSet::unify", "Number of columns equals 0");
            Q_ASSERT_X(rows > 0, "QVDisjointSet::unify", "Number of rows equals 0");
            Q_ASSERT_X(QRect(0,0,cols, rows).contains(QPoint(c1, r1)),
                    "QVDisjointSet::unify", "First QPoint out of image bounds");
            Q_ASSERT_X(QRect(0,0,cols, rows).contains(QPoint(c2, r2)),
                    "QVDisjointSet::unify", "Second QPoint out of image bounds");

            return unify(INDEX(c1,r1),INDEX(c2,r2));
            }

        /// @brief Joins two subsets.
        ///
        /// Given two elements of the partitionated set (or their set indexes), joins the two subsets that contain those elements in a new subset.
        ///
        /// @param index1 number identifying first element.
        /// @param index2 number identifying second element.
        /// @see unify(QPoint p1, QPoint p2)
        /// @see unify(uInt c1, uInt r1, uInt c2, uInt r2)
        /// @return the canonical element for the new set.
        uInt unify(uInt index1, uInt index2);

        /// @brief Gets the number of elements contained in the set that includes the given element.
        ///
        /// @param p1 point contained in the set.
        /// @returns number of elements contained in the set.
        inline uInt getSetCardinality(const QPoint &p1)	{ return getSetCardinality(INDEX(p1.x(), p1.y())); }

        /// @brief Gets the number of elements contained in the set that uncles the given element.
        ///
        /// @param col first coordinate of the point.
        /// @param row second coordinate of the point.
        /// @returns number of elements contained in the set.
        inline uInt getSetCardinality(uInt col, uInt row)	{ return getSetCardinality(INDEX(col, row)); }

        /// @brief Gets the number of elements contained in the set that includes the given element.
        ///
        /// @param index identifying integer of the element contained in the set.
        /// @returns number of elements contained in the set.
        inline uInt getSetCardinality(uInt index)
            {
            Q_ASSERT(count[find(index)] > 0);
            return count[find(index)];
            }

        /// @brief Gets the number of different subgroups contained in the disjoint set.
        ///
        /// @returns number of different subgroups held in the disjoint set.
        inline uInt numberOfSets() const	{ return sets; }

        /// @brief Gets the number corresponding to the given point, in the integer set.
        ///
        /// @param p point contained in the image.
        /// @returns number corresponding to the given point in the disjoint set.
        inline uInt index(QPoint p) const { return INDEX(p.x(), p.y()); }

        /// @brief Gets the number corresponding to the given point, in the integer set.
        ///
        /// @param col first coordinate of the point.
        /// @param col second coordinate of the point.
        /// @returns number corresponding to the given point in the disjoint set.
        inline uInt index(uInt col, uInt row) const { return INDEX(col, row); }

        /// @brief Checks if a given element is the root of its set.
        ///
        /// @param col first coordinate of the point.
        /// @param col second coordinate of the point.
        /// @returns true if the element is the canonical element of its group, false otherwise.
        /// @see isRootElement(uInt index)
        inline bool isRootElement(uInt col, uInt row) const { return isRootElement(INDEX(col, row)); }

        /// @brief Checks if a given element is the root of its set.
        ///
        /// This function is a replacement for the expression:
        ///
        /// \code (find(index) == index) \endcode
        ///
        /// Faster than that expression, if <i>find</i> is not needed to be called.
        /// @param col first coordinate of the point.
        /// @param col second coordinate of the point.
        /// @returns true if the element is the canonical element of its group, false otherwise.
        inline bool isRootElement(uInt index) const { return parent[index] == index; }

    private:
        uInt cols, rows, elements, sets;
		QVector<uInt> parent, rank, count;
		//uInt *parent, *rank, *count;

        void makeSet();
        //void allocData();
        //void freeData();
    };
#endif
