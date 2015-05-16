#ifndef ADABOOST_H
#define ADABOOST_H


#include "Base/classificadorbase.h"
#include <stdio.h>


using namespace std;

class AdaBoost : public ClassificadorBase
{
public:
    AdaBoost();
    ~AdaBoost();

    void Load();

protected:
    void Treino(int quantidadePositiva);

 	 float CalculaPredict(Mat &image);
	 bool ValorAceitavel(float predict);

private:
     CvBoost boost;


	 void InicializaRede();
    void SetTrainsParams();
    void SetTermCriteria();

    void CriaRede();
    Mat CriaLayes();


};

#endif // ADABOOST_H
