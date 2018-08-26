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

#include <QVVectorMap>

#define	SIGNATURE(Vector)	(Vector.sum()/sqrt((long double) (Vector.size())))

void QVVectorMap::add(const QVVector &vector)
	{
	insertMulti(SIGNATURE(vector), vector);
	}

QVVectorMap::QVVectorMap(const QList<QVVector> & vectors): QMap<double, QVVector>()
	{
	foreach(QVVector vector, vectors)
		add(vector);	
	};

QList<QVVector> QVVectorMap::getClosestVectors(const QVVector actualVector, const QList<QVVector> &vectors, const int n)
	{
	QMap<double, QVVector> hash;
	foreach(QVVector v, vectors)
		hash.insertMulti((v - actualVector).norm2(), v);
	return hash.values().mid(0,n);
	}

QVVector QVVectorMap::getClosestVector(const QVVector &vector) const
	{
	if (size() == 0)
		return QVVector();
	else
		return getClosestVectors(vector, 1).first();
	}

QList<QVVector> QVVectorMap::getClosestVectors(const QVVector &vector, const int maxVectors) const
	{
	const double vector_signature = SIGNATURE(vector);

	// Trivial cases
	if (size() == 0 || maxVectors <= 0)
		return QList<QVVector>();

	if (size() <= maxVectors)
		return values();
	
	// Special threatment of the first element
	int t = 0;
	QMap<double, QVVector> closestVectors;
	for(QMap<double, QVVector>::const_iterator i = constBegin(); t < maxVectors; ++t, ++i)
		closestVectors.insertMulti((vector - i.value()).norm2(), i.value());

	// Iterate to the left of the pivot element
	double last_key = (--(closestVectors.end())).key();

	// Locate the pivot in the closest vector
	QMap<double, QVVector>::const_iterator pivot = lowerBound(SIGNATURE(vector));
	if (pivot == constEnd())
		--pivot;

	// Iterate to the left of the pivot element.
	if (pivot != constBegin())
		for (QMap<double, QVVector>::const_iterator i = pivot; i != constBegin(); --i)
			{
			if (ABS(i.key() - vector_signature) >= last_key)
				break;

			const double actualDistance = (vector - i.value()).norm2();
			if (actualDistance < last_key)
				{
				closestVectors.take(last_key);
				closestVectors.insertMulti(actualDistance, i.value());
				last_key = (--(closestVectors.end())).key();
				}
			}

	// Iterate to the right of the pivot element.
	for (QMap<double, QVVector>::const_iterator i = pivot + 1; i != constEnd(); ++i)
		{
		if (ABS(i.key() - vector_signature) >= last_key)
			break;

		const double actualDistance = (vector - i.value()).norm2();
		if (actualDistance < last_key)
			{
			closestVectors.take(last_key);
			closestVectors.insertMulti(actualDistance, i.value());
			last_key = (--(closestVectors.end())).key();
			}
		}

	return closestVectors.values();
	}
