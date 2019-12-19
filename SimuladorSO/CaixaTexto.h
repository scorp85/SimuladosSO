#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

using std::string;

class CaixaTexto
{
public:
	CaixaTexto(SDL_Renderer* rndr, TTF_Font* fnt,int tamanhoF, const string tex, int pX, int pY, int tamanhoX, int tamanhoY, SDL_Color cor, SDL_Color corB, bool giro=false) : renderer(rndr), fonte(fnt), texto(tex), corTexto(cor), corCaixa(corB), flip(giro)
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(fonte, texto.c_str(), corTexto);
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_FreeSurface(textSurface);
		caixa.x = pX;
		caixa.y = pY;
		caixa.h = tamanhoY;
		caixa.w = tamanhoX;
		tamanhoFonte.h = tamanhoF;
		tamanhoFonte.w = tamanhoF * texto.size();
		tamanhoFonte.x = pX + (tamanhoX - tamanhoFonte.w) / 2;
		tamanhoFonte.y = pY + (tamanhoY - tamanhoF) / 2;
		if (flip)
		{
			tamanhoFonte.h = caixa.w;
			tamanhoFonte.w = caixa.w * texto.size();
			tamanhoFonte.x = 0;
			tamanhoFonte.y = 0;
		}
	}

	void setTexto(const string tex)
	{
		texto = tex;
		SDL_DestroyTexture(mTexture);
		SDL_Surface* textSurface = TTF_RenderText_Solid(fonte, texto.c_str(), corTexto);
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_FreeSurface(textSurface);

		tamanhoFonte.w = tamanhoFonte.h * texto.size();
		tamanhoFonte.x = caixa.x + (caixa.w - tamanhoFonte.w) / 2;
		tamanhoFonte.y = caixa.y + (caixa.h - tamanhoFonte.h) / 2;

	}
/*
	void setFonte(TTF_Font* font)
	{
		fonte = font;
		SDL_DestroyTexture(mTexture);
		SDL_Surface* textSurface = TTF_RenderText_Solid(fonte, texto.c_str(), corTexto);
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_FreeSurface(textSurface);
	}

	void setCor(SDL_Color novaCor)
	{
		corTexto = novaCor;
		SDL_DestroyTexture(mTexture);
		SDL_Surface* textSurface = TTF_RenderText_Solid(fonte, texto.c_str(), corTexto);
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_FreeSurface(textSurface);
	}
	*/
	void setTamanho(int novoTamanhoX, int novoTamanhoY)
	{
		caixa.w = novoTamanhoX;
		caixa.h = novoTamanhoY;
		tamanhoFonte.x = caixa.x + (caixa.w - tamanhoFonte.w) / 2;
		tamanhoFonte.y = caixa.y + (caixa.h - tamanhoFonte.h) / 2;
	}
	int getAlturaCaixa() { return caixa.h; }
	int getLarguraCaixa() { return caixa.w; }

	void setPos(int x, int y)
	{
		int difX = x - caixa.x;
		int difY = y - caixa.y;
		caixa.x += difX;
		caixa.y += difY;
		tamanhoFonte.x += difX;
		tamanhoFonte.y += difY;
	}

	int getPosX() {
		return caixa.x;
	}

	int getPosY() {
		return caixa.y;
	}

	void render()
	{
		SDL_SetRenderDrawColor(renderer, corCaixa.r, corCaixa.g, corCaixa.b, corCaixa.a);
		SDL_RenderFillRect(renderer, &caixa);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		static SDL_Rect contorno;
		contorno = SDL_Rect{ caixa.x,caixa.y,caixa.w + 1,caixa.h + 1 };
		SDL_RenderDrawRect(renderer,&contorno );

		SDL_SetRenderDrawColor(renderer, corTexto.r, corTexto.g, corTexto.b, corTexto.a);
		SDL_RendererFlip flipType = SDL_FLIP_NONE;
		if(flip)
			SDL_RenderCopyEx(renderer, mTexture, NULL, &tamanhoFonte,-90.0,NULL, flipType);
		else
			SDL_RenderCopyEx(renderer, mTexture, NULL, &tamanhoFonte, 0.0, NULL, flipType);
	}

	void free()
	{
		SDL_DestroyTexture(mTexture);
	}

private:
	SDL_Renderer* renderer;
	SDL_Texture* mTexture;
	TTF_Font* fonte;
	SDL_Rect tamanhoFonte;
	SDL_Color corTexto;
	SDL_Color corCaixa;
	SDL_Rect caixa;
	string texto;
	bool flip;
};

