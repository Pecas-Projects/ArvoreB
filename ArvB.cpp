#include "bibliotecaOriginal.h"

using namespace std;


int main()
{
	char comando;

	TipoRegistro A;
	TipoRegistro B;
	TipoRegistro C;
	TipoRegistro D;
	TipoRegistro F;
	TipoRegistro G;
	TipoRegistro H;
	
	A.Chave = 1;
	A.custo = 200.3;
	A.descricao[0] = 'A';
	A.descricao[1] = 'B';
	A.descricao[2] = '\0';
	
	
	B.Chave = 2;
	B.custo = 437.89;
	B.descricao[0] = 'B';
	B.descricao[1] = 'B';
	B.descricao[2] = '\0';
	
	C.Chave = 3;
	C.custo = 890.000;
	C.descricao[0] = 'C';
	C.descricao[1] = 'B';
	C.descricao[2] = '\0';
	
	D.Chave = 4;
	D.custo = 890.000;
	D.descricao[0] = 'C';
	D.descricao[1] = 'A';
	D.descricao[2] = '\0';
	
	F.Chave = 5;
	F.custo = 890.000;
	F.descricao[0] = 'C';
	F.descricao[1] = 'C';
	F.descricao[2] = '\0';
	
	G.Chave = 6;
	G.custo = 890.000;
	G.descricao[0] = 'C';
	G.descricao[1] = 'G';
	G.descricao[2] = '\0';
	
	H.Chave = 7;
	H.custo = 890.000;
	H.descricao[0] = 'C';
	H.descricao[1] = 'A';
	H.descricao[2] = '\0';

	TipoPagina *arvore;
	Inicializa(&arvore);

	Insere(A, &arvore);
	Insere(B, &arvore);
	Insere(C, &arvore);
	Insere(D, &arvore);
	Insere(F, &arvore);
	Insere(G, &arvore);
	Insere(H, &arvore);
	
	
	
	
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
