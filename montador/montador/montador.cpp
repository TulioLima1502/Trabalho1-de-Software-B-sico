// montador.cpp: Define o ponto de entrada para a aplicação de console.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ios>

using namespace std;

int main() {
	string line;
	ifstream myfile("example.txt"); // ifstream = padrão ios:in
	if (myfile.is_open())
	{
		while (!myfile.eof()) //enquanto end of file for false continua
		{
			getline(myfile, line); // como foi aberto em modo texto(padrão)
								   //e não binário(ios::bin) pega cada linha
			cout << line << endl;
		}
		myfile.close();
	}

	else cout << "Unable to open file";

	return 0;
}


//void lerarquivo(){
	
//}