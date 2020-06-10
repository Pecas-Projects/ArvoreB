#include "ArvoreB_biblioteca.h"

using namespace std;

int main()
{
	TipoRegistro novo;
	novo.Chave = 1;
	novo.descr = "cimento";
	novo.custo = 1000.00;
	
	TipoPagina *arvore;
	
	Inicializa(&arvore);

	Insere(novo,&arvore);
	
//	Imprime(*aponta);
	
	return 0;
}