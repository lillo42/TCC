#pragma once
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>
#include <stdlib.h>
#include <stdio.h>


using namespace cv;
using namespace std;

class ClassificadorBase
{
public:
	ClassificadorBase();
	~ClassificadorBase();

	void virtual Treina(vector<Mat> &caracteristica, vector<Mat> &naoCarracteristica);
	float virtual Predicao(Mat image);
	void virtual LoadBoost();

protected:
	string xml;

	void TreinoBase(vector<Mat> &caracteristica, vector<Mat> &naoCarracteristica, Mat &trainData, Mat &responses);

	void virtual AtribuiValorAoVetor(vector<vector <float> > & vetor, vector<Mat>& local);

};