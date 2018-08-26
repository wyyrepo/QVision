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

#ifndef QVRANSAC_H
#define QVRANSAC_H

#include <iostream>
#include <QMap>

#include <qvmath.h>

/*!
@class QVRANSAC qvmath/qvsampleconsensus.h QVRANSAC qvsampleconsensus.h qvmath/qvsampleconsensus.h
@brief Implementation of <a href="http://en.wikipedia.org/wiki/RANSAC">RANSAC</a>, a robust statistical model fitting algorithm.

RANSAC can be used for regression over sample data sets, containing a significant percentage of gross errors. The following image shows the result of using RANSAC to fit a linear model over a set of points in the bi-dimensional plane:

\image html ransac-linear-fitting.png

it is a more robust linear fitting than those performed by other common algorithms, such as least squares, because RANSAC can ignore a big amount of erroneous or not corresponding data elements.

The input to the RANSAC algorithm is a set <b><i>S</i></b> of observed data values, or elements, and a parametric model <b><i>M</i></b> which must be fitted to the observations. RANSAC looks randomly for subsets <b><i>s</i></b> &isin; <b><i>S</i></b> of a fixed size <b><i>n</i></b>, which gets a model <b><i>M</i></b> that fits better the whole data set <b><i>S</i></b>.

With each subset <b><i>s</i></b>, a model fitting is performed, obtaining the parameters for the model <b><i>M</i></b> that fit it best to the elements of the subset. If this succeeds, the algorithm counts the number of elements of the set <b><i>S</i></b> that fit with the new model.

After testing a fixed number <b><i>k</i></b> of random subsets, the algorithm stops, and returns the parameters of the model <b><i>M</i></b> that make it fit the most elements of <b><i>S</i></b>.

To create a RANSAC iterator, the class QVRANSAC should be extended, instantiating the Element and Model template parameters with the type or class for the observed data values, and the model, respectively. The following example defines a RANSAC iterator that will fit a line (represented as an object derived from class Line) over a set of points (represented as objects derived from class QPoint):

@code
// We create the class for the fitting model
class Line
    {
    [...]
    public:
        Line()					{ [...] };
        Line(const QPoint, const QPoint)	{ [...] };
        double distance(const QPoint) const	{ return [...]; }
    };

// And a subclass extending class QVRANSAC
class myRANSAC: public QVRANSAC<QPoint, Line>
    {
    private:
        double maximalDistance;

    public:
        myRANSAC(const QList<QPoint> &observedPoints, const double maximalDistance):
            QVRANSAC< QPoint, Line>(2, 10), maximalDistance(maximalDistance)
            {
            foreach(QPoint point, observedPoints)
                addElement(point);
            }

        const bool fit(const QList<QPoint> &testInliers, Line &model)
            {
            model = Line(testInliers.first(), testInliers.last());
            return true;
            };

        const bool test(const Line &model, const QPoint &point)
            { return model.distance(point) < maximalDistance; };
    };

@endcode

The constructor should call QVRANSAC constructor, providing the size of the subsets <b><i>n</i></b>, and the minimum number of points that a model should fit, from the whole set <b><i>S</i></b>, to be considered a valid model. In this case, only 2 points are needed to create a line, and we will require 10 points fitting in the line to consider it a proper line.

Value <i>maximalDistance</i> will be used to establish the maximal distance between a point and a line, to consider that point as fitting in the line.
The parameter <i>observedPoints</i> is the list of observed data values, points in this case. The constructor myRANSAC adds them to the RANSAC search using the function @ref addElement.

Methods @ref fit and @ref test are declared as <i><b>virtual</b></i> in QVRANSAC, and must be implemented for class myRANSAC. Method @ref fit must contain the code to generate a line model from a subset of the observed values <b><i>s</i></b>. Method @ref test must be able to perform element-model fitting test. Once created the RANSAC class, extending class QVRANSAC, the search must be initiated:

@code
[...]
QList<QPoint> observedData;
observedData.append(QPoint(10,20));
observedData.append(QPoint(20,50));
[...]

int maxIterations = 100;
myRANSAC samplerConsensus(observedData, 1.5);
if (samplerConsensus.iterate(maxIterations))
    {
    Line line = samplerConsensus.getBestModel();
    std::cout << "Found regression line." << std::endl;
    }
else
    std::cout << "A line couldn't be fitted to the data, in " << maxIterations << " iterations.";
[...]

@endcode

The @ref iterate method starts a RANSAC search over of a maximum number of random subsets from <b><i>S</i></b>. It returns true when the search is successful, meaning that a line, closer than 1.5 units to at least 10 sample points from the <i>observedData</i> set was found by the algorithm, in exactly 100 tries. Else it will return false.

The maximum number of iterations (aka, number <b><i>k</i></b> of subsets of <i>observedData</i>to test) should be small enough to stop the search if the probability of finding a good fitting subset <b><i>s</i></b> becomes low. It should be established upon the probability that a valid model would fit a random element of the set <b><i>S</i></b>.

@section References
Martin A. Fischler and Robert C. Bolles. <a href="http://portal.acm.org/citation.cfm?doid=358669.358692">Random Sample Consensus: A Paradigm for Model Fitting with Applications to Image Analysis and Automated Cartography</a>. <i>Comm. of the ACM 24: 381–395.</i>

@see QVPROSAC

@ingroup qvstatistics
*/
template <typename Element, typename Model> class QVRANSAC
    {
    protected:
        int sampleSetSize, minInliers, iteration;

        // To use after initialization
        QList< Element > elements;
        bool continueCondition;

        // To return to the user.
        QList<Element> bestInliers;
        Model bestModel;

        virtual bool init()
            {
            // Check if there are enough in-liners to work.
            if (elements.size() < sampleSetSize)
                return continueCondition = false;
            else
                return continueCondition = true;
            }


        virtual const QList< Element > getNewTentativeInliersSet()
            {
			QVector<int> indexes;
			indexes.reserve(this->sampleSetSize);

            for (int i = 0; i < this->sampleSetSize; i++)
				{
				int index = RANDOM(0, this->elements.size()-1);
				// Do not include the same element twice.
				while( indexes.contains(index) )
					index = RANDOM(0, this->elements.size()-1);

                //result.append(this->elements.at( index ));
				indexes << index;
				}

            QList< Element > result;
			result.reserve(indexes.count());
			foreach(int index, indexes)
                result << this->elements.at( index );

            return result;
            }

    public:
        /// @brief Constructor for QVRANSAC class
        ///
        /// Because QVRANSAC is a pure virtual class, this constructor should only be called from the constructor of
        /// its subclasses.
        /// @param sampleSetSize size of the subsets <i><b>s</b></i> to be used for model fitting.
        /// @param minInliers minimum number of sample data for a model to fit, to be considered a valid model.
        QVRANSAC(const int sampleSetSize, const int minInliers):sampleSetSize(sampleSetSize), minInliers(minInliers) { }

        /// @brief Generate a model from a set of observations
        ///
        /// This method should be implemented by subclasses of QVRANSAC with the code
        /// to generate a model, from a set of sample data.
        /// @param elementList list of test inliers.
        /// @param model model to store parameters fitting the observed elements.
        /// @returns true if model fitting was successful, for the elementList set of observations, Else false.
        virtual bool fit(const QList<Element> &elementList, Model &model) = 0;

        /// @brief Check if an observation fits in a model.
        ///
        /// This method should be implemented by subclasses of QVRANSAC with the code to
        /// check if a sample data fits in a generated model,
        /// @param element element.
        /// @param model model.
        /// @returns true if the observation fits in the model, else false.
        virtual bool test(const Model &model, const Element &element) = 0;

        /// @brief Adds a data sample to the observations set.
        ///
        /// This method should be called before performing any search with the function @ref iterate.
        ///
        /// @param element element.
        void addElement(const Element &element)					{ elements.append(element); }

        /// @brief Gets the best model obtained in a search.
        ///
        /// This method should be called after performing a search with the function @ref iterate.
        ///
        /// @Returns the best model obtained in a search, after calling the @ref init() method.
        const Model & getBestModel() const					{ return bestModel; }

        /// @brief Gets the data elements matching with the best model.
        ///
        /// This method should be called after performing a search with the function @ref iterate.
        /// It will return the data elements from the observations set, matching with the best model.
        /// @returns data elements matching with the best model obtained in a search.
        const QList<Element> & getBestInliers() const				{ return bestInliers; }

        /// @brief Gets the number of iterations performed in a search.
        ///
        /// This method should be called after performing a search with the function @ref iterate.
        /// It will return the number of random sets tested for model fitting in a RANSAC search.
        /// @returns number of sets tested in the ransac search.
        int getIterations() const						{ return iteration; }

        /// @brief Starts a RANSAC search.
        ///
        /// This method will perform a random search over the elements of the observations set, to
        /// find a model that fits a given number of elements from that set, specified in the
        /// constructor of the RANSAC object.
        /// @returns true if a suitable model, that fits in a minimum number of observations specified
        /// in the construction of the RANSAC object, was found, else false.
        bool iterate(const int maxIterations)
            {
            if (!init())
                return false;

            iteration = 0;

            while(continueCondition && (iteration++) < maxIterations)
                {
                // Get new feasible maybe model.
                Model tentativeModel;

                // If no feasible model was found, continue with the next tentative set.
                if (!fit(getNewTentativeInliersSet(), tentativeModel))
                    continue;

                // Else, get consensus set.
                QList<Element> inliersSet;
                foreach (Element element, elements)
                    if (test(tentativeModel, element))
                        inliersSet.append(element);

                // Get consensus model.
                if (inliersSet.size() >= minInliers )
                    {
                    fit(inliersSet, tentativeModel);
                    bestModel = tentativeModel;
                    bestInliers = inliersSet;
                    return true;
                    }
                }

            return false;
            }
    };

/*!
@class QVPROSAC qvsampleconsensus.h qvmath/qvsampleconsensus.h
@brief Implementation of PROSAC, an extension to RANSAC (see @ref QVRANSAC)

This class implements PROSAC, a robust statistical model fitting algorithm.

PROSAC is a more sophisticated and efficient version of RANSAC. The latter is described in the documentation of the class @ref QVRANSAC, which is an implementation of that algorithm for the QVision.

PROSAC can handle heuristic information about the probability that a sample data could fit in a valid model. When picking random samples from the observations set, sample data with high heuristic value is more likely to be chosen, increasing the probability of finding a good sample set that would fit into a valid model.

This makes PROSAC to obtain a fitting model generally faster, trying less random subsets than RANSAC. In practice, with an adequate heuristic function for the sample data, PROSAC can be up to 100 times faster than RANSAC.

Usage of the class @ref QVPROSAC is similar to @ref QVRANSAC. The only difference is at the function @ref addElement, which now takes two input parameters: the sample data, and a numeric heuristic value, which will penalize or benefit the sample data at the random selection of the PROSAC algorithm.

The algorithm is programmed to choose with more probability sample data's with a low heuristic value.

@section References
Chum, Ondřej, Matas, Jiř&iacute;. <a href="http://portal.acm.org/citation.cfm?id=1068507.1068918">Matching with PROSAC - Progressive Sample Consensus</a>. <i>Proc. of Conference on Computer Vision and Pattern Recognition (CVPR). Volume 1, Pages 220-226, June, 2005</i>

@see QVRANSAC

@ingroup qvstatistics
*/
template <typename Element, typename Model> class QVPROSAC: public QVRANSAC<Element, Model>
    {
    protected:
        QMap<double, Element > elementsMap;

        #ifndef DOXYGEN_IGNORE_THIS
        virtual const QList< Element > getNewTentativeInliersSet()
            {
            const int maxSize = 2* log(this->getIterations()) / log(2);
            QList< Element > result;

            for (int i = 0; i < this->sampleSetSize; i++)
                result.append(this->elements.at( RANDOM(0, MAX(this->sampleSetSize, maxSize-1)) ));

            return result;
            }

        bool init()
            {
            const QList<double> preferenceList = elementsMap.uniqueKeys();
            for (int i = 0; i < preferenceList.size(); i++)
                this->elements += elementsMap.values(preferenceList.at(i));

            return QVRANSAC<Element, Model>::init();
            }
        #endif

    public:
        /// @brief Constructor for QVPROSAC class
        ///
        /// Because QVPROSAC is a pure virtual class, this constructor should only be called from the constructor of
        /// its subclasses.
        /// @param sampleSetSize size of the subsets <i><b>s</b></i> to be used for model fitting.
        /// @param minInliers minimum number of sample data for a model to fit, to be considered a valid model.
        QVPROSAC(const int sampleSetSize, const int minInliers): QVRANSAC<Element, Model>(sampleSetSize, minInliers) { }

        /// @brief Starts a PROSAC search.
        ///
        /// This method will perform a random search over the elements of the observations set, to
        /// find a model that fits a given number of elements from that set, specified in the
        /// constructor of the RANSAC object.
        /// @returns true if a suitable model, that fits in a minimum number of observations specified
        /// in the construction of the RANSAC object, was found, else false.
        void addElement(const Element &element, const double preference = 0)
            { elementsMap.insertMulti(preference, element); }
    };

#endif
