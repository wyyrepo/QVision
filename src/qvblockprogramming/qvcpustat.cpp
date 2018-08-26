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

#include <qvblockprogramming/qvcpustat.h>
#include <iostream>

void QVStat::addFlag(int pos, QString name)
	{
	if (pos > flagNames.size())
		{
		std::cerr << "cpustat::addFlag -> index out of bounds" << std::endl;
		return;
		}

	lastOrder++;
	flagOrder.insert(pos, lastOrder);
	flagNames.insert(pos, name);
	stats.insert(pos, 0);
	}

void QVStat::setValue(int pos, double value)
	{
	if (pos > flagNames.size())
		{
		std::cerr << "cpustat::setValue -> index out of bounds" << std::endl;
		return;
		}

	stats[pos] = value;
	}


