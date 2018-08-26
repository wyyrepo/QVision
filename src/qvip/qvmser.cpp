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

#include <QVMSER>
#include <qvmath.h>

void getMSERContours(const QVImage<uChar, 1> &image, const QList<QVMSER> &MSERList, QList< QVPolyline > &polylineMSERList)
	{
	const uInt rows = image.getRows(), cols = image.getCols();

	QVImage<uChar> notImage = image;
	for (uInt col = 0; col < cols; col++)
		for (uInt row = 0; row < rows; row++)
			// Weird: using the following line produces a core error:
			//notImage(col, row) = 255 - image(col, row);
			notImage(col, row) = 255 - notImage(col, row);

	for (int msers = 0; msers < MSERList.size(); msers++)
		{
		QVPolyline polylineMSER = getConnectedSetBorderContourThreshold(notImage,
						MSERList.at(msers).seed,  255 - MSERList.at(msers).threshold);
		polylineMSERList.append (polylineMSER);
		}
	}

#define	RELATIVE_DISTANCE(X,Y)	(ABS((X-Y)/(Y)))
void getMSER(const QVImage<uChar,1> &image, QList<QVMSER> &MSERList, const int delta, const int minArea, const int maxArea, const double diffAreaThreshold)
	{
	/////////////////
	// Prune low areas from image, with component tree
	QVComponentTree componentTree(image);

	/////////////////
	// Tree transversing
	uInt histogram[256];
	double q_function[256];

	for (uInt node = 0; node < componentTree.getNumNodes(); node++)
		{
		int firstThres = componentTree.firstThreshold(node), lastThres = componentTree.lastThreshold(node);

		if (lastThres - firstThres - 2*delta - 2 < 0)
			continue;

		// We obtain histogram
		for (int threshold = firstThres; threshold <= lastThres; threshold++)
				{
				uInt area = componentTree.area(node)[threshold], lastHistogramValue = 0 /* esta variable no sería necesaria, se puede asignar area */;
				if(area != 0)
					lastHistogramValue = area;
				histogram[threshold] = lastHistogramValue;
				}

		// Calculate 'q' function (from the paper)
		for (int threshold = firstThres + delta; threshold <= lastThres - delta; threshold++)
			{
			q_function[threshold] = (double)(histogram[threshold + delta] - histogram[threshold - delta]) / histogram[threshold];
			}

		// Get local minima of the function, and append them to MSER list
		int lastMSERThreshold = -1, minLastMSERThreshold = 0;
		for (int threshold = firstThres + delta + 1; threshold <= lastThres - delta - 1; threshold++)
			{
			if ( ((int)histogram[threshold] < minArea) || ((int)histogram[threshold] > maxArea) )
				continue;

			if ( (q_function[threshold + 1] > q_function[threshold]) && (q_function[threshold - 1] > q_function[threshold]) )
				// We have a minimum in the q function
				{
				if (lastMSERThreshold == -1)
					// We don't have any previous local minima in the node
					{
					lastMSERThreshold = threshold;
					minLastMSERThreshold = threshold;
					}
				else
					if (RELATIVE_DISTANCE((float)histogram[lastMSERThreshold], (float)histogram[threshold]) < diffAreaThreshold)
						// if distance with last minima isn't enough, we just actialize minimum MSER
						{
						if (q_function[minLastMSERThreshold] > q_function[threshold])
								minLastMSERThreshold = threshold;
						}
					else	// We have a previous minima, and far enough from the actual minimum, we add the smallest MSER found in the previous set of minimums
						{
						MSERList.append(QVMSER(QPoint(componentTree.seedX(node), componentTree.seedY(node)), minLastMSERThreshold));
						lastMSERThreshold = threshold;
						minLastMSERThreshold = threshold;
						}
				}
			}
		if (lastMSERThreshold != -1)
			MSERList.append(QVMSER(QPoint(componentTree.seedX(node), componentTree.seedY(node)), minLastMSERThreshold));
		}

	}

