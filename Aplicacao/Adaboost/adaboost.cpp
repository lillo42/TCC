#include "adaboost.h"

AdaBoost::AdaBoost()
{
    xml = "Adaboost.xml";
}

AdaBoost::~AdaBoost()
{

}

void AdaBoost::Load()
{
    ClassificadorBase::Load();
    boost.load(xml.toStdString().c_str());
}

void AdaBoost::Treino(int quantidadePositiva)
{
    Size DIM(Features[1].size(),Features.size()); // (width, height)

    Mat trainData( DIM, CV_32FC1, Scalar::all(0) );
    Mat responses( Size(1, Features.size()), CV_32SC1, Scalar::all(0) );

    //  --------- Carrega os vetores em cv::Mat para a fase de Treino --------------

    for(std::vector<int>::size_type i = 0; i < Features.size(); i++)

        if ( i < quantidadePositiva )
            responses.at<int>(0,i) = 1;
        else
            responses.at<int>(0,i) = -1;


    for(int k = 0; k < trainData.rows; k++)
        for(int l = 0; l < trainData.cols; l++)
            trainData.at<float>(k,l) = Features[k][l];

    // -----------------------------------------------------------------------------

    Features.clear();

    if ( responses.depth() == TIPO_MAT && trainData.depth() == TIPO_MAT )
    {
        // As amostras estao armazenadas em linhas ...
        boost.train(trainData, CV_ROW_SAMPLE, responses); //, Mat(), Mat(), Mat(), Mat(), BoostParams(CvBoost::REAL, 100, 0.95, 5, false, 0));
        Salva();
    }
    else
        cout << "Os dados para treino ou resposta estão em formatos errado !";
}
	 
 	 
float AdaBoost::CalculaPredict(Mat &image)
{
  
  Mat temp;
  
  MatConstIterator_<float> it = image.begin<float>(), it_end = image.end<float>();

  for(; it != it_end; ++it) temp.push_back(*it);
  
  return boost.predict( temp, Mat(),Range::all(),false,true);
}
	 
bool AdaBoost::ValorAceitavel(float predict)
{
    return predict > 12;
}

void AdaBoost::Salva()
{
    ClassificadorBase::Salva();
    boost.save( xml.toStdString().c_str() );
}
