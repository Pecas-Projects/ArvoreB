#include <iostream>
#include "leitura_arq.h"

// codigo de demonstra��o de uso da biblioteca de leitura do arquivo
using namespace std;

int main(){
	setlocale(LC_ALL, "Portuguese");
	char linha[50], palavra[20];
	estrutura entrega;
	FILE* arq;
	abreArq(&arq);
	limpaStruct(&entrega);
	
	while(fgets(linha, sizeof(linha), arq) != NULL)
	{
		//cout << linha << endl;
		
		//verifica��es

		memset(palavra, 0, sizeof(palavra));
		if(strstr(linha, "Cod"))  //se encontrar a tag do Codigo na linha
		{
			inserePalavra(linha, palavra);
			entrega.cod = atoi(palavra); //conversao para inteiro e inser��o na estrutura
		}
		else if(strstr(linha, "Descr"))  //se encontrar a tag do Descri��o na linha
		{
			inserePalavra(linha, palavra);
			strcpy(entrega.descricao, palavra); //inser��o na estrutura
		}
		else if(strstr(linha, "Custo"))  //se encontrar a tag do Custo na linha
		{
			inserePalavra(linha, palavra);
			entrega.custo = atol(palavra); //conversao para double e inser��o na estrutura
		}
		
		if(structCompleta(entrega)){ //se a struct estiver completa
			cout << "Custo: " << entrega.custo << endl;
			cout << "Descricao: " << entrega.descricao << endl;
			cout << "C�digo: " << entrega.cod << endl;
			//a insercao na arvore deve ser feita nesse momento
			limpaStruct(&entrega);
		}
	} 
	obtemPalavras(&entrega, &arq);
	fechaArq(&arq);
	
	return 0;
}