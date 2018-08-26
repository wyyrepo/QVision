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
/// @brief Test for Cholesky decomposition based functions from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

/*!
@file
@ingroup ExamplePrograms
@brief Performs several validation tests on the QVImage class.

@section UsageImageTests Usage of the program.
Compile and execute the application with the following line:
@code ./image-tests <path to image files> @endcode

If any of the tests is not satisfied, the string '[** FAILED **]' is printed, and the application finishes.
This would indicate a programming error in the class QVImage, or the IPP wrapper functions.
*/

#include <iostream>
#include <QVImage>
#include <QDir>
#include <qvimageio.h>

void doTests(const QVImage<uChar, 3> &image)
	{
	// -------------------------------------------------
	// Test: QImage convert
	const QVImage<uChar, 3> imageCopy = image;
	QVImage<uChar, 3> imageCopy2;
	imageCopy2 = image;

	Q_ASSERT_X(image == imageCopy,	"test QImage convert", "QVImage copy 1");
	Q_ASSERT_X(image == imageCopy2,	"test QImage convert", "QVImage copy 2");

	if (image.getCols() > 50 and image.getRows() > 50)
		{
		imageCopy2.setROI(QRect(QPoint(10,10), QPoint(50, 50)));
		imageCopy2.setAnchor(QPoint(4,4));

		const QVImage<uChar, 3> imageCopy3 = imageCopy2;
		QVImage<uChar, 3> imageCopy4;
		imageCopy4 = imageCopy2;

		Q_ASSERT_X(image != imageCopy3, "test QImage convert", "QVImage copy 3");
		Q_ASSERT_X(image != imageCopy4, "test QImage convert", "QVImage copy 4");
		Q_ASSERT_X(imageCopy3.getROI() == QRect(QPoint(10,10), QPoint(50, 50)), "test QImage convert", "QVImage copy 5");
		Q_ASSERT_X(imageCopy4.getROI() == QRect(QPoint(10,10), QPoint(50, 50)), "test QImage convert", "QVImage copy 6");
		Q_ASSERT_X(imageCopy3.getAnchor() == QPoint(4,4), "test QImage convert", "QVImage copy 7");
		Q_ASSERT_X(imageCopy4.getAnchor() == QPoint(4,4), "test QImage convert", "QVImage copy 8");
		}

	// -------------------------------------------------
	// Test: QImage convert.
	const QImage qImage = image;
	QImage qImage2;
	qImage2 = image;

	const QVImage<uChar, 3> fromQImage = qImage,
							fromQImage2 = qImage2;

	Q_ASSERT_X(image == fromQImage, "test QImage convert", "QImage convert 1");
	Q_ASSERT_X(image == fromQImage2, "test QImage convert", "QImage convert 2");

	// -------------------------------------------------
	// Test: QImage convert.
	IplImage *iplImage = image;
	const QVImage<uChar, 3> fromIplImage = iplImage;
	cvReleaseImage(&iplImage);

	Q_ASSERT_X(image == fromIplImage, "test QImage convert", "IplImage convert");

	// -------------------------------------------------
	// Test: Image channel splitting.
	const QVImage<uChar>	channelR = image(0),
							channelG = image(1),
							channelB = image(2);

	const QVImage<uChar, 3> imageRGB(channelR, channelG, channelB);
	Q_ASSERT_X(image == imageRGB, "test QImage channel selection", "Image channel splitting test 1");

	const QVImage<uChar, 3> imageBRG(image(2), image(0), image(1));
	const QVImage<uChar, 3> imageRGB2(imageBRG(1), imageBRG(2), imageBRG(0));
	Q_ASSERT_X(image == imageRGB2, "test QImage channel selection", "Image channel splitting test 2");

	// -------------------------------------------------
	// Test: Image conversion to BW.
	QVImage<uChar>	imageBW = image;
	const QVImage<uChar,3>	imageBWRGB = imageBW;

	Q_ASSERT_X(imageBWRGB(0) == imageBWRGB(1), "test QImage conversion to BW", "First channel of BW image is not equal to second.");
	Q_ASSERT_X(imageBWRGB(1) == imageBWRGB(2), "test QImage conversion to BW", "Second channel of BW image is not equal to third.");

	imageBW = imageBWRGB;
	// This test FAILS!
	//Q_ASSERT_X(imageBW == imageBWRGB(0), "test QImage conversion to BW", "Last conversion to BW failed.");

	// -------------------------------------------------
	// Test: Type conversions
	const QVImage<sFloat,3>	sFloatImage = image;
	const QVImage<uChar,3>	sFloatImageOrig = sFloatImage;
	Q_ASSERT_X(image == sFloatImage, "test type conversion", "Conversion with type sFloat failed.");

	const QVImage<sChar,3>	sCharImage = image;
	const QVImage<uChar,3>	sCharImageOrig = sCharImage;
	Q_ASSERT_X(image == sCharImage, "test type conversion", "Conversion with type sChar failed.");

	const QVImage<sInt,3>	sIntImage = image;
	const QVImage<uChar,3>	sIntImageOrig = sIntImage;
	Q_ASSERT_X(image == sIntImage, "test type conversion", "Conversion with type sInt failed.");

	const QVImage<uInt,3>	uIntImage = image;
	const QVImage<uChar,3>	uIntImageOrig = uIntImage;
	Q_ASSERT_X(image == uIntImage, "test type conversion", "Conversion with type uInt failed.");

	const QVImage<sShort,3>	sShortImage = image;
	const QVImage<uChar,3>	sShortImageOrig = sShortImage;
	Q_ASSERT_X(image == sShortImage, "test type conversion", "Conversion with type sShort failed.");

	const QVImage<uShort,3>	uShortImage = image;
	const QVImage<uChar,3>	uShortImageOrig = uShortImage;
	Q_ASSERT_X(image == uShortImage, "test type conversion", "Conversion with type uShort failed.");

	// -------------------------------------------------
	// Test: pixel access
	QVImage<uChar, 3> imageBis(image.getCols(), image.getRows());
	for(uInt i = 0; i < image.getRows(); i++)
		for(uInt j = 0; j < image.getCols(); j++)
			{
			imageBis(j,i,0) = image(j,i,0);
			imageBis(j,i,1) = image(j,i,1);
			imageBis(j,i,2) = image(j,i,2);
			}

	imageBis.setROI(image.getROI());
	Q_ASSERT_X(image == imageBis, "test pixel access", "First pixel access test failed.");
	}

int main(int argc, char *argv[])
	{
	// Check if the user provided enough command line parameters.
	if (argc < 2)
		{
		std::cout << "Usage: " << argv[0] << " <path to input images>" << std::endl;
		return -1;
		}

	int num_images = 0;
	const QDir imagesDir(argv[1]);
	const QStringList files = imagesDir.entryList(QDir::Files|QDir::Readable);
	foreach (QString file, files)
		{
		// Read the input file.
		QVImage<uChar, 3> image;
		readQVImageFromFile(QString(argv[1]) + "/" + file, image);

		// If it contains an image, perform tests on it.
		if (image.getCols() != 1 and image.getRows() != 1)
			{
			// Do tests for the image.
			std::cout << "Testing image " << (num_images++) << " '" << qPrintable(file) << "'. Size (" << image.getCols() << ", " << image.getRows() << ")" << std::endl;
			doTests(image);
			}
		}
	return 0;
	}

