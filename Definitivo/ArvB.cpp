#include "AvrB_arq.h"

using namespace std;


int main()
{
	TipoPagina *arvore;
	Inicializa(&arvore);
	char comando;
	char linha[50], palavra[20];
	TipoRegistro entrega;
	FILE* arq;
	abreArq(&arq);
	limpaStruct(&entrega);

	while(fgets(linha, sizeof(linha), arq) != NULL)
	{		
		//verificações

		if(strstr(linha, "Cod"))  //se encontrar a tag do Codigo na linha
		{
			inserePalavra(linha, palavra);
			entrega.Chave = atoi(palavra); //conversao para inteiro e inserção na estrutura
		}
		else if(strstr(linha, "Descr"))  //se encontrar a tag do Descrição na linha
		{
			inserePalavra(linha, palavra);
			strcpy(entrega.descricao, palavra); //inserção na estrutura
		}
		else if(strstr(linha, "Custo"))  //se encontrar a tag do Custo na linha
		{
			inserePalavra(linha, palavra);
			entrega.custo = atol(palavra); //conversao para double e inserção na estrutura
		}
		
		if(structCompleta(entrega)){ //se a struct estiver completa
			Insere(entrega, &arvore);
			limpaStruct(&entrega);
		}
	} 
	
	while (1){
		
		printf("Digite:\n");
		printf("	[P] Pesquisar\n");
		printf("	[E] Exibir\n");
		printf("	[T] Custo Total\n");
		printf("	[S] Sair\n");
		fflush(stdin);
		scanf("%c", &comando);
		
		
		if(comando == 'P'){
			int cod;
			TipoChave o;
			printf("Digite o codigo que deseja pesquisar: ");
			scanf("%d", &cod);
			o= cod;				
			Pesquisa(o, arvore);
			
		}else if (comando == 'E'){
			Imprime(arvore);
					
		}else if (comando == 'T'){
			total =0;
			Soma(arvore);
			printf("O Custo total da obra foi: %lf\n", total);
			
		}else if (comando == 'S'){
			break;
		}		
	}
	
	
	return 0;
}
