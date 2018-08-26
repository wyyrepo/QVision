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


#ifndef GROUPNODE_H
#define GROUPNODE_H

#include "node.h"

#define SUBSCALE 0.3

#ifndef DOXYGEN_IGNORE_THIS

class GroupNode : public Node
{
public:
    GroupNode(QString _name, SlateWindow *wind, QGraphicsItem * parent = 0, QGraphicsScene * scene = 0);
    ~GroupNode();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void addNode(Node *node);
	void updateLinksPos();
    void removeLink(Link *link);
	GroupInfo getInfo();
	void abstractView(bool mode);
	bool getAbstract() const { return abstractPaint; }

protected:
    void paintProps(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paintGroup(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	void drawCurvArrow(const QRectF rectangle, QPainter *painter);
	void changeLinkToGroup(Link *link, bool toNode /* si el nodo que se incluye es el toNode del link */);
    QRectF outlineRect() const;
	void setHide(bool hide);

	bool abstractPaint; // el primero indica el modo en que se pinta (influye el nivel de zoom), el segundo si el zoom paso el umbral
	QMap<Link *, Link *> internalLinks; // los links externos asociados, indexados por su link interno del grupo

	static uint maxId;
	static uint getNewId() { return ++maxId; }
};

#endif
#endif
