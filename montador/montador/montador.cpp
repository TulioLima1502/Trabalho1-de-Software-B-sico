// montador.cpp: Define o ponto de entrada para a aplicação de console.
//

//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void filtro_comentarios(string line) {
	size_t poscom=line.find(";");
	string escreve;
	int coluna;

	ofstream mfile("auxiliar",ios::app);
	
	if (poscom!=line.npos)
	{
		//cout << "tem um comentario ae:" << poscom;
		coluna=poscom;
		//remove o comentario
		//pega linha e copia os caracteres até o poscom é feito com substr
		//coluna tem o número da linha que tem o comentário
		escreve=line.substr(0,coluna);
		//cout<<escreve+"\n";
		//escreve o arquivo direto no arquivo intermediário
		if (mfile.is_open())
		{
			mfile << escreve << endl;
			//mfile.close();
			
		}
		else cout << "\nArquivo nao pode ser aberto!!!\n\n";
	}
	else
	{
		//cout << "\n nem tem comentario aqui \n";
		//cout << line +"\n";
		if (mfile.is_open())
		{
			mfile << line << endl;
			//mfile.close();
		}
		else cout << "\nArquivo nao pode ser aberto!!!\n\n";
		//escreve o arquivo direto no arquivo destino
	}
	mfile.close();

}

void lerarquivo(char* file_name) { 
	//cout<<nome;
	//char name[] = {nome};
	string line;
	cout<<file_name;
	ifstream myfile(file_name);
	if (myfile.is_open())
	{
		cout << "\n";
		while (getline(myfile, line))
		{
			filtro_comentarios(line);
		}
		cout << "\n";
		myfile.close();
	}

	else cout << "\nArquivo nao pode ser aberto!!!\n\n";

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
	lerarquivo(argv[2]);
	montagem();
	codigo_objeto();
	return 0;
}