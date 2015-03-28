#include <iostream>
#include "LbpClassificador.h"
#include "LbpRN.h"

int main(int argc, char** argv)
{
	LbpClassificador c;
	c.SetPastaCaracateristica("C:/Users/Rafel/Documents/GitHub/TCC/Database/Pessoa");
	c.SetNaoPastaCaracateristica("C:/Users/Rafel/Documents/GitHub/TCC/Database/NPessoa");
	c.Treina();
}
