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

#include <iostream>
#include "qvnumericplot.h"

QVNumericPlot::QVNumericPlot(const QString name, bool time, int step, QWidget *parent): QVPlot(name, true, false, false, true, time, step, parent)
	{ }

bool QVNumericPlot::linkUnspecifiedInputProperty(QVPropertyContainer *sourceContainer, QString sourcePropName, LinkType linkType)
	{
	QVProcessingBlock* block;
	if((block = dynamic_cast<QVProcessingBlock*>(sourceContainer)) != NULL)
		{
		//int propType = block->getPropertyType(sourcePropName);
		if (not (	sourceContainer->isType<int>(sourcePropName)	||
				sourceContainer->isType<double>(sourcePropName)	||
				sourceContainer->isType<uChar>(sourcePropName)
			))
		//if ( (propType != QVariant::Int) && (propType != QVariant::Double) )
			{
			std::cerr << "Warning: a numericplot only can be linked to a int or double property." << std::endl;
			return false;
			}
		else
			return QVPlot::linkUnspecifiedInputProperty(block, sourcePropName, linkType);
		}
	else
		return false;
	}

QStringList QVNumericPlot::getPropertyCurvNames(QString property) const
	{
	return (QStringList() << property);
	}

QList<double> QVNumericPlot::getPropertyCurvValues(QString property) const
	{
	//int propType = getPropertyType(property);

	QList<double> value;
	if (isType<int>(property))
	//if (propType == QVariant::Int)
		value << getPropertyValue<int>(property);
	else if (isType<double>(property))
	//else if (propType == QVariant::Double)
		value << getPropertyValue<double>(property);
	else if (isType<uChar>(property))
		value << getPropertyValue<uChar>(property);

	return value;
	}

QList<int> QVNumericPlot::getPropertyCurvOrders(QString) const
	{
	QList<int> order;
	return (order << 1);
	}

