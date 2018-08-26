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


#include "itemproperties.h"
#include "QVPropertyContainer"


// genera un item properties vacio
ItemProperties::ItemProperties(QString type): containerType(type)
{
}

// genera un item properties a partir de un qvpropertycontainer
ItemProperties::ItemProperties(QString type, QVPropertyContainer *container): containerType(type)
{
	QList<QString> prop( container->getPropertyList() );

	for (int i = 0; i < prop.size(); i++)
	{ // para cada propiedad
		QVPropertyContainer::PropertyFlags flags = container->getPropertyFlags(prop[i]);
		if ( !(flags & (QVPropertyContainer::guiInvisible | QVPropertyContainer::internalProp)) )
		{ // solo la incluyo si no es ni guiinvisible ni internalprop
			properties.append( prop[i] );
			types.append( container->getPropertyType(prop[i]) );
			inputs.append( container->isInput(prop[i]) );
			outputs.append( container->isOutput(prop[i]) );
			infos.append( container->getPropertyInfo(prop[i]) );
		}
	}
}

QString ItemProperties::getType() const
{
	return containerType;
}

QList<QString> ItemProperties::getProperties() const
{
	return properties;
}

int ItemProperties::propertyType(const uint i) const
{
	if (i >= (uint)types.size()) return 0;
	return types[i];
}

bool ItemProperties::isInput(const uint i) const
{
	if (i >= (uint)inputs.size()) return false;
	return inputs[i];
}

bool ItemProperties::isOutput(const uint i) const
{
	if (i >= (uint)outputs.size()) return false;
	return outputs[i];
}

QString ItemProperties::info(const uint i) const
{
	if (i >= (uint)outputs.size()) return QString();
	return infos[i];
}

void ItemProperties::insertProperty(int pos, QString name, int type, bool input, bool output)
{
	if ( (pos >= 0) && (pos <= properties.size()) )
	{
		properties.insert(pos, name);
		types.insert(pos, type);
		inputs.insert(pos, input);
		outputs.insert(pos, output);
	}
}

void ItemProperties::deleteProperty(int pos)
{
	if ( (pos >= 0) && (pos <= properties.size()) )
	{
		properties.removeAt(pos);
		types.removeAt(pos);
		inputs.removeAt(pos);
		outputs.removeAt(pos);
	}
}

void ItemProperties::deleteProperty(QString name)
{
	deleteProperty(properties.indexOf(name));
}

