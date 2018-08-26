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
#include <QDebug>
#include <iostream>

#include "slatewindow.h"
#include "sinclink.h"
#include "asinclink.h"
#include "sequenlink.h"
#include "node.h"
#include "groupnode.h"
#include "inputnode.h"
#include "middlenode.h"
#include "outputnode.h"
#include "slateview.h"
#include "insertaction.h"

#include <QVDesignerGUI>
//#include "../designergui.h"
#include "../facade/itemproperties.h"


SlateWindow::SlateWindow(QVDesignerGUI *desig, QWidget * parent): QMainWindow(parent), designer(desig)
{
    scene = new QGraphicsScene(-1180, -900, 3200, 2400);

    view = new SlateView;
    view->setScene(scene);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    view->setContextMenuPolicy(Qt::ActionsContextMenu);
    setCentralWidget(view);

    minZ = 0;
    maxZ = 0;
    seqNumber = 0;

    createMenus();
    createToolBars();

	statusbar = new QStatusBar();
	setStatusBar(statusbar);

    connect(scene, SIGNAL(selectionChanged()), this, SLOT(updateActions()));

	scene->setBackgroundBrush(QPixmap(":/images/background1.png"));

    setWindowTitle(tr("Slate"));

	showMessage("Pulsa \"Stop\" para poder editar el ejemplo.");

    updateActions();
}

void SlateWindow::closeEvent(QCloseEvent *)
	{
	emit closed();
	}

///@todo reducir el tamaño del Pen del link en función del número de antecesores (*0.5 por cada uno)
bool SlateWindow::createLink(Node *fromNode, int fromPoint, Node *toNode, int toPoint)
{
	// si está en ejecución no se permite lincar
	if (stopAction->isEnabled()) return false;

	uint fromId = 0, toId = 0;
	fromId = fromNode->getId();
	toId = toNode->getId();

	bool sinc = addSLinkAction->isChecked();
	bool sequ = (!addSLinkAction->isChecked() && !addALinkAction->isChecked());

	designer->addLink(fromId, fromNode->propName(fromPoint), toId, toNode->propName(toPoint), sinc, sequ);

return true;
}

void SlateWindow::addLinkLine(uint fromId, QString fromProp, uint toId, QString toProp, bool sinc, bool sequential)
{
	Link *link;
	QString linkName = QString("%1").arg(fromId) + "[" + fromProp + "] => " + QString("%1").arg(toId) + "[" + toProp + "]";

	if ( insertNodes.contains(fromId) && insertNodes.contains(toId) ) {
		Node *from = insertNodes.value(fromId);
		Node *to = insertNodes.value(toId);

		if (sequential) {
			link = new SequenLink(from, fromProp, to, toProp, 0, scene);
			insertLinks.insert(linkName, link);
			link->trackNodes();
		}
		else if (sinc) {
			link = new SincLink(from, fromProp, to, toProp, 0, scene);
			insertLinks.insert(linkName, link);
			link->trackNodes();
		}
		else {
			link = new AsincLink(from, fromProp, to, toProp, 0, scene);
			insertLinks.insert(linkName, link);
			link->trackNodes();
		}
	}
}

void SlateWindow::delLinkLine(uint fromId, QString fromProp, uint toId, QString toProp)
{
	QString linkName = QString("%1").arg(fromId) + "[" + fromProp + "] => " + QString("%1").arg(toId) + "[" + toProp + "]";
	if (insertLinks.contains(linkName)) {
		delete insertLinks.value(linkName);
		insertLinks.remove(linkName);
	}
}

void SlateWindow::insertItem(QString type)
{
	QString name = type.toLower();
	name.replace('<', '_');
	name.replace(',', '_');
	name.replace('>', '_');
	name.replace(' ', "");

	designer->addItem(type, name);
}

void SlateWindow::setName(Node *item, QString name)
{
	designer->setName(insertNodes.key(item), name); // si no esta el item devuelve 0, que es id nulo
}

void SlateWindow::setItemName(uint id, QString name)
{
	if (insertNodes.contains(id))
		insertNodes.value(id)->setName(name);
}

void SlateWindow::addItemNode(QString type, QString name, uint id, ItemProperties *item, uint lastId)
{
	///@todo ver si los nodos al destruirse tendrían que destruir explicitamente el ItemProperties pasado
	bool inputItemsContainsType = false;
	foreach(QList<QString> groupItems, designer->getInputItemTypes().values())
		if (groupItems.contains(type)) {
			inputItemsContainsType = true;
			break;
		}
	if (inputItemsContainsType) {
		InputNode *node = new InputNode(*item, name, id, this, 0, scene);
		insertNodes.insert(id, node);
		setupNode(node);
		if (insertNodesPos.contains(lastId)) {
			node->setPos(insertNodesPos.value(lastId));
			insertNodesPos.remove(lastId);
			insertNodesPos.insert(id, node->pos());
		}
		else
			insertNodesPos.insert(id, node->pos());
	}
	else {
		bool middleItemsContainsType = false;
		foreach(QList<QString> groupItems, designer->getMiddleItemTypes().values())
			if (groupItems.contains(type)) {
				middleItemsContainsType = true;
				break;
			}
		if (middleItemsContainsType) {
			MiddleNode *node = new MiddleNode(*item, name, id, this, 0, scene);
			insertNodes.insert(id, node);
			setupNode(node);
			if (insertNodesPos.contains(lastId)) {
				node->setPos(insertNodesPos.value(lastId));
				insertNodesPos.remove(lastId);
				insertNodesPos.insert(id, node->pos());
			}
			else
				insertNodesPos.insert(id, node->pos());
		}
		else {
			bool outputItemsContainsType = false;
			foreach(QList<QString> groupItems, designer->getOutputItemTypes().values())
				if (groupItems.contains(type)) {
					outputItemsContainsType = true;
					break;
				}
			if (outputItemsContainsType) {
				OutputNode *node = new OutputNode(*item, name, id, this, 0, scene);
				insertNodes.insert(id, node);
				setupNode(node);
				if (insertNodesPos.contains(lastId)) {
					node->setPos(insertNodesPos.value(lastId));
					insertNodesPos.remove(lastId);
					insertNodesPos.insert(id, node->pos());
				}
				else
					insertNodesPos.insert(id, node->pos());
			}
		}
	}
}

void SlateWindow::delItemNode(uint id)
{
	if (insertNodes.contains(id)) {
		insertNodesPos.remove(id);	// guarda la posición del nodo, por si se vuelve a insertar uno con el mismo nombre
		insertNodesPos.insert(id, insertNodes.value(id)->pos());
		delete insertNodes.value(id);
		insertNodes.remove(id);
	}
}

void SlateWindow::addProperty(uint id, QString propName, int type, bool in, bool out)
{
	if (insertNodes.contains(id)) {
		insertNodes.value(id)->insertProperty(propName, type, in, out);
	}
}

void SlateWindow::delProperty(uint id, QString propName)
{
	if (insertNodes.contains(id)) {
		insertNodes.value(id)->removeProperty(propName);
	}
}

void SlateWindow::del()
{
	// primero borro solo los links, ya que al borrar un nodo pueden desaparecer links seleccionados, que se intentarian borrar y daría un core
	foreach(QGraphicsItem *item, scene->selectedItems()) {
        Link *link = dynamic_cast<Link *>(item);

        if (link && (link->fromNode() != NULL) && (link->toNode() != NULL)) {
			uint fromId = 0, toId = 0;
			fromId = link->fromNode()->getId();
			toId = link->toNode()->getId();

			designer->delLink(fromId, link->fromProp(), toId, link->toProp());
        }
    }

	// luego borro los grupos seleccionados
	foreach(QGraphicsItem *item, scene->selectedItems()) {
		GroupNode *node = dynamic_cast<GroupNode *>(item);

		if (node) {
			// si es subgrupo de otro grupo, todos los elementos internos de este pasan a formar parte del padre
			// y el grupo borrado se desregistra como subgrupo del padre
			GroupInfo delGroupInfo = createdGroupInfos[(Node *)node]; // obtengo el GroupInfo del grupo a borrar
			foreach(Node *group, createdGroupInfos.keys()) { // para cada grupo creado en la pizarra
				GroupInfo groupInfo = createdGroupInfos[group];
				foreach(uint subgroupId, groupInfo.getSubgroups())
					if (subgroupId == delGroupInfo.getId()) { // si contiene como subgrupo al grupo a borrar
						foreach(uint internalNode, delGroupInfo.getNodes()) // le añado los nodos de este
							groupInfo.addNode(internalNode);
						foreach(uint internalSubgroup, delGroupInfo.getSubgroups()) // le añado los subgrupos de este
							groupInfo.addSubgroup(internalSubgroup);
						groupInfo.delSubgroup(delGroupInfo.getId()); // quito el grupo a borrar como su subgrupo
						createdGroupInfos.insert(group, groupInfo); // y actualizo los cambios
					}
			}

			createdGroupInfos.remove(node);
			createdGroups.remove(node->getId());
			delete node;
		}
    }

	// y por último los nodos reatantes
	foreach(QGraphicsItem *item, scene->selectedItems()) {
		Node *node = dynamic_cast<InputNode *>(item);
		if (!node) node = dynamic_cast<MiddleNode *>(item);
		if (!node) node = dynamic_cast<OutputNode *>(item);

		if (node) {
			uint itemnode = 0;
			itemnode = node->getId();
			designer->delItem(itemnode);
		}
    }
}

void SlateWindow::join()
{
	QList<QGraphicsItem *> group = selectedNodeGroup();

	// obtengo la posición media de los items a agrupar, para situar el grupo lo más centrado posible
	QPointF middlePos;
	int count = 0;
	foreach (QGraphicsItem *item, group) {
		Node *itemNode = dynamic_cast<Node *>(item);
		if (itemNode) {
			middlePos += itemNode->pos();
			count++;
		}
	}
	middlePos /= count;

	// creo el nuevo grupo
    GroupNode *node = new GroupNode("Group", this, 0, scene);
	node->setPos(middlePos);

	// si los items seleccionados estaban ya dentro de otro grupo, este se añade a el (sino a la escena)
	if ( !group.isEmpty() && group.first() && group.first()->parentItem() ) {
		GroupNode *parentNode = dynamic_cast<GroupNode *>(group.first()->parentItem());
		if (parentNode) parentNode->addNode(node);
	}

	// para cada item si es un nodo lo añado al nuevo grupo
	foreach (QGraphicsItem *item, group) {
		Node *itemNode = dynamic_cast<Node *>(item);
		if (itemNode) {
			node->addNode(itemNode);

			//se actualiza el tamaño de sus links
			//y si la otra punta no se va a meter al grupo pasa a formar parte de este
			foreach (Link *link, itemNode->getInLinks()) {
				Node *other = link->fromNode();
				if (group.contains(other)) {
					QPen pen = link->pen();
					pen.setWidthF(pen.width()*0.5);
					link->setPen(pen);
					link->update();
				}
			}
			foreach (Link *link, itemNode->getOutLinks()) {
				Node *other = link->toNode();
				if (group.contains(other)) {
					QPen pen = link->pen();
					pen.setWidthF(pen.width()*0.5);
					link->setPen(pen);
					link->update();
				}
			}
			itemNode->updateLinksPos(); // para que se actualiza la posición y tamaño de los links del nodo
		}
	}

	createdGroupInfos.insert(node, node->getInfo());
	createdGroups.insert(node->getId(), node);
}

void SlateWindow::bringToFront()
{
    maxZ += 2; // dos, uno para el y otro para sus link que serán: el + 1
    setZValue(maxZ);
}

void SlateWindow::sendToBack()
{
    minZ += 2; // dos, uno para el y otro para sus link que serán: el + 1
    setZValue(minZ);
}

void SlateWindow::run()
{
	foreach (QAction *action, insertMenu->actions()) {
		action->setEnabled(false);
	}
	foreach (QMenu *submenu, insertSubmenus) {
		submenu->setEnabled(false);
		foreach (QAction *action, submenu->actions()) {
			action->setEnabled(false);
		}
	}

	deleteAction->setEnabled(false);
	openAction->setEnabled(false);

	runAction->setEnabled(false);
	stopAction->setEnabled(true);
	designer->run();
}

void SlateWindow::stop()
{
	designer->stop();
	stopAction->setEnabled(false);
	runAction->setChecked(false);
	runAction->setEnabled(true);

    bool hasSelection = !scene->selectedItems().isEmpty();
	deleteAction->setEnabled(hasSelection);
	openAction->setEnabled(true);

	foreach (QAction *action, insertMenu->actions()) {
		action->setEnabled(true);
	}
	foreach (QMenu *submenu, insertSubmenus) {
		foreach (QAction *action, submenu->actions()) {
			action->setEnabled(true);
		}
		submenu->setEnabled(true);
	}
}

void SlateWindow::setZValue(int z)
{
    Node *node = selectedNode();
    if (node) {
        node->setZValue(z);
		node->updateLinksPos();
	}
}

void SlateWindow::showProperties()
{
    Node *node = selectedNode();

    if (node) showProperties(node);
}

void SlateWindow::showProperties(Node *node)
{
	uint itemnode = 0;
	itemnode = node->getId();

	designer->showProperties(itemnode);
}

void SlateWindow::updateActions()
{
    bool hasSelection = !scene->selectedItems().isEmpty();
    bool isNode = (selectedNode() != 0);
//	bool isNodePair = (selectedNodePair() != NodePair());
	bool isNodeGroup = false;
	int count = 0;
	foreach (QGraphicsItem *item, selectedNodeGroup())
		if (dynamic_cast<Node *>(item)) count++;
	if (count > 0) isNodeGroup = true;

	joinAction->setEnabled(isNodeGroup);
	// si está en ejecución no se permite borrar
    if (runAction->isEnabled()) {
		deleteAction->setEnabled(hasSelection);
		openAction->setEnabled(true);
	}
    bringToFrontAction->setEnabled(isNode);
    sendToBackAction->setEnabled(isNode);
    propertiesAction->setEnabled(isNode);

    foreach (QAction *action, view->actions())
        view->removeAction(action);

    foreach (QAction *action, editMenu->actions()) {
        if (action->isEnabled())
            view->addAction(action);
    }

	if (!hasSelection) {
		// añado las acciones del menu insertar al desplegable del botón derecho (de dos formas distintas)
		QAction *insertTitle = new QAction(tr("Insert"), this);
		insertTitle->setEnabled(false);
		QFont font(insertTitle->font());
		font.setWeight(QFont::Black);
		font.setStyle(QFont::StyleItalic);
		insertTitle->setFont(font);
		view->addAction(insertTitle);
		view->addActions(insertMenu->actions());
	}
}

void SlateWindow::clearSelection()
{
	scene->clearSelection();
}

bool SlateWindow::isSelected(QGraphicsItem *item)
{
	return scene->selectedItems().contains(item);
}

void SlateWindow::setupNode(Node *node)
{
    node->setPos( QPoint(10 + (seqNumber % 10) * 6, 20 + (seqNumber % 10) * 6) );
    ++seqNumber;

    clearSelection();
    node->setSelected(true);
    bringToFront();
}

void SlateWindow::createMenus()
{
	///@todo usar el QAction.setStatusTip(string) para establecer una indicación de que hace cada acción
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    addALinkAction = new QAction(tr("&Asynchronous Link Mode"), this);
    addALinkAction->setIcon(QIcon(":/images/alink.png"));
    addALinkAction->setShortcut(tr("Ctrl+A"));
	addALinkAction->setCheckable(true); // para que se mantenga pulsada
	addALinkAction->setChecked(true); // por defecto está seleccionado asincrono

    addSLinkAction = new QAction(tr("&Synchronous Link Mode"), this);
    addSLinkAction->setIcon(QIcon(":/images/slink.png"));
    addSLinkAction->setShortcut(tr("Ctrl+S"));
	addSLinkAction->setCheckable(true); // para que se mantenga pulsada

    addQLinkAction = new QAction(tr("Se&quential Link Mode"), this);
    addQLinkAction->setIcon(QIcon(":/images/qlink.png"));
    addQLinkAction->setShortcut(tr("Ctrl+Q"));
	addQLinkAction->setCheckable(true); // para que se mantenga pulsada

	// con esto conseguimos meterlas en un grupo exclusivo, o una o la otra
	linkGroup = new QActionGroup(this);
	linkGroup->setExclusive(true);
	linkGroup->addAction(addALinkAction);
	linkGroup->addAction(addSLinkAction);
	linkGroup->addAction(addQLinkAction);


    joinAction = new QAction(tr("&Join"), this);
    joinAction->setIcon(QIcon(":/images/join.png"));
    joinAction->setShortcut(tr("Ctrl+J"));
    connect(joinAction, SIGNAL(triggered()), this, SLOT(join()));

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setIcon(QIcon(":/images/delete.png"));
    deleteAction->setShortcut(tr("Del"));
	deleteAction->setEnabled(false);
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(del()));

    bringToFrontAction = new QAction(tr("Bring to &Front"), this);
    bringToFrontAction->setIcon(QIcon(":/images/bringtofront.png"));
    connect(bringToFrontAction, SIGNAL(triggered()),this, SLOT(bringToFront()));

    sendToBackAction = new QAction(tr("&Send to Back"), this);
    sendToBackAction->setIcon(QIcon(":/images/sendtoback.png"));
    connect(sendToBackAction, SIGNAL(triggered()), this, SLOT(sendToBack()));

    propertiesAction = new QAction(tr("P&roperties..."), this);
    connect(propertiesAction, SIGNAL(triggered()), this, SLOT(showProperties()));

    runAction = new QAction(tr("&Run"), this);
    runAction->setIcon(QIcon(":/images/run.png"));
	runAction->setCheckable(true); // para que se mantenga pulsada
	runAction->setChecked(true); // porque comienza en ejecución
	runAction->setEnabled(false); // porque comienza en ejecución
    connect(runAction, SIGNAL(triggered()), this, SLOT(run()));

    stopAction = new QAction(tr("&Stop"), this);
    stopAction->setIcon(QIcon(":/images/stop.png"));
	stopAction->setEnabled(true); // porque comienza en ejecución
    connect(stopAction, SIGNAL(triggered()), this, SLOT(stop()));

    exportAction = new QAction(tr("&Export"), this);
    exportAction->setShortcut(tr("Ctrl+E"));
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportAs()));

    saveAsAction = new QAction(tr("&Save As"), this);
    saveAsAction->setShortcut(tr("Ctrl+S"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    openAction = new QAction(tr("&Load"), this);
    openAction->setShortcut(tr("Ctrl+L"));
	openAction->setEnabled(false);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(exportAction);
	fileMenu->addAction(saveAsAction);
	fileMenu->addAction(openAction);
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(addALinkAction);
    editMenu->addAction(addSLinkAction);
    editMenu->addAction(addQLinkAction);

    editMenu->addSeparator();
    editMenu->addAction(joinAction);
    editMenu->addAction(deleteAction);
    editMenu->addSeparator();
    editMenu->addAction(bringToFrontAction);
    editMenu->addAction(sendToBackAction);
    editMenu->addSeparator();
    editMenu->addAction(propertiesAction);


	// generamos el insert menu a partir de la lista que nos devuelve el controlador
	insertMenu = menuBar()->addMenu(tr("&Insert"));

	QMap<QString, QList<QString> > itemTypes = designer->getItemTypes();
	foreach (QString group, itemTypes.keys()) {
		QMenu *submenu = insertMenu->addMenu(group);
		submenu->setEnabled(false);
		insertSubmenus.append(submenu);

		foreach (QString item, itemTypes.value(group))
		{
			InsertAction *action = new InsertAction(item, this);
			action->setEnabled(false);
			connect(action, SIGNAL(triggered(QString)), this, SLOT(insertItem(QString)));
			submenu->addAction(action);
		}
	}
	insertUserSubmenu = insertMenu->addMenu("User node");
	insertUserSubmenu->setEnabled(false);
	insertSubmenus.append(insertUserSubmenu);
}

void SlateWindow::includeItemType(QString itemType)
{
	InsertAction *action = new InsertAction(itemType, this);
	action->setEnabled(false);
	connect(action, SIGNAL(triggered(QString)), this, SLOT(insertItem(QString)));
	insertUserSubmenu->addAction(action);

	updateActions();
}

void SlateWindow::createToolBars()
{
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(addALinkAction);
    editToolBar->addAction(addSLinkAction);
    editToolBar->addAction(addQLinkAction);
    editToolBar->addAction(joinAction);
    editToolBar->addAction(deleteAction);
    editToolBar->addSeparator();
    editToolBar->addSeparator();
    editToolBar->addAction(bringToFrontAction);
    editToolBar->addAction(sendToBackAction);

	editToolBar->addSeparator();
	editToolBar->addAction(runAction);
	editToolBar->addAction(stopAction);
}

Node *SlateWindow::selectedNode() const
{
    QList<QGraphicsItem *> items = scene->selectedItems();
    if (items.count() == 1) {
        return dynamic_cast<Node *>(items.first());
    } else {
        return 0;
    }
}

Link *SlateWindow::selectedLink() const
{
    QList<QGraphicsItem *> items = scene->selectedItems();
    if (items.count() == 1) {
        return dynamic_cast<Link *>(items.first());
    } else {
        return 0;
    }
}

SlateWindow::NodePair SlateWindow::selectedNodePair() const
{
    QList<QGraphicsItem *> items = scene->selectedItems();
    if (items.count() == 2) {
        Node *first = dynamic_cast<Node *>(items.first());
        Node *second = dynamic_cast<Node *>(items.last());
        if (first && second)
            return NodePair(first, second);
    }
    return NodePair();
}

// devuelve la lista de onlyParents seleccionados, si todos ellos comparten padre (ya sea 0 o un grupo), tambien devuelve los link de dicha lista
QList<QGraphicsItem *> SlateWindow::selectedNodeGroup() const
{
    QList<QGraphicsItem *> items = onlyParents(scene->selectedItems());

	//si quedan almemos dos
    if (items.count() > 1) {
		// y si comparten padre
		QGraphicsItem * parent = 0;
		QMutableListIterator<QGraphicsItem *> i(items);
		if (i.hasNext()) parent = i.next()->parentItem();

		while (i.hasNext())
			if ( i.next()->parentItem() != parent) return QList<QGraphicsItem *>();

		return items;
    }
    return items;
}

// obtiene los QGraphicsItem de la lista cuyo padre no pertenece a la lista
QList<QGraphicsItem *> SlateWindow::onlyParents(QList<QGraphicsItem *> items) const
{
    QList<QGraphicsItem *> parentItems;

    QMutableListIterator<QGraphicsItem *> i(items);
    while (i.hasNext()) {
		i.next();
		bool parent = true;
		QMutableListIterator<QGraphicsItem *> j(items);
		while (j.hasNext()) {
			j.next();
			if ( (i.value()) && (i.value()->parentItem() == j.value()) ) {
				parent = false;
				break;
			}
		}
		if (parent) parentItems.append(i.value());
    }

	return parentItems;
}

bool SlateWindow::exportAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Save C++"), ".",
                               tr("C++ files (*.cpp)"));
    if (fileName.isEmpty())
        return false;
	return saveFile(fileName, false);
}

bool SlateWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Save XML"), ".",
                               tr("XML files (*.xml)"));
    if (fileName.isEmpty())
        return false;
	return saveFile(fileName, true);
}

bool SlateWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Open File"), ".",
                               tr("XML files (*.xml)"));
    if (fileName.isEmpty()) return false;


    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("QVDesignerGUI"),
                             tr("Cannot open file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }
	QTextStream in(&file);
    return (designer->loadXML(in.readAll()));
}

bool SlateWindow::saveFile(const QString &fileName, bool xmlFile)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("QVDesignerGUI"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
	if (xmlFile)
		out << designer->getXMLText();
	else
	    out << designer->getCppText();

    return true;
}

void SlateWindow::showMessage(QString message)
{
	if (statusbar)
		statusbar->showMessage(message, 10000); // lo muestra 10 segundos
}


void SlateWindow::arrangeItems()
{
	QList<QList<Node *> *> levels;
	int left = 10;
	int bottom = 20;
	const int MARGIN = 20;

	// obtengo los niveles en que se encuentran los items, organizandolos por columnas en "levels"
	foreach(Node *node, insertNodes) {
		int level = node->precursors();
		while(levels.size() <= level)
			levels.append(new QList<Node *>);
		levels[level]->append(node);
	}

	//muevo los items en la pizarra en función de los tamaños y niveles de estos
	foreach(QList<Node *> *levelNodes, levels) {
		int maxWidth = 0;
		if (levelNodes) {
			foreach(Node *node, *levelNodes) {
				node->setPos(QPoint(left, bottom));
				insertNodesPos.insert(insertNodes.key(node), node->pos());
				bottom += (int)node->boundingRect().height() + MARGIN; //le sumo a bottom el alto mas un margen
				int width = (int)node->boundingRect().width();
				if (maxWidth < width) maxWidth = width; //actualiza maxWidth
			}
		}
		left += maxWidth + MARGIN; //le sumo a left maxWide mas un margen
		bottom = 20;//reseteo bottom
	}

	// vacio la estructura usada
	foreach(QList<Node *> *levelNodes, levels) {
		levelNodes->clear();
		delete levelNodes;
	}
}

QPointF SlateWindow::getNodePos(uint id) const
{
	return insertNodes.value(id)->pos();
}

bool SlateWindow::moveNode(uint id, QPointF pos)
{
	if (insertNodes.contains(id)) {
		Node *node = insertNodes.value(id);
		node->setPos(pos);
		insertNodesPos.remove(id);
		insertNodesPos.insert(id, node->pos());
		return true;
	}

	return false;
}

QList<GroupInfo> SlateWindow::getGroups()
{
	// actualizo las posiciones de los grupos antes de pasarlos
	foreach(Node *group, createdGroupInfos.keys()) {
		createdGroupInfos[group].setPos(group->pos());
		createdGroupInfos[group].setName(group->getName());
		if (dynamic_cast<GroupNode *>(group))
			createdGroupInfos[group].setAbstract( ((GroupNode *)group)->getAbstract() );
	}

	return createdGroupInfos.values();
}

void SlateWindow::eraseGroups()
{
	foreach(Node *group, createdGroupInfos.keys()) {
		delete group;
	}

	createdGroupInfos.clear();
	createdGroups.clear();
}

uint SlateWindow::createGroup(GroupInfo info)
{
	QList<QGraphicsItem *> group;
	foreach (uint nodeId, info.getNodes()) {
		if (insertNodes.contains(nodeId)) {
			group.append(insertNodes.value(nodeId));
		}
		else {
// 			std::cout << QString("ERROR: Devuelvo 0 porque no existe el nodo %1\n").arg(nodeId).toStdString();
			return 0;
		}
	}
	foreach (uint subgroupId, info.getSubgroups()) {
		if (createdGroups.contains(subgroupId)) {
			group.append(createdGroups.value(subgroupId));
		}
		else {
// 			std::cout << QString("ERROR: Devuelvo 0 porque no existe el grupo %1\n").arg(subgroupId).toStdString();
			return 0;
		}
	}

	// creo el nuevo grupo
    GroupNode *node = new GroupNode(info.getName(), this, 0, scene);
	node->setPos(info.getPos());

	// si los items seleccionados estaban ya dentro de otro grupo, este se añade a el (sino a la escena)
	if ( !group.isEmpty() && group.first() && group.first()->parentItem() ) {
		GroupNode *parentNode = dynamic_cast<GroupNode *>(group.first()->parentItem());
		if (parentNode) parentNode->addNode(node);
	}

	// para cada item si es un nodo lo añado al nuevo grupo
	foreach (QGraphicsItem *item, group) {
		Node *itemNode = dynamic_cast<Node *>(item);
		if (itemNode) {
			node->addNode(itemNode);

			//se actualiza el tamaño de sus links
			//y si la otra punta no se va a meter al grupo pasa a formar parte de este
			foreach (Link *link, itemNode->getInLinks()) {
				Node *other = link->fromNode();
				if (group.contains(other)) {
					QPen pen = link->pen();
					pen.setWidthF(pen.width()*0.5);
					link->setPen(pen);
					link->update();
				}
			}
			foreach (Link *link, itemNode->getOutLinks()) {
				Node *other = link->toNode();
				if (group.contains(other)) {
					QPen pen = link->pen();
					pen.setWidthF(pen.width()*0.5);
					link->setPen(pen);
					link->update();
				}
			}
			itemNode->updateLinksPos(); // para que se actualiza la posición y tamaño de los links del nodo
		}
	}

	createdGroupInfos.insert(node, node->getInfo());
	createdGroups.insert(node->getId(), node);
	node->abstractView(info.getAbstract());

	return node->getId();
}



