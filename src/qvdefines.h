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

#ifndef QVDEFINES_H
#define QVDEFINES_H

// Include a small set of Qt classes, which will be declared as basic types for the metatypes.
#include <QMetaType>
#include <QList>
#include <QVector>
#include <QPoint>
#include <QPointF>
#include <QRect>
#include <QPair>
#include <limits>
#include <iso646.h>
#include <iostream>

#if !defined(Q_WARNING)
#  ifndef QT_NO_DEBUG
#    define Q_WARNING(cond) { if (not (cond)) std::cerr << "WARNING: condition \"" << #cond << "\" in file \"" << __FILE__ << "\", line " << __LINE__ << " does not hold" << std::endl; }
#  else
#    define Q_WARNING(cond) qt_noop()
#  endif
#endif

#if !defined(Q_WARNING_X)
#  ifndef QT_NO_DEBUG
#    define Q_WARNING_X(cond,where,what) { if (not (cond)) std::cerr << "WARNING: in file \"" << __FILE__ << "\", line " << __LINE__ << ": " << what << std::endl; }
#  else
#    define Q_WARNING_X(cond) qt_noop()
#  endif
#endif

#if !defined(Q_CHECKPOINT)
#  ifndef QT_NO_DEBUG
#    define Q_CHECKPOINT { std::cout << " (CHKPT@" << __FILE__ << ":" << __LINE__ << ") "; }
#  else
#    define Q_CHECKPOINT qt_noop()
#  endif
#endif

/*
#if !defined(Q_WARNING_X)
#  ifndef QT_NO_DEBUG
#    define Q_ASSERT_X(cond, where, what) ((!(cond)) ? qt_assert_x(where, what,__FILE__,__LINE__) : qt_noop())
#  else
#    define Q_ASSERT_X(cond, where, what) qt_noop()
#  endif
#endif
*/

typedef unsigned char 	uChar;		// Ipp8u	1 bytes
typedef unsigned short 	uShort;		// Ipp16u	2 "
typedef unsigned int 	uInt;		// Ipp32u	4 "
typedef signed char 	sChar;		// Ipp8s	1 ...
typedef signed short 	sShort;		// Ipp16s	2
typedef signed int 	sInt;		// Ipp32s	4
//typedef __INT64 	sLong;		// Ipp64s	8 (not an estandar type)
//typedef __UINT64 	uLong;		// Ipp64u	8 (not an estandar type)
typedef float 		sFloat;		// Ipp32f	4
typedef double 		sDouble;	// Ipp64f	8

// Other type definitions

/*!
Type for a pair of points.
@ingroup qvmath
 */
typedef QPair<QPointF, QPointF> QPointFMatching;

// Qt metatypes definitions: QVision defined types must be metatyped in their respective header files.
// Qt's and C++'s metatypes must be listed below.
Q_DECLARE_METATYPE(sChar);
Q_DECLARE_METATYPE(QVector<sFloat>);
Q_DECLARE_METATYPE(QVector<sDouble>);
Q_DECLARE_METATYPE(QList<sInt>);
Q_DECLARE_METATYPE(QList<sFloat>);
Q_DECLARE_METATYPE(QList<sDouble>);
Q_DECLARE_METATYPE(QList<QPoint>);
Q_DECLARE_METATYPE(QList<QPointF>);
Q_DECLARE_METATYPE(QList<QRect>);
Q_DECLARE_METATYPE(QList< QList< QPoint > >);
Q_DECLARE_METATYPE(QList< QList< QPointF > >);

Q_DECLARE_METATYPE(QPointFMatching);
Q_DECLARE_METATYPE(QList<QPointFMatching>);

#include <QColor>
const QColor qvColors[] = {
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
		};

std::ostream& operator << (std::ostream &os, const QPointF &point);
std::ostream& operator << (std::ostream &os, const QPoint &point);
std::ostream& operator << (std::ostream &os, const QPointFMatching &matching);

uint qHash(const double &value);
uint qHash(const QPointF &point);
uint qHash(const QPoint &point);

long long getMicroseconds();

#ifdef QVOCTAVE
	// This is to avoid an ugly dissambiguation error for operator == which g++ reports when compiling the Octave module.
	#include <QLocale>
	inline bool operator==(const QLocale::NumberOptions & a,const QLocale::NumberOptions & b) {
	return static_cast<int>(a) == static_cast<int>(b);
	}
#endif // QVOCTAVE

#ifdef QVIPP
#include <ipp.h>
Q_DECLARE_METATYPE(IppiMaskSize);
Q_DECLARE_METATYPE(IppCmpOp);
Q_DECLARE_METATYPE(IppRoundMode);
#endif // QVIPP

#ifndef DOXYGEN_IGNORE_THIS
// Compose "Swiss army knife" template function.
// This function inserts each element from the input container 'containerA' into the 'containerB', which returns on output.
// The elements of 'containerA' are converted consequently prior to their insertion in 'containerB'
// This function is useful for example:
// - To create a vector composing the elements contained in a QList, assuming that the type of these elements provides a casting operator to the type QVVector.
// - To convert all the elements contained in a QList to another type, assuming that the original type provides a casting operator to the second type.
template < template<typename T> class TypeContainer, typename TypeElement, typename TypeIndex>
QVector< QPair<TypeElement, TypeElement> > compose(	const TypeContainer< QPair<TypeIndex, TypeIndex> > &pairIndexes,
													const TypeContainer<TypeElement> &containerA,
													const TypeContainer<TypeElement> &containerB)
	{
	QVector< QPair<TypeElement, TypeElement> > result(pairIndexes.count());

	TypeIndex i = 0;
	QPair<TypeIndex, TypeIndex> element;
	foreach(element, pairIndexes)
		{
		result[i].first = containerA[element.first];
		result[i].second = containerB[element.second];
		i++;
		}

	return result;
	}

// Compose "Swiss army knife" template function.
// This function inserts each element from the input container 'containerA' into the 'containerB', which returns on output.
// The elements of 'containerA' are converted consequently prior to their insertion in 'containerB'
// This function is useful for example:
// - To create a vector composing the elements contained in a QList, assuming that the type of these elements provides a casting operator to the type QVVector.
// - To convert all the elements contained in a QList to another type, assuming that the original type provides a casting operator to the second type.
template< template< typename T> class ContainerA, typename Element, typename ContainerB> ContainerB compose(const ContainerA<Element> &containerA)
	{
	ContainerB containerB;
	foreach(Element e, containerA)
		containerB << e;
	return containerB;
	}

#endif // DOXYGEN_IGNORE_THIS

#define GLUPERSPECTIVE_SUBSTITUTE

#ifdef GLUPERSPECTIVE_SUBSTITUTE
	#include <GL/glu.h>
	void qvGluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
#else // GLUPERSPECTIVE_SUBSTITUTE
	#define qvGluPerspective gluPerspective
#endif // GLUPERSPECTIVE_SUBSTITUTE

#endif


