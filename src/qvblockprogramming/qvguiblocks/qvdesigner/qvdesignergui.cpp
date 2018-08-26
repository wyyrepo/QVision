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


//#include "qvdesignergui.h"
#include <QVDesignerGUI>
#include <QVApplication>
#include <QVPropertyContainer>
#include <QVPropertyContainerChange>
//#include <QVMPlayerCamera>
#include <QVIndexedStringList>
#include <QVVideoReaderBlock>
#include <QVProcessingBlock>
#include <QVImageCanvas>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "../qvplot.h"
#include "facade/blockdialog.h"
//#include "facade/cameradialog.h"
#include "facade/imagecanvasdialog.h"
#include "facade/camerablockdialog.h"

QVDesignerGUI::QVDesignerGUI(): QObject(), factory(), slate(this), informer(&slate)
{
    qDebug() << "QVDesignerGUI::QVDesignerGUI()";
    if (qvApp == NULL)
        {
        QString str =	"QVDesignerGUI::QVDesignerGUI(): the SlateGUI cannot be created before the QVApplication instance. Aborting now.";
        std::cerr << qPrintable(str) << std::endl;
        exit(1);
        }

    // if its a --help call, do nothing
    if (qvApp->forHelp()) return;

    connect(&slate, SIGNAL(closed()), this, SLOT(quit()));

    qvApp->registerGUI(this);
    qvApp->setTerminateOnLastBlock(false); // para que no termine cuando se resetea el escenario (y se quitan todos los blocks temporalmente)

/*	// se conecta al informador estatico de la clase para obtener señales cuando se crea y se destruye un property container
    QVPropertyContainerInformer *inf = QVPropertyContainer::getGlobalInformer();
    connect(inf, SIGNAL(changed(QVPropertyContainerChange)), this, SLOT(processChange(QVPropertyContainerChange)));*/

    qDebug() << "QVDesignerGUI::QVDesignerGUI() <~ return";
}

void QVDesignerGUI::init()
{
    // registra y pinta los property containers
    foreach(QVPropertyContainer* qvp, qvApp->getQVPropertyContainers()) {
        // registro su tipo
        QVProcessingBlock* block;
        if((block = dynamic_cast<QVProcessingBlock*>(qvp)) != NULL) {
            QString registered = factory.registerUserBlock(block);
            if (!registered.isEmpty())
                slate.includeItemType(registered);
        }

        // registra y pinta el property container
        QString type = factory.containerType(qvp);
        QString name = qvp->getName();
        uint id = qvp->getId();
        // no se incluye en "containers", ya que no se pueden borrar desde aqui, ya que se crearon en el main y no con new. Se registra en "initialContainers"
        initialContainers.insert(id, qvp);
        createdItems.insert(id, CreatedItem(type, name, id));
        // se conecta al informador de ese container para obtener señales de sus cambios.
        connect(qvp->getInformer(), SIGNAL(changed(QVPropertyContainerChange)), this, SLOT(processChange(QVPropertyContainerChange)));
        slate.addItemNode(type, name, id, new ItemProperties(type, qvp));
        // creo su dialogo
        createDialog(id);
    }

    // una vez he registrado todos los property containers, registro y pinto los links de salida de cada uno (asi los pinto todos sin repetir)
    foreach(QVPropertyContainer* qvp, qvApp->getQVPropertyContainers()) {
        foreach(QString prop, qvp->getPropertyList()) {
            QVPropertyContainer *source = qvp->getSourceContainer(prop);
            QString sourceProp = qvp->getSourceProperty(prop);
            bool sync = qvp->isSynchronous(prop);
            bool sequ = qvp->isSequential(prop);

            if ( (source != NULL) && (!sourceProp.isEmpty()) ) {
                QString fromId = QString("%1").arg(source->getId());
                QString fromProp = sourceProp;
                QString toId = QString("%1").arg(qvp->getId());
                QString toProp = prop;
                QString linkName = getLinkName(fromId, fromProp, toId, toProp);
                createdLinks.insert(linkName, CreatedLink(source->getId(), fromProp, qvp->getId(), toProp, sync, sequ));
                slate.addLinkLine(source->getId(), fromProp, qvp->getId(), toProp, sync, sequ);
// 				informer.inform(QString("Link añadido: ") + getLinkName(fromName, fromProp, toName, toProp));
            }
        }
    }

    // por último se pide a la vista, ahora que estan todos los nodos y links, que reordene los mismos
    slate.arrangeItems();
}

void QVDesignerGUI::show()
{
    slate.show();
}

QMap<QString, QList<QString> > QVDesignerGUI::getItemTypes() const
{
    return factory.getItemTypes();
}

QMap<QString, QList<QString> > QVDesignerGUI::getInputItemTypes() const
{
    return factory.getInputItemTypes();
}

QMap<QString, QList<QString> > QVDesignerGUI::getMiddleItemTypes() const
{
    return factory.getMiddleItemTypes();
}

QMap<QString, QList<QString> > QVDesignerGUI::getOutputItemTypes() const
{
    return factory.getOutputItemTypes();
}

uint QVDesignerGUI::addItem(QString type, QString name, uint lastId)
{
    //std::cout << "Creo " + name.toStdString() + "\n";
    QVPropertyContainer *cont = factory.createContainer(type, name);
    if (cont != 0) {
        containers.insert(cont->getId(), cont);
        createdItems.insert(cont->getId(), CreatedItem(type, name, cont->getId()));
        // se conecta al informador de ese container para obtener señales de sus cambios.
        connect(cont->getInformer(), SIGNAL(changed(QVPropertyContainerChange)), this, SLOT(processChange(QVPropertyContainerChange)));

        slate.addItemNode(type, name, cont->getId(), new ItemProperties(type, cont), lastId);
        return cont->getId();
    }
    return 0;
}

bool QVDesignerGUI::setName(const uint id, const QString name)
{
    if (containers.contains(id))
        containers.value(id)->setName(name);
    else if (initialContainers.contains(id))
        initialContainers.value(id)->setName(name);
    else
        return FALSE;

    return TRUE;
}

bool QVDesignerGUI::addLink(uint fromId, QString fromProp, uint toId, QString toProp, bool synchronous, bool sequential)
{
    ///@todo homogeneizar un poco las llamadas a link de los distintops tipos de elementos
    if (containers.contains(fromId) && containers.contains(toId)) {
        QVPropertyContainer *fromCont = containers.value(fromId);
        QVPropertyContainer *toCont = containers.value(toId);

        QVVideoReaderBlock *cameraBlock;
        QVPropertyContainer::LinkType linkType = QVProcessingBlock::AsynchronousLink;
        if (synchronous) linkType = QVProcessingBlock::SynchronousLink;
        if (sequential) linkType = QVProcessingBlock::SequentialLink;


        /// @todo revisar si esto se puede eliminar sin problemas.
        /*if((dynamic_cast<QVMPlayerCamera*>(fromCont)) != NULL)
            fromCont->linkProperty(toCont, toProp, linkType);

        else*/ if((cameraBlock = dynamic_cast<QVVideoReaderBlock*>(fromCont)) != NULL)
            cameraBlock->linkProperty(toCont, toProp);

        else if((dynamic_cast<QVImageCanvas*>(toCont)) != NULL)
            fromCont->linkProperty(fromProp, toCont, linkType);

        else if((dynamic_cast<QVPlot*>(toCont)) != NULL)
            fromCont->linkProperty(fromProp, toCont, linkType);

        else if(!fromCont->containsProperty(fromProp))
            fromCont->linkProperty(toCont, toProp, linkType);

        else if(!toCont->containsProperty(toProp))
            fromCont->linkProperty(fromProp, toCont, linkType);

        else
            fromCont->linkProperty(fromProp, toCont, toProp, linkType);
    }
    else
        return FALSE;

    return TRUE;
}

bool QVDesignerGUI::delItem(const uint id)
{
    if (containers.contains(id)) {
        // borramos el propertyContainer asociado
        factory.deleteContainer(containers.value(id));
        return true;
    }
    return false;
}

bool QVDesignerGUI::delLink(const uint fromId, const QString fromProp, const uint toId, const QString toProp)
{
    if (containers.contains(fromId) && containers.contains(toId))
        return containers.value(fromId)->unlinkProperty(fromProp, containers.value(toId), toProp);
    else
        return false;
}

template <class Type> bool QVDesignerGUI::setProperty(const uint fromId, const QString fromProp, const Type &value)
{
    return false;
}

QString QVDesignerGUI::getLinkName(QVPropertyContainerChange change)
{
    return getLinkName(QString("%1").arg(change.getOrigId()), change.getOrigProp(), QString("%1").arg(change.getDestId()), change.getDestProp());
}

QString QVDesignerGUI::getLinkName(QString fromIdName, QString fromProp, QString toIdName, QString toProp)
{
    return getAbsPropName(fromIdName, fromProp) + " => " + getAbsPropName(toIdName, toProp);
}

QString QVDesignerGUI::getAbsPropName(QString fromIdName, QString fromProp)
{
    return fromIdName + "[" + fromProp + "]";
}


void QVDesignerGUI::processChange(QVPropertyContainerChange change)
{
    switch (change.getChangeType())
    {
    case QVPropertyContainerChange::Name:
        {
            uint id = change.getSourceId();
            QString name = change.getSourceName();
            if (createdItems.contains(id)) {
                //std::cout << change.toString().toStdString() << std::endl;
                slate.setItemName(id, name);
                if (createdItems.contains(id)) createdItems[id].name = name;
            }
        }
        break;

    case QVPropertyContainerChange::ContainerDel:
        {
            uint id = change.getSourceId();
            containers.remove(id);
            createdItems.remove(id);
            slate.delItemNode(id);

            // si se ha creado su dialogo, tambien lo borramos
            deleteDialog(id);

            //std::cout << change.toString().toStdString() << std::endl;
        }
        break;

    case QVPropertyContainerChange::PropertyAdd:
        if (createdItems.contains(change.getSourceId()))
        {
            uint srcId = change.getSourceId();
            QString propName = change.getPropName();

            if (containers.contains(srcId))
            {
                QVPropertyContainer *cont = containers.value(srcId);
                int type = cont->getPropertyType(propName);
                bool in = cont->isInput(propName);
                bool out = cont->isOutput(propName);
                slate.addProperty(srcId, propName, type, in, out);
            }
            //std::cout << change.toString().toStdString() << std::endl;
        }
        break;

    case QVPropertyContainerChange::PropertyDel:
        if (createdItems.contains(change.getSourceId()))
        {
            uint srcId = change.getSourceId();
            QString propName = change.getPropName();
            slate.delProperty(srcId, propName);
            //std::cout << change.toString().toStdString() << std::endl;
        }
        break;

    case QVPropertyContainerChange::PropertyValue:
        break;

    case QVPropertyContainerChange::LinkAdd:
        {
            uint fromId = change.getOrigId();
            QString fromProp = change.getOrigProp();
            uint toId = change.getDestId();
            QString toProp = change.getDestProp();
            QString linkName = getLinkName(change);
            if ( createdItems.contains(fromId) && createdItems.contains(toId) )
            {
                createdLinks.insert(linkName, CreatedLink(fromId, fromProp, toId, toProp, change.isSinc(), change.isSequ()));
                slate.addLinkLine(fromId, fromProp, toId, toProp, change.isSinc(), change.isSequ());
// 				informer.inform(QString("Link creado: ") + linkName);
            }
// 			else
// 				informer.inform(QString("Se ha creado un link no registrado: ") + linkName);
        }
        break;

    case QVPropertyContainerChange::LinkDel:
        {
            uint fromId = change.getOrigId();
            QString fromProp = change.getOrigProp();
            uint toId = change.getDestId();
            QString toProp = change.getDestProp();
            QString linkName = getLinkName(change);
            if (createdLinks.contains(linkName))
            {
                createdLinks.remove(linkName);
                slate.delLinkLine(fromId, fromProp, toId, toProp);
                //std::cout << change.toString().toStdString() << std::endl;
            }
        }
        break;

    case QVPropertyContainerChange::All:
        //std::cout << change.toString().toStdString() << std::endl;
        break;

    default:
        break;
    }
}

// esto se hace para que se almacenen los cambios antes de darle a run y que se hagan los read y writes
void QVDesignerGUI::dialogChange(QVPropertyContainerChange change)
{
    switch (change.getChangeType())
    {
        case QVPropertyContainerChange::PropertyValue:
        {
            uint dialogId = change.getSourceId();
            if (dialogsToContainers.contains(dialogId))
            {
                uint contId = dialogsToContainers.value(dialogId);
                QString prop = change.getPropName();
                propertyChanges.insert(getAbsPropName(QString("%1").arg(contId), prop), PropertyChange(contId, prop, change.getValue()));
            }
            break;
        }

        default:
            break;
    }
}

void QVDesignerGUI::showProperties(const uint id)
{
    if (containers.contains(id)) {
        if (dialogs.contains(id)) {
            (dialogs.value(id))->show();
        }
        else {
            if (createDialog(id))
                (dialogs.value(id))->show();
        }
    }
    else if (initialContainers.contains(id)) {
        if (dialogs.contains(id)) {
            (dialogs.value(id))->show();
        }
        else {
            if (createDialog(id))
            (dialogs.value(id))->show();
        }
    }
}

bool QVDesignerGUI::createDialog(const uint itemId)
{
    QVPropertyContainer *cont;
    if (containers.contains(itemId))
        cont = containers.value(itemId);
    else if (initialContainers.contains(itemId))
        cont = initialContainers.value(itemId);
    else
        return false;

    QVVideoReaderBlock *cameraBlock;
    QVProcessingBlock* block;
    //QVMPlayerCamera* camera;
    QVImageCanvas* imageCanvas;
    if((cameraBlock = dynamic_cast<QVVideoReaderBlock*>(cont)) != NULL) {
        CameraBlockDialog *dialog = new CameraBlockDialog(cameraBlock);
        dialogs.insert(itemId, dialog);
        dialogsToContainers.insert(dialog->getNodeId(), itemId);
        connect(dialog->getInformer(), SIGNAL(changed(QVPropertyContainerChange)), this, SLOT(dialogChange(QVPropertyContainerChange)));
        return true;
    }
    else if((block = dynamic_cast<QVProcessingBlock*>(cont)) != NULL) {
        BlockDialog *dialog = new BlockDialog(block);
        dialogs.insert(itemId, dialog);
        dialogsToContainers.insert(dialog->getNodeId(), itemId);
        connect(dialog->getInformer(), SIGNAL(changed(QVPropertyContainerChange)), this, SLOT(dialogChange(QVPropertyContainerChange)));
        return true;
    }
    /// @todo revisar si esto se puede eliminar sin problemas.
    /*else if((camera = dynamic_cast<QVMPlayerCamera*>(cont)) != NULL) {
        CameraDialog * dialog = new CameraDialog(camera);
        dialogs.insert(itemId, dialog);
        dialogsToContainers.insert(dialog->getNodeId(), itemId);
        connect(dialog->getInformer(), SIGNAL(changed(QVPropertyContainerChange)), this, SLOT(dialogChange(QVPropertyContainerChange)));
        return true;
    }*/
    else if((imageCanvas = dynamic_cast<QVImageCanvas*>(cont)) != NULL) {
        ImageCanvasDialog * dialog = new ImageCanvasDialog(imageCanvas);
        dialogs.insert(itemId, dialog);
        dialogsToContainers.insert(dialog->getNodeId(), itemId);
        connect(dialog->getInformer(), SIGNAL(changed(QVPropertyContainerChange)), this, SLOT(dialogChange(QVPropertyContainerChange)));
        return true;
    }
    return false;
}

void QVDesignerGUI::deleteDialog(const uint itemId)
{
    // si se ha creado su dialogo, tambien lo borramos (puede no haberse creado si no se ha dado a run)
    if (dialogs.contains(itemId)) {
        delete dialogs.value(itemId);
        dialogs.remove(itemId);
    }
}

void QVDesignerGUI::run()
{
    // creamos los dialogos que no se han creado aun, ya que después no se puede (porque no se puede lincar)
    foreach (uint id, containers.keys()) {
        if (!dialogs.contains(id))
            createDialog(id);
    }

    // y arrancamos la simulación
    qvApp->startItems();
}

void QVDesignerGUI::stop()
{
    // guardando la descripción de lo que tenía creado
    QList<CreatedItem> lastItems = createdItems.values();
    QList<CreatedLink> lastLinks = createdLinks.values();
    QMap<uint, uint> oldId_To_NewId;
    QList<GroupInfo> lastGroups =  slate.getGroups();

    // detenemos la simulación (lo que desregistra los elementos del qvApp y deslinca los items)
    qvApp->quitItems();

    // procesa todos los dellLink emitidos al parar los elementos desde el qvapp (para que no se solapen con su recontrucción)
    qApp->processEvents();

    // oculto los objetos creados desde el main y borro sus dialogos, que se crean al arrancar
    foreach (QVPropertyContainer * cont, initialContainers) {
        uint id = cont->getId();
        slate.delItemNode(id);
        deleteDialog(id);
        createdItems.remove(id);
    }
    initialContainers.clear(); // solo hay que ocultar los elementos de entrada una vez (ya que esos objetos no se pueden eliminar desde este contexto)

    // borro los grupos creados
    slate.eraseGroups();

    // borro los objetos creados
    foreach (QVPropertyContainer * cont, containers) {
        factory.deleteContainer(cont);
    }
    dialogsToContainers.clear();
    createdLinks.clear();

    // creo otros iguales (registrandose en la lista "containers")
    foreach (CreatedItem item, lastItems) {
        uint newId = addItem(item.type, item.name, item.id);
        oldId_To_NewId.insert(item.id, newId);
        if (newId == 0) std::cerr << "QVDesignerGUI - resetItems(): error al crear el Item " + item.name.toStdString() + "\n";
    }

    // creo links iguales a los que teniamos para los nuevos items (teniendo en cuenta el cambio de id que sufren)
    foreach (CreatedLink link, lastLinks) {
        if (oldId_To_NewId.contains(link.fromId) && (oldId_To_NewId.value(link.fromId) > 0) &&
            oldId_To_NewId.contains(link.toId)   && (oldId_To_NewId.value(link.toId) > 0) ) {
            if (!addLink(oldId_To_NewId.value(link.fromId), link.fromProp, oldId_To_NewId.value(link.toId), link.toProp, link.synchronous, link.sequential))
                std::cerr << "QVDesignerGUI - resetItems(): error al crear el Link " + QString("%1").arg(link.fromId).toStdString() + " -> " + QString("%1").arg(link.toId).toStdString() + "\n";
        }
    }

    // restauro los valores cambiados por el usuario
    for (QMap<QString, PropertyChange>::iterator it = propertyChanges.begin(); it != propertyChanges.end(); it++) { // uso un iterador para poder modificar
        if ( oldId_To_NewId.contains(it.value().id) && (oldId_To_NewId.value(it.value().id) > 0) ) {
            it.value().id = oldId_To_NewId.value(it.value().id);  // uso en id del nuevo item (que sustituye al anterior)
            QVPropertyContainer *cont = containers.value(it.value().id);
            QString prop = it.value().propName;
            QVariant value = it.value().value;

            if (cont->isType<int>(prop))
                cont->setPropertyValue<int>(prop, value.value<int>());
            else if (cont->isType<float>(prop))
                cont->setPropertyValue<float>(prop, value.value<float>());
            else if (cont->isType<bool>(prop))
                cont->setPropertyValue<bool>(prop, value.value<bool>());
            else if (cont->isType<double>(prop))
                cont->setPropertyValue<double>(prop, value.value<double>());
            else if (cont->isType<QString>(prop))
                cont->setPropertyValue<QString>(prop, value.value<QString>());
            else if (cont->isType<QVIndexedStringList>(prop))
                cont->setPropertyValue<QVIndexedStringList>(prop, value.value<QVIndexedStringList>());
            else
                std::cerr << "QVDesignerGUI - resetItems(): error al restaurar valor: " + getAbsPropName(QString("%1").arg(it.value().id), it.value().propName).toStdString() + "\n";
        }
        else
            std::cerr << "QVDesignerGUI - resetItems(): error al restaurar valor: " + getAbsPropName(QString("%1").arg(it.value().id), it.value().propName).toStdString() + "\n";
    }

    ///// creo grupos como los que teniamos en un principio
    createGroups(lastGroups, oldId_To_NewId);
}

void QVDesignerGUI::createGroups(QList<GroupInfo> &lastGroups, QMap<uint, uint> &oldId_To_NewId) {
    // primero actualizo los Ids relativos a los nodos de todos los subgrupos, ya que han cambiado
//std::cout << QString("lastGroups contiene:\n").toStdString();
    for (QList<GroupInfo>::iterator it = lastGroups.begin(); it != lastGroups.end(); it++) {
//std::cout << QString("     %1\n").arg((*it).getId()).toStdString();
        //std::cout << "para el info " << QString((*it).getName()).toStdString() << " hago los siguientes cambios de ID:\n";
        foreach (uint oldId, (*it).getNodes()) {
//std::cout << QString("         que cnontiene a %1\n").arg(oldId).toStdString();
            //std::cout << QString("     cambio oldId = %1...").arg(oldId).toStdString();
            if (oldId_To_NewId.contains(oldId)) {
                (*it).updateNodeId(oldId, oldId_To_NewId.value(oldId));
                //std::cout << QString(" a newId = %1").arg(oldId_To_NewId.value(oldId)).toStdString();
            }
            //std::cout << "\n";
        }
    }
    // Voy creando los nuevos grupos por pasadas (para que cree primero los subgrupos), y a la misma vez se van actualizando los IDs de los subgrupos de los restantes
    bool reloop = true;
    while (reloop) { // bucle por pasadas, intenta crear los grupos restantes, hasta que en una pasada no se cree ninguno
        //std::cout << "Una pasada: \n";
        QMap<uint, uint> changes;
        QList<GroupInfo>::iterator it = lastGroups.begin();
        while (it != lastGroups.end()) { // intento crear los grupos y guardo el cambio de ID
            uint oldId = (*it).getId();
//std::cout << QString("intento crear el grupo %1... ").arg(oldId).toStdString();
            uint newId = slate.createGroup(*it);
//std::cout << QString("como %1\n").arg(newId).toStdString();
            //std::cout << QString("Encuentro un info, oldId = %1, newId = %2...").arg(oldId).arg(newId).toStdString();
            if (newId > 0) {
                changes.insert(oldId, newId);
                it = lastGroups.erase(it);// borro el elemento cambiado de la lista (lo que avanza la lista), ya se ha creado su grupo
                //std::cout << " por lo que inserto un cambio";
            }
            else it++;
            //std::cout << "\n";
        }
        foreach (uint idChanged, changes.keys()) { // actualizo los cambios en el resto
            for (QList<GroupInfo>::iterator it = lastGroups.begin(); it != lastGroups.end(); it++)
                foreach (uint oldId, (*it).getSubgroups())
                    if (oldId == idChanged)
                        (*it).updateSubgroupId(idChanged, changes.value(idChanged));
        }
        reloop = !changes.isEmpty();
    }
}

void QVDesignerGUI::quit()
{
    qvApp->deregisterGUI();
    qvApp->quit();
}









/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////  Input/output functions
///////


QString QVDesignerGUI::getCppText() const
{
    QString result;

    // incluye una cabezera inicial con el copyright de la librería QVision
    result += "/*\n *	Copyright (C) 2007, 2008, 2009, 2010, 2011, 2012. PARP Research Group.\n *	<http://perception.inf.um.es>\n *	University of Murcia, Spain.\n *\n *	This file is part of the QVision library.\n *\n *	QVision is free software: you can redistribute it and/or modify\n *	it under the terms of the GNU Lesser General Public License as\n *	published by the Free Software Foundation, version 3 of the License.\n *\n *	QVision is distributed in the hope that it will be useful,\n *	but WITHOUT ANY WARRANTY; without even the implied warranty of\n *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n *	GNU Lesser General Public License for more details.\n *\n *	You should have received a copy of the GNU Lesser General Public\n *	License along with QVision. If not, see <http://www.gnu.org/licenses/>.\n */\n\n";

    // genera la lista de includes, si alguno de los elementos ha sido definido por el usuario, lo declara para que el usuario lo referencie
    result += "#include <QVApplication>\n#include <QVDefaultGUI>\n";
    QList<QString> types;
    foreach(CreatedItem item, createdItems.values()) {
        QString chopType = item.type;
        int espInd = chopType.indexOf(' ');
        int lesInd = chopType.indexOf('<');
        if ((espInd > 0) && (espInd < lesInd))
            types.append(chopType.left(espInd));
        else
            types.append(chopType.left(lesInd));
    }
    QSet<QString> unrepeatedTypes = types.toSet();
    foreach(QString unrepType, unrepeatedTypes) {
        if (factory.isUserType(unrepType))
            result += QString("class ") + unrepType + QString(";\n");
        else
            result += QString("#include <") + unrepType + QString(">\n");
    }
    // si en alguno de los items se ha modificado una propiedad QVIndexedStringList, se añade su include
    bool QVISLadded = FALSE;
    foreach(CreatedItem item, createdItems.values()) {
        foreach(PropertyChange change, propertyChanges.values()) {
            if ( (change.id == item.id) && (containers.value(item.id)->isType<QVIndexedStringList>(change.propName)) ) {
                result += QString("#include <QVIndexedStringList>\n");
                QVISLadded = TRUE;
                break;
            }
        }
        if (QVISLadded) break;
    }

    // comienza el método main
    result += "\n#ifndef DOXYGEN_IGNORE_THIS\n\n";
    result += "int main(int argc, char *argv[])\n	{\n	QVApplication app(argc, argv, \"Example program for QVision library.\");\n\n";

    // contruye los objetos usados
    foreach(CreatedItem item, createdItems.values()) {
        result += QString("	") + item.type + QString(" ") + item.name + QString("(\"") + item.name + QString("\");\n");
    }
    result += "\n	QVDefaultGUI interface;\n\n";

    // realiza los links
    foreach(CreatedLink link, createdLinks.values()) {
        if (containers.contains(link.fromId) && containers.contains(link.toId)) {
            QVPropertyContainer *fromCont = containers.value(link.fromId);
            QVPropertyContainer *toCont = containers.value(link.toId);

            //QVMPlayerCamera* camera;
            QVProcessingBlock* block;
            QVProcessingBlock* block2;
            QVImageCanvas* canvas;
            QVPlot* plot;

            /// @todo revisar si esto se puede eliminar sin problemas.
            /*if((camera = dynamic_cast<QVMPlayerCamera*>(fromCont)) != NULL) {
                if((block = dynamic_cast<QVProcessingBlock*>(toCont)) != NULL) {
                    result += QString("	") + fromCont->getName() + QString(".link(&") + toCont->getName() + QString(", \"") + link.toProp + QString("\");\n");
                }
            }
            else*/ if((block = dynamic_cast<QVProcessingBlock*>(fromCont)) != NULL) {
                if((block2 = dynamic_cast<QVProcessingBlock*>(toCont)) != NULL) {
                    result += QString("	") + fromCont->getName() + QString(".linkProperty(\"") + link.fromProp + QString("\", &");
                    result += toCont->getName() + QString(", \"") + link.toProp;
                    if (link.synchronous)
                        result += QString("\", QVProcessingBlock::SynchronousLink);\n");
                    else
                        result += QString("\", QVProcessingBlock::AsynchronousLink);\n");
                }
                else if((canvas = dynamic_cast<QVImageCanvas*>(toCont)) != NULL) {
                    result += QString("	") + toCont->getName() + QString(".linkProperty(") + fromCont->getName() + QString(", \"") + link.fromProp + QString("\");\n");
                }
                else if((plot = dynamic_cast<QVPlot*>(toCont)) != NULL) {
                    result += QString("	") + toCont->getName() + QString(".linkProperty(") + fromCont->getName() + QString(", \"") + link.fromProp + QString("\");\n");
                }
            }
        }
    }

    // establece los valores actuales de las propiedades
    result += "\n";
    foreach(CreatedItem item, createdItems.values()) {
        foreach(PropertyChange change, propertyChanges.values()) {
            if (change.id == item.id) {
                QVPropertyContainer *cont = containers.value(item.id);
                QString prop = change.propName;
                QVariant value = change.value;

                if (cont->isType<int>(prop))
                    result += QString("	") + item.name + ".setPropertyValue<int>(\"" + prop + "\", " + value.toString() + ");\n";
                else if (cont->isType<bool>(prop))
                    result += QString("	") + item.name + ".setPropertyValue<bool>(\"" + prop + "\", " + value.toString() + ");\n";
                else if (cont->isType<double>(prop))
                    result += QString("	") + item.name + ".setPropertyValue<double>(\"" + prop + "\", " + value.toString() + ");\n";
                else if (cont->isType<QString>(prop))
                    result += QString("	") + item.name + ".setPropertyValue<QString>(\"" + prop + "\", " + value.toString() + ");\n";
                else if (cont->isType<QVIndexedStringList>(prop)) {
                    QVIndexedStringList indlist = value.value<QVIndexedStringList>();
                    result += QString("	QVIndexedStringList ") + "QVISLfor_" + item.name + ";\n";
                    foreach (QString option, indlist) {
                        result += QString("	QVISLfor_") + item.name + ".append(\"" + option + "\");\n";
                    }
                    result += QString("	QVISLfor_") + item.name + QString(".setIndex(%1);\n").arg(indlist.getIndex());
                    result += QString("	") + item.name + ".setPropertyValue<QVIndexedStringList>(\"" + prop + "\", QVISLfor_" + item.name + ");\n";
                }
            }
        }
    }

    // finaliza el fichero
    result += "\n	return app.exec();\n	}\n\n#endif\n\n";
    return result;
}

QString QVDesignerGUI::getXMLText()
{
    QString text;
    QXmlStreamWriter xmlWriter(&text);
    xmlWriter.setAutoFormatting(true);
    uint xmlId = 1;
    QMap<uint, uint> ItemId_To_xmlId;

    xmlWriter.writeStartDocument("1.0");
    xmlWriter.writeStartElement("QVApplication");

    // añade las características de los items
    xmlWriter.writeStartElement("Nodes");
    foreach(CreatedItem item, createdItems.values()) {
        xmlWriter.writeStartElement("Node");
        xmlWriter.writeAttribute("Type", item.type);
        xmlWriter.writeAttribute("Id", QString("%1").arg(xmlId));
        ItemId_To_xmlId.insert(item.id, xmlId++);
        xmlWriter.writeAttribute("Name", item.name);
        QPointF pos = slate.getNodePos(item.id);
        xmlWriter.writeAttribute("X", QString("%1").arg(pos.x()));
        xmlWriter.writeAttribute("Y", QString("%1").arg(pos.y()));

        // añade las características de los cambios en las  propiedades de cada item
        foreach(PropertyChange change, propertyChanges.values()) {
            if (change.id == item.id) {
                QString strValue = change.value.toString();
                if (!strValue.isEmpty()) {
                    xmlWriter.writeStartElement("Property");
                    xmlWriter.writeAttribute("Name", change.propName);
                    xmlWriter.writeAttribute("Value", strValue);
                    xmlWriter.writeEndElement();
                }
            }
        }
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();

    // añade las características de los links
    xmlWriter.writeStartElement("Links");
    foreach (CreatedLink link, createdLinks.values()) {
        if ( (containers.contains(link.fromId) && containers.contains(link.toId)) ||
              (initialContainers.contains(link.fromId) && initialContainers.contains(link.toId)) ) { // igual tendría que no registrar a los paramInspector al init
            if (link.synchronous)		xmlWriter.writeStartElement("SynchronousLink");
            else if (link.sequential)	xmlWriter.writeStartElement("SequentialLink");
            else						xmlWriter.writeStartElement("AsynchronousLink");
            xmlWriter.writeAttribute("FromId", QString("%1").arg(ItemId_To_xmlId.value(link.fromId)));
            xmlWriter.writeAttribute("FromProp", link.fromProp);
            xmlWriter.writeAttribute("ToId", QString("%1").arg(ItemId_To_xmlId.value(link.toId)));
            xmlWriter.writeAttribute("ToProp", link.toProp);
            xmlWriter.writeEndElement();
        }
    }
    xmlWriter.writeEndElement();

    // añade las características de los grupos credos en la pizarra
    xmlWriter.writeStartElement("Groups");
    QList<GroupInfo> groupList = slate.getGroups();
    foreach (GroupInfo group, groupList) {
        xmlWriter.writeStartElement("Group");
        xmlWriter.writeAttribute("Id", QString("%1").arg(group.getId()));
        xmlWriter.writeAttribute("Name", group.getName());
        QPointF pos =group.getPos();
        xmlWriter.writeAttribute("X", QString("%1").arg(pos.x()));
        xmlWriter.writeAttribute("Y", QString("%1").arg(pos.y()));
        foreach (uint nodeId, group.getNodes()) {
            xmlWriter.writeStartElement("ChildNode");
            xmlWriter.writeAttribute("Id", QString("%1").arg(ItemId_To_xmlId.value(nodeId)));
            xmlWriter.writeEndElement();
        }
        foreach (uint subId, group.getSubgroups()) {
            xmlWriter.writeStartElement("ChildGroup");
            xmlWriter.writeAttribute("Id", QString("%1").arg(subId));
            xmlWriter.writeEndElement();
        }
        foreach (LinkInfo link, group.getNodeLinks()) {
            xmlWriter.writeStartElement("VisibleNodeLink");
            xmlWriter.writeAttribute("ChildNode", QString("%1").arg(ItemId_To_xmlId.value(link.getNode())));
            xmlWriter.writeAttribute("Prop", link.getProp());
            xmlWriter.writeAttribute("Direction", link.getInput() ? "Input" : "Output");
            xmlWriter.writeEndElement();
        }
        foreach (LinkInfo link, group.getSubgroupLinks()) {
            xmlWriter.writeStartElement("VisibleGroupLink");
            xmlWriter.writeAttribute("ChildGroup", QString("%1").arg(link.getNode()));
            xmlWriter.writeAttribute("Prop", link.getProp());
            xmlWriter.writeAttribute("Direction", link.getInput() ? "Input" : "Output");
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    return text;
}

bool QVDesignerGUI::loadXML(QString text)
{
    // borra todo lo que hay
    slate.eraseGroups();
    createdLinks.clear();

    foreach (QVPropertyContainer * cont, containers) {
        factory.deleteContainer(cont);
    }

    propertyChanges.clear();
    dialogsToContainers.clear();




    // carga lo del fichero
    QXmlStreamReader xmlReader(text);

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "QVApplication")
                readXMLQVApplication(xmlReader);
            else
                readXMLUnknownElement(xmlReader);
        }
    }

    XMLId_To_ContainersId.clear(); // se resetea para la siguiente llamada

    if (xmlReader.hasError()) return false;

    return true;
}

bool QVDesignerGUI::readXMLQVApplication(QXmlStreamReader &xmlReader)
{
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "QVApplication");

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "Nodes")
                readXMLNodes(xmlReader);
            else if (xmlReader.name() == "Links")
                readXMLLinks(xmlReader);
            else if (xmlReader.name() == "Groups")
                readXMLGroups(xmlReader);
            else
                readXMLUnknownElement(xmlReader);
        }
     }

    return true;
}

bool QVDesignerGUI::readXMLNodes(QXmlStreamReader &xmlReader)
{
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "Nodes");

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "Node")
                readXMLNode(xmlReader);
            else
                readXMLUnknownElement(xmlReader);
        }
     }

    return true;
}

bool QVDesignerGUI::readXMLNode(QXmlStreamReader &xmlReader)
{
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "Node");

    QXmlStreamAttributes attributes = xmlReader.attributes();
    QString type = attributes.value("Type").toString();
    QString XMLid = attributes.value("Id").toString();
    QString name = attributes.value("Name").toString();
    QString x = attributes.value("X").toString();
    QString y = attributes.value("Y").toString();


    uint itemId = addItem(type, name);
// 	qApp->processEvents();
    XMLId_To_ContainersId.insert(XMLid.toInt(), itemId);
    slate.moveNode(itemId, QPointF(x.toFloat(), y.toFloat()));

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "Property")
                readXMLProperty(xmlReader, itemId);
            else
                readXMLUnknownElement(xmlReader);
        }
     }

    return true;
}

bool QVDesignerGUI::readXMLProperty(QXmlStreamReader &xmlReader, uint id)
{
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "Property");

    QXmlStreamAttributes attributes = xmlReader.attributes();
    QString name = attributes.value("Name").toString();
    QString value = attributes.value("Value").toString();

    if (containers.contains(id)) {
        QVPropertyContainer *cont = containers.value(id);

        if (cont->isType<int>(name)) {
            cont->setPropertyValue<int>(name, value.toInt());
            propertyChanges.insert(getAbsPropName(QString("%1").arg(id), name), PropertyChange(id, name, QVariant(value.toInt())));
        }
        if (cont->isType<float>(name)) {
            cont->setPropertyValue<float>(name, value.toFloat());
            propertyChanges.insert(getAbsPropName(QString("%1").arg(id), name), PropertyChange(id, name, QVariant(value.toFloat())));
        }
        else if (cont->isType<bool>(name)) {
            cont->setPropertyValue<bool>(name, (value == "true" ? true : false));
            propertyChanges.insert(getAbsPropName(QString("%1").arg(id), name), PropertyChange(id, name, QVariant((value == "true" ? true : false))));
        }
        else if (cont->isType<double>(name)) {
            cont->setPropertyValue<double>(name, value.toDouble());
            propertyChanges.insert(getAbsPropName(QString("%1").arg(id), name), PropertyChange(id, name, QVariant(value.toDouble())));
        }
        else if (cont->isType<QString>(name)) {
            cont->setPropertyValue<QString>(name, value);
            propertyChanges.insert(getAbsPropName(QString("%1").arg(id), name), PropertyChange(id, name, QVariant(value)));
        }
    }

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement()) {
            readXMLUnknownElement(xmlReader);
        }
     }

    return true;
}

bool QVDesignerGUI::readXMLLinks(QXmlStreamReader &xmlReader)
{
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "Links");

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "AsynchronousLink")
                readXMLAsynchronousLink(xmlReader);
            else if (xmlReader.name() == "SynchronousLink")
                readXMLSynchronousLink(xmlReader);
            else if (xmlReader.name() == "SequentialLink")
                readXMLSequentialLink(xmlReader);
            else
                readXMLUnknownElement(xmlReader);
        }
     }

    return true;
}

bool QVDesignerGUI::readXMLAsynchronousLink(QXmlStreamReader &xmlReader)
{
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "AsynchronousLink");

    QXmlStreamAttributes attributes = xmlReader.attributes();
    QString fromId = attributes.value("FromId").toString();
    QString fromProp = attributes.value("FromProp").toString();
    QString toId = attributes.value("ToId").toString();
    QString toProp = attributes.value("ToProp").toString();

    addLink(XMLId_To_ContainersId.value(fromId.toUInt()), fromProp, XMLId_To_ContainersId.value(toId.toUInt()), toProp, false, false);

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement()) {
            readXMLUnknownElement(xmlReader);
        }
     }

    return true;
}

bool QVDesignerGUI::readXMLSynchronousLink(QXmlStreamReader &xmlReader)
{
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "SynchronousLink");

    QXmlStreamAttributes attributes = xmlReader.attributes();
    QString fromId = attributes.value("FromId").toString();
    QString fromProp = attributes.value("FromProp").toString();
    QString toId = attributes.value("ToId").toString();
    QString toProp = attributes.value("ToProp").toString();

    addLink(XMLId_To_ContainersId.value(fromId.toUInt()), fromProp, XMLId_To_ContainersId.value(toId.toUInt()), toProp, true, false);

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement()) {
            readXMLUnknownElement(xmlReader);
        }
     }

    return true;
}

bool QVDesignerGUI::readXMLSequentialLink(QXmlStreamReader &xmlReader)
{
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "SequentialLink");

    QXmlStreamAttributes attributes = xmlReader.attributes();
    QString fromId = attributes.value("FromId").toString();
    QString fromProp = attributes.value("FromProp").toString();
    QString toId = attributes.value("ToId").toString();
    QString toProp = attributes.value("ToProp").toString();

    addLink(XMLId_To_ContainersId.value(fromId.toUInt()), fromProp, XMLId_To_ContainersId.value(toId.toUInt()), toProp, false, true);

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement()) {
            readXMLUnknownElement(xmlReader);
        }
     }

    return true;
}

bool QVDesignerGUI::readXMLGroups(QXmlStreamReader &xmlReader) {
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "Groups");

    QList<GroupInfo> groupInfos;

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "Group")
                readXMLGroup(xmlReader, groupInfos);
            else
                readXMLUnknownElement(xmlReader);
        }
     }

    createGroups(groupInfos, XMLId_To_ContainersId);

    return true;
}

bool QVDesignerGUI::readXMLGroup(QXmlStreamReader &xmlReader, QList<GroupInfo> &groupInfos) {
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "Group");

    QXmlStreamAttributes attributes = xmlReader.attributes();
    QString XMLid = attributes.value("Id").toString();
    QString name = attributes.value("Name").toString();
    QString x = attributes.value("X").toString();
    QString y = attributes.value("Y").toString();

    GroupInfo groupInfo(XMLid.toInt(), name);
    groupInfo.setPos(QPointF(x.toFloat(), y.toFloat()));
    groupInfo.setAbstract(false);

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "ChildNode")
                readXMLChildNode(xmlReader, groupInfo);
            else if (xmlReader.name() == "ChildGroup")
                readXMLChildGroup(xmlReader, groupInfo);
            else if (xmlReader.name() == "VisibleNodeLink")
                readXMLVisibleNodeLink(xmlReader, groupInfo);
            else if (xmlReader.name() == "VisibleGroupLink")
                readXMLVisibleGroupLink(xmlReader, groupInfo);
            else
                readXMLUnknownElement(xmlReader);
        }
     }

    groupInfos.append(groupInfo);

    return true;
}

bool QVDesignerGUI::readXMLChildNode(QXmlStreamReader &xmlReader, GroupInfo &groupInfo) {
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "ChildNode");

    QXmlStreamAttributes attributes = xmlReader.attributes();
    QString XMLid = attributes.value("Id").toString();

    groupInfo.addNode(XMLid.toInt());

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement()) {
            readXMLUnknownElement(xmlReader);
        }
     }

    return true;
}

bool QVDesignerGUI::readXMLChildGroup(QXmlStreamReader &xmlReader, GroupInfo &groupInfo) {
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "ChildGroup");

    QXmlStreamAttributes attributes = xmlReader.attributes();
    QString XMLid = attributes.value("Id").toString();

    groupInfo.addSubgroup(XMLid.toInt());

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement()) {
            readXMLUnknownElement(xmlReader);
        }
     }

    return true;
}

bool QVDesignerGUI::readXMLVisibleNodeLink(QXmlStreamReader &xmlReader, GroupInfo &groupInfo) {
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "VisibleNodeLink");

    QXmlStreamAttributes attributes = xmlReader.attributes();
    QString XMLid = attributes.value("ChildNode").toString();
    QString prop = attributes.value("Prop").toString();
    QString direction = attributes.value("Direction").toString();

    groupInfo.addNodeLink(LinkInfo(XMLid.toInt(), prop, direction == "Input" ? true : false));

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement()) {
            readXMLUnknownElement(xmlReader);
        }
     }

    return true;
}

bool QVDesignerGUI::readXMLVisibleGroupLink(QXmlStreamReader &xmlReader, GroupInfo &groupInfo) {
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "VisibleGroupLink");

    QXmlStreamAttributes attributes = xmlReader.attributes();
    QString XMLid = attributes.value("ChildGroup").toString();
    QString prop = attributes.value("Prop").toString();
    QString direction = attributes.value("Direction").toString();

    groupInfo.addSubgroupLink(LinkInfo(XMLid.toInt(), prop, direction == "Input" ? true : false));

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement()) {
            readXMLUnknownElement(xmlReader);
        }
     }

    return true;
}

bool QVDesignerGUI::readXMLUnknownElement(QXmlStreamReader &xmlReader)
{
    Q_ASSERT(xmlReader.isStartElement());

// std::cout << "Algo extaño\n";

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isEndElement())
            break;

        if (xmlReader.isStartElement())
            readXMLUnknownElement(xmlReader);
     }

    return true;
}

