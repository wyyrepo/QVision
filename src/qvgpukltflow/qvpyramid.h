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

#ifndef QVPYRAMID_H
#define QVPYRAMID_H

#include "v3d_gpubase.h"
#include "v3d_gpuflow.h"
#include "v3d_gpupyramid.h"
#include "v3d_utilities.h"

#include <QVImage>

using namespace V3D_GPU;
using namespace V3D;

#ifndef DOXYGEN_IGNORE_THIS
/*!
@class QVPyramid qvgpukltflow/qvpyramid.h QVPyramid
@brief Obtain a pyramid image scale with the GPU.

@ingroup qvgpukltflow
*/
class QVPyramid
{

public:
    // Constructors
    /// @brief Default constructor
    /// Do nothing.
    QVPyramid();

    /// @brief Copy constructor.
    ///
    /// This method initializes and configures a pyramid with parameters below.
    /// @param width number of columns of the first level image
    /// @param height number of rows of the first level image
    /// @param nLevels number of levels of the pyramid
    QVPyramid( int width, int height, int nLevels);


    // Destructors
    /// @brief Default destructor
    /// Deallocate the pyramid from the GPU
    ~QVPyramid ();

    /// @brief Build a image pyramid.
    ///
    /// This method builds a image pyramid from one image.
    /// @param image image to use
    void buildPyramid ( const QVImage<uChar,1> &image) ;

    /// @brief Get the texture identifier of the pyramid
    ///
    /// @return the texture identifier of the pyramid
    unsigned int getID() const;

    /// @brief Get the width of the first level image
    ///
    /// @return the width of the first level image
    int getWidth () const;

    /// @brief Get the height of the first level image
    ///
    /// @return the height of the first level image
    int getHeight() const;

    /// @brief Get from the GPU the images for all levels
    ///
    /// This method extracts from the GPU memory the images of the pyramid and
    /// stores them into the QVPyramid object.
    void getFromGPU ();

    /// @brief Get the image of one level of the pyramid.
    ///
    /// The method getFromGPU has to be called before.
    /// @param level level of the image
    /// @return the image of one level of the pyramid.
    QVImage<sFloat,1> getImage (int level) const;

private:

    PyramidWithDerivativesCreator *pyr;
    int width, height;
    QVImage<sFloat,1> * pyr_images;
};

#endif // DOXYGEN_IGNORE_THIS
#endif // QVPYRAMID_H
