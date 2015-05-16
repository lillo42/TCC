#include <QCoreApplication>

#include "Base/classificadorbase.h"
#include "Adaboost/adaboost.h"
#include "RN/redeneural.h"

using namespace std;

void Treino(ClassificadorBase&);
void TesteTreino(ClassificadorBase&);
void TesteHardCode(ClassificadorBase&);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RedeNeural c;
    //AdaBoost c;

    Treino(c);
    TesteTreino(c);
    TesteHardCode(c);

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
