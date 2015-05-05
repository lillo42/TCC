#ifndef REDENEURAL_H
#define REDENEURAL_H


#include "Base/classificadorbase.h"
#include <opencv2/ml/ml.hpp>
#include "ArquivoTxt/arquivotexto.h"
#include "ArquivoTxt/eredeneural.h"

#define ATTRIBUTES 644              //Number of pixels per sample.16X16
#define CLASSES 2                   //Number of distinct labels.


//http://www.nithinrajs.in/ocr-artificial-neural-network-opencv-part-3final-preprocessing/
class RedeNeural : public ClassificadorBase
{
public:
    RedeNeural();
    ~RedeNeural();

    void Treino();
    int Teste(Mat &Query);
    void TesteHardCodeMonitorado(QString nomeArquivo);
    void TesteTreino();
    void CarregaConfiguracao(QString arquivoConfiguracao);
    void Load();

protected:
    void Treino(int quantidadePositiva);

private:
    CvANN_MLP mlp;
    CvANN_MLP_TrainParams params;
    CvTermCriteria criteria;

    vector< vector<float> > testRN;

    void PreencheParametro();

    void InicializaRede();
    void SetTrainsParams();
    void SetTermCriteria();

    void CriaRede();
    Mat CriaLayes();

    int valorTestePessoas;
    int valorTesteNPessoas;

    int tempoTotalTreino;
    int activateFunc;

    ERedeNeural salva;

};

#endif // REDENEURAL_H
