#include "Memoria.h"
#include <iostream>

Memoria::Memoria()
{
	//o tamanho da mem�ria � de 2^30 Bytes,
	listaMem.push_back(elem{ 0,1073741824, VAZIO, nullptr });
}

void Memoria::bestFit(Disco& hd, Processo *novo)
{
	//Se a memoria utilizada pelo processo for maior que a memoria ram simulada, o simulador desiste de viver.
	if (novo->memoria > 1073741824) throw 10;
	auto escolhido = listaMem.begin();
	while (escolhido->estadoMemoria != VAZIO && escolhido != listaMem.end())
		escolhido++;
	//Percorre a lista procurando por espa�os vazios pra ocupar
	for (auto i = escolhido; i != listaMem.end(); i++)
	{
		//Se o elemento for vazio e possuir memoria suficiente para o processo
		if (i->estadoMemoria == VAZIO && i->tamanho >= novo->memoria)
		{
			//Se a quantidade que sobra de memoria para o elemento atual for menor que para o elemento escolhido
			if (((i->tamanho) - (novo->memoria)) <= ((escolhido->tamanho) - (novo->memoria)))
				//Escolhe o elemento atual
				escolhido = i;
		}
	}
	//Se foi encontrado um espa�o adequado
	if (escolhido->estadoMemoria == VAZIO && escolhido->tamanho >= novo->memoria)
	{
		//Insere o elemento do processo antes do elemento vazio escolhido
		listaMem.insert(escolhido, elem{ escolhido->indice, novo->memoria, OCUPADO,novo });
		//Atualiza o elemento vazio escolhido
		escolhido->indice += novo->memoria;
		escolhido->tamanho -= novo->memoria;
		novo->estado = PRONTO;
	}
	//Se n�o foi encontrado um espa�o adequado
	else
	{
		//Faz swap
		swap(hd, novo);
	}
}

void Memoria::swap(Disco& hd, Processo* novo)
{
	//Processo mais antigo
	//Caso o primeiro elemento da lista esteja ocupado come�amos por ele
	auto maisAntigo = listaMem.begin();
	//Caso contrario come�amos com o segundo
	if (maisAntigo->estadoMemoria == VAZIO)
		maisAntigo++;
	//Percorremos a lista em busca de processos com a maior quantidade de instru��es executadas

	for (auto i = maisAntigo; i != listaMem.end(); i++)
	{
		//Se o elemento est� ocupado e o processo ocupante � mais antigo
		if (i->estadoMemoria == OCUPADO)
			if ((i->processo)->instrucoesExecutadas > (maisAntigo->processo)->instrucoesExecutadas)
				maisAntigo = i;
	}


	std::cout << "Processo " << maisAntigo->processo->nome << " foi o escolhido para swap" << std::endl;
	//Move o processo da memoria ram para o hd
	hd.salvaEmDisco(maisAntigo->processo);

	//libera a ram
	maisAntigo->estadoMemoria = VAZIO;
	maisAntigo->processo = nullptr;
	uneElemVazios(maisAntigo);
	bestFit(hd, novo);
}

void Memoria::uneElemVazios(list<elem>::iterator primeiro)
{
	std::cout << "Unindo os vazios na RAM" << std::endl;
	//Testa se o elemento a unir � realmente vazio, se � o ultimo, e se o proximo � realmente vazio
	if (std::next(primeiro) == listaMem.end())
		return;
	if (std::next(primeiro)->estadoMemoria != VAZIO)
		return;
	std::cout << "Vazios seguidos confirmados" << std::endl;
	//Soma os tamanhos
	primeiro->tamanho += std::next(primeiro)->tamanho;
	//Remove da lista
	listaMem.erase(std::next(primeiro));
	std::cout << "Sucesso em unir os vazios na RAM" << std::endl;
}