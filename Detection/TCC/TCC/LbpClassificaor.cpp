#include "LbpClassificador.h"


LbpClassificador::LbpClassificador()
{
	height = 32;
	width = 36;
	this->valorAceitavelPredicao = 10;
}


LbpClassificador::~LbpClassificador()
{
}

void LbpClassificador::Treina()
{
	vector<Mat> caracteristicas;
	vector<Mat> naoCaracteristicas;
	LbpBase::Treina(caracteristicas, naoCaracteristicas);
	boost.Treina(caracteristicas, naoCaracteristicas);
}

int LbpClassificador::CalculaPredicao(Mat &frame)
{
	return boost.Predicao(frame);
}

//bool LbpClassificador::AchouCaracteristica(Mat image, bool desenha)
//{
//	bool retorno = false;
//	Mat ROI(Size(width, height), CV_32FC1, Scalar::all(0));
//	Mat LBP;
//	DetectFeatures df;
//	features.clear();
//	Point roi;  // Armazena as coordenadas das Features
//	Size size(width, height);
//	Mat ROI_TRUE = Mat::zeros(size, CV_32FC1);
//
//	for (int i = 0; i <= image.rows - height; i++)
//	{
//		roi.y = i;
//
//		for (int j = 0; j <= image.cols - width; j++)
//		{
//			roi.x = j;
//
//			image.operator ()(Rect(roi.x, roi.y, width, height)).convertTo(ROI, CV_32FC1, 1, 0);
//			resize(ROI, ROI_TRUE, size);
//			lbp.AplicaLBP(ROI_TRUE, LBP, 1, 8);
//
//			Mat temp;
//
//			MatConstIterator_<float> it = LBP.begin<float>(), it_end = LBP.end<float>();
//
//			for (; it != it_end; ++it)
//				temp.push_back(*it);
//
//
//			int predicao = boost.Predicao(temp);
//
//			if (predicao > 15)
//			{
//				retorno = true;
//				df.predicao = predicao; df.ponto = roi;
//				features.push_back(df);
//			}
//		}
//	}
//
//	if (desenha)
//	{
//		RemoveReptidos();
//		DesenhaRetangulo(image);
//	}
//	return retorno;
//}




//void LbpClassificador::RemoveReptidos()
//{
//	unsigned i = 0;
//
//	while (i + 1 < features.size())
//	{
//		if ((features[i + 1].ponto.x - features[i].ponto.x <= width) &&
//			(features[i + 1].ponto.y - features[i].ponto.y <= height))
//		{
//
//			if (features[i + 1].predicao > features[i].predicao)
//				features.erase(features.begin() + i);
//			else
//				features.erase(features.begin() + 1 + i);
//		}
//		else
//			i++;
//	}	
//}

//void LbpClassificador::DesenhaRetangulo(Mat &imagem)
//{
//	Point center;
//	int radius, scale = 0.264583333; // Converte para mm
//
//	for (unsigned long i = 0; i < features.size(); i++)
//	{
//		rectangle(imagem, (Rect(features[i].ponto.x,
//			features[i].ponto.y, width + 1, height + 1)),
//			CV_RGB(255, 255, 0), 1.5);
//
//		// comparar distancia entre os rec, e verficar a media.... para eliminar falsos positivos.
//		center.x = features[i].ponto.x + width / 2;
//		center.y = features[i].ponto.y + height / 2;
//		radius = cvRound((width + height)*0.25*scale);
//		circle(imagem, center, radius, CV_RGB(0, 255, 0), 2);
//	}
//}