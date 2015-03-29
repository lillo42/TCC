#include <iostream>
#include "LbpClassificador.h"
#include "LbpRN.h"

using namespace std;

int main(int argc, char** argv)
{
	LbpClassificador c;
	c.SetPastaCaracateristica("C:/Users/Rafel/Documents/GitHub/TCC/Database/Pessoa");
	c.SetNaoPastaCaracateristica("C:/Users/Rafel/Documents/GitHub/TCC/Database/NPessoa");

	cout << "Começou o Treino" << endl;
	c.Treina();

	cout << "Terminou" << endl;
	getchar();
	return 0;
}
