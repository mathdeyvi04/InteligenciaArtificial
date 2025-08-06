#include "src/Ambiente.h"
#include <time.h>

void
apresentation_points(){
	/*
	Descrição:
		Caso desejado pelo usuário, providenciará 
		a apresentação da aplicação para o caso 2D.
	*/
	Janela janela;

	Mother mae;

	while( janela.is_running ){

		if( janela.get_keys() ){
			// Então houve um clique.

			float dist_sq_media = mae.gerar_novo_conj(SDL_GetMouseState);
			fprintf(stderr, "\nDist Quadrática Média / Área: %f", dist_sq_media);
		}

		// Vamos renderizar.

		SDL_SetRenderDrawColor(janela.renderer, 255, 255, 255, 255);  // fundo
        SDL_RenderClear(janela.renderer);

        janela.apresentar_pontos(mae.points, mae.QUANT_PONTOS, mae.indice_especial);

        SDL_RenderPresent(janela.renderer);
		SDL_Delay(100);
	}

	mae.encerrar();
	janela.encerrar();
}

void
simulation_points(int dimension, int quant_de_pontos, int param_convergence){
	/*
	Forneceremos uma descrição mais apropriada dentro do pybind11.
	*/

	int n_gen = 0;
	Mother mae;
	mae.DIMENSION = dimension;
	mae.QUANT_PONTOS = quant_de_pontos;

	// Devemos criar uma forma de centralizar a execução apenas no algoritmo.
	




	mae.encerrar();
}


int main(int argc, char* argv[]){
	/*
	Descrição:
		Responsável por executar a simulação de diferentes formas.

	Parâmetros:
		-> ./main
			Executará uma apresentação 2D.

		-> ./main N_1 N_2 N_3
			Retornará um número indicando a quantidade de gerações
			necessárias para que a quantidade N_2 de pontos em um espaço
			de N_1 dimensões atinjam a convergência a partir de um 
			parâmetro N_3.
	*/

	srand(time(NULL));

	switch(argc){

		case 1:
			// Caso nada seja inserido.
			apresentation_points();
			break;

		case 4:
			// Precisamos fornecer os argumentos corretos.
			simulation_points(std::atoi(argv[1]), std::atoi(argv[2]), std::atoi(argv[3]));
			break;

		default:
			break;
	}

	fprintf(stderr, "\n");
	return 0;
}