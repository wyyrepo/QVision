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

#ifndef QVKLTFEATURETRACKING_H
#define QVKLTFEATURETRACKING_H

#include <QVKLTTracker>
#include <iostream>

using namespace std;

/*!
@class QVKLTFeatureTracking
@brief Class to store the successive positions of an individual feature tracked in a video sequence.

@ingroup qvgpukltflow
*/
class QVKLTFeatureTracking {
  private:
    QList<QVKLTTrackerFeature> track;
    int firstFrame, lastFrame;

  public:
    /// @brief Constructor from an freshly detected feature.
    ///
    /// @param feature Feature just detected.
    /// @param firstFrame Frame number in which the feature was detected.
    QVKLTFeatureTracking(QVKLTTrackerFeature feature, int firstFrame) {
        track = QList<QVKLTTrackerFeature>();
        track.append(feature);
        this->firstFrame = firstFrame;
        this->lastFrame = firstFrame;
    };

    /// @brief Default constructor
    QVKLTFeatureTracking() {
        track = QList<QVKLTTrackerFeature>();
        this->firstFrame = -1;
        this->lastFrame = -1;
    }

    /// @brief Copy constructor
    QVKLTFeatureTracking(const QVKLTFeatureTracking &ft)
        :track(ft.track), firstFrame(ft.firstFrame), lastFrame(ft.lastFrame) { }

    ~QVKLTFeatureTracking() { }

    /// @brief Update the tracking hash with the updated feature hash.
    ///
    /// This method updates the tracking hash according to the feature status
    /// in the input feature hash.
    /// @param tracks Input feature hash.
    void addFeature(const QVKLTTrackerFeature &feature) {
        track.append(feature);
        lastFrame++;
    };

    /*void endTracking(int lastFrame) {
        if (this->lastFrame == -1) {
            cerr << "Error: El tracking ya se terminó en el frame " << this->lastFrame << endl;
        }
        this->lastFrame = lastFrame;
    }*/

    /// @brief Gets the list of feature positions in the tracking.
    ///
    /// @return List of feature positions in the tracking.
    QList<QVKLTTrackerFeature> getFeatureList() const {
        return track;
    }

    /// @brief Gets the index of the last frame in which the feature was detected.
    ///
    /// @return Index of the last frame in which the feature was detected.
    int getLastFrame() const {
        return lastFrame;
    }

    /// @brief Gets the index of the first frame in which the feature was detected.
    ///
    /// @return Index of the first frame in which the feature was detected.
    int getFirstFrame() const {
        return firstFrame;
    }

    /// @brief Gets the size of the tracking (number of frames in which the feature was tracked).
    ///
    /// @return Size of the tracking.
    int size() const {
        return track.size();
    };
};

/*!
@class QVTrackingManager
@brief Class to manage trackings of features in video sequences.

@ingroup qvgpukltflow
*/
class QVTrackingManager {
  public:
    /// @brief Default constructor.
    ///
    QVTrackingManager(bool removeLostTrackings=true) {
        this->trackings = QHash<int, QVKLTFeatureTracking> ();
        this->removeLostTrackings = removeLostTrackings;
        this->actualFrame = 0;
    }

    /// @brief Default destructor.
    ~QVTrackingManager() { };

    /// @brief Update the tracking hash with the updated feature hash.
    ///
    /// This method updates the tracking hash according to the feature status
    /// in the input feature hash.
    /// @param tracks Input feature hash.
    void updateTrackings(QHash<int, QVKLTTrackerFeature>* tracks);

    /// @brief Get all features tracked in a given frame.
    ///
    /// @param frame number of the frame
    /// @return A list with the identifiers of all features tracked in that frame.
    QList<int> getTrackingsAtFrame(int frame);

    /// @brief Get all features tracked in the last frame.
    ///
    /// @return A list with the identifiers of all features tracked in the last frame.
    QList<int> getTrackingsAtLastFrame ();

    /// @brief Get all trackings.
    ///
    /// @return A hash containing all the trackings.
    QHash<int, QVKLTFeatureTracking> getTrackings () const {
        return trackings;
    }

    /// @brief Get the tracking corresponding to a given individual feature.
    ///
    /// @param id Feature identifier
    /// @return The tracking corresponding to that feature
    QVKLTFeatureTracking& getFeatureTracking (int id) {
        return trackings[id];
    }

private:
    QHash<int, QVKLTFeatureTracking> trackings;
    bool removeLostTrackings;
    int actualFrame;
};

#endif // QVKLTFEATURETRACKING_H
