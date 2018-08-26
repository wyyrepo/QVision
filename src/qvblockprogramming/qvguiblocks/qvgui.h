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

#ifndef QVGUI_H
#define QVGUI_H


/*!
@class QVGUI qvblockprogramming/qvguiblocks/qvgui.h QVGUI
@brief Main user interface widget for QVision applications.

This is a pure virtual class parent of the different graphical user interface main classes.

They are widgets which offer to the user the possibility to control the execution of the different blocks registered in the application, the flow of the input video camera objects, and modify the scalar input parameters defined and not linked at the blocks (see @ref TheGUI ).

@ingroup qvblockprogramming
*/
class QVGUI
{
public:
	/// @brief Constructs a QVGUI object.
	QVGUI() { }
	virtual ~QVGUI() { }

	/// @brief initialice the QVGUI object.
	virtual void init() = 0;

	/// @brief show the QVGUI object.
	virtual void show() = 0;
};

#endif

