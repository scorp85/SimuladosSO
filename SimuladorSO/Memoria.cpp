#include "Memoria.h"

Memoria::Memoria()
{
	//o tamanho da mem�ria � de 2^30 Bytes,
	listaMem.push_back(elem{ 0,1073741824, VAZIO, nullptr });
}

void Memoria::bestFit(Disco& hd, Processo& novo)
{
	//Se a memoria utilizada pelo processo for maior que a memoria ram simulada, o simulador desiste de viver.
	if (novo.memoria > 1073741824) throw 10;
	auto escolhido = listaMem.begin();
	while (escolhido->estado != VAZIO && escolhido != listaMem.end())
		escolhido++;
	//Percorre a lista procurando por espa�os vazios pra ocupar
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
	//Se foi encontrado um espa�o adequado
	if (escolhido->estado == VAZIO && escolhido->tamanho >= novo.memoria)
	{
		//Insere o elemento do processo antes do elemento vazio escolhido
		listaMem.insert(escolhido, elem{ escolhido->indice, novo.memoria, OCUPADO,&novo });
		//Atualiza o elemento vazio escolhido
		escolhido->indice += novo.memoria;
		escolhido->tamanho -= novo.memoria;
		novo.estado = PRONTO;
	}
	//Se n�o foi encontrado um espa�o adequado
	else
	{
		//Faz swap
		swap(hd, novo);
	}
}

void Memoria::swap(Disco& hd, Processo& novo)
{
	//Processo mais antigo
	//Caso o primeiro elemento da lista esteja ocupado come�amos por ele
	auto maisAntigo = listaMem.begin();
	//Caso contrario come�amos com o segundo
	if (maisAntigo->estado == VAZIO)
		maisAntigo++;
	//Percorremos a lista em busca de processos com a maior quantidade de instru��es executadas
	for (auto i = listaMem.begin(); i != listaMem.end(); i++)
	{
		//Se o elemento est� ocupado e o processo ocupante � mais antigo
		if ((i->estado == OCUPADO) && ((i->processo)->instrucoesExecutadas > (maisAntigo->processo)->instrucoesExecutadas))
			maisAntigo = i;
	}
	//Move o processo da memoria ram para o hd
	hd.salvaEmDisco(maisAntigo->processo);
	//libera a ram
	maisAntigo->estado = VAZIO;
	maisAntigo->processo = nullptr;
	uneElemVazios(maisAntigo);
	bestFit(hd, novo);
}

void Memoria::uneElemVazios(list<elem>::iterator primeiro)
{
	//Testa se o elemento a unir � realmente vazio, se � o ultimo, e se o proximo � realmente vazio
	if (primeiro->estado != VAZIO || std::next(primeiro) == listaMem.end() || std::next(primeiro)->estado != VAZIO)
		return;
	//Soma os tamanhos
	primeiro->tamanho += std::next(primeiro)->tamanho;
	//Remove da lista
	listaMem.erase(std::next(primeiro));
}