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
	Description:
	    Executes the visual presentation of the application in the 2D case, allowing mouse interaction and
	    rendering of the best individuals, depending on the algorithm, in colors.

	    - Clicking generates a new generation;
	    - Clicking and holding ensures continuous creation of generations;

	    The window has a fixed size of 800x800.

	Parameters:
	    is_simulation (int):
	        Indicates whether the execution is in simulation mode.
	    algoritmo_escolhido (int):
	        Identifier of the algorithm to be used in the simulation.
	    quant_de_pontos (int):
	        Total number of points that will be processed and displayed.
	    is_debug (bool, optional):
	        Enables debug mode to display additional information (default: False).
	    mutation_ratio (int, optional):
	        Mutation ratio applied during processing (default: 20).
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

std::vector<float>
execute_simulation(
	int algoritmo_escolhido,
	int dimensao,
	int quant_de_pontos,
	int quant_de_geracoes,
	bool is_debug = False,
	int mutation_ratio = 20
){

	std::vector<float> result(quant_de_geracoes);

	Mother mae(
		1,
		algoritmo_escolhido,
		dimensao,
		quant_de_pontos,
		is_debug,
		mutation_ratio
	);

	int n_gen = 0;
	while(
		n_gen != quant_de_geracoes
	){	

		result.push_back(
			mae.get_sex(
				[](int* a, int* b) -> unsigned int { return 1; }
			)
		);

		n_gen++;
	}

	mae.encerrar();

	return result;
}

#ifdef BUILD_AS_PYTHON_MODULE

// ---------------------------------------
// Execução para Python
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
using namespace pybind11::literals;

PYBIND11_MODULE(meumodulo, m) {
	m.doc() = R"pbdoc(

	)pbdoc";

    m.def(
    	"apresentation_points", 
    	&apresentation_points, 
    	R"pbdoc(
    	Description:
		    Executes the visual presentation of the application in the 2D case, allowing mouse interaction and
		    rendering of the best individuals, depending on the algorithm, in colors.

		    - Clicking generates a new generation;
		    - Clicking and holding ensures continuous creation of generations;

		    The window has a fixed size of 800x800.

		Parameters:
		    is_simulation (int):
		        Indicates whether the execution is in simulation mode.
		    algoritmo_escolhido (int):
		        Identifier of the algorithm to be used in the simulation.
		    quant_de_pontos (int):
		        Total number of points that will be processed and displayed.
		    is_debug (bool, optional):
		        Enables debug mode to display additional information (default: False).
		    mutation_ratio (int, optional):
		        Mutation ratio applied during processing (default: 20).
    	)pbdoc",
    	"is_simulation"_a, 
    	"algoritm_selected"_a,
    	"number_points"_a,
    	"is_debug"_a,
    	"mutation_ratio"_a
    );

    m.def(
    	"execute_simulation", 
    	&execute_simulation, 
    	R"pbdoc(

    	)pbdoc",
    	"algoritm_selected"_a,
    	"dimension"_a,
    	"number_points"_a,
    	"number_gerations"_a,
    	"is_debug"_a,
    	"mutation_ratio"_a
    );
}

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

		./main 0 N_1 N_2 N_3 N_4 N_5? N_6?

			N_1 -> Algoritmo Selecionado
			N_2 -> Dimensão
			N_3 -> Quantidade de Pontos
			N_4 -> Quantidade de Gerações
	*/

	if(
		// Verificando se é apresentação.
		std::atoi(argv[1])
	){

		switch(argc){
			case 7: {

				apresentation_points(
					std::atoi(argv[2]),
					std::atoi(argv[3]),
					std::atoi(argv[4]),
					std::atoi(argv[5]),
					std::atoi(argv[6])
				);
				break;
			}

			case 6: {

				apresentation_points(
					std::atoi(argv[2]),
					std::atoi(argv[3]),
					std::atoi(argv[4]),
					std::atoi(argv[5])
				);
				break;
			}

			case 5: {

				apresentation_points(
					std::atoi(argv[2]),
					std::atoi(argv[3]),
					std::atoi(argv[4])
				);
				break;
			}

			default: {
				fprintf(stderr, "\nInicializou com a quantidade errada de argumentos.\n");
			}
		}
	}
	else{

		switch(argc){
			case 8: {

				execute_simulation(
					std::atoi(argv[2]),
					std::atoi(argv[3]),
					std::atoi(argv[4]),
					std::atoi(argv[5]),
					std::atoi(argv[6]),
					std::atoi(argv[7])
				);
				break;
			}

			case 7: {

				execute_simulation(
					std::atoi(argv[2]),
					std::atoi(argv[3]),
					std::atoi(argv[4]),
					std::atoi(argv[5]),
					std::atoi(argv[6])
				);
				break;
			}

			case 6: {

				execute_simulation(
					std::atoi(argv[2]),
					std::atoi(argv[3]),
					std::atoi(argv[4]),
					std::atoi(argv[5])
				);
				break;
			}

			default: {
				fprintf(stderr, "\nInicializou com a quantidade errada de argumentos.\n");
			}
		}
	}

	fprintf(stderr, "\n");
	return 0;
}

#endif