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

#include <QVSynchronizerBlock>

bool QVSynchronizer::linkProperty(QString sourcePropName, QVPropertyContainer *destinyContainer, QString destinyPropName, LinkType linkType)
	{
	return QVPropertyContainer::linkProperty(sourcePropName, destinyContainer, destinyPropName, linkType);
	}

bool QVSynchronizer::linkProperty(QString sourcePropertyName, QVPropertyContainer &destinyContainer, QString destinyPropertyName, LinkType linkType)
	{
	return linkProperty(sourcePropertyName, &destinyContainer, destinyPropertyName, linkType);
	}

bool QVSynchronizer::linkProperty(QVPropertyContainer *destCont, QString propName, LinkType linkType)
	{
	if (linkType == QVProcessingBlock::SynchronousLink) {
		addPropertyFromQVariant(propName, inputFlag | outputFlag, destCont->getPropertyQVariantValue(propName), destCont->getPropertyInfo(propName));
		return QVPropertyContainer::linkProperty(propName, destCont, propName, linkType);
		}
	else {
		std::cerr << "ERROR: QVSychronizer::linkProperty(): a QVSychronizer new link must be Synchronous" << std::endl;
		return FALSE;
		}
	}

bool QVSynchronizer::linkProperty(QVPropertyContainer &destinyContainer, QString destinyPropertyName, LinkType linkType)
	{
	return linkProperty(&destinyContainer, destinyPropertyName, linkType);
	}

bool QVSynchronizer::linkProperty(QString sourcePropName, QVPropertyContainer *destinyContainer, LinkType linkType)
	{
	return QVPropertyContainer::linkProperty(sourcePropName, destinyContainer, linkType);
	}

bool QVSynchronizer::linkProperty(QString sourcePropertyName, QVPropertyContainer &destinyContainer, LinkType linkType)
	{
	return linkProperty(sourcePropertyName, &destinyContainer, linkType);
	}

void QVSynchronizer::linkProperty(QVPropertyContainer *, LinkType)
	{
	std::cerr << "ERROR: QVSychronizer::linkProperty(): a QVSychronizer has not output properties to be linked" << std::endl;
	}

void QVSynchronizer::linkProperty(QVPropertyContainer &container, LinkType linkType)
	{
	linkProperty(&container, linkType);
	}

bool QVSynchronizer::unlinkProperty(QString origName, QVPropertyContainer *destCont, QString destName)
	{
	return QVPropertyContainer::unlinkProperty(origName, destCont, destName);
	}

bool QVSynchronizer::unlinkProperty(QString origName, QVPropertyContainer &destCont, QString destName)
	{
	return unlinkProperty(origName, &destCont, destName);
	}

bool QVSynchronizer::linkUnspecifiedInputProperty(QVPropertyContainer *sourceCont, QString propName, LinkType linkType)
	{
	if (linkType == QVProcessingBlock::SynchronousLink) {
		addPropertyFromQVariant(propName, inputFlag | outputFlag, sourceCont->getPropertyQVariantValue(propName), sourceCont->getPropertyInfo(propName));
		return sourceCont->linkProperty(propName, this, propName, linkType);
		}
	else {
		std::cerr << "ERROR: QVSychronizer::linkProperty(): a QVSychronizer new link must be Synchronous" << std::endl;
		return FALSE;
		}
	}

bool QVSynchronizer::treatUnlinkInputProperty(QString destPropName, QVPropertyContainer *, QString sourcePropName)
	{
	if ( (destPropName != "max block iterations") && (destPropName != "stats enabled") && (destPropName != "cpu stats") )
		removeProperty(sourcePropName);

	return true;
	}

