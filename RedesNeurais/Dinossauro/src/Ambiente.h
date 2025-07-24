#ifndef AMBIENTE_H
#define AMBIENTE_H

#include "Graficos.h"

// Os obstáculos deverão ter comprimento constante, mas suas alturas e posições serão aleatórias.
#define WIDTH_OBS 10
#define MAX_HEIGTH_OBs 10

// Informações do sprite
#define WIDTH_PX 1600
#define HEIGTH_PX 87

class Ambiente {
	/*
	Descrição:
		Classe responsável por manutenir todo o ambiente e seus respectivos objetos.
	*/
public:

	class Objeto {
		/*
		Para cada obstáculo, entraremos com um conjunto de número que o representará.
		*/
	public:

		friend class Ambiente;

		// Vamos definir atributos padrões de cada objeto.



	};

	// 0 -> chão 1
	// 1 -> chão 2
	// 1 -> nuvem 1
	// 2 -> nuvem 2
	// 3 -> nuvem 3
	// . -> obstáculos
	Objeto conj_de_objetos[8];

	SDL_Texture *textura_geral;
	graphicx::Aplicacao aplication;

	Ambiente(
		graphicx::Aplicacao& aplication_
	){
		/*
		Responsável por inicializar elementos que não participarão
		da simulação.
		*/

		// Carregamos a imagem geral 
		SDL_Surface* surface = IMG_Load("src/sprite.png");
		if(!surface) { fprintf(stderr, "\nErro na Leitura da Sprite."); }
		textura_geral = SDL_CreateTextureFromSurface(aplication_.renderer, surface);
		if(!textura_geral) { fprintf(stderr, "\nErro na Construção da Textura."); }
		aplication = aplication_;

		// Devemos realizar os respectivos cortes.
		carregar_ambiente();



		SDL_FreeSurface(surface); // Liberamos pois não precisaremos mais.
	};

	void 
	carregar_ambiente(){
		/*
		Descrição:
			Responsável por realizar os cortes dos sprites e
			popular a lista de obstáculos.
		*/

		SDL_Rect corte_chao{0, 68, WIDTH_PX - 1, HEIGTH_PX - 1};
		SDL_Rect pos{0, 750, WIDTH_PX - 1, 25};

		
		SDL_RenderCopy(aplication.renderer, textura_geral, &corte_chao, &pos);
	}

	void
	destroy(){
		/*
		Descrição:
			Destruiremos todas as texturas e superfícies.
		*/

		if( textura_geral ) { SDL_DestroyTexture(textura_geral); }
	};

};

#endif // AMBIENTE_H