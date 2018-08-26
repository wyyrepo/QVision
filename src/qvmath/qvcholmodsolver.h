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

// This code is partially based on the class 'CSparse', contained in the SBA package for the ROS framework:
//	http://www.ros.org/wiki/sba


#ifndef QVCHOLMODSOLVER_H
#define QVCHOLMODSOLVER_H

#ifndef DOXYGEN_IGNORE_THIS

#include <QVMatrix>
#include <QMap>
#include <QVSparseBlockMatrix>

#include <SuiteSparse/cholmod.h>

class QVCholmodSolver
	{
	private:
		// Blocks storage
		QVector< QVMatrix > diagonal;
		QVector< QMap<int, QVMatrix> > offdiagonal;

		// parameters
		int asize, bsize, csize;           // matrix A is asize x asize (blocks), csize x csize (elements)
		int nnz;                    // number of non-zeros in A

		// CHOLMOD structures
		cholmod_sparse *chA;        // linear problem matrix
		cholmod_common Common;

	public:
		// constructor
		QVCholmodSolver(const QVSparseBlockMatrix &sparseA);

		~QVCholmodSolver();

		// set up compressed column structure; <init> true if first time
		// <diaginc> is the diagonal multiplier for LM
		void init();

		// doing the Cholesky with QVCholmodSolver or Cholmod
		bool solve(QVVector &x, QVVector &b);              // solve in place with RHS B
	};

#endif	// DOXYGEN_IGNORE_THIS

#endif
