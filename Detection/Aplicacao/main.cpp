#include <QCoreApplication>

#include <iostream>

#include "Adaboost/lbpadaboost.h"
#include "RedeNeural/lbpredeneural.h"
#include "Base/lbpbase.h"
#include "Cascade/lbpcascade.h"
#include "SVM/lbpsvm.h"

using namespace std;

void Treina(LbpBase&);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout <<  "Adaboost" << endl;
    LbpAdaBoost c;
    Treina(c);
    c.TesteHardCode();

//    cout << endl << endl << "Rede neural" << endl;
//    LbpRedeNeural rn;
//    Treina(rn);

//    cout << "Comecou teste hardcode" << endl;
//    c.TesteHardCode();

//    LbpCascade cs;
//    Treina(cs);
    //cs.TesteHardCode();

//    VideoCapture cap(0); // open the default camera
//    cap.set(CV_CAP_PROP_FRAME_WIDTH,320);
//    cap.set(CV_CAP_PROP_FRAME_HEIGHT,240);

//    Mat frame;

//    while(true)
//    {
//        Mat gray;
//        cap >>frame;
//        cvtColor(frame,gray,COLOR_BGR2GRAY);
//        equalizeHist( gray, gray );
//        cs.Detecta(frame,gray);
//        imshow( "faces", frame);
//        int c = waitKey(10);
//        if((char)c == 27 )
//            break;
//    }

//    LbpSVM svm;
//    Treina(svm);
//    svm.TesteHardCode();

    return a.exec();
}


void Treina(LbpBase &lbp)
{
    lbp.SetPastaCaracateristica("/home/tcc/Documents/GitHub/TCC/Database/Pessoa");
    lbp.SetNaoPastaCaracateristica("/home/tcc/Documents/GitHub/TCC/Database/NPessoa");

    cout << "Comecou o Treino" << endl;
    lbp.Treina();

    cout << "Terminou" << endl;
}
