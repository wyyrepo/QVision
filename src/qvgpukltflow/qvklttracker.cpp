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

#include <QVKLTTracker>

QVKLTTracker::QVKLTTracker(int width, int height, bool trackWithGain,
                           int featuresWidth , int featuresHeight,
                           int nIterations, int nLevels, int levelSkip,int windowWidth,
                           float trackBorderMargin, float detectBorderMargin,
                           float convergenceThreshold, float SSD_Threshold,
                           int minDistance, float minCornerness) {
    KLT_SequenceTrackerConfig cfg;

    cfg.nIterations = nIterations;
    cfg.nLevels = nLevels;
    cfg.levelSkip = levelSkip;
    cfg.trackBorderMargin = trackBorderMargin;
    cfg.convergenceThreshold = convergenceThreshold;
    cfg.SSD_Threshold = SSD_Threshold;
    cfg.trackWithGain = trackWithGain;
    cfg.minDistance = minDistance;
    cfg.minCornerness = minCornerness;
    cfg.detectBorderMargin = detectBorderMargin;
    cfg.windowWidth = windowWidth;

    tracker = new KLT_SequenceTracker(cfg);
    tracker->allocate(width, height, nLevels, featuresWidth, featuresHeight);
    nFeatures = featuresHeight * featuresWidth;
    feat = new KLT_TrackedFeature[nFeatures];
    trackID = new int [nFeatures];
    for(int i=0; i<nFeatures; i++) {
        trackID[i] = 0;
    }
    lastID = 1;
}

QVKLTTracker::~QVKLTTracker() {
    tracker->deallocate();
    delete tracker;
    delete feat;
    delete trackID;
}

void QVKLTTracker::updateHashTable(QHash<int,QVKLTTrackerFeature> &features,int width,int height) {
    // features->clear(); // Really not needed.
    // std::cout << "features->size() before = " << features->size() << std::endl;
    // int sum0 = 0,sum1 = 0,sum2 = 0;
    for(int i=0; i<nFeatures; i++) {
        if(feat[i].status == 0) { // Succesfully tracked feature.
            // We update the corresponding feature in the hash:
            features.insert(trackID[i],
                             QVKLTTrackerFeature(feat[i].pos[0]*width, feat[i].pos[1]*height,
                                                  feat[i].gain));
            // sum0++;
        } else if (feat[i].status > 0) { // New detected feature.
            // First, remove old feature from hash if new feature substitutes an old one which was
            // not successfully tracked:
            if(trackID[i] != 0)
                features.remove(trackID[i]);
            // Now we add the new feature to the hash:
            trackID[i] = lastID;
            lastID++;
            features.insert(trackID[i],
                             QVKLTTrackerFeature(feat[i].pos[0]*width, feat[i].pos[1]*height,
                                                 feat[i].gain));
            // sum1++;
        } else { // feat[i].status < 0 -> lost feature.
            // Remove old feature from hash (if it really existed in the hash):
            if(trackID[i] != 0)
                features.remove(trackID[i]);
            // sum2++;
        }
    }
    //std::cout << "sum0 = " << sum0 << "   sum1 = " << sum1 << "   sum2 = " << sum2 << std::endl;
    //std::cout << "features->size() after = " << features->size() << std::endl;
    //std::cout << "lastID = " << lastID << std::endl;
}

void QVKLTTracker::detect(const QVImage<uChar,1> &image, QHash<int,QVKLTTrackerFeature> &features) {
    int nDetectedFeatures = 0;
    int width = image.getCols(), height = image.getRows();

    tracker->detect((V3D_GPU::uchar *)image.getReadData(), nDetectedFeatures, feat);
    // std::cout << "nDetectedFeatures = " << nDetectedFeatures << std::endl;
    updateHashTable(features,width,height);
    tracker->advanceFrame();
}

void QVKLTTracker::redetect(const QVImage<uChar,1> &image, QHash<int,QVKLTTrackerFeature> &features) {
    int nNewFeatures;
    int width = image.getCols(), height = image.getRows();

    tracker->redetect((V3D_GPU::uchar *)image.getReadData(), nNewFeatures, feat);
    // std::cout << "nNewFeatures = " << nNewFeatures << std::endl;
    updateHashTable(features,width,height);
    tracker->advanceFrame();
}

void QVKLTTracker::track(const QVImage<uChar,1> &image, QHash<int,QVKLTTrackerFeature> &features) {
    int nPresentFeatures;
    int width = image.getCols(), height = image.getRows();

    tracker->track((V3D_GPU::uchar *)image.getReadData(), nPresentFeatures, feat);
    // std::cout << "nPresentFeatures = " << nPresentFeatures << std::endl;
    updateHashTable(features,width,height);
    tracker->advanceFrame();
}
