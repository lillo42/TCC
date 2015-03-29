#ifndef LBP_H
#define LBP_H


#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdio.h>
#include <math.h>

using namespace cv;
using namespace std;

class LBP
{
public:
    LBP();
    ~LBP();

   void AplicaLBP(Mat& origem, Mat& destino, int raio, int vizinho);
};

#endif // LBP_H
