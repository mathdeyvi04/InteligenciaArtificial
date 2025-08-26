#include "Graphicx.hpp"

int main(){

	Graphicx aplication(
		"Stone Rain",
		800, 600
	);

	while(
		aplication.if_is_running()
	){

		aplication.controll_fps();
		aplication.get_keys();
		aplication.set_renderer();

		// Implementação da Lógica


		aplication.set_renderer();
		aplication.controll_fps();
	}

	printf("\n");
	return 0;
}