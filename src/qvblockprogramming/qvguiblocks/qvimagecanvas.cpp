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

/// @file
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#include <QVImageCanvas>
#include <qvmath.h>

QVImageCanvas::QVImageCanvas(const QString name, QWidget *parent): QVCanvas(parent), QVPropertyContainer(name), _low(0.0), _high(255.0), colorCursor(0),
	contentLinkedBlocks(0)
	{
	qDebug() << "QVImageCanvas::QVImageCanvas()";
	if (qvApp == NULL)
		{
		QString str = "QVImageCanvas::QVImageCanvas(): the QVPlot cannot be created before the QVApplication instance. Aborting now.";
		std::cerr << qPrintable(str) << std::endl;
		exit(1);
		}
	// if its a --help call, do nothing
	if (qvApp->forHelp()) return;

	setWindowTitle("Image canvas for " + getName());
	addProperty<QRect>("rect select", outputFlag, QRect(), "Rectangule selected in it's image area");
	addProperty<QVPolyline>("poly select", outputFlag, QVPolyline(), "Poliline selected in it's image area");
	addProperty<QColor>("Color for selected polygon", outputFlag | internalProp, Qt::red, "Color for property poly select");	// to draw the polyline
	addProperty<bool>("Print tags for selected polygon", outputFlag | internalProp, false, "Print tag flag poly select");		//
	addProperty<TPolyMode>("Mode for selected polygon", outputFlag | internalProp, LINE, "Polyline select mode");			//
	addProperty<QPoint>("Center for selected polygon", outputFlag | internalProp, QPoint(), "Polyline select center");		//
	addProperty<float>("Radius for selected polygon", outputFlag | internalProp, 0.0, "Polyline select radius");			//

	//setColor("rect select", Qt::
	addProperty< QVImage<uChar, 3> >("Content", outputFlag);

	//addProperty<QVMatrix>("Camera calibration matrix", inputFlag);
	//addProperty<QVCameraPose>("Camera pose", inputFlag);

	show();
	};

void QVImageCanvas::viewer()
	{
	qDebug() << "QVImageCanvas::viewer()";
	QMutexLocker locker(&qvApp->mutex);

	readInputProperties();

	// Draw images objects
	foreach(QString name, getPropertyList())
                if( (getPropertyFlags(name) & inputFlag) and not (getPropertyFlags(name) & guiInvisible) )
                        {
			// Draw <uChar,1> images
			if (isType< QVImage<uChar,1> >(name)) {
				QVImage<uChar, 1> imageAux = getPropertyValue<QVImage<uChar,1> >(name);
				getQVPainter()->drawQVImage(&imageAux);
				}
			// Draw <uChar,3> images
			else if (isType< QVImage<uChar,3> >(name)) {
				QVImage<uChar,3> imageAux = getPropertyValue<QVImage<uChar,3> >(name);
				getQVPainter()->drawQVImage(&imageAux);
				}
			// Draw <sFloat,1> images
			else if (isType< QVImage<sFloat,1> >(name)) {
				QVImage<sFloat,1> imageAux = getPropertyValue<QVImage<sFloat,1> >(name);
				getQVPainter()->drawQVImage(&imageAux, TRUE, _low, _high);
				}
			// Draw <sFloat,3> images
			else if (isType< QVImage<sFloat,3> >(name)) {
				QVImage<sFloat,3> imageAux = getPropertyValue<QVImage<sFloat,3> >(name);
				getQVPainter()->drawQVImage(&imageAux, TRUE, _low, _high);
				}
			///@todo El código en qvcanvas para que se representen las imagenes uShort, sShort y sInt está incluido, pero como genera
			/// una imagen negra (cuyo motivo desconozco), he añadido aqui una conversión de esos tipos de imagen a uChar,
			/// para su visualización. Lo cual no es lo más correcto, ya que este tipo de conversiones trunca los valores
			/// que exceden del rango de uChar (no lo he dejado sobre sFloat porque parece relentizar el proceso). Depurar esto.
			// Draw <sShort,1> images
			else if (isType< QVImage<uShort,1> >(name)) {
				QVImage<uChar, 1> imageAux = getPropertyValue<QVImage<uShort,1> >(name);
				getQVPainter()->drawQVImage(&imageAux);
				}
			// Draw <sShort,3> images
			else if (isType< QVImage<uShort,3> >(name)) {
				QVImage<uChar, 3> imageAux = getPropertyValue<QVImage<uShort,3> >(name);
				getQVPainter()->drawQVImage(&imageAux);
				}
			// Draw <sShort,1> images
			else if (isType< QVImage<sShort,1> >(name)) {
				QVImage<uChar, 1> imageAux = getPropertyValue<QVImage<sShort,1> >(name);
				getQVPainter()->drawQVImage(&imageAux);
				}
			// Draw <sShort,3> images
			else if (isType< QVImage<sShort,3> >(name)) {
				QVImage<uChar, 3> imageAux = getPropertyValue<QVImage<sShort,3> >(name);
				getQVPainter()->drawQVImage(&imageAux);
				}
			// Draw <sInt,1> images
			else if (isType< QVImage<sInt,1> >(name)) {
				QVImage<uChar, 1> imageAux = getPropertyValue<QVImage<sInt,1> >(name);
				getQVPainter()->drawQVImage(&imageAux);
				}
			// Draw <sInt,3> images
			else if (isType< QVImage<sInt,3> >(name)) {
				QVImage<uChar, 3> imageAux = getPropertyValue<QVImage<sInt,3> >(name);
				getQVPainter()->drawQVImage(&imageAux);
				}
			}

	// Draw other objects
	foreach(QString name, getPropertyList())
                if( (getPropertyFlags(name) & inputFlag) and not (getPropertyFlags(name) & guiInvisible) )
			{
			getQVPainter()->setBrush(QBrush(Qt::NoBrush));

			// Draw points list.
			if (isType< QList<QPoint> >(name))
				draw(	getPropertyValue< QList<QPoint> >(name),
						getPropertyValue<QColor>("Color for " + name),
						getPropertyValue<bool>("Print tags for " + name),
						getPropertyValue<int>("Radius for " + name)
						);

			// Draw floating points list.
			else if (isType< QList<QPointF> >(name))
				draw(	getPropertyValue< QList<QPointF> >(name),
						getPropertyValue<QColor>("Color for " + name),
						getPropertyValue<bool>("Print tags for " + name),
						getPropertyValue<int>("Radius for " + name)
						);

			// Draw polylines.
			else if (isType< QVPolyline >(name))
				draw(	getPropertyValue< QVPolyline >(name),
						getPropertyValue<QColor>("Color for " + name),
						getPropertyValue<bool>("Print tags for " + name)
						);

			// Draw float polylines.
			else if (isType< QVPolylineF >(name))
				draw(	getPropertyValue< QVPolylineF >(name),
						getPropertyValue<QColor>("Color for " + name),
						getPropertyValue<bool>("Print tags for " + name)
						);

			// Draw rectangles.
			else if (isType< QRect >(name))
				draw(	getPropertyValue< QRect >(name),
						getPropertyValue<QColor>("Color for " + name),
						getPropertyValue<bool>("Print tags for " + name)
						);

			// Draw polyline list.
			else if (isType< QList<QVPolyline> >(name))
				foreach(QVPolyline polyline, getPropertyValue< QList<QVPolyline> >(name))
					draw(	polyline,
							getPropertyValue<QColor>("Color for " + name),
							getPropertyValue<bool>("Print tags for " + name)
							);

			// Draw float polyline list.
			else if (isType< QList<QVPolylineF> >(name))
				foreach(QVPolylineF polyline, getPropertyValue< QList<QVPolylineF> >(name))
					draw(	polyline,
							getPropertyValue<QColor>("Color for " + name),
							getPropertyValue<bool>("Print tags for " + name)
							);

			// Draw rectangles list.
			else if (isType< QList<QRect> >(name))
				foreach(QRect rectangle, getPropertyValue< QList<QRect> >(name))
					draw(	rectangle,
							getPropertyValue<QColor>("Color for " + name),
							getPropertyValue<bool>("Print tags for " + name)
							);
			// Draw points list.
			else if (isType< QList<QPointFMatching> >(name))
				foreach(QPointFMatching matching, getPropertyValue< QList<QPointFMatching> >(name))
					draw(	matching,
							getPropertyValue<double>("Radius for " + name)
							);

			}
	// ---------------------------------
	QVMatrix K = QVMatrix();
	QVCameraPose cameraPose;

	// Detect camera pose and/or calibration matrix.
	foreach(QString name, getPropertyList())
                if( getPropertyFlags(name) & inputFlag )
			{
			if (isType< QVCameraPose >(name))
				cameraPose = getPropertyValue< QVCameraPose >(name);
			else if (isType< QVMatrix >(name))
				K = getPropertyValue< QVMatrix >(name);
			}

	if (K.getCols() == 3 and K.getRows() == 3)
		{
		// Draw 3D stuff.
		beginDrawWorldFromCamera(K(0,0), K(1,1), cameraPose);

		// Draw primitive types.
		foreach(QString name, getPropertyList())
			if (getPropertyFlags(name) & inputFlag)
				{
				// Draw QV3DPolylineF
				if (isType< QV3DPolylineF >(name))
					draw(	getPropertyValue< QV3DPolylineF >(name),
						getPropertyValue<QColor>("Color for " + name),
						getPropertyValue<double>("Size for " + name));
				// Draw QList<QV3DPointF>
				else if (isType< QList<QV3DPointF> >(name))
					draw(	getPropertyValue< QList<QV3DPointF> >(name),
						getPropertyValue<QColor>("Color for " + name),
						getPropertyValue<double>("Size for " + name));
				// Draw QList<QV3DPolylineF>
				else if (isType< QList<QV3DPolylineF> >(name))
					foreach(QV3DPolylineF polyline, getPropertyValue< QList<QV3DPolylineF> >(name))
						draw(	polyline,
							getPropertyValue<QColor>("Color for " + name));
				}

		// Draw 3D models.
		foreach(QV3DModel *model, models)
			model->updatePaint( * (this->imageArea));

		custom_viewer_3D();

		endDrawWorldFromCamera();
		}

	custom_viewer();

	// ---------------------------------

	//custom_viewer();

	/// @todo La captura de imágenes de un QVImageCanvas no funciona. El método <i>contentImage</i>
	/// de la clase QVCanvas no obtiene correctamente la imágen contenida en el canvas.
	// If an image property was linked from a block, render it to an QVImage property.
	if (contentLinkedBlocks > 0)
		{
		QVImage<uChar, 3> image = contentImage();
		std::cout << "Linked Blocks = " << contentLinkedBlocks << std::endl;
		std::cout << "\t dims(ImageCanvas) = " << image.getCols() << "x" << image.getRows() << std::endl;
		setPropertyValue< QVImage<uChar, 3> >("Content", image);
		}

	writeOutputProperties();

	qDebug() << "QVImageCanvas::viewer() <~ return";
	}

/////////////////////////////////////////

void QVImageCanvas::draw(const QList<QPoint> &pointList, QColor color, bool printTags, int radius)
	{
	const int diameter = 2*radius;
	getQVPainter()->setPen(color);
	getQVPainter()->setBrush(QBrush(color, Qt::SolidPattern));

	// Paint points with a circle.
	for (int i = 0; i< pointList.size(); i++)
		{
		const QPoint point = pointList.at(i);
		if (printTags)
			getQVPainter()->drawText(point + QPoint(2,-2), QString("%1").arg(i));

		getQVPainter()->drawEllipse(point.x()-radius, point.y()-radius, diameter, diameter);
		}
	}

void QVImageCanvas::draw(const QList<QPointF> &pointList, QColor color, bool printTags, double radius)
	{
	const double diameter = 2*radius;
	getQVPainter()->setPen(Qt::black);
	getQVPainter()->setBrush(QBrush(color, Qt::SolidPattern));

	// Paint points with a circle.
	for (int i = 0; i< pointList.size(); i++)
		{
		const QPointF point = pointList.at(i);
		if (printTags)
			getQVPainter()->drawText(point+QPointF(2,-2), QString("%1").arg(i));

		QRectF rect(point.x() - radius, point.y() - radius, diameter, diameter);
		getQVPainter()->drawEllipse(rect);
		}
	}

void QVImageCanvas::draw(const QPointFMatching &matching, const int radius)
	{
	const int	x = ABS(int(matching.first.x())),
				y = ABS(int(matching.first.y()));

	const QColor color(	int(123456*x + 654321*y)%255,
						int(162534*x + 615243*y)%255,
						int(342516*x + 435261*y)%255 );

	//const QColor color = qvColors[ int(matching.first.x()+matching.first.y()) % 10];

	// Draw line segments between each pair of adjacent points in the polyline.
	getQVPainter()->setPen(color);
	getQVPainter()->drawLine(matching.first, matching.second);


	const double diameter = 2*radius;
	getQVPainter()->setPen(Qt::black);
	getQVPainter()->setBrush(QBrush(color, Qt::SolidPattern));
	getQVPainter()->drawEllipse(QRectF(matching.first.x() - radius, matching.first.y() - radius, diameter, diameter));
	getQVPainter()->drawEllipse(QRectF(matching.second.x() - radius, matching.second.y() - radius, diameter, diameter));
	}

//@todo La posicione de los píxeles esta desplazado respecto a los clic de raton, esto se ve a la hora de pintar polilineas o seleccionar ROIs al máximo zoom, queriendo ajustar la precisión al pixel.
void QVImageCanvas::draw(const QVPolyline &polyline, QColor color, bool /*printTags*/)
	{
	getQVPainter()->setPen(color);

	for (int i = polyline.size()-1; i>0; i--)
		getQVPainter()->drawLine(polyline.at(i-1)+QPointF(0.5,0.5),polyline.at(i)+QPointF(0.5,0.5));

	if (polyline.closed)
		getQVPainter()->drawLine(polyline.at(0) + QPointF(0.5,0.5), polyline.at(polyline.size() -1) + QPointF(0.5,0.5));

	//getQVPainter()->drawArc(QRect(polyline.at(0) + QPoint(0,0), polyline.at(0) + QPoint(1,1)), 0, 16*360);
	/*getQVPainter()->drawLine(last + QPointF(0.72500,   0.88971), last + QPointF(0.27500,   0.11029));
	getQVPainter()->drawLine(last + QPointF(0.88971,   0.72500), last + QPointF(0.11029,   0.27500));
	getQVPainter()->drawLine(last + QPointF(0.88971,   0.27500), last + QPointF(0.11029,   0.72500));
	getQVPainter()->drawLine(last + QPointF(0.72500,   0.11029), last + QPointF(0.27500,   0.88971));*/
	}

void QVImageCanvas::draw(const QVPolylineF &polyline, QColor color, bool /*printTags*/)
	{
	getQVPainter()->setPen(color);

	// Draw line segments between each pair of adjacent points in the polyline.
	for (int i = polyline.size()-1; i>0; i--)
		getQVPainter()->drawLine(polyline.at(i-1)+QPointF(0.5,0.5),polyline.at(i)+QPointF(0.5,0.5));

	if (polyline.closed)
		getQVPainter()->drawLine(polyline.at(0) + QPointF(0.5,0.5), polyline.at(polyline.size() -1) + QPointF(0.5,0.5));

	//getQVPainter()->drawArc(QRect(polyline.at(0) + QPoint(0,0), polyline.at(0) + QPoint(1,1)), 0, 16*360);
	/*getQVPainter()->drawLine(last + QPointF(0.72500,   0.88971), last + QPointF(0.27500,   0.11029));
	getQVPainter()->drawLine(last + QPointF(0.88971,   0.72500), last + QPointF(0.11029,   0.27500));
	getQVPainter()->drawLine(last + QPointF(0.88971,   0.27500), last + QPointF(0.11029,   0.72500));
	getQVPainter()->drawLine(last + QPointF(0.72500,   0.11029), last + QPointF(0.27500,   0.88971));*/
	}

void QVImageCanvas::draw(const QRect &rectangle, QColor color, bool /*printTags*/)
	{
	getQVPainter()->setPen(color);

	getQVPainter()->drawLine(rectangle.topLeft(), rectangle.topRight() );
	getQVPainter()->drawLine(rectangle.topLeft(), rectangle.bottomLeft() );
	getQVPainter()->drawLine(rectangle.bottomLeft(), rectangle.bottomRight() );
	getQVPainter()->drawLine(rectangle.topRight(), rectangle.bottomRight() );
	}

void QVImageCanvas::unlink()
	{
	std::cerr << "ERROR: QVImageCanvas::linkProperty(): global unlink not implemented" << std::endl;
	}

bool QVImageCanvas::linkUnspecifiedInputProperty(QVPropertyContainer *sourceContainer, QString sourcePropName, LinkType linkType)
	{
	if (containsProperty(sourcePropName))
		return false;

	if (linkType == SynchronousLink)
		{
		std::cerr << "ERROR: QVImageCanvas::linkUnspecifiedInputProperty(): the linkType must be AsynchronousLink, the link will not be done" << std::endl;
		return false;
		}

	QVProcessingBlock* block;
	if((block = dynamic_cast<QVProcessingBlock*>(sourceContainer)) != NULL)
		{
		addPropertyFromQVariant(sourcePropName, inputFlag, block->getPropertyQVariantValue(sourcePropName), block->getPropertyInfo(sourcePropName));

		if (	block->isType< QList<QPoint> >(sourcePropName)		||
				block->isType< QList<QPointF> >(sourcePropName)		||
				block->isType< QVPolyline >(sourcePropName)			||
				block->isType< QVPolylineF >(sourcePropName)		||
				block->isType< QRect >(sourcePropName)				||
				block->isType< QList<QVPolyline> >(sourcePropName)	||
				block->isType< QList<QVPolylineF> >(sourcePropName)	||
				block->isType< QList<QRect> >(sourcePropName)		)
			{
			std::cout << "Adding property of name " << qPrintable(sourcePropName) << " with default color " << colorCursor << std::endl;
			addProperty<QColor>("Color for " + sourcePropName, inputFlag, getNextColor(), QString("Color for object ") + sourcePropName);
			addProperty<bool>("Print tags for " + sourcePropName, inputFlag, false, QString("Print tags for object ") + sourcePropName);
			if (	sourceContainer->isType< QList<QPointF> >(sourcePropName)||
				sourceContainer->isType< QList<QPoint> >(sourcePropName)	)
				addProperty<int>(	"Radius for " + sourcePropName, inputFlag, 3,
							QString("Specify a radius for the points to be displayed.") + sourcePropName);
			}
		else if (	block->isType< QV3DPolylineF >(sourcePropName)	||
				block->isType< QList<QV3DPointF> >(sourcePropName)	||
				block->isType< QList<QV3DPolylineF> >(sourcePropName)	)
				{
				addProperty<QColor>("Color for " + sourcePropName, inputFlag, getNextColor(), QString("Color for object ") + sourcePropName);
				addProperty<double>("Size for " + sourcePropName, inputFlag, 1, QString("Size for object ") + sourcePropName);

				#ifdef DEBUG
				std::cout << "QV3DCanvas: Added property 'Color for " << qPrintable(sourcePropName) << "'" << std::endl;
				std::cout << "QV3DCanvas: Added property 'Size for " << qPrintable(sourcePropName) << "'" << std::endl;
				#endif // DEBUG
				}
		else if ( block->isType< QList<QPointFMatching> >(sourcePropName) )
				{
				addProperty<double>("Radius for " + sourcePropName, inputFlag, 1, QString("Radius for object ") + sourcePropName);

				#ifdef DEBUG
				std::cout << "QV3DCanvas: Added property 'Radius for " << qPrintable(sourcePropName) << "'" << std::endl;
				#endif // DEBUG
				}

		bool result = block->linkProperty(sourcePropName, this, sourcePropName ,QVProcessingBlock::AsynchronousLink);
		QObject::connect(block, SIGNAL(endIteration(uint, int)), this, SLOT(refreshImageArea()));
		return result;
		}
	else
		{
		std::cerr << "ERROR: QVImageCanvas::linkUnspecifiedInputProperty(): the sourceContainer container must be a QVProcessingBlock, the link will not be done" << std::endl;
		return false;
		}
	}

bool QVImageCanvas::linkUnspecifiedOutputProperty(QVPropertyContainer *destContainer, QString destPropName, LinkType linkType)
	{
	
	if (linkType == SynchronousLink)
		std::cerr << "ERROR: QVImageCanvas::linkUnspecifiedOutputProperty(): the linkType must be AsynchronousLink, the link will not be done." << std::endl;
	else if (dynamic_cast<QVProcessingBlock*>(destContainer) == NULL)
		std::cerr << "ERROR: QVImageCanvas::linkUnspecifiedOutputProperty(): destination block is not a block." << std::endl;
	else  if (!destContainer->isType< QVImage<uChar, 3> >(destPropName))
		std::cerr << "ERROR: QVImageCanvas::linkUnspecifiedOutputProperty(): destination property is not of type QVImage<uChar, 3>." << std::endl;
	else if (linkProperty("Content", destContainer, destPropName ,QVProcessingBlock::AsynchronousLink))
		{
		//std::cerr << "OK: QVImageCanvas::linkUnspecifiedOutputProperty(): linked image." << std::endl;
		contentLinkedBlocks++;
		return true;
		}

	return false;
	}

bool QVImageCanvas::treatUnlinkInputProperty(QString destPropName, QVPropertyContainer *sourceContainer, QString sourcePropName)
	{
	if ( (destPropName != "rect select") && (destPropName != "poly select") )
		{
		removeProperty(sourcePropName);

		if (	sourceContainer->isType< QList<QPoint> >(sourcePropName)		||
				sourceContainer->isType< QList<QPointF> >(sourcePropName)		||
				sourceContainer->isType< QVPolyline >(sourcePropName)			||
				sourceContainer->isType< QVPolylineF >(sourcePropName)			||
				sourceContainer->isType< QRect >(sourcePropName)				||
				sourceContainer->isType< QList<QVPolyline> >(sourcePropName)	||
				sourceContainer->isType< QList<QVPolylineF> >(sourcePropName)	||
				sourceContainer->isType< QList<QRect> >(sourcePropName)			)
			{
			removeProperty("Color for " + sourcePropName);
			removeProperty("Print tags for " + sourcePropName);
			if (	sourceContainer->isType< QList<QPointF> >(sourcePropName)||
				sourceContainer->isType< QList<QPoint> >(sourcePropName)	)
				removeProperty("Radius for " + sourcePropName);
			}
		else if	(	sourceContainer->isType< QV3DPolylineF >(sourcePropName)		||
					sourceContainer->isType< QList<QV3DPointF> >(sourcePropName)	||
					sourceContainer->isType< QList<QV3DPolylineF> >(sourcePropName) )
			{
			removeProperty("Color for " + sourcePropName);
			removeProperty("Size for " + sourcePropName);
			}
		else if (	sourceContainer->isType< QList<QPointFMatching> >(sourcePropName) )
			removeProperty("Size for " + sourcePropName);

		QVProcessingBlock* block;
		if((block = dynamic_cast<QVProcessingBlock*>(sourceContainer)) != NULL)
			QObject::disconnect(block, SIGNAL(endIteration(uint, int)), this, SLOT(refreshImageArea()));
		}
	return true;
	}

void QVImageCanvas::setSaturationRange(float low,float high)
	{
	_low = low;
	_high = high;
	}

void QVImageCanvas::rectSelectedSlot(QRect rect)
	{
	setPropertyValue<QRect>("rect select", rect);
	writeOutputProperties();
	}

void QVImageCanvas::polySelectedSlot(QPoint point, bool reset, TPolyMode mode)
	{
	if (reset)
		setPropertyValue<QVPolyline>("poly select", QVPolyline());
	else
		{
		QVPolyline poly = getPropertyValue<QVPolyline>("poly select");
		poly.append(point);
		setPropertyValue<QVPolyline>("poly select", poly);
		}

	setPropertyValue<TPolyMode>("Mode for selected polygon", mode);
	writeOutputProperties();
	}

