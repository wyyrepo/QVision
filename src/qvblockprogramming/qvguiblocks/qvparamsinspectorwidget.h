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

#ifndef QVPARAMSINSPECTORWIDGET_H
#define QVPARAMSINSPECTORWIDGET_H

#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QTabWidget>

#include <QVPropertyContainer>

/// @file
/// @brief QVParamsInspector interface file.
/// @author PARP Group (http://perception.inf.um.es), Univ. of Murcia (Spain)

#ifndef DOXYGEN_IGNORE_THIS
/*!
@class QVParamsInspectorWidget qvblockprogramming/qvguiblocks/qvparamsinspectorwidget.h QVParamsInspectorWidget
@brief QVParamsInspectorWidget class.

This class implements a QWidget that shows controls to view and modify
the state of double, int and boolean properties in a QVProcessingBlock object,
in execution time. It also shows buttons for corresponding block triggers,
if apply.
(see @ref QVProcessingBlock::addTrigger() method).
@ingroup qvqwt
*/
class QVParamsInspectorWidget: public QWidget, public QVPropertyContainer
{
	Q_OBJECT
public:

	/// @brief Constructs an empty QVParamsInspectorWidget object.
	/// @param holder Pointer to the property holder object.
	/// @param parent (Optional) pointer to the parent widget.
	QVParamsInspectorWidget(QVPropertyContainer *holder, QWidget *parent = 0);

private:
	QVBoxLayout *vboxLayout;
	QTabWidget *tabWidget;
	QWidget *inputWidget;
	QVBoxLayout *inputVboxLayout;
	QWidget *outputWidget;
	QVBoxLayout *outputVboxLayout;

private slots:
	void somePropertyChanged();
	void somePropertyUpdate();
};
#endif
#endif

