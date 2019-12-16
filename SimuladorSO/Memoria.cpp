#include "Memoria.h"

Memoria::Memoria()
{
	//o tamanho da memória é de 2^30 Bytes,
	listaMem.push_back(elem{ 0,1073741824, VAZIO, nullptr });
}

void Memoria::bestFit(Processo& novo)
{
	//Se a memoria utilizada pelo processo for maior que a memoria ram simulada, o simulador desiste de viver.
	if (novo.memoria > 1073741824) throw 10;
	auto escolhido = listaMem.begin();
	while (escolhido->estado != VAZIO && escolhido != listaMem.end())
		escolhido++;
	//Percorre a lista procurando por espaços vazios pra ocupar
	for (auto i = escolhido; i != listaMem.end(); i++)
	{
		//Se o elemento for vazio e possuir memoria suficiente para o processo
		if (i->estado == VAZIO && i->tamanho >= novo.memoria)
		{
			//Se a quantidade que sobra de memoria para o elemento atual for menor que para o elemento escolhido
			if ((i->tamanho - novo.memoria) <= (escolhido->tamanho - novo.memoria))
				//Escolhe o elemento atual
				escolhido = i;
		}
	}
	//Se foi encontrado um espaço adequado
	if (escolhido->estado == VAZIO && escolhido->tamanho >= novo.memoria)
	{
		//Insere o elemento do processo antes do elemento vazio escolhido
		listaMem.insert(escolhido, elem{ escolhido->indice, novo.memoria, OCUPADO,&novo });
		//Atualiza o elemento vazio escolhido
		escolhido->indice += novo.memoria;
		escolhido->tamanho -= novo.memoria;
	}
	//Se não foi encontrado um espaço adequado
	else
	{
		//Faz swap
	}
}