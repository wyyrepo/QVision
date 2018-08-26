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

#include "qvplot.h"
#include <qwt_plot_layout.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_widget.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_plot_canvas.h>
#include <qpainter.h>

/*QColor QVPlot::colors[] = {
        Qt::red,
        Qt::green,
        Qt::blue,
        Qt::cyan,
        Qt::magenta,
        Qt::darkRed,
        Qt::darkGreen,
        Qt::darkBlue,
        Qt::darkCyan,
        Qt::darkMagenta
        };*/

/////////////////////////////////////////////////////////////////////////////////////////////////////
// auxiliar classes functionality
QVPlot::PieMarker::PieMarker(QVPlot *plot): qvplot(plot)
    {
    setZ(1000);
    setRenderHint(QwtPlotItem::RenderAntialiased, true);
    }

int QVPlot::PieMarker::rtti() const
    {
    return QwtPlotItem::Rtti_PlotUserItem;
    }

void QVPlot::PieMarker::draw(QPainter *p, const QwtScaleMap &, const QwtScaleMap &, const QRect &rect) const
    {
    const int margin = 5;
    int diameter = ( (rect.height() > rect.width()) ? rect.width(): rect.height() ) / 4;

    QRect pieRect;
    pieRect.setX(rect.right() - margin - diameter);
    pieRect.setY(rect.top() + margin);

    pieRect.setHeight(diameter);
    pieRect.setWidth(diameter);

    int angle = (int)(5760 * 0.75);

    double sum = 0;
    for(int i = 0; i < qvplot->linkCont.size(); i++)
        for(int j = 0; j < qvplot->linkCont[i].properties.size(); j++)
            for(int k = 0; k < qvplot->linkCont[i].properties[j].curves.size(); k++)
                if (qvplot->linkCont[i].properties[j].curves[k].plot->style() != QwtPlotCurve::NoCurve)
                    sum += qvplot->linkCont[i].properties[j].curves[k].history[MAX_HISTORY - 1];


    for(int i = 0; i < qvplot->linkCont.size(); i++)
        for(int j = 0; j < qvplot->linkCont[i].properties.size(); j++)
            for(int k = 0; k < qvplot->linkCont[i].properties[j].curves.size(); k++)
                {
                const QwtPlotCurve *curve = qvplot->linkCont[i].properties[j].curves[k].plot;
                if ( (curve->style() != QwtPlotCurve::NoCurve) && (curve->dataSize() > 0) )
                    {
                    const int value = (int)(5760 * qvplot->linkCont[i].properties[j].curves[k].history[MAX_HISTORY - 1] / sum);
                    p->save();
                    p->setBrush(QBrush(curve->pen().color(), Qt::SolidPattern));
                    if ( value != 0 )
                        p->drawPie(pieRect, -angle, -value);
                    p->restore();

                    angle += value;
                    }
                }
    }

//////////////////////////////////////////////////////////////////////////////////////////////////

QVPlot::QVPlot(const QString name, bool decorations, bool havePie, bool brush, bool _autoShow, bool time, int step, QWidget *parent): QwtPlot(parent),
    QVPropertyContainer(name), byTime(time), iterationIndex(1), decorations(decorations), hPie(havePie), doBrush(brush), nStep(step), initied(false),
    autoShow(_autoShow), timer(0), haveCurves(FALSE), activeBlocks(0), usedColors(0)
    {
    qDebug() << "QVPlot::QVPlot()";
    if (qvApp == NULL)
        {
        QString str = "QVPlot::QVPlot(): the QVPlot cannot be created before the QVApplication instance. Aborting now.";
        std::cerr << qPrintable(str) << std::endl;
        exit(1);
        }
    // if its a --help call, do nothing
    if (qvApp->forHelp()) return;
    else QwtPlot(parent);


    setWindowTitle("Plot for " + getName());
    resize(400,200);
    setAutoReplot(false);

    for ( int i = 0; i < MAX_HISTORY; i++ ) timeData[i] = i;

    plotLayout()->setAlignCanvasToScales(true);

    if (decorations)
        {
        QwtLegend *legend = new QwtLegend;
        legend->setItemMode(QwtLegend::CheckableItem);
        insertLegend(legend, QwtPlot::RightLegend);
        }
    else
        {
        enableAxis(0,false);
        enableAxis(1,false);
        enableAxis(2,false);
        }

    class TimeScaleDraw: public QwtScaleDraw
        {
        public:
            TimeScaleDraw(const int stp): baseTime(), step(stp) { }
            virtual QwtText label(double v) const {	return baseTime.addSecs( (int)((v-MAX_HISTORY)*step/100)).toString(); }
        private:
            QTime baseTime;
            int step;
        };
    class IterScaleDraw: public QwtScaleDraw
        {
        public:
            IterScaleDraw(const int stp): step(stp) { }
            virtual QwtText label(double v) const	{ return QString::number((int)(v-MAX_HISTORY)*step); }
        private:
            int step;
        };
    if (byTime)	setAxisScaleDraw(QwtPlot::xBottom, new TimeScaleDraw(nStep));
    else		setAxisScaleDraw(QwtPlot::xBottom, new IterScaleDraw(nStep));

    setAxisScale(QwtPlot::xBottom, 0, MAX_HISTORY);
    setAxisLabelRotation(QwtPlot::xBottom, -50.0);
    setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);

    /* In situations, when there is a label at the most right position of the
    scale, additional space is needed to display the overlapping part
    of the label would be taken by reducing the width of scale and canvas.
    To avoid this "jumping canvas" effect, we add a permanent margin.
    We don't need to do the same for the left border, because there
    is enough space for the overlapping label below the left scale. */

    QwtScaleWidget *scaleWidget = axisWidget(QwtPlot::xBottom);
    const int fmh = QFontMetrics(scaleWidget->font()).height();
    scaleWidget->setMinBorderDist(0, fmh / 2);

    setAxisTitle(QwtPlot::yLeft, "Value");
    if (byTime)	setAxisTitle(QwtPlot::xBottom, "Time");
    else		setAxisTitle(QwtPlot::xBottom, "Iterations");
    }

QVPlot::~QVPlot()
{
    stop();
    ///@todo faltaría eliminar más objetos creados con new
}

bool QVPlot::linkProperty(QString, QVPropertyContainer *, QString, LinkType)
    {
        std::cerr << "ERROR: QVPlot::linkProperty(): a QVPlot has not output properties to be linked" << std::endl;
        return FALSE;
    }

bool QVPlot::linkProperty(QString sourcePropertyName, QVPropertyContainer &destinyContainer, QString destinyPropertyName, LinkType linkType)
    {
        return linkProperty(sourcePropertyName, &destinyContainer, destinyPropertyName, linkType);
    }

bool QVPlot::linkProperty(QVPropertyContainer *, QString, LinkType)
    {
        std::cerr << "ERROR: QVPlot::linkProperty(): a QVPlot has not output properties to be linked" << std::endl;
        return FALSE;
    }

bool QVPlot::linkProperty(QVPropertyContainer &destinyContainer, QString destinyPropertyName, LinkType linkType)
    {
        return linkProperty(&destinyContainer, destinyPropertyName, linkType);
    }

bool QVPlot::linkProperty(QString, QVPropertyContainer *, LinkType)
    {
        std::cerr << "ERROR: QVPlot::linkProperty(): a QVPlot has not output properties to be linked" << std::endl;
        return FALSE;
    }

bool QVPlot::linkProperty(QString sourcePropertyName, QVPropertyContainer &destinyContainer, LinkType linkType)
    {
        return linkProperty(sourcePropertyName, &destinyContainer, linkType);
    }

void QVPlot::linkProperty(QVPropertyContainer *, LinkType)
    {
        std::cerr << "ERROR: QVPlot::linkProperty(): a QVPlot has not output properties to be linked" << std::endl;
    }

void QVPlot::linkProperty(QVPropertyContainer &container, LinkType linkType)
    {
        linkProperty(&container, linkType);
    }

bool QVPlot::unlinkProperty(QString, QVPropertyContainer *, QString)
    {
        std::cerr << "ERROR: QVPlot::linkProperty(): a QVPlot has not output properties to be unlinked" << std::endl;
        return FALSE;
    }

bool QVPlot::unlinkProperty(QString origName, QVPropertyContainer &destCont, QString destName)
    {
        return unlinkProperty(origName, &destCont, destName);
    }

void QVPlot::unlink()
    {
        std::cerr << "ERROR: QVPlot::linkProperty(): a QVPlot has not output properties to be unlinked" << std::endl;
    }

bool QVPlot::linkUnspecifiedInputProperty(QVPropertyContainer *sourceContainer, QString sourcePropName, LinkType linkType)
    {
    if (initied)
        {
        std::cerr << "Warning: a block can't be linked before plot was initied." << std::endl;
        return false;
        }

    if (linkType != AsynchronousLink) {
        std::cerr << "ERROR: QVPlot::linkUnspecifiedInputProperty(): the linkType must be AsynchronousLink, the link will not be done" << std::endl;
        return false;
    }

    QVProcessingBlock* block;
    if((block = dynamic_cast<QVProcessingBlock*>(sourceContainer)) != NULL)
        {
        bool newBlock = false;
        if (!pcl_Blocks.contains(block))
            {
            pcl_Blocks << block;
            if ( (!byTime) && (!QVPropertyContainer::areSynchronized(pcl_Blocks)) )
                {
                pcl_Blocks.removeLast();
                std::cerr << "Warning: linked property's block must be synchronized with previous plot's linked blocks." << std::endl;
                return false;
                }
            activeBlocks++;
            newBlock = true;
            }

        QString myPropertyName = sourcePropName + QString(" (%1)").arg(block->getId());
        addPropertyFromQVariant(myPropertyName, inputFlag, block->getPropertyQVariantValue(sourcePropName), block->getPropertyInfo(sourcePropName));
        bool result = block->linkProperty(sourcePropName, this, myPropertyName, QVProcessingBlock::AsynchronousLink);

        if (newBlock)
            {
            linkCont << LinkedContainer(block->getId());

            // este tipo de bloqueo pos iteraciones puede retardar al block
            QObject::connect(block, SIGNAL(endIteration(uint, int)), this, SLOT(update(uint, int)), Qt::BlockingQueuedConnection);
            QObject::connect(block, SIGNAL(statusUpdate(QVProcessingBlock::TBlockStatus)), this, SLOT(blockChange(QVProcessingBlock::TBlockStatus)));
            }

        for (int i = 0; i < linkCont.size(); i++)
            if (linkCont[i].id == block->getId())
                {
                linkCont[i].properties.append(Property(myPropertyName));
                break;
                }

        return result;
        }
    else
        {
        std::cerr << "ERROR: QVPlot::linkUnspecifiedInputProperty(): the sourceContainer container must be a QVProcessingBlock, the link will not be done" << std::endl;
        return false;
        }
    }

bool QVPlot::treatUnlinkInputProperty(QString destPropName, QVPropertyContainer *sourceCont, QString)
    {
    for (int i = 0; i < linkCont.size(); i++)
        if (linkCont[i].id == sourceCont->getId())
            {
            int pos = -1;
            for (int j = 0; j < linkCont[i].properties.size(); j++)
                if (linkCont[i].properties[j].name == destPropName)
                    pos = j;

            if (pos >= 0)
                {
                linkCont[i].properties.removeAt(pos);
                }

            if (linkCont[i].properties.size() == 0)
                {
                linkCont.removeAt(i);
                pcl_Blocks.removeAll(sourceCont);
                activeBlocks--;

                QVProcessingBlock* block;
                if((block = dynamic_cast<QVProcessingBlock*>(sourceCont)) != NULL)
                    {
                    QObject::disconnect(block, SIGNAL(endIteration(uint, int)), this, SLOT(update(uint, int)));
                    QObject::disconnect(block, SIGNAL(statusUpdate(QVProcessingBlock::TBlockStatus)), this, SLOT(blockChange(QVProcessingBlock::TBlockStatus)));
                    }
                }
                break;
            }

    removeProperty(destPropName);
    return true;
    }

void QVPlot::init()
    {
    if (initied)
        {
        std::cerr << "Warning: a plot can't be initied more than one time." << std::endl;
        return;
        }

    if (hPie)
        {
        pie = new PieMarker(this);
        pie->attach(this);
        }

    readInputProperties();
    for(int i = 0; i < linkCont.size(); i++)
        for(int j = 0; j < linkCont[i].properties.size(); j++)
            {
            const QStringList curvNames = getPropertyCurvNames(linkCont[i].properties[j].name);

            for(int k = curvNames.size()-1; k >= 0; k--)
                {
                QString finalName = curvNames.at(k);

                QwtPlotCurve * qwtpc = new QwtPlotCurve(finalName);
                qwtpc->setRenderHint(QwtPlotItem::RenderAntialiased);
                QColor color = nextColor();
                qwtpc->setPen(color);
                if (doBrush) qwtpc->setBrush(color);
                qwtpc->setVisible(true);
                qwtpc->attach(this);

                if (byTime) linkCont[i].properties[j].curves.prepend(Curve(finalName, qwtpc, 1));
                else	    linkCont[i].properties[j].curves.prepend(Curve(finalName, qwtpc, linkCont.size()+1));
                haveCurves = TRUE;
                }

            // and conect the legend items chechek signal
            updateLegendItems();
            }

    if (byTime) timer = startTimer(nStep * 10); // nStep * 10 ms

    initied = true;
    }

void QVPlot::stop()
    {
    if (byTime && initied) killTimer(timer);
    initied = false;
    }

QColor QVPlot::nextColor()
    {
    QColor color = qvColors[usedColors % 10];
    usedColors++;
    return color;
    }

void QVPlot::timerEvent(QTimerEvent *)
    {
    if (!initied)
        {
        std::cerr << "Warning: a plot can't be advanced before it was initied." << std::endl;
        return;
        }

    // if there are data of flags, advance the Plot
    if (haveCurves) advancePlot();
    for (int i = 0; i < linkCont.size(); i++) linkCont[i].meanItems = 0;
    }

void QVPlot::blockChange(QVProcessingBlock::TBlockStatus status)
    {
    if ( (status == QVProcessingBlock::Finished) && (activeBlocks > 0) ) activeBlocks--;
    }

void QVPlot::update(uint id, int)
    {
    // First must be initied
    if (!initied)
        {
        std::cerr << "Warning: a plot can't be advanced before it was initied." << std::endl;
        return;
        }

    if (byTime)
        {
        readInputProperties();
        for(int i = 0; i < linkCont.size(); i++)
            if (linkCont[i].id == id)
                {
                for(int j = 0; j < linkCont[i].properties.size(); j++)
                    {
                    insertNewFlags(i, j);

                    const QList<double> values = getPropertyCurvValues(linkCont[i].properties[j].name);
                    if (values.size() != linkCont[i].properties[j].curves.size())
                        {
                        std::cerr << "QVPlot internal error: flags insert." << std::endl;
                        return;
                        }

                    for (int k = 0; k < linkCont[i].properties[j].curves.size(); k++)
                        if (linkCont[i].meanItems < 1)
                            linkCont[i].properties[j].curves[k].temp[0] = values[k];
                        else
                            linkCont[i].properties[j].curves[k].temp[0] =
                            (linkCont[i].properties[j].curves[k].temp[0]*linkCont[i].meanItems+values[k]) / (linkCont[i].meanItems + 1);
                    linkCont[i].meanItems++;
                    }
                break;
                }
        }
    else
        {
        readInputProperties();
        for(int i = 0; i < linkCont.size(); i++)
            if (linkCont[i].id == id)
                {
                linkCont[i].iter++;
                for(int j = 0; j < linkCont[i].properties.size(); j++)
                    {
                    insertNewFlags(i, j);

                    const QList<double> values = getPropertyCurvValues(linkCont[i].properties[j].name);
                    if (values.size() != linkCont[i].properties[j].curves.size())
                        {
                        std::cerr << "QVPlot internal error: flags insert." << std::endl;
                        return;
                        }

                    // update block's properties values for its iteration in the "temp" buffer (add the new value)
                    for (int k = 0; k < linkCont[i].properties[j].curves.size(); k++)
                        linkCont[i].properties[j].curves[k].temp[(linkCont[i].iter % (linkCont.size()+1))] += values[k];
                    }
                break;
                }

        int updateBlocks = 0;
        for (int i = 0; i < linkCont.size(); i++)
            if (linkCont[i].iter >= iterationIndex) updateBlocks++;

        // If has completed the current iteration column
        if (updateBlocks >= activeBlocks)
            {
            // If has completed nStep iterations
            if ((iterationIndex % nStep) == 0)
                {
                // obtain the mean to it
                for(int i = 0; i < linkCont.size(); i++)
                    {
                    linkCont[i].meanItems++;
                    for(int j = 0; j < linkCont[i].properties.size(); j++)
                        for (int k = 0; k < linkCont[i].properties[j].curves.size(); k++)
                            linkCont[i].properties[j].curves[k].temp[(iterationIndex % (linkCont.size()+1))] /= linkCont[i].meanItems;
                    linkCont[i].meanItems = 0;
                    }

                // Advance the plot
                if (haveCurves) advancePlot();
                }
            else
                {
                for(int i = 0; i < linkCont.size(); i++)
                    {
                    linkCont[i].meanItems++;
                    for(int j = 0; j < linkCont[i].properties.size(); j++)
                        for (int k = 0; k < linkCont[i].properties[j].curves.size(); k++)
                            linkCont[i].properties[j].curves[k].temp[((iterationIndex+1) % (linkCont.size()+1))] +=
                            linkCont[i].properties[j].curves[k].temp[(iterationIndex % (linkCont.size()+1))];
                    }
                }
            // And reset the column
            for(int i = 0; i < linkCont.size(); i++)
                for(int j = 0; j < linkCont[i].properties.size(); j++)
                    for (int k = 0; k < linkCont[i].properties[j].curves.size(); k++)
                        linkCont[i].properties[j].curves[k].temp[(iterationIndex % (linkCont.size()+1))] = 0;
            iterationIndex++;
            }
        }
    }

void QVPlot::insertNewFlags(int cont, int prop)
    {
    const QStringList curvNames = getPropertyCurvNames(linkCont[cont].properties[prop].name);
    if ( (linkCont.size() > cont) && (linkCont[cont].properties.size() > prop) && (curvNames.size() > linkCont[cont].properties[prop].curves.size()) )
        {
        const QList<int> curvOrders = getPropertyCurvOrders(linkCont[cont].properties[prop].name);
        for (int i = 0; i < curvOrders.size(); i++)
            if (curvOrders.at(i) > linkCont[cont].properties[prop].curves.size())
                {
                QString finalName = curvNames.at(i);

                QwtPlotCurve * qwtpc = new QwtPlotCurve(finalName);
                qwtpc->setRenderHint(QwtPlotItem::RenderAntialiased);
                QColor color = nextColor();
                qwtpc->setPen(color);
                if (doBrush) qwtpc->setBrush(color);
                qwtpc->setVisible(true);

                if (byTime) linkCont[cont].properties[prop].curves.insert(i, Curve(finalName, qwtpc, 1));
                else	    linkCont[cont].properties[prop].curves.insert(i, Curve(finalName, qwtpc, linkCont.size()+1));
                haveCurves = TRUE;
                }

        for(int i = linkCont.size()-1; i >= 0; i--)
            for(int j = linkCont[i].properties.size()-1; j >= 0; j--)
                for (int k = linkCont[i].properties[j].curves.size()-1; k >= 0; k--)
                    {
                    linkCont[i].properties[j].curves[k].plot->detach();
                    linkCont[i].properties[j].curves[k].plot->attach(this);
                    }

        // and reconect the legend items chechek signal
        updateLegendItems();
        }
    }

void QVPlot::advancePlot()
    {
    if (!haveCurves)
        {
        std::cerr << "QVPlot internal error: early call to advancePlot." << std::endl;
        return;
        }

    if (activeBlocks < 1)
        return;

    // increments the values to scroll the window
    for ( int j = 0; j < MAX_HISTORY; j++ ) timeData[j]++;

    double max = 0;
    double brush[MAX_HISTORY]; for (int i = 0; i < MAX_HISTORY; i++) brush[i] = 0;

    // for each curve
    for(int i = 0; i < linkCont.size(); i++)
        for(int j = 0; j < linkCont[i].properties.size(); j++)
            for(int k = 0; k < linkCont[i].properties[j].curves.size(); k++) {
                 // scroll the curve values
                for (int l = 0; l < MAX_HISTORY-1; l++)
                    linkCont[i].properties[j].curves[k].history[l] = linkCont[i].properties[j].curves[k].history[l+1];

                // update the new value
                if (byTime)	linkCont[i].properties[j].curves[k].history[MAX_HISTORY-1] = linkCont[i].properties[j].curves[k].temp[0];
                else		linkCont[i].properties[j].curves[k].history[MAX_HISTORY-1] = linkCont[i].properties[j].curves[k].temp[(iterationIndex%(linkCont.size()+1))];

                // if is visible, update the plot values
                if (linkCont[i].properties[j].curves[k].plot->style() != QwtPlotCurve::NoCurve) {
                    if (doBrush) { // if is in brush mode, update the increment, sets the brush value, calculate the max value, and set the curve's plot
                        for (int l = 0; l < MAX_HISTORY; l++) {
                            brush[l] += linkCont[i].properties[j].curves[k].history[l];
                            linkCont[i].properties[j].curves[k].brushHistory[l] = brush[l];
                            if (max < linkCont[i].properties[j].curves[k].brushHistory[l]) max = linkCont[i].properties[j].curves[k].brushHistory[l];
                        }
                        linkCont[i].properties[j].curves[k].plot->setRawData(timeData, linkCont[i].properties[j].curves[k].brushHistory, MAX_HISTORY);
                    }
                    else { // if isn't in brush mode, calculate the max value, and set the curve's plot
                        for (int l = 0; l < MAX_HISTORY; l++) {
                            if (max < linkCont[i].properties[j].curves[k].history[l]) max = linkCont[i].properties[j].curves[k].history[l];
                        }
                        linkCont[i].properties[j].curves[k].plot->setRawData(timeData, linkCont[i].properties[j].curves[k].history, MAX_HISTORY);
                    }
                }
            }
    max = 1.1 *max;

    setAxisScale(QwtPlot::yLeft, 0, max);
    setAxisScale(QwtPlot::xBottom, timeData[MAX_HISTORY - 1], timeData[0]);

    // and replot
    replot();
    }










void QVPlot::updateLegendItems()
    {
    if (decorations)
        foreach(QWidget *widgetItem, legend()->legendItems())
            {
            QwtLegendItem *legendItem;
            if((legendItem = dynamic_cast<QwtLegendItem*>(widgetItem)) != NULL)
                QObject::connect(legendItem, SIGNAL(checked(bool)), this, SLOT(legendItemCheked(bool)));
            }
    }

void QVPlot::legendItemCheked(bool)
    {
    if (decorations)
        foreach(QWidget *widgetItem, legend()->legendItems())
            {
            QwtLegendItem *legendItem;
            if ((legendItem = dynamic_cast<QwtLegendItem*>(widgetItem)) != NULL) {
                if (legendItem->isChecked())
                    hideStat(legendItem->text().text());
                else
                    showStat(legendItem->text().text());
            }
            }
    }

void QVPlot::hideStat(const QString labelText)
    {
    for(int i = 0; i < linkCont.size(); i++)
        for(int j = 0; j < linkCont[i].properties.size(); j++)
            for(int k = 0; k < linkCont[i].properties[j].curves.size(); k++)
                if (linkCont[i].properties[j].curves[k].name == labelText) {
                    linkCont[i].properties[j].curves[k].plot->setStyle(QwtPlotCurve::NoCurve);
                    return;
                }
    }

void QVPlot::showStat(const QString labelText)
    {
    for(int i = 0; i < linkCont.size(); i++)
        for(int j = 0; j < linkCont[i].properties.size(); j++)
            for(int k = 0; k < linkCont[i].properties[j].curves.size(); k++)
                if (linkCont[i].properties[j].curves[k].name == labelText)
                    {
                    linkCont[i].properties[j].curves[k].plot->setStyle(QwtPlotCurve::Lines);
                    return;
                    }
    }
