#include "lbpredeneural.h"

LbpRedeNeural::LbpRedeNeural()
{
    height = 32;
    width = 36;
    this->valorAceitavelPredicao = 10;
}

LbpRedeNeural::~LbpRedeNeural()
{

}

void LbpRedeNeural::Treina()
{
    vector<Mat> caracteristicas;
    vector<Mat> naoCaracteristicas;
    LbpBase::Treina(caracteristicas, naoCaracteristicas);
    rn.Treina(caracteristicas, naoCaracteristicas);
}

int LbpRedeNeural::CalculaPredicao(Mat &frame)
{
    return rn.Predicao(frame);
}

