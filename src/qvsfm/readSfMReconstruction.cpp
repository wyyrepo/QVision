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

#include <qvsfm.h>

// Read the numbers contained in the file, as a vector
// Faster than 'readVector'.
bool readNumbersFromTextStream(QTextStream &stream, QVVector &numbers, const int estimatedSize)
	{
	numbers.clear();
	numbers.reserve(estimatedSize);

	double sign = +1.0;
	int idx = 0;
	char buffer[256] = "";

	while (not stream.atEnd())
		{
		char c;
		stream >> c;
		//file.getChar(&c);

		// If number, dot, or minus, store in the buffer.
		if (	( (c >= '0') and (c <= '9') ) or 
				( (idx > 0) and (c == 'e') ) or
				(c == '.') //or (c == '-') or (c == '+')
			)
			buffer[idx++] = c;
		// Ignore line comments.
		else if ( c == '#' )
			{
			while ( (c != '\n') and (not stream.atEnd()) )
				stream >> c;
				//file.getChar(&c);
			if (stream.atEnd())
				break;
			}
		else
			{
			buffer[idx] = '\0';

			if (idx > 0)
				numbers << sign * atof(buffer);

			idx = 0;

			if (c == '-')
				sign = -1.0;
			else //if (c == '+')
				sign = +1.0;
			}

		if(idx >= 256)
			{
			std::cout << "[readNumbersFromFile] Error: buffer overrun." << std::endl;
			exit(0);
			}
		}

	return true;
	}


// Read the numbers contained in the file, as a vector
// Faster than 'readVector'.
bool readNumbersFromFile(QFile &file, QVVector &numbers, const int estimatedSize)
	{
	numbers.clear();
	numbers.reserve(estimatedSize);

	double sign = +1.0;
	int idx = 0;
	char buffer[256] = "";

	while (not file.atEnd())
		{
		char c;
		file.getChar(&c);

		// If number, dot, or minus, store in the buffer.
		if (	( (c >= '0') and (c <= '9') ) or 
				( (idx > 0) and (c == 'e') ) or
				(c == '.') //or (c == '-') or (c == '+')
			)
			buffer[idx++] = c;
		// Ignore line comments.
		else if ( c == '#' )
			{
			while ( (c != '\n') and (not file.atEnd()) )
				file.getChar(&c);
			if (file.atEnd())
				break;
			}
		else
			{
			buffer[idx] = '\0';

			if (idx > 0)
				numbers << sign * atof(buffer);

			idx = 0;

			if (c == '-')
				sign = -1.0;
			else //if (c == '+')
				sign = +1.0;
			}

		if(idx >= 256)
			{
			std::cout << "[readNumbersFromFile] Error: buffer overrun." << std::endl;
			exit(0);
			}
		}

	return true;
	}

// Read the numbers contained in the file, as a vector
// Faster than 'readVector'.
bool readNumbersFromFile(const QString fileName, QVVector &numbers, const int estimatedSize)
	{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
		std::cout << "[readNumbersFromFile] Cannot open file " << qPrintable(fileName) << std::endl;
		return false;
		}

	return readNumbersFromFile(file, numbers, estimatedSize);
	}

QVVector readVector(QFile &file)
    {
    bool ok = false;
    while(not file.atEnd())
        {
        const QString line = file.readLine();
        if (line.contains("#"))
            continue;

        const QStringList stringList = line.split(" ", QString::SkipEmptyParts);

        QList<double> vector;
        foreach(QString string, stringList)
            {
            const double value = string.toDouble(&ok);
            if (ok)
                vector << value;
            }
        return vector.toVector();
        }
    return QVVector(0,0.0);
    }

QVVector readVector(const QString &line)
    {
    bool ok = false;
    const QStringList stringList = line.split(" ", QString::SkipEmptyParts);

    QList<double> vector;
    foreach(QString string, stringList)
        {
        const double value = string.toDouble(&ok);
        if (ok)
            vector << value;
        }
    return vector.toVector();
    }


QVMatrix readMatrix(const QString fileName)
    {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return QVMatrix();

    QList<QVVector> rows;
    while (!file.atEnd())
        {
        const QString line = file.readLine();
        if (line.contains("#"))
            continue;

        const QStringList stringList = line.split (" ", QString::SkipEmptyParts);

        QVVector v;
        foreach(QString string, stringList)
            {
            bool ok = false;
            const double value = string.toDouble(&ok);
            if (ok)
                v << value;
            }

        rows << v;
        }
    return QVMatrix(rows);
    }

bool readReconstruction_NVM(	const QString fileName,
								QList<QString> &imageFiles,
								QList<QVMatrix> &cameraCalibrationMatrices,
								QList<QVCameraPose> &cameraPoses,
								QList<QV3DPointF> &points3D,
								QList< QColor > &rgbColors,
								QList< QHash< int, QPointF> > &pointTrackings)
    {
	QVVector temp;

	imageFiles.clear();
	cameraCalibrationMatrices.clear();
    cameraPoses.clear();
    points3D.clear();
    rgbColors.clear();
    pointTrackings.clear();

    int numline = 0;
    std::cout << "[readReconstruction_NVM] Opening file" << std::endl;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

	const QString line = file.readLine();
        if (not line.startsWith("NVM_V3"))
			return false;

	// Read cameras.
	file.readLine();
	temp = readVector(file);
	if (temp.count() != 1)
		return false;
	const int numCameras = temp[0];
	std::cout << "[readReconstruction_NVM] Reading " << numCameras << " cameras...";

	for (int idx = 0; idx < numCameras; idx++)
		{
		const QStringList tokens = QString(file.readLine()).split('\t');
		if (tokens.count() != 2)
			return false;

		temp = readVector(tokens[1]);

		if (temp.count() != 10)
			return false;

		imageFiles << tokens[0];
		cameraCalibrationMatrices << QVMatrix::cameraCalibrationMatrix(temp[0]);
		cameraPoses << QVCameraPose( QVQuaternion(temp[2], temp[3], temp[4], temp[1]), QV3DPointF(temp[5], temp[6], temp[7]));
		}

	std::cout << "done." << std::endl;

	// Read points.
	file.readLine();
	temp = readVector(file);
	if (temp.count() != 1)
		return false;
	const int numPoints = temp[0];
	std::cout << "[readReconstruction_NVM] Reading " << numPoints << " points..." << std::endl;

    for(int i = 0; i < numPoints; i++)
		{
		temp = readVector(file);

		points3D << QV3DPointF(temp[0], temp[1], temp[2]);
		rgbColors << QColor(temp[3], temp[4], temp[5]);
		const int numMeasurements = temp[6];

		if(temp.count() - 7 != numMeasurements * 4)
			return false;

		QHash< int, QPointF> tracking;
		for(int j = 7; j < temp.count(); j+=4)
			tracking[ temp[j] ] = QPointF(temp[j+2], temp[j+3]);
		pointTrackings << tracking;
		}

	return true;

    std::cout << "[readReconstruction_NVM] Readed "	<< numPoints << " points, " << numCameras << " cameras." << std::endl;
    file.close();
    return true;
    }


bool readReconstruction_BAITL(	const QString fileName,
                QList<QVMatrix> &cameraCalibrations,
                QList<QVCameraPose> &cameraPoses,
                QList<QV3DPointF> &points3D,
                QList< QColor > &rgbColors,
                QList< QHash< int, QPointF> > &pointTrackings)
    {
    const QVMatrix	A1 = QVMatrix::diagonal(QV3DPointF(+1.0, -1.0, +1.0)),
            A2 = QVMatrix::diagonal(QV3DPointF(+1.0, +1.0, -1.0)),
            A3 = QVMatrix::diagonal(QV3DPointF(-1.0, +1.0, +1.0));

    cameraPoses.clear();
    points3D.clear();
    rgbColors.clear();
    pointTrackings.clear();

    int numline = 0;
    std::cout << "[readReconstruction_BAITL] Opening file" << std::endl;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    bool ok = false;
    int numCameras = -1, numPoints = -1, numProjections = -1;

    // Read header
    while (not ok and not file.atEnd())
        {
        const QString line = file.readLine();
        if (line.contains("#"))
            continue;

        const QStringList stringList = line.split (" ", QString::SkipEmptyParts);

        numCameras = stringList[0].toInt(&ok);
        numPoints = stringList[1].toInt(&ok);
        numProjections = stringList[2].toInt(&ok);
        numline++;
        }

    const int fractionCameras = numCameras / 7, fractionPoints = numPoints / 7, fractionProjections = numProjections / 7;

    // Read point projections
    for(int i = 0; i < numPoints; i++)
        pointTrackings << QHash< int, QPointF>();

    std::cout << "[readReconstruction_BAITL] Reading " << numProjections << " projections" << std::endl;
    for(int numProjection = 0; numProjection < numProjections; numProjection++)
        {
        const QVVector line = readVector(file);
        numline++;

        if (line.count() != 4)
            std::cout << "Error: in point projections list." << std::endl;

        const int numCamera = line[0], numPoint = line[1];
        const QPointF projection(line[2], line[3]);

        if (numCamera +1 > numCameras or numCamera < 0)
            std::cout << "Error: camera index out of bounds." << std::endl;
        if (numPoint +1 > numPoints or numPoint < 0)
            std::cout << "Error: point index out of bounds." << std::endl;
        pointTrackings[numPoint][numCamera] = -projection;

        if ( numProjection % fractionProjections == 0 )
            std::cout << "[readReconstruction_BAITL]\t" << int(double(100*numProjection) / double(numProjections)) << "% loaded." << std::endl;
        }

    QHash<int, int> fileCameraIndexToRealCameraIndex;
    std::cout << "[readReconstruction_BAITL] Reading " << numCameras << " cameras" << std::endl;
    for(int numCamera = 0; numCamera < numCameras; numCamera++)
        {
        QVVector rodriguesRotation, cameraCenter;

        for(int i = 0; i < 3; i++)
            {
            rodriguesRotation << readVector(file)[0];
            }
        numline+=3;

        for(int i = 0; i < 3; i++)
            cameraCenter << readVector(file)[0];
        numline+=3;

        const double	focal = readVector(file)[0],	// Focal.
                k1 = readVector(file)[0],	// First radial distortion parameter.
                k2 = readVector(file)[0];	// Second radial distortion parameter.
        Q_UNUSED(k1);
        Q_UNUSED(k2);
        numline+=3;

        // Do not add camera if the focal distance is not reasonable.
        if (ABS(focal) < 1e-1)
            {
            std::cout << "******* SMALL FOCAL at line " << numline << " for camera "<< numCamera << " !!! " << focal << std::endl;
            continue;
            }

        if (ABS( focal ) > 1e+10)
            {
            std::cout << "******* LARGE FOCAL at line " << numline << " for camera "<< numCamera << " !!! " << focal << std::endl;
            continue;
            }

        const double angle = rodriguesRotation.norm2();
        const QVVector rotationVector = rodriguesRotation / angle;
        const QVMatrix R = expSO3(rotationVector * angle);

        const QVQuaternion q(R);
        const QVEuclideanMapping3 cameraPose(q, cameraCenter);//q.inverse().rotate(cameraCenter) * (-1.0) );
        QVMatrix K = focal * QVMatrix::identity(3);
        K(2,2) = 1.0;

        // -------------------------
        fileCameraIndexToRealCameraIndex[numCamera] = cameraPoses.count();
        cameraCalibrations << K;
        cameraPoses << cameraPose;

        //if (fileCameraIndexToRealCameraIndex[numCamera] >= cameras.count())
        //	std::cout << "*** ERROR iiiiiii !!!!!!!!! " << numCamera << ", " << cameras.count() << std::endl;

        if ( numCamera % fractionCameras == 0 )
            std::cout << "[readReconstruction_BAITL]\t" << int(double(100*numCamera) / double(numCameras)) << "% loaded." << std::endl;
        }

    // Reorganize projections container, eliminating projections to not added cameras due to unreasonable focal distances,
    // and adjusting camera indexes.
    for(int i = 0; i < pointTrackings.size(); i++)
        {
        const QHash< int, QPointF> &oldCorrespondences = pointTrackings[i];

        QHash< int, QPointF> newCorrespondences;

        foreach(int numCamera, oldCorrespondences.keys())
            if (fileCameraIndexToRealCameraIndex.contains(numCamera))
                newCorrespondences[ fileCameraIndexToRealCameraIndex[ numCamera ] ] = oldCorrespondences[numCamera];

        pointTrackings[i] = newCorrespondences;
        }

    std::cout << "[readReconstruction_BAITL] Reading " << numPoints << " points" << std::endl;

    // Read points
    for(int numPoint = 0; numPoint < numPoints; numPoint++)
        {
        QVVector point;
        for(int i = 0; i < 3; i++)
            point << readVector(file)[0];
        points3D << point;
        rgbColors << QColor(128,128,128);

        if ( numPoint % fractionPoints == 0 )
            std::cout << "[readReconstruction_BAITL]\t" << int(double(100*numPoint) / double(numPoints)) << "% loaded." << std::endl;
        }

    std::cout << "[readReconstruction_BundlerOutput] Readed "	<< numPoints << " points, " << numCameras << " cameras." << std::endl;
    file.close();
    return true;
    }

/*bool readReconstruction_BundlerOutput(	const QString &fileName,
                    QList<QVMatrix> &cameraCalibrations,
                    QList<QVVector> &cameraRadialParameters,
                    QList<QVCameraPose> &cameraPoses,
                    QList<QV3DPointF> &points3D,
                    QList<QHash<int, QPointF> > &pointTrackings,
                    QList< QColor > &rgbColors
                    )

    {
    cameraCalibrations.clear();
    cameraRadialParameters.clear();
    cameraPoses.clear();
    points3D.clear();
    pointTrackings.clear();
    rgbColors.clear();

    std::cout << "[readReconstruction_BundlerOutput] Opening file" << std::endl;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
        std::cout << "[readReconstruction_BundlerOutput] Could not open file '" << qPrintable(fileName) << "'" << std::endl;
        return false;
        }

    // Read header
    const QString line = file.readLine();
    if (not line.contains("# Bundle file v0.3"))
        {
        std::cout << "[readReconstruction_BundlerOutput] The file does not seems to contain a valid Bulde 0.3 format." << std::endl;
        file.close();
        return false;
        }

    // Read number of cameras and points
    bool ok = false;
    int numCameras = -1, numPoints = -1;

    while (not ok and not file.atEnd())
        {
        const QString line = file.readLine();
        if (line.contains("#"))
            continue;

        const QStringList stringList = line.split (" ", QString::SkipEmptyParts);

        numCameras = stringList[0].toInt(&ok);
        numPoints = stringList[1].toInt(&ok);
        }

    const int fractionCameras = numCameras / 7, fractionPoints = numPoints / 7;

    std::cout << "[readReconstruction_BundlerOutput] Reading cameras." << std::endl;
    // Read cameras
    int numCamera, numPoint, numProjections = 0;
    QHash<int, int> virtualCameraIndexToRealCameraIndex;
    for(numCamera = 0; numCamera < numCameras and not file.atEnd(); numCamera++)
        {
        const QVVector intrinsics = readVector(file);

        QList<QVVector> Rlist;
        Rlist << readVector(file);
        Rlist << readVector(file);
        Rlist << readVector(file);

        const QVMatrix R(Rlist);
        const QVQuaternion q(R);

        const QVVector t = readVector(file);
        const QVEuclideanMapping3 cameraPose(q, t);
        QVMatrix K = intrinsics[0]*QVMatrix::identity(3);
        K(2,2) = 1.0;

        if (t != QV3DPointF(0.0, 0.0, 0.0))
            {
            virtualCameraIndexToRealCameraIndex[numCamera] = cameraPoses.count();
            cameraCalibrations << K;
            cameraPoses << cameraPose;
            cameraRadialParameters << intrinsics.mid(1);
            }
        if ( numCamera % fractionCameras == 0 )
            std::cout << "[readReconstruction_BundlerOutput]\t" << int(double(100*numCamera) / double(numCameras)) << "% loaded." << std::endl;
        }

    std::cout << "[readReconstruction_BundlerOutput] Reading points" << std::endl;
    // Read points
    for(numPoint = 0, numProjections = 0; numPoint < numPoints and not file.atEnd(); numPoint++)
        {
        const QVVector	position = readVector(file),
                color = readVector(file),
                viewList = readVector(file);

        points3D << position;
        rgbColors << QColor(int(color[0]), int(color[1]),int(color[2]));

        if (viewList[0] != (viewList.count() -1) / 4)
            std::cout << "Error: in point projections list." << std::endl;
        else	{
            QHash< int, QPointF> projections;
            for (int i = 1; i < viewList.count(); i+=4)
                {
                const int numCamera = viewList[i];
                const double coorX = viewList[i+2], coorY =  viewList[i+3];
                if (numCamera +1 > numCameras or numCamera < 0)
                    std::cout << "Error: camera index out of bounds." << std::endl;
                if (virtualCameraIndexToRealCameraIndex.contains( numCamera ))
                    projections[ virtualCameraIndexToRealCameraIndex[ numCamera ] ] = -QPointF( coorX, coorY );
                else
                    std::cout << "Error: found point projection for uninitialized camera pose." << std::endl;
                }
            pointTrackings << projections;
            numProjections += projections.count();
            }
        if ( numPoint % fractionPoints == 0 )
            std::cout << "[readReconstruction_BundlerOutput]\t" << int(double(100*numPoint) / double(numPoints)) << "% loaded." << std::endl;
        }

    file.close();
    return true;
    }*/

bool readReconstruction_BundlerOutput(	const QString &fileName,
                    QList<QVMatrix> &cameraCalibrations,
                    QList<QVVector> &cameraRadialParameters,
                    QList<QVCameraPose> &cameraPoses,
                    QList<QV3DPointF> &points3D,
                    QList<QHash<int, QPointF> > &pointTrackings,
                    QList< QColor > &rgbColors
                    )

    {
    cameraCalibrations.clear();
    cameraRadialParameters.clear();
    cameraPoses.clear();
    points3D.clear();
    pointTrackings.clear();
    rgbColors.clear();

    std::cout << "[readReconstruction_BundlerOutput] Opening file" << std::endl;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
        std::cout << "[readReconstruction_BundlerOutput] Could not open file '" << qPrintable(fileName) << "'" << std::endl;
        return false;
        }

    // Read header
    const QString line = file.readLine();
    if (not line.contains("# Bundle file v0.3"))
        {
        std::cout << "[readReconstruction_BundlerOutput] The file does not seems to contain a valid Bulde 0.3 format." << std::endl;
        file.close();
        return false;
        }

    // Read number of cameras and points
    bool ok = false;
    int numCameras = -1, numPoints = -1;

    while (not ok and not file.atEnd())
        {
        const QString line = file.readLine();
        if (line.contains("#"))
            continue;

        const QStringList stringList = line.split (" ", QString::SkipEmptyParts);

        numCameras = stringList[0].toInt(&ok);
        numPoints = stringList[1].toInt(&ok);
        }

    const int fractionCameras = numCameras / 7, fractionPoints = numPoints / 7;

    std::cout << "[readReconstruction_BundlerOutput] Reading " << numCameras << " cameras." << std::endl;

    // Read cameras
    int numCamera, numPoint, numProjections = 0;
    QHash<int, int> virtualCameraIndexToRealCameraIndex;
    for(numCamera = 0; numCamera < numCameras and not file.atEnd(); numCamera++)
        {
        const QVVector intrinsics = readVector(file);

        QList<QVVector> Rlist;
        Rlist << readVector(file);
        Rlist << readVector(file);
        Rlist << readVector(file);

        const QVMatrix R(Rlist);
        const QVVector t = readVector(file);

        if ( numCamera % fractionCameras == 0 )
            std::cout << "[readReconstruction_BundlerOutput]\t" << int(double(100*numCamera) / double(numCameras)) << "% loaded." << std::endl;

		if (R.norm2() == 0)
			continue;

		Q_ASSERT( (QVMatrix::identity(3)-R.transpose()* R).norm2() < 1e-6 );

        if (t != QV3DPointF(0.0, 0.0, 0.0))
            {
            virtualCameraIndexToRealCameraIndex[numCamera] = cameraPoses.count();
            cameraCalibrations << QVMatrix::cameraCalibrationMatrix(intrinsics[0]);
            cameraPoses << QVEuclideanMapping3(R | t);
            cameraRadialParameters << intrinsics.mid(1);
            }
        }

    std::cout << "[readReconstruction_BundlerOutput] Reading points" << std::endl;
    // Read points
    for(numPoint = 0, numProjections = 0; numPoint < numPoints and not file.atEnd(); numPoint++)
        {
        const QVVector	position = readVector(file),
                color = readVector(file),
                viewList = readVector(file);

        points3D << position;
        rgbColors << QColor(int(color[0]), int(color[1]),int(color[2]));

        if (viewList[0] != (viewList.count() -1) / 4)
            std::cout << "Error: in point projections list." << std::endl;
        else	{
            QHash< int, QPointF> projections;
            for (int i = 1; i < viewList.count(); i+=4)
                {
                const int numCamera = viewList[i];
                const double coorX = viewList[i+2], coorY =  viewList[i+3];
                if (numCamera +1 > numCameras or numCamera < 0)
                    std::cout << "Error: camera index out of bounds." << std::endl;
                if (virtualCameraIndexToRealCameraIndex.contains( numCamera ))
                    projections[ virtualCameraIndexToRealCameraIndex[ numCamera ] ] = -QPointF( coorX, coorY );
                else
                    std::cout << "Error: found point projection for uninitialized camera pose." << std::endl;
                }
            pointTrackings << projections;
            numProjections += projections.count();
            }
        if ( numPoint % fractionPoints == 0 )
            std::cout << "[readReconstruction_BundlerOutput]\t" << int(double(100*numPoint) / double(numPoints)) << "% loaded." << std::endl;
        }

    file.close();
    return true;
    }

bool readCameras_laSBA(const QString fileName, QList<QVCameraPose> &cameraPoses)
    {
    QFile file(fileName);
    if (not file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    while (not file.atEnd())
        {
        const QString line = file.readLine();
        if (line.contains("#"))
            continue;

        const QStringList stringList = line.split (" ", QString::SkipEmptyParts);

        QVVector v;
        foreach(QString string, stringList)
            {
            bool ok = false;
            const double value = string.toDouble(&ok);
            if (ok)
                v << value;
            }

        const QVQuaternion q(v[1], v[2], v[3], v[0]);
        const QV3DPointF t(v[4], v[5], v[6]);

        cameraPoses << QVEuclideanMapping3(q, t);
        }

    return true;
    }

bool readPoints_laSBA(const QString fileName, QList<QV3DPointF> &points3D, QList<QHash<int, QPointF> > &pointTrackings)
    {
    QFile file(fileName);
    if (not file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    while (not file.atEnd())
        {
        const QString line = file.readLine();

        if (line.contains("#"))
            continue;

        const QStringList stringList = line.split (" ", QString::SkipEmptyParts);
        QVVector v;
        foreach(QString string, stringList)
            {
            bool ok = false;
            const double value = string.toDouble(&ok);
            if (ok)
                v << value;
            }

        const QV3DPointF t(v[0], v[1], v[2]);

        QHash<int, QPointF> projections;
        for(int i = 4; i < v.size(); i+=3)
            projections[ v[i] ] = QPointF(v[i+1], v[i+2]);
        pointTrackings << projections;
        points3D << t;
        }

    return true;
    }

bool readSfMReconstruction_laSBA(	const QString &filesPath,
                    QList<QVMatrix> &cameraCalibrations,
                    QList<QVCameraPose> &cameraPoses,
                    QList<QV3DPointF> &points3D,
                    QList<QHash<int, QPointF> > &pointTrackings
                    )
    {
    cameraCalibrations.clear();
    cameraPoses.clear();
    points3D.clear();
    pointTrackings.clear();

    const QVMatrix Ks = readMatrix(filesPath + "/calib.txt");
	Q_ASSERT(Ks.getCols() == 3);
	Q_ASSERT(Ks.getRows() == 3);

    for(int i = 0; i < Ks.getRows(); i+=3)
        cameraCalibrations << Ks.getSubmatrix(i, i+2, 0, 2);

    if (not readCameras_laSBA(filesPath + "/cams.txt", cameraPoses))
        {
        std::cout << "[readSfMReconstruction_laSBA] Error: could not read file " << qPrintable(filesPath + "/cams.txt") << std::endl;
        return false;
        }

    if (not readPoints_laSBA(filesPath + "/pts.txt", points3D, pointTrackings))
        {
        std::cout << "[readSfMReconstruction_laSBA] Error: could not read file " << qPrintable(filesPath + "/pts.txt") << std::endl;
        return false;
        }

	Q_ASSERT_X( (cameraCalibrations.count() == 1) or (cameraCalibrations.count() == cameraPoses.count()), "[readSfMReconstruction_laSBA]", "Error reading calibrations from file: incorrect number.");

    return true;
    }

#include <QFileInfo>
bool readSfMReconstruction(	const QString &path,
                QList<QVMatrix> &cameraCalibrations,
                QList<QVCameraPose> &initialCameraPoses,
                QList<QV3DPointF> &filePoints3D,
                QList<QHash<int, QPointF> > &pointsProjections
                )
    {
    const QFileInfo info(path);

    if (not info.exists())
        {
        std::cout << "[readSfMReconstruction] Error: specified path '" << qPrintable(path) << "' does not exists." << std::endl;
        return false;
        }
    else if (info.isDir())
        {
        if (not readSfMReconstruction_laSBA(path, cameraCalibrations, initialCameraPoses, filePoints3D, pointsProjections))
            {
            std::cout << "[readSfMReconstruction] Specified path is a directory, but one of the files is missing: 'calib.txt', 'pts.txt' or 'cams.txt'." << std::endl;
            return false;
            }
        }
    else if (info.isFile())
        {
        QList< QColor > rgbColors;
        QList<QVVector> cameraRadialParameters;

        if ( not readReconstruction_BundlerOutput(path, cameraCalibrations, cameraRadialParameters, initialCameraPoses, filePoints3D, pointsProjections, rgbColors) )
            // Try with a "Bundle Adjustment in the Large" dataset type.
            if ( not readReconstruction_BAITL(path, cameraCalibrations, initialCameraPoses, filePoints3D, rgbColors, pointsProjections) )
                {
                std::cout << "[readSfMReconstruction] Could not load reconstruction from specified file." << std::endl;
                return false;
                }
        }

    return true;
    }

// ----------------------
#include <QTextStream>
bool saveMatrix(const QString fileName, const QVMatrix &matrix)
	{
	QFile file(fileName);
	if (not file.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

	QTextStream stream(&file);

	stream.setRealNumberPrecision(16); // Default is 6, not enough precission to faithfully store certain maps.

	const double *data = matrix.getReadData();
	for (int i=0; i < matrix.getRows(); i++)
		{
		for (int j = 0; j < matrix.getCols(); j++)
			stream << qPrintable(QString("%1").arg(data[i*matrix.getCols() + j], -8, 'f', 6)) << " ";
		stream << "\n";
		}

	file.close();
	return true;
	}

void writeCameras_laSBA(const QString &fileName, const QList<QVCameraPose> &cameraPoses)
	{
	QList<QVVector> cameraVectors;
	foreach(QVCameraPose cameraPose, cameraPoses)
		cameraVectors << cameraPose.operator QVEuclideanMapping3();

	const QVMatrix cameraPosesMatrixPre(cameraVectors);
	const QVMatrix cameraPosesMatrix = QVMatrix(cameraPosesMatrixPre.getCol(3)).transpose()
										| cameraPosesMatrixPre.getCol(0)
										| cameraPosesMatrixPre.getCol(1)
										| cameraPosesMatrixPre.getCol(2)
										| cameraPosesMatrixPre.getCol(4)
										| cameraPosesMatrixPre.getCol(5)
										| cameraPosesMatrixPre.getCol(6);

	saveMatrix(fileName, cameraPosesMatrix);
	}

#include <fstream>
#include <iostream>
void writePoints_laSBA(const QString fileName, const QList<QV3DPointF> &points3D, const QList<QHash<int, QPointF> > &pointTrackings)
	{
	QFile file(fileName);
	if (not file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;

	QTextStream stream(&file);

	stream.setRealNumberPrecision(16); // Default is 6, not enough precission to faithfully store certain maps.

	for (int i=0; i < points3D.size(); i++)
		{
		for (int j = 0; j < points3D[i].size(); j++)
			stream << qPrintable(QString("%1").arg(points3D[i][j], -8, 'f', 6)) << " ";
		stream << qPrintable(QString("%1").arg(pointTrackings[i].count(), -8)) << " ";
		foreach(int index, pointTrackings[i].keys())
			stream	<< qPrintable(QString("%1").arg(index, -8)) << " "
					<< qPrintable(QString("%1").arg(pointTrackings[i][index].x(), -8, 'f', 6)) << " "
					<< qPrintable(QString("%1").arg(pointTrackings[i][index].y(), -8, 'f', 6)) << " ";
		stream << "\n";
		}

	file.close();
	}

