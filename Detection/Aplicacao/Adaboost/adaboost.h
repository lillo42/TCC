#ifndef ADABOOST_H
#define ADABOOST_H

#include "Base/classificadorbase.h"

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;

class Adaboost : public ClassificadorBase
{
public:
    Adaboost();
    ~Adaboost();

    void Treina(vector<Mat> &caracteristica, vector<Mat> &naoCarracteristica);

    float Predicao(Mat image);

    void LoadBoost();

private:

    CvBoost boost;

};

#endif // ADABOOST_H
