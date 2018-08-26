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

#include "qvvideoreaderblockwidget.h"
#include <QFileDialog>

QVVideoReaderBlockWidget::QVVideoReaderBlockWidget(QVVideoReaderBlock *cam, QWidget *parent): QWidget(parent), QVPropertyContainer("")
    {
    slider_active = true;
    form.setupUi(this);
    this->camera = cam;

    // Set prop. container name:
    setName(QString("GUI for camera ")+cam->getName());

    // First, we initialize our properties by looking at the initial properties of the camera.
    // Danger: Here we must read directly from camera properties, in order to initialize correctly the values of the
    // widget. We need to do it this way to avoid the need of making them also output properties in the camera
    // In any case, here it is still safe to do this, because the camera block is still not running. It is a similar
    // case to that of a qvparaminspectorwidget.
    int cols = camera->getPropertyValue<int>("Cols"), rows = camera->getPropertyValue<int>("Rows");
    QString url = camera->getPropertyValue<QString>("URL");
    bool noloop = camera->getPropertyValue<bool>("NoLoop"), deinterlaced = camera->getPropertyValue<bool>("Deinterlaced");
    bool realTime = camera->getPropertyValue<bool>("RealTime");

    setPropertyValue<int>("Cols",cols);
    setPropertyValue<int>("Rows",rows);
    setPropertyValue<QString>("URL",url);
    setPropertyValue<bool>("NoLoop",noloop);
    setPropertyValue<bool>("Deinterlaced",deinterlaced);

    form.spinbox_cols->setValue(cols);
    form.spinbox_rows->setValue(rows);
    form.url_line_edit->setText(url);
    form.noloop_button->setChecked(noloop);
    form.deinterlaced_button->setChecked(deinterlaced);
    form.real_time_label->setText(realTime?"Real Time":"Max speed");

    // Subscribe (asynchronously) to all relevant input properties of the camera:
    subscribeToInputProperty(cam,"NoLoop");
    subscribeToInputProperty(cam,"Deinterlaced");
    subscribeToInputProperty(cam,"URL");
    subscribeToInputProperty(cam,"Cols");
    subscribeToInputProperty(cam,"Rows");

    subscribeToOutputProperty(cam,"Opened");
    subscribeToOutputProperty(cam,"FPS");
    subscribeToOutputProperty(cam,"Frames");
    subscribeToOutputProperty(cam,"ColsR");
    subscribeToOutputProperty(cam,"RowsR");
    subscribeToOutputProperty(cam,"Pos");
    subscribeToOutputProperty(cam,"Length");

    connect(cam,SIGNAL(opened()),this,SLOT(updateOpened())/*,Qt::BlockingQueuedConnection*/);
    connect(cam,SIGNAL(closed()),this,SLOT(updateClosed())/*,Qt::BlockingQueuedConnection*/);
    if(realTime)
        connect(cam,SIGNAL(grabbed()),this,SLOT(newFrameGrabbed()));
    else
        connect(cam,SIGNAL(endIteration(uint,int)),this,SLOT(newFrameGrabbed()));

    connect(form.stop_button,SIGNAL(pressed()),this,SLOT(stopPressed()));

    connect(form.pause_button,SIGNAL(pressed()),cam,SLOT(pause()));
    connect(form.pause_button,SIGNAL(pressed()),this,SLOT(pausePressed()));

    connect(form.play_button,SIGNAL(pressed()),cam,SLOT(unPause()));
    connect(form.play_button,SIGNAL(pressed()),this,SLOT(playPressed()));

    connect(form.next_button,SIGNAL(pressed()),cam,SLOT(step()));
    connect(form.next_button,SIGNAL(pressed()),this,SLOT(nextPressed()));

    connect(form.seek_slider,SIGNAL(sliderPressed()),this,SLOT(seekPressed()));
    connect(form.seek_slider,SIGNAL(sliderReleased()),this,SLOT(seekReleased()));

    connect(this,SIGNAL(seek_requested(int)),camera,SLOT(setPos(int)));

    connect(form.url_line_edit,SIGNAL(editingFinished()),this,SLOT(somePropertyChanged()));
    connect(form.spinbox_cols,SIGNAL(valueChanged(int)),this,SLOT(somePropertyChanged()));
    connect(form.spinbox_rows,SIGNAL(valueChanged(int)),this,SLOT(somePropertyChanged()));
    connect(form.noloop_button,SIGNAL(toggled(bool)),this,SLOT(somePropertyChanged()));
    connect(form.deinterlaced_button,SIGNAL(toggled(bool)),this,SLOT(somePropertyChanged()));

    connect(form.file_open_button,SIGNAL(pressed()),this,SLOT(fileOpenButtonPressed()));
    connect(this,SIGNAL(file_selected()),cam,SLOT(reopen()));

    connect(form.reopen_button,SIGNAL(pressed()),cam,SLOT(reopen()));

    }

void QVVideoReaderBlockWidget::subscribeToOutputProperty(QVPropertyContainer *qvp, QString name, LinkType linktype)
    {
    // Adds a property with the same name than that of another qvpropertycontainer, and links to it (from there to here)
    // with the desired link type. Observe that the property is initialized with its current value in the qvp object:
    addPropertyFromQVariant(name, inputFlag, qvp->getPropertyQVariantValue(name),qvp->getPropertyInfo(name));
    qvp->linkProperty(name,this,name,linktype);
    }

void QVVideoReaderBlockWidget::subscribeToInputProperty(QVPropertyContainer *qvp, QString name, LinkType linktype)
    {
    // Adds a property with the same name than that of another qvpropertycontainer, and links to it (from here to there)
    // with the desired link type. Observe that the property is initialized with its current value in the qvp object:
    addPropertyFromQVariant(name, outputFlag, qvp->getPropertyQVariantValue(name),qvp->getPropertyInfo(name));
    this->linkProperty(name,qvp,name,linktype);
    }

void QVVideoReaderBlockWidget::somePropertyChanged()
    {
    setPropertyValue<QString>("URL",form.url_line_edit->text());
    setPropertyValue<int>("Cols",form.spinbox_cols->value());
    setPropertyValue<int>("Rows",form.spinbox_rows->value());
    setPropertyValue<bool>("NoLoop",form.noloop_button->isChecked());
    setPropertyValue<bool>("Deinterlaced",form.deinterlaced_button->isChecked());

    writeOutputProperties();
    }

void QVVideoReaderBlockWidget::updateOpened()
    {
    form.stop_button->setEnabled(TRUE);
    form.pause_button->setEnabled(TRUE);
    form.play_button->setEnabled(FALSE);
    form.next_button->setEnabled(FALSE);
    }

void QVVideoReaderBlockWidget::updateClosed()
    {
    form.stop_button->setEnabled(FALSE);
    form.pause_button->setEnabled(FALSE);
    form.play_button->setEnabled(FALSE);
    form.next_button->setEnabled(FALSE);
    }

void QVVideoReaderBlockWidget::stopPressed()
    {
    form.stop_button->setEnabled(FALSE);
    form.pause_button->setEnabled(FALSE);
    form.play_button->setEnabled(FALSE);
    form.next_button->setEnabled(FALSE);
    }

void QVVideoReaderBlockWidget::pausePressed()
    {
    form.pause_button->setEnabled(FALSE);
    form.play_button->setEnabled(TRUE);
    form.next_button->setEnabled(TRUE);
    }

void QVVideoReaderBlockWidget::playPressed()
    {
    form.pause_button->setEnabled(TRUE);
    form.play_button->setEnabled(FALSE);
    form.next_button->setEnabled(FALSE);
    }

void QVVideoReaderBlockWidget::nextPressed()
    {
    }

void QVVideoReaderBlockWidget::newFrameGrabbed()
    {
    readInputProperties();

    form.frames_label->setText(QString("Frames: %1").arg(getPropertyValue<int>("Frames")));
    form.size_label->setText(QString("Size: %1x%2").arg(getPropertyValue<int>("ColsR")).arg(getPropertyValue<int>("RowsR")));
    //QString len_string = QString("%1").arg(getPropertyValue<int>("Length"),1,'f',1);
    //QString pos_string = QString("%1").arg(getPropertyValue<int>("Pos"),1,'f',1);
    QString len_string = QString("%1").arg(getPropertyValue<int>("Length"),1);
    QString pos_string = QString("%1").arg(getPropertyValue<int>("Pos"),1);
    form.pos_label->setText("Position: " + pos_string + "/" + len_string );
    form.fps_label->setText(QString("FPS: %1").arg(getPropertyValue<int>("FPS")));

    if(getPropertyValue<int>("Length") > 0)
        {
        form.seek_slider->setEnabled(TRUE);
        if(slider_active)
            {
            int pos = (int)(form.seek_slider->maximum()*getPropertyValue<int>("Pos")/getPropertyValue<int>("Length"));
            form.seek_slider->setValue(pos);
            }
        }
    }


void QVVideoReaderBlockWidget::seekPressed()
    {
    slider_active = false;
    }

void QVVideoReaderBlockWidget::seekReleased()
    {
    slider_active = true;
    emit seek_requested(form.seek_slider->value()*getPropertyValue<int>("Length")/form.seek_slider->maximum());
    }

void QVVideoReaderBlockWidget::fileOpenButtonPressed()
    {
    QFileDialog dialog(this);

    QStringList filters;

    /*#ifdef QVIPP
    if((dynamic_cast<QVYUV4MPEG2ReaderBlock*>(camera)) != NULL)
        filters << "Video Files (*.yuv)" << "All files (*)";
    #ifdef QVMPLAYER
    else if((dynamic_cast<QVMPlayerReaderBlock*>(camera)) != NULL)
        filters << "Video Files (*.avi *.dv *.mpg *.mpeg *.yuv *.wmv)" << "All files (*)";
    #endif // QVMPLAYER
    else
        filters << "All files (*)";
    #else // QVIPP
        filters << "All files (*)";
    #endif // QVIPP*/

    filters << "Video Files (*.avi *.dv *.mpg *.mpeg *.yuv *.wmv)" << "All files (*)";

    #if QT_VERSION >= 0x040400
        dialog.setNameFilters(filters);
    #else
        dialog.setFilters(filters);
    #endif

    dialog.setWindowTitle("Open video file");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);

    QString str = getPropertyValue<QString>("URL");
    QStringList strl = str.split("/");
    strl.removeLast();
    str = strl.join("/");
    QDir dir(str);

    if(dir.exists())
        dialog.setDirectory(str);
    else
        dialog.setDirectory(QDir::currentPath());

    QString fileName;
    if (dialog.exec())
        {
        QString filename = dialog.selectedFiles().first();
        setPropertyValue<QString>("URL",filename);
        form.url_line_edit->setText(filename);
        writeOutputProperties();
        emit file_selected();
        }
    }


