#pragma once
/*Uma estrutura de dados para representar seus processos que dever� ter
	uma quantia de mem�ria (em bytes) que ele ocupa enquanto est� sendo 
	executado, o tipo do processo (I/O ou Programa) e a quantia de 
	instru��es que o programa possui.*/
enum TipoDeProcesso
{
	IO, PROCESSO
};
class Processo
{
public:
	//quantia de mem�ria (em bytes) que ele ocupa enquanto est� sendo executado
	int memoria;
	//quantia de instru��es que o programa possui
	int instrucoes;
	//tipo do processo(I/O ou Programa)
	TipoDeProcesso tipo;
};

