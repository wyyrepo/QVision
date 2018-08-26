/*
 *	Copyright (C) 2007, 2008, 2009, 2010, 2011, 2012. PARP Research Group.
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

/// @file
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#include <QVDisjointSet>
#include <QVPropertyContainer>

uint QVPropertyContainer::maxIdent = 0;
// QVPropertyContainerInformer QVPropertyContainer::globalInformer;

QVPropertyContainer::QVPropertyContainer(const QString name):
    name(name), errorString(), variants(), safelyCopiedVariants(), minimum(),
    maximum(), _info(), io_flags(), link_flags(), insertion_order(),
    inputLinks(), outputLinks(), master(this), deepLevel(0)
    {
    ident = getNewIdent();
    qDebug() << "QVPropertyContainer::QVPropertyContainer(" << name << ")";
    if(qvApp == NULL)
        {
        QString str = "QVPropertyContainer::QVPropertyContainer(): holder " + name +
                      ": property holders cannot be created before the " +
                      "QVApplication instance. Aborting now.";
        std::cerr << qPrintable(str) << std::endl;
        exit(1);
        }
    else
        {
        qvApp->registerQVPropertyContainer(this);
// 		QVPropertyContainer::globalInformer.emitChange(QVPropertyContainerChange(this, QVPropertyContainerChange::ContainerAdd));
        }
    slavesByLevel.append(QList<QVPropertyContainer *>());
    slavesByLevel[0].append(this);
    qDebug() << "QVPropertyContainer::QVPropertyContainer(" << name << ") <- return";
    }

QVPropertyContainer::QVPropertyContainer(const QVPropertyContainer &cont):
    name(cont.name), ident(cont.ident), errorString(cont.errorString), variants(cont.variants),
    safelyCopiedVariants(cont.safelyCopiedVariants), minimum(cont.minimum), maximum(cont.maximum),
    _info(cont._info), io_flags(cont.io_flags), link_flags(cont.link_flags), insertion_order(cont.insertion_order),
    RWLock(), inputLinks(cont.inputLinks), outputLinks(cont.outputLinks), master(this), deepLevel(0)
    {
    qDebug() << "QVPropertyContainer::QVPropertyContainer(" << name << ")";
    if(qvApp == NULL)
        {
        QString str = "QVPropertyContainer::QVPropertyContainer(): holder " + name +
                      ": property holders cannot be created before the " +
                      "QVApplication instance. Aborting now.";
        std::cerr << qPrintable(str) << std::endl;
        exit(1);
        }
    else
        {
        qvApp->registerQVPropertyContainer(this);
// 		QVPropertyContainer::globalInformer.emitChange(QVPropertyContainerChange(this, QVPropertyContainerChange::ContainerAdd));
        }
    slavesByLevel.append(QList<QVPropertyContainer *>());
    slavesByLevel[0].append(this);
    qDebug() << "QVPropertyContainer::QVPropertyContainer(" << name << ") <- return";
    }

QVPropertyContainer & QVPropertyContainer::operator=(const QVPropertyContainer &cont)
    {
    name = cont.name;
    ident = cont.ident;
    errorString = cont.errorString;
    variants = cont.variants;
    safelyCopiedVariants = cont.safelyCopiedVariants;
    minimum = cont.minimum;
    maximum = cont.maximum;
    _info = cont._info;
    io_flags = cont.io_flags;
    link_flags = cont.link_flags;
    insertion_order = cont.insertion_order;
    inputLinks = cont.inputLinks;
    outputLinks = cont.outputLinks;
    master = this;
    deepLevel = 0;

    slavesByLevel.append(QList<QVPropertyContainer *>());
    slavesByLevel[0].append(this);
    informer.emitChange(QVPropertyContainerChange(this->getName(), this->getId(), QVPropertyContainerChange::All));
    return *this;
    }

QVPropertyContainer::~QVPropertyContainer()
    {
    if(qvApp != NULL)
        qvApp->deregisterQVPropertyContainer(this);

    unlink();
    readInputProperties();
    writeOutputProperties();
    informer.emitChange(QVPropertyContainerChange(this->getName(), this->getId(), QVPropertyContainerChange::ContainerDel));
    }

void QVPropertyContainer::setName(const QString name)
    { this->name = name; informer.emitChange(QVPropertyContainerChange(this->getName(), this->getId(), QVPropertyContainerChange::Name)); }

const QString QVPropertyContainer::getName() const
    { return this->name; }

uint QVPropertyContainer::getId() const
    { return this->ident; }

bool QVPropertyContainer::operator==(const QVPropertyContainer &cont) const
    { return (ident == cont.ident); }

QList<QString> QVPropertyContainer::getPropertyList() const
    { return variants.keys(); }

bool QVPropertyContainer::containsProperty(const QString name) const
    { return variants.contains(name); }

int QVPropertyContainer::getPropertyType(const QString name, bool *ok) const
    {
    if(not checkExists(name,"QVPropertyContainer::getPropertyType()"))
        {
        if(ok != NULL) *ok = FALSE;
        return QVariant::Invalid;
        }
    if(ok != NULL) *ok = TRUE;
    QVariant variant = variants.value(name);
    return variant.userType();
    }

bool QVPropertyContainer::removeProperty(const QString name)
    {
    if(not checkExists(name,"QVPropertyContainer::removeProperty()"))
        return FALSE;
    this->variants.remove(name);
    this->safelyCopiedVariants.remove(name);
    this->minimum.remove(name);
    this->maximum.remove(name);
    this->_info.remove(name);
    this->io_flags.remove(name);
    int i = this->insertion_order.indexOf(name);
    this->insertion_order.removeAt(i);
    informer.emitChange(QVPropertyContainerChange(this->getName(), this->getId(), QVPropertyContainerChange::PropertyDel, name));
    return TRUE;
    }
/*
bool QVPropertyContainer::setPropertyRange(const QString name, const double & minimum, const double & maximum)
    {
    std::cerr << "WARNING: setPropertyRange() is deprecated. Specify range in the function addProperty instead." << std::endl;
    if(not checkExists(name,"QVPropertyContainer::setPropertyRange()"))
        return FALSE;
    if(minimum <= getPropertyValue<double>(name) and
        maximum >= getPropertyValue<double>(name))
        {
            this->minimum[name] = QVariant::fromValue(minimum);
            this->maximum[name] = QVariant::fromValue(maximum);
            return TRUE;
        } else {
            QString str =  "QVPropertyContainer::setPropertyRange(): property " +
                           name + " in holder " + getName() + " has value " +
                           QString("%1").arg(getPropertyValue<double>(name)) +
                           ", which is not valid for the range [" +
                           QString("%1,%2").arg(minimum).arg(maximum) + "]." ;
            setLastError(str);
            if(qvApp->isRunning()) {
                std::cerr << qPrintable("Warning: " + str + "\n");
            } // Otherwise, qApp will show the error and won't start the program.
            return FALSE;
        }
    }

bool QVPropertyContainer::setPropertyRange(QString name, int & minimum, int & maximum)
    { return setPropertyRange(name, static_cast<double>(minimum), static_cast<double>(maximum)); }
*/
bool QVPropertyContainer::hasRange(const QString name) const
    { return maximum.contains(name) and minimum.contains(name); }

bool QVPropertyContainer::isInput(const QString name) const
    { return (io_flags[name] & inputFlag);};

bool QVPropertyContainer::isOutput(const QString name) const
    { return (io_flags[name] & outputFlag);};

bool QVPropertyContainer::isGUIInvisible(const QString name) const
    { return (io_flags[name] & guiInvisible);};

bool QVPropertyContainer::isLinkedInput(const QString name) const
    { return (link_flags[name] & linkedInputFlag);};

bool QVPropertyContainer::isLinkedOutput(const QString name) const
    { return (link_flags[name] & linkedOutputFlag);};

QVariant QVPropertyContainer::getPropertyQVariantValue(const QString name, bool *ok) const
    {
    if (not checkExists(name,"QVPropertyContainer::getPropertyQVariantValue()")) {
        if(ok != NULL) *ok = FALSE;
    } else {
        if(ok != NULL) *ok = TRUE;
    }
    return variants[name];
    }

QString QVPropertyContainer::getPropertyInfo(const QString name, bool *ok) const
    {
    if(not checkExists(name,"QVPropertyContainer::getPropertyInfo()")) {
        if(ok != NULL) *ok = FALSE;
    } else {
        if(ok != NULL) *ok = TRUE;
    }
    return this->_info[name];
    }

QString QVPropertyContainer::getLastError() const
    {
    return errorString;
    }

const QString QVPropertyContainer::infoInputProperties() const
    {
    qDebug() << "QVPropertyContainer::infoInputProperties(" << getName() << ")";

    QString info = QString("Input parameters for ") + getName() + QString(":\n");
    bool emptyInfo=TRUE;

    qDebug() << "QVPropertyContainer::infoInputProperties(): Properties " << insertion_order;

    foreach (QString property, insertion_order)
    //QListIterator<QString> i(insertion_order);
    //while (i.hasNext())
        {
        //const QString property = i.next();

        if( not isInput(property) )
            continue;

        bool printableProperty = TRUE;
        QString propertyInfo("  --" + property + "=");

        switch(getPropertyType(property))
            {
            case QVariant::String:
                propertyInfo += QString() + "[text] " + "(def. '" + getPropertyValue<QString>(property) + "') ";
                break;

            case QVariant::Double:
                propertyInfo += ( (maximum.contains(property) and minimum.contains(property))?
                    "[" + QString().setNum(getPropertyMinimum<double>(property)) + "..."
                        + QString().setNum(getPropertyMaximum<double>(property)) + "] ":
                    "[double] " ) + "(def. "+ QString().setNum(getPropertyValue<double>(property)) + ") ";
                break;

            case QVariant::Int:
                propertyInfo += ( (maximum.contains(property) and minimum.contains(property))?
                    "[" + QString().setNum(getPropertyMinimum<int>(property)) + "..." +
                        QString().setNum(getPropertyMaximum<int>(property)) + "] ":
                    "[int] " ) + "(def. "+ QString().setNum(getPropertyValue<int>(property)) + ") ";
                break;

            case QVariant::Bool:
                propertyInfo += "[true,false]" + (getPropertyValue<bool>(property) ?
                                QString(" (def. true) "):QString("(def. false) "));
                break;

            default:
                printableProperty = FALSE;
                break;
            }

        if (printableProperty)
            {
            info += propertyInfo + getPropertyInfo(property).rightJustified(100-propertyInfo.split('\n').last().length(),'.') + ".\n";
            emptyInfo=FALSE;
            }
        }

    qDebug() << "QVPropertyContainer::infoInputProperties(" << getName() << ") <~ return";

    if(emptyInfo)
        return QString("");

    return info;
    }

bool QVPropertyContainer::correctRange(const QString name, const double & value) const
    {
    if(not maximum.contains(name) and not minimum.contains(name))
        return TRUE;
    double maximum = getPropertyMaximum<double>(name);
    double minimum = getPropertyMinimum<double>(name);
    if(minimum <= value and maximum >= value)
        return TRUE;
    else
        {
        QString str =  "QVPropertyContainer::setPropertyValue(): value " +
                       QString("%1").arg(value) + " for property " +
                       name + " in holder " + getName() +
                       "is not valid for the specified range [" +
                       QString("%1,%2").arg(minimum).arg(maximum) +
                       "]" ;
        setLastError(str);
        if(qvApp->isRunning())
            {
            std::cerr << qPrintable("Warning: " + str + "\n");
            } // Otherwise, qApp will show the error and won't start the program.
        return FALSE;
        }
    }

bool QVPropertyContainer::correctRange(const char *name, const int & value) const
    { return correctRange(QString(name),static_cast<double>(value)); }

bool QVPropertyContainer::correctRange(QString name, const int & value) const
    { return correctRange(name,static_cast<double>(value)); }

bool QVPropertyContainer::checkExists(const QString name, const QString methodname) const
    {
    if(not variants.contains(name))
        {
        QString str =  methodname + ": property " + name +
                       " doesn't exists in holder " + getName() + ".";
        setLastError(str);
        if(qvApp->isRunning()) {
            std::cerr << qPrintable("Warning: " + str + "\n");
        } // Otherwise, qApp will show the error and won't start the program.
        return FALSE;
        } else {
        return TRUE;
        }
    }

bool QVPropertyContainer::checkIsNewProperty(const QString name, const QString methodname) const
    {
    if(variants.contains(name))
        {
        QString str =  methodname + "(): property " + name +
                       " already exists in holder " + getName() + ".";
        setLastError(str);
        if(qvApp->isRunning()) {
            std::cerr << qPrintable("Warning: " + str + "\n");
        } // Otherwise, qApp will show the error and won't start the program.
        return FALSE;
        } else {
        return TRUE;
        }
    }

///////////////////

bool QVPropertyContainer::linkProperty(QString prop_orig, QVPropertyContainer *qvp_dest, QString prop_dest, LinkType link_type)
    {
    bool ok1,ok2;
    QString errMsg;
    int t1,t2;
    QVPropertyContainer *qvp_err=NULL;

    t1 = this->getPropertyType(prop_orig,&ok1);
    t2 = qvp_dest->getPropertyType(prop_dest,&ok2);
    if(qvApp->isRunning())
        {
        qvp_err = this;
        errMsg = QString("QVPropertyContainer::linkProperty(): Property holder %1:"
                    "Cannot link properties after launching QVApplication.\n")
                    .arg(prop_orig).arg(this->getName());
        }
    else if(this == qvp_dest)
        {
        errMsg = QString("QVPropertyContainer::linkProperty(): Property holder %1: cannot link a QVPropertyContainer with itself.\n").arg(this->getName());
        qvp_err = this;
        }
    else if(not ok1)
        {
        errMsg = QString("QVPropertyContainer::linkProperty(): Property %1 does not exist in property holder %2.\n")
                .arg(prop_orig).arg(this->getName());
        qvp_err = this;
        }
    else if (not ok2)
        {
        errMsg = QString("QVPropertyContainer::linkProperty(): Property %1 does not exist in property holder %2.\n")
                .arg(prop_dest).arg(qvp_dest->getName());
        qvp_err = qvp_dest;
        }
    else if(t1 != t2)
        {
        errMsg = QString("QVPropertyContainer::linkProperty(): Properties %1 and %2 of QVPropertyContainers %3 and %4 respectively are not of the same type.\n").arg(prop_orig).arg(prop_dest).arg(this->getName()).arg(qvp_dest->getName());
        qvp_err = this;
        }
    else if(not (this->io_flags[prop_orig] & outputFlag))
        {
        errMsg = QString("QVPropertyContainer::linkProperty(): Property %1 of property holder %2 is not of Output type, and cannot be linked as such.\n").arg(prop_orig).arg(this->getName());
        qvp_err = this;
        }
    else if(not (qvp_dest->io_flags[prop_dest] & inputFlag))
        {
        errMsg = QString("QVPropertyContainer::linkProperty(): Property %1 property holder %2 is not of Input type, and cannot be linked as such.\n").arg(prop_dest).arg(qvp_dest->getName());
        qvp_err = qvp_dest;
        }
    else if( (link_type == SequentialLink) && (!ProcessPosibleSequentialLink(qvp_dest)) )
        {
        errMsg = QString("QVPropertyContainer::linkProperty(): A new link cannot generate a cycle of SequentialLinks.\n");
        qvp_err = this;
        }

    if(errMsg != QString())
        {
        qvp_err->setLastError(errMsg);
        if(qvApp->isRunning()) {
            std::cerr << qPrintable("Warning: " + errMsg + "\n");
        } // Otherwise, qApp will show the error and won't start the program.
        return FALSE;
        }
    else
        {
        QVPropertyContainerLink *link = new QVPropertyContainerLink(this,prop_orig,qvp_dest,prop_dest,link_type);
        this->outputLinks[prop_orig].push_back(link);
        this->link_flags[prop_orig] |= linkedOutputFlag;
        // We add a new method "addInputLink(prop_dest, link);" instead of doing
        // "qvp_dest->inputLinks[prop_dest] = link; qvp_dest->link_flags[prop_dest] |= linkedInputFlag;", for
        // qvp_dest to emit a signal saying that its links were changed.
        qvp_dest->addInputLink(prop_dest, link);

        // Now, we initialize the shared state, simply protected by the
        // corresponding RWLock:
        this->RWLock.lockForWrite();
        safelyCopiedVariants[prop_orig] = variants[prop_orig];
        this->RWLock.unlock();

        if (link_type == QVPropertyContainer::AsynchronousLink)
            informer.emitChange(QVPropertyContainerChange(this->getName(), this->getId(), QVPropertyContainerChange::LinkAdd, this->getName(), this->getId(), prop_orig, qvp_dest->getName(), qvp_dest->getId(), prop_dest,FALSE,FALSE));
        else if (link_type == QVPropertyContainer::SynchronousLink)
            informer.emitChange(QVPropertyContainerChange(this->getName(), this->getId(), QVPropertyContainerChange::LinkAdd, this->getName(), this->getId(), prop_orig, qvp_dest->getName(), qvp_dest->getId(), prop_dest,TRUE, FALSE));
        else
            informer.emitChange(QVPropertyContainerChange(this->getName(), this->getId(), QVPropertyContainerChange::LinkAdd, this->getName(), this->getId(), prop_orig, qvp_dest->getName(), qvp_dest->getId(), prop_dest,FALSE, TRUE));

        return TRUE;
        }
    }

bool QVPropertyContainer::linkProperty(QVPropertyContainer *destinyContainer, QString destinyPropertyName, LinkType linkType)
    {
    if (linkUnspecifiedOutputProperty(destinyContainer, destinyPropertyName, linkType))
        return true;
    else	{
        std::cerr << "ERROR: QVPropertyContainer::linkProperty(): source container " << qPrintable(getName()) << " can't handle unspecified output properties linking" << std::endl;
        return false;
        }
    }

bool QVPropertyContainer::linkProperty(QString sourcePropertyName, QVPropertyContainer *destinyContainer, LinkType linkType)
    {
    if (destinyContainer->linkUnspecifiedInputProperty(this, sourcePropertyName, linkType))
        return true;
    else	{
        std::cerr << "ERROR: QVPropertyContainer::linkProperty(): destination container " << qPrintable(destinyContainer->getName()) << " can't handle unspecified input properties linking" << std::endl;
        return false;
        }
    }

void QVPropertyContainer::linkProperty(QVPropertyContainer *container, LinkType linkType)
    {
    QList<QString> localProper = getPropertyList();
    QList<QString> inputProper = container->getPropertyList();

    qSort(localProper.begin(), localProper.end());
    qSort(inputProper.begin(), inputProper.end());

    int i=0, l=0;
    while ( (i < inputProper.size()) && (l < localProper.size()) )
        {
        QString localName = localProper[l];
        QString inputName = inputProper[i];
        if (
            (localName == inputName) && // si tienen el mismo nombre
            (getPropertyType(localName) == container->getPropertyType(inputName)) && // si tienen el mismo tipo
            (io_flags[localName] & outputFlag) && // si una es de entrada
            (container->io_flags[inputName] & inputFlag) && // y otra de salida
            (!(io_flags[localName] & internalProp)) && // y no son propiedades internas
            (!(container->io_flags[inputName] & internalProp))
           )
            linkProperty(localProper[l], container, inputProper[i], linkType);

        if(localName <= inputName) l++;
        if(localName >= inputName) i++;
        }
    }

///////////////////////////////

bool QVPropertyContainer::linkProperty(QString prop_orig, QVPropertyContainer &qvp_dest, QString prop_dest, LinkType link_type)
    {
    return linkProperty(prop_orig, &qvp_dest, prop_dest, link_type);
    }

bool QVPropertyContainer::linkProperty(QVPropertyContainer &destinyContainer, QString destinyPropertyName, LinkType linkType)
    {
    return linkProperty(&destinyContainer, destinyPropertyName, linkType);
    }

bool QVPropertyContainer::linkProperty(QString sourcePropertyName, QVPropertyContainer &destinyContainer, LinkType linkType)
    {
    return linkProperty(sourcePropertyName, &destinyContainer, linkType);
    }

void QVPropertyContainer::linkProperty(QVPropertyContainer &container, LinkType linkType)
    {
    linkProperty(&container, linkType);
    }

//////////////////////////////

bool QVPropertyContainer::linkUnspecifiedInputProperty(QVPropertyContainer *srcCont, QString srcProp, LinkType linkType)
    {
    if (containsProperty(srcProp))
        return srcCont->linkProperty(srcProp, this, srcProp, linkType);
    else
        return false;
    }

bool QVPropertyContainer::linkUnspecifiedOutputProperty(QVPropertyContainer *dstCont, QString dstProp, LinkType linkType)
    {
    if (containsProperty(dstProp))
        return linkProperty(dstProp, dstCont, dstProp, linkType);
    else
        return false;
    }

//////////////////////////////

void QVPropertyContainer::addInputLink(QString prop_dest, QVPropertyContainerLink *link)
    {
    inputLinks[prop_dest] = link;
    link_flags[prop_dest] |= linkedInputFlag;
    }

bool QVPropertyContainer::unlinkProperty(QString origName, QVPropertyContainer *destCont, QString destName)
    {
    QList<QVPropertyContainerLink*> linkList = outputLinks[origName];
    foreach(QVPropertyContainerLink* link, linkList) {
        if ( (link->qvp_orig == this) && (link->prop_orig == origName) &&
            (link->qvp_dest == destCont) && (link->prop_dest == destName) ) {
            if (!link->markedForDeletion) {
                bool isSequential = (link->link_type == SequentialLink) ? true : false;
                link->markedForDeletion = TRUE;
                // Protect against a possible pending acquire() for our output
                // in other holders:
                link->SyncSemaphoreOut.release();
                destCont->treatUnlinkInputProperty(destName, this, origName);
                // This ProcessSequentialUnlink cannot generate a core for acceding to all group nodes
                // because the two QVPropertyContainer's are in the same thread and its unlinks
                // are doing sequentialy
                if (isSequential) ProcessSequentialUnlink(this, destCont);
                informer.emitChange(QVPropertyContainerChange(this->getName(), this->getId(), QVPropertyContainerChange::LinkDel, this->getName(), this->getId(), origName, destCont->getName(), destCont->getId(), destName));
            }
            return TRUE;
        }
    }
    return FALSE;
    }

bool QVPropertyContainer::unlinkProperty(QString origName, QVPropertyContainer &destCont, QString destName)
    {
    return unlinkProperty(origName, &destCont, destName);
    }

bool QVPropertyContainer::treatUnlinkInputProperty(QString, QVPropertyContainer *, QString)
    {
    return true;
    }

void QVPropertyContainer::unlink()
{
    foreach(QVPropertyContainerLink* link, inputLinks.values()) {
        if (!link->markedForDeletion) {
            bool isSequential = (link->link_type == SequentialLink) ? true : false;
            link->markedForDeletion = TRUE;
            // Protect against a possible pending acquire() from our input
            // in other holders:
            link->SyncSemaphoreIn.release();
            // This ProcessSequentialUnlink cannot generate a core for acceding to all group nodes
            // because the two QVPropertyContainer's are in the same thread and its unlinks
            // are doing sequentialy
            if (isSequential) ProcessSequentialUnlink(link->qvp_orig, link->qvp_dest);
            informer.emitChange(QVPropertyContainerChange(this->getName(), this->getId(), QVPropertyContainerChange::LinkDel, link->qvp_orig_name, link->qvp_orig_id, link->prop_orig, link->qvp_dest_name, link->qvp_dest_id, link->prop_dest));
        }
    }

    foreach(QList<QVPropertyContainerLink*> linkList, outputLinks.values()) {
        foreach(QVPropertyContainerLink* link, linkList) {
            if (!link->markedForDeletion) {
                bool isSequential = (link->link_type == SequentialLink) ? true : false;
                link->markedForDeletion = TRUE;
                // Protect against a possible pending acquire() for our output
                // in other holders:
                link->SyncSemaphoreOut.release();
                if (link->qvp_dest != NULL) link->qvp_dest->treatUnlinkInputProperty(link->prop_dest, this, link->prop_orig);
                // This ProcessSequentialUnlink cannot generate a core for acceding to all group nodes
                // because the two QVPropertyContainer's are in the same thread and its unlinks
                // are doing sequentialy
                if (isSequential) ProcessSequentialUnlink(link->qvp_orig, link->qvp_dest);
                informer.emitChange(QVPropertyContainerChange(this->getName(), this->getId(), QVPropertyContainerChange::LinkDel, link->qvp_orig_name, link->qvp_orig_id, link->prop_orig, link->qvp_dest_name, link->qvp_dest_id, link->prop_dest));
            }
        }
    }
}

void QVPropertyContainer::readInputProperties()
    {
    // We read every linked input property from its source, protecting
    // the read with a standard RWLock (that here we just lock for read).
    // The only caveat is that if a property is synchronously read, then
    // we must wait for the producer to write it first. We implement that
    // by waiting on the SyncSemaphoreOut of the link. Also, in this
    // case when we finish reading the property, we signal every possible
    // waiting writer that, regarding this specific link, it can write now
    // a new value if it needs to, because we have read the old value yet.
    // This is implemented by releasing the SyncSemaphoreIn associated to
    // the link.
    QMutableMapIterator<QString, QVPropertyContainerLink*> i(inputLinks);
    while (i.hasNext()) {
        i.next();
        QVPropertyContainerLink *link = i.value();

        // Possible link deletion:
        if(link->markedForDeletion) {
            i.remove();
            toDeleteLink(link);
        }
        else {
            if(link->link_type == SynchronousLink) {
                link->SyncSemaphoreOut.acquire();
            }
            if (link->link_type != SequentialLink)
                link->qvp_orig->RWLock.lockForRead();
            //this->setPropertyValueQVariant(link->prop_dest,link->qvp_orig->safelyCopiedVariants[link->prop_orig]);
            this->variants[link->prop_dest] = link->qvp_orig->safelyCopiedVariants[link->prop_orig];
            if (link->link_type != SequentialLink)
                link->qvp_orig->RWLock.unlock();
            if(link->link_type == SynchronousLink) {
                link->SyncSemaphoreIn.release();
            }
        }
    }
    informer.emitChange(QVPropertyContainerChange(this->getName(), this->getId(), QVPropertyContainerChange::PropertiesValues));
}

void QVPropertyContainer::writeOutputProperties()
    {
    QMutableMapIterator<QString, QList<QVPropertyContainerLink*> >i(outputLinks);

    // For every QVP synchronously linked to this QVP's output, we ask
    // for permision to write a new output (that will only be possible if
    // all of these QVP's have read their inputs already):
    bool someSequential = false;
    while (i.hasNext()) {
        i.next();
        QListIterator<QVPropertyContainerLink*> j(i.value());
        while(j.hasNext()) {
            QVPropertyContainerLink *link = j.next();
            if(link->link_type == SynchronousLink and not link->markedForDeletion) {
                link->SyncSemaphoreIn.acquire();
            }
            else if(link->link_type == SequentialLink and not link->markedForDeletion) {
                someSequential = true;
            }
        }
    }

    // Now, we write a new coherent state, simply protected by the
    // corresponding RWLock:
    i.toFront();
    if (!someSequential)
        this->RWLock.lockForWrite();
    while (i.hasNext()) {
        i.next();
        QString prop_orig = i.key();
        safelyCopiedVariants[prop_orig] = variants[prop_orig];
    }
    if (!someSequential)
        this->RWLock.unlock();

    // Finally, we signal to QVP's synchronously linked to this QVP's output
    // that there is a new coherent output, by releasing the corresponding
    // semaphore.
    i.toFront();
    while (i.hasNext()) {
        i.next();
        QMutableListIterator<QVPropertyContainerLink*> j(i.value());
        while(j.hasNext()) {
            QVPropertyContainerLink *link = j.next();
            if(link->link_type == SynchronousLink and not link->markedForDeletion) {
                link->SyncSemaphoreOut.release();
            }
            // Possible link deletion:
            if(link->markedForDeletion) {
                j.remove();
                toDeleteLink(link);
                if(i.value().isEmpty()) {
                    i.remove();
                    break;
                }
            }
        }
    }
}

void QVPropertyContainer::toDeleteLink(QVPropertyContainerLink* link)
    {
        if (link->qvp_orig == this) {
            link->qvp_orig = NULL;
        }
        else if (link->qvp_dest == this) {
            link->qvp_dest = NULL;
        }

        if ((link->qvp_orig == NULL) && (link->qvp_dest == NULL)) delete link;
    }

void QVPropertyContainer::setLastError(QString str) const
    { errorString = str; }

QVPropertyContainer *QVPropertyContainer::getSourceContainer(const QString name) const
    {
        const QMap<QString, QVPropertyContainerLink* > inLinks = getInputLinks();
        if (inLinks.contains(name))
            return inLinks.value(name)->qvp_orig;

        return NULL;
    }

QList<QVPropertyContainer *> QVPropertyContainer::getDestinyContainers(const QString name) const
    {
        QList<QVPropertyContainer *> list;

        if (outputLinks.contains(name))
            foreach(QVPropertyContainerLink* link, outputLinks.value(name))
                if ( (link->qvp_dest != NULL) && (!list.contains(link->qvp_dest)) ) list.append(link->qvp_dest);

        return list;
    }

QString QVPropertyContainer::getSourceProperty(const QString name) const
    {
        const QMap<QString, QVPropertyContainerLink* > inLinks = getInputLinks();
        if (inLinks.contains(name))
            return inLinks.value(name)->prop_orig;

        return QString();
    }

bool QVPropertyContainer::isSynchronous(const QString name) const
    {
        const QMap<QString, QVPropertyContainerLink* > inLinks = getInputLinks();
        if (inLinks.contains(name))
            return (inLinks.value(name)->link_type == SynchronousLink);

        return FALSE;
    }

bool QVPropertyContainer::isSequential(const QString name) const
    {
        const QMap<QString, QVPropertyContainerLink* > inLinks = getInputLinks();
        if (inLinks.contains(name))
            return (inLinks.value(name)->link_type == SequentialLink);

        return FALSE;
    }

bool QVPropertyContainer::areSynchronized(const QList<QVPropertyContainer *> conts)
    {
    QVDisjointSet dSet(conts.size());

    for (int i = 0; i < conts.size(); i++)
        for (int j = i+1; j < conts.size(); j++) // for each pair of container
            {
            bool find = false; // only need one syncrhonous property to be synchronized

            if (conts.at(i)->getId() == conts.at(j)->getId()) // if they are the same container, they are synchronized
                {
                dSet.unify(i, j); // unify their sets
                find = true;
                }
            if (!find)
                {
                const QMap<QString, QVPropertyContainerLink* > inLinksI = conts.at(i)->getInputLinks();
                foreach(QVPropertyContainerLink* proConLink, inLinksI.values())        // for each first container's linked input property
                    if ( (proConLink->qvp_orig_id == conts.at(j)->getId()) &&         // if is linked from second container
                         (proConLink->link_type != AsynchronousLink)               ) // and is a synchronous link
                        {
                        dSet.unify(i, j); // unify their sets
                        find = true;
                        break;
                        }
                }
            if (!find)
                {
                const QMap<QString, QVPropertyContainerLink* > inLinksJ = conts.at(j)->getInputLinks();
                foreach(QVPropertyContainerLink* proConLink, inLinksJ.values())        // for each second container's linked input property
                    if ( (proConLink->qvp_orig_id == conts.at(i)->getId()) &&         // if is linked from first container
                         (proConLink->link_type != AsynchronousLink)               ) // and is a synchronous link
                        {
                        dSet.unify(i, j); // unify their sets
                        break;
                        }
                }
            }

    return (dSet.numberOfSets() == 1);
    }

template <> bool QVPropertyContainer::parseArgument<bool>(const QString parameter, const QString value)
    {
    if (value.toLower() == "true" || value.toLower() == "false")
        {
        //variants[parameter] = QVariant::fromValue<bool>(value.toLower() == "true");
        setPropertyValue<bool>(parameter,value.toLower() == "true");
        return TRUE;
        }
    else {
        errorString = "QVPropertyContainer::parseArgument(): holder " + getName() +
                    ": value " + value +
                    " is not a valid boolean value for parameter " +
                    parameter + ".\n";
        return FALSE;
        }
    }

template <> bool QVPropertyContainer::parseArgument<int>(const QString parameter, const QString value)
    {
    bool okInt;
    int intValue = value.toInt(&okInt);
    if(not okInt)
        {
        errorString = "QVPropertyContainer::parseArgument(): holder " + getName() +
                    ": value " + value +
                    " is not a valid integer value for parameter " +
                    parameter + ".\n";
        return FALSE;
        }
    //variants[parameter] = QVariant::fromValue<int>(intValue);
    setPropertyValue<int>(parameter,intValue);
    return TRUE;
    }

template <> bool QVPropertyContainer::parseArgument<float>(const QString parameter, const QString value)
{
    bool okFloat;
    float floatValue = value.toFloat(&okFloat);
    if(not okFloat)	{
        errorString = "QVPropertyContainer::parseArgument(): holder " + getName() +
                ": value " + value +
                " is not a valid float value for parameter " +
                parameter + ".\n";
    return FALSE;
    }
    //variants[parameter] = QVariant::fromValue<float>(floatValue);
    setPropertyValue<float>(parameter,floatValue);

    return TRUE;
}

template <> bool QVPropertyContainer::parseArgument<double>(const QString parameter, const QString value)
    {
    bool okDouble;
    double doubleValue = value.toDouble(&okDouble);
    if(not okDouble)
        {
        errorString = "QVPropertyContainer::parseArgument(): holder " + getName() +
                    ": value " + value +
                    " is not a valid double value for parameter " +
                    parameter + ".\n";
        return FALSE;
        }
    //variants[parameter] = QVariant::fromValue<double>(doubleValue);
    setPropertyValue<double>(parameter,doubleValue);

    return TRUE;
    }

template <> bool QVPropertyContainer::parseArgument<QString>(const QString parameter, const QString value)
    {
    //variants[parameter] = QVariant::fromValue<QString>(value);
    setPropertyValue<QString>(parameter,value);
    return TRUE;
    }

// the sequential subgraphs cannot have cicles
bool QVPropertyContainer::ProcessPosibleSequentialLink(QVPropertyContainer *destCont)
    {
        // Return false if the link will generate a sequential links cicle
        if (haveSyncPrecursor(destCont))
            return false;

        // If they are sequentiely connected yet, do nothing
        if (destCont->haveSyncPrecursor(this))
            return true;

        // Update de deeps
        destCont->updateDeep(deepLevel);

        // choose the new master of the join group
        QVPropertyContainer *winnerMaster, *loserMaster;
        if (this->master->getId() < destCont->master->getId()) {
            winnerMaster = this->master;
            loserMaster = destCont->master;
        }
        else {
            winnerMaster = destCont->master;
            loserMaster = this->master;
        }

        // change the masters of the group's items
        for(int i = 0; i < loserMaster->slavesByLevel.size(); i++) {
            if(winnerMaster->slavesByLevel.size() <= i)
                winnerMaster->slavesByLevel.append(QList<QVPropertyContainer *>());

            QList<QVPropertyContainer *> level = loserMaster->slavesByLevel[i];
            foreach(QVPropertyContainer *slave, level) {
                slave->master = winnerMaster;
                winnerMaster->slavesByLevel[i].append(slave);
            }
        }

        // update the old master (looser master)
        foreach(QList<QVPropertyContainer *> level, loserMaster->slavesByLevel) {
            loserMaster->slavesByLevel.removeAll(level);
        }

        return true;
    }

// the sequential subgraphs cannot have cicles
void QVPropertyContainer::updateDeep(int origDeep)
     {
        int newDeep = origDeep + 1; // sets its minim deep
        foreach(QVPropertyContainerLink* inLink, getInputLinks()) { // calculate the new deep
            QVPropertyContainer *cont = inLink->qvp_orig;
            if ( (cont != NULL) && (inLink->markedForDeletion == FALSE) && (inLink->link_type == SequentialLink) )
                if (cont->deepLevel >= newDeep)
                    newDeep = cont->deepLevel + 1;
        }

        if (newDeep != deepLevel) { // if the deep changes, change his level position, his deep, and his successors deep
            master->slavesByLevel[deepLevel].removeAll(this);
            deepLevel = newDeep;

            while(master->slavesByLevel.size() <= deepLevel)
                master->slavesByLevel.append(QList<QVPropertyContainer *>());
            master->slavesByLevel[deepLevel].append(this);

            foreach(QString prop, getPropertyList())
                foreach(QVPropertyContainer *container, getDestinySequentialContainers(prop))
                    container->updateDeep(deepLevel);
        }
    }

// the sequential subgraphs cannot have cicles
void QVPropertyContainer::ProcessSequentialUnlink(QVPropertyContainer *origCont, QVPropertyContainer *destCont)
    {
        // if the group still join do nothing
        if (destCont->haveSyncPrecursor(origCont)) return;

        // if origCont is in the masterless subgroup, they becomes a new master
        if( (origCont->master != origCont) && !origCont->haveSyncPrecursor(origCont->master) && !origCont->master->haveSyncPrecursor(origCont) ) {
            // changes all subgroup master
            origCont->changeMaster(origCont);
            origCont->propagateBackwardMasterChange(origCont);
            origCont->propagateForwardMasterChange(origCont);

            // update its (and its succesors) deep
            origCont->updateDeep(-1);

            // they must update other subgroup deep
            destCont->updateDeep(-1);
        }
        // if destCont is in the masterless subgroup, they becomes a new master
        else if( (destCont->master != destCont) && !destCont->haveSyncPrecursor(destCont->master) && !destCont->master->haveSyncPrecursor(destCont) ) {
            // changes all subgroup master
            destCont->propagateBackwardMasterChange(destCont);
            destCont->propagateForwardMasterChange(destCont);
            destCont->changeMaster(destCont);

            // update its (and its succesors) deep
            destCont->updateDeep(-1);
        }
    }

// the sequential subgraphs cannot have cicles
bool QVPropertyContainer::haveSyncPrecursor(QVPropertyContainer *precursor)
    {
        foreach(QString prop, getPropertyList()) {
            if (/*isSynchronous(prop) || */isSequential(prop)) {
                const QMap<QString, QVPropertyContainerLink* > inLinks = getInputLinks();
                QVPropertyContainer *cont = inLinks.value(prop)->qvp_orig;
                if ( (cont != NULL) && (inLinks.value(prop)->markedForDeletion == FALSE) )
                    if ( (precursor == cont) || (cont->haveSyncPrecursor(precursor)) ) return true;
            }
        }
        return false;
    }

// the sequential subgraphs cannot have cicles
void QVPropertyContainer::propagateBackwardMasterChange(QVPropertyContainer *newMaster)
    {
        foreach(QVPropertyContainerLink *link, getInputLinks()) {
            QVPropertyContainer *cont = link->qvp_orig;
            if ( (cont != NULL) && (link->markedForDeletion == FALSE) && (link->link_type == SequentialLink) && (cont->master != newMaster) ) {
                cont->changeMaster(newMaster);
                cont->propagateBackwardMasterChange(newMaster);
                cont->propagateForwardMasterChange(newMaster);
            }
        }

    }

// the sequential subgraphs cannot have cicles
void QVPropertyContainer::propagateForwardMasterChange(QVPropertyContainer *newMaster)
    {
        foreach(QString prop, getPropertyList()) {
            foreach(QVPropertyContainer *container, getDestinySequentialContainers(prop)) {
                if (container->master != newMaster) {
                    container->changeMaster(newMaster);
                    container->propagateForwardMasterChange(newMaster);
                    container->propagateBackwardMasterChange(newMaster);
                }
            }
        }
    }

// the sequential subgraphs cannot have cicles
void QVPropertyContainer::changeMaster(QVPropertyContainer *newMaster)
    {
        master->slavesByLevel[deepLevel].removeAll(this);
        master = newMaster;

        while(master->slavesByLevel.size() <= deepLevel)
            master->slavesByLevel.append(QList<QVPropertyContainer *>());
        master->slavesByLevel[deepLevel].append(this);
    }

// the sequential subgraphs cannot have cicles
QList<QVPropertyContainer *> QVPropertyContainer::getDestinySequentialContainers(const QString name) const
    {
        QList<QVPropertyContainer *> list;

        if (outputLinks.contains(name))
            foreach(QVPropertyContainerLink* link, outputLinks.value(name)) {
                if ( (link->qvp_dest != NULL) &&
                     (link->markedForDeletion == FALSE) &&
                     (!list.contains(link->qvp_dest)) &&
                     (link->link_type == SequentialLink) ) list.append(link->qvp_dest);
            }

        return list;
    }
