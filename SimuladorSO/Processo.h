#pragma once
#include <string>
/*Uma estrutura de dados para representar seus processos que dever� ter
	uma quantia de mem�ria (em bytes) que ele ocupa enquanto est� sendo 
	executado, o tipo do processo (I/O ou Programa) e a quantia de 
	instru��es que o programa possui.*/
enum EstadoProcesso
{
	NOVO, BLOQUEADO, EXECUTANDO, PRONTO
};
class Processo
{
public:
	Processo(std::string n, int i, int m):nome(n), instrucoes(i), memoria(m)
	{
		estado = NOVO;
	}
	//quantia de mem�ria (em bytes) que ele ocupa enquanto est� sendo executado
	int memoria;
	//quantia de instru��es que o programa possui
	int instrucoes;
	//tipo do processo(I/O ou Programa)
	EstadoProcesso estado;
	std::string nome;
};

