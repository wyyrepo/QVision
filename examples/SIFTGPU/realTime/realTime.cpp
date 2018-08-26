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

/*!
@file realTime.cpp
@ingroup SIFTGPUExamplePrograms
@brief Performs real-time SIFT detection and matching on the frames from an input video sequence using SIFTGPU.

<a href="http://www.cs.unc.edu/~ccwu/siftgpu/">SIFTGPU</a> is a software package with functionality to perform parallel SIFT detection and matching on GPU hardware.
This example uses QVision wrapper functions for that software package to detect SIFT features on the input frames of a video sequence.
Those wrapper functions are also used to perform feature matching between the most recent frame in the video sequence and a key-frame selected by the user.

See file 'config.pri' to enable QVision compatibility with the SIFTGPU package.

@section Usage
Once compiled, the program should be used with this command line:
\code
	./realTime --URL=<path or url to video>
\endcode

An image canvas shows the input frame and the SIFT features detected on it, with the orientation and the scale indicated with a segment line drawn from the location of each feature:

@image html SIFTGPU-features.png
@image latex SIFTGPU-features.png

<p>Pushing the button <i>Grab reference frame</i> sets the actual frame as the key-frame.</p>
<p>Then the application will match the SIFT features detected at the key-frame with the features detected at each new input frame from the video sequence.<p>
</p>These matchings are shown in another image canvas:</p>

@image html SIFTGPU-matchings.png
@image latex SIFTGPU-matchings.png


@param URL Video source identification string. See dynamic property URL for @ref QVMPlayerCamera.
@author PARP Research Group. University of Murcia, Spain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QDebug>

#include <QVApplication>
#include <QVVideoReaderBlock>
#include <QVDefaultGUI>
#include <QVImageCanvas>

#include <qvipp.h>
#include <qvsiftgpu.h>

#ifndef DOXYGEN_IGNORE_THIS

class SIFTGPUMatcher: public QVProcessingBlock
	{
	private:
		QVImage<uChar, 3> referenceFrame;
		QList<QVSIFTFeature> referenceFrameFeatures;

	public:
		SIFTGPUMatcher(QString name): QVProcessingBlock(name),
			referenceFrame(1,1)
			{
			addProperty< QVImage<uChar,3> >("Actual frame", inputFlag|outputFlag);
			addProperty< QList<QPointF> >("Actual features", outputFlag);
			addProperty< QList<QVPolylineF> >("Actual features orientations", outputFlag);

			// Matching with reference frame
			addProperty< QVImage<uChar,3> >("Matching images", outputFlag);
			addProperty< QList<QPointFMatching> >("Matching correspondences", outputFlag);

			addTrigger("Grab reference frame");
			}

		// Sets the reference frame
		void processTrigger(const QString triggerName)
			{
			referenceFrame = getPropertyValue< QVImage<uChar,3> >("Actual frame");
			referenceFrameFeatures = getSiftGPUFeatures(referenceFrame, CUDA_METHOD);
			//setPropertyValue< QVImage<uChar,3> >("Reference frame", referenceFrame);
			}

		void iterate()
			{
			// Read actual image frame.
			const QVImage<sFloat,3> actualFrame = getPropertyValue< QVImage<uChar,3> >("Actual frame");
			timeFlag("Read input image");

			// Get SIFT features for the actual frame.
			const QList<QVSIFTFeature> actualFrameFeatures = getSiftGPUFeatures(actualFrame, CUDA_METHOD);
			timeFlag("Get SIFT features");

			// Show SIFT features.
			QList<QPointF> points;
			QList<QVPolylineF> orientations;
			foreach(QVSIFTFeature feature, actualFrameFeatures)
				{
				QVPolylineF orientation;
				orientation << feature.keypoint.location();
				orientation << feature.keypoint.location() + 3.0 * ABS(feature.keypoint.scale()) * QPointF(	sin(feature.keypoint.orientation()),
																													cos(feature.keypoint.orientation()));
				orientations << orientation;
				points << feature.keypoint.location();
				}
			setPropertyValue< QList<QPointF> >("Actual features", points);
			setPropertyValue< QList<QVPolylineF> >("Actual features orientations", orientations);
			timeFlag("Show SIFT features");

			if (referenceFrame.getCols() == 1 and referenceFrame.getRows() == 1)
				return;

			// Get matchings between actual and reference features.
			const QList< QPair<int, int> > matchings = matchSiftGPUFeatures(actualFrameFeatures, referenceFrameFeatures);
			timeFlag("Match with reference frame");

			// Show SIFT matchings.
			const QPointF offset(referenceFrame.getCols(), 0);
			QList<QPointFMatching> matchingCorrespondences;
			for(int i = 0; i < matchings.count(); i++)
				{
				const QPointF	sourcePoint = referenceFrameFeatures[matchings[i].second].keypoint.location(),
								destinationPoint = actualFrameFeatures[matchings[i].first].keypoint.location();

				matchingCorrespondences << QPointFMatching(	sourcePoint,
															destinationPoint + offset);
				}

			QVImage<uChar, 3> matchingImages = referenceFrame;
			Copy(actualFrame, matchingImages, QPoint(referenceFrame.getCols(), 0));
			matchingImages.resetROI();

			setPropertyValue< QVImage<uChar,3> >("Matching images", matchingImages);
			setPropertyValue< QList<QPointFMatching> >("Matching correspondences", matchingCorrespondences);
			timeFlag("Show matchings");
			}
	};

int main(int argc, char *argv[])
	{
	QVApplication app(argc, argv,
		"Example program for QVision library. Performs SIFT feature detection and matching on an input video sequence."
		);

	SIFTGPUMatcher SIFTMatcher("SIFT matcher");

	QVVideoReaderBlock videoReader("Video");
	videoReader.linkProperty(&SIFTMatcher,"Actual frame");

	QVDefaultGUI interface;

	// Image canvas for displaying SIFT features.
	QVImageCanvas actualFrame("Actual frame");
	SIFTMatcher.linkProperty("Actual frame", actualFrame);
	SIFTMatcher.linkProperty("Actual features", actualFrame);
	SIFTMatcher.linkProperty("Actual features orientations", actualFrame);
	actualFrame.setRadius("Actual features", 2);
	actualFrame.setColor("Actual features orientations", Qt::blue);

	// Image canvas for displaying SIFT matchings.
	QVImageCanvas referenceFrame("Matchings");
	SIFTMatcher.linkProperty("Matching images", referenceFrame);
	SIFTMatcher.linkProperty("Matching correspondences", referenceFrame);
	referenceFrame.setRadius("Matching correspondences", 2);

	return app.exec();
	}

#endif
