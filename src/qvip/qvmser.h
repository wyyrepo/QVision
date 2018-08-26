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

#ifndef QVMSER_H
#define QVMSER_H

#include <qvdefines.h>
#include <QVPolyline>
#include <QVComponentTree>

/*! @class QVMSER qvip/qvmser.h QVMSER
@brief Maximally stable extremal region datatype.
@ingroup qvmser
*/
class QVMSER
	{
	public:
            QVMSER() : seed(0,0), threshold(0), merit(0.0), area(0) { };
            QVMSER(QPoint s, uChar t): seed(s), threshold(t) {};
            QVMSER(int pseedx, int pseedy, int pth, float pmerit, int parea):
                        seed(pseedx,pseedy), threshold(pth), merit(pmerit), area(parea) { };

            /// @brief Seed coordinates (darkest point in region)
            QPoint seed;

            /// @brief Threshold value to obtain region
            uChar threshold;

            /// @brief Merit value (i.e., value of \f$ \frac{area_{th-delta} - area_{th-delta}}{area_{th-delta}} \f$ )
            float merit;

            /// @brief Area of region (in pixels)
            int area;
        };

/*!
@brief Obtains border contours for an MSER list, obtained with the function @ref getMSER
@ingroup qvip

@param image image to obtain border contours of MSER. Should be the same used with the function @ref getMSER, if that was the one used to obtain MSER list.
@param MSERList list of MSER. It generally will be obtain using the function @ref getMSER.
@param polylineMSERList list of border contours, represented as @ref QVPolyline objects.
@see getMSER
*/
void getMSERContours(const QVImage<uChar, 1> &image, const QList<QVMSER> &MSERList, QList< QVPolyline > &polylineMSERList);

/*! @brief This algorithm obtains MSER's - from an image.
@ingroup qvip

This is an implementation of the MSER algorithm (see [<a href="#matas">Matas</a>]. It does clustering of the MSER found in each node, keeping just the one with lowest <i>q</i> value. Also, small or large MSER are cleaned up using minimal and maximal areas permitted.

REFERENCES:<ul>
<li><a name="matas"><i>Robust Wide Baseline Stereo from Maximally Stable Extremal Regions</i>. J. Matas et al.</li>
<li><a name="vedaldi"><i>An implementation of Multi-Dimensional Maximally Stable Extremal Regions</i></a>. Andrea Vedaldi.</li>
@param image image to obtain MSER's from.
@param MSERList list that will contain obtained MSER's.
@param delta Delta parameter from the [<a href="#matas">Matas</a>] paper.
@param minArea MSER of area lesser than this value are discarted.
@param maxArea MSER of area greater than this value are discarted.
@param diffAreaThreshold MSER found to have a relative difference of areas lesser to that value are clustered together, and
@see getMSERContours
the algorithm just keeps the one with lesser <i>q</i> value, discarding the others.
*/
void getMSER(const QVImage<uChar,1> &image, QList<QVMSER> &MSERList, const int delta, const int minArea, const int maxArea, const double diffAreaThreshold);
#endif

