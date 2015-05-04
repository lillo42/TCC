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

    void Treino();
    int Teste(Mat &Query);
    void Load();

protected:
    void Treino(int quantidadePositiva);

private:
     CvBoost boost;
};

#endif // ADABOOST_H
