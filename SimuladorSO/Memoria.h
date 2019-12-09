#pragma once
#include <list>
using std::list;
/*Uma estrutura de dados para representar a sua memória (o tamanho da 
	memória é de 1GByte). Essa estrutura de dados pode ser na forma de 
	bitmaps ou de listas encadeadas, contanto que consiga representar a 
	quantia de bytes que está sendo alocada e seus devidos espaços. Cada 
	célula da sua memória deverá conter um 1byte, ou seja, caso eu tenha 
	uma memória de 1Mbyte, eu terei 1024 posições de memória ou 1024 
	bitmaps caso a implementação seja feita dessa forma.*/
typedef struct _elem
{

}elem;

class Memoria
{
	//o tamanho da memória é de 2^30 Bytes,
	int tamanho;
	//listas encadeadas, contanto que consiga representar a quantia de bytes que está sendo alocada e seus devidos espaços.
	list<elem> lista;
};

