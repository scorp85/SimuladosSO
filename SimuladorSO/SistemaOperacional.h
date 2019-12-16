#pragma once

#include "Processo.h"
#include <list>
#include <vector>
#include <cstdlib>
#include <fstream>
#include "Memoria.h"
#include "Disco.h"

class SistemaOperacional
{
public:
	SistemaOperacional();
	void geraProcessoNumerado(int nInstrucoes, int memoria);
	void geraProcessoAleatorio();
	auto begin() { return lista.begin(); }
	auto end() { return lista.end(); }

private:

	std::list<Processo> lista;
	std::vector<std::string> listaDeNomes;
	Memoria ram;
	Disco hd;
};