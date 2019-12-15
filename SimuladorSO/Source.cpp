/*Criado usando o tutorial encontrado em http://lazyfoo.net/tutorials/SDL/ */
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
#include "CaixaTexto.h"
#include "ListaProcessos.h"
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::this_thread;
using namespace std::chrono;

//Objeto mutex
std::mutex mtx;

//Função usada na thread
void threadGeraProcesso(ListaProcessos& listaP, bool& quit)
{
	while (!quit)
	{
		//Função para dormir por 1 segundo
		sleep_until(system_clock::now() + seconds(1));
		mtx.lock();
		listaP.geraProcessoAleatorio();
		mtx.unlock();
	}
}

//Tamanho da janela
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 650;



int main(int argc, char* argv[])
{
	//Inicialização da biblioteca sdl
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow
	("Simulador de SO", // window's title
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
	CaixaTexto hd(renderer, font, 100, "HD", 20, SCREEN_HEIGHT / 4, SCREEN_WIDTH - 60, SCREEN_HEIGHT / 6, corTexto, corCaixa);
	CaixaTexto CPU1(renderer, font, 20, "CPU1", SCREEN_WIDTH - SCREEN_HEIGHT / 6 - 40, SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 6, SCREEN_HEIGHT / 6, corTexto, corCaixa);
	CaixaTexto CPU2(renderer, font, 20, "CPU2", SCREEN_WIDTH - SCREEN_HEIGHT / 6 - 40, SCREEN_HEIGHT / 2 + 120, SCREEN_HEIGHT / 6, SCREEN_HEIGHT / 6, corTexto, corCaixa);

	//Criação da lista de processos em execução
	ListaProcessos processosExecutando;
	//Criação de uma caixa de texto para representar a lista de processos em execução
	CaixaTexto caixaEmExec(renderer, font, 15, "xxxxxx", 30, 300, 400, 40, corTexto, corCaixa);

	

	
	//Booleano de controle, enquanto quit for falso o programa continua rodando
	bool quit = false;
	//Cria a thread
	std::thread th1(threadGeraProcesso, std::ref(processosExecutando), std::ref(quit));
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
		CPU1.render();
		CPU2.render();
		//Desenha a lista de processos em execução
		int posOri = caixaEmExec.getPosY();
		for (auto i = processosExecutando.begin(); i != processosExecutando.end(); i++)
		{
			caixaEmExec.setTexto((*i).nome);
			caixaEmExec.render();
			caixaEmExec.setPos(caixaEmExec.getPosX(), caixaEmExec.getPosY() + 40);
		}
		caixaEmExec.setPos(caixaEmExec.getPosX(), posOri);

		//Atualiza
		SDL_RenderPresent(renderer);
	}
	//Finaliza a thread
	th1.join();
	//fecha a fonte
	TTF_CloseFont(font);
	//Libera as texturas alocadas
	ram.free();
	hd.free();
	CPU1.free();
	CPU2.free();
	caixaEmExec.free();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	SDL_Quit();
	return 0;
}