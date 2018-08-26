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

#ifndef QVCOMBINATIONITERATOR_H
#define QVCOMBINATIONITERATOR_H

#include <qvmath.h>
#include <QVector>

/*!
@class QVCombinationIterator qvmath/qvcombinationiterator.h QVCombinationIterator
@brief Iterator over all possible <a href="http://en.wikipedia.org/wiki/Combination">combinations</a> over a set.

Generates a sequence containing all the possible subsets of a given cardinallity, from a original set.
This set will be the integer numbers from zero to an specified value, so the elements of the original set should be contained in a QList or a QVector.


Use examples: The following examples show how to use this iterator.
<ul>
<li><i>While</i> flavour:
@code
QVCombinationIterator combination(7, 3);

while(!combination.finished())
    {
    std::cout << combination;
    combination.increment();
    }
@endcode</li>
<li><i>Do.. while</i> flavour:
@code
QVCombinationIterator combination(7, 3);

do	std::cout << combination;
    while(combination.increment());
@endcode</li>
<li><i>For</i> flavour:
@code
for (QVCombinationIterator combination(7, 3); !combination.finished(); combination++)
    std::cout << combination;
@endcode</li>

All of the previous examples will print the resulting combination of elements from the original set, producing the following output:
@code
Combination(3 elements over 7):  [0] [1] [2]  3   4   5   6
Combination(3 elements over 7):  [0] [1]  2  [3]  4   5   6
Combination(3 elements over 7):  [0]  1  [2] [3]  4   5   6
Combination(3 elements over 7):   0  [1] [2] [3]  4   5   6
Combination(3 elements over 7):  [0] [1]  2   3  [4]  5   6
Combination(3 elements over 7):  [0]  1  [2]  3  [4]  5   6
Combination(3 elements over 7):   0  [1] [2]  3  [4]  5   6
Combination(3 elements over 7):  [0]  1   2  [3] [4]  5   6
Combination(3 elements over 7):   0  [1]  2  [3] [4]  5   6
Combination(3 elements over 7):   0   1  [2] [3] [4]  5   6
Combination(3 elements over 7):  [0] [1]  2   3   4  [5]  6
Combination(3 elements over 7):  [0]  1  [2]  3   4  [5]  6
Combination(3 elements over 7):   0  [1] [2]  3   4  [5]  6
Combination(3 elements over 7):  [0]  1   2  [3]  4  [5]  6
Combination(3 elements over 7):   0  [1]  2  [3]  4  [5]  6
Combination(3 elements over 7):   0   1  [2] [3]  4  [5]  6
Combination(3 elements over 7):  [0]  1   2   3  [4] [5]  6
Combination(3 elements over 7):   0  [1]  2   3  [4] [5]  6
Combination(3 elements over 7):   0   1  [2]  3  [4] [5]  6
Combination(3 elements over 7):   0   1   2  [3] [4] [5]  6
Combination(3 elements over 7):  [0] [1]  2   3   4   5  [6]
Combination(3 elements over 7):  [0]  1  [2]  3   4   5  [6]
Combination(3 elements over 7):   0  [1] [2]  3   4   5  [6]
Combination(3 elements over 7):  [0]  1   2  [3]  4   5  [6]
Combination(3 elements over 7):   0  [1]  2  [3]  4   5  [6]
Combination(3 elements over 7):   0   1  [2] [3]  4   5  [6]
Combination(3 elements over 7):  [0]  1   2   3  [4]  5  [6]
Combination(3 elements over 7):   0  [1]  2   3  [4]  5  [6]
Combination(3 elements over 7):   0   1  [2]  3  [4]  5  [6]
Combination(3 elements over 7):   0   1   2  [3] [4]  5  [6]
Combination(3 elements over 7):  [0]  1   2   3   4  [5] [6]
Combination(3 elements over 7):   0  [1]  2   3   4  [5] [6]
Combination(3 elements over 7):   0   1  [2]  3   4  [5] [6]
Combination(3 elements over 7):   0   1   2  [3]  4  [5] [6]
Combination(3 elements over 7):   0   1   2   3  [4] [5] [6]
@endcode

Meaning the selected elements surrounded by brackets for each combination. The index for each one of the selected elements can be accessed with the @ref operator[]. The number of elements accessible with it can
be obtained with method @ref getSubsetsSize(), which is the size of the subsets.

@ingroup qvmath
*/


class QVCombinationIterator: public QVector<int>
    {
    private:
        int numElements;
        bool endCondition;

    public:
        /// @brief Constructs a default combination iterator.
        ///
        /// Generate a combination iterator with one element, and its internal state is defined to finished.
        QVCombinationIterator(): QVector<int>(1), numElements(1), endCondition(true)
            { }

        /// @brief Constructs a new combination iterator that is a copy of other.
        ///
        /// @param combinationIterator the combination iterator to be copied.
        QVCombinationIterator(const QVCombinationIterator &combinationIterator): QVector<int>(combinationIterator),
            numElements(combinationIterator.numElements), endCondition(combinationIterator.endCondition)
            { }

        /// @brief Constructs a new combination iterator with a specifics cardinallity and subset's size.
        ///
        /// The new combination iterator contains the first subset of the iteration.
        /// @param numElements the cardinallity of the susets, must be > 0.
        /// @param elementsXSet the subset's size, must be <= numElements.
        QVCombinationIterator(const int numElements, const int elementsXSet): QVector<int>(elementsXSet),
            numElements(numElements), endCondition(false)
            {
            Q_ASSERT(numElements > 0);
            Q_ASSERT(numElements >= elementsXSet);
            for (int i=0; i < elementsXSet; i++)
                operator[](i) = i;
            }

        virtual ~QVCombinationIterator() { }

        /// @brief Obtains the next subset of the iteration, indicating if the iteration has finished.
        ///
        /// Returns a true valor until it obtains the last subset, the following times
        /// it returns false valor and passes to an undefined subset.
        /// @returns true if it obtain the next subset and false if the iteration has finished.
        virtual bool increment();

        /// @brief infix ++ operator.
        ///
        /// Increment the iteration.
        // infix ++ operator
        QVCombinationIterator& operator++ ()	{ increment(); return *this; }

        /// @brief postfix ++ operator.
        ///
        /// Increment the iteration.
        // postfix ++ operator
        void operator++ (int)			{ ++(*this); }

        /// @brief Obtains the amount of possible subsets of a given size and cardinallity.
        ///
        /// The increment function returns a true valor the first getSubsetNmber - 1 invocations.
        /// @returns the number of posible subsets.
        double getSubsetNumber()	const	{ return qvCombination(numElements, size()); }

        /// @brief Indicate if the iteration has finished.
        /// @returns true if contains a valid subset, and false if has been incremented after it contains the last subset.
        bool finished()		const	{ return endCondition; }

        /// @brief Obtains the first element of the current subset.
        /// @returns the first element of the current subset.
        int firstIndex()		const	{ return first(); }

        /// @brief Obtains the last element of the current subset.
        /// @returns the last element of the current subset.
        int lastIndex()		const	{ return last(); }

        /// @brief Obtains the cardinallity of the combination.
        /// @returns the cardinallity.
        int getSetCardinallity()	const	{ return numElements; }

        /// @brief Obtains the subset's size.
        /// @returns subset's size.
        int getSubsetsSize()	const	{ return size(); }
    };

        /// @brief Return a stream with the current subset.
        ///
        /// The stream's format is:
        /// Combination(X elements over Y):  {[}0{]}  {[}1{]}  {[}2{]}  ... {[}Y{]}
        /// where "X" is the subset's size, "Y" the cardinallity and the brackets appears if the element its contain
        /// belongs to the subset.
        /// @returns the current subset's stream.
std::ostream& operator << ( std::ostream &os, const QVCombinationIterator &combination);

#endif
