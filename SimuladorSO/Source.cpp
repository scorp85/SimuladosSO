/*Criado usando o tutorial encontrado em http://lazyfoo.net/tutorials/SDL/ */
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
#include "CaixaTexto.h"

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
	TTF_Font* font = TTF_OpenFont("Hack-Regular.ttf", 80);
	SDL_Color corTexto = { 0,10,0 };

	CaixaTexto ram(renderer, font, 15,"Windows",60, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 6, 30, corTexto);
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
		SDL_Rect retanguloRAM = { 6, SCREEN_HEIGHT / 16, SCREEN_WIDTH-12, SCREEN_HEIGHT / 6 };
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
		//Função pra desenhar um retangulo cheio
		SDL_RenderFillRect(renderer, &retanguloRAM);
		SDL_Rect outlineRectRAM = { 6, SCREEN_HEIGHT / 16, SCREEN_WIDTH-12, SCREEN_HEIGHT / 6 };
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		//Função pra desenhar um retangulo vazio
		SDL_RenderDrawRect(renderer, &outlineRectRAM);

		SDL_Rect retanguloHD = { 6, SCREEN_HEIGHT / 3, SCREEN_WIDTH - 12, SCREEN_HEIGHT / 6 };
		SDL_SetRenderDrawColor(renderer, 0x22, 0x66, 0x22, 0xFF);
		//Função pra desenhar um retangulo cheio
		SDL_RenderFillRect(renderer, &retanguloHD);
		SDL_Rect outlineRectHD = { 6, SCREEN_HEIGHT / 3, SCREEN_WIDTH - 12, SCREEN_HEIGHT / 6 };
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		//Função pra desenhar um retangulo vazio
		SDL_RenderDrawRect(renderer, &outlineRectHD);

		//Escreve texto
		ram.render();
		//hd.render();
		//Atualiza
		SDL_RenderPresent(renderer);
	}

	TTF_CloseFont(font);

	ram.free();
	//hd.free();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	SDL_Quit();
	return 0;
}