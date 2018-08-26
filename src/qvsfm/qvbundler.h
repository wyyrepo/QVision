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

#ifndef QVBUNDLER_H
#define QVBUNDLER_H

#include <QString>
#include <QVDirectedGraph>

/*!
@brief Write matching information from the <i>matchings</i> file.

@param fileName Name for the destination file.
@param matchings Matchings graph containing pair-wise indexes for the matched features.
@ingroup qvbundler
@todo Document this.
*/
bool writeMatchingsToBundlerMatchingsFile(const QString &fileName, const QVDirectedGraph< QVector<QVIndexPair> > &matchings);

#endif
