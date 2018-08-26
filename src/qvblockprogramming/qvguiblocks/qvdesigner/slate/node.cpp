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

#include "node.h"
#include <QGraphicsScene>


Node::Node(QString _name, SlateWindow *wind, QGraphicsItem * parent, QGraphicsScene * scene): QGraphicsItem(parent, scene), name(), type(),
	itemProp("Group"), numProp(itemProp.getProperties().size()), window(wind), clickedPoint(-1), externalMarkedPoint(-1), markedPoint(-1)
{
    myTextColor = Qt::darkGreen;
    myOutlineColor = Qt::darkBlue;
    myBackgroundColor = Qt::white;
    setFlags(ItemIsMovable | ItemIsSelectable);

	type = "Group";
	name = _name;
	id = 0;

	CorrectTextChange();
	update();
}

Node::Node(ItemProperties item, QString _name, uint _id, SlateWindow *wind, QGraphicsItem * parent, QGraphicsScene * scene): QGraphicsItem(parent, scene), name(),
	type(), itemProp(item), numProp(itemProp.getProperties().size()), window(wind), clickedPoint(-1), externalMarkedPoint(-1), markedPoint(-1)
{
    myTextColor = Qt::darkGreen;
    myOutlineColor = Qt::darkBlue;
    myBackgroundColor = Qt::white;
    setFlags(ItemIsMovable | ItemIsSelectable);

	type = itemProp.getType();
	name = _name;
	id = _id;

	CorrectTextChange();
	update();
}

Node::~Node()
{
     foreach (Link *link, getLinks())
        delete link;
}

void Node::addInLink(Link *link)
{
    myInLinks.append(link);
}

void Node::addOutLink(Link *link)
{
    myOutLinks.append(link);
}

void Node::removeLink(Link *link)
{
    myInLinks.removeAll(link);
	myOutLinks.removeAll(link);
}

QList<Link *> Node::getLinks() const
{
	return (myInLinks + myOutLinks);
}

QList<Link *> Node::getInLinks() const
{
	return myInLinks;
}

QList<Link *> Node::getOutLinks() const
{
	return myOutLinks;
}

int Node::precursors(QList<Node *> tail)
{
	if (myInLinks.isEmpty()) {
		return 0;
	}
	else if (tail.contains(this)) { // si se ha producido un ciclo
		return 0;
	}
	else {
		int maxPre = 0;
		tail.append(this);
		foreach(Link *link, myInLinks) {
			if ((link) && (link->fromNode())) {
				int pre = link->fromNode()->precursors(tail);
				if (maxPre < pre) maxPre = pre; //actualizo maxPre
			}
		}
		return maxPre + 1;
	}
}



void Node::setText(const QString &text)
{
    prepareGeometryChange();
    myText = text;
    update();
}

QString Node::text() const
{
    return myText;
}

void Node::setTextColor(const QColor &color)
{
    myTextColor = color;
    update();
}

QColor Node::textColor() const
{
    return myTextColor;
}

void Node::setOutlineColor(const QColor &color)
{
    myOutlineColor = color;
    update();
}

QColor Node::outlineColor() const
{
    return myOutlineColor;
}

void Node::setBackgroundColor(const QColor &color)
{
    myBackgroundColor = color;
    update();
}

QColor Node::backgroundColor() const
{
    return myBackgroundColor;
}

QRectF Node::boundingRect() const
{
    const int Margin = 1;
    return outlineRect().adjusted(-Margin, -Margin, +Margin, +Margin);
}

QPainterPath Node::shape() const
{
    QRectF rect = outlineRect();

    QPainterPath path;
    path.addRoundRect(rect, roundness(rect.width()),
                      roundness(rect.height()));
    return path;
}

uint Node::getId()
{
	return id;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
    QPen pen(myOutlineColor);
    if (option->state & QStyle::State_Selected) {
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
    }
    painter->setPen(pen);
    painter->setBrush(myBackgroundColor);

    QRectF rect = outlineRect();
	painter->drawRect(rect);
	painter->drawLine((int)rect.left(), (int)(rect.top() + lineSpacing), (int)rect.right(), (int)(rect.top() + lineSpacing));

    painter->setPen(myTextColor);
	//painter->drawText(rect, Qt::AlignTop | Qt::AlignHCenter, QString("") + QString("(%1) ").arg(getId()) + name);
    painter->drawText(rect, Qt::AlignTop | Qt::AlignHCenter, QString("") + name);
    painter->drawText(rect.adjusted(0.0, lineSpacing, 0.0, 0.0), Qt::AlignTop | Qt::AlignHCenter, myText);

	// y pinta los puntos de unión a ambos lados del texto
    painter->setPen(Qt::white);
	painter->setBrush(Qt::black);
	for (int i = 0; i < numProp; i++)
	{
		if (itemProp.isInput(i)) // si tiene enlace de entrada lo pinto
	    		painter->drawEllipse((int)(rect.left() + lineSpacing*0.1), (int)(rect.top() + lineSpacing*(i + 1.1)), (int)(lineSpacing*0.8), (int)(lineSpacing*0.8));
		if (itemProp.isOutput(i)) // // si tiene enlace de salida lo pinto
			painter->drawEllipse((int)(rect.right() - lineSpacing*0.9), (int)(rect.top() + lineSpacing*(i + 1.1)), (int)(lineSpacing*0.8), (int)(lineSpacing*0.8));
	}

	// si uno de los puntos está marcado, lo pinta dependiendo de su validez
	if (markedPoint >= 0)
	{
		if (markedValidity) painter->setBrush(Qt::green);
		else				painter->setBrush(Qt::red);

		if (markedPoint < numProp)
			painter->drawEllipse((int)(rect.left() + lineSpacing*0.1), (int)(rect.top() + lineSpacing*(markedPoint + 1.1)), (int)(lineSpacing*0.8), (int)(lineSpacing*0.8));
		else
			painter->drawEllipse((int)(rect.right() - lineSpacing*0.9), (int)(rect.top() + lineSpacing*(markedPoint - numProp + 1.1)), (int)(lineSpacing*0.8), (int)(lineSpacing*0.8));
	}
}

// devuelve la posición (en cordenadas de la scena) del centro del punto indicado por el índice point, si se sale del rango devuelve la posición del nodo
QPointF Node::scenePointPos(int point) const
{
	QRectF rect = outlineRect();

	if (point < 0) return this->scenePos();
	if (point < numProp) return mapToScene( QPointF(rect.left() + lineSpacing*0.1, rect.top() + lineSpacing*(point + 1.5)) );
	if (point < 2 * numProp) return mapToScene( QPointF(rect.right() - lineSpacing*0.2, rect.top() + lineSpacing*(point-numProp + 1.5)) );
	return this->scenePos();
}

QPointF Node::scenePointPos(QString name, bool in) const
{
	return scenePointPos(propPoint(name, in));
}


int Node::numProps() const
{
	return numProp;
}


void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QRectF rect = outlineRect();
	QPointF click = mapFromScene(event->scenePos());

	if (click.y() > rect.top() + lineSpacing) {
		window->showProperties(this);
	}
	else {
		QString text = QInputDialog::getText(event->widget(),
							tr("Edit Name"), tr("Enter new name:"),
							QLineEdit::Normal, name);
		if (!text.isEmpty()) {
			window->setName(this, text);
		}
	}
}

void Node::setName(QString _name) {
	prepareGeometryChange();
	name = _name;
	CorrectTextChange();
	update();
}

// estas funciones son para conseguir que los puntos se pinten de rojo cunado se pasa sobre ellos
// y que se cree la linea al arrastar y creen los link cuando suelte en una posición correcta
void Node::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	if (!window->isSelected(this)) {
		window->clearSelection();
		setSelected(true);
	}

	clickedPoint = pointAt(event->pos());
	if (clickedPoint < 0)
	{
		// si no coincidía con un punto mueve el item normalmente
		QGraphicsItem::mousePressEvent(event);
	}
	else
	{
		// si coincide con un punto crea una línea indicadora del posible enlace
		line = new QGraphicsLineItem( QLineF(event->scenePos(), event->scenePos()) );
		line->setZValue(1000);
		scene()->addItem(line);
	}
}

void Node::prepareHierarchy()
{
	// actualiza a toda la gerarquía de grupos que tiene por encima
	QGraphicsItem *ancestor = parentItem();
	while (ancestor) {
		if (dynamic_cast<Node *>(ancestor))
			((Node *)ancestor)->publicPrepareGeometryChange();
		ancestor = ancestor->parentItem();
	}
}

void Node::publicPrepareGeometryChange() {
	prepareGeometryChange();
}

void Node::updateHierarchy()
{
	// actualiza a toda la gerarquía de grupos que tiene por encima
	QGraphicsItem *ancestor = parentItem();
	while (ancestor) {
		ancestor->update();
		if (dynamic_cast<Node *>(ancestor))
			((Node *)ancestor)->updateLinksPos();
		ancestor = ancestor->parentItem();
	}
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
	// si no se ha pinchado sobre un punto, muevo el item
	if (clickedPoint < 0)
	{
		// actualiza a toda la gerarquía de grupos que tiene por encima, por si han de encogerse
		updateHierarchy();

		QGraphicsItem::mouseMoveEvent(event);

		// actualiza a toda la gerarquía de grupos que tiene por encima, por si han de ensancharse
		updateHierarchy();
	}
	else
	{
		// desplazo la línea como el mouse, pero un poco (0.5) más corta, ya que sino cuando busquemos el item de justo
		// debajo del cursor nos puede dar la própia línea en vez del que buscamos.
		QLineF shortLine = QLineF(line->line().p1(), event->scenePos());
		shortLine.setLength(shortLine.length() - 0.5);
		line->setLine(shortLine);

		// si había un punto marcado lo desmarco
		if (externalMarkedPoint >= 0)
		{
			externalMarkedItem->unmarkPoint();
			externalMarkedPoint = -1;
		}

		// y si está sobre otro punto válido para el enlace, lo marco
		Node *target = dynamic_cast<Node *>(scene()->itemAt(event->scenePos())); // en un futuro tendrá que hacer el cast a Node
		if (target)
		{
			// obtengo el punto concreto a partir de las coordenadas locales al otro item
			int pointPos = target->pointAt(target->mapFromScene(event->scenePos()));
			if (pointPos >= 0)
			{ // marco el nuevo punto en función de la validez del enlace que generaría
				externalMarkedPoint = pointPos;
				externalMarkedItem = target;
				externalMarkedItem->markPoint(externalMarkedPoint, isValidLink(this, clickedPoint, target, pointPos));
			}
		}
	}
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	// si no se ha arrastrado desde un punto hago un release normal
	if (clickedPoint < 0)
	{
		QGraphicsItem::mouseReleaseEvent(event);
	}
	else
	{
		// elimino la línea indicadora
		delete(line);

		// si había un punto marcado lo desmarco
		if (externalMarkedPoint >= 0)
		{
			externalMarkedItem->unmarkPoint();
			externalMarkedPoint = -1;
		}

		// si está sobre un punto válido creo el enlace
		Node *target = dynamic_cast<Node *>(scene()->itemAt(event->scenePos())); // en un futuro tendrá que hacer el cast a Node
		if (target)
		{
			// obtiene el punto concreto a partir de las coordenadas locales al otro item
			int pointPos = target->pointAt(target->mapFromScene(event->scenePos()));

			// si es valido crea el enlace entre clickedPoint de this y pointPos de target
			if ( (pointPos >= 0) && isValidLink(this, clickedPoint, target, pointPos) )
			{
				if (clickedPoint >= numProp) // si clickedPoint es un punto de salida, el enlace parte de this
					validLinkRelease(this, clickedPoint, target, pointPos);
				else // si no, parte de target
					validLinkRelease(target, pointPos, this, clickedPoint);
			}
		}

		clickedPoint = -1;
	}
}

void Node::validLinkRelease(Node *fromNode, int fromPoint, Node *toNode, int toPoint)
{
	window->createLink(fromNode, fromPoint, toNode, toPoint);
}

void Node::markPoint(int point, bool validity)
{
	markedPoint = point;
	markedValidity = validity;
	update();
}

void Node::unmarkPoint()
{
	markedPoint = -1;
	update();
}

// indica si un enlace sería válido
///@todo tendría que mirar también si el tipo de las propiedades es compatible.
bool Node::isValidLink(Node *fromNode, int fromPoint, Node *toNode, int toPoint) const
{
	int fromNumProp = fromNode->numProp;
	int toNumProp = toNode->numProp;

	if (fromNode == toNode) return false; // si son iguales
	if (fromNode->parentItem() != toNode->parentItem()) return false; // si no están al mismo nivel
	if ( (fromPoint < 0) || (toPoint < 0) ) return false; // si alguno no es un punto
	if ( (fromPoint < fromNumProp) && (toPoint < toNumProp) ) return false; // si los dos son de entrada
	if ( (fromPoint >= fromNumProp) && (toPoint >= toNumProp) ) return false; // si los dos son de salida
	if ( (fromPoint >= 2 * fromNumProp) || (toPoint >= 2 * toNumProp) ) return false; // si alguno no es un punto existente
	return true;
}

int Node::insertPos() const
{
	return numProp;
}

int Node::insertProperty(QString name, int type, bool input, bool output)
{
	int pos = insertPos();
	insertProperty(pos, name, type, input, output);
	return pos;
}

void Node::insertProperty(int pos, QString name, int type, bool input, bool output)
{
	prepareGeometryChange();
	itemProp.insertProperty(pos, name, type, input, output);
	numProp = itemProp.getProperties().size();

	CorrectTextChange();
	update();
}

void Node::removeProperty(QString name)
{
	prepareGeometryChange();
	itemProp.deleteProperty(name);
	numProp = itemProp.getProperties().size();

	CorrectTextChange();
	update();
}

void Node::deleteProperty(int pos)
{
	prepareGeometryChange();
	itemProp.deleteProperty(pos);
	numProp = itemProp.getProperties().size();

	CorrectTextChange();
	update();
}

void Node::CorrectTextChange()
{
	// recalcula el rectángulo exterior
    QFontMetricsF metrics = qApp->font();
	lineSpacing = metrics.lineSpacing();
    outlinerect = metrics.boundingRect(QString("") + QString("(%1) ").arg(getId()) + name);

	const QList<QString> props = itemProp.getProperties();
	for (int i = 0; i < props.size(); i++)
		outlinerect |= metrics.boundingRect(props[i]);

    outlinerect.adjust(0.0, 0.0, lineSpacing*4, props.size()*metrics.lineSpacing() /* sin +1, por que ya tiene el alto de una linea */);


	// recalcula el texto a escribir
	QString propsText("");
	for (int i = 0; i < props.size(); i++) {
		if (i > 0) propsText += QString("\n");
		propsText += props[i];
	}

	setText(propsText);
	updateLinksPos();
}

void Node::delLastProp()
{
	prepareGeometryChange();
	deleteProperty(numProp - 2);
	update();
}

QVariant Node::itemChange(GraphicsItemChange change,
                          const QVariant &value)
{
    if (change == ItemPositionHasChanged)
		updateLinksPos();

    return QGraphicsItem::itemChange(change, value);
}

void Node::updateLinksPos()
{
	foreach (Link *link, getLinks())
		link->trackNodes();
}

QRectF Node::outlineRect() const
{
	return outlinerect;
}

int Node::roundness(double size) const
{
    const int Diameter = 12;
    return 100 * Diameter / int(size);
}

// Devuelve el indice del punto de enlace que hay debajo de la posición "pos", en coordenadas del blocknode;
// empieza a contar desde 0 y los de los de salida los cuenta a continuación de los de entrada;
// si "pos" no está sobre ningún punto de enlace válido devuelve -1.
int Node::pointAt(QPointF pos) const
{
	QRectF rect = outlineRect();
	if ((pos.x() >= rect.left() + lineSpacing*0.1) && (pos.x() <= rect.left() + lineSpacing*0.9)) // si está en la columna de entrada
	{
		if (pos.y() - rect.top() >= lineSpacing*1.1) // si está por debajo del título
		{
			int relativePos = (int)(pos.y() - rect.top() - lineSpacing*1.1);
			if (relativePos % (int)lineSpacing <= lineSpacing*0.8) // si está sobre el lugar del punto
				if (itemProp.isInput((int)(relativePos / lineSpacing))) return (int)(relativePos / lineSpacing); // si la propiedad tiene enlace de entrada, es valido
		}
	}
	else if ((pos.x() >= rect.right() - lineSpacing*0.9) && (pos.x() <= rect.right() - lineSpacing*0.1)) // si está en la columna de salida
	{
		if (pos.y() - rect.top() >= lineSpacing*1.1) // si está por debajo del título
		{
			int relativePos = (int)(pos.y() - rect.top() - lineSpacing*1.1);
			if (relativePos % (int)lineSpacing <= lineSpacing*0.8) // si está sobre el lugar del punto
				if (itemProp.isOutput((int)(relativePos / lineSpacing))) return (int)(relativePos / lineSpacing + numProp);  // si la propiedad tiene enlace de salida, es valido
		}
	}
	return -1;
}

QString Node::propName(int point) const
{
	if ( (point < 0) || (point >= 2 * numProp) ) return QString(); // si point se sale de rango

	if (point >= numProp) point = point - numProp; // ignoro si es de entrada o salida
	return itemProp.getProperties()[point];
}

int Node::propPoint(QString name, bool in) const
{
	int pos = itemProp.getProperties().indexOf(name);
	if (pos < 0) return pos;
	if (!in) return pos += numProp;
	return pos;
}

int Node::propType(int point) const
{
	if ( (point < 0) && (point >= 2 * numProp) ) return 0; // si point se sale de rango devuelvo "no type"

	if (point >= numProp) point = point - numProp; // ignoro si es de entrada o salida
	return itemProp.propertyType(point);
}

void Node::setHide(bool hide)
{
	foreach(Link *link, getLinks())
		link->setVisible(!hide);

	setVisible(!hide);
}

