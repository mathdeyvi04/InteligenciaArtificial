#ifndef AMBIENTE_H
#define AMBIENTE_H

#include "Graficos.h"

// Os obstáculos deverão ter comprimento constante, mas suas alturas e posições serão aleatórias.
#define WIDTH_OBS 30
#define MAX_HEIGTH_OBs 10

// Informações do sprite
#define WIDTH_PX WIDTH
#define HEIGTH_PX 87

class Ambiente {
	/*
	Descrição:
		Classe responsável por manutenir todo o ambiente e seus respectivos objetos.
	*/
	friend class Objeto;
public:

	class Objeto {
		/*
		Para cada objeto:
		
		-> id: representando o que ele é.
			0 - chão
			1 - obstáculo fixo
			2 - obstáculo móvel
			3 - dinossauro
		-> pos: posx, posy
		-> cortes_de_sprites: conj de quadruplas que representam as sprites.
			A essa altura, já saberemos quem é quem.
		*/
	public:

		friend class Ambiente;

		// Vamos definir atributos padrões de cada objeto.

		float pos[2] = {0, 0};
		int id = 0;
		int index_de_sprite = 0;
		int *cortes_de_sprites = nullptr;
		int ratio_img[2] = {0};

		Objeto() = default;

		Objeto(
			// Estes imediatamente são para armazenarmos os ponteiros.
			int *conj_de_sprites,
			int index,
			int id_
		){

			cortes_de_sprites = conj_de_sprites;

			switch(id_){

				case 0:
					// Chão

					id = 0; 
					index_de_sprite = 0;

					pos[0] = 0 + index * (WIDTH_PX - 2);
					pos[1] = 750;
					ratio_img[0]  = WIDTH_PX - 1;
					ratio_img[1]  = 25;

					break;

				case 1:
					// Obstáculo Fixo

					id = 1;
					index_de_sprite = rand() % 9; 

					pos[0] = 1600 + (index - 2) * 200;
					pos[1] = 710;
					ratio_img[0]  = 50;
					ratio_img[1]  = 70;

					break;

				case 2:
					// Obstáculo Móvel

					break;

				default:
					break;
			}
		}

		void
		mover_se( int vel ){
			/*
			Aplicaremos o movimento a cada um.
			*/

			if( (pos[0] + ratio_img[0]) < 0 ) { pos[0] = WIDTH; }

			pos[0] -= vel * graphicx::delta_time();
		}
	};

	// 0 -> chão 1
	// 1 -> chão 2
	// . -> obstáculos
	std::vector<Objeto> conj_de_objetos;

	SDL_Texture *textura_geral;
	graphicx::Aplicacao aplication;

	int VEL_AMBIENTE = 150;

	int *respectivos_cortes = nullptr;
	int conj_de_sprites[4] = {0};

	int QUANT_DE_OBJ = 2 + 5;
	int quant_populada = 0;

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
		_carregar_cortes();
		_popular_ambiente();

		SDL_FreeSurface(surface); // Liberamos pois não precisaremos mais.
	};

	void 
	_popular_ambiente(){
		/*
		Descrição:
			Responsável por popular a lista de obstáculos.
		*/

		int index = 0;
		while(
			index < QUANT_DE_OBJ
		){

			if(
				index == 0 || index == 1
			){

				conj_de_objetos.push_back(
					Objeto(
						&respectivos_cortes[conj_de_sprites[0]],
						index,
						0
					)
				);

				quant_populada++;
			}
			else{

				// Lógica para móveis e fixos.
				// Proporção de 5 fixos para cada móvel. Depois podemos adicionar aleatoriedade.
				bool is_fixed = 1;

				conj_de_objetos.push_back(
					Objeto(
						&respectivos_cortes[conj_de_sprites[(is_fixed) ? 1 : 2]],
						index,
						(is_fixed) ? 1 : 2
					)
				);

				quant_populada++;
			}

			index++;
		}

	}

	void
	_carregar_cortes(){
		/*
		Descrição:
			Obteremos os cortes realizados.
		*/

		FILE *arquivo = fopen("src/cortes_de_sprites.txt", "r");
		if(!arquivo) { fprintf(stderr, "Erro na Leitura do Arquivo.txt de Sprites."); return; }

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


		valor = 0;
		count = 0;
		while(
			respectivos_cortes[count] != 0
		){

			// Guardaremos o índice que o sprite começa
			conj_de_sprites[valor] = count + 1;

			valor++;
			count += 4 * respectivos_cortes[count] + 1;
		}
	}

	void 
	apresentar_ambiente(){
		/*
		Descrição:
			Responsável unicamente por apresentar todo o ambiente.
		*/

		for(
			int i = 0;
				i < quant_populada;
				i++
		){

			conj_de_objetos[i].mover_se(VEL_AMBIENTE);		

			// Devemos verificar se a imagem é vísivel. Caso não, não devemos desenhá-la.
			if( conj_de_objetos[i].pos[0] > WIDTH ){ continue; }

			SDL_Rect corte{
				conj_de_objetos[i].cortes_de_sprites[0 + 4 * conj_de_objetos[i].index_de_sprite],
				conj_de_objetos[i].cortes_de_sprites[1 + 4 * conj_de_objetos[i].index_de_sprite],
				conj_de_objetos[i].cortes_de_sprites[2 + 4 * conj_de_objetos[i].index_de_sprite],
				conj_de_objetos[i].cortes_de_sprites[3 + 4 * conj_de_objetos[i].index_de_sprite]				
			};

			SDL_Rect pos{
				(int)conj_de_objetos[i].pos[0],
				(int)conj_de_objetos[i].pos[1],
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