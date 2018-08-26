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

#ifndef QVIMAGERETARDERWORKER_H
#define QVIMAGERETARDERWORKER_H

#include <QVImage>
#include <QVProcessingBlock>

#ifndef DOXYGEN_IGNORE_THIS
/*!
@todo document this class
@ingroup qvblockprogramming
*/
template <typename T, int C> class QVImageRetarderBlock: public QVProcessingBlock
	{
	private:
		QList< QVImage<T,C> > imageCache;

	public:
		QVImageRetarderBlock(QString name = QString(), const int defaultRetardedFrames = 5, const int minRetardedFrames = 0, const int maxRetardedFrames = 255): QVProcessingBlock(name)
			{
			// Input properties
			addProperty< QVImage<T,C> >("Input image", inputFlag|outputFlag);
			addProperty< int >("Second image delay", inputFlag|outputFlag, defaultRetardedFrames, "Number of frames from the input image to the second", minRetardedFrames, maxRetardedFrames);

			// Output image
			addProperty< QVImage<T,C> >("Output image", outputFlag);
			}

		void iterate()
			{
			// 0. Read input property values.
			const QVImage<T,C> image = getPropertyValue< QVImage<uChar,C> >("Input image");
			const int secondImageDelay = getPropertyValue<int>("Second image delay");

			// 2. Insert new image in image cache
			imageCache.append(image);

			// 3. Write output image
			setPropertyValue< QVImage<T,C> >("Output image", imageCache.front());

			// 4. Keep a maximum size for image cache
			while (imageCache.size() > secondImageDelay)
				imageCache.removeFirst();
			}
	};

#endif

#endif
