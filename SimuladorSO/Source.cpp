/*Criado usando o tutorial encontrado em http://lazyfoo.net/tutorials/SDL/ */
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include "SDL.h"
#include "SDL_ttf.h"
#include "CaixaTexto.h"
#include "SistemaOperacional.h"
#include "Cpu.h"


using namespace std::this_thread;
using namespace std::chrono;
const double normalizador = 0.000001154839992523193359375;
//Objeto mutex
std::mutex mtx;

//Função usada na thread
void threadGeraProcesso(SistemaOperacional& listaP, bool& quit)
{
	//sleep_until(system_clock::now() + seconds(1));
	while (!quit)
	{
		//Função para dormir por 1 segundo
		sleep_until(system_clock::now() + seconds(2));
		mtx.lock();
		listaP.geraProcessoAleatorio();
		mtx.unlock();
	}
}

void threadRoundRobin(Cpu &cpu, bool &quit)
{
	sleep_until(system_clock::now() + seconds(1));
	while (!quit)
	{
		mtx.lock();
		cpu.atualizaFila();
		cpu.preExecutaCPU1();
		cpu.preExecutaCPU2();
		mtx.unlock();
		sleep_until(system_clock::now() + seconds(1));
		mtx.lock();
		cpu.executaCPU1();
		cpu.executaCPU2();
		mtx.unlock();
	}
}

//Tamanho da janela
const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 650;



int main(int argc, char* argv[])
{
	//Inicialização da biblioteca sdl
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow
	("Simulador SO", // window's title
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, // coordinates on the screen, in pixels, of the window's upper left corner
		SCREEN_WIDTH, SCREEN_HEIGHT, // window's length and height in pixels  
		SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	//Inicialização da biblioteca de fontes
	TTF_Init();
	//Fontes "monospaced" funcionam melhor
	TTF_Font* font = TTF_OpenFont("Hack-Regular.ttf", 400);

	//Cores usadas nas caixas e nos textos
	SDL_Color corTexto = { 0,10,0, 100 };
	SDL_Color corCaixa = { 0x99, 0xff, 0x99, 0xFF };

	//Criação das caixas de texto "ram", "hd"...
	CaixaTexto ram(renderer, font, 100, "RAM", 20, SCREEN_HEIGHT / 16, SCREEN_WIDTH - 60, SCREEN_HEIGHT / 6, corTexto, corCaixa);
	corCaixa = SDL_Color{ 0x99, 0x99, 0xff, 0xFF };
	CaixaTexto hd(renderer, font, 100, "HD", 20, SCREEN_HEIGHT / 4, SCREEN_WIDTH - 60, SCREEN_HEIGHT / 6, corTexto, corCaixa);
	corCaixa = SDL_Color{ 0xdd, 0xdd, 0x99, 0xFF };
	CaixaTexto CPU1(renderer, font, 20, "CPU1", SCREEN_WIDTH - SCREEN_HEIGHT / 6 - 40, SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 6, SCREEN_HEIGHT / 6, corTexto, corCaixa);
	CaixaTexto CPU2(renderer, font, 20, "CPU2", SCREEN_WIDTH - SCREEN_HEIGHT / 6 - 40, SCREEN_HEIGHT / 2 + 120, SCREEN_HEIGHT / 6, SCREEN_HEIGHT / 6, corTexto, corCaixa);

	//Criação da lista de processos em execução
	SistemaOperacional processosExecutando;
	//Criação de uma caixa de texto para representar a lista de processos em execução
	corCaixa = SDL_Color{ 0xdd, 0xdd, 0xdd, 0xFF };
	CaixaTexto caixaEmExec(renderer, font, 15, "", 30, 300, 400, 20, corTexto, corCaixa);

	//Criação de uma caixa de texto para representar a lista de processos na RAM
	corCaixa = SDL_Color{ 0xaa, 0xdd, 0xaa, 0xFF };
	CaixaTexto caixaEmRam(renderer, font, 15, "", 20, SCREEN_HEIGHT / 16, 10, SCREEN_HEIGHT / 6, corTexto, corCaixa, true);
	
	//Criação de uma caixa de texto para representar a lista de processos no HD
	corCaixa = SDL_Color{ 0xaa, 0xaa, 0xdd, 0xFF };
	CaixaTexto caixaEmHd(renderer, font, 15, "", 20, SCREEN_HEIGHT / 4, 10, SCREEN_HEIGHT / 6, corTexto, corCaixa, true);
	
	//Cria a CPU
	Cpu ryzen(&processosExecutando);

	//Booleano de controle, enquanto quit for falso o programa continua rodando
	bool quit = false;
	//Cria a thread
	std::thread th1(threadGeraProcesso, std::ref(processosExecutando), std::ref(quit));
	std::thread th2(threadRoundRobin, std::ref(ryzen), std::ref(quit));
	//Variavel SDL para armazenar eventos
	SDL_Event e;
	//Loop principal do programa
	while (!quit)
	{
		//Eventos
		while (SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
				quit = true;
			else if(e.type == SDL_KEYDOWN)
				switch (e.key.keysym.sym)
				{
				case SDLK_1:
					//Tecla 1 apertada, crie um processo com 1 instrução e 100 Bytes de memória
					
					break;
				case SDLK_2:
					//Tecla 1 apertada, crie um processo com 10 instrução e 1 MByte de memória
					break;
				case SDLK_3:
					//Tecla 1 apertada, crie um processo com 30 instrução e 150 MBytes de memória
					break;
				default:
					break;
				}
		}
		//ATUALIZAÇÃO DA TELA
		//
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		//Limpa
		SDL_RenderClear(renderer);
		//Desenha
		

		//Desenha as caixas
		ram.render();
		hd.render();
		mtx.lock();
		if (ryzen.cpu1 != nullptr)
		{
			CPU1.setTexto(ryzen.cpu1->nome);
		}
		CPU1.render();
		if (ryzen.cpu2 != nullptr)
		{
			CPU2.setTexto(ryzen.cpu2->nome);
		}
		CPU2.render();
		//Desenha a lista de processos em execução
		int posOri = caixaEmExec.getPosY();
		for (auto i = processosExecutando.begin(); i != processosExecutando.end(); i++)
		{
			caixaEmExec.setTexto(i->nome);
			caixaEmExec.render();
			caixaEmExec.setPos(caixaEmExec.getPosX(), caixaEmExec.getPosY() + 20);
		}
		caixaEmExec.setPos(caixaEmExec.getPosX(), posOri);

;
		for (auto i = processosExecutando.ram.listaMem.begin(); i != processosExecutando.ram.listaMem.end(); i++)
		{
			if (i->estadoMemoria == VAZIO)
				continue;
			caixaEmRam.setTexto((i->processo)->nome);
			caixaEmRam.setTamanho(i->tamanho *normalizador, caixaEmRam.getAlturaCaixa());

			caixaEmRam.setPos(20 + i->indice*normalizador, caixaEmRam.getPosY());
			caixaEmRam.render();
		}

		int posOriHD = caixaEmHd.getPosX();
		for (auto i = processosExecutando.hd.armazenamento.begin(); i != processosExecutando.hd.armazenamento.end(); i++)
		{
			caixaEmHd.setTexto((*i)->nome);
			caixaEmHd.render();
			caixaEmHd.setPos(caixaEmHd.getPosX() + 15, caixaEmHd.getPosY());
		}
		mtx.unlock();
		caixaEmHd.setPos(posOriHD, caixaEmHd.getPosY());


		//Atualiza
		SDL_RenderPresent(renderer);
	}
	//Finaliza a thread
	th1.join();
	th2.join();
	//fecha a fonte
	TTF_CloseFont(font);
	//Libera as texturas alocadas
	ram.free();
	hd.free();
	CPU1.free();
	CPU2.free();
	caixaEmExec.free();
	caixaEmRam.free();
	caixaEmHd.free();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	SDL_Quit();
	return 0;
}