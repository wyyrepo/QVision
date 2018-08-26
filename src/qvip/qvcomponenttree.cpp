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
#include <QVComponentTree>

QVComponentTree::QVComponentTree(const QVImage<uChar,1> &image, bool inverseTree, bool /*useAlternative*/): numNodes(0), freePoints(0), inverseTree(inverseTree)
	{
	const uInt cols = image.getCols(), rows = image.getRows();

	this->numNodes = 0;
	this->leafNodes = 0;
	this->freePoints = 0;
	this->totalPoints = 0;
	this->maxNodes = cols * rows;
	this->nodes.resize(maxNodes/10);	// 10 factor is an heuristic value, estimated from several tries.

	if (inverseTree)
		{
		QVImage<uChar> notImage(cols, rows);

		QVIMAGE_INIT_READ(uChar,image);
		QVIMAGE_INIT_WRITE(uChar,notImage);
		for (uInt col = 0; col < cols; col++)
			for (uInt row = 0; row < rows; row++)
				QVIMAGE_PIXEL(notImage, col, row,0) = 255 - QVIMAGE_PIXEL(image, col, row,0);

		getComponentTree(notImage);
		}
	else
		getComponentTree(image);
	}

void QVComponentTree::getComponentTree(const QVImage<uChar> &image)
	{
	qDebug() << "getComponentTree()";
	const uInt cols = image.getCols(), rows = image.getRows();

	QVIMAGE_INIT_READ(uChar,image);

	const QVector< QVector< QPoint > > points = CountingSort(image);
	QVDisjointSet disjointSet(cols, rows);

	uInt *nodeID = new uInt[maxNodes];
	for(uInt i=0; i<maxNodes; i++)
		nodeID[i] = NULL_NODE;

	// This loop creates the structure of the component tree, using the disjoint set, transversiong the pixels of the image
	// ordered by their gray-scale value, sorted thanks to 'CountingSort' function.
	for (int threshold = 0; threshold < points.size(); threshold++)
		{
		// We join in the disjoint set pixels with gray-scale equal to threshold, with adjacent regions, or pixels, with
		// a gray-scale value equal or lesser than threshold. This is done here only for the disjoint set.
		//
		// Also, here are also joined component tree nodes which have in common one of the processed points.
		for (int n=0; n< points[threshold].size(); n++)
			{
			const uInt	col = points[threshold][n].x(),  
					row = points[threshold][n].y();			// coordinates of the current pixel
			const uChar	actualPixel = QVIMAGE_PIXEL(image, col, row,0); // Value of the current pixel
			uInt		actualSet = disjointSet.find(col, row);		// canonical element of the subset

			// Transverse neighbourhood of a pixel looking for close pixels to join with
			// (those with gray-scale level lower or equal to that of the actual pixel)
			for (uInt i = (uInt) MAX(0,(int)col-1); i< MIN(cols, col+2); i++)  // we look at the 8 rounding neighbours
				for (uInt j = (uInt) MAX(0,(int)row-1); j< MIN(rows, row+2); j++)
					if ((col != i) || (row != j))
					{
					const uChar vecinoPixel = QVIMAGE_PIXEL(image, i, j, 0);  // neighbour's gray-level 
					if (vecinoPixel <= actualPixel)
						{
						const uInt vecinoSet = disjointSet.find(i,j);  // neighbour's canonical element
						if (vecinoSet != actualSet)
							{
							// We should join this pixel to the set of the neighbour
							// Each canonical element of a subset has a nodeID element which contains information about the region.
							const uInt actualNodeID = nodeID[actualSet], vecinoNodeID = nodeID[vecinoSet];
	
							actualSet = disjointSet.unify(col, row, i, j); // both subsets are unified.
	
							Q_ASSERT(disjointSet.find(disjointSet.index(col, row)) == disjointSet.find(disjointSet.index(i, j)));
	
							// If actual point is not in a node already, we associate it with the point that is
							// associated to a node.
							if (vecinoNodeID == NULL_NODE)
								nodeID[actualSet] = actualNodeID;
							else if (actualNodeID == NULL_NODE)
								nodeID[actualSet] = vecinoNodeID;
							else	// Otherwise, both actual and neighbour are associated to a node already.
								// We create a new node, and join both nodes of actual and neighbour pixels to
								// that one.
								{
								// We check that no one of the nodes of actual and neighbour pixels
								// is new. In that case it will be parent node.
								if (!closedNode(actualNodeID) && closedNode(vecinoNodeID))
									// We just add the node...
									{
									addChild(actualNodeID, vecinoNodeID);
									nodeID[actualSet] = actualNodeID;
									}
								else if (closedNode(actualNodeID) && !closedNode(vecinoNodeID))
									// We just add the other node...
									{
									addChild(vecinoNodeID, actualNodeID);
									nodeID[actualSet] = vecinoNodeID;
									}
								else if (closedNode(actualNodeID) && closedNode(vecinoNodeID))
									// We have two old nodes, and create a parent to unify them.
									{
									const uInt newNodeID = newNode(col, row, threshold);
									addChild(newNodeID, actualNodeID);
									addChild(newNodeID, vecinoNodeID);
	
									//nodeID[actualIndex] = newNodeID;
									nodeID[actualSet] = newNodeID;
									}
								else // if ( !NODE(actualNodeID).closed and !NODE(vecinoNodeID).closed )
									// We have two parent nodes, we leave things as they are.
									// No, we should unify both, passing childs of one of them to the
									// other.
									{
									Q_ASSERT(closedNode(actualNodeID) == false);
									Q_ASSERT(closedNode(vecinoNodeID) == false);
									Q_ASSERT(numChilds(actualNodeID) > 0);
									Q_ASSERT(numChilds(vecinoNodeID) > 0);
	
									mergeNodes(actualNodeID, vecinoNodeID);
									nodeID[actualSet] = actualNodeID;
									}
								}
	
							// Actualize areas for the resulting parent node.
							if (nodeID[actualSet] != NULL_NODE)
								{
								/// @TODO Repasar este assert, que si se descomenta protesta de un QVector "index out of range"
								//Q_ASSERT(area(actualNodeID)[lastThreshold(actualNodeID)]
								//	<= disjointSet.getSetCardinality(actualIndex));
								lastThreshold(nodeID[actualSet]) = threshold;
								area(nodeID[actualSet])[threshold] = disjointSet.getSetCardinality(actualSet);
								}
	
							Q_ASSERT(nodeID[disjointSet.find(disjointSet.index(col, row))] ==
								nodeID[disjointSet.find(disjointSet.index(i, j))]);
							}
						}
					}
			}

		// In this loop we actualize areas for the gray-level of the threshold of the two old nodes, and create new nodes, 
		// case we find a set of one or several pixels of gray-scale value equal to threshold value, which are not joined
		// to any connected set represented already in a node of the component tree.
		//
		// In this point, we have processed all pixels with gray-scale value equal or lesser to threshold. All of them are
		// grouped to a group of pixels with same gray-scale level, in which case we have the vertex of a node, or well
		// or well joined to a previously created node.
		//
		// Then we creater for the former case new nodes, and in any case we actualize areas for nodes with new points
		// in them.
		for (int n=0; n< points[threshold].size(); n++)
			{
			const uInt	col = points[threshold][n].x(),
					row = points[threshold][n].y(),
					actualIndex = disjointSet.index(col, row),
					actualSet = disjointSet.find(actualIndex);

			Q_ASSERT_X(threshold < 256, "getComponentTree", "out of bounds 4");
			Q_ASSERT_X(actualIndex < cols * rows, "getComponentTree", "out of bounds 5");

			// We have a pixel with gray-scale level equal to threshold, and disjoint set identifier equal to
			// himself.
			// This means either it is an isolated pixel, surrounded by pixels of gray-scale level higher than his, or
			// that he is in a connected set of pixels, all of them with exactly gray-scale level value of threshold
			// (and we hill be the only one of that set, with disjoint set identifier equal to himself).
			// Either case we create a new node, with seed point equal to this node.
			if (actualIndex == actualSet)
				{
				if (nodeID[actualIndex] == NULL_NODE)
					// We have a header point for the new component tree node.
					// We initialize the values for his node.
					{
					nodeID[actualSet] = newNode(col, row, threshold);
					area(nodeID[actualSet])[threshold] = disjointSet.getSetCardinality(actualSet);

					this->leafNodes++;
					}
				else	// Actual pixel is associated to a node, but this one was created for other pixel.
					// We count as a free pixel the one that created the node that contains actual pixel.
					this->freePoints++;
				}
			else	// Actual pixel is not its group head
				this->freePoints++;

			const uInt actualNodeID = nodeID[actualSet];

			if (actualNodeID != NULL_NODE)
				{
				// Actualize histogram for the node of the actual pixel.
				//lastThreshold(actualNodeID) = threshold;
				//area(actualNodeID)[threshold] = disjointSet.getSetCardinality(actualIndex);

				// Close node for the actual pixel, if open.
				closedNode(actualNodeID) = true;
				}

			// Actualize total number of points processed.
			this->totalPoints++;
			}
		}

	rootNode() = nodeID[disjointSet.find(0)];

	// Component tree finished, performing some tests....
	#ifndef QT_NO_DEBUG
	//testComponentTree(image, disjointSet);
	#endif

	delete nodeID;

	qDebug() << "getComponentTree() <~ return";
	}
