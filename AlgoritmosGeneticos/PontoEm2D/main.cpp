#include "src/Ambiente.h"
#include <time.h>


int main(){

	srand(time(NULL));

	Janela janela;

	Mother mae;
	mae.debug = False;

	while( janela.is_running ){

		if( janela.get_keys() ){
			// Então houve um clique.

			// A partir deste item especial, devemos montar um novo conj de pontos
			mae.gerar_novo_conj();

			// Devemos obter o novo ponto especial para o novo conj
			mae.atualizar_ponto_especial(SDL_GetMouseState);
		}

		// Vamos renderizar.

		SDL_SetRenderDrawColor(janela.renderer, 255, 255, 255, 255);  // fundo
        SDL_RenderClear(janela.renderer);

        janela.apresentar_pontos(mae.points, mae.indice_especial);

        SDL_RenderPresent(janela.renderer);
		SDL_Delay(100);
	}

	janela.encerrar();

	fprintf(stderr, "\n");
	return 0;
}
