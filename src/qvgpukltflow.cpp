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

#include <qvgpukltflow.h>

//#define _POSIX_SOURCE
#include <stdlib.h>
void initShadersEnvironment()
    {
    #ifdef V3D_SHADER_PATH
        setenv("V3D_SHADER_DIR", V3D_SHADER_PATH, 0);
    #else
        std::cout << "[initShadersEnvironment] Warking: no V3D_SHADER_PATH variable defined at 'config.pri'." << std::endl;
    #endif
    }

#include <iostream>
#include <QGLPixelBuffer>
// Function to init GLEW and CG system (called just once):
void InitGLEWCg()
    {
    // Off-screen buffer (just to use its context isolatedly, in order to be used by the GPU process
    // avoiding conflict with the rest of QGLWidgets of the application):
    QGLPixelBuffer *pixelbuffer;

    // In fact any size is valid for the initial QGLPixelBuffer (the really important thing is
    // to call tracker->allocate and tracker->deallocate functions with a correct size afterwards,
    // depending on the image input size:
    pixelbuffer = new QGLPixelBuffer(	QSize(720,576), // GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE
                        QGLFormat(QGL::DoubleBuffer|QGL::DepthBuffer|QGL::Rgba));

    // With this current buffer we init GLEW and Cg:
    pixelbuffer->makeCurrent();
    std::cout << "GLEW initialization:" << std::endl;
    GLenum err =  glewInit();
    if (GLEW_OK != err)
        std::cout << "Error initializing GLEW: " << glewGetErrorString(err) << std::endl;
    else
        std::cout << "OK initializing GLEW: " << glewGetErrorString(err) << std::endl;
    Cg_ProgramBase::initializeCg();
    std::cout << "Done with initialization" << std::endl;
    }

