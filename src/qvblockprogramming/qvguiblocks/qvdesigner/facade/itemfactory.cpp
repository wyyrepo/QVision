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


#include "itemfactory.h"

#include <typeinfo>

#include <QVApplication>
//#include <QVMPlayerCamera>
#include <QVProcessingBlock>

#include <QVPointBlock>

#include <QVImageCanvas>
#include <QVNumericPlot>
#include <QVHistogramPlot>
#include <QVFunctionPlot>
#include <QVCPUPlot>

#include <QVSynchronizerBlock>

#ifdef QVIPP
#include <QVGraphsBlock>
#include <QVFilterSelectorBlock>
#include <QVYUV4MPEG2WriterBlock>
#include <QVYUV4MPEG2ReaderBlock>
#include <QVImageRetarderBlock>
#include <QVImageMeansBlock>
#endif

/*#ifdef QVMPLAYER
#include <QVMPlayerReaderBlock>
#endif*/
#include <QVVideoReaderBlock>

///@todo no crear todos los blocks aqui, sino sacal la lista de nombres y luego crearlos bajo demanda
ItemFactory::ItemFactory(): QObject()
{
    inputItems.insert("Input node", QList<QString>());
    #ifdef QVMPLAYER
    inputItems["Input node"].append("QVMPlayerReaderBlock");
    #endif
    #ifdef QVIPP
    inputItems["Input node"].append("QVYUV4MPEG2ReaderBlock");
    #endif
    inputItems["Input node"].append("QVPointBlock");

    outputItems.insert("Output node", QList<QString>());
    outputItems["Output node"].append("QVImageCanvas");
    outputItems["Output node"].append("QVNumericPlot");
    outputItems["Output node"].append("QVHistogramPlot");
    outputItems["Output node"].append("QVFunctionPlot");
    outputItems["Output node"].append("QVCPUPlot");
    #ifdef QVIPP
    outputItems["Output node"].append("QVYUV4MPEG2WriterBlock");
    #endif
    outputItems["Output node"].append("QVSynchronizer");

    middleItems.insert("QVision block", QList<QString>());
    #ifdef QVIPP
    middleItems["QVision block"].append("QVGraphsBlock");
    middleItems["QVision block"].append("QVFilterSelectorBlock<uchar,1>");
    middleItems["QVision block"].append("QVFilterSelectorBlock<uchar,3>");
    middleItems["QVision block"].append("QVImageRetarderBlock<uchar,3>");
    middleItems["QVision block"].append("QVImageRetarderBlock<uchar,1>");
    middleItems["QVision block"].append("QVImageMeans<uChar,1>");
    middleItems["QVision block"].append("QVImageMeans<uChar,3>");

    // Añadimos los tipos de las IPP.
    QMap<QString, QString> ippBlocks = getQVIPPBlocksNames();
    foreach(QString ippGroup, ippBlocks.keys())
        {
        middleItems.insert(ippGroup, QList<QString>());
        foreach(QString qvippBlockName, ippBlocks.values(ippGroup))
            middleItems[ippGroup].append(qvippBlockName);
        }
    #endif

    // Añadimos los tipos creados por el usuario.
/*	foreach(QVPropertyContainer* qvp, qvApp->getQVPropertyContainers()) {
        QVProcessingBlock* block;
        if((block = dynamic_cast<QVProcessingBlock*>(qvp)) != NULL)
            middleItems.append(block.getName());
        }*/
}

QMap<QString, QList<QString> > ItemFactory::getItemTypes() const
{
    QMap<QString, QList<QString> > items = inputItems;

    foreach(QString group, middleItems.keys()) {
        if (items.contains(group))
            items[group] = items.value(group) + middleItems.value(group);
        else
            items.insert(group, middleItems.value(group));
    }

    foreach(QString group, outputItems.keys()) {
        if (items.contains(group))
            items[group] = items.value(group) + outputItems.value(group);
        else
            items.insert(group, outputItems.value(group));
    }

    return items;
}

QMap<QString, QList<QString> > ItemFactory::getInputItemTypes() const
{
    return inputItems;
}

QMap<QString, QList<QString> > ItemFactory::getMiddleItemTypes() const
{
    return middleItems;
}

QMap<QString, QList<QString> > ItemFactory::getOutputItemTypes() const
{
    return outputItems;
}

QVPropertyContainer *ItemFactory::createContainer(QString type, QString name) const
{
    #ifdef QVIPP
    QVPropertyContainer *qvippBlock = newQVIPPBlock(type, name);
    if (qvippBlock != NULL)
        return qvippBlock;
    #endif
    /*else if (type == "QVMPlayerCamera") {
        QVMPlayerCamera* mpc = new QVMPlayerCamera(name);
        if (mpc->getPropertyValue<QString>("URL").isEmpty())
            mpc->setPropertyValue("URL", QString("http://perception.inf.um.es/public_data/videos/misc/penguin.dv"));
        return mpc;
    }*/

    if (type == "QVImageCanvas") return new QVImageCanvas(name);
    else if (type == "QVNumericPlot") return new QVNumericPlot(name);
    else if (type == "QVHistogramPlot") return new QVHistogramPlot(name);
    else if (type == "QVFunctionPlot") return new QVFunctionPlot(name);
    else if (type == "QVCPUPlot") return new QVCPUPlot(name);
    //else if (type == "QVAdd_uCharC1Block") return new QVAdd_uCharC1Block(name);
    else if (type == "QVPointBlock") return new QVPointBlock(name);
    else if (type == "QVSynchronizer") return new QVSynchronizer(name);
    else if (type == "QVCPUPlot") return new QVCPUPlot(name);


    /*	#ifdef QVMPLAYER
    else if (type == "QVMPlayerReaderBlock") {
        QVMPlayerReaderBlock* mpc = new QVMPlayerReaderBlock(name);
        if (mpc->getPropertyValue<QString>("URL").isEmpty())
            mpc->setPropertyValue("URL", QString("http://perception.inf.um.es/public_data/videos/misc/penguin.dv"));
        return mpc;
    }
    #endif
    #ifdef QVIPP
    else if (type == "QVYUV4MPEG2ReaderBlock") {
        QVYUV4MPEG2ReaderBlock* mpc = new QVYUV4MPEG2ReaderBlock(name);
        if (mpc->getPropertyValue<QString>("URL").isEmpty())
            mpc->setPropertyValue("URL", QString("http://perception.inf.um.es/public_data/videos/misc/penguin.dv"));
        return mpc;
    }*/
    else if (type == "QVVideoReaderBlock") { // FIXME: still not tested (after video input system changes);
        QVVideoReaderBlock* mpc = new QVVideoReaderBlock(name);
        if (mpc->getPropertyValue<QString>("URL").isEmpty())
            mpc->setPropertyValue("URL", QString("http://perception.inf.um.es/public_data/videos/misc/penguin.dv"));
        return mpc;
    }
//    else if (type == "QVYUV4MPEG2Camera") return new QVYUV4MPEG2ReaderBlock(name);
	#ifdef QVIPP
    else if (type == "QVYUV4MPEG2WriterBlock") return new QVYUV4MPEG2WriterBlock(name);
    else if (type == "QVImageRetarderBlock<uchar,3>") return new QVImageRetarderBlock<uchar, 3>(name);
    else if (type == "QVImageRetarderBlock<uchar,1>") return new QVImageRetarderBlock<uchar, 1>(name);
    else if (type == "QVImageMeans<uChar,1>") return new QVImageMeans<uChar, 1>(name);
    else if (type == "QVFilterSelectorBlock<uchar,1>") return new QVFilterSelectorBlock<uchar, 1>(name);
    else if (type == "QVFilterSelectorBlock<uchar,3>") return new QVFilterSelectorBlock<uchar, 3>(name);
    else if (type == "QVGraphsBlock") return new QVGraphsBlock(name);
    #endif // QVIPP
    else if (userBlocks.contains(type)) {
        QVProcessingBlock * newBlock = (QVProcessingBlock *)QMetaType::construct(userBlocks.value(type), (void *)0);
        newBlock->setName(name);
        return newBlock;
    }
    return 0;
}

bool ItemFactory::deleteContainer(QVPropertyContainer *cont) const
{
    // obtiene el nombre y el valor del tipo de la subclase concreta
    QString type = typeName(cont);

/*	// lo destruye dependiendo de como se ha creado
    if (isUserType(type))
        QMetaType::destroy(userBlocks.value(type), (void *)cont);
    else
        delete cont;*/

    delete cont;

    return TRUE;
}

QString ItemFactory::containerType(QVPropertyContainer *cont) const
{
    // obtiene el nombre y el valor del tipo de la subclase concreta
    return QString(typeName(cont));
}

const QString ItemFactory::registerUserBlock(QVProcessingBlock * block)
{
    const char * choptypeidname = typeName(block);

    // obtiene el nombre y el valor del tipo de la subclase concreta
    QString typeString(choptypeidname);
    int type = QMetaType::type(choptypeidname);

    // almacena el subtipo concreto del objeto, si no existía ya y si estaba registrado en el sistema con qRegisterMetaType<Type>("Type")
    bool middleItemsContainsType = false;
    foreach(QList<QString> groupItems, middleItems.values())
        if (groupItems.contains(typeString)) {
            middleItemsContainsType = true;
            break;
        }
    if ( (type != 0) && (!middleItemsContainsType) ) {
        if (!middleItems.contains("User block")) middleItems.insert("User block", QList<QString>());
        middleItems["User block"].append(typeString);
        userBlocks.insert(typeString, type);
        return typeString;
    }
    return QString();
}

bool ItemFactory::isUserType(QString type) const
{
    return userBlocks.contains(type);
}

const char *ItemFactory::typeName(QVPropertyContainer *cont) const
{
    char *qvippBlockName = NULL; //QVIPPBlockName(cont);
    if (qvippBlockName != NULL)
        return qvippBlockName;

    if(dynamic_cast<QVImageCanvas*>(cont) != NULL) return "QVImageCanvas";
    else if(dynamic_cast<QVNumericPlot*>(cont) != NULL) return "QVNumericPlot";
    else if(dynamic_cast<QVHistogramPlot*>(cont) != NULL) return "QVHistogramPlot";
    else if(dynamic_cast<QVFunctionPlot*>(cont) != NULL) return "QVFunctionPlot";
    else if(dynamic_cast<QVCPUPlot*>(cont) != NULL) return "QVCPUPlot";
    else if(dynamic_cast<QVPointBlock*>(cont) != NULL) return "QVPointBlock";
    else if(dynamic_cast<QVSynchronizer*>(cont) != NULL) return "QVSynchronizer";
    #ifdef QVIPP
    else if(dynamic_cast<QVGraphsBlock*>(cont) != NULL) return "QVGraphsBlock";
    //else if(dynamic_cast<QVYUV4MPEG2ReaderBlock*>(cont) != NULL) return "QVYUV4MPEG2Camera";
    else if(dynamic_cast<QVYUV4MPEG2WriterBlock*>(cont) != NULL) return "QVYUV4MPEG2WriterBlock";
    else if(dynamic_cast<QVFilterSelectorBlock<uchar,1>*>(cont) != NULL) return "QVFilterSelectorBlock<uchar,1>";
    else if(dynamic_cast<QVFilterSelectorBlock<uchar,3>*>(cont) != NULL) return "QVFilterSelectorBlock<uchar,3>";
    else if(dynamic_cast<QVImageRetarderBlock<uchar,3>*>(cont) != NULL) return "QVImageRetarderBlock<uchar,3>";
    else if(dynamic_cast<QVImageRetarderBlock<uchar,1>*>(cont) != NULL) return "QVImageRetarderBlock<uchar,1>";
    else if(dynamic_cast<QVImageMeans<uChar,1>*>(cont) != NULL) return "QVImageMeans<uChar,1>";
    else if(dynamic_cast<QVImageMeans<uChar,3>*>(cont) != NULL) return "QVImageMeans<uChar,3>";
    #endif

    // obtiene el tipo real del objeto (la sunclase concreta de block) en un formato char * de longitud+nombre (ejemplo: 8MyBlock)
    const char * typeidname = typeid(*cont).name();

    // se salta la pirmera parte de la cadena, la que contiene el número de caracteres del tipo
    int i = 0;
    while ( (typeidname[i] != '\0') && ((typeidname[i] == '0') || (typeidname[i] == '1') || (typeidname[i] == '2') || (typeidname[i] == '3') ||
            (typeidname[i] == '4') || (typeidname[i] == '5') || (typeidname[i] == '6') || (typeidname[i] == '7') || (typeidname[i] == '8') ||
            (typeidname[i] == '9')) ) {
        i++;
    }
    return (typeidname + i*(sizeof(char)));
}


