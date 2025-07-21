#include <SDL.h>
#include <iostream>
#include <cstdio>

// Instalações de Código
#include "src/Dinossauro.h"



int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erro ao iniciar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Simulação da Rede Neural",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        640, 480, 
        0
    );


    

    SDL_Delay(1000); // Janela aberta por 3s











    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}






















