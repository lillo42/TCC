#ifndef CASCADE_H
#define CASCADE_H


#include "Base/classificadorbase.h"

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace cv;
using namespace std;

class Cascade : public ClassificadorBase
{
public:
    Cascade();
    ~Cascade();

    void Detecta(Mat &image, vector<Rect> &faces);
    void LoadBoost();

private:
    CascadeClassifier faces;
};

#endif // CASCADE_H
