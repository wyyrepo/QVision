/*
 *	Copyright (C) 2008, 2009, 2010, 2011, 2012. PARP Research Group.
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

/*!
@file
@ingroup ExamplePrograms
@brief Example usage for the Designer User Interface

The Designer User Interface allows the user to dynamically modify the block and linking structure of a QVision application, adding new processing nodes to its structure, deleting them, or creating new data connections between them.

@section Usage Usage of the program.
Once QVision has been correctly installed in your system, compile using the <i>qmake</i> and <i>make</i> tools:
@code # qmake; make @endcode
Execute the application with the following line:
@code ./designer @endcode
For example:

See section @ref QVDesignerGUI for further info about the Designer Interface.

@author PARP Research Group. University of Murcia, Spain.
*/

#include <QVDesignerGUI>
#include <QVApplication>
#include <QVCannyEdgeDetector>
#include <QVVideoReaderBlock>
#include <QVImageCanvas>

#include <QVProcessingBlock>
#include <qvip.h>

//#include <qvipp.h>

#include <qvmath.h>
#include <QV2DMap>

#ifndef DOXYGEN_IGNORE_THIS
/*class QVMyFilterHipass: public QVProcessingBlock
	{
	public:
		QVMyFilterHipass(QString name = QString()): QVProcessingBlock(name)
			{
			addProperty< QVImage<uChar,3> >("Input image", inputFlag|outputFlag);
			addProperty< QVImage<uChar,3> >("Output image", outputFlag);
			addProperty< IppiMaskSize >("mask", inputFlag, ippMskSize5x5);
			addProperty< QPoint >("destROIOffset", inputFlag);
			}

		void iterate()
			{
			// 0. Read input image.
			const QVImage<uChar, 3> qvimage_pSrc = getPropertyValue< QVImage<uChar, 3> > ("Input image");
			const IppiMaskSize mask = getPropertyValue< IppiMaskSize > ("mask");
			const QPoint destROIOffset = getPropertyValue< QPoint > ("destROIOffset");
		
			QVImage<uChar, 3> qvimage_pDst;
		
			FilterHipass(qvimage_pSrc, qvimage_pDst, mask, destROIOffset);
			setPropertyValue< QVImage<uChar, 3> >("Output image", qvimage_pDst);
			}
	};*/

class QVSFloatC1MaximalPoints: public QVProcessingBlock
	{
	public:
		QVSFloatC1MaximalPoints(QString name = QString()): QVProcessingBlock(name)
			{
			// Input properties
			addProperty< QVImage<sFloat> >("Input image", inputFlag|outputFlag);
			addProperty< double >("Threshold", inputFlag);
			addProperty< int >("Radius", inputFlag);

			// Output properties
			addProperty< QList<QPointF> >("max", outputFlag);
			}

		void iterate()
			{
			// 0. Read input image.
			const QVImage<sFloat> image = getPropertyValue< QVImage<sFloat> >("Input image");
			const double threshold = getPropertyValue< double >("Threshold");
			const int radius = getPropertyValue< int >("Radius");

			QMap<sFloat, QPointF> map = maximalPoints(image, threshold, radius);

			// 1. Export single-channel images
			setPropertyValue< QList<QPointF> >("max", map.values());
			}
	};

int main(int argc, char *argv[])
	{
	QVApplication app(argc, argv, "Example application for QVision.", true );
	
	//QVDesignerGUI::registerUserType<QVMyFilterHipass>("QVMyFilterHipass");
	QVDesignerGUI::registerUserType<QVSFloatC1MaximalPoints>("QVSFloatC1MaximalPoints");

 //   QVMyFilterHipass hipass("Hipass");
    QVSFloatC1MaximalPoints max("Maximal");

	QVDesignerGUI interface;

	return app.exec();
	}

#endif
