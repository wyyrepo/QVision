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

#include <qvsfm/qvgea/so3EssentialEvaluation.h>
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
Norm2 := V -> sqrt(V(1)^2 + V(2)^2 + V(3)^2):
CrossProductMatrix := V -> Matrix([[0, -V(3), V(2)], [V(3), 0, -V(1)], [-V(2), V(1), 0]]):

# R =	cos(v_t)*I +
#	(sin(v_t)/v_t) * v.crossProductMatrix() +
#	((1-cos(v_t))/ (v_t * v_t) )* v.toColumnMatrix() * v.toRowMatrix();
I3 := Matrix([[1,0,0],[0,1,0],[0,0,1]]):
Ang := V -> Norm2(V) + Epsi:
expSO3 := V -> cos(Ang(V)).I3 + (sin(Ang(V))/Ang(V)) . CrossProductMatrix(V) + (1-cos(Ang(V)))/(Ang(V) Ang(V)) . V . Transpose(V):

###################
# Epipolar expression.
#
# The essential matrix is expressed related to two cameras, defined by the vectors
#
#	[v1x0, v1x1, v1x2, v1x3, v1x4, v1x5]
#
#	and
#
#	[v2x0, v2x1, v2x2, v2x3, v2x4, v2x5]
#
R1 := expSO3(Vector([v1x0, v1x1, v1x2])):
R2 := expSO3(Vector([v2x0, v2x1, v2x2])):
c1 := Vector([v1x3, v1x4, v1x5]):
c2 := Vector([v2x3, v2x4, v2x5]):
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
[ diff(vectorE(1), v1x0), diff(vectorE(1), v1x1), diff(vectorE(1), v1x2), diff(vectorE(1), v1x3), diff(vectorE(1), v1x4), diff(vectorE(1), v1x5), diff(vectorE(1), v2x0), diff(vectorE(1), v2x1), diff(vectorE(1), v2x2), diff(vectorE(1), v2x3), diff(vectorE(1), v2x4), diff(vectorE(1), v2x5), vectorE(1) ],
[ diff(vectorE(2), v1x0), diff(vectorE(2), v1x1), diff(vectorE(2), v1x2), diff(vectorE(2), v1x3), diff(vectorE(2), v1x4), diff(vectorE(2), v1x5), diff(vectorE(2), v2x0), diff(vectorE(2), v2x1), diff(vectorE(2), v2x2), diff(vectorE(2), v2x3), diff(vectorE(2), v2x4), diff(vectorE(2), v2x5), vectorE(2) ],
[ diff(vectorE(3), v1x0), diff(vectorE(3), v1x1), diff(vectorE(3), v1x2), diff(vectorE(3), v1x3), diff(vectorE(3), v1x4), diff(vectorE(3), v1x5), diff(vectorE(3), v2x0), diff(vectorE(3), v2x1), diff(vectorE(3), v2x2), diff(vectorE(3), v2x3), diff(vectorE(3), v2x4), diff(vectorE(3), v2x5), vectorE(3) ],
[ diff(vectorE(4), v1x0), diff(vectorE(4), v1x1), diff(vectorE(4), v1x2), diff(vectorE(4), v1x3), diff(vectorE(4), v1x4), diff(vectorE(4), v1x5), diff(vectorE(4), v2x0), diff(vectorE(4), v2x1), diff(vectorE(4), v2x2), diff(vectorE(4), v2x3), diff(vectorE(4), v2x4), diff(vectorE(4), v2x5), vectorE(4) ],
[ diff(vectorE(5), v1x0), diff(vectorE(5), v1x1), diff(vectorE(5), v1x2), diff(vectorE(5), v1x3), diff(vectorE(5), v1x4), diff(vectorE(5), v1x5), diff(vectorE(5), v2x0), diff(vectorE(5), v2x1), diff(vectorE(5), v2x2), diff(vectorE(5), v2x3), diff(vectorE(5), v2x4), diff(vectorE(5), v2x5), vectorE(5) ],
[ diff(vectorE(6), v1x0), diff(vectorE(6), v1x1), diff(vectorE(6), v1x2), diff(vectorE(6), v1x3), diff(vectorE(6), v1x4), diff(vectorE(6), v1x5), diff(vectorE(6), v2x0), diff(vectorE(6), v2x1), diff(vectorE(6), v2x2), diff(vectorE(6), v2x3), diff(vectorE(6), v2x4), diff(vectorE(6), v2x5), vectorE(6) ],
[ diff(vectorE(7), v1x0), diff(vectorE(7), v1x1), diff(vectorE(7), v1x2), diff(vectorE(7), v1x3), diff(vectorE(7), v1x4), diff(vectorE(7), v1x5), diff(vectorE(7), v2x0), diff(vectorE(7), v2x1), diff(vectorE(7), v2x2), diff(vectorE(7), v2x3), diff(vectorE(7), v2x4), diff(vectorE(7), v2x5), vectorE(7) ],
[ diff(vectorE(8), v1x0), diff(vectorE(8), v1x1), diff(vectorE(8), v1x2), diff(vectorE(8), v1x3), diff(vectorE(8), v1x4), diff(vectorE(8), v1x5), diff(vectorE(8), v2x0), diff(vectorE(8), v2x1), diff(vectorE(8), v2x2), diff(vectorE(8), v2x3), diff(vectorE(8), v2x4), diff(vectorE(8), v2x5), vectorE(8) ],
[ diff(vectorE(9), v1x0), diff(vectorE(9), v1x1), diff(vectorE(9), v1x2), diff(vectorE(9), v1x3), diff(vectorE(9), v1x4), diff(vectorE(9), v1x5), diff(vectorE(9), v2x0), diff(vectorE(9), v2x1), diff(vectorE(9), v2x2), diff(vectorE(9), v2x3), diff(vectorE(9), v2x4), diff(vectorE(9), v2x5), vectorE(9) ]
]):

###################
# Display the C code to evaluate the previous matrix
#
CodeGeneration[C](M, optimize = true);

*/

void so3EssentialEvaluation(const double *pose1, const double *pose2, double *cg0, const double Epsi)
{
const double
        v1x0 = pose1[0],
        v1x1 = pose1[1],
        v1x2 = pose1[2],
        v1x3 = pose1[3],
        v1x4 = pose1[4],
        v1x5 = pose1[5];

const double
        v2x0 = pose2[0],
        v2x1 = pose2[1],
        v2x2 = pose2[2],
        v2x3 = pose2[3],
        v2x4 = pose2[4],
        v2x5 = pose2[5];

    const double t1 = v2x0 * v2x0;
    const double t2 = v2x1 * v2x1;
    const double t3 = v2x2 * v2x2;
    const double t5 = sqrt(t1 + t2 + t3);
    const double t6 = t5 + Epsi;
    const double t7 = sin(t6);
    const double t8 = 0.1e1 / t6;
    const double t9 = t7 * t8;
    const double t10 = t9 * v2x2;
    const double t11 = cos(t6);
    const double t12 = 0.1e1 - t11;
    const double t13 = t6 * t6;
    const double t14 = 0.1e1 / t13;
    const double t15 = t12 * t14;
    const double t17 = t15 * v2x0 * v2x1;
    const double t18 = -t10 + t17;
    const double t19 = (v2x3 * v2x3);
    const double t22 = (v1x3 * v1x3);
    const double t23 = (v2x4 * v2x4);
    const double t26 = (v1x4 * v1x4);
    const double t27 = (v2x5 * v2x5);
    const double t30 = (v1x5 * v1x5);
    const double t31 = t19 - 2 * v2x3 * v1x3 + t22 + t23 - 2 * v2x4 * v1x4 + t26 + t27 - 2 * v2x5 * v1x5 + t30;
    const double t32 = sqrt(t31);
    const double t33 = 0.1e1 / t32;
    const double t34 = t18 * t33;
    const double t35 = v2x5 - v1x5;
    const double t37 = t9 * v2x1;
    const double t39 = t15 * v2x0 * v2x2;
    const double t40 = t37 + t39;
    const double t41 = t40 * t33;
    const double t42 = v2x4 - v1x4;
    const double t44 = t34 * t35 - t41 * t42;
    const double t45 = v1x0 * v1x0;
    const double t46 = v1x1 * v1x1;
    const double t47 = v1x2 * v1x2;
    const double t49 = sqrt(t45 + t46 + t47);
    const double t50 = t49 + Epsi;
    const double t51 = sin(t50);
    const double t52 = 0.1e1 / t49;
    const double t53 = t51 * t52;
    const double t54 = t53 * v1x0;
    const double t55 = t45 * v1x0;
    const double t56 = t50 * t50;
    const double t57 = 0.1e1 / t56;
    const double t60 = cos(t50);
    const double t61 = 0.1e1 - t60;
    const double t64 = t61 / t56 / t50;
    const double t68 = t61 * t57;
    const double t69 = t68 * v1x0;
    const double t71 = -t54 + t53 * t55 * t57 - 0.2e1 * t64 * t55 * t52 + 0.2e1 * t69;
    const double t74 = t11 + t15 * t1;
    const double t75 = t74 * t33;
    const double t77 = v2x3 - v1x3;
    const double t79 = -t75 * t35 + t41 * t77;
    const double t80 = t60 * t52;
    const double t81 = 0.1e1 / t50;
    const double t82 = v1x0 * t81;
    const double t84 = t80 * t82 * v1x2;
    const double t85 = t51 * t57;
    const double t86 = v1x2 * t52;
    const double t88 = t85 * t86 * v1x0;
    const double t89 = t45 * t57;
    const double t91 = t53 * t89 * v1x1;
    const double t95 = 0.2e1 * t64 * t45 * v1x1 * t52;
    const double t96 = t68 * v1x1;
    const double t97 = -t84 + t88 + t91 - t95 + t96;
    const double t101 = t75 * t42 - t34 * t77;
    const double t103 = t80 * t82 * v1x1;
    const double t106 = t85 * v1x1 * t52 * v1x0;
    const double t108 = t53 * t89 * v1x2;
    const double t112 = 0.2e1 * t64 * t45 * v1x2 * t52;
    const double t113 = t68 * v1x2;
    const double t114 = t103 - t106 + t108 - t112 + t113;
    const double t117 = t53 * v1x1;
    const double t118 = -t117 + t91 - t95;
    const double t122 = t80 * v1x1 * t81 * v1x2;
    const double t123 = t86 * v1x1;
    const double t124 = t85 * t123;
    const double t125 = t46 * t57;
    const double t127 = t53 * t125 * v1x0;
    const double t131 = 0.2e1 * t64 * v1x0 * t46 * t52;
    const double t132 = -t122 + t124 + t127 - t131 + t69;
    const double t135 = t80 * t46 * t81;
    const double t137 = t85 * t46 * t52;
    const double t138 = t51 * t81;
    const double t141 = t117 * t57 * v1x0 * v1x2;
    const double t144 = 0.2e1 * t64 * v1x0 * t123;
    const double t145 = t135 - t137 + t138 + t141 - t144;
    const double t148 = t53 * v1x2;
    const double t149 = -t148 + t108 - t112;
    const double t152 = t80 * t47 * t81;
    const double t154 = t85 * t47 * t52;
    const double t155 = -t152 + t154 - t138 + t141 - t144;
    const double t157 = t47 * t57;
    const double t159 = t53 * t157 * v1x0;
    const double t163 = 0.2e1 * t64 * v1x0 * t47 * t52;
    const double t164 = t122 - t124 + t159 - t163 + t69;
    const double t168 = 0.1e1 / t32 / t31;
    const double t169 = t18 * t168;
    const double t170 = -2 * t35 * t77;
    const double t171 = t169 * t170;
    const double t172 = t40 * t168;
    const double t173 = -2 * t42 * t77;
    const double t174 = t172 * t173;
    const double t175 = -t171 + t174;
    const double t177 = t60 + t68 * t45;
    const double t179 = t74 * t168;
    const double t182 = -2 * t77 * t77;
    const double t185 = t179 * t170 / 0.2e1 - t172 * t182 / 0.2e1 - t41;
    const double t186 = t138 * v1x2;
    const double t188 = t68 * v1x0 * v1x1;
    const double t189 = -t186 + t188;
    const double t195 = -t179 * t173 / 0.2e1 + t169 * t182 / 0.2e1 + t34;
    const double t196 = t138 * v1x1;
    const double t198 = t68 * v1x0 * v1x2;
    const double t199 = t196 + t198;
    const double t202 = -2 * t35 * t42;
    const double t205 = -2 * t42 * t42;
    const double t208 = -t169 * t202 / 0.2e1 + t172 * t205 / 0.2e1 + t41;
    const double t210 = t179 * t202;
    const double t211 = t210 - t174;
    const double t217 = -t179 * t205 / 0.2e1 - t75 + t169 * t173 / 0.2e1;
    const double t220 = -2 * t35 * t35;
    const double t225 = -t169 * t220 / 0.2e1 - t34 + t172 * t202 / 0.2e1;
    const double t231 = t179 * t220 / 0.2e1 + t75 - t172 * t170 / 0.2e1;
    const double t233 = -t210 + t171;
    const double t236 = 0.1e1 / t5;
    const double t237 = t11 * t236;
    const double t238 = v2x0 * t8;
    const double t240 = t237 * t238 * v2x2;
    const double t241 = t7 * t14;
    const double t242 = v2x2 * t236;
    const double t244 = t241 * t242 * v2x0;
    const double t245 = t7 * t236;
    const double t246 = t1 * t14;
    const double t248 = t245 * t246 * v2x1;
    const double t251 = t12 / t13 / t6;
    const double t255 = 0.2e1 * t251 * t1 * v2x1 * t236;
    const double t256 = t15 * v2x1;
    const double t258 = (-t240 + t244 + t248 - t255 + t256) * t33;
    const double t261 = t237 * t238 * v2x1;
    const double t264 = t241 * v2x1 * t236 * v2x0;
    const double t266 = t245 * t246 * v2x2;
    const double t270 = 0.2e1 * t251 * t1 * v2x2 * t236;
    const double t271 = t15 * v2x2;
    const double t273 = (t261 - t264 + t266 - t270 + t271) * t33;
    const double t275 = t258 * t35 - t273 * t42;
    const double t277 = t245 * v2x0;
    const double t278 = t1 * v2x0;
    const double t284 = t15 * v2x0;
    const double t287 = (-t277 + t245 * t278 * t14 - 0.2e1 * t251 * t278 * t236 + 0.2e1 * t284) * t33;
    const double t290 = -t287 * t35 + t273 * t77;
    const double t294 = t287 * t42 - t258 * t77;
    const double t299 = t237 * v2x1 * t8 * v2x2;
    const double t300 = t242 * v2x1;
    const double t301 = t241 * t300;
    const double t302 = t2 * t14;
    const double t304 = t245 * t302 * v2x0;
    const double t308 = 0.2e1 * t251 * v2x0 * t2 * t236;
    const double t310 = (-t299 + t301 + t304 - t308 + t284) * t33;
    const double t313 = t237 * t2 * t8;
    const double t315 = t241 * t2 * t236;
    const double t316 = t245 * v2x1;
    const double t319 = t316 * t14 * v2x0 * v2x2;
    const double t322 = 0.2e1 * t251 * v2x0 * t300;
    const double t324 = (t313 - t315 + t9 + t319 - t322) * t33;
    const double t326 = t310 * t35 - t324 * t42;
    const double t329 = (-t316 + t248 - t255) * t33;
    const double t332 = -t329 * t35 + t324 * t77;
    const double t336 = t329 * t42 - t310 * t77;
    const double t340 = t237 * t3 * t8;
    const double t342 = t241 * t3 * t236;
    const double t344 = (-t340 + t342 - t9 + t319 - t322) * t33;
    const double t346 = t3 * t14;
    const double t348 = t245 * t346 * v2x0;
    const double t352 = 0.2e1 * t251 * v2x0 * t3 * t236;
    const double t354 = (t299 - t301 + t348 - t352 + t284) * t33;
    const double t356 = t344 * t35 - t354 * t42;
    const double t358 = t245 * v2x2;
    const double t360 = (-t358 + t266 - t270) * t33;
    const double t363 = -t360 * t35 + t354 * t77;
    const double t367 = t360 * t42 - t344 * t77;
    const double t370 = 2 * t35 * t77;
    const double t371 = t169 * t370;
    const double t372 = 2 * t42 * t77;
    const double t373 = t172 * t372;
    const double t374 = -t371 + t373;
    const double t378 = 2 * t77 * t77;
    const double t381 = t179 * t370 / 0.2e1 - t172 * t378 / 0.2e1 + t41;
    const double t387 = -t179 * t372 / 0.2e1 + t169 * t378 / 0.2e1 - t34;
    const double t390 = 2 * t35 * t42;
    const double t393 = 2 * t42 * t42;
    const double t396 = -t169 * t390 / 0.2e1 + t172 * t393 / 0.2e1 - t41;
    const double t398 = t179 * t390;
    const double t399 = t398 - t373;
    const double t405 = -t179 * t393 / 0.2e1 + t75 + t169 * t372 / 0.2e1;
    const double t408 = 2 * t35 * t35;
    const double t413 = -t169 * t408 / 0.2e1 + t34 + t172 * t390 / 0.2e1;
    const double t419 = t179 * t408 / 0.2e1 - t75 - t172 * t370 / 0.2e1;
    const double t421 = -t398 + t371;
    const double t428 = t84 - t88 + t91 - t95 + t96;
    const double t430 = -t54 + t127 - t131;
    const double t433 = t80 * t45 * t81;
    const double t435 = t85 * t45 * t52;
    const double t436 = -t433 + t435 - t138 + t141 - t144;
    const double t439 = t122 - t124 + t127 - t131 + t69;
    const double t441 = t46 * v1x1;
    const double t448 = -t117 + t53 * t441 * t57 - 0.2e1 * t64 * t441 * t52 + 0.2e1 * t96;
    const double t451 = t53 * t125 * v1x2;
    const double t455 = 0.2e1 * t64 * t46 * v1x2 * t52;
    const double t456 = -t103 + t106 + t451 - t455 + t113;
    const double t459 = t152 - t154 + t138 + t141 - t144;
    const double t461 = -t148 + t451 - t455;
    const double t464 = t53 * t157 * v1x1;
    const double t468 = 0.2e1 * t64 * v1x1 * t47 * t52;
    const double t469 = -t84 + t88 + t464 - t468 + t96;
    const double t472 = t186 + t188;
    const double t475 = t60 + t68 * t46;
    const double t477 = t138 * v1x0;
    const double t479 = t68 * v1x1 * v1x2;
    const double t480 = -t477 + t479;
    const double t519 = -t103 + t106 + t108 - t112 + t113;
    const double t521 = t433 - t435 + t138 + t141 - t144;
    const double t523 = -t54 + t159 - t163;
    const double t526 = -t135 + t137 - t138 + t141 - t144;
    const double t528 = t103 - t106 + t451 - t455 + t113;
    const double t530 = -t117 + t464 - t468;
    const double t533 = -t122 + t124 + t159 - t163 + t69;
    const double t535 = t84 - t88 + t464 - t468 + t96;
    const double t537 = t47 * v1x2;
    const double t544 = -t148 + t53 * t537 * t57 - 0.2e1 * t64 * t537 * t52 + 0.2e1 * t113;
    const double t547 = -t196 + t198;
    const double t549 = t477 + t479;
    const double t552 = t60 + t68 * t47;
    const double t592 = t11 + t15 * t2;
    const double t593 = t592 * t33;
    const double t595 = t9 * v2x0;
    const double t597 = t15 * v2x1 * v2x2;
    const double t598 = -t595 + t597;
    const double t599 = t598 * t33;
    const double t601 = t593 * t35 - t599 * t42;
    const double t603 = t10 + t17;
    const double t604 = t603 * t33;
    const double t607 = -t604 * t35 + t599 * t77;
    const double t611 = t604 * t42 - t593 * t77;
    const double t622 = t592 * t168;
    const double t623 = t622 * t170;
    const double t624 = t598 * t168;
    const double t625 = t624 * t173;
    const double t626 = -t623 + t625;
    const double t628 = t603 * t168;
    const double t633 = t628 * t170 / 0.2e1 - t624 * t182 / 0.2e1 - t599;
    const double t639 = -t628 * t173 / 0.2e1 + t622 * t182 / 0.2e1 + t593;
    const double t646 = -t622 * t202 / 0.2e1 + t624 * t205 / 0.2e1 + t599;
    const double t648 = t628 * t202;
    const double t649 = t648 - t625;
    const double t655 = -t628 * t205 / 0.2e1 - t604 + t622 * t173 / 0.2e1;
    const double t662 = -t622 * t220 / 0.2e1 - t593 + t624 * t202 / 0.2e1;
    const double t668 = t628 * t220 / 0.2e1 + t604 - t624 * t170 / 0.2e1;
    const double t670 = -t648 + t623;
    const double t674 = (-t277 + t304 - t308) * t33;
    const double t677 = t237 * t1 * t8;
    const double t679 = t241 * t1 * t236;
    const double t681 = (-t677 + t679 - t9 + t319 - t322) * t33;
    const double t683 = t674 * t35 - t681 * t42;
    const double t686 = (t240 - t244 + t248 - t255 + t256) * t33;
    const double t689 = -t686 * t35 + t681 * t77;
    const double t693 = t686 * t42 - t674 * t77;
    const double t696 = t2 * v2x1;
    const double t704 = (-t316 + t245 * t696 * t14 - 0.2e1 * t251 * t696 * t236 + 0.2e1 * t256) * t33;
    const double t707 = t245 * t302 * v2x2;
    const double t711 = 0.2e1 * t251 * t2 * v2x2 * t236;
    const double t713 = (-t261 + t264 + t707 - t711 + t271) * t33;
    const double t715 = t704 * t35 - t713 * t42;
    const double t718 = (t299 - t301 + t304 - t308 + t284) * t33;
    const double t721 = -t718 * t35 + t713 * t77;
    const double t725 = t718 * t42 - t704 * t77;
    const double t729 = (-t358 + t707 - t711) * t33;
    const double t732 = t245 * t346 * v2x1;
    const double t736 = 0.2e1 * t251 * v2x1 * t3 * t236;
    const double t738 = (-t240 + t244 + t732 - t736 + t256) * t33;
    const double t740 = t729 * t35 - t738 * t42;
    const double t743 = (t340 - t342 + t9 + t319 - t322) * t33;
    const double t746 = -t743 * t35 + t738 * t77;
    const double t750 = t743 * t42 - t729 * t77;
    const double t753 = t622 * t370;
    const double t754 = t624 * t372;
    const double t755 = -t753 + t754;
    const double t761 = t628 * t370 / 0.2e1 - t624 * t378 / 0.2e1 + t599;
    const double t767 = -t628 * t372 / 0.2e1 + t622 * t378 / 0.2e1 - t593;
    const double t774 = -t622 * t390 / 0.2e1 + t624 * t393 / 0.2e1 - t599;
    const double t776 = t628 * t390;
    const double t777 = t776 - t754;
    const double t783 = -t628 * t393 / 0.2e1 + t604 + t622 * t372 / 0.2e1;
    const double t790 = -t622 * t408 / 0.2e1 + t593 + t624 * t390 / 0.2e1;
    const double t796 = t628 * t408 / 0.2e1 - t604 - t624 * t370 / 0.2e1;
    const double t798 = -t776 + t753;
    const double t909 = t595 + t597;
    const double t910 = t909 * t33;
    const double t913 = t11 + t15 * t3;
    const double t914 = t913 * t33;
    const double t916 = t910 * t35 - t914 * t42;
    const double t918 = -t37 + t39;
    const double t919 = t918 * t33;
    const double t922 = -t919 * t35 + t914 * t77;
    const double t926 = t919 * t42 - t910 * t77;
    const double t937 = t909 * t168;
    const double t938 = t937 * t170;
    const double t939 = t913 * t168;
    const double t940 = t939 * t173;
    const double t941 = -t938 + t940;
    const double t943 = t918 * t168;
    const double t948 = t943 * t170 / 0.2e1 - t939 * t182 / 0.2e1 - t914;
    const double t954 = -t943 * t173 / 0.2e1 + t937 * t182 / 0.2e1 + t910;
    const double t961 = -t937 * t202 / 0.2e1 + t939 * t205 / 0.2e1 + t914;
    const double t963 = t943 * t202;
    const double t964 = t963 - t940;
    const double t970 = -t943 * t205 / 0.2e1 - t919 + t937 * t173 / 0.2e1;
    const double t977 = -t937 * t220 / 0.2e1 - t910 + t939 * t202 / 0.2e1;
    const double t983 = t943 * t220 / 0.2e1 + t919 - t939 * t170 / 0.2e1;
    const double t985 = -t963 + t938;
    const double t989 = (t677 - t679 + t9 + t319 - t322) * t33;
    const double t992 = (-t277 + t348 - t352) * t33;
    const double t994 = t989 * t35 - t992 * t42;
    const double t997 = (-t261 + t264 + t266 - t270 + t271) * t33;
    const double t1000 = -t997 * t35 + t992 * t77;
    const double t1004 = t997 * t42 - t989 * t77;
    const double t1008 = (t261 - t264 + t707 - t711 + t271) * t33;
    const double t1011 = (-t316 + t732 - t736) * t33;
    const double t1013 = t1008 * t35 - t1011 * t42;
    const double t1016 = (-t313 + t315 - t9 + t319 - t322) * t33;
    const double t1019 = -t1016 * t35 + t1011 * t77;
    const double t1023 = t1016 * t42 - t1008 * t77;
    const double t1027 = (t240 - t244 + t732 - t736 + t256) * t33;
    const double t1029 = t3 * v2x2;
    const double t1037 = (-t358 + t245 * t1029 * t14 - 0.2e1 * t251 * t1029 * t236 + 0.2e1 * t271) * t33;
    const double t1039 = t1027 * t35 - t1037 * t42;
    const double t1042 = (-t299 + t301 + t348 - t352 + t284) * t33;
    const double t1045 = -t1042 * t35 + t1037 * t77;
    const double t1049 = t1042 * t42 - t1027 * t77;
    const double t1052 = t937 * t370;
    const double t1053 = t939 * t372;
    const double t1054 = -t1052 + t1053;
    const double t1060 = t943 * t370 / 0.2e1 - t939 * t378 / 0.2e1 + t914;
    const double t1066 = -t943 * t372 / 0.2e1 + t937 * t378 / 0.2e1 - t910;
    const double t1073 = -t937 * t390 / 0.2e1 + t939 * t393 / 0.2e1 - t914;
    const double t1075 = t943 * t390;
    const double t1076 = t1075 - t1053;
    const double t1082 = -t943 * t393 / 0.2e1 + t919 + t937 * t372 / 0.2e1;
    const double t1089 = -t937 * t408 / 0.2e1 + t910 + t939 * t390 / 0.2e1;
    const double t1095 = t943 * t408 / 0.2e1 - t919 - t939 * t370 / 0.2e1;
    const double t1097 = -t1075 + t1052;

    cg0[13*0+0] = t44 * t71 + t79 * t97 + t101 * t114;
    cg0[13*0+1] = t44 * t118 + t79 * t132 + t101 * t145;
    cg0[13*0+2] = t44 * t149 + t79 * t155 + t101 * t164;
    cg0[13*0+3] = t175 * t177 / 0.2e1 + t185 * t189 + t195 * t199;
    cg0[13*0+4] = t208 * t177 + t211 * t189 / 0.2e1 + t217 * t199;
    cg0[13*0+5] = t225 * t177 + t231 * t189 + t233 * t199 / 0.2e1;
    cg0[13*0+6] = t275 * t177 + t290 * t189 + t294 * t199;
    cg0[13*0+7] = t326 * t177 + t332 * t189 + t336 * t199;
    cg0[13*0+8] = t356 * t177 + t363 * t189 + t367 * t199;
    cg0[13*0+9] = t374 * t177 / 0.2e1 + t381 * t189 + t387 * t199;
    cg0[13*0+10] = t396 * t177 + t399 * t189 / 0.2e1 + t405 * t199;
    cg0[13*0+11] = t413 * t177 + t419 * t189 + t421 * t199 / 0.2e1;
    cg0[13*0+12] = t44 * t177 + t79 * t189 + t101 * t199;
    cg0[13*1+0] = t44 * t428 + t79 * t430 + t101 * t436;
    cg0[13*1+1] = t44 * t439 + t79 * t448 + t101 * t456;
    cg0[13*1+2] = t44 * t459 + t79 * t461 + t101 * t469;
    cg0[13*1+3] = t175 * t472 / 0.2e1 + t185 * t475 + t195 * t480;
    cg0[13*1+4] = t208 * t472 + t211 * t475 / 0.2e1 + t217 * t480;
    cg0[13*1+5] = t225 * t472 + t231 * t475 + t233 * t480 / 0.2e1;
    cg0[13*1+6] = t275 * t472 + t290 * t475 + t294 * t480;
    cg0[13*1+7] = t326 * t472 + t332 * t475 + t336 * t480;
    cg0[13*1+8] = t356 * t472 + t363 * t475 + t367 * t480;
    cg0[13*1+9] = t374 * t472 / 0.2e1 + t381 * t475 + t387 * t480;
    cg0[13*1+10] = t396 * t472 + t399 * t475 / 0.2e1 + t405 * t480;
    cg0[13*1+11] = t413 * t472 + t419 * t475 + t421 * t480 / 0.2e1;
    cg0[13*1+12] = t44 * t472 + t79 * t475 + t101 * t480;
    cg0[13*2+0] = t44 * t519 + t79 * t521 + t101 * t523;
    cg0[13*2+1] = t44 * t526 + t79 * t528 + t101 * t530;
    cg0[13*2+2] = t44 * t533 + t79 * t535 + t101 * t544;
    cg0[13*2+3] = t175 * t547 / 0.2e1 + t185 * t549 + t195 * t552;
    cg0[13*2+4] = t208 * t547 + t211 * t549 / 0.2e1 + t217 * t552;
    cg0[13*2+5] = t225 * t547 + t231 * t549 + t233 * t552 / 0.2e1;
    cg0[13*2+6] = t275 * t547 + t290 * t549 + t294 * t552;
    cg0[13*2+7] = t326 * t547 + t332 * t549 + t336 * t552;
    cg0[13*2+8] = t356 * t547 + t363 * t549 + t367 * t552;
    cg0[13*2+9] = t374 * t547 / 0.2e1 + t381 * t549 + t387 * t552;
    cg0[13*2+10] = t396 * t547 + t399 * t549 / 0.2e1 + t405 * t552;
    cg0[13*2+11] = t413 * t547 + t419 * t549 + t421 * t552 / 0.2e1;
    cg0[13*2+12] = t44 * t547 + t79 * t549 + t101 * t552;
    cg0[13*3+0] = t601 * t71 + t607 * t97 + t611 * t114;
    cg0[13*3+1] = t601 * t118 + t607 * t132 + t611 * t145;
    cg0[13*3+2] = t601 * t149 + t607 * t155 + t611 * t164;
    cg0[13*3+3] = t626 * t177 / 0.2e1 + t633 * t189 + t639 * t199;
    cg0[13*3+4] = t646 * t177 + t649 * t189 / 0.2e1 + t655 * t199;
    cg0[13*3+5] = t662 * t177 + t668 * t189 + t670 * t199 / 0.2e1;
    cg0[13*3+6] = t683 * t177 + t689 * t189 + t693 * t199;
    cg0[13*3+7] = t715 * t177 + t721 * t189 + t725 * t199;
    cg0[13*3+8] = t740 * t177 + t746 * t189 + t750 * t199;
    cg0[13*3+9] = t755 * t177 / 0.2e1 + t761 * t189 + t767 * t199;
    cg0[13*3+10] = t774 * t177 + t777 * t189 / 0.2e1 + t783 * t199;
    cg0[13*3+11] = t790 * t177 + t796 * t189 + t798 * t199 / 0.2e1;
    cg0[13*3+12] = t601 * t177 + t607 * t189 + t611 * t199;
    cg0[13*4+0] = t601 * t428 + t607 * t430 + t611 * t436;
    cg0[13*4+1] = t601 * t439 + t607 * t448 + t611 * t456;
    cg0[13*4+2] = t601 * t459 + t607 * t461 + t611 * t469;
    cg0[13*4+3] = t626 * t472 / 0.2e1 + t633 * t475 + t639 * t480;
    cg0[13*4+4] = t646 * t472 + t649 * t475 / 0.2e1 + t655 * t480;
    cg0[13*4+5] = t662 * t472 + t668 * t475 + t670 * t480 / 0.2e1;
    cg0[13*4+6] = t683 * t472 + t689 * t475 + t693 * t480;
    cg0[13*4+7] = t715 * t472 + t721 * t475 + t725 * t480;
    cg0[13*4+8] = t740 * t472 + t746 * t475 + t750 * t480;
    cg0[13*4+9] = t755 * t472 / 0.2e1 + t761 * t475 + t767 * t480;
    cg0[13*4+10] = t774 * t472 + t777 * t475 / 0.2e1 + t783 * t480;
    cg0[13*4+11] = t790 * t472 + t796 * t475 + t798 * t480 / 0.2e1;
    cg0[13*4+12] = t601 * t472 + t607 * t475 + t611 * t480;
    cg0[13*5+0] = t601 * t519 + t607 * t521 + t611 * t523;
    cg0[13*5+1] = t601 * t526 + t607 * t528 + t611 * t530;
    cg0[13*5+2] = t601 * t533 + t607 * t535 + t611 * t544;
    cg0[13*5+3] = t626 * t547 / 0.2e1 + t633 * t549 + t639 * t552;
    cg0[13*5+4] = t646 * t547 + t649 * t549 / 0.2e1 + t655 * t552;
    cg0[13*5+5] = t662 * t547 + t668 * t549 + t670 * t552 / 0.2e1;
    cg0[13*5+6] = t683 * t547 + t689 * t549 + t693 * t552;
    cg0[13*5+7] = t715 * t547 + t721 * t549 + t725 * t552;
    cg0[13*5+8] = t740 * t547 + t746 * t549 + t750 * t552;
    cg0[13*5+9] = t755 * t547 / 0.2e1 + t761 * t549 + t767 * t552;
    cg0[13*5+10] = t774 * t547 + t777 * t549 / 0.2e1 + t783 * t552;
    cg0[13*5+11] = t790 * t547 + t796 * t549 + t798 * t552 / 0.2e1;
    cg0[13*5+12] = t601 * t547 + t607 * t549 + t611 * t552;
    cg0[13*6+0] = t916 * t71 + t922 * t97 + t926 * t114;
    cg0[13*6+1] = t916 * t118 + t922 * t132 + t926 * t145;
    cg0[13*6+2] = t916 * t149 + t922 * t155 + t926 * t164;
    cg0[13*6+3] = t941 * t177 / 0.2e1 + t948 * t189 + t954 * t199;
    cg0[13*6+4] = t961 * t177 + t964 * t189 / 0.2e1 + t970 * t199;
    cg0[13*6+5] = t977 * t177 + t983 * t189 + t985 * t199 / 0.2e1;
    cg0[13*6+6] = t994 * t177 + t1000 * t189 + t1004 * t199;
    cg0[13*6+7] = t1013 * t177 + t1019 * t189 + t1023 * t199;
    cg0[13*6+8] = t1039 * t177 + t1045 * t189 + t1049 * t199;
    cg0[13*6+9] = t1054 * t177 / 0.2e1 + t1060 * t189 + t1066 * t199;
    cg0[13*6+10] = t1073 * t177 + t1076 * t189 / 0.2e1 + t1082 * t199;
    cg0[13*6+11] = t1089 * t177 + t1095 * t189 + t1097 * t199 / 0.2e1;
    cg0[13*6+12] = t916 * t177 + t922 * t189 + t926 * t199;
    cg0[13*7+0] = t916 * t428 + t922 * t430 + t926 * t436;
    cg0[13*7+1] = t916 * t439 + t922 * t448 + t926 * t456;
    cg0[13*7+2] = t916 * t459 + t922 * t461 + t926 * t469;
    cg0[13*7+3] = t941 * t472 / 0.2e1 + t948 * t475 + t954 * t480;
    cg0[13*7+4] = t961 * t472 + t964 * t475 / 0.2e1 + t970 * t480;
    cg0[13*7+5] = t977 * t472 + t983 * t475 + t985 * t480 / 0.2e1;
    cg0[13*7+6] = t994 * t472 + t1000 * t475 + t1004 * t480;
    cg0[13*7+7] = t1013 * t472 + t1019 * t475 + t1023 * t480;
    cg0[13*7+8] = t1039 * t472 + t1045 * t475 + t1049 * t480;
    cg0[13*7+9] = t1054 * t472 / 0.2e1 + t1060 * t475 + t1066 * t480;
    cg0[13*7+10] = t1073 * t472 + t1076 * t475 / 0.2e1 + t1082 * t480;
    cg0[13*7+11] = t1089 * t472 + t1095 * t475 + t1097 * t480 / 0.2e1;
    cg0[13*7+12] = t916 * t472 + t922 * t475 + t926 * t480;
    cg0[13*8+0] = t916 * t519 + t922 * t521 + t926 * t523;
    cg0[13*8+1] = t916 * t526 + t922 * t528 + t926 * t530;
    cg0[13*8+2] = t916 * t533 + t922 * t535 + t926 * t544;
    cg0[13*8+3] = t941 * t547 / 0.2e1 + t948 * t549 + t954 * t552;
    cg0[13*8+4] = t961 * t547 + t964 * t549 / 0.2e1 + t970 * t552;
    cg0[13*8+5] = t977 * t547 + t983 * t549 + t985 * t552 / 0.2e1;
    cg0[13*8+6] = t994 * t547 + t1000 * t549 + t1004 * t552;
    cg0[13*8+7] = t1013 * t547 + t1019 * t549 + t1023 * t552;
    cg0[13*8+8] = t1039 * t547 + t1045 * t549 + t1049 * t552;
    cg0[13*8+9] = t1054 * t547 / 0.2e1 + t1060 * t549 + t1066 * t552;
    cg0[13*8+10] = t1073 * t547 + t1076 * t549 / 0.2e1 + t1082 * t552;
    cg0[13*8+11] = t1089 * t547 + t1095 * t549 + t1097 * t552 / 0.2e1;
    cg0[13*8+12] = t916 * t547 + t922 * t549 + t926 * t552;
}

// -- test functions -----------------------------------------------------
// 3 expresiones para la matriz de rotación, a través del exponente en so3:
// (fuente: http://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula#Conversion_to_rotation_matrix)
//	Datos intermedios:
//		const QVMatrix I = QVMatrix::identity(3),
//		const QVMatrix kkT = k.toColumnMatrix() * k.toRowMatrix(),
//		const QVMatrix k_x = k.crossProductMatrix();
//	Rotaciones:
//		const QVMatrix R1 = cos(theta)*I+ sin(theta)*k_x + (1-cos(theta))*kkT;
//		const QVMatrix R2 = I + sin(theta)*k_x + (1-cos(theta))* k_x*k_x;
//		const QVMatrix R3 = I + sin(theta)*k_x + (1-cos(theta))*(kkT-I);
//
QVMatrix getRotation(const double r1, const double r2, const double r3, const double Epsi)
    {
    const double t1 = r1 * r1;
    const double t2 = r2 * r2;
    const double t3 = r3 * r3;
    const double t5 = sqrt(t1 + t2 + t3);
    const double t6 = t5 + Epsi;
    const double t7 = cos(t6);
    const double t9 = t6 * t6;
    const double t11 = (0.1e1 - t7) / t9;
    const double t14 = sin(t6);
    const double t16 = t14 / t6;
    const double t17 = t16 * r3;
    const double t19 = t11 * r1 * r2;
    const double t21 = t16 * r2;
    const double t23 = t11 * r1 * r3;
    const double t28 = t16 * r1;
    const double t30 = t11 * r2 * r3;

    double cg[3][3];
    cg[0][0] = t7 + t11 * t1;
    cg[0][1] = -t17 + t19;
    cg[0][2] = t21 + t23;
    cg[1][0] = t17 + t19;
    cg[1][1] = t7 + t11 * t2;
    cg[1][2] = -t28 + t30;
    cg[2][0] = -t21 + t23;
    cg[2][1] = t28 + t30;
    cg[2][2] = t7 + t11 * t3;

    QVMatrix R(3,3);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            R(i,j) = cg[i][j];
    return R;
    }

QVMatrix so3EssentialEvaluation_bis(const QVVector pose1, const QVVector pose2)
    {
    QVVector x;
    x << pose1;
    x << pose2;

    QuadraticFunction2 f;
    const QVVector e = f(x);
    const QVMatrix jacs2 = qvEstimateJacobian(f, x, 1e-6);
    return jacs2 | e;
    }

void test_so3EssentialEvaluation()
    {
    //#define EPSILON_LOCAL	1e-32

    srand(0);
    QV3DPointF	v1 = QVVector::random(3),
            v2 = QVVector::random(3),
            c1 = QVVector::random(3),
            c2 = QVVector::random(3);

    //const QVMatrix	R1 = expSO3(v1), R2 = expSO3(v2),
    //		R1bis = getRotation(v1[0], v1[1], v1[2], EPSILON_LOCAL),
    //		R2bis = getRotation(v2[0], v2[1], v2[2], EPSILON_LOCAL);

    //std::cout << "R1 = " << R1 << std::endl;
    //std::cout << "R1bis = " << R1bis << std::endl;
    //std::cout << "R2 = " << R2 << std::endl;
    //std::cout << "R2bis = " << R2bis << std::endl;

    // E = R2.CrossProductMatrix( (c2-c1) / Norm2(c2-c1)).Transpose(R1):
    //const QVMatrix E = R2 * ( (c2-c1) / (c2-c1).norm2() ).crossProductMatrix() * R1.transpose();

    QVVector pose1, pose2;
    pose1 << v1;
    pose1 << c1;

    pose2 << v2;
    pose2 << c2;

    QVMatrix jacs(9,13);
    so3EssentialEvaluation(pose1.data(), pose2.data(), jacs.getWriteData());

    const QVMatrix jacs2 = so3EssentialEvaluation_bis(pose1, pose2);
    //QVVector x;
    //x << v1;
    //x << c1;
    //x << v2;
    //x << c2;

    //QuadraticFunction2 f;
    //const QVVector e = f(x);
    //const QVMatrix jacs2 = qvEstimateJacobian(f, x, 1e-6);

    //std::cout << "E = " << QVVector(9, E.getReadData()) << std::endl;
    //std::cout << "e1 = " << jacs.getCol(12) << std::endl;
    //std::cout << "e2 = " << e << std::endl;

    //std::cout << "jacs 1 = " << jacs << std::endl;
    //std::cout << "jacs 2 = " << jacs2 << std::endl;
    std::cout << "||jacs1 - jacs2|| = " << (jacs - jacs2).norm2() / ( jacs.norm2() + jacs2.norm2() )<< std::endl;
    }


