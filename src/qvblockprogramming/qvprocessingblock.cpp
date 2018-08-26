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

#include <iostream>

#include <QDebug>
#include <QMutex>
#include <QWaitCondition>
#include <QApplication>

#include <QVProcessingBlock>
#include <QVVideoReaderBlock>

QVProcessingBlock::QVProcessingBlock(const QString name):QVPropertyContainer(name), numIterations(0), status(Running), triggerList(), minms(0)
    {
    qDebug() << "QVProcessingBlock::QVProcessingBlock(" << name << ")";
    Q_ASSERT_X(qvApp != NULL, "QVProcessingBlock::QVProcessingBlock()", "QVApplication object does not exist.");
    if (qvApp == NULL)
        {
        QString str = "QVProcessingBlock::QVProcessingBlock(): the QVProcessingBlock cannot be created before the QVApplication instance. Aborting.";
        std::cerr << qPrintable(str) << std::endl;
        exit(1);
        }

    addProperty<int>("max block iterations", inputFlag | guiInvisible | internalProp, -1, "Maximal number of iterations to execute block");
    maxIterations = getPropertyValue<int>("max block iterations");

    addProperty<bool>("stats enabled", inputFlag | guiInvisible | internalProp, TRUE, "Block CPU stats are enabled/disabled");
    statsEnabled = getPropertyValue<bool>("stats enabled");

    if (statsEnabled)
        cpuStatControler = new QVStatControler();

    if (statsEnabled)
        addProperty<QVStat>("cpu stats", outputFlag, cpuStatControler->value(), "CPU stats");
    else
        addProperty<QVStat>("cpu stats", outputFlag, QVStat(), "CPU stats");

    informer.setParent(this); // set the informer's parent = this, in order to it will be moved to the block's thread when the qvApp do block->moveToThread(block)

    addProperty<int>("stats printing frequency", inputFlag | guiInvisible | internalProp, 0, "Frequency to print CPU statistics (in iterations)");
    const int printStatsFrequency = getPropertyValue<int>("stats printing frequency");

    if (printStatsFrequency > 0)
        setPrintStatsFrequency(printStatsFrequency);

    qDebug() << "QVProcessingBlock::QVProcessingBlock(" << name << ") <- return";
    };

QVProcessingBlock::QVProcessingBlock(const QVProcessingBlock &other):QThread(), QVPropertyContainer(other), statsEnabled(other.statsEnabled), numIterations(other.numIterations),
    maxIterations(other.maxIterations), status(other.status), triggerList(other.triggerList), iterationTime(other.iterationTime), curms(other.curms),
    minms(other.minms)
    {
    if (statsEnabled) cpuStatControler = new QVStatControler();
    }

QVProcessingBlock::~QVProcessingBlock()
    {
    if (statsEnabled)
        delete cpuStatControler;

    informer.setParent(0); // in order not to delete the informer object, when all its childrens will be deleted
    }

/*
void QVProcessingBlock::unlink()
    {
    if(status == Finished)
        QVPropertyContainer::unlink();
    else
        std::cerr << "WARNING: A block only can be unlinked if the block's status is Finished." << std::endl;
    }
*/

void QVProcessingBlock::run()
    {
    qDebug() << "QVProcessingBlock::run()";

    while(status != Finished)
        {
        qDebug() << "Processing events in block " << qPrintable(getName());

        // First, we check if there are any pending signals, and if so, we
        // execute their associated slots:
        qApp->processEvents();

        qDebug() << "QVProcessingBlock::iterate(): iteration" << numIterations;

        // Avoids "apparent hanging" (greedy ocupation of CPU by extremely fast
        // blocks, such as paused ones). It is just 1 millisecond, so
        // it should not be appreciable in any practical situation.
        usleep(1000);

        switch (status)
            {
            case RunningOneStep:
                qDebug() << "QVProcessingBlock::iterate(): RunningOneStep";
                status = Paused;

            case Running:
                iterationTime.start();
                foreach(QList<QVPropertyContainer *> level, slavesByLevel) // Iterate all its slaves (included itself)
                    foreach(QVPropertyContainer * slave, level)
                        if(dynamic_cast<QVProcessingBlock *>(slave) != NULL) ((QVProcessingBlock *)slave)->blockIterate();

                curms = iterationTime.elapsed();
                if(minms > curms)
                    usleep(1000*(minms-curms));
                /*if(numIterations!=1) // First iteration time is too noisy:
                    acumms = (acumms*(numIterations-2) + curms) / (numIterations-1);
                std::cout << "-----> curms=" << curms << " acumms=" << acumms << "\n";*/
                break;

            case Stopped:
                // A stopped block should never block anybody, but keeps linked to
                // other blocks (otherwise, it would simply be deleted). So, it must
                // read its inputs an write its outputs always, even being stopped.
                readInputProperties();
                writeOutputProperties();
                usleep(100); // This avoids spurious CPU consuming when stopped.
                break;


            case Paused:
                qDebug() << "QVProcessingBlock::iterate(): Paused";
                if(dynamic_cast<QVVideoReaderBlock*>(this) != NULL)
                    {
                    // A special pause case for camera blocks: we do not want paused cameras
                    // to block linked blocks:
                    readInputProperties();
                    writeOutputProperties();
                    }
                usleep(100); // This avoids spurious CPU consuming when paused.
                break;

            case Finished:
                qDebug() << "QVProcessingBlock::iterate(): Finished";
                break;
            }

        if (maxIterations != -1 && numIterations >= maxIterations)
            finish();

        qDebug() << "QVProcessingBlock::iterate() <- return";
        }


    foreach(QList<QVPropertyContainer *> level, slavesByLevel) // Return to the main thread all its slaves (included itselve)
        foreach(QVPropertyContainer * slave, level)
            if(dynamic_cast<QVProcessingBlock *>(slave) != NULL) ((QVProcessingBlock *)slave)->moveToThread(qvApp->thread());

    foreach(QList<QVPropertyContainer *> level, slavesByLevel) // Unlink all its slaves (included itselve)
        foreach(QVPropertyContainer * slave, level)
            if(dynamic_cast<QVProcessingBlock *>(slave) != NULL) {
                QMutexLocker locker(&qvApp->mutex); // in safe mode with other thread's unlinks and with the canvas viewer()
                ((QVProcessingBlock *)slave)->unlink();
            }

    qApp->processEvents();

    qDebug() << "QVProcessingBlock::run() <- return";
    }

void QVProcessingBlock::blockIterate()
    {
    if (statsEnabled) cpuStatControler->step();
    emit startIteration();
    readInputProperties();
    timeFlag("System");
    iterate();
    if (statsEnabled) setPropertyValue<QVStat>("cpu stats", cpuStatControler->value());
    writeOutputProperties();
    numIterations++;
    emit endIteration(getId(), getIteration());
    }

