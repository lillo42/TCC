#ifndef SVMC_H
#define SVMC_H


#include "Base/classificadorbase.h"

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


class SVMC : public ClassificadorBase
{
public:
    SVMC();
    ~SVMC();

    void Treina(vector<Mat> &caracteristica, vector<Mat> &naoCarracteristica);

    float Predicao(Mat image);

    void LoadBoost();

private:
    CvSVM svm;
    CvSVMParams parametro;

    void LoadParametros();
};

#endif // SVM_H
