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

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <iostream>

#include <qvip.h>
#include <qvmath.h>
#include <qvdefines.h>
#include <qvmatrixalgebra.h>
#include <QVPolyline>
#include <QVPolylineF>
#include <QList>

#include<qvip/fast-C-src-2.1/fast.h>

#ifdef QVIPP
#include <qvipp.h>
#endif

#ifndef QVIPP
QVector<int> HistogramRange(const QVImage<uChar, 1> &src)
	{
	QVector< int > result(256);

	QVIMAGE_INIT_READ(uChar,src);
	for(uInt row = 0; row < src.getRows(); row++)
		for(uInt col = 0; col < src.getCols(); col++)
			result[QVIMAGE_PIXEL(src, col, row,0)]++;

	return result;
	}
#endif

QVector< QVector< QPoint > > CountingSort(const QVImage<uChar, 1> &image)
	{
	QVector< QVector <QPoint> > result(256);
	const QVector<int> histogram = HistogramRange(image);

	for (int k=0; k<256; k++)
		result[k].reserve(histogram[k]);

	QVIMAGE_INIT_READ(uChar,image);
	for(uInt row = 0; row < image.getRows(); row++)
		for(uInt col = 0; col < image.getCols(); col++)
			result[QVIMAGE_PIXEL(image, col, row,0)].append(QPoint(col, row));
	
	return result;
	}

QList<QPointF> getLocalExtremaPixels(const QVImage<uChar, 1> responseImg, const int threshold)
	{
	const uChar	*imgData = responseImg.getReadData();
	const int	imgStep = responseImg.getStep();
	const int	minX = responseImg.getROI().x(),
			maxX = minX + responseImg.getROI().width(),
			minY = responseImg.getROI().y(),
			maxY = minY + responseImg.getROI().height();
			
	QList<QPointF> pointsHi;
	const int imgStepX2 = imgStep*2;
	for(int i = minY + 2; i < maxY-2; i++)
		{
		const uChar *rowData = imgData + i*imgStep;
		//uChar *gaussRowData = gaussData + i*gaussStep;
		for(int j = minX + 2; j < maxX-2; j++)
			if (rowData[j] > threshold)
				{
				const uChar value = rowData[j];

				if (value <= rowData[j-1])
					continue;
				if (value <= rowData[j+1])
					continue;
				if (value <= rowData[j+imgStep])
					continue;
				if (value <= rowData[j-imgStep])
					continue;
				if (value <= rowData[j-1+imgStep])
					continue;
				if (value <= rowData[j+1+imgStep])
					continue;
				if (value <= rowData[j-1-imgStep])
					continue;
				if (value <= rowData[j+1-imgStep])
					continue;

				// ---------------------------------
				if (value <= rowData[j-2])
					continue;
				if (value <= rowData[j+2])
					continue;
				if (value <= rowData[j+imgStepX2])
					continue;
				if (value <= rowData[j-imgStepX2])
					continue;
				if (value <= rowData[j-2+imgStepX2])
					continue;
				if (value <= rowData[j+2+imgStepX2])
					continue;
				if (value <= rowData[j-2-imgStepX2])
					continue;
				if (value <= rowData[j+2-imgStepX2])
					continue;

				// ---------------------------------
				if (value <= rowData[j-2+imgStep])
					continue;
				if (value <= rowData[j-2-imgStep])
					continue;
				if (value <= rowData[j+2+imgStep])
					continue;
				if (value <= rowData[j+2-imgStep])
					continue;
				if (value <= rowData[j+1+imgStepX2])
					continue;
				if (value <= rowData[j-1+imgStepX2])
					continue;
				if (value <= rowData[j+1+imgStepX2])
					continue;
				if (value <= rowData[j-1+imgStepX2])
					continue;

				pointsHi << QPointF(j+2,i+2);
				}
		}
	return pointsHi;
	}

double ShiTomasiScore(	const uChar *imagePtr, const int imageStep,
			const int x, const int y,
			const int nHalfBoxSize)
	{
	float dXX = 0.0, dYY = 0.0, dXY = 0.0;
	  
	for(int ir_y = y - nHalfBoxSize; ir_y <= y + nHalfBoxSize; ir_y++)
		for(int ir_x = x - nHalfBoxSize; ir_x <= x + nHalfBoxSize; ir_x++)
		{
		int imageIndex = ir_x + ir_y * imageStep;
		float	dx = imagePtr[imageIndex +1] - imagePtr[imageIndex-1],
			dy = imagePtr[imageIndex + imageStep] - imagePtr[imageIndex - imageStep];

		dXX += dx*dx;
		dYY += dy*dy;
		dXY += dx*dy;
		}

	int nPixels = 2.0 * POW2(2*nHalfBoxSize+1);
	dXX = dXX / nPixels;
	dYY = dYY / nPixels;
	dXY = dXY / nPixels;
	  
	// Find and return smaller eigenvalue:
	return 0.5 * (dXX + dYY - sqrt( (dXX + dYY) * (dXX + dYY) - 4.0 * (dXX * dYY - dXY * dXY) ));
	};

QMap<double, QPointF> pointsByShiTomasiValue(const QVImage<uChar, 1> & image, const QList<QPointF> &points, const int shiTomasiRadius)
	{
	const int	imgCols = image.getCols(),
			imgRows = image.getRows(),
			maxCol = imgCols - shiTomasiRadius -1,
			maxRows = imgRows - shiTomasiRadius - 1;

	const int imageStep = image.getStep();
	const uChar *imagePtr = image.getReadData();

	// Insert corners in the map, sorted by their Shi-Tomasi score.
	QMap<double, QPointF> pointsMap;
	foreach(QPointF point, points)
		{
		const double x = point.x(), y = point.y();
		if ( x > shiTomasiRadius and x < maxCol and y > shiTomasiRadius and y < maxRows)
			pointsMap.insertMulti( -ShiTomasiScore(imagePtr, imageStep, x, y, shiTomasiRadius), point);
		}
	return pointsMap;
	}

#ifdef QVIPP
QList<QPointF> hiPassPointDetector(const QVImage<uChar, 1> &image, const int threshold)
	{
	QVImage<uChar, 1> gauss3x3;
	FilterGauss(image, gauss3x3, ippMskSize3x3, image.getROI().topLeft() + QPoint(1,1));

	QVImage<uChar, 1> hiPass;
	FilterHipass(gauss3x3, hiPass, ippMskSize3x3, gauss3x3.getROI().topLeft() + QPoint(1,1));

	return getLocalExtremaPixels(hiPass, threshold);
	}

QList<QPointF> DoGPointDetector(const QVImage<uChar, 1> &image, const int threshold)
	{
	QVImage<uChar, 1> gauss3x3;
	FilterGauss(image, gauss3x3, ippMskSize3x3, image.getROI().topLeft() + QPoint(1,1));

	QVImage<uChar, 1> gauss5x5;
	FilterGauss(gauss3x3, gauss5x5, ippMskSize3x3, gauss3x3.getROI().topLeft() + QPoint(1,1));

	gauss3x3.setROI(gauss5x5.getROI());

	QVImage<uChar, 1> absDiff;
	AbsDiff(gauss3x3, gauss5x5, absDiff, gauss5x5.getROI().topLeft());

	return getLocalExtremaPixels(absDiff, threshold);
	}

/*QList<QPointF> hiPassPointDetector(const QVImage<uChar, 1> &image, const int threshold)
	{
	QVImage<uChar, 1> gauss3x3;
	FilterGauss(image, gauss3x3, ippMskSize3x3, QPoint(1,1));

	QVImage<uChar, 1> hiPass;
	FilterHipass(gauss3x3, hiPass, ippMskSize3x3, QPoint(1,1));

	return getLocalExtremaPixels(hiPass, threshold);
	}

QList<QPointF> DoGPointDetector(const QVImage<uChar, 1> &image, const int threshold)
	{
	QVImage<uChar, 1> gauss3x3;
	FilterGauss(image, gauss3x3, ippMskSize3x3, QPoint(1,1));

	QVImage<uChar, 1> gauss5x5;
	FilterGauss(gauss3x3, gauss5x5, ippMskSize3x3, QPoint(1,1));

	gauss3x3.setROI(gauss5x5.getROI());

	QVImage<uChar, 1> absDiff;
	AbsDiff(gauss3x3, gauss5x5, absDiff);
	return getLocalExtremaPixels(absDiff, threshold);
	}*/

void FilterHarrisCornerResponseImage(const QVImage<uChar> &image, QVImage<sFloat> &result, int aperture, int avgwindow, const QPoint &/*destROIOffset*/)
	{
	QVImage<uChar> buffer;
	MinEigenValGetBufferSize(image, buffer);

	MinEigenVal(image, result, ippKernelSobel, aperture, avgwindow, buffer);
	}

void FilterDoG(const QVImage<uChar> &image, QVImage<uChar> &result)
	{
	const uInt rows = image.getRows(), cols = image.getCols();
	QVImage<uChar> gauss3x3(cols, rows), gauss5x5(cols, rows);
	
	// ¿TODO: llevar a mismo marco común?
	FilterGauss(image, gauss3x3, ippMskSize3x3, QPoint(1,1));
	FilterGauss(image, gauss5x5, ippMskSize5x5, QPoint(2,2));

	gauss3x3.setROI(gauss5x5.getROI());

	AbsDiff(gauss3x3, gauss5x5, result);	
	}

void SobelCornerResponseImage(const QVImage<sFloat> &image, QVImage<sFloat> &result)
	{
	std::cerr << "WARNING: SobelCornerResponseImage is deprecated. Use FilterHessianCornerResponseImage instead." << std::endl;
	FilterHessianCornerResponseImage(image, result);
	}

void FilterHessianCornerResponseImage(const QVImage<sFloat> &image, QVImage<sFloat> &result, const QPoint &destROIOffset)
	{
	QVImage<sFloat> Gx, Gy, Gxx, Gxy, Gyy, GxyGxy, GxxGyy;

	FilterSobelHorizMask(image,Gx, ippMskSize3x3);
	FilterSobelVertMask(image,Gy, ippMskSize3x3);

	FilterSobelHorizMask(Gx,Gxx, ippMskSize3x3, QPoint(2,2));
	FilterSobelVertMask(Gy,Gyy, ippMskSize3x3, QPoint(2,2));
	FilterSobelVertMask(Gx,Gxy, ippMskSize3x3, QPoint(2,2));

	Gxx.setROI(Gxy.getROI());
	Gyy.setROI(Gxy.getROI());

	Mul(Gxy, Gxy, GxyGxy);
	Mul(Gxx, Gyy, GxxGyy);
	AbsDiff(GxyGxy, GxxGyy, result, destROIOffset);
	}

#ifdef GSL_AVAILABLE
void FilterSeparable(const QVImage<sFloat, 1> &image, QVImage<sFloat, 1> &dest,
	const QVVector &rowFilter, const QVVector &colFilter, const QPoint &destROIOffset)
	{
	const uInt cols = image.getCols(), rows = image.getRows();
	QVImage<sFloat> rowFiltered(cols, rows);
	FilterRow(image, rowFiltered, rowFilter);
	FilterColumn(rowFiltered, dest, colFilter, destROIOffset);
	}
#endif // GSL_AVAILABLE

QMap<sFloat, QPointF>  fastMaximalPoints(const QVImage<sFloat> &image, const double threshold, const int windowRadius)
	{
	QVImage<sFloat> maxImage;
	FilterMax(image, maxImage, QSize(2*windowRadius+1, 2*windowRadius+1), QPoint(0,0), image.getROI().topLeft() + QPoint(windowRadius, windowRadius));

	const QRect	ROI = maxImage.getROI();
	const int	maxStep = maxImage.getStep() / sizeof(sFloat),
			imageStep = image.getStep() / sizeof(sFloat);

	QMap<sFloat, QPointF> sortedPoints;

	sFloat *actualPtr = (sFloat *) image.getReadData() + (imageStep + 1) * windowRadius;
	sFloat *maxPtr = (sFloat *) maxImage.getReadData() + (maxStep + 1) * windowRadius;

	for(int j = 0; j < ROI.height(); j++, actualPtr += imageStep, maxPtr += maxStep)
		for(int i = 0; i < ROI.width(); i++)
			if ( (actualPtr[i] >= threshold) and (maxPtr[i] == actualPtr[i]) )
				sortedPoints.insertMulti(-actualPtr[i], QPointF(i+ROI.x(), j+ROI.y()));	

	return sortedPoints;
	}

QMap<uChar, QPointF>  fastMaximalPoints(const QVImage<uChar> &image, const double threshold, const int windowRadius)
	{
	QVImage<uChar> maxImage;
	FilterMax(image, maxImage, QSize(2*windowRadius+1, 2*windowRadius+1), QPoint(0,0), image.getROI().topLeft() + QPoint(windowRadius, windowRadius));

	const QRect	ROI = maxImage.getROI();
	const int	maxStep = maxImage.getStep() / sizeof(uChar),
				imageStep = image.getStep() / sizeof(uChar);

	QMap<uChar, QPointF> sortedPoints;

	uChar *actualPtr = (uChar *) image.getReadData() + (imageStep + 1) * windowRadius;
	uChar *maxPtr = (uChar *) maxImage.getReadData() + (maxStep + 1) * windowRadius;

	for(int j = 0; j < ROI.height(); j++, actualPtr += imageStep, maxPtr += maxStep)
		for(int i = 0; i < ROI.width(); i++)
			if ( (actualPtr[i] >= threshold) and (maxPtr[i] == actualPtr[i]) )
				sortedPoints.insertMulti(-actualPtr[i], QPointF(i+ROI.x(), j+ROI.y()));	

	return sortedPoints;
	}

#define DEFINE_QVDTA_FUNCTION_NORMALIZE(TYPE, C)								\
void FilterNormalize(const QVImage<TYPE,C> &image, QVImage<TYPE,C> &equalized, const QPoint &destROIOffset)		\
	{														\
	TYPE	maxVal, minVal;						\
									\
	Max(image,maxVal);						\
	Min(image,minVal);						\
									\
	QVImage<TYPE,C> temp, result;					\
	SubC(image, minVal, temp);					\
	MulC(temp, 255/(maxVal-minVal), result, 1, destROIOffset);	\
	equalized = result;						\
	}

DEFINE_QVDTA_FUNCTION_NORMALIZE(uChar,1);

#define DEFINE_QVDTA_FUNCTION_NORMALIZE2(TYPE, C)								\
void FilterNormalize(const QVImage<TYPE,C> &image, QVImage<TYPE,C> &equalized, const QPoint &destROIOffset)		\
	{														\
	uInt	rows = image.getRows(), cols = image.getCols();		\
	TYPE	maxVal, minVal;						\
									\
	Max(image,maxVal);						\
	Min(image,minVal);						\
									\
	QVImage<TYPE,C> temp(cols, rows), result(cols, rows);		\
	SubC(image, minVal, temp);					\
	MulC(temp, 255/(maxVal-minVal), result, destROIOffset);		\
	equalized = result;						\
	}
DEFINE_QVDTA_FUNCTION_NORMALIZE2(sFloat,1);
#endif // IPP_AVAILABLE

void FilterLocalMax(const QVImage<sFloat> &src, QVImage<uChar> &dest, uInt colMaskSize, uInt rowMaskSize, sFloat threshold)
	{
	const int cols = src.getCols(), rows = src.getRows();
	Set(0, dest);
	sFloat actual;
	QVIMAGE_INIT_READ(sFloat,src);
	QVIMAGE_INIT_WRITE(uChar,dest);
	for(int row = ((int)rowMaskSize); row < rows-((int)rowMaskSize); row++)
		for(int col = ((int)colMaskSize); col < cols-((int)colMaskSize); col++)
			{
			actual = QVIMAGE_PIXEL(src, col, row,0);
			if (actual >= threshold)
				{
				QVIMAGE_PIXEL(dest, col, row, 0) = std::numeric_limits<unsigned char>::max();
				for (int j = ((int)row-rowMaskSize); (j < row+((int)rowMaskSize)) && (QVIMAGE_PIXEL(dest, col, row, 0) > 0); j++)
					for (int i = ((int)col-colMaskSize); i < col+((int)colMaskSize); i++)
						if ( ((i != col) || (j != row)) && (actual <= QVIMAGE_PIXEL(src, i, j, 0)) )
							{
							QVIMAGE_PIXEL(dest, col, row, 0) = 0;
							break;
							}
				}
			}
	}

/// @todo this function is deprecated: erase it and replace calls to it by IPP's flood fill function.
int myFloodFill(QVImage<uChar> &image, uInt x, uInt y, uInt value, uInt minVal, uInt maxVal)
	{
	// Value should be inside range [minVal, maxVal]
	Q_ASSERT( (value <= minVal) || (value >= maxVal) );
	Q_ASSERT( minVal <= maxVal );

	// Coordinates should be inside the image.
	if ( (x >= image.getCols()) || (y >= image.getRows()))
		return 0;

	if ( (image(x,y) < minVal) || (image(x,y) > maxVal) )
		return 0;

	image(x,y) = value;

	int val = 1;
	val += myFloodFill(image, x-1, y, value, minVal, maxVal);
	val += myFloodFill(image, x, y-1, value, minVal, maxVal);
	val += myFloodFill(image, x+1, y, value, minVal, maxVal);
	val += myFloodFill(image, x, y+1, value, minVal, maxVal);

	val += myFloodFill(image, x-1, y-1, value, minVal, maxVal);
	val += myFloodFill(image, x-1, y+1, value, minVal, maxVal);
	val += myFloodFill(image, x+1, y-1, value, minVal, maxVal);
	val += myFloodFill(image, x+1, y+1, value, minVal, maxVal);

	return val;
	}

////////////////////////////

#include <QVComponentTree>

void pruneLowComponentTreeAux(QVImage<uChar> &image, QVComponentTree &componentTree, uInt minArea, uInt node, uInt validThreshold)
	{
	Q_ASSERT(componentTree.area(node)[componentTree.firstThreshold(node)] != 0);
	Q_ASSERT(componentTree.area(node)[componentTree.lastThreshold(node)] != 0);
	Q_ASSERT(validThreshold >= componentTree.lastThreshold(node));

	bool prune = false;
	int lastValidThreshold = validThreshold;

	// Here we decide if this node should be directly pruned
	// or if there's any sub-node we should prune
	for (int threshold = componentTree.lastThreshold(node); threshold >= componentTree.firstThreshold(node) && !prune; threshold--)
		if (componentTree.area(node)[threshold] > 0)
			{
			if (componentTree.area(node)[threshold] < minArea)
				prune = true;
			else
				lastValidThreshold = threshold;
			}

	// We prune node, or get on with it's childrens
	if (prune)
		myFloodFill(image, componentTree.seedX(node), componentTree.seedY(node), lastValidThreshold, 0, lastValidThreshold-1);
	else
		for (uInt child = componentTree.firstChild(node); child != NULL_NODE; child = componentTree.nextSibling(child))
			pruneLowComponentTreeAux(image, componentTree, minArea, child, lastValidThreshold);
	}

void pruneHighComponentTreeAux(QVImage<uChar> &image, QVComponentTree &componentTree, uInt minArea, uInt node, uInt validThreshold)
	{
	Q_ASSERT(componentTree.area(node)[componentTree.firstThreshold(node)] != 0);
	Q_ASSERT(componentTree.area(node)[componentTree.lastThreshold(node)] != 0);
	Q_ASSERT(validThreshold >= componentTree.lastThreshold(node));

	bool prune = false;
	int lastValidThreshold = validThreshold;

	// Here we decide if this node should be directly pruned
	// or if there's any sub-node we should prune
	for (int threshold = componentTree.lastThreshold(node); threshold >= componentTree.firstThreshold(node) && !prune; threshold--)
		if (componentTree.area(node)[threshold] > 0)
			{
			if (componentTree.area(node)[threshold] < minArea)
				prune = true;
			else
				lastValidThreshold = threshold;
			}

	// We prune node, or get on with it's childrens
	if (prune)
		myFloodFill(image, componentTree.seedX(node), componentTree.seedY(node), 255-lastValidThreshold, 255-lastValidThreshold+1, 255-0);
	else
		for (uInt child = componentTree.firstChild(node); child != NULL_NODE; child = componentTree.nextSibling(child))
			pruneHighComponentTreeAux(image, componentTree, minArea, child, lastValidThreshold);
	}

void FilterPruneComponentTreeSmallRegions(QVImage<uChar> &image, QVComponentTree &componentTree, uInt minArea)
	{
	qDebug() << "pruneRegions()";
	if (componentTree.isInverseTree())
		{
		if(componentTree.area(componentTree.rootNode())[componentTree.lastThreshold(componentTree.rootNode())] > minArea)
			pruneHighComponentTreeAux(image, componentTree, minArea, componentTree.rootNode(), componentTree.lastThreshold(componentTree.rootNode()));
		}
	else	{
		if(componentTree.area(componentTree.rootNode())[componentTree.lastThreshold(componentTree.rootNode())] > minArea)
			pruneLowComponentTreeAux(image, componentTree, minArea, componentTree.rootNode(), componentTree.lastThreshold(componentTree.rootNode()));
		}

	qDebug() << "pruneRegions() <~ return";
	}

#include <qvmath/qvdisjointset.h>
//#include <qvmath/qvvector.h>

QMap<sFloat, QPointF>  maximalPoints(const QVImage<sFloat> &cornerResponseImage, const double threshold, const int windowRadius)
	{
	const QRect	ROI = cornerResponseImage.getROI();
	const int	step = cornerResponseImage.getStep() / sizeof(sFloat),
			windowSize = windowRadius * 2 +1;

	QVIMAGE_INIT_READ(sFloat,cornerResponseImage);

	QMap<sFloat, QPointF> sortedPoints;
	for(int row = ROI.y() + windowRadius; row < ROI.y() + ROI.height() - windowRadius; row++)
		for(int col = ROI.x() + windowRadius; col < ROI.x() + ROI.width() - windowRadius; col++)
			{
			const sFloat actual = QVIMAGE_PIXEL(cornerResponseImage, col, row, 0);
			if (actual >= threshold)
				{
				bool cond = true;

				sFloat const * pixel = & QVIMAGE_PIXEL(cornerResponseImage, col, row, 0) - windowRadius * (1 + step);
				for (int j = 0; j < windowSize && cond; j++, pixel += step - windowSize )
					for (int i = 0; i < windowSize && cond; i++, pixel++)
						if ( ( i != windowRadius || j != windowRadius ) && ( actual <= *pixel) )
							cond = false;

				if (cond)
					sortedPoints.insertMulti(-actual, QPointF(col+2, row+2));
				}
			}

	return sortedPoints;
	}

QList<QPointF> FASTFeatures(const QVImage<uChar, 1> & image, const int threshold, const FASTDetectionAlgorithm &fastAlgorithm)
	{
	// Convert QVImage to CVD Image
	const int	cols = image.getCols(),
				rows = image.getRows(),
				step = image.getStep();
	const byte *imgData = image.getReadData();

	int num_corners;
	xy *points;

	switch(fastAlgorithm)
		{
		case Fast9:
			points = fast9_detect_nonmax(imgData, cols, rows, step, threshold, &num_corners);
			break;
		case Fast10:
			points = fast10_detect_nonmax(imgData, cols, rows, step, threshold, &num_corners);
			break;
		case Fast11:
			points = fast11_detect_nonmax(imgData, cols, rows, step, threshold, &num_corners);
			break;
		case Fast12:
			points = fast12_detect_nonmax(imgData, cols, rows, step, threshold, &num_corners);
			break;
		}

	QList<QPointF> result;
	for (int i = 0; i < num_corners; i++)
		result << QPointF(points[i].x, points[i].y);

	free(points);

	return result;
	}


////////////////////////////////////
// Iterative point elimination
#ifndef DOXYGEN_IGNORE_THIS
class ClassAuxIPE
	{
	public:
		double cost;
		int index;
		ClassAuxIPE *prev,*next;
	};

class ClassAuxIPE_F
	{
	public:
		double cost;
		int index;
		ClassAuxIPE_F *prev,*next;
	};

bool costLessThan(ClassAuxIPE* &s1,ClassAuxIPE* &s2)
	{
	return s1->cost < s2->cost;
	}

bool costLessThanF(ClassAuxIPE_F* &s1,ClassAuxIPE_F* &s2)
	{
	return s1->cost < s2->cost;
	}

bool indexLessThan(ClassAuxIPE* &s1,ClassAuxIPE* &s2)
	{
	return s1->index < s2->index;
	}

bool indexLessThanF(ClassAuxIPE_F* &s1,ClassAuxIPE_F* &s2)
	{
	return s1->index < s2->index;
	}

inline double costElimination(const QVPolyline &polyline,int ia, int ib, int ic)
	{
	double   xA,yA,xB,yB,xC,yC;
	xA = polyline[ia].x(); yA=polyline[ia].y();
	xB = polyline[ib].x(); yB=polyline[ib].y();
	xC = polyline[ic].x(); yC=polyline[ic].y();
	if((xA != xC) or (yA != yC))
		return ABS(xA*(yC-yB) + xB*(yA-yC) + xC*(yB-yA)) / sqrt((xA-xC)*(xA-xC)+(yA-yC)*(yA-yC));
	else
		return sqrt((xB-xC)*(xB-xC)+(yB-yC)*(yB-yC));
	}

inline double costEliminationF(const QVPolylineF &polyline,int ia, int ib, int ic)
	{
	double   xA,yA,xB,yB,xC,yC;
	xA = polyline[ia].x(); yA=polyline[ia].y();
	xB = polyline[ib].x(); yB=polyline[ib].y();
	xC = polyline[ic].x(); yC=polyline[ic].y();
	if((xA != xC) or (yA != yC))
		return ABS(xA*(yC-yB) + xB*(yA-yC) + xC*(yB-yA)) / sqrt((xA-xC)*(xA-xC)+(yA-yC)*(yA-yC));
	else
		return sqrt((xB-xC)*(xB-xC)+(yB-yC)*(yB-yC));
	}

class auxLine {
	public:
	auxLine(double l1,double l2,double l3,bool ok) : l1(l1),l2(l2),l3(l3),ok(ok) {};
	double l1,l2,l3;
	bool ok;
};

class auxLine_F {
	public:
	auxLine_F(double l1,double l2,double l3,bool ok) : l1(l1),l2(l2),l3(l3),ok(ok) {};
	double l1,l2,l3;
	bool ok;
};
#endif // DOXYGEN_IGNORE_THIS

#ifdef QVMATRIXALGEBRA_AVAILABLE
double IterativePointElimination(const QVPolyline &polyline, QVPolyline &result,
	const double param, bool maxNumberOfPointsMethod,bool intersectLines,
	double *max_removed_cost)
	{
	const uInt tot_siz = polyline.size();
	QList<ClassAuxIPE*> list;

	// We start with an empty list:
	result.clear();

	// Maximum removed cost initialized to zero:
	if(max_removed_cost != NULL) *max_removed_cost = 0.0;

	// Only for polylines with 3 points or more; otherwise, the same
	// input polyline is returned:
	if(polyline.size()<3)
		{
		result = polyline;
		return FLT_MAX;
		}

	// Initialization of main data structure:
	for(uInt i=0;i<tot_siz;i++)
		list.push_back(new ClassAuxIPE);

	for(uInt i=0;i<tot_siz;i++)
		{
		int ia = (i==0)?tot_siz-1:i-1, ib = i, ic = (i==tot_siz-1)?0:i+1;
		list[i]->cost = costElimination(polyline,ia,ib,ic);
		list[i]->index = ib;
		list[i]->prev = list[ia];
		list[i]->next = list[ic];
		}
	if(not polyline.closed) // If not closed, never eliminate end points:
		{
		list[0]->cost = FLT_MAX;
		list[tot_siz-1]->cost = FLT_MAX;
		}
	qSort(list.begin(),list.end(), costLessThan);

	// Main loop:
	while(TRUE)
		{
		// Stop condition:
		if( (list.size() == 3) or // Minimal size of a polyline.
		    ((not maxNumberOfPointsMethod) and (list[0]->cost > param)) or
		    ((maxNumberOfPointsMethod) and
		     (list.size() <= static_cast<int>(param))) )
			break;

		// Removal of best point (first in the list): 
		ClassAuxIPE *elem = list.takeAt(0),
			    *elemPrev = list.takeAt(list.indexOf(elem->prev)),
			    *elemNext = list.takeAt(list.indexOf(elem->next));
		elemPrev->next = elem->next;
		elemNext->prev = elem->prev;
		if(elemPrev->cost != FLT_MAX)
			elemPrev->cost = costElimination(polyline,elemPrev->prev->index,
								elemPrev->index,
								elemPrev->next->index);
		if(elemNext->cost != FLT_MAX)
		elemNext->cost = costElimination(polyline,elemNext->prev->index,
							elemNext->index,
							elemNext->next->index);

		// Binary (fast) insertion of neighbours in data structure:
		int here;
		for(int i=0;i<2;i++)
			{
			ClassAuxIPE* newelem = ((i==0)?elemNext:elemPrev);
			int first=0,last=list.size()-1;
			while (first <= last) {
				int mid = (first + last) / 2;
				if (newelem->cost > list[mid]->cost)
					first = mid + 1;
				else if (newelem->cost < list[mid]->cost)
					last = mid - 1;
				else
					{
					here = mid;
					break;
					}
			}
			if(first>last)
				here=first;
			list.insert(here,newelem);

			}

		if(max_removed_cost != NULL)
			if(elem->cost > *max_removed_cost)
				*max_removed_cost = elem->cost;
		delete elem;
		}

	// We will return the cost of the first non deleted point:
	double return_value = list.first()->cost;

	// Once IPE finished, sort the list by position in original polyline:
	qSort(list.begin(),list.end(),indexLessThan);

	// Now, postprocess, fitting lines:
	QList<ClassAuxIPE*>::iterator it = list.begin();
	if(intersectLines)
		{
		// Line intersection computation (could be subpixel, in fact...):
		double ratio_eig=1.0;
		QList<auxLine> lines;
		for(int i=0;i<list.size();i++)
			{
 			// If not closed, do not need to compute last line:
			if((not polyline.closed) and (i==list.size()-1))
				break;
			int i1 = list[i]->index;
			int i2 = list[(i+1)%list.size()]->index;
			if(i2<i1) i2 += tot_siz;
			int dist = i2-i1+1;
			#define MIN_PIXELS_IPE_LINE 15
			if(dist >= MIN_PIXELS_IPE_LINE)
				{
				i1 = (i1+dist/5)%tot_siz;
				i2 = (i2-dist/5)%tot_siz;
				dist = dist-2*(dist/5);
				}
			else 
				{
				dist = i2-i1+1;
				i1 = i1%tot_siz;
				i2 = i2%tot_siz;
				}
	
			double x=0,y=0,xx=0,xy=0,yy=0;
			uInt j=i1;
			do
				{
				x += polyline[j].x();
				y += polyline[j].y();
				xx += polyline[j].x()*polyline[j].x();
				xy += polyline[j].x()*polyline[j].y();
				yy += polyline[j].y()*polyline[j].y();
				j = (j+1)%tot_siz;
				} while(j!=(i2+1)%tot_siz);
			double l1,l2,l3;
			x /= dist; y /= dist; xx /= dist; xy /= dist; yy /= dist;
			// If line does not fit well, just put old point instead of intersection:
                        //#ifdef GSL_AVAILABLE
                        ratio_eig = homogLineFromMoments(x,y,xx,xy,yy,l1,l2,l3);
                        //#else
                        //std::cerr << "[IterativePointElimination] ERROR: GSL is required to intersect lines"<< std::endl;
                        //exit(0);
                        //#endif

			lines.push_back(auxLine(l1,l2,l3,ratio_eig < 0.1));
			}

		for(int i=0;i<list.size();i++)
			{
			QPoint oldPoint = polyline[list[i]->index];
			if( (not polyline.closed) and ((i==0) or (i==list.size()-1)))
				{
				// If not closed, just include end points:
				result.append(oldPoint);
				continue;
				}
			int ant = (i-1+list.size())%list.size();
			int post = (i+1)%list.size();
			double 	newx = (lines[i].l2)*(lines[ant].l3) - (lines[i].l3)*(lines[ant].l2);
			double	newy = -(lines[i].l1)*(lines[ant].l3) + (lines[i].l3)*(lines[ant].l1);
			double	newz = (lines[i].l1)*(lines[ant].l2) - (lines[i].l2)*(lines[ant].l1);
			if ( (not lines[i].ok) or (not lines[ant].ok) or // Bad segment
				(fabs(newz) < EPSILON) ) // Lines too parallel
				result.append(oldPoint);
			else
				{
				int nx = qRound(newx/newz);
				int ny = qRound(newy/newz);
				// Only consider intersection if it is inside
				// a maximum radius circle around the old point
				// (relative to its nearer previous/next point
				// in polyline):
				double dist =
					sqrt((nx-oldPoint.x())*(nx-oldPoint.x()) +
					     (ny-oldPoint.y())*(ny-oldPoint.y()));
				QPoint prevPoint = polyline[list[ant]->index],
					nextPoint = polyline[list[post]->index];
				double minDist =
					qMin(
					sqrt((prevPoint.x()-oldPoint.x())*(prevPoint.x()-oldPoint.x()) +
					(prevPoint.y()-oldPoint.y())*(prevPoint.y()-oldPoint.y())),
					sqrt((nextPoint.x()-oldPoint.x())*(nextPoint.x()-oldPoint.x()) +
					(nextPoint.y()-oldPoint.y())*(nextPoint.y()-oldPoint.y()))
					);
				if(dist < 0.2*minDist)
					result.append(QPoint(nx,ny));
				else
					result.append(oldPoint);
				}
			}
		}
	else 
		{
		// No postprocess, simply store the resulting points in result polyline.
		it = list.begin();
		while(it != list.end())
			{
				result.append(polyline.at((*it)->index));
				it++;
			}
		}

	// Free memory of remaining structure:
	while (!list.isEmpty())
		delete list.takeFirst();

	// Polyline type and direction are the same of the original polyline:
	result.closed = polyline.closed;
	result.direction = polyline.direction;

	// We return the cost of the first non deleted point:
	return return_value;
	}

double IterativePointElimination(const QVPolylineF &polyline, QVPolylineF &result,
	const double param, bool maxNumberOfPointsMethod,bool intersectLines,
	double *max_removed_cost)
	{
	const uInt tot_siz = polyline.size();
	QList<ClassAuxIPE_F*> list;

	// We start with an empty list:
	result.clear();

	// Maximum removed cost initialized to zero:
	if(max_removed_cost != NULL) *max_removed_cost = 0.0;

	// Only for polylines with 3 points or more; otherwise, the same
	// input polyline is returned:
	if(polyline.size()<3)
		{
		result = polyline;
		return FLT_MAX;
		}

	// Initialization of main data structure:
	for(uInt i=0;i<tot_siz;i++)
		list.push_back(new ClassAuxIPE_F);

	for(uInt i=0;i<tot_siz;i++)
		{
		int ia = (i==0)?tot_siz-1:i-1, ib = i, ic = (i==tot_siz-1)?0:i+1;
		list[i]->cost = costEliminationF(polyline,ia,ib,ic);
		list[i]->index = ib;
		list[i]->prev = list[ia];
		list[i]->next = list[ic];
		}
	if(not polyline.closed) // If not closed, never eliminate end points:
		{
		list[0]->cost = FLT_MAX;
		list[tot_siz-1]->cost = FLT_MAX;
		}
	qSort(list.begin(),list.end(),costLessThanF);

	// Main loop:
	while(TRUE)
		{
		// Stop condition:
		if( (list.size() == 3) or // Minimal size of a polyline.
		    ((not maxNumberOfPointsMethod) and (list[0]->cost > param)) or
		    ((maxNumberOfPointsMethod) and
		     (list.size() <= static_cast<int>(param))) )
			break;

		// Removal of best point (first in the list): 
		ClassAuxIPE_F *elem = list.takeAt(0),
			    *elemPrev = list.takeAt(list.indexOf(elem->prev)),
			    *elemNext = list.takeAt(list.indexOf(elem->next));
		elemPrev->next = elem->next;
		elemNext->prev = elem->prev;
		if(elemPrev->cost != FLT_MAX)
			elemPrev->cost = costEliminationF(polyline,elemPrev->prev->index,
								elemPrev->index,
								elemPrev->next->index);
		if(elemNext->cost != FLT_MAX)
		elemNext->cost = costEliminationF(polyline,elemNext->prev->index,
							elemNext->index,
							elemNext->next->index);

		// Binary (fast) insertion of neighbours in data structure:
		int here;
		for(int i=0;i<2;i++)
			{
			ClassAuxIPE_F* newelem = ((i==0)?elemNext:elemPrev);
			int first=0,last=list.size()-1;
			while (first <= last) {
				int mid = (first + last) / 2;
				if (newelem->cost > list[mid]->cost)
					first = mid + 1;
				else if (newelem->cost < list[mid]->cost)
					last = mid - 1;
				else
					{
					here = mid;
					break;
					}
			}
			if(first>last)
				here=first;
			list.insert(here,newelem);

			}

		if(max_removed_cost != NULL)
			if(elem->cost > *max_removed_cost)
				*max_removed_cost = elem->cost;
		delete elem;
		}

	// We will return the cost of the first non deleted point:
	double return_value = list.first()->cost;

	// Once IPE finished, sort the list by position in original polyline:
	qSort(list.begin(),list.end(),indexLessThanF);

	// Now, postprocess, fitting lines:
	QList<ClassAuxIPE_F*>::iterator it = list.begin();
	if(intersectLines)
		{
		// Line intersection computation (could be subpixel, in fact...):
		double ratio_eig=1.0;
		QList<auxLine_F> lines;
		for(int i=0;i<list.size();i++)
			{
 			// If not closed, do not need to compute last line:
			if((not polyline.closed) and (i==list.size()-1))
				break;
			int i1 = list[i]->index;
			int i2 = list[(i+1)%list.size()]->index;
			if(i2<i1) i2 += tot_siz;
			int dist = i2-i1+1;
			#define MIN_PIXELS_IPE_LINE 15
			if(dist >= MIN_PIXELS_IPE_LINE)
				{
				i1 = (i1+dist/5)%tot_siz;
				i2 = (i2-dist/5)%tot_siz;
				dist = dist-2*(dist/5);
				}
			else 
				{
				dist = i2-i1+1;
				i1 = i1%tot_siz;
				i2 = i2%tot_siz;
				}
	
			double x=0,y=0,xx=0,xy=0,yy=0;
			uInt j=i1;
			do
				{
				x += polyline[j].x();
				y += polyline[j].y();
				xx += polyline[j].x()*polyline[j].x();
				xy += polyline[j].x()*polyline[j].y();
				yy += polyline[j].y()*polyline[j].y();
				j = (j+1)%tot_siz;
				} while(j!=(i2+1)%tot_siz);
			double l1,l2,l3;
			x /= dist; y /= dist; xx /= dist; xy /= dist; yy /= dist;

                        // If line does not fit well, just put old point instead of intersection:
                        //#ifdef GSL_AVAILABLE
			ratio_eig = homogLineFromMoments(x,y,xx,xy,yy,l1,l2,l3);
                        //#else
                        //std::cerr << "[IterativePointElimination] ERROR: GSL is required to intersect lines"<< std::endl;
                        //exit(0);
                        //#endif

			lines.push_back(auxLine_F(l1,l2,l3,ratio_eig < 0.1));
			}

		for(int i=0;i<list.size();i++)
			{
			QPointF oldPoint = polyline[list[i]->index];
			if( (not polyline.closed) and ((i==0) or (i==list.size()-1)))
				{
				// If not closed, just include end points:
				result.append(oldPoint);
				continue;
				}
			int ant = (i-1+list.size())%list.size();
			int post = (i+1)%list.size();
			double 	newx = (lines[i].l2)*(lines[ant].l3) - (lines[i].l3)*(lines[ant].l2);
			double	newy = -(lines[i].l1)*(lines[ant].l3) + (lines[i].l3)*(lines[ant].l1);
			double	newz = (lines[i].l1)*(lines[ant].l2) - (lines[i].l2)*(lines[ant].l1);
			if ( (not lines[i].ok) or (not lines[ant].ok) or // Bad segment
				(fabs(newz) < EPSILON) ) // Lines too parallel
				result.append(oldPoint);
			else
				{
				double nx = newx/newz;
				double ny = newy/newz;
				// Only consider intersection if it is inside
				// a maximum radius circle around the old point
				// (relative to its nearer previous/next point
				// in polyline):
				double dist =
					sqrt((nx-oldPoint.x())*(nx-oldPoint.x()) +
					     (ny-oldPoint.y())*(ny-oldPoint.y()));
				QPointF prevPoint = polyline[list[ant]->index],
					nextPoint = polyline[list[post]->index];
				double minDist =
					qMin(
					sqrt((prevPoint.x()-oldPoint.x())*(prevPoint.x()-oldPoint.x()) +
					(prevPoint.y()-oldPoint.y())*(prevPoint.y()-oldPoint.y())),
					sqrt((nextPoint.x()-oldPoint.x())*(nextPoint.x()-oldPoint.x()) +
					(nextPoint.y()-oldPoint.y())*(nextPoint.y()-oldPoint.y()))
					);
				if(dist < 0.2*minDist)
					result.append(QPointF(nx,ny));
				else
					result.append(oldPoint);
				}
			}
		}
        else // LAPACK_AVAILABLE
		{
		// No postprocess, simply store the resulting points in result polyline.
		it = list.begin();
		while(it != list.end())
			{
				result.append(polyline.at((*it)->index));
				it++;
			}
		}

	// Free memory of remaining structure:
	while (!list.isEmpty())
		delete list.takeFirst();

	// Polyline type and direction are the same of the original polyline:
	result.closed = polyline.closed;
	result.direction = polyline.direction;

	// We return the cost of the first non deleted point:
	return return_value;
	}
#else
double IterativePointElimination(const QVPolyline &polyline, QVPolyline &result,
	const double param, bool maxNumberOfPointsMethod,bool intersectLines,
	double *max_removed_cost)
	{
	result = polyline;
	std::cout << "Warning: IterativePointElimination requires GSL, MKL or LAPACK functionality enabled to work properly." << std::endl;
	return 0.0;
	}


double IterativePointElimination(const QVPolylineF &polyline, QVPolylineF &result,
	const double param, bool maxNumberOfPointsMethod,bool intersectLines,
	double *max_removed_cost)
	{
	result = polyline;
	std::cout << "Warning: IterativePointElimination requires GSL, MKL or LAPACK functionality enabled to work properly." << std::endl;
	return 0.0;
	}

#endif // QVMATRIXALGEBRA_AVAILABLE

///////////////////////////////////////////////////////////////////////////
// Get borders and contours
// Direction-number		Y
//	NE-7	N-0	NW-1	|
//	E-6	*	W-2	v
//	SE-5	S-4	SW-3
// X -->
//						N	NO	O	SO	S	SE	E	NE
#ifndef DOXYGEN_IGNORE_THIS
const char	coorX8Connect[8] =	{	0,	1,	1,	1,	0,	-1,	-1,	-1	};
const char	coorY8Connect[8] =	{	-1,	-1,	0,	1,	1,	1,	0,	-1	};
const char	coorX4Connect[4] =	{	0,		1,		0,		-1,		};
const char	coorY4Connect[4] =	{	-1,		0,		1,		0,		};
const char	coorX4Diag[8] =		{		1,		1,		-1,		-1	};
const char	coorY4Diag[8] =		{		-1,		1,		1,		-1	};
#endif

// Auxiliar function for border extraction. It gets a border point, and the direction where there is one of the outside of the connected-set pixels.
#ifndef DOXYGEN_IGNORE_THIS
QVPolyline getConnectedSetBorderContourThresholdFromBorderPoint(const QVImage<uChar> &image, const int startPointX, const int startPointY, const uChar threshold)
	{
	QVPolyline lista;

	lista.closed = true;
	lista.append(QPoint(startPointX, startPointY));

	QVIMAGE_INIT_READ(uChar,image);
	QRect roi = image.getROI();

	Q_ASSERT_X(roi.contains(startPointX, startPointY), "getContourThresholdFromBorderPoint", "start point out of image ROI");
	Q_ASSERT_X(QVIMAGE_PIXEL(image, startPointX, startPointY, 0) >= threshold, "getContourThresholdFromBorderPoint", "start point is not contained in a connected set");

	// We check this is not an interior pixel, neither a solitary one.
	// Also we look for a neighbour pixel not belonging to any connected set.
	uChar searchDir = 128, numOuterPixels = 0;
	for (int i = 0; i<8; i++)
		{
		int x =  startPointX +coorX8Connect[i], y =  startPointY +coorY8Connect[i];
		if (!roi.contains(x, y))
			{
			numOuterPixels++;
			searchDir = i;
			}
		else if (QVIMAGE_PIXEL(image, x, y,0) < threshold)
			{
			numOuterPixels++;
			searchDir = i;
			}
		}

	// Case we receive an interior pixel, raise assert.
	Q_ASSERT_X(searchDir < 8, "getContourThresholdFromBorderPoint", "start point is inside the set, not in the border");

	// Case we have a solitary pixel, we return that pixel.
	if (numOuterPixels == 8)
		return lista;

	// We insert each point of the border contour, inserting it to the point list.
	int sumSearchDir = 0, actualPointX = startPointX, actualPointY = startPointY;
	while (true)
		{
		// We search for the next point belonging to the contour.
		uChar d;
		int	nextPointX, nextPointY;
		for (d = 0; d < 8; d++)
			{
			searchDir = (searchDir+1)%8;
			nextPointX = actualPointX + coorX8Connect[searchDir];
			nextPointY = actualPointY + coorY8Connect[searchDir];
			if (roi.contains(nextPointX, nextPointY))
				if ( (QVIMAGE_PIXEL(image, nextPointX, nextPointY,0) >= threshold) )
					break;
			}

		sumSearchDir += d - 3;

		actualPointX = nextPointX;
		actualPointY = nextPointY;

		if ( QVIMAGE_PIXEL(image, actualPointX, actualPointY,0) < threshold )
			break;

		if ( startPointX == actualPointX && startPointY == actualPointY)
			break;

		lista.append(QPoint(actualPointX, actualPointY));
		searchDir = searchDir + 4;
		}

	lista.direction = (sumSearchDir >= 0);
	return lista;
	}

QVPolyline getConnectedSetBorderContourThresholdFromBorderPoint(const QVImage<uShort> &image, const int startPointX, const int startPointY, const uShort threshold)
        {
        QVPolyline lista;

        lista.closed = true;
        lista.append(QPoint(startPointX, startPointY));

        QVIMAGE_INIT_READ(uShort,image);
        QRect roi = image.getROI();

        Q_ASSERT_X(roi.contains(startPointX, startPointY), "getContourThresholdFromBorderPoint", "start point out of image ROI");
        Q_ASSERT_X(QVIMAGE_PIXEL(image, startPointX, startPointY, 0) >= threshold, "getContourThresholdFromBorderPoint", "start point is not contained in a connected set");

        // We check this is not an interior pixel, neither a solitary one.
        // Also we look for a neighbour pixel not belonging to any connected set.
        uShort searchDir = 128, numOuterPixels = 0;
        for (int i = 0; i<8; i++)
                {
                int x =  startPointX +coorX8Connect[i], y =  startPointY +coorY8Connect[i];
                if (!roi.contains(x, y))
                        {
                        numOuterPixels++;
                        searchDir = i;
                        }
                else if (QVIMAGE_PIXEL(image, x, y,0) < threshold)
                        {
                        numOuterPixels++;
                        searchDir = i;
                        }
                }

        // Case we receive an interior pixel, raise assert.
        Q_ASSERT_X(searchDir < 8, "getContourThresholdFromBorderPoint", "start point is inside the set, not in the border");

        // Case we have a solitary pixel, we return that pixel.
        if (numOuterPixels == 8)
                return lista;

        // We insert each point of the border contour, inserting it to the point list.
        int sumSearchDir = 0, actualPointX = startPointX, actualPointY = startPointY;
        while (true)
                {
                // We search for the next point belonging to the contour.
                uShort d;
                int	nextPointX, nextPointY;
                for (d = 0; d < 8; d++)
                        {
                        searchDir = (searchDir+1)%8;
                        nextPointX = actualPointX + coorX8Connect[searchDir];
                        nextPointY = actualPointY + coorY8Connect[searchDir];
                        if (roi.contains(nextPointX, nextPointY))
                                if ( (QVIMAGE_PIXEL(image, nextPointX, nextPointY,0) >= threshold) )
                                        break;
                        }

                sumSearchDir += d - 3;

                actualPointX = nextPointX;
                actualPointY = nextPointY;

                if ( QVIMAGE_PIXEL(image, actualPointX, actualPointY,0) < threshold )
                        break;

                if ( startPointX == actualPointX && startPointY == actualPointY)
                        break;

                lista.append(QPoint(actualPointX, actualPointY));
                searchDir = searchDir + 4;
                }

        lista.direction = (sumSearchDir >= 0);
        return lista;
        }




#endif

QVPolyline getConnectedSetBorderContourThreshold(const QVImage<uChar> &image, const QPoint startPoint, const uChar threshold)
	{
	QVIMAGE_INIT_READ(uChar,image);
	const QRect roi = image.getROI();

	int col = startPoint.x(), row = startPoint.y();

	if (QVIMAGE_PIXEL(image, col, row,0) < threshold)
		return QVPolyline();

	while (roi.contains(col+1, row))
		{
		if ( QVIMAGE_PIXEL(image, col+1, row,0) < threshold )
			break;
		col++;
		}

	return getConnectedSetBorderContourThresholdFromBorderPoint(image, col, row, threshold);
	}

QVPolyline getConnectedSetBorderContourThreshold(const QVImage<uShort> &image, const QPoint startPoint, const uShort threshold)
        {
        QVIMAGE_INIT_READ(uShort,image);
        const QRect roi = image.getROI();

        int col = startPoint.x(), row = startPoint.y();

        if (QVIMAGE_PIXEL(image, col, row,0) < threshold)
                return QVPolyline();

        while (roi.contains(col+1, row))
                {
                if ( QVIMAGE_PIXEL(image, col+1, row,0) < threshold )
                        break;
                col++;
                }

        return getConnectedSetBorderContourThresholdFromBorderPoint(image, col, row, threshold);
        }

QList<QVPolyline> getConnectedSetBorderContoursThreshold(const QVImage <uChar> &image, const uChar threshold)
	{
	qDebug() << "getPolylinesThreshold()";
	QVImage<uChar> mask(image.getCols()+1, image.getRows()+1);
	Set(0, mask);

	QVIMAGE_INIT_READ(uChar,image);
	QVIMAGE_INIT_WRITE(uChar,mask);

	const QRect roi = image.getROI();

	QList<QVPolyline> polylineList;

	// We look for pixels contained in a connected set (gray-level value >= threshold) in the image
	for (int row = roi.y(); row < roi.y() + roi.height(); row++)
		for (int col = roi.x(); col < roi.y() + roi.width(); col++)
			{
			// If we find any pixel like that, we can be sure (because the search we did) it belongs to it's border.
			if (QVIMAGE_PIXEL(image, col, row,0) >= threshold)
				{
				// if pixel is not marked, we get it's contour
				if ( !QVIMAGE_PIXEL(mask, col, row,0) )
					{
					QVPolyline lista = getConnectedSetBorderContourThresholdFromBorderPoint(image, col, row, threshold);
					polylineList.append(lista);

					QListIterator<QPoint> iterator(lista);
					for (QPoint previous = iterator.next(), actual; iterator.hasNext(); previous = actual)
						{
						actual = iterator.next();
						foreach (QPoint point, QVPolyline::line(actual.x(), actual.y(), previous.x(), previous.y()))
							QVIMAGE_PIXEL(mask, point.x(), point.y(),0) = true;
						}
					}

				// We ensure next pixel we process will not belong to a connected set.
				while (roi.contains(col+1, row))
					{
					if ( QVIMAGE_PIXEL(image, col+1, row,0) < threshold )
						break;
					col++;
					}

				// This is for the case in which we find an internal contour, that has not been processed and marked.
				if ( !QVIMAGE_PIXEL(mask, col, row,0) )
					{
					QVPolyline lista = getConnectedSetBorderContourThresholdFromBorderPoint(image, col, row, threshold);
					polylineList.append(lista);

					QListIterator<QPoint> iterator(lista);
					for (QPoint previous = iterator.next(), actual; iterator.hasNext(); previous = actual)
						{
						actual = iterator.next();
						foreach (QPoint point, QVPolyline::line(actual.x(), actual.y(), previous.x(), previous.y()))
							QVIMAGE_PIXEL(mask, point.x(), point.y(),0) = true;
						}
					}
				}

			}
	qDebug() << "getPolylinesThreshold():"<< polylineList.size() << "contours obtained";
	qDebug() << "getPolylinesThreshold() <~ return";
	return polylineList;
	}


QList<QVPolyline> getConnectedSetBorderContoursThreshold(const QVImage <uShort> &image, const uShort threshold)
        {
        qDebug() << "getPolylinesThreshold()";
        QVImage<uShort> mask(image.getCols()+1, image.getRows()+1);
        Set(0, mask);

        QVIMAGE_INIT_READ(uShort,image);
        QVIMAGE_INIT_WRITE(uShort,mask);

        const QRect roi = image.getROI();

        QList<QVPolyline> polylineList;

        // We look for pixels contained in a connected set (gray-level value >= threshold) in the image
        for (int row = roi.y(); row < roi.y() + roi.height(); row++)
                for (int col = roi.x(); col < roi.y() + roi.width(); col++)
                        {
                        // If we find any pixel like that, we can be sure (because the search we did) it belongs to it's border.
                        if (QVIMAGE_PIXEL(image, col, row,0) >= threshold)
                                {
                                // if pixel is not marked, we get it's contour
                                if ( !QVIMAGE_PIXEL(mask, col, row,0) )
                                        {
                                        QVPolyline lista = getConnectedSetBorderContourThresholdFromBorderPoint(image, col, row, threshold);
                                        polylineList.append(lista);

                                        QListIterator<QPoint> iterator(lista);
                                        for (QPoint previous = iterator.next(), actual; iterator.hasNext(); previous = actual)
                                                {
                                                actual = iterator.next();
                                                foreach (QPoint point, QVPolyline::line(actual.x(), actual.y(), previous.x(), previous.y()))
                                                        QVIMAGE_PIXEL(mask, point.x(), point.y(),0) = true;
                                                }
                                        }

                                // We ensure next pixel we process will not belong to a connected set.
                                while (roi.contains(col+1, row))
                                        {
                                        if ( QVIMAGE_PIXEL(image, col+1, row,0) < threshold )
                                                break;
                                        col++;
                                        }

                                // This is for the case in which we find an internal contour, that has not been processed and marked.
                                if ( !QVIMAGE_PIXEL(mask, col, row,0) )
                                        {
                                        QVPolyline lista = getConnectedSetBorderContourThresholdFromBorderPoint(image, col, row, threshold);
                                        polylineList.append(lista);

                                        QListIterator<QPoint> iterator(lista);
                                        for (QPoint previous = iterator.next(), actual; iterator.hasNext(); previous = actual)
                                                {
                                                actual = iterator.next();
                                                foreach (QPoint point, QVPolyline::line(actual.x(), actual.y(), previous.x(), previous.y()))
                                                        QVIMAGE_PIXEL(mask, point.x(), point.y(),0) = true;
                                                }
                                        }
                                }

                        }
        qDebug() << "getPolylinesThreshold():"<< polylineList.size() << "contours obtained";
        qDebug() << "getPolylinesThreshold() <~ return";
        return polylineList;
        }



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QVPolyline getLineContourThreshold4Connectivity(QVImage<uChar> &image, const QPoint point, QVPolyline &polyline, const uChar threshold, bool reverse)
	{
	const uInt cols = image.getCols(), rows = image.getRows();
	QVIMAGE_INIT_WRITE(uChar, image);

	uInt lastDir = 666, coorX = point.x(), coorY = point.y();

	qDebug() << "\tContour: new contour";

	forever	{
		qDebug() << "\tContour:\tAppending point (" << coorX << ", " << coorY << ")";
		if (reverse)
			polyline.prepend(QPoint(coorX, coorY));
		else
			polyline.append(QPoint(coorX, coorY));

		QVIMAGE_PIXEL(image, coorX, coorY, 0) = 0;

		uInt dir;
		int newCoorX, newCoorY;
		for (dir = 0; dir < 4; dir++)
			{
			newCoorX = coorX + coorX4Connect[dir];
			newCoorY = coorY + coorY4Connect[dir];

			// Check if we are inside the limits in that direction
			if ( (newCoorX < 0) || (newCoorY < 0) || (newCoorX >= ((int)cols)) || (newCoorY >= ((int)rows)) )
				continue;

			// Check if it is a valid direction and if the pixel in that direction is part of a contour
			if ( (QVIMAGE_PIXEL(image, newCoorX, newCoorY, 0) >= threshold)  && (lastDir != dir) )
				break;
			}

		if (dir == 4) break;

		coorX = newCoorX;
		coorY = newCoorY;
		lastDir = (dir+2)%4;
		}

	return polyline;
	}

QList<QVPolyline> getLineContoursThreshold4Connectivity(const QVImage<uChar> &image, const uChar threshold)
	{
	const uInt cols = image.getCols(), rows = image.getRows();
	QVImage<uChar> clone = image;

	QList<QVPolyline> polylineList;

	// Transverse the image
	for(uInt col = 0; col < cols; col++)
		for(uInt row = 0; row < rows; row++)
			{
			QVIMAGE_INIT_READ(uChar, clone);
			// If we don't have an active pixel, continue
			if ( (QVIMAGE_PIXEL(clone, col, row, 0) < threshold) )
				continue;

			// Else, we compose the contour following two active neighbour pixels:
			QVPolyline polyline;

			// We follow first active neighbour pixel, composing the list of pixels in direct order
			getLineContourThreshold4Connectivity(clone, QPoint(col, row), polyline, threshold, false);

			// Find another neighbour close to the pixel.
			uInt dir;			
			int	newCoorX, newCoorY;
			for (dir = 0; dir < 4; dir++)
				{
				newCoorX = col + coorX4Connect[dir];
				newCoorY = row + coorY4Connect[dir];
	
				// Check if we are inside the limits in that direction
				if ( (newCoorX < 0) || (newCoorY < 0) || (newCoorX >= ((int)cols)) || (newCoorY >= ((int)rows)) )
					continue;
	
				// Check if it is a valid direction and if the pixel in that direction is part of a contour
				if ( (clone(newCoorX, newCoorY) >= threshold) )
					break;
				}

			// If we found it, add the contour in reverse order.
			if (dir != 4)
				getLineContourThreshold4Connectivity(clone, QPoint(newCoorX, newCoorY), polyline, threshold, true);

			// Finally add the polyline to the list.
			polylineList.append(polyline);
			}

	return polylineList;
	}

////////////////////////////////////////////////////////////////////////////////////
// Replicated functions from 4-connected version.
QVPolyline getLineContourThreshold8Connectivity(QVImage<uChar> &image, const QPoint point, QVPolyline &polyline, const uChar threshold, bool reverse)
	{
	const uInt cols = image.getCols(), rows = image.getRows();
	QVIMAGE_INIT_WRITE(uChar, image);

	uInt lastDir = 666, coorX = point.x(), coorY = point.y();

	qDebug() << "\tContour: new contour";

	bool continueCond = true;
	while(continueCond)
		{
		qDebug() << "\tContour:\tAppending point (" << coorX << ", " << coorY << ")";
		if (reverse)
			polyline.prepend(QPoint(coorX, coorY));
		else
			polyline.append(QPoint(coorX, coorY));

		QVIMAGE_PIXEL(image, coorX, coorY, 0) = 0;

		// Buscamos un píxel en los vecinos 4 conectados.
		uInt dir;
		int newCoorX, newCoorY;
		for (dir = 0; dir < 4; dir++)
			{
			newCoorX = coorX + coorX4Connect[dir];
			newCoorY = coorY + coorY4Connect[dir];

			// Check if we are inside the limits in that direction
			if ( (newCoorX < 0) || (newCoorY < 0) || (newCoorX >= ((int)cols)) || (newCoorY >= ((int)rows)) )
				continue;

			// Check if it is a valid direction and if the pixel in that direction is part of a contour
			if ( (QVIMAGE_PIXEL(image, newCoorX, newCoorY, 0) >= threshold)  && (lastDir != dir) )
				break;
			}

		if (dir == 4) 
			{
			// Buscamos un píxel en los vecinos 4 conectados diagonalmente.
			uInt dir;
			int newCoorX, newCoorY;
			for (dir = 0; dir < 4; dir++)
				{
				newCoorX = coorX + coorX4Diag[dir];
				newCoorY = coorY + coorY4Diag[dir];
	
				// Check if we are inside the limits in that direction
				if ( (newCoorX < 0) || (newCoorY < 0) || (newCoorX >= ((int)cols)) || (newCoorY >= ((int)rows)) )
					continue;
	
				// Check if it is a valid direction and if the pixel in that direction is part of a contour
				if ( (QVIMAGE_PIXEL(image, newCoorX, newCoorY, 0) >= threshold)  && (lastDir != dir) )
					break;
				}
			if (dir == 4) break;

			coorX = newCoorX;
			coorY = newCoorY;
			lastDir = (dir+2)%4;
			}
		else	{
			coorX = newCoorX;
			coorY = newCoorY;
			lastDir = (dir+2)%4;
			}
		}

	return polyline;
	}

QList<QVPolyline> getLineContoursThreshold8Connectivity(const QVImage<uChar> &image, const uChar threshold)
	{
	const uInt cols = image.getCols(), rows = image.getRows();
	QVImage<uChar> clone = image;

	QList<QVPolyline> polylineList;

	// Transverse the image
	for(uInt col = 0; col < cols; col++)
		for(uInt row = 0; row < rows; row++)
			{
			QVIMAGE_INIT_READ(uChar, clone);
			// If we don't have an active pixel, continue
			if ( (QVIMAGE_PIXEL(clone, col, row, 0) < threshold) )
				continue;

			// Else, we compose the contour following two active neighbour pixels:
			QVPolyline polyline;

			// We follow first active neighbour pixel, composing the list of pixels in direct order
			getLineContourThreshold8Connectivity(clone, QPoint(col, row), polyline, threshold, false);

			// Find another neighbour close to the pixel, in 4 connected neighbours
			uInt dir;			
			int	newCoorX, newCoorY;
			for (dir = 0; dir < 4; dir++)
				{
				newCoorX = col + coorX4Connect[dir];
				newCoorY = row + coorY4Connect[dir];
	
				// Check if we are inside the limits in that direction
				if ( (newCoorX < 0) || (newCoorY < 0) || (newCoorX >= ((int)cols)) || (newCoorY >= ((int)rows)) )
					continue;
	
				// Check if it is a valid direction and if the pixel in that direction is part of a contour
				if ( (clone(newCoorX, newCoorY) >= threshold) )
					break;
				}

			// If we found it, add the contour in reverse order.
			if (dir != 4)
				getLineContourThreshold8Connectivity(clone, QPoint(newCoorX, newCoorY), polyline, threshold, true);
			else	{
				// Find another neighbour close to the pixel, in diagonal connected neighbours
				uInt dir;			
				int	newCoorX, newCoorY;
				for (dir = 0; dir < 4; dir++)
					{
					newCoorX = col + coorX4Diag[dir];
					newCoorY = row + coorY4Diag[dir];
		
					// Check if we are inside the limits in that direction
					if ( (newCoorX < 0) || (newCoorY < 0) || (newCoorX >= ((int)cols)) || (newCoorY >= ((int)rows)) )
						continue;
		
					// Check if it is a valid direction and if the pixel in that direction is part of a contour
					if ( (clone(newCoorX, newCoorY) >= threshold) )
						break;
					}
	
				// If we found it, add the contour in reverse order.
				if (dir != 4)
					getLineContourThreshold8Connectivity(clone, QPoint(newCoorX, newCoorY), polyline, threshold, true);
				}

			// Finally add the polyline to the list.
			polylineList.append(polyline);
			}

	return polylineList;
	}

QVImage<uChar, 1> FastLaplaceFilter(const QVImage<uChar, 1> image)
	{
	const int	cols = image.getCols(),
				rows = image.getRows();

	if ( (cols == 0) or (rows == 0) )
		return image;

	QVImage<uChar, 1> result(cols, rows);

	// Result image and intermediate pointers.
	const int	srcStep = image.getStep(),
				dstStep = result.getStep();
	const uChar	*srcData = image.getReadData();
	uChar		*dstData = result.getWriteData(),
				*bottomDstRowData = dstData + (rows-1) * dstStep;

	// Set top and bottom marging to zero.
	for(int j = 0; j < cols; j++)
		dstData[j] = bottomDstRowData[j] = 0;

	// Evaluate smooth pixels inside the margings.
	for(int i = 1; i < rows-1; i++)
		{
		const uChar	*srcRowData = srcData + i * srcStep;
		uChar		*dstRowData = dstData + i * dstStep;

		// Set zero left and right margin.
		dstRowData[0] = dstRowData[cols-1] = 0;

		for(int j = 1; j < cols-1; j++)
			{
			const int value = int(srcRowData[j]);
			const int neighbour1 = int(srcRowData[j - 1]);
			const int neighbour2 = int(srcRowData[j + 1]);
			const int neighbour3 = int(srcRowData[j - srcStep]);
			const int neighbour4 = int(srcRowData[j + srcStep]);
			const int minus = neighbour1 + neighbour2 + neighbour3 + neighbour4;

			dstRowData[j] = ABS( (value << 2) - minus);
			}
		}

	return result;
	}

QVImage<uChar, 1> FastSmoothFilter(const QVImage<uChar, 1> image, const uChar threshold)
	{
	const int	cols = image.getCols(),
				rows = image.getRows();

	if ( (cols == 0) or (rows == 0) )
		return image;

	QVImage<uChar, 1> result(cols, rows);

	// Result image and intermediate pointers.
	const int	srcStep = image.getStep(),
				dstStep = result.getStep();
	const uChar	*srcData = image.getReadData();
	uChar		*dstData = result.getWriteData(),
				*bottomDstRowData = dstData + (rows-1) * dstStep;

	// Set top and bottom marging to zero.
	for(int j = 0; j < cols; j++)
		dstData[j] = bottomDstRowData[j] = 0;

	// Evaluate smooth pixels inside the margings.
	for(int i = 1; i < rows-1; i++)
		{
		const uChar	*srcRowData = srcData + i * srcStep;
		uChar		*dstRowData = dstData + i * dstStep;

		// Set zero left and right margin.
		dstRowData[0] = dstRowData[cols-1] = 0;

		for(int j = 1; j < cols-1; j++)
			{
			const int value = int(srcRowData[j]);

			if (value < threshold)
				{
				dstRowData[j] = 0;
				continue;
				}

			dstRowData[j] = ( (value << 1)
											+ int(srcRowData[j - 1])
											+ int(srcRowData[j + 1])
											+ int(srcRowData[j - srcStep])
											+ int(srcRowData[j + srcStep]) ) / 6;
			}
		}

	return result;
	}

QVImage<uChar, 1> SmoothFilter(const QVImage<uChar, 1> image, const uChar threshold)
	{
	const int	cols = image.getCols(),
				rows = image.getRows();

	if ( (cols == 0) or (rows == 0) )
		return image;

	// Result image and intermediate pointers.
	QVImage<uChar, 1> result(cols, rows);
	const int	srcStep = image.getStep(),
				dstStep = result.getStep();
	const uChar	*srcData = image.getReadData();
	uChar		*dstData = result.getWriteData(),
				*bottomDstRowData = dstData + (rows-1) * dstStep;

	// Set top and bottom marging to zero.
	for(int j = 0; j < cols; j++)
		dstData[j] = bottomDstRowData[j] = 0;

	// Evaluate smooth pixels inside the margings.
	for(int i = 1; i < rows-1; i++)
		{
		const uChar	*srcRowData = srcData + i * srcStep;
		uChar		*dstRowData = dstData + i * dstStep;

		// Set zero left and right margin.
		dstRowData[0] = dstRowData[cols-1] = 0;

		for(int j = 1; j < cols-1; j++)
			{
			const int value = int(srcRowData[j]);

			if (value < threshold)
				{
				dstRowData[j] = 0;
				continue;
				}

			dstRowData[j] = ( (value << 2)
								+ (int(srcRowData[j - 1]) << 1)
								+ (int(srcRowData[j + 1]) << 1)
								+ (int(srcRowData[j - srcStep]) << 1)
								+ (int(srcRowData[j + srcStep]) << 1)

								+ int(srcRowData[j - 1 - srcStep])
								+ int(srcRowData[j + 1 - srcStep])
								+ int(srcRowData[j - 1 + srcStep])
								+ int(srcRowData[j + 1 + srcStep])
								) >> 4;
			}
		}

	return result;
	}

QList<QPointF> FastLaplacePoints(const QVImage<uChar, 1> &image, const int threshold, const bool applyPreviousSmooth, const bool smoothResponseImage)
	{
	const QVImage<uChar, 1> laplaceImage = FastLaplaceFilter(applyPreviousSmooth?FastSmoothFilter(image):image);

	return getLocalExtremaPixels(smoothResponseImage?FastSmoothFilter(laplaceImage, threshold):laplaceImage, threshold);
	}



