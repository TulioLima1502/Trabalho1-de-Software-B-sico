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

void filtro_comentarios() {

}

void montagem() {

}

void codigo_objeto() {

}

int main() {
	lerarquivo();
	filtro_comentarios(); // Podemos salvar em um vetor
	montagem();
	codigo_objeto();
	return 0;
}