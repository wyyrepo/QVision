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

#include <QVBRIEFDetector>
#include <QVIndexPair>
QVector <QVIndexPair> getImageFeaturedSortedPairs(	const QVBRIEFDetector &briefDetector,
													const QVector<unsigned int> &sourceFrameBRIEFDescriptors,
													const QVector<unsigned int> &destFrameBRIEFDescriptors,
													const int maxBinaryDistance = 256,
													const int maxFeatures = std::numeric_limits<int>::max())
	{
	const int	sourceCount = sourceFrameBRIEFDescriptors.count() / briefDetector.getDescriptorInts(),
				destCount = destFrameBRIEFDescriptors.count() / briefDetector.getDescriptorInts();

	// Search parameters.
	const int maxTests = MIN(maxBinaryDistance, briefDetector.getNumTests());

	// Brute force matching for descriptors: every source descriptor with every destination descriptor.
	int sortedMatchingsCount = 0;
	QVector< QList< QVIndexPair > > matchingsHistogramVector(maxTests);
	for(int i = 0; i < MIN(sourceCount, maxFeatures); i++)
		for(int j = 0; j < MIN(destCount, maxFeatures); j++)
			{
			const int distanceBis =	briefDetector.distance(sourceFrameBRIEFDescriptors, destFrameBRIEFDescriptors, i, j);

			if (distanceBis < maxTests)
				{
				matchingsHistogramVector [ distanceBis ] << QVIndexPair(i, j);
				sortedMatchingsCount++;
				}
			}

	// Get list of matchings sorted by their Hamming distance.
	QVector<QVIndexPair> sortedMatchings;
	sortedMatchings.reserve(sortedMatchingsCount);
	for(int i = 0; i < maxTests; i++)
		foreach(QVIndexPair pair, matchingsHistogramVector [ i ])
			sortedMatchings << pair;

	return sortedMatchings;
	}

#include <QFile>
#include <QTextStream>
bool saveBRIEFDescriptorsInLoweSIFTFileFormat(const QString fileName, const QVector<QPointF> features, const QVector<unsigned int> descriptors)
	{
	const int descriptorInts = descriptors.count() / features.count();

	QFile	keyFile(fileName);
	if (not keyFile.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

    QTextStream	outFile(&keyFile);

	bool cond = false;

	outFile << features.count() << " " << (descriptorInts*32) << "\n";
	for(int i = 0; i < features.count(); i++)
			{

			if (cond)
				outFile << "\n";

			outFile << features[i].y() << " " << features[i].x() << " 1.0 0.0\n";

			//outFile.setIntegerBase(16);
			//for (int j = 0; j < BRIEFDetector.getDescriptorInts(); j++)
			//	outFile << "*** " << descriptors[ i * BRIEFDetector.getDescriptorInts() + j ] << "\n";
			//outFile.setIntegerBase(10);

			for (int j = 0, n = 0; j < descriptorInts; j++)
				{
				const int intIndex = i * descriptorInts + j;
				Q_ASSERT(intIndex < descriptors.count());
				int tests = descriptors[intIndex];

				for(int k = 0; k < 32; k++, n++)
					{
					outFile << " " << ((tests & 1)?"255":"0");
					tests >>= 1;
					if (( (n+1) % 20) == 0)
						outFile << "\n";
					}
				}

			cond = true;
			}
	keyFile.close(); 

	return true;
	}

