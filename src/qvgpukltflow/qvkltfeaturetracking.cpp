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

#include <QVKLTFeatureTracking>

void QVTrackingManager::updateTrackings(QHash<int, QVKLTTrackerFeature> *tracks) {
    // First we check for lost trackings, and remove them (only if the tracking was initially
    // configured to do so):
    if (removeLostTrackings) {
        QList<int> lost = QList<int> ();
        QHash<int, QVKLTFeatureTracking>::iterator j;
        // We run through all trackings, and remove those that belong to a lost feature:
        for (j = trackings.begin(); j != trackings.end(); j++) {
            if (!tracks->contains(j.key()))
                lost << j.key();
        }
        for (int i=0; i < lost.size(); i++){
            trackings.remove(lost[i]);
        }
    }

    // Then we add features from the current frame to the stored trackings:
    QHash<int, QVKLTTrackerFeature>::iterator i;
    for (i = tracks->begin(); i != tracks->end(); ++i) {
        if (trackings.contains(i.key())) {
            // Existing feature -> add to corresponding tracking:
            trackings[i.key()].addFeature(i.value());
        } else {
            // New feature -> create new tracking:
            trackings.insert(i.key(), QVKLTFeatureTracking(i.value(), this->actualFrame));
        }
    }

    this->actualFrame++;
}

QList<int> QVTrackingManager::getTrackingsAtLastFrame() {
    if (removeLostTrackings) {
        return trackings.keys();
    } else{
        return getTrackingsAtFrame(this->actualFrame);
    }
}

QList<int> QVTrackingManager::getTrackingsAtFrame(int frame) {
    QList<int> ids = QList<int> ();
    QHash<int, QVKLTFeatureTracking>::iterator j;
    for(j = trackings.begin(); j != trackings.end(); j++) {
        QVKLTFeatureTracking ft = j.value();
        // if(ft.getLastFrame() <= frame) // OJO (?)
        if( (ft.getFirstFrame() <= frame) and (frame <= ft.getLastFrame()) )
            ids << j.key();
    }
    return ids;
}
