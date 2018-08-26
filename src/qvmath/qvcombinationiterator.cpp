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

#include <QVCombinationIterator>

bool QVCombinationIterator::increment()
	{
	if (endCondition == true)
		return false;

	const int siz = size();
	int pivot = siz-1;

	// Get the first element for which there is a gap with the previous
	for (int i=0; (pivot == siz-1) && (i < siz-1); i++)
		// See if there is a gap between actual element and next element
		if (operator[](i+1) > operator[](i) + 1)
			pivot = i;

	//Increment element at pivot index
	operator[](pivot)++;

	// Take all elements after pivot element to start
	for (int i = 0; i < pivot; i++)
		operator[](i) = i;

	// Check finishing condition
	if (operator[](siz-1) == numElements)
		endCondition = true;

	return not endCondition;
	}

std::ostream& operator << ( std::ostream &os, const QVCombinationIterator &combination)
	{
	os << "Combination(" << combination.getSubsetsSize() << " elements over " << combination.getSetCardinallity() << "):\t";

	for (int j = 0; j < combination[0]; j++)
		os << "  " << j << " ";
	os << " [" << combination[0] << "]";

	for (int i = 1; i < combination.getSubsetsSize(); i++)
		{
		for (int j = combination[i-1]+1; j < combination[i]; j++)
			os << "  " << j << " ";
		os << " [" << combination[i] << "]";
		}

	for (int j = combination[combination.getSubsetsSize()-1]; j < combination.getSetCardinallity()-1; j++)
		os << "  " << (j+1) << " ";

	os << std::endl;

	return os;
	}
