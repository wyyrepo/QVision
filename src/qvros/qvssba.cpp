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

#include <qvros.h>

#include <ros/ros.h>
#include <sba/sba.h>
#include <sba/sba_file_io.h>
#include <sba/visualization.h>
#include <visualization_msgs/Marker.h>
#include <time.h>
#include <map>
#include <qvsfm.h>

using namespace sba;
using namespace std;
using namespace Eigen;
using namespace frame_common;

#include <QTime>

//template <typename SysSBAType>
int initReconstructionToSysSBA(	SysSBA& sbaout,
				const QList<QVCameraPose> &cameraPoses,
				const QList<QV3DPointF> &points3D,
				const QList< QHash< int, QPointF> > &pointsProjections)
	{
	const int ncams = cameraPoses.count();
	const int npts  = points3D.count();

	for (int i=0; i<ncams; i++)
		{
		// camera params
		//Vector3d &camp = camps[i];
		CamParams cpars = { -1.0, -1.0, 0, 0, 0 }; // set focal length, no offset

		// Rotation.
		const QVCameraPose &cameraPose = cameraPoses[i];
		const QVQuaternion q = (QVQuaternion(1.0, 0.0, 0.0, 0.0) * cameraPose.getOrientation()).inverse();
		Quaternion<double> frq;	// camera frame rotation, from Bundler docs
		frq.x() = q.i();
		frq.y() = q.j();
		frq.z() = q.k();
		frq.w() = q.real();

		// Translation.		
		const QV3DPointF c = cameraPose.getCenter();

		Vector4d frt;
		frt[0] = c.x();
		frt[1] = c.y();
		frt[2] = c.z();
		frt[3] = 1.0;

		sbaout.addNode(frt, frq, cpars);
		}
	
	// set up points
	for (int i=0; i<npts; i++)
		{
		const QV3DPointF p = points3D[i];
		Point pt;
		pt[0] = p.x();
		pt[1] = p.y();
		pt[2] = p.z();
		pt[3] = 1;

		sbaout.addPoint(pt);
		}
		
	sbaout.useLocalAngles = true;    // use local angles
	sbaout.nFixed = 1;

	// set up projections
	for (int numPoint=0; numPoint<npts; numPoint++)
		{
		// track
		const QHash< int, QPointF> &projections = pointsProjections[numPoint];
		foreach(int numCam, projections.keys())
			{
			const QPointF p = projections[numCam];
			Vector2d pt;
			pt[0] = p.x();
			pt[1] = -p.y();
			sbaout.addMonoProj(numCam,numPoint,pt);
			}
		}
	return 0;
	}

//template <typename SysSBAType>
int recoverReconstructionFromSysSBA(SysSBA &sbain, QList<QVCameraPose> &cameraPoses, QList<QV3DPointF> &points3D, QList< QHash< int, QPointF> > &pointsProjections)
	{
	unsigned int i = 0;

	// Set up transform matrix for camera parameters
	Matrix3d m180x;		// rotate 180 deg around X axis, to convert Bundler frames to SBA frames
	m180x << 1, 0, 0, 0, -1, 0, 0, 0, -1;

	// Then goes information about each camera, in <f> <k1> <k2>\n<R>\n<t> format.
	for (i = 0; i < sbain.nodes.size(); i++)
		{
		Quaternion<double> quat(sbain.nodes[i].qrot);
		quat.normalize();
		Matrix3d rotmat = m180x * quat.toRotationMatrix().transpose();
		Matrix3d &Kcam = sbain.nodes[i].Kcam;

		//Vector3d trans = sbain.nodes[i].trans.start<3>();
		//trans = -rotmat*trans;

		QVMatrix R(3,3), K(3,3);
		for(int idx = 0; idx < 3; idx++)
			for(int jdx = 0; jdx < 3; jdx++)
				{
				R(idx,jdx) = rotmat(idx,jdx);
				K(idx,jdx) = Kcam(idx, jdx);
				}
		K(2,2) = -K(2,2);

		QV3DPointF transX(	sbain.nodes[i].trans(0,0),
							sbain.nodes[i].trans(1,0),
							sbain.nodes[i].trans(2,0) );

		transX = -R * transX;

		const double errorK = ( QVMatrix::identity(3) + K ).norm2();
		if (errorK != 0.0)
			std::cout << "**** ERROR: sSBA changed the intrinsic camera parameters." << std::endl;

		//cameraPoses << QVEuclideanMapping3(QVQuaternion(R), QV3DPointF(trans(0), trans(1), trans(2)));
		cameraPoses << QVEuclideanMapping3(QVQuaternion(R), transX);
		}

	// Then goes information about each point. <pos>\n<color>\n<viewlist>
	for (i = 0; i < sbain.tracks.size(); i++)
		{
		// World <x y z>
		points3D << QV3DPointF(sbain.tracks[i].point(0), sbain.tracks[i].point(1), sbain.tracks[i].point(2));
		ProjMap &prjs = sbain.tracks[i].projections;
		pointsProjections << QHash< int, QPointF>();

		// Output all the tracks as monocular tracks.
		for(ProjMap::iterator itr = prjs.begin(); itr != prjs.end(); itr++)
			{
			Proj &prj = itr->second;
			// y is reversed (-y)
			Node &node = sbain.nodes[prj.ndi];
			
			double cx = node.Kcam(0, 2);
			double cy = node.Kcam(1, 2);
			double coorX = prj.kp(0)-cx;
			double coorY = -(prj.kp(1)-cy);

			pointsProjections[i][prj.ndi] = QPointF(coorX, coorY);
			}
		}
	
	return 0;
	} 

int sSBAOptimization(	const QList<QVCameraPose> &cameraPoses,
			const QList<QV3DPointF> &points3D,
			const QList< QHash<int, QPointF> > &pointsProjections,
			QList<QVCameraPose> &refinedCameraPoses,
			QList<QV3DPointF> &refinedPoints3D,
			int &time_sSBA,
			const int numIters,
			const double lambda,
			const int useCSparse,
			const int numFixedCameras,
			const double initTolCG,
			const int maxItersCG
			)
	{
	Q_ASSERT(not testCheirality(cameraPoses, pointsProjections));

	// Init sSBA algorithm.
	SysSBA sys;
	initReconstructionToSysSBA(sys, cameraPoses, points3D, pointsProjections);

	sys.nFixed = numFixedCameras;

	// Note: You can't select wether to include the intrinsic camera parameters (focal, radial distortion coefficients) in the optimization, or not.
	// Seems that this SBA implementation only optimizes the camera pose.

	// Get the time of LM optimization only.
	QTime time;
	time.start();
	const int numPerformedIters = sys.doSBA(numIters, lambda, useCSparse, initTolCG, maxItersCG);
	time_sSBA = time.elapsed();

	refinedPoints3D.clear();
	refinedCameraPoses.clear();

	QList< QHash< int, QPointF> > refinedPointsProjections;
	recoverReconstructionFromSysSBA(sys, refinedCameraPoses, refinedPoints3D, refinedPointsProjections);

	#ifdef DEBUG
	if (refinedPointsProjections != pointsProjections)
		{
		std::cout << "---------- Lambda ERROR x343432----------------------------------" << std::endl;
		exit(0);
		}
	#endif

	return numPerformedIters;
	}



