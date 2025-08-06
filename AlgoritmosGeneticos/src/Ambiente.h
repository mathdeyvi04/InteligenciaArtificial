#ifndef AMBIENTE_H
#define AMBIENTE_H

#include "Mother.h"
#include <SDL2/SDL.h>

class Janela {
	/*
	Descrição:
		Responsável por aglutinar responsabilidades da Janela.
	*/

public:
	~Janela() {} 

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	bool is_running;

	Janela(){

		window = SDL_CreateWindow(
			"Evoluções",
        	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        	TAMANHO, TAMANHO,
        	0
        );

    	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		is_running = 1;
	}

	bool 
	get_keys(){
		/*
		Descrição:
			Responsável por adquirir entradas do usuário.

		Retorno:
			True -> Caso Haja Clique
			False  -> Qualquer Outro Caso
		*/

		while(SDL_PollEvent(&event) != 0) {

			if( event.type == SDL_QUIT ){
				is_running = 0;
			}

			if( event.type == SDL_MOUSEBUTTONDOWN ){
				// Ok, avançar.

				return True;
			}

	    }

		// Qualquer outro caso
		return False;
	}

	void 
	desenhar(int x, int y){
		/*
		Descrição:
			Algoritmo responsável por printarmos o quadrado
			correspondente à ponto.
		*/

		SDL_Rect rect{x - TAM / 2, y - TAM / 2, TAM, TAM};

		SDL_RenderDrawRect(renderer, &rect);     // Contorno
		SDL_RenderFillRect(renderer, &rect);     // Preenchido
	}

	void 
	apresentar_pontos(
		int* points,
		int quant_pontos,
		int especial
	){
		/*
		Descrição:
			Apresentará os pontos bidimensionais.
		*/

		for(
			int i = 0;
				i < 2 * quant_pontos;
				i += 2
		){

			if( i == especial ){

				SDL_SetRenderDrawColor(renderer, 3, 144, 252, 255);
			}
			else{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			}

			desenhar(
				points[i],
				points[i + 1]
			);
		}
	}

	void 
	encerrar(){
		SDL_DestroyRenderer(renderer);
	    SDL_DestroyWindow(window);
	    SDL_Quit();
	}
};

#endif // AMBIENTE_H