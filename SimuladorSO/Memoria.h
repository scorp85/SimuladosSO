#pragma once
#include <list>
#include "Processo.h"
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
	Processo *processo;
	int indice;
	int tamanho;
	estadoMem estado;	

}elem;

class Memoria
{
	//o tamanho da mem�ria � de 2^30 Bytes,
	int tamanho;
	//listas encadeadas, contanto que consiga representar a quantia de bytes que est� sendo alocada e seus devidos espa�os.
	list<elem> lista;
};

