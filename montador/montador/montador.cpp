// montador.cpp: Define o ponto de entrada para a aplicação de console.
//

//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string filtro_comentarios(string line) {
	size_t poscom=line.find(";");
	int coluna;
	
	if (poscom!=(line).npos)
	{
		coluna=poscom;
		line=line.substr(0,coluna);
	}
	return(line);
}

string formato_padrao(string line) {
	size_t posspace;
	size_t postab = line.find("\t");

	while (postab!=line.npos) 						//loop que tira tabs e troca por espacos.
	{
		if (postab==0){
			line.erase(line.begin()+postab);
		}
		else {
			line.replace(line.begin()+postab, line.begin()+postab+1," ");
		}
		postab=line.find("\t");
	}

	posspace = line.find(" ");					// loop que tira espacos a mais.
	while (posspace!=line.npos) {				// o formato padrao eh com todos argumentos 
		if (posspace==0) {						// com apenas um espaco entre eles.
			do {
				line.erase(line.begin()+posspace);
				posspace=line.find(" ");	
			} while (posspace==0);		
		}
		else
		{
			posspace=line.find("  ");
			while (posspace!=line.npos) 
			{
				line.erase(line.begin()+posspace);
				posspace=line.find("  ");
			}
		}
	}
	if (line[line.size()-1]==' ') {      //retira espacos no final
		line.pop_back();
	}

	if (line=="\n") {					//se a linha se resumir a uma quebra de linha,
		line = "";						//a mesma eh descartada.
	}


	return (line);
}

void lerarquivo(char* file_name) { 
	//cout<<nome;
	//char name[] = {nome};
	string line;
	cout<<file_name;
	ifstream myfile(file_name);

	remove("auxiliar");
	ofstream mfile("auxiliar", ios::app);
	if (myfile.is_open())
	{
		cout << "\n";
		while (getline(myfile, line))
		{
			line=filtro_comentarios(line);
			line=formato_padrao(line); 	// remove tabulacoes, espacos extras e quebras de linhas.
			if (mfile.is_open() && line!="")
			{
				mfile << line << endl;
			}
		}
		cout << "\n";
		myfile.close();
	}

	else cout << "\nArquivo nao pode ser aberto!!!\n\n";

}

void passagem_zero() {

	string line,nomedamacro;
	ifstream meufile("auxiliar");
	ofstream mntfile("MNT",ios::app);
	ofstream mdtfile("MDT",ios::app);
	int linhamdt=0;
	//ifstream mntfile("MNT");
	//ifstream mdtfile("MDT");
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
						//cout<<nomedamacro+"\n";
						 //inicialização da variável que diz qual linha estará o escopo da macro
						if (mntfile.is_open())
						{
							mntfile << nomedamacro+"\t";
							mntfile << linhamdt << endl;						
						}
						else cout << "\nArquivo nao pode ser aberto!!!\n\n";
						
						getline(meufile, line);

						do{
							//cout<<line;
							mdtfile << line << endl;
							linhamdt++;
							getline(meufile, line);
						}while(line!="ENDMACRO");

						//o nome desse arquivo é MNT(Macro Name Table)
				//Chama uma rotina para salvar em uma tabela o código da macro até o valor ENDMACRO
						//o nome desse arquivo é MDT(Macro Definition Table)
			}//else cout << "\n Não tem uma MACRO aqui \n";
		}
		cout << "\n";
		meufile.close();
		mdtfile.close();
		mntfile.close();
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
	//passagem_zero();
	montagem();
	codigo_objeto();
	return 0;
}

//pré processamento completo mas com resalvas que tem que ser corrigidas
//Realizar a passagem 0 antes da passagem única de acordo com a tabela que tem no slides