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

#include "qvopticalflow.h"

void qvInitFlowGPU (TVL1_FlowEstimator * &flowEstimator, int w, int h, int nLevels, int nIterations, int nOuterIterations,
           double lambda, double tau, double theta) {
    int startLevel = 0;
    TVL1_FlowEstimator::Config flowCfg(tau, theta);

    flowEstimator = new TVL1_FlowEstimator(nLevels);
    flowEstimator->configurePrecision(false, false, false);
    flowEstimator->allocate(w, h);
    flowEstimator->setLambda(lambda);
    flowEstimator->configure(flowCfg);
    flowEstimator->setInnerIterations(nIterations);
    flowEstimator->setOuterIterations(nOuterIterations);
    flowEstimator->setStartLevel(startLevel);
}

void qvOpticalFlowGPU(TVL1_FlowEstimator * flowEstimator, QVPyramid* p1, QVPyramid* p2,
                 QVImage<sFloat, 1> &x, QVImage<sFloat, 1> &y) {

    int startLevel = 0;
    GLint textureWidth, textureHeight;

    flowEstimator->run(p1->getID(), p2->getID());
    glFinish();

    warpImageWithFlowField(flowEstimator->getFlowFieldTextureID(),
                           p1->getID(), p2->getID(), startLevel,
                           *flowEstimator->getWarpedBuffer(startLevel));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,flowEstimator->getFlowFieldTextureID());
    glEnable(GL_TEXTURE_2D);


    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);

    glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_FLOAT, x.getWriteData());
    glGetTexImage(GL_TEXTURE_2D, 0, GL_GREEN, GL_FLOAT, y.getWriteData());

    glDisable(GL_TEXTURE_2D);
    checkGLErrorsHere0();
}
