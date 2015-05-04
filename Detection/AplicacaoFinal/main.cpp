#include <QCoreApplication>

#include "Base/classificadorbase.h"
#include "Adaboost/adaboost.h"
#include "RN/redeneural.h"

using namespace std;

void Treino(ClassificadorBase&);
void TesteHardCode(ClassificadorBase&);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    cout << "Adaboost" << endl;
//    AdaBoost ad;
//    Treino(ad);
//    TesteHardCode(ad);

     cout << "Rede Neural" << endl;
     RedeNeural rn;
     Treino(rn);
     TesteHardCode(rn);

    return a.exec();
}


void Treino(ClassificadorBase &c)
{
    c.SetPastaCaracateristica("/home/tcc/Documents/DataBase/P");
    c.SetNaoPastaCaracateristica("/home/tcc/Documents/DataBase/N");

    c.Treino();
}

void TesteHardCode(ClassificadorBase &c)
{
    c.SetPastaTeste("/home/tcc/Documents/DataBase/TT");
    c.SetPastaSalva("/home/tcc/Documents/DataBase/R");
    c.Load();
    c.TesteTreino();
}
