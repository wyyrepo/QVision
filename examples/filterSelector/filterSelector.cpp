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

/*!
@file
@ingroup ExamplePrograms
@brief Shows the use of QVApllication and QVProcessingBlock classes.

@todo Detailed description should follow.

@section Usage
Simply compile, and execute the binary:
\code
	./filterselectos
\endcode

@author PARP Research Group. University of Murcia, Spain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QDebug>

#include <QVApplication>
#include <QVVideoReaderBlock>
#include <QVFilterSelectorBlock>

#include <QVDefaultGUI>
#include <QVImageCanvas>

#ifndef DOXYGEN_IGNORE_THIS

int main(int argc, char *argv[])
	{
	QVApplication app(argc, argv, "Example program for QVision library.");

	QVVideoReaderBlock camera("Video");
	QVFilterSelectorBlock<uChar, 3> filterBlock("Image filter block");
	camera.linkProperty(&filterBlock,"Input image");

	QVDefaultGUI interface;

	QVImageCanvas filteredImage("Filtered image");
	filterBlock.linkProperty("Output image", filteredImage);

	return app.exec();
	}

#endif

