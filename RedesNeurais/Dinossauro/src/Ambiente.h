#ifndef AMBIENTE_H
#define AMBIENTE_H

#include "Graficos.h"

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
		int caso_seja_movel = 0;
		float vely = 0; 

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

					pos[0] = 0 + index * WIDTH_PX;
					pos[1] = 750;
					ratio_img[0]  = WIDTH_PX;
					ratio_img[1]  = 25;

					break;

				case 1:
					// Obstáculo Fixo

					id = 1;
					index_de_sprite = 6 + rand() % 2; 

					pos[0] = 1600 + index * 400;
					pos[1] = (index_de_sprite < 5) ? 720 : 710;
					ratio_img[0]  = 50;
					ratio_img[1]  = (index_de_sprite < 5) ? 70 : 60;

					break;

				case 2:
					// Obstáculo Móvel

					id = 2;
					index_de_sprite = 0; 

					pos[0] = 1600 + index * 400;
					pos[1] = 675;
					ratio_img[0]  = 50;
					ratio_img[1]  = 70;

					break;

				case 3:
					// Dinossauro

					id = 3;
					index_de_sprite = 0;

					pos[0] = 10;
					pos[1] = 705;
					ratio_img[0]  = 60;
					ratio_img[1]  = 70;

				default:
					break;
			}
		}

		void
		mover_se( int vel_do_ambiente, Objeto* obj_mais_distante_ ){
			/*
			Aplicaremos o movimento a cada um.
			*/

			if(
				id != 3
			){

				if( (pos[0] + ratio_img[0]) < 0 ) { Ambiente::algoritmo_de_reciclagem(this, obj_mais_distante_); }

				// Animação do obstáculo móvel.
				if(
					id == 2
				){

					if( caso_seja_movel == 7 ) { index_de_sprite = !index_de_sprite; caso_seja_movel = 0; } else { caso_seja_movel++; }
				}

				pos[0] -= vel_do_ambiente * graphicx::delta_time();

				return;
			}

			///////////////////////////////////////
			// Então, temos apenas dinossauro.

			// Animação do mesmo.
			if( caso_seja_movel == 7 ){

				// Então ele está em pé, ou, senão, estará agachado.
				if( index_de_sprite == 0 || index_de_sprite == 1 ){ index_de_sprite = 1 - index_de_sprite; } else { index_de_sprite = 5 - index_de_sprite; }

				caso_seja_movel = 0;				
			}
			else{
				caso_seja_movel++;
			}

			if(
				pos[1] <= 705
			){

				// Então estamos nos movimentando no ar.
				vely -= 650 * graphicx::delta_time();
				pos[1] -= vely * graphicx::delta_time();
			}
			else{

				pos[1] = 705;
				vely = 0;
			}
		}
	};

	// 0 -> chão 1
	// 1 -> chão 2
	// . -> obstáculos
	std::vector<Objeto> conj_de_objetos;

	SDL_Texture *textura_geral;
	graphicx::Aplicacao* aplication = nullptr;

	int VEL_AMBIENTE = 150;
	Objeto* obj_mais_distante = nullptr;

	int *respectivos_cortes = nullptr;
	int conj_de_sprites[4] = {0};

	int quant_de_obj_fixos = 10;
	int quant_de_obj_moveis = 5;
	int QUANT_DE_OBJ = 2 + quant_de_obj_fixos + quant_de_obj_moveis;

	Ambiente(
		graphicx::Aplicacao* aplication_
	){
		/*
		Responsável por inicializar elementos que não participarão
		da simulação.
		*/

		// Carregamos a imagem geral 
		SDL_Surface* surface = IMG_Load("src/sprite.png");
		if(!surface) { fprintf(stderr, "\nErro na Leitura da Sprite."); }
		textura_geral = SDL_CreateTextureFromSurface(aplication_->renderer, surface);
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

		// Populamos o chão
		conj_de_objetos.push_back(
			Objeto(
				&respectivos_cortes[conj_de_sprites[0]],
				0,
				0
			)
		);

		conj_de_objetos.push_back(
			Objeto(
				&respectivos_cortes[conj_de_sprites[0]],
				1,
				0
			)
		);

		// Com isso, conseguimos adicionar aleatoriedade na ordem.

		int idx_fixo = 0;
		int idx_movel = 0;
		while(
			idx_fixo < quant_de_obj_fixos || idx_movel < quant_de_obj_moveis
		){

			if(
				idx_fixo < quant_de_obj_fixos && rand() % 2
			){

				// Vamos colocar fixo.

				conj_de_objetos.push_back(
					Objeto(
						&respectivos_cortes[conj_de_sprites[1]],
						idx_fixo + idx_movel,
						1
					)
				);

				idx_fixo++;
				continue;
			}

			if(
				idx_movel < quant_de_obj_moveis
			){
				// Vamos colocar móvel.
				
				conj_de_objetos.push_back(
					Objeto(
						&respectivos_cortes[conj_de_sprites[2]],
						idx_movel + idx_fixo,
						2
					)
				);

				idx_movel++;
			}
		}

		// Sabemos que, no início, o último elemento adicionado na lista de objetos é 
		// o mais distante.
		obj_mais_distante = &conj_de_objetos.back();
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
			Responsável unicamente por mover os objetos e apresentá-los.

			Há dois loops, um para movê-los.
		*/

		// Ambiente deve esperar que dino tome decisão e aplique-a.
		sync_barrier.arrive_and_wait();

		int todos_ja_foram_movidos = 0;
		for(
			int i = 0;
				i < (int)conj_de_objetos.size();
				i++
		){

			if(
				!todos_ja_foram_movidos
			){

				conj_de_objetos[i].mover_se(VEL_AMBIENTE, obj_mais_distante);

				if( (i + 1) == (QUANT_DE_OBJ + QUANT_DINOS) ) { i = -1; todos_ja_foram_movidos = 1; }

				continue;
			}

			// Agora podemos decidir que está mais distante.
			if( conj_de_objetos[i].id != 3 && conj_de_objetos[i].id != 0 && conj_de_objetos[i].pos[0] > obj_mais_distante->pos[0] ) { obj_mais_distante = &conj_de_objetos[i]; }

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

			SDL_RenderCopy(aplication->renderer, textura_geral, &corte, &pos);
		}

		// Ambiente libera dinossauro.
		sync_barrier.arrive_and_wait();
	}

	static void
	algoritmo_de_reciclagem(
		Objeto* obj,
		Objeto* obj_mais_distante_
	){
		/*
		Descrição:
			Função responsável por prover o algoritmo de reciclagem 
			dos objetos dispostos.

			Em comentários, teremos versões anteriores.
		*/

		// O chão deve só seguir 
		if( !obj->id ) { obj->pos[0] = WIDTH; return; }  

		double distancia_a_ser_colocado_do_ultimo = 200.0 + (rand() % 150) * 2;
		fprintf(stderr, "\nAlocação: %.0lf", distancia_a_ser_colocado_do_ultimo);

		obj->pos[0] = obj_mais_distante_->pos[0] + distancia_a_ser_colocado_do_ultimo;
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