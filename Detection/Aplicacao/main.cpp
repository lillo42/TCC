#include <QCoreApplication>

#include <iostream>

#include "Adaboost/lbpadaboost.h"
#include "RedeNeural/lbpredeneural.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LbpAdaBoost c;
    c.SetPastaCaracateristica("/home/tcc/Documents/GitHub/TCC/Database/Pessoa");
    c.SetNaoPastaCaracateristica("/home/tcc/Documents/GitHub/TCC/Database/NPessoa");

    cout << "Come�ou o Treino" << endl;
    c.Treina();

    cout << "Terminou" << endl;
    c.TesteHardCode();

    return a.exec();
}
