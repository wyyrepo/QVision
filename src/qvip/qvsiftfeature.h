/*
 *	Copyright (C) 2011, 2012. PARP Research Group.
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

#ifndef QVSIFTFEATURE_H
#define QVSIFTFEATURE_H

#include <QVVector>
#include <QVKeypoint>

/*!
@class QVSiftFeature qvip/qvsiftfeature.h QVSiftFeature
@brief Class for SIFT feature.

This class contains the keypoint location and the SIFT descriptor for a SIFT image feature.

@ingroup qvip
*/
class QVSiftFeature
	{
	public:
		QVKeypoint keypoint;
		QVVector descriptor;

		/// @brief Default constructor
		///
		/// Creates a new SIFT image feature from a keypoint location and a descriptor vector.
		///
		/// @param keypoint Keypoint location form the SIFT image feature.
		/// @param descriptor Descriptor vector.
		QVSiftFeature(const QVKeypoint keypoint = QVKeypoint(), const QVVector descriptor = QVVector()):
			keypoint(keypoint), descriptor(descriptor)
				{ }

		double distance(const QVSiftFeature &other) const
			{
			return (descriptor - other.descriptor).norm2();
			}
	};

/*!
@brief Write a list of image features and BRIEF descriptors to a text file in Lowe's SIFT file format.

This function writes a list of image features and their associated BRIEF descriptors in a .key file in the same output format used
by the application<a href="http://www.cs.ubc.ca/~lowe/keypoints/">David Lowe's SIFT detector</a> to store the SIFT descriptors and
the features detected on an input image.

The following is an extract of the documentation for Lowe's implementation, which describes this output format:

@code
The file format starts with 2 integers giving the total number of
keypoints and the length of the descriptor vector for each keypoint
(128). Then the location of each keypoint in the image is specified by
4 floating point numbers giving subpixel row and column location,
scale, and orientation (in radians from -PI to PI).  Obviously, these
numbers are not invariant to viewpoint, but can be used in later
stages of processing to check for geometric consistency among matches.
Finally, the invariant descriptor vector for the keypoint is given as
a list of 128 integers in range [0,255].  Keypoints from a new image
can be matched to those from previous images by simply looking for the
descriptor vector with closest Euclidean distance among all vectors
from previous images.
@endcode

@param fileName Name for the descriptor's file.
@param features List containing the location for the image features.
@param descriptors List containing the corresponding descriptors for these features.

@see QVBRIEFDetector

@ingroup qvip
*/
bool saveBRIEFDescriptorsInLoweSIFTFileFormat(const QString fileName, const QVector<QPointF> features, const QVector<unsigned int> descriptors);

/*!
@brief Write a list of SIFT image features to a text file in Lowe's SIFT file format.

This function writes a list of SIFT features and their associated descriptors in a .key file in the same output format used
by the application <a href="http://www.cs.ubc.ca/~lowe/keypoints/">David Lowe's SIFT detector</a> to store the SIFT descriptors and
the features detected on an input image.

The following is an extract of the documentation for Lowe's implementation, which describes this output format:

@code
The file format starts with 2 integers giving the total number of
keypoints and the length of the descriptor vector for each keypoint
(128). Then the location of each keypoint in the image is specified by
4 floating point numbers giving subpixel row and column location,
scale, and orientation (in radians from -PI to PI).  Obviously, these
numbers are not invariant to viewpoint, but can be used in later
stages of processing to check for geometric consistency among matches.
Finally, the invariant descriptor vector for the keypoint is given as
a list of 128 integers in range [0,255].  Keypoints from a new image
can be matched to those from previous images by simply looking for the
descriptor vector with closest Euclidean distance among all vectors
from previous images.
@endcode

@param fileName Name for the descriptor's file.
@param features List of SIFT features.

@ingroup qvip
*/
bool saveSIFTDescriptorsInLoweSIFTFileFormat(const QString &fileName, const QList<QVSiftFeature> &features);

#endif
