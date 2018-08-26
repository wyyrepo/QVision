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

/// @file qvltmser.h
/// @brief Functions to get image regions using the linear time MSER algorithm by Nister and Stewanius (ECCV 2008)
/// @author PARP Research Group. University of Murcia, Spain.

#ifndef QVLTMSER_H
#define QVLTMSER_H

#include <QVPolyline>
#include <QVMSER>

/*!
@brief Obtains the MSER (linear time MSER) contours from a QVImage<uChar>.

The obtained MSER are in fact only the MSER+ (regions darker than background). If you want to
detect MSER- regions, you should manually negate the input image (using Not function, for example),
and calling again this function. Besides the typical parameters (minArea, maxArea, delta and
delta_threshold; see paper), the last parameter to this function allows to downscale the input image
used to obtain the (intermediate) MSER seeds, though the final seed position values are returned
rescaled back to the original size. This can be used to accelerate seed extraction (of course at the
cost of discarding smaller regions) without loosing precision when obtaining the rest of contours
(as the seeds are used on the original image, instead of the rescaled one, thus preserving original
precission in the borders of each contour -in fact, this is not completely true, because the final
threshold is also affected by downscaling; anyway, for many applications the approximation should
behave acceptably-).

@ingroup qvmser

@param input_image Image to obtain MSERs from.
@param minArea Minimum area for each MSER.
@param maxArea Maximal area for each MSER.
@param delta Delta value for MSER algorithm (see paper).
@param delta_threhold Delta threshold value for MSER algorithm.
@param downscaling Initial scaling performed of input image; by default, no downscaling is performed

@returns output_contours List of output contours corresponding to detected MSERs.

@see getLTMSER getLTMSERContours(QVImage<uChar>&,QList<QVMSER>);
*/
QList<QVPolyline> getLTMSERContours(QVImage< uChar > &input_image,
                                    const int minArea=20, const int maxArea=100000,
                                    const int delta=15, const float delta_threshold=0.03,
                                    const unsigned int downscaling=1);

/*!
@brief Obtains the extracted MSER regions (QVMSER structures) using linear time MSER on a QVImage<uChar>

This function differs from the one above in that it does not compute the corresponding contours.

@ingroup qvmser

@param input_image Image to obtain MSERs from.
@param minArea Minimum area for MSER.
@param maxArea Maximal area for MSER.
@param delta Delta value for MSER algorithm (see paper).
@param delta_threhold Delta threshold value for MSER algorithm.
@param downscaling Initial scaling performed of input image; by default, no downscaling is performed

@returns List of output obtained QVMSER structures.

@see getLTMSERContours(QVImage<uChar> &,const int,const int,const int,const float,const unsigned int) getLTMSERContours(QVImage<uChar> &,QList<QVMSER>) QVMSER
*/
QList<QVMSER> getLTMSER(QVImage< uChar > &input_image,
                        const int minArea=20, const int maxArea=100000,
                        const int delta=15, const float delta_threshold=0.03,
                        const unsigned int downscaling=1);

/*!
@brief Obtains the MSER (linear time MSER) contours corresponding to a list of given QVMSER structures.

This function can be called with the output of the above function to get the list of contours
corresponding to a list of given QVMSER structures.

@ingroup qvmser

@param input_image Image to obtain MSERs from.
@param minArea Minimum area for MSER.
@param maxArea Maximal area for MSER.
@param delta Delta value for MSER algorithm (see paper).
@param delta_threhold Delta threshold value for MSER algorithm.

@returns List of output contours obtained from the input QVMSER structures.

@see getLTMSERContours(QVImage<uChar> &,const int,const int,const int,const float,const unsigned int) getLTMSER QVMSER
*/
QList<QVPolyline> getLTMSERContours(QVImage< uChar > &input_image,QList<QVMSER> mser_list);

#endif
