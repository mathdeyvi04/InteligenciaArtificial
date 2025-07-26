#ifndef DINOSSAURO_H
#define DINOSSAURO_H

#include "Ambiente.h"

class Dino : Ambiente::Objeto {
	/*
	Descrição:
		Representaremos a Rede Neural a partir desse garotão.

		Cada dinossauro será jogado por uma thread e sua respectiva Rede Neural.
		A simulação deve parar quando não houver mais dinossauros jogando.
	*/

public:

	Dino( Ambiente ambiente ) {
		/*
		Descrição:
			Responsável por inicializar características críticas do dinossauro.
		*/

		ambiente.conj_de_objetos.emplace_back(
			Objeto(
				&ambiente.respectivos_cortes[ambiente.conj_de_sprites[3]],
				0, // index não importa.
				3
			)
		);




	}



};

void
jogador( Ambiente ambiente ){
	/*
	Descrição:
		Responsável por representar o fluxo do jogador.
	*/

	int i = rand() % 100;

	fprintf(stderr, "\nThread %d entrou.", i);

	Dino dino(ambiente);

	while(ambiente.aplication.is_running){
		fprintf(stderr, "\nVejo %d", ambiente.aplication.is_running);

		// Dino deve tomar uma decisão e aplicá-la.
		// Ambiente esperará por isso.
		// dino.decisao()
		sync_barrier.arrive_and_wait();

		// Dino deve esperar ambiente mover a todos e apresentá-los.
		sync_barrier.arrive_and_wait();
	}

	

	fprintf(stderr, "\nThread %d saiu.", i);
}







#endif // DINOSSAURO_H	