#include "Disco.h"

void Disco::salvaEmDisco(Processo* processo)
{
	armazenamento.push_back(*processo);
}