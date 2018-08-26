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

#include <vector>
#include <locale.h>
#include <SiftGPU.h>
#include <QtOpenGL>

#include <qvsiftgpu.h>

static bool firstTime = TRUE;
static SiftGPU *sift = NULL;

bool resetSiftGPU()
    {
    delete sift;

    firstTime = TRUE;
    sift = NULL;
    return true;
    }

const QList<QVSiftFeature>	getSiftGPUFeatures(const QVImage<uChar> &image,
                                nvidia_method method,
                                bool sd, double f, double w, double dw,
                                int fo, double t, double e, int d, int v)
    {
    //static SiftGPU sift;

    if (sift == NULL)
        sift = new SiftGPU();

    // Needed for correct interpretation of dot (.) in numeric strings: (!)
    setlocale(LC_NUMERIC,"C");

    // String arguments for sift parsing of parameters:
    char * t_argv[] = { (char*) "", (char*) "-f", (char*) "4.0", (char*) "-w", (char*) "2.0",
    (char*) "-dw", (char*) "3.0", (char*) "-fo", (char*) "0",
    (char*) "-t", (char*) "0.00666", (char*) "-e", (char*) "10.0",
    (char*) "-d", (char*) "3",
    (char*) "-v", (char*) "0",
    (char*) "-sign", (char*) "-sd" };

    int t_argc = sizeof(t_argv)/sizeof(char*);

    // Choose CUDA, GLSL or CG method:
    switch(method)
        {
        case CUDA_METHOD:
            t_argv[0] = (char*) "-cuda";
            break;
        case GLSL_METHOD:
            t_argv[0] = (char*) "-glsl";
            break;
        case CG_METHOD:
            t_argv[0] = (char*) "-cg";
            break;
        }

    // If not descriptors needed, do not take into account last parameter "-sd".
    if(not sd)
        t_argc--;

    // Rest of parameters:
    QString aux_f = QString::number(f,'f',6);
    QString aux_w = QString::number(w,'f',6);
    QString aux_dw = QString::number(dw,'f',6);
    QString aux_fo = QString::number(fo);
    QString aux_t = QString::number(t,'f',6);
    QString aux_e = QString::number(e,'f',6);
    QString aux_d = QString::number(d);
    QString aux_v = QString::number(v);

    t_argv[2] = new char[50]; strcpy(t_argv[2],aux_f.toLatin1().data());
    t_argv[4] = new char[50];  strcpy(t_argv[4],aux_w.toLatin1().data());
    t_argv[6] = new char[50];  strcpy(t_argv[6],aux_dw.toLatin1().data());
    t_argv[8] = new char[50];  strcpy(t_argv[8],aux_fo.toLatin1().data());
    t_argv[10] = new char[50];  strcpy(t_argv[10],aux_t.toLatin1().data());
    t_argv[12] = new char[50];  strcpy(t_argv[12],aux_e.toLatin1().data());
    t_argv[14] = new char[50];  strcpy(t_argv[14],aux_d.toLatin1().data());
    t_argv[16] = new char[50];  strcpy(t_argv[16],aux_v.toLatin1().data());

    sift->ParseParam(t_argc, t_argv);

    delete [] t_argv[2];
    delete [] t_argv[4];
    delete [] t_argv[6];
    delete [] t_argv[8];
    delete [] t_argv[10];
    delete [] t_argv[12];
    delete [] t_argv[14];
    delete [] t_argv[16];

    // OpenGL context creation:
    if(firstTime)
        {
        if(sift->CreateContextGL() != SiftGPU::SIFTGPU_FULL_SUPPORTED)
            std::cerr << "Falla inicialización ContextGL\n";
        firstTime = FALSE;
        }

    // Run of GPU SIFT method:
    int width = /* image.getCols() */ image.getStep(), height = image.getRows();
    const unsigned char *data = image.getReadData();
    sift->RunSIFT(width,height,data,GL_LUMINANCE,GL_UNSIGNED_BYTE);

    // Extract output:
    int num = sift->GetFeatureNum();
    std::vector<float> descriptors(128*num);
    std::vector<SiftGPU::SiftKeypoint> keys(num);
    sift->GetFeatureVector(&keys[0],&descriptors[0]);
    QList<QVSiftFeature> feature_list;
    for(int i=0;i<num;i++)
        {
        QVKeypoint keypoint;
        QVVector descriptor(128);

        keypoint.x() = keys[i].x;
        keypoint.y() = keys[i].y;
        keypoint.scale() = keys[i].s;
        keypoint.orientation() = keys[i].o;

        for(int j=0;j<128;j++)
            descriptor[j] = descriptors[128*i+j];

        feature_list.append( QVSiftFeature(keypoint, descriptor) );
        }

    return feature_list;
    }

//QList< QPair<int, int> > matchSiftGPUFeatures(const QList<QVSiftFeature> img1features, const QList<QVSiftFeature> img2features)
QList< QPair<int, int> > matchSiftGPUFeatures(const QList<QVSiftFeature> img1features, const QList<QVSiftFeature> img2features, const float distmax, const float ratiomax, const bool mutual_best_match)
    {
    if (sift == NULL)
        sift = new SiftGPU();

    if(firstTime)
        {
        if(sift->CreateContextGL() != SiftGPU::SIFTGPU_FULL_SUPPORTED)
            std::cerr << "Falla inicialización ContextGL\n";
        firstTime = FALSE;
        }

    const int	size1 = img1features.size(),
            size2 = img2features.size(),
            minSize = MIN(size1, size2);

    float des1[128*size1], des2[128*size2];

    for(int i=0;i<size1;i++)
        for(int j=0;j<128;j++)
            des1[i*128+j] = img1features[i].descriptor[j];

    for(int i=0;i<size2;i++)
        for(int j=0;j<128;j++)
            des2[i*128+j] = img2features[i].descriptor[j];

    SiftMatchGPU matcher(minSize);
    if(matcher.VerifyContextGL() == 0)
        {
        std::cout << "Error in matcher. VerifyContextGL\n";
        return QList<QPair<int, int> >();
        }

    matcher.SetDescriptors(0, size1, des1);
    matcher.SetDescriptors(1, size2, des2);

    int match_buf[minSize][2];
    int num_matchings = matcher.GetSiftMatch(minSize, match_buf, distmax, ratiomax, mutual_best_match);

    QList< QPair<int, int> > matchings;
    for(int i = 0; i < num_matchings; i++)
        matchings << QPair<int, int>(match_buf[i][0], match_buf[i][1]);

    return matchings;
    }

