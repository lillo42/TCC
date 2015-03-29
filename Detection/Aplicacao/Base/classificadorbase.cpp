#include "classificadorbase.h"

ClassificadorBase::ClassificadorBase()
{

}

ClassificadorBase::~ClassificadorBase()
{

}

void ClassificadorBase::Treina(vector<Mat> &caracteristica, vector<Mat> &naoCarracteristica)
{

}


float ClassificadorBase::Predicao(Mat image)
{

}

void ClassificadorBase::LoadBoost()
{

}

void ClassificadorBase::TreinoBase(vector<Mat> &caracteristica, vector<Mat> &naoCarracteristica, Mat &trainData, Mat &responses)
{
    cout << "Comecando o treino" <<endl;
    vector<vector <float> > features;

    cout << "Atribuindo valor de carateristica" << endl;
    AtribuiValorAoVetor(features, caracteristica);

    cout << "Atribuindo valor de Nao carateristica" << endl;
    AtribuiValorAoVetor(features, naoCarracteristica);

    if (features.size() < 1)
        return;

    cout << "Tamanho vetor de features: " << features.size() << endl;
    cout << "Tamanho vetor de caracteristica: " << caracteristica.size() << endl;
    cout << "Tamanho vetor de naoCaracteristica: " << naoCarracteristica.size() << endl;

    Size dim(features[1].size(), features.size()); // (width, height)
    trainData =  Mat(dim, CV_32FC1, Scalar::all(0));
    responses = Mat(Size(1, features.size()), CV_32SC1, Scalar::all(0));

    cout << "Carregando valores" << endl;
    // -------- - Carrega os vetores em cv::Mat para a fase de Treino--------------
    for (int i = 0; i < features.size(); i++)
    {

        if (i < caracteristica.size())
            responses.at<int>(i, 0) = 1;
        else
            responses.at<int>(i,0) = -1;
    }

    cout << "Terminou de carregar o vetor" << endl;
    cout << "Carregando o treino" << endl;
    for (int k = 0; k < trainData.rows; k++)
        for (int l = 0; l < trainData.cols; l++)
            trainData.at<float>(k, l) = features[k][l];

    // -----------------------------------------------------------------------------

    features.clear();
}

void ClassificadorBase::AtribuiValorAoVetor(vector<vector<float> > &vetor, vector<Mat> &local)
{
    for (unsigned i = 0; i < local.size(); i++)
    {
        Mat lbp = local.at(i);

        vector<float> temp;
        MatConstIterator_<float> it = lbp.begin<float>(), it_end = lbp.end<float>();

        for (; it != it_end; ++it)
            temp.push_back(*it);

        vetor.push_back(temp);

        temp.empty();
    }
}

