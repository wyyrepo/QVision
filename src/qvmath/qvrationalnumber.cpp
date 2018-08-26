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

#include <iostream>
#include <qvmath/qvrationalnumber.h>

std::ostream & operator<< (std::ostream &os, const QVRationalNumber &factInteger )
{
    os << "QVRationalNumber(" << (double) factInteger;

    QList<int> keys = factInteger.keys();
    if (keys.size() > 0)
    {
        os << " = " << keys.at(0) << "^" << factInteger[keys.at(0)];
        for (int i = 1; i < keys.size(); i++)
            if (factInteger[keys.at(i)] != 0)
                os << " + " << keys.at(i) << "^" << factInteger[keys.at(i)];
    }
    os << ")";

    return os;
}

QVRationalNumber QVRationalNumber::operator*(const QVRationalNumber &factInteger) const
{
    QVRationalNumber result = *this;
    QList<int> keys = factInteger.keys();

    foreach(int key, factInteger.keys())
        if (result.contains(key))
            result[key] += factInteger[key];
        else
            result.insert(key,factInteger[key]);

    return result;
};

QVRationalNumber QVRationalNumber::operator/(const QVRationalNumber &factInteger) const
{
    QVRationalNumber result = *this;
    QList<int> keys = factInteger.keys();

    foreach(int key, factInteger.keys())
        if (result.contains(key))
            result[key] -= factInteger[key];
        else
            result.insert(key,-factInteger[key]);

    return result;
};

QVRationalNumber::operator double() const
{
    double result = 1;
    foreach(int key, keys())
        result *= pow(key, operator[](key));
    return result;
}

void QVRationalNumber::mult(const int integer)
{
    const int maxIndex = (int)sqrt(integer);

    int remain = integer;
    for (int i = 2; i <= maxIndex; i++)
        if (remain % i == 0)
        {
            if (!contains(i))
                insert(i,0);
            while(remain % i == 0)
            {
                operator[](i)++;
                remain = remain/i;
            }
        }
        else if (remain == 1)
            break;

    if (remain != 1) {
        if (!contains(remain))
            insert(remain,1);
        else
            operator[](remain)++;
    }
};

