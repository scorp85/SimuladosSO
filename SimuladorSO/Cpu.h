#pragma once
#include <list>
#include "Processo.h"
#include "SistemaOperacional.h"

using std::list;

class Cpu
{
public:
	Cpu(SistemaOperacional*);
	//Insere novos processos na fila de RoundRobin
	void atualizaFila();
	//Prepara o processo para ser executado
	void preExecutaCPU1();
	//Executa o processo
	void executaCPU1();
	//Prepara o processo para ser executado
	void preExecutaCPU2();
	//Executa o processo
	void executaCPU2();

	Processo* cpu1;
	Processo* cpu2;
private:
	Processo* selecionaProximoProcesso();
	void finaliza(Processo*);
	list<Processo*> rrList;
	SistemaOperacional* so;
	int quanta;
};

//Percorre a lista de processos do sistema operacional em busca de
//processos PRONTOS que ainda não estão na sua lista de roundrobin

//Pega o primeiro elemento da lista de round robin e verifica se está
//em ram.
	//Se não estiver faz swap
//Remove o processo selecionado da lista, incrementa o numero de instruções
//executadas do processo e dorme por 1 segundo

//Verifica se a quantidade de instruções executadas é igual a quantidade
//de instruções totais do processo
	//Se for finaliza o processo
	//Se não for insere o processo no fim da fila de roundrobin