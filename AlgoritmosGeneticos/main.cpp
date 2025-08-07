#include "src/Ambiente.h"
#include <vector>

void
apresentation_points(

){
	/*
	Descrição:
		Caso desejado pelo usuário, providenciará 
		a apresentação da aplicação para o caso 2D.
	*/
	Janela janela;

	Mother mae(
		False,
		1,
		2,
		20,
		50
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
		SDL_Delay(100);
	}

	mae.encerrar();
	janela.encerrar();
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
		-> ./main
			Executará uma apresentação 2D.

		-> ./main N_1 N_2 N_3
			Retornará vetor de N_3 distâncias quadráticas médias 
			correspondendo às N_3 gerações de N_2 pontos cada uma tendo 
			dimensão N_1.

			Há um 4° parâmetro que pode ser inserido a fim de modificar a taxa
			de mutação.
	*/

	switch(argc){

		case 1: {
			// Caso nada seja inserido.
			apresentation_points();
			break;
		}

		default:
			break;
	}

	fprintf(stderr, "\n");
	return 0;
}

#endif