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
#include <QDirIterator>
#include <QDebug>

#include "LBP/lbp.h"

using namespace cv;
using namespace std;

//#define WIDTH  25 // cols 25
//#define HEIGHT  30 // rows 30

//#define WIDTH_ANDA 6 //cols 6
//#define HEIGHT_ANDA 6  //rows 6
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
    virtual void TesteTreino();
    virtual void Load();

    void SetPastaCaracateristica(QString pastaCaracateristica);
    QString GetPastaCaracateristica();

    void SetNaoPastaCaracateristica(QString pastaNaoCaracateristica);
    QString GetNaoPastaCaracateristica();

    void SetPastaTeste(QString pastaTeste);
    QString GetPastaTeste();

    void SetPastaSalva(QString pastaSalva);
    QString GetPastaSalva();

protected:
    QString pastaCaracateristica;
    QString pastaNaoCaracateristica;
    QString pastaTeste;
    QString pastaSalva;
    QString xml;

    int WIDTH; // cols 25
    int HEIGHT; // rows 30

    int WIDTH_ANDA; //cols 6
    int HEIGHT_ANDA; //rows 6

    Lbp lbp;
    vector<vector <float> > Features;
    vector<DetectFace> faces;

    void extraiCaracteristicas(Mat &Query );

    virtual void Teste(Mat &query, int &positivo, int &negativo);

    virtual void Treino(int quantidadePositiva);    

    virtual float CalculaPredict(Mat &image);
    virtual bool ValorAceitavel(float predict);

    const string currentDateTime();

    void eliminaRepetidos(int &quantidade);
    void desenhaRetangulo(Mat &imagem);

    virtual void Salva();

    void LerImagemPasta(vector<Mat>& retorno, QString pasta);
    void GetAllFilesNamesWithinFolder(QDir dir, QStringList &retorno);
};

#endif // CLASSIFICADORBASE_H
