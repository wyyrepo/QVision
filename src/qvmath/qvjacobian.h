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

#ifndef QVJACOBIAN_H
#define QVJACOBIAN_H

/*!
@class QVJacobian qvmath/qvjacobian.h QVJacobian
@brief Class to create jacobian functions.

This class can be used to create Jacobian function class types. Objects derived from this class are function objects, that map vector to matrix objects.

The Jacobian function objects must be initialized with a \f$ R^n \to R^m \f$ function, which must be provided in a @ref QVFunction object. The Jacobian object function will use the method @ref qvEstimateJacobian to obtain a numerical approximation of the Jacobian matrix for that vector function.

An example usage of these objects is the following:

@code
[...]
class ExampleVectorFunction: public QVFunction<QVVector, QVVector>
	{
	public:
		QVVector evaluate(const QVVector &v) const
			{
			[...]
			}
	};

[...]

int main()
	{
	[...]
	ExampleVectorFunction f;
	QVJacobian eJacobian(f);

	QVVector x = QVVector::random(10);
	std::cout << "x = " << x << std::endl;
	std::cout << "f(x) = " << f(x) << std::endl;
	std::cout << "Jacobian of f(x) = " << eJacobian(x) << std::endl;
	[...]
	}
@endcode

@ingroup qvnumericalanalysis
*/

#include <qvmath/qvnumericalanalysis.h>
class QVJacobian: public QVFunction<QVVector, QVMatrix>
        {
        private:
		QVFunction<QVVector, QVVector> *function;

                QVMatrix evaluate(const QVVector &x) const
                        {
                        return qvEstimateJacobian(*function, x);
			}
			
	public:

		/// @brief Jacobian function constructor
		///
		/// Creates a new Jacobian function, from a vector function.
		///
		/// @param function The vector function.
		QVJacobian(QVFunction<QVVector, QVVector> &function): QVFunction<QVVector, QVMatrix>(), function(&function) { }
	};
#endif
