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


#include <QVCholmodSolver>

QVCholmodSolver::QVCholmodSolver(const QVSparseBlockMatrix &sparseA)
	{
	chA = NULL;
	nnz = 0;
	asize = sparseA.getMajorRows();
	bsize = sparseA.getMinorRows();
	csize = asize*bsize;

	diagonal = QVector<QVMatrix>( asize, QVMatrix(bsize, bsize, 0.0) );
	offdiagonal = QVector< QMap<int, QVMatrix> >(asize);

	foreach(int ib, sparseA.keys())
		{
		const QMap<int, QVMatrix> &majorRow = sparseA[ib];
		foreach(int jb, majorRow.keys())
			{
			const QVMatrix &qvblockMatrix = majorRow[jb];

			if (ib == jb)
				diagonal[ib] = diagonal[ib] + qvblockMatrix;
			else	{
				offdiagonal[jb][ib] = qvblockMatrix;
				offdiagonal[ib][jb] = qvblockMatrix.transpose();
				}
			}
		}

	cholmod_start(&Common); // this is finished in doChol()
	}

QVCholmodSolver::~QVCholmodSolver()
	{
	cholmod_free_sparse(&chA, &Common);
	cholmod_finish (&Common);   // finish it ???
	}

// Set up CSparse structure; <init> true if first time
// <diaginc> is the diagonal multiplier for LM
// this version sets upper triangular matrix,
void QVCholmodSolver::init()
	{

	// reserve space and set things up
	nnz = asize * bsize * (bsize+1) / 2;
	for (int i=0; i< asize; i++)
		nnz += bsize * bsize * offdiagonal[i].count();

	chA = cholmod_allocate_sparse(csize, csize, nnz, true, true, 1, CHOLMOD_REAL, &Common);

	// now figure out the column pointers
	int	colp = 0,  		// index of where the column starts in Ai
		*Ap = (int *)chA->p,	// column pointer
		*Ai = (int *)chA->i;	// row indices

	for (int ib=0; ib < asize; ib++)
		{
		const QMap<int, QVMatrix> &column = offdiagonal[ib];

		const int numCols = column.count();

		// do this for 'bsize' columns
		for (int k=0; k<bsize; k++)
			{
			*Ap++ = colp;

			// iterate over the map
			if (numCols > 0)
				// iterate over block column entries
				foreach(int jb, column.keys())
					for (int j=0, row = bsize*jb; j<bsize; j++)
						Ai[colp++] = row++;

			// add in diagonal entries
			for (int kk=0, row = bsize*ib; kk<k+1; kk++)
				Ai[colp++] = row++;
			}
		}

	*Ap = nnz;            // last entry

	// now put the entries in place
	colp = 0;              			// index of where the column starts in Ai
	double *Ax = (double *)chA->x;		// values

	for (int ib=0; ib < asize; ib++)
		{
		const QMap<int, QVMatrix> &column = offdiagonal[ib];

		const int numCols = column.count();

		// do this for 'bsize' columns
		for (int k=0; k<bsize; k++)
			{
			// iterate over the map
			if (numCols > 0)
				// iterate over block column entries
				foreach(int jb, column.keys())
					{
					const QVMatrix &m = column[jb];
					for (int j=0; j<bsize; j++)
						Ax[colp++] = m(j,k);
					}
			// add in diagonal entries
			const QVMatrix &m = diagonal[ib];
			for (int kk=0; kk<k+1; kk++)
				Ax[colp++] = m(kk,k);
			}
		}      
	}

// solve in place, returns RHS B
bool QVCholmodSolver::solve(QVVector &qvX, QVVector &qvB)
	{
	//cholmod_print_sparse (chA, (char *)"A", &Common) ; // print simple stats

	// Init objective vector
	cholmod_dense b;
	b.nrow = csize;
	b.ncol = 1;
	b.d = csize;                // leading dimension (???)
	b.xtype = CHOLMOD_REAL;
	b.dtype = CHOLMOD_DOUBLE;
	b.x = qvB.data();

	// Analize
	cholmod_factor *L = cholmod_analyze (chA, &Common) ; // analyze 

	// Factorize matrix
	cholmod_factorize (chA, L, &Common) ; // factorize 

	// Solve system
	cholmod_dense *x = cholmod_solve (CHOLMOD_A, L, &b, &Common) ; // solve Ax=b
	qvX = QVVector(csize, (double *)x->x);

	// Do a cheap iterative refinement.
	// Ax=b was factorized and solved, R = B-A*X
	cholmod_dense *R = cholmod_copy_dense (&b, &Common);
	double one [2] = { 1.0, 0.0 }, minusone [2] = { -1.0, 0.0 };
	cholmod_sdmult(chA, 0, minusone, one, x, R, &Common);
	cholmod_dense *R2 = cholmod_solve(CHOLMOD_A, L, R, &Common);

	for (int i=0 ; i<csize ; i++)
		qvX[i] += ((double *)R2->x)[i];

	// free matrices 
	cholmod_free_dense (&R2, &Common);
	cholmod_free_dense (&R, &Common);
	cholmod_free_factor (&L, &Common);
	cholmod_free_dense (&x, &Common);

	return true;
	}


