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

#include <qvsfm/qvgea/quaternionEssentialEvaluation.h>
/*
Maple code to generate the function 'essentialEvaluation':
--------------------------------------

###################
# Including modules with required functionality
#
with(VectorCalculus):
with(LinearAlgebra):

###################
# Defining some projective algebra functions
#
Norm2 := v -> sqrt(v(1)^2 + v(2)^2 + v(3)^2):
#FromHomogeneous2D := p3D -> Vector([p3D(1)/p3D(3), p3D(2)/p3D(3)]):
CrossProductMatrix := v -> Matrix([[0, -v(3), v(2)], [v(3), 0, -v(1)], [-v(2), v(1), 0]]):
QuaternionToRotationMatrix := q ->
	Matrix([[1,0,0],[0,1,0],[0,0,1]]) +
	(2.0 / (q(1)^2+q(2)^2+q(3)^2+q(4)^2)) *
	Matrix(	[	[-q(2)*q(2)-q(3)*q(3), q(1)*q(2)-q(3)*q(4), q(3)*q(1)+q(2)*q(4)],
			[q(1)*q(2)+q(3)*q(4), -q(3)*q(3)-q(1)*q(1), q(2)*q(3)-q(1)*q(4)],
			[q(3)*q(1)-q(2)*q(4), q(2)*q(3)+q(1)*q(4), -q(2)*q(2)-q(1)*q(1)]
		]):

###################
# Epipolar expression.
#
# The essential matrix is expressed related to two cameras, defined by the vectors
#
#	[v1x0, v1x1, v1x2, v1x3, v1x4, v1x5, v1x6]
#
#	and
#
#	[v2x0, v2x1, v2x2, v2x3, v2x4, v2x5, v2x6]
#
R1 := QuaternionToRotationMatrix(Vector([v1x0, v1x1, v1x2, v1x3])):
R2 := QuaternionToRotationMatrix(Vector([v2x0, v2x1, v2x2, v2x3])):
c1 := Vector([v1x4, v1x5, v1x6]):
c2 := Vector([v2x4, v2x5, v2x6]):
E := R2.CrossProductMatrix( (c2-c1) / Norm2(c2-c1)).Transpose(R1):

###################
# Vectorized expression of the essential matrix
#
vectorE := Vector([E(1,1), E(1,2), E(1,3), E(2,1), E(2,2), E(2,3), E(3,1), E(3,2), E(3,3)]):

###################
# Epipolar evaluation and Jacobian matrices.
# This matrix contains the jacobians for each pair of cameras in the map,
# and the evaluation of the epipolar error function, for the cameras
#
M := Matrix([
[ diff(vectorE(1), v1x0), diff(vectorE(1), v1x1), diff(vectorE(1), v1x2), diff(vectorE(1), v1x3), diff(vectorE(1), v1x4), diff(vectorE(1), v1x5), diff(vectorE(1), v1x6), diff(vectorE(1), v2x0), diff(vectorE(1), v2x1), diff(vectorE(1), v2x2), diff(vectorE(1), v2x3), diff(vectorE(1), v2x4), diff(vectorE(1), v2x5), diff(vectorE(1), v2x6), vectorE(1) ],
[ diff(vectorE(2), v1x0), diff(vectorE(2), v1x1), diff(vectorE(2), v1x2), diff(vectorE(2), v1x3), diff(vectorE(2), v1x4), diff(vectorE(2), v1x5), diff(vectorE(2), v1x6), diff(vectorE(2), v2x0), diff(vectorE(2), v2x1), diff(vectorE(2), v2x2), diff(vectorE(2), v2x3), diff(vectorE(2), v2x4), diff(vectorE(2), v2x5), diff(vectorE(2), v2x6), vectorE(2) ],
[ diff(vectorE(3), v1x0), diff(vectorE(3), v1x1), diff(vectorE(3), v1x2), diff(vectorE(3), v1x3), diff(vectorE(3), v1x4), diff(vectorE(3), v1x5), diff(vectorE(3), v1x6), diff(vectorE(3), v2x0), diff(vectorE(3), v2x1), diff(vectorE(3), v2x2), diff(vectorE(3), v2x3), diff(vectorE(3), v2x4), diff(vectorE(3), v2x5), diff(vectorE(3), v2x6), vectorE(3) ],
[ diff(vectorE(4), v1x0), diff(vectorE(4), v1x1), diff(vectorE(4), v1x2), diff(vectorE(4), v1x3), diff(vectorE(4), v1x4), diff(vectorE(4), v1x5), diff(vectorE(4), v1x6), diff(vectorE(4), v2x0), diff(vectorE(4), v2x1), diff(vectorE(4), v2x2), diff(vectorE(4), v2x3), diff(vectorE(4), v2x4), diff(vectorE(4), v2x5), diff(vectorE(4), v2x6), vectorE(4) ],
[ diff(vectorE(5), v1x0), diff(vectorE(5), v1x1), diff(vectorE(5), v1x2), diff(vectorE(5), v1x3), diff(vectorE(5), v1x4), diff(vectorE(5), v1x5), diff(vectorE(5), v1x6), diff(vectorE(5), v2x0), diff(vectorE(5), v2x1), diff(vectorE(5), v2x2), diff(vectorE(5), v2x3), diff(vectorE(5), v2x4), diff(vectorE(5), v2x5), diff(vectorE(5), v2x6), vectorE(5) ],
[ diff(vectorE(6), v1x0), diff(vectorE(6), v1x1), diff(vectorE(6), v1x2), diff(vectorE(6), v1x3), diff(vectorE(6), v1x4), diff(vectorE(6), v1x5), diff(vectorE(6), v1x6), diff(vectorE(6), v2x0), diff(vectorE(6), v2x1), diff(vectorE(6), v2x2), diff(vectorE(6), v2x3), diff(vectorE(6), v2x4), diff(vectorE(6), v2x5), diff(vectorE(6), v2x6), vectorE(6) ],
[ diff(vectorE(7), v1x0), diff(vectorE(7), v1x1), diff(vectorE(7), v1x2), diff(vectorE(7), v1x3), diff(vectorE(7), v1x4), diff(vectorE(7), v1x5), diff(vectorE(7), v1x6), diff(vectorE(7), v2x0), diff(vectorE(7), v2x1), diff(vectorE(7), v2x2), diff(vectorE(7), v2x3), diff(vectorE(7), v2x4), diff(vectorE(7), v2x5), diff(vectorE(7), v2x6), vectorE(7) ],
[ diff(vectorE(8), v1x0), diff(vectorE(8), v1x1), diff(vectorE(8), v1x2), diff(vectorE(8), v1x3), diff(vectorE(8), v1x4), diff(vectorE(8), v1x5), diff(vectorE(8), v1x6), diff(vectorE(8), v2x0), diff(vectorE(8), v2x1), diff(vectorE(8), v2x2), diff(vectorE(8), v2x3), diff(vectorE(8), v2x4), diff(vectorE(8), v2x5), diff(vectorE(8), v2x6), vectorE(8) ],
[ diff(vectorE(9), v1x0), diff(vectorE(9), v1x1), diff(vectorE(9), v1x2), diff(vectorE(9), v1x3), diff(vectorE(9), v1x4), diff(vectorE(9), v1x5), diff(vectorE(9), v1x6), diff(vectorE(9), v2x0), diff(vectorE(9), v2x1), diff(vectorE(9), v2x2), diff(vectorE(9), v2x3), diff(vectorE(9), v2x4), diff(vectorE(9), v2x5), diff(vectorE(9), v2x6), vectorE(9) ]
]):

###################
# Display the C code to evaluate the previous matrix
#
CodeGeneration[C](M, optimize = true);

*/
void quaternionEssentialEvaluation(const double *pose1, const double *pose2, double *cg)
{
const double	
		v1x0 = pose1[0],
		v1x1 = pose1[1],
		v1x2 = pose1[2],
		v1x3 = pose1[3],
		v1x4 = pose1[4],
		v1x5 = pose1[5],
		v1x6 = pose1[6];

const double	
		v2x0 = pose2[0],
		v2x1 = pose2[1],
		v2x2 = pose2[2],
		v2x3 = pose2[3],
		v2x4 = pose2[4],
		v2x5 = pose2[5],
		v2x6 = pose2[6];

const double t1 = v2x0 * v2x0;
const double t2 = v2x1 * v2x1;
const double t3 = v2x2 * v2x2;
const double t4 = v2x3 * v2x3;
const double t5 = t1 + t2 + t3 + t4;
const double t6 = 0.1e1 / t5;
const double t8 = 0.20e1 * v2x0 * v2x1;
const double t10 = 0.20e1 * v2x2 * v2x3;
const double t11 = t8 - t10;
const double t12 = t6 * t11;
const double t13 =  ( v2x4 *  v2x4);
const double t16 =  ( v1x4 *  v1x4);
const double t17 =  ( v2x5 *  v2x5);
const double t20 =  ( v1x5 *  v1x5);
const double t21 =  ( v2x6 *  v2x6);
const double t24 =  ( v1x6 *  v1x6);
const double t25 = t13 - 2 * v2x4 * v1x4 + t16 + t17 - 2 * v2x5 * v1x5 + t20 + t21 - 2 * v2x6 * v1x6 + t24;
const double t26 = sqrt( t25);
const double t27 = 0.1e1 / t26;
const double t28 = v2x6 - v1x6;
const double t29 = t27 *  t28;
const double t32 = 0.20e1 * v2x2 * v2x0;
const double t34 = 0.20e1 * v2x1 * v2x3;
const double t35 = t32 + t34;
const double t36 = t6 * t35;
const double t37 = v2x5 - v1x5;
const double t38 = t27 *  t37;
const double t40 = t12 * t29 - t36 * t38;
const double t41 = v1x0 * v1x0;
const double t42 = v1x1 * v1x1;
const double t43 = v1x2 * v1x2;
const double t44 = v1x3 * v1x3;
const double t45 = t41 + t42 + t43 + t44;
const double t46 = t45 * t45;
const double t47 = 0.1e1 / t46;
const double t48 = t40 * t47;
const double t49 = 0.20e1 * t42;
const double t50 = 0.20e1 * t43;
const double t51 = -t49 - t50;
const double t52 = t51 * v1x0;
const double t55 = 0.20e1 * t2;
const double t56 = 0.20e1 * t3;
const double t57 = -t55 - t56;
const double t59 = 0.1e1 + t6 * t57;
const double t60 = t59 * t27;
const double t62 = v2x4 - v1x4;
const double t63 = t27 *  t62;
const double t65 = -t60 *  t28 + t36 * t63;
const double t66 = t65 * t47;
const double t68 = 0.20e1 * v1x0 * v1x1;
const double t70 = 0.20e1 * v1x2 * v1x3;
const double t71 = t68 - t70;
const double t72 = t71 * v1x0;
const double t75 = 0.1e1 / t45;
const double t76 = t65 * t75;
const double t78 = 0.20e1 * t76 * v1x1;
const double t81 = t60 *  t37 - t12 * t63;
const double t82 = t81 * t47;
const double t84 = 0.20e1 * v1x2 * v1x0;
const double t86 = 0.20e1 * v1x1 * v1x3;
const double t87 = t84 + t86;
const double t88 = t87 * v1x0;
const double t91 = t81 * t75;
const double t93 = 0.20e1 * t91 * v1x2;
const double t95 = t47 * t51;
const double t99 = 0.40e1 * t75 * v1x1;
const double t100 = -0.2e1 * t95 * v1x1 - t99;
const double t102 = t71 * v1x1;
const double t106 = 0.20e1 * t76 * v1x0;
const double t107 = t87 * v1x1;
const double t111 = 0.20e1 * t91 * v1x3;
const double t116 = 0.40e1 * t75 * v1x2;
const double t117 = -0.2e1 * t95 * v1x2 - t116;
const double t119 = t71 * v1x2;
const double t123 = 0.20e1 * t76 * v1x3;
const double t124 = t87 * v1x2;
const double t128 = 0.20e1 * t91 * v1x0;
const double t130 = t51 * v1x3;
const double t133 = t71 * v1x3;
const double t137 = 0.20e1 * t76 * v1x2;
const double t138 = t87 * v1x3;
const double t142 = 0.20e1 * t91 * v1x1;
const double t145 = 0.1e1 / t26 /  t25;
const double t146 = t145 *  t28;
const double t147 = -0.2e1 * t146 *  t62;
const double t149 = t145 *  t37;
const double t150 = -0.2e1 * t149 *  t62;
const double t152 = -t12 * t147 + t36 * t150;
const double t154 = 0.1e1 + t75 * t51;
const double t156 = t59 * t145;
const double t157 = -2 * t28 * t62;
const double t160 = t145 *  t62;
const double t161 = -0.2e1 * t160 *  t62;
const double t164 = t36 * t27;
const double t165 = t156 *  t157 / 0.2e1 - t36 * t161 / 0.2e1 - t164;
const double t166 = t165 * t75;
const double t168 = -2 * t37 * t62;
const double t173 = t12 * t27;
const double t174 = -t156 *  t168 / 0.2e1 + t12 * t161 / 0.2e1 + t173;
const double t175 = t174 * t75;
const double t178 = -0.2e1 * t146 *  t37;
const double t181 = -0.2e1 * t149 *  t37;
const double t184 = -t12 * t178 / 0.2e1 + t36 * t181 / 0.2e1 + t164;
const double t186 = -2 * t28 * t37;
const double t187 = t156 *  t186;
const double t188 = -0.2e1 * t160 *  t37;
const double t190 = t187 - t36 * t188;
const double t191 = t190 * t75 / 0.2e1;
const double t193 = -2 * t37 * t37;
const double t198 = -t156 *  t193 / 0.2e1 - t60 + t12 * t188 / 0.2e1;
const double t199 = t198 * t75;
const double t202 = -0.2e1 * t146 *  t28;
const double t205 = -0.2e1 * t149 *  t28;
const double t208 = -t12 * t202 / 0.2e1 - t173 + t36 * t205 / 0.2e1;
const double t210 = -2 * t28 * t28;
const double t213 = -0.2e1 * t160 *  t28;
const double t216 = t156 *  t210 / 0.2e1 + t60 - t36 * t213 / 0.2e1;
const double t217 = t216 * t75;
const double t220 = -t187 + t12 * t213;
const double t221 = t220 * t75 / 0.2e1;
const double t224 = t5 * t5;
const double t225 = 0.1e1 / t224;
const double t226 = t225 * t11;
const double t227 = t29 * v2x0;
const double t230 = t6 * v2x1;
const double t232 = 0.20e1 * t230 * t29;
const double t233 = t225 * t35;
const double t234 = t38 * v2x0;
const double t237 = t6 * v2x2;
const double t239 = 0.20e1 * t237 * t38;
const double t240 = -0.2e1 * t226 * t227 + t232 + 0.2e1 * t233 * t234 - t239;
const double t242 = t225 * t57;
const double t245 = t63 * v2x0;
const double t249 = 0.20e1 * t237 * t63;
const double t250 = 0.2e1 * t242 * t227 - 0.2e1 * t233 * t245 + t249;
const double t251 = t250 * t75;
const double t258 = 0.20e1 * t230 * t63;
const double t259 = -0.2e1 * t242 * t234 + 0.2e1 * t226 * t245 - t258;
const double t260 = t259 * t75;
const double t263 = t29 * v2x1;
const double t266 = t6 * v2x0;
const double t268 = 0.20e1 * t266 * t29;
const double t269 = t38 * v2x1;
const double t272 = t6 * v2x3;
const double t274 = 0.20e1 * t272 * t38;
const double t275 = -0.2e1 * t226 * t263 + t268 + 0.2e1 * t233 * t269 - t274;
const double t279 = 0.40e1 * t230;
const double t281 = (-0.2e1 * t242 * v2x1 - t279) * t27;
const double t283 = t63 * v2x1;
const double t287 = 0.20e1 * t272 * t63;
const double t288 = -t281 *  t28 - 0.2e1 * t233 * t283 + t287;
const double t289 = t288 * t75;
const double t295 = 0.20e1 * t266 * t63;
const double t296 = t281 *  t37 + 0.2e1 * t226 * t283 - t295;
const double t297 = t296 * t75;
const double t300 = t29 * v2x2;
const double t304 = 0.20e1 * t272 * t29;
const double t305 = t38 * v2x2;
const double t309 = 0.20e1 * t266 * t38;
const double t310 = -0.2e1 * t226 * t300 - t304 + 0.2e1 * t233 * t305 - t309;
const double t314 = 0.40e1 * t237;
const double t316 = (-0.2e1 * t242 * v2x2 - t314) * t27;
const double t318 = t63 * v2x2;
const double t321 = -t316 *  t28 - 0.2e1 * t233 * t318 + t295;
const double t322 = t321 * t75;
const double t327 = t316 *  t37 + 0.2e1 * t226 * t318 + t287;
const double t328 = t327 * t75;
const double t331 = t29 * v2x3;
const double t335 = 0.20e1 * t237 * t29;
const double t336 = t38 * v2x3;
const double t340 = 0.20e1 * t230 * t38;
const double t341 = -0.2e1 * t226 * t331 - t335 + 0.2e1 * t233 * t336 - t340;
const double t345 = t63 * v2x3;
const double t348 = 0.2e1 * t242 * t331 - 0.2e1 * t233 * t345 + t258;
const double t349 = t348 * t75;
const double t355 = -0.2e1 * t242 * t336 + 0.2e1 * t226 * t345 + t249;
const double t356 = t355 * t75;
const double t359 = 0.2e1 * t146 *  t62;
const double t361 = 0.2e1 * t149 *  t62;
const double t363 = -t12 * t359 + t36 * t361;
const double t365 = 2 * t28 * t62;
const double t368 = 0.2e1 * t160 *  t62;
const double t371 = t156 *  t365 / 0.2e1 - t36 * t368 / 0.2e1 + t164;
const double t372 = t371 * t75;
const double t374 = 2 * t37 * t62;
const double t379 = -t156 *  t374 / 0.2e1 + t12 * t368 / 0.2e1 - t173;
const double t380 = t379 * t75;
const double t383 = 0.2e1 * t146 *  t37;
const double t386 = 0.2e1 * t149 *  t37;
const double t389 = -t12 * t383 / 0.2e1 + t36 * t386 / 0.2e1 - t164;
const double t391 = 2 * t28 * t37;
const double t392 = t156 *  t391;
const double t393 = 0.2e1 * t160 *  t37;
const double t395 = t392 - t36 * t393;
const double t396 = t395 * t75 / 0.2e1;
const double t398 = 2 * t37 * t37;
const double t403 = -t156 *  t398 / 0.2e1 + t60 + t12 * t393 / 0.2e1;
const double t404 = t403 * t75;
const double t407 = 0.2e1 * t146 *  t28;
const double t410 = 0.2e1 * t149 *  t28;
const double t413 = -t12 * t407 / 0.2e1 + t173 + t36 * t410 / 0.2e1;
const double t415 = 2 * t28 * t28;
const double t418 = 0.2e1 * t160 *  t28;
const double t421 = t156 *  t415 / 0.2e1 - t60 - t36 * t418 / 0.2e1;
const double t422 = t421 * t75;
const double t425 = -t392 + t12 * t418;
const double t426 = t425 * t75 / 0.2e1;
const double t433 = t68 + t70;
const double t434 = t433 * v1x0;
const double t437 = t40 * t75;
const double t439 = 0.20e1 * t437 * v1x1;
const double t440 = 0.20e1 * t41;
const double t441 = -t50 - t440;
const double t442 = t47 * t441;
const double t446 = 0.40e1 * t75 * v1x0;
const double t447 = -0.2e1 * t442 * v1x0 - t446;
const double t450 = 0.20e1 * v1x1 * v1x2;
const double t452 = 0.20e1 * v1x0 * v1x3;
const double t453 = t450 - t452;
const double t454 = t453 * v1x0;
const double t458 = t433 * v1x1;
const double t462 = 0.20e1 * t437 * v1x0;
const double t463 = t441 * v1x1;
const double t466 = t453 * v1x1;
const double t470 = t433 * v1x2;
const double t474 = 0.20e1 * t437 * v1x3;
const double t477 = -0.2e1 * t442 * v1x2 - t116;
const double t479 = t453 * v1x2;
const double t483 = t433 * v1x3;
const double t487 = 0.20e1 * t437 * v1x2;
const double t488 = t441 * v1x3;
const double t491 = t453 * v1x3;
const double t495 = t152 * t75 / 0.2e1;
const double t498 = 0.1e1 + t75 * t441;
const double t502 = t184 * t75;
const double t507 = t208 * t75;
const double t512 = t240 * t75;
const double t517 = t275 * t75;
const double t522 = t310 * t75;
const double t527 = t341 * t75;
const double t532 = t363 * t75 / 0.2e1;
const double t537 = t389 * t75;
const double t542 = t413 * t75;
const double t551 = t84 - t86;
const double t552 = t551 * v1x0;
const double t555 = t450 + t452;
const double t556 = t555 * v1x0;
const double t559 = -t49 - t440;
const double t560 = t47 * t559;
const double t563 = -0.2e1 * t560 * v1x0 - t446;
const double t566 = t551 * v1x1;
const double t569 = t555 * v1x1;
const double t574 = -0.2e1 * t560 * v1x1 - t99;
const double t577 = t551 * v1x2;
const double t580 = t555 * v1x2;
const double t583 = t559 * v1x2;
const double t587 = t551 * v1x3;
const double t590 = t555 * v1x3;
const double t593 = t559 * v1x3;
const double t600 = 0.1e1 + t75 * t559;
const double t643 = 0.20e1 * t1;
const double t644 = -t56 - t643;
const double t646 = 0.1e1 + t6 * t644;
const double t647 = t646 * t27;
const double t650 = 0.20e1 * v2x1 * v2x2;
const double t652 = 0.20e1 * v2x0 * v2x3;
const double t653 = t650 - t652;
const double t654 = t6 * t653;
const double t656 = t647 *  t28 - t654 * t38;
const double t657 = t656 * t47;
const double t660 = t8 + t10;
const double t661 = t6 * t660;
const double t664 = -t661 * t29 + t654 * t63;
const double t665 = t664 * t47;
const double t668 = t664 * t75;
const double t670 = 0.20e1 * t668 * v1x1;
const double t673 = t661 * t38 - t647 *  t62;
const double t674 = t673 * t47;
const double t677 = t673 * t75;
const double t679 = 0.20e1 * t677 * v1x2;
const double t685 = 0.20e1 * t668 * v1x0;
const double t689 = 0.20e1 * t677 * v1x3;
const double t695 = 0.20e1 * t668 * v1x3;
const double t699 = 0.20e1 * t677 * v1x0;
const double t706 = 0.20e1 * t668 * v1x2;
const double t710 = 0.20e1 * t677 * v1x1;
const double t712 = t646 * t145;
const double t713 = t712 *  t157;
const double t715 = -t713 + t654 * t150;
const double t721 = t654 * t27;
const double t722 = t661 * t147 / 0.2e1 - t654 * t161 / 0.2e1 - t721;
const double t723 = t722 * t75;
const double t727 = -2 * t62 * t62;
const double t730 = -t661 * t150 / 0.2e1 + t712 *  t727 / 0.2e1 + t647;
const double t731 = t730 * t75;
const double t738 = -t712 *  t186 / 0.2e1 + t654 * t181 / 0.2e1 + t721;
const double t742 = t661 * t178 - t654 * t188;
const double t743 = t742 * t75 / 0.2e1;
const double t747 = t661 * t27;
const double t750 = -t661 * t181 / 0.2e1 - t747 + t712 *  t168 / 0.2e1;
const double t751 = t750 * t75;
const double t758 = -t712 *  t210 / 0.2e1 - t647 + t654 * t205 / 0.2e1;
const double t764 = t661 * t202 / 0.2e1 + t747 - t654 * t213 / 0.2e1;
const double t765 = t764 * t75;
const double t768 = -t661 * t205 + t713;
const double t769 = t768 * t75 / 0.2e1;
const double t772 = t225 * t644;
const double t775 = 0.40e1 * t266;
const double t777 = (-0.2e1 * t772 * v2x0 - t775) * t27;
const double t779 = t225 * t653;
const double t782 = t777 *  t28 + 0.2e1 * t779 * t234 + t274;
const double t784 = t225 * t660;
const double t789 = 0.2e1 * t784 * t227 - t232 - 0.2e1 * t779 * t245 - t287;
const double t790 = t789 * t75;
const double t795 = -0.2e1 * t784 * t234 + t340 - t777 *  t62;
const double t796 = t795 * t75;
const double t803 = -0.2e1 * t772 * t263 + 0.2e1 * t779 * t269 - t239;
const double t809 = 0.2e1 * t784 * t263 - t268 - 0.2e1 * t779 * t283 + t249;
const double t810 = t809 * t75;
const double t816 = -0.2e1 * t784 * t269 + t309 + 0.2e1 * t772 * t283;
const double t817 = t816 * t75;
const double t823 = (-0.2e1 * t772 * v2x2 - t314) * t27;
const double t827 = t823 *  t28 + 0.2e1 * t779 * t305 - t340;
const double t833 = 0.2e1 * t784 * t300 - t304 - 0.2e1 * t779 * t318 + t258;
const double t834 = t833 * t75;
const double t839 = -0.2e1 * t784 * t305 + t274 - t823 *  t62;
const double t840 = t839 * t75;
const double t847 = -0.2e1 * t772 * t331 + 0.2e1 * t779 * t336 + t309;
const double t853 = 0.2e1 * t784 * t331 - t335 - 0.2e1 * t779 * t345 - t295;
const double t854 = t853 * t75;
const double t860 = -0.2e1 * t784 * t336 + t239 + 0.2e1 * t772 * t345;
const double t861 = t860 * t75;
const double t864 = t712 *  t365;
const double t866 = -t864 + t654 * t361;
const double t872 = t661 * t359 / 0.2e1 - t654 * t368 / 0.2e1 + t721;
const double t873 = t872 * t75;
const double t877 = 2 * t62 * t62;
const double t880 = -t661 * t361 / 0.2e1 + t712 *  t877 / 0.2e1 - t647;
const double t881 = t880 * t75;
const double t888 = -t712 *  t391 / 0.2e1 + t654 * t386 / 0.2e1 - t721;
const double t892 = t661 * t383 - t654 * t393;
const double t893 = t892 * t75 / 0.2e1;
const double t899 = -t661 * t386 / 0.2e1 + t747 + t712 *  t374 / 0.2e1;
const double t900 = t899 * t75;
const double t907 = -t712 *  t415 / 0.2e1 + t647 + t654 * t410 / 0.2e1;
const double t913 = t661 * t407 / 0.2e1 - t747 - t654 * t418 / 0.2e1;
const double t914 = t913 * t75;
const double t917 = -t661 * t410 + t864;
const double t918 = t917 * t75 / 0.2e1;
const double t927 = t656 * t75;
const double t929 = 0.20e1 * t927 * v1x1;
const double t937 = 0.20e1 * t927 * v1x0;
const double t946 = 0.20e1 * t927 * v1x3;
const double t954 = 0.20e1 * t927 * v1x2;
const double t960 = t715 * t75 / 0.2e1;
const double t965 = t738 * t75;
const double t970 = t758 * t75;
const double t975 = t782 * t75;
const double t980 = t803 * t75;
const double t985 = t827 * t75;
const double t990 = t847 * t75;
const double t995 = t866 * t75 / 0.2e1;
const double t1000 = t888 * t75;
const double t1005 = t907 * t75;
const double t1084 = t650 + t652;
const double t1085 = t6 * t1084;
const double t1087 = -t55 - t643;
const double t1089 = 0.1e1 + t6 * t1087;
const double t1090 = t1089 * t27;
const double t1092 = t1085 * t29 - t1090 *  t37;
const double t1093 = t1092 * t47;
const double t1096 = t32 - t34;
const double t1097 = t6 * t1096;
const double t1100 = -t1097 * t29 + t1090 *  t62;
const double t1101 = t1100 * t47;
const double t1104 = t1100 * t75;
const double t1106 = 0.20e1 * t1104 * v1x1;
const double t1109 = t1097 * t38 - t1085 * t63;
const double t1110 = t1109 * t47;
const double t1113 = t1109 * t75;
const double t1115 = 0.20e1 * t1113 * v1x2;
const double t1121 = 0.20e1 * t1104 * v1x0;
const double t1125 = 0.20e1 * t1113 * v1x3;
const double t1131 = 0.20e1 * t1104 * v1x3;
const double t1135 = 0.20e1 * t1113 * v1x0;
const double t1142 = 0.20e1 * t1104 * v1x2;
const double t1146 = 0.20e1 * t1113 * v1x1;
const double t1149 = t1089 * t145;
const double t1150 = t1149 *  t168;
const double t1151 = -t1085 * t147 + t1150;
const double t1157 = t1097 * t147 / 0.2e1 - t1149 *  t727 / 0.2e1 - t1090;
const double t1158 = t1157 * t75;
const double t1164 = t1085 * t27;
const double t1165 = -t1097 * t150 / 0.2e1 + t1085 * t161 / 0.2e1 + t1164;
const double t1166 = t1165 * t75;
const double t1173 = -t1085 * t178 / 0.2e1 + t1149 *  t193 / 0.2e1 + t1090;
const double t1176 = t1097 * t178 - t1150;
const double t1177 = t1176 * t75 / 0.2e1;
const double t1181 = t1097 * t27;
const double t1184 = -t1097 * t181 / 0.2e1 - t1181 + t1085 * t188 / 0.2e1;
const double t1185 = t1184 * t75;
const double t1192 = -t1085 * t202 / 0.2e1 - t1164 + t1149 *  t186 / 0.2e1;
const double t1198 = t1097 * t202 / 0.2e1 + t1181 - t1149 *  t157 / 0.2e1;
const double t1199 = t1198 * t75;
const double t1203 = -t1097 * t205 + t1085 * t213;
const double t1204 = t1203 * t75 / 0.2e1;
const double t1207 = t225 * t1084;
const double t1210 = t225 * t1087;
const double t1214 = (-0.2e1 * t1210 * v2x0 - t775) * t27;
const double t1216 = -0.2e1 * t1207 * t227 + t304 - t1214 *  t37;
const double t1218 = t225 * t1096;
const double t1222 = 0.2e1 * t1218 * t227 - t335 + t1214 *  t62;
const double t1223 = t1222 * t75;
const double t1229 = -0.2e1 * t1218 * t234 + t239 + 0.2e1 * t1207 * t245 - t287;
const double t1230 = t1229 * t75;
const double t1238 = (-0.2e1 * t1210 * v2x1 - t279) * t27;
const double t1240 = -0.2e1 * t1207 * t263 + t335 - t1238 *  t37;
const double t1245 = 0.2e1 * t1218 * t263 + t304 + t1238 *  t62;
const double t1246 = t1245 * t75;
const double t1252 = -0.2e1 * t1218 * t269 - t274 + 0.2e1 * t1207 * t283 - t249;
const double t1253 = t1252 * t75;
const double t1260 = -0.2e1 * t1207 * t300 + t232 + 0.2e1 * t1210 * t305;
const double t1266 = 0.2e1 * t1218 * t300 - t268 - 0.2e1 * t1210 * t318;
const double t1267 = t1266 * t75;
const double t1273 = -0.2e1 * t1218 * t305 + t309 + 0.2e1 * t1207 * t318 - t258;
const double t1274 = t1273 * t75;
const double t1281 = -0.2e1 * t1207 * t331 + t268 + 0.2e1 * t1210 * t336;
const double t1287 = 0.2e1 * t1218 * t331 + t232 - 0.2e1 * t1210 * t345;
const double t1288 = t1287 * t75;
const double t1294 = -0.2e1 * t1218 * t336 - t340 + 0.2e1 * t1207 * t345 - t295;
const double t1295 = t1294 * t75;
const double t1299 = t1149 *  t374;
const double t1300 = -t1085 * t359 + t1299;
const double t1306 = t1097 * t359 / 0.2e1 - t1149 *  t877 / 0.2e1 + t1090;
const double t1307 = t1306 * t75;
const double t1313 = -t1097 * t361 / 0.2e1 + t1085 * t368 / 0.2e1 - t1164;
const double t1314 = t1313 * t75;
const double t1321 = -t1085 * t383 / 0.2e1 + t1149 *  t398 / 0.2e1 - t1090;
const double t1324 = t1097 * t383 - t1299;
const double t1325 = t1324 * t75 / 0.2e1;
const double t1331 = -t1097 * t386 / 0.2e1 + t1181 + t1085 * t393 / 0.2e1;
const double t1332 = t1331 * t75;
const double t1339 = -t1085 * t407 / 0.2e1 + t1164 + t1149 *  t391 / 0.2e1;
const double t1345 = t1097 * t407 / 0.2e1 - t1181 - t1149 *  t365 / 0.2e1;
const double t1346 = t1345 * t75;
const double t1350 = -t1097 * t410 + t1085 * t418;
const double t1351 = t1350 * t75 / 0.2e1;
const double t1360 = t1092 * t75;
const double t1362 = 0.20e1 * t1360 * v1x1;
const double t1370 = 0.20e1 * t1360 * v1x0;
const double t1379 = 0.20e1 * t1360 * v1x3;
const double t1387 = 0.20e1 * t1360 * v1x2;
const double t1393 = t1151 * t75 / 0.2e1;
const double t1398 = t1173 * t75;
const double t1403 = t1192 * t75;
const double t1408 = t1216 * t75;
const double t1413 = t1240 * t75;
const double t1418 = t1260 * t75;
const double t1423 = t1281 * t75;
const double t1428 = t1300 * t75 / 0.2e1;
const double t1433 = t1321 * t75;
const double t1438 = t1339 * t75;
cg[15*0+0] = -0.2e1 * t48 * t52 - 0.2e1 * t66 * t72 + t78 - 0.2e1 * t82 * t88 + t93;
cg[15*0+1] = t40 * t100 - 0.2e1 * t66 * t102 + t106 - 0.2e1 * t82 * t107 + t111;
cg[15*0+2] = t40 * t117 - 0.2e1 * t66 * t119 - t123 - 0.2e1 * t82 * t124 + t128;
cg[15*0+3] = -0.2e1 * t48 * t130 - 0.2e1 * t66 * t133 - t137 - 0.2e1 * t82 * t138 + t142;
cg[15*0+4] = t152 * t154 / 0.2e1 + t166 * t71 + t175 * t87;
cg[15*0+5] = t184 * t154 + t191 * t71 + t199 * t87;
cg[15*0+6] = t208 * t154 + t217 * t71 + t221 * t87;
cg[15*0+7] = t240 * t154 + t251 * t71 + t260 * t87;
cg[15*0+8] = t275 * t154 + t289 * t71 + t297 * t87;
cg[15*0+9] = t310 * t154 + t322 * t71 + t328 * t87;
cg[15*0+10] = t341 * t154 + t349 * t71 + t356 * t87;
cg[15*0+11] = t363 * t154 / 0.2e1 + t372 * t71 + t380 * t87;
cg[15*0+12] = t389 * t154 + t396 * t71 + t404 * t87;
cg[15*0+13] = t413 * t154 + t422 * t71 + t426 * t87;
cg[15*0+14] = t40 * t154 + t76 * t71 + t91 * t87;
cg[15*1+0] = -0.2e1 * t48 * t434 + t439 + t65 * t447 - 0.2e1 * t82 * t454 - t111;
cg[15*1+1] = -0.2e1 * t48 * t458 + t462 - 0.2e1 * t66 * t463 - 0.2e1 * t82 * t466 + t93;
cg[15*1+2] = -0.2e1 * t48 * t470 + t474 + t65 * t477 - 0.2e1 * t82 * t479 + t142;
cg[15*1+3] = -0.2e1 * t48 * t483 + t487 - 0.2e1 * t66 * t488 - 0.2e1 * t82 * t491 - t128;
cg[15*1+4] = t495 * t433 + t165 * t498 + t175 * t453;
cg[15*1+5] = t502 * t433 + t190 * t498 / 0.2e1 + t199 * t453;
cg[15*1+6] = t507 * t433 + t216 * t498 + t221 * t453;
cg[15*1+7] = t512 * t433 + t250 * t498 + t260 * t453;
cg[15*1+8] = t517 * t433 + t288 * t498 + t297 * t453;
cg[15*1+9] = t522 * t433 + t321 * t498 + t328 * t453;
cg[15*1+10] = t527 * t433 + t348 * t498 + t356 * t453;
cg[15*1+11] = t532 * t433 + t371 * t498 + t380 * t453;
cg[15*1+12] = t537 * t433 + t395 * t498 / 0.2e1 + t404 * t453;
cg[15*1+13] = t542 * t433 + t421 * t498 + t426 * t453;
cg[15*1+14] = t437 * t433 + t65 * t498 + t91 * t453;
cg[15*2+0] = -0.2e1 * t48 * t552 + t487 - 0.2e1 * t66 * t556 + t123 + t81 * t563;
cg[15*2+1] = -0.2e1 * t48 * t566 - t474 - 0.2e1 * t66 * t569 + t137 + t81 * t574;
cg[15*2+2] = -0.2e1 * t48 * t577 + t462 - 0.2e1 * t66 * t580 + t78 - 0.2e1 * t82 * t583;
cg[15*2+3] = -0.2e1 * t48 * t587 - t439 - 0.2e1 * t66 * t590 + t106 - 0.2e1 * t82 * t593;
cg[15*2+4] = t495 * t551 + t166 * t555 + t174 * t600;
cg[15*2+5] = t502 * t551 + t191 * t555 + t198 * t600;
cg[15*2+6] = t507 * t551 + t217 * t555 + t220 * t600 / 0.2e1;
cg[15*2+7] = t512 * t551 + t251 * t555 + t259 * t600;
cg[15*2+8] = t517 * t551 + t289 * t555 + t296 * t600;
cg[15*2+9] = t522 * t551 + t322 * t555 + t327 * t600;
cg[15*2+10] = t527 * t551 + t349 * t555 + t355 * t600;
cg[15*2+11] = t532 * t551 + t372 * t555 + t379 * t600;
cg[15*2+12] = t537 * t551 + t396 * t555 + t403 * t600;
cg[15*2+13] = t542 * t551 + t422 * t555 + t425 * t600 / 0.2e1;
cg[15*2+14] = t437 * t551 + t76 * t555 + t81 * t600;
cg[15*3+0] = -0.2e1 * t657 * t52 - 0.2e1 * t665 * t72 + t670 - 0.2e1 * t674 * t88 + t679;
cg[15*3+1] = t656 * t100 - 0.2e1 * t665 * t102 + t685 - 0.2e1 * t674 * t107 + t689;
cg[15*3+2] = t656 * t117 - 0.2e1 * t665 * t119 - t695 - 0.2e1 * t674 * t124 + t699;
cg[15*3+3] = -0.2e1 * t657 * t130 - 0.2e1 * t665 * t133 - t706 - 0.2e1 * t674 * t138 + t710;
cg[15*3+4] = t715 * t154 / 0.2e1 + t723 * t71 + t731 * t87;
cg[15*3+5] = t738 * t154 + t743 * t71 + t751 * t87;
cg[15*3+6] = t758 * t154 + t765 * t71 + t769 * t87;
cg[15*3+7] = t782 * t154 + t790 * t71 + t796 * t87;
cg[15*3+8] = t803 * t154 + t810 * t71 + t817 * t87;
cg[15*3+9] = t827 * t154 + t834 * t71 + t840 * t87;
cg[15*3+10] = t847 * t154 + t854 * t71 + t861 * t87;
cg[15*3+11] = t866 * t154 / 0.2e1 + t873 * t71 + t881 * t87;
cg[15*3+12] = t888 * t154 + t893 * t71 + t900 * t87;
cg[15*3+13] = t907 * t154 + t914 * t71 + t918 * t87;
cg[15*3+14] = t656 * t154 + t668 * t71 + t677 * t87;
cg[15*4+0] = -0.2e1 * t657 * t434 + t929 + t664 * t447 - 0.2e1 * t674 * t454 - t689;
cg[15*4+1] = -0.2e1 * t657 * t458 + t937 - 0.2e1 * t665 * t463 - 0.2e1 * t674 * t466 + t679;
cg[15*4+2] = -0.2e1 * t657 * t470 + t946 + t664 * t477 - 0.2e1 * t674 * t479 + t710;
cg[15*4+3] = -0.2e1 * t657 * t483 + t954 - 0.2e1 * t665 * t488 - 0.2e1 * t674 * t491 - t699;
cg[15*4+4] = t960 * t433 + t722 * t498 + t731 * t453;
cg[15*4+5] = t965 * t433 + t742 * t498 / 0.2e1 + t751 * t453;
cg[15*4+6] = t970 * t433 + t764 * t498 + t769 * t453;
cg[15*4+7] = t975 * t433 + t789 * t498 + t796 * t453;
cg[15*4+8] = t980 * t433 + t809 * t498 + t817 * t453;
cg[15*4+9] = t985 * t433 + t833 * t498 + t840 * t453;
cg[15*4+10] = t990 * t433 + t853 * t498 + t861 * t453;
cg[15*4+11] = t995 * t433 + t872 * t498 + t881 * t453;
cg[15*4+12] = t1000 * t433 + t892 * t498 / 0.2e1 + t900 * t453;
cg[15*4+13] = t1005 * t433 + t913 * t498 + t918 * t453;
cg[15*4+14] = t927 * t433 + t664 * t498 + t677 * t453;
cg[15*5+0] = -0.2e1 * t657 * t552 + t954 - 0.2e1 * t665 * t556 + t695 + t673 * t563;
cg[15*5+1] = -0.2e1 * t657 * t566 - t946 - 0.2e1 * t665 * t569 + t706 + t673 * t574;
cg[15*5+2] = -0.2e1 * t657 * t577 + t937 - 0.2e1 * t665 * t580 + t670 - 0.2e1 * t674 * t583;
cg[15*5+3] = -0.2e1 * t657 * t587 - t929 - 0.2e1 * t665 * t590 + t685 - 0.2e1 * t674 * t593;
cg[15*5+4] = t960 * t551 + t723 * t555 + t730 * t600;
cg[15*5+5] = t965 * t551 + t743 * t555 + t750 * t600;
cg[15*5+6] = t970 * t551 + t765 * t555 + t768 * t600 / 0.2e1;
cg[15*5+7] = t975 * t551 + t790 * t555 + t795 * t600;
cg[15*5+8] = t980 * t551 + t810 * t555 + t816 * t600;
cg[15*5+9] = t985 * t551 + t834 * t555 + t839 * t600;
cg[15*5+10] = t990 * t551 + t854 * t555 + t860 * t600;
cg[15*5+11] = t995 * t551 + t873 * t555 + t880 * t600;
cg[15*5+12] = t1000 * t551 + t893 * t555 + t899 * t600;
cg[15*5+13] = t1005 * t551 + t914 * t555 + t917 * t600 / 0.2e1;
cg[15*5+14] = t927 * t551 + t668 * t555 + t673 * t600;
cg[15*6+0] = -0.2e1 * t1093 * t52 - 0.2e1 * t1101 * t72 + t1106 - 0.2e1 * t1110 * t88 + t1115;
cg[15*6+1] = t1092 * t100 - 0.2e1 * t1101 * t102 + t1121 - 0.2e1 * t1110 * t107 + t1125;
cg[15*6+2] = t1092 * t117 - 0.2e1 * t1101 * t119 - t1131 - 0.2e1 * t1110 * t124 + t1135;
cg[15*6+3] = -0.2e1 * t1093 * t130 - 0.2e1 * t1101 * t133 - t1142 - 0.2e1 * t1110 * t138 + t1146;
cg[15*6+4] = t1151 * t154 / 0.2e1 + t1158 * t71 + t1166 * t87;
cg[15*6+5] = t1173 * t154 + t1177 * t71 + t1185 * t87;
cg[15*6+6] = t1192 * t154 + t1199 * t71 + t1204 * t87;
cg[15*6+7] = t1216 * t154 + t1223 * t71 + t1230 * t87;
cg[15*6+8] = t1240 * t154 + t1246 * t71 + t1253 * t87;
cg[15*6+9] = t1260 * t154 + t1267 * t71 + t1274 * t87;
cg[15*6+10] = t1281 * t154 + t1288 * t71 + t1295 * t87;
cg[15*6+11] = t1300 * t154 / 0.2e1 + t1307 * t71 + t1314 * t87;
cg[15*6+12] = t1321 * t154 + t1325 * t71 + t1332 * t87;
cg[15*6+13] = t1339 * t154 + t1346 * t71 + t1351 * t87;
cg[15*6+14] = t1092 * t154 + t1104 * t71 + t1113 * t87;
cg[15*7+0] = -0.2e1 * t1093 * t434 + t1362 + t1100 * t447 - 0.2e1 * t1110 * t454 - t1125;
cg[15*7+1] = -0.2e1 * t1093 * t458 + t1370 - 0.2e1 * t1101 * t463 - 0.2e1 * t1110 * t466 + t1115;
cg[15*7+2] = -0.2e1 * t1093 * t470 + t1379 + t1100 * t477 - 0.2e1 * t1110 * t479 + t1146;
cg[15*7+3] = -0.2e1 * t1093 * t483 + t1387 - 0.2e1 * t1101 * t488 - 0.2e1 * t1110 * t491 - t1135;
cg[15*7+4] = t1393 * t433 + t1157 * t498 + t1166 * t453;
cg[15*7+5] = t1398 * t433 + t1176 * t498 / 0.2e1 + t1185 * t453;
cg[15*7+6] = t1403 * t433 + t1198 * t498 + t1204 * t453;
cg[15*7+7] = t1408 * t433 + t1222 * t498 + t1230 * t453;
cg[15*7+8] = t1413 * t433 + t1245 * t498 + t1253 * t453;
cg[15*7+9] = t1418 * t433 + t1266 * t498 + t1274 * t453;
cg[15*7+10] = t1423 * t433 + t1287 * t498 + t1295 * t453;
cg[15*7+11] = t1428 * t433 + t1306 * t498 + t1314 * t453;
cg[15*7+12] = t1433 * t433 + t1324 * t498 / 0.2e1 + t1332 * t453;
cg[15*7+13] = t1438 * t433 + t1345 * t498 + t1351 * t453;
cg[15*7+14] = t1360 * t433 + t1100 * t498 + t1113 * t453;
cg[15*8+0] = -0.2e1 * t1093 * t552 + t1387 - 0.2e1 * t1101 * t556 + t1131 + t1109 * t563;
cg[15*8+1] = -0.2e1 * t1093 * t566 - t1379 - 0.2e1 * t1101 * t569 + t1142 + t1109 * t574;
cg[15*8+2] = -0.2e1 * t1093 * t577 + t1370 - 0.2e1 * t1101 * t580 + t1106 - 0.2e1 * t1110 * t583;
cg[15*8+3] = -0.2e1 * t1093 * t587 - t1362 - 0.2e1 * t1101 * t590 + t1121 - 0.2e1 * t1110 * t593;
cg[15*8+4] = t1393 * t551 + t1158 * t555 + t1165 * t600;
cg[15*8+5] = t1398 * t551 + t1177 * t555 + t1184 * t600;
cg[15*8+6] = t1403 * t551 + t1199 * t555 + t1203 * t600 / 0.2e1;
cg[15*8+7] = t1408 * t551 + t1223 * t555 + t1229 * t600;
cg[15*8+8] = t1413 * t551 + t1246 * t555 + t1252 * t600;
cg[15*8+9] = t1418 * t551 + t1267 * t555 + t1273 * t600;
cg[15*8+10] = t1423 * t551 + t1288 * t555 + t1294 * t600;
cg[15*8+11] = t1428 * t551 + t1307 * t555 + t1313 * t600;
cg[15*8+12] = t1433 * t551 + t1325 * t555 + t1331 * t600;
cg[15*8+13] = t1438 * t551 + t1346 * t555 + t1350 * t600 / 0.2e1;
cg[15*8+14] = t1360 * t551 + t1104 * t555 + t1109 * t600;
}

/*
###################
# Including modules with required functionality
#
with(VectorCalculus):
with(LinearAlgebra):

###################
# Defining some projective algebra functions
#
Norm2 := v -> sqrt(v(1)^2 + v(2)^2 + v(3)^2):
#FromHomogeneous2D := p3D -> Vector([p3D(1)/p3D(3), p3D(2)/p3D(3)]):
CrossProductMatrix := v -> Matrix([[0, -v(3), v(2)], [v(3), 0, -v(1)], [-v(2), v(1), 0]]):
QuaternionToRotationMatrix := q ->
	Matrix([[1,0,0],[0,1,0],[0,0,1]]) +
	(2.0 / (q(1)^2+q(2)^2+q(3)^2+q(4)^2)) *
	Matrix(	[	[-q(2)*q(2)-q(3)*q(3), q(1)*q(2)-q(3)*q(4), q(3)*q(1)+q(2)*q(4)],
			[q(1)*q(2)+q(3)*q(4), -q(3)*q(3)-q(1)*q(1), q(2)*q(3)-q(1)*q(4)],
			[q(3)*q(1)-q(2)*q(4), q(2)*q(3)+q(1)*q(4), -q(2)*q(2)-q(1)*q(1)]
		]):

###################
# Epipolar expression.
#
# The essential matrix is expressed related to two cameras, defined by the vectors
#
#	[v1x0, v1x1, v1x2, v1x3, v1x4, v1x5, v1x6]
#
#	and
#
#	[v2x0, v2x1, v2x2, v2x3, v2x4, v2x5, v2x6]
#
R1 := QuaternionToRotationMatrix(Vector([v1x0, v1x1, v1x2, v1x3])):
R2 := QuaternionToRotationMatrix(Vector([v2x0, v2x1, v2x2, v2x3])):
c1 := Vector([v1x4, v1x5, v1x6]):
c2 := Vector([v2x4, v2x5, v2x6]):
E := R2.CrossProductMatrix( (c2-c1) / Norm2(c2-c1)).Transpose(R1):

###################
# Vectorized expression of the essential matrix
#
vectorE := Vector([E(1,1), E(1,2), E(1,3), E(2,1), E(2,2), E(2,3), E(3,1), E(3,2), E(3,3)]):

###################
# Epipolar evaluation and Jacobian matrices.
# This matrix contains the jacobians for each pair of cameras in the map,
# and the evaluation of the epipolar error function, for the cameras
#
M := Matrix([
[ diff(vectorE(1), v1x0), diff(vectorE(1), v1x1), diff(vectorE(1), v1x2), diff(vectorE(1), v1x3), diff(vectorE(1), v1x4), diff(vectorE(1), v1x5), diff(vectorE(1), v1x6), vectorE(1) ],
[ diff(vectorE(2), v1x0), diff(vectorE(2), v1x1), diff(vectorE(2), v1x2), diff(vectorE(2), v1x3), diff(vectorE(2), v1x4), diff(vectorE(2), v1x5), diff(vectorE(2), v1x6), vectorE(2) ],
[ diff(vectorE(3), v1x0), diff(vectorE(3), v1x1), diff(vectorE(3), v1x2), diff(vectorE(3), v1x3), diff(vectorE(3), v1x4), diff(vectorE(3), v1x5), diff(vectorE(3), v1x6), vectorE(3) ],
[ diff(vectorE(4), v1x0), diff(vectorE(4), v1x1), diff(vectorE(4), v1x2), diff(vectorE(4), v1x3), diff(vectorE(4), v1x4), diff(vectorE(4), v1x5), diff(vectorE(4), v1x6), vectorE(4) ],
[ diff(vectorE(5), v1x0), diff(vectorE(5), v1x1), diff(vectorE(5), v1x2), diff(vectorE(5), v1x3), diff(vectorE(5), v1x4), diff(vectorE(5), v1x5), diff(vectorE(5), v1x6), vectorE(5) ],
[ diff(vectorE(6), v1x0), diff(vectorE(6), v1x1), diff(vectorE(6), v1x2), diff(vectorE(6), v1x3), diff(vectorE(6), v1x4), diff(vectorE(6), v1x5), diff(vectorE(6), v1x6), vectorE(6) ],
[ diff(vectorE(7), v1x0), diff(vectorE(7), v1x1), diff(vectorE(7), v1x2), diff(vectorE(7), v1x3), diff(vectorE(7), v1x4), diff(vectorE(7), v1x5), diff(vectorE(7), v1x6), vectorE(7) ],
[ diff(vectorE(8), v1x0), diff(vectorE(8), v1x1), diff(vectorE(8), v1x2), diff(vectorE(8), v1x3), diff(vectorE(8), v1x4), diff(vectorE(8), v1x5), diff(vectorE(8), v1x6), vectorE(8) ],
[ diff(vectorE(9), v1x0), diff(vectorE(9), v1x1), diff(vectorE(9), v1x2), diff(vectorE(9), v1x3), diff(vectorE(9), v1x4), diff(vectorE(9), v1x5), diff(vectorE(9), v1x6), vectorE(9) ]
]):

###################
# Display the C code to evaluate the previous matrix
#
CodeGeneration[C](M, optimize = true);
*/
void partialLeftQuaternionEssentialEvaluation(const double *pose1, const double *pose2, double *cg)
{
const double	
		v1x0 = pose1[0],
		v1x1 = pose1[1],
		v1x2 = pose1[2],
		v1x3 = pose1[3],
		v1x4 = pose1[4],
		v1x5 = pose1[5],
		v1x6 = pose1[6];

const double	
		v2x0 = pose2[0],
		v2x1 = pose2[1],
		v2x2 = pose2[2],
		v2x3 = pose2[3],
		v2x4 = pose2[4],
		v2x5 = pose2[5],
		v2x6 = pose2[6];

const double t1 = v2x0 * v2x0;
const double t2 = v2x1 * v2x1;
const double t3 = v2x2 * v2x2;
const double t4 = v2x3 * v2x3;
const double t6 = 0.1e1 / (t1 + t2 + t3 + t4);
const double t8 = 0.20e1 * v2x0 * v2x1;
const double t10 = 0.20e1 * v2x2 * v2x3;
const double t12 = t6 * (t8 - t10);
const double t13 =  (v2x4 * v2x4);
const double t16 =  (v1x4 * v1x4);
const double t17 =  (v2x5 * v2x5);
const double t20 =  (v1x5 * v1x5);
const double t21 =  (v2x6 * v2x6);
const double t24 =  (v1x6 * v1x6);
const double t25 = t13 - 2 * v2x4 * v1x4 + t16 + t17 - 2 * v2x5 * v1x5 + t20 + t21 - 2 * v2x6 * v1x6 + t24;
const double t26 = sqrt(t25);
const double t27 = 0.1e1 / t26;
const double t28 = v2x6 - v1x6;
const double t29 = t27 * t28;
const double t32 = 0.20e1 * v2x2 * v2x0;
const double t34 = 0.20e1 * v2x1 * v2x3;
const double t36 = t6 * (t32 + t34);
const double t37 = v2x5 - v1x5;
const double t38 = t27 * t37;
const double t40 = t12 * t29 - t36 * t38;
const double t41 = v1x0 * v1x0;
const double t42 = v1x1 * v1x1;
const double t43 = v1x2 * v1x2;
const double t44 = v1x3 * v1x3;
const double t45 = t41 + t42 + t43 + t44;
const double t46 = t45 * t45;
const double t47 = 0.1e1 / t46;
const double t48 = t40 * t47;
const double t49 = 0.20e1 * t42;
const double t50 = 0.20e1 * t43;
const double t51 = -t49 - t50;
const double t52 = t51 * v1x0;
const double t55 = 0.20e1 * t2;
const double t56 = 0.20e1 * t3;
const double t59 = 0.1e1 + t6 * (-t55 - t56);
const double t60 = t59 * t27;
const double t62 = v2x4 - v1x4;
const double t63 = t27 * t62;
const double t65 = -t60 * t28 + t36 * t63;
const double t66 = t65 * t47;
const double t68 = 0.20e1 * v1x0 * v1x1;
const double t70 = 0.20e1 * v1x2 * v1x3;
const double t71 = t68 - t70;
const double t72 = t71 * v1x0;
const double t75 = 0.1e1 / t45;
const double t76 = t65 * t75;
const double t78 = 0.20e1 * t76 * v1x1;
const double t81 = t60 * t37 - t12 * t63;
const double t82 = t81 * t47;
const double t84 = 0.20e1 * v1x2 * v1x0;
const double t86 = 0.20e1 * v1x1 * v1x3;
const double t87 = t84 + t86;
const double t88 = t87 * v1x0;
const double t91 = t81 * t75;
const double t93 = 0.20e1 * t91 * v1x2;
const double t95 = t47 * t51;
const double t99 = 0.40e1 * t75 * v1x1;
const double t100 = -0.2e1 * t95 * v1x1 - t99;
const double t102 = t71 * v1x1;
const double t106 = 0.20e1 * t76 * v1x0;
const double t107 = t87 * v1x1;
const double t111 = 0.20e1 * t91 * v1x3;
const double t116 = 0.40e1 * t75 * v1x2;
const double t117 = -0.2e1 * t95 * v1x2 - t116;
const double t119 = t71 * v1x2;
const double t123 = 0.20e1 * t76 * v1x3;
const double t124 = t87 * v1x2;
const double t128 = 0.20e1 * t91 * v1x0;
const double t130 = t51 * v1x3;
const double t133 = t71 * v1x3;
const double t137 = 0.20e1 * t76 * v1x2;
const double t138 = t87 * v1x3;
const double t142 = 0.20e1 * t91 * v1x1;
const double t145 = 0.1e1 / t26 / t25;
const double t146 = t145 * t28;
const double t147 = -0.2e1 * t146 * t62;
const double t149 = t145 * t37;
const double t150 = -0.2e1 * t149 * t62;
const double t152 = -t12 * t147 + t36 * t150;
const double t154 = 0.1e1 + t75 * t51;
const double t156 = t59 * t145;
const double t157 = -2 * t28 * t62;
const double t160 = t145 * t62;
const double t161 = -0.2e1 * t160 * t62;
const double t164 = t36 * t27;
const double t165 = t156 * t157 / 0.2e1 - t36 * t161 / 0.2e1 - t164;
const double t166 = t165 * t75;
const double t168 = -2 * t37 * t62;
const double t173 = t12 * t27;
const double t174 = -t156 * t168 / 0.2e1 + t12 * t161 / 0.2e1 + t173;
const double t175 = t174 * t75;
const double t178 = -0.2e1 * t146 * t37;
const double t181 = -0.2e1 * t149 * t37;
const double t184 = -t12 * t178 / 0.2e1 + t36 * t181 / 0.2e1 + t164;
const double t186 = -2 * t28 * t37;
const double t187 = t156 * t186;
const double t188 = -0.2e1 * t160 * t37;
const double t190 = t187 - t36 * t188;
const double t191 = t190 * t75 / 0.2e1;
const double t193 = -2 * t37 * t37;
const double t198 = -t156 * t193 / 0.2e1 - t60 + t12 * t188 / 0.2e1;
const double t199 = t198 * t75;
const double t202 = -0.2e1 * t146 * t28;
const double t205 = -0.2e1 * t149 * t28;
const double t208 = -t12 * t202 / 0.2e1 - t173 + t36 * t205 / 0.2e1;
const double t210 = -2 * t28 * t28;
const double t213 = -0.2e1 * t160 * t28;
const double t216 = t156 * t210 / 0.2e1 + t60 - t36 * t213 / 0.2e1;
const double t217 = t216 * t75;
const double t220 = -t187 + t12 * t213;
const double t221 = t220 * t75 / 0.2e1;
const double t228 = t68 + t70;
const double t229 = t228 * v1x0;
const double t232 = t40 * t75;
const double t234 = 0.20e1 * t232 * v1x1;
const double t235 = 0.20e1 * t41;
const double t236 = -t50 - t235;
const double t237 = t47 * t236;
const double t241 = 0.40e1 * t75 * v1x0;
const double t242 = -0.2e1 * t237 * v1x0 - t241;
const double t245 = 0.20e1 * v1x1 * v1x2;
const double t247 = 0.20e1 * v1x0 * v1x3;
const double t248 = t245 - t247;
const double t249 = t248 * v1x0;
const double t253 = t228 * v1x1;
const double t257 = 0.20e1 * t232 * v1x0;
const double t258 = t236 * v1x1;
const double t261 = t248 * v1x1;
const double t265 = t228 * v1x2;
const double t269 = 0.20e1 * t232 * v1x3;
const double t272 = -0.2e1 * t237 * v1x2 - t116;
const double t274 = t248 * v1x2;
const double t278 = t228 * v1x3;
const double t282 = 0.20e1 * t232 * v1x2;
const double t283 = t236 * v1x3;
const double t286 = t248 * v1x3;
const double t290 = t152 * t75 / 0.2e1;
const double t293 = 0.1e1 + t75 * t236;
const double t297 = t184 * t75;
const double t302 = t208 * t75;
const double t311 = t84 - t86;
const double t312 = t311 * v1x0;
const double t315 = t245 + t247;
const double t316 = t315 * v1x0;
const double t319 = -t49 - t235;
const double t320 = t47 * t319;
const double t323 = -0.2e1 * t320 * v1x0 - t241;
const double t326 = t311 * v1x1;
const double t329 = t315 * v1x1;
const double t334 = -0.2e1 * t320 * v1x1 - t99;
const double t337 = t311 * v1x2;
const double t340 = t315 * v1x2;
const double t343 = t319 * v1x2;
const double t347 = t311 * v1x3;
const double t350 = t315 * v1x3;
const double t353 = t319 * v1x3;
const double t360 = 0.1e1 + t75 * t319;
const double t375 = 0.20e1 * t1;
const double t378 = 0.1e1 + t6 * (-t56 - t375);
const double t379 = t378 * t27;
const double t382 = 0.20e1 * v2x1 * v2x2;
const double t384 = 0.20e1 * v2x0 * v2x3;
const double t386 = t6 * (t382 - t384);
const double t388 = t379 * t28 - t386 * t38;
const double t389 = t388 * t47;
const double t393 = t6 * (t8 + t10);
const double t396 = -t393 * t29 + t386 * t63;
const double t397 = t396 * t47;
const double t400 = t396 * t75;
const double t402 = 0.20e1 * t400 * v1x1;
const double t405 = t393 * t38 - t379 * t62;
const double t406 = t405 * t47;
const double t409 = t405 * t75;
const double t411 = 0.20e1 * t409 * v1x2;
const double t417 = 0.20e1 * t400 * v1x0;
const double t421 = 0.20e1 * t409 * v1x3;
const double t427 = 0.20e1 * t400 * v1x3;
const double t431 = 0.20e1 * t409 * v1x0;
const double t438 = 0.20e1 * t400 * v1x2;
const double t442 = 0.20e1 * t409 * v1x1;
const double t444 = t378 * t145;
const double t445 = t444 * t157;
const double t447 = -t445 + t386 * t150;
const double t453 = t386 * t27;
const double t454 = t393 * t147 / 0.2e1 - t386 * t161 / 0.2e1 - t453;
const double t455 = t454 * t75;
const double t459 = -2 * t62 * t62;
const double t462 = -t393 * t150 / 0.2e1 + t444 * t459 / 0.2e1 + t379;
const double t463 = t462 * t75;
const double t470 = -t444 * t186 / 0.2e1 + t386 * t181 / 0.2e1 + t453;
const double t474 = t393 * t178 - t386 * t188;
const double t475 = t474 * t75 / 0.2e1;
const double t479 = t393 * t27;
const double t482 = -t393 * t181 / 0.2e1 - t479 + t444 * t168 / 0.2e1;
const double t483 = t482 * t75;
const double t490 = -t444 * t210 / 0.2e1 - t379 + t386 * t205 / 0.2e1;
const double t496 = t393 * t202 / 0.2e1 + t479 - t386 * t213 / 0.2e1;
const double t497 = t496 * t75;
const double t500 = -t393 * t205 + t445;
const double t501 = t500 * t75 / 0.2e1;
const double t510 = t388 * t75;
const double t512 = 0.20e1 * t510 * v1x1;
const double t520 = 0.20e1 * t510 * v1x0;
const double t529 = 0.20e1 * t510 * v1x3;
const double t537 = 0.20e1 * t510 * v1x2;
const double t543 = t447 * t75 / 0.2e1;
const double t548 = t470 * t75;
const double t553 = t490 * t75;
const double t605 = t6 * (t382 + t384);
const double t609 = 0.1e1 + t6 * (-t55 - t375);
const double t610 = t609 * t27;
const double t612 = t605 * t29 - t610 * t37;
const double t613 = t612 * t47;
const double t617 = t6 * (t32 - t34);
const double t620 = -t617 * t29 + t610 * t62;
const double t621 = t620 * t47;
const double t624 = t620 * t75;
const double t626 = 0.20e1 * t624 * v1x1;
const double t629 = t617 * t38 - t605 * t63;
const double t630 = t629 * t47;
const double t633 = t629 * t75;
const double t635 = 0.20e1 * t633 * v1x2;
const double t641 = 0.20e1 * t624 * v1x0;
const double t645 = 0.20e1 * t633 * v1x3;
const double t651 = 0.20e1 * t624 * v1x3;
const double t655 = 0.20e1 * t633 * v1x0;
const double t662 = 0.20e1 * t624 * v1x2;
const double t666 = 0.20e1 * t633 * v1x1;
const double t669 = t609 * t145;
const double t670 = t669 * t168;
const double t671 = -t605 * t147 + t670;
const double t677 = t617 * t147 / 0.2e1 - t669 * t459 / 0.2e1 - t610;
const double t678 = t677 * t75;
const double t684 = t605 * t27;
const double t685 = -t617 * t150 / 0.2e1 + t605 * t161 / 0.2e1 + t684;
const double t686 = t685 * t75;
const double t693 = -t605 * t178 / 0.2e1 + t669 * t193 / 0.2e1 + t610;
const double t696 = t617 * t178 - t670;
const double t697 = t696 * t75 / 0.2e1;
const double t701 = t617 * t27;
const double t704 = -t617 * t181 / 0.2e1 - t701 + t605 * t188 / 0.2e1;
const double t705 = t704 * t75;
const double t712 = -t605 * t202 / 0.2e1 - t684 + t669 * t186 / 0.2e1;
const double t718 = t617 * t202 / 0.2e1 + t701 - t669 * t157 / 0.2e1;
const double t719 = t718 * t75;
const double t723 = -t617 * t205 + t605 * t213;
const double t724 = t723 * t75 / 0.2e1;
const double t733 = t612 * t75;
const double t735 = 0.20e1 * t733 * v1x1;
const double t743 = 0.20e1 * t733 * v1x0;
const double t752 = 0.20e1 * t733 * v1x3;
const double t760 = 0.20e1 * t733 * v1x2;
const double t766 = t671 * t75 / 0.2e1;
const double t771 = t693 * t75;
const double t776 = t712 * t75;
cg[8*0 + 0] = -0.2e1 * t48 * t52 - 0.2e1 * t66 * t72 + t78 - 0.2e1 * t82 * t88 + t93;
cg[8*0 + 1] = t40 * t100 - 0.2e1 * t66 * t102 + t106 - 0.2e1 * t82 * t107 + t111;
cg[8*0 + 2] = t40 * t117 - 0.2e1 * t66 * t119 - t123 - 0.2e1 * t82 * t124 + t128;
cg[8*0 + 3] = -0.2e1 * t48 * t130 - 0.2e1 * t66 * t133 - t137 - 0.2e1 * t82 * t138 + t142;
cg[8*0 + 4] = t152 * t154 / 0.2e1 + t166 * t71 + t175 * t87;
cg[8*0 + 5] = t184 * t154 + t191 * t71 + t199 * t87;
cg[8*0 + 6] = t208 * t154 + t217 * t71 + t221 * t87;
cg[8*0 + 7] = t40 * t154 + t76 * t71 + t91 * t87;
cg[8*1 + 0] = -0.2e1 * t48 * t229 + t234 + t65 * t242 - 0.2e1 * t82 * t249 - t111;
cg[8*1 + 1] = -0.2e1 * t48 * t253 + t257 - 0.2e1 * t66 * t258 - 0.2e1 * t82 * t261 + t93;
cg[8*1 + 2] = -0.2e1 * t48 * t265 + t269 + t65 * t272 - 0.2e1 * t82 * t274 + t142;
cg[8*1 + 3] = -0.2e1 * t48 * t278 + t282 - 0.2e1 * t66 * t283 - 0.2e1 * t82 * t286 - t128;
cg[8*1 + 4] = t290 * t228 + t165 * t293 + t175 * t248;
cg[8*1 + 5] = t297 * t228 + t190 * t293 / 0.2e1 + t199 * t248;
cg[8*1 + 6] = t302 * t228 + t216 * t293 + t221 * t248;
cg[8*1 + 7] = t232 * t228 + t65 * t293 + t91 * t248;
cg[8*2 + 0] = -0.2e1 * t48 * t312 + t282 - 0.2e1 * t66 * t316 + t123 + t81 * t323;
cg[8*2 + 1] = -0.2e1 * t48 * t326 - t269 - 0.2e1 * t66 * t329 + t137 + t81 * t334;
cg[8*2 + 2] = -0.2e1 * t48 * t337 + t257 - 0.2e1 * t66 * t340 + t78 - 0.2e1 * t82 * t343;
cg[8*2 + 3] = -0.2e1 * t48 * t347 - t234 - 0.2e1 * t66 * t350 + t106 - 0.2e1 * t82 * t353;
cg[8*2 + 4] = t290 * t311 + t166 * t315 + t174 * t360;
cg[8*2 + 5] = t297 * t311 + t191 * t315 + t198 * t360;
cg[8*2 + 6] = t302 * t311 + t217 * t315 + t220 * t360 / 0.2e1;
cg[8*2 + 7] = t232 * t311 + t76 * t315 + t81 * t360;
cg[8*3 + 0] = -0.2e1 * t389 * t52 - 0.2e1 * t397 * t72 + t402 - 0.2e1 * t406 * t88 + t411;
cg[8*3 + 1] = t388 * t100 - 0.2e1 * t397 * t102 + t417 - 0.2e1 * t406 * t107 + t421;
cg[8*3 + 2] = t388 * t117 - 0.2e1 * t397 * t119 - t427 - 0.2e1 * t406 * t124 + t431;
cg[8*3 + 3] = -0.2e1 * t389 * t130 - 0.2e1 * t397 * t133 - t438 - 0.2e1 * t406 * t138 + t442;
cg[8*3 + 4] = t447 * t154 / 0.2e1 + t455 * t71 + t463 * t87;
cg[8*3 + 5] = t470 * t154 + t475 * t71 + t483 * t87;
cg[8*3 + 6] = t490 * t154 + t497 * t71 + t501 * t87;
cg[8*3 + 7] = t388 * t154 + t400 * t71 + t409 * t87;
cg[8*4 + 0] = -0.2e1 * t389 * t229 + t512 + t396 * t242 - 0.2e1 * t406 * t249 - t421;
cg[8*4 + 1] = -0.2e1 * t389 * t253 + t520 - 0.2e1 * t397 * t258 - 0.2e1 * t406 * t261 + t411;
cg[8*4 + 2] = -0.2e1 * t389 * t265 + t529 + t396 * t272 - 0.2e1 * t406 * t274 + t442;
cg[8*4 + 3] = -0.2e1 * t389 * t278 + t537 - 0.2e1 * t397 * t283 - 0.2e1 * t406 * t286 - t431;
cg[8*4 + 4] = t543 * t228 + t454 * t293 + t463 * t248;
cg[8*4 + 5] = t548 * t228 + t474 * t293 / 0.2e1 + t483 * t248;
cg[8*4 + 6] = t553 * t228 + t496 * t293 + t501 * t248;
cg[8*4 + 7] = t510 * t228 + t396 * t293 + t409 * t248;
cg[8*5 + 0] = -0.2e1 * t389 * t312 + t537 - 0.2e1 * t397 * t316 + t427 + t405 * t323;
cg[8*5 + 1] = -0.2e1 * t389 * t326 - t529 - 0.2e1 * t397 * t329 + t438 + t405 * t334;
cg[8*5 + 2] = -0.2e1 * t389 * t337 + t520 - 0.2e1 * t397 * t340 + t402 - 0.2e1 * t406 * t343;
cg[8*5 + 3] = -0.2e1 * t389 * t347 - t512 - 0.2e1 * t397 * t350 + t417 - 0.2e1 * t406 * t353;
cg[8*5 + 4] = t543 * t311 + t455 * t315 + t462 * t360;
cg[8*5 + 5] = t548 * t311 + t475 * t315 + t482 * t360;
cg[8*5 + 6] = t553 * t311 + t497 * t315 + t500 * t360 / 0.2e1;
cg[8*5 + 7] = t510 * t311 + t400 * t315 + t405 * t360;
cg[8*6 + 0] = -0.2e1 * t613 * t52 - 0.2e1 * t621 * t72 + t626 - 0.2e1 * t630 * t88 + t635;
cg[8*6 + 1] = t612 * t100 - 0.2e1 * t621 * t102 + t641 - 0.2e1 * t630 * t107 + t645;
cg[8*6 + 2] = t612 * t117 - 0.2e1 * t621 * t119 - t651 - 0.2e1 * t630 * t124 + t655;
cg[8*6 + 3] = -0.2e1 * t613 * t130 - 0.2e1 * t621 * t133 - t662 - 0.2e1 * t630 * t138 + t666;
cg[8*6 + 4] = t671 * t154 / 0.2e1 + t678 * t71 + t686 * t87;
cg[8*6 + 5] = t693 * t154 + t697 * t71 + t705 * t87;
cg[8*6 + 6] = t712 * t154 + t719 * t71 + t724 * t87;
cg[8*6 + 7] = t612 * t154 + t624 * t71 + t633 * t87;
cg[8*7 + 0] = -0.2e1 * t613 * t229 + t735 + t620 * t242 - 0.2e1 * t630 * t249 - t645;
cg[8*7 + 1] = -0.2e1 * t613 * t253 + t743 - 0.2e1 * t621 * t258 - 0.2e1 * t630 * t261 + t635;
cg[8*7 + 2] = -0.2e1 * t613 * t265 + t752 + t620 * t272 - 0.2e1 * t630 * t274 + t666;
cg[8*7 + 3] = -0.2e1 * t613 * t278 + t760 - 0.2e1 * t621 * t283 - 0.2e1 * t630 * t286 - t655;
cg[8*7 + 4] = t766 * t228 + t677 * t293 + t686 * t248;
cg[8*7 + 5] = t771 * t228 + t696 * t293 / 0.2e1 + t705 * t248;
cg[8*7 + 6] = t776 * t228 + t718 * t293 + t724 * t248;
cg[8*7 + 7] = t733 * t228 + t620 * t293 + t633 * t248;
cg[8*8 + 0] = -0.2e1 * t613 * t312 + t760 - 0.2e1 * t621 * t316 + t651 + t629 * t323;
cg[8*8 + 1] = -0.2e1 * t613 * t326 - t752 - 0.2e1 * t621 * t329 + t662 + t629 * t334;
cg[8*8 + 2] = -0.2e1 * t613 * t337 + t743 - 0.2e1 * t621 * t340 + t626 - 0.2e1 * t630 * t343;
cg[8*8 + 3] = -0.2e1 * t613 * t347 - t735 - 0.2e1 * t621 * t350 + t641 - 0.2e1 * t630 * t353;
cg[8*8 + 4] = t766 * t311 + t678 * t315 + t685 * t360;
cg[8*8 + 5] = t771 * t311 + t697 * t315 + t704 * t360;
cg[8*8 + 6] = t776 * t311 + t719 * t315 + t723 * t360 / 0.2e1;
cg[8*8 + 7] = t733 * t311 + t624 * t315 + t629 * t360;
}


/*
###################
# Including modules with required functionality
#
with(VectorCalculus):
with(LinearAlgebra):

###################
# Defining some projective algebra functions
#
Norm2 := v -> sqrt(v(1)^2 + v(2)^2 + v(3)^2):
FromHomogeneous2D := p3D -> Vector([p3D(1)/p3D(3), p3D(2)/p3D(3)]):
CrossProductMatrix := v -> Matrix([[0, -v(3), v(2)], [v(3), 0, -v(1)], [-v(2), v(1), 0]]):
QuaternionToRotationMatrix := q ->
	Matrix([[1,0,0],[0,1,0],[0,0,1]]) +
	(2.0 / (q(1)^2+q(2)^2+q(3)^2+q(4)^2)) *
	Matrix(	[	[-q(2)*q(2)-q(3)*q(3), q(1)*q(2)-q(3)*q(4), q(3)*q(1)+q(2)*q(4)],
			[q(1)*q(2)+q(3)*q(4), -q(3)*q(3)-q(1)*q(1), q(2)*q(3)-q(1)*q(4)],
			[q(3)*q(1)-q(2)*q(4), q(2)*q(3)+q(1)*q(4), -q(2)*q(2)-q(1)*q(1)]
		]):

###################
# Epipolar expression.
#
# The essential matrix is expressed related to two cameras, defined by the vectors
#
#	[v1x0, v1x1, v1x2, v1x3, v1x4, v1x5, v1x6]
#
#	and
#
#	[v2x0, v2x1, v2x2, v2x3, v2x4, v2x5, v2x6]
#
R1 := QuaternionToRotationMatrix(Vector([v1x0, v1x1, v1x2, v1x3])):
R2 := QuaternionToRotationMatrix(Vector([v2x0, v2x1, v2x2, v2x3])):
c1 := Vector([v1x4, v1x5, v1x6]):
c2 := Vector([v2x4, v2x5, v2x6]):
E := R2.CrossProductMatrix( (c2-c1) / Norm2(c2-c1)).Transpose(R1):

###################
# Vectorized expression of the essential matrix
#
vectorE := Vector([E(1,1), E(1,2), E(1,3), E(2,1), E(2,2), E(2,3), E(3,1), E(3,2), E(3,3)]):

###################
# Epipolar evaluation and Jacobian matrices.
# This matrix contains the jacobians for each pair of cameras in the map,
# and the evaluation of the epipolar error function, for the cameras
#
M := Matrix([
[ diff(vectorE(1), v2x0), diff(vectorE(1), v2x1), diff(vectorE(1), v2x2), diff(vectorE(1), v2x3), diff(vectorE(1), v2x4), diff(vectorE(1), v2x5), diff(vectorE(1), v2x6), vectorE(1) ],
[ diff(vectorE(2), v2x0), diff(vectorE(2), v2x1), diff(vectorE(2), v2x2), diff(vectorE(2), v2x3), diff(vectorE(2), v2x4), diff(vectorE(2), v2x5), diff(vectorE(2), v2x6), vectorE(2) ],
[ diff(vectorE(3), v2x0), diff(vectorE(3), v2x1), diff(vectorE(3), v2x2), diff(vectorE(3), v2x3), diff(vectorE(3), v2x4), diff(vectorE(3), v2x5), diff(vectorE(3), v2x6), vectorE(3) ],
[ diff(vectorE(4), v2x0), diff(vectorE(4), v2x1), diff(vectorE(4), v2x2), diff(vectorE(4), v2x3), diff(vectorE(4), v2x4), diff(vectorE(4), v2x5), diff(vectorE(4), v2x6), vectorE(4) ],
[ diff(vectorE(5), v2x0), diff(vectorE(5), v2x1), diff(vectorE(5), v2x2), diff(vectorE(5), v2x3), diff(vectorE(5), v2x4), diff(vectorE(5), v2x5), diff(vectorE(5), v2x6), vectorE(5) ],
[ diff(vectorE(6), v2x0), diff(vectorE(6), v2x1), diff(vectorE(6), v2x2), diff(vectorE(6), v2x3), diff(vectorE(6), v2x4), diff(vectorE(6), v2x5), diff(vectorE(6), v2x6), vectorE(6) ],
[ diff(vectorE(7), v2x0), diff(vectorE(7), v2x1), diff(vectorE(7), v2x2), diff(vectorE(7), v2x3), diff(vectorE(7), v2x4), diff(vectorE(7), v2x5), diff(vectorE(7), v2x6), vectorE(7) ],
[ diff(vectorE(8), v2x0), diff(vectorE(8), v2x1), diff(vectorE(8), v2x2), diff(vectorE(8), v2x3), diff(vectorE(8), v2x4), diff(vectorE(8), v2x5), diff(vectorE(8), v2x6), vectorE(8) ],
[ diff(vectorE(9), v2x0), diff(vectorE(9), v2x1), diff(vectorE(9), v2x2), diff(vectorE(9), v2x3), diff(vectorE(9), v2x4), diff(vectorE(9), v2x5), diff(vectorE(9), v2x6), vectorE(9) ]
]):

###################
# Display the C code to evaluate the previous matrix
#
CodeGeneration[C](M, optimize = true);
*/
void partialRightQuaternionEssentialEvaluation(const double *pose1, const double *pose2, double *cg)
{
const double	
		v1x0 = pose1[0],
		v1x1 = pose1[1],
		v1x2 = pose1[2],
		v1x3 = pose1[3],
		v1x4 = pose1[4],
		v1x5 = pose1[5],
		v1x6 = pose1[6];

const double	
		v2x0 = pose2[0],
		v2x1 = pose2[1],
		v2x2 = pose2[2],
		v2x3 = pose2[3],
		v2x4 = pose2[4],
		v2x5 = pose2[5],
		v2x6 = pose2[6];

const double t1 = v2x0 * v2x0;
const double t2 = v2x1 * v2x1;
const double t3 = v2x2 * v2x2;
const double t4 = v2x3 * v2x3;
const double t5 = t1 + t2 + t3 + t4;
const double t6 = t5 * t5;
const double t7 = 0.1e1 / t6;
const double t9 = 0.20e1 * v2x0 * v2x1;
const double t11 = 0.20e1 * v2x2 * v2x3;
const double t12 = t9 - t11;
const double t13 = t7 * t12;
const double t14 =  ( v2x4 *  v2x4);
const double t17 =  ( v1x4 *  v1x4);
const double t18 =  ( v2x5 *  v2x5);
const double t21 =  ( v1x5 *  v1x5);
const double t22 =  ( v2x6 *  v2x6);
const double t25 =  ( v1x6 *  v1x6);
const double t26 = t14 - 2 * v2x4 * v1x4 + t17 + t18 - 2 * v2x5 * v1x5 + t21 + t22 - 2 * v2x6 * v1x6 + t25;
const double t27 = sqrt( t26);
const double t28 = 0.1e1 / t27;
const double t29 = v2x6 - v1x6;
const double t30 = t28 *  t29;
const double t31 = t30 * v2x0;
const double t34 = 0.1e1 / t5;
const double t35 = t34 * v2x1;
const double t37 = 0.20e1 * t35 * t30;
const double t39 = 0.20e1 * v2x2 * v2x0;
const double t41 = 0.20e1 * v2x1 * v2x3;
const double t42 = t39 + t41;
const double t43 = t7 * t42;
const double t44 = v2x5 - v1x5;
const double t45 = t28 *  t44;
const double t46 = t45 * v2x0;
const double t49 = t34 * v2x2;
const double t51 = 0.20e1 * t49 * t45;
const double t52 = -0.2e1 * t13 * t31 + t37 + 0.2e1 * t43 * t46 - t51;
const double t53 = v1x0 * v1x0;
const double t54 = v1x1 * v1x1;
const double t55 = v1x2 * v1x2;
const double t56 = v1x3 * v1x3;
const double t58 = 0.1e1 / (t53 + t54 + t55 + t56);
const double t59 = 0.20e1 * t54;
const double t60 = 0.20e1 * t55;
const double t63 = 0.1e1 + t58 * (-t59 - t60);
const double t65 = 0.20e1 * t2;
const double t66 = 0.20e1 * t3;
const double t67 = -t65 - t66;
const double t68 = t7 * t67;
const double t71 = v2x4 - v1x4;
const double t72 = t28 *  t71;
const double t73 = t72 * v2x0;
const double t77 = 0.20e1 * t49 * t72;
const double t78 = 0.2e1 * t68 * t31 - 0.2e1 * t43 * t73 + t77;
const double t79 = t78 * t58;
const double t81 = 0.20e1 * v1x0 * v1x1;
const double t83 = 0.20e1 * v1x2 * v1x3;
const double t84 = t81 - t83;
const double t91 = 0.20e1 * t35 * t72;
const double t92 = -0.2e1 * t68 * t46 + 0.2e1 * t13 * t73 - t91;
const double t93 = t92 * t58;
const double t95 = 0.20e1 * v1x2 * v1x0;
const double t97 = 0.20e1 * v1x1 * v1x3;
const double t98 = t95 + t97;
const double t101 = t30 * v2x1;
const double t104 = t34 * v2x0;
const double t106 = 0.20e1 * t104 * t30;
const double t107 = t45 * v2x1;
const double t110 = t34 * v2x3;
const double t112 = 0.20e1 * t110 * t45;
const double t113 = -0.2e1 * t13 * t101 + t106 + 0.2e1 * t43 * t107 - t112;
const double t117 = 0.40e1 * t35;
const double t119 = (-0.2e1 * t68 * v2x1 - t117) * t28;
const double t121 = t72 * v2x1;
const double t125 = 0.20e1 * t110 * t72;
const double t126 = -t119 *  t29 - 0.2e1 * t43 * t121 + t125;
const double t127 = t126 * t58;
const double t133 = 0.20e1 * t104 * t72;
const double t134 = t119 *  t44 + 0.2e1 * t13 * t121 - t133;
const double t135 = t134 * t58;
const double t138 = t30 * v2x2;
const double t142 = 0.20e1 * t110 * t30;
const double t143 = t45 * v2x2;
const double t147 = 0.20e1 * t104 * t45;
const double t148 = -0.2e1 * t13 * t138 - t142 + 0.2e1 * t43 * t143 - t147;
const double t152 = 0.40e1 * t49;
const double t154 = (-0.2e1 * t68 * v2x2 - t152) * t28;
const double t156 = t72 * v2x2;
const double t159 = -t154 *  t29 - 0.2e1 * t43 * t156 + t133;
const double t160 = t159 * t58;
const double t165 = t154 *  t44 + 0.2e1 * t13 * t156 + t125;
const double t166 = t165 * t58;
const double t169 = t30 * v2x3;
const double t173 = 0.20e1 * t49 * t30;
const double t174 = t45 * v2x3;
const double t178 = 0.20e1 * t35 * t45;
const double t179 = -0.2e1 * t13 * t169 - t173 + 0.2e1 * t43 * t174 - t178;
const double t183 = t72 * v2x3;
const double t186 = 0.2e1 * t68 * t169 - 0.2e1 * t43 * t183 + t91;
const double t187 = t186 * t58;
const double t193 = -0.2e1 * t68 * t174 + 0.2e1 * t13 * t183 + t77;
const double t194 = t193 * t58;
const double t197 = t34 * t12;
const double t199 = 0.1e1 / t27 /  t26;
const double t200 = t199 *  t29;
const double t201 = 0.2e1 * t200 *  t71;
const double t203 = t34 * t42;
const double t204 = t199 *  t44;
const double t205 = 0.2e1 * t204 *  t71;
const double t207 = -t197 * t201 + t203 * t205;
const double t210 = 0.1e1 + t34 * t67;
const double t211 = t210 * t199;
const double t212 = 2 * t29 * t71;
const double t215 = t199 *  t71;
const double t216 = 0.2e1 * t215 *  t71;
const double t219 = t203 * t28;
const double t220 = t211 *  t212 / 0.2e1 - t203 * t216 / 0.2e1 + t219;
const double t221 = t220 * t58;
const double t223 = 2 * t44 * t71;
const double t228 = t197 * t28;
const double t229 = -t211 *  t223 / 0.2e1 + t197 * t216 / 0.2e1 - t228;
const double t230 = t229 * t58;
const double t233 = 0.2e1 * t200 *  t44;
const double t236 = 0.2e1 * t204 *  t44;
const double t239 = -t197 * t233 / 0.2e1 + t203 * t236 / 0.2e1 - t219;
const double t241 = 2 * t29 * t44;
const double t242 = t211 *  t241;
const double t243 = 0.2e1 * t215 *  t44;
const double t245 = t242 - t203 * t243;
const double t246 = t245 * t58 / 0.2e1;
const double t248 = 2 * t44 * t44;
const double t251 = t210 * t28;
const double t254 = -t211 *  t248 / 0.2e1 + t251 + t197 * t243 / 0.2e1;
const double t255 = t254 * t58;
const double t258 = 0.2e1 * t200 *  t29;
const double t261 = 0.2e1 * t204 *  t29;
const double t264 = -t197 * t258 / 0.2e1 + t228 + t203 * t261 / 0.2e1;
const double t266 = 2 * t29 * t29;
const double t269 = 0.2e1 * t215 *  t29;
const double t272 = t211 *  t266 / 0.2e1 - t251 - t203 * t269 / 0.2e1;
const double t273 = t272 * t58;
const double t276 = -t242 + t197 * t269;
const double t277 = t276 * t58 / 0.2e1;
const double t282 = t197 * t30 - t203 * t45;
const double t286 = -t251 *  t29 + t203 * t72;
const double t287 = t286 * t58;
const double t291 = t251 *  t44 - t197 * t72;
const double t292 = t291 * t58;
const double t295 = t52 * t58;
const double t296 = t81 + t83;
const double t298 = 0.20e1 * t53;
const double t301 = 0.1e1 + t58 * (-t60 - t298);
const double t304 = 0.20e1 * v1x1 * v1x2;
const double t306 = 0.20e1 * v1x0 * v1x3;
const double t307 = t304 - t306;
const double t310 = t113 * t58;
const double t315 = t148 * t58;
const double t320 = t179 * t58;
const double t325 = t207 * t58 / 0.2e1;
const double t330 = t239 * t58;
const double t335 = t264 * t58;
const double t340 = t282 * t58;
const double t345 = t95 - t97;
const double t347 = t304 + t306;
const double t351 = 0.1e1 + t58 * (-t59 - t298);
const double t382 = 0.20e1 * t1;
const double t383 = -t66 - t382;
const double t384 = t7 * t383;
const double t387 = 0.40e1 * t104;
const double t389 = (-0.2e1 * t384 * v2x0 - t387) * t28;
const double t392 = 0.20e1 * v2x1 * v2x2;
const double t394 = 0.20e1 * v2x0 * v2x3;
const double t395 = t392 - t394;
const double t396 = t7 * t395;
const double t399 = t389 *  t29 + 0.2e1 * t396 * t46 + t112;
const double t401 = t9 + t11;
const double t402 = t7 * t401;
const double t407 = 0.2e1 * t402 * t31 - t37 - 0.2e1 * t396 * t73 - t125;
const double t408 = t407 * t58;
const double t413 = -0.2e1 * t402 * t46 + t178 - t389 *  t71;
const double t414 = t413 * t58;
const double t421 = -0.2e1 * t384 * t101 + 0.2e1 * t396 * t107 - t51;
const double t427 = 0.2e1 * t402 * t101 - t106 - 0.2e1 * t396 * t121 + t77;
const double t428 = t427 * t58;
const double t434 = -0.2e1 * t402 * t107 + t147 + 0.2e1 * t384 * t121;
const double t435 = t434 * t58;
const double t441 = (-0.2e1 * t384 * v2x2 - t152) * t28;
const double t445 = t441 *  t29 + 0.2e1 * t396 * t143 - t178;
const double t451 = 0.2e1 * t402 * t138 - t142 - 0.2e1 * t396 * t156 + t91;
const double t452 = t451 * t58;
const double t457 = -0.2e1 * t402 * t143 + t112 - t441 *  t71;
const double t458 = t457 * t58;
const double t465 = -0.2e1 * t384 * t169 + 0.2e1 * t396 * t174 + t147;
const double t471 = 0.2e1 * t402 * t169 - t173 - 0.2e1 * t396 * t183 - t133;
const double t472 = t471 * t58;
const double t478 = -0.2e1 * t402 * t174 + t51 + 0.2e1 * t384 * t183;
const double t479 = t478 * t58;
const double t483 = 0.1e1 + t34 * t383;
const double t484 = t483 * t199;
const double t485 = t484 *  t212;
const double t486 = t34 * t395;
const double t488 = -t485 + t486 * t205;
const double t490 = t34 * t401;
const double t495 = t486 * t28;
const double t496 = t490 * t201 / 0.2e1 - t486 * t216 / 0.2e1 + t495;
const double t497 = t496 * t58;
const double t501 = 2 * t71 * t71;
const double t504 = t483 * t28;
const double t505 = -t490 * t205 / 0.2e1 + t484 *  t501 / 0.2e1 - t504;
const double t506 = t505 * t58;
const double t513 = -t484 *  t241 / 0.2e1 + t486 * t236 / 0.2e1 - t495;
const double t517 = t490 * t233 - t486 * t243;
const double t518 = t517 * t58 / 0.2e1;
const double t522 = t490 * t28;
const double t525 = -t490 * t236 / 0.2e1 + t522 + t484 *  t223 / 0.2e1;
const double t526 = t525 * t58;
const double t533 = -t484 *  t266 / 0.2e1 + t504 + t486 * t261 / 0.2e1;
const double t539 = t490 * t258 / 0.2e1 - t522 - t486 * t269 / 0.2e1;
const double t540 = t539 * t58;
const double t543 = -t490 * t261 + t485;
const double t544 = t543 * t58 / 0.2e1;
const double t549 = t504 *  t29 - t486 * t45;
const double t553 = -t490 * t30 + t486 * t72;
const double t554 = t553 * t58;
const double t558 = t490 * t45 - t504 *  t71;
const double t559 = t558 * t58;
const double t562 = t399 * t58;
const double t567 = t421 * t58;
const double t572 = t445 * t58;
const double t577 = t465 * t58;
const double t582 = t488 * t58 / 0.2e1;
const double t587 = t513 * t58;
const double t592 = t533 * t58;
const double t597 = t549 * t58;
const double t634 = t392 + t394;
const double t635 = t7 * t634;
const double t638 = -t65 - t382;
const double t639 = t7 * t638;
const double t643 = (-0.2e1 * t639 * v2x0 - t387) * t28;
const double t645 = -0.2e1 * t635 * t31 + t142 - t643 *  t44;
const double t647 = t39 - t41;
const double t648 = t7 * t647;
const double t652 = 0.2e1 * t648 * t31 - t173 + t643 *  t71;
const double t653 = t652 * t58;
const double t659 = -0.2e1 * t648 * t46 + t51 + 0.2e1 * t635 * t73 - t125;
const double t660 = t659 * t58;
const double t668 = (-0.2e1 * t639 * v2x1 - t117) * t28;
const double t670 = -0.2e1 * t635 * t101 + t173 - t668 *  t44;
const double t675 = 0.2e1 * t648 * t101 + t142 + t668 *  t71;
const double t676 = t675 * t58;
const double t682 = -0.2e1 * t648 * t107 - t112 + 0.2e1 * t635 * t121 - t77;
const double t683 = t682 * t58;
const double t690 = -0.2e1 * t635 * t138 + t37 + 0.2e1 * t639 * t143;
const double t696 = 0.2e1 * t648 * t138 - t106 - 0.2e1 * t639 * t156;
const double t697 = t696 * t58;
const double t703 = -0.2e1 * t648 * t143 + t147 + 0.2e1 * t635 * t156 - t91;
const double t704 = t703 * t58;
const double t711 = -0.2e1 * t635 * t169 + t106 + 0.2e1 * t639 * t174;
const double t717 = 0.2e1 * t648 * t169 + t37 - 0.2e1 * t639 * t183;
const double t718 = t717 * t58;
const double t724 = -0.2e1 * t648 * t174 - t178 + 0.2e1 * t635 * t183 - t133;
const double t725 = t724 * t58;
const double t728 = t34 * t634;
const double t731 = 0.1e1 + t34 * t638;
const double t732 = t731 * t199;
const double t733 = t732 *  t223;
const double t734 = -t728 * t201 + t733;
const double t736 = t34 * t647;
const double t741 = t731 * t28;
const double t742 = t736 * t201 / 0.2e1 - t732 *  t501 / 0.2e1 + t741;
const double t743 = t742 * t58;
const double t749 = t728 * t28;
const double t750 = -t736 * t205 / 0.2e1 + t728 * t216 / 0.2e1 - t749;
const double t751 = t750 * t58;
const double t758 = -t728 * t233 / 0.2e1 + t732 *  t248 / 0.2e1 - t741;
const double t761 = t736 * t233 - t733;
const double t762 = t761 * t58 / 0.2e1;
const double t766 = t736 * t28;
const double t769 = -t736 * t236 / 0.2e1 + t766 + t728 * t243 / 0.2e1;
const double t770 = t769 * t58;
const double t777 = -t728 * t258 / 0.2e1 + t749 + t732 *  t241 / 0.2e1;
const double t783 = t736 * t258 / 0.2e1 - t766 - t732 *  t212 / 0.2e1;
const double t784 = t783 * t58;
const double t788 = -t736 * t261 + t728 * t269;
const double t789 = t788 * t58 / 0.2e1;
const double t794 = t728 * t30 - t741 *  t44;
const double t798 = -t736 * t30 + t741 *  t71;
const double t799 = t798 * t58;
const double t803 = t736 * t45 - t728 * t72;
const double t804 = t803 * t58;
const double t807 = t645 * t58;
const double t812 = t670 * t58;
const double t817 = t690 * t58;
const double t822 = t711 * t58;
const double t827 = t734 * t58 / 0.2e1;
const double t832 = t758 * t58;
const double t837 = t777 * t58;
const double t842 = t794 * t58;
cg[8*0 + 0] = t52 * t63 + t79 * t84 + t93 * t98;
cg[8*0 + 1] = t113 * t63 + t127 * t84 + t135 * t98;
cg[8*0 + 2] = t148 * t63 + t160 * t84 + t166 * t98;
cg[8*0 + 3] = t179 * t63 + t187 * t84 + t194 * t98;
cg[8*0 + 4] = t207 * t63 / 0.2e1 + t221 * t84 + t230 * t98;
cg[8*0 + 5] = t239 * t63 + t246 * t84 + t255 * t98;
cg[8*0 + 6] = t264 * t63 + t273 * t84 + t277 * t98;
cg[8*0 + 7] = t282 * t63 + t287 * t84 + t292 * t98;
cg[8*1 + 0] = t295 * t296 + t78 * t301 + t93 * t307;
cg[8*1 + 1] = t310 * t296 + t126 * t301 + t135 * t307;
cg[8*1 + 2] = t315 * t296 + t159 * t301 + t166 * t307;
cg[8*1 + 3] = t320 * t296 + t186 * t301 + t194 * t307;
cg[8*1 + 4] = t325 * t296 + t220 * t301 + t230 * t307;
cg[8*1 + 5] = t330 * t296 + t245 * t301 / 0.2e1 + t255 * t307;
cg[8*1 + 6] = t335 * t296 + t272 * t301 + t277 * t307;
cg[8*1 + 7] = t340 * t296 + t286 * t301 + t292 * t307;
cg[8*2 + 0] = t295 * t345 + t79 * t347 + t92 * t351;
cg[8*2 + 1] = t310 * t345 + t127 * t347 + t134 * t351;
cg[8*2 + 2] = t315 * t345 + t160 * t347 + t165 * t351;
cg[8*2 + 3] = t320 * t345 + t187 * t347 + t193 * t351;
cg[8*2 + 4] = t325 * t345 + t221 * t347 + t229 * t351;
cg[8*2 + 5] = t330 * t345 + t246 * t347 + t254 * t351;
cg[8*2 + 6] = t335 * t345 + t273 * t347 + t276 * t351 / 0.2e1;
cg[8*2 + 7] = t340 * t345 + t287 * t347 + t291 * t351;
cg[8*3 + 0] = t399 * t63 + t408 * t84 + t414 * t98;
cg[8*3 + 1] = t421 * t63 + t428 * t84 + t435 * t98;
cg[8*3 + 2] = t445 * t63 + t452 * t84 + t458 * t98;
cg[8*3 + 3] = t465 * t63 + t472 * t84 + t479 * t98;
cg[8*3 + 4] = t488 * t63 / 0.2e1 + t497 * t84 + t506 * t98;
cg[8*3 + 5] = t513 * t63 + t518 * t84 + t526 * t98;
cg[8*3 + 6] = t533 * t63 + t540 * t84 + t544 * t98;
cg[8*3 + 7] = t549 * t63 + t554 * t84 + t559 * t98;
cg[8*4 + 0] = t562 * t296 + t407 * t301 + t414 * t307;
cg[8*4 + 1] = t567 * t296 + t427 * t301 + t435 * t307;
cg[8*4 + 2] = t572 * t296 + t451 * t301 + t458 * t307;
cg[8*4 + 3] = t577 * t296 + t471 * t301 + t479 * t307;
cg[8*4 + 4] = t582 * t296 + t496 * t301 + t506 * t307;
cg[8*4 + 5] = t587 * t296 + t517 * t301 / 0.2e1 + t526 * t307;
cg[8*4 + 6] = t592 * t296 + t539 * t301 + t544 * t307;
cg[8*4 + 7] = t597 * t296 + t553 * t301 + t559 * t307;
cg[8*5 + 0] = t562 * t345 + t408 * t347 + t413 * t351;
cg[8*5 + 1] = t567 * t345 + t428 * t347 + t434 * t351;
cg[8*5 + 2] = t572 * t345 + t452 * t347 + t457 * t351;
cg[8*5 + 3] = t577 * t345 + t472 * t347 + t478 * t351;
cg[8*5 + 4] = t582 * t345 + t497 * t347 + t505 * t351;
cg[8*5 + 5] = t587 * t345 + t518 * t347 + t525 * t351;
cg[8*5 + 6] = t592 * t345 + t540 * t347 + t543 * t351 / 0.2e1;
cg[8*5 + 7] = t597 * t345 + t554 * t347 + t558 * t351;
cg[8*6 + 0] = t645 * t63 + t653 * t84 + t660 * t98;
cg[8*6 + 1] = t670 * t63 + t676 * t84 + t683 * t98;
cg[8*6 + 2] = t690 * t63 + t697 * t84 + t704 * t98;
cg[8*6 + 3] = t711 * t63 + t718 * t84 + t725 * t98;
cg[8*6 + 4] = t734 * t63 / 0.2e1 + t743 * t84 + t751 * t98;
cg[8*6 + 5] = t758 * t63 + t762 * t84 + t770 * t98;
cg[8*6 + 6] = t777 * t63 + t784 * t84 + t789 * t98;
cg[8*6 + 7] = t794 * t63 + t799 * t84 + t804 * t98;
cg[8*7 + 0] = t807 * t296 + t652 * t301 + t660 * t307;
cg[8*7 + 1] = t812 * t296 + t675 * t301 + t683 * t307;
cg[8*7 + 2] = t817 * t296 + t696 * t301 + t704 * t307;
cg[8*7 + 3] = t822 * t296 + t717 * t301 + t725 * t307;
cg[8*7 + 4] = t827 * t296 + t742 * t301 + t751 * t307;
cg[8*7 + 5] = t832 * t296 + t761 * t301 / 0.2e1 + t770 * t307;
cg[8*7 + 6] = t837 * t296 + t783 * t301 + t789 * t307;
cg[8*7 + 7] = t842 * t296 + t798 * t301 + t804 * t307;
cg[8*8 + 0] = t807 * t345 + t653 * t347 + t659 * t351;
cg[8*8 + 1] = t812 * t345 + t676 * t347 + t682 * t351;
cg[8*8 + 2] = t817 * t345 + t697 * t347 + t703 * t351;
cg[8*8 + 3] = t822 * t345 + t718 * t347 + t724 * t351;
cg[8*8 + 4] = t827 * t345 + t743 * t347 + t750 * t351;
cg[8*8 + 5] = t832 * t345 + t762 * t347 + t769 * t351;
cg[8*8 + 6] = t837 * t345 + t784 * t347 + t788 * t351 / 0.2e1;
cg[8*8 + 7] = t842 * t345 + t799 * t347 + t803 * t351;
}


