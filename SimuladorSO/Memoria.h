#pragma once
#include <list>
#include "Processo.h"
#include "Disco.h"

using std::list;
/*Uma estrutura de dados para representar a sua memória (o tamanho da 
	memória é de 1GByte). Essa estrutura de dados pode ser na forma de 
	bitmaps ou de listas encadeadas, contanto que consiga representar a 
	quantia de bytes que está sendo alocada e seus devidos espaços. Cada 
	célula da sua memória deverá conter um 1byte, ou seja, caso eu tenha 
	uma memória de 1Mbyte, eu terei 1024 posições de memória ou 1024 
	bitmaps caso a implementação seja feita dessa forma.*/

enum estadoMem
{
		VAZIO, OCUPADO
};

typedef struct _elem
{
	int indice;
	int tamanho;
	estadoMem estadoMemoria;
	Processo *processo;

}elem;

class Memoria
{
public:
	Memoria();
	void bestFit(Disco& hd, Processo *novo);
	//listas encadeadas, contanto que consiga representar a quantia de bytes que está sendo alocada e seus devidos espaços.
	void uneElemVazios(list<elem>::iterator primeiro);
	list<elem> listaMem;
private:
	void swap(Disco& hd, Processo *novo);
	//Une um par de elementos vazios
	
};

