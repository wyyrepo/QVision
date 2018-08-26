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

#ifndef QVCPUSTATCONTROLER_H
#define QVCPUSTATCONTROLER_H
#include <qvblockprogramming/qvcpustat.h>
#include <QTime>

#ifndef DOXYGEN_IGNORE_THIS
class QVStatControler : public QObject
{
Q_OBJECT
public:
	QVStatControler(): QObject(), cpustats(), lastTime(), lastFlagPos(-1), totalRounds(0), rounds(0), freq(0), blockName()
		{ lastTime.start(); }
	void step();
	void setFlag(QString name);
	QVStat value() const { return cpustats; }
	void setFreq(int frequency);
	void setBlockName(QString name) { blockName = name; }
	void printStats();

private:
	QVStat cpustats;
	QTime lastTime;
	int lastFlagPos;


	int totalRounds, rounds, freq;
        QList<double> accumulated, totalAccumulated;
	QString blockName;
	
};
#endif
#endif
