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


#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <QObject>
#include <QList>
#include <QString>
#include "itemproperties.h"
#include <QVProcessingBlock>

#ifdef QVIPP
#include <qvippblocks.h>
#endif

#ifndef DOXYGEN_IGNORE_THIS

// Clase que se encargará de implemetar la obtención de los tipos de blocks de que disponemos (parecido a un Factory)
class ItemFactory: QObject
{
	Q_OBJECT
	
	public:
		ItemFactory();

		// devuelve la lista de Items disponibles en el sistema, cada uno de estos items es un elemento del diseño de los programas de QVision
		QMap<QString, QList<QString> > getItemTypes() const;

		// devuelve la lista de Items de entrada disponibles en el sistema, cada uno de estos items es un elemento del diseño de los programas de QVision
		QMap<QString, QList<QString> > getInputItemTypes() const;

		// devuelve la lista de Items intermedios disponibles en el sistema, cada uno de estos items es un elemento del diseño de los programas de QVision
		QMap<QString, QList<QString> > getMiddleItemTypes() const;

		// devuelve la lista de Items de salida disponibles en el sistema, cada uno de estos items es un elemento del diseño de los programas de QVision
		QMap<QString, QList<QString> > getOutputItemTypes() const;

		QVPropertyContainer *createContainer(QString type, QString name) const;

		bool deleteContainer(QVPropertyContainer *cont) const;

		QString containerType(QVPropertyContainer *cont) const;

		// registra en tiempo de ejecución un nuevo tipo de block a partir de un objeto de ese tipo, posteriormente se podrán crear objetos de este tipo
		const QString registerUserBlock(QVProcessingBlock * block);

		bool isUserType(QString type) const;

	private:
		const char *typeName(QVPropertyContainer *cont) const;

		QMap<QString, QList<QString> > inputItems, middleItems, outputItems;
		QMap<QString, int> userBlocks;
};

#endif
#endif
