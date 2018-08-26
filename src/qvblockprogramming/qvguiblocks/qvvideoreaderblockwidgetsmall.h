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

#ifndef QVCAMERAWORKERWIDGETSMALL_H
#define QVCAMERAWORKERWIDGETSMALL_H

#include <QVVideoReaderBlock>

#include <ui/ui_qvvideoreaderblockwidgetsmall.h>

#ifndef DOXYGEN_IGNORE_THIS
class QVVideoReaderBlockWidgetSmall: public QWidget
{
    Q_OBJECT
public:
    Ui::QVVideoReaderBlockWidgetSmall form;
    QVVideoReaderBlockWidgetSmall(QVVideoReaderBlock *camera, QWidget *parent = 0);
    ~QVVideoReaderBlockWidgetSmall();

private:
    QVVideoReaderBlock *camera;
    //FIXME quedará... QVVideoReaderBlockWidget *cameraWidget;
    //bool sliderActive;

signals:
    //void speedPressed(double speed);
    //void seekPressed(QVCamera::TSeekType seek_type,double value);

public slots:
    //void updateCameraVisibleInfoSlot();
    //void updateCameraStateSlot(QVCamera::TCameraStatus);

private slots:
    //void seekPressedSlot();
    //void seekReleasedSlot();
    //void seekMovedSlot();
    //void closePressedSlot();
};
#endif

#endif

