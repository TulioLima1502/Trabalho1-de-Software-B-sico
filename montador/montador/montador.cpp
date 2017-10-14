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

void passagem_zero() {

	string line,nomedamacro;
	ifstream meufile("auxiliar");
	ifstream mntfile("MNT");
	ifstream mdtfile("MDT");
	if (meufile.is_open())
	{
		cout << "\n";
		while (getline(meufile, line))
		{
			//cout << line +"\n";
			size_t poscom=line.find("MACRO");
			if (poscom!=line.npos)
			{
				cout << "\nTem uma MACRO aqui \n\n";
				//salva aqui o nome das MACROS definidas no código
				//Chama uma rotina para salvar em um arquivo o nome da macro, a quantidade de parametros e a linha que será adicionada na MDT
						//Pega a linha em que foi achada a macro, e encontra o nome que vem antes dos ':'
						//nomedamacro=line.substr(0,poscom);
						//cout<<nomedamacro+"\n";
						poscom=line.find(":");
						nomedamacro=line.substr(0,poscom);
						cout<<nomedamacro+"\n";

						//o nome desse arquivo é MNT(Macro Name Table)
				//Chama uma rotina para salvar em uma tabela o código da macro até o valor ENDMACRO
						//o nome desse arquivo é MDT(Macro Definition Table)
			}//else cout << "\n Não tem uma MACRO aqui \n";
		}
		cout << "\n";
		meufile.close();
	}

	else cout << "\nArquivo nao pode ser aberto!!!\n\n";

}

void salva_MNT() {
	//Função para salvar o nome da Macro em um Arquivo MDT, salva a quantidade de parametros e o em qual linha da MDT o código será inserido
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
	passagem_zero();
	montagem();
	codigo_objeto();
	return 0;
}

//pré processamento completo mas com resalvas que tem que ser corrigidas
//Realizar a passagem 0 antes da passagem única de acordo com a tabela que tem no slides