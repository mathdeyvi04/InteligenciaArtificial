
// Instalações de Código
#include "src/Ambiente.h"

/*
Thread Principal:
    Responsável por iniciar demais threads e cuidar dos objetos do ambiente.


*/


int main() {
    
    graphicx::Aplicacao aplication = graphicx::init_aplication();

    Ambiente ambiente(aplication);

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






    ambiente.destroy();
    graphicx::destroy_aplication(aplication);

    return 0;
}






















