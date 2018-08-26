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

#include <QVVector>
#include <QVKeypoint>
#include <QFile>
#include <QTextStream>
#include <QVSiftFeature>

bool saveSIFTDescriptorsInLoweSIFTFileFormat(const QString &fileName, const QList<QVSiftFeature> &features)
	{
	QFile file(fileName);
	if (not file.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

	QTextStream stream(&file);

	stream.setRealNumberPrecision(16); // Default is 6, not enough precission to faithfully store certain maps.

	stream << features.count() << " 128\n";
	foreach(QVSiftFeature feature, features)
		{
		stream	<< feature.keypoint.y() << " "
			<< feature.keypoint.x() << " "
			<< feature.keypoint.scale() << " "
			<< feature.keypoint.orientation();

		const QVVector descriptor = 512 * feature.descriptor / feature.descriptor.norm2();

		for(int i = 0; i < 128; i++)
			{
			if ( (i % 20) == 0 )
				stream << "\n";
			stream << " " << int(descriptor[i]);
			}
		stream << "\n";
		}

	file.close();
	return true;
	}

