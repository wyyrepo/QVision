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

#ifndef QVIMAGEMEANSWORKER_H
#define QVIMAGEMEANSWORKER_H

#include <QVImage>
#include <QVProcessingBlock>

/// \cond
/*!
@todo document this class
@ingroup qvblockprogramming
*/
template <typename T, int C> class QVImageMeans: public QVProcessingBlock
	{
	private:
		QVImage<T, C> mean;

	public:
		QVImageMeans(QString name = QString()): QVProcessingBlock(name)
			{
			// Input properties
			addProperty< QVImage<T,C> >("Input image", inputFlag|outputFlag);

			// Output properties
			addProperty< QVImage<T,C> >("Output image", outputFlag);
			}

		void iterate()
			{
			// 0. Read input image.
			const QVImage<T,C> image = getPropertyValue< QVImage<T,C> >("Input image");

			if (mean.getCols() != image.getCols() || mean.getRows() != image.getRows())
				mean = image;
			else	{
				QVImage<T, C> temp(mean.getCols(), mean.getRows());
				Add(image, mean, temp);
				mean = temp;
				}

			// 1. Export scaled image
			setPropertyValue< QVImage<T,C> >("Output image", mean);
			}
	};
/// \endcond

#endif
