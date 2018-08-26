/*
 *	Copyright (C) 2009, 2010, 2011, 2012. PARP Research Group.
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
@file
@ingroup OpenCVExamplePrograms
@brief Performs Kalman filtering over a corrupted sinoidal function.

This example uses the Kalman filter implemented in the OpenCV to estimate a robust value for an input function. The provided value is corrupted with artificial measurement and process noises.

@section Usage
Once compiled, the program should be used with this command line:
\code
	./kalmanExample
\endcode

Two graphical plots will show up: The first plot displays the real sinoidal function value, the corrupted value, and the Kalman estimation. The second plot compares the error of the Kalman filtered value regarding the real sinoidal value, against the error of the direct corrupted measurement.

@author PARP Research Group. University of Murcia, Spain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <QDebug>
#include <QVApplication>
#include <QVDefaultGUI>

#include <QVNumericPlot>
#include <QVVector>
#include <QVMatrix>

#include <qvmath.h>

#ifndef DOXYGEN_IGNORE_THIS

#define MEASUREMENT_NOISE_COV	0.5
#define	PROCESS_NOISE_COV	0.1

class QVKalmanFilter
	{
	private:
		CvKalman* kalman;

	public:
		QVKalmanFilter(	const int dynamParams, const int measureParams, const QVMatrix &transitionMatrix,
				const double processNoiseCovariance, const double measurementNoiseCovariance):
			kalman(cvCreateKalman(dynamParams, measureParams, 0))
			{
			CvMat *transitionCvMatrix = transitionMatrix.toCvMat(CV_32F);
			cvCopy(transitionCvMatrix, kalman->transition_matrix);

			cvReleaseMat(&transitionCvMatrix);
			
			cvSetIdentity(kalman->process_noise_cov,	cvRealScalar(processNoiseCovariance));
			cvSetIdentity(kalman->measurement_noise_cov,	cvRealScalar(measurementNoiseCovariance));
			cvSetIdentity(kalman->measurement_matrix,	cvRealScalar(1));
			cvSetIdentity(kalman->error_cov_post,		cvRealScalar(1));

			cvZero( kalman->state_post );
			}

		const QVVector predict() const
			{
			return QVMatrix(cvKalmanPredict( kalman, 0 ));
			}

		void correct(const QVVector &z)
			{
			CvMat* z_k = z.toColumnMatrix().toCvMat(CV_32F);
			cvKalmanCorrect( kalman, z_k );
			cvReleaseMat(&z_k);
			}

	static const QVMatrix linearMotionTransitionMatrix(const int size = 1, const double step = 0.1)
		{
		QVMatrix transitionMatrix = QVMatrix::identity(2*size);
		for (int i = 0; i < size; i++)
			transitionMatrix(i,size+i) = step;
	
		return transitionMatrix;
		}
	};


class KalmanFilterBlock: public QVProcessingBlock
	{
	private:
		QVKalmanFilter kalmanFilter;
	
	public:
		KalmanFilterBlock(const QString name): QVProcessingBlock(name),
			kalmanFilter(2, 1, QVKalmanFilter::linearMotionTransitionMatrix(), PROCESS_NOISE_COV, MEASUREMENT_NOISE_COV)
			{
			addProperty<double>("Kalman[sin(x) + noise]", outputFlag);
			addProperty<double>("sin(x)", outputFlag);
			addProperty<double>("sin(x) + noise", outputFlag);

			addProperty<double>("Kalman error", outputFlag);
			addProperty<double>("Measurement error", outputFlag);
			}

		void iterate()
			{
			// Read sensor, actualize real state.
			const double	realState = 1 - cos((double) getIteration() / 512.0),
					measurementNoise = ((double)(rand()%2000)/1000.0 - 1.0) * sqrt(MEASUREMENT_NOISE_COV),
					processNoise = ((double)(rand()%2000)/1000.0 - 1.0) * sqrt(PROCESS_NOISE_COV);

			// Predict and correct Kalman filter state
			const QVVector y = kalmanFilter.predict();
			kalmanFilter.correct(QVVector(1, realState + processNoise + measurementNoise));

			// Publish results
			setPropertyValue<double>("Kalman[sin(x) + noise]", y[0]);
			setPropertyValue<double>("sin(x)", realState + processNoise);
			setPropertyValue<double>("sin(x) + noise", realState + processNoise + measurementNoise);
			setPropertyValue<double>("Kalman error", ABS(realState - y[0]));
			setPropertyValue<double>("Measurement error", ABS(processNoise + measurementNoise));
			}
	};

#include <QVYUV4MPEG2WriterBlock>
#include <QVNumericPlot>

int main(int argc, char *argv[])
	{
	QVApplication app(argc, argv,
		"Example program for QVision library. Applies Kalman filtering to an input function."
		);

	KalmanFilterBlock kalmanFilterBlock("Corners Block");

        QVDefaultGUI gui;

	QVNumericPlot measurePlot("Obtained values");
	kalmanFilterBlock.linkProperty("Kalman[sin(x) + noise]", measurePlot);
	kalmanFilterBlock.linkProperty("sin(x)", measurePlot);
	kalmanFilterBlock.linkProperty("sin(x) + noise", measurePlot);

	QVNumericPlot errorPlot("Estimation errors");
	kalmanFilterBlock.linkProperty("Kalman error", errorPlot);
	kalmanFilterBlock.linkProperty("Measurement error", errorPlot);

	return app.exec();

	}

#endif

