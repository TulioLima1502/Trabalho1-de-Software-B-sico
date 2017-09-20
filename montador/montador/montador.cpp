// montador.cpp: Define o ponto de entrada para a aplicação de console.
//

//#include "stdafx.h"
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
	//retira os comentários
	//assim que encontra um símbolo de comentário pula para a próxiam linha
	//reescreve esse arquivo em um intermediário
}

void montagem() {
	//faz a conversão do código conforme a passagem única
	//preenche as tabelas de simbolos e uso
	//checa erros (fazer uma função de detecção de erros da linguagem inventada)
	//escrever em um arquivo de saida

}

void codigo_objeto() {
	//mostra o código objetos escrito
}

int main(int argc, char* argv[]) {	
	//argc eh um inteiro com o numero de argumentos passados pela linha de comando
	//argv eh um vetor com os argumentos. argv[0] sempre sera o path do programa,
	//entao eh basicamente ignorado. por isso, o argc na verdade vai ser o numero
	//de argumentos mais um.
	string file_name;
	//verificar como é a chamada do programa pelo gcc
	
	file_name = argv[2]; // passar para learquivo(). eh o nome do arquivo .asm.
	lerarquivo();
	filtro_comentarios(); // Podemos salvar em um vetor
	montagem();
	codigo_objeto();
	return 0;
}