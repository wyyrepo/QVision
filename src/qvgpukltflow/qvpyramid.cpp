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

#include <QVPyramid>

QVPyramid::QVPyramid(){}

QVPyramid::QVPyramid(int width, int height, int nLevels){

    this->width = width;
    this->height = height;

    this->pyr = new PyramidWithDerivativesCreator ();

    //Allocate GPU memory:
    this->pyr->allocate(width, height, nLevels);

    //Allocate CPU memory:
    this->pyr_images = new QVImage<sFloat,1> [nLevels];
}

void QVPyramid::buildPyramid(const QVImage<uChar, 1> &image) {
    this->pyr->buildPyramidForGrayscaleImage(image.getReadData());
}

void QVPyramid::getFromGPU() {
    int textureWidth, textureHeight;

    for (int i=0; i < this->pyr->numberOfLevels(); i++){
        this->pyr_images[i] = QVImage<sFloat,1> (width >> i, height >> i);
        //Activa el nivel i de la pirámide
        this->pyr->activateTarget(i);
        //Se lee del buffer OpenGL
        glReadPixels(0,0, width >> i, height >> i, GL_RED, GL_FLOAT, pyr_images[i].getWriteData());
    }
}

QVImage<sFloat,1> QVPyramid::getImage(int level) const{
    return this->pyr_images[level];
}

QVPyramid::~QVPyramid(){
    this->pyr->deallocate();
}

unsigned int QVPyramid::getID() const{
    return this->pyr->textureID();
}

int QVPyramid::getWidth () const{
    return this->width;
}

int QVPyramid::getHeight() const{
    return this->height;
}
