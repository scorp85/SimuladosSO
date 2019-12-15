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

std::mutex mtx;

void threadGeraProcesso(ListaProcessos& listaP, bool& quit)
{
	while (!quit)
	{
		
		sleep_until(system_clock::now() + seconds(1));
		mtx.lock();
		listaP.geraProcessoAleatorio();
		mtx.unlock();
	}
}

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 650;



int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);


	SDL_Window* window = SDL_CreateWindow
	("Simulador de SO", // window's title
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, // coordinates on the screen, in pixels, of the window's upper left corner
		SCREEN_WIDTH, SCREEN_HEIGHT, // window's length and height in pixels  
		SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	TTF_Init();
	//Fontes "monospaced" funcionam melhor
	TTF_Font* font = TTF_OpenFont("Hack-Regular.ttf", 400);
	SDL_Color corTexto = { 0,10,0, 100 };
	SDL_Color corCaixa = { 0x99, 0xff, 0x99, 0xFF };

	CaixaTexto ram(renderer, font, 100, "RAM", 20, SCREEN_HEIGHT / 16, SCREEN_WIDTH - 60, SCREEN_HEIGHT / 6, corTexto, corCaixa);
	CaixaTexto hd(renderer, font, 100, "HD", 20, SCREEN_HEIGHT / 4, SCREEN_WIDTH - 60, SCREEN_HEIGHT / 6, corTexto, corCaixa);
	CaixaTexto CPU1(renderer, font, 20, "CPU1", SCREEN_WIDTH - SCREEN_HEIGHT / 6 - 40, SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 6, SCREEN_HEIGHT / 6, corTexto, corCaixa);
	CaixaTexto CPU2(renderer, font, 20, "CPU2", SCREEN_WIDTH - SCREEN_HEIGHT / 6 - 40, SCREEN_HEIGHT / 2 + 120, SCREEN_HEIGHT / 6, SCREEN_HEIGHT / 6, corTexto, corCaixa);

	ListaProcessos processosExecutando;

	processosExecutando.geraProcessoAleatorio();

	CaixaTexto caixaEmExec(renderer, font, 15, "xxxxxx", 30, 300, 400, 40, corTexto, corCaixa);

	/*
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "RAM", corTexto);
	SDL_Texture *mTextureRAM = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	*/
	//CaixaTexto hd(renderer, font, 20, "teste1", 40, 40, 40, 40, corTexto);
	
	/*textSurface = TTF_RenderText_Solid(font, "HD", corTexto);
	SDL_Texture* mTextureHD = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	*/

	

	bool quit = false;
	//Cria a thread
	std::thread th1(threadGeraProcesso, std::ref(processosExecutando), std::ref(quit));
	SDL_Event e;
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
		

		//Escreve texto
		ram.render();
		hd.render();
		CPU1.render();
		CPU2.render();

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

	th1.join();
	TTF_CloseFont(font);

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