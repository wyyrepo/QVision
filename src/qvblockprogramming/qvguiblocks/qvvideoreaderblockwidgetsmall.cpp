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

#include "qvvideoreaderblockwidgetsmall.h"

QVVideoReaderBlockWidgetSmall::QVVideoReaderBlockWidgetSmall(QVVideoReaderBlock *camera, QWidget *parent): QWidget(parent)
    {
    form.setupUi(this);
    this->camera = camera;
    //FIXME quedará this->cameraWidget = new QVCameraWidget(camera);

    form.groupBox->setTitle(camera->getName());

/*	this->sliderActive = true;

    if (this->camera->isLiveCamera())
        form.seekSlider->setEnabled(false);

    // Connection of signals in camera control widget to private slots...
    connect(form.pause_button,SIGNAL(pressed()),camera,SLOT(pauseCam()));
    connect(form.play_button,SIGNAL(pressed()),camera,SLOT(unpauseCam()));
    connect(form.next_button,SIGNAL(pressed()),camera,SLOT(nextFrameCam()));
    connect(form.stop_button, SIGNAL(pressed()),camera,SLOT(close()));

    connect(form.expand_button, SIGNAL(pressed()), cameraWidget,SLOT(show()));
    ///////////////////////////////////////

    connect(form.seekSlider,SIGNAL(sliderPressed()),this,SLOT(seekPressedSlot()));
    connect(form.seekSlider,SIGNAL(sliderReleased()),this,SLOT(seekReleasedSlot()));
    connect(form.seekSlider,SIGNAL(valueChanged(int)),this,SLOT(seekMovedSlot()));
    connect(form.seekSlider,SIGNAL(sliderMoved(int)),this,SLOT(seekMovedSlot()));

    // ...and from private signals to public camera slots...
    connect(this,SIGNAL(speedPressed(double)), camera,SLOT(setSpeedCam(double)));
    connect(this,SIGNAL(seekPressed(QVCamera::TSeekType,double)), camera, SLOT(seekCam(QVCamera::TSeekType,double)));

    // ... and, finally, of camera newGrab and newRead signals to the
    // updateVisibleInfo slot...
    connect(camera,SIGNAL(newGrab()),this,SLOT(updateCameraVisibleInfoSlot()));
    connect(camera,SIGNAL(newRead()),this,SLOT(updateCameraVisibleInfoSlot()));
    connect(camera,SIGNAL(statusChange(QVCamera::TCameraStatus)),
        this,SLOT(updateCameraStateSlot(QVCamera::TCameraStatus)));

    // ... and the closed signal of the camera, also to the closePressed slot:
    //connect(camera,SIGNAL(camClosed()),this,SLOT(closePressedSlot()));

*/
    }

QVVideoReaderBlockWidgetSmall::~QVVideoReaderBlockWidgetSmall()
    {
        //FIXME quedará... delete this->cameraWidget;
    }

/*void QVCameraWidgetSmall::seekPressedSlot()
    {
    sliderActive = false;
    }

void QVCameraWidgetSmall::seekReleasedSlot()
    {
    sliderActive = true;
    emit seekPressed((QVCamera::TSeekType)1,form.seekSlider->value());
    }

void QVCameraWidgetSmall::seekMovedSlot()
    {
    //emit seekPressed((QVCamera::TSeekType)1,form.seekSlider->value());
    }

void QVCameraWidgetSmall::updateCameraVisibleInfoSlot()
    {
    int percen = (int)((100*camera->getTimePos())/camera->getTimeLength());
    if (sliderActive) form.seekSlider->setValue(percen);
    }

void QVCameraWidgetSmall::updateCameraStateSlot(QVCamera::TCameraStatus status)
    {
    qDebug() << "QVCameraWidgetSmall::updateCameraStateSlot()";
    qDebug() << "QVCameraWidgetSmall::updateCameraStateSlot(): new state id:" << status;
    switch(status)
        {
        case QVCamera::Closed:
            qDebug() << "QVCameraWidgetSmall::updateCameraStateSlot(): new state: Closed";
            form.stop_button->setEnabled(FALSE);
            form.pause_button->setEnabled(FALSE);
            form.play_button->setEnabled(FALSE);
            form.next_button->setEnabled(FALSE);
            form.expand_button->setEnabled(FALSE);
            break;

        case QVCamera::Running:
            qDebug() << "QVCameraWidgetSmall::updateCameraStateSlot(): new state: Running";
            form.stop_button->setEnabled(TRUE);
            form.pause_button->setEnabled(TRUE);
            form.play_button->setEnabled(FALSE);
            form.next_button->setEnabled(FALSE);
            form.expand_button->setEnabled(TRUE);
            break;

        case QVCamera::RunningOneStep:
            qDebug() << "QVCameraWidgetSmall::updateCameraStateSlot(): new state: Running one step";

        case QVCamera::Paused:
            qDebug() << "QVCameraWidgetSmall::updateCameraStateSlot(): new state: Paused";
            form.stop_button->setEnabled(TRUE);
            form.pause_button->setEnabled(FALSE);
            form.play_button->setEnabled(TRUE);
            form.next_button->setEnabled(TRUE);
            form.expand_button->setEnabled(TRUE);
            break;

        default:
            break;
        }

    qDebug() << "QVCameraWidgetSmall::updateCameraStateSlot() <~ return";
    }
*/
