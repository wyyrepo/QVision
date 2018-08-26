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

#ifndef QVPARAMWIDGET_H
#define QVPARAMWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QComboBox>
#include <QLineEdit>

#include <QVProcessingBlock>
#include <QVIndexedStringList>

class QLineEdit;
class QSlider;
class QwtSlider;
class QCheckBox;
class QLabel;

#ifndef DOXYGEN_IGNORE_THIS

/// @class QVSIntParamWidget qvblockprogramming/qvguiblocks/qvparamwidget.h QVSIntParamWidget
/// @brief QVSIntParamWidget class.
///
/// This is a widget that presents an edit box and a slider to the user, where
/// he can inspect and modify the integer value of an integer type property,
/// from a QVPropertyContainer object.
/// @ingroup qvqwt
class QVSIntParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		/// @brief Creates a new QVSIntParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVSIntParamWidget and QVPropertyContainer, or a bigger widget that
		/// contains the QVSIntParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVSIntParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	signals:
		/// @brief This signal is emitted when the value of the int parameter
		/// has been changed by the user.
		void valueChanged(int);

	private slots:
		void setValue();

	private:
		int value,min,max;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QLineEdit *lineedit;
		QSlider *slider;
	};

/// @class QVUIntParamWidget
/// @brief QVUIntParamWidget class.
///
/// This is a widget that presents an edit box and a slider to the user, where
/// he can inspect and modify the integer value of an integer type property,
/// from a QVPropertyContainer object.
/// @ingroup qvqwt
class QVUIntParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		/// @brief Creates a new QVUIntParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVUIntParamWidget and QVPropertyContainer, or a bigger widget that
		/// contains the QVUIntParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVUIntParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	signals:
		/// @brief This signal is emitted when the value of the int parameter
		/// has been changed by the user.
		void valueChanged(unsigned int);

	private slots:
		void setValue();

	private:
		int value,min,max;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QLineEdit *lineedit;
		QSlider *slider;
	};

/// @class QVSCharParamWidget
/// @brief QVSCharParamWidget class.
///
/// This is a widget that presents an edit box and a slider to the user, where
/// he can inspect and modify the integer value of an integer type property,
/// from a QVPropertyContainer object.
/// @ingroup qvqwt
class QVSCharParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		/// @brief Creates a new QVUIntParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVUIntParamWidget and QVPropertyContainer, or a bigger widget that
		/// contains the QVUIntParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVSCharParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	signals:
		/// @brief This signal is emitted when the value of the int parameter
		/// has been changed by the user.
		void valueChanged(char);

	private slots:
		void setValue();

	private:
		int value,min,max;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QLineEdit *lineedit;
		QSlider *slider;
	};

/// @class QVUCharParamWidget
/// @brief QVUCharParamWidget class.
///
/// This is a widget that presents an edit box and a slider to the user, where
/// he can inspect and modify the integer value of an integer type property,
/// from a QVPropertyContainer object.
/// @ingroup qvqwt
class QVUCharParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		/// @brief Creates a new QVUIntParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVUIntParamWidget and QVPropertyContainer, or a bigger widget that
		/// contains the QVUIntParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVUCharParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	signals:
		/// @brief This signal is emitted when the value of the int parameter
		/// has been changed by the user.
		void valueChanged(unsigned char);

	private slots:
		void setValue();

	private:
		int value,min,max;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QLineEdit *lineedit;
		QSlider *slider;
	};
/// @class QVDoubleParamWidget
/// @brief QVDoubleParamWidget class.
///
/// This is a widget that presents an edit box and a slider to the user, where
/// he can inspect and modify the value of a double type property,
/// from a QVPropertyContainer object.
/// @ingroup qvqwt
class QVDoubleParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		/// @brief Creates a new QVDoubleParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVDoubleParamWidget and QVPropertyContainer, or a bigger widget
		/// that contains the QVDoubleParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVDoubleParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	signals:
		/// @brief This signal is emitted when the value of the int parameter
		/// has been changed by the user.
		void valueChanged(double);

	private slots:
		void setValue();

	private:
		double value,min,max;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QLineEdit *lineedit;
		QwtSlider *qwtslider;
	};

/// @class QVDoubleParamWidget
/// @brief QVDoubleParamWidget class.
///
/// This is a widget that presents an edit box and a slider to the user, where
/// he can inspect and modify the value of a double type property,
/// from a QVPropertyContainer object.
/// @ingroup qvqwt
class QVFloatParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		/// @brief Creates a new QVDoubleParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVDoubleParamWidget and QVPropertyContainer, or a bigger widget
		/// that contains the QVDoubleParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVFloatParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	signals:
		/// @brief This signal is emitted when the value of the int parameter
		/// has been changed by the user.
		void valueChanged(float);

	private slots:
		void setValue();

	private:
		double value,min,max;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QLineEdit *lineedit;
		QwtSlider *qwtslider;
	};


/// @class QVBoolParamWidget
/// @brief QVBoolParamWidget class.
///
/// This is a widget that presents a check box to the user, where
/// he can inspect and modify the value of a bool type property,
/// from a QVPropertyContainer object.
/// @ingroup qvqwt
class QVBoolParamWidget: public QWidget
	{
		Q_OBJECT
	public:	
		/// @brief Creates a new QVBoolParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVBoolParamWidget and QVPropertyContainer, or a bigger widget
		/// that contains the QVBoolParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVBoolParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);
	
	signals:
		/// @brief This signal is emitted when the value of the bool parameter
		/// has been changed by the user.
		void valueChanged(bool);

	private slots:
		void setValue();
	
	private:
		bool value;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QCheckBox *checkbox;
	};

/// @class QVStringParamWidget
/// @brief QVStringParamWidget class.
///
/// This is a widget that presents a line edit to the user, where
/// he can inspect and modify the value of an string type property,
/// from a QVPropertyContainer object.
/// @ingroup qvqwt
class QVStringParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		/// @brief Creates a new QVStringParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVStringParamWidget and QVPropertyContainer, or a bigger widget that
		/// contains the QVStringParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVStringParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	signals:
		/// @brief This signal is emitted when the value of the string parameter
		/// has been changed by the user.
		void valueChanged(QString);

	private slots:
		void setValue();

	private:
		QString value;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QLineEdit *lineedit;
	};

/// @class QVStringListParamWidget
/// @brief QVStringListParamWidget class.
///
/// This is a widget that presents a combo box to the user, where
/// he can inspect and select the string value of an string list type property,
/// from a QVPropertyContainer object.
/// @ingroup qvqwt
class QVStringListParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		/// @brief Creates a new QVStringListParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVStringListParamWidget and QVPropertyContainer, or a bigger widget that
		/// contains the QVStringListParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVStringListParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	signals:
		/// @brief This signal is emitted when the value of the String list parameter
		/// has been changed by the user.
		void valueChanged(QVIndexedStringList);

	private slots:
		void setValue();

	private:
		QVIndexedStringList value;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QComboBox *combobox;
	};


/// @class QVProcessingBlockTriggerWidget
/// @brief QVBoolParamWidget class.
///
/// This is a widget that presents a button to the user that, when it is
/// clicked, emits a valueChanged(QString), where the QString is the name
/// given to the trigger.
/// @ingroup qvqwt
class QVProcessingBlockTriggerWidget: public QWidget
	{
	Q_OBJECT

	public:
		/// @brief Creates a new QVProcessingBlockTriggerWidget object
		/// @param block pointer to the associated block.
		/// @param property name of the trigger that will be emitted.
		/// @param parent parent of the widget.
		QVProcessingBlockTriggerWidget(QVProcessingBlock *block, const QString triggername, QWidget *parent = 0);

	signals:
		/// @brief This signal is emitted when the corresponding button has
		///been pressed.
		void valueChanged(QString);

	private slots:
		void setValue();

	private:
		QVProcessingBlock *block;
		QString triggername;
		QToolButton *toolbutton;
	};

#include <QColor>
class QVColorParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		/// @brief Creates a new QVColorParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVColorParamWidget and QVPropertyContainer, or a bigger widget that
		/// contains the QVColorParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVColorParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	signals:
		/// @brief This signal is emitted when the value of the int parameter
		/// has been changed by the user.
		void valueChanged(QColor);

	private slots:
		void setValue();

	private:
		QColor value;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QLineEdit *lineeditR, *lineeditG, *lineeditB;
		QSlider *sliderR, *sliderG, *sliderB;
	};

#include <QSize>
class QVSizeParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		QVSizeParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	signals:
		void valueChanged(QSize);

	private slots:
		void setValue();

	private:
		QSize value;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property;
		QLineEdit *lineWidth, *lineHeight;
	};

#include <QPoint>
class QVPointParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		QVPointParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	signals:
		void valueChanged(QPoint);

	private slots:
		void setValue();

	private:
		QPoint value;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property;
		QLineEdit *lineX, *lineY;
	};

#ifdef QVIPP
#include <ipp.h>
class QVIppiMaskSizeParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		QVIppiMaskSizeParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	signals:
		void valueChanged(IppiMaskSize);

	private slots:
		void setValue();

	private:
		IppiMaskSize value;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property;
		QComboBox *combobox;
	};

class QVIppCmpOpParamWidget: public QWidget
	{
	Q_OBJECT
	public:

		QVIppCmpOpParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	signals:
		void valueChanged(IppCmpOp);

	private slots:
		void setValue();

	private:
		IppCmpOp value;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property;
		QComboBox *combobox;
	};


class QVIppRoundModeParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		QVIppRoundModeParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);
	signals:
		void valueChanged(IppRoundMode);

	private slots:
		void setValue();

	private:
		IppRoundMode value;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property;
		QComboBox *combobox;
	};
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @class QVOutputIntParamWidget
/// @brief QVOutputIntParamWidget class.
///
/// This is a widget that represents an viewe to the user, where
/// he can inspect the integer value of an integer type property,
/// from a QVPropertyContainer object.
/// @ingroup qvqwt
class QVOutputIntParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		/// @brief Creates a new QVOutputIntParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVSIntParamWidget and QVPropertyContainer, or a bigger widget that
		/// contains the QVSIntParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVOutputIntParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	private slots:
		void update();

	private:
		int value;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QLabel *label;
	};

/// @class QVOutputDoubleParamWidget
/// @brief QVOutputDoubleParamWidget class.
///
/// This is a widget that represents an viewe to the user, where
/// he can inspect the double value of an double type property,
/// from a QVPropertyContainer object.
/// @ingroup qvqwt
class QVOutputDoubleParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		/// @brief Creates a new QVOutputDoubleParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVSIntParamWidget and QVPropertyContainer, or a bigger widget that
		/// contains the QVSIntParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVOutputDoubleParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	private slots:
		void update();

	private:
		double value;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QLabel *label;
	};

/// @class QVOutputBoolParamWidget
/// @brief QVOutputBoolParamWidget class.
///
/// This is a widget that represents an viewe to the user, where
/// he can inspect the boolean value of an boolean type property,
/// from a QVPropertyContainer object.
/// @ingroup qvqwt
class QVOutputBoolParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		/// @brief Creates a new QVOutputBoolParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVSIntParamWidget and QVPropertyContainer, or a bigger widget that
		/// contains the QVSIntParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVOutputBoolParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	private slots:
		void update();

	private:
		bool value;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QLabel *label;
	};

/// @class QVOutputStringParamWidget
/// @brief QVOutputStringParamWidget class.
///
/// This is a widget that represents an viewe to the user, where
/// he can inspect the string value of an string type property,
/// from a QVPropertyContainer object.
/// @ingroup qvqwt
class QVOutputStringParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		/// @brief Creates a new QVOutputStringParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVSIntParamWidget and QVPropertyContainer, or a bigger widget that
		/// contains the QVSIntParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVOutputStringParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	private slots:
		void update();

	private:
		QString value;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QLabel *label;
	};

/// @class QVOutputStringListParamWidget
/// @brief QVOutputStringListParamWidget class.
///
/// This is a widget that represents an viewe to the user, where
/// he can inspect the QVIndexedStringList value of an QVIndexedStringList type property,
/// from a QVPropertyContainer object.
/// @ingroup qvqwt
class QVOutputStringListParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		/// @brief Creates a new QVOutputIntParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVSIntParamWidget and QVPropertyContainer, or a bigger widget that
		/// contains the QVSIntParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVOutputStringListParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	private slots:
		void update();

	private:
		QVIndexedStringList value;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QLabel *label;
	};

/// @class QVOutputColorParamWidget
/// @brief QVOutputColorParamWidget class.
///
/// This is a widget that represents an viewe to the user, where
/// he can inspect the QColor value of an QColor type property,
/// from a QVPropertyContainer object.
/// @ingroup qvqwt
class QVOutputColorParamWidget: public QWidget
	{
	Q_OBJECT
	public:
		/// @brief Creates a new QVOutputColorParamWidget object
		/// @param orig_holder pointer to property holder which contains the
		/// parameter that should be inspected.
		/// @param gui_holder pointer to property holder to which the widget
		/// will be associated. It could be simply an object which inherits both
		/// from QVSIntParamWidget and QVPropertyContainer, or a bigger widget that
		/// contains the QVSIntParamWidget (commonly, a 
		/// @ref QVParamsInspectorWidget).
		/// @param property name of the property that will be inspected.
		/// @param parent parent of the widget.
		QVOutputColorParamWidget(QVPropertyContainer *orig_holder, QVPropertyContainer *gui_holder, const QString property, QWidget *parent = 0);

	private slots:
		void update();

	private:
		QColor value;
		QVPropertyContainer *orig_holder,*gui_holder;
		QString property, info;
		QLabel *label;
	};

#endif
#endif

