#pragma once

#pragma region OpenCV

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

#pragma endregion

#pragma region Std

#include <vector>
#include <stdlib.h>
#include <stdio.h>

#pragma endregion

#include "ClassificadorBase.h"


using namespace cv;
using namespace std;

class Adaboost: public ClassificadorBase
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

