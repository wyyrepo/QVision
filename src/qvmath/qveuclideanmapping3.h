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

#ifndef QVEUCLIDEANMAPPING3_H
#define QVEUCLIDEANMAPPING3_H

#include <QVMatrix>
#include <QV3DPointF>
#include <qvmath.h>

/*!
@class QVEuclideanMapping3 qvmath/qveuclideanmapping3.h QVEuclideanMapping3
@brief Class modeling rotation-translation transformations for 3D points.

This class models elements from the E<sub>3</sub> group. These elements are combinations of
translations and rotations in the 3D euclidean space.

Each element from this class contains a quaternion and a 3D point, respectively representing the rotation
and the translation of the elements of the 3D space.

@ingroup qvmath
*/
class QVEuclideanMapping3
	{
	private:
		QVQuaternion	q;
		QV3DPointF	t;

	public:
		/// @brief Default constructor
		QVEuclideanMapping3(): q(), t()	{ }

		/// @brief Copy constructor
		QVEuclideanMapping3(const QVEuclideanMapping3 &other): q(other.q), t(other.t)	{ }

		/// @brief Initialization from a quaternion rotation, and a translation vector
		/// @param q Quaternion for the rotation
		/// @param t 3D point for the translation
		QVEuclideanMapping3(const QVQuaternion &q, const QV3DPointF &t): q(q), t(t)	{ }

		/// @brief Initialization from the components of a quaternion rotation, and a translation vector
		///
		/// @param quatx Coefficient for the <i>i</i> coordinate of the quaternion
		/// @param quaty Coefficient for the <i>j</i> coordinate of the quaternion
		/// @param quatz Coefficient for the <i>k</i> coordinate of the quaternion
		/// @param quatw Coefficient for the real coordinate of the quaternion
		/// @param tx	The <i>x</i> coordinate of the translation
		/// @param ty	The <i>y</i> coordinate of the translation
		/// @param tz	The <i>z</i> coordinate of the translation
		QVEuclideanMapping3(const double quatx, const double quaty, const double quatz, const double quatw,
				const double tx, const double ty, const double tz):
				q(quatx, quaty, quatz, quatw), t(tx, ty, tz)
				{ }

		/// @brief Initialization from the components of a quaternion rotation, and a translation vector
		///
		/// @param v Vector of size 7 containing the coefficients for the <i>i</i>, <i>j</i>, <i>k</i>,
		/// and the real components of the quaternion, and the <i>x</i>, <i>y</i>, <i>z</i> components
		/// of the translation, in that order.
		QVEuclideanMapping3(const QVVector &v): q(v[0], v[1], v[2], v[3]), t(v[4], v[5], v[6])
			{ }

		/// @brief Initialization from a rotation-translation matrix
		///
		/// @param Rt The rotation/translation matrix. It is equal to \f$ [R|t] \f$, where \f$ R \f$ is the
		/// rotation matrix, and \f$ t \f$ is the translation vector.
		QVEuclideanMapping3(const QVMatrix &Rt);

		/// @brief Applies the euclidean transformation for the point
		///
		/// @param X Point to apply the euclidean rotation-translation transformation
		QV3DPointF apply(const QV3DPointF &X) const 
			{
			return q.rotate(X) + t;
			}

		/// @brief Cast to a 7-size vector.
		///
		/// @return Vector of size 7 containing the coefficients for the <i>i</i>, <i>j</i>, <i>k</i>,
		/// and the real components of the quaternion, and the <i>x</i>, <i>y</i>, <i>z</i> components
		/// of the translation, in that order.
		operator QVVector() const
			{
			QVVector result(7);

			result[0] = q[0];
			result[1] = q[1];
			result[2] = q[2];
			result[3] = q[3];

			result[4] = t[0];
			result[5] = t[1];
			result[6] = t[2];

			return result;
			}

		/// @brief Equality compare operator
		///
		bool operator ==(const QVEuclideanMapping3 &other) const
			{
			return (q == other.q and t == other.t);
			}

		/// @brief Inequality compare operator
		///
		bool operator !=(const QVEuclideanMapping3 &other) const
			{
			return (q != other.q or t != other.t);
			}

		/// @brief Cast to a Rotation-translation matrix.
		///
		/// @return A rotation translation matrix \f$ [R|t] \f$, where \f$ R \f$ is the rotation matrix,
		/// and \f$ t \f$ is the translation vector.
		QVMatrix toRotationTranslationMatrix() const
			{
			QVMatrix Rt = QVMatrix::identity(4);
			const QVMatrix R = q.toRotationMatrix();
			
			for (int i = 0; i < 3; i++)
				{
				for (int j = 0; j < 3; j++)
					Rt(i,j) = R(i,j);
				Rt(i,3) = t[i];
				}

			return Rt;
			}

		/// @brief Returns the rotation quaternion of the mapping
		QVQuaternion	getRotation()		const	{ return q; }

		/// @brief Returns the translation of the mapping
		QV3DPointF	getTranslation()	const	{ return t; }

		/// @brief Sets the rotation quaternion of the mapping
		void	setRotation(const QVQuaternion &other)	{ q = other; }

		/// @brief Sets the translation of the mapping
		void	setTranslation(const QV3DPointF &other)	{ t = other; }

        /// @brief Computes the inverse of the mapping
		///
		QVEuclideanMapping3 inverse() const
			{
			const QVQuaternion qInv = q.inverse();
			return QVEuclideanMapping3(qInv, QV3DPointF(qInv.rotate(t)) * (-1));
			}

		/// @brief Composes two euclidean mappings.
		///
		QVEuclideanMapping3 compose(const QVEuclideanMapping3 &other) const
			{
			return QVEuclideanMapping3(q * other.q, q.rotate(other.t) + t);
			}

		/// @brief Composes two euclidean mappings.
		///
		QVEuclideanMapping3 operator*(const QVEuclideanMapping3 &other) const		{ return compose(other); 	};

		/// @brief Divides an euclidean mapping by another one.
		///
		/// This operator is equivalent to the following code:
		///
		/// @code
		/// this->compose(other.inverse())
		/// @endcode
		///
		QVEuclideanMapping3 operator/(const QVEuclideanMapping3 &other) const		{ return compose(other.inverse()); 	};
	};
#endif
