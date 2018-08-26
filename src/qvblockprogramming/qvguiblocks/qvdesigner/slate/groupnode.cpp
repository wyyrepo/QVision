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

#include "groupnode.h"
#include <QGraphicsSceneDragDropEvent>
#include <iostream>
#include "grouplink.h"


uint GroupNode::maxId = 0;

GroupNode::GroupNode(QString _name, SlateWindow *wind, QGraphicsItem * parent, QGraphicsScene * scene): Node(_name, wind, parent, scene), abstractPaint(false)
{
    myTextColor = Qt::darkGreen;
    myOutlineColor = Qt::darkBlue;
    myBackgroundColor = Qt::white;

    QFontMetricsF metrics = qApp->font();
	lineSpacing = metrics.lineSpacing();

    setFlags(ItemIsMovable | ItemIsSelectable);

	type = "Group";
	if (_name.isEmpty())	name = type;
	else  			name = _name;
	id = getNewId(); // el identificador de subgrupo es independiente del de los Nodos
}

GroupNode::~GroupNode()
{
	// quito los link internos, adaptando los links a los que servían
    foreach (Link *interLink, internalLinks.keys()) {
		Link *exterLink = internalLinks.value(interLink);
		if (exterLink) {
			if (exterLink->toNode() == this)
				exterLink->changeToPoint(interLink->toNode(), interLink->toProp());
			else
				exterLink->changeFromPoint(interLink->fromNode(), interLink->fromProp());
		}
        delete interLink;
	}

	// saco a los hijos del grupo antes de borrar
	prepareGeometryChange();
    foreach (QGraphicsItem *child, children()) {
        child->setParentItem(this->parentItem());
		if (!this->parentItem()) { // para que  no corrija nada si era subgrupo (estos se ajustan automáticos)
			child->scale(1.0 / SUBSCALE, 1.0 / SUBSCALE);
			child->setPos(child->pos() / SUBSCALE);
		}
		if (dynamic_cast<Node *>(child)) // para que si está en modo abstracto y se borra los hijos no salgan ocultos
			((Node *)child)->setHide(false);
	}
	update();
}

void GroupNode::addNode(Node *node)
{
	node->setParentItem(this); //se actualiza cambio el padre
	node->scale(SUBSCALE, SUBSCALE); //se escala
	node->setPos(node->pos() * SUBSCALE); //se escala su posición para que no se separen cuando se unen

	// actualizamos las propiedades de entrada que tiene el grupo, en función de las que quedan lincadas hacia afuera
	foreach(Link *link, node->getInLinks()) {
		changeLinkToGroup(link, true);
	}

	// actualizamos las propiedades de salida que tiene el grupo, en función de las que quedan lincadas hacia afuera
	foreach(Link *link, node->getOutLinks()) {
		changeLinkToGroup(link, false);
	}
}

void GroupNode::changeLinkToGroup(Link *link, bool toNode)
{
	Node *addedNode = (toNode) ? link->toNode() : link->fromNode();
	Node *linkedNode = (toNode) ? link->fromNode() : link->toNode();
	QString addedNodeProp = (toNode) ? link->toProp() : link->fromProp();
	QString linkedNodeProp = (toNode) ? link->fromProp() : link->toProp();

	bool isGroup = (dynamic_cast<GroupNode*>(addedNode)) ? true : false;
	if ( (isGroup) && (((GroupNode*)addedNode)->internalLinks.contains(link)) ) return; // no tengo en cuenta los link internos de los subgrupos

// 	std::cout << "LLamada para el link: " << QString("%1, addedNode:").arg((uint)link).toStdString() << QString("%1, addedNodeProp: ").arg(addedNode->getId()).toStdString() << addedNodeProp.toStdString() << ", linkedNode " << QString("%1, linkedNodeProp ").arg(linkedNode->getId()).toStdString() << linkedNodeProp.toStdString() << std::endl;

	if (linkedNode != this) { // si el otro nodo del link esta fuera del grupo, quiebro el link (pasando por el grupo)
		int nodePos = addedNode->itemProp.getProperties().indexOf(addedNodeProp);
		QString thisNameProp = ( (isGroup) ? QString("") : QString("%1: ").arg(addedNode->getId()) ) + addedNodeProp;
// 		std::cout << "añado para " << QString("%1:: ").arg(addedNode->getId()).toStdString() << " esta " << thisNameProp.toStdString() << std::endl;
		insertProperty(thisNameProp, addedNode->itemProp.propertyType(nodePos), toNode, !toNode);
		if (toNode) {
			internalLinks.insert(new GroupLink(this, thisNameProp, addedNode, addedNodeProp, true, 0, scene()), link);
			link->changeToPoint(this, thisNameProp);
		}
		else {
			internalLinks.insert(new GroupLink(addedNode, addedNodeProp, this, thisNameProp, false, 0, scene()), link);
			link->changeFromPoint(this, thisNameProp);
		}
	}
	else { // sino borro la propiedad del grupo
// 		std::cout << "borro para " << QString("%1:: ").arg(addedNode->getId()).toStdString() << " esta " << linkedNodeProp.toStdString() << std::endl;
		Link *interLink = internalLinks.key(link);
		if (interLink) {
			if (toNode) {
				link->changeFromPoint(interLink->fromNode(), interLink->fromProp());
				internalLinks.remove(interLink);
				removeProperty(interLink->toProp());
				delete interLink;
			}
			else {
				link->changeToPoint(interLink->toNode(), interLink->toProp());
				internalLinks.remove(interLink);
				removeProperty(interLink->fromProp());
				delete interLink;
			}
		}
// 		else std::cout << "ERROR-1" << std::endl;
	}
}

void GroupNode::removeLink(Link *link)
{
	Node::removeLink(link);

	if (internalLinks.contains(link)) { // si era un link interno
		internalLinks.remove(link);
	}
	if (internalLinks.values().contains(link)) { // si era un link asociado a un link interno
		internalLinks[internalLinks.key(link)] = NULL;
	}
}

void GroupNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
// 	abstractPaint = (option->levelOfDetail < 0.75) ? true : abstractMode;

	if (abstractPaint)
		paintProps(painter, option, widget);
	else
		paintGroup(painter, option, widget);
}

void GroupNode::paintProps(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
    QPen pen(myOutlineColor);
    if (option->state & QStyle::State_Selected) {
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
    }
    painter->setPen(pen);
    painter->setBrush(myBackgroundColor);

    QRectF rect = outlineRect();
    painter->drawRoundRect(rect.adjusted(0.0, lineSpacing-2, 0.0, 0.0), roundness(rect.width()),
                           roundness(rect.height()));

    painter->setPen(myTextColor);
    painter->drawText(rect, Qt::AlignTop, name);
    painter->drawText(rect.adjusted(0.0, lineSpacing, 0.0, 0.0), Qt::AlignTop | Qt::AlignHCenter, myText);

	// muestra el boton redonde de abajo-derecha
	QRectF arrowRect((int)rect.right() - 15, (int)rect.bottom() - 10, 13, 8);
	drawCurvArrow(arrowRect, painter);

	// y pinta los puntos de unión a ambos lados del texto
    painter->setPen(Qt::white);
	painter->setBrush(Qt::black);
	for (int i = 0; i < numProp; i++) {
		if (itemProp.isInput(i)) // si tiene enlace de entrada lo pinto
	    	painter->drawEllipse((int)(rect.left() + lineSpacing*0.1), (int)(rect.top() + lineSpacing*(i + 1.1)), (int)(lineSpacing*0.8), (int)(lineSpacing*0.8));
		if (itemProp.isOutput(i)) // // si tiene enlace de salida lo pinto
			painter->drawEllipse((int)(rect.right() - lineSpacing*0.9), (int)(rect.top() + lineSpacing*(i + 1.1)), (int)(lineSpacing*0.8), (int)(lineSpacing*0.8));
	}

	// si uno de los puntos está marcado, lo pinta dependiendo de su validez
	if (markedPoint >= 0) {
		if (markedValidity) painter->setBrush(Qt::green);
		else				painter->setBrush(Qt::red);

		if (markedPoint < numProp)
			painter->drawEllipse((int)(rect.left() + lineSpacing*0.1), (int)(rect.top() + lineSpacing*(markedPoint + 1.1)), (int)(lineSpacing*0.8), (int)(lineSpacing*0.8));
		else
			painter->drawEllipse((int)(rect.right() - lineSpacing*0.9), (int)(rect.top() + lineSpacing*(markedPoint - numProp + 1.1)), (int)(lineSpacing*0.8), (int)(lineSpacing*0.8));
	}
}

void GroupNode::paintGroup(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
    QPen pen(myOutlineColor);
    if (option->state & QStyle::State_Selected) {
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
    }
    painter->setPen(pen);
    painter->setBrush(myBackgroundColor);

    QRectF rect = outlineRect();
    painter->drawRoundRect(rect.adjusted(0.0, lineSpacing-2, 0.0, .0), roundness(rect.width()),
                           roundness(rect.height()));

    painter->setPen(myTextColor);
    painter->drawText(rect, Qt::AlignTop, name);

	// muestra el boton redonde de abajo-derecha
	QRectF arrowRect((int)rect.right() - 15, (int)rect.bottom() - 10, 13, 8);
	drawCurvArrow(arrowRect, painter);

	// y pinta los puntos de unión a ambos lados del texto
    painter->setPen(Qt::white);
	painter->setBrush(Qt::black);
	for (int i = 0; i < numProp; i++) {
		if (itemProp.isInput(i)) // si tiene enlace de entrada lo pinto
	    	painter->drawEllipse((int)(rect.left() + lineSpacing*0.1), (int)(rect.top() + lineSpacing*(i + 1.1)), (int)(lineSpacing*0.8), (int)(lineSpacing*0.8));
		if (itemProp.isOutput(i)) // // si tiene enlace de salida lo pinto
			painter->drawEllipse((int)(rect.right() - lineSpacing*0.9), (int)(rect.top() + lineSpacing*(i + 1.1)), (int)(lineSpacing*0.8), (int)(lineSpacing*0.8));
	}

	// si uno de los puntos está marcado, lo pinta dependiendo de su validez
	if (markedPoint >= 0) {
		if (markedValidity) painter->setBrush(Qt::green);
		else				painter->setBrush(Qt::red);

		if (markedPoint < numProp)
			painter->drawEllipse((int)(rect.left() + lineSpacing*0.1), (int)(rect.top() + lineSpacing*(markedPoint + 1.1)), (int)(lineSpacing*0.8), (int)(lineSpacing*0.8));
		else
			painter->drawEllipse((int)(rect.right() - lineSpacing*0.9), (int)(rect.top() + lineSpacing*(markedPoint - numProp + 1.1)), (int)(lineSpacing*0.8), (int)(lineSpacing*0.8));
	}

	// muestra los puntos de enlace a izquierda y derecha
/*    painter->setPen(Qt::white);
	painter->setBrush(Qt::black);
	painter->drawEllipse((int)rect.right() - 20 - (int)(lineSpacing*0.5), (int)rect.bottom() - 10, (int)(lineSpacing*0.5), (int)(lineSpacing*0.5));
	painter->drawEllipse((int)rect.left() + 20, (int)rect.bottom() - 10, (int)(lineSpacing*0.5), (int)(lineSpacing*0.5)); */
}

void GroupNode::drawCurvArrow(const QRectF rect, QPainter *painter)
{
	QRectF smallCurveRect = QRectF(rect.x(), rect.y() - rect.height() * 2/5, rect.width() * 2/3, rect.height() * 4/5);
	QRectF bigCurveRect = QRectF(rect.x() - rect.width() * 1/3, rect.y() - rect.height() * 4/5, rect.width() * 4/3, rect.height() * 8/5);

	painter->drawArc(smallCurveRect, 270 * 16, 90 * 16);
	painter->drawArc(bigCurveRect, 270 * 16, 90 * 16);

	painter->drawLine(QPointF(rect.x() + rect.width() * 2/3, rect.y()), QPointF(rect.x() + rect.width() * 19/24, rect.y() + rect.height() * 1/5));
	painter->drawLine(QPointF(rect.x() + rect.width() * 19/24, rect.y() + rect.height() * 1/5), QPointF(rect.x() + rect.width(), rect.y()));

	painter->drawLine(QPointF(rect.x() + rect.width() * 1/3, rect.y() + rect.height() * 2/5), QPointF(rect.x() + rect.width() * 1/3, rect.y() + rect.height() * 1/5));
	painter->drawLine(QPointF(rect.x() + rect.width() * 1/3, rect.y() + rect.height() * 1/5), QPointF(rect.x(), rect.y() + rect.height() * 3/5));
	painter->drawLine(QPointF(rect.x(), rect.y() + rect.height() * 3/5), QPointF(rect.x() + rect.width() * 1/3, rect.y() + rect.height()));
	painter->drawLine(QPointF(rect.x() + rect.width() * 1/3, rect.y() + rect.height()), QPointF(rect.x() + rect.width() * 1/3, rect.y() + rect.height() * 4/5));
}

void GroupNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QRectF rect = outlineRect();
	QPointF click = mapFromScene(event->scenePos());

	prepareHierarchy();
	if ((click.x() > rect.right() - 15) && (click.y() > rect.bottom() - 10)) {
		// cambia de la vista de nodos unidos a los puntos laterales a la vista de los nombres de las propiedades de entrada y salida.
		prepareGeometryChange();
		abstractPaint = abstractPaint ? false : true;
		foreach(QGraphicsItem *item, children()) {
			if (dynamic_cast<Node *>(item))
				((Node *)item)->setHide(abstractPaint);
		}
		update();
	}
	else {
		QString text = QInputDialog::getText(event->widget(), tr("Edit Text"), tr("Enter new text:"), QLineEdit::Normal, name);
		prepareGeometryChange();
		name = text;
		update();
	}
	updateLinksPos();
	updateHierarchy();
}

void GroupNode::abstractView(bool mode)
{
	if (abstractPaint == mode) return;

	// cambia de la vista de nodos unidos a los puntos laterales a la vista de los nombres de las propiedades de entrada y salida.
	prepareHierarchy();
	prepareGeometryChange();
	abstractPaint = mode;
	foreach(QGraphicsItem *item, children()) {
		if (dynamic_cast<Node *>(item))
			((Node *)item)->setHide(abstractPaint);
	}
	update();
	updateLinksPos();
	updateHierarchy();
}

void GroupNode::updateLinksPos()
{
    foreach (Link *link, getLinks())
        link->trackNodes();

	foreach (QGraphicsItem *child, children()) {
		Node *nodeChild = dynamic_cast<Node *>(child);
		if (nodeChild)
			nodeChild->updateLinksPos();
	}
}

QRectF GroupNode::outlineRect() const
{
	if (abstractPaint) {
		QFontMetricsF metrics = qApp->font();
		double width = metrics.boundingRect(name).width();
	
		const QList<QString> props = itemProp.getProperties();
		for (int i = 0; i < props.size(); i++)
			if (width < metrics.boundingRect(props[i]).width()) width = metrics.boundingRect(props[i]).width();

		width += lineSpacing*4; // vale el ancho de la linea más grande más 4 espacios para los puntos de los lados
		double height = (numProp+2)*lineSpacing; // vale el alto de todas las lineas
		double xPos = childrenBoundingRect().left()-lineSpacing;
		double yPos = childrenBoundingRect().top()-lineSpacing;

		return QRectF(xPos, yPos, width, height);
	}
	else {
		QRectF rect = childrenBoundingRect();
		if (rect.height() < numProp*lineSpacing) rect.setHeight(numProp*lineSpacing);
		return rect.adjusted(0.0-lineSpacing*2, 0.0-lineSpacing, lineSpacing*2, lineSpacing);
	}
}


void GroupNode::setHide(bool hide)
{
	foreach(Link *link, getLinks())
		if (internalLinks.contains(link))
			link->setVisible(!hide && !abstractPaint);
		else
			link->setVisible(!hide);

	foreach(QGraphicsItem *item, children()) {
		if (dynamic_cast<Node *>(item))
			((Node *)item)->setHide(hide || abstractPaint);
	}

	setVisible(!hide);
}

GroupInfo GroupNode::getInfo()
{
	GroupInfo info(id, name);
// 	std::cout << "creo el grupo: " << QString("%1").arg(id).toStdString() << ", " << name.toStdString() << std::endl;

	foreach(QGraphicsItem *item, children()) {
		if (dynamic_cast<Node *>(item)) {
			if (dynamic_cast<GroupNode *>(item)) {
				info.addSubgroup( ((GroupNode *)item)->getId() );
// 				std::cout << "     le añado el subgrupo: " << QString("%1").arg(((Node *)item)->getId()).toStdString() << std::endl;
			}
			else {
				info.addNode( ((Node *)item)->getId() );
// 				std::cout << "     le añado el nodo: " << QString("%1").arg(((Node *)item)->getId()).toStdString() << std::endl;
			}
		}
	}

	foreach(Link *link, internalLinks.keys()) {
		if (link->fromNode() == this) {
			if (dynamic_cast<GroupNode *>(link->toNode()))
				info.addSubgroupLink(LinkInfo(link->toNode()->getId(), link->toProp(), true));
			else
				info.addNodeLink(LinkInfo(link->toNode()->getId(), link->toProp(), true));
// 			std::cout << "     le añado el link: " << QString("%1").arg(link->toNode()->getId()).toStdString() << "[" << link->toProp().toStdString() << "] (input)" << std::endl;
		}
		else {
			if (dynamic_cast<GroupNode *>(link->fromNode()))
				info.addSubgroupLink(LinkInfo(link->fromNode()->getId(), link->fromProp(), false));
			else
				info.addNodeLink(LinkInfo(link->fromNode()->getId(), link->fromProp(), false));
// 			std::cout << "     le añado el link: " << QString("%1").arg(link->fromNode()->getId()).toStdString() << "[" << link->fromProp().toStdString() << "] (output)" << std::endl;
		}
	}

	info.setPos(pos());
	info.setAbstract(abstractPaint);
// 	std::cout << "     con la posición: [" << QString("%1").arg(pos().x()).toStdString() << ", " << QString("%1").arg(pos().y()).toStdString() << "]" << std::endl;

	return info;
}


