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

#include "qvparamwidget.h"
#include "qvparamsinspectorwidget.h"
#include <QLabel>

#include <QVProcessingBlock>
#include <QVIndexedStringList>

QVParamsInspectorWidget::QVParamsInspectorWidget(QVPropertyContainer *holder, QWidget *parent):
	QWidget(parent), QVPropertyContainer("QVParamsInspectorWidget for " + holder->getName())
	{
	//setGeometry(QRect(10, 20, 200, 0));
	inputWidget = new QWidget(this);
	outputWidget = new QWidget(this);
	inputVboxLayout = new QVBoxLayout(inputWidget);
	outputVboxLayout = new QVBoxLayout(outputWidget);
	inputVboxLayout->setSpacing(0);
	outputVboxLayout->setSpacing(0);

	tabWidget = new QTabWidget(this);
	tabWidget->addTab(inputWidget, "input properties");
	tabWidget->addTab(outputWidget, "output properties");

	vboxLayout = new QVBoxLayout(this);
	vboxLayout->setSpacing(0);
	vboxLayout->addWidget(tabWidget);


	QVProcessingBlock *block;
	if((block = dynamic_cast<QVProcessingBlock*>(holder)) != NULL)
		foreach(QString property, block->getTriggerList())
			inputVboxLayout->addWidget(new QVProcessingBlockTriggerWidget(block, property, this));

	bool haveInputWidgets = false;
	bool haveOutputWidgets = false;
	foreach(QString property, holder->getPropertyList()) {
		if(not holder->isLinkedInput(property) && holder->isInput(property) && not holder->isGUIInvisible(property)) {
			if(holder->isType<int>(property)) // if the property is int.
				{
				QVSIntParamWidget *int_widget = new QVSIntParamWidget(holder,this,property);
				inputVboxLayout->addWidget(int_widget);
				haveInputWidgets = true;
				writeOutputProperties();
				connect(int_widget,SIGNAL(valueChanged(int)),this,SLOT(somePropertyChanged()));
				}
			else if(holder->isType<unsigned int>(property)) // if the property is unsigned int.
				{
				QVUIntParamWidget *int_widget = new QVUIntParamWidget(holder,this,property);
				inputVboxLayout->addWidget(int_widget);
				haveInputWidgets = true;
				writeOutputProperties();
				connect(int_widget,SIGNAL(valueChanged(unsigned int)),this,SLOT(somePropertyChanged()));
				}
			else if(holder->isType<char>(property)) // if the property is unsigned char.
				{
				QVSCharParamWidget *int_widget = new QVSCharParamWidget(holder,this,property);
				inputVboxLayout->addWidget(int_widget);
				haveInputWidgets = true;
				writeOutputProperties();
				connect(int_widget,SIGNAL(valueChanged(char)),this,SLOT(somePropertyChanged()));
				}
			else if(holder->isType<unsigned char>(property)) // if the property is unsigned char.
				{
				QVUCharParamWidget *int_widget = new QVUCharParamWidget(holder,this,property);
				inputVboxLayout->addWidget(int_widget);
				haveInputWidgets = true;
				writeOutputProperties();
				connect(int_widget,SIGNAL(valueChanged(unsigned char)),this,SLOT(somePropertyChanged()));
				}
			else if(holder->isType<double>(property)) // if the property is double.
				{
				QVDoubleParamWidget *double_widget = new QVDoubleParamWidget(holder,this,property);
				inputVboxLayout->addWidget(double_widget);
				haveInputWidgets = true;
				writeOutputProperties();
				connect(double_widget,SIGNAL(valueChanged(double)),this,SLOT(somePropertyChanged()));
				}
			else if(holder->isType<float>(property)) // if the property is double.
				{
				QVFloatParamWidget *double_widget = new QVFloatParamWidget(holder,this,property);
				inputVboxLayout->addWidget(double_widget);
				haveInputWidgets = true;
				writeOutputProperties();
				connect(double_widget,SIGNAL(valueChanged(float)),this,SLOT(somePropertyChanged()));
				}
			else if(holder->isType<bool>(property)) // if the property is bool.
				{
				QVBoolParamWidget *bool_widget = new QVBoolParamWidget(holder,this,property);
				inputVboxLayout->addWidget(bool_widget);
				haveInputWidgets = true;
				writeOutputProperties();
				connect(bool_widget,SIGNAL(valueChanged(bool)),this,SLOT(somePropertyChanged()));
				}
			else if(holder->isType<QString>(property)) // if the property is QString.
				{
				QVStringParamWidget *st_widget = new QVStringParamWidget(holder,this,property);
				inputVboxLayout->addWidget(st_widget);
				haveInputWidgets = true;
				writeOutputProperties();
				connect(st_widget,SIGNAL(valueChanged(QString)),this,SLOT(somePropertyChanged()));
				}
			else if(holder->isType<QVIndexedStringList>(property)) // if the property is QVIndexedStringList.
				{
				QVStringListParamWidget *sl_widget = new QVStringListParamWidget(holder,this,property);
				inputVboxLayout->addWidget(sl_widget);
				haveInputWidgets = true;
				writeOutputProperties();
				connect(sl_widget,SIGNAL(valueChanged(QVIndexedStringList)),this,SLOT(somePropertyChanged()));
				}
			else if(holder->isType<QColor>(property)) // if the property is QColor
				{
				QVColorParamWidget *sl_widget = new QVColorParamWidget(holder,this,property);
				inputVboxLayout->addWidget(sl_widget);
				haveInputWidgets = true;
				writeOutputProperties();
				connect(sl_widget,SIGNAL(valueChanged(QColor)),this,SLOT(somePropertyChanged()));
				}
			else if(holder->isType<QSize>(property)) // if the property is QSize
				{
				QVSizeParamWidget *sl_widget = new QVSizeParamWidget(holder,this,property);
				inputVboxLayout->addWidget(sl_widget);
				haveInputWidgets = true;
				writeOutputProperties();
				connect(sl_widget,SIGNAL(valueChanged(QSize)),this,SLOT(somePropertyChanged()));
				}
			else if(holder->isType<QPoint>(property)) // if the property is QPoint
				{
				QVPointParamWidget *sl_widget = new QVPointParamWidget(holder,this,property);
				inputVboxLayout->addWidget(sl_widget);
				haveInputWidgets = true;
				writeOutputProperties();
				connect(sl_widget,SIGNAL(valueChanged(QPoint)),this,SLOT(somePropertyChanged()));
				}
			#ifdef QVIPP
			else if(holder->isType<IppiMaskSize>(property)) // if the property is IppiMaskSize
				{
				QVIppiMaskSizeParamWidget *sl_widget = new QVIppiMaskSizeParamWidget(holder,this,property);
				inputVboxLayout->addWidget(sl_widget);
				haveInputWidgets = true;
				writeOutputProperties();
				connect(sl_widget,SIGNAL(valueChanged(IppiMaskSize)),this,SLOT(somePropertyChanged()));
				}
			else if(holder->isType<IppCmpOp>(property)) // if the property is IppCmpOp
				{
				QVIppCmpOpParamWidget *sl_widget = new QVIppCmpOpParamWidget(holder,this,property);
				inputVboxLayout->addWidget(sl_widget);
				haveInputWidgets = true;
				writeOutputProperties();
				connect(sl_widget,SIGNAL(valueChanged(IppCmpOp)),this,SLOT(somePropertyChanged()));
				}
			else if(holder->isType<IppRoundMode>(property)) // if the property is IppRoundMode
				{
				QVIppRoundModeParamWidget *sl_widget = new QVIppRoundModeParamWidget(holder,this,property);
				inputVboxLayout->addWidget(sl_widget);
				haveInputWidgets = true;
				writeOutputProperties();
				connect(sl_widget,SIGNAL(valueChanged(IppRoundMode)),this,SLOT(somePropertyChanged()));
				}
			#endif
		}
		else if(not holder->isLinkedOutput(property) && holder->isOutput(property) && not holder->isGUIInvisible(property)) {
			if(holder->isType<int>(property)) // if the property is int.
				{
				QVProcessingBlock* block;
				if((block = dynamic_cast<QVProcessingBlock*>(holder)) != NULL) {
					QVOutputIntParamWidget *int_widget = new QVOutputIntParamWidget(block,this,property);
					outputVboxLayout->addWidget(int_widget);
					haveOutputWidgets = true;
					connect(block,SIGNAL(endIteration(uint, int)),this,SLOT(somePropertyUpdate()));
					connect(block,SIGNAL(endIteration(uint, int)),int_widget,SLOT(update()));
					}
				}
			else if(holder->isType<double>(property)) // if the property is double.
				{
				QVProcessingBlock* block;
				if((block = dynamic_cast<QVProcessingBlock*>(holder)) != NULL) {
					QVOutputDoubleParamWidget *double_widget = new QVOutputDoubleParamWidget(block,this,property);
					outputVboxLayout->addWidget(double_widget);
					haveOutputWidgets = true;
					connect(block,SIGNAL(endIteration(uint, int)),this,SLOT(somePropertyUpdate()));
					connect(block,SIGNAL(endIteration(uint, int)),double_widget,SLOT(update()));
					}
				}
			else if(holder->isType<bool>(property)) // if the property is bool.
				{
				QVProcessingBlock* block;
				if((block = dynamic_cast<QVProcessingBlock*>(holder)) != NULL) {
					QVOutputBoolParamWidget *bool_widget = new QVOutputBoolParamWidget(block,this,property);
					outputVboxLayout->addWidget(bool_widget);
					haveOutputWidgets = true;
					connect(block,SIGNAL(endIteration(uint, int)),this,SLOT(somePropertyUpdate()));
					connect(block,SIGNAL(endIteration(uint, int)),bool_widget,SLOT(update()));
					}
				}
			else if(holder->isType<QString>(property)) // if the property is QString.
				{
				QVProcessingBlock* block;
				if((block = dynamic_cast<QVProcessingBlock*>(holder)) != NULL) {
					QVOutputStringParamWidget *st_widget = new QVOutputStringParamWidget(block,this,property);
					outputVboxLayout->addWidget(st_widget);
					haveOutputWidgets = true;
					connect(block,SIGNAL(endIteration(uint, int)),this,SLOT(somePropertyUpdate()));
					connect(block,SIGNAL(endIteration(uint, int)),st_widget,SLOT(update()));
					}
				}
			else if(holder->isType<QVIndexedStringList>(property)) // if the property is QVIndexedStringList.
				{
				QVProcessingBlock* block;
				if((block = dynamic_cast<QVProcessingBlock*>(holder)) != NULL) {
					QVOutputStringListParamWidget *sl_widget = new QVOutputStringListParamWidget(block,this,property);
					outputVboxLayout->addWidget(sl_widget);
					haveOutputWidgets = true;
					connect(block,SIGNAL(endIteration(uint, int)),this,SLOT(somePropertyUpdate()));
					connect(block,SIGNAL(endIteration(uint, int)),sl_widget,SLOT(update()));
					}
				}
			else if(holder->isType<QColor>(property)) // if the property is QColor
				{
				QVProcessingBlock* block;
				if((block = dynamic_cast<QVProcessingBlock*>(holder)) != NULL) {
					QVOutputColorParamWidget *sl_widget = new QVOutputColorParamWidget(block,this,property);
					outputVboxLayout->addWidget(sl_widget);
					haveOutputWidgets = true;
					connect(block,SIGNAL(endIteration(uint, int)),this,SLOT(somePropertyUpdate()));
					connect(block,SIGNAL(endIteration(uint, int)),sl_widget,SLOT(update()));
					}
				}
		}
	}

	if (!haveInputWidgets) inputVboxLayout->addWidget(new QLabel("\n\tThis container has no\n\teditable input properties."));
	if (!haveOutputWidgets) outputVboxLayout->addWidget(new QLabel("\n\tThis container has no\n\tvisible output properties."));

	inputVboxLayout->addStretch();
	}

void QVParamsInspectorWidget::somePropertyChanged()
	{
	writeOutputProperties();
	}

void QVParamsInspectorWidget::somePropertyUpdate()
	{
	readInputProperties();
	}
