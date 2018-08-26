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

#include <opencv/cv.h>
#include <QPointF>
#include <QRect>
#include <QList>

#ifndef QVDELAUNAYTRIANGULATION_H
#define QVDELAUNAYTRIANGULATION_H

#ifndef DOXYGEN_IGNORE_THIS
// Inspired in Roman Stanchak's Delaunay triangulation code for OpenCV.
//	http://opencv.willowgarage.com/wiki/RomanStanchak
class QVDelaunayTriangulation
	{
	private:
		QRect		range;
		CvMemStorage*	storage;	//Storage for the Delaunay subdivsion.
		CvSubdiv2D*	subdiv; 	// The subdivision itself.
		QList<QPointF>	points;

	public:
		QVDelaunayTriangulation(const QRect &range): range(range)
			{
			storage = cvCreateMemStorage(0);
			subdiv = cvCreateSubdiv2D(CV_SEQ_KIND_SUBDIV2D, sizeof(*subdiv), sizeof(CvSubdiv2DPoint), sizeof(CvQuadEdge2D), storage);
			cvInitSubdivDelaunay2D(subdiv, (CvRect){ range.left(), range.top(), range.right(), range.bottom() });
			}

		void addPoint(const QPointF &point)	{ points << point; cvSubdivDelaunay2DInsert(subdiv, (CvPoint2D32f){ point.x(), point.y() }); }
		QList<QPointF> getPoints()	const	{ return points; }

		QHash<QPointF, QPointF> getLinks() const
			{
			const int	minX = range.left(), minY = range.top(),
					maxX = range.right(), maxY = range.bottom();

			CvSeqReader reader;
			QHash <QPointF, QPointF> correspondences;
			cvStartReadSeq((CvSeq *)subdiv->edges, &reader);
		
			for(int i=0; i<subdiv->edges->total; i++)
				{
				CvQuadEdge2D * edge = (CvQuadEdge2D *) reader.ptr;
				if(CV_IS_SET_ELEM(edge))
					{
					CvSubdiv2DPoint * org = cvSubdiv2DEdgeOrg( (CvSubdiv2DEdge) edge );
					CvSubdiv2DPoint * dst = cvSubdiv2DEdgeDst( (CvSubdiv2DEdge) edge );
					if(org && dst && (CV_IS_SET_ELEM(org) && ((org)->flags & CV_SUBDIV2D_VIRTUAL_POINT_FLAG)==0))
						if ( (org->pt.x > minX) && (org->pt.x < maxX) && (dst->pt.y > minY) && (dst->pt.y < maxY) )
							correspondences.insertMulti(QPointF(org->pt.x, org->pt.y), QPointF(dst->pt.x, dst->pt.y));
					}
				CV_NEXT_SEQ_ELEM(subdiv->edges->elem_size, reader);
				}

			return correspondences;
			}
	};
#endif // DOXIGEN_IGNORE_THIS
#endif // QVDELAUNAYTRIANGULATION_H
