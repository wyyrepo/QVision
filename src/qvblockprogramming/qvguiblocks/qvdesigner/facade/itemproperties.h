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


#ifndef ITEMPROPERTIES_H
#define ITEMPROPERTIES_H

#include <QString>
#include <QList>


class QVPropertyContainer;

#ifndef DOXYGEN_IGNORE_THIS

// Clase que representa a un propertycontainer, de forma que podemos obtener el nombre de este, y su lista de propiedades y los parámetros de estas
class ItemProperties
{
public:
	ItemProperties(QString type);
	ItemProperties(QString type, QVPropertyContainer *container);

	QString getType() const;
	QList<QString> getProperties() const;
	int propertyType(const uint i) const;
	bool isInput(const uint i) const;
	bool isOutput(const uint i) const;
	QString info(const uint i) const;

	void insertProperty(int pos, QString name, int type, bool input, bool output);
	void deleteProperty(int pos);
	void deleteProperty(QString name);


private:
	QString containerType;

	QList<QString> properties;
	QList<int> types;
	QList<bool> inputs;
	QList<bool> outputs;
	QList<QString> infos;
};

#endif
#endif
