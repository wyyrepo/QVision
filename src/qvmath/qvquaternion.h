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

#ifndef QVQUATERNION_H
#define QVQUATERNION_H

#include <math.h>
#include <iostream>
#include <QVVector>
#include <QV3DPointF>

class QVMatrix;

/*!
@class QVQuaternion qvmath/qvquaternion.h QVQuaternion
@brief Implementation of <a href="http://en.wikipedia.org/wiki/Quaternion">quaternions</a>.

Quaternions are an extension of the imaginary numbers. They are mostly used to represent rotations in the euclidean 3D space.

@ingroup qvmath
*/

class QVQuaternion: public QVVector
    {
    public:
        //////////////////
        // Constructors

        /// @brief Identity constructor.
        ///
        /// Creates quaternion to identity rotation.
        QVQuaternion();

        /// @brief Axis rotation constructor.
        ///
        /// Creates a quaternion object which rotates around a direction a given angle.
        ///
        /// @param direction quaternion will rotate around this direction.
        /// @param phi quaternion will rotate this angle, given in radians.
        QVQuaternion(const QVVector direction, const double phi);

        /// @brief Construct from a vector.
        ///
        /// Creates a quaternion from a vector of size 4.
        ///
        /// @param source The vector of size 4.
        QVQuaternion(const QVVector &source):QVVector(source) { Q_ASSERT(norm2() > 0); };

        /// @brief Axis rotation constructor.
        ///
        /// Creates a quaternion object which rotates around a direction a given angle.
        ///
        /// @param direction quaternion will rotate around this direction.
        /// @param phi quaternion will rotate this angle, given in radians.
        QVQuaternion(const QVVector direction, float phi);

        /// @brief Direct coordinates constructor.
        ///
        /// Creates a quaternion from its coordinate coefficients.
        ///
        /// @param i Coefficient for the <i>i</i> coordinate
        /// @param j Coefficient for the <i>j</i> coordinate
        /// @param k Coefficient for the <i>k</i> coordinate
        /// @param r Coefficient for the real coordinate
        QVQuaternion(const double i, const double j, const double k, const double r);

        /// @brief Constructor from 3 euler angles
        ///
        /// Creates a quaternion given the three euler angles of the rotation it represents.
        /// @param xAngle Euler angle for the <i>x</i> axis.
        /// @param yAngle Euler angle for the <i>y</i> axis.
        /// @param zAngle Euler angle for the <i>z</i> axis.
        QVQuaternion(const double xAngle, const double yAngle, const double zAngle);

        /// @brief Rotation matrix constructor
        ///
        /// Creates a quaternion from a rotation matrix.
        ///
        /// @param matrix rotation matrix to create the quaternion from
        QVQuaternion(const QVMatrix &matrix);

        /// @brief Quaternion product
        ///
        /// @param quaternion operand for the product
        /// @see quaternionProduct
        QVQuaternion operator*(const QVQuaternion &quaternion) const		{ return quaternionProduct(quaternion); 	};

        /// @brief Copy constructor.
        ///
        /// Creates a quaternion copying its coordinates from a given one.
        ///
        /// @param quaternion quaternion to copy coordinates
        QVQuaternion(const QVQuaternion &quaternion): QVVector(quaternion)	{ }

        /// @brief Gets the quaternion corresponding to a trackball rotation
        ///
        /// Creates a quaternion which rotates given two points at a plane, mapped to a sphere.
        ///
        /// @param p1x first coordinate for first point.
        /// @param p1y second coordinate for first point.
        /// @param p2x first coordinate for second point.
        /// @param p2y second coordinate for second point.
        /// @returns quaternion corresponding to rotate in a sphere from point (p1x, p1y) to (p2x, p2y).
        /// corresponding to this quaternion, and at element (4,4), the unity.
        static QVQuaternion trackball(float p1x, float p1y, float p2x, float p2y);

        /// @brief Combination operation for quaternions
        ///
        /// Creates a quaternion corresponding to combination of rotations corresponding to actual
        /// quaternion and the one received by parameter
        ///
        /// @param quaternion operand in the combining operation.
        /// @returns resulting quaternion.
        QVQuaternion quaternionProduct(const QVQuaternion &quaternion) const;

        /// @brief Gets the Euler angles corresponding to the Quaternion.
        ///
        /// @param xAxis Return variable that will contain the rotation in the <i>x</i> angle for the quaternion.
        /// @param yAxis Return variable that will contain the rotation in the <i>y</i> angle for the quaternion.
        /// @param zAxis Return variable that will contain the rotation in the <i>z</i> angle for the quaternion.
        void toEulerAngles(double &xAngle, double &yAngle, double &zAngle) const;

        /// @brief Gets the rotation matrix corresponding to the Quaternion.
        ///
        /// @return rotation matrix
        QVMatrix toRotationMatrix() const;

        /// @brief Gets the conjugate of the quaternion
        ///
        /// @return The conjugate quaternion.
        QVQuaternion conjugate() const;

        /// @brief Gets the inverse of the quaternion
        ///
        /// @return The inverse quaternion.
        QVQuaternion inverse() const;

        /// @brief Gets the norm2 of the quaternion
        ///
        /// @return The value of the norm 2
        double norm2() const;

        /// @brief Direct vector rotation
        ///
        /// Rotates a 3D Applies the quaternion rotation to a 3D point.
        ///
        /// @returns resulting 3D point.
        QV3DPointF rotate(const QV3DPointF &v) const;

        /// @brief Returns the coordinate for the real component of the cuaternion
        inline double &real()	{ return operator[](3);		}

        /// @brief Returns the coordinate <i>i</i> of the cuaternion
        inline double &i()	{ return operator[](0);		}

        /// @brief Returns the coordinate <i>j</i> of the cuaternion
        inline double &j()	{ return operator[](1);		}

        /// @brief Returns the coordinate <i>k</i> of the cuaternion
        inline double &k()	{ return operator[](2);		}

        /// @brief Sets the coordinate for the real component of the cuaternion
        inline double real() const	{ return operator[](3);		}

        /// @brief Sets the coordinate <i>i</i> of the cuaternion
        inline double i() const		{ return operator[](0);		}

        /// @brief Sets the coordinate <i>j</i> of the cuaternion
        inline double j() const		{ return operator[](1);		}

        /// @brief Sets the coordinate <i>k</i> of the cuaternion
        inline double k() const		{ return operator[](2);		}

        /// @brief Retuns a normalized quaternion.
        QVQuaternion normalizeQuaternion() const;
    };

std::ostream& operator << ( std::ostream &os, const QVQuaternion &quaternion );

#endif

