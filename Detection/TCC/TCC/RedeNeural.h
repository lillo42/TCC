#pragma once

#pragma region OpenCV

//#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

#pragma endregion

#pragma region Std

#include <stdio.h>
#include <math.h>
#pragma endregion

using namespace cv;
using namespace std;

//http://docs.opencv.org/modules/ml/doc/neural_networks.html
//http://www.nithinrajs.in/ocr-artificial-neural-network-opencv-part-3final-preprocessing/
class RedeNeural
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

	string xml;

	void InicializaRede();
	void SetTrainsParams();
	void SetTermCriteria();

	void CriaRede();
	Mat CriaLayes();

	void AtribuiValorAoVetor(vector<vector <float> > & vetor, vector<Mat>& local);
};

