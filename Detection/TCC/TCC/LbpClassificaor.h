#pragma once

#pragma region OpenCV

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv2\core\core.hpp>

#pragma endregion



#pragma region STD

#include <string>

#pragma endregion

#pragma region MinhasBibliotecas

#include "Leitor.h"
#include "LBP.h"
#include "Classificador.h"

#pragma endregion


using namespace cv;
using namespace std;

struct detF {
	float predicao;     // Armazena a predicao, para comparare elimiar falsos positivos por distância
	Point ponto;        // Localizacao a Face
} typedef DetectFeatures;

class LbpClassificaor
{
public:
	LbpClassificaor();
	~LbpClassificaor();

	void Treina();
	bool AchouCaracteristica(Mat image, bool desenha);
	

	void SetPastaCaracateristica(string pastaCaracateristica);
	string GetPastaCaracateristica();

	void SetNaoPastaCaracateristica(string pastaNaoCaracateristica);
	string GetNaoPastaCaracateristica();

private:
	string pastaCaracateristica;
	string pastaNaoCaracateristica;

	LBP lbp;
	Leitor ler;
	Classificador boost;

	vector<DetectFeatures> features;

	int height;
	int width;


	void AplicaLBP(vector<Mat>& aplica);
	vector<Mat> AplicaLBPImage(Mat &image);

	void RemoveReptidos();

	void DesenhaRetangulo(Mat &imagem);
	
};

