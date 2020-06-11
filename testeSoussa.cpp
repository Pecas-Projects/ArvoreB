#include "bibliotecaOriginal.h"

using namespace std;


int main()
{

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
	
	B.Chave = 2;
	B.custo = 437.89;
	B.descricao[0] = 'B';
	
	C.Chave = 3;
	C.custo = 890.000;
	C.descricao[0] = 'C';
	
	D.Chave = 4;
	F.Chave = 5;
	G.Chave = 6;
	H.Chave = 7;

	TipoPagina *arvore;
	Inicializa(&arvore);

	Insere(A, &arvore);
	Insere(B, &arvore);
	Insere(C, &arvore);
	Insere(D, &arvore);
	Insere(F, &arvore);
	Insere(G, &arvore);
	Insere(H, &arvore);
	
	Imprime(arvore);


	return 0;
}
