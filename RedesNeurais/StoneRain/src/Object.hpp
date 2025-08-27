#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SDL2/SDL.h>
#include <array>
#include <stdlib.h>
	
/**
 * @brief Representará os objetos de uma maneira geral e abstrata.
 */
class Object {
protected:

	SDL_Rect rect{0, 0, 15, 15};

	double pos[2]  = {0, 0};
	double vel[2]  = {0, 0};
	double acel[2] = {0, 0};

public:

	/**
	 * @brief Função estática para gerar números aleatórios.
	 */
	static int
	get_random(int min, int max){ return min + (rand() % (max - min + 1)); }

	Object() = default;

	/**
	 * @brief Construtor da Classe Objeto	
	 */
	Object(
		int _x,
		int _y,
		int _w,
		int _h
	) : rect{_x, _y, _w, _h},
		pos{(double)_x, (double)_y}
	{}

	/**
	 * @brief Getter do Retângulo	
	 */
	const SDL_Rect&
	get_rect() const { return rect; }

	/**
	 * @brief Setter das características cinemáticas
	 */
	void
	set_kinematic(
		int x,
		int y, 
		int vel_x,
		int vel_y,
		int acel_x,
		int acel_y
	){

		pos[0] = x;
		pos[1] = y;
		rect.x = x;
		rect.y = y;

		vel[0] = vel_x;
		vel[1] = vel_y;

		acel[0] = acel_x;
		acel[1] = acel_y;
	}

	/**
	 * @brief Responsável por apresentar o objeto.	
	 * @details
	 * 
	 * Executa individualmente o preenchimento do retângulo.
	 * Não se responsabiliza pela definição de cor.
	 */
	void
	print(
		SDL_Renderer* renderer
	){

		SDL_RenderFillRect(
			renderer,
			&rect
		);
	}

	/**
	 * @brief Responsável por analisar colisões	entre objetos.
	 * @param other_object Outro Objeto
	 */
	bool
	check_colision(
		const Object& other_object
	){
		return SDL_HasIntersection(
									&this->rect,
									&other_object.get_rect()
			                      );
	}

	/**
	 * @brief Responsável por prover a movimentação do objeto.	
	 * @param interv Intervalo de Tempo
	 */
	void
	move(
		double interv
	){	

		// Usamos intermediárias já que o rect aceita apenas inteiros
		// e com isso perderíamos precisão.
		vel[0] += acel[0] * interv;
		vel[1] += acel[1] * interv;
		pos[0] += vel[0] * interv;
		pos[1] += vel[1] * interv;

		rect.x = pos[0];
		rect.y = pos[1];
	}


};
	
/**
 * @brief Representará os obstáculos de chuva.
 * @tparam quant_de_obst Quantidade de Obstáculos
 * @details
 * 
 * Responsável por agrupar funcionalidades inerentes à chuva.
 */
template <int quant_de_obst>
class StoneRain {
private:

	std::array<Object, quant_de_obst> obsts;

public:

	/**
	 * @brief Construtor da Classe 
	 * @param lim_inf_x Limite inferior X dos objetos
	 * @param lim_sup_x Limite Superior X dos objetos
	 * @param lim_inf_y Limite Inferior Y dos objetos
	 * @param lim_sup_y Limite Superior Y dos objetos
	 */
	StoneRain(
		int lim_inf_x, 
		int lim_sup_x,
		int lim_inf_y,
		int lim_sup_y
	){

		for(
			int i = 0;
				i < quant_de_obst;
				i++
		){

			obsts[i].set_kinematic(
								   Object::get_random(lim_inf_x, lim_sup_x),
								   Object::get_random(lim_inf_y, lim_sup_y),
								   0,
								   10,  // Velocidade padrão da chuva
								   0, 
								   0
				                  );
		}
	}



	/**
	 * @brief Responsável por apresentar todos os elementos de chuva.	
	 * @param interv Intervalo de Tempo
	 */
	void
	move_and_print_rain(
		SDL_Renderer* renderer,
		double interv
	){

		for(
			int i = 0;
				i < quant_de_obst;
				i++
		){

			obsts[i].move(interv);
			obsts[i].print(renderer);
		}

	}


};

/**
 * @brief Representará nosso jogador, nossa rede neural.
 */
class Player : public Object {

};

#endif // OBJECT_HPP