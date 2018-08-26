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

#include <QVDirectedGraph>

bool operator<(const QVGraphLink &link1, const QVGraphLink &link2)
	{
	if (link1.x() < link2.x())
		return true;

	if (link1.x() > link2.x())
		return false;

	return link1.y() < link2.y();
	};

#include<QFile>
#include<QTextStream>
bool writeGraphToDotFile(const QString &fileName, const QVDirectedGraph<QString> &graph, const QStringList &nodeLabels)
	{
	Q_ASSERT(nodeLabels.empty() or (graph.numNodes() == nodeLabels.count()));

	QFile file(fileName);
	if (not file.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

	QString result;

	result += "digraph StringGraph {\n";
	result += "node [shape=ellipse,color=black,style=bold];\n";
	result += "edge [arrowhead=open];\n";

	for(int i = 0; i < graph.numNodes(); i++)
		result += "node" + QString::number(i) + QString(" [label=\"") + ((nodeLabels.empty())?("node" + QString::number(i)):nodeLabels[i]) + "\"];\n";

	foreach(QVGraphLink link, graph.keys())
		result += "node" + QString::number(link.x()) + " -> node" + QString::number(link.y()) + " [label=\"" + graph[link] + "\"];\n";

	result += "}";

	QTextStream out(&file);
	out << qPrintable(result) << QString("\n");
	file.close();

	return true;
	}


