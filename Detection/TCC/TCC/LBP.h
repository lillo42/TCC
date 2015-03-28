#pragma once

#pragma region OpenCV

#include <opencv/cv.h>
#include <opencv/highgui.h>
//#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#pragma endregion

#pragma region Std

#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

#pragma endregion

using namespace cv;
using namespace std;

class LBP
{
public:
	LBP();
	~LBP();

	void AplicaLBP(Mat& origem, Mat& destino, int raio, int vizinho);
};

