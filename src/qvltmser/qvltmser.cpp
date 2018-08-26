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

/// @file qvltmser.cpp
/// @brief Functions to get image regions using the linear time MSER algorithm by Nister and Stewanius (ECCV 2008)
/// @author PARP Research Group. University of Murcia, Spain.

#include <qvltmser/qvltmser.h>
#include <qvip.h>
#include <qvipp.h>
#include <qvltmser/qvltmser_ds.h>

// "ProcessStack" function of original algorithm. It uses the component stack and the gray level of the last
// unstacked pixel in the boundary.
void processStack(QVLtmserComponentStack &theQVLtmserComponentStack, uInt levelGreyBoundary)
{
    int top;
    int greyLevel2;
    QVLtmserComponent *theComponentTop, *theComponent2;
    while(true) {
        top = theQVLtmserComponentStack.getPosTop();
        if(top != 0)
            theComponent2 = (*theQVLtmserComponentStack.components)[top-1];
        else {
            // Just one element in stack -> uprise graylevel of stack to levelGreyBoundary and return:
            theComponentTop = (*theQVLtmserComponentStack.components)[top];
            theComponentTop->upGreyLevel(levelGreyBoundary);
            break;
        }
        greyLevel2 = theComponent2->greyLevel;
        theComponentTop = (*theQVLtmserComponentStack.components)[top];
        if (levelGreyBoundary < (uInt)greyLevel2) {
            theComponentTop->upGreyLevel(levelGreyBoundary);
            break;
        } else {
            theComponent2->addComponent(*theComponentTop,levelGreyBoundary);
            theQVLtmserComponentStack.popComponent();
            if (levelGreyBoundary == (uInt)greyLevel2)
                break;
        }
    }
}

// Linear-Time MSER fuction to get the list of seeds:
QList<QVMSER> getLTMSER(QVImage< uChar > &input_image,
                        const int minArea, const int maxArea, const int delta,
                        const float delta_threshold, const unsigned int downscaling)
{
    static QVLtmserBoundary *theQVLtmserBoundary = NULL; // Structure for goundary pixels
    static QVLtmserComponentStack *theQVLtmserComponentStack = NULL;
    static uInt former_width = 0, former_height = 0; // Size of former image (if they change, resize structures).
    static const uInt greyLevels=256; // Number of gray levels.
    uChar valueOfPixel;
    bool visited;
    uInt currentGreyLevel, greyLevelNeighbor, indexNeighbor;
    int levelGreyBoundary, col = 0, row = 0, cPixel_x, cPixel_y;
    uInt currentPixel, neighbor, pixelBoundary;
    QVLtmserComponent *theComponentTop;
    QVPolyline aContour;
    QVImage<uChar> image;
    int minAreaScaled=minArea, maxAreaScaled=maxArea;

    if(downscaling != 1) {
        QVImage<uChar> resized(input_image.getCols()/downscaling,input_image.getRows()/downscaling);
        Resize(input_image,resized);
        image = resized;
        minAreaScaled = minArea/(downscaling*downscaling);
        maxAreaScaled = maxArea/(downscaling*downscaling);
    } else {
        image = input_image;
    }

    const uInt cols = image.getCols(), rows = image.getRows();

    if(cols != former_width or rows != former_height) {
        // New image size; resize structures:
        if (theQVLtmserBoundary != NULL)
            delete theQVLtmserBoundary;
        theQVLtmserBoundary = new QVLtmserBoundary(cols, rows, greyLevels);
        if (theQVLtmserComponentStack != NULL)
            delete theQVLtmserComponentStack;
        theQVLtmserComponentStack = new QVLtmserComponentStack(greyLevels);
        former_width = cols;
        former_height = rows;
    }

    theQVLtmserComponentStack->initComponents();

    // Initialize static variables of QVLtmserComponent class (to avoid unneeded intensive passing of parameters)
    QVLtmserComponent::theSeedList = QHash<QPoint,QVMSER>();
    QVLtmserComponent::minArea = minAreaScaled;
    QVLtmserComponent::maxArea = maxAreaScaled;
    QVLtmserComponent::delta = delta;
    QVLtmserComponent::delta_threshold = delta_threshold;

    uChar *pimage = image.getWriteData();

    // Initialize visited pixels mask. For efficiency, it will be embedded in the same image (LSB of each pixel):
    AndC(image,0xFE,image);

    int imageStep = image.getStep();

    // Initialize heap from histogram:
    QVector< int > histogram = HistogramRange(image);
    theQVLtmserBoundary->initHeap(histogram);

    // First visited pixel:
    currentGreyLevel = pimage[0] & 0xFE;
    currentPixel = 0;
    valueOfPixel = pimage[0];
    pimage[0] = valueOfPixel | 0x01;

    theQVLtmserComponentStack->pushComponent(currentGreyLevel,0,0);
    while(true) { // Infinite loop (until break):
        cPixel_y = (int)(currentPixel / cols);
        cPixel_x = currentPixel - (cPixel_y * cols);

        char nn = -1;
        while (nn != 3) {
            // Test next pixel (neighbour of current):
            if (nn == -1)
                nn = 0;
            else
                nn++;
            switch(nn) {
                case 0: row = cPixel_y-1; col = cPixel_x; break;
                case 1: row = cPixel_y; col = cPixel_x+1; break;
                case 2: row = cPixel_y+1; col = cPixel_x; break;
                case 3: row = cPixel_y; col = cPixel_x-1; break;
            }
            if (row < 0 || col < 0 || static_cast<uInt>(row) >= rows || static_cast<uInt>(col) >= cols)
                continue;
            indexNeighbor = (row*imageStep) + col;
            valueOfPixel = pimage[indexNeighbor];
            visited = valueOfPixel & 0x01;
            if (visited)
                continue;
            else {
                greyLevelNeighbor = pimage[indexNeighbor] & 0xFE;
                valueOfPixel = pimage[indexNeighbor];
                pimage[indexNeighbor] = valueOfPixel | 0x01;
                if (greyLevelNeighbor >= currentGreyLevel) {
                    // If graylevel(neighbour) >= graylevel(current) -> move to boundary heap:
                    neighbor = (row * cols) + col;
                    theQVLtmserBoundary->pushPixel(greyLevelNeighbor, neighbor);
                } else {
                    // If graylevel(neighbour) < graylevel(current) -> move current pixel to heap and
                    // make neighbour the current pixel. This will add a new element to the components stack,
                    // and to start checking the neighbours of the new current pixel (nn=0 in next iteration):
                   theQVLtmserBoundary->pushPixel(currentGreyLevel, currentPixel);
                   currentPixel = (row * cols) + col;
                   cPixel_y = row;
                   cPixel_x = col;
                   currentGreyLevel = greyLevelNeighbor;
                   theQVLtmserComponentStack->pushComponent(currentGreyLevel,row,col);
                   nn = -1;
                }
            }
        }
        // We have run through every neighbour of current pixel without moving, so we must "fill" the pixel
        // (add it to the component on the top of the stack)...
        theComponentTop = (*theQVLtmserComponentStack->components)[theQVLtmserComponentStack->getPosTop()];
        theComponentTop->addPixel(currentGreyLevel);
        // ... then get the next pixel from the boundary heap...
        levelGreyBoundary = theQVLtmserBoundary->maxStackPr;
        if (levelGreyBoundary == -1 or not theQVLtmserBoundary->popPixel(levelGreyBoundary, pixelBoundary)) {
            int acum=0;
            for(uInt i=theComponentTop->greyLevelMin;i<=theComponentTop->greyLevel;i++) {
                acum += (*theComponentTop->history)[i];
            }

            theQVLtmserComponentStack->popComponent(); // To delete last component of stack.
            break; // Get out of main "while" loop.
        }
        // ... and, if it applies (only if the new pixel popped out of the heap is greater than current), we
        // call processStack (which keeps on filling the current "hole" with water):
        if (levelGreyBoundary > (int)currentGreyLevel)
            processStack(*theQVLtmserComponentStack, levelGreyBoundary);
        currentPixel = pixelBoundary;
        currentGreyLevel = levelGreyBoundary;
    }

    QList<QVMSER> mser_list;
    if(downscaling != 1) {
        foreach(QVMSER mser, QVLtmserComponent::theSeedList.values()) {
            int tx=downscaling*mser.seed.x(), ty=downscaling*mser.seed.y();
            int minvalue = input_image(tx,ty);
            for(unsigned int i=0;i<downscaling;i++) {
                for(unsigned int j=0;j<downscaling;j++) {
                    if(tx+i>=input_image.getCols() or ty+j>=input_image.getRows())
                        continue;
                    if(input_image(tx+i,ty+j)<minvalue) {
                        minvalue = input_image(tx+i,ty+j);
                        tx = tx+i;
                        ty = ty+j;
                    }
                }
            }
            mser_list.append(QVMSER(tx,ty,mser.threshold,mser.merit,
                                           mser.area*downscaling*downscaling));
        }
    } else {
        mser_list = QVLtmserComponent::theSeedList.values();
    }

    // Return seeds:
    return mser_list;
}

// Function to get MSER contours from seeds, using IPP floodfill on input image:
QList<QVPolyline> getLTMSERContours(QVImage< uChar > &input_image,QList<QVMSER> mser_list)
{
    QVImage< uChar > not_image;

    Not(input_image,not_image);
    QList<QVPolyline> output_contours;
    foreach (QVMSER mser, mser_list) {
        QVPolyline polyline = getConnectedSetBorderContourThreshold(not_image,mser.seed, 255-mser.threshold);
        output_contours.append(polyline);
    }
    return output_contours;
}

// Linear-Time MSER fuction to get the final contours, first obtaining seeds, then filling to get contours:
QList<QVPolyline> getLTMSERContours(QVImage< uChar > &input_image,
                                    const int minArea, const int maxArea, const int delta,
                                   const float delta_threshold,
                                   unsigned int downscaling)
{
    QList<QVMSER> mser_list;

    mser_list = getLTMSER(input_image,minArea,maxArea,delta,delta_threshold,downscaling);

    return getLTMSERContours(input_image,mser_list);
}

/* Possible pending performance issues:
   1. Machine instruction to get most prioritary pixel of heap?
   2. inline functions?
*/
