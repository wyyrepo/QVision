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

#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <qwt_slider.h>
QVSIntParamWidget::QVSIntParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	value = orig_holder->getPropertyValue<int>(property);
	info = orig_holder->getPropertyInfo(property);
	if(orig_holder->hasRange(property))
		{
		max = orig_holder->getPropertyMaximum<int>(property);
		min = orig_holder->getPropertyMinimum<int>(property);
		gui_holder->addProperty<int>(property,QVPropertyContainer::outputFlag,value,"",min,max);
		gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

		lineedit = new QLineEdit(this);
		lineedit->setFixedWidth(80);
		slider = new QSlider(Qt::Horizontal,this);
		slider->setMinimum(min);
		slider->setMaximum(max);
		slider->setFixedWidth(150);

		QVBoxLayout *vboxlayout = new QVBoxLayout(this);
		vboxlayout->setSpacing(0);
		QHBoxLayout *hboxlayout1 = new QHBoxLayout();
		QLabel *label = new QLabel(QString("<i>int</i> <b>%1</b>").arg(property));
		label->setToolTip(info);
		hboxlayout1->addWidget(label);
		hboxlayout1->addStretch();
		hboxlayout1->addWidget(new QLabel(QString("(%1,%2)").arg(min).arg(max)));
		QHBoxLayout *hboxlayout2 = new QHBoxLayout();
		hboxlayout2->addWidget(lineedit);
		hboxlayout2->addStretch();
		hboxlayout2->addWidget(slider);
		vboxlayout->addLayout(hboxlayout1);
		vboxlayout->addLayout(hboxlayout2);

		slider->setValue(value);
		connect(slider,SIGNAL(valueChanged(int)),this,SLOT(setValue()));
		}
	else
		{
		gui_holder->addProperty<int>(property,QVPropertyContainer::outputFlag,value,"");
		gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

		lineedit = new QLineEdit(this);
		lineedit->setFixedWidth(80);

		QHBoxLayout *hboxlayout = new QHBoxLayout(this);
		QLabel *label = new QLabel(QString("<i>int</i> <b>%1</b>").arg(property));
		label->setToolTip(info);
		hboxlayout->addWidget(label);
		hboxlayout->addStretch();
		hboxlayout->addWidget(lineedit);
		//hboxlayout->addStretch();
		}

	connect(lineedit,SIGNAL(editingFinished()),this,SLOT(setValue()));
	gui_holder->setPropertyValue<int>(property,value);
	lineedit->setText(QString("%1").arg(value));
	emit valueChanged(value);
	}

void QVSIntParamWidget::setValue()
	{
	if(sender() == lineedit)
		{
		bool ok;
		value = lineedit->text().toInt(&ok);
		if( (not ok) or
			(orig_holder->hasRange(property) and (value<min or value>max) ) )
			value = gui_holder->getPropertyValue<int>(property);
		}
	else if(sender() == slider) {
		value = slider->value();
		}
	else
		value = gui_holder->getPropertyValue<int>(property);

	lineedit->setText(QString("%1").arg(value));
	if(orig_holder->hasRange(property))
		slider->setValue(value);
	gui_holder->setPropertyValue<int>(property,value);
	emit valueChanged(value);
	}

/////////////////////////////
QVUIntParamWidget::QVUIntParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	value = orig_holder->getPropertyValue<unsigned int>(property);
	info = orig_holder->getPropertyInfo(property);
	if(orig_holder->hasRange(property))
		{
		max = orig_holder->getPropertyMaximum<unsigned int>(property);
		min = orig_holder->getPropertyMinimum<unsigned int>(property);
		gui_holder->addProperty<unsigned int>(property,QVPropertyContainer::outputFlag,value,"",min,max);
		gui_holder->linkProperty(property, orig_holder, property, QVPropertyContainer::AsynchronousLink);

		lineedit = new QLineEdit(this);
		lineedit->setFixedWidth(80);
		slider = new QSlider(Qt::Horizontal,this);
		slider->setMinimum(min);
		slider->setMaximum(max);
		slider->setFixedWidth(150);

		QVBoxLayout *vboxlayout = new QVBoxLayout(this);
		vboxlayout->setSpacing(0);
		QHBoxLayout *hboxlayout1 = new QHBoxLayout();
		QLabel *label = new QLabel(QString("<i>unsigned int</i> <b>%1</b>").arg(property));
		label->setToolTip(info);
		hboxlayout1->addWidget(label);
		hboxlayout1->addStretch();
		hboxlayout1->addWidget(new QLabel(QString("(%1,%2)").arg(min).arg(max)));
		QHBoxLayout *hboxlayout2 = new QHBoxLayout();
		hboxlayout2->addWidget(lineedit);
		hboxlayout2->addStretch();
		hboxlayout2->addWidget(slider);
		vboxlayout->addLayout(hboxlayout1);
		vboxlayout->addLayout(hboxlayout2);

		slider->setValue(value);
		connect(slider,SIGNAL(valueChanged(unsigned int)),this,SLOT(setValue()));
		}
	else
		{
		gui_holder->addProperty<unsigned int>(property,QVPropertyContainer::outputFlag,value,"");
		gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

		lineedit = new QLineEdit(this);
		lineedit->setFixedWidth(80);

		QHBoxLayout *hboxlayout = new QHBoxLayout(this);
		QLabel *label = new QLabel(QString("<i>unsigned int</i> <b>%1</b>").arg(property));
		label->setToolTip(info);
		hboxlayout->addWidget(label);
		hboxlayout->addStretch();
		hboxlayout->addWidget(lineedit);
		//hboxlayout->addStretch();
		}

	connect(lineedit,SIGNAL(editingFinished()),this,SLOT(setValue()));
	gui_holder->setPropertyValue<unsigned int>(property,value);
	lineedit->setText(QString("%1").arg(value));
	emit valueChanged(value);
	}

void QVUIntParamWidget::setValue()
	{
	if(sender() == lineedit)
		{
		bool ok;
		value = lineedit->text().toInt(&ok);
		if( (not ok) or
			(orig_holder->hasRange(property) and (value<min or value>max) ) )
			value = gui_holder->getPropertyValue<unsigned int>(property);
		}
	else if(sender() == slider) {
		value = slider->value();
		}
	else
		value = gui_holder->getPropertyValue<unsigned int>(property);

	lineedit->setText(QString("%1").arg(value));
	if(orig_holder->hasRange(property))
		slider->setValue(value);
	gui_holder->setPropertyValue<unsigned int>(property,value);
	emit valueChanged(value);
	}

/////////////////////////////

QVSCharParamWidget::QVSCharParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	value = orig_holder->getPropertyValue<char>(property);
	info = orig_holder->getPropertyInfo(property);
	if(orig_holder->hasRange(property))
		{
		max = orig_holder->getPropertyMaximum<char>(property);
		min = orig_holder->getPropertyMinimum<char>(property);
		}
	else	{
		max = 255;
		min = 0;
		}

	max = (max > 255)? 255: max;
	min = (min < 0)? 0: min;

	gui_holder->addProperty<char>(property,QVPropertyContainer::outputFlag,value,"",min,max);
	gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

	lineedit = new QLineEdit(this);
	lineedit->setFixedWidth(80);

	slider = new QSlider(Qt::Horizontal,this);
	slider->setMinimum(min);
	slider->setMaximum(max);
	slider->setFixedWidth(150);

	QVBoxLayout *vboxlayout = new QVBoxLayout(this);
	vboxlayout->setSpacing(0);
	QHBoxLayout *hboxlayout1 = new QHBoxLayout();
	QLabel *label = new QLabel(QString("<i>char</i> <b>%1</b>").arg(property));
	label->setToolTip(info);
	hboxlayout1->addWidget(label);
	hboxlayout1->addStretch();
	hboxlayout1->addWidget(new QLabel(QString("(%1,%2)").arg(min).arg(max)));
	QHBoxLayout *hboxlayout2 = new QHBoxLayout();
	hboxlayout2->addWidget(lineedit);
	hboxlayout2->addStretch();
	hboxlayout2->addWidget(slider);
	vboxlayout->addLayout(hboxlayout1);
	vboxlayout->addLayout(hboxlayout2);

	slider->setValue(value);
	connect(slider,SIGNAL(valueChanged(int)),this,SLOT(setValue()));

	connect(lineedit,SIGNAL(editingFinished()),this,SLOT(setValue()));
	gui_holder->setPropertyValue<char>(property,value);
	lineedit->setText(QString("%1").arg(value));
	emit valueChanged(value);
	}

void QVSCharParamWidget::setValue()
	{
	if(sender() == lineedit)
		{
		bool ok;
		value = lineedit->text().toInt(&ok);
		if( (not ok) or
			(/*orig_holder->hasRange(property) and*/ (value<min or value>max) ) )
			value = gui_holder->getPropertyValue<unsigned char>(property);
		}
	else if(sender() == slider) {
		value = slider->value();
		}
	else
		value = gui_holder->getPropertyValue<unsigned char>(property);

	lineedit->setText(QString("%1").arg(value));
	//if(orig_holder->hasRange(property))
	slider->setValue(value);
	gui_holder->setPropertyValue<unsigned char>(property,value);
	emit valueChanged(value);
	}
/////////////////////////////

QVUCharParamWidget::QVUCharParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	value = orig_holder->getPropertyValue<unsigned char>(property);
	info = orig_holder->getPropertyInfo(property);
	if(orig_holder->hasRange(property))
		{
		max = orig_holder->getPropertyMaximum<unsigned char>(property);
		min = orig_holder->getPropertyMinimum<unsigned char>(property);
		}
	else	{
		max = 255;
		min = 0;
		}

	max = (max > 255)? 255: max;
	min = (min < 0)? 0: min;

	gui_holder->addProperty<unsigned char>(property,QVPropertyContainer::outputFlag,value,"",min,max);
	gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

	lineedit = new QLineEdit(this);
	lineedit->setFixedWidth(80);

	slider = new QSlider(Qt::Horizontal,this);
	slider->setMinimum(min);
	slider->setMaximum(max);
	slider->setFixedWidth(150);

	QVBoxLayout *vboxlayout = new QVBoxLayout(this);
	vboxlayout->setSpacing(0);
	QHBoxLayout *hboxlayout1 = new QHBoxLayout();
	QLabel *label = new QLabel(QString("<i>unsigned char</i> <b>%1</b>").arg(property));
	label->setToolTip(info);
	hboxlayout1->addWidget(label);
	hboxlayout1->addStretch();
	hboxlayout1->addWidget(new QLabel(QString("(%1,%2)").arg(min).arg(max)));
	QHBoxLayout *hboxlayout2 = new QHBoxLayout();
	hboxlayout2->addWidget(lineedit);
	hboxlayout2->addStretch();
	hboxlayout2->addWidget(slider);
	vboxlayout->addLayout(hboxlayout1);
	vboxlayout->addLayout(hboxlayout2);

	slider->setValue(value);
	connect(slider,SIGNAL(valueChanged(int)),this,SLOT(setValue()));

	connect(lineedit,SIGNAL(editingFinished()),this,SLOT(setValue()));
	gui_holder->setPropertyValue<unsigned char>(property,value);
	lineedit->setText(QString("%1").arg(value));
	emit valueChanged(value);
	}

void QVUCharParamWidget::setValue()
	{
	if(sender() == lineedit)
		{
		bool ok;
		value = lineedit->text().toInt(&ok);
		if( (not ok) or
			(/*orig_holder->hasRange(property) and*/ (value<min or value>max) ) )
			value = gui_holder->getPropertyValue<unsigned char>(property);
		}
	else if(sender() == slider) {
		value = slider->value();
		}
	else
		value = gui_holder->getPropertyValue<unsigned char>(property);

	lineedit->setText(QString("%1").arg(value));
	//if(orig_holder->hasRange(property))
	slider->setValue(value);
	gui_holder->setPropertyValue<unsigned char>(property,value);
	emit valueChanged(value);
	}

/////////////////////////////
QVDoubleParamWidget::QVDoubleParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{

	value = orig_holder->getPropertyValue<double>(property);
	info = orig_holder->getPropertyInfo(property);
	if(orig_holder->hasRange(property))
		{
		max = orig_holder->getPropertyMaximum<double>(property);
		min = orig_holder->getPropertyMinimum<double>(property);
		gui_holder->addProperty<double>(property,QVPropertyContainer::outputFlag,value,"",min,max);
		gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

		lineedit = new QLineEdit(this);
		lineedit->setFixedWidth(80);
		qwtslider = new QwtSlider(this,Qt::Horizontal,QwtSlider::NoScale,QwtSlider::BgSlot);
		qwtslider->setThumbLength(20);
		qwtslider->setThumbWidth(10);
		qwtslider->setRange(min,max);
		qwtslider->setFixedWidth(150);

		QVBoxLayout *vboxlayout = new QVBoxLayout(this);
		vboxlayout->setSpacing(0);
		QHBoxLayout *hboxlayout1 = new QHBoxLayout();
		QLabel *label = new QLabel(QString("<i>double</i> <b>%1</b>").arg(property));
		label->setToolTip(info);
		hboxlayout1->addWidget(label);
		hboxlayout1->addStretch();
		hboxlayout1->addWidget(new QLabel(QString("(%1,%2)").arg(min).arg(max)));
		QHBoxLayout *hboxlayout2 = new QHBoxLayout();
		hboxlayout2->addWidget(lineedit);
		hboxlayout2->addStretch();
		hboxlayout2->addWidget(qwtslider);
		vboxlayout->addLayout(hboxlayout1);
		vboxlayout->addLayout(hboxlayout2);

		qwtslider->setValue(value);
		connect(qwtslider,SIGNAL(valueChanged(double)),this,SLOT(setValue()));
		}
	else
		{
		gui_holder->addProperty<double>(property,QVPropertyContainer::outputFlag,value,"");
		gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

		lineedit = new QLineEdit(this);
		lineedit->setFixedWidth(80);

		QHBoxLayout *hboxlayout = new QHBoxLayout(this);
		QLabel *label = new QLabel(QString("<i>double</i> <b>%1</b>").arg(property));
		label->setToolTip(info);
		hboxlayout->addWidget(label);
		hboxlayout->addStretch();
		hboxlayout->addWidget(lineedit);
		//hboxlayout->addStretch();
		}

	connect(lineedit,SIGNAL(editingFinished()),this,SLOT(setValue()));
	gui_holder->setPropertyValue<double>(property,value);
	lineedit->setText(QString("%1").arg(value));
	emit valueChanged(value);

	}

void QVDoubleParamWidget::setValue()
	{
	if(sender() == lineedit)
		{
		bool ok;
		value = lineedit->text().toDouble(&ok);
		if( (not ok) or
			(orig_holder->hasRange(property) and (value<min or value>max) ) )
			value = gui_holder->getPropertyValue<double>(property);
		}
	else if(sender() == qwtslider) {
		value = qwtslider->value();
		}
	else
		value = gui_holder->getPropertyValue<double>(property);

	lineedit->setText(QString("%1").arg(value));
	if(orig_holder->hasRange(property))
		qwtslider->setValue(value);
	gui_holder->setPropertyValue<double>(property,value);
	emit valueChanged(value);
	}

/////////////////////////////
QVFloatParamWidget::QVFloatParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{

	value = orig_holder->getPropertyValue<float>(property);
	info = orig_holder->getPropertyInfo(property);
	if(orig_holder->hasRange(property))
		{
		max = orig_holder->getPropertyMaximum<float>(property);
		min = orig_holder->getPropertyMinimum<float>(property);
		gui_holder->addProperty<float>(property,QVPropertyContainer::outputFlag,value,"",min,max);
		gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

		lineedit = new QLineEdit(this);
		lineedit->setFixedWidth(80);
		qwtslider = new QwtSlider(this,Qt::Horizontal,QwtSlider::NoScale,QwtSlider::BgSlot);
		qwtslider->setThumbLength(20);
		qwtslider->setThumbWidth(10);
		qwtslider->setRange(min,max);
		qwtslider->setFixedWidth(150);

		QVBoxLayout *vboxlayout = new QVBoxLayout(this);
		vboxlayout->setSpacing(0);
		QHBoxLayout *hboxlayout1 = new QHBoxLayout();
		QLabel *label = new QLabel(QString("<i>float</i> <b>%1</b>").arg(property));
		label->setToolTip(info);
		hboxlayout1->addWidget(label);
		hboxlayout1->addStretch();
		hboxlayout1->addWidget(new QLabel(QString("(%1,%2)").arg(min).arg(max)));
		QHBoxLayout *hboxlayout2 = new QHBoxLayout();
		hboxlayout2->addWidget(lineedit);
		hboxlayout2->addStretch();
		hboxlayout2->addWidget(qwtslider);
		vboxlayout->addLayout(hboxlayout1);
		vboxlayout->addLayout(hboxlayout2);

		qwtslider->setValue(value);
		connect(qwtslider,SIGNAL(valueChanged(double)),this,SLOT(setValue()));
		}
	else
		{
		gui_holder->addProperty<float>(property,QVPropertyContainer::outputFlag,value,"");
		gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

		lineedit = new QLineEdit(this);
		lineedit->setFixedWidth(80);

		QHBoxLayout *hboxlayout = new QHBoxLayout(this);
		QLabel *label = new QLabel(QString("<i>float</i> <b>%1</b>").arg(property));
		label->setToolTip(info);
		hboxlayout->addWidget(label);
		hboxlayout->addStretch();
		hboxlayout->addWidget(lineedit);
		//hboxlayout->addStretch();
		}

	connect(lineedit,SIGNAL(editingFinished()),this,SLOT(setValue()));
	gui_holder->setPropertyValue<float>(property,value);
	lineedit->setText(QString("%1").arg(value));
	emit valueChanged(value);

	}

void QVFloatParamWidget::setValue()
	{
	if(sender() == lineedit)
		{
		bool ok;
		value = lineedit->text().toFloat(&ok);
		if( (not ok) or
			(orig_holder->hasRange(property) and (value<min or value>max) ) )
			value = gui_holder->getPropertyValue<float>(property);
		}
	else if(sender() == qwtslider) {
		value = qwtslider->value();
		}
	else
		value = gui_holder->getPropertyValue<float>(property);

	lineedit->setText(QString("%1").arg(value));
	if(orig_holder->hasRange(property))
		qwtslider->setValue(value);
	gui_holder->setPropertyValue<float>(property,value);
	emit valueChanged(value);
	}

/////////////////////////////
QVBoolParamWidget::QVBoolParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	value = orig_holder->getPropertyValue<bool>(property);
	info = orig_holder->getPropertyInfo(property);

	QHBoxLayout *hboxlayout = new QHBoxLayout(this);
	//hboxlayout->setSpacing(0);
	QLabel *label = new QLabel(QString("<i>bool</i> <b>%1</b>").arg(property),this);
	label->setToolTip(info);
	hboxlayout->addWidget(label);
	hboxlayout->addStretch();
	checkbox = new QCheckBox(this);
	hboxlayout->addWidget(checkbox);

	gui_holder->addProperty<bool>(property,QVPropertyContainer::outputFlag,value,"");

	gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

	connect(checkbox,SIGNAL(stateChanged(int)),this,SLOT(setValue()));
	gui_holder->setPropertyValue<bool>(property,value);
	if(value)
		checkbox->setCheckState(Qt::Checked);
	else
		checkbox->setCheckState(Qt::Unchecked);
	emit valueChanged(value);
	}

void QVBoolParamWidget::setValue()
	{
	if (checkbox->checkState() == Qt::Unchecked)
		value = false;
	else if (checkbox->checkState() == Qt::Checked)
		value = true;

	gui_holder->setPropertyValue<bool>(property,value);
	emit valueChanged(value);
	}

/////////////////////////////
QVStringParamWidget::QVStringParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	value = orig_holder->getPropertyValue<QString>(property);
	info = orig_holder->getPropertyInfo(property);

	QHBoxLayout *hboxlayout = new QHBoxLayout(this);
	hboxlayout->setSpacing(0);
	QLabel *label = new QLabel(QString("<i>string</i> <b>%1 </b>").arg(property),this);
	label->setToolTip(info);
	hboxlayout->addWidget(label);
	lineedit = new QLineEdit(this);
	hboxlayout->addWidget(lineedit);

	lineedit->setText(value);

	gui_holder->addProperty<QString>(property,QVPropertyContainer::outputFlag,value,"");
	gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

	connect(lineedit,SIGNAL(textChanged(QString)),this,SLOT(setValue()));

	gui_holder->setPropertyValue<QString>(property,value);

	emit valueChanged(value);
	}

void QVStringParamWidget::setValue()
	{
	value = lineedit->text();
	gui_holder->setPropertyValue<QString>(property,value);
	emit valueChanged(value);
	}

/////////////////////////////
QVStringListParamWidget::QVStringListParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	value = orig_holder->getPropertyValue<QVIndexedStringList>(property);
	info = orig_holder->getPropertyInfo(property);

	QHBoxLayout *hboxlayout = new QHBoxLayout(this);
	hboxlayout->setSpacing(0);
	QLabel *label = new QLabel(QString("<i>stringlist</i> <b>%1</b>").arg(property),this);
	label->setToolTip(info);
	hboxlayout->addWidget(label);
	combobox = new QComboBox(this);
	hboxlayout->addWidget(combobox);

	gui_holder->addProperty<QVIndexedStringList>(property,QVPropertyContainer::outputFlag,value,"");
	gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

	connect(combobox,SIGNAL(activated(int)),this,SLOT(setValue()));

	gui_holder->setPropertyValue<QVIndexedStringList>(property,value);

	combobox->addItems(value);
	combobox->setCurrentIndex(value.getIndex());
	emit valueChanged(value);
	}

void QVStringListParamWidget::setValue()
	{
	value.setIndex(combobox->currentIndex());
	gui_holder->setPropertyValue<QVIndexedStringList>(property,value);
	emit valueChanged(value);
	}

/////////////////////////////
QVProcessingBlockTriggerWidget::QVProcessingBlockTriggerWidget(QVProcessingBlock *block, const QString triggername, QWidget *parent): QWidget(parent), block(block), triggername(triggername)
	{
	QHBoxLayout *hboxlayout = new QHBoxLayout(this);
	toolbutton = new QToolButton(this);
	toolbutton->setText(triggername);
	hboxlayout->addWidget(new QLabel(QString("<i>trigger</i> <b>%1</b>").arg(triggername)));
hboxlayout->addStretch();
	hboxlayout->addWidget(toolbutton);

	connect(toolbutton,SIGNAL(pressed()),this,SLOT(setValue()));
	connect(this,SIGNAL(valueChanged(QString)),block,SLOT(processTrigger(QString)),Qt::QueuedConnection);
	}

void QVProcessingBlockTriggerWidget::setValue()
	{
	emit valueChanged(triggername);
	}

/*		doublespinbox->setMinimum(min);
		doublespinbox->setMaximum(max);
		int signif=static_cast<int>(round(log(max-min)/log(10)));
		double val=pow(10,signif);
		std::cout << val << " " << signif << std::endl;
		doublespinbox->setSingleStep(val/100);
		if(signif >= 5)
			doublespinbox->setDecimals(0);
		else
			doublespinbox->setDecimals(5-signif);
*/

/////////////////////////////
// -- QVColorParamWidget
QVColorParamWidget::QVColorParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	const int max = 255, min = 0;
	value = orig_holder->getPropertyValue<QColor>(property);
	info = orig_holder->getPropertyInfo(property);

	gui_holder->addProperty<QColor>(property,QVPropertyContainer::outputFlag,value,"");
	gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

	lineeditR = new QLineEdit(this);
	lineeditR->setFixedWidth(80);
	lineeditG = new QLineEdit(this);
	lineeditG->setFixedWidth(80);
	lineeditB = new QLineEdit(this);
	lineeditB->setFixedWidth(80);

	sliderR = new QSlider(Qt::Horizontal,this);
	sliderR->setMinimum(min);
	sliderR->setMaximum(max);
	sliderR->setFixedWidth(150);

	sliderG = new QSlider(Qt::Horizontal,this);
	sliderG->setMinimum(min);
	sliderG->setMaximum(max);
	sliderG->setFixedWidth(150);

	sliderB = new QSlider(Qt::Horizontal,this);
	sliderB->setMinimum(min);
	sliderB->setMaximum(max);
	sliderB->setFixedWidth(150);

	QHBoxLayout *hboxlayout1 = new QHBoxLayout();
	QLabel *label = new QLabel(QString("<i>int</i> <b>%1</b>").arg(property));
	label->setToolTip(info);
	hboxlayout1->addWidget(label);
	hboxlayout1->addStretch();
	hboxlayout1->addWidget(new QLabel(QString("(%1,%2)").arg(min).arg(max)));

	QHBoxLayout *hboxlayoutR = new QHBoxLayout();
	hboxlayoutR->addWidget(new QLabel(QString("R")));
	hboxlayoutR->addWidget(lineeditR);
	hboxlayoutR->addStretch();
	hboxlayoutR->addWidget(sliderR);

	QHBoxLayout *hboxlayoutG = new QHBoxLayout();
	hboxlayoutG->addWidget(new QLabel(QString("G")));
	hboxlayoutG->addWidget(lineeditG);
	hboxlayoutG->addStretch();
	hboxlayoutG->addWidget(sliderG);

	QHBoxLayout *hboxlayoutB = new QHBoxLayout();
	hboxlayoutB->addWidget(new QLabel(QString("B")));
	hboxlayoutB->addWidget(lineeditB);
	hboxlayoutB->addStretch();
	hboxlayoutB->addWidget(sliderB);

	QVBoxLayout *vboxlayout = new QVBoxLayout(this);
	vboxlayout->setSpacing(0);
	vboxlayout->addLayout(hboxlayout1);
	vboxlayout->addLayout(hboxlayoutR);
	vboxlayout->addLayout(hboxlayoutG);
	vboxlayout->addLayout(hboxlayoutB);

	sliderR->setValue(value.red());
	sliderG->setValue(value.green());
	sliderB->setValue(value.blue());
	connect(sliderR,SIGNAL(valueChanged(int)),this,SLOT(setValue()));
	connect(sliderG,SIGNAL(valueChanged(int)),this,SLOT(setValue()));
	connect(sliderB,SIGNAL(valueChanged(int)),this,SLOT(setValue()));

	connect(lineeditR,SIGNAL(editingFinished()),this,SLOT(setValue()));
	connect(lineeditG,SIGNAL(editingFinished()),this,SLOT(setValue()));
	connect(lineeditB,SIGNAL(editingFinished()),this,SLOT(setValue()));
	gui_holder->setPropertyValue<QColor>(property,value);
	lineeditR->setText(QString("%1").arg(value.red()));
	lineeditG->setText(QString("%1").arg(value.green()));
	lineeditB->setText(QString("%1").arg(value.blue()));
	emit valueChanged(value);
	}

void QVColorParamWidget::setValue()
	{
	if(sender() == lineeditR || sender() == lineeditG || sender() == lineeditB)
		value = QColor(	lineeditR->text().toInt(), lineeditG->text().toInt(), lineeditB->text().toInt() );
	else if(sender() == sliderR || sender() == sliderG || sender() == sliderB)
		value = QColor(	sliderR->value(), sliderG->value(), sliderB->value() );
	else
		value = gui_holder->getPropertyValue<QColor>(property);

	lineeditR->setText(QString("%1").arg(value.red()));
	lineeditG->setText(QString("%1").arg(value.green()));
	lineeditB->setText(QString("%1").arg(value.blue()));

	sliderR->setValue(value.red());
	sliderG->setValue(value.green());
	sliderB->setValue(value.blue());

	std::cout << "Setting color to " << value.red() << ", " << value.green() << ", "  << value.blue()
		<< std::endl;  
	gui_holder->setPropertyValue<QColor>(property,value);
	emit valueChanged(value);
	}

///////////////7
QVSizeParamWidget::QVSizeParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	value = orig_holder->getPropertyValue<QSize>(property);
	
	gui_holder->addProperty<QSize>(property,QVPropertyContainer::outputFlag,value);
	gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

	lineWidth = new QLineEdit(this);
	lineWidth->setFixedWidth(80);

	lineHeight = new QLineEdit(this);
	lineHeight->setFixedWidth(80);

	QHBoxLayout *hboxnamelayout = new QHBoxLayout();
	hboxnamelayout->addWidget(new QLabel(QString("<i>QSize</i> <b>%1</b>").arg(property)));

	QHBoxLayout *hboxwidthlayout = new QHBoxLayout();
	hboxwidthlayout->addWidget(lineWidth);
	hboxwidthlayout->addStretch();
	hboxwidthlayout->addWidget(new QLabel(QString("Width")));

	QHBoxLayout *hboxheightlayout = new QHBoxLayout();
	hboxheightlayout->addWidget(lineHeight);
	hboxheightlayout->addStretch();
	hboxheightlayout->addWidget(new QLabel(QString("Height")));

	QVBoxLayout *vboxlayout = new QVBoxLayout(this);
	vboxlayout->setSpacing(0);
	vboxlayout->addLayout(hboxnamelayout);
	vboxlayout->addLayout(hboxwidthlayout);
	vboxlayout->addLayout(hboxheightlayout);

	connect(lineWidth,SIGNAL(editingFinished()),this,SLOT(setValue()));
	gui_holder->setPropertyValue<QSize>(property,value);
	lineWidth->setText(QString("%1").arg(value.width()));
	lineHeight->setText(QString("%1").arg(value.height()));
	emit valueChanged(value);
	}

void QVSizeParamWidget::setValue()
	{
	if(sender() == lineWidth ||sender() == lineHeight)
		{
		bool ok1, ok2;
		value = QSize(lineWidth->text().toInt(&ok1), lineHeight->text().toInt(&ok2));
		if(not ok1 || not ok2)
			value = gui_holder->getPropertyValue<QSize>(property);
		}
	else
		value = gui_holder->getPropertyValue<QSize>(property);

	lineWidth->setText(QString("%1").arg(value.width()));
	lineHeight->setText(QString("%1").arg(value.height()));
	gui_holder->setPropertyValue<QSize>(property,value);
	emit valueChanged(value);
	}

///////////////////////////

QVPointParamWidget::QVPointParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	value = orig_holder->getPropertyValue<QPoint>(property);
	
	gui_holder->addProperty<QPoint>(property,QVPropertyContainer::outputFlag,value);
	gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

	lineX = new QLineEdit(this);
	lineX->setFixedWidth(80);

	lineY = new QLineEdit(this);
	lineY->setFixedWidth(80);

	QHBoxLayout *hboxnamelayout = new QHBoxLayout();
	hboxnamelayout->addWidget(new QLabel(QString("<i>QPoint</i> <b>%1</b>").arg(property)));

	QHBoxLayout *hboxwidthlayout = new QHBoxLayout();
	hboxwidthlayout->addWidget(lineX);
	hboxwidthlayout->addStretch();
	hboxwidthlayout->addWidget(new QLabel(QString("x")));

	QHBoxLayout *hboxheightlayout = new QHBoxLayout();
	hboxheightlayout->addWidget(lineY);
	hboxheightlayout->addStretch();
	hboxheightlayout->addWidget(new QLabel(QString("y")));

	QVBoxLayout *vboxlayout = new QVBoxLayout(this);
	vboxlayout->setSpacing(0);
	vboxlayout->addLayout(hboxnamelayout);
	vboxlayout->addLayout(hboxwidthlayout);
	vboxlayout->addLayout(hboxheightlayout);

	connect(lineX,SIGNAL(editingFinished()),this,SLOT(setValue()));
	gui_holder->setPropertyValue<QPoint>(property,value);
	lineX->setText(QString("%1").arg(value.x()));
	lineY->setText(QString("%1").arg(value.y()));
	emit valueChanged(value);
	}

void QVPointParamWidget::setValue()
	{
	if(sender() == lineX ||sender() == lineY)
		{
		bool ok1, ok2;
		value = QPoint(lineX->text().toInt(&ok1), lineY->text().toInt(&ok2));
		if(not ok1 || not ok2)
			value = gui_holder->getPropertyValue<QPoint>(property);
		}
	else
		value = gui_holder->getPropertyValue<QPoint>(property);

	lineX->setText(QString("%1").arg(value.x()));
	lineY->setText(QString("%1").arg(value.y()));
	gui_holder->setPropertyValue<QPoint>(property,value);
	emit valueChanged(value);
	}

///////////////////////////
#ifdef QVIPP
QVIppiMaskSizeParamWidget::QVIppiMaskSizeParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	QHBoxLayout *hboxlayout = new QHBoxLayout(this);
	hboxlayout->setSpacing(0);
	QLabel *label = new QLabel(QString("<i>IppiMaskSize</i> <b>%1</b>").arg(property),this);
	hboxlayout->addWidget(label);
	combobox = new QComboBox(this);
	hboxlayout->addWidget(combobox);

	value = orig_holder->getPropertyValue<IppiMaskSize>(property);

	gui_holder->addProperty<IppiMaskSize>(property,QVPropertyContainer::outputFlag,value);
	gui_holder->setPropertyValue<IppiMaskSize>(property,value);

	gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

	connect(combobox,SIGNAL(activated(int)),this,SLOT(setValue()));

	QVIndexedStringList ippiMaskSizes;
	ippiMaskSizes.append("ippMskSize3x1");
	ippiMaskSizes.append("ippMskSize5x1");
	ippiMaskSizes.append("ippMskSize1x3");
	ippiMaskSizes.append("ippMskSize3x3");
	ippiMaskSizes.append("ippMskSize1x5");
	ippiMaskSizes.append("ippMskSize5x5");
	combobox->addItems(ippiMaskSizes);

	combobox->setCurrentIndex(
			(value==ippMskSize3x1)? 0:
			(value==ippMskSize5x1)? 1:
			(value==ippMskSize1x3)? 2:
			(value==ippMskSize3x3)? 3:
			(value==ippMskSize1x5)? 4:
			/*(value==ippMskSize5x5)?*/ 5);

	emit valueChanged(value);
	}

void QVIppiMaskSizeParamWidget::setValue()
	{
	value =	(combobox->currentIndex()==0)? ippMskSize3x1:
		(combobox->currentIndex()==1)? ippMskSize5x1:
		(combobox->currentIndex()==2)? ippMskSize1x3:
		(combobox->currentIndex()==3)? ippMskSize3x3:
		(combobox->currentIndex()==4)? ippMskSize1x5:
		/*(combobox->currentIndex()==0)?*/ ippMskSize5x5;

	gui_holder->setPropertyValue<IppiMaskSize>(property,value);
	emit valueChanged(value);
	}

QVIppCmpOpParamWidget::QVIppCmpOpParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	QHBoxLayout *hboxlayout = new QHBoxLayout(this);
	hboxlayout->setSpacing(0);
	QLabel *label = new QLabel(QString("<i>IppiCmpOp</i> <b>%1</b>").arg(property),this);
	hboxlayout->addWidget(label);
	combobox = new QComboBox(this);
	hboxlayout->addWidget(combobox);

	value = orig_holder->getPropertyValue<IppCmpOp>(property);

	gui_holder->addProperty<IppCmpOp>(property,QVPropertyContainer::outputFlag,value);
	gui_holder->setPropertyValue<IppCmpOp>(property,value);

	gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

	connect(combobox,SIGNAL(activated(int)),this,SLOT(setValue()));

	QVIndexedStringList ippCmpOp;
	ippCmpOp.append("ippCmpLess");
	ippCmpOp.append("ippCmpLessEq");
	ippCmpOp.append("ippCmpEq");
	ippCmpOp.append("ippCmpGreaterEq");
	ippCmpOp.append("ippCmpGreater");

	combobox->addItems(ippCmpOp);
	combobox->setCurrentIndex(
			(value==ippCmpLess)? 0:
			(value==ippCmpLessEq)? 1:
			(value==ippCmpEq)? 2:
			(value==ippCmpGreaterEq)? 3:
			/*(value==ippCmpGreater?*/ 4);
			
	emit valueChanged(value);
	}

void QVIppCmpOpParamWidget::setValue()
	{
	value =	(combobox->currentIndex()==1)? ippCmpLess:
		(combobox->currentIndex()==2)? ippCmpLessEq:
		(combobox->currentIndex()==3)? ippCmpEq:
		(combobox->currentIndex()==4)? ippCmpGreaterEq:
		/*(combobox->currentIndex()==1)?*/ ippCmpGreater;

	gui_holder->setPropertyValue<IppCmpOp>(property,value);
	emit valueChanged(value);
	}


/////////////////////////////

QVIppRoundModeParamWidget::QVIppRoundModeParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	QHBoxLayout *hboxlayout = new QHBoxLayout(this);
	hboxlayout->setSpacing(0);
	QLabel *label = new QLabel(QString("<i>IppRoundMode</i> <b>%1</b>").arg(property),this);
	hboxlayout->addWidget(label);
	combobox = new QComboBox(this);
	hboxlayout->addWidget(combobox);

	value = orig_holder->getPropertyValue<IppRoundMode>(property);

	gui_holder->addProperty<IppRoundMode>(property,QVPropertyContainer::outputFlag,value);
	gui_holder->setPropertyValue<IppRoundMode>(property,value);

	gui_holder->linkProperty(property,orig_holder,property,QVPropertyContainer::AsynchronousLink);

	connect(combobox,SIGNAL(activated(int)),this,SLOT(setValue()));

	QVIndexedStringList ippRoundMode;
	ippRoundMode.append("ippRndZero");
	ippRoundMode.append("ippRndNear");
	ippRoundMode.append("ippRndFinancial");

	combobox->addItems(ippRoundMode);
	combobox->setCurrentIndex(
			(value==ippRndZero)? 0:
			(value==ippRndNear)? 1:
			/*(value==ippRndFinancial)?*/ 2);
			
	emit valueChanged(value);
	}

void QVIppRoundModeParamWidget::setValue()
	{
	value =	(combobox->currentIndex()==1)? ippRndZero:
		(combobox->currentIndex()==2)? ippRndNear:
		/*(combobox->currentIndex()==3)?*/ ippRndFinancial;

	gui_holder->setPropertyValue<IppRoundMode>(property,value);
	emit valueChanged(value);
	}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



QVOutputIntParamWidget::QVOutputIntParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	value = orig_holder->getPropertyValue<int>(property);
	info = orig_holder->getPropertyInfo(property);

	gui_holder->addProperty<int>(property,QVPropertyContainer::inputFlag,value,"");
	_orig_holder->linkProperty(property,_gui_holder,property,QVPropertyContainer::AsynchronousLink);

	QHBoxLayout *hboxlayout = new QHBoxLayout(this);
	label = new QLabel(QString("<i>int</i> <b>%1: %2</b>").arg(property).arg(value));
	label->setToolTip(info);
	hboxlayout->addWidget(label);
	hboxlayout->addStretch();

	gui_holder->setPropertyValue<int>(property,value);
	}

void QVOutputIntParamWidget::update()
	{
	value = gui_holder->getPropertyValue<int>(property);
	label->setText(QString("<i>int</i> <b>%1: %2</b>").arg(property).arg(value));
	}

QVOutputDoubleParamWidget::QVOutputDoubleParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	value = orig_holder->getPropertyValue<double>(property);
	info = orig_holder->getPropertyInfo(property);

	gui_holder->addProperty<double>(property,QVPropertyContainer::inputFlag,value,"");
	_orig_holder->linkProperty(property,_gui_holder,property,QVPropertyContainer::AsynchronousLink);

	QHBoxLayout *hboxlayout = new QHBoxLayout(this);
	label = new QLabel(QString("<i>double</i> <b>%1: %2</b>").arg(property).arg(value));
	label->setToolTip(info);
	hboxlayout->addWidget(label);
	hboxlayout->addStretch();

	gui_holder->setPropertyValue<double>(property,value);
	}

void QVOutputDoubleParamWidget::update()
	{
	value = gui_holder->getPropertyValue<double>(property);
	label->setText(QString("<i>double</i> <b>%1: %2</b>").arg(property).arg(value));
	}

QVOutputBoolParamWidget::QVOutputBoolParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	value = orig_holder->getPropertyValue<bool>(property);
	info = orig_holder->getPropertyInfo(property);

	gui_holder->addProperty<bool>(property,QVPropertyContainer::inputFlag,value,"");
	_orig_holder->linkProperty(property,_gui_holder,property,QVPropertyContainer::AsynchronousLink);

	QHBoxLayout *hboxlayout = new QHBoxLayout(this);
	if (value) {
		label = new QLabel(QString("<i>bool</i> <b>%1: TRUE</b>").arg(property));
		label->setToolTip(info);
		}
	else {
		label = new QLabel(QString("<i>bool</i> <b>%1: FALSE</b>").arg(property));
		label->setToolTip(info);
		}
	hboxlayout->addWidget(label);
	hboxlayout->addStretch();

	gui_holder->setPropertyValue<bool>(property,value);
	}

void QVOutputBoolParamWidget::update()
	{
	value = gui_holder->getPropertyValue<bool>(property);
	if (value) {
		label = new QLabel(QString("<i>bool</i> <b>%1: TRUE</b>").arg(property));
		label->setToolTip(info);
		}
	else {
		label = new QLabel(QString("<i>bool</i> <b>%1: FALSE</b>").arg(property));
		label->setToolTip(info);
		}
	}

QVOutputStringParamWidget::QVOutputStringParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	value = orig_holder->getPropertyValue<QString>(property);
	info = orig_holder->getPropertyInfo(property);

	gui_holder->addProperty<QString>(property,QVPropertyContainer::inputFlag,value,"");
	_orig_holder->linkProperty(property,_gui_holder,property,QVPropertyContainer::AsynchronousLink);

	QHBoxLayout *hboxlayout = new QHBoxLayout(this);
	label = new QLabel(QString("<i>string</i> <b>%1: %2</b>").arg(property).arg(value));
	label->setToolTip(info);
	hboxlayout->addWidget(label);
	hboxlayout->addStretch();

	gui_holder->setPropertyValue<QString>(property,value);
	}

void QVOutputStringParamWidget::update()
	{
	value = gui_holder->getPropertyValue<QString>(property);
	label->setText(QString("<i>string</i> <b>%1: %2</b>").arg(property).arg(value));
	}

QVOutputStringListParamWidget::QVOutputStringListParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	value = orig_holder->getPropertyValue<QVIndexedStringList>(property);
	info = orig_holder->getPropertyInfo(property);

	gui_holder->addProperty<QVIndexedStringList>(property,QVPropertyContainer::inputFlag,value,"");
	_orig_holder->linkProperty(property,_gui_holder,property,QVPropertyContainer::AsynchronousLink);

	QHBoxLayout *hboxlayout = new QHBoxLayout(this);
	label = new QLabel(QString("<i>indexed string list</i> <b>%1: %2</b>").arg(property).arg(value.getCurrent()));
	label->setToolTip(info);
	hboxlayout->addWidget(label);
	hboxlayout->addStretch();

	gui_holder->setPropertyValue<QVIndexedStringList>(property,value);
	}

void QVOutputStringListParamWidget::update()
	{
	value = gui_holder->getPropertyValue<QVIndexedStringList>(property);
	label->setText(QString("<i>indexed string list</i> <b>%1: %2</b>").arg(property).arg(value.getCurrent()));
	}

QVOutputColorParamWidget::QVOutputColorParamWidget(QVPropertyContainer *_orig_holder, QVPropertyContainer *_gui_holder, const QString _property, QWidget *parent): QWidget(parent), orig_holder(_orig_holder), gui_holder(_gui_holder), property(_property)
	{
	value = orig_holder->getPropertyValue<QColor>(property);
	info = orig_holder->getPropertyInfo(property);

	gui_holder->addProperty<QColor>(property,QVPropertyContainer::inputFlag,value,"");
	_orig_holder->linkProperty(property,_gui_holder,property,QVPropertyContainer::AsynchronousLink);

	QHBoxLayout *hboxlayout = new QHBoxLayout(this);
	label = new QLabel(QString("<i>color</i> <b>%1: R = %2 G = %3 B = %4</b>").arg(property).arg(value.red()).arg(value.green()).arg(value.blue()));
	label->setToolTip(info);
	hboxlayout->addWidget(label);
	hboxlayout->addStretch();

	gui_holder->setPropertyValue<QColor>(property,value);
	}

void QVOutputColorParamWidget::update()
	{
	value = gui_holder->getPropertyValue<QColor>(property);
	label->setText(QString("<i>color</i> <b>%1: R = %2 G = %3 B = %4</b>").arg(property).arg(value.red()).arg(value.green()).arg(value.blue()));
	}
