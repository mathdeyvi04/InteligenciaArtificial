
// Instalações de Código
#include "src/Dinossauro.h"
#include "src/Graficos.h"



int main() {
    
    graphicx::Aplicacao aplication = graphicx::init_aplication();

    while(
        aplication.is_running
    ){

        graphicx::get_keys(aplication);

        graphicx::renderizar(aplication, 1);


        graphicx::sync_fps(aplication);

        graphicx::renderizar(aplication, -1);
    }







    graphicx::destroy_aplication(aplication);

    return 0;
}






















