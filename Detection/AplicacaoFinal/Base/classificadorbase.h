#ifndef CLASSIFICADORBASE_H
#define CLASSIFICADORBASE_H


#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>

#include <stdio.h>
#include <iostream>
#include <string>
#include <time.h> /* clock_t, clock, CLOCKS_PER_SEC */

#include <QString>
#include <QDir>

#include "LBP/lbp.h"

using namespace cv;
using namespace std;


#define WIDTH 25 // cols
#define HEIGHT 30 // rows

#define WIDTH_ANDA 6 //cols
#define HEIGHT_ANDA 6 //rows

#define RAIO 1
#define VIZINHO 8

#define TIPO_MAT CV_32F


struct detF {
    float predicao;     // Armazena a predicao, para comparare elimiar falsos positivos por distancia
    Point ponto;        // Localizacao a Face
} typedef DetectFace;

class ClassificadorBase
{
public:
    ClassificadorBase();
    ~ClassificadorBase();

    virtual void Treino();
    virtual void TesteHardCode();
    virtual void TesteHardCodeMonitorado(QString nomeArquivo);
    virtual void CarregaConfiguracao(QString arquivoConfiguracao);
    virtual int Teste(Mat &Query);
    virtual void Load();

    void SetPastaCaracateristica(QString pastaCaracateristica);
    QString GetPastaCaracateristica();

    void SetNaoPastaCaracateristica(QString pastaNaoCaracateristica);
    QString GetNaoPastaCaracateristica();

    void SetPastaTeste(QString pastaTeste);
    QString GetPastaTeste();

    void SetPastaSalva(QString pastaSalva);
    QString GetPastaSalva();

    virtual void TesteTreino();

protected:
    QString pastaCaracateristica;
    QString pastaNaoCaracateristica;
    QString pastaTeste;
    QString pastaSalva;
    QString xml;

    Lbp lbp;
    vector<vector <float> > Features;
    vector<DetectFace> faces;

    void extraiCaracteristicas(Mat &Query );

    virtual void Treino(int quantidadePositiva);    

    const string currentDateTime();

    void eliminaRepetidos(int &quantidade);
    void desenhaRetangulo(Mat &imagem);

    void LerImagemPasta(vector<Mat>& retorno, QString pasta);
    QStringList GetAllFilesNamesWithinFolder(QDir dir);
};

#endif // CLASSIFICADORBASE_H
