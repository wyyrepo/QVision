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

/// @file qvltmser_ds.h
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#ifndef QVLTMSER_DS_H
#define QVLTMSER_DS_H

#include <QVImage>
#include <QVector>
#include <QVMSER>

// Class for boundary pixels (it is a priority queue of stacks, with high priority for darker gray levels:
class QVLtmserBoundary {
  public:
    // Index of maximum priority entry on the queue (-1 if empty):
    int maxStackPr;

    // Constructor:
    // * pGreyLevels: number of gray levels of image.
    // * pWidth, pHeight: image dimensions.
    QVLtmserBoundary(uInt pWidth, uInt pHeight, uInt pGreyLevels);

    // Heap initialization:
    void initHeap(QVector< int > &histogram);

    // Push a new pixel in boundary, for a given gray level:
    void pushPixel(uInt greyLevel, uInt pixel);

    // Pop a pixel from boundary (returns true if it has been possible, false otherwise):
    bool popPixel(uInt greyLevel, uInt &pixel);

  protected:
    // Image size:
    uInt width, height;

    // Number of gray levels:
    uInt greyLevels;

    // Number of pixels to process:
    uInt numPixels;

    // Length of stacks:
    QVector<int> stackLength;

    // Start of each stack (-1 if it will never have any pixel):
    QVector<int> stackStart;

    // The heap is implemented in a compressed manner. Array stackStart contains the start index of each stack
    // (for a given priority), or -1 if that stack is empty, while array stackLength contains the corresponding
    // top of the stack. The first array will be initialized once at the beginning, using the image histogram.
    // Note: Coordinates of pixels have been previously transformed to ints (int_value=(y*num_cols)+x).
    QVector<uInt> heap;

    // Get index of stack with greater priority (-1 if heap is empty)
    int getMaxStackPr();
};

// Class for each individual component of the component stack:
class QVLtmserComponent {
  public:
    // Constructor:
    QVLtmserComponent(uInt pGreyLevel);

    // Destructor.
    ~QVLtmserComponent();

    // Current and minimum gray levels of component:
    uChar greyLevel, greyLevelMin;

    // Seed pixel: (at the deepest point of component):
    uInt seedX, seedY;

    // Number of pixels that the component has in the current grayLevel:
    uInt numPixels;

    // History of areas of the component:
    QVector<uInt> *history;

    // Static class members: pointer to result seed list and algorithm parameters:
    static QHash<QPoint,QVMSER> theSeedList;
    static uInt minArea;
    static uInt maxArea;
    static uChar delta;
    static float delta_threshold;

    // Set seed of component:
    void setSeed(uInt r, uInt c);

    // Add a new pixel to component:
    void addPixel(uChar pGreyLevel);

    // Test if component is a MSER:
    void testMSER();
                   
    // Raise gray level to "newGreyLevel", updating variables "greyLevel" and "numPixels", and history of component:
    void upGreyLevel(uInt newGreyLevel);

    // Add another component to this component:
    void addComponent(QVLtmserComponent &otherComponent, uInt newlevel);

    private:
    // Reference counter to history (to delete it in destructor when counter reaches zero):
    uInt countRefsHistory;
};

// Class for component stack:
class QVLtmserComponentStack {
  public:
    // Constructor:
    // * pGreyLevels: Number of possible gray levels:
    QVLtmserComponentStack(uInt pGreyLevels);

    // Destructor:
    ~QVLtmserComponentStack();

    // Components of stack are stored as pointers in a vector:
    QVector<QVLtmserComponent*> *components;

    // Initialize component stack:
    void initComponents();

    // Push a new component in the stack (its gray level must be lesser than the gray level of component that
    // was until now in the top):
    void pushComponent(uInt aGreyLevel, int r, int c);

    // Pop and destroy the component in the top of the stack:
    void popComponent();

    // Get index in vector corresponding to top (returns -1 if empty):
    int getPosTop();

  protected:

    // Number of gray levels:
    uInt greyLevels;

    // Position of top in "components". If empty, posTop=-1:
    int posTop;
};

#endif
