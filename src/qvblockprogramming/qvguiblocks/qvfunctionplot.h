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

#ifndef HISTOGRAMPLOT2_H
#define HISTOGRAMPLOT2_H

#include "qvplot.h"
#include <qvdefines.h>
#include <QVector>

/*!
@class QVFunctionPlot qvblockprogramming/qvguiblocks/qvfunctionplot.h QVFunctionPlot
@brief Widget for plotting QList<double> property values from a block, as an histogram, over the time.

This class creates a widget which plots some arrays of values as functions:

@image html qvision_functionplot_window.png

For further information about its usage and functionality see section @ref QVFunctionPlotWidget

@see QVNumericPlot
@see QVCPUPlot

@ingroup qvqwt
*/

class QVFunctionPlot : public QVPlot
	{
	Q_OBJECT
	public:
		/// @brief Constructs a QVFunctionPlot with a given string identifier, and a iteration's parameters.
		/// Construct a new plot that shows QList<double> properties graphs as an histogram graph. This plot shows decorations, it hasn't got a pie graph,
		/// don't brush the data and autoshow. It can show graphs of QList<double> linked properties of different blocks.
		///
		/// @param name Identifier for the object to be created.
		/// @param time True if the iterations are based on clock time (in second hundredths), and false if they are based on block's iterations.
		/// @param step Set the base measure to plot's iterations ratio.
		/// @param maxim The left axis maximum value shown, if it is 0, the maximum value is auto scale.
		/// @param minim The left axis minimum value shown, it must be less than maximum value.
		/// @param parent Identifier for the parent widget.
		QVFunctionPlot(const QString name = QString (), bool time = true, int step = 10, QWidget *parent = 0);

	public slots:
		#ifndef DOXYGEN_IGNORE_THIS
		/// @brief Initialize the histogram plot.
		/// A histogram plot must be initialized after links all properties, and before update or shown the graphs.
		///
 		void init();
		#endif

	protected:
		void resizeEvent(QResizeEvent * e);

		/// @brief Links properties from blocks.
		/// This method safely links properties from blocks in a thread safe manner.
		/// If the iterations are based on block's iterations (time == false), the block must be synchronised with previous linked blocks.
		/// Only can be linked QList<double> properties.
		///
		/// See also QVPropertyContainer::LinkType.
		/// @param sourceContainer The container that whants to be linked.
		/// @param sourcePropName The name of the source property to be linked.
		/// @param linkType The link's type.
		bool linkUnspecifiedInputProperty(QVPropertyContainer *sourceContainer, QString sourcePropName, LinkType linkType = AsynchronousLink);

	private:
		/// @brief Returns a list with a QList<double> property curve's names.
		/// Return a list with the index of the items: 0, 1, 2, ..., list size - 1.
		///
		/// @param property The property name.
		QStringList getPropertyCurvNames(QString property) const;

		/// @brief Returns a list with a QList<double> property curve's value.
		/// Return a list with the value of the items.
		///
		/// @param property The property name.
		QList<double> getPropertyCurvValues(QString property) const;

		/// @brief Returns a list with a QList<double> property curve's index.
		/// Return a list with the order of the items: 1, 2, 3, ..., list size.
		///
		/// @param property The property name.
		QList<int> getPropertyCurvOrders(QString property) const;

		#ifndef DOXYGEN_IGNORE_THIS
		void advancePlot();
		void insertNewFlags(int cont, int prop);
		int maxAxisNumbers;
		#endif
	};

#endif

