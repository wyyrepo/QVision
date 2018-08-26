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

#ifndef QVKEYPOINT_H
#define QVKEYPOINT_H

#include <QPointF>

/*!
@class QVKeypoint qvip/qvkeypoint.h QVKeypoint
@brief Class for image key point data-type.

The pixel location, the scale and the orientation identify several kinds of image features.
This class models these image features.

@ingroup qvip
*/
class QVKeypoint
    {
    private:
        double _x, _y, _scale, _orientation;

    public:

        /// @brief Default constructor
        ///
        /// Creates a new keypoint location for an image feature.
        ///
        /// @param x horizontal image coordinate for the image feature.
        /// @param y vertical image coordinate for the image feature.
        /// @param scale scale of the image feature.
        /// @param orientation orientation of the image feature.
        QVKeypoint(const double x = 0.0, const double y = 0.0, const double scale = 0.0, const double orientation = 0.0):
            _x(x), _y(y), _scale(scale), _orientation(orientation)
            { }

        /// @brief Copy constructor
        ///
        /// Creates a new keypoint location from another.
        ///
        /// @param x horizontal image coordinate for the image feature.
        /// @param y vertical image coordinate for the image feature.
        /// @param scale scale of the image feature.
        /// @param orientation orientation of the image feature.
        QVKeypoint(const QVKeypoint &other): _x(other._x), _y(other._y), _scale(other._scale), _orientation(other._orientation)
            { }

        QVKeypoint(const QPointF &location, const double scale = 0.0, const double orientation = 0.0):
            _x(location.x()), _y(location.y()), _scale(scale), _orientation(orientation)
            { }

        /// @brief Point conversion operator.
        /// Gets the location of the image feature in a QPointF object.
        operator QPointF()		const { return location(); }

        /// @brief Gets the location of the image feature.
        /// Gets the location of the image feature in a QPointF object.
        QPointF	location()		const { return QPointF(_x,_y); }

        /// @brief Horizontal coordinate of the image feature
        double &x()			{ return _x; }

        /// @brief Horizontal coordinate of the image feature
        double x()		const { return _x; }

        /// @brief Vertical coordinate of the image feature
        double &y()			{ return _y; }

        /// @brief Vertical coordinate of the image feature
        double y()		const { return _y; }

        /// @brief Scale of the image feature
        double &scale()			{ return _scale; }

        /// @brief Scale of the image feature
        double scale()		const { return _scale; }

        /// @brief Orientation of the image feature
        double &orientation()		{ return _orientation; }

        /// @brief Orientation of the image feature
        double orientation()	const { return _orientation; }
    };

#endif
