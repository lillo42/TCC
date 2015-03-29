#include "lbpadaboost.h"

LbpAdaBoost::LbpAdaBoost()
{
    height = 112;
    width = 92;
    this->valorAceitavelPredicao = 10;
}

LbpAdaBoost::~LbpAdaBoost()
{

}

void LbpAdaBoost::Treina()
{
    vector<Mat> caracteristicas;
    vector<Mat> naoCaracteristicas;
    LbpBase::Treina(caracteristicas, naoCaracteristicas);
    boost.Treina(caracteristicas, naoCaracteristicas);
}

int LbpAdaBoost::CalculaPredicao(Mat &frame)
{
    return boost.Predicao(frame);
}

