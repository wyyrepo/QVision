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

#include "qvblockinterfacesmall.h"

#ifndef DOXYGEN_IGNORE_THIS
QVProcessingBlockInterfaceSmall::QVProcessingBlockInterfaceSmall(QVProcessingBlock *block, QWidget *parent): QWidget(parent), cpuPlot(0)
    {
    qDebug() << "QVProcessingBlockInterfaceSmall::QVProcessingBlockInterfaceSmall("<< block->getName() << ")";
    form.setupUi(this);

    setWindowTitle(block->getName());
    //form.groupBox->setTitle(block->getName());
    this->block = block;
    isGroupMaster = block->isSequentialGroupMaster();

    if (block->isStatsEnabled()) {
        this->cpuPlot = new QVCPUPlot("CPU performance plot of: " + block->getName(), true, false);
        block->linkProperty("cpu stats", this->cpuPlot);
        this->cpuPlot->init();
        connect(form.stat_button,SIGNAL(toggled(bool)),cpuPlot,SLOT(setVisible(bool)));
        connect(cpuPlot,SIGNAL(closed()),form.stat_button,SLOT(toggle()));
    }
    else
        form.stat_button->setEnabled(false);

/*	this->cpuPlotSmall = new QVCPUPlot("Small cpu plot of: " + block->getName(), false);
    this->cpuPlotSmall->linkProperty(*block);
    this->cpuPlotSmall->setFixedHeight(75);
    form.vboxLayout->addWidget(this->cpuPlotSmall);*/

    // Connect block slots with form's buttons
    connect(form.pause_button,SIGNAL(pressed()),block,SLOT(pause()),Qt::QueuedConnection);
    connect(form.play_button,SIGNAL(pressed()),block,SLOT(unPause()),Qt::QueuedConnection);
    connect(form.next_button,SIGNAL(pressed()),block,SLOT(step()),Qt::QueuedConnection);
    connect(form.stop_button, SIGNAL(pressed()),block,SLOT(stop()),Qt::QueuedConnection);
    connect(form.finish_button, SIGNAL(pressed()),this,SLOT(finishBlock()),Qt::QueuedConnection);

    // Connecting slot with block update signal
    connect(block,SIGNAL(endIteration(uint, int)),this,SLOT(newIterationSlot()),Qt::QueuedConnection);
    connect(block,SIGNAL(statusUpdate(QVProcessingBlock::TBlockStatus)),
        this,SLOT(statusUpdate(QVProcessingBlock::TBlockStatus)),Qt::QueuedConnection);

    statusUpdate(block->getStatus());

    show();
    qDebug() << "QVProcessingBlockInterfaceSmall::QVProcessingBlockInterfaceSmall(" << block->getName() << ") <- return";
    }

QVProcessingBlockInterfaceSmall::~QVProcessingBlockInterfaceSmall()
    {
        if (this->cpuPlot) delete this->cpuPlot;
    }

void QVProcessingBlockInterfaceSmall::finishBlock()
    {
        qvApp->quitBlock(block);
    }

void QVProcessingBlockInterfaceSmall::newIterationSlot()
    { form.iterationsLabel->setText(QString("Iteration: ")+QString().setNum(block->getIteration())); }

void QVProcessingBlockInterfaceSmall::statusUpdate(QVProcessingBlock::TBlockStatus status)
    {
    isGroupMaster = block->isSequentialGroupMaster();
    if (!isGroupMaster) {
        form.finish_button->setEnabled(FALSE);
        form.stop_button->setEnabled(FALSE);
        form.pause_button->setEnabled(FALSE);
        form.play_button->setEnabled(FALSE);
        form.next_button->setEnabled(FALSE);
        }
    else {
        switch(status)
            {
            case QVProcessingBlock::Finished:
                form.finish_button->setEnabled(FALSE);
                form.stop_button->setEnabled(FALSE);
                form.pause_button->setEnabled(FALSE);
                form.play_button->setEnabled(FALSE);
                form.next_button->setEnabled(FALSE);
                break;

            case QVProcessingBlock::Stopped:
                form.finish_button->setEnabled(TRUE);
                form.stop_button->setEnabled(FALSE);
                form.pause_button->setEnabled(FALSE);
                form.play_button->setEnabled(FALSE);
                form.next_button->setEnabled(FALSE);
                break;

            case QVProcessingBlock::Running:
                form.finish_button->setEnabled(TRUE);
                form.stop_button->setEnabled(TRUE);
                form.pause_button->setEnabled(TRUE);
                form.play_button->setEnabled(FALSE);
                form.next_button->setEnabled(FALSE);
                break;

            case QVProcessingBlock::RunningOneStep:
            case QVProcessingBlock::Paused:
                form.finish_button->setEnabled(TRUE);
                form.stop_button->setEnabled(TRUE);
                form.pause_button->setEnabled(FALSE);
                form.play_button->setEnabled(TRUE);
                form.next_button->setEnabled(TRUE);
                break;

            default:
                break;
            }
        }
    }
#endif

