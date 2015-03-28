#pragma once

#pragma region OpenCV

#include <opencv/cv.h>
//#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>

#pragma endregion



#pragma region STD

#include <string>

#pragma endregion

#pragma region MinhasBibliotecas

#include "Leitor.h"
#include "LBP.h"
#include "Classificador.h"
#include "LbpBase.h"

#pragma endregion


using namespace cv;
using namespace std;

//struct detF {
//	float predicao;     // Armazena a predicao, para comparare elimiar falsos positivos por distância
//	Point ponto;        // Localizacao a Face
//} typedef DetectFeatures;

class LbpClassificador : public LbpBase
{
public:
	LbpClassificador();
	~LbpClassificador();

	void Treina();
	bool AchouCaracteristica(Mat image, bool desenha);

protected:
	int virtual CalculaPredicao(Mat &frame);


private:
	Classificador boost;
	
};

