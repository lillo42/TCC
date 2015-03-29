#include "redeneural.h"

RedeNeural::RedeNeural()
{
    xml = "RedeNeural.xml";
    InicializaRede();
}

RedeNeural::~RedeNeural()
{

}

void RedeNeural::Treina(vector<Mat> &caracteristica, vector<Mat> &naoCarracteristica)
{
    Mat  trainData, responses;
    ClassificadorBase::TreinoBase(caracteristica,naoCarracteristica,trainData,responses);
    cout << "Comecou treino de verdade" << endl;
    cout << "Treinando..." << endl;
    mlp.train(trainData, responses, Mat(), Mat(), params);
    cout << "Salvando treino" << endl;
    mlp.save(xml.toStdString().c_str());
}

float RedeNeural::Predicao(Mat image)
{
    Mat temp;

    MatConstIterator_<float> it = image.begin<float>(), it_end = image.end<float>();

    for (; it != it_end; ++it)
        temp.push_back(*it);
    Mat retorno;
    return mlp.predict(temp,retorno);
}

void RedeNeural::InicializaRede()
{
    SetTermCriteria();
    SetTrainsParams();
    CriaRede();
}

void RedeNeural::SetTrainsParams()
{
    params.train_method = CvANN_MLP_TrainParams::RPROP;//CvANN_MLP_TrainParams::BACKPROP;
    params.bp_dw_scale = 0.1;//0.05f;
    params.bp_moment_scale = 0.1;//0.05f;
    params.term_crit = criteria;
}

void RedeNeural::SetTermCriteria()
{
    criteria.max_iter = 100;
    criteria.epsilon = 0.00001f;
    criteria.type = CV_TERMCRIT_ITER | CV_TERMCRIT_EPS;
}

void RedeNeural::CriaRede()
{
    Mat layers = CriaLayes();
    mlp.create(layers, CvANN_MLP::SIGMOID_SYM);
}

Mat RedeNeural::CriaLayes()
{
    Mat layers = cv::Mat(4, 1, CV_32SC1);

    layers.row(0) = cv::Scalar(2);
    layers.row(1) = cv::Scalar(10);
    layers.row(2) = cv::Scalar(15);
    layers.row(3) = cv::Scalar(1);

    // define the structure for the neural network (MLP)
    // The neural network has 3 layers.
    // - one input node per attribute in a sample so 256 input nodes
    // - 16 hidden nodes
    // - 10 output node, one for each class.

    //Mat layers(3, 1, CV_32S);
    //layers.at<int>(0, 0) = 256;//input layer
    //layers.at<int>(1, 0) = 16;//hidden layer
    //layers.at<int>(2, 0) = 10;//output layer
    return layers;
}

