#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#define M 1
#define MM  (M + 2)

#define FALSE 0
#define TRUE  1

typedef long TipoChave;

typedef struct TipoRegistro {
	TipoChave Chave;
	double custo;
	char descricao[20];
} TipoRegistro;

typedef struct TipoPagina* TipoApontador;
typedef struct TipoPagina {
	short n;
	TipoRegistro r[MM];
	TipoApontador p[MM + 1];
} TipoPagina;

void Inicializa(TipoApontador *Dicionario){  
	*Dicionario = NULL; 
}

void Pesquisa(TipoRegistro *x, TipoApontador Ap){ 
	long i = 1;
	if (Ap == NULL) { 
		printf("TipoRegistro não está presente na árvore\n");
		return;
	}
	while (i < Ap->n && x->Chave > Ap->r[i-1].Chave) 
		i++;
	if (x->Chave == Ap->r[i-1].Chave) { 
		*x = Ap->r[i-1];
		return;
	}
	if (x->Chave < Ap->r[i-1].Chave) 
		Pesquisa(x, Ap->p[i-1]);
	else 
		Pesquisa(x, Ap->p[i]);
} 

void Pesquisa(TipoChave chave, TipoApontador Ap){ 
    TipoRegistro *x;
    long i = 1;
    if (Ap == NULL) { 
        printf("Código da etapa não se encontra no sistema!\n");
        return;
    }
    while (i < Ap->n && chave > Ap->r[i-1].Chave) 
        i++;
    
    if (chave == Ap->r[i-1].Chave) {
    	printf("O código digitado retornou a etapa: \n");
    	printf("Descrição: %s\n",(char*)Ap->r[i-1].descricao);
        printf("Custo: %.2lf\n",(double) Ap->r[i-1].custo);
        return;
    }
    if (chave < Ap->r[i-1].Chave) 
        Pesquisa(chave, Ap->p[i-1]);
    else 
        Pesquisa(chave, Ap->p[i]);
} 



void InsereNaPagina(TipoApontador Ap, 
                    TipoRegistro Reg, 
					TipoApontador ApDir){ 
	short NaoAchouPosicao;
	int k;
	k = Ap->n;  NaoAchouPosicao = (k > 0);
	while (NaoAchouPosicao) 
	{ 
		if (Reg.Chave >= Ap->r[k-1].Chave) 
		{ 
			NaoAchouPosicao = FALSE;
			break;
		}
		Ap->r[k] = Ap->r[k-1];
		Ap->p[k+1] = Ap->p[k];
		k--;
		if (k < 1) NaoAchouPosicao = FALSE;
	}
	Ap->r[k] = Reg; 
	Ap->p[k+1] = ApDir;
	Ap->n++;
} 

void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu, 
         TipoRegistro *RegRetorno,  TipoApontador *ApRetorno){ 
	long i = 1; long j;
  	TipoApontador ApTemp;
  	if (Ap == NULL) { 
  		*Cresceu = TRUE; (*RegRetorno) = Reg; (*ApRetorno) = NULL;
		return;
  	}
	while (i < Ap->n && Reg.Chave > Ap->r[i-1].Chave)  
		i++;
  	if (Reg.Chave == Ap->r[i-1].Chave) { 
		printf(" Erro: O registro já está presente\n"); *Cresceu = FALSE;
    	return;
  	}
  	if (Reg.Chave < Ap->r[i-1].Chave) i--;
  	Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);
  	if (!*Cresceu) return;
  	if (Ap->n < MM) { /* Pagina tem espaco */
		InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    	*Cresceu = FALSE;
    	return;
    }
	/* Overflow: Pagina tem que ser dividida */
	ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
	ApTemp->n = 0;  
	ApTemp->p[0] = NULL;
	if (i < M + 1) { 
		InsereNaPagina(ApTemp, Ap->r[MM-1], Ap->p[MM]);
		Ap->n--;
		InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
	} 
	else 
		InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
	for (j = M + 2; j <= MM; j++) 
		InsereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j]);
	Ap->n = M;  
	ApTemp->p[0] = Ap->p[M+1];
	*RegRetorno = Ap->r[M];  
	*ApRetorno = ApTemp;
}

void Insere(TipoRegistro Reg, TipoApontador *Ap) { 
	short Cresceu;
	TipoRegistro RegRetorno;
	TipoPagina *ApRetorno, *ApTemp;
	Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);
	if (Cresceu){  /* Arvore cresce na altura pela raiz */	 
		ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));
		ApTemp->n = 1; 
		ApTemp->r[0] = RegRetorno;
		ApTemp->p[1] = ApRetorno;
		ApTemp->p[0] = *Ap;  *Ap = ApTemp;
	}
}

void Reconstitui(TipoApontador ApPag, TipoApontador ApPai, 
                 int PosPai, short *Diminuiu){ 
	TipoPagina *Aux;  long DispAux, j;
  	if (PosPai < ApPai->n)  /* Aux = TipoPagina a direita de ApPag */
	{ 
		Aux = ApPai->p[PosPai+1];  DispAux = (Aux->n - M + 1) / 2;
    	ApPag->r[ApPag->n] = ApPai->r[PosPai];
    	ApPag->p[ApPag->n + 1] = Aux->p[0];  
		ApPag->n++;
    	if (DispAux > 0)  /* Existe folga: transfere de Aux para ApPag */
    	{ 
			for (j = 1; j < DispAux; j++)
        		InsereNaPagina(ApPag, Aux->r[j-1], Aux->p[j]);
      		ApPai->r[PosPai] = Aux->r[DispAux-1];  
			Aux->n -= DispAux;
      		for (j = 0; j < Aux->n; j++) Aux->r[j] = Aux->r[j + DispAux];
      		for (j = 0; j <= Aux->n; j++) Aux->p[j] = Aux->p[j + DispAux];
      		*Diminuiu = FALSE;
    	}
    	else /* Fusao: intercala Aux em ApPag e libera Aux */
      	{ 
			for (j = 1; j <= M; j++)
          		InsereNaPagina(ApPag, Aux->r[j-1], Aux->p[j]);
        	free(Aux);
        	for (j = PosPai + 1; j < ApPai->n; j++) 
          	{ 
				ApPai->r[j-1] = ApPai->r[j]; 
	    		ApPai->p[j] = ApPai->p[j+1]; 
	  		}
        	ApPai->n--;
        	if (ApPai->n >= M) *Diminuiu = FALSE;
      	}
  	}
  	else /* Aux = TipoPagina a esquerda de ApPag */
    { 
		Aux = ApPai->p[PosPai-1]; 
		DispAux = (Aux->n - M + 1) / 2;
		for (j = ApPag->n; j >= 1; j--) ApPag->r[j] = ApPag->r[j-1];
			ApPag->r[0] = ApPai->r[PosPai-1];
		for (j = ApPag->n; j >= 0; j--) ApPag->p[j+1] = ApPag->p[j];
			ApPag->n++;
		if (DispAux > 0) /* Existe folga: transf. de Aux para ApPag */
		{ 
			for (j = 1; j < DispAux; j++)
          		InsereNaPagina(ApPag, Aux->r[Aux->n - j], 
	        Aux->p[Aux->n - j + 1]);
        	ApPag->p[0] = Aux->p[Aux->n - DispAux + 1];
        	ApPai->r[PosPai-1] = Aux->r[Aux->n - DispAux];
        	Aux->n -= DispAux;  
			*Diminuiu = FALSE;
      	}
      	else /* Fusao: intercala ApPag em Aux e libera ApPag */
        { 
			for (j = 1; j <= M; j++)
            	InsereNaPagina(Aux, ApPag->r[j-1], ApPag->p[j]);
          	free(ApPag);  ApPai->n--;
          	if (ApPai->n >= M)  *Diminuiu = FALSE;
        }
    }
}

void Antecessor(TipoApontador Ap, int Ind, 
                TipoApontador ApPai, short *Diminuiu){
	if (ApPai->p[ApPai->n] != NULL) 
  	{ 
		Antecessor(Ap, Ind, ApPai->p[ApPai->n], Diminuiu);
    	if (*Diminuiu) 
    		Reconstitui(ApPai->p[ApPai->n], ApPai, (long)ApPai->n, Diminuiu);
    	return;
  	}
  	Ap->r[Ind-1] = ApPai->r[ApPai->n - 1]; 
  	ApPai->n--;  *Diminuiu = (ApPai->n < M);
} 

void Ret(TipoChave Ch, TipoApontador *Ap, short *Diminuiu){ 
	long j, Ind = 1;
	TipoApontador Pag;
	if (*Ap == NULL) { 
		printf("Erro: registro não está na arvore\n"); *Diminuiu = FALSE;
		return;
	}
  	Pag = *Ap;
  	while (Ind < Pag->n && Ch > Pag->r[Ind-1].Chave) Ind++;
  	if (Ch == Pag->r[Ind-1].Chave) { 
	  	if (Pag->p[Ind-1] == NULL)   /* TipoPagina folha */
	    { 
			Pag->n--;
	      	*Diminuiu = (Pag->n < M);
	      	for (j = Ind; j <= Pag->n; j++) 
	        { 
				Pag->r[j-1] = Pag->r[j];  
				Pag->p[j] = Pag->p[j+1]; 
			}
	      	return;
	    }
	    /* TipoPagina nao e folha: trocar com antecessor */
	    Antecessor(*Ap, Ind, Pag->p[Ind-1], Diminuiu);
	    if (*Diminuiu) 
	    	Reconstitui(Pag->p[Ind-1], *Ap, Ind - 1, Diminuiu);
	    return;
	}
	if (Ch > Pag->r[Ind-1].Chave) Ind++;
		Ret(Ch, &Pag->p[Ind-1], Diminuiu);
	if (*Diminuiu) Reconstitui(Pag->p[Ind-1], *Ap, Ind - 1, Diminuiu);
}  

void Retira(TipoChave Ch, TipoApontador *Ap){ 
	short Diminuiu;
	TipoApontador Aux;
	Ret(Ch, Ap, &Diminuiu);
	if (Diminuiu && (*Ap)->n == 0)  /* Arvore diminui na altura */
	{ 
		Aux = *Ap;   
		*Ap = Aux->p[0]; 
		free(Aux);
	}
}  

void ImprimeI(TipoApontador p, int nivel){ 
	long i;
	if (p == NULL) return;
	printf("Nível %d : ", nivel);
	for (i = 0; i < p->n; i++){
		printf("\n");
		printf("Código: %ld \n",(long)p->r[i].Chave);
		printf("Custo: %.2lf \n",(double)p->r[i].custo);
		printf("Descrição: %s \n", (char*)p->r[i].descricao);
		printf("\n");	
	}
		
	putchar('\n');
	nivel++;
	for (i = 0; i <= p->n; i++)
		ImprimeI(p->p[i], nivel);
} 

void Imprime(TipoApontador p){ 
	int  n = 0; 
	ImprimeI(p, n); 
} 

double total;
void SomaI(TipoApontador p, int nivel){ 
	long i;
	if (p == NULL) return;
	for (i = 0; i < p->n; i++){
		total = total + ((double)p->r[i].custo);	
	}
		
	putchar('\n');
	nivel++;
	for (i = 0; i <= p->n; i++)
		SomaI(p->p[i], nivel);
} 

void Soma(TipoApontador p){ 
	int  n = 0; 
	SomaI(p, n); 
} 

void abreArq(FILE** arq)
{
	*arq = fopen("xml.txt", "r");
	if(*arq == NULL)
	{
		printf("Não foi possível abrir seu arquivo!\n");

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


void limpaStruct(TipoRegistro *estrut)  //limpa os valores da estrutura estrutura
{
	(*estrut).Chave = 0;
	(*estrut).custo = 0;
	memset(estrut->descricao, 0, sizeof(char*));
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

bool structCompleta(TipoRegistro estrut){ //retorna se a struct está completa ou não
	if(estrut.Chave != 0 && estrut.custo != 0 && strlen(estrut.descricao) != 0){
		return true;
	}
	return false;
}




