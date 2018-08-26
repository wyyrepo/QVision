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

#ifndef QVCAMERAWORKERWIDGET_H
#define QVCAMERAWORKERWIDGET_H

#include <QWidget>

#include <QVPropertyContainer>
#include <QVVideoReaderBlock>
#include <ui/ui_qvvideoreaderblockwidget.h>

#ifndef DOXYGEN_IGNORE_THIS
class QVVideoReaderBlockWidget: public QWidget, public QVPropertyContainer
    {
    Q_OBJECT
    public:
        Ui::QVVideoReaderBlockWidget form;
        QVVideoReaderBlockWidget(QVVideoReaderBlock *camera, QWidget *parent = 0);

    private:
        QVVideoReaderBlock * camera;
        void subscribeToOutputProperty(QVPropertyContainer *qvp, QString name, LinkType linktype = AsynchronousLink);
        void subscribeToInputProperty(QVPropertyContainer *qvp, QString name, LinkType linktype = AsynchronousLink);
        bool slider_active;

    private slots:
        void somePropertyChanged();
        void updateOpened();
        void updateClosed();
        void stopPressed();
        void pausePressed();
        void playPressed();
        void nextPressed();
        void newFrameGrabbed();
        void seekPressed();
        void seekReleased();
        void fileOpenButtonPressed();

    signals:
        void seek_requested(int pos);
        void file_selected();

};
#endif

#endif
