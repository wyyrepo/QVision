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

#ifndef QVPROPERTYHOLDER_H
#define QVPROPERTYHOLDER_H

#include <QStringList>
#include <QVariant>
#include <QRegExp>
#include <QSet>
#include <QReadWriteLock>
#include <QSemaphore>
#include <QDebug>
#include <QVPropertyContainerChange>

#include <iostream>
#include <QVApplication>

#ifndef DOXYGEN_IGNORE_THIS
/*!
@class QVPropertyContainerInformer qvblockprogramming/qvpropertycontainer.h QVPropertyContainerInformer
@brief Class for inform about the QVPropertyContainer changes.

The QVPropertyContainerInformer emits the signals changed(QVPropertyContainerChange) instead of the QVPropertyContainer, because QVPropertyContainer can't inherit of QObjet.

@todo ¿La señal 'changed' no debería estar en el propio property container? ¿Porqué está separada? Preguntar a Antonio.
@ingroup qvblockprogramming
*/
class QVPropertyContainerInformer : public QObject
    {
        Q_OBJECT
        public:
            /// @brief Emit the signal changed whith the current change.
            ///
            /// @param change Type of change done.
            void emitChange(QVPropertyContainerChange change) {
                emit changed(change);
            }
        signals:
            /// @brief Signal emited when the property container id changed.
            ///
            /// @param change Type of change done.
            void changed(QVPropertyContainerChange change);
    };

#endif

/*!
@class QVPropertyContainer
@brief Base class for dynamic property container objects.

This is the parent class for any object in the QVision framework capable of containing or sharing values through the use of dynamic properties. This class offers methods to register new properties, update and obtain the contained value, and retrieve listings of dynamic property identifiers and types contained in the object, amongst other things.

This class emits "changed" signals when it is changed (change the container name or a property value, add/remove a property, add/remove a link, or copy from other QVPropertyContainer). In each signal emited it passes a QVPropertyContainerChange indicating the type and position of the change, in order to let include observer objects for the property containers structure.

It has a static global informer, that can be get with getGlobalInformer(), that emits "changed" signals when a QVPropertyContainer is created or destroyed.

For further information about them, see section @ref CreatingCustomProcessingBlocks.

@ingroup qvblockprogramming
*/
class QVPropertyContainer
    {

    public:
        /// @brief Semantics for a link between QVPropertyContainers.
        ///
        /// If a link between a source property of a QVPropertyContainer object A
        /// and a corresponding destination property of another one B is
        /// declared as synchronous, it means that every time that the
        /// readInputProperties() method is executed on B, the system assures
        /// that one (and just one) corresponding call to the
        /// writeOutputProperties() has been previously executed on A.
        /// In the (common) case of a link between two QVThread's, that would
        /// mean, for example, that each running of the source QVThread
        /// corresponds exactly to another (posterior) running of the
        /// destination QVThread.
        ///
        /// That is equivalent to say that every data produced by the source is
        /// always consumed by the destination, so no data is ever "lost" in
        /// that sense. The obvious cost is that both threads will have to run
        /// at the speed of the slowest, of course.
        ///
        /// An alternative is an asynchronous link, in which the only thing
        /// that the system assures on the properties read by the destination
        /// is that, in the case of a multiple link (several input properties
        /// of B connected to several corresponding output properties of B), all
        /// of them correspond to the same iteration of the source (more
        /// precisely, to the last execution of the writeOutputProperties()
        /// method in A, independently of the specific sequence number of that
        /// iteration). We say that the output is 'coherent' in all the
        /// properties linked this way. But, as has been already said,
        /// the iterations are not linked in the temporal sense, so, for
        /// example, for the case of QVThreads, both could run asynchronously,
        /// and at different speeds.
        ///
        /// Other alternative is an sequential link, in witch the system assures nothing
        /// because the two QVPropertyContainer will be in the same thread and will be
        /// executed in a secuencial mode.
        /// When a group of QVPropertyContainers are linked whith sequential link, they
        /// choose a master QVPropertyContainer and the others have a reference to it.
        /// In this case the QVApplication will not create threads for the no-master
        /// QVPropertyContainer, and if they are QVProcessingBlocks they will be moved and executed
        /// by his master's thread.
        ///
        /// See also the QVPropertyContainer::linkProperty() method.
        typedef enum {AsynchronousLink,SynchronousLink,SequentialLink} LinkType;

        /// @brief Flags for each property.
        ///
        /// Currently, if a property is of the "input type" and/or "output type"
        /// are the only supported flags.
        typedef enum {noInputOutputFlag=0x0,inputFlag=0x1,outputFlag=0x2, guiInvisible=0x4, internalProp=0x8} PropertyFlag;
        Q_DECLARE_FLAGS(PropertyFlags, PropertyFlag)

        #ifndef DOXYGEN_IGNORE_THIS
        typedef enum {noLinkFlag=0x0,linkedInputFlag=0x1,linkedOutputFlag=0x2} PropertyLinkFlag;
        Q_DECLARE_FLAGS(PropertyLinkFlags, PropertyLinkFlag)
        #endif

        /// @brief Constructs a QVPropertyContainer with a given string identifier.
        ///
        /// @param name Identifier for the object to be created.
        QVPropertyContainer(const QString name = QString());

        /// @brief Copy constructor.
        ///
        /// @param cont property container to be copied.
        QVPropertyContainer(const QVPropertyContainer &cont);

        /// @brief Copy operator.
        ///
        /// @param cont property container to be copied.
        QVPropertyContainer & operator=(const QVPropertyContainer &cont);

        /// @brief Virtual destructor.
        ///
        /// Frees the QVPropertyContainer, and all its associated links. Besides,
        /// this destructor can (and in many cases should!) also be
        /// reimplemented in subclasses.
        virtual ~QVPropertyContainer();

        /// @brief Sets a new string identifier for a QVPropertyContainer.
        ///
        /// @param name New string identifier for the object.
        void setName(const QString name);

        /// @brief Retrieves identifier QString of the object.
        /// @return QString identifying the property holder object.
        const QString getName() const;

        /// @brief Retrieves identifier uint of the object.
        /// @return uint identifying the property holder object, begining to 1.
        uint getId() const;

        /// @brief Compare operator.
        ///
        /// Compare the PropertyContainers id;
        ///
        /// @param cont property container to be compared.
        bool operator==(const QVPropertyContainer &cont) const;

        /// @brief Gets list of properties of the QVPropertyContainer.
        ///
        /// Retrieves the names of the properties registered in the property
        /// holder, in a QStringList.
        /// @return QStringList of names of properties in the object.
        QList<QString> getPropertyList() const;

        /// @brief Gets the names of the properties of a given type.
        ///
        /// Retrieves the names of those properties, registered in the property
        /// holder, which hold values of the type given by the template
        /// parameter, in a QStringList.
        /// @return QList of identifying QStrings.
        template <class Type> QList<QString> getPropertyListByType() const
            {
            QList<QString> result;
            QList<QString> names = variants.keys();

            for(QList<QString>::iterator i = names.begin();i != names.end();++i)
                if(isType<Type>(*i))
                    result.append(*i);

            return result;
            }

        /// @brief Checks if a property is of a given type.
        ///
        /// Returns true if type passed as template parameter equals type
        /// of value contained in a property.
        /// @param name QString identifying the property.
        /// @param ok Pointer to bool value which is set to true if property
        ///           exists, and to false otherwise.
        /// @return True if property has same type as parameter template.
        template <class Type> bool isType(QString name,bool *ok = NULL) const
            {
            if(not checkExists(name,"QVPropertyContainer::propertyIsType()"))
                {
                if(ok != NULL) *ok = FALSE;
                return FALSE;
                }
            if(ok != NULL) *ok = TRUE;
            QVariant::Type type = QVariant::fromValue(Type()).type();
            if ((type != QVariant::UserType) && (variants[name].type() == type))
                return TRUE;
            if (variants[name].userType() == QVariant::fromValue(Type()).userType())
                return TRUE;
            return FALSE;
            }

        /// @brief Check whether the property holder has a given property.
        /// @param name QString identifying the property.
        /// @return True if the QVPropertyContainer contains a property with the
        ///         given name, otherwise returns false.
        bool containsProperty(const QString name) const;

        /// @brief Given a property identifying QString (see getPropertyList()
        ///        function above), returns the type of the property.
        /// @param name QString identifying the property.
        /// @param ok Pointer to bool value which is set to true if property
        ///           exists, and to false otherwise.
        /// @return a <a href="http://doc.trolltech.com/qtopia4.2/qvariant.html#Type-enum">QVariant::Type</a>
        /// value. Note that user defined properties will return value.
        int getPropertyType(const QString name, bool *ok = NULL) const;

        /// @brief Registers a new property in the property holder.
        ///
        /// @param name Name of the new property.
        /// @param value Initial value for the property.
        /// @param info Info string for the property.
        /// @param flags Whether the property is input, output, or both.
        /// @return True if property was correctly added, false otherwise.
        template <class Type> bool addProperty(const QString name,
            const PropertyFlags flags = inputFlag,
            const Type & value = Type(), const QString info = QString("(Info not available)"))
            {
            if (addPropertyFromQVariant(name, flags, QVariant::fromValue(value), info))
                setPropertyFromArguments<Type>(name);
            else
                return FALSE;

            return TRUE;
            }

        /// @brief Registers a new property in the property holder.
        ///
        /// @param name Name of the new property.
        /// @param value Initial value for the property.
        /// @param info Info string for the property.
        /// @param flags Whether the property is input, output, or both.
        /// @param minValue Minimum value for the property.
        /// @param maxValue Maximum value for the property.
        /// @return True if property was correctly added, false otherwise.
        template <class Type> bool addProperty(const QString name,
            const PropertyFlags flags,
            const Type & value, const QString info,
            const Type & minValue, const Type & maxValue)
            {
            if (addProperty<Type>(name, flags, value, info))
                setPropertyRange<Type>(name, minValue, maxValue);
            else
                return FALSE;

            return TRUE;
            }

        /// @brief Registers a new property in the property holder.
        ///
        /// @param name Name of the new property.
        /// @param flags Whether the property is input, output, or both.
        /// @param variant Initial QVariant value for the property
        /// @param info Info string for the property.
        /// @return True if property was correctly added, false otherwise.
        bool addPropertyFromQVariant(const QString &name, const PropertyFlags flags, QVariant variant, const QString info)
            {
            //qDebug() << "PEO adding property" << name << "to container" << getName();
            if(not checkIsNewProperty(name,"QVPropertyContainer::addProperty()"))
                return FALSE;
            insertion_order.push_back(name);
            //qDebug() << "PEO insertion_order after new property " << name << "->" << insertion_order;
            _info[name] = info;
            io_flags[name] = flags;
            link_flags[name] = noLinkFlag;

            variants[name] = variant;

            informer.emitChange(QVPropertyContainerChange(this->getName(), this->getId(), QVPropertyContainerChange::PropertyAdd, name));
            return TRUE;
            }

        /// @brief De-registers a property in the property holder.
        ///
        /// @param name Name of the property to delete.
        /// @return True if property was correctly removed, false otherwise.
        bool removeProperty(const QString name);

/*		/// \deprecated Should set range in the constructor.
        bool setPropertyRange(const QString name, const double & minimum, const double & maximum);

        /// \deprecated Should set range in the constructor.
        bool setPropertyRange(QString name, int & minimum, int & maximum); */

        /// @brief Tells if a range has been set for the property.
        ///
        /// @param name Name of the property.
        /// @return True if there exist a range for the property.
        bool hasRange(const QString name) const;

        /// @brief Returns flags for a property
        ///
        /// @param name Name of the property.
        /// @return Flags for the property.
        PropertyFlags getPropertyFlags(const QString name) const { return io_flags[name]; }

        /// @brief Tells if a property is of the input type.
        ///
        /// @param name Name of the property.
        /// @return True if the property is of the input type.
        bool isInput(const QString name) const;

        /// @brief Tells if a property is of the output type.
        ///
        /// @param name Name of the property.
        /// @return True if the property is of the output type.
        bool isOutput(const QString name) const;

        /// @brief Tells if a property can be modified through the GUI.
        ///
        /// @param name Name of the property.
        /// @return True if the property will not be visible and editable through the GUI.
        bool isGUIInvisible(const QString name) const;

        /// @brief Tells if a property is of the input type and is linked.
        ///
        /// @param name Name of the property.
        /// @return True if the property is of the input type and is linked.
        bool isLinkedInput(const QString name) const;

        /// @brief Tells if a property is of the output type and is linked.
        ///
        /// @param name Name of the property.
        /// @return True if the property is of the output type and is linked.
        bool isLinkedOutput(const QString name) const;

        /// @brief Sets value for property.
        ///
        /// If the property is not writable, this function will return false,
        /// and won't change property value. Besides, if there is a
        /// [minimum,maximum] range and the value is not in it, also fails to
        /// set the value. In both cases the function issues a warning through
        /// stderr, and returns false.
        /// @param name Identifying QString for the property.
        /// @param value Value to set the property with.
        /// @return True if the value was set successfully.
        template <class Type> bool setPropertyValue(const QString name, const Type &value)
            {
            if(not checkExists(name,"QVPropertyContainer::setPropertyValue()"))
                return FALSE;
            else if (not correctRange(name,value))
                return FALSE;
            else {
                QVariant variant =  QVariant::fromValue<Type>(value);
                variants[name] = variant;

                informer.emitChange(QVPropertyContainerChange(this->getName(), this->getId(), QVPropertyContainerChange::PropertyValue, name, variant));
                return TRUE;
                }
            }

        /// @brief Method to get the actual value of a property.
        ///
        /// @param name Identifying QString for the property.
        /// @param ok Pointer to bool value which is set to true if property
        ///           exists, and to false otherwise.
        /// @return Actual value for the property.
        template <class Type> Type getPropertyValue(const QString name, bool *ok = NULL) const
            {
            if (not checkExists(name,"QVPropertyContainer::getPropertyValue()")) {
                if(ok != NULL) *ok = FALSE;
            } else {
                if(ok != NULL) *ok = TRUE;
            }
            return variants[name].value<Type>();
            }

        /// @brief Method to get the value of a property as a QVariant.
        ///
        /// @param name Identifying QString for the property.
        /// @param ok Pointer to bool value which is set to true if property
        ///           exists, and to false otherwise.
        /// @return Actual value for the property.
        QVariant getPropertyQVariantValue(const QString name, bool *ok = NULL) const;

        /// @brief Method to get the maximum value for a property.
        ///
        /// @param name Identifying QString for the property.
        /// @param ok Pointer to bool value which is set to true if property
        ///           exists, and to false otherwise.
        /// @return Maximum value for the property.
        template <class Type> Type getPropertyMaximum(const QString name, bool *ok = NULL) const
            {
            if(not checkExists(name,"QVPropertyContainer::getPropertyMaximum()")) {
                if(ok != NULL) *ok = FALSE;
            } else if(not maximum.contains(name) and not minimum.contains(name))
                {
                QString str = QString("QVPropertyContainer::getPropertyMaximum():")
                              + QString(" property ") + name
                              + QString(" has no maximum value in ")
                              + QString("holder ") + getName() + QString(".");
                setLastError(str);
                if(qvApp->isRunning()) {
                    std::cerr << qPrintable("Warning: " + str + "\n");
                } // Otherwise, qApp will show the error and won't start the program.
                if(ok != NULL) *ok = FALSE;
                }
            else
                if(ok != NULL) *ok = TRUE;
            return maximum[name].value<Type>();
            }

        /// @brief Method to get the minimum value for a property.
        ///
        /// @param name Identifying QString for the property.
        /// @param ok Pointer to bool value which is set to true if property
        ///           exists, and to false otherwise.
        /// @return Minimum value for the property.
        template <class Type> Type getPropertyMinimum(const QString name, bool *ok = NULL) const
            {
            if(not checkExists(name,"QVPropertyContainer::getPropertyMinimum()")) {
                if(ok != NULL) *ok = FALSE;
            } else if(not maximum.contains(name) and not minimum.contains(name))
                {
                QString str = QString("QVPropertyContainer::getPropertyMinimum():")
                              + QString(" property ") + name
                              + QString(" has no minimum value in ")
                              + QString("holder ") + getName() + QString(".");
                setLastError(str);
                if(qvApp->isRunning()) {
                    std::cerr << qPrintable("Warning: " + str + "\n");
                } // Otherwise, qApp will show the error and won't start the program.
                if(ok != NULL) *ok = FALSE;
                }
            else
                if(ok != NULL) *ok = TRUE;
            return minimum[name].value<Type>();
            }

        /// @brief Method to get the info QString for int typed property.
        ///
        /// @param name Identifying QString for the property.
        /// @param ok Pointer to bool value which is set to true if property
        ///           exists, and to false otherwise.
        /// @return The info QString about the property, if defined. Empty
        ///         QString otherwise.
        QString getPropertyInfo(const QString name, bool *ok = NULL) const;

        /// @brief Gets the (possible) last error string.
        ///
        /// @return A QString indicating the last error that occurred in an
        ///         operation on the the property, if defined. Empty QString
        ///         otherwise.
        QString getLastError() const;

        /// @brief Formatted description of properties (useful to show help).
        ///
        /// Obtains a human readable description QString of all the object's
        /// properties that have some associated info (otherwise they are
        /// ignored).
        /// @return QString containing human readable list of properties, and
        ///         info about them.
        const QString infoInputProperties() const;

        /// @brief Links properties among QVPropertyContainer's.
        ///
        /// This method safely links properties among property holders in a
        /// thread safe manner. It is mainly used when programming
        /// multithreaded applications -with multiple QVProcessingBlocks-, but also, for
        /// example, when linking blocks (running in an independent thread)
        /// with GUI widgets (running in the main thread).
        ///
        /// The pointer this corresponds to the source QVPropertyContainer.
        ///
        /// See also QVPropertyContainer::LinkType.
        /// @param sourcePropName Identifying QString for the source property.
        /// @param destinyContainer Pointer to the destination QVPropertyContainer.
        /// @param destinyPropName Identifying QString for the destination property.
        /// @param linkType Synchronous or asynchronous.
        /// @return TRUE if the connection went OK, FALSE otherwise (for example,
        /// due to type mismatch, some of the properties does not exists, or
        /// whatever).
        virtual bool linkProperty(QString sourcePropName, QVPropertyContainer *destinyContainer, QString destinyPropName, LinkType linkType = AsynchronousLink);
        virtual bool linkProperty(QString sourcePropName, QVPropertyContainer &destinyContainer, QString destinyPropName, LinkType linkType = AsynchronousLink);
        virtual bool linkProperty(QVPropertyContainer *destinyContainer, QString destinyPropName, LinkType linkType = AsynchronousLink);
        virtual bool linkProperty(QVPropertyContainer &destinyContainer, QString destinyPropName, LinkType linkType = AsynchronousLink);
        virtual bool linkProperty(QString sourcePropName, QVPropertyContainer *destinyContainer, LinkType linkType = AsynchronousLink);
        virtual bool linkProperty(QString sourcePropName, QVPropertyContainer &destinyContainer, LinkType linkType = AsynchronousLink);

        /// @brief Links properties among QVPropertyContainer's.
        ///
        /// This method safely links all input properties from a container with the same
        /// name and type output current container's properties, holders in a
        /// thread safe manner. It is mainly used when programming
        /// multithreaded applications -with multiple QVProcessingBlocks-, but also, for
        /// example, when linking blocks (running in an independent thread)
        /// with GUI widgets (running in the main thread).
        ///
        /// @param container Pointer to the destination QVPropertyContainer.
        /// @param linkType Synchronous or asynchronous.
        virtual void linkProperty(QVPropertyContainer *container, LinkType linkType = AsynchronousLink);
        virtual void linkProperty(QVPropertyContainer &container, LinkType linkType = AsynchronousLink);

        /// @brief Unlinks properties among QVPropertyContainer's.
        ///
        /// This method safely ulinks properties among property holders in a
        /// thread safe manner.
        ///
        /// The pointer this corresponds to the source QVPropertyContainer.
        ///
        /// See also QVPropertyContainer::LinkType.
        /// @param origName Identifying QString for the source property.
        /// @param destCont Pointer to the destination QVPropertyContainer.
        /// @param destName Identifying QString for the destination property.
        /// @return TRUE if the disconnection went OK, FALSE otherwise (for example,
        /// due to type mismatch, some of the properties does not exists, or
        /// whatever).
        virtual bool unlinkProperty(QString origName, QVPropertyContainer *destCont, QString destName);
        virtual bool unlinkProperty(QString origName, QVPropertyContainer &destCont, QString destName);

        /// @brief Completely unlinks a property holder.
        ///
        /// Deletes all the input and output links associated to the holder.
        /// Of course, all the corresponding necessary unlinks in other property
        /// holders are also performed.
        virtual void unlink();

        /// @brief Check if a group of QVPropertyContainers are synchronously or Sequentialy linked.
        ///
        /// Check if a group of QVPropertyContainers are synchronously or Sequentialy linked.
        /// @param containers List of QVPropertyContainer to be Checked.
        static bool areSynchronized(const QList<QVPropertyContainer *> containers);

        /// @brief Gets the QVPropertyContainerInformer.
        ///
        /// The QVPropertyContainerInformer is the object in charge of emit the changes of the QVPropertyContainer.
        ///
        /// @return the QVPropertyContainerInformer.
        QVPropertyContainerInformer *getInformer() { return &informer; }

/*		/// @brief Gets the global QVPropertyContainerInformer.
        ///
        /// The QVPropertyContainerInformer is the object in charge of emit the changes of the QVPropertyContainer's environment,
        /// like a QVPropertyContainer contruction or a QVPropertyContainer destruction.
        ///
        /// @return the QVPropertyContainerInformer.
        static QVPropertyContainerInformer *getGlobalInformer() { return &globalInformer; } */

        /// @brief Gets the source QVPropertyContainer of a given property.
        ///
        /// @param name Name of the property.
        /// @return The source QVPropertyContainer, NULL if is not linked.
        QVPropertyContainer *getSourceContainer(const QString name) const;

        /// @brief Gets the destiny QVPropertyContainers of a given property.
        ///
        /// @param name Name of the property.
        /// @return The destiny QVPropertyContainers, a empty list if is not linked.
        QList<QVPropertyContainer *> getDestinyContainers(const QString name) const;

        /// @brief Gets the source property name of a given property.
        ///
        /// @param name Name of the property.
        /// @return The source property name, a void QString if is not linked.
        QString getSourceProperty(const QString name) const;

        /// @brief Check if a property is linked syncronously.
        ///
        /// @param name Name of the property.
        /// @return TRUE if a property is linked synchronously, FALSE if is not linked.
        bool isSynchronous(const QString name) const;

        /// @brief Check if a property is linked Sequentialy.
        ///
        /// @param name Name of the property.
        /// @return TRUE if a property is linked Sequentialy, FALSE if is not linked.
        bool isSequential(const QString name) const;

        #ifndef DOXYGEN_IGNORE_THIS
        virtual bool linkUnspecifiedInputProperty(QVPropertyContainer *sourceContainer, QString sourcePropName, LinkType linkType = AsynchronousLink);
        virtual bool linkUnspecifiedOutputProperty(QVPropertyContainer *destContainer, QString destPropName, LinkType linkType = AsynchronousLink);
        virtual bool treatUnlinkInputProperty(QString destPropName, QVPropertyContainer *sourceCont, QString sourcePropName);
        #endif

        bool isSequentialGroupMaster() const	{ return master == this; }
        QVPropertyContainer *getMaster() const { return master; }

    protected:
        /// @brief Read linked input properties from other QVPropertyContainer's.
        ///
        /// This is a protected function that should be called from the
        /// subclasses of QVPropertyContainer just before starting to use any
        /// input property linked to another property holder (for
        /// example, just before the iterate() function in a QVProcessingBlock, or just
        /// before the viewer() function in a QVCanvas).
        void readInputProperties();

        /// @brief Write linked output properties to other QVPropertyContainer's.
        ///
        /// This is a protected function that should be called from the
        /// subclasses of QVPropertyContainer just after having a new set of
        /// output properties ready to be read by another property holder (for
        /// example, just after the iterate() function in a QVProcessingBlock, or just
        /// after the viewer() function in a QVCanvas). The effect is that
        /// a coherent state of the linked output properties is saved, so
        /// other QVPropertyContainer's can safely read from it -while we can
        /// be writing new values corresponding to a new iteration-.
        void writeOutputProperties();

        /// @brief Parses a property value from a string.
        ///
        /// Parses a QString containing the value for a property (mainly useful
        /// when initializing it from the command line). QVPropertyContainer
        /// implements a series of default parsers (namely for bool, int, double
        /// and QString properties). But the method is templatized to allow
        /// customization of the parsed QString, if we wish to add new parameter
        /// types in the subclasses. In that case, users should specialize
        /// the corresponding template this way:\n
        /// \code
        /// template <> bool MyDerivedQVPropertyContainer::parseArgument<MyType>(const QString parameter, const QString value)
        /// {
        ///     bool ok;
        ///     MyType myVar1 = myParserForMyType1(value,&ok);
        ///     if(ok) { // parsing OK
        ///          setPropertyValue<MyType>(parameter,myVar1);
        ///          return TRUE;
        ///     } else { // parsing failed
        ///          QString errorString = "MyDerivedQVPropertyContainer::parseArgument(): holder "
        ///          + getName() + ": value " + value
        ///          + " is not a valid MyType value for parameter " + parameter + ".\n";
        ///          setLastError(errorString);
        ///          return FALSE;
        ///     }
        /// }
        /// \endcode
        /// The format of the input params in the command line should be the
        /// following: \n
        ///	\c --[holder:]\<name\>=\<value\>
        /// \n where
        ///	- \b holder is the (optional) name of the property holder.
        ///	- \b name is the name of the property.
        ///	- \b value is the value to initialize the property.
        /// @param parameter The name of the property to be set.
        /// @param value QString from which to obtain the value.
        ///
        /// If the optional holder name is not present, any holder which has
        /// a property with name 'name' is assigned the corresponding parsed
        /// value.
        template <class Type> bool parseArgument(const QString parameter, const QString value);

        /// @brief Sets an error string message.
        ///
        /// Sets an error string message corresponding to the last error that
        /// occurred in an operation on the QVPropertyContainer (if such an error
        /// occurred). If no error occurred since the creation of the object,
        /// the string will be empty. The method is const because it only
        /// modifies the error message (which is mutable), not the object
        /// itself.
        void setLastError(QString str) const;

        /// @brief Obtains the origin block's id of a input property.
        ///
        /// Obtains the origin block's id of a input property.
        /// @return Block's id if exist the property, or 0 if not.
        uint inputPropertyBlock(QString prop) const
            {
            if (inputLinks.contains(prop))
                return inputLinks[prop]->qvp_orig->getId();
            else
                return 0;
            }


        QVPropertyContainerInformer informer;

        // the group of slaves QVPropertyContainer, sorts by level of deep, in witch it is its master
        QList<QList<QVPropertyContainer *> > slavesByLevel;

    //protected:

    private:
        QString name;
        uint ident;
        mutable QString errorString;
        QMap<QString, QVariant> variants,safelyCopiedVariants;
        QMap<QString, QVariant> minimum, maximum;
        QMap<QString, QString> _info;
        QMap<QString, PropertyFlags> io_flags;
        QMap<QString, PropertyLinkFlags> link_flags;
        QList<QString> insertion_order;

        static uint maxIdent;
        static uint getNewIdent() { return ++maxIdent; }
// 		static QVPropertyContainerInformer globalInformer;

        QReadWriteLock RWLock;
        class QVPropertyContainerLink {
          public:
            QVPropertyContainerLink(QVPropertyContainer *_qvp_orig,QString _prop_orig,QVPropertyContainer *_qvp_dest,QString _prop_dest,LinkType _link_type) : qvp_orig(_qvp_orig), prop_orig(_prop_orig), qvp_orig_name(_qvp_orig->getName()), qvp_orig_id(_qvp_orig->getId()), qvp_dest(_qvp_dest), prop_dest(_prop_dest), qvp_dest_name(_qvp_dest->getName()), qvp_dest_id(_qvp_dest->getId()), link_type(_link_type), markedForDeletion(FALSE) {
                // SyncSemaphoreIn value must initially be 1:
                SyncSemaphoreIn.release();
                // SyncSemaphoreOut is simply initialized with 0 (default value).
            };
            QVPropertyContainer *qvp_orig;
            QString prop_orig, qvp_orig_name;
            uint qvp_orig_id;
            QVPropertyContainer *qvp_dest;
            QString prop_dest, qvp_dest_name;
            uint qvp_dest_id;
            LinkType link_type;
            QSemaphore SyncSemaphoreIn,SyncSemaphoreOut;
            bool markedForDeletion;
        };
        QMap<QString, QVPropertyContainerLink* > inputLinks;
        QMap<QString, QList<QVPropertyContainerLink*> > outputLinks;

        const QMap<QString, QVPropertyContainerLink* > getInputLinks() const { return inputLinks; }
        void addInputLink(QString prop_dest, QVPropertyContainerLink *link);
        void toDeleteLink(QVPropertyContainerLink* link);



        QVPropertyContainer *master; // the QVPropertyContainer that have been choose has his master for sequential links (if haven't sequential links itselve)
        int deepLevel; // the sequential links subgraph deep level, 0 for root QVPropertyContainer

        ///////////// functions that management the sequential link (the sequential subgraphs cannot have cicles)
        ////
        // process a posible sequential link, they must be done after the link process. Return false if the link will generate a sequential links cicle
        bool ProcessPosibleSequentialLink(QVPropertyContainer *destCont);
        // Update the current deep level to the maxim of origDeep and its predecessors deep level plus 1. It update its successors too
        void updateDeep(int origDeep);
        // process a sequential unlink, they must be done before the unlink process. They update the masters and deep levels
        void ProcessSequentialUnlink(QVPropertyContainer *origCont, QVPropertyContainer *destCont);
        // Indicate if they have destCont has a sequential precursor (not only a direct sequential preursor)
        bool haveSyncPrecursor(QVPropertyContainer *precursor);
        // Propagate resourcefuly a master change to his predecesors (and they propagate it to his predecesors and successors). The change must be done previously
        void propagateBackwardMasterChange(QVPropertyContainer *newMaster);
        // Propagate resourcefuly a master change to his successors (and they propagate it to his predecesors and successors). The change must be done previously
        void propagateForwardMasterChange(QVPropertyContainer *newMaster);
        // change its master
        void changeMaster(QVPropertyContainer *newMaster);
        // get the list of QVPropertyContainers that has successors of it and have been linked sequentialy
        QList<QVPropertyContainer *> getDestinySequentialContainers(const QString name) const;
        ////
        /////////////


        template <class Type> bool setPropertyRange(const QString name, const Type & minimum, const Type & maximum)
            {
            if(not checkExists(name,"QVPropertyContainer::setPropertyRange()"))
                return FALSE;
            if(minimum <= getPropertyValue<Type>(name) and
                maximum >= getPropertyValue<Type>(name))
                {
                    this->minimum[name] = QVariant::fromValue(minimum);
                    this->maximum[name] = QVariant::fromValue(maximum);
                    return TRUE;
                } else {
                    QString str =  "QVPropertyContainer::setPropertyRange(): property " +
                                   name + " in holder " + getName() + " has value " +
                                   QString("%1").arg(getPropertyValue<Type>(name)) +
                                   ", which is not valid for the range [" +
                                   QString("%1,%2").arg(minimum).arg(maximum) + "]." ;
                    setLastError(str);
                    if(qvApp->isRunning()) {
                        std::cerr << qPrintable("Warning: " + str + "\n");
                    } // Otherwise, qApp will show the error and won't start the program.
                    return FALSE;
                }
            }

        template <class Type> bool setPropertyFromArguments(QString propertyName)
            {
            QStringList arguments = qvApp->arguments();

            QMutableStringListIterator iterator(arguments);
            while (iterator.hasNext())
                {
                QString argument = iterator.next();
                // Only if the name of the property holder is the same as defined in
                // the argument, in the form --name:property=value, (with name:
                // optional) the value will be intended to be applied to the property:
                if (argument.contains(QRegExp("^--")))
                    {
                    QString propertyContainerName(argument), parameter(argument), value(argument);
                    // Checks whether in the argument string there is a name for
                    // restricting the application of the value to a variable of
                    // a specific property holder.
                    if (argument.contains(QRegExp("^--[^=]+:")))
                        {
                        propertyContainerName.remove(QRegExp("^--")).remove(QRegExp(":.*"));
                        if(propertyContainerName != getName())
                            continue;
                        parameter.remove(QRegExp("^--[^=]+:")).remove(QRegExp("=.*$"));
                        }
                    else
                        {
                        parameter.remove(QRegExp("^--")).remove(QRegExp("=.*$"));
                        }
                    if(parameter != propertyName)
                        continue;
                    // If we get here, then we must assign the value to the property:
                    value.remove(QRegExp("^--[^=]*="));
                    if(parseArgument<Type>(parameter,value))
                        {
                        if(not isInput(propertyName))
                            {
                            QString str = QString("QVPropertyContainer::setPropertyFromArguments():")
                                        + QString(" property ") + propertyName
                                        + QString(" in holder ") + getName()
                                        + QString(" is not of Input type, and cannot be parsed.");
                            setLastError(str);
                            //qApp will show the error and won't start the program.
                            }
                        qvApp->setArgumentAsUsed(argument);
                        return TRUE;
                        }
                    }
                }
                // If we get here, then we did not parse any value for the property:
                return FALSE;
            }

        bool correctRange(const QString name, const double & value) const;
        // Any type inference ambiguity resolved with this:
        // 1. For int values:
        bool correctRange(const char *name, const int & value) const;
        bool correctRange(QString name, const int & value) const;

        // 2. Rest of types have no range, so we always return true:
        template <typename T> bool correctRange(const QString parameter, const T & value) {
            Q_UNUSED(parameter);
            Q_UNUSED(value);
            return TRUE;
        }

        bool checkExists(const QString name, const QString methodname) const;
        bool checkIsNewProperty(const QString name, const QString methodname) const;
    };

template <class Type> bool QVPropertyContainer::parseArgument(const QString parameter, const QString value)
    {
    // Float parms will be parsed just as doubles:
                bool ok,ok2;
                ok2 = isType<float>(parameter,&ok);
                if(ok and ok2)
                    return parseArgument<double>(parameter, value);
                // Otherwise:
        errorString = "QVPropertyContainer::parseArgument(): holder " + getName() +
                        ": parameter " + parameter +
                        " has an unknown type to command line parser " +
                        QString("(trying to parse value %1)").arg(value) ;
        return FALSE;
    }

template <> bool QVPropertyContainer::parseArgument<bool>(const QString parameter, const QString value);
template <> bool QVPropertyContainer::parseArgument<int>(const QString parameter, const QString value);
template <> bool QVPropertyContainer::parseArgument<float>(const QString parameter, const QString value);
template <> bool QVPropertyContainer::parseArgument<double>(const QString parameter, const QString value);
template <> bool QVPropertyContainer::parseArgument<QString>(const QString parameter, const QString value);

Q_DECLARE_OPERATORS_FOR_FLAGS(QVPropertyContainer::PropertyFlags)
Q_DECLARE_OPERATORS_FOR_FLAGS(QVPropertyContainer::PropertyLinkFlags)

#endif
