#include "redeneural.h"

RedeNeural::RedeNeural()
{
    xml = "RedeNeural.xml";
    InicializaRede();
}

RedeNeural::~RedeNeural()
{

}

void RedeNeural::Load()
{
    mlp.load(xml.toStdString().c_str());
}

void RedeNeural::InicializaRede()
{
    SetTermCriteria();
    SetTrainsParams();
    CriaRede();
}

void RedeNeural::SetTrainsParams()
{   
    params.train_method = CvANN_MLP_TrainParams::RPROP; //CvANN_MLP_TrainParams::BACKPROP;
//  params.bp_dw_scale = 0.05;//0.05f;
//  params.bp_moment_scale = 0.05;//0.05f;

    params.rp_dw0 = 0.01;
    params.rp_dw_plus = 1.2;
    params.rp_dw_minus = 0.05;
    params.rp_dw_min = FLT_EPSILON;
    params.rp_dw_max = 500;
    params.term_crit = criteria;
}

void RedeNeural::SetTermCriteria()
{
    criteria.max_iter = 1000;
    criteria.epsilon = 0.01;
    criteria.type = CV_TERMCRIT_ITER + CV_TERMCRIT_EPS;
}

void RedeNeural::CriaRede()
{
    Mat layers = CriaLayes();
    activateFunc = CvANN_MLP::SIGMOID_SYM; //CvANN_MLP::IDENTITY; // CvANN_MLP::GAUSSIAN
    mlp.create(layers,activateFunc);
}

Mat RedeNeural::CriaLayes()
{
    // define the structure for the neural network (MLP)
    // The neural network has 3 layers.
    // - one input node per attribute in a sample so 256 input nodes
    // - 16 hidden nodes
    // - 10 output node, one for each class.

    Mat layers(4, 1, CV_32S);
    layers.at<int>(0, 0) = ATTRIBUTES;//input layer
    layers.at<int>(1, 0) = 50;//hidden layer
    layers.at<int>(2, 0) = 50;//hidden layer
    layers.at<int>(3, 0) = CLASSES;//output layer
    return layers;
}

void RedeNeural::Treino(int quantidadePositiva)
{
    Size DIM(Features[1].size(),Features.size());

    Mat trainData( DIM, TIPO_MAT, Scalar::all(0) );
    Mat responses( Size(2, Features.size()), TIPO_MAT, Scalar::all(0) );

    //  --------- Carrega os vetores em cv::Mat para a fase de Treino --------------

    for(int i = 0; i < Features.size(); i++)
    {
        if ( i < quantidadePositiva )
            responses.at<float>(i,0) = 1.0;
        else
            responses.at<float>(i,1) = 1.0;
    }


    for(int k = 0; k < trainData.rows; k++)
        for(int l = 0; l < trainData.cols; l++)
            trainData.at<float>(k,l) = Features[k][l];

    // -----------------------------------------------------------------------------

    Features.clear();

   if ( responses.depth() == TIPO_MAT && trainData.depth() == TIPO_MAT )
    {
        // As amostras estao armazenadas em linhas ...
        //boost.train(trainData, CV_ROW_SAMPLE, responses); //, Mat(), Mat(), Mat(), Mat(), BoostParams(CvBoost::REAL, 100, 0.95, 5, false, 0));
        int flag = 0;//CvANN_MLP::NO_OUTPUT_SCALE;
        mlp.train(trainData,responses, Mat(),Mat(),params,flag);
        //boost.save( xml.toStdString().c_str() );
        mlp.save(xml.toStdString().c_str());
    }
    else
       cout << "Os dados para treino ou resposta estão em formatos errado !";
}

	 
 	 
float RedeNeural::CalculaPredict(Mat &image)
{
  
   vector<float> temp;

  MatConstIterator_<float> it = image.begin<float>(), it_end = image.end<float>();

  for(; it != it_end; ++it) temp.push_back(*it);

  Mat test(1,temp.size(),TIPO_MAT);

  for(int k = 0; k < test.rows; k++)
    for(int l = 0; l < test.cols; l++)
    test.at<float>(k,l) = temp[l];

  Mat response(1,CLASSES,TIPO_MAT);


  mlp.predict(test,response);

  int maxIndex = 0;
  float value=0.0f;
  float maxValue = response.at<float>(0,0);

  for(int index=1; index < CLASSES; index++)
  {
    value = response.at<float>(0,index);
    if(value > maxValue)
    {
      maxValue = value;
      maxIndex = index;
    }
  }
  
  return maxIndex;
}
	 
bool RedeNeural::ValorAceitavel(float predict)
{
     return predict == 0;
}
