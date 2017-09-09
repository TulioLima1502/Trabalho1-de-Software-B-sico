// montador.cpp: Define o ponto de entrada para a aplicação de console.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void lerarquivo() {
	string line;
	ifstream myfile("entrada.txt");
	if (myfile.is_open())
	{
		cout << "\n";
		while (getline(myfile, line))
		{
			cout << line << '\n';
		}
		cout << "\n";
		myfile.close();
	}

	else cout << "\nArquivo nao pode ser aberto!!!\n\n";

}

int main() {
	lerarquivo();
	return 0;
}