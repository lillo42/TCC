#include <QCoreApplication>

#include <iostream>

#include "Adaboost/lbpadaboost.h"
#include "RedeNeural/lbpredeneural.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LbpAdaBoost c;
    c.SetPastaCaracateristica("C:/Users/Rafel/Documents/GitHub/TCC/Database/Pessoa");
    c.SetNaoPastaCaracateristica("C:/Users/Rafel/Documents/GitHub/TCC/Database/NPessoa");

    cout << "Come�ou o Treino" << endl;
    c.Treina();

    cout << "Terminou" << endl;

    return a.exec();
}
