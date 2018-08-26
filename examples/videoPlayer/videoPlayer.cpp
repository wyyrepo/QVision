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

/*!
@file videoPlayer.cpp

@brief Simple example of a QVision processing block for video input from many kind of sources, displaying the
       output to a canvas window.

This program will display in one or three image canvas the contents of a video file or the input from a video
resource. Using the --ColorRGBYUV comand line parameter, you can choose whether to show color, RGB separated or
YUV separated channels as output (execute './videoPlayer --help' for details).

@section Usage Usage of the program.

Once installed the QVision, compile using the <i>qmake</i> and <i>make</i> tools:
@code # qmake; make @endcode
Execute the application with the following line:
@code ./videoPlayer --URL=<source video identifier string> @endcode

For example:
@code ./videoPlayer --URL=http://perception.inf.um.es/public_data/videos/misc/minuto.avi @endcode

Execute with parameter @c --code to get help on additional available command line options:
@code ./videoPlayer --help @endcode

See section @ref VideoReaderURLFormat for further info about the format and types of source video identifier strings.

@ingroup ExamplePrograms

@author PARP Research Group. University of Murcia, Spain.
*/

#include <QVApplication>
#include <QVDefaultGUI>
#include <QVImageCanvas>
#include <QVVideoReaderBlock>
#include <qvip.h>
//#include <QVYUV4MPEG2WriterBlock>

#ifndef DOXYGEN_IGNORE_THIS
class PlayerBlock: public QVProcessingBlock
    {
	int frameNumber;
	QVImage<uChar, 3> actualImage;
    public:
        PlayerBlock(QString name): QVProcessingBlock(name),
			frameNumber(0)
            {
            addProperty< QVImage<uChar,3> >("RGB image", inputFlag|outputFlag);
            addProperty< QVImage<uChar> >("Y image", inputFlag|outputFlag);
            addProperty< QVImage<uChar> >("U image", inputFlag|outputFlag);
            addProperty< QVImage<uChar> >("V image", inputFlag|outputFlag);
            addProperty< QVImage<uChar> >("R image", inputFlag|outputFlag);
            addProperty< QVImage<uChar> >("G image", inputFlag|outputFlag);
            addProperty< QVImage<uChar> >("B image", inputFlag|outputFlag);
            addProperty<int>("ColorRGBYUV", inputFlag|guiInvisible, 1,
                             "Show Color (1), RGB separated (2) or YUV separated (3)",1,3);

			addTrigger("Store frame");
            }

		void processTrigger(const QString triggerName)
			{
			const QString fileName = QString("frame_") +	QString::number(frameNumber++).rightJustified(6, '0') + QString(".png");
			std::cout << "Storing frame in file " << qPrintable(fileName) << std::endl;
			writeQVImageToFile(fileName, actualImage);
			}

        void iterate()
			{
			actualImage = getPropertyValue< QVImage<uChar, 3> >("RGB image");
			}
    };

int main(int argc, char *argv[])
{
    QVApplication app(argc, argv, "Example program for QVision library. Displays the contents of a video source.");

    QVVideoReaderBlock camera("Video");
    PlayerBlock player("Video player");
    QVDefaultGUI interface;

    // QVYUV4MPEG2WriterBlock recorder("Video recorder");
    // player.linkProperty("RGB image", recorder, QVProcessingBlock::SynchronousLink);

    if(player.getPropertyValue<int>("ColorRGBYUV") == 1) {
        QVImageCanvas canvasRGB("RGB image");
        camera.linkProperty(&player,"RGB image");
        player.linkProperty("RGB image",canvasRGB);
        return app.exec();
    } else if(player.getPropertyValue<int>("ColorRGBYUV") == 2) {
        QVImageCanvas canvasR("R image"), canvasG("G image"), canvasB("B image");
        camera.linkProperty(&player,"R image","G image","B image",true);
        player.linkProperty("R image",canvasR);
        player.linkProperty("G image",canvasG);
        player.linkProperty("B image",canvasB);
        return app.exec();
    } else if(player.getPropertyValue<int>("ColorRGBYUV") == 3) {
        QVImageCanvas canvasY("Y image"), canvasU("U image"), canvasV("V image");
        camera.linkProperty(&player,"Y image","U image","V image");
        player.linkProperty("Y image",canvasY);
        player.linkProperty("U image",canvasU);
        player.linkProperty("V image",canvasV);
        return app.exec();
    } else {
        // Show error message and exit (app.exec() will do it):
        return app.exec();
    }
}
#endif

