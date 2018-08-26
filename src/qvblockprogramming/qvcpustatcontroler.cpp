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

#include <qvblockprogramming/qvcpustatcontroler.h>

#include <iostream>

void QVStatControler::step()
	{
	if (freq > 0)
		{
		for (int i = 0; i < cpustats.getFlagNames().size(); i++)
			accumulated[i] += cpustats.getLastStats()[i];
		rounds++;
		if ( (rounds % freq) == 0 ) printStats();
		}

	lastFlagPos = -1;
	lastTime.start();
	}


void QVStatControler::setFreq(int frequency)
		{
		if (frequency >= 0)
			{
			freq = frequency;
        		for (int i = 0; i < cpustats.getFlagNames().size(); i++)
                		accumulated[i] = 0;
			rounds = 0;
			}
		}

void QVStatControler::printStats()
	{
	for (int i = 0; i < cpustats.getFlagNames().size(); i++)
		totalAccumulated[i] += (accumulated[i] / rounds);
	totalRounds++;

	std::cout << "Cpu stats of " << blockName.toStdString() << ": Iteration " << totalRounds << " (steps elapsed " << rounds << ")." << std::endl;
	std::cout << "Cpu stats:\t\tMean Total\tMean Actual\tFlag name" << std::endl;
	for (int i = 0; i< cpustats.getFlagNames().size(); i++)
		std::cout << "CpuStat: stats:\t\t" << totalAccumulated[i]/(double)totalRounds << "\t\t" << (accumulated[i] / rounds) << "\t\t"
			  << cpustats.getFlagNames().at(i).toStdString() << std::endl;
	std::cout << "Cpu stats:" << std::endl;

	for (int i = 0; i < cpustats.getFlagNames().size(); i++)
		accumulated[i] = 0;
	rounds = 0;
	}


void QVStatControler::setFlag(QString flagName)
	{
	bool exist = (cpustats.getFlagNames()).contains(flagName);
	double elapsedTime = lastTime.restart();
	
	lastFlagPos++;
	if (!exist)
		{
		cpustats.addFlag(lastFlagPos, flagName);
                accumulated.insert(lastFlagPos, 0);
                totalAccumulated.insert(lastFlagPos, 0);
		}
	cpustats.setValue(lastFlagPos, elapsedTime);
	}




