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

#ifndef NUMERICPLOT_H
#define NUMERICPLOT_H

#include "qvplot.h"

/*!

@class QVNumericPlot qvblockprogramming/qvguiblocks/qvnumericplot.h QVNumericPlot
@brief Class for plot graphs of block's int or double properties.

Class @ref QVNumericPlot shows a widget which will read a set of integer or double values and plot their time evolution during the corresponding block execution.

The abscissa axis will display the number of iterations (or the number of elapsed seconds, depending on the boolean <i>time</i> parameter of the constructor @ref QVNumericPlot::QVNumericPlot ). The ordinate axis will scale to the maximum value of the integer or double values read from the block (or blocks) in the time interval displayed. One @ref QVNumericPlot widget can read integer or double values from several blocks, but obviously, for this to work correctly, either <i>a)</i> the blocks must be synchronized, or <i>b)</i> the QVNumericPlot should display the elapsed time in the abscissa axis (not the number of iterations).

To show the usage of the class, first we need a block that produces some integer or double output values which we are interested in monitoring. The following code shows an example:

@code
class MyBlock: public QVProcessingBlock
	{
	public:
		MyBlock(QString name): QVProcessingBlock(name)
			{
			addProperty<int>("val_int", outputFlag);
			addProperty<double>("val_double", outputFlag);
			[...]
			}

		void iterate()
			{
			int	val_int;
			double	val_double;
			[...]
			// Calculate values for 'val_int' and 'val_double' variables.
			[...]
			setPropertyValue<int>("val_int", val_int);
			setPropertyValue<double>("val_double", val_double);
			[...]
			}
	}
@endcode

And then, in the main function, we can create a QVNumericPlot object and link it with those properties, like this:

@code
#include <QVNumericPlot>

void main()
	{
	[...]
	MyBlock myBlock("block");
	QVNumericPlot numericPlot("Values int y double",false);
	myBlock.linkProperty("val_int",numericPlot);
	myBlock.linkProperty("val_double",numericPlot);
	[...]
	}
@endcode

The result will be an application showing the following window widget:

@image html qvision_numericplot_window.png

If the numeric plot would have been declared with <i>true</i> as last parameter (instead of <i>false</i>), then the abscissas axis would show time in seconds (instead of number of iterations), like this:	

@image html qvision_numericplot_window_true.png

@see QVHistogramPlot
@see QVCPUPlot

@ingroup qvqwt
*/

class QVNumericPlot : public QVPlot
	{
	Q_OBJECT
	public:
		/// @brief Constructs a QVNumericPlot with a given string identifier, and iteration's parameters.
		/// Construct a new plot that shows int and double properties graphs. This plot shows decorations, it hasn't got a pie graph, don't brush the data
		/// and autoshow. It can show graphs of int and double linked properties of different blocks.
		///
		/// @param name Identifier for the object to be created.
		/// @param time True if the iterations are based on clock time (in second hundredths), and false if they are based on block's iterations.
		/// @param step Set the base measure to plot's iterations ratio.
		/// @param parent Identifier for the parent widget.
		QVNumericPlot(const QString name = QString (), bool time = true, int step = 10, QWidget *parent = 0);

#ifndef DOXYGEN_IGNORE_THIS
	protected:
		/// @brief Links an unspecified input property.
		///
		/// This method safely links only int or double properties from blocks in a thread safe manner.
		/// When the user creates a link with an unispecified output property, the source container calls this destiny's method.
		/// If the destiny container is a QVNumericPlot lets only links from int or double properties, creates a property with the
		/// source property's name and calls the source container in order to it do the link with this new property.
		///
		/// See also linkProperty(QVProcessingBlock &block, const QString propertyName).
		/// @param sourceContainer The container that whants to be linked.
		/// @param sourcePropName The name of the source property to be linked.
		/// @param linkType The link's type.
		bool linkUnspecifiedInputProperty(QVPropertyContainer *sourceContainer, QString sourcePropName, LinkType linkType = AsynchronousLink);

	private:
		/// @brief Returns a list with a int or double property curve's names.
		/// Return a list with the name of the given property, that only contains one curve.
		///
		/// @param property The property name.
		QStringList getPropertyCurvNames(QString property) const;

		/// @brief Returns a list with a int or double property curve's value.
		/// Return a list with the value of the given property, that only contains one curve.
		///
		/// @param property The property name.
		QList<double> getPropertyCurvValues(QString property) const;

		/// @brief Returns a list with a int or double property curve's index.
		/// Return a list with the value 1 for the given property order, that only contains one curve, the first.
		///
		/// @param property The property name.
		QList<int> getPropertyCurvOrders(QString property) const;
	};
#endif
#endif

