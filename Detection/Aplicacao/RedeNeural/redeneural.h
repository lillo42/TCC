#ifndef REDENEURAL_H
#define REDENEURAL_H

#include "Base/classificadorbase.h"

#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

#include <stdio.h>
#include <math.h>

using namespace cv;
using namespace std;

//http://docs.opencv.org/modules/ml/doc/neural_networks.html
//http://www.nithinrajs.in/ocr-artificial-neural-network-opencv-part-3final-preprocessing/

class RedeNeural : public ClassificadorBase
{
public:
    RedeNeural();
    ~RedeNeural();

    void Treina(vector<Mat> &caracteristica, vector<Mat> &naoCarracteristica);
    float Predicao(Mat image);

private:
    CvANN_MLP mlp;
    CvANN_MLP_TrainParams params;
    CvTermCriteria criteria;

    void InicializaRede();
    void SetTrainsParams();
    void SetTermCriteria();

    void CriaRede();
    Mat CriaLayes();

};

#endif // REDENEURAL_H
