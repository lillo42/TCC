#ifndef LBPBASE_H
#define LBPBASE_H

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>


#include <iostream>
#include <string>

#include <QString>

#include "Outros/lbp.h"
#include "Outros/leitor.h"

using namespace cv;
using namespace std;

#define WIDTH 128 // cols
#define HEIGHT 128 // rows


struct detF {
    float predicao;     // Armazena a predicao, para comparare elimiar falsos positivos por dist�ncia
    Point ponto;        // Localizacao a Face
} typedef DetectFeatures;

class LbpBase
{
public:
    LbpBase();
    ~LbpBase();


    bool AchouCaracteristica(Mat &image, bool desenha);

    void SetPastaCaracateristica(QString pastaCaracateristica);
    QString GetPastaCaracateristica();

    void SetNaoPastaCaracateristica(QString pastaNaoCaracateristica);
    QString GetNaoPastaCaracateristica();
protected:
    QString pastaCaracateristica;
    QString pastaNaoCaracateristica;

    LBP lbp;
    Leitor ler;
    vector<DetectFeatures> features;

    int height;
    int width;
    int valorAceitavelPredicao;

    void AplicaLBP(vector<Mat>& aplica);
    void AplicaLBPCaracteristica(vector<Mat> &aplica);

    vector<Mat> AplicaLBPImage(Mat &image);

    void virtual RemoveReptidos();

    void virtual DesenhaRetangulo(Mat &imagem);

    int virtual CalculaPredicao(Mat &frame)
    {
        return 0;
    }

    void Treina(vector<Mat> &caracteristicas, vector<Mat> &naoCaracteristicas);
};

#endif // LBPBASE_H
