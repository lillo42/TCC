#include "LbpRN.h"


LbpRN::LbpRN()
{
	height = 32;
	width = 36;
	this->valorAceitavelPredicao = 10;
}


LbpRN::~LbpRN()
{
}

void LbpRN::Treina()
{
	vector<Mat> caracteristicas;
	vector<Mat> naoCaracteristicas;
	LbpBase::Treina(caracteristicas, naoCaracteristicas);
	rn.Treina(caracteristicas, naoCaracteristicas);
}

int LbpRN::CalculaPredicao(Mat &frame)
{
	return rn.Predicao(frame);
}
