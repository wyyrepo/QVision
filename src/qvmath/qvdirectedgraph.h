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

#ifndef QVDIRECTEDGRAPH_H
#define QVDIRECTEDGRAPH_H

#include <QPoint>
#include <QHash>
#include <QMap>
#include <QVVector>

#include <qvmath.h>

/*!
@brief Link between two nodes in a graph.
*/
typedef QPoint QVGraphLink;

bool operator<(const QVGraphLink &link1, const QVGraphLink &link2);

/*!
@brief Directed graph class.

This class represents a directed graph.

@ingroup qvmath
*/
template <typename Element> class QVDirectedGraph: public QMap<QVGraphLink, Element>
	{
	private:
		int maxNodeIndex;

	public:

		/// @brief Returns the number of links connecting each node.
		QVVector getNodesConnectivity()	const
			{
			QVVector result(maxNodesIndex()+1, 0.0);
			foreach(QVGraphLink link, this->keys())
				{
				result[link.x()]++;
				result[link.y()]++;
				}

			return result;
			}

		/// @brief Returns the minimal number of links connecting each node.
		int getMinConnectivity()		const	{ return int(getNodesConnectivity().min()); }

		/// @brief Returns the maximal number of links connecting each node.
		int getMaxConnectivity()		const	{ return int(getNodesConnectivity().max()); }

		/// @brief Returns the mean number of links connecting each node.
		double getMeanConnectivity()	const	{ return getNodesConnectivity().mean(); }		
			
/*
        /// @brief Arrow types for the DOT file representation.
        /// @see qvWriteGraphToDotFile
		enum ArrowHeadType {
			normal,
			inv,
			dot,
			invdot,
			odot,
			invodot,
			none,
			tee,
			empty,
			invempty,
			diamond,
			odiamond,	
			ediamond,
			crow,
			box,
			obox,	
			open,
			halfopen,
			vee
			};

        /// @see QVDirectedGraph::ArrowHeadType
        typedef QFlags<ArrowHeadType> ArrowHeadTypes;
*/

		/// @brief Constructor.
		QVDirectedGraph():QMap<QVGraphLink, Element>(), maxNodeIndex(0)
			{
			}

		/// @brief Add a link between two nodes of the graph.
		void insert(const int source, const int destination, const Element element)
			{
			Q_ASSERT(source >= 0);
			Q_ASSERT(destination >= 0);

			maxNodeIndex = MAX(maxNodeIndex, MAX(source, destination));
			QMap<QVGraphLink, Element>::insert(QVGraphLink(source, destination), element);
			}

		/// @brief Add a link between two nodes of the graph.
		void insert(const QVGraphLink &link, const Element element)
			{
			Q_ASSERT(link.x() >= 0);
			Q_ASSERT(link.y() >= 0);

			maxNodeIndex = MAX(maxNodeIndex, MAX(link.x(), link.y()));
			QMap<QVGraphLink, Element>::insert(link, element);
			}

		/// @brief Retrieve element for a link between two nodes
		Element operator [](const QVGraphLink &link) const
			{
			Q_ASSERT(link.x() >= 0);
			Q_ASSERT(link.y() >= 0);

			Q_ASSERT(link.x() <= maxNodeIndex);
			Q_ASSERT(link.y() <= maxNodeIndex);

			return QMap<QVGraphLink, Element>::operator[](link);
			}

		/// @brief Retrieve element for a link between two nodes
		Element & operator [](const QVGraphLink &link)
			{
			Q_ASSERT(link.x() >= 0);
			Q_ASSERT(link.y() >= 0);

			maxNodeIndex = MAX(maxNodeIndex, MAX(link.x(), link.y()));
			return QMap<QVGraphLink, Element>::operator[](link);
			}

		/// @brief Retrieve element for a link between two nodes
		inline const Element value(const int source, const int destination) const
			{
			Q_ASSERT(source >= 0);
			Q_ASSERT(destination >= 0);

			Q_ASSERT(source <= maxNodeIndex);
			Q_ASSERT(destination <= maxNodeIndex);

			return QMap<QVGraphLink, Element>::value(QVGraphLink(source, destination));
			}

		/// @brief Retrieve element for a link between two nodes
		inline bool contains(const int source, const int destination) const
			{
			return QMap<QVGraphLink, Element>::contains(QVGraphLink(source, destination));
			}

		/// @brief Retrieve element for a link between two nodes
		inline bool contains(const QVGraphLink &link) const
			{
			return QMap<QVGraphLink, Element>::contains(link);
			}

		/// @brief Retrieve links defined between the nodes of the graph.
		QList<QVGraphLink> getLinks()	const
			{
			return this->keys();
			}

		/// @brief Delete nodes connected by less nodes than a given value, with other nodes in the graph.
		///
		/// This method eliminates the nodes with a smaller connectivity, leaving a skeletal graph of the best connected nodes.
		void deleteInsufficientlyConnectedNodes(const int minConnections)
			{
			QMap<int, int> counts = numLinksPerNode();	
			while(true)
				{
				foreach( QVGraphLink p, this->keys() )
					if ( (counts[p.x()] < minConnections) or (counts[p.y()] < minConnections) )
						this->remove(p);

				QMap<int, int> newCounts = numLinksPerNode();

				if (counts == newCounts)
					break;

				counts = newCounts;
				}
			}

		/// @brief Return the number of connected nodes in the graph.
		int numNodes()				const
			{
			return numLinksPerNode().count();
			}

		/// @brief Return the maximal index for the nodes in the graph.
		/// @deprecated for @ref getMaxNodeIndex
		int maxNodesIndex()				const
			{
		    std::cout << "WARNING: 'QVDirectedGraph::maxNodesIndex' deprecated. Use 'QVDirectedGraph::getMaxNodeIndex' instead." << std::endl;
			int result = 0;
			foreach(QVGraphLink link, this->keys())
				result = MAX(result, MAX(link.x(), link.y()));

			return result;
			}

		/// @brief Returns the maximal index for a node in the graph.
		int getMaxNodeIndex() const
			{
			#ifdef DEBUG
			int temp = 0;
			foreach(QVGraphLink key, this->keys())
				temp = MAX(temp, MAX(key.x(), key.y()));

			Q_ASSERT(maxNodeIndex == temp);
			Q_ASSERT(maxNodeIndex == maxNodesIndex());
			#endif // DEBUG
				
			return maxNodeIndex;
			}

		/// @deprecated for @ref numLinksPerNode
		QMap<int, int> numLinksForNode()	const
			{
		    std::cout << "WARNING: 'QVDirectedGraph::numLinksForNode' deprecated. Use 'QVDirectedGraph::numLinksPerNode' instead." << std::endl;
			return numLinksPerNode();
			}
	
		/// @brief Returns the number of connections for each node in the graph.
		/// @return A map containing the number of links for each node in the graph.
		QMap<int, int> numLinksPerNode()	const
			{
			QMap<int, int> result;
	
			foreach(QVGraphLink link, this->keys())
					{
					result[link.x()] ++;
					result[link.y()] ++;
					}
			return result;
			}

	};

#include <QStringList>

/*! @brief Writes a directed graph in a .dot file.

@param fileName Name for the .dot file.
@param graph Graph to store in the .dot file.
@param nodeLabels List of labels for the nodes in the .dot file.
@ingroup qvmath
*/
bool writeGraphToDotFile(const QString &fileName, const QVDirectedGraph<QString> &graph, const QStringList &nodeLabels = QStringList());

#endif

