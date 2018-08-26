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

/*!
@file qv3dobjects.h
*/

#include <qvblockprogramming/qvguiblocks/qvcanvas.h>

#ifndef DOXYGEN_IGNORE_THIS

class QV3DArrow: public QV3DModel
	{
	private:
		const double pointLength, pointWidth, trunkLength, trunkWidth;
		const int sections;
		const QColor color;

		void glDrawDisk(const double firstHeight, const double firstWidth,
				const double secondHeight, const double secondWidth,
				const int sections)
			{
			glBegin(GL_TRIANGLE_STRIP);

			for (double x = 0; x <= 2*PI; x += 2*PI/(double)sections)
				{
				glVertex3d(firstWidth * sin(x), firstWidth * cos(x), firstHeight);
				glVertex3d(secondWidth * sin(x), secondWidth * cos(x), secondHeight);
				}
			glEnd();
			}

	public:
		QV3DArrow(	const double pointLength = 128, const double pointWidth = 24,
				const double trunkLength = 256, const double trunkWidth = 10,
				const int sections = 10, const QColor & color = Qt::red): QV3DModel(),
			pointLength(pointLength), pointWidth(pointWidth), trunkLength(trunkLength), trunkWidth(trunkWidth),
			sections(sections), color(color)
			{
			}

		void paint(QGLWidget &glWidget)
			{
			glWidget.qglColor(color);
			glDrawDisk(0, 0, 0, trunkWidth, sections);					// Trunk base
			glDrawDisk(0, trunkWidth, trunkLength, trunkWidth, sections);			// Trunk
			glDrawDisk(trunkLength, 0, trunkLength, pointWidth, sections);			// Point base
			glDrawDisk(trunkLength, pointWidth, trunkLength+pointLength, 0, sections);	// Point
			};
	};

class QV3DCoordinateCenter: public QV3DModel
	{
	private:
		QV3DArrow xAxis, yAxis, zAxis;
	public:
		QV3DCoordinateCenter(const double axisSizes = 400):QV3DModel(),
			xAxis(axisSizes/4, axisSizes/20, axisSizes/2, axisSizes/45, 10, Qt::red),
			yAxis(axisSizes/4, axisSizes/20, axisSizes/2, axisSizes/45, 10, Qt::green),
			zAxis(axisSizes/4, axisSizes/20, axisSizes/2, axisSizes/45, 10, Qt::blue)
			{ }

		void paint(QGLWidget &glWidget)
			{
			// Z axis
			zAxis.paint(glWidget);

			// Y axis
			glPushMatrix();
			glMultMatrixd(QVMatrix::rotationMatrix3dXAxis(PI/2).transpose().getReadData());
			yAxis.paint(glWidget);
			glPopMatrix();

			// X axis
			glPushMatrix();
			glMultMatrixd(QVMatrix::rotationMatrix3dYAxis(-PI/2).transpose().getReadData());
			xAxis.paint(glWidget);
			glPopMatrix();

			//glShadeModel(GL_SMOOTH);
			//glShadeModel(GL_FLAT);
			//drawSphere(0.5, 50, 50);
			};
	};
#endif

