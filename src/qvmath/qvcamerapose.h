/*
 *	Copyright (C) 2011, 2012. PARP Research Group.
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

#ifndef QVCAMERAPOSE_H
#define QVCAMERAPOSE_H

#include<QV3DPointF>
#include<QVEuclideanMapping3>

/*!
@class QVCameraPose qvmath/qvcamerapos.h QVCameraPose
@brief Class for the camera pose of a view, in a 3D reconstruction.

This class specifies the orientation and location of a camera, in a SfM reconstruction.

It is similar to the class @ref QVEuclideanMapping3.
The main difference is that the camera center in class @ref QVCameraPose is stored explicitally, instead of as an indirect measurement of the translation of the euclidean mapping.

@ingroup qvprojective
*/
class QVCameraPose
	{
	private:
		QVQuaternion orientation;
		QV3DPointF center;

	public:
		/// @brief Default constructor
		///
		/// Creates a new camera pose from its orientation and its center location.
		///
		/// @param q Quaternion representing the orientation of the camera.
		/// @param centre 3D location of the camera center.
		QVCameraPose(const QVQuaternion q = QVQuaternion(), const QV3DPointF &centre = QV3DPointF()):	orientation(q), center(centre)
			{
			Q_ASSERT(orientation.norm2() > 0);
			Q_WARNING(not orientation.containsNaN());
			Q_WARNING(not center.containsNaN());
			}

		/// @brief Default constructor
		///
		/// Creates a new camera pose from its orientation and its center location.
		///
		/// @param q Quaternion representing the orientation of the camera.
		/// @param centre 3D location of the camera center.
		QVCameraPose(const QVVector &v):	orientation(v.mid(0,4)), center(v.mid(4,3))
			{
			Q_ASSERT(orientation.norm2() > 0);
			Q_WARNING(not orientation.containsNaN());
			Q_WARNING(not center.containsNaN());
			}

		/// @brief Convert constructor
		///
		/// Creates a new camera pose from its pin-hole geometry, specified by an euclidean transformation.
		/// This constructor takes as input the 3D euclidean transformation which maps the 3D point location to the homogeneous coordinates of the image 2D points.
		/// This mapping is transformed to the camera pose.
		///
		/// @param e3 euclidean mapping corresponding to the pin-hole camera geometry.
		QVCameraPose(const QVEuclideanMapping3 e3):
				orientation(e3.getRotation()),
				center(e3.getRotation().inverse().rotate( e3.getTranslation() ) * (-1.0))
			{
			Q_ASSERT(orientation.norm2() > 0);
			Q_WARNING(not orientation.containsNaN());
			Q_WARNING(not center.containsNaN());
			}

		/// @brief Convert to 3D euclidean mapping operator
		///
		/// This operator converts the camera pose to the 3D euclidean transformation which maps 3D point locations to 2D homogeneous image point coordinates.
		///
		operator QVEuclideanMapping3 () const
			{
			Q_ASSERT(orientation.norm2() > 0);
			Q_WARNING(not orientation.containsNaN());
			Q_WARNING(not center.containsNaN());

			return QVEuclideanMapping3(orientation, orientation.rotate(center) * (-1.0));		
			}

		/// @brief Convert to compact vector representation operator
		///
		/// This operator obtains a compact vector representation of the camera pose in 7 coordinates:
		/// - 4 for the orientation, parametrized as a quaternion vector.
		/// - 3 for the camera center.
		operator QVVector () const
			{
			Q_ASSERT(orientation.norm2() > 0);
			Q_WARNING(not orientation.containsNaN());
			Q_WARNING(not center.containsNaN());

			QVVector result(7);

			for(int j = 0; j < 4; j++)
				result[j] = orientation[j];

			for(int j = 0; j < 3; j++)
				result[4+j] = center[j];

			return result;
			}

		/// @brief Detect NaN values in the components of the camera pose.
		///
		/// @return true if either the components of the orientation quaternion or the center point contain a NaN value.
		bool containsNaN()	const	{ return orientation.containsNaN() or center.containsNaN(); }

		/// @brief Compare equal operator
		///
		/// @return true if the orientation and the camera center of both camera poses is equal.
		bool operator==(const QVCameraPose &other) const
			{
			Q_ASSERT(orientation.norm2() > 0);
			Q_WARNING(not orientation.containsNaN());
			Q_WARNING(not center.containsNaN());

			return (orientation == other.orientation) and (center == other.center);
			};

		/// @brief Compare not equal operator
		///
		/// @return true if the orientation and the camera center of both camera poses is equal.
		bool operator!=(const QVCameraPose &other) const
			{
			Q_ASSERT(orientation.norm2() > 0);
			Q_WARNING(not orientation.containsNaN());
			Q_WARNING(not center.containsNaN());

			return (orientation != other.orientation) or (center != other.center);
			};

		/// @brief Orientation of the camera pose.
		///
		/// @return A quaternion vector representing the camera pose orientation.
		QVQuaternion getOrientation()	const	{ return orientation; }

		/// @brief Center of the camera pose.
		///
		/// @return A 3D point corresponding to the camera center.
		QV3DPointF getCenter()		const	{ return center; }

		/// @brief Projects a 3D point at the image plane for the camera pose.
		///
		/// @param p3D 3D point to project.
		/// @return A 2D image point corresponding to the projection of the 3D point.
		QPointF project(const QV3DPointF &p3D)		const
			{
			Q_ASSERT(orientation.norm2() > 0);
			Q_WARNING(not orientation.containsNaN());
			Q_WARNING(not center.containsNaN());

			return orientation.rotate(p3D - center);
			}

		/// @brief Obtains the coordinates for a 3D point, regarding the camera pose coordinate system.
		///
		/// @param p3D 3D point.
		/// @return 3D point coordinates, regarding the camera coordinate reference.
		QV3DPointF toCameraReferenceCoordinates(const QV3DPointF &p3D)		const
			{
			Q_ASSERT(orientation.norm2() > 0);
			Q_WARNING(not orientation.containsNaN());
			Q_WARNING(not center.containsNaN());

			return orientation.rotate(p3D - center);
			}

		/// @brief Cast to a pin-hole projection matrix.
		///
		/// @return A rotation-translation matrix \f$ R[I|-C] \f$, where \f$ R \f$ is the orientation of the camera,
		/// and \f$ C \f$ is the center location of the camera.
		QVMatrix toProjectionMatrix() const
			{
			Q_ASSERT(orientation.norm2() > 0);
			Q_WARNING(not orientation.containsNaN());
			Q_WARNING(not center.containsNaN());

			QVMatrix Rt = QVMatrix::identity(4);
			const QVMatrix R = orientation.toRotationMatrix();
			const QV3DPointF t = orientation.rotate(-center);
			
			for (int i = 0; i < 3; i++)
				{
				for (int j = 0; j < 3; j++)
					Rt(i,j) = R(i,j);
				Rt(i,3) = t[i];
				}

			return Rt;
			}

		/// @brief Composes two camera poses.
		///
		/// @param Operand camera pose for the composition.
		/// @see compose
		QVCameraPose operator*(const QVCameraPose &other) const		{ return compose(other); 	};

		/// @brief Composes two camera poses.
		///
		QVCameraPose compose(const QVCameraPose &other) const
			{
			Q_ASSERT(other.orientation.norm2() > 0);
			Q_ASSERT(orientation.norm2() > 0);

			Q_WARNING(not orientation.containsNaN());
			Q_WARNING(not center.containsNaN());
			Q_WARNING(not other.orientation.containsNaN());
			Q_WARNING(not other.center.containsNaN());

			/*std::cout << "x1" << std::endl;
			Q_ASSERT((orientation * other.orientation).norm2() > 0);

			std::cout << "x2" << std::endl;

			const QVQuaternion q = other.orientation.inverse();

			std::cout << "x3" << std::endl;*/

			const QVCameraPose result(orientation * other.orientation, other.center + other.orientation.inverse().rotate(center));

			#ifdef DEBUG
			if (not (orientation.containsNaN() or center.containsNaN() or other.orientation.containsNaN() or other.center.containsNaN() ) )
				Q_ASSERT( relativeEuclideanDistance(toProjectionMatrix() * other.toProjectionMatrix(), result.toProjectionMatrix()) < 1e-3);
			#endif // DEBUG

			//std::cout << "x4" << std::endl;
			return result;
			}

		/// @brief Provides the inverse of the camera pose.
		///
		#ifdef QVMATRIXALGEBRA_AVAILABLE
		QVCameraPose inverse() const
			{
			Q_ASSERT(orientation.norm2() > 0);
			Q_WARNING(not orientation.containsNaN());
			Q_WARNING(not center.containsNaN());

			const QVCameraPose result(orientation.inverse(), -orientation.rotate(center));

			#ifdef DEBUG
			if (not (orientation.containsNaN() or center.containsNaN() ) )
				Q_ASSERT( relativeEuclideanDistance(toProjectionMatrix().inverse(), result.toProjectionMatrix()) < 1e-6);
			#endif // DEBUG

			return result;
			}
		#endif // QVMATRIXALGEBRA_AVAILABLE
	};

#include <QMetaType>
Q_DECLARE_METATYPE(QVCameraPose);

#endif
