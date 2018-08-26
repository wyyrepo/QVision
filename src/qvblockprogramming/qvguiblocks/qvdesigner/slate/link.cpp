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

#include "link.h"
#include "node.h"

Link::Link(Node *fromNode, QString fromProp, Node *toNode, QString toProp, QGraphicsItem * parent, QGraphicsScene * scene): QGraphicsLineItem(parent, scene), line2(this, scene), line3(this, scene), line4(this, scene), line5(this, scene)
{
    myFromNode = fromNode;
    myToNode = toNode;
	myFromProp = fromProp;
	myToProp = toProp;

    myFromNode->addOutLink(this);
    myToNode->addInLink(this);

    setFlags(QGraphicsItem::ItemIsSelectable);
	line2.setFlags(QGraphicsItem::ItemIsSelectable);
	line3.setFlags(QGraphicsItem::ItemIsSelectable);
	line4.setFlags(QGraphicsItem::ItemIsSelectable);
	line5.setFlags(QGraphicsItem::ItemIsSelectable);

	setHandlesChildEvents(true);

    trackNodes();
}

Link::~Link()
{
    myFromNode->removeLink(this);
    myToNode->removeLink(this);
}

void Link::changeFromPoint(Node *newNode, QString NewProp)
{
	myFromNode->removeLink(this);
	myFromNode = newNode;
	myFromProp = NewProp;
    myFromNode->addOutLink(this);

    trackNodes();
}

void Link::changeToPoint(Node *newNode, QString NewProp)
{
	myToNode->removeLink(this);
	myToNode = newNode;
	myToProp = NewProp;
    myToNode->addInLink(this);

    trackNodes();
}

Node *Link::fromNode() const
{
    return myFromNode;
}

Node *Link::toNode() const
{
    return myToNode;
}

QString Link::fromProp() const
{
	return myFromProp;
}

QString Link::toProp() const
{
	return myToProp;
}

void Link::setColor(const QColor &color)
{
    setPen(QPen(color, 2.0));
}

QColor Link::color() const
{
    return pen().color();
}


void Link::trackNodes()
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
	QPointF orig = myFromNode->scenePointPos(myFromProp, FALSE);
	QPointF dest = myToNode->scenePointPos(myToProp, TRUE);

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

bool Link::sceneEvent(QEvent *)
{
	setSelected(true);
	line2.setSelected(true);
	line3.setSelected(true);
	line4.setSelected(true);
	line5.setSelected(true);

	return true;
}


