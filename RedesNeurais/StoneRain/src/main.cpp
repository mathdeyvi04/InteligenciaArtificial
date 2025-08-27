#include "Graphicx.hpp"
#include "Object.hpp"

int main(){

	Graphicx aplication(
		"Stone Rain",
		800, 600
	);

	StoneRain<20> exe(
					  0,
					  aplication.get_width(),
					  0,
					  aplication.get_height()
					 );

	while(
		aplication.if_is_running()
	){

		aplication.controll_fps();
		aplication.get_keys();
		aplication.set_renderer();

		// Implementação da Lógica
		SDL_SetRenderDrawColor(aplication.get_renderer(), 0, 0, 0, 255);

		// Avanço do tempo
		exe.move_and_print_rain(aplication.get_renderer(), aplication.get_delta_time());


		aplication.set_renderer();
		aplication.controll_fps();
	}

	printf("\n");
	return 0;
}