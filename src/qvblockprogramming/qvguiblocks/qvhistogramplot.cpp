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
#include "qvhistogramplot.h"
#include <qwt_interval_data.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_div.h>
#include <qwt_scale_engine.h>
#include <QResizeEvent>

/// @todo los parámetros de configuración de los widgets numericplot e histogramplot puedan ser propiedades dinámicas.
QVHistogramPlot::QVHistogramPlot(const QString name, bool time, int step, double maxim, double minim, QWidget *parent):
	QVPlot(name, false, false, false, true, time, step, parent), histItem(), max(maxim), min(minim), maxAxisNumbers(10)
	{
	histItem.setColor(Qt::darkCyan);
	enableAxis(0,true);
	enableAxis(2,true);
	setAxisScaleDraw(QwtPlot::xBottom, new QwtScaleDraw());
	setAxisTitle(QwtPlot::xBottom, "Index");
	}

bool QVHistogramPlot::linkUnspecifiedInputProperty(QVPropertyContainer *sourceContainer, QString sourcePropName, LinkType linkType)
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

QStringList QVHistogramPlot::getPropertyCurvNames(QString propertyName) const
	{
	QStringList names;

	const int auxListSize =	isType< QList<double> >(propertyName)? getPropertyValue< QList<double> >(propertyName).size():
				isType< QVector<double> >(propertyName)? getPropertyValue< QVector<double> >(propertyName).size(): -1;

	for (int i = 0; i < auxListSize; i++)
		names << QString::number(i);

	return names;
	}

QList<double> QVHistogramPlot::getPropertyCurvValues(QString propertyName) const
	{
	if (isType< QList<double> >(propertyName))
		return getPropertyValue< QList<double> >(propertyName);
	else if (isType< QVector<double> >(propertyName))
		return getPropertyValue< QVector<double> >(propertyName).toList();
	else
		std::cout << "ERROR 34: Love unknown error codes?" << std::endl;

	return QList<double>();
	}

QList<int> QVHistogramPlot::getPropertyCurvOrders(QString propertyName) const
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

void QVHistogramPlot::init()
	{
	if (initied)
		{
		std::cerr << "Warning: a plot can't be initied more than one time." << std::endl;
		return;
		}

	histItem.attach(this);

	readInputProperties();
	for(int i = 0; i < linkCont.size(); i++)
		for(int j = 0; j < linkCont[i].properties.size(); j++)
			{
			const QStringList curvNames = getPropertyCurvNames(linkCont[i].properties[j].name);

			for(int k = curvNames.size()-1; k >= 0; k--)
				{
				QString finalName = curvNames.at(k) + QString(" (%1)").arg(linkCont[i].id);

				QwtPlotCurve * qwtpc = new QwtPlotCurve(finalName);
				if (byTime) linkCont[i].properties[j].curves.prepend(Curve(curvNames.at(k), qwtpc, 1));
				else	    linkCont[i].properties[j].curves.prepend(Curve(curvNames.at(k), qwtpc, linkCont.size()+1));
				haveCurves = TRUE;
				}
			}

	if (byTime) timer = startTimer(nStep * 10); // nStep * 10 ms

	initied = true;
	}

void QVHistogramPlot::insertNewFlags(int cont, int prop)
	{
	const QStringList curvNames = getPropertyCurvNames(linkCont[cont].properties[prop].name);
	if ( (linkCont.size() > cont) && (linkCont[cont].properties.size() > prop) && (curvNames.size() > linkCont[cont].properties[prop].curves.size()) )
		{
		const QList<int> curvOrders = getPropertyCurvOrders(linkCont[cont].properties[prop].name);
		for (int i = 0; i < curvOrders.size(); i++)
			if (curvOrders.at(i) > linkCont[cont].properties[prop].curves.size())
				{
				QString finalName = curvNames.at(i) + QString(" (%1)").arg(linkCont[cont].id);

				QwtPlotCurve * qwtpc = new QwtPlotCurve(finalName);
				if (byTime) linkCont[cont].properties[prop].curves.insert(i, Curve(curvNames.at(i), qwtpc, 1));
				else	    linkCont[cont].properties[prop].curves.insert(i, Curve(curvNames.at(i), qwtpc, linkCont.size()+1));
				haveCurves = TRUE;
				}
		}
	}

void QVHistogramPlot::advancePlot()
	{
	if (!haveCurves)
		{
		std::cerr << "QVPlot internal error: early call to advancePlot." << std::endl;
		return;
		}

	// update data
	int numValues = 0;
	for(int i = 0; i < linkCont.size(); i++)
		for(int j = 0; j < linkCont[i].properties.size(); j++) {
			for(int k = 0; k < linkCont[i].properties[j].curves.size(); k++)
				{
				// update the new value
				if (byTime)	linkCont[i].properties[j].curves[k].history[0] = linkCont[i].properties[j].curves[k].temp[0];
				else		linkCont[i].properties[j].curves[k].history[0] = linkCont[i].properties[j].curves[k].temp[(iterationIndex%(linkCont.size()+1))];
				}
			if (numValues < linkCont[i].properties[j].curves.size()) numValues = linkCont[i].properties[j].curves.size();
		}

	QwtArray<QwtDoubleInterval> intervals(numValues);
	QwtArray<double> values(numValues);

	// curve update
	for(int i = 0; i < linkCont.size(); i++)
		for(int j = 0; j < linkCont[i].properties.size(); j++) {
			for(int k = 0; k < linkCont[i].properties[j].curves.size(); k++)
				{
				if (values[k] < linkCont[i].properties[j].curves[k].history[0]) values[k] = linkCont[i].properties[j].curves[k].history[0];
				intervals[k] = QwtDoubleInterval(double(k)-0.5, double(k+1)-0.5);
				}
		}

	// scroll bottom axis, scaled like an index
	int scaleShow = MAX(numValues/maxAxisNumbers, 1);
	setAxisScaleDiv(QwtPlot::xBottom, axisScaleEngine(QwtPlot::xBottom)->divideScale(-0.5, double(numValues)-0.5, 1, 1, scaleShow));

	histItem.setData(QwtIntervalData(intervals, values));

	// adjust left axis (using the visible values's maximum)
	if (max == 0)
		{
		for(int i = 0; i < linkCont.size(); i++)
			for(int j = 0; j < linkCont[i].properties.size(); j++)
				for(int k = 0; k < linkCont[i].properties[j].curves.size(); k++)
					if (max < linkCont[i].properties[j].curves[k].history[0]) max = linkCont[i].properties[j].curves[k].history[0];
		max = 1.1 *max;
		setAxisScale(QwtPlot::yLeft, min, max);
		max = 0;
		}
	else setAxisScale(QwtPlot::yLeft, min, max);

	// and replot
	replot();
	}



void QVHistogramPlot::resizeEvent(QResizeEvent * e)
	{
		QVPlot::resizeEvent(e);
		maxAxisNumbers = e->size().width() / 50;
	}

