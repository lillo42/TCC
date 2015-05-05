#include <QCoreApplication>

#include "Base/classificadorbase.h"
#include "Adaboost/adaboost.h"
#include "RN/redeneural.h"

using namespace std;

void Treino(ClassificadorBase&);
void TesteTreino(ClassificadorBase&);
void TesteHardCode(ClassificadorBase&);
void TreinoMonitorado(ClassificadorBase&);
void Carrega(ClassificadorBase&);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    cout << "Adaboost" << endl;
//    AdaBoost ad;
//    Treino(ad);
//    TesteHardCode(ad);

     cout << "Rede Neural" << endl;
     RedeNeural rn;
     //Treino(rn);
     Carrega(rn);
     TreinoMonitorado(rn);

    return a.exec();
}


void Treino(ClassificadorBase &c)
{
    c.SetPastaCaracateristica("/home/tcc/Documents/DataBase/P");
    c.SetNaoPastaCaracateristica("/home/tcc/Documents/DataBase/N");

    c.Treino();
}

void TesteTreino(ClassificadorBase &c)
{
    c.SetPastaTeste("/home/tcc/Documents/DataBase/TT");
    c.SetPastaSalva("/home/tcc/Documents/DataBase/R");
    c.Load();
    c.TesteTreino();
}

void TesteHardCode(ClassificadorBase &c)
{
    c.SetPastaTeste("/home/tcc/Documents/DataBase/T");
    c.SetPastaSalva("/home/tcc/Documents/DataBase/R");
    c.Load();
    c.TesteHardCode();
}

void TreinoMonitorado(ClassificadorBase &c)
{
    c.SetPastaTeste("/home/tcc/Documents/DataBase/T");
    c.SetPastaSalva("/home/tcc/Documents/DataBase/RC");
    //c.Load();
    //c.TesteHardCodeMonitorado();
}

void Carrega(ClassificadorBase &c)
{

}
