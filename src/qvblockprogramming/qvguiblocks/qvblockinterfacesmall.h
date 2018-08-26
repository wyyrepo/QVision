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

#ifndef QVWORKERINTERFACESMALL_H
#define QVWORKERINTERFACESMALL_H

#include <QVProcessingBlock>
#include "qvcpuplot.h"
#include <ui/ui_qvprocessingblockformsmall.h>

#ifndef DOXYGEN_IGNORE_THIS
// file qvblockinterfacesmall.h
// brief QVProcessingBlockInterfaceSmall interface file.
// author PARP Group (http://perception.inf.um.es), Univ. of Murcia (Spain)
// class QVProcessingBlockInterfaceSmall qvparamsinspectorwidget.h qvblockprogramming/qvguiblocks/qvparamsinspectorwidget.h
// brief QVProcessingBlockInterfaceSmall class.
//
// This class is a QWidget able to inspect and modify properties from a QVProcessingBlock object, managing QVCameras, and other QVPropertyContainers registered in the system, allowing the final user to modify some of their property values in real time, and to show QVImages resulting from the QVProcessingBlock's work, on the screen.
// ingroup qvblockprogramming
class QVProcessingBlockInterfaceSmall: public QWidget
{
	Q_OBJECT

public:	
	Ui::QVProcessingBlockFormSmall form;

	// brief Constructs a QVProcessingBlockInterfaceSmall object, given the QVProcessingBlock object which work (properties, result images, 
	// etc...) will be inspected.
	// param name identifier for the object to be created.
	QVProcessingBlockInterfaceSmall(QVProcessingBlock *block, QWidget *parent = 0);
	~QVProcessingBlockInterfaceSmall();

public slots:
	void newIterationSlot();
	void statusUpdate(QVProcessingBlock::TBlockStatus status);

private slots:
	void finishBlock();

private:
	QVProcessingBlock *block;
	bool isGroupMaster;
	QVCPUPlot * cpuPlot;// * cpuPlotSmall;
	QWidget * leftLayout, * rightLayout;
	QVBoxLayout * leftVBox, * rightVBox;
};
#endif
#endif // QVWORKERINTERFACESMALL_H
