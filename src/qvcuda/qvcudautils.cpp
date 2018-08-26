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

#include <cstdio>
#include <cstdlib>

#include <cuda.h>
#include <cuda_runtime.h>

#include "cutil.h"

#include "qvcudautils.h"

void InitCuda(int argc, char **argv) { CUT_DEVICE_INIT(argc,argv); }

int iDivUp(int a, int b) { return (a % b != 0) ? (a / b + 1) : (a / b); };

int iDivDown(int a, int b) { return a / b; };

int iAlignUp(int a, int b) { return (a % b != 0) ?  (a - a % b + b) : a; };

int iAlignDown(int a, int b) { return a - a % b; };

void StartTimer(unsigned int *hTimer)
{
  CUT_SAFE_CALL(cutCreateTimer(hTimer));
  CUT_SAFE_CALL(cutResetTimer(*hTimer));
  CUT_SAFE_CALL(cutStartTimer(*hTimer));
}

double StopTimer(unsigned int hTimer)
{
  CUT_SAFE_CALL(cutStopTimer(hTimer));
  double gpuTime = cutGetTimerValue(hTimer);	
  CUT_SAFE_CALL(cutDeleteTimer(hTimer));
  return gpuTime;
}
