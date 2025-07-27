#ifndef IMPORTACOES_H
#define IMPORTACOES_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <vector>
#include <thread>
#include <barrier>
#include <mutex>

//////////////////////////////////////////////////////////////////////

#define QUANT_DINOS 1

std::mutex mtx;

std::barrier sync_barrier(QUANT_DINOS + 1); // Thread Principal


#endif // IMPORTACOES_H
