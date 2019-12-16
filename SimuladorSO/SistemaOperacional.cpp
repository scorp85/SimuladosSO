#include "SistemaOperacional.h"
#include <random>


SistemaOperacional::SistemaOperacional()
{
	std::ifstream MyReadFile("nomes.txt");
	std::string myText;

	while (getline(MyReadFile, myText))
	{
		listaDeNomes.push_back(myText);
	}
	MyReadFile.close();
}

void SistemaOperacional::geraProcessoNumerado(int nInstrucoes, int memoria)
{
	static int i = 0;
	lista.push_back(Processo("Processo " + std::to_string(i), nInstrucoes, memoria));
	++i;

	ram.bestFit(lista.back());
}

void SistemaOperacional::geraProcessoAleatorio()
{
	static std::default_random_engine generator;
	static std::uniform_int_distribution<int> geradorInstr(1, 200);
	static std::uniform_int_distribution<int> geradorMem(1024,150*1048576);
	static std::uniform_int_distribution<int> geradorNome(0, listaDeNomes.size() - 1);
	std::string nomeEscolhido = listaDeNomes[geradorNome(generator)];
	lista.push_back(Processo(nomeEscolhido.c_str(), geradorInstr(generator), geradorMem(generator)));
	ram.bestFit(lista.back());
}