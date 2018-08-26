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

#include <QVPropertyContainerChange>


QString QVPropertyContainerChange::toString() const
{
	QString result("Change emited from ");
	result+= sourceName;
	result += ", of type ";

	switch (changeType) {
	case Name:
		result += "Name";
		break;
// 	case ContainerAdd:
// 		result += "ContainerAdd";
// 		break;
	case ContainerDel:
		result += "ContainerDel";
		break;
	case PropertyAdd:
		result += "PropertyAdd: ";
		result += propName;
		break;
	case PropertyDel:
		result += "PropertyDel: ";
		result += propName;
		break;
	case PropertyValue:
		result += "PropertyValue: ";
		result += propName;
		result += ". New value = ";
		result += value.toString();
		break;
	case PropertiesValues:
		result += "PropertiesValues";
		break;
	case LinkAdd:
		result += "LinkAdd: ";
		result += origName;
		result += "[";
		result += propName;
		result += "] => ";
		result += destName;
		result += "[";
		result += destPropName;
		result += "]";
		break;
	case LinkDel:
		result += "LinkDel: ";
		result += origName;
		result += "[";
		result += propName;
		result += "] => ";
		result += destName;
		result += "[";
		result += destPropName;
		result += "]";
		break;
	case All:
		result += "All";
		break;
	default:
		result += "None";
		break;
	}
	result += ".";

	return result;
}

