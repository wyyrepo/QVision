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

#ifndef QNAMEDPIPE_H
#define QNAMEDPIPE_H

#include <qobject.h>

#ifdef WIN32
#include <QThread>
#include <windows.h>
#include <tchar.h>
class QNamedPipeThread : public QThread
	{
	public:
		QNamedPipeThread(HANDLE, HANDLE, char *);
		~QNamedPipeThread();
		void run();
		bool finished;
	private:
		HANDLE hPipe1, hPipe2;
		char *pipeName;
	};

#endif

class QNamedPipe: public QObject
{
Q_OBJECT;
public:
	QNamedPipe(QString identifier);
	~QNamedPipe();
	
	QString getInputFilePath() const;
	QString getOutputFilePath() const;
	QString getPipeName() const;

private:
	QString name, pathIn,pathOut;
	static int namedPipesNum;
	#ifdef WIN32
	QNamedPipeThread * pipeThread;
	#endif
	void init(QString uniqueIdentifier);
};

#endif

