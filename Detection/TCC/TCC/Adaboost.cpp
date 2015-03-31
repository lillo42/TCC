#include "Adaboost.h"


Adaboost::Adaboost()
{
	xml = "AdaBoost.xml";
}

Adaboost::~Adaboost()
{

}

void Adaboost::Treina(vector<Mat> &caracteristica, vector<Mat> &naoCarracteristica)
{
	Mat trainData, responses;
	ClassificadorBase::TreinoBase(caracteristica, naoCarracteristica, trainData, responses);

	cout << "Comecou treino de verdade" << endl;
	if (responses.depth() == CV_32SC1 && trainData.depth() == CV_32FC1)
	{
		// As amostras estao armazenadas em linhas ...
		cout << "Treinando..." << endl;
		boost.train(trainData, CV_ROW_SAMPLE, responses); //, Mat(), Mat(), Mat(), Mat(), BoostParams(CvBoost::REAL, 100, 0.95, 5, false, 0));
		cout << "Salvando treino" << endl;
		boost.save(xml.c_str());
	}
}

float Adaboost::Predicao(Mat image)
{
	Mat temp;

	MatConstIterator_<float> it = image.begin<float>(), it_end = image.end<float>();

	for (; it != it_end; ++it)
		temp.push_back(*it);

	return boost.predict(temp, Mat(), Range::all(), false, true);
}

void Adaboost::LoadBoost()
{
	boost.load(xml.c_str());
}