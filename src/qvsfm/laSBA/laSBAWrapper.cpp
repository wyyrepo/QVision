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

#define SBA_OPTSSZ        5
#define SBA_INFOSZ        10
#define SBA_ERROR         -1
#define SBA_INIT_MU       1E-03
#define SBA_STOP_THRESH   1E-12
#define SBA_CG_NOPREC     0
#define SBA_CG_JACOBI     1
#define SBA_CG_SSOR       2
#define SBA_VERSION       "1.6 (Aug. 2009)"

#include <QTime>
#include <qvsfm/laSBA/laSBAWrapper.h>
#include <qvsfm/laSBA/sba-1.6/compiler.h>
#include <qvsfm/laSBA/sba-1.6/sba.h>

const int	CAMERA_VECTOR_SIZE=7,	// Camera size: 4 rot params + 3 trans params.
		POINT3D_SIZE=3,			// 3D Point size.
		POINT2D_SIZE=2;			// 2D Points size.

void initData(	const QList<QVEuclideanMapping3> &cameras,
		const QList<QV3DPointF> &points3D,
		const QList< QHash<int, QPointF> > &pointProjections,
		double	*motstruct,
		double *imgpts,
		char *vmask
		);

void img_proj2(int numCam, int numPoint, double *cam, double *p3D, double *p2D, void *);

void readData(	const double	*motstruct,
		const int	numFrames,	// Frames
		const int	numPoints3D,	// Number of points
		QList<QVEuclideanMapping3> &refinedCameras,
		QList<QV3DPointF> &refinedPoints3D);

double final_reprojection_error, initial_reprojection_error;
int sba_elapsed_milisecs = 0, sba_iterations = 0, sba_stop_condition = -1;

/* Euclidean bundle adjustment demo using the sba package */
// -------------------------------------------------------
void my_img_proj(int numCam, int numPoint, double *camera, double *p3D, double *p2D, void *)
	{
	const double	camera0 = camera[0],
				camera1 = camera[1],
				camera2 = camera[2],
				camera3 = camera[3],
				camera4 = camera[4],
				camera5 = camera[5],
				camera6 = camera[6];
	const double	p3D0 = p3D[0],
				p3D1 = p3D[1],
				p3D2 = p3D[2];

	/*
	Maple code to evaluate the reprojection error:
	--------------------------------
	with(VectorCalculus)
	with(LinearAlgebra):
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
	R := QuaternionToRotationMatrix(Vector([camera0, camera1, camera2, camera3])):
	t := Vector([camera4, camera5, camera6]):
	point3D := Vector([p3D0, p3D1, p3D2]):
	p2D := FromHomogeneous2D(R.point3D + t):
	CodeGeneration[C](p2D, optimize = true);
	*/
	const double t1 = camera0 * camera0;
	const double t2 = camera1 * camera1;
	const double t3 = camera2 * camera2;
	const double t4 = camera3 * camera3;
	const double t6 = 0.1e1 / (t1 + t2 + t3 + t4);
	const double t7 = 0.20e1 * t2;
	const double t8 = 0.20e1 * t3;
	const double t14 = 0.20e1 * camera0 * camera1;
	const double t16 = 0.20e1 * camera2 * camera3;
	const double t21 = 0.20e1 * camera2 * camera0;
	const double t23 = 0.20e1 * camera1 * camera3;
	const double t32 = 0.20e1 * camera1 * camera2;
	const double t34 = 0.20e1 * camera0 * camera3;
	const double t38 = 0.20e1 * t1;
	const double t44 = 0.1e1 / (t6 * (t21 - t23) * p3D0 + t6 * (t32 + t34) * p3D1 + (0.1e1 + t6 * (-t7 - t38)) * p3D2 + camera6);
	p2D[0] = ((0.1e1 + t6 * (-t7 - t8)) * p3D0 + t6 * (t14 - t16) * p3D1 + t6 * (t21 + t23) * p3D2 + camera4) * t44;
	p2D[1] = (t6 * (t14 + t16) * p3D0 + (0.1e1 + t6 * (-t8 - t38)) * p3D1 + t6 * (t32 - t34) * p3D2 + camera5) * t44;
	}

void my_img_proj_jac(int numCam, int numPoint, double *camera, double *p3D, double * jacmRT, double * jacmS, void *)
	{
	const double	camera0 = camera[0],
				camera1 = camera[1],
				camera2 = camera[2],
				camera3 = camera[3],
				camera4 = camera[4],
				camera5 = camera[5],
				camera6 = camera[6];
	const double	p3D0 = p3D[0],
				p3D1 = p3D[1],
				p3D2 = p3D[2];
		
	/*
	Maple code:
	------------------
	J := Vector([
		diff(p2D(1), camera0), diff(p2D(1), camera1), diff(p2D(1), camera2), diff(p2D(1), camera3), diff(p2D(1), camera4), diff(p2D(1), camera5), diff(p2D(1), camera6), diff(p2D(1), p3D0), diff(p2D(1), p3D1), diff(p2D(1), p3D2),
		diff(p2D(2), camera0), diff(p2D(2), camera1), diff(p2D(2), camera2), diff(p2D(2), camera3), diff(p2D(2), camera4), diff(p2D(2), camera5), diff(p2D(2), camera6), diff(p2D(2), p3D0), diff(p2D(2), p3D1), diff(p2D(2), p3D2)
		]):
	CodeGeneration[C](J, optimize = true);
	*/
	const double t1 = camera0 * camera0;
	const double t2 = camera1 * camera1;
	const double t3 = camera2 * camera2;
	const double t4 = camera3 * camera3;
	const double t5 = t1 + t2 + t3 + t4;
	const double t6 = t5 * t5;
	const double t7 = 0.1e1 / t6;
	const double t8 = 0.20e1 * t2;
	const double t9 = 0.20e1 * t3;
	const double t10 = -t8 - t9;
	const double t11 = t7 * t10;
	const double t12 = camera0 * p3D0;
	const double t16 = 0.20e1 * camera0 * camera1;
	const double t18 = 0.20e1 * camera2 * camera3;
	const double t19 = t16 - t18;
	const double t20 = t7 * t19;
	const double t21 = p3D1 * camera0;
	const double t24 = 0.1e1 / t5;
	const double t25 = t24 * camera1;
	const double t27 = 0.20e1 * t25 * p3D1;
	const double t29 = 0.20e1 * camera2 * camera0;
	const double t31 = 0.20e1 * camera1 * camera3;
	const double t32 = t29 + t31;
	const double t33 = t7 * t32;
	const double t34 = p3D2 * camera0;
	const double t37 = t24 * camera2;
	const double t39 = 0.20e1 * t37 * p3D2;
	const double t41 = t29 - t31;
	const double t42 = t24 * t41;
	const double t45 = 0.20e1 * camera1 * camera2;
	const double t47 = 0.20e1 * camera0 * camera3;
	const double t48 = t45 + t47;
	const double t49 = t24 * t48;
	const double t51 = 0.20e1 * t1;
	const double t52 = -t8 - t51;
	const double t54 = 0.1e1 + t24 * t52;
	const double t56 = t42 * p3D0 + t49 * p3D1 + t54 * p3D2 + camera6;
	const double t57 = 0.1e1 / t56;
	const double t60 = 0.1e1 + t24 * t10;
	const double t62 = t24 * t19;
	const double t64 = t24 * t32;
	const double t67 = t56 * t56;
	const double t68 = 0.1e1 / t67;
	const double t69 = (t60 * p3D0 + t62 * p3D1 + t64 * p3D2 + camera4) * t68;
	const double t70 = t7 * t41;
	const double t74 = 0.20e1 * t37 * p3D0;
	const double t75 = t7 * t48;
	const double t78 = t24 * camera3;
	const double t80 = 0.20e1 * t78 * p3D1;
	const double t81 = t7 * t52;
	const double t84 = t24 * camera0;
	const double t85 = 0.40e1 * t84;
	const double t88 = -0.2e1 * t70 * t12 + t74 - 0.2e1 * t75 * t21 + t80 + (-0.2e1 * t81 * camera0 - t85) * p3D2;
	const double t93 = 0.40e1 * t25;
	const double t96 = p3D1 * camera1;
	const double t100 = 0.20e1 * t84 * p3D1;
	const double t101 = p3D2 * camera1;
	const double t105 = 0.20e1 * t78 * p3D2;
	const double t108 = p3D0 * camera1;
	const double t112 = 0.20e1 * t78 * p3D0;
	const double t116 = 0.20e1 * t37 * p3D1;
	const double t121 = -0.2e1 * t70 * t108 - t112 - 0.2e1 * t75 * t96 + t116 + (-0.2e1 * t81 * camera1 - t93) * p3D2;
	const double t126 = 0.40e1 * t37;
	const double t129 = p3D1 * camera2;
	const double t132 = p3D2 * camera2;
	const double t136 = 0.20e1 * t84 * p3D2;
	const double t139 = p3D0 * camera2;
	const double t143 = 0.20e1 * t84 * p3D0;
	const double t148 = -0.2e1 * t70 * t139 + t143 - 0.2e1 * t75 * t129 + t27 - 0.2e1 * t81 * t132;
	const double t151 = camera3 * p3D0;
	const double t154 = p3D1 * camera3;
	const double t157 = p3D2 * camera3;
	const double t161 = 0.20e1 * t25 * p3D2;
	const double t167 = 0.20e1 * t25 * p3D0;
	const double t172 = -0.2e1 * t70 * t151 - t167 - 0.2e1 * t75 * t154 + t100 - 0.2e1 * t81 * t157;
	const double t184 = t16 + t18;
	const double t185 = t7 * t184;
	const double t188 = -t9 - t51;
	const double t189 = t7 * t188;
	const double t194 = t45 - t47;
	const double t195 = t7 * t194;
	const double t200 = t24 * t184;
	const double t203 = 0.1e1 + t24 * t188;
	const double t205 = t24 * t194;
	const double t208 = (t200 * p3D0 + t203 * p3D1 + t205 * p3D2 + camera5) * t68;
	jacmRT[0] = (-0.2e1 * t11 * t12 - 0.2e1 * t20 * t21 + t27 - 0.2e1 * t33 * t34 + t39) * t57 - t69 * t88;
	jacmRT[1] = ((-0.2e1 * t11 * camera1 - t93) * p3D0 - 0.2e1 * t20 * t96 + t100 - 0.2e1 * t33 * t101 + t105) * t57 - t69 * t121;
	jacmRT[2] = ((-0.2e1 * t11 * camera2 - t126) * p3D0 - 0.2e1 * t20 * t129 - t80 - 0.2e1 * t33 * t132 + t136) * t57 - t69 * t148;
	jacmRT[3] = (-0.2e1 * t11 * t151 - 0.2e1 * t20 * t154 - t116 - 0.2e1 * t33 * t157 + t161) * t57 - t69 * t172;
	jacmRT[4] = t57;
	jacmRT[5] = 0.0e0;
	jacmRT[6] = -t69;
	jacmRT[7] = (-0.2e1 * t185 * t12 + t167 + (-0.2e1 * t189 * camera0 - t85) * p3D1 - 0.2e1 * t195 * t34 - t105) * t57 - t208 * t88;
	jacmRT[8] = (-0.2e1 * t185 * t108 + t143 - 0.2e1 * t189 * t96 - 0.2e1 * t195 * t101 + t39) * t57 - t208 * t121;
	jacmRT[9] = (-0.2e1 * t185 * t139 + t112 + (-0.2e1 * t189 * camera2 - t126) * p3D1 - 0.2e1 * t195 * t132 + t161) * t57 - t208 * t148;
	jacmRT[10] = (-0.2e1 * t185 * t151 + t74 - 0.2e1 * t189 * t154 - 0.2e1 * t195 * t157 - t136) * t57 - t208 * t172;
	jacmRT[11] = 0.0e0;
	jacmRT[12] = t57;
	jacmRT[13] = -t208;
	jacmS[0] = t60 * t57 - t69 * t42;
	jacmS[1] = t62 * t57 - t69 * t49;
	jacmS[2] = t64 * t57 - t69 * t54;
	jacmS[3] = t200 * t57 - t208 * t42;
	jacmS[4] = t203 * t57 - t208 * t49;
	jacmS[5] = t205 * t57 - t208 * t54;
	}

// ---------------------------------------

bool laSBAOptimization(	const QList<QVCameraPose> &cameras,
				const QList<QV3DPointF> &points3D,
				const QList< QHash<int, QPointF> > &pointProjections,
				QList<QVCameraPose> &refinedCameras,
				QList<QV3DPointF> &refinedPoints3D,
				const unsigned int numIterations,
				const unsigned int numFixedFrames,
				const unsigned int numFixedPoints,
				const double initialMuScaleFactor,
				const double stoppingThresholdForJacobian,
				const double stoppingThresholdForProjections,
				const double stoppingThresholdForReprojectionError,
				const double stoppingThresholdForReprojectionErrorIncrement)
	{
	const int	numPoints3D = points3D.size(),	// Number of points
			numFrames = cameras.size(),	// Frames
			CAMERA_VECTOR_SIZE=7,		// Camera size: 4 rot params + 3 trans params.
			POINT3D_SIZE=3,			// 3D Point size.
			POINT2D_SIZE=2;			// 2D Points size.
	
	int n2Dprojs = 0;
	for(int i = 0; i < pointProjections.size(); i++)
		n2Dprojs += pointProjections[i].size();
		
	double	motstruct[numFrames*CAMERA_VECTOR_SIZE + numPoints3D*POINT3D_SIZE],
		imgpts[n2Dprojs*POINT2D_SIZE];

	char vmask[numPoints3D * numFrames];
	
	// -- Init data

	// Load camera data
	for (int i = 0; i < numFrames; i++)
		{
		const QVVector camera = cameras[i].operator QVEuclideanMapping3();
		for(int j = 0; j < CAMERA_VECTOR_SIZE; j++)
			motstruct[i*CAMERA_VECTOR_SIZE+j] = camera[j];
		}

	// Load points data
	for (int i = 0; i < numPoints3D; i++)
		for(int j = 0; j < POINT3D_SIZE; j++)
			(motstruct+numFrames*CAMERA_VECTOR_SIZE)[i*POINT3D_SIZE+j] = points3D[i][j];
	
	// Load projections
	for(int j = 0, index = 0; j < numPoints3D; j++)
		for(int i = 0; i < numFrames; i++)
			if (pointProjections[j].contains(i))
				{
				imgpts[index*POINT2D_SIZE+0] = pointProjections[j][i].x();
				imgpts[index*POINT2D_SIZE+1] = pointProjections[j][i].y();
				index++;
				vmask[j*numFrames + i] = true;
				}
			else	vmask[j*numFrames + i] = false;
	
	double opts[SBA_OPTSSZ];
	opts[0]=initialMuScaleFactor;				// Scale factor for initial \mu,
	opts[1]=stoppingThresholdForJacobian;			// Stopping threshold for ||J^T e||_inf,
	opts[2]=stoppingThresholdForProjections;		// Stopping threshold for ||dp||_2
	opts[3]=stoppingThresholdForReprojectionError;		// Stopping threshold for ||e||_2 (reprojection error)
	opts[4]=stoppingThresholdForReprojectionErrorIncrement;	// Stopping threshold for (||e||_2-||e_new||_2)/||e||_2 (increment in the RMS reprojection error)

	// -- Call to sba
	double info[SBA_INFOSZ];
	/*
                * info[0]=||e||_2 at initial p.
                * info[1-4]=[ ||e||_2, ||J^T e||_inf,  ||dp||_2, mu/max[J^T J]_ii ], all computed at estimated p.
                * info[5]= # iterations,
                * info[6]=reason for terminating: 1 - stopped by small gradient J^T e
                *                                 2 - stopped by small dp
                *                                 3 - stopped by itmax
                *                                 4 - stopped by small relative reduction in ||e||_2
                *                                 5 - stopped by small ||e||_2
                *                                 6 - too many attempts to increase damping. Restart with increased mu
                *                                 7 - stopped by invalid (i.e. NaN or Inf) "func" values; a user error
                * info[7]= # function evaluations
                * info[8]= # Jacobian evaluations
                * info[9]= # number of linear systems solved, i.e. number of attempts for reducing error
	*/

	QTime time;
	time.start();
	sba_iterations = sba_motstr_levmar(	numPoints3D,		// Number of 3D points.
						numFixedPoints,		// Number of fixed points.
						numFrames,		// Number of images/cameras.
						numFixedFrames,		// Number of constant images/cameras.
						vmask,			// Point visibility for each frame.
						motstruct,		// Cameras + points.
						CAMERA_VECTOR_SIZE,	// Camera size.
						POINT3D_SIZE,		// 3D Point size.
						imgpts,			// Pointer to image projections.
						NULL,			// Variance matrices for the image projections.
						POINT2D_SIZE,		// Size of each projected point.
						my_img_proj,		// Projection function.
						my_img_proj_jac,	// Jacobian function of the projection function.
						NULL,			// *data.
						numIterations,		// Max iterations.
						false,			// Print debug messages.
						opts,			// Options
						info			// Output info.
						);
 	sba_elapsed_milisecs = time.elapsed();	
	refinedPoints3D = points3D;

	// -- Get data from sba structures
	// Load camera data
	for (int i = 0; i < numFrames; i++)
		{
		QVVector cameraVector(CAMERA_VECTOR_SIZE);
		for(int j = 0; j < CAMERA_VECTOR_SIZE; j++)
			cameraVector[j] = motstruct[i*CAMERA_VECTOR_SIZE+j];
		refinedCameras << QVEuclideanMapping3(cameraVector);
		}

	// Load points data
	for (int i = 0; i < numPoints3D; i++)
		for(int j = 0; j < POINT3D_SIZE; j++)
			refinedPoints3D[i][j] = (motstruct+numFrames*CAMERA_VECTOR_SIZE)[i*POINT3D_SIZE+j];

	sba_stop_condition = info[6];
	initial_reprojection_error = info[0];
	final_reprojection_error = info[1];

	return (info[6] > 0 and info[6] < 6);
	}


