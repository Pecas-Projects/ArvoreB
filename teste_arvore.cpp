#include "ArvoreB_biblioteca.h"

using namespace std;

int main()
{
	TipoRegistro novo;
	
	novo.Chave = 1;
	novo.custo = 1000.00;
	novo.descricao = {'o', 'i'};
	
	TipoApontador arvore;
	
	Inicializa(&arvore);
	
	Insere(novo,&arvore);
	
	Imprime(arvore);
	
	Pesquisa(&novo, arvore);
	
	return 0;
}