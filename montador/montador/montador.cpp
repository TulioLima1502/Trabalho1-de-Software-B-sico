// montador.cpp: Define o ponto de entrada para a aplicação de console.
// Nesse programa, implementamos o funcionamento compilador em diferentes estágios e comandos
// de forma que a montagem do código siga a lógica de uma passagem.
// Código desenvolvido pelos seguintes alunos:

// ALUNOS: 
// Tulio Mariano da Silva Lima	12/0054337
// Matheus Barbosa de Miranda 13/0015083

// O CÓDIGO DA DUPLA ENCONTRA-SE DISPONÍVEL NO GITHUB, NO SEGUINTE REPOSITÓRIO:
//
// 		https://github.com/TulioLima1502/Trabalho1-de-Software-B-sico
//
// PARA A CONFECÇÃO DO TRABALHO 1 FOI UTILIZADO O VISUAL STUDIO CODE (	diferente do visual studio community, mas igualmente gratuito)
//
// INSTRUÇÕES DE USO/COMPILAÇÃO
// É NECESSÁRIO DE UM COMPUTADOR COM LINUX (UBUNTU 16)
// É NECESSAŔIO TER OS PACOTES DE C++ PARA REALIZAR A COMPILAÇÃO E EXECUÇÃO PELA LINHA DE COMANDO
// É NECESSÁRIO REALIZAR A COMPILAÇÃO PARA SÓ EM SEGUIDA EXECUTAR
// O COMANDO DE COMPILAÇÃO É: g++ -std=c++11 montador.cpp -o <nome do executável>
// DEPOIS DE COMPILADO BASTA EXECUTAR O PROGRAMA COM O COMANDO: 
//
//				./<nome do executável> -x <nome do arquivo>.asm <nome do arquivo de saida>
// 
// ** PARA CORRETO FUNCIONAMENTO É NECESSAŔIO TER UM ARQUIVO TEXTO COM EXTENSÃO .ASM NA MESMA PASTA DO PROGRAMA MONTADOR.CPP


//#include "stdafx.h"
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <string>
#include <cstring>
#include <iostream>
#include <map>
#include <cstddef>
#include <vector>


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

void lerarquivo(char* file_name,char* file_name2 ) { 
	//cout<<nome;
	//char name[] = {nome};
	string line;


	string nome,saida,mcr,pontoo;
	//cout<<file_name2<< endl;
	nome=file_name2;
	nome=nome.substr(0,nome.size());
	//nome.append(".pre");
	cout << nome;

	saida = nome.substr(0,nome.size())+".pre";
	//cout << saida << endl;
	mcr=nome.substr(0,nome.size())+".MCR";
	//cout << mcr << endl;
	pontoo=nome.substr(0,nome.size())+".o";

	const char * psaida = saida.c_str();
	const char * pmcr = mcr.c_str();
	const char * ppontoo = pontoo.c_str();

	//cout<<file_name;
	ifstream myfile(file_name);
	int achoutext=0, achoudata=0, errosection = 0 ;

	remove ("auxiliar");
	remove ("MNT");
	remove ("MDT");
	remove ("EQU");
	remove (psaida);
	remove (pmcr);
	remove("tabela_de_simbolos");
	remove (ppontoo);


	ofstream mfile("auxiliar", ios::app);
	if (myfile.is_open())
	{
		//cout << "\n";
		while (getline(myfile, line))
		{
			line=filtro_comentarios(line);
			line=formato_padrao(line); 	// remove tabulacoes, espacos extras e quebras de linhas.
			if (mfile.is_open() && line!="")
			{
				for(int i=0;i < line.size();i++)
				{
					line[i]=toupper(line[i]);
				}
				//cout << line << endl;
				mfile << line << endl;
			}
			if (line.find("SECTION TEXT")==0){
				achoutext=1;
			}
			if (line.find("SECTION DATA")==0){
				achoudata=1;
			}
			if (line.find("SECTION")==0){
				size_t pos = line.find("SECTION");
				int tamlinha = line.size();
				string sectionerrada = line.substr(pos+8,tamlinha);
				if ((sectionerrada.compare("DATA")!=0) && (sectionerrada.compare("TEXT")!=0)){
					errosection = 1;
				}
			}
		}
		//cout << "\n";
		myfile.close();
	}

	else cout << "\nArquivo nao pode ser aberto!!!\n\n";

	if (achoutext==0){
		cout << "ERRO, FALTOU A SECTION TEXT" << endl;
	}
	if (achoudata==0){
		cout << "ERRO, FALTOU A SECTION DATA" << endl;
	}
	if (errosection==1) {
		cout << "ERRO na difinição do Section" << endl;
	}

}

void expande_macro(char* file_name){

	string nome;
	cout<<file_name << endl;
	nome=file_name;
	nome=nome.substr(0,nome.size());
	cout << nome;

	string line, nomedamacro, nomeparam, valorparam, nomeequ, valorequ, token, mntbusca, mdtbusca, mdtline, linhabusca, comparando, linhafimacro;

	string saida = nome.substr(0,nome.size())+".pre";

	ifstream meufile(saida);
	ofstream mntfile("MNT",ios::app);
	ofstream mdtfile("MDT",ios::app);
	ofstream menosm(nome.append(".MCR"), ios::app);

	string termina="END";

	int linhamdt=0, tam, contador=0, compara=0, linhafim;

	if (meufile.is_open())
	{

		//cout << "ta aqui?" << endl;
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
				cout << nomedamacro << endl;
				//inicialização da variável que diz qual linha estará o escopo da macro
				//cout << nomedamacro << endl;
				if (mntfile.is_open())
				{
					mntfile << nomedamacro << "\t" << linhamdt << endl; //o nome desse arquivo é MNT(Macro Name Table)
					getline(meufile,line);
					do{
						mdtfile << line << endl;
						getline(meufile,line);
						cout << line << endl;
						comparando=line;
						cout << "Comparacao: " << comparando.compare(termina) << endl;
						linhamdt++;				
					}while( ( comparando.compare(termina) != 0 ) );
	
					cout << "\n      finalizou a MACRO      \n" << endl;
				}	else cout << "\nArquivo nao pode ser aberto!!!\n\n";
				//getline(meufile, line);
				//Chama uma rotina para salvar em uma tabela o código da macro até o valor ENDMACRO
				//o nome desse arquivo é MDT(Macro Definition Table)
				//strcmp(pesq, agen[contador].nome) == 0
				cout << line << endl;
				
			} else 
				{
					// Se for uma chamada de macro, aqui ela sera expandida
					size_t posdelimit = line.find(" ");
					// Se nao tiver espacos, ou eh diretiva ou eh macro.
					// Testa aqui se eh macro (pela mnt)
					// Se nao for, tem que ser diretiva (verificar durante a montagem)
					if (posdelimit == line.npos) {
						ifstream mntfile("MNT");
						if (mntfile.is_open()) {
							while (getline(mntfile, mntbusca)) {
								token = line;
								size_t postab = mntbusca.find("\t");
								cout << "Token: " << token << endl;
								cout << "mntbusca: " << mntbusca << endl;
								mdtbusca = mntbusca.substr(0, postab);
								cout << "mdtbusca: " << mdtbusca << endl;
								cout << mdtbusca.compare(token) << endl;
								// Se entrar nesse if, achou o nome da macro na mnt
								// Vai agora entrar no if e ir na mdt.

								// Procura as macros, ainda nao expande mas ta quase la
								
								if (mdtbusca.compare(token)==0) {
									ifstream mdtfile("MDT");									

									if (getline(mntfile,linhafimacro)) {
										int tam2 = linhafimacro.size();
										linhafimacro = linhafimacro.substr(tam2-1,tam2);
										linhafim = stoi(linhafimacro);
									}
									
									else {
										linhafim = 100000;
									}

									tam = mntbusca.size();
									linhabusca = mntbusca.substr(tam-1, tam);
									compara = stoi(linhabusca);	
									cout << "linha fim : " << linhafim << endl;
																														
									if (mdtfile.is_open()) {

										while ((getline(mdtfile, mdtline)) && compara!=contador) {
											contador++;
											cout << "compara: " << compara << endl;
											cout << "contador: " << contador << endl;
											cout << "linha da mdt: " << mdtline << endl;
										}

										// o arquivo MDT esta exatamente na linha da macro chamada
										// linhafim tem o valor da ultima linha que eh pra ser copiada
										
										do {
										cout << "entrou aqui!" << endl;
											if (menosm.is_open()) {
												cout << mdtline << endl;
												menosm << mdtline << endl;
												contador++;
												cout << "contador: " << contador << endl;
												cout << "linha fim: " << linhafim << endl;
											}
										} 	while (getline(mdtfile, mdtline) && contador!=linhafim);
											
										
								
									} else {
										cout << "Nao foi possivel abrir o arquivo MDT para busca" << endl;
									}

								} 
								
							}
							if (token=="STOP") {  				// esse if eh so pra colocar o STOP no .mcr. sem isso o stop nao entra.				
								//cout << "entrou aqui!" << endl;
								if (menosm.is_open()) {
									menosm << token << endl;
								}
							}
							mdtfile.close();
							mntfile.close();
							contador=0;
						} else cout << "Nao foi possivel abrir o arquivo MNT para expandir macros!" << endl;

					} else	{		
						// Se nao for definicao de macro nem chamada de macro, escreve direto no .mcr
						if (menosm.is_open()) {  
							menosm << line << endl;
						} else cout << "Nao foi possivel abrir o arquivo .mcr! " << endl; 
					}	
				} 

		}
	}
	menosm.close();	
	mntfile.close();
	mdtfile.close();
	meufile.close();
}

void pre_procesamento(char* file_name) {
	

	string nome;
	cout<<file_name << endl;
	nome=file_name;
	nome=nome.substr(0,nome.size());
	//nome.append(".pre");
	//cout << nome;


	string line, nomedamacro, nomeparam, valorparam, nomeequ, valorequ;
	int fim, posequ, fimequ, remover, teste;
	ifstream meufile("auxiliar");
	ofstream equfile("EQU",ios::app);
	ofstream saidafile(nome.append(".pre"),ios::app);


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
					//cout << "tá aqui nesse caralho\n";
				}
				else cout << "\nArquivo nao pode ser aberto EQU!!!\n\n";

			}else if(line.find("IF")!=line.npos){
				cout << "\nTem um IF aqui\n";
				fim=line.size();
				size_t posif=line.find("IF");
				nomeparam=line.substr(posif+3,fim);
				teste = nomeparam.size();
				nomeparam=line.substr(3,teste);  // No PC do tulio: teste-1. No do barbosa: teste.
				cout << line << endl;	
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
				} 	else cout << "\nArquivo nao pode ser aberto EQU Este caralho!!!\n\n";
			}	else{saidafile << line << endl;}
		}
		equfile.close();
		meufile.close();
		saidafile.close();			
	}
}

void montagem(char* file_name) {
	//faz a conversão do código conforme a passagem única
	
	string nome;
	//cout<<file_name << endl;
	nome=file_name;
	nome=nome.substr(0,nome.size());
	//nome.append(".pre");
	//cout << nome;
	string teste = nome.substr(0,nome.size())+".MCR";
	string remover=nome.append(".o");

	const char *premove = remover.c_str();
	
	string line, label, simbolo, SimboloDaTS, simbolo_lido, linha_da_ts, definicao, buscatabela, arquivosaida, linhaobjeto, linha_lida;
	char * token;
	char ch = ' ';
	int espacos, linhadependencia, dependencia;
	string linha_da_tabelaconsulta, linedois, labeldois;

	int numlinha=0, tamanhot, flagSimbIgual=0, pc=0, valor,i, achou=0,somador=0;
	bool flag[17] = { 0 };

	/* vetor de flags para indicar qual eh a instrucao instanciando
	os argumentos da linha. no nosso vetor, a posicao [0] corresponde 
	ao ADD, [1] ao sub, e assim por diante de acordo com a tabela da
	especificacao do trabalho. As posicoes [14], [15] e [16], respectivamente,
	correspondem `as diretivas section, space e const. */
	
	ifstream meufile(file_name);
	ifstream entrada(teste);
	ofstream saida(remover, ios::app);
	
	//pegar uma linha verificar o tem nela e testar a função strtok, com :, ai adiciona ou procura na tabela de símbolos
	if (entrada.is_open())
	{
		//cout << "\n";
		while (getline(entrada, line))
		{
			//size_t dois_pontos=line.find(":");
			//strtok();
			char *duplicata = strdup(line.c_str());
			//linha=line.c_str();
			token = strtok (duplicata," ");
			while (token != NULL)
			{
				//cout << token << endl;
				label=token;
				//cout << label << endl;
				size_t dois_pontos=label.find(":");
				if (dois_pontos!=label.npos)
				{
	
					tamanhot = label.size();
					simbolo = label.substr(0,tamanhot-1);
					//cout << simbolo << endl;
					ifstream ts("tabela_de_simbolos", ios::app);
					if (ts.is_open()){
						
						while (getline(ts, SimboloDaTS)) {
							
							size_t postab = SimboloDaTS.find("\t");
							size_t postabdois = SimboloDaTS.find("\t",postab+3,1);
							size_t novo;
							if (postab!=line.npos) {
								novo = postab;
								definicao=SimboloDaTS.substr(novo+4,postabdois);
								SimboloDaTS = SimboloDaTS.substr(0, postab);
								//pega o valor da definição encontrada e depois compara para ver se é F ou T
								//caso seja T ele deve mostrar um erro
								//caso seja F ele deve resolver as pendencias desse operando
								if ((simbolo.compare(SimboloDaTS)==0)&&(definicao=="T")) {
									cout << "\nA Label " << simbolo <<  " ja foi definida!\n" << endl;
									cout << definicao << endl;
									flagSimbIgual = 1;
									// tem que mostrar um erro

								} else if ((simbolo.compare(SimboloDaTS)==0)&&(definicao=="F")) {
									cout << definicao << endl;
									//cout << simbolo << "\n\nPOR FAVOR RESOLVA AS PENDENCIAS DESSE PARAMETRO\n\n";
									// aqui já pode ser resolvida as pendencias que aparecerem
									// fazer a função para resolver as pendencias do código objeto 

								}
							
							}
						} // se achar o valor mas se estiver definido como F então tem que pegar o valore dele e escrever em cada pendencia
						ts.close();

						ofstream ts("tabela_de_simbolos", ios::app);
						if (ts.is_open() && flagSimbIgual==0) {
							cout << "\n\n PROGRAM COUNTER:  " << pc << endl;
							ts << simbolo << "\t" << pc << "\t" << "T" << endl;
							ts.close();
						}
						flagSimbIgual=0;
					} 
				} else {
						cout << label << endl;
						if (label.compare("ADD")==0){
							pc+=1;								
							cout << "opcode = 01" << endl;
							if (saida.is_open()) {
								saida << "01" << " ";
							}


						} else if (label.compare("SUB")==0) {
							pc+=1;	
							cout << "opcode = 02" << endl;	
							if (saida.is_open()) {
								saida << "02" << " ";
							}
						} else if (label.compare("MULT")==0) {
							pc+=1;
							cout << "opcode = 03" << endl;
							if (saida.is_open()) {
								saida << "03" << " ";
							}

						} else if (label.compare("DIV")==0) {
							pc+=1;	
							
							cout << "opcode = 04" << endl;
							if (saida.is_open()) {
								saida << "04" << " ";
							}
						} else if (label.compare("JMP")==0) {
							pc+=1;	
							
							cout << "opcode = 05" << endl;
							if (saida.is_open()) {
								saida << "05" << " ";
							}
						} else if (label.compare("JMPN")==0) {
							pc+=1;	
							
							cout << "opcode = 06" << endl;
							if (saida.is_open()) {
								saida << "06" << " ";
							}
						} else if (label.compare("JMPP")==0) {
							pc+=1;	
							
							cout << "opcode = 07" << endl;
							if (saida.is_open()) {
								saida << "07" << " ";
							}
						} else if (label.compare("JMPZ")==0) {
							pc+=1;	
							
							cout << "opcode = 08" << endl;
							if (saida.is_open()) {
								saida << "08" << " ";
							}
						} else if (label.compare("COPY")==0) {
							pc+=1;	
							
							cout << "opcode = 09" << endl;
							if (saida.is_open()) {
								saida << "09" << " ";
							}
							// TEM QUE CHECAR ESSE DE MANEIRA ISOLADA
						} else if (label.compare("LOAD")==0) {
							pc+=1;	
							
							cout << "opcode = 10" << endl;
							if (saida.is_open()) {
								saida << "10" << " ";
							}
						} else if (label.compare("STORE")==0) {
							pc+=1;	
							
							cout << "opcode = 11" << endl;
							if (saida.is_open()) {
								saida << "11" << " ";
							}
						} else if (label.compare("INPUT")==0) {
							pc+=1;	
							
							cout << "opcode = 12" << endl;
							if (saida.is_open()) {
								saida << "12" << " ";
							}
						} else if (label.compare("OUTPUT")==0) {
							pc+=1;	
							
							cout << "opcode = 13" << endl;
							if (saida.is_open()) {
								saida << "13" << " ";
							}
						} else if (label.compare("STOP")==0) {
							pc+=1;	
							
							cout << "opcode = 14" << endl;
							numlinha--;
							if (saida.is_open()) {
								saida << "14" << " ";
							}
						} else if (label.compare("SPACE")==0) {
														
							
							size_t posicao = line.find("SPACE");
							string teste = line.substr(0,posicao+5);
							//cout << teste << endl;
							//cout << "oi" << endl;
							int posnum = teste.size();
							int comprimento = line.size();
							int result = comprimento - posnum;
							
							if (result > 1){
								token = strtok (NULL, " ");
								label=token;
								//cout << label << endl;
								espacos=atoi(token);
								//cout << espacos << endl;
							} else if(result < 1){
								espacos = 1;
								//cout << espacos << endl;
							}

							if (saida.is_open()) {
								for(i=0;i<espacos;i++){
								pc++;
								saida << "0" <<" ";
								}
							}

							cout << "diretiva space: " << endl;
							numlinha--;

						} else if (label.compare("SECTION")==0) {	
							
							cout << "eh uma section" << endl;
							numlinha--;
						} else if (label.compare("TEXT")==0) {

							cout << "eh uma section" << endl;
							numlinha--;

						} else if (label.compare("CONST")==0) {
							token = strtok (NULL, " ");
							label=token;
							if (label.substr(0,2)=="0x") {
								valor = (int) strtol(token, NULL, 0);
							} else if (label.substr(0,3)=="-0x"){
								valor = (int) strtol(token, NULL, 0);								
							} else {
								valor = stoi (label);
							}

							if (saida.is_open()) {
								saida << valor << " ";
							}
							
							pc++;
							
							numlinha--;
						} else {
							//procurar dentro da tabela de símbolos para ver se está definido
							
							ifstream ts("tabela_de_simbolos", ios::app);
							if (ts.is_open()){
									
								while (getline(ts, linha_da_ts)) {
									
									size_t postab = linha_da_ts.find("\t");
									size_t novo;
									if (postab!=linha_da_ts.npos) {
										simbolo_lido = linha_da_ts.substr(0, postab);
										if (label.compare(simbolo_lido)==0) {
											//cout << "\n\nachou esse caralho\n" << endl;
											novo = postab;
											postab=linha_da_ts.find("\t",postab+3,1);
											definicao=linha_da_ts.substr(novo+4, postab);
											//cout << definicao << endl;
											// verifica a definição do símbolo, se for T verifica o valor do simbolo
											if (definicao.compare("T")==0){
												cout << "\n\n simbolo já estava na tabela PODE PEGAR O VALOR DA LINHA\n\n";
												// NESSA PARTE PODE INSERIR A ESCRITA NO ARQUIVO DE SAIDA.O
												
											} else if (definicao.compare("F")==0) {
												cout << "\n\n simbolo ainda não foi definido TEM QUE ESCREVER AS PENDENCIAS\n\n";
												// VERIFICAR SE A LINHA DE CODIGO ANTERIOR RESOLVE ESSE CASO
												// AQUI PODE ESCREVER O X NO VALOR DO PARAMETRO NO ARQUIVO DE SAIDA.O
												
											} else {
												//cout << "simbolo não encontrado" << endl;
												// VERIFICAR SE A LINHA DE CODIGO ANTERIOR RESOLVE ESSE CASO
												// AQUI PODE ESCREVER O X NO VALOR DO PARAMETRO NO ARQUIVO DE SAIDA.O
												// DEPOIS DE FEITO TUDO ISSO TEM QUE VERIFICAR RESOLVER AS PENDENCIAS DE TODOS ARQUIVOS
												// TEM QUE DECIDIR SE AS PENDENCIAS VÃO SER RESOLVIDAS SÓ NO FINAL OU SE NA HORA QUE ACHAR ELE VAI RESOLVER
												
											}
											// se for F adiciona nas pendências depois do valor de difinição do simbolo 

										}else {
											//cout << "\n\n esse caralho não existe" << endl;
											//incluir na tabela de simbolos com o valor de definição F e a pendencia
											flagSimbIgual = 2;
											
										}
									
									}
								}
								
								ofstream ts("tabela_de_simbolos", ios::app);
								if (ts.is_open()) {
									ts << label << "\t" << pc << "\t" << "F" << endl;
									pc++;
									if (saida.is_open()) {
										saida << "xx" << " ";

									}
									ts.close();
								}
								flagSimbIgual=0;

								ts.close();
							}


							//caso na tabela de símbolos não exista o token, então ele deve ser criado e iniciado com valor de definição F
							//a linha é salva na tabela de pendências
							//caso na tabela de símbolos exista o token, mas definido com F, atualiza a lista de pendências
							//caso na tabela de símbolos exista o token e ele esteja definido com V, pode escrever o valor
							//caso na tabela de símbolos exista o token mas o operando só esta sendo definido agora, resolva todas as pendências 
						}

									
					
				}
			  	token = strtok (NULL, " ");
			}
		
		} 
		saida.close();


		// Resolvendo pendencias:

		ifstream ts("tabela_de_simbolos");
		while (getline(ts, linha_da_ts)) {
			cout << "Comecando a procurar..." <<endl;
			size_t rposdef = linha_da_ts.rfind("\t");
			size_t poslabel = linha_da_ts.find("\t");
			label = linha_da_ts.substr(0,poslabel);
			int tam = 0;
			tam=linha_da_ts.size();
			line = linha_da_ts.substr(rposdef+1,tam);
			cout << label << endl;
			//cout << line  << " m "<< endl;
			if (line=="T"){
				ifstream tabelaconsulta("tabela_de_simbolos");
				while (getline(tabelaconsulta, linha_da_tabelaconsulta)){
					cout << "Comecando a procurar...2" <<endl;
					size_t rposdef = linha_da_tabelaconsulta.rfind("\t");
					size_t poslabel = linha_da_tabelaconsulta.find("\t");

					labeldois = linha_da_tabelaconsulta.substr(0,poslabel);
					int tamdois = 0;
					tamdois=linha_da_tabelaconsulta.size();
					linedois = linha_da_tabelaconsulta.substr(rposdef+1,tamdois);
					//cout << label << endl;
					//cout << linedois << endl;
					if (label==labeldois){
						if (linedois=="F"){
							cout << label << endl;
							cout << linedois << endl;
							cout << linha_da_tabelaconsulta << endl;
							//basta resolver as pendencias aqui
							//pega o valor da linha que tem que resolver
							size_t primeiro = linha_da_tabelaconsulta.rfind("\t");
							size_t segundo = linha_da_tabelaconsulta.find("\t");
							
							string linha_da_pendencia = linha_da_tabelaconsulta.substr(segundo+1,primeiro-segundo);
							
							//transforma esse valor para inteiro
							int valorinteiro=stoi(linha_da_pendencia);
							cout << valorinteiro << endl;
							//abre o arquivo de saida e pesquisa pelo valor de interesse
							ifstream saida(remover);
							if (saida.is_open()) {							
								while (getline(saida, arquivosaida)) {
									//cout << arquivosaida << endl;
									size_t encontrou = arquivosaida.find(" ");
									somador=1;
									cout << "aqui" << endl;
									arquivosaida=arquivosaida.substr(encontrou+1,arquivosaida.size());
									cout<<arquivosaida<<endl;
									while(arquivosaida.size()>0){
										arquivosaida = arquivosaida.substr(arquivosaida.find(" ")+1);
										cout << arquivosaida << endl;
										//arquivosaida=arquivosaida.substr(encontrou);
										somador++;
										if (somador==valorinteiro){
											//troca aqui
											cout << "troca aqui" << endl;
											cout << valorinteiro << " ";
											cout << arquivosaida.substr(3) << endl;
											//salta a quantidade de tabs até o ponto
											//altera no arquivo de saida
											//copia do valor que foi alterado até o inicio para o arquivo de saida
											//depois soma com o valor alterado e o proximo valor até o final do arquivo de saida
											//reescreve o valor no arquivo de saida

										}
									}

								}
							}

						
							

						}
					}


				}

			}
			/*if (line=="F") {
				while (getline(ts, linha_da_ts) && achou==0) {
					poslabel = linha_da_ts.find("\t");
					buscatabela = linha_da_ts.substr(0, poslabel);
					if (label.compare(buscatabela)==0 && achou==0) {
						rposdef = linha_da_ts.rfind("\t");
						tam=linha_da_ts.size();
						line = linha_da_ts.substr(rposdef+1,tam);
						if (line=="T") {
							achou = 1;
							line = linha_da_ts.substr(poslabel+1,rposdef-3);
							dependencia=stoi(line);
							poslabel =line.find("\t");	
							line = line.substr(0,poslabel);		
							
							// e se ele inserir aqui logo???
							//tem que procurar pelo valor da linha que tem que inserir
							//depois que tiver tem que ter o valor que tem que ser escrito nela
							//procura dentro de um arquivo de saida a linha
							//achou, resecreve o arquivo texto com esse valor correto
							//essa logica pode dar certo, mas a que eu tenho já funciona, mas eu preciso para vários
						}
					}
				} 
				ts.close();
				ifstream ts("tabela_de_simbolos");
				while (getline(ts,linha_da_ts)) {
					poslabel = linha_da_ts.find("\t");
					buscatabela = linha_da_ts.substr(0, poslabel);
					cout << "Busca tabela: " << buscatabela << endl;
					cout << "Label: " << label << endl;				
					if (buscatabela.compare(label)==0) {
						cout << "linha da ts: " << linha_da_ts << endl;
						poslabel = linha_da_ts.find("\t");
						rposdef = linha_da_ts.rfind("\t");
						linhadependencia = stoi(linha_da_ts.substr(poslabel, rposdef));
						ifstream saida(remover);
						achou =0;
						if (saida.is_open()) {							
							if (getline(saida, arquivosaida)) {
								linha_lida = arquivosaida;
								char *duplicate = strdup(linha_lida.c_str());
								token = strtok (duplicate," ");
								cout << linha_lida << endl;
								cout << token << endl;
								linhaobjeto=token;
								somador=0;
								remove(premove);
								ofstream arquivofinal(remover);
								//se for xx e somador for igual a linha tabela altera o valor
								while ((token!=NULL)||(somador==linhadependencia)){
									linhaobjeto=token;
									if ((linhaobjeto.compare("xx")==0)&&(somador==linhadependencia)){
										cout << "troca" << endl;
										// pega a linha toda substitui essa posicao e salva em saida novamente
										//ofstream arquivofinal("SAIDA.o");
										if (arquivofinal.is_open()) {
											arquivofinal << line << " ";
											token = strtok (NULL, " ");
										}
									}
									if (arquivofinal.is_open()) {
										arquivofinal << token << " ";
									}
									somador++;
									token = strtok (NULL, " ");
								}

								//cout << "Linha dependencia : " << linhadependencia << endl;

							}
						}
					}
				}
				//ts.close();
			}*/
			cout<< line << " n " << endl;
		}
		

	}
	//verificar labels

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
	lerarquivo(argv[2],argv[3]);

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
		pre_procesamento(argv[3]);
		expande_macro(argv[3]);
		montagem(argv[3]);
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