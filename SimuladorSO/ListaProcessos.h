#pragma once

#include "Processo.h"
#include <list>
#include <vector>
#include <cstdlib>
#include <fstream>

class ListaProcessos
{
public:
	ListaProcessos();
	void geraProcessoNumerado(int nInstrucoes, int memoria);
	void geraProcessoAleatorio();
	auto begin() { return lista.begin(); }
	auto end() { return lista.end(); }

private:

	std::list<Processo> lista;
	std::vector<std::string> listaDeNomes;
};