#pragma once
#include <list>
#include "Processo.h"
#include "Disco.h"

using std::list;
/*Uma estrutura de dados para representar a sua mem�ria (o tamanho da 
	mem�ria � de 1GByte). Essa estrutura de dados pode ser na forma de 
	bitmaps ou de listas encadeadas, contanto que consiga representar a 
	quantia de bytes que est� sendo alocada e seus devidos espa�os. Cada 
	c�lula da sua mem�ria dever� conter um 1byte, ou seja, caso eu tenha 
	uma mem�ria de 1Mbyte, eu terei 1024 posi��es de mem�ria ou 1024 
	bitmaps caso a implementa��o seja feita dessa forma.*/

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
	//listas encadeadas, contanto que consiga representar a quantia de bytes que est� sendo alocada e seus devidos espa�os.
	void uneElemVazios(list<elem>::iterator primeiro);
	list<elem> listaMem;
private:
	void swap(Disco& hd, Processo *novo);
	//Une um par de elementos vazios
	
};

