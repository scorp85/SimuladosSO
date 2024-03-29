#pragma once
#include <set>
#include "Processo.h"
using std::set;
/*Uma estrutura de dados para representar o seu disco. Assuma que esse disco
	tem tamanho ilimitado e que voc� pode armazenar todos os processos que
	n�o cabem na sua mem�ria e que n�o est�o sendo utilizados no disco.*/
class Disco
{
public:
	void salvaEmDisco(Processo* processo);
	//Lista de Processos guardados em hd(swap).
	set<Processo*> armazenamento;
};