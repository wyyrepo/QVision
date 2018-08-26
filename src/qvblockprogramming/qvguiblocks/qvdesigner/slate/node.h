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


#ifndef NODE_H
#define NODE_H

#include <QApplication>
#include <QColor>
#include <QGraphicsItem>
#include <QSet>

#include "link.h"
#include "slatewindow.h"
#include "../facade/itemproperties.h"

class ItemProperties;

#ifndef DOXYGEN_IGNORE_THIS

class Node : public QGraphicsItem
{
	friend class GroupNode;
    Q_DECLARE_TR_FUNCTIONS(Node)

public:
    Node(QString _name, SlateWindow *wind, QGraphicsItem * parent = 0, QGraphicsScene * scene = 0);
    Node(ItemProperties item, QString _name, uint _id, SlateWindow *wind, QGraphicsItem * parent = 0, QGraphicsScene * scene = 0);
    ~Node();

    void setText(const QString &text);
    QString text() const;
    void setTextColor(const QColor &color);
    QColor textColor() const;
    void setOutlineColor(const QColor &color);
    QColor outlineColor() const;
    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void addInLink(Link *link);
    void addOutLink(Link *link);
    virtual void removeLink(Link *link);
	QList<Link *> getLinks() const;
	QList<Link *> getInLinks() const;
	QList<Link *> getOutLinks() const;
	int precursors(QList<Node *> tail = QList<Node *>());

	QString getName() const { return name; }
	QString getType() const { return type; }
	void setType(QString _type) { type = _type; }
    QRectF boundingRect() const;
    QPainterPath shape() const;

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	virtual QPointF scenePointPos(int point) const;
	virtual QPointF scenePointPos(QString name, bool in) const;
	virtual void updateLinksPos();
	virtual void setHide(bool hide);
	int numProps() const;
	QString propName(int point) const; // devuelve el nombre de la propiedad señalada por point
	int propPoint(QString name, bool in) const; // devuelve el punto (de entrada o salida) de una propiedad.
	int propType(int point) const; // devuelve el tipo de la propiedad señalada por point
	void insertProperty(int pos, QString name, int type, bool input, bool output);
	int insertProperty(QString name, int type, bool input, bool output);
	void removeProperty(QString name);
	uint getId();
	void setName(QString _name);
	void prepareHierarchy(); // actualiza a toda la gerarquía de grupos que tiene por encima
	void updateHierarchy(); // actualiza a toda la gerarquía de grupos que tiene por encima
	void publicPrepareGeometryChange();


protected:
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void CorrectTextChange();

	void markPoint(int point, bool validity);
	void unmarkPoint();
	bool isValidLink(Node *fromNode, int fromPoint, Node *toNode, int toPoint) const;
	void deleteProperty(int pos);
	void delLastProp();

	virtual QRectF outlineRect() const;
	virtual int roundness(double size) const;
	virtual int pointAt(QPointF pos) const;
	virtual int insertPos() const; // posición en que se quieren insertar las nuevas propiedades, para que sea la última menos el los de los "..."
	virtual void validLinkRelease(Node *fromNode, int fromPoint, Node *toNode, int toPoint); // función que trata un nuevo enlace y llama a la slate para crearlo
	ItemProperties getItemProp() { return itemProp; }

    QList<Link *> myInLinks;
	QList<Link *> myOutLinks;

    QString myText;
    QColor myTextColor;
    QColor myBackgroundColor;
    QColor myOutlineColor;

	QString name;
	QString type;

	ItemProperties itemProp; // propiedades del block asociado
	int numProp; // número de propiedades del block asociado
	SlateWindow *window; // ventana con que se ha creado, para lanzarle las peticiones de creación de links
	QRectF outlinerect;

	int clickedPoint; // indica si el último click se ha hecho sobre una de los puntos, y sobre cual
	QGraphicsLineItem *line; // linea indicadora del proceso de enlace
	int externalMarkedPoint; // punto de otro item sobre el que se está intentando realizar un enlace
	Node *externalMarkedItem; // item sobre el que se esa intentando realizar el enlace
	int markedPoint; // punto local que se ha seleccionado para colorear por que se está intentando hacer un link sobre el
	bool markedValidity; // indica si el markedPoint es un objetivo correcto, lo que determinará el color usado

	uint id;

	double lineSpacing;
};

#endif
#endif
