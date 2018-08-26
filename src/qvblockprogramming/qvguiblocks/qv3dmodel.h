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

#ifndef QV3DMODEL_H
#define QV3DMODEL_H

#ifndef DOXYGEN_IGNORE_THIS
#include <QGLWidget>

#include <QVImage>
#include <QVPropertyContainer>
#include <qvblockprogramming/qvguiblocks/qvcanvas.h>

class QV3DCanvas;

class QV3DModel: public QVPropertyContainer
	{
	public:
		QV3DModel(const QString name = QString()): QVPropertyContainer(name) {}
		virtual ~QV3DModel() {};

		// This method must be redefined to include the painting code
		virtual void paint(QGLWidget &glWidget) = 0;

		// Because readInputProperties is protected, it must be called from the QV3DModel
		void updatePaint(QGLWidget &glWidget)
			{
			readInputProperties();
			glPushMatrix();
			paint(glWidget);
			glPopMatrix();
			}
	};

#endif

#endif


