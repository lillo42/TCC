#include "RedeNeural.h"


RedeNeural::RedeNeural()
{
	InicializaRede();
}


RedeNeural::~RedeNeural()
{

}

void RedeNeural::Treina(vector<Mat> &caracteristica, vector<Mat> &naoCarracteristica)
{
	vector<vector <float> > features;
	AtribuiValorAoVetor(features, caracteristica);
	AtribuiValorAoVetor(features, naoCarracteristica);

	if (features.size() < 1)
		return;

	Size dim(features[1].size(), features.size()); // (width, height)
	Mat trainData(dim, CV_32FC1, Scalar::all(0));
	Mat responses(Size(1, features.size()), CV_32SC1, Scalar::all(0));

	// -------- - Carrega os vetores em cv::Mat para a fase de Treino--------------
	for (int i = 0; i < features.size(); i++)
	{
		if (i < caracteristica.size())
			responses.at<int>(i,0) = 1;
		else
			responses.at<int>(i,0) = -1;
	}

	for (int k = 0; k < trainData.rows; k++)
		for (int l = 0; l < trainData.cols; l++)
			trainData.at<float>(k, l) = features[k][l];

	// -----------------------------------------------------------------------------

	features.clear();

	mlp.train(trainData, responses, Mat(), Mat(), params);
	mlp.save(xml.c_str());
}

float RedeNeural::Predicao(Mat image)
{
	Mat temp;

	MatConstIterator_<float> it = image.begin<float>(), it_end = image.end<float>();

	for (; it != it_end; ++it)
		temp.push_back(*it);

	return mlp.predict(temp, Mat());
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

void RedeNeural::AtribuiValorAoVetor(vector<vector <float> > & vetor, vector<Mat>& local)
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