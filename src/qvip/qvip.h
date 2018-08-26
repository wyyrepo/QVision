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

#ifndef QVIP_H
#define QVIP_H

#include <iostream>

#include <qvdefines.h>
#include <qvimageio.h>
#include <QVImage>
#include <QVPolyline>

#include <QVImage>
#include <QFile>


#ifndef DOXYGEN_IGNORE_THIS
double ShiTomasiScore(const uChar *imagePtr, const int imageStep, const int x, const int y, const int nHalfBoxSize);
#endif // DOXYGEN_IGNORE_THIS

/*! @brief Obtains the Harris corner response image
@note This function is based on the IPP library functionality. Thus it requires that library, to be available.
@todo document this
@ingroup qvipp
*/
void FilterHarrisCornerResponseImage(const QVImage<uChar> &image, QVImage<sFloat> &result, int aperture=3, int avgwindow=5, const QPoint &destROIOffset = QPoint(0,0));

/*! @brief Obtains the DoG corner response image
@note This function is based on the IPP library functionality. Thus it requires that library, to be available.
@todo document this
@ingroup qvipp
*/
void FilterDoG(const QVImage<uChar> &image, QVImage<uChar> &result);

/*! @brief Obtains the Sobel corner response image
@note This function is based on the IPP library functionality. Thus it requires that library, to be available.
@todo document this
@ingroup qvipp
*/
void SobelCornerResponseImage(const QVImage<sFloat> &image, QVImage<sFloat> &result);

/*! @brief Obtains the Hessian corner response image
@note This function is based on the IPP library functionality. Thus it requires that library, to be available.
@todo document this
@ingroup qvipp
*/
void FilterHessianCornerResponseImage(	const QVImage<sFloat> &image, QVImage<sFloat> &result,
					const QPoint &destROIOffset = QPoint(0,0));

#ifndef DOXYGEN_IGNORE_THIS
void FilterNormalize(const QVImage<uChar,1> &image, QVImage<uChar,1> &equalized, const QPoint &destROIOffset = QPoint(0,0));
void FilterNormalize(const QVImage<sFloat,1> &image, QVImage<sFloat,1> &equalized, const QPoint &destROIOffset = QPoint(0,0));
#endif

/*! @brief Filters connected sets of pixels with small areas, using a component tree.
@note This function is based on the IPP library functionality. Thus it requires that library, to be available.
@todo document this
@ingroup qvipp
@see QVComponentTree
*/
class QVComponentTree;
void FilterPruneComponentTreeSmallRegions(QVImage<uChar> &image, QVComponentTree &componentTree, uInt area);

#ifdef GSL_AVAILABLE
#include <qvmath/qvvector.h>
#include <QPoint>
/*! @brief Applies a separable filter
@note This function is based on the IPP library functionality. Thus it requires that library, to be available.
@note This function also requires GSL compatibility. This will not be necessary in the future.
@todo document this
@ingroup qvipp
*/
void FilterSeparable(const QVImage<sFloat, 1> &image, QVImage<sFloat, 1> &dest,
	const QVVector &rowFilter, const QVVector &colFilter, const QPoint &destROIOffset = QPoint(0,0));
#endif

/*!
@brief Finds luminance peaks in the input image
@todo document this
@see fastMaximalPoints(const QVImage<uChar> &, const double, const int)
@ingroup qvipp
*/
QMap<sFloat, QPointF> fastMaximalPoints(const QVImage<sFloat> &image, const double threshold = 1.0, const int windowSize = 2);

/*!
@brief Finds luminance peaks in the input image
This is an overloaded version provided for convenience. Processing 8 bit depth images is faster than doing it on 64 floating images.

Pixels with a maximal luminance value inside a search window centered at them will be considered peaks. The search algorithm filters low response peaks with a threshold value to improve the performance time.

@param image Image to detect luminance peaks.
@param threshold Threshold used to filter out low luminance value peaks.
@param windowRadius Radius for the search window.

@see maximalPoints(const QVImage<sFloat> &, const double, const int)
@see fastMaximalPoints(const QVImage<sFloat> &, const double, const int)
@ingroup qvipp
*/
QMap<uChar, QPointF>  fastMaximalPoints(const QVImage<uChar> &image, const double threshold, const int windowRadius = 2);

///////////////// END OF IPP DEPENDANT FUNCTIONS //////////////////////////////////////

/*!
@brief Finds luminance peaks in the input image
@todo document this
@ingroup qvip
*/
QMap<sFloat, QPointF> maximalPoints(const QVImage<sFloat> &image, const double threshold = 1.0, const int windowRadius = 2);

/*!
@brief Generates a binary image of local grey-scale maximal value pixels.
@ingroup qvip

This function receives a QVImage, and generates a binary image where each pixel is set to IPP_MAX_8U if the pixel in the
original image is strict maximal in value regarding to pixels in a vicinity window of colMaskSize width, and rowMaskSize
height.

@todo
	- Fix resulting image ROI, obtain maximums restricted to the ROI.
	- Use IPP functions to obtain the result.

@param src source image.
@param dest binary image that will contain maximal values.
@param colMaskSize width of the vicinity.
@param rowMaskSize height of the vicinity.
*/
void FilterLocalMax(const QVImage<sFloat> &src, QVImage<uChar> &dest, uInt colMaskSize, uInt rowMaskSize, sFloat threshold = 0);

/*! @brief Sorts pixels in an image, given their gray-scale value.
@ingroup qvip

This function uses the <a href="http://en.wikipedia.org/wiki/Counting_sort">Counting Sort</a> algorithm to get an arrangement of the pixels of an input 8-bit image, regarding their gray-scale value. This arrangement is useful when you need to process the pixels of that image, which contain a certain gray-scale value.

@param img Image to obtain the pixel arrangement.
@return A vector of 256 lists of points. The element <i>n</i> of the vector is the list of the image pixels (points) that contain the gray-scale value <i>n</i>.
*/
QVector< QVector< QPoint > > CountingSort(const QVImage<uChar, 1> &img);

/*!
@brief Eliminates points of a polyline of small shape contribution using the IPE algorithm
@ingroup qvip

This function eliminates points of a QVPolylineF, simplifying it.
Points are recursively eliminated while a) their distance to the line joining
its two immediate neighbours is smaller than a given maximum value, or
b) the number of points of the approximated polyline falls below a given
number (depending on the chosen method).

The return value (which indicates the cost of the first not deleted point)
and the optional parameter max_removed_cost are useful to estimate
a measure of how well the polyline approximation did. A good
approximation will have (relative) low max_removed_cost/return_cost ratio,
and (absolute) low max_removed_cost value.

@param polyline polyline to simplify.
@param result will store resulting simplified polyline.
@param param maximal distance for a point to eliminate it, if
             maxNumberOfPointsMethod is FALSE, or maximal number of points in the
             result polyline, if maxNumberOfPointsMethod is TRUE.
@param maxNumberOfPointsMethod if TRUE, the procedure ends when the number
             of points of the resulting polyline is lesser or equal to param.
             If FALSE, the procedure ends when there are no more points
             with distance to line given by its neighbours smaller than
             param.
@param intersectLines If TRUE, a post-processing stage adjusts final
             points using all the deleted points among vertexes to fit
             straight lines, whose intersection by pairs gives the final
             points (recommended for greater precision, at a minimal
             additional cost).
@param max_removed_cost If not NULL, pointer to a float value that the
             procedure will fill with the maximum cost (distance to
             corresponding line) of all the removed points.
@return The function returns the cost value of the first NOT deleted point
        of the polyline.
@see IterativePointElimination(const QVPolylineF &, QVPolyline &, const double, bool, bool, double *);
*/
double IterativePointElimination(const QVPolyline &polyline, QVPolyline &result,
	const double param, bool maxNumberOfPointsMethod=FALSE,
	bool intersectLines=TRUE, double *max_removed_cost=NULL);

/*!
@brief Eliminates points of a polyline of small shape contribution using the IPE algorithm
@ingroup qvip

This is an overloaded version of the <i>IterativePointElimination</i>, provided for convenience. It simplifies floating point polylines.

@see IterativePointElimination(const QVPolyline &, QVPolyline &, const double, bool, bool, double *);
@note If GSL compatibility is not enabled, the re-estimation of the segments intersection will not be done. Thus the parameter intersectLines will always be considered false.
*/
double IterativePointElimination(const QVPolylineF &polyline, QVPolylineF &result,
	const double param, bool maxNumberOfPointsMethod=FALSE,
	bool intersectLines=TRUE, double *max_removed_cost=NULL);

/*
@brief Obtains the border contour of a connected set of pixels in an image, given a membership condition.
@ingroup qvip

This function obtains the borders of <a href="http://en.wikipedia.org/wiki/Connected_set">connected sets</a> of pixels, containing gray-scale values equal or greater than a given threshold value.

Both inner borders and outer borders of each connected set detected by the function are transversed. Each border is transversed, storing the pixels detected on it in a polyline.

@param image Image to obtain from the borders.
@param threshold Threshold separating the pixels inside and outside the connected sets.
@returns A list, containing the polylines corresponding to the borders of the connected sets.




Borders obtained with this function can be either inner borders (corresponding to the border of an empty space inside the connected set) or the outer border of the connected set. The programmer can tell whether a given border is inner or outer by the boolean value @ref QVPolyline::direction, which will store <i>TRUE</i> for an outer contour, and <i>FALSE</i> for an inner contour.


@see getConnectedSetBorderContoursThreshold
*/
#ifndef DOXYGEN_IGNORE_THIS
QVPolyline getConnectedSetBorderContourThreshold(const QVImage<uChar> &image, const QPoint point, const uChar threshold = 128);
QVPolyline getConnectedSetBorderContourThreshold(const QVImage<uShort> &image, const QPoint point, const uShort threshold = 128);
#endif

/*!
@brief Obtains the borders of connected sets of pixels, containing gray-scale values equal or greater than a given threshold.
@ingroup qvip

This function thresholds an input image. Then it obtains the borders of the <a href="http://en.wikipedia.org/wiki/Connected_set">connected sets</a> of the pixels remaining. An example of these connected sets, and the borders this function obtains can be seen in the following picture:

\image html bordercontours.png

Circles indicate the first of the pixels in each border set. The last of the pixels in each detected border is indicated with an asterisk.
The function detects inner and outer borders for each connected set. The image displays inner borders in blue color, and outer borders in red color.

The function returns a list of polylines, each one representing a different border.

@param image Image to obtain from the borders.
@param threshold Threshold separating the pixels inside and outside the connected sets.
@returns A list, containing the polylines corresponding to the borders of the connected sets.
*/
QList<QVPolyline> getConnectedSetBorderContoursThreshold(const QVImage <uChar> &image, const uChar threshold = 128);
QList<QVPolyline> getConnectedSetBorderContoursThreshold(const QVImage <uShort> &image, const uShort threshold = 128);

/*!
@brief Obtains a list of the 4-connected pixel lines in the image
@ingroup qvip

This function can be used to obtain the 4-connected lines appearing in a border response image.
It returns the lines as a @ref QVPolyline objects.

A pixel will be considered as a line pixel if it contains a gray-scale value equal or larger than the given threshold.

\image html contours4connected.png

Circles indicate the first of the pixels in each line. The last of the pixels in each detected line is indicated with an asterisk.
Ambiguous situations (such as pixels with more than two 4-connected neighbor pixels) return unpredictable joining results.

@param image image from were to obtain the polylines.
@param threshold threshold to test if a pixel is considered a line pixels or not.
@returns the list of contours (as @ref QVPolyline) in the image.
@see Canny
*/
QList<QVPolyline> getLineContoursThreshold4Connectivity(const QVImage<uChar> &image, const uChar threshold = 128);

/*!
@brief Obtains a list of the 8-connected pixel lines in the image
@ingroup qvip

This function can be used to obtain the 8-connected lines appearing in a border response image.
It returns the lines as a @ref QVPolyline objects.

A pixel will be considered as a line pixel if it contains a gray-scale value equal or larger than the given threshold.

\image html contours8connected.png

Circles indicate the first of the pixels in each line. The last of the pixels in each detected line is indicated with an asterisk.
Ambiguous situations (such as pixels with more than two 4-connected neighbor pixels) return unpredictable joining results.

@param image image from were to obtain the polylines.
@param threshold threshold to test if a pixel is considered a border or not.
@returns the list of contours (as @ref QVPolyline) in the image.
@see Canny
*/
QList<QVPolyline> getLineContoursThreshold8Connectivity(const QVImage<uChar> &image, const uChar threshold = 128);


/*!
@brief FAST detection algorithms.
@ingroup qvip
*/
enum FASTDetectionAlgorithm {
	Fast9 = 9,
	Fast10 = 10,
	Fast11 = 11,
	Fast12 = 12
	};

/*!
@brief Obtains FAST features on an image-
@note This function is a wrapper function for Edward Rosten's <a href="http://www.edwardrosten.com/work/fast.html">FAST detector implementation</a>.

@param image Input image.
@param threshold Threshold value for the FAST algorithm.
@param fastAlgorithm One of the four versions of the FAST detector.

@return List of locations for the FAST features in the image.
@ingroup qvip
*/
QList<QPointF> FASTFeatures(const QVImage<uChar, 1> & image, const int threshold, const FASTDetectionAlgorithm &fastAlgorithm = Fast9);

// --------------------------------------------

/*!
@brief Applies a fast Laplace filter on the input image

This function returns the following \f$ 3 \times 3 \f$ matrix, corresponding to the intrinsic calibration matrix of a camera:

Obtains an image containing the absolute values corresponding to the image filtered with the following convolution kernel:

\f$K = \frac{1}{8}\left(\begin{array}{ccc} 0 & -1 & 0 \\ -1 & 4 & -1 \\ 0 & -1 & 0 \end{array}\right)\f$

@param image Input image.
@ingroup qvip
*/
QVImage<uChar, 1> FastLaplaceFilter(const QVImage<uChar, 1> image);

/*!
@brief Applies a fast smooth filter on the input image

This function convolutes the image with the following filter:

\f$K = \frac{1}{8}\left(\begin{array}{ccc} 0 & 1 & 0 \\ 1 & 4 & 1 \\ 0 & 1 & 0 \end{array}\right)\f$

@param image Input image.
@param threshold pixels with a value velow this threshold will be set to zero directly.
@ingroup qvip
*/
QVImage<uChar, 1> FastSmoothFilter(const QVImage<uChar, 1> image, const uChar threshold = 0);

/*!
@brief Applies a smooth filter on the input image

This function convolutes the image with the following filter:

\f$K = \frac{1}{16}\left(\begin{array}{ccc} 1 & 2 & 1 \\ 2 & 4 & 2 \\ 1 & 2 & 1 \end{array}\right)\f$

@param image Input image.
@param threshold pixels with a value velow this threshold will be set to zero directly.
@ingroup qvip
*/
QVImage<uChar, 1> SmoothFilter(const QVImage<uChar, 1> image, const uChar threshold = 0);

/*!
@brief Detects salient points in the Laplace response of an input image.

This function uses @ref FastLaplaceFilter and @ref getLocalExtremaPixels to detect maximal pixels in the Laplace response image.

@param image Input image.
@param threshold Ignore pixels in the Laplace response image with a value velow this threshold. Set it to a non-zero value to speed up the maximal detection.
@param applyPreviousSmooth Apply a fast smooth on the input image using the function @ref FastSmoothFilter before obtaining the Laplace response image.
@param smoothResponseImage Apply a fast smooth on the Laplace response image before the maximal pixel detection.
@ingroup qvip
*/
QList<QPointF> FastLaplacePoints(const QVImage<uChar, 1> &image, const int threshold = 40, const bool applyPreviousSmooth = true, const bool smoothResponseImage = true);

#ifndef DOXYGEN_IGNORE_THIS
QList<QPointF> getLocalExtremaPixels(const QVImage<uChar, 1> hiPass, const int HiPassThreshold);
double ShiTomasiScore(const uChar *imagePtr, const int imageStep, const int x, const int y, const int nHalfBoxSize);
QMap<double, QPointF> pointsByShiTomasiValue(const QVImage<uChar, 1> & image, const QList<QPointF> &points, const int shiTomasiRadius);
QList<QPointF> hiPassPointDetector(const QVImage<uChar, 1> &image, const int threshold);
QList<QPointF> DoGPointDetector(const QVImage<uChar, 1> &image, const int threshold);

void FilterGauss8Adjacency(const QVImage<uChar, 1> responseImg, QVImage<uChar, 1> &result);

#endif // DOXYGEN_IGNORE_THIS

#endif

