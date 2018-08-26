/*
 *	Copyright (C) 2012. PARP Research Group.
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
#include <iostream>

#ifndef QVBRIEFDETECTOR_H
#define QVBRIEFDETECTOR_H

#include <QVImage>
#include <QVKeypoint>

#include <math.h>

/*! @brief Simple implementation of BRIEF (Binary Robust Independent Elementary Features) descriptors

BRIEF descriptors are designed to perform accelerated image keypoint matching.

These descriptors are variant to scale and orientation, but their lightweight evaluation and matching speed make them suitable for many different image matching applications.

BRIEF descriptors are binary strings representing a pattern of pair-wise comparations of pixels or tests, located inside a patch on the image centered at the given keypoint.

This class obtains BRIEF descriptors for points from an input image, and can be used to perform an efficient matching between them.

The following is an example usage code:

@code
// Init BRIEF detector.
// The detector will generate 3*32 test patterns.
// Each descriptor contains 3 integer values, and 32 bits for each integer value store tests results.
// The maximal distance between the tested pixels in the pattern to the feature location is 5 pixels.
// The binary test pattern is different for each BRIEF detector object created.
QVBRIEFDetector BRIEFDetector(3,5);

// Init images and keypoint lists
QVImage<uChar, 1> imageA, imageB;
QVector<QPointF> keypointsA, keypointsB;

[...]

// Get descriptors for keypoints and images.
// It is important to use the same BRIEF detector to compare descriptors from different images.
// Each vector of binary descriptors will contain n*m integers, where 'n' is the size of the keypoint list,
// and 'm' is the number of integers per descriptor (in this case, m = 3).
QVector<unsigned int>	binaryDescriptorsA = BRIEFDetector.getDescriptors(imageA, keypointsA), // Get descriptors for keypoints in image A.
			binaryDescriptorsB = BRIEFDetector.getDescriptors(imageB, keypointsB);	// Get descriptors for keypoints in image B.

[...]

// Example code to obtain the distance between the descriptor for each keypoint in A, and the descriptor for each point in B.
// The result is stored in the following distance matrix.
QVMatrix distanceMatrix(keypointsA.count(), keypointsB.count(), 0.0);

for(int i = 0; i < keypointsA.count(); i++)
	for(int j = 0; j < keypointsB.count(); j++)
		// Get distance between i-th descriptor from image A, and j-th descriptor from image B.
		// The comparison must be done with the same BRIEF detector used to obtain the descriptors.
		distanceMatrix(i,j) = BRIEFDetector.distance( binaryDescriptorsA, binaryDescriptorsB, i, j);

@endcode

@ingroup qvip
*/
class QVBRIEFDetector
	{
	private:
		const unsigned int descriptorInts, numTests;
		const int windowRadius;

	public:
		QVector<char> coordinates;

	public:
		inline unsigned int getWindowRadius()		const	{ return windowRadius; }
		inline unsigned int getNumTests()			const	{ return numTests; }
		//inline unsigned int getDescriptorBytes()	const	{ return descriptorInts; }
		inline unsigned int getDescriptorInts()		const	{ return descriptorInts; }

		/// @brief Evaluates the Hamming distance between two binary descriptors.
		///
		/// This method uses the xor operator and the @ref qvNiftyParallelBitCount function to evaluate the number of bits
		/// which differ between two binary descriptors.
		///
		/// @param descriptorsA set of descriptors for the first image.
		/// @param descriptorsB set of descriptors for the second image.
		/// @param indexA	index for the feature descriptor in the first image.
		/// @param indexB	index for the feature descriptor in the second image.
		/// @return the number of bits set in the integer obtained from the xor operation between the two descriptors.
		inline unsigned int distance(const QVector<unsigned int> &descriptorsA, const QVector<unsigned int> &descriptorsB, const int indexA = 0, const int indexB = 0) const
			{
			Q_ASSERT(descriptorsA.count() > descriptorInts * indexA);
			Q_ASSERT(descriptorsB.count() > descriptorInts * indexB);

			const unsigned int	*dA = &(descriptorsA[descriptorInts*indexA]),
								*dB = &(descriptorsB[descriptorInts*indexB]);

			unsigned int count = 0;
			for(int i = 0; i < descriptorInts; i++)
				count += qvNiftyParallelBitCount(dA[i] xor dB[i]);

			return count;
			}

		/// @brief Main constructor.
		/// @param descriptorInts Size of the descriptor. Each element of the descriptor is an integer containing 32 bit tests.
		/// @param windowRadius Max radius for the testing window around the pixel.
		QVBRIEFDetector(const unsigned int descriptorInts = 4, const unsigned int windowRadius = 16):
			descriptorInts(descriptorInts), numTests(descriptorInts*32), windowRadius(windowRadius), coordinates(numTests * 4)
			{
			if (windowRadius > 127)
				std::cout << "[QVBRIEFDetector0::QVBRIEFDetector0()] Error: Test distance must be less than 127." << std::endl;

			//for(unsigned int i = 0; i < coordinates[0].count(); i++)
			//	coordinates[0][i] = rand()%(2*windowRadius) - windowRadius;

			for(unsigned int i = 0; i < numTests*4; i+=2)
				{
				const double	random1 = double(random()%1000) / 1000.0,
								random2 = double(random()%500) / 1000.0 + 0.5;

				Q_ASSERT(random1 >= 0);
				Q_ASSERT(random2 >= 0);
				Q_ASSERT(random1 <= 1.0);
				Q_ASSERT(random2 <= 1.0);

				const double	angle = 2.0 * PI * random1,
								dist = random2;

				const int	x = qvSymmetricFloor(dist * cos(angle) * int(windowRadius)),
							y = qvSymmetricFloor(dist * sin(angle) * int(windowRadius));

				Q_ASSERT(x >= -int(windowRadius));
				Q_ASSERT(y >= -int(windowRadius));
				Q_ASSERT(x <= +int(windowRadius));
				Q_ASSERT(y <= +int(windowRadius));

				coordinates[i+0] = x;
				coordinates[i+1] = y;
				}
			}

		/// @brief Gets the descriptor for a set of features in an image.
		/// @return a vector containing the concatenated descriptors for the features in the image. The order of the features is preserved in the vector of descriptors.
		QVector<unsigned int> getDescriptors(	const QVImage<uChar, 1> &image,
												const QVector<QPointF> &keypoints,
												const unsigned int octave = 1) const
			{
			QVector<unsigned int> result(keypoints.count()*descriptorInts);

			const uChar	*imgData = image.getReadData();

			const int	imgStep = image.getStep(),
						imgCols = image.getCols(),
						imgRows = image.getRows();

			#ifdef DEBUG
			const uChar *imageDataLimit = imgData + imgStep * imgCols + imgRows;
			#endif // DEBUG

			// Get the binary descriptors for the keypoints.
			for(int index = 0; index < keypoints.count(); index++)
				{
				const QPointF &kp = keypoints[index];

				//const int	xCoor = kp.x(), //double(kp.x) / double(kp.scale),
				//			yCoor = kp.y(); //double(kp.y) / double(kp.scale);

				const int	xCoor = kp.x() / double(octave),
							yCoor = kp.y() / double(octave);

				// Expected range for the angle.
				//Q_ASSERT(kp.angle >= -PI);
				//Q_ASSERT(kp.angle <= +PI);

				const QVector<char> coors = coordinates;

				// Mind the image data boundaries.
				Q_ASSERT(xCoor - windowRadius >= 0);
				Q_ASSERT(yCoor - windowRadius >= 0);
				Q_ASSERT(xCoor + windowRadius < imgCols);
				Q_ASSERT(yCoor + windowRadius < imgRows);

				// Get the binary descriptor for the keypoint.
				const uChar *pixelPtr = imgData + imgStep * yCoor + xCoor;
				for(int b = 0; b < descriptorInts; b++)
					{
					Q_ASSERT(result.count() > descriptorInts*index+b);

					int ac = 0;
					unsigned int binaryDescriptor = 0;
					for(int i = 32*4*b; i < 32*4*(b+1); i+=4)
						{
						Q_ASSERT(i+3 < coors.count());

						// Careful with the image data boundaries.
						Q_ASSERT(xCoor + coors[i+0] >= 0);
						Q_ASSERT(yCoor + coors[i+1] >= 0);
						Q_ASSERT(xCoor + coors[i+0] < imgCols);
						Q_ASSERT(yCoor + coors[i+1] < imgRows);

						Q_ASSERT(xCoor + coors[i+2] >= 0);
						Q_ASSERT(yCoor + coors[i+3] >= 0);
						Q_ASSERT(xCoor + coors[i+2] < imgCols);
						Q_ASSERT(yCoor + coors[i+3] < imgRows);

						Q_ASSERT(*(pixelPtr + imgStep * coors[i+1] + coors[i+0]) == pixelPtr[ imgStep * coors[i+1] + coors[i+0] ]);
						Q_ASSERT(*(pixelPtr + imgStep * coors[i+3] + coors[i+2]) == pixelPtr[ imgStep * coors[i+3] + coors[i+2] ]);

						// Shift binary descriptor, to make room for the result of the next binary test.
						binaryDescriptor <<=1;

						// Evaluate binary test.
						binaryDescriptor |=	pixelPtr[ imgStep * coors[i+1] + coors[i+0] ]	// First pixel in the binary test.
											>
											pixelPtr[ imgStep * coors[i+3] + coors[i+2] ];	// Second pixel in the binary test.

						}
					result[descriptorInts*index+b] = binaryDescriptor;
					}
				}

			return result;
			}
	};

/*!
@brief Write a list of image features and BRIEF descriptors to a text file.

This function writes a list of image features and their associated BRIEF descriptors in a .key file in the same output format used
by <a href="http://www.cs.ubc.ca/~lowe/keypoints/">David Lowe's SIFT detector</a> to store the SIFT descriptors and
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

@ingroup qvip
*/
bool saveBRIEFDescriptorsInLoweSIFTFileFormat(const QString fileName, const QVector<QPointF> features, const QVector<unsigned int> descriptors);

#endif // QVBRIEFDETECTOR_H
