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

#ifndef SLATEWINDOW_H
#define SLATEWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QPair>
#include <QAction>
#include <iostream>


class QGraphicsItem;
class QGraphicsScene;
class QGraphicsView;
class Link;
class Node;
class GroupNode;
class ItemNode;
class ItemProperties;
class SlateView;
class QVDesignerGUI;

#ifndef DOXYGEN_IGNORE_THIS


class LinkInfo
{
public:
	///@todo como distingue entre si el ID es como Nodo o como Grupo???????????
	LinkInfo(): node(0), prop(""), input(false) {  }

	LinkInfo(uint _node, QString _prop, bool _input): node(_node), prop(_prop), input(_input) { }

	bool operator==(const LinkInfo &other) const { return (node == other.getNode() && prop == other.getProp() && input == other.getInput()); }

	uint getNode() const { return node; }

	void setNode(uint _node) { node = _node; }

	QString getProp() const { return prop; }

	void setProp(QString _prop) { prop = _prop; }

	bool getInput() const { return input; }

	void setInput(bool _input) { input = _input; }

protected:
	uint node;
	QString prop;
	bool input;
};

class GroupInfo
{
public:
	GroupInfo(): id(0), name(""), nodes(), subgroups(), visibleNodeLinks(), visibleSubgroupLinks(), pos(0.0, 0.0) { }

	GroupInfo(uint _id, QString _name): id(_id), name(_name), nodes(), subgroups(), visibleNodeLinks(), visibleSubgroupLinks(), pos(0.0, 0.0) { }

	uint getId() const { return id; }

	QString getName() const { return name; }

	void addNode(uint node) { if (!nodes.contains(node)) nodes.append(node); }

	void addSubgroup(uint subgroup) { if (!subgroups.contains(subgroup)) subgroups.append(subgroup); }

	void delSubgroup(uint subgroup) { subgroups.removeAll(subgroup); }

	void addNodeLink(LinkInfo link) { if (!visibleNodeLinks.contains(link)) visibleNodeLinks.append(link); }

	void addSubgroupLink(LinkInfo link) { if (!visibleSubgroupLinks.contains(link)) visibleSubgroupLinks.append(link); }

	void delNode(uint node) {
		int pos = nodes.indexOf(node);
		if (pos > 0) nodes.removeAt(pos);
	}

	void delNodeLink(LinkInfo link) {
		int pos = visibleNodeLinks.indexOf(link);
		if (pos > 0) visibleNodeLinks.removeAt(pos);
	}

	void delSubgroupLink(LinkInfo link) {
		int pos = visibleSubgroupLinks.indexOf(link);
		if (pos > 0) visibleSubgroupLinks.removeAt(pos);
	}

	QList<uint> getNodes() const { return nodes; }

	QList<uint> getSubgroups() const { return subgroups; }

	QList<LinkInfo> getNodeLinks() const { return visibleNodeLinks; }

	QList<LinkInfo> getSubgroupLinks() const { return visibleSubgroupLinks; }

	void setPos(QPointF _pos) { pos = _pos; }

	void setName(QString _name) { name = _name; }

	QPointF getPos() const { return pos; }

	void setAbstract(bool abs) { abstract = abs; }

	bool getAbstract() const {  return abstract; }

	void updateNodeId(uint oldId, uint newId) {
		int pos = nodes.indexOf(oldId);
		if (pos >= 0) {
			nodes.removeAt(pos);
			nodes.append(newId);
		}
		for (QList<LinkInfo>::iterator it = visibleNodeLinks.begin(); it != visibleNodeLinks.end(); it++) { // uso un iterador para poder modificar
			if ((*it).getNode() == oldId)
				(*it).setNode(newId);
		}
	}

	void updateSubgroupId(uint oldId, uint newId) {
		int pos = subgroups.indexOf(oldId);
		if (pos >= 0) {
			subgroups.removeAt(pos);
			subgroups.append(newId);
		}
		for (QList<LinkInfo>::iterator it = visibleSubgroupLinks.begin(); it != visibleSubgroupLinks.end(); it++) { // uso un iterador para poder modificar
			if ((*it).getNode() == oldId)
				(*it).setNode(newId);
		}
	}

protected:
	uint id;
	QString name;
	QList<uint> nodes;
	QList<uint> subgroups;
	QList<LinkInfo> visibleNodeLinks;
	QList<LinkInfo> visibleSubgroupLinks;
	QPointF pos;
	bool abstract;
};


// usar QGraphicsItem::collidesWithItem() para meter automátcamente un item dentro de un grupo (debería estar en node)
class SlateWindow : public QMainWindow
{
    Q_OBJECT

public:
    SlateWindow(QVDesignerGUI *desig, QWidget * parent = 0);
	bool createLink(Node *fromNode, int fromPoint, Node *toNode, int toPoint);
	void addLinkLine(uint fromId, QString fromProp, uint toId, QString toProp, bool sinc, bool sequential);
	void delLinkLine(uint fromId, QString fromProp, uint toId, QString toProp);
	void addItemNode(QString type, QString name, uint id, ItemProperties *item, uint lastId = 0);
	void delItemNode(uint id);
	void addProperty(uint id, QString propName, int type, bool in, bool out);
	void delProperty(uint id, QString propName);
	void closeEvent(QCloseEvent *event);
	void includeItemType(QString itemType);
	void arrangeItems();
	void clearSelection();
	bool isSelected(QGraphicsItem *item);
	void setName(Node *item, QString name);
	void setItemName(uint id, QString name);
	QPointF getNodePos(uint id) const;
	bool moveNode(uint id, QPointF pos);
	QList<GroupInfo> getGroups();
	void eraseGroups();
	uint createGroup(GroupInfo group); // devuelve el identificador del nuevo grupo creado, 0 si aun no se ha creado alguno de sus elementos (nodo o subgrupo)

public slots:
    void showProperties();
	void showProperties(Node *node);
	void showMessage(QString message);

private slots:
    void del();
	void join();
    void bringToFront();
    void sendToBack();
    void updateActions();
	void insertItem(QString type);
	void run();
	void stop();
	bool saveAs();
	bool open();
	bool exportAs();

signals:
	/// @brief Emited when the window closes.
	void closed();

private:
    typedef QPair<Node *, Node *> NodePair;

    QPoint startPos;

    void createMenus();
    void createToolBars();
    void setZValue(int z);
    void setupNode(Node *node);
    Node *selectedNode() const;
    Link *selectedLink() const;
    NodePair selectedNodePair() const;
    QList<QGraphicsItem *> selectedNodeGroup() const;
	QList<QGraphicsItem *> onlyParents(QList<QGraphicsItem *> items) const;
    bool saveFile(const QString &fileName, bool xmlFile);
    bool exportFile(const QString &fileName);
	int precursors(Node *node);

    QMenu *fileMenu;
    QMenu *editMenu;
	QMenu *insertMenu;
	QMenu *insertUserSubmenu;
	QList<QMenu *> insertSubmenus;
    QToolBar *editToolBar;
    QAction *exitAction;
    QAction *addSLinkAction;
    QAction *addALinkAction;
    QAction *addQLinkAction;
	QActionGroup *linkGroup;
    QAction *joinAction;
    QAction *deleteAction;
    QAction *bringToFrontAction;
    QAction *sendToBackAction;
    QAction *propertiesAction;
	QAction *runAction;
	QAction *stopAction;
	QAction *exportAction;
	QAction *saveAsAction;
	QAction *openAction;

	QStatusBar *statusbar;

    QGraphicsScene *scene;
    SlateView *view;
	QVDesignerGUI *designer;

    int minZ;
    int maxZ;
    int seqNumber;

	QMap<uint, Node *> insertNodes;
	QMap<uint, QPointF> insertNodesPos;
	QMap<QString, Link *> insertLinks;

	QMap<Node *, GroupInfo> createdGroupInfos;
	QMap<uint, GroupNode *> createdGroups;
};

#endif
#endif
