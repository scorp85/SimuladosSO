#pragma once
/*Uma estrutura de dados para representar seus processos que deverá ter
	uma quantia de memória (em bytes) que ele ocupa enquanto está sendo 
	executado, o tipo do processo (I/O ou Programa) e a quantia de 
	instruções que o programa possui.*/
enum TipoDeProcesso
{
	IO, PROCESSO
};
class Processo
{
public:
	//quantia de memória (em bytes) que ele ocupa enquanto está sendo executado
	int memoria;
	//quantia de instruções que o programa possui
	int instrucoes;
	//tipo do processo(I/O ou Programa)
	TipoDeProcesso tipo;
};

