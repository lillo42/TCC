#ifndef REDENEURAL_H
#define REDENEURAL_H


#include "Base/classificadorbase.h"
#include <opencv2/ml/ml.hpp>


//#define ATTRIBUTES 644
#define CLASSES 2                   //Number of distinct labels.


//http://www.nithinrajs.in/ocr-artificial-neural-network-opencv-part-3final-preprocessing/
class RedeNeural : public ClassificadorBase
{
public:
	RedeNeural();
    ~RedeNeural();

    void Load();

protected:
    void Treino(int quantidadePositiva);

 	 float CalculaPredict(Mat &image);
	 bool ValorAceitavel(float predict);
     void Salva();

private:
    CvANN_MLP mlp;
    CvANN_MLP_TrainParams params;
    CvTermCriteria criteria;

    int ATTRIBUTES;             //Number of pixels per sample.16X16;

    int activateFunc;

    void InicializaRede();
    void SetTrainsParams();
    void SetTermCriteria();
    void CriaRede();
    Mat CriaLayes();


};

#endif // REDENEURAL_H
