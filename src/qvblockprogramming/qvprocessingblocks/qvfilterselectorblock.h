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

#ifndef QVFILTERSELECTORWORKER_H
#define QVFILTERSELECTORWORKER_H

#include <qvipp.h>
#include <qvip.h>

#include <QVImage>
#include <QVProcessingBlock>

#include <QVIndexedStringList>

/// \cond
/*!
@todo document this class
@ingroup qvblockprogramming
*/
template <typename T, int C> class QVFilterSelectorBlock: public QVProcessingBlock
	{
	private:
		QVIndexedStringList firstFilter;

		//////////////////
		// Function that apply a canny filter
		QVImage<T,1> cannyIterate(QVImage<T,1> image, double threLow, double threHigh)
			{
			//////////////////
			// Read input parameters
			uInt cols = image.getCols(), rows = image.getRows();
			QVImage<sFloat>	imageFloat(cols, rows), dX(cols, rows), dY(cols, rows), dXNeg(cols, rows);
			QVImage<uChar>	canny(cols, rows), buffer;
		
			//////////////////
			// Convert image from uChar to sShort
			Convert(image, imageFloat);
		
			//////////////////
			// Obtain horizontal and vertical gradients from image
			FilterSobelHorizMask(imageFloat, dY, ippMskSize3x3);
			FilterSobelVertMask(imageFloat, dX, ippMskSize3x3);
			MulC(dX, -1, dXNeg);
		
			/////////////////
			// Apply Canny operator
			CannyGetSize(canny, buffer);
			Canny(dXNeg, dY, canny, threLow, threHigh, buffer);
		
			/////////////////
			// Publish resulting images
			return canny;
			}


		//////////////////
		// Function that apply the selected filter
		QVImage<T,1> applyFilter(QVImage<T,1> image, int choice, double threLow, double threHigh, bool sizeOf5, int maskRow, int maskCol)
			{
			switch (choice)
				{
				case 0: // None
					{
					break;
					}
				case 1: // Canny
					{
					image = cannyIterate(image, threLow, threHigh);
					break;
					}
				case 2: // Hessian
					{
					QVImage<sFloat, 1> auxImage(image);
					FilterHessianCornerResponseImage(image, auxImage);
					Ln(auxImage, auxImage);
					FilterNormalize(auxImage, image);
					break;
					}
				case 3: // Harris
					{
					QVImage<sFloat, 1> auxImage(image);
					FilterHarrisCornerResponseImage(image, auxImage);
					Ln(auxImage, auxImage);
					FilterNormalize(auxImage, image);
					break;
					}
				case 4: // DOG
					{
					QVImage<sFloat, 1> auxImage(image);
					//FilterDoG(image, auxImage);
					Ln(auxImage, auxImage);
					FilterNormalize(auxImage, image);
					break;
					}
				case 5: // Gauss
					{
					QVImage<sFloat, 1> auxImage(image);
					if (sizeOf5)
						FilterGauss(image, auxImage, ippMskSize5x5);
					else
						FilterGauss(image, auxImage, ippMskSize3x3);
					return auxImage;
					break;
					}
				case 6: // Sharpen
					{
					QVImage<sFloat, 1> auxImage(image);
					FilterSharpen(image, auxImage);
					return auxImage;
					break;
					}
				case 7: // Box
					{
					QVImage<sFloat, 1> auxImage(image);
					FilterBox(image, auxImage, QSize(maskRow, maskCol));
					return auxImage;
					break;
					}
				}
			return image;
			}

	public:
		QVFilterSelectorBlock(QString name = QString()): QVProcessingBlock(name)
			{
			//////////////////
			// Generate the filter's combobox
			firstFilter.append("None");
			firstFilter.append("Canny");
			firstFilter.append("Hessian");
			firstFilter.append("Harris");
			firstFilter.append("DOG");
			firstFilter.append("Gauss");
			firstFilter.append("Sharpen");
			firstFilter.append("Box");
			addProperty< QVIndexedStringList >("Filter", inputFlag, firstFilter);

			//////////////////
			// Generate the filter's parameters
			addProperty<bool>("Mask: Size of 5 (gauss)", inputFlag, false);
			addProperty<int>("Mask: Row (Box)", inputFlag, 3, "Row Mask Size", 1, 10);
			addProperty<int>("Mask: Col (Box)", inputFlag, 3, "Col Mask Size", 1, 10);

			addProperty<double>("Threshold high (canny)", inputFlag, 150, "High threshold for Canny operator", 50, 1000);
			addProperty<double>("Threshold low (canny)", inputFlag, 50, "Low threshold for Canny operator", 10, 500);

			
			addProperty< QVImage<T,C> >("Input image", inputFlag|outputFlag);
			addProperty< QVImage<T,C> >("Output image", outputFlag);
			}

		void iterate()
			{
			QVImage<T,1> image = getPropertyValue< QVImage<uChar,C> >("Input image");

			//////////////////
			// Get the parameters's current values
			const QVIndexedStringList auxFF = getPropertyValue<QVIndexedStringList>("Filter");

			const double threLow = getPropertyValue<double>("Threshold low (canny)");
			const double threHigh = getPropertyValue<double>("Threshold high (canny)");

			const bool sizeOf5 = getPropertyValue<bool>("Mask: Size of 5 (gauss)");
			const int maskRow = getPropertyValue<int>("Mask: Row (Box)");
			const int maskCol = getPropertyValue<int>("Mask: Col (Box)");
			timeFlag("Read input parameters");

			//////////////////
			// Apply the filter
			QVImage<T,C> filteredImage = applyFilter(image, auxFF.getIndex(), threLow, threHigh, sizeOf5, maskRow, maskCol);
			timeFlag("Apply the filter");

			setPropertyValue< QVImage<T,C> >("Output image", filteredImage);
			timeFlag("Write input parameters");
			}
	};
/// \endcond

#endif
