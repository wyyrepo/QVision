/* This sample code was originally provided by Liu Liu
 * Copyright� 2009, Liu Liu All rights reserved.
 */

/*
This source is one of the sample codes from the OpenCV 2.3 library
*/

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc_c.h"


void help()
{
        printf("\nThis program demonstrates the Maximal Extremal Region interest point detector.\n"
                        "It finds the most stable (in size) dark and white regions as a threshold is increased.\n"
                        "\nCall:\n"
                        "./mser_sample <path_and_image_filename, Default is 'puzzle.png'>\n\n");
}

static CvScalar colors[] =
{
    {{0,0,255}},
    {{0,128,255}},
    {{0,255,255}},
    {{0,255,0}},
    {{255,128,0}},
    {{255,255,0}},
    {{255,0,0}},
    {{255,0,255}},
    {{255,255,255}},
    {{196,255,255}},
    {{255,255,196}}
};

static uchar bcolors[][3] =
{
    {0,0,255},
    {0,128,255},
    {0,255,255},
    {0,255,0},
    {255,128,0},
    {255,255,0},
    {255,0,0},
    {255,0,255},
    {255,255,255}
};


int main( int argc, char** argv )
{
        char path[1024];
        IplImage* img;
        help();
        if (argc!=2)
        {
                strcpy(path,"puzzle.png");
                img = cvLoadImage( path, CV_LOAD_IMAGE_GRAYSCALE );
                if (!img)
                {
                        printf("\nUsage: mser_sample <path_to_image>\n");
                        return 0;
                }
        }
        else
        {
                strcpy(path,argv[1]);
                img = cvLoadImage( path, CV_LOAD_IMAGE_GRAYSCALE );
        }

        if (!img)
        {
                printf("Unable to load image %s\n",path);
                return 0;
        }
        IplImage* rsp = cvLoadImage( path, CV_LOAD_IMAGE_COLOR );
        IplImage* ellipses = cvCloneImage(rsp);
        cvCvtColor(img,ellipses,CV_GRAY2BGR);
        CvSeq* contours;
        CvMemStorage* storage= cvCreateMemStorage();
        IplImage* hsv = cvCreateImage( cvGetSize( rsp ), IPL_DEPTH_8U, 3 );
        cvCvtColor( rsp, hsv, CV_BGR2YCrCb );
        CvMSERParams params = cvMSERParams();//cvMSERParams( 5, 60, cvRound(.2*img->width*img->height), .25, .2 );

        double t = (double)cvGetTickCount();
        cvExtractMSER( hsv, NULL, &contours, storage, params );
        t = cvGetTickCount() - t;
        printf( "MSER extracted %d contours in %g ms.\n", contours->total, t/((double)cvGetTickFrequency()*1000.) );
        uchar* rsptr = (uchar*)rsp->imageData;
        // draw mser with different color
        for ( int i = contours->total-1; i >= 0; i-- )
        {
                CvSeq* r = *(CvSeq**)cvGetSeqElem( contours, i );
                for ( int j = 0; j < r->total; j++ )
                {
                        CvPoint* pt = CV_GET_SEQ_ELEM( CvPoint, r, j );
                        rsptr[pt->x*3+pt->y*rsp->widthStep] = bcolors[i%9][2];
                        rsptr[pt->x*3+1+pt->y*rsp->widthStep] = bcolors[i%9][1];
                        rsptr[pt->x*3+2+pt->y*rsp->widthStep] = bcolors[i%9][0];
                }
        }
        // find ellipse ( it seems cvfitellipse2 have error or sth?
        for ( int i = 0; i < contours->total; i++ )
        {
                CvContour* r = *(CvContour**)cvGetSeqElem( contours, i );
                CvBox2D box = cvFitEllipse2( r );
                box.angle=(float)CV_PI/2-box.angle;

                if ( r->color > 0 )
                        cvEllipseBox( ellipses, box, colors[9], 2 );
                else
                        cvEllipseBox( ellipses, box, colors[2], 2 );

        }

        cvSaveImage( "rsp.png", rsp );

        cvNamedWindow( "original", 0 );
        cvShowImage( "original", img );

        cvNamedWindow( "response", 0 );
        cvShowImage( "response", rsp );

        cvNamedWindow( "ellipses", 0 );
        cvShowImage( "ellipses", ellipses );

        cvWaitKey(0);

        cvDestroyWindow( "original" );
        cvDestroyWindow( "response" );
        cvDestroyWindow( "ellipses" );
        cvReleaseImage(&rsp);
        cvReleaseImage(&img);
        cvReleaseImage(&ellipses);

}
