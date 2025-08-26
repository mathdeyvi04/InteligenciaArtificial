#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SDL2/SDL.h>
#include <stdlib.h>
	
/**
 * @brief Representará os objetos de uma maneira geral e abstrata.
 */
class Object {
protected:

	int  x, y, w, h;
	SDL_Color color;

public:

	/**
	 * @brief Função estática para gerar números aleatórios.
	 */
	static int
	get_random(int min, int max){ return min + (rand() % (max - min + 1)); }

	/**
	 * @brief Construtor da Classe Objeto	
	 */
	Object(
		int _x,
		int _y,
		int _w,
		int _h
	) : x(_x),
		y(_y),
		w(_w),
		h(_h) 
	{}

	/**
	 * @brief Responsável por apresentar o objeto.	
	 */
	print(){
		
		SDL_rect rect = {x, y, w, h};
		SDL_SetRenderDrawColor()

	}
};

#endif // OBJECT_HPP