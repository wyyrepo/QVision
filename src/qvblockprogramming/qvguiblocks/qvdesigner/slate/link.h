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


#ifndef LINK_H
#define LINK_H

#include <QGraphicsLineItem>

#ifndef DOXYGEN_IGNORE_THIS

class Node;

class Link : public QGraphicsLineItem
{
public:
    Link(Node *fromNode, QString fromProp, Node *toNode, QString toProp, QGraphicsItem * parent = 0, QGraphicsScene * scene = 0);
    ~Link();

    Node *fromNode() const;
    Node *toNode() const;
    QString fromProp() const;
    QString toProp() const;

	void changeFromPoint(Node *newNode, QString NewProp);
	void changeToPoint(Node *newNode, QString NewProp);

    void setColor(const QColor &color);
    QColor color() const;

    virtual void trackNodes();

protected:
	bool sceneEvent(QEvent * event);

    Node *myFromNode;
    Node *myToNode;
	QString myFromProp;
	QString myToProp;

	QGraphicsLineItem line2, line3, line4, line5;
};

#endif
#endif
