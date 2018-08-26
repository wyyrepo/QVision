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

#include <QDebug>
#include <QMetaType>
#include <QSet>
#include <QGLWidget>

#include <QVApplication>
#include <QVGUI>
#include <QVImageCanvas>
#include <QVProcessingBlock>
#include <QMutexLocker>

#ifdef QVQWT
#include "qvguiblocks/qvplot.h"
#endif

QVApplication::QVApplication (int &argc,char **argv, QString infoString,bool GUIenabled) : QApplication(argc,argv,GUIenabled), info(infoString), unusedArguments(), qvps(), visionInterface(NULL), isRunningFlag(FALSE), blockCount(0), terminateOnLastBlock(TRUE), forHelpFlag(FALSE)
	{

	if (GUIenabled and not QGLFormat::hasOpenGL() )
		qFatal("This system has no OpenGL support, and QVision GUI needs it. Exiting.");

	qRegisterMetaType< QVariant >("QVariant");
	//qRegisterMetaType< QVCamera::TCameraStatus >("QVCamera::TCameraStatus");
	qRegisterMetaType< QVProcessingBlock::TBlockStatus >("QVProcessingBlock::TBlockStatus");
	qRegisterMetaType< QVImage<uChar,1> >("QVImage<uChar,1>");
	qRegisterMetaType< QVImage<sShort,1> >("QVImage<sShort,1>");
	qRegisterMetaType< QVImage<sFloat,1> >("QVImage<sFloat,1>");
	qRegisterMetaType< QVImage<uChar,3> >("QVImage<uChar,3>");
	qRegisterMetaType< QVImage<sShort,3> >("QVImage<sShort,3>");
	qRegisterMetaType< QVImage<sFloat,3> >("QVImage<sFloat,3>");
	qRegisterMetaType< QVPropertyContainerChange >("QVPropertyContainerChange");

	unusedArguments = arguments();
	setApplicationName(unusedArguments[0].split("/").last());
	unusedArguments.removeAt(0); // Application name removed.

	if(unusedArguments.contains("--help")) forHelpFlag = TRUE;

	}

int QVApplication::processArguments()
        {
        // If --help parameter was given, show help and exit:
        if(unusedArguments.contains("--help"))
                {
                printHelp();
                return 0;
                }

        // An initialization error of any QVPropertyContainer aborts execution:
        foreach(QVPropertyContainer* qvp, qvps)
                {
                QString lastError;
                if((lastError = qvp->getLastError()) != QString())
                        {
                        std::cerr << "Error initializing QVApplication: "
                                  << qPrintable(lastError) << std::endl;
                        return -1;
                        }
                }

        // If there are unused arguments, show error and exit
        if(not unusedArguments.isEmpty())
                {
                foreach(QString argument, unusedArguments)
                        std::cerr << "Error initializing QVApplication: "
                                  << "unknown command line parameter: "
                                  << qPrintable(argument) << std::endl;
                return -1;
                }
        return 1;
        }


int QVApplication::exec()
	{
	qDebug() << "QVApplication::exec()";

        // First, process arguments and, if error in command line, or only asked for help, return:
        int ret_value = processArguments();
        if(ret_value != 1)
                return ret_value;

	// Now we init the GUI, in order to register all cameras and blocks, and create its widgets
	if (visionInterface)
		{
		visionInterface->init();
		visionInterface->show();
		}
		qDebug() << "QVApplication::exec(): GUI initied";
	
	// Now we init all registered items (cameras, plots,canvas, blocks, ...)
	if (!startItems()) return -1;

	qDebug() << "Entering in QApplication::exec()";
	isRunningFlag = TRUE;
	int returnvalue = QApplication::exec();
	qDebug() << "Back from QApplication::exec()";

	qDebug() << "QVApplication::exec() <- return";
	return returnvalue;
	}

bool QVApplication::startItems()
	{
	// TODO: mover la inicialización de los QVImageCanvas al principio de esta función. Problema con el alumno de PFC.

	// Now we will open all cameras:
	/*foreach(QVPropertyContainer* qvp, qvps)
		{
		QVCamera* camera;
		if((camera = dynamic_cast<QVCamera*>(qvp)) != NULL)
			//{
			//std::cout << "QVApplication::startItems(" << qPrintable(qvp->getName()) << "), camera" << std::endl;
			if(camera->isClosed())
				{
				if(not camera->open())
					{
					std::cerr << "Error initializing QVApplication: "
							<< "could not open camera: "
							<< qPrintable(camera->getName()) << std::endl;
					return false;
					}
				}
			//else
			//	std::cout << "QVApplication::startItems(" << qPrintable(qvp->getName()) << "): camera not closed" << std::endl;
			//}
		}
	qDebug() << "QVApplication::initItems(): cameras opened";*/

	// Now we will init all Plots, that are PropertyContainer:
	#ifdef QVQWT
	foreach(QVPropertyContainer* qvp, qvps)
		{
		QVPlot* plot;
		if((plot = dynamic_cast<QVPlot*>(qvp)) != NULL)
			{
			if (!plot->isInitied()) plot->init();
			if (plot->isAutoShow()) plot->show();
			}
		}
	qDebug() << "QVApplication::initItems(): plots initied";
	#endif

	// Now we will show all canvas
	foreach(QVPropertyContainer* qvp, qvps)
		{
		QVImageCanvas* canvas;
		if((canvas = dynamic_cast<QVImageCanvas*>(qvp)) != NULL)
			canvas->show();
		}
	qDebug() << "QVApplication::initItems(): canvas shown";

	// Now we will start all blocks:
	foreach(QVPropertyContainer* qvp, qvps)
		{
		QVProcessingBlock* block;
		if((block = dynamic_cast<QVProcessingBlock*>(qvp)) != NULL)
			{
				QVProcessingBlock* masterBlock;
				// The block must be moved to his master thread (if its a block), that will be usualy himself
				if((masterBlock = dynamic_cast<QVProcessingBlock*>(qvp->getMaster())) != NULL)
					block->moveToThread(masterBlock);
				connect(block,SIGNAL(finished()),this,SLOT(blockFinished()));
				// only start the masters threads, and only count this blocks to the endOnLastIteration condition
				if (block->isSequentialGroupMaster()) {
					blockCount++;
					block->start();
				}
			}
		}
	isRunningFlag = TRUE;
	qDebug() << "QVApplication::initItems(): blocks started";
	return true;
	}

void QVApplication::quit()
	{
	quitItems();
	deregisterGUI();
	this->exit(0);
	}

void QVApplication::quitItems()
	{
	qDebug() << "QVApplication::quitItems()";

	// We order all blocks to finish...
	foreach(QVPropertyContainer* qvp, qvps)
		{
		QVProcessingBlock* block;
		if((block = dynamic_cast<QVProcessingBlock*>(qvp)) != NULL)
			block->finish();
		}
	// ... and then wait for all of them (Warning, it won't work if we try to
	// finish and wait in the same loop).
	foreach(QVPropertyContainer* qvp, qvps)
		{
		QVProcessingBlock* block;
		if((block = dynamic_cast<QVProcessingBlock*>(qvp)) != NULL)
			{
			// Needed to treat possible pending Qt::BlockingQueuedConnection
			// signals from qvpropertycontainer.h:
			// if it is not a master the threat was not started, and wait do nothing
			while(not block->wait(10/*ms*/)) processEvents();
			deregisterQVPropertyContainer(block);
			}
		}
	qDebug() << "QVApplication::quitItems(): blocks finished";

	// Now we will hide all canvas
	foreach(QVPropertyContainer* qvp, qvps)
		{
		QVImageCanvas* canvas;
		if((canvas = dynamic_cast<QVImageCanvas*>(qvp)) != NULL)
			{
			canvas->hide();
			deregisterQVPropertyContainer(canvas);
			}
		}
	qDebug() << "QVApplication::quitItems(): canvas hiden";

	#ifdef QVQWT
	// Now we will stop all Plots, that are PropertyContainer:
	foreach(QVPropertyContainer* qvp, qvps)
		{
		QVPlot* plot;
		if((plot = dynamic_cast<QVPlot*>(qvp)) != NULL)
			{
			plot->stop();
			plot->hide();
			deregisterQVPropertyContainer(plot);
			}
		}
	qDebug() << "QVApplication::quitItems(): plots initied";
	#endif

	// Now we will close all cameras:
	/*foreach(QVPropertyContainer* qvp, qvps)
		{
		QVCamera* camera;
		if((camera = dynamic_cast<QVCamera*>(qvp)) != NULL)
			{
			if(!camera->isClosed()) camera->close();
			deregisterQVPropertyContainer(camera);
			}
		}
	qDebug() << "QVApplication::quitItems(): cameras closed";*/

	isRunningFlag = FALSE; // para que se pueda parar y realizar nuevos enlaces
	}

void QVApplication::quitBlock(QVProcessingBlock *block)
	{
		if (qvps.contains(block)) {
			block->finish();

			while(not block->wait(10/*ms*/)) processEvents();
			deregisterQVPropertyContainer(block);

// 			delete block; // no se puede si no se crean con new
		}
	}

QStringList QVApplication::getUnusedArguments()
	{ return unusedArguments; }

void QVApplication::setArgumentAsUsed(QString argument)
	{
	qDebug() << "QVApplication::setArgumentAsUsed(QString,bool)";
	int index = unusedArguments.indexOf(argument);
	if(index != -1)
		unusedArguments.removeAt(index);
	qDebug() << "QVApplication::setArgumentAsUsed(QString,bool) <- return";
	}

#ifndef DOXYGEN_IGNORE_THIS
void QVApplication::registerQVPropertyContainer(QVPropertyContainer *qvp)
	{
	qDebug() << "QVApplication::registerQVPropertyContainer(" << qvp->getName() << ")";
	qvps.insert(qvp);
	qDebug() << "QVApplication::registerQVPropertyContainer(" << qvp->getName() << ") -> return";
	}

void QVApplication::deregisterQVPropertyContainer(QVPropertyContainer *qvp)
	{
	qDebug() << "QVApplication::registerQVPropertyContainer(" << qvp->getName() << ")";
	qvps.remove(qvp);
	qDebug() << "QVApplication::registerQVPropertyContainer(" << qvp->getName() << ") -> return";
	}

void QVApplication::registerGUI(QVGUI *visionInterface)
	{
	this->visionInterface = visionInterface;
	}

void QVApplication::deregisterGUI()
	{
	this->visionInterface = 0;
	}
#endif

void QVApplication::printHelp()
	{
	std::cout << qPrintable(getHelp());
	}

void QVApplication::blockFinished()
{
	blockCount--;
	if(blockCount == 0)
		if(terminateOnLastBlock)
			quit();
}

QString QVApplication::getHelp()
{
	QString help_string;

	help_string = "Usage: " + applicationName() + " [OPTIONS]\n\n";

	if (info != QString())
		help_string = help_string + qPrintable(info) + "\n\n";

	QSetIterator<QVPropertyContainer *> iq(qvps);
	while (iq.hasNext())
		{
		QString infoHolder = iq.next()->infoInputProperties();
		if(infoHolder != QString() )
			help_string += infoHolder + "\n";
		}

	return help_string;

}
