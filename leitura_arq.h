#include "bibliotecaOriginal.h"

//biblioteca para leitura de obtencao das palavras

/*typedef struct
{
	int cod;
	double custo;
	char descricao[20];
} estrutura;*/

void limpaStruct(TipoRegistro *estrut)  //limpa os valores da estrutura estrutura
{
	(*estrut).Chave = 0;
	(*estrut).custo = 0;
	memset(estrut->descricao, 0, sizeof(char*));
}

bool structCompleta(TipoRegistro estrut){ //retorna se a struct está completa ou não
	if(estrut.Chave != 0 && estrut.custo != 0 && strlen(estrut.descricao) != 0){
		return true;
	}
	return false;
}

int primeiraOcorrencia(char* str, char letra)  //retorna a posicao da primeira ocorrencia do char na string
{
	int i;
	for(i = 0; i < strlen(str); i++)
	{
		if(str[i] == letra)
		{
			return i;
		}
	}
	i = -1; //no caso de não encontrar
	return i;
}

void abreArq(FILE** arq)
{
	*arq = fopen("xml.txt", "r");
	if(*arq == NULL)
	{
		printf("Nao foi possivel abrir seu arquivo!\n");

	}
	else
	{
		printf("Arquivo aberto com sucesso!\n");
	}
}

void fechaArq(FILE** arq)
{
	fclose(*arq);
	printf("Arquivo fechado com sucesso!\n");
}

void inserePalavra(char* linha, char* palavra) //função que busca a palavra entre tags de comando para inserir na estruct
{
	int k = 0, i, posicao;
	posicao = primeiraOcorrencia(linha, '>');
	memset(palavra, 0, sizeof(*palavra)); //tira o lixo de memoria da string
	for(i = posicao + 1; i < strlen(linha); i++) //percorre a frase a partir da primeira tag
	{
		if(linha[i] == '<') //se encontrar o inicio da proxima tag sai do laço
		{
			break;
		}
		palavra[k] = linha[i]; //palavra recebe as letras que estão entre as tags
		k++;
	}
	//return palavra; 
}

void obtemPalavras(TipoRegistro* entrega, FILE** arq)
{
	setlocale(LC_ALL, "Portuguese");
	setbuf(stdout, NULL);	
	char linha[50], palavra[20];
	
	while(fgets(linha, sizeof(linha), *arq) != NULL)
	{
		printf("%s\n", linha);
		memset(&palavra, 0, sizeof(palavra)); //tira o lixo de memoria da string
		//verificações
		if(strstr(linha, "Cod"))  //se encontrar a tag do Codigo na linha
		{
			inserePalavra(linha, palavra);
			(*entrega).Chave = atoi(palavra); //conversao para inteiro e inserção na estrutura
		}
		else if(strstr(linha, "Descr"))  //se encontrar a tag do Descrição na linha
		{
			inserePalavra(linha, palavra);
			strcpy((*entrega).descricao, palavra); //inserção na estrutura
		}
		else if(strstr(linha, "Custo"))  //se encontrar a tag do Custo na linha
		{
			inserePalavra(linha, palavra);
			(*entrega).custo = atol(palavra); //conversao para double e inserção na estrutura
		}
		if(structCompleta(*entrega)){ //se a struct estiver completa
			printf("Custo: %.2lf\n", (*entrega).custo);
			printf("Código: %d\n", (*entrega).Chave);
			printf("Custo: %s\n", (*entrega).descricao);
			//a insercao da arvore deve ser feita nesse momento
			
			limpaStruct(entrega);
		}
	}
}
