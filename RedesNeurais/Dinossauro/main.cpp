
// Instalações de Código
#include "src/Dinossauro.h"

/*
Thread Principal:
    Responsável por iniciar demais threads e cuidar dos objetos do ambiente.
*/

int main() {

    srand(time(NULL));
    
    // Iniciamos gráficos.
    graphicx::Aplicacao aplication = graphicx::init_aplication();

    // Iniciamos ambiente.
    Ambiente ambiente(&aplication);

    // Iniciamos jogadores.
    std::vector<std::thread> dinossauros;
    for(
        int i = 0;
            i < QUANT_DINOS;
            i++
    ){

        dinossauros.emplace_back(
            jogador, &ambiente
        );
    }

    while(
        aplication.is_running
    ){

        graphicx::get_keys(aplication);

        SDL_SetRenderDrawColor(aplication.renderer, 255, 255, 255, 255);
        SDL_RenderClear(aplication.renderer);



        ambiente.apresentar_ambiente();

        graphicx::sync_fps(aplication);
        SDL_RenderPresent(aplication.renderer);
    }

    // Encerramos a simulação.
    for( auto& t : dinossauros ){ t.join(); }
    ambiente.destroy();
    graphicx::destroy_aplication(aplication);
    fprintf(stderr, "\n");
    return 0;
}






















