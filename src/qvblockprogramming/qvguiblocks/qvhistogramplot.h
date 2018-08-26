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

#ifndef HISTOGRAMPLOT_H
#define HISTOGRAMPLOT_H

#include "qvplot.h"
#include "qvhistogram.h"
#include <qvdefines.h>
#include <QVector>

/*!
@class QVHistogramPlot qvblockprogramming/qvguiblocks/qvhistogramplot.h QVHistogramPlot
@brief Widget for plotting QList<double> property values from a block, as an histogram, over the time.

Class @ref QVHistogramPlot shows a widget which will read a QList<double> from a block's output property, and will continuously plot its evolution in time during block execution.

The abscissas axis will correspond to the QList size, while the ordinate axis will scale to the maximum value of the double values in the list read from the block.

To show the usage of the class, we need again a block which produces the QList<double> of values to be plotted. The following code shows an example:

@code
class MyBlock: public QVProcessingBlock
	{
	public:
		MyBlock(QString name): QVProcessingBlock(name)
			{
			addProperty<QList<double> >("histogram", outputFlag);
			[...]
			}

		void iterate()
			{
			QList<double> histogram;
			[...]
			// Calculate values for the 'histogram' variable.
			[...]
			setPropertyValue<QList<double> >("histogram", histogram);
			[...]
			}
	}
@endcode

And then, in the main function, we can create a QVHistogramPlot and link it with that property, like this:

@code
#include <QVHistogramPlot>

void main()
	{
	[...]
	MyBlock myBlock("block");
	QVHistogramPlot histPlot("Histogram", false, 1);
	myBlock.linkProperty(histPlot,"histogram");
	[...]
	}
@endcode

The result will be an application showing the following window widget:

@image html qvision_histogramplot_window.png

The second and third parameters in the constructor of the @ref QVListPlot correspond to time (true) or iteration (false) based operation, and the refreshing interval (in hundreths of seconds, in the first case, or in absolute number of iterations, in the second case).

@see QVNumericPlot
@see QVCPUPlot

@ingroup qvqwt
*/

class QVHistogramPlot : public QVPlot
	{
	Q_OBJECT
	public:
		/// @brief Constructs a QVHistogramPlot with a given string identifier, and a iteration's parameters.
		/// Construct a new plot that shows QList<double> properties graphs as an histogram graph. This plot shows decorations, it hasn't got a pie graph,
		/// don't brush the data and autoshow. It can show graphs of QList<double> linked properties of different blocks.
		///
		/// @param name Identifier for the object to be created.
		/// @param time True if the iterations are based on clock time (in second hundredths), and false if they are based on block's iterations.
		/// @param step Set the base measure to plot's iterations ratio.
		/// @param maxim The left axis maximum value shown, if it is 0, the maximum value is auto scale.
		/// @param minim The left axis minimum value shown, it must be less than maximum value.
		/// @param parent Identifier for the parent widget.
		QVHistogramPlot(const QString name = QString (), bool time = true, int step = 10, double maxim = 0, double minim = 0, QWidget *parent = 0);

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

		QVHistogram histItem;
		double max, min;
		int maxAxisNumbers;
		#endif
	};

#endif

