#pragma once
#include <string>
/*Uma estrutura de dados para representar seus processos que deverá ter
	uma quantia de memória (em bytes) que ele ocupa enquanto está sendo 
	executado, o tipo do processo (I/O ou Programa) e a quantia de 
	instruções que o programa possui.*/
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
	//quantia de memória (em bytes) que ele ocupa enquanto está sendo executado
	int memoria;
	//quantia de instruções que o programa possui
	int instrucoes;
	//tipo do processo(I/O ou Programa)
	EstadoProcesso estado;
	std::string nome;
};

