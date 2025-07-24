#ifndef GRAFICOS_H
#define GRAFICOS_H

#include "importacoes.h"

#define WIDTH 1600
#define HEIGTH 900

namespace graphicx {
	/*
	Não acho que seria uma escolha mantermos uma classe com essas responsabilidades.
	Entretanto, sei da necessidade de organizá-las. Sendo assim, propus um namespace.
	*/

	struct Aplicacao {
		SDL_Window* window;
		SDL_Renderer* renderer;
		TTF_Font* font;
		int is_running;
	};

	// Como só uma thread terá acesso, estará tudo bem.
	// Teremos um limite para esse cara também.
	struct FPSController {
		int FPS;
		double interv;
		double ultimo_frame;

		int ultimo_fps_printado;
		char fps_texto[8];
		SDL_Surface *surf;
		SDL_Texture *text;
		SDL_Rect rect;

	};

	FPSController fps_controller{
		30,
		1000 / 30,
		0,
		
		0,
		{0},
		nullptr,
		nullptr,
		{0, 0, 0, 0}
	};

	SDL_Event evento;

	int overboost = 1;

	Aplicacao
	init_aplication(){
		/*
		Descrição:
			Iniciar a aplicação gráfica.
		*/

		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	        return {NULL, NULL, NULL, 0};
	    }

	    TTF_Init();
	    IMG_Init(IMG_INIT_PNG);

	    SDL_Window* window = SDL_CreateWindow(
	        "Simulação da Rede Neural",
	        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
	        WIDTH, HEIGTH, 
	        0
	    );

	    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	    TTF_Font* font = TTF_OpenFont("src/Roboto-Regular.ttf", 20);
	    if(!font) { fprintf(stderr, "Erro ao carregar fonte: %s\n", TTF_GetError()); }

	    return {window, renderer, font, 1};
	}

	inline void
	destroy_aplication(
		Aplicacao& aplication 
	){
		/*
		Descrição:
			Destruir a aplicação gráfica da maneira correta.
		*/


		// 1. Destruir as texturas, caso haja alguma.

		// 2. Fechar fontes
		if( aplication.font     ) { TTF_CloseFont(aplication.font);           }

		// 3. Fechar Janela e Renderer
		if( aplication.renderer ) { SDL_DestroyRenderer(aplication.renderer); }
	    if( aplication.window   ) { SDL_DestroyWindow(aplication.window);     }

	    TTF_Quit();
	    IMG_Quit();
	    SDL_Quit();
	}

	inline void 
	get_keys(
		Aplicacao& aplication
	){

		while (SDL_PollEvent(&evento)) {
	        if(evento.type == SDL_QUIT)
	            aplication.is_running = false;

	        if (evento.type == SDL_KEYDOWN) {
	            if (evento.key.keysym.sym == SDLK_UP && fps_controller.FPS < 95) {
	                fps_controller.FPS += 5;
					fps_controller.interv = 1000 / fps_controller.FPS;
					continue;
	            }
	            if (evento.key.keysym.sym == SDLK_DOWN && fps_controller.FPS > 5) {
	                fps_controller.FPS -= 5;
					fps_controller.interv = 1000 / fps_controller.FPS;
					continue;
	            }
	            if (evento.key.keysym.sym == SDLK_RIGHT && overboost < 5) {
	               	overboost += 1;
	               	continue;
	            }
	            if (evento.key.keysym.sym == SDLK_LEFT && overboost > 1) {
	               	overboost -= 1;
	               	continue;
	            }

	        }
	    }
	}

	inline void 
	sync_fps(
		Aplicacao& aplication
	){
		/*
		Descrição:
			Responsável por sincronizar a velocidade da aplicação e
			apresentar a informação de FPS na tela.

			Deve estar necessariamente ao final do loop principal.
		*/

		////////////////////////////////////////////////////////////////////
		// Apresentaremos aqui para não afetar intervalos.

		if(
			fps_controller.FPS != fps_controller.ultimo_fps_printado
		){

			snprintf(fps_controller.fps_texto, sizeof(fps_controller.fps_texto), "FPS: %d", fps_controller.FPS);

			if( fps_controller.surf ) { SDL_FreeSurface(fps_controller.surf);    }
			if( fps_controller.text ) { SDL_DestroyTexture(fps_controller.text); }

			fps_controller.surf = TTF_RenderText_Blended(aplication.font, fps_controller.fps_texto, {0, 0, 0});
			if(!fps_controller.surf) { fprintf(stderr, "Erro ao renderizar texto: %s\n", TTF_GetError()); }

			fps_controller.text = SDL_CreateTextureFromSurface(aplication.renderer, fps_controller.surf);

			fps_controller.rect = {
				WIDTH - fps_controller.surf->w - 10,
				HEIGTH - fps_controller.surf->h - 10,
				fps_controller.surf->w,
				fps_controller.surf->h
			};

			fps_controller.ultimo_fps_printado = fps_controller.FPS;
		}

		SDL_RenderCopy(aplication.renderer, fps_controller.text, nullptr, &fps_controller.rect);
		
		/////////////////////////////////////////////////////////////////////

		double tempo_passado = SDL_GetTicks() - fps_controller.ultimo_frame;

		if( tempo_passado < fps_controller.interv ){ SDL_Delay(fps_controller.interv - tempo_passado); /* fprintf(stderr, "\nParei por %lf", fps_controller.interv - tempo_passado); */ }

		fps_controller.ultimo_frame = SDL_GetTicks();
	}

	double
	delta_time(){ return fps_controller.interv * 0.001 * overboost; }
};






#endif // GRAFICOS_H