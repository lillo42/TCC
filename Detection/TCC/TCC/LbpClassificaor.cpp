#include "LbpAdaBoost.h"


LbpAdaBoost::LbpAdaBoost()
{
	height = 112;
	width = 92;
	this->valorAceitavelPredicao = 10;
}


LbpAdaBoost::~LbpAdaBoost()
{
}

void LbpAdaBoost::Treina()
{
	vector<Mat> caracteristicas;
	vector<Mat> naoCaracteristicas;
	LbpBase::Treina(caracteristicas, naoCaracteristicas);
	boost.Treina(caracteristicas, naoCaracteristicas);
}


void LbpAdaBoost::TesteHardCode()
{
	vector<Mat> teste;
	string pasta = "C:/Users/Rafel/Documents/GitHub/TCC/Database/Teste";
	string salva = "C:/Users/Rafel/Documents/GitHub/TCC/Database/Resultado/T";
	string extensao = ".jpg";
	ler.LerImagemPasta(teste, pasta);

	for (int i = 0; i < teste.size(); i++)
	{
		cout << "Teste imagem: " << i << endl;
		Mat frame = teste.at(i);
		bool foi = AchouCaracteristica(frame, true);
		if (foi)
		{
			cout << "Achou rosto na imagem: " << i << endl;
			string local = salva + to_string(i) +extensao;
			imwrite(local, frame);
		}
		else
		{
			cout << "Nao achou rosto na imagem: " << i << endl;
		}
	}
}

int LbpAdaBoost::CalculaPredicao(Mat &frame)
{
	return boost.Predicao(frame);
}