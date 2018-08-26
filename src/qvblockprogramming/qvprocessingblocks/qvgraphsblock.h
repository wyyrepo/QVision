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

#ifndef QVGRAPHSWORKER_H
#define QVGRAPHSWORKER_H

#include <qvipp.h>
#include <qvip.h>

#include <QVImage>
#include <QVProcessingBlock>

/// \cond
/*!
@todo document this class
@ingroup qvblockprogramming
*/
class QVGraphsBlock: public QVProcessingBlock
	{
	public:
		QVGraphsBlock(QString name = QString()): QVProcessingBlock(name)
			{
			addProperty< QVImage<uChar,1> >("Input image", inputFlag|outputFlag);
			addProperty< QVImage<uChar,1> >("Output image", outputFlag);
			addProperty<int>("Max pixel", outputFlag);
			addProperty<int>("Min pixel", outputFlag);
// 			addProperty<QList<double> >("MinMaxList", outputFlag);
// 			addProperty<QList<double> >("FirstRow", outputFlag);
			}

		void iterate()
			{
			QVImage<uChar> image = getPropertyValue< QVImage<uChar,1> >("Input image");
			uchar min, max;
			Max(image, max);
			Min(image, min);
			setPropertyValue<int>("Max pixel", max);
			setPropertyValue<int>("Min pixel", min);
/*			QList<double> minmaxlist;
			minmaxlist << min << max;
			setPropertyValue<QList<double> >("MinMaxList", minmaxlist);

			QList<double> firstrow;
			for (uint i = 0; i < image.getCols(); i++) firstrow << image(i, 0);
			setPropertyValue<QList<double> >("FirstRow", firstrow);
*/
			QVImage<uChar> dest(image);
			AddC(image, 10, dest);
			setPropertyValue< QVImage<uChar,1> >("Output image", dest);
			}
	};
/// \endcond

#endif
