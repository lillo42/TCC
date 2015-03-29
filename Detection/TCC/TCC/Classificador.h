#pragma once

#pragma region OpenCV

#include <opencv/cv.h>
//#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

#pragma endregion

#pragma region Std

#include <vector>
#include <stdlib.h>
#include <stdio.h>

#pragma endregion


using namespace cv;
using namespace std;

class Classificador
{
public:
	Classificador();
	~Classificador();

	void Treina(vector<Mat> &caracteristica, vector<Mat> &naoCarracteristica);

	float Predicao(Mat image);

private:
	string xml;
	CvBoost boost;

	void LoadBoost();

	void AtribuiValorAoVetor(vector<vector <float> > & vetor, vector<Mat>& local);
};

