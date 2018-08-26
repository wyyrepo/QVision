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

#ifndef CPUPLOT_H
#define CPUPLOT_H

#include "qvplot.h"
#include <qvblockprogramming/qvcpustat.h>

/*!
@class QVCPUPlot qvblockprogramming/qvguiblocks/qvcpuplot.h QVCPUPlot
@brief Class for plot graphs of block's cpustat properties.

This class lets us plot graphs for QVStat block's output properties. Each @ref QVProcessingBlock object is created with a property containing a stat object, resuming its time consumption and internal statistics. The class @ref QVCPUPlot can be used to plot those time statistics.

The following code features how to create a CPU plot object in a QVision application:

\code
void main()
	{
	[...]
	ComponentTreeBlock componentTreeBlock("Component Tree");
	CannyBlock cannyBlock("Canny operator");
	ContourPainter contourPainter("Contour painter");
	[...]
	QVCPUPlot cpuPlot("CPU Plot", true, 10);
	componentTreeBlock.linkProperty("cpu stats", cpuPlot);
	cannyBlock.linkProperty("cpu stats", cpuPlot);
	contourPainter.linkProperty("cpu stats", cpuPlot);
	[...]
	}
\endcode

This application will display a plot like the following:

\image html qvision_cpuplot_window.png

By default, the @ref QVDefaultGUI includes the following button for CPU plot statistics displaying, which opens a @ref QVNumericPlot widget plotting the block CPU usage:

\image html qvision_gui_graphbutton.png

@see QVNumericPlot
@see QVHistogramPlot

@ingroup qvqwt
*/
class QVCPUPlot : public QVPlot
	{
	Q_OBJECT
	public:
		/// @brief Constructs a QVCPUPlot with a given string identifier, showing properties and iteration's parameters.
		///
		/// @param name Identifier for the object to be created.
		/// @param decorations Indicate if the plot must shown the scale axis.
		/// @param autoShow Indicate if the plot are shown at the beginning or must be shown by the user.
		/// @param time True if the iterations are based on clock time (in second hundredths), and false if they are based on block's iterations.
		/// @param step Set the base measure to plot's iterations ratio.
		/// @param parent Identifier for the parent widget.
		QVCPUPlot(const QString name = QString(), bool decorations = true, bool autoShow = true, bool time = true, int step = 100, QWidget *parent = 0);

#ifndef DOXYGEN_IGNORE_THIS
	protected:
		/// @brief Links an unspecified input property.
		///
		/// This method safely links only QVStat properties from blocks in a thread safe manner.
		/// When the user creates a link with an unispecified output property, the source container calls this destiny's method.
		/// If the destiny container is a QVCPUPlot lets only links from QVStat properties, creates a property with the source
		/// property's name and calls the source container in order to it do the link with this new property.
		///
		/// See also linkProperty(QVProcessingBlock &block, const QString propertyName).
		/// @param sourceContainer The container that whants to be linked.
		/// @param sourcePropName The name of the source property to be linked.
		/// @param linkType The link's type.
		bool linkUnspecifiedInputProperty(QVPropertyContainer *sourceContainer, QString sourcePropName, LinkType linkType = AsynchronousLink);

	private:
		/// @brief Returns a list with a int or double property curve's names.
		/// Return a list with the flag's names of the given cpustat property, one for each block's time flag.
		///
		/// @param property The property name.
		QStringList getPropertyCurvNames(QString property) const;

		/// @brief Returns a list with a int or double property curve's value.
		/// Return a list with the time value of the property flags, one for each block's time flag.
		///
		/// @param property The property name.
		QList<double> getPropertyCurvValues(QString property) const;

		/// @brief Returns a list with a int or double property curve's index.
		/// Return a list with the order with the flags appears in the block. In order to a time flag that not appear in the firsts iterations can't be
		/// shown out of order. The order begins to 1.
		///
		/// @param property The property name.
		QList<int> getPropertyCurvOrders(QString property) const;
	};
#endif
#endif

