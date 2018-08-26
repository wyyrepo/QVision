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

#ifndef READSFMRECONSTRUCTION_H
#define READSFMRECONSTRUCTION_H

#include <QFile>
#include <qvprojective.h>

#ifndef DOXYGEN_IGNORE_THIS
bool readNumbersFromFile(const QString fileName, QVVector &result, const int estimatedSize = 10000);
bool readNumbersFromFile(QFile &file, QVVector &numbers, const int estimatedSize = 10000);
bool readNumbersFromTextStream(QTextStream &stream, QVVector &result, const int estimatedSize = 10000);
bool readPoints_laSBA(const QString fileName, QList<QV3DPointF> &points3D, QList<QHash<int, QPointF> > &pointTrackings);
#endif // DOXYGEN_IGNORE_THIS

/*!
@brief Loads a SfM reconstruction from a file or files.
This function loads a SfM reconstruction from three different file formats.
The function detects the correct file format automatically, depending on the type (directory or file), and the headers of the files.

The readable file formats are:

<ul>
<li><b>laSBA demo file format:</b> the parameter <i>path</i> contains the path to a directory containing the following files:
	- pts.txt (containing the points).
	- cams.txt (containing the camera poses).
	- calib.txt (containing the intrinsic calibration matrices for each camera).

The format of these files is the same used by the example applications included in the
<a href="http://www.ics.forth.gr/~lourakis/sba/">laSBA</a> package.
This is an extract from the file 'README.txt' describing these formats:
\code
eucsbademo accepts 3 file names as arguments:
They are the initial estimates for the camera motion (i.e. pose) parameters, the initial
estimates for the 3D point parameters along with the 3D points image projections and the
camera intrinsic calibration parameters. The file for the camera motion parameters has a
separate line for every camera (i.e. frame), each line containing 7 parameters (a 4
element quaternion for rotation and a 3 element vector for translation). Rotation
quaternions have the scalar part as their first element, i.e. a rotation by angle TH
around the unit vector U=(Ux, Uy, Uz) should be specified as
cos(TH/2) Ux*sin(TH/2) Uy*sin(TH/2) Uz*sin(TH/2).
The file for 3D points and image projections is made up of lines of the form 

X Y Z  NFRAMES  FRAME0 x0 y0  FRAME1 x1 y1 ...

each corresponding to a single 3D point. X Y Z are the points' Euclidean 3D coordinates,
NFRAMES the total number of images in which the points' projections are available and each
of the NFRAMES subsequent triplets FRAME x y specifies that the 3D point in question projects
to pixel x y in image FRAME. For example, the line

100.0 200.0 300.0 3  2 270.0 114.1 4 234.2 321.7 5 173.6 425.8

specifies the 3D point (100.0, 200.0, 300.0) projecting to the 3 points (270.0, 114.1),
(234.2, 321.7) and (173.6, 425.8) in images 2, 4 and 5 respectively. Pixel coordinates
are measured using the common convention, i.e. from the top left corner of images with
the positive x axis running from left to right and y from top to bottom. Camera and 3D
point indices count from 0.
\endcode
</li>

<li><b><i>BAITL</i> data-set file format:</b>
	The file specified in the <i>path</i> parameter must follow the format of the data-sets referenced by the paper <i>Bundle Adjustment in the Large</i>

	These data-sets were obtained with the <a href="http://phototour.cs.washington.edu/bundler/">Bundler</a> SfM system.
	You can find a description for this file format <a href="http://grail.cs.washington.edu/projects/bal/">here</a>.
</li>

<li><b>Bundler output format:</b> this is the standard file format for the output of the <a href="http://phototour.cs.washington.edu/bundler/">Bundler</a> SfM system.
A description of the format follows:
	\code
Bundler produces files typically called 'bundle_*.out' (we'll call
these "bundle files").  With the default commands, Bundler outputs a
bundle file called 'bundle_<n>.out' containing the current state of
the scene after each set of images has been registered (n = the number
of currently registered cameras).  After all possible images have been
registered, Bundler outputs a final file named 'bundle.out'.  In
addition, a "ply" file containing the reconstructed cameras and points
is written after each round.  These ply files can be viewed with the
"scanalyze" mesh viewer, available at
http://graphics.stanford.edu/software/scanalyze/.

The bundle files contain the estimated scene and camera geometry have
the following format:

# Bundle file v0.3
<num_cameras> <num_points>   [two integers]
<camera1>
<camera2>
...
<cameraN>
<point1>
<point2>
...
<pointM>

Each camera entry <cameraI> contains the estimated camera intrinsics
and extrinsics, and has the form:

<f> <k1> <k2>   [the focal length, followed by two radial distortion coeffs]
<R>             [a 3x3 matrix representing the camera rotation]
<t>             [a 3-vector describing the camera translation]

The cameras are specified in the order they appear in the list of
images.

Each point entry <pointI> has the form:
<position>      [a 3-vector describing the 3D position of the point]
<color>         [a 3-vector describing the RGB color of the point]
<view list>     [a list of views the point is visible in]

The view list begins with the length of the list (i.e., the number of
cameras the point is visible in).  The list is then given as a list of
quadruplets <camera> <key> <x> <y>, where <camera> is a camera index,
<key> the index of the SIFT keypoint where the point was detected in
that camera, and <x> and <y> are the detected positions of that
keypoint.  Both indices are 0-based (e.g., if camera 0 appears in the
list, this corresponds to the first camera in the scene file and the
first image in "list.txt").  

We use a pinhole camera model; the parameters we estimate for each
camera are a focal length (f), two radial distortion parameters (k1
and k2), a rotation (R), and translation (t), as described in the file
specification above.  The formula for projecting a 3D point X into a
camera (R, t, f) is:

    P = R * X + t       (conversion from world to camera coordinates)
    p = -P / P.z        (perspective division)
    p' = f * r(p) * p   (conversion to pixel coordinates)

where P.z is the third coordinate of P.  In the last equation, r(p) is
a function that computes a scaling factor to undo the radial
distortion:

r(p) = 1.0 + k1 * ||p||^2 + k2 * ||p||^4.

This gives a projection in pixels, where the origin of the image is
the center of the image, the positive x-axis points right, and the
positive y-axis points up (in addition, in the camera coordinate
system, the positive z-axis points backwards, so the camera is looking
down the negative z-axis, as in OpenGL).

Finally, the equations above imply that the camera viewing direction
is:

    R' * [0 0 -1]'  (i.e., the third row of R or third column of R')

(where ' indicates the transpose of a matrix or vector).

and the 3D position of a camera is 

    -R' * t .
	\endcode
</li>
</ul>
@param path Path to the file (formats Bundler or BAITL), or directory (format laSBA) containing the files for the reconstruction.
@param cameraCalibrations Output parameter containing the intrinsic calibration matrices for the cameras in the reconstruction.
	The list can contain either one matrix for each camera, or a single common calibration matrix for every view in the reconstruction if their calibration is the same.
@param cameraPoses On output, contains the camera poses for the views in the reconstruction.
@param points3D On output contains the 3D points.
@param pointsProjection Output list. Each element contains the image projections of one of the 3D points, on each view it is visible.
	The projection of the i-th 3D point, on the j-th view can be accessed with the expression 'pointTrackings[i][j]'.
@ingroup qvsfm
*/
bool readSfMReconstruction(	const QString &path,
				QList<QVMatrix> &cameraCalibrations,
				QList<QVCameraPose> &cameraPoses,
				QList<QV3DPointF> &points3D,
				QList<QHash<int, QPointF> > &pointsProjections
				);

/*!
@brief Loads a SfM reconstruction from a NVM file.

This function loads a SfM reconstruction from the reconstruction files provided by the <a href = "http://homes.cs.washington.edu/~ccwu/vsfm/doc.html">Visual SfM</a> application.
The function detects the correct file format automatically, depending on the type (directory or file), and the headers of the files.

@param fileName Path to the .NVM file containing the reconstruction.
@param imageFiles List of paths to the input image files.
@param cameraCalibrations Output parameter containing the intrinsic calibration matrices for the cameras in the reconstruction.
	The list can contain either one matrix for each camera, or a single common calibration matrix for every view in the reconstruction if their calibration is the same.
@param cameraPoses On output, contains the camera poses for the views in the reconstruction.
@param points3D On output contains the 3D points.
@param pointTrackings Projection trackings for the 3D points. Each element in this list contains the image projections of one of the 3D points, on each view it is visible.
	The projection of the i-th 3D point, on the j-th view can be accessed with the expression 'pointTrackings[i][j]'.
@ingroup qvsfm
*/
bool readReconstruction_NVM(	const QString fileName,
								QList<QString> &imageFiles,
								QList<QVMatrix> &cameraCalibrationMatrices,
								QList<QVCameraPose> &cameraPoses,
								QList<QV3DPointF> &points3D,
								QList< QColor > &rgbColors,
								QList< QHash< int, QPointF> > &pointTrackings);

#ifndef DOXYGEN_IGNORE_THIS
void writePoints_laSBA(const QString fileName, const QList<QV3DPointF> &points3D, const QList<QHash<int, QPointF> > &pointTrackings);
void writeCameras_laSBA(const QString &fileName, const QList<QVCameraPose> &cameraPoses);
bool saveMatrix(const QString fileName, const QVMatrix &matrix);
QVVector readVector(const QString &line);
#endif // DOXYGEN_IGNORE_THIS

#endif

