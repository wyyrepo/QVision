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

#include <QDialog>
#include <QTextEdit>
#include <QFont>

#include <QVDefaultGUI>
#include <QVVideoReaderBlock>
#include <QVImageCanvas>

#ifdef GSL_AVAILABLE
#include <QV3DCanvas>
#endif

#include "qvplot.h"
#include "qvparamsinspectorwidget.h"
#include "qvblockinterfacesmall.h"
#include "qvvideoreaderblockwidget.h"

QVDefaultGUI::QVDefaultGUI(QWidget *parent): QWidget(parent)
    {
    if (qvApp == NULL)
        {
        QString str =	"QVDefaultGUI::QVDefaultGUI(): the QVDefaultGUI cannot be created before the QVApplication instance. Aborting now.";
        std::cerr << qPrintable(str) << std::endl;
        exit(1);
        }

    // If its a --help call, do nothing:
    if (qvApp->forHelp()) return;

    // On closing, quit application:
    connect(this,SIGNAL(closed()),qvApp,SLOT(quit()));

    // Window title
    setWindowTitle("QVision default GUI for " + qApp->applicationName());

    // Lay out menu bar, and cameras and block groupbox vertically:
    vboxlayout = new QVBoxLayout(this);
    menubar = new QMenuBar(this);
    windowmenu = new QMenu("&Window",menubar);
    QAction *quit_action = menubar->addAction("&Quit");
    connect(quit_action,SIGNAL(triggered()),qvApp,SLOT(quit()));
    menubar->addMenu(windowmenu);
    QAction *help_action = menubar->addAction("&Help");
    connect(help_action,SIGNAL(triggered()),this,SLOT(showHelp()));

    // Register GUI in QVApplication:
    qvApp->registerGUI(this);
    }

void QVDefaultGUI::showHelp()
    {
    QDialog dialog;
    QString help_string = QVApplication::instance()->getHelp().trimmed();
    dialog.setWindowTitle("QVision help for " + qApp->applicationName());
    QVBoxLayout vboxlayout(&dialog);
    QTextEdit textedit;
    QFont font("Courier");
    textedit.setReadOnly(TRUE);
    textedit.setFont(font);
    textedit.setPlainText(help_string);
    QFontMetrics fontmetrics = textedit.font();
    int w = qMin(fontmetrics.size(0,help_string).width() + 30,800);
    int h = qMin(fontmetrics.size(0,help_string).height() + 30,500);
    textedit.setMinimumSize(QSize(w,h));
    vboxlayout.addWidget(&textedit);
    QPushButton button("OK");
    QHBoxLayout hboxlayout;
    hboxlayout.addStretch();
    hboxlayout.addWidget(&button);
    hboxlayout.addStretch();
    vboxlayout.addLayout(&hboxlayout);
    connect(&button,SIGNAL(pressed()),&dialog,SLOT(close()));
    dialog.exec();
    }

void QVDefaultGUI::init()
    {
    QVBoxLayout *groupboxcameraslayout,*groupboxblockslayout;
    QMenu *menu_imagecanvas = NULL, *menu_glcanvas = NULL, *menu_qvplot = NULL;
    bool some_block = FALSE, some_camera = FALSE;

    // We run through every qvApp property container and create the corresponding widgets and/or menus:
    foreach(QVPropertyContainer* qvp, qvApp->getQVPropertyContainers())
        {
        // QVProcessingBlocks (which are not QVVideoReaderBlocks):
        QVProcessingBlock* block;
        if(((block = dynamic_cast<QVProcessingBlock*>(qvp)) != NULL) and (dynamic_cast<QVVideoReaderBlock*>(qvp) == NULL))
            {
            if(not some_block)
                {
                some_block = TRUE;
                groupboxblocks = new QGroupBox("Blocks and windows",this);
                toolboxblocks = new QToolBox(groupboxblocks);
                }
            QVProcessingBlockInterfaceSmall *blockWidget = new QVProcessingBlockInterfaceSmall(block,this);
            QVParamsInspectorWidget *qvparamsinspectorwidget = new QVParamsInspectorWidget(block,this);
            QWidget *widget = new QWidget(this);
            QVBoxLayout *vboxlayout2 = new QVBoxLayout(widget);
            vboxlayout2->setSpacing(0);
            vboxlayout2->setMargin(0);
            vboxlayout2->addWidget(blockWidget);
            vboxlayout2->addWidget(qvparamsinspectorwidget);
            toolboxblocks->addItem(widget,block->getName());
            //qvparamsinspectorwidget->updateGeometry();
            continue;
            }
        // QVVideoReaderBlocks:
        QVVideoReaderBlock* camera;
        if((camera = dynamic_cast<QVVideoReaderBlock*>(qvp)) != NULL)
            {
            if(not some_camera)
                {
                some_camera = TRUE;
                groupboxcameras = new QGroupBox("Cameras",this);
                groupboxcameras->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
                toolboxcameras = new QToolBox(groupboxcameras);
                }
            QVVideoReaderBlockWidget *cameraWidget = new QVVideoReaderBlockWidget(camera,this);
            toolboxcameras->addItem(cameraWidget, camera->getName());
            continue;
            }
        // QVImageCanvas:
        QVImageCanvas *imageCanvas;
        if((imageCanvas = dynamic_cast<QVImageCanvas*>(qvp)) != NULL)
            {
            if(menu_imagecanvas == NULL)
                menu_imagecanvas = windowmenu->addMenu("&Image windows");
            QAction *action = menu_imagecanvas->addAction(imageCanvas->getName());
            action->setCheckable(TRUE);
            action->setChecked(imageCanvas->isVisible());
            connect(action,SIGNAL(toggled(bool)),imageCanvas,SLOT(setVisible(bool)));
            connect(imageCanvas,SIGNAL(closed()),action,SLOT(toggle()));

            if(not some_block)
                {
                some_block = TRUE;
                groupboxblocks = new QGroupBox("Blocks and windows",this);
                toolboxblocks = new QToolBox(groupboxblocks);
                }
            QVParamsInspectorWidget *qvparamsinspectorwidget = new QVParamsInspectorWidget(imageCanvas,this);
            QWidget *widget = new QWidget(this);
            QVBoxLayout *vboxlayout2 = new QVBoxLayout(widget);
            vboxlayout2->setSpacing(0);
            vboxlayout2->setMargin(0);
            vboxlayout2->addWidget(qvparamsinspectorwidget);
            toolboxblocks->addItem(widget,imageCanvas->getName());
            //qvparamsinspectorwidget->updateGeometry();

            continue;
            }
        #ifdef GSL_AVAILABLE
        // QV3DCanvas:
        QV3DCanvas *glCanvas;
        if((glCanvas = dynamic_cast<QV3DCanvas*>(qvp)) != NULL)
            {
            if(menu_glcanvas == NULL)
                menu_glcanvas = windowmenu->addMenu("&OpenGL windows");
            QAction *action = menu_glcanvas->addAction(glCanvas->getName());
            action->setCheckable(TRUE);
            action->setChecked(glCanvas->isVisible());
            connect(action,SIGNAL(toggled(bool)),glCanvas,SLOT(setVisible(bool)));
            connect(glCanvas,SIGNAL(closed()),action,SLOT(toggle()));
            continue;
            }
        #endif
        // QVPlots:
        QVPlot *qvplot;
        if((qvplot = dynamic_cast<QVPlot*>(qvp)) != NULL)
            {
            if(menu_qvplot == NULL)
                menu_qvplot = windowmenu->addMenu("&Plot windows");
            QAction *action = menu_qvplot->addAction(qvplot->getName());
            action->setCheckable(TRUE);
            //FIXME:  It should be: action->setChecked(qvplot->isVisible());
            // but, for any reason, qvplots are not shown until later (ask Antonio)
            action->setChecked(TRUE);
            connect(action,SIGNAL(toggled(bool)),qvplot,SLOT(setVisible(bool)));
            connect(qvplot,SIGNAL(closed()),action,SLOT(toggle()));
            continue;
            }
        }

    vboxlayout->setSpacing(5);
    vboxlayout->setMargin(5);
    vboxlayout->addWidget(menubar);

    if(some_block)
        {
        groupboxblockslayout = new QVBoxLayout(groupboxblocks);
        groupboxblockslayout->addWidget(toolboxblocks);
        vboxlayout->addWidget(groupboxblocks);
        }

    if(some_camera)
        {
        groupboxcameraslayout = new QVBoxLayout(groupboxcameras);
        groupboxcameraslayout->addWidget(toolboxcameras);
        vboxlayout->addWidget(groupboxcameras);
        }

    }

void QVDefaultGUI::show()
    {
    QWidget::show();
    }

void QVDefaultGUI::closeEvent(QCloseEvent *event)
    {
    Q_UNUSED(event);
    qvApp->deregisterGUI();
    emit closed();
    }
