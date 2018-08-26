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

/// @file qvdesignergui.h
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#ifndef DESIGNERGUI_H
#define DESIGNERGUI_H

#include <QObject>
#include <QList>
#include <QString>
#include <QMap>
class QXmlStreamReader;
#include "../qvgui.h"
#include "facade/itemproperties.h"
#include "facade/itemfactory.h"
#include "slate/slatewindow.h"
#include "slate/informer.h"
#include <QMetaType>
class QVPropertyContainer;
class QVPropertyContainerChange;


/*!
@class QVDesignerGUI qvblockprogramming/qvguiblocks/qvdesigner/qvdesignergui.h QVDesignerGUI
@brief Advanced graphic block oriented programming interface widget for QVision applications.

Class @ref QVDesignerGUI is used in QVision applications to create an advanced GUI that offers the user the possibility to control the execution of the different workers registered in the application, the flow of the input video camera objects, modify the input parameters defined in them (and which are not linked to the output of other workers, in whose case they obviously should not be controlled directly by the user), and modify the application's structure with a graphic oriented programming widget in run time.

For an introduction to the programming and usage of this graphical interface, see section @ref TheDesignerGUI of the manual.

@ingroup qvqwt
*/
class QVDesignerGUI: QObject, QVGUI
{ // Clase que se encargará de hacer de intermediario entre la vista y el modelo (el slate y la QVAplication)
	Q_OBJECT
	
	public:

		/// @brief Constructs a QVDesignerGUI object.
		// /// @param parent (Optional) parent for the created widget
		QVDesignerGUI();

#ifndef DOXYGEN_IGNORE_THIS
		//////////////////////////////////////////// funcionalidad de gui de la qvision ////////////////////////////////////////////

		/// @brief initialice the QVGUI object.
		virtual void init();
	
		/// @brief show the QVGUI object.
		void show();

		//////////////////////////////////////////// obtención de los items disponibles ////////////////////////////////////////////

		// devuelve la lista de Items disponibles en el sistema, cada uno de estos items es un elemento del diseño de los programas de QVision
		QMap<QString, QList<QString> > getItemTypes() const;
	
		// devuelve la lista de Items de entrada disponibles en el sistema, cada uno de estos items es un elemento del diseño de los programas de QVision
		QMap<QString, QList<QString> > getInputItemTypes() const;
	
		// devuelve la lista de Items intermedios disponibles en el sistema, cada uno de estos items es un elemento del diseño de los programas de QVision
		QMap<QString, QList<QString> > getMiddleItemTypes() const;
	
		// devuelve la lista de Items de salida disponibles en el sistema, cada uno de estos items es un elemento del diseño de los programas de QVision
		QMap<QString, QList<QString> > getOutputItemTypes() const;

		QString getCppText() const;

		QString getXMLText();

		bool loadXML(QString text);


		////////////////////////////////////// modificación del entorno común (slate + qvision) //////////////////////////////////////

		/// @todo Revisar, función para añadir. Esta función permite registrar nuevos tipos de blocks en el ámbito de nombres de la aplicación, para que
		/// el designer pueda crear clases de ese tipo.
		// crea y registra un item, del tipo especificado y nombre concreto, en el sistema. Devuelve el id del item (0 si no lo ha creado)
		template<typename T> static uint registerUserType(const QString name)
			{ return qRegisterMetaType<T>(name.toAscii().data()); }

		// crea y registra un item, del tipo especificado y nombre concreto, en el sistema. Devuelve el id del item (0 si no lo ha creado)
		uint addItem(const QString type, const QString name, uint lastId = 0);
	
		// crea y registra un link entre dos items del sistema
		bool addLink(const uint fromId, const QString fromProp, const uint toId, const QString toProp, const bool synchronous, const bool sequential);

		// borra y desregistra un item
		bool delItem(const uint id);
	
		// borra y desregistra un link
		bool delLink(const uint fromId, const QString fromProp, const uint toId, const QString toProp);

		// establece el valor de la propiedad de un item del sistema
		template <class Type> bool setProperty(const uint fromId, const QString fromProp, const Type &value);

		bool setName(const uint id, const QString name);

		void showProperties(const uint id);

		///////////////////////////////////////////////////// control del entorno /////////////////////////////////////////////////////

		// lanza un sistema como el compuesto en la pizarra
		void run();
	
		// para el sistema lanzado
		void stop();

	public slots:
		void quit();
		void processChange(QVPropertyContainerChange change);
		void dialogChange(QVPropertyContainerChange change);

	private:
		bool createDialog(const uint itemId);
		void deleteDialog(const uint itemId);
		QString getLinkName(QVPropertyContainerChange change);
		QString getLinkName(QString fromName, QString fromProp, QString toName, QString toProp);
		QString getAbsPropName(QString fromName, QString fromProp);
		void createGroups(QList<GroupInfo> &lastGroups, QMap<uint, uint> &oldId_To_NewId);

		bool readXMLQVApplication(QXmlStreamReader &xmlReader);
		bool readXMLNodes(QXmlStreamReader &xmlReader);
		bool readXMLNode(QXmlStreamReader &xmlReader);
		bool readXMLProperty(QXmlStreamReader &xmlReader, uint id);
		bool readXMLLinks(QXmlStreamReader &xmlReader);
		bool readXMLAsynchronousLink(QXmlStreamReader &xmlReader);
		bool readXMLSynchronousLink(QXmlStreamReader &xmlReader);
		bool readXMLSequentialLink(QXmlStreamReader &xmlReader);
		bool readXMLGroups(QXmlStreamReader &xmlReader);
		bool readXMLGroup(QXmlStreamReader &xmlReader, QList<GroupInfo> &groupInfos);
		bool readXMLChildNode(QXmlStreamReader &xmlReader, GroupInfo &groupInfo);
		bool readXMLChildGroup(QXmlStreamReader &xmlReader, GroupInfo &groupInfo);
		bool readXMLVisibleNodeLink(QXmlStreamReader &xmlReader, GroupInfo &groupInfo);
		bool readXMLVisibleGroupLink(QXmlStreamReader &xmlReader, GroupInfo &groupInfo);
		bool readXMLUnknownElement(QXmlStreamReader &xmlReader);

		ItemFactory factory;
		SlateWindow slate;
		Informer informer;

		QMap<uint, QVPropertyContainer *> containers;
		QMap<uint, QVPropertyContainer *> initialContainers;
		QMap<uint, QDialog *> dialogs; // el identificador es del container asociado
		QMap<uint, uint> dialogsToContainers; // los containers asociados a los dialogos (id dialogo, id container)

			class CreatedLink
				{
				public:
					CreatedLink(const uint _fromId, const QString _fromProp, const uint _toId, const QString _toProp, const bool _sync, const bool _sequ):
						fromId(_fromId), fromProp(_fromProp), toId(_toId), toProp(_toProp), synchronous(_sync), sequential(_sequ) { }

					uint fromId;
					QString fromProp;
					uint toId;
					QString toProp;
					bool synchronous;
					bool sequential;
				};

			class CreatedItem
				{
				public:
					CreatedItem(): type(""), name(""), id(0) { }
					CreatedItem(const QString _type, const QString _name, uint _id): type(_type), name(_name), id(_id) { }

					QString type, name;
					uint id;
				};

			class PropertyChange
				{
				public:
					PropertyChange(const uint contId, const QString prop, const QVariant val): id(contId), propName(prop), value(val) { }

					uint id;
					QString propName;
					QVariant value;
				};

		QMap<QString, CreatedLink> createdLinks; // the key is "fromName[fromProp] => toName[toProp]"
		QMap<uint, CreatedItem> createdItems;
		QMap<QString, PropertyChange> propertyChanges; // the key is "contName[propName]"

		QMap<uint, uint> XMLId_To_ContainersId; // para cuando estamos cargando el XML ya que se hace recursivo entre muchas funciones

#endif
};

#endif

