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

#ifndef QVKLTTRACKER_H
#define QVKLTTRACKER_H

#include <GL/glew.h>
#include <QVImage>
#include <QGLPixelBuffer>

#include "v3d_gpuklt.h"

using namespace V3D_GPU;

/*!
@class QVKLTTrackerFeature qvgpukltflow/qvklttracker.h QVKLTTrackerFeature
@brief Image feature location used by the GPU-KLT tracker.

@ingroup qvgpukltflow
*/
class QVKLTTrackerFeature{
private:
    QPointF position;
    float gain;

public:
    QVKLTTrackerFeature() { };

    QVKLTTrackerFeature(float x, float y, float gain) {
        this->position = QPointF(x,y);
        this->gain = gain;
    }

    void setGain (float gain){
        this->gain = gain;
    }
    void setPosition (float x, float y){
            this->position = QPointF(x,y);
    }

    float getGain() const {
        return gain;
    }

    QPointF getPosition() const{
        return position;
    };
};

/*!
@class QVKLTTracker qvgpukltflow/qvklttracker.h QVKLTTracker
@brief Wrapper class to perform image feature tracking with the GPU-KLT library.

@ingroup qvgpukltflow
*/
class QVKLTTracker
{
public:
    //Constructors

    /// @brief Default constructor
    /// Do nothing.
    QVKLTTracker() { };

    /// @brief Allocation constructor.
    ///
    /// This method initializes and configures a new tracker with parameters below.
    /// @param width Number of cols of the images.
    /// @param height Number of rows of the images.
    /// @param trackWithGain Wether the tracker uses the gain in the tracking method or not.
    /// @param featuresWidth featuresWidth*featuresHeight gives the maximum number of features to track.
    /// @param featuresHeight featuresWidth*featuresHeight gives the maximum number of features to track.
    /// @param nIterations Number of iterations.
    /// @param nLevels Number of pyramid levels to skip. Reasonable values are 1 (all levels) and nLevels-1 (2 levels only)
    /// @param levelSkip Number of pyramid levels to skip.
    /// @param windowWidth Size of KLT window.
    /// @param trackBorderMargin Size of the border image margin when tracking.
    /// @param detectBorderMargin Size of the border image margin when redetecting.
    /// @param convergenceThreshold Convergence threshold for KLT.
    /// @param SSD_Threshold SSD threshold for KLT.
    /// @param minDistance Minimum distance among tracked features.
    /// @param minConnerness Minimum degree of cornerness for detecting new features.
    QVKLTTracker(int width, int height, bool trackWithGain=true,
                 int featuresWidth=64, int featuresHeight=64,
                 int nIterations=10, int nLevels=4, int levelSkip=1,int windowWidth=7,
                 float trackBorderMargin=20.0f, float detectBorderMargin=20.0f,
                 float convergenceThreshold=0.1f, float SSD_Threshold=5000.0f,
                 int minDistance=7, float minCornerness=50.0f);

    //Destructors
    // @brief Default destructor
    /// Deallocate the tracker from the GPU
    ~QVKLTTracker();

    /// @brief Detect all features in image from scratch.
    ///
    /// This method builds a hash with freshly detected features.
    /// @param image Input image.
    /// @param features Pointer to created hash.
    void detect (const QVImage<uChar,1> &image, QHash<int, QVKLTTrackerFeature> &features);

    /// @brief Detect new features while respecting old ones.
    ///
    /// This method updates the feature hash with new features while respecting old ones.
    /// @param image Input image.
    /// @param features Pointer to hash that will be updated.
    void redetect (const QVImage<uChar,1> &image, QHash<int, QVKLTTrackerFeature> &features);

    /// @brief Track features in the hash.
    ///
    /// This method updates the hash with the new positions of the features, deleting the lost ones.
    /// @param image Input image
    /// @param features Pointer to hash that will be updated.
    void track (const QVImage<uChar,1> &image, QHash<int, QVKLTTrackerFeature> &features);

private:
      void updateHashTable( QHash<int,QVKLTTrackerFeature> &features,int width,int height);

      KLT_SequenceTracker* tracker;
      KLT_TrackedFeature* feat;
      int* trackID;
      int nFeatures;
      int lastID;
};

#endif // QVKLTTRACKER_H
