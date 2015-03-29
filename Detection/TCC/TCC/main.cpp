#include <iostream>
#include "LbpClassificador.h"
#include "LbpRN.h"

using namespace std;

int main(int argc, char** argv)
{
	LbpClassificador c;
	c.SetPastaCaracateristica("C:/Users/Rafel/Documents/GitHub/TCC/Database/Pessoa");
	c.SetNaoPastaCaracateristica("C:/Users/Rafel/Documents/GitHub/TCC/Database/NPessoa");

	//cout << "Começou o Treino Adaboost" << endl;
	//c.Treina();

	//cout << "Terminou o treino Adaboost" << endl;
	c.Load();

	cout << "Teste Adaboost" << endl;
	
	c.TesteHardCode();

	//LbpRN r;
	//r.SetPastaCaracateristica("C:/Users/Rafel/Documents/GitHub/TCC/Database/Pessoa");
	//r.SetNaoPastaCaracateristica("C:/Users/Rafel/Documents/GitHub/TCC/Database/NPessoa");

	//cout << "Começou o Treino RN" << endl;
	//r.Treina();

	//cout << "Terminou o treino RN" << endl;

	getchar();
	return 0;
}
