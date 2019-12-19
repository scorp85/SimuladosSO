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

	std::list<Processo> lista;

	Memoria ram;
	Disco hd;
private:
	std::vector<std::string> listaDeNomes;

};