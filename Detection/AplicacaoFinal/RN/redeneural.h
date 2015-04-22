#ifndef REDENEURAL_H
#define REDENEURAL_H


#include "Base/classificadorbase.h"
#include <opencv2/ml/ml.hpp>

//http://www.nithinrajs.in/ocr-artificial-neural-network-opencv-part-3final-preprocessing/
class RedeNeural : public ClassificadorBase
{
public:
    RedeNeural();
    ~RedeNeural();

    void Treino();
    int Teste(Mat &Query);
    void Load();

protected:
    void Treino(int quantidadePositiva);

private:
    CvANN_MLP mlp;
    CvANN_MLP_TrainParams params;
    CvTermCriteria criteria;

    void InicializaRede();
    void SetTrainsParams();
    void SetTermCriteria();

    void CriaRede();
    Mat CriaLayes();

   void InverteLinhaColuna(Mat &original, Mat &retorno);

};

#endif // REDENEURAL_H
