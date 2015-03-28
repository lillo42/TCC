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
#include "RedeNeural.h"
#include "LbpBase.h"

#pragma endregion

class LbpRN : public LbpBase
{
public:
	LbpRN();
	~LbpRN();

	void Treina();
	bool AchouCaracteristica(Mat image, bool desenha);

protected:
	int virtual CalculaPredicao(Mat &frame);


private:
	RedeNeural rn;
};

