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
		size_t posfinal = line.size()-1;
		line.erase(line.begin()+posfinal);
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
	remove ("saida");
	
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

void expande_macro(char* file_name){

	string line, nomedamacro, nomeparam, valorparam, nomeequ, valorequ;

	ifstream meufile(file_name);
	ofstream mntfile("MNT",ios::app);
	ofstream mdtfile("MDT",ios::app);

	string termina="ENDMACRO";
	string comparando;

	int linhamdt=0;

	if (meufile.is_open())
	{
		cout << "\n";
		while (getline(meufile, line))
		{
			size_t poscom=line.find("MACRO");
			if (poscom!=line.npos){
				cout << "\nTem uma MACRO aqui \n\n";
				//salva aqui o nome das MACROS definidas no código
				//Chama uma rotina para salvar em um arquivo o nome da macro, a quantidade de parametros e a linha que será adicionada na MDT
				//Pega a linha em que foi achada a macro, e encontra o nome que vem antes dos ':'
				poscom=line.find(":");
				nomedamacro=line.substr(0,poscom);
				//inicialização da variável que diz qual linha estará o escopo da macro
				//cout << nomedamacro << endl;
				if (mntfile.is_open())
				{
					mntfile << nomedamacro << "\t" << linhamdt << endl; //o nome desse arquivo é MNT(Macro Name Table)
					getline(meufile,line);

					while( ( line.compare("ENDMACRO") != 0 ) && (linhamdt<20)){
						
						mdtfile << line << endl;
						cout << line << endl;
						//comparando=line;
						//cout << comparando << endl;
						linhamdt++;	
						getline(meufile,line);

					}
					//mdtfile << line << endl;
	
					cout << "\n      finalizou a MACRO      \n" << endl;
					//getline(meufile,line);
				
				}else cout << "\nArquivo nao pode ser aberto!!!\n\n";
				//getline(meufile, line);
				//Chama uma rotina para salvar em uma tabela o código da macro até o valor ENDMACRO
				//o nome desse arquivo é MDT(Macro Definition Table)
<<<<<<< HEAD
				//strcmp(pesq, agen[contador].nome) == 0
				getline(meufile,line);

				do{
					cout << "Essa eh a linha logo antes: " << line << endl;
					mdtfile << line << endl;
					getline(meufile,line);
					cout << "logo depois da escrita: " << line << endl;
					comparando=line;
					cout << "COmparacao: " << comparando.compare(termina) << endl;
					linhamdt++;				
				}while( ( comparando.compare(termina) != 0 ) );

				cout << "\n      finalizou a MACRO      \n" << endl;
				getline(meufile,line);
=======
				//getline(meufile,line);
				
>>>>>>> df629beedcc7011572316a8bfaa76d3614ab2b6f
			}
		}
	}
	mntfile.close();
	mdtfile.close();
	meufile.close();
}

void pre_procesamento(char* file_name) {
	
	string line, nomedamacro, nomeparam, valorparam, nomeequ, valorequ;
	int fim, posequ, fimequ, remover, teste;
	ifstream meufile("auxiliar");
	ofstream equfile("EQU",ios::app);
	ofstream saidafile("saida",ios::app);


	if (meufile.is_open()) 
	{
		while(getline(meufile, line))
		{
			if (line.find("EQU")!=line.npos)
			{
				cout << "\nTem um EQU aqui\n";
				fim=line.size();


				//No computador do Túlio a próxima linha é -2, no do Barbosa é -1

				valorparam=line[fim-1];

				posequ=line.find(":");
				nomeparam=line.substr(0,posequ);

				//salva na tabela o nome e o valor do parametro
				if (equfile.is_open())
				{
					equfile << nomeparam + "\t"; //o nome desse arquivo é MNT(Macro Name Table)
					equfile << valorparam <<endl;
					cout << "tá aqui nesse caralho\n";
				}
				else cout << "\nArquivo nao pode ser aberto EQU!!!\n\n";

			}else if(line.find("IF")!=line.npos){
				cout << "\nTem um IF aqui\n";
				fim=line.size();
				size_t posif=line.find("IF");
				nomeparam=line.substr(posif+3,fim);
				teste = nomeparam.size();
				nomeparam=line.substr(3,teste-1);	
				cout << nomeparam << endl;
				cout << nomeparam.size() << endl;
				ifstream equfile("EQU");				
 				if(equfile.is_open()){
					while(getline(equfile,line)){
						//le a linha ate o espaço depois disso
						posequ=line.find("\t");
						//depois pega o valor até o espaço e compara com o if que queremos
						nomeequ=line.substr(0,posequ);
						fimequ=line.size();
						valorequ=line[fimequ-1];
						//line.substr(posequ,fim);
						cout << nomeequ.size() << endl;
						cout << valorequ.size() << endl;
						//olha na tabela de EQU procurando o valor que está logo após o IF
						if(nomeequ.compare(nomeparam)==0){
							//parametro existe na tabela e podemos verificar o seu valor
							cout << nomeequ << endl;
							cout << "aqui" <<endl;
							cout << valorequ << endl;
							//verifica o valor de nomeequ
							if(valorequ=="1"){
								remover=0;
								getline(meufile,line);
								saidafile << line << endl;
							}else if(valorequ=="0"){
								remover=1;
								cout << remover << endl;
								getline(meufile,line);
							}
							//se for 1 adiciona a linha posterior ao if
							//se for 0 remove a linha posterior ao if
							//caso o valor não esteja na tabela, retorna um erro
							//inserir erro aqui!!!
						}

					}
				}
				else cout << "\nArquivo nao pode ser aberto EQU Este caralho!!!\n\n";
			}else{saidafile << line << endl;}
		}
		equfile.close();
		meufile.close();
		saidafile.close();			
	}
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

	file_name = argv[2]; // passar para learquivo(). eh o nome do arquivo .asm.
	lerarquivo(argv[2]);

	if (string(argv[1])=="-p"){
		pre_procesamento(argv[3]);
	}else if (string(argv[1])=="-m"){
		pre_procesamento(argv[3]);
		expande_macro(argv[3]);
		// realiza a expansão das macros em um arquivo com extensão .mcr
		// pega o arquivo da etapa anterior, le o que está nele e executa a criação da MNT e da MDT
		// depois utiliza o algoritmo de expansão das macros que está na função de passagem zero
		// mostra esse arquivo com as macros expandidas

		//montagem();
		//codigo_objeto();
	}else if (string(argv[1])=="-o"){
		//Realiza a montagem do código depois de expandir as macros
	}else {
		cout << " Comando de execução não encontrado.    ERRO     " << endl;
	}
	return 0;
}

//pré processamento completo mas com resalvas que tem que ser corrigidas
//Realizar a passagem 0 antes da passagem única de acordo com a tabela que tem no slides

// com o código que temos, adicionar o preprocesamento com -p
// cria o arquivo em que o código .pre será arquivado
// o que é preciso ser feito é pegar a função que cria a MNT e MDT e adaptar para resolver apenas os EQU IF
// e depois disso salva em um arquivo para mostrar no final

// -m para realizar a expansão da macros é só pegar o código que foi criado para expandir criar a MDT e MNT