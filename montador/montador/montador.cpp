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

	remove ("auxiliar");
	remove ("MNT");
	remove ("MDT");
	remove ("EQU");
	
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

	string line, nomedamacro, nomeparam, valorparam, nomeequ, valorequ;
	ifstream meufile("auxiliar");
	ofstream mntfile("MNT",ios::app);
	ofstream mdtfile("MDT",ios::app);
	ofstream equfile("EQU",ios::app);
	ifstream equalfile("EQU");
	int linhamdt=0,fim,fimequ;
	bool remove;
	//ifstream mntfile("MNT");
	//ifstream mdtfile("MDT");
	if (meufile.is_open())
	{
		cout << "\n";
		while (getline(meufile, line))
		{
			//cout << line +"\n";
			size_t poscom=line.find("MACRO");
			size_t posequ=line.find("EQU");
			size_t posif=line.find("IF");
			if (poscom!=line.npos){
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
							mntfile << nomedamacro+"\t"; //o nome desse arquivo é MNT(Macro Name Table)
							mntfile << linhamdt << endl;						
						}
						else cout << "\nArquivo nao pode ser aberto!!!\n\n";
						
						getline(meufile, line);
						//Chama uma rotina para salvar em uma tabela o código da macro até o valor ENDMACRO
						//o nome desse arquivo é MDT(Macro Definition Table)
						do{
							//cout<<line;
							mdtfile << line << endl;
							linhamdt++;
							getline(meufile, line);
							posif=line.find("IF");
							if(posif!=line.npos) {
								//verifica o que tem depois do IF
								cout << "\nTem um IF aqui\n";
								fim=line.size();
								nomeparam=line.substr(posif+3,fim);
								cout << nomeparam << endl;
				
								//getline(equfile, line);
								if (equalfile.is_open()){
									//getline(equalfile, line);
									while(getline(equalfile, line)){
										//cout << line << endl;
										//le a linha ate o espaço depois disso
										posequ=line.find("\t");
										//depois pega o valor até o espaço e compara com o if que queremos
										nomeequ=line.substr(0,posequ);
										fimequ=line.size();
										valorequ=line.substr(posequ+1,fimequ);
										line.substr(posequ,fim);
										//cout << nomeequ << endl;
										//olha na tabela de EQU procurando o valor que está logo após o IF
										if(nomeequ==nomeparam){
											//parametro existe na tabela e podemos verificar o seu valor
											//cout << nomeequ << endl;
											//cout << valorequ << endl;
											//verifica o valor de nomeequ
											if(valorequ=="1"){
												//cout << "Deixa a linha\n";
												remove=0;
											}else if(valorequ=="0"){
												//cout << "Remove a linha\n";
												remove=1;
												cout << remove;
											}
											//se for 1 adiciona a linha posterior ao if
											//se for 0 remove a linha posterior ao if
											//caso o valor não esteja na tabela, retorna um erro
											//inserir erro aqui!!!
										}
										//equfile << line << endl;
										//getline(equalfile, line);
									}
				
									if(remove==1){
										getline(meufile, line);
										getline(meufile, line);
										//cout << line;
									}
								}else cout << "Erro ao abrir o arquivo EQU";
								//caso seja igual a zero remove a próxima linha
								//caso seja igual a um adiciona a próxima linha
							}
						}while(line!="ENDMACRO");
						
			}else if(posequ!=line.npos) { 
				cout << "\nTem um EQU aqui\n";
				fim=line.size();
				valorparam=line.substr(fim-1,fim);
				//if(valorparam=="1"){
					//salva na tabela de EQU o valor 
				//}else if (valorparam=="0"){

				//}else{ cout << "erro" << endl;}
				cout << valorparam << endl;
				posequ=line.find(":");
				nomeparam=line.substr(0,posequ);
				cout << nomeparam << endl;

				//salva na tabela o nome e o valor do parametro
				if (equfile.is_open())
				{
					equfile << nomeparam+"\t"; //o nome desse arquivo é MNT(Macro Name Table)
					equfile << valorparam << endl;		
				}
				else cout << "\nArquivo nao pode ser aberto!!!\n\n";

			}else if(posif!=line.npos) {
				//verifica o que tem depois do IF
				cout << "\nTem um IF aqui\n";
				fim=line.size();
				nomeparam=line.substr(posif+3,fim);
				cout << nomeparam << endl;

				//getline(equfile, line);
				if (equalfile.is_open()){
					//getline(equalfile, line);
					while(getline(equalfile, line)){
						//cout << line << endl;
						//le a linha ate o espaço depois disso
						posequ=line.find("\t");
						//depois pega o valor até o espaço e compara com o if que queremos
						nomeequ=line.substr(0,posequ);
						fimequ=line.size();
						valorequ=line.substr(posequ+1,fimequ);
						line.substr(posequ,fim);
						//cout << nomeequ << endl;
						//olha na tabela de EQU procurando o valor que está logo após o IF
						if(nomeequ==nomeparam){
							//parametro existe na tabela e podemos verificar o seu valor
							//cout << nomeequ << endl;
							//cout << valorequ << endl;
							//verifica o valor de nomeequ
							if(valorequ=="1"){
								//cout << "Deixa a linha\n";
								remove=0;
							}else if(valorequ=="0"){
								//cout << "Remove a linha\n";
								remove=1;
								cout << remove;
							}
							//se for 1 adiciona a linha posterior ao if
							//se for 0 remove a linha posterior ao if
							//caso o valor não esteja na tabela, retorna um erro
							//inserir erro aqui!!!
						}
						//equfile << line << endl;
						//getline(equalfile, line);
					}

					if(remove==1){
						getline(meufile, line);
						//cout << line;
					}
				}else cout << "Erro ao abrir o arquivo EQU";
				//caso seja igual a zero remove a próxima linha
				//caso seja igual a um adiciona a próxima linha
			}
			//procura pelo IF e assim que ele é encontrado, verifica se dentro dele existe um parâmetro válido por um EQ
		}
		cout << "\n";
		meufile.close();
		mdtfile.close();
		mntfile.close();
		equfile.close();
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