#include "src/Ambiente.h"
#include <vector>

void
apresentation_points(
	int is_simulation,
	int algoritmo_escolhido,
	int quant_de_pontos,
	bool is_debug = False,
	int mutation_ratio = 20
){
	/*
	Descrição:
		Caso desejado pelo usuário, providenciará 
		a apresentação da aplicação para o caso 2D.
	*/
	Janela janela;

	Mother mae(
		is_simulation,
		algoritmo_escolhido,
		2,
		quant_de_pontos,
		is_debug,
		mutation_ratio
	);

	while( janela.is_running ){

		if( janela.get_keys() ){
			// Então houve um clique.

			float dist_sq_media = mae.get_sex(SDL_GetMouseState);
		}

		// Vamos renderizar.

		SDL_SetRenderDrawColor(janela.renderer, 255, 255, 255, 255);  // fundo
        SDL_RenderClear(janela.renderer);

        janela.apresentar_pontos(mae.points, mae.QUANT_PONTOS, mae.indice_especial, mae.quant_de_indices_a_serem_populados);

        SDL_RenderPresent(janela.renderer);
		SDL_Delay(janela.delay);
	}

	mae.encerrar();
	janela.encerrar();
}

void
execute_simulation(
	int algoritmo_escolhido,
	int dimensao,
	int quant_de_pontos,
	bool is_debug = False,
	int mutation_ratio = 20
){

}

// Função Anônima: [](int* a, int* b) -> unsigned int { return 1; }

#ifdef BUILD_AS_PYTHON_MODULE

// ---------------------------------------
// Execução para Python
// #include <pybind11/pybind11.h>
// #include <pybind11/stl.h>
// using namespace pybind11::literals;

// int soma(int x, int y) {
//     return x + y;
// }

// PYBIND11_MODULE(meumodulo, m) {
//     m.def("soma", &soma, "Soma dois números", "x"_a, "y"_a);
// }




#else

// ------------------------------------------------
// Execução usando C++

int main(int argc, char* argv[]){
	/*
	Descrição:
		Responsável por executar a simulação de diferentes formas.

	Parâmetros:
	
		O primeiro argumento inserido representa `is_apresentation`,
		relatando se trata-se de uma apresentação 2D.

		Os argumentos N_4 e N_5 estão com '?' pois são opcionais,
		representando `is_debug` e taxa de mutação, respectivamente.

		./main 1 N_1 N_2 N_3 N_4? N_5?
	
			N_1 -> Configuração de Simulação
			N_2 -> Algoritmo Selecionado
			N_3 -> Quantidade de Pontos

		./main 0 N_1 N_2 N_3 N_4? N_5?

			N_1 -> Algoritmo Selecionado
			N_2 -> Dimensão
			N_3 -> Quantidade de Pontos
	*/

	switch(argc){

		case 1: {
			// Caso nada seja inserido, vamos colocar o padrão.
			apresentation_points(0, 1, 20);
			break;
		}

		case 5: {

			if(
				std::atoi(argv[1]) == 1
			){

				apresentation_points(
					std::atoi(argv[2]),
					std::atoi(argv[3]),
					std::atoi(argv[4])
				);
			}
			else{

				execute_simulation(
					std::atoi(argv[2]),
					std::atoi(argv[3]),
					std::atoi(argv[4])
				);
			}

			break;
		}

		case 6: {

			if(
				std::atoi(argv[1]) == 1
			){

				apresentation_points(
					std::atoi(argv[2]),
					std::atoi(argv[3]),
					std::atoi(argv[4]),
					std::atoi(argv[5])
				);
			}
			else{

				execute_simulation(
					std::atoi(argv[2]),
					std::atoi(argv[3]),
					std::atoi(argv[4]),
					std::atoi(argv[5])
				);
			}

			break;
		}

		case 7: {

			if(
				std::atoi(argv[1]) == 1
			){

				apresentation_points(
					std::atoi(argv[2]),
					std::atoi(argv[3]),
					std::atoi(argv[4]),
					std::atoi(argv[5]),
					std::atoi(argv[6])
				);
			}
			else{

				execute_simulation(
					std::atoi(argv[2]),
					std::atoi(argv[3]),
					std::atoi(argv[4]),
					std::atoi(argv[5]),
					std::atoi(argv[6])
				);
			}

			break;
		}

		default:
			break;
	}

	fprintf(stderr, "\n");
	return 0;
}

#endif