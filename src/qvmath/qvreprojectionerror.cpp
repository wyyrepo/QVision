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

#include <qvmath/qvreprojectionerror.h>

/* evaluateReprojectionResidualsAndJacobian function:
   --------------------------------------------------
  This is an auxiliar function for 'optimizeReprojectionErrorForCameraPose',
  which estimates the Jacobian of the reprojection error function.

  Maple code:

    ----------------------------------------
Norm2 := v -> sqrt(v[1]^2 + v[2]^2):
FromHomogeneous2D := p3D -> Vector([p3D[1]/p3D[3], p3D[2]/p3D[3]]):
QuaternionToRotationMatrix := q ->
    Matrix([[1,0,0],[0,1,0],[0,0,1]]) +
    (2.0 / (q[1]^2+q[2]^2+q[3]^2+q[4]^2)) *
    Matrix(	[	[-q[2]*q[2]-q[3]*q[3], q[1]*q[2]-q[3]*q[4], q[3]*q[1]+q[2]*q[4]],
            [q[1]*q[2]+q[3]*q[4], -q[3]*q[3]-q[1]*q[1], q[2]*q[3]-q[1]*q[4]],
            [q[3]*q[1]-q[2]*q[4], q[2]*q[3]+q[1]*q[4], -q[2]*q[2]-q[1]*q[1]]
        ]):

R := QuaternionToRotationMatrix(Vector([q1,q2,q3,q4])):
t := Vector([tx,ty,tz]):
p := Vector([px, py]):
P := Vector([x,y,z]):
res := Norm2(FromHomogeneous2D(R.P+t)-p):

M := Vector([ diff(res, q1), diff(res, q2), diff(res, q3), diff(res, q4), diff(res, tx), diff(res, ty), diff(res, tz), res ]):
CodeGeneration[C](M, optimize = true);
    ----------------------------------------
*/

void evaluateReprojectionResidualsAndJacobian(	const double q1, const double q2, const double q3, const double q4,
                        const double tx, const double ty, const double tz,
                        const double px, const double py,
                        const double x, const double y, const double z,
                        double *residual, double *jacobian)
    {
    const double t1 = q1 * q1;
    const double t2 = q2 * q2;
    const double t3 = q3 * q3;
    const double t4 = q4 * q4;
    const double t5 = t1 + t2 + t3 + t4;
    const double t6 = 0.1e1 / t5;
    const double t7 = -t2 - t3;
    const double t12 = q1 * q2;
    const double t13 = q3 * q4;
    const double t14 = t12 - t13;
    const double t18 = q3 * q1;
    const double t19 = q2 * q4;
    const double t20 = t18 + t19;
    const double t24 = (0.1e1 + 0.20e1 * t6 * t7) * x + 0.20e1 * t6 * t14 * y + 0.20e1 * t6 * t20 * z + tx;
    const double t25 = t18 - t19;
    const double t29 = q2 * q3;
    const double t30 = q1 * q4;
    const double t31 = t29 + t30;
    const double t35 = -t2 - t1;
    const double t40 = 0.20e1 * t6 * t25 * x + 0.20e1 * t6 * t31 * y + (0.1e1 + 0.20e1 * t6 * t35) * z + tz;
    const double t41 = 0.1e1 / t40;
    const double t43 = t24 * t41 - px;
    const double t44 = t43 * t43;
    const double t45 = t12 + t13;
    const double t49 = -t3 - t1;
    const double t54 = t29 - t30;
    const double t58 = 0.20e1 * t6 * t45 * x + (0.1e1 + 0.20e1 * t6 * t49) * y + 0.20e1 * t6 * t54 * z + ty;
    const double t60 = t58 * t41 - py;
    const double t61 = t60 * t60;
    const double t63 = sqrt(t44 + t61);
    const double t64 = 0.1e1 / t63;
    const double t65 = t5 * t5;
    const double t66 = 0.1e1 / t65;
    const double t67 = t66 * t7;
    const double t68 = q1 * x;
    const double t71 = t66 * t14;
    const double t72 = y * q1;
    const double t75 = t6 * q2;
    const double t77 = 0.20e1 * t75 * y;
    const double t78 = t66 * t20;
    const double t79 = z * q1;
    const double t82 = t6 * q3;
    const double t84 = 0.20e1 * t82 * z;
    const double t87 = t40 * t40;
    const double t88 = 0.1e1 / t87;
    const double t89 = t24 * t88;
    const double t90 = t66 * t25;
    const double t94 = 0.20e1 * t82 * x;
    const double t95 = t66 * t31;
    const double t98 = t6 * q4;
    const double t100 = 0.20e1 * t98 * y;
    const double t101 = t66 * t35;
    const double t104 = t6 * q1;
    const double t105 = 0.40e1 * t104;
    const double t108 = -0.40e1 * t90 * t68 + t94 - 0.40e1 * t95 * t72 + t100 + (-0.40e1 * t101 * q1 - t105) * z;
    const double t112 = t66 * t45;
    const double t116 = 0.20e1 * t75 * x;
    const double t117 = t66 * t49;
    const double t122 = t66 * t54;
    const double t126 = 0.20e1 * t98 * z;
    const double t129 = t58 * t88;
    const double t138 = 0.40e1 * t75;
    const double t141 = y * q2;
    const double t145 = 0.20e1 * t104 * y;
    const double t146 = z * q2;
    const double t151 = x * q2;
    const double t155 = 0.20e1 * t98 * x;
    const double t159 = 0.20e1 * t82 * y;
    const double t164 = -0.40e1 * t90 * t151 - t155 - 0.40e1 * t95 * t141 + t159 + (-0.40e1 * t101 * q2 - t138) * z;
    const double t171 = 0.20e1 * t104 * x;
    const double t186 = 0.40e1 * t82;
    const double t189 = y * q3;
    const double t192 = z * q3;
    const double t196 = 0.20e1 * t104 * z;
    const double t199 = x * q3;
    const double t206 = -0.40e1 * t90 * t199 + t171 - 0.40e1 * t95 * t189 + t77 - 0.40e1 * t101 * t192;
    const double t219 = 0.20e1 * t75 * z;
    const double t228 = q4 * x;
    const double t231 = y * q4;
    const double t234 = z * q4;
    const double t245 = -0.40e1 * t90 * t228 - t116 - 0.40e1 * t95 * t231 + t145 - 0.40e1 * t101 * t234;

    jacobian[0] = t64 * (t43 * ((-0.40e1 * t67 * t68 - 0.40e1 * t71 * t72 + t77 - 0.40e1 * t78 * t79 + t84) * t41 - t89 * t108) + t60 * ((-0.40e1 * t112 * t68 + t116 + (-0.40e1 * t117 * q1 - t105) * y - 0.40e1 * t122 * t79 - t126) * t41 - t129 * t108));
    jacobian[1] = t64 * (t43 * (((-0.40e1 * t67 * q2 - t138) * x - 0.40e1 * t71 * t141 + t145 - 0.40e1 * t78 * t146 + t126) * t41 - t89 * t164) + t60 * ((-0.40e1 * t112 * t151 + t171 - 0.40e1 * t117 * t141 - 0.40e1 * t122 * t146 + t84) * t41 - t129 * t164));
    jacobian[2] = t64 * (t43 * (((-0.40e1 * t67 * q3 - t186) * x - 0.40e1 * t71 * t189 - t100 - 0.40e1 * t78 * t192 + t196) * t41 - t89 * t206) + t60 * ((-0.40e1 * t112 * t199 + t155 + (-0.40e1 * t117 * q3 - t186) * y - 0.40e1 * t122 * t192 + t219) * t41 - t129 * t206));
    jacobian[3] = t64 * (t43 * ((-0.40e1 * t67 * t228 - 0.40e1 * t71 * t231 - t159 - 0.40e1 * t78 * t234 + t219) * t41 - t89 * t245) + t60 * ((-0.40e1 * t112 * t228 + t94 - 0.40e1 * t117 * t231 - 0.40e1 * t122 * t234 - t196) * t41 - t129 * t245));
    jacobian[4] = t64 * t43 * t41;
    jacobian[5] = t64 * t60 * t41;
    jacobian[6] = t64 * (-t43 * t24 * t88 - t60 * t58 * t88);
    residual[0] = t63;
    }

QVEuclideanMapping3 optimizeReprojectionErrorForCameraPose(const QVEuclideanMapping3 &camera0, const QList<QPointF> &points2D, const QList<QV3DPointF> &points3D, const int iterations)
    {
    const int n = points2D.size();

    QVVector x = camera0;
    for(int i = 0; i < iterations; i++)
        {
        QVVector f_x(n);
        QVMatrix J(n, 7);
        double	*data_f_x = f_x.data(),
            *data_J = J.getWriteData();

        QListIterator<QPointF> iteratorPoints2D(points2D);
        QListIterator<QV3DPointF> iteratorPoints3D(points3D);

        int j = 0;
        while (iteratorPoints2D.hasNext())
            {
            const QPointF p2D = iteratorPoints2D.next();
            const QV3DPointF p3D = iteratorPoints3D.next();
            evaluateReprojectionResidualsAndJacobian(x[0], x[1], x[2], x[3], x[4], x[5], x[6], p2D.x(), p2D.y(), p3D.x(), p3D.y(), p3D.z(), data_f_x + j, data_J + (7*j));
            j++;
            }

        QVMatrix H = J.dotProduct(J, true, false);
        for(int i = 0; i < H.getCols(); i++)
            H(i,i) += 0.01;
        QVVector b = J.dotProduct(f_x, true);

        QVVector xInc;
        solveByCholeskyDecomposition(H, xInc, b);

        x = x - xInc;
        }

    return QVEuclideanMapping3(x);
    }

/* reprojectionResidualsAndJacobianFor3DPoint function:
   --------------------------------------------------
  This is an auxiliar function for 'optimizeReprojectionError3DPoint',
  which estimates the Jacobian of the reprojection error function.

  Maple code:

    ----------------------------------------

Norm2 := v -> sqrt(v[1]^2 + v[2]^2):
FromHomogeneous2D := p3D -> Vector([p3D[1]/p3D[3], p3D[2]/p3D[3]]):
QuaternionToRotationMatrix := q ->
    Matrix([[1,0,0],[0,1,0],[0,0,1]]) +
    (2.0 / (q[1]^2+q[2]^2+q[3]^2+q[4]^2)) *
    Matrix(	[	[-q[2]*q[2]-q[3]*q[3], q[1]*q[2]-q[3]*q[4], q[3]*q[1]+q[2]*q[4]],
            [q[1]*q[2]+q[3]*q[4], -q[3]*q[3]-q[1]*q[1], q[2]*q[3]-q[1]*q[4]],
            [q[3]*q[1]-q[2]*q[4], q[2]*q[3]+q[1]*q[4], -q[2]*q[2]-q[1]*q[1]]
        ]):

R := QuaternionToRotationMatrix(Vector([q1,q2,q3,q4])):
t := Vector([tx,ty,tz]):
p := Vector([px, py]):
P := Vector([x,y,z]):
res := Norm2(FromHomogeneous2D(R.P+t)-p);

M := Vector([ diff(res, x), diff(res, y), diff(res, z), res ]):
CodeGeneration[C](M, optimize = true);
    ----------------------------------------
*/
void reprojectionResidualsAndJacobianFor3DPoint(	const double q1, const double q2, const double q3, const double q4,
                            const double tx, const double ty, const double tz,
                            const double px, const double py,
                            const double x, const double y, const double z,
                            double *residual, double *jacobian)
    {
    const double t1 = q1 * q1;
    const double t2 = q2 * q2;
    const double t3 = q3 * q3;
    const double t4 = q4 * q4;
    const double t6 = 0.1e1 / (t1 + t2 + t3 + t4);
    const double t10 = 0.1e1 + 0.20e1 * t6 * (-t2 - t3);
    const double t12 = q1 * q2;
    const double t13 = q3 * q4;
    const double t15 = t6 * (t12 - t13);
    const double t18 = q3 * q1;
    const double t19 = q2 * q4;
    const double t21 = t6 * (t18 + t19);
    const double t24 = t10 * x + 0.20e1 * t15 * y + 0.20e1 * t21 * z + tx;
    const double t26 = t6 * (t18 - t19);
    const double t29 = q2 * q3;
    const double t30 = q1 * q4;
    const double t32 = t6 * (t29 + t30);
    const double t38 = 0.1e1 + 0.20e1 * t6 * (-t2 - t1);
    const double t40 = 0.20e1 * t26 * x + 0.20e1 * t32 * y + t38 * z + tz;
    const double t41 = 0.1e1 / t40;
    const double t43 = t24 * t41 - px;
    const double t44 = t43 * t43;
    const double t46 = t6 * (t12 + t13);
    const double t52 = 0.1e1 + 0.20e1 * t6 * (-t3 - t1);
    const double t55 = t6 * (t29 - t30);
    const double t58 = 0.20e1 * t46 * x + t52 * y + 0.20e1 * t55 * z + ty;
    const double t60 = t58 * t41 - py;
    const double t61 = t60 * t60;
    const double t63 = sqrt(t44 + t61);
    const double t64 = 0.1e1 / t63;
    const double t66 = t40 * t40;
    const double t67 = 0.1e1 / t66;
    const double t68 = t24 * t67;
    const double t75 = t58 * t67;
    jacobian[0] = t64 * (t43 * (t10 * t41 - 0.20e1 * t68 * t26) + t60 * (0.20e1 * t46 * t41 - 0.20e1 * t75 * t26));
    jacobian[1] = t64 * (t43 * (0.20e1 * t15 * t41 - 0.20e1 * t68 * t32) + t60 * (t52 * t41 - 0.20e1 * t75 * t32));
    jacobian[2] = t64 * (t43 * (0.20e1 * t21 * t41 - t68 * t38) + t60 * (0.20e1 * t55 * t41 - t75 * t38));
    residual[0] = t63;
    }

QV3DPointF optimizeReprojectionErrorFor3DPoint(const QV3DPointF &point3D, const QList<QVEuclideanMapping3> &cameraPoses, const QHash<int, QPointF> &projectionsOfAPoint, const int iterations, const double lambda)
    {
    const int n = projectionsOfAPoint.count();

    QVVector x = point3D;
    for(int i = 0; i < iterations; i++)
        {
        QVVector f_x(n);
        QVMatrix J(n, 3);
        double	*data_f_x = f_x.data(),
            *data_J = J.getWriteData();

        QHashIterator<int, QPointF> it(projectionsOfAPoint);
        int j=0;
        while (it.hasNext())
            {
            it.next();
            const QPointF p2D = it.value();
            const QVVector v = cameraPoses[it.key()];

            reprojectionResidualsAndJacobianFor3DPoint(v[0], v[1], v[2], v[3], v[4], v[5], v[6], p2D.x(), p2D.y(), x[0], x[1], x[2], data_f_x + j, data_J + (3*j));
            j++;
            }

        QVMatrix H = J.dotProduct(J, true, false);
        for(int i = 0; i < H.getCols(); i++)
            H(i,i) += lambda;
        QVVector b = J.dotProduct(f_x, true);

        QVVector xInc;
        solveByCholeskyDecomposition(H, xInc, b);

        x = x - xInc;
        }

    return x;
    }

/* evaluateReprojectionResidualsAndJacobianCauchyDistribution function:
   --------------------------------------------------
  This is an auxiliar function for 'optimizeReprojectionErrorForCameraPose',
  which estimates the Jacobian of the reprojection error function.

  Maple code:

    ----------------------------------------
Norm2 := v -> sqrt(v[1]^2 + v[2]^2):
FromHomogeneous2D := p3D -> Vector([p3D[1]/p3D[3], p3D[2]/p3D[3]]):
QuaternionToRotationMatrix := q ->
    Matrix([[1,0,0],[0,1,0],[0,0,1]]) +
    (2.0 / (q[1]^2+q[2]^2+q[3]^2+q[4]^2)) *
    Matrix(	[	[-q[2]*q[2]-q[3]*q[3], q[1]*q[2]-q[3]*q[4], q[3]*q[1]+q[2]*q[4]],
            [q[1]*q[2]+q[3]*q[4], -q[3]*q[3]-q[1]*q[1], q[2]*q[3]-q[1]*q[4]],
            [q[3]*q[1]-q[2]*q[4], q[2]*q[3]+q[1]*q[4], -q[2]*q[2]-q[1]*q[1]]
        ]):

R := QuaternionToRotationMatrix(Vector([q1,q2,q3,q4])):
t := Vector([tx,ty,tz]):
p := Vector([px, py]):
P := Vector([x,y,z]):
res := log(1+Norm2(FromHomogeneous2D(R.(P-t))-p)^2 / sigma^2):

M := Vector([ diff(res, q1), diff(res, q2), diff(res, q3), diff(res, q4), diff(res, tx), diff(res, ty), diff(res, tz), res ]):
CodeGeneration[C](M, optimize = true);
    ----------------------------------------
*/

void evaluateReprojectionResidualsAndJacobianCauchyDistribution(
		const double q1, const double q2, const double q3, const double q4,
		const double tx, const double ty, const double tz,
		const QPointF p2D, const QV3DPointF p3D,
		const double sigma,
		double *residual, double *jacobian)
    {
	//const double sigma = 3.0;
	const double	px = p2D.x(),
					py = p2D.y(),
					x = p3D.x(),
					y = p3D.y(),
					z = p3D.z();

	const double t1 = q1 * q1;
	const double t2 = q2 * q2;
	const double t3 = q3 * q3;
	const double t4 = q4 * q4;
	const double t5 = t1 + t2 + t3 + t4;
	const double t6 = 0.1e1 / t5;
	const double t7 = -t2 - t3;
	const double t10 = 0.1e1 + 0.20e1 * t6 * t7;
	const double t11 = x - tx;
	const double t13 = q1 * q2;
	const double t14 = q3 * q4;
	const double t15 = t13 - t14;
	const double t16 = t6 * t15;
	const double t17 = y - ty;
	const double t20 = q3 * q1;
	const double t21 = q2 * q4;
	const double t22 = t20 + t21;
	const double t23 = t6 * t22;
	const double t24 = z - tz;
	const double t27 = t10 * t11 + 0.20e1 * t16 * t17 + 0.20e1 * t23 * t24;
	const double t28 = t20 - t21;
	const double t29 = t6 * t28;
	const double t32 = q2 * q3;
	const double t33 = q1 * q4;
	const double t34 = t32 + t33;
	const double t35 = t6 * t34;
	const double t38 = -t2 - t1;
	const double t41 = 0.1e1 + 0.20e1 * t6 * t38;
	const double t43 = 0.20e1 * t29 * t11 + 0.20e1 * t35 * t17 + t41 * t24;
	const double t44 = 0.1e1 / t43;
	const double t46 = t27 * t44 - px;
	const double t47 = t5 * t5;
	const double t48 = 0.1e1 / t47;
	const double t49 = t48 * t7;
	const double t50 = q1 * t11;
	const double t53 = t48 * t15;
	const double t54 = t17 * q1;
	const double t57 = t6 * q2;
	const double t59 = 0.20e1 * t57 * t17;
	const double t60 = t48 * t22;
	const double t61 = t24 * q1;
	const double t64 = t6 * q3;
	const double t66 = 0.20e1 * t64 * t24;
	const double t69 = t43 * t43;
	const double t70 = 0.1e1 / t69;
	const double t71 = t27 * t70;
	const double t72 = t48 * t28;
	const double t76 = 0.20e1 * t64 * t11;
	const double t77 = t48 * t34;
	const double t80 = t6 * q4;
	const double t82 = 0.20e1 * t80 * t17;
	const double t83 = t48 * t38;
	const double t86 = t6 * q1;
	const double t87 = 0.40e1 * t86;
	const double t90 = -0.40e1 * t72 * t50 + t76 - 0.40e1 * t77 * t54 + t82 + (-0.40e1 * t83 * q1 - t87) * t24;
	const double t94 = t13 + t14;
	const double t95 = t6 * t94;
	const double t98 = -t3 - t1;
	const double t101 = 0.1e1 + 0.20e1 * t6 * t98;
	const double t103 = t32 - t33;
	const double t104 = t6 * t103;
	const double t107 = 0.20e1 * t95 * t11 + t101 * t17 + 0.20e1 * t104 * t24;
	const double t109 = t107 * t44 - py;
	const double t110 = t48 * t94;
	const double t114 = 0.20e1 * t57 * t11;
	const double t115 = t48 * t98;
	const double t120 = t48 * t103;
	const double t124 = 0.20e1 * t80 * t24;
	const double t127 = t107 * t70;
	const double t132 = sigma * sigma;
	const double t133 = 0.1e1 / t132;
	const double t135 = t46 * t46;
	const double t136 = t109 * t109;
	const double t139 = 0.1e1 + (t135 + t136) * t133;
	const double t140 = 0.1e1 / t139;
	const double t144 = 0.40e1 * t57;
	const double t147 = t17 * q2;
	const double t151 = 0.20e1 * t86 * t17;
	const double t152 = t24 * q2;
	const double t157 = t11 * q2;
	const double t161 = 0.20e1 * t80 * t11;
	const double t165 = 0.20e1 * t64 * t17;
	const double t170 = -0.40e1 * t72 * t157 - t161 - 0.40e1 * t77 * t147 + t165 + (-0.40e1 * t83 * q2 - t144) * t24;
	const double t177 = 0.20e1 * t86 * t11;
	const double t192 = 0.40e1 * t64;
	const double t195 = t17 * q3;
	const double t198 = t24 * q3;
	const double t202 = 0.20e1 * t86 * t24;
	const double t205 = t11 * q3;
	const double t212 = -0.40e1 * t72 * t205 + t177 - 0.40e1 * t77 * t195 + t59 - 0.40e1 * t83 * t198;
	const double t225 = 0.20e1 * t57 * t24;
	const double t234 = q4 * t11;
	const double t237 = t17 * q4;
	const double t240 = t24 * q4;
	const double t251 = -0.40e1 * t72 * t234 - t114 - 0.40e1 * t77 * t237 + t151 - 0.40e1 * t83 * t240;
	const double t310 = log(t139);

	jacobian[0] = 0.2e1 * (t46 * ((-0.40e1 * t49 * t50 - 0.40e1 * t53 * t54 + t59 - 0.40e1 * t60 * t61 + t66) * t44 - t71 * t90) + t109 * ((-0.40e1 * t110 * t50 + t114 + (-0.40e1 * t115 * q1 - t87) * t17 - 0.40e1 * t120 * t61 - t124) * t44 - t127 * t90)) * t133 * t140;
	jacobian[1] = 0.2e1 * (t46 * (((-0.40e1 * t49 * q2 - t144) * t11 - 0.40e1 * t53 * t147 + t151 - 0.40e1 * t60 * t152 + t124) * t44 - t71 * t170) + t109 * ((-0.40e1 * t110 * t157 + t177 - 0.40e1 * t115 * t147 - 0.40e1 * t120 * t152 + t66) * t44 - t127 * t170)) * t133 * t140;
	jacobian[2] = 0.2e1 * (t46 * (((-0.40e1 * t49 * q3 - t192) * t11 - 0.40e1 * t53 * t195 - t82 - 0.40e1 * t60 * t198 + t202) * t44 - t71 * t212) + t109 * ((-0.40e1 * t110 * t205 + t161 + (-0.40e1 * t115 * q3 - t192) * t17 - 0.40e1 * t120 * t198 + t225) * t44 - t127 * t212)) * t133 * t140;
	jacobian[3] = 0.2e1 * (t46 * ((-0.40e1 * t49 * t234 - 0.40e1 * t53 * t237 - t165 - 0.40e1 * t60 * t240 + t225) * t44 - t71 * t251) + t109 * ((-0.40e1 * t110 * t234 + t76 - 0.40e1 * t115 * t237 - 0.40e1 * t120 * t240 - t202) * t44 - t127 * t251)) * t133 * t140;
	jacobian[4] = 0.2e1 * (t46 * (-t10 * t44 + 0.20e1 * t71 * t29) + t109 * (-0.20e1 * t95 * t44 + 0.20e1 * t127 * t29)) * t133 * t140;
	jacobian[5] = 0.2e1 * (t46 * (-0.20e1 * t16 * t44 + 0.20e1 * t71 * t35) + t109 * (-t101 * t44 + 0.20e1 * t127 * t35)) * t133 * t140;
	jacobian[6] = 0.2e1 * (t46 * (-0.20e1 * t23 * t44 + t71 * t41) + t109 * (-0.20e1 * t104 * t44 + t127 * t41)) * t133 * t140;
	residual[0] = t310;
    }

QVCameraPose optimizeReprojectionErrorForCameraPoseCauchy(const QVCameraPose &cameraPose, const QList<QPointF> &points2D, const QList<QV3DPointF> &points3D, const int iterations, const double lambda, const double sigma)
    {
    const int n = points2D.size();

    QVVector x = cameraPose;
    for(int i = 0; i < iterations; i++)
        {
        QVVector f_x(n);
        QVMatrix J(n, 7);
        double	*data_f_x = f_x.data(),
            *data_J = J.getWriteData();

        QListIterator<QPointF> iteratorPoints2D(points2D);
        QListIterator<QV3DPointF> iteratorPoints3D(points3D);

        int j = 0;
        while (iteratorPoints2D.hasNext())
            {
            const QPointF p2D = iteratorPoints2D.next();
            const QV3DPointF p3D = iteratorPoints3D.next();
            evaluateReprojectionResidualsAndJacobianCauchyDistribution(x[0], x[1], x[2], x[3], x[4], x[5], x[6], p2D, p3D, sigma, data_f_x + j, data_J + (7*j));
            j++;
            }

		Q_ASSERT(not f_x.containsNaN());
		Q_ASSERT(not J.containsNaN());

        QVMatrix H = J.dotProduct(J, true, false);
        for(int i = 0; i < H.getCols(); i++)
            H(i,i) += lambda;
        QVVector b = J.dotProduct(f_x, true);

        QVVector xInc;
        solveByCholeskyDecomposition(H, xInc, b);

        x = x - xInc;
        }

    return QVCameraPose(x);
    }

