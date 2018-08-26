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

#ifndef QVGPUKLTFLOW_H
#define QVGPUKLTFLOW_H

#include <GL/glew.h>
#include <QGLWidget>
#include <qvgpukltflow/qvopticalflow.h>

/*! @brief Inits the environment variables for the GPU-KLT library functions.

This function should be called in the <i>main</i> function, to set the path for the shader source files,
specified at the 'config.pri' file.

@ingroup qvgpukltflow
*/
void initShadersEnvironment();

/*! @brief Init GLEW and CG system.

This function should be called just once before any call to the GPU-KLT+FLOW wrapper functions from the thread that will use them, to set up the GPU context.
@ingroup qvgpukltflow
*/
void InitGLEWCg();

#endif
