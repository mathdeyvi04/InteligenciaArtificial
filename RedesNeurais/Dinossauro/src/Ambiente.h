#ifndef AMBIENTE_H
#define AMBIENTE_H

#include "Graficos.h"

// Os obstáculos deverão ter comprimento constante, mas suas alturas e posições serão aleatórias.
#define WIDTH_OBS 30
#define MAX_HEIGTH_OBs 10
#define QUANT_DE_OBJ 1

// Informações do sprite
#define WIDTH_PX WIDTH
#define HEIGTH_PX 87

class Ambiente {
	/*
	Descrição:
		Classe responsável por manutenir todo o ambiente e seus respectivos objetos.
	*/
public:

	class Objeto {
		/*
		Para cada objeto:
		
		-> id: representando o que ele é.
			0 - chão
			1 - nuvem
			2 - obstáculo
		-> cinematica: posx, posy, velx, vely, ay.
		-> cortes_de_sprites: conj de quadruplas que representam as sprites.
			A essa altura, já saberemos quem é quem.
		*/
	public:

		friend class Ambiente;

		// Vamos definir atributos padrões de cada objeto.

		float cinematica[5] = {0, 0, 0, 0, - 1.5};
		int id = 0;
		int index_de_sprite = 0;
		int *cortes_de_sprites = nullptr;
		int ratio_img[2] = {0};

		Objeto() = default;

		Objeto(
			int& index,
			int *args
		){

			if(
				// Temos o chão
				index == 0 || index == 1
			){

				id = 0; 
				index_de_sprite = 0;
				cortes_de_sprites = &args[index + 1];

				cinematica[0] = 0 + index * WIDTH_PX;
				cinematica[1] = 750;
				ratio_img[0]  = WIDTH_PX - 1;
				ratio_img[1]  = 25;
			}
		}
	};

	// 0 -> chão 1
	// 1 -> chão 2
	// 1 -> nuvem 1
	// 2 -> nuvem 2
	// 3 -> nuvem 3
	// . -> obstáculos
	Objeto conj_de_objetos[QUANT_DE_OBJ];

	SDL_Texture *textura_geral;
	graphicx::Aplicacao aplication;

	int *respectivos_cortes = nullptr;

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

		// Devemos realizar os respectivos cortes e posicionamentos iniciais.
		_carregar_cortes_e_posicao_inicial();
		_carregar_ambiente();

		SDL_FreeSurface(surface); // Liberamos pois não precisaremos mais.
	};

	void 
	_carregar_ambiente(){
		/*
		Descrição:
			Responsável por realizar os cortes dos sprites e
			popular a lista de obstáculos.

			-> respectivos_cortes[]:
				quantidade_de_quadruplas_que_representam_sprites, sprites..., pos_inicial

			A informação de quantas sprites existem é útil aqui para automatizarmos a leitura.
		*/

		int index = 0;
		while(
			respectivos_cortes[index] != 0
		){

			conj_de_objetos[index] = Objeto(
				index,
				respectivos_cortes
			);

			index += 4 * (respectivos_cortes[index] + 1) + 1;
		}
	}

	void
	_carregar_cortes_e_posicao_inicial(){
		/*
		Infelizmente, vamos ter que aceitar o tamanho da janela.
		Construiremos um arquivo de texto com os dados.
		*/

		FILE *arquivo = fopen("src/cortes_de_sprites_e_posicoes.txt", "r");

		int valor = 0;
		int count = 0;
		while(
			fscanf(arquivo, "%d", &valor) == 1
		){
			// fprintf(stderr, "\nEstou vendo:%d", valor);
			
			// Há pelo menos 1 elemento
			respectivos_cortes = (int*) realloc(respectivos_cortes, (count + 1) * sizeof(int));

			respectivos_cortes[count] = valor;
			count++;
		}

		fclose(arquivo);
	}

	void 
	apresentar_ambiente(){
		/*
		Descrição:
			Responsável unicamente por apresentar todo o ambiente.
		*/

		for(
			int i = 0;
				i < QUANT_DE_OBJ;
				i++
		){
			SDL_Rect corte{
				conj_de_objetos[i].cortes_de_sprites[0 + 4 * conj_de_objetos[i].index_de_sprite],
				conj_de_objetos[i].cortes_de_sprites[1 + 4 * conj_de_objetos[i].index_de_sprite],
				conj_de_objetos[i].cortes_de_sprites[2 + 4 * conj_de_objetos[i].index_de_sprite],
				conj_de_objetos[i].cortes_de_sprites[3 + 4 * conj_de_objetos[i].index_de_sprite]				
			};

			SDL_Rect pos{
				(int)conj_de_objetos[i].cinematica[0],
				(int)conj_de_objetos[i].cinematica[1],
				conj_de_objetos[i].ratio_img[0],
				conj_de_objetos[i].ratio_img[1]
			};

			SDL_RenderCopy(aplication.renderer, textura_geral, &corte, &pos);
		}

	}

	void
	destroy(){
		/*
		Descrição:
			Destruiremos todas as texturas e superfícies.
		*/
		if( respectivos_cortes ) { free(respectivos_cortes); }
		if( textura_geral ) { SDL_DestroyTexture(textura_geral); }
	};

};

#endif // AMBIENTE_H