#include "Cpu.h"
#include <iostream>

Cpu::Cpu(SistemaOperacional* sistema) :so(sistema)
{
	cpu1 = nullptr;
	cpu2 = nullptr;
	quanta = 0;
}

void Cpu::atualizaFila()
{
	//Percorre a lista de processos do sistema operacional
	for (auto processo = so->begin(); processo != so->end(); processo++)
	{
		//Em busca de processos PRONTOS
		if (processo->estado == PRONTO)
		{
			//Que ainda não estão na sua lista de roundrobin
			bool novo = true;
			for (auto i = rrList.begin(); i != rrList.end(); i++)
			{
				if (*i == &(*processo))
				{
					novo = false;
				}
			}
			if (novo) {
				std::cout << processo->nome << " inserido no round robin" << std::endl;
				rrList.push_back(&(*processo));
			}
		}
	}
}

Processo* Cpu::selecionaProximoProcesso()
{
	//Caso fila esteja vazia, não retorna nada
	if (rrList.begin() == rrList.end())
		return nullptr;
	bool emRam = false;
	//Caminha pela memoria ram
	for (auto i = so->ram.listaMem.begin(); i != so->ram.listaMem.end(); i++)
	{
		//Verifica se o primeiro processo na fila RR está em ram
		if (rrList.front() == i->processo)
			emRam = true;
	}
	//Se não estiver faz swap
	if (!emRam) 
	{
		so->hd.armazenamento.erase(rrList.front());
		so->ram.bestFit(so->hd, rrList.front());
	}
	//Remove o processo selecionado da lista
	Processo* selecionado = rrList.front();
	//Muda o estado do processo para executando para não ser re-inserido na lista
	std::cout << selecionado->nome << " executando" << std::endl;
	selecionado->estado = EXECUTANDO;
	rrList.pop_front();
	return selecionado;
}


void Cpu::preExecutaCPU1()
{
	
	//Se o ultimo processo ter acabado
	if (quanta == 0)
	{
		//Insere o processo anterior no fundo da fila
		if (cpu1 != nullptr)
		{
			cpu1->estado = PRONTO;
			rrList.push_back(cpu1);
		}
		//Pega o processo na frente da fila
		cpu1 = selecionaProximoProcesso();
		if (cpu1 == nullptr)
			return;
		//Define 10 quantas para executar o processo
		quanta = 10;
		std::cout << cpu1->nome << " preexecutado com quanta igual a " << quanta << std::endl;
	}
}
	//SLEEP

void Cpu::executaCPU1()
{
	//Caso o processo não tenha sido carregado, não faz nada
	if (cpu1 == nullptr)
		return;
	std::cout << "Executando "<< cpu1->nome <<" quanta = " << quanta << std::endl;
	//Aumenta a quantidade de instruções executadas
	++(cpu1->instrucoesExecutadas);
	//Se o processo estiver em sua ultima instrução, marca para remoção
	if (cpu1->instrucoesExecutadas >= cpu1->instrucoes)
	{
		std::cout << "Finalizando " << cpu1->nome << " quanta = " << quanta << std::endl;
		quanta = 0;
		finaliza(cpu1);
		cpu1 = nullptr;
	}
	else
	{
		--quanta;
	}
	
}

void Cpu::preExecutaCPU2()
{

	//Se o ultimo processo ter acabado
	if (quanta == 0)
	{
		//Insere o processo anterior no fundo da fila
		if (cpu2 != nullptr)
		{
			cpu2->estado = PRONTO;
			rrList.push_back(cpu2);
		}
		//Pega o processo na frente da fila
		cpu2 = selecionaProximoProcesso();
		if (cpu2 == nullptr)
			return;
		//Define 10 quantas para executar o processo
		quanta = 10;
		std::cout << cpu2->nome << " preexecutado com quanta igual a " << quanta << std::endl;
	}
}
//SLEEP

void Cpu::executaCPU2()
{
	//Caso o processo não tenha sido carregado, não faz nada
	if (cpu2 == nullptr)
		return;
	std::cout << "Executando " << cpu2->nome << " quanta = " << quanta << std::endl;
	//Aumenta a quantidade de instruções executadas
	++(cpu2->instrucoesExecutadas);
	//Se o processo estiver em sua ultima instrução, marca para remoção
	if (cpu2->instrucoesExecutadas >= cpu2->instrucoes)
	{
		quanta = 0;
		finaliza(cpu2);
		cpu2 = nullptr;
	}
	else
	{
		--quanta;
	}

}

//Função para remover o processo da RAM e lista de processos em execução
void Cpu::finaliza(Processo* acabado)
{
	for (auto i = so->ram.listaMem.begin(); i != so->ram.listaMem.end(); i++)
	{
		if (i->processo == acabado)
		{
			std::cout << "Liberando memoria de " << i->processo->nome << std::endl;
			i->estadoMemoria = VAZIO;
			i->processo = nullptr;
			//so->ram.uneElemVazios(i);
			break;
		}
	}
	for (auto i = so->begin(); i != so->end(); i++)
	{
		if (&(*i) == acabado)
		{
			std::cout << "Removendo " << i->nome << std::endl;

			so->lista.erase(i);
			break;
		}
	}
}