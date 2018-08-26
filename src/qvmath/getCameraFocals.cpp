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

#include <qvprojective.h>

/*
# Get coefficients for polynomial:
#	a x^3 + b x^2 + c x + d
with(linalg):
Mf := Matrix(4,4,symbol=mf):
Mg := Matrix(4,4,symbol=mg):
d := det(Mf - x Mg):

CodeGeneration[C](Vector([ coeff(d, x, 0), coeff(d, x, 1), coeff(d, x, 2), coeff(d, x, 3), coeff(d, x, 4) ]), optimize = true);
*/
// Get coefficients 'a_i' for the following polynomial:
//	determinant(Mf - x Mg) = a_4 x^4 + a_3 x^3 + a_2 x^2 + a_1 x + a_0
QList<double> getPolynomialCoefficientsForMf_xMg(const QVMatrix &Mf, const QVMatrix &Mg)
	{
	double mf[4][4], mg[4][4];
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			{
			mf[i][j] = Mf(i,j);
			mg[i][j] = Mg(i,j);
			}

	const double t1 = mf[0][0] * mf[1][1];
	const double t2 = mf[2][2] * mf[3][3];
	const double t4 = mf[2][3] * mf[3][2];
	const double t6 = mf[0][0] * mf[2][1];
	const double t7 = mf[1][2] * mf[3][3];
	const double t9 = mf[1][3] * mf[3][2];
	const double t11 = mf[0][0] * mf[3][1];
	const double t12 = mf[1][2] * mf[2][3];
	const double t14 = mf[1][3] * mf[2][2];
	const double t16 = mf[1][0] * mf[2][1];
	const double t17 = mf[0][2] * mf[3][3];
	const double t19 = mf[0][3] * mf[3][2];
	const double t21 = mf[1][0] * mf[0][1];
	const double t24 = mf[1][0] * mf[3][1];
	const double t25 = mf[0][3] * mf[2][2];
	const double t27 = mf[0][2] * mf[2][3];
	const double t29 = t1 * t2 - t1 * t4 - t6 * t7 + t6 * t9 + t11 * t12 - t11 * t14 + t16 * t17 - t16 * t19 + t21 * t4 - t21 * t2 + t24 * t25 - t24 * t27;
	const double t30 = mf[2][0] * mf[0][1];
	const double t33 = mf[2][0] * mf[1][1];
	const double t36 = mf[2][0] * mf[3][1];
	const double t37 = mf[0][2] * mf[1][3];
	const double t39 = mf[0][3] * mf[1][2];
	const double t41 = mf[3][0] * mf[0][1];
	const double t44 = mf[3][0] * mf[1][1];
	const double t47 = mf[3][0] * mf[2][1];
	const double t50 = t30 * t7 - t30 * t9 - t33 * t17 + t33 * t19 + t36 * t37 - t36 * t39 - t41 * t12 + t41 * t14 + t44 * t27 - t44 * t25 - t47 * t37 + t47 * t39;
	const double t52 = mf[3][0] * mg[1][1];
	const double t54 = mg[3][0] * mf[0][1];
	const double t57 = mg[3][0] * mf[1][1];
	const double t60 = mg[3][0] * mf[2][1];
	const double t63 = mf[3][0] * mg[0][1];
	const double t65 = mf[0][2] * mg[1][3];
	const double t67 = mg[0][2] * mf[1][3];
	const double t69 = mf[0][3] * mg[1][2];
	const double t71 = mg[0][3] * mf[1][2];
	const double t73 = -t52 * t27 + t54 * t12 - t54 * t14 - t57 * t27 + t57 * t25 + t60 * t37 - t60 * t39 + t63 * t12 + t47 * t65 + t47 * t67 - t47 * t69 - t47 * t71;
	const double t74 = mf[3][0] * mg[2][1];
	const double t76 = mf[0][0] * mg[3][1];
	const double t79 = mf[1][2] * mg[3][3];
	const double t81 = mg[2][2] * mf[3][3];
	const double t83 = mf[0][0] * mg[1][1];
	const double t85 = mg[2][3] * mf[3][2];
	const double t87 = mg[1][3] * mf[3][2];
	const double t89 = mg[0][2] * mf[2][3];
	const double t91 = mf[0][3] * mg[2][2];
	const double t93 = mf[1][0] * mg[2][1];
	const double t95 = mf[0][2] * mg[2][3];
	const double t97 = t74 * t37 - t76 * t12 + t76 * t14 + t6 * t79 - t1 * t81 - t83 * t2 + t1 * t85 - t6 * t87 - t44 * t89 + t44 * t91 + t93 * t19 + t24 * t95;
	const double t101 = mg[0][3] * mf[2][2];
	const double t103 = mf[1][0] * mg[3][1];
	const double t106 = mf[2][3] * mg[3][2];
	const double t109 = mg[2][0] * mf[0][1];
	const double t111 = mg[2][0] * mf[1][1];
	const double t114 = mg[1][0] * mf[2][1];
	const double t116 = mf[0][2] * mg[3][3];
	const double t118 = t24 * t89 - t24 * t91 - t24 * t101 + t103 * t27 - t30 * t79 - t21 * t106 - t21 * t85 + t109 * t9 + t111 * t17 - t103 * t25 - t114 * t17 + t33 * t116;
	const double t119 = mg[0][2] * mf[3][3];
	const double t121 = mf[0][3] * mg[3][2];
	const double t123 = mg[0][3] * mf[3][2];
	const double t125 = mf[2][0] * mg[1][1];
	const double t133 = mf[2][0] * mg[3][1];
	const double t136 = t33 * t119 - t33 * t121 - t33 * t123 + t125 * t17 + t36 * t69 - t125 * t19 - t36 * t65 - t36 * t67 - t109 * t7 + t36 * t71 - t133 * t37 + t133 * t39;
	const double t139 = mf[0][0] * mg[2][1];
	const double t141 = mf[1][3] * mg[2][2];
	const double t143 = mf[1][3] * mg[3][2];
	const double t146 = mg[1][3] * mf[2][2];
	const double t149 = mg[1][2] * mf[2][3];
	const double t152 = mf[1][0] * mg[0][1];
	const double t154 = mf[1][2] * mg[2][3];
	const double t156 = mf[2][2] * mg[3][3];
	const double t158 = mg[1][2] * mf[3][3];
	const double t160 = -t139 * t9 + t11 * t141 - t6 * t143 + t1 * t106 + t11 * t146 + t83 * t4 - t11 * t149 - t44 * t95 + t152 * t2 - t11 * t154 - t1 * t156 + t6 * t158;
	const double t165 = mf[2][0] * mg[0][1];
	const double t174 = t139 * t7 - t74 * t39 - t63 * t14 + t30 * t87 - t165 * t7 + t165 * t9 - t152 * t4 - t16 * t116 - t16 * t119 + t16 * t121 + t16 * t123 - t93 * t17;
	const double t176 = mg[1][0] * mf[0][1];
	const double t179 = mg[1][0] * mf[3][1];
	const double t183 = mg[2][0] * mf[3][1];
	const double t191 = -t176 * t4 + t176 * t2 - t179 * t25 + t179 * t27 - t111 * t19 - t183 * t37 + t183 * t39 + t41 * t154 + t41 * t149 - t41 * t141 - t41 * t146 + t52 * t25;
	const double t196 = mg[0][0] * mf[1][1];
	const double t199 = mg[0][0] * mf[2][1];
	const double t202 = mg[0][0] * mf[3][1];
	const double t207 = -t30 * t158 + t30 * t143 + t114 * t19 + t21 * t81 - t196 * t2 + t196 * t4 + t199 * t7 - t199 * t9 - t202 * t12 + t202 * t14 + t21 * t156 + t44 * t101;
	const double t211 = mg[2][0] * mg[1][1];
	const double t217 = mg[2][0] * mg[3][1];
	const double t224 = mg[3][0] * mg[1][1];
	const double t232 = t211 * t19 + t183 * t65 + t183 * t67 - t183 * t69 - t183 * t71 + t217 * t37 - t217 * t39 + t57 * t95 + t57 * t89 - t57 * t91 - t57 * t101 + t224 * t27 + t52 * t95 + t52 * t89 - t63 * t154 - t54 * t154 - t54 * t149 + t54 * t146;
	const double t234 = mg[3][0] * mg[0][1];
	const double t240 = mg[3][0] * mg[2][1];
	const double t246 = mg[0][2] * mg[2][3];
	const double t250 = mg[0][0] * mg[2][1];
	const double t255 = -t224 * t25 - t234 * t12 - t60 * t65 - t60 * t67 + t60 * t69 + t60 * t71 - t240 * t37 + t240 * t39 + t234 * t14 - t93 * t121 - t93 * t123 - t24 * t246 - t103 * t95 - t103 * t89 + t250 * t9 + t111 * t121 + t63 * t146 - t202 * t141;
	const double t262 = mg[0][3] * mg[2][2];
	const double t268 = mg[1][0] * mg[0][1];
	const double t275 = mg[1][0] * mg[2][1];
	const double t278 = t54 * t141 + t109 * t79 + t133 * t65 + t103 * t91 + t103 * t101 + t24 * t262 - t176 * t156 - t176 * t81 + t176 * t106 + t176 * t85 - t268 * t2 + t268 * t4 + t114 * t116 + t114 * t119 - t114 * t121 - t114 * t123 + t275 * t17 - t275 * t19;
	const double t283 = mg[2][0] * mg[0][1];
	const double t294 = mg[2][2] * mg[3][3];
	const double t296 = mg[1][2] * mg[2][3];
	const double t298 = mg[1][3] * mg[2][2];
	const double t301 = -t133 * t71 + t109 * t158 - t109 * t143 - t109 * t87 + t283 * t7 - t283 * t9 - t111 * t116 - t111 * t119 + t111 * t123 - t211 * t17 + t202 * t154 + t196 * t156 - t199 * t158 - t250 * t7 - t21 * t294 - t41 * t296 + t41 * t298 - t63 * t149;
	const double t306 = mg[0][2] * mg[1][3];
	const double t308 = mg[0][3] * mg[1][2];
	const double t317 = mg[2][3] * mg[3][2];
	const double t323 = mg[0][2] * mg[3][3];
	const double t325 = mg[0][3] * mg[3][2];
	const double t327 = -t52 * t91 - t52 * t101 - t47 * t306 + t47 * t308 - t74 * t65 - t74 * t67 + t139 * t143 - t125 * t119 + t74 * t69 + t74 * t71 + t63 * t141 + t21 * t317 - t152 * t156 - t152 * t81 + t152 * t106 + t152 * t85 + t16 * t323 - t16 * t325;
	const double t334 = mg[1][0] * mg[3][1];
	const double t337 = mg[1][2] * mg[3][3];
	const double t339 = mg[1][3] * mg[3][2];
	const double t346 = mg[0][0] * mg[1][1];
	const double t350 = t93 * t116 + t93 * t119 - t179 * t95 - t179 * t89 + t179 * t91 + t179 * t101 - t334 * t27 + t334 * t25 + t30 * t337 - t30 * t339 + t165 * t79 + t165 * t158 - t165 * t143 - t165 * t87 - t202 * t146 - t346 * t4 + t202 * t149 - t33 * t323;
	const double t370 = t33 * t325 - t125 * t116 + t125 * t121 + t125 * t123 + t36 * t306 - t36 * t308 + t133 * t67 - t133 * t69 + t199 * t143 - t139 * t79 - t6 * t337 - t139 * t158 + t11 * t296 + t1 * t294 - t83 * t85 - t1 * t317 + t83 * t81 + t139 * t87;
	const double t371 = mg[0][0] * mg[3][1];
	const double t390 = t371 * t12 - t371 * t14 - t199 * t79 + t196 * t81 + t346 * t2 - t196 * t85 + t199 * t87 - t196 * t106 + t76 * t154 + t83 * t156 + t76 * t149 - t76 * t141 - t76 * t146 - t11 * t298 + t6 * t339 - t83 * t106 + t44 * t246 - t44 * t262;
	const double t406 = -t76 * t296 + t76 * t298 + t139 * t337 - t52 * t246 + t54 * t296 - t54 * t298 + t224 * t91 + t224 * t101 + t60 * t306 - t60 * t308 + t240 * t65 + t240 * t67;
	const double t419 = -t240 * t69 - t240 * t71 - t93 * t323 + t93 * t325 + t83 * t317 - t283 * t79 + t165 * t339 - t103 * t262 + t176 * t294 - t176 * t317 + t268 * t156 + t268 * t81;
	const double t433 = -t268 * t106 - t268 * t85 - t114 * t323 + t114 * t325 - t275 * t116 - t275 * t119 + t275 * t121 + t275 * t123 + t133 * t308 - t109 * t337 + t109 * t339 - t283 * t158;
	const double t446 = t283 * t143 + t283 * t87 + t111 * t323 - t111 * t325 + t211 * t116 + t211 * t119 + t52 * t262 + t74 * t306 - t346 * t81 + t346 * t106 + t202 * t298 - t199 * t339;
	const double t461 = -t183 * t306 + t183 * t308 - t217 * t65 - t217 * t67 + t217 * t69 + t217 * t71 - t234 * t141 - t234 * t146 - t57 * t246 + t57 * t262 - t224 * t95 - t224 * t89;
	const double t474 = t234 * t149 + t250 * t79 - t74 * t308 + t63 * t296 - t63 * t298 - t250 * t87 + t152 * t294 - t152 * t317 + t179 * t246 + t334 * t95 + t334 * t89 - t334 * t91;
	const double t488 = -t334 * t101 - t179 * t262 - t165 * t337 + t199 * t337 + t250 * t158 - t202 * t296 - t196 * t294 + t346 * t85 + t196 * t317 + t125 * t323 - t125 * t325 - t133 * t306;
	const double t501 = t234 * t154 - t139 * t339 - t83 * t294 - t250 * t143 - t371 * t154 - t346 * t156 - t371 * t149 + t371 * t141 + t371 * t146 + t103 * t246 - t211 * t121 - t211 * t123;
	const double t517 = t371 * t296 - t371 * t298 - t250 * t337 - t346 * t317 + t250 * t339 - t334 * t246 + t334 * t262 + t346 * t294 - t224 * t262 - t240 * t306 + t240 * t308 - t234 * t296;
	const double t530 = -t268 * t294 + t268 * t317 + t275 * t323 - t275 * t325 + t283 * t337 - t283 * t339 - t211 * t323 + t211 * t325 + t217 * t306 - t217 * t308 + t234 * t298 + t224 * t246;

	QList<double> result;
	result << t29 + t50;
	result << t73 + t97 + t118 + t136 + t160 + t174 + t191 + t207;
	result << t232 + t255 + t278 + t301 + t327 + t350 + t370 + t390;
	result << t406 + t419 + t433 + t446 + t461 + t474 + t488 + t501;
	result << t517 + t530;

	return result;
	}


/*
# Get matrices Mf and Mg.
#
# These matrices are such:
#	Mf * [ a, b, c, 1 ] = U.X.Vt
#	Mg * [ a, b, c, 1 ] = U.cofactorX.Vt
#
# Where 'F' is the fundamental matrix in:
#	F = U.diag(r,s,0).Wt
# or
#	F = (U.X.Et.Wt).(W.Z.Wt)
# and
#	Vt = Et x Wt
#	E = [0,1,0; -1,0,0; 0,0,1]
# -----------------------
# or
#	F = U x diag(r,s,0) x Vt
#
*/

/*
# Get coefficient matrix for expression::
#	Mf(a,b,c,1) = U*X*V^T
# Where
#	X = [r, 0, a; 0, s, b; 0, 0, c]
# Given 'U', 'V', 'r' and 's' values known
with(VectorCalculus):
with(LinearAlgebra):
U := Matrix(3, 3, symbol=u):
V := Matrix(3, 3, symbol=v):
X := Matrix([ [r, 0, a], [0, s, b], [0, 0, c] ]):
f := U.X.Transpose(V):
fVector := Vector([ f[1,1], f[1,2], f[2,1], f[2,2] ]):
fVectorDiffA := diff(fVector, a):
fVectorDiffB := diff(fVector, b):
fVectorDiffC := diff(fVector, c):
fVectorDiffRes := simplify(fVector - a fVectorDiffA - b fVectorDiffB - c fVectorDiffC):
Mf := Matrix([fVectorDiffA, fVectorDiffB, fVectorDiffC, fVectorDiffRes]):

# Must be vector zero.
simplify(Mf . Vector([a, b, c, 1]) - fVector);

CodeGeneration[C](Mf, optimize = true);
*/
QVMatrix getMfCoeffsMatrix(const QVMatrix &U, const QVMatrix &V, const double r, const double s)
	{
	double u[4][4], v[4][4];
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			{
			u[i][j] = U(i,j);
			v[i][j] = V(i,j);
			}

	const double t4 = u[0][0] * r;
	const double t6 = u[0][1] * s;
	const double t18 = u[1][0] * r;
	const double t20 = u[1][1] * s;

	double mf[4][4];
	mf[0][0] = u[0][0] * v[0][2];
	mf[0][1] = u[0][1] * v[0][2];
	mf[0][2] = u[0][2] * v[0][2];
	mf[0][3] = t4 * v[0][0] + t6 * v[0][1];
	mf[1][0] = u[0][0] * v[1][2];
	mf[1][1] = u[0][1] * v[1][2];
	mf[1][2] = u[0][2] * v[1][2];
	mf[1][3] = t4 * v[1][0] + t6 * v[1][1];
	mf[2][0] = u[1][0] * v[0][2];
	mf[2][1] = u[1][1] * v[0][2];
	mf[2][2] = u[1][2] * v[0][2];
	mf[2][3] = t18 * v[0][0] + t20 * v[0][1];
	mf[3][0] = u[1][0] * v[1][2];
	mf[3][1] = u[1][1] * v[1][2];
	mf[3][2] = u[1][2] * v[1][2];
	mf[3][3] = t18 * v[1][0] + t20 * v[1][1];

	QVMatrix Mf(4,4);
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			Mf(i,j) = mf[i][j];

	return Mf;
	}

/*
# Get coefficient matrix for expression::
#	Mf(a,b,c,1) = U*cofactorX*V^T
# Where
#	X = [s.c, 0, 0; 0, r.c, 0; -s.a, -r.b, r.s]
# Given 'U', 'V', 'r' and 's' values known
with(VectorCalculus):
with(LinearAlgebra):
U := Matrix(3, 3, symbol=u):
V := Matrix(3, 3, symbol=v):
cofactorX := Matrix([ [s.c, 0, 0], [0, r.c, 0], [-s.a, -r.b, r.s] ]):
g := U.cofactorX.Transpose(V):
gVector := Vector([ g[1,1], g[1,2], g[2,1], g[2,2] ]):
gVectorDiffA := diff(gVector, a):
gVectorDiffB := diff(gVector, b):
gVectorDiffC := diff(gVector, c):
gVectorDiffRes := simplify(gVector - a gVectorDiffA - b gVectorDiffB - c gVectorDiffC):
Mg := Matrix([gVectorDiffA, gVectorDiffB, gVectorDiffC, gVectorDiffRes]):

# Must be vector zero.
simplify(Mg . Vector([a, b, c, 1]) - gVector);

CodeGeneration[C](Mg, optimize = true);
*/

QVMatrix getMgCoeffsMatrix(const QVMatrix &U, const QVMatrix &V, const double r, const double s)
	{
	double u[4][4], v[4][4];
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			{
			u[i][j] = U(i,j);
			v[i][j] = V(i,j);
			}

	const double t1 = u[0][2] * s;
	const double t3 = u[0][2] * r;
	const double t5 = u[0][0] * s;
	const double t7 = u[0][1] * r;
	const double t10 = s * v[0][2];
	const double t17 = s * v[1][2];
	const double t19 = u[1][2] * s;
	const double t21 = u[1][2] * r;
	const double t23 = u[1][0] * s;
	const double t25 = u[1][1] * r;

	double mg[4][4];
	mg[0][0] = -t1 * v[0][0];
	mg[0][1] = -t3 * v[0][1];
	mg[0][2] = t5 * v[0][0] + t7 * v[0][1];
	mg[0][3] = t3 * t10;
	mg[1][0] = -t1 * v[1][0];
	mg[1][1] = -t3 * v[1][1];
	mg[1][2] = t5 * v[1][0] + t7 * v[1][1];
	mg[1][3] = t3 * t17;
	mg[2][0] = -t19 * v[0][0];
	mg[2][1] = -t21 * v[0][1];
	mg[2][2] = t23 * v[0][0] + t25 * v[0][1];
	mg[2][3] = t21 * t10;
	mg[3][0] = -t19 * v[1][0];
	mg[3][1] = -t21 * v[1][1];
	mg[3][2] = t23 * v[1][0] + t25 * v[1][1];
	mg[3][3] = t21 * t17;


	QVMatrix Mg(4,4);
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			Mg(i,j) = mg[i][j];

	return Mg;
	}

QVMatrix getX(const double r, const double s, const double a, const double b, const double c)
	{
	QVMatrix X(3,3, 0.0);
	X(0,0) = r;
	X(1,1) = s;
	X(0,2) = a;
	X(1,2) = b;
	X(2,2) = c;
	return X;
	}

QVMatrix getCofactorX(const double r, const double s, const double a, const double b, const double c)
	{
	QVMatrix cofactorX(3,3, 0.0);
	cofactorX(0,0) = s*c;
	cofactorX(1,1) = r*c;
	cofactorX(2,0) = -s*a;
	cofactorX(2,1) = -r*b;
	cofactorX(2,2) = r*s;
	return cofactorX;
	}

double evalPolynomial(const QVVector &coeffs, const double x)
	{
	double accum = 0.0, xExp = 1.0;
	for(int i = 0; i < coeffs.count(); i++)
		{
		accum += coeffs[i]*xExp;
		xExp *= x;
		}

	return accum;
	}

bool	directCamerasFocalsCalibration(const QVMatrix &preF, double &f1, double &f2)
	{
	const QVMatrix F = preF * ( (determinant(preF) < 0.0)?-1.0:1.0 );

	QVMatrix E(3,3, 0.0);
	E(0,1) = 1.0; E(1,0) = -1.0; E(2,2) = 1.0;

	QVMatrix U, W;
	QVVector d;
	singularValueDecomposition(F, U, d, W);

	QVMatrix V = W*E;

	const double det_U = determinant(U), det_V = determinant(V);

	// determinant(F)<0.0 <=> determinant(U)*determinant(V) < 0.0 ?
	// Using (-U, V) raises the same results as using (U, -V) in this procedure?
	if (det_U * det_V < 0.0)
		{
		std::cout << "[directCamerasFocalsCalibration] Error 954381." << std::endl;
		std::cout << "[directCamerasFocalsCalibration] det(F) = " << determinant(F) << std::endl;
		return false;
		}
	else if (det_U < 0.0)
		{
		U = U * -1.0;
		V = V * -1.0;
		}

	const double r = d[0], s = d[1];

	const QVMatrix	Mf = getMfCoeffsMatrix(U, V, r, s),
			Mg = getMgCoeffsMatrix(U, V, r, s);

	const QVVector coeffs = getPolynomialCoefficientsForMf_xMg(Mf, Mg).toVector();

	const double x = sqrt(ABS(coeffs[1] / coeffs[3]));

	const double polynomialValueAtX = evalPolynomial(coeffs, x);
	if (ABS(polynomialValueAtX) > 1e-8)
		{
		std::cout << "[directCamerasFocalsCalibration] Error: could not find x such Mf = x·Mg. polynomial(x) = " << ABS(polynomialValueAtX) << std::endl;
		return false;
		}

	const QVMatrix A = Mf - x * Mg;

	// Sanity check. The determinant of A should be close to zero.
	if (ABS(determinant(A) > 1e-8))
		{
		std::cout << "[directCamerasFocalsCalibration] Error: |det(Mf - x Mg)| = " << ABS(determinant(A)) << std::endl;
		return false;
		}

	QVVector vals;
	solveHomogeneous(A, vals);
	vals = vals / vals[3];

	const QVMatrix	f = U*getX(r, s, vals[0], vals[1], vals[2])*V.transpose(),
					gx = U*getCofactorX(r, s, vals[0], vals[1], vals[2])*V.transpose() * x;

	// Solve k1, k2 from equations:
	//	k1 = a1; k1 = a2;
	//	k2 = a3; k2 = a4;
	//	k1*a6 - k2*a5 = 0;
	const double	a1 = sqrt(ABS(f(0,2) / gx(0,2))),
			a2 = sqrt(ABS(f(1,2) / gx(1,2))),
			a3 = sqrt(ABS(gx(2,0) / f(2,0))),
			a4 = sqrt(ABS(gx(2,1) / f(2,1))),
			a5 = sqrt(ABS(f(2,2))),
			a6 = sqrt(ABS(gx(2,2)));

	const QVMatrix	coeffsMatrix(5,2, (double[5*2]){ 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, a6, -a5 });
	const QVVector	objectivesVector(5, (double[5]){ a1, a2, a3, a4, 0.0 });
	QVVector xVector;
	solveBySingularValueDecomposition(coeffsMatrix, xVector, objectivesVector);

	// This error should be almost zero.
	const double equationsError = (coeffsMatrix * xVector - objectivesVector).norm2();
	if (equationsError > 1e-8)
		{
		std::cout << "[directCamerasFocalsCalibration] Error: norm of residuals for linear equations is not close to zero: " << equationsError << std::endl;
		return false;
		}

	f1 = 1.0/xVector[0];
	f2 = 1.0/xVector[1];

        if ( (isnan(f1) or isnan(f2)))
		{
		std::cout << "[directCamerasFocalsCalibration] Got NaN values for focals." << std::endl;
		return false;
		}

	return true;
	}

// Creation of a quadratic function class type
double calibrationErrorForFundamentalMatrix(const QVMatrix &F, const double f1, const double f2)
	{
	const QVMatrix estimatedE = QVMatrix::diagonal(QV3DPointF(f2, f2, 1.0)) * F * QVMatrix::diagonal(QV3DPointF(f1, f1, 1.0));

	QVVector sv;
	singularValues(estimatedE, sv);

	return 1.0 - sv[1]/sv[0];
	}

double QVCalibrationErrorFunction::evaluate(const QVVector &x)
	{
	const double error = calibrationErrorForFundamentalMatrix(F, x[0], x[1]);
	return error;
	}

QVCalibrationErrorFunction::QVCalibrationErrorFunction(const QVMatrix &F): QVFunction<QVVector, double>(), F(F)
	{ }

void getPointMatchingsVariance(	const QList<QPointFMatching> matchings,
				const double cx1, const double cy1, const double cx2, const double cy2,
				double &variance1, double &variance2)
	{
	QVVector m1x, m1y, m2x, m2y;
	foreach(QPointFMatching matching, matchings)
		{
		m1x << matching.first.x() - cx1;
		m1y << matching.first.y() - cy1;
		m2x << matching.second.x() - cx2;
		m2y << matching.second.y() -cy2;
		}

	variance1 = 0.5*(m1x.variance() + m1y.variance());
	variance2 = 0.5*(m2x.variance() + m2y.variance());
	}

//calibrateCamerasFocals
bool getCameraFocals(	const QList<QPointFMatching> &matchings,
						double &focal1, double &focal2,
						const QPointF principalPoint1,
						const QPointF principalPoint2,
						const GSLMultiminFDFMinimizerType gslMinimizerAlgorithm,
						const int optimizationIterations)
	{
	const double	cx1 = principalPoint1.x(),
					cy1 = principalPoint1.y(),
					cx2 = principalPoint2.x(),
					cy2 = principalPoint2.y();

	// Correct variance of the point projections.
	double variance1, variance2;
	getPointMatchingsVariance(matchings, cx1, cy1, cx2, cy2, variance1, variance2);

	// Use standard deviation for initial focal correction.
	const QVMatrix	Q1 = QVMatrix::cameraCalibrationMatrix(sqrt(variance1), 1.0, cx1, cy1, 0.0),
					Q2 = QVMatrix::cameraCalibrationMatrix(sqrt(variance2), 1.0, cx2, cy2, 0.0);

	const QList<QPointFMatching> correctedMatchings = correctIntrinsics(Q1, Q2, matchings);

	#ifdef QVOPENCV
	const QVMatrix F = cvFindFundamentalMat(correctedMatchings);
	#else
	const QVMatrix F = computeFundamentalMatrix(correctedMatchings);
	#endif

	if (F == QVMatrix())
		return false;

	// Estimate initial focals.
	double f1, f2;
	if (not directCamerasFocalsCalibration(F, f1, f2))
		{
		std::cout << "[calibrateCamerasFocals] Direct method for focals failed. Initializing focals to 1.0." << std::endl;
		f1 = 1.0;
		f2 = 1.0;
		}

	// Optimize focals.
	QVCalibrationErrorFunction error(F);
	QVVector fs(2);
	fs[0] = f1;
	fs[1] = f2;
	qvGSLMinimizeFDF(error, fs, gslMinimizerAlgorithm, optimizationIterations);
	f1 = fs[0];
	f2 = fs[1];

	focal1 = f1 * sqrt(variance1),
	focal2 = f2 * sqrt(variance2);

	return true;
	}

// -----------------------------------------------------


