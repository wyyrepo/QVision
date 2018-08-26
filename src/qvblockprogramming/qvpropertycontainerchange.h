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

#ifndef QVPROPERTYCONTAINERCHANGE_H
#define QVPROPERTYCONTAINERCHANGE_H

#ifndef DOXYGEN_IGNORE_THIS
#include <QObject>
#include <QVariant>

/*!
@class QVPropertyContainerChange qvblockprogramming/qvpropertycontainerchange.h QVPropertyContainerChange
@brief Base class for property container object's changes.

This class represents a property container change, indicating the type and some parameters to locate it (depending of the type).

For further information about them, see section @ref QVPropertyContainer.

@ingroup qvblockprogramming
*/
class QVPropertyContainerChange : public QObject
{
Q_OBJECT

public:
    /// @brief Semantics for a change type of a QVPropertyContainer.
    ///
    /// None: there are no change, for default constructor.
    /// Name: has changed only the name of the property container.
    // / ContainerAdd: a container has been add.
    /// ContainerDel: a container has been delete.
    /// PropertyAdd: a property has been add.
    /// PropertyDel: a property has been delete.
    /// PropertyValue: has changed a property value.
    /// PropertiesValues: has changed all properties values (in a readInputProperties).
    /// LinkAdd: a Link has been add, the link can be a input or a output link.
    /// LinkDel: a Link has been delete, the link can be a input or a output link.
    /// All: it should been changed all the property container, when a property container has been copied from other.
    ///
    typedef enum {None, Name, /*ContainerAdd, */ContainerDel, PropertyAdd, PropertyDel, PropertyValue, PropertiesValues, LinkAdd, LinkDel, All} ChangeType;

    /// @brief Constructs a None type QVPropertyContainerChange.
    ///
    QVPropertyContainerChange():
            QObject(), sourceName(""), origName(""), destName(""), sourceId(0), origId(0), destId(0), changeType(None), propName(""), destPropName(""),
            sinchronous(FALSE), sequential(FALSE), value()
        { }

    /// @brief Copy constructor.
    ///
    /// @param other property container's change to be copied.
    ///
    QVPropertyContainerChange(const QVPropertyContainerChange &other):
            QObject(), sourceName(other.sourceName), origName(other.origName), destName(other.destName), sourceId(other.sourceId), origId(other.origId),
            destId(other.destId), changeType(other.changeType), propName(other.propName), destPropName(other.destPropName), sinchronous(other.sinchronous),
            sequential(other.sequential), value(other.value)
        { }

    /// @brief Constructs a simple QVPropertyContainerChange.
    ///
    /// Constructs a simple QVPropertyContainerChange, with a property name value (for PropertyAdd, PropertyDel or PropertyValue changes)
    /// or without values (for None, Name or All changes).
    ///
    /// @param source The QVPropertyContainer changed's name.
    /// @param id The QVPropertyContainer changed's id.
    /// @param type Type of the new QVPropertyContainerChange.
    /// @param prop Name of the property changed, added or removed.
    /// @param prop The new value of the property changed.
    ///
    QVPropertyContainerChange(	const QString source,
                                const uint id,
                                const ChangeType type,
                                const QString prop = QString(),
                                const QVariant variant = QVariant()):
            QObject(), sourceName(source), origName(""), destName(""), sourceId(id), origId(0), destId(0), changeType(type), propName(prop), destPropName(""),
            sinchronous(FALSE), sequential(FALSE), value(variant)
        { }

    /// @brief Constructs a Link QVPropertyContainerChange.
    ///
    /// Constructs a Link QVPropertyContainerChange, used to set the linkAdd or LinkDel change values.
    ///
    /// @param source The QVPropertyContainer changed's name.
    /// @param id The QVPropertyContainer changed's id.
    /// @param type Type of the new QVPropertyContainerChange.
    /// @param contOrig The source QVPropertyContainer's name.
    /// @param contOrigId The source QVPropertyContainer's id.
    /// @param propOrig Name of the origin property changed.
    /// @param contDest The destiny QVPropertyContainer's name.
    /// @param contDestId The destiny QVPropertyContainer's id.
    /// @param propDest Name of the destiny property.
    /// @param sinc Indicates if the link is Synchronous (if not is Asynchronous).
    /// @param sequ Indicates if the link is Sequential (if is sequential the "sinc" value must be ignorate).
    ///
    QVPropertyContainerChange(	const QString source,
                                const uint id,
                                const ChangeType type,
                                const QString contOrig,
                                const uint contOrigId,
                                const QString propOrig,
                                const QString contDest,
                                const uint contDestId,
                                const QString propDest,
                                const bool sinc = FALSE,
                                const bool sequ = FALSE):
            QObject(), sourceName(source), origName(contOrig), destName(contDest), sourceId(id), origId(contOrigId), destId(contDestId), changeType(type),
            propName(propOrig), destPropName(propDest), sinchronous(sinc), sequential(sequ), value()
        { }


    /// @brief Retrieves the name of the object changed.
    /// @return QString name of the object changed.
    ///
    const QString getSourceName() const { return sourceName; }

    /// @brief Retrieves the name of the link's origin object if it is of Link type.
    /// @return QString name of the link's origin object.
    ///
    const QString getOrigName() const { return origName; }

    /// @brief Retrieves the name of the link's destiny object if it is of Link type.
    /// @return QString name of the link's destiny object.
    ///
    const QString getDestName() const { return destName; }

    /// @brief Retrieves the identification number of the object changed.
    /// @return QString identification number of the object changed.
    ///
    uint getSourceId() const { return sourceId; }

    /// @brief Retrieves the identification number of the link's origin object if it is of Link type.
    /// @return QString identification number of the link's origin object.
    ///
    uint getOrigId() const { return origId; }

    /// @brief Retrieves the identification number of the link's destiny object if it is of Link type.
    /// @return QString identification number of the link's destiny object.
    ///
    uint getDestId() const { return destId; }

    /// @brief Retrieves the type of the change: None, Name, Property, Link or All.
    /// @return ChangeType the type of the change.
    ///
    ChangeType getChangeType() const { return changeType; }

    /// @brief Retrieves the name of the property changed if it is of Property type.
    /// @return QString the name of the property changed.
    ///
    const QString getPropName() const { return propName; }

    /// @brief Retrieves the name of the origin property if it is of Link type.
    /// @return QString the name of the origin property.
    ///
    const QString getOrigProp() const { return propName; }

    /// @brief Retrieves the name of the destiny property if it is of Link type.
    /// @return QString the name of the destiny property.
    ///
    const QString getDestProp() const { return destPropName; }

    /// @brief Retrieves the value of the property changed if it is of PropertyValue type.
    /// @return QVariant the value of the property changed.
    ///
    const QVariant getValue() const { return value; }

    /// @brief Retrieves if the link is sinchronous.
    /// @return bool if the link is sinchronous (if not is Asynchronous).
    ///
    bool isSinc() const { return sinchronous; }

    /// @brief Retrieves if the link is sequential.
    /// @return bool if the link is sequential.
    ///
    bool isSequ() const { return sequential; }

    /// @brief Retrieves a QVPropertyContainerChange's description.
    /// @return QString the QVPropertyContainerChange's description.
    ///
    QString toString() const;


private:
    const QString sourceName, origName, destName;
    uint sourceId, origId, destId;
    const ChangeType changeType;
    const QString propName, destPropName;
    const bool sinchronous;
    const bool sequential;
    const QVariant value;

};

#endif

#endif

