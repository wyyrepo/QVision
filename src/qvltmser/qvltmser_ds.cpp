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

/// @file qvltmser_ds.cpp
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#include <QVImageCanvas>
#include <qvltmser/qvltmser_ds.h>

QVLtmserBoundary::QVLtmserBoundary(uInt pWidth, uInt pHeight, uInt pGreyLevels)
{
    width = pWidth;
    height = pHeight;
    greyLevels = pGreyLevels;
    if (greyLevels == 0)
        greyLevels = 256;
    if (greyLevels > 0 && width >0 && height > 0)
        numPixels = width * height;
    else
        numPixels = 0;
    maxStackPr = 9999;
    heap = QVector<uInt>(numPixels,0);
    stackLength = QVector<int>(greyLevels,0);
    stackStart = QVector<int>(greyLevels,-1);
}

void QVLtmserBoundary::initHeap(QVector<int> &histogram)
{
    int index = 0;
    /*for (uInt i = 0; i<numPixels; i++)
        heap[i] = 0; */
    for (uInt i = 0; i < greyLevels; i++) {
        if (histogram[i] > 0) {
            stackStart[i] = index;
            index = index + histogram[i];
        } else
            stackStart[i] = -1;
        stackLength[i] = 0;
    }
    maxStackPr = 9999;
} 

void QVLtmserBoundary::pushPixel(uInt greyLevel, uInt pixel)
{
    heap[stackStart[greyLevel] + stackLength[greyLevel]] = pixel;
    stackLength[greyLevel]++;
    if (greyLevel < (uInt)maxStackPr)
        maxStackPr = greyLevel;
}

bool QVLtmserBoundary::popPixel(uInt greyLevel, uInt &pixel)
{
    if (stackLength[greyLevel] > 0) {
        stackLength[greyLevel]--;
        pixel = heap[stackStart[greyLevel] + stackLength[greyLevel]];
        if (stackLength[greyLevel] == 0)
            maxStackPr = getMaxStackPr();
        return true;
    } else
        return false;
}

int QVLtmserBoundary::getMaxStackPr()
{
    int resp = -1;
    for (uInt i=0; i < greyLevels; i++) {
        if (stackLength[i] > 0) {
            resp = i;
            break;
        }
    }
    return resp;
}

QHash<QPoint,QVMSER> QVLtmserComponent::theSeedList;
uInt QVLtmserComponent::minArea;
uInt QVLtmserComponent::maxArea;
uChar QVLtmserComponent::delta;
float QVLtmserComponent::delta_threshold;

QVLtmserComponent::QVLtmserComponent(uInt pGreyLevel)
{
    greyLevel = pGreyLevel;
    greyLevelMin = greyLevel;
    numPixels = 0;
    history = new QVector<uInt>(256,0);
    countRefsHistory = 1;
}

QVLtmserComponent::~QVLtmserComponent()
{
    countRefsHistory--;
    if(countRefsHistory == 0) {
        testMSER();
        delete history;
    }
}

void QVLtmserComponent::setSeed(uInt r, uInt c)
{
    seedX = c;
    seedY = r;
}

void QVLtmserComponent::addPixel(uChar pGreyLevel)
{
    numPixels++;
    greyLevel = pGreyLevel;
    (*history)[greyLevel]++;
}

void QVLtmserComponent::testMSER()
{
    uInt hist_acum[256],acum=0,val/*,i2*/;
    float /*dif,*/merit[256];

    // Compute accumulated histogram of component, from history (which was incremental):
    for(uChar i=greyLevelMin;i<=greyLevel;i++) {
        if ((val=(*history)[i]) != 0)
            acum += val;
        hist_acum[i] = acum;
    }


    float min = 1E10;
    int indmin = -1;
    for(uChar i=greyLevelMin+delta;i<=greyLevel-delta;i++) {
        merit[i] = ((float)hist_acum[i+delta] - (float)hist_acum[i-delta]) / (float)hist_acum[i];
        if(merit[i]<min) {
            min = merit[i];
            indmin = i;
        }
    }

    if(indmin == -1)
        return;

    if (min <= delta_threshold) {
            uInt area_mser = hist_acum[indmin];
            if(area_mser >= minArea and area_mser <= maxArea) {
                if(theSeedList.contains(QPoint(seedX,seedY)))
                    if(theSeedList[QPoint(seedX,seedY)].merit < min)
                        return;
                theSeedList[QPoint(seedX,seedY)] = QVMSER(seedX,seedY,indmin,min,area_mser);
            }
     }
}

void QVLtmserComponent::upGreyLevel(uInt newGreyLevel)
{
    greyLevel = newGreyLevel;
};

void QVLtmserComponent::addComponent(QVLtmserComponent &otherComponent, uInt newlevel)
{
    for(int i=otherComponent.greyLevelMin;i<=otherComponent.greyLevel;i++) {
        (*history)[i] += (*otherComponent.history)[i];
    }
   // We set graylevel of the component to delete (other) to the same as the other one (for it to be taken
   // into account when testing for MSER before deletion);
   otherComponent.greyLevel = greyLevel-1;
   // (*history)[greyLevel] += otherComponent.numPixels;
   // Finally, we update number of pixels, grayLevelMin and seed coordinates:
   numPixels += otherComponent.numPixels;
   if (otherComponent.greyLevelMin < greyLevelMin) {
       greyLevelMin = otherComponent.greyLevelMin;
       seedX = otherComponent.seedX;
       seedY = otherComponent.seedY;
   }

   greyLevel = newlevel;





/*   uInt cur_size = (*history)[greyLevel];
   // The current component (this) is the second from the stack. The otherComponent is in the top of the
   // stack. We consider current component total number of pixel minus the ones at the current gray level.
   // If the other component (on top of stack, and which does not contain that current gray level) has more
   // pixels, then before deleting the "absorbed" component (current one), we test for MSERs, and "inherit" the
   // other component's history; otherwise, the absorbed component will be the other, and it will be tested for
   // MSERs in its posterior deletion (theQVLtmserComponentStack.popComponent()). In both cases, we conveniently
   // update history:

    if (otherComponent.numPixels > numPixels-cur_size) {
        // Test for MSER before deleting absorbed component (this), without having into account current greyLevel:
        greyLevel--;
        testMSER();
        greyLevel++;
        // Finally we delete history, and continue with the other one:
        delete history;
        history = otherComponent.history;
        otherComponent.countRefsHistory++;
        (*history)[greyLevel] += numPixels;
    } else {
        // We set graylevel of the component to delete (other) to the same as the other one (for it to be taken
        // into account when testing for MSER before deletion);
        otherComponent.greyLevel = greyLevel-1;
        (*history)[greyLevel] += otherComponent.numPixels;
    }
    // Finally, we update number of pixels, grayLevelMin and seed coordinates:
    numPixels += otherComponent.numPixels;
    if (otherComponent.greyLevelMin < greyLevelMin) {
        greyLevelMin = otherComponent.greyLevelMin;
        seedX = otherComponent.seedX;
        seedY = otherComponent.seedY;
    }*/
};

QVLtmserComponentStack::QVLtmserComponentStack(uInt pGreyLevels)
{
    greyLevels = pGreyLevels;
    posTop = -1;
    components = new QVector< QVLtmserComponent *>(greyLevels,NULL);
}

QVLtmserComponentStack::~QVLtmserComponentStack()
{
    (*components).clear();
    delete components;
}

void QVLtmserComponentStack::initComponents()
{
    for (uInt i = 0; i < greyLevels; i++)
        if ((*components)[i] != NULL) {
            delete (*components)[i];
            (*components)[i] = NULL;
        }
    posTop = -1;
}

void QVLtmserComponentStack::pushComponent(uInt aGreyLevel, int r, int c)
{
    QVLtmserComponent *aComponent;
    if (posTop != -1)
        if(aGreyLevel >= (*components)[posTop]-> greyLevel) {
            qFatal("Error in QVLtmserComponentStack::pushComponent");
        }
    aComponent = new QVLtmserComponent(aGreyLevel);
    aComponent->setSeed(r,c);
    posTop++;
    (*components)[posTop] = aComponent;
}

void QVLtmserComponentStack::popComponent()
{
    if (posTop == -1)
        qFatal("Error in QVLtmserComponentStack::popComponent");
    QVLtmserComponent *component = (*components)[posTop];
    (*components)[posTop] = NULL;
    posTop--;
    delete component;
}

int QVLtmserComponentStack::getPosTop()
{
  return posTop;
};
