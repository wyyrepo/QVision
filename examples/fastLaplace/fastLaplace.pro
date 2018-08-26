#
#   Copyright (C) 2012. PARP Research Group.
#   <http://perception.inf.um.es>
#   University of Murcia, Spain.
#
#   This file is part of the QVision library.
#
#   QVision is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Lesser General Public License as
#   published by the Free Software Foundation, version 3 of the License.
#
#   QVision is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with QVision. If not, see <http://www.gnu.org/licenses/>.
#

#############################
#
#   File fastLaplace.pro
#

include(../../qvproject.pri)

qvipp_available : qvqwt_available	{
		TARGET = fastLaplace
		SOURCES += fastLaplace.cpp
		}
else	{
		warning(in example \'fastLaplace\'. QVision is not correctly configured to use IPP or QWT. See file \'config.pri\'.)
		TEMPLATE = subdirs
		SUBDIRS = 
		}
