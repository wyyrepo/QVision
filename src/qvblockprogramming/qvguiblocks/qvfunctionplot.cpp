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

#include <qvmath.h>
#include <iostream>
#include "qvfunctionplot.h"
#include <qwt_interval_data.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_div.h>
#include <qwt_scale_engine.h>
#include <QResizeEvent>

/// @todo los parámetros de configuración de los widgets numericplot e histogramplot puedan ser propiedades dinámicas.
QVFunctionPlot::QVFunctionPlot(const QString name, bool time, int step, QWidget *parent):
	QVPlot(name, false, false, false, true, time, step, parent), maxAxisNumbers(10)
	{
	enableAxis(0,true);
	enableAxis(2,true);
	setAxisScaleDraw(QwtPlot::xBottom, new QwtScaleDraw());
	setAxisTitle(QwtPlot::xBottom, "Index");
	}

bool QVFunctionPlot::linkUnspecifiedInputProperty(QVPropertyContainer *sourceContainer, QString sourcePropName, LinkType linkType)
	{
	QVProcessingBlock* block;
	if((block = dynamic_cast<QVProcessingBlock*>(sourceContainer)) != NULL)
		{
		if ( block->isType< QList<double> >(sourcePropName) || block->isType< QVector<double> >(sourcePropName) )
			return QVPlot::linkUnspecifiedInputProperty(block, sourcePropName, linkType);
		else
			{
			std::cerr << "Warning: a histogramplot can only be linked to a QList<double> or QVector<double> property." << std::endl;
			return false;
			}
		}
	else
		return false;
	}

QStringList QVFunctionPlot::getPropertyCurvNames(QString propertyName) const
	{
	QStringList names;

	const int auxListSize =	isType< QList<double> >(propertyName)? getPropertyValue< QList<double> >(propertyName).size():
				isType< QVector<double> >(propertyName)? getPropertyValue< QVector<double> >(propertyName).size(): -1;

	for (int i = 0; i < auxListSize; i++)
		names << QString::number(i);

	return names;
	}

QList<double> QVFunctionPlot::getPropertyCurvValues(QString propertyName) const
	{
	if (isType< QList<double> >(propertyName))
		return getPropertyValue< QList<double> >(propertyName);
	else if (isType< QVector<double> >(propertyName))
		return getPropertyValue< QVector<double> >(propertyName).toList();
	else
		std::cout << "ERROR 34: Love unknown error codes?" << std::endl;

	return QList<double>();
	}

QList<int> QVFunctionPlot::getPropertyCurvOrders(QString propertyName) const
	{
	QList<int> order;
	//const int auxListSize = getPropertyValue< QList<double> >(property).size();
	//QList<double> auxList = getPropertyValue< QList<double> >(property);
	const int auxListSize =	isType< QList<double> >(propertyName)? getPropertyValue< QList<double> >(propertyName).size():
				isType< QVector<double> >(propertyName)? getPropertyValue< QVector<double> >(propertyName).size(): -1;

	for (int i = 1; i <= auxListSize; i++)
	//for (int i = 1; i <= auxList.size(); i++)
		order << i;
	return order;
	}

void QVFunctionPlot::init()
	{
	if (initied)
		{
		std::cerr << "Warning: a plot can't be initied more than one time." << std::endl;
		return;
		}

	readInputProperties();
	for(int i = 0; i < linkCont.size(); i++)
		for(int j = 0; j < linkCont[i].properties.size(); j++)
			{
			const QStringList curvNames = getPropertyCurvNames(linkCont[i].properties[j].name);

			for(int k = curvNames.size()-1; k >= 0; k--)
				{
				QString finalName = curvNames.at(k) + QString(" (%1)").arg(linkCont[i].id);

				QwtPlotCurve * qwtpc = NULL;
				if (k == 0) {
					qwtpc = new QwtPlotCurve(finalName);
					qwtpc->setRenderHint(QwtPlotItem::RenderAntialiased);
					QColor color = nextColor();
					qwtpc->setPen(color);
					if (doBrush) qwtpc->setBrush(color);
					qwtpc->setVisible(true);
					qwtpc->attach(this);
				}

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

void QVFunctionPlot::insertNewFlags(int cont, int prop)
	{
	const QStringList curvNames = getPropertyCurvNames(linkCont[cont].properties[prop].name);
	if ( (linkCont.size() > cont) && (linkCont[cont].properties.size() > prop) && (curvNames.size() > linkCont[cont].properties[prop].curves.size()) )
		{
		const QList<int> curvOrders = getPropertyCurvOrders(linkCont[cont].properties[prop].name);
		for (int i = 0; i < curvOrders.size(); i++)
			if (curvOrders.at(i) > linkCont[cont].properties[prop].curves.size())
				{
				QString finalName = curvNames.at(i) + QString(" (%1)").arg(linkCont[cont].id);

				QwtPlotCurve * qwtpc = NULL;
				if (curvOrders.at(i) == 1) {
					qwtpc = new QwtPlotCurve(finalName);
					qwtpc->setRenderHint(QwtPlotItem::RenderAntialiased);
					QColor color = nextColor();
					qwtpc->setPen(color);
					if (doBrush) qwtpc->setBrush(color);
					qwtpc->setVisible(true);
				}

				if (byTime) linkCont[cont].properties[prop].curves.insert(i, Curve(finalName, qwtpc, 1));
				else	    linkCont[cont].properties[prop].curves.insert(i, Curve(finalName, qwtpc, linkCont.size()+1));
				haveCurves = TRUE;
				}

		for(int i = linkCont.size()-1; i >= 0; i--)
			for(int j = linkCont[i].properties.size()-1; j >= 0; j--)
					if (linkCont[i].properties[j].curves.size() > 0)
					{
						linkCont[i].properties[j].curves[0].plot->detach();
						linkCont[i].properties[j].curves[0].plot->attach(this);
					}

		// and reconect the legend items chechek signal
		updateLegendItems();
		}
	}

void QVFunctionPlot::advancePlot()
	{
	if (!haveCurves)
		{
		std::cerr << "QVPlot internal error: early call to advancePlot." << std::endl;
		return;
		}

	double max = 0;

	int maxSize = 0;
	for(int i = 0; i < linkCont.size(); i++)
		for(int j = 0; j < linkCont[i].properties.size(); j++)
			if (maxSize < linkCont[i].properties[j].curves.size()) maxSize = linkCont[i].properties[j].curves.size();

	QList<double *> curves;
	double curvePos[maxSize];
	for (int i = 0; i < maxSize; i++) curvePos[i] = i;
	QwtArray<QwtDoubleInterval> intervals(maxSize);

	// for each property
	for(int i = 0; i < linkCont.size(); i++)
		for(int j = 0; j < linkCont[i].properties.size(); j++) {
			double *tempCurve = new double[maxSize];
			for (int k = 0; k < maxSize; k++) tempCurve[k] = 0;
			curves.append(tempCurve);
			

			for(int k = 0; k < linkCont[i].properties[j].curves.size(); k++) {
				if (byTime)	tempCurve[k] = linkCont[i].properties[j].curves[k].temp[0];
				else		tempCurve[k] = linkCont[i].properties[j].curves[k].temp[(iterationIndex%(linkCont.size()+1))];
				intervals[k] = QwtDoubleInterval(double(k)-0.5, double(k+1)-0.5);
			}

			// if is visible, update the plot values
			if (linkCont[i].properties[j].curves.size() > 0) {
				if (linkCont[i].properties[j].curves[0].plot->style() != QwtPlotCurve::NoCurve) {
					for (int k = 0; k < linkCont[i].properties[j].curves.size(); k++) {
						if (max < tempCurve[k]) max = tempCurve[k];
					}
					linkCont[i].properties[j].curves[0].plot->setRawData(curvePos, tempCurve, maxSize);
				}
			}
		}

	max = 1.1 *max;


	setAxisScale(QwtPlot::yLeft, 0, max);
	setAxisScale(QwtPlot::xBottom, maxSize, 0);

	int scaleShow = MAX(maxSize/maxAxisNumbers, 1);
	setAxisScaleDiv(QwtPlot::xBottom, axisScaleEngine(QwtPlot::xBottom)->divideScale(-0.5, double(maxSize)-0.5, 1, 1, scaleShow));


	// and replot
	replot();

	foreach(double * curve, curves)
		delete curve;
	}

void QVFunctionPlot::resizeEvent(QResizeEvent * e)
	{
		QVPlot::resizeEvent(e);
		maxAxisNumbers = e->size().width() / 50;
	}



