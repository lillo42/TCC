#pragma once

#pragma region OpenCV

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>

#pragma endregion



#pragma region STD

#include <iostream>
#include <string>

#pragma endregion

#pragma region MinhasBibliotecas

#include "Leitor.h"
#include "LBP.h"

#pragma endregion


using namespace cv;
using namespace std;

#define WIDTH 128 // cols
#define HEIGHT 128 // rows


struct detF {
	float predicao;     // Armazena a predicao, para comparare elimiar falsos positivos por distância
	Point ponto;        // Localizacao a Face
} typedef DetectFeatures;

class LbpBase
{
public:
	LbpBase();
	~LbpBase();

	bool AchouCaracteristica(Mat image, bool desenha);

	void SetPastaCaracateristica(string pastaCaracateristica);
	string GetPastaCaracateristica();

	void SetNaoPastaCaracateristica(string pastaNaoCaracateristica);
	string GetNaoPastaCaracateristica();

protected:
	string pastaCaracateristica;
	string pastaNaoCaracateristica;

	LBP lbp;
	Leitor ler;
	vector<DetectFeatures> features;

	int height;
	int width;
	int valorAceitavelPredicao;

	void AplicaLBP(vector<Mat>& aplica);
	void AplicaLBPCaracteristica(vector<Mat> &aplica);

	vector<Mat> AplicaLBPImage(Mat &image);

	void virtual RemoveReptidos();

	void virtual DesenhaRetangulo(Mat &imagem);

	int virtual CalculaPredicao(Mat &frame)
	{
		return 0;
	}

	void Treina(vector<Mat> &caracteristicas, vector<Mat> &naoCaracteristicas);
};

