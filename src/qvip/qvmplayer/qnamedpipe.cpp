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

#ifdef unix
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#elif WIN32
#include <QThread>
#include <windows.h>
#include <tchar.h>
#endif

// header
#include <QNamedPipe>
#include <QDebug>
#include <unistd.h>	// for getpid

///////////////////////////////////////////////////////////////////////////////////////
// QNamedPipeThread
#ifdef WIN32
TCHAR * char_to_tchar(const char* pSrc)
	{
	if(!pSrc) return NULL;
	unsigned int n = strlen (pSrc);
	TCHAR * wsOut = new TCHAR[n+1];
	for (unsigned int i=0; i<1+n; i++)
		wsOut[i] = pSrc[i];

	return wsOut;
	};

#define BUFSIZE 256*1024

QNamedPipeThread::QNamedPipeThread(HANDLE pipe1, HANDLE pipe2, char *name)
	{
	qDebug() << "QNamedPipeThread::QNamedPipeThread(" << pipe1 << "," << pipe2 << "," << name << ")";
	this->hPipe1 = pipe1;
	this->hPipe2 = pipe2;
	this->finished = false;
	this->pipeName = strdup(name);
	qDebug() << "QNamedPipeThread::QNamedPipeThread() <- return";
	}
	
QNamedPipeThread::~QNamedPipeThread()
	{
	qDebug() << "QNamedPipeThread::~QNamedPipeThread()";
	delete this->pipeName;
	qDebug() << "QNamedPipeThread::~QNamedPipeThread() <- return";
	}
	
	
void QNamedPipeThread::run()
	{
	qDebug() << "QNamedPipeThread::run()";

	// we receive conexion from programs using the pipe
	BOOL	fConnected1 = ConnectNamedPipe(hPipe1, NULL) ?
				TRUE : (GetLastError() == ERROR_PIPE_CONNECTED); 
	qDebug() << "QNamedPipeThread::run(): input end for pipe" << pipeName << "connected";

	BOOL	fConnected2 = ConnectNamedPipe(hPipe2, NULL) ?
				TRUE : (GetLastError() == ERROR_PIPE_CONNECTED); 
	qDebug() << "QNamedPipeThread::run(): output end for pipe" << pipeName << "connected";

	if (!fConnected1 || !fConnected2)
		{
		qDebug() << "QNamedPipeThread::run(): connection for named pipe " << pipeName << "failed";
		return;
		}

	// main loop: we read data from input pipe (1) and send it to output pipe (2)
	int c = 0;
	
	while (not finished) 
		{
		qDebug() << "QNamedPipeThread::run(): dispatching loop for named pipe " << pipeName << "started";

		TCHAR buffer[BUFSIZE]; 
		DWORD cbBytesRead, cbWritten;
		//while (cbBytesRead < 0) 
		// Read client requests from the pipe. 
		BOOL fSuccess = ReadFile( 
			hPipe1,		// handle to pipe 
			buffer,		// buffer to receive data 
			BUFSIZE*sizeof(TCHAR), // size of buffer 
			&cbBytesRead,	// number of bytes read 
			NULL);		// not overlapped I/O 
		qDebug() << "QNamedPipeThread::run(): read " << cbBytesRead << "bytes from input of pipe" << pipeName;
		
		FlushFileBuffers(hPipe1);
 		qDebug() << "QNamedPipeThread::run(): done flushing for input end of named pipe"<< pipeName;
		c += cbBytesRead;

		if (! fSuccess)
			{
			qDebug() << "QNamedPipeThread::run(): ReadFile false, exiting main loop for pipe"<< pipeName;
			finished = true;
			break;
			}
		else if (cbBytesRead == 0)
			{
			qDebug() << "QNamedPipeThread::run(): 0 bytes read, exiting main loop for pipe"<< pipeName;
			finished = true;
			break;
			}
		else
			{
			fSuccess = WriteFile( 
				hPipe2,		// handle to pipe 
				buffer,		// buffer to write from 
				cbBytesRead,	// number of bytes to write
				&cbWritten,	// number of bytes written
				NULL);		// not overlapped I/O
			qDebug() << "QNamedPipeThread::run(): sent" << cbWritten << "bytes to output end of named pipe" << pipeName;

			FlushFileBuffers(hPipe2);
			qDebug() << "QNamedPipeThread::run(): done flushing for output end of named pipe"<< pipeName;

			c -= cbWritten;

			if (c > BUFSIZE)
				qDebug() << "QNamedPipeThread::run(): Buffer OVERFLOW" << c << "of" << BUFSIZE << "bytes max\n";

			if (! fSuccess || cbBytesRead != cbWritten) break;
			qDebug() << "QNamedPipeThread::run(): finished loop for pipe" << pipeName;
			}
		}
		
	qDebug() << "QNamedPipeThread::run(): closing pipe" << pipeName;

	// flushing and closing pipes
	FlushFileBuffers(hPipe1); 
	FlushFileBuffers(hPipe2);
	DisconnectNamedPipe(hPipe1);
	DisconnectNamedPipe(hPipe2);
	CloseHandle(hPipe1);
	CloseHandle(hPipe2);
	qDebug() << "QNamedPipeThread::run() <- return";
	}
#endif

////////////////////////////////////////////////////////////
// constructor and destructors
QNamedPipe::QNamedPipe(QString identifier): QObject()
	{
	qDebug() << "QNamedPipeThread::QNamedPipe(" << identifier <<")";

	name =	identifier + QString(".")
		+ QString().setNum(QNamedPipe::namedPipesNum++)
		+ QString(".pid") + QString().setNum(getpid());

	#ifdef unix
	pathIn = 	QString("/tmp/") + name + QString(".qnamedpipe");
	pathOut = 	QString("/tmp/") + name + QString(".qnamedpipe");
	qDebug() << "QNamedPipeThread::QNamedPipe(): (UNIX) going to create pipe" << name
		<< "\n\t"<< pathIn << "\n\t" << pathOut;	

	mkfifo(pathIn.toAscii().data(),0644); pathOut = pathIn;	

	#elif WIN32
	pathIn = QString("\\\\.\\pipe\\") + name + QString(".in.qnamedpipe");
	pathOut = QString("\\\\.\\pipe\\") + name + QString(".out.qnamedpipe");
	qDebug() << "QNamedPipeThread::QNamedPipe(): (WIN32) going to create pipe" << name
		<< "\n\t"<< pathIn << "\n\t" << pathOut;

	// closing pipes
	HANDLE hPipe1 = CreateNamedPipe(
		TEXT(char_to_tchar(pathIn.toAscii().data())),	// pipe name
		PIPE_ACCESS_DUPLEX,				// read/write access 
		PIPE_TYPE_BYTE |				// message type pipe
		PIPE_WAIT,					// blocking mode
		1,						// max. instances
		BUFSIZE,					// output buffer size
		BUFSIZE,					// input buffer size 
		NMPWAIT_USE_DEFAULT_WAIT,			// client time-out
		NULL);

 	HANDLE hPipe2 = CreateNamedPipe(
		TEXT(char_to_tchar(pathOut.toAscii().data())),	// pipe name
		PIPE_ACCESS_DUPLEX,				// read/write access
		PIPE_TYPE_BYTE |				// message type pipe
		PIPE_WAIT,					// blocking mode
		1,						// max. instances 
		BUFSIZE,					// output buffer size
		BUFSIZE,					// input buffer size
		NMPWAIT_USE_DEFAULT_WAIT,			// client time-out
		NULL);

	// check we closed the pipes
	if ((hPipe1 == INVALID_HANDLE_VALUE) || (hPipe2 == INVALID_HANDLE_VALUE))
		{
		qDebug() << "QNamedPipeThread::QNamedPipe(): failed create of pipe" << name;
		return;
		}

	pipeThread = new QNamedPipeThread(hPipe1,hPipe2,name.toAscii().data());
	pipeThread->start(QThread::TimeCriticalPriority);
	#endif
	qDebug() << "QNamedPipeThread::QNamedPipe(): named pipe" << name
		<< "created:\n\t"<< pathIn << "\n\t" << pathOut;	

	qDebug() << "QNamedPipeThread::QNamedPipe() <- return";
	}

QNamedPipe::~QNamedPipe()
	{
	qDebug() << "QNamedPipeThread::~QNamedPipe()";
	qDebug() << "QNamedPipeThread::~QNamedPipe(): deleting pipe" << name;
	
	#ifdef unix
	remove(pathIn.toAscii().data());
	#elif WIN32
	pipeThread->finished = true;
	pipeThread->wait();
	qDebug() << "QNamedPipeThread::~QNamedPipe(): pipeThread finished";
	delete pipeThread;
	qDebug() << "QNamedPipeThread::~QNamedPipe(): pipeThread deleted";
	#endif
	
	qDebug() << "QNamedPipeThread::~QNamedPipe() <- return";
	}

// accessing
QString QNamedPipe::getInputFilePath() const { return pathIn; }
QString QNamedPipe::getOutputFilePath() const { return pathOut; }
QString QNamedPipe::getPipeName() const { return name; }
int QNamedPipe::namedPipesNum = 0;
