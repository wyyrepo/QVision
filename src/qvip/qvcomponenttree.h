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

#ifndef QVCOMPONENTTREE_H
#define QVCOMPONENTTREE_H

/// @file
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <qvip.h>

#define	 NULL_NODE	256*256*256

/*!
@class QVComponentTree qvip/qvcomponenttree.h QVComponentTree
@brief Image component tree data structure.

A level set in a gray-scale image is a connected set of points (pixels) with a gray-scale level
above a given threshold. Component trees are built upon the inclusion relation of the level sets in
an image.

They are a representation useful to obtain non-flat connected component filters, that may preserve
connected components in the image, satisfying a given criterion. These trees are used in computer
vision for task like image segmentation, filtering, scale and rotation invariant image feature
extraction (like MSER, see [<a href="#matas">Matas</a>]), amongst other.

For a wider explanation about component trees, you can read paper [<a href="#rjones">Jones</a>].
The former implementation of component trees is very efficient, so that it can be used with regular
sized images (320x240 to 640x480, depending on the computer speed) in real-time programs.
It is based in the algorithm described in the paper [<a href="#najman">Najman</a>], which is supposed
to obtain the component tree in quasi-linear time.

There's a main difference between this implementation and that described in the paper. While the latter
constructs a node for each gray-level in a level set, this implementation compacts every gray-level
included in a same level set, in one node only. It will only be stored for every gray-level in the same
node it's histogram area; thus, every non-leaf node in QVision's component tree will have more than one
descendant, making smaller trees.

You can access the properties of a node by its index, using the functions @ref seedX and @ref seedY,
@ref firstThreshold, @ref lastThreshold, and @ref area. All of these accept as parameter the node index.

You can get the index of the different nodes of the tree by transversing it, using functions @ref rootNode,
@ref numChilds, @ref firstChild and @ref nextSibling. A code example of use of these functions is the following

@code
void processNode(QVComponentTree &componentTree, uInt nodeIndex)
	{
	std::cout << "Node seed: " << componentTree.seedX(nodeIndex) << ", "
	<< componentTree.seedY(nodeIndex) << std::endl;
	
	for (	int childIndex = componentTree.firstChild(nodeIndex);
		childIndex != NULL_NODE;
		childIndex = componentTree.nextSibling(childIndex) )
		processNode(componentTree, childIndex);
	}

void processComponentTree(QVComponentTree &componentTree)
	{
	processNode(componentTree, componentTree.rootNode());
	}
@endcode

This code transverses the component-tree in a depth-first pre-order walk, and just shows the horizontal and vertical
coordinate for each node's seed point.

Each node has a seed point, which is any of the points at the vertex of the node if it is a leaf node, or any
of the points with gray-level value close to the child nodes if it is an internal node. You can get the seed point
of a node with the functions @ref seedX and @ref seedY functions.

Also, every node saves information about the histogram areas of their gray-level values. With the functions
@ref firstThreshold and @ref lastThreshold you can obtain the lowest and the highest of the gray-level values of the
pixels in the node (if the tree is direct. If it is reversed, the highest and the lowest).

@section References
<ul>
<li><a name="rjones"><i>Component trees for image filtering and segmentation</i></a>. Ronald Jones.</li>
<li><a name="najman"><i>Building the component tree in quasi-linear time</i></a>. L. Najman and M. Couprie.</li>
<li><a name="matas"><i>Robust Wide Baseline Stereo from Maximally Stable Extremal Regions</i>. J. Matas et al.</li>
@ingroup qvip
*/
class QVComponentTree
	{
	public:
		/// @brief Constructs a component tree set, from a gray-scale image.
		///
		/// By default the leaf nodes will represent low gray-scale value areas in the image.
		/// 
		/// A reverse version of the tree can be created by setting the second parameter of the
		/// constructor ( <i>inverseTree</i> ) to true. In that case, leaf nodes will represent
		/// high gray-scale valued areas in the image, and will increase to lower gray-scale
		/// valued areas, as you transverse the tree to the root node.
		///
		/// \todo Check sum of childs for node equals numChilds(node)
		///
		/// @param image image to create from the component tree.
                /// @param inverseTree tells the function whether construct a direct or a reverse tree.
		QVComponentTree(const QVImage<uChar,1> &image, bool inverseTree= false, bool useAlternative = false);

                /// @brief Returns whether this tree is inverted or not.
		/// @returns true if the tree represent high gray-scale valued areas in the image, and false otherwise.
		bool isInverseTree()	const		{ return inverseTree; }

		/// @brief Returns index for the root node in the image.
		///
		/// Nodes in the component tree can be accessed by their index, that is a integer number.
		/// It is not assured that root node will have index zero for every component tree, so
		/// it's index should be obtained with this function.
		/// @returns index for the root node in the image.
		uInt & rootNode()			{ return rootNodeID; }

		/// @brief Returns horizontal coordinate for the seed point of a node, given it's index.
		///
		/// The seed point of a component tree's node is one of the points (or the point
		/// if it is unique) of the vertex of the region it represents.
		///
		/// Given the index of a node in the component tree, this function returns
		/// first coordinate of that point.
		/// @param index index for a node.
		/// @returns horizontal coordinate for seed point of that node.
		uInt & seedX(uInt index) 		{ return nodes[index].seedX; }

		/// @brief Returns vertical coordinate for the seed point of a node, given it's index.
		///
		/// The seed point of a component tree's node is one of the points (or the point
		/// if it is unique) of the vertex of the region it represents.
		///
		/// Given the index of a node in the component tree, this function returns
		/// second coordinate of that point.
		/// @param index index for a node.
		/// @returns vertical coordinate for seed point of that node.
		uInt & seedY(uInt index) 		{ return nodes[index].seedY; }

		/// @brief Returns gray-scale value of the points at the vertex of a node.
		///
		/// This function returns the minimal (or maximal, if the tree is inverted)
		/// gray-scale value of the pixels contained in it.
		/// @param node index for a node.
		/// @returns gray-scale value of the points at the vertex of a node.
		uChar & firstThreshold(uInt index)	{ return nodes[index].firstThreshold; }

		/// @brief Returns gray-scale value of the points at the base of a node.
		///
		/// This function returns the maximal (or minimal, if the tree is inverted)
		/// gray-scale value of the pixels contained in it.
		/// @param node index for a node.
		/// @returns gray-scale value of the points at the base of a node.
		uChar & lastThreshold(uInt index) 	{ return nodes[index].lastThreshold; }

		/// @brief Returns the number of child nodes for a node.
		/// @param node index for a node.
		/// @returns number of child nodes that a node has got.
		uInt & numChilds(uInt index) 		{ return nodes[index].numChilds; }

		/// @brief Returns the index for the first of the childs of a node.
		/// @param node index for a node.
		/// @returns index to the first of the childs of a node.
		uInt & firstChild(uInt index)	 	{ return nodes[index].child; }

		/// @brief Returns the index for the next node in the list of childs, for a node.
		/// @param node index for a node.
		/// @returns index for the next node in the list of childs, for a node.
		uInt & nextSibling(uInt index) 		{ return nodes[index].sibling; }

		/// @brief Returns the accumulative histogram of the gray-level values of the pixels,
		/// for a node.
		///
		/// Considering the gray-scale values of the pixels of an image as indicator of a topological
		/// level or height, we can think of a node as a convex surface. That surface will have
		/// different areas for the different horizontal slides that we can think of.
		///
		/// Because heights in our topological image are discretized, we can store in a 256 integer
		/// array the number of pixels that get to a given level. That is what the array returned
		/// by this function gives, the area of the different slides, for the concave surface
		/// defined by the gray-scale values of the pixels of the node.
		///
		/// Generally you will obtain valid values in the range of cells between @ref firstThreshold
		/// and @ref lastThreshold functions. There's an exception to that, when you find in that range
		/// cells containing the value zero, that means we have the keep the previous value in the array.
		/// @param node index for a node.
		/// @returns array of areas of the slides of the concave surface defined by the pixels in the node.
		uInt *area(uInt index) 			{ return nodes[index].area; }

		/// @brief Gets the number of total nodes in the tree.
		/// @returns the number of total nodes in the tree.
		uInt getNumNodes() const	{ return numNodes; }

		/// @brief Gets the number of leaf nodes in the tree.
		/// @returns the number of leaf nodes in the tree.
		uInt getLeafNodes() const	{ return leafNodes; }

		/// @brief Gets the number of pixels processed by the tree construction.
		///
		/// This value should always equal cols x rows of the image fron which the tree was obtained.
		/// @returns the number of pixels in the original image.
		uInt getTotalPoints() const	{ return totalPoints; }

	private:
		void getComponentTree(const QVImage<uChar> &image);

		uInt numNodes, freePoints, totalPoints, leafNodes, rootNodeID, maxNodes;
		bool inverseTree;

		/// @brief Checks if a node has been closed. This means it has all the childs it should have.
 		bool & closedNode(uInt index) 		{ return nodes[index].closed; }

		uInt newNode(uInt SeedX, uInt SeedY, uChar Threshold)
			{
			uInt newNodeID = this->numNodes++;

			seedX(newNodeID) = SeedX;
			seedY(newNodeID) = SeedY;
			firstThreshold(newNodeID) = lastThreshold(newNodeID) = Threshold;
			firstChild(newNodeID) =	 nextSibling(newNodeID) = NULL_NODE;
			numChilds(newNodeID) = 0;
			area(newNodeID)[Threshold] = 0;
			closedNode(newNodeID) = false;
			
			return newNodeID;
			}

		void addChild(uInt ParentNodeID, uInt ChildNodeID)
			{
			nextSibling(ChildNodeID) = firstChild(ParentNodeID);
			firstChild(ParentNodeID) = ChildNodeID;
			numChilds(ParentNodeID)++;
			}

		void mergeNodes(uInt actualNodeID, uInt vecinoNodeID)
			{
			uInt next, lastActualChildNodeID = firstChild(actualNodeID);
			while ((next=nextSibling(lastActualChildNodeID)) != NULL_NODE)
				lastActualChildNodeID = next;

			numChilds(actualNodeID) += numChilds(vecinoNodeID);
			nextSibling(lastActualChildNodeID) = firstChild(vecinoNodeID);
			}

		class QVComponentTreeNode
			{
			public:
				uInt seedX, seedY;
				uInt child, sibling, numChilds;
				uChar firstThreshold, lastThreshold;
				uInt area[256];
				bool closed;

				/*bool operator==(const QVComponentTreeNode &other) const
					{
					if (seedX != other.seedX)
						return false;
					if (seedY != other.seedY)
						return false;
					//if (child != other.child)
					//	return false;
					//if (sibling != other.sibling)
					//	return false;
					if (numChilds != other.numChilds)
						return false;
					if (firstThreshold != other.firstThreshold)
						return false;
					if (lastThreshold != other.lastThreshold)
						return false;
					for (int i = firstThreshold; i < lastThreshold; i++)
						if (area[i] != other.area[i])
							return false;
					return true;
					}*/
			};

		QVector<QVComponentTreeNode> nodes;

		//void testComponentTree(const QVImage<uChar,1> &image, QVDisjointSet &disjointSet);
	};

#endif //IFNDEF
