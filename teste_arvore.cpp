#include "ArvoreB_biblioteca.h"

using namespace std;

int main()
{
	TipoRegistro novo;
	TipoRegistro teste1;
	TipoRegistro teste2;
	
	novo.Chave = 1;
	novo.custo = 1000.00;
	novo.descricao = {'o', 'i', '\n'};
	
	teste1.Chave = 3;
	teste1.custo = 4500.32;
	teste1.descricao = {'c', 'a', 'r', 'r', 'o', '\n'};
	
	teste2.Chave = 777;
	teste2.custo = 867.987;
	teste2.descricao = {'f', 'o', 'm', 'e', '\n'};
	
	
	TipoPagina *arvore;
	
	Inicializa(&arvore);
	
	Insere(novo,&arvore);
	Insere(teste1,&arvore);
	Insere(teste2,&arvore);
	
	
	Imprime(arvore);
	
	
	Pesquisa(teste1.Chave, arvore);
	
	
	return 0;
}