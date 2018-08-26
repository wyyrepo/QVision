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

#ifndef QVPLOT_H
#define QVPLOT_H

#include <QTimer>
#include <QVProcessingBlock>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#define MAX_HISTORY 60 // seconds

/// @class QVPlot qvblockprogramming/qvguiblocks/qvplot.h QVPlot
/// @brief Class for plot block's graphs.
///
/// This virtual class plots graphs for block's properties that have been linked previously. But it doesn't know what type of properties are linked,
/// or how to gets the properties values. Each plot class must restrict the type of linked properties, and implements the getPropertyCurvNames, getPropertyCurvValues
/// and getPropertyCurvOrders functions.
///
/// @ingroup qvqwt

class QVPlot: public QwtPlot, public QVPropertyContainer
    {
    Q_OBJECT
    public:
        /// @brief Constructs a QVPlot with a given string identifier, showing properties and iteration's parameters.
        ///
        /// @param name Identifier for the object to be created.
        /// @param decorations Indicate if the plot must shown the scale axis.
        /// @param havePie Indicate if the plot must shown a top-right pie graph.
        /// @param brush Indicate if the graph's data values will be count form the axis or from the previous value.
        /// @param autoShow Indicate if the plot are shown at the beginning or must be shown by the user.
        /// @param time True if the iterations are based on clock time (in second hundredths), and false if they are based on block's iterations.
        /// @param step Set the base measure to plot's iterations ratio.
        /// @param parent Identifier for the parent widget.
        QVPlot(const QString name = QString(), bool decorations = true, bool havePie = false, bool brush = false, bool _autoShow = false, bool time = true,
               int step = 10, QWidget *parent = 0);

        ~QVPlot();

        /// @brief Links properties from blocks.
        ///
        /// This method safely links properties from blocks in a thread safe manner.
        /// If the iterations are based on block's iterations (time == false), the block must be synchronized with previous linked blocks.
        ///
        /// See also QVPropertyContainer::LinkType.
        /// @param block The source QVProcessingBlock.
        /// @param propertyName Identifying QString for the source property.
        bool linkProperty(QString sourcePropertyName, QVPropertyContainer *destinyContainer, QString destinyPropertyName, LinkType linkType = AsynchronousLink);
        bool linkProperty(QString sourcePropertyName, QVPropertyContainer &destinyContainer, QString destinyPropertyName, LinkType linkType = AsynchronousLink);
        bool linkProperty(QVPropertyContainer *destinyContainer, QString destinyPropertyName, LinkType linkType = AsynchronousLink);
        bool linkProperty(QVPropertyContainer &destinyContainer, QString destinyPropertyName, LinkType linkType = AsynchronousLink);
        bool linkProperty(QString sourcePropertyName, QVPropertyContainer *destinyContainer, LinkType linkType = AsynchronousLink);
        bool linkProperty(QString sourcePropertyName, QVPropertyContainer &destinyContainer, LinkType linkType = AsynchronousLink);
        void linkProperty(QVPropertyContainer *container, LinkType linkType = AsynchronousLink);
        void linkProperty(QVPropertyContainer &container, LinkType linkType = AsynchronousLink);
        bool unlinkProperty(QString origName, QVPropertyContainer *destCont, QString destName);
        bool unlinkProperty(QString origName, QVPropertyContainer &destCont, QString destName);
        void unlink();


        /// @brief Indicates if the plot is an auto-show plot.
        ///
        /// This method Indicates if the plot is an auto-show plot.
        bool isAutoShow() const { return autoShow; }

        /// @brief Indicates if the plot is initied.
        ///
        /// This method Indicates if the plot is initied.
        bool isInitied() const { return initied; }

    public slots:
        /// @brief Initialice the plot.
        /// A plot must be initialised after links all properties, and before update or shown the graphs.
        virtual void init();

        /// @brief Stop the plot.
        /// A plot must be stopped before initied.
        virtual void stop();

        /// @brief Update the block properties value of this block.
        ///
        /// @param id The block id whose properties value must be updated.
        /// @param iteration The current blocks iteration.
        void update(uint id, int iteration);

        /// @brief Inform the plot if a linked block has finish.
        /// In a plot based in block's iterations, it inform that the plot must wait less block's update to advance the graph.
        ///
        /// @param status A block status, it only matter if there are finished.
        void blockChange(QVProcessingBlock::TBlockStatus status);

        /// @brief Inform the plot if a item of the right legend has been cheked.
        /// In a plot has decorations, it inform that the plot must show or hide a stat value.
        ///
        /// @param status If has been checked.
        void legendItemCheked(bool check);

    signals:
        void closed();

#ifndef DOXYGEN_IGNORE_THIS
    protected:
        /// @brief Links an unspecified input property.
        ///
        /// This method safely links properties from blocks in a thread safe manner.
        /// When the user creates a link with an unispecified output property, the source container calls this destiny's method.
        /// If the destiny container is a QVPlot creates a property with the source property's name and calls the source container
        /// in order to it do the link with this new property.
        ///
        /// See also linkProperty(QVProcessingBlock &block, const QString propertyName).
        /// @param sourceContainer The container that whants to be linked.
        /// @param sourcePropName The name of the source property to be linked.
        /// @param linkType The link's type.
        virtual bool linkUnspecifiedInputProperty(QVPropertyContainer *sourceContainer, QString sourcePropName, LinkType linkType = AsynchronousLink);

        bool treatUnlinkInputProperty(QString destPropName, QVPropertyContainer *sourceCont, QString sourcePropName);

        void closeEvent(QCloseEvent *event) { Q_UNUSED(event); emit closed(); }


        /// @brief Returns a list with a property curve's names.
        /// A property can contain several values to be plot, each value must have a name.
        ///
        /// @param property The property name.
        virtual QStringList getPropertyCurvNames(QString property) const = 0;

        /// @brief Returns a list with a property curve's values.
        /// A property can contain several values to be plot.
        ///
        /// @param property The property name.
        virtual QList<double> getPropertyCurvValues(QString property) const = 0;

        /// @brief Returns a list with a property curve's index.
        /// A property can contain several values to be plot, each value must have a index that indicate the order to be plot. This value is useful
        /// in brush mode plots.
        ///
        /// @param property The property name.
        virtual QList<int> getPropertyCurvOrders(QString property) const = 0;

        class Curve
            {
            public:
                Curve(QString n, QwtPlotCurve *qwtpc, int tempSize): name(n), plot(qwtpc)
                    {
                    for (int i = 0; i < MAX_HISTORY; i++) history[i] = 0;
                    if (tempSize > 0)
                        {
                        temp = new double[tempSize];
                        for (int i = 0; i < tempSize; i++) temp[i] = 0;
                        }
                    }
                QString name;
                QwtPlotCurve * plot;
                double history[MAX_HISTORY];
                double brushHistory[MAX_HISTORY];
                double * temp;
            };

        class Property
            {
            public:
                Property(QString n): name(n) {}
                QString name;
                QList<Curve> curves;
            };

        class LinkedContainer
            {
            public:
                LinkedContainer(int ident): id(ident), iter(0), meanItems(0) {}
                uint id;
                int iter;
                QList<Property> properties;
                int meanItems;
            };

        QList<LinkedContainer> linkCont;
        const bool byTime;
        int iterationIndex;

        QColor nextColor();
        virtual void advancePlot();
        void timerEvent(QTimerEvent *e);
        virtual void insertNewFlags(int cont, int prop);
        void updateLegendItems();
        void hideStat(const QString labelText);
        void showStat(const QString labelText);

        const bool decorations, hPie, doBrush;
        const int nStep;

        friend class PieMarker;
        class PieMarker: public QwtPlotItem
            {
            public:
                PieMarker(QVPlot *plot);
                virtual int rtti() const;
                virtual void draw(QPainter *p, const QwtScaleMap &, const QwtScaleMap &, const QRect &rect) const;

            private:
                QVPlot *qvplot;
            };

        bool initied, autoShow;
        int timer;
        PieMarker *pie;
        bool haveCurves;
        int activeBlocks;
        QList<QVPropertyContainer *> pcl_Blocks;
        double timeData[MAX_HISTORY];
        int usedColors;
    };

#endif
#endif

