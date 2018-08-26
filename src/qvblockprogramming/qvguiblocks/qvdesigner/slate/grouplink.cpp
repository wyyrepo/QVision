/*
 *	Copyright (C) 2008, 2009, 2010, 2011, 2012. PARP Research Group.
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


#include <QtGui>

#include "grouplink.h"
#include "node.h"

GroupLink::GroupLink(Node *fromNode, QString fromProp, Node *toNode, QString toProp, bool _input, QGraphicsItem * parent, QGraphicsScene * scene): Link(fromNode, fromProp, toNode, toProp, parent, scene), input(_input)
{
	setColor(QColor(255, 127, 0));
	QPen dotPen = pen();
	dotPen.setStyle(Qt::DashDotLine);
	setPen(dotPen);
}

void GroupLink::trackNodes()
{
	// actualiza el zValue al máximo de los dos, o al del mayor grupo al que pertenecen
	// reducimos el tamaño del Pen del link en función del número de antecesores (*0.5 por cada uno)
	//(solo se mira para uno pq no se permiten enlaces entre grupos)
	double zvalue = (myFromNode->zValue() > myToNode->zValue()) ? myFromNode->zValue() + 1 : myToNode->zValue() + 1;

	// obtenemos el pen
	QGraphicsItem *ancestor = myFromNode->parentItem();
	QPen myPen = pen();
    while (ancestor) {
		setZValue(ancestor->zValue() + 1);
		myPen.setWidthF(myPen.width() * 0.4);
		ancestor = ancestor->parentItem();
	}

	// obtenemos las posiciones origen y destino
	QPointF orig = myFromNode->scenePointPos(myFromProp, input); // dependiend de si es input o no tiene que tomar los puntos de origen o de destino
	QPointF dest = myToNode->scenePointPos(myToProp, input); // dependiend de si es input o no tiene que tomar los puntos de origen o de destino

	if (orig.x() <= dest.x()) {
		setZValue(zvalue);
		setPen(myPen);
		setLine(QLineF(orig, dest));
		line2.hide();
		line3.hide();
		line4.hide();
		line5.hide();
	}
	else {
		// obtenemos el desplazamiento lateral para esta propiedad dentro de sus nodos (para que no se solapen verticalmente)
		double origDesp = 10.0 * (fromNode()->numProps() - fromNode()->propPoint(fromProp(), true) + 1);
		double destDesp = 10.0 * (toNode()->numProps() - toNode()->propPoint(toProp(), true) + 1);

		// obtenemos la coordenada Y de las partes inferior
		double origBottom = /*fromNode()->scenePos().y() +*/ fromNode()->sceneBoundingRect().bottom() + origDesp;
		double destBottom = /*toNode()->scenePos().y() +*/ toNode()->sceneBoundingRect().bottom() + destDesp;
		double bottom = origBottom > destBottom ? origBottom : destBottom;

		setZValue(zvalue);
		line2.setZValue(zvalue);
		line3.setZValue(zvalue);
		line4.setZValue(zvalue);
		line5.setZValue(zvalue);
		setPen(myPen);
		line2.setPen(myPen);
		line3.setPen(myPen);
		line4.setPen(myPen);
		line5.setPen(myPen);
		setLine(QLineF(orig, orig + QPointF(origDesp, 0.0)));
		line2.setLine(QLineF(orig + QPointF(origDesp, 0.0), QPointF(orig.x() + origDesp, bottom)));
		line3.setLine(QLineF(QPointF(orig.x() + origDesp, bottom), QPointF(dest.x() - destDesp, bottom)));
		line4.setLine(QLineF(QPointF(dest.x() - destDesp, bottom), dest + QPointF(0.0 - destDesp, 0.0)));
		line5.setLine(QLineF(dest + QPointF(0.0 - destDesp, 0.0), dest));
		if ((myFromNode->isVisible()) && (myToNode->isVisible())) {
			line2.show();
			line3.show();
			line4.show();
			line5.show();
		}
	}
}


