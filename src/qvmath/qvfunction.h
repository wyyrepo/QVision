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

#ifndef QVFUNCTION_H
#define QVFUNCTION_H

/*!
@class QVFunction qvmath/qvfunction.h QVFunction
@brief Base class for function objects.

This class can be used to create function class types. Objects derived from this class will wrap functions so they can be provided as parameters to other methods or procedures.

These objects can be used as any C++ function, using their overloaded function operator (). This operator calls to the virtual method <i>evaluate</i>, which must be implemented by subclasses of @ref QVFunction to contain the code of the function:

@code
[...]
class FactorialFunction: public QVFunction<int, int>
	{
	public:
		int evaluate(const int &value)
			{
			int accum = 1;
			for (int i = 0; i < value; i++)
				accum *= i;
			return accum;
			}
	};

[...]

int main()
	{
	[...]
	FactorialFunction factorial;
	std::cout << "10! = " << factorial(10) << std::endl;
	[...]
	}
@endcode

Function objects can contain parametrization data to evaluate the function, besides each given input value:

@code
class QuadraticFunction: public QVFunction<double, double>
	{
	private:
		const double a, b, c;

	public:
		QuadraticFunction(const double a, const double b, const double c):
			QVFunction<double, double>(), a(a), b(b), c(c)
			{ }

		double evaluate(const double &x)
			{ return a*x*x + b*x + c; }
	};
@endcode

@ingroup qvnumericalanalysis
*/
#include <QList>
template <typename Input, typename Output> class QVFunction
	{
	public:
		QVFunction()	{ }
		virtual ~QVFunction()	{ }

		/// @brief Virtual method implementing the code for the function evaluation.
		///
		/// This virtual method must be redefined at any @ref QVFunction subclass.
		/// It should implement the code for the function evaluation.
		///
		/// @param input Input value provided for its evaluation.
		virtual Output evaluate(const Input &input)	= 0;

		/// @brief Operator to evaluate the function
		///
		/// This operator calls to the @ref evaluate method, to obtain the return value of the function.
		///
		/// @param input Input value provided for its evaluation.
		/// @see evaluate
		Output operator()(const Input &input)	{ return evaluate(input); }


		/// @brief Function map operator
		///
		/// This operator maps a list of inputs, to their corresponding outputs.
		///
		/// @param input List of input values provided for their evaluation
		/// @see map
		QList<Output> operator()(const QList<Input> &input)	{ return map(input); }

		/// @brief Maps a list of input elements, to the outputs for those elements
		///
		/// This operator calls the @ref evaluate method for each element of the input list.
		///
		/// @param input List of input values provided for their evaluation
		/// @return A list containing the outputs of the function for the values contained in the inputs list.
		/// 	This function preserves the order of the outputs, regarding the order of their corresponding inputs at the input list.
		/// @see evaluate
		QList<Output> map(const QList<Input> &inputs)
			{
			QList<Output> result;
			foreach(Input input, inputs)
				result.append(evaluate(input));
		
			return result;
			}
	};
#endif
