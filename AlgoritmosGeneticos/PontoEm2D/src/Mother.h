#ifndef MOTHER_H
#define MOTHER_H

#include <cstdio>
#include <cstdlib>
#include <climits>

#define COMPRIMENTO 1000
#define ALTURA 800

#define True true
#define False false

#define TAM 14
#define QUANT_PONTOS 10

class Mother {
	/*
	Descrição:
		Responsável por gerenciar as gerações de pontos.
	*/
public:

	// Considera-se que o mínimo é 0.
	static int gerar_aleatorio(int min, int max){ return rand() % (max - min + 1) + min; } 

	// Separaremos como [..., x_i, y_i, ...].
	int points[2 * QUANT_PONTOS];
	int ponto_de_convergencia[2];

	bool debug = False;

	int indice_especial = -1;
	int mutation_ratio = 100;

	Mother(){
		/*
		Descrição:
			Responsável por inicializar o conjunto de pontos.
			Todos nascem de forma aleatória pelo cartesiano.
		*/

		for(
			int i = 0;
				i < 2 * QUANT_PONTOS;
				i += 2
		){

			points[i]     = gerar_aleatorio(0, COMPRIMENTO);
			points[i + 1] = gerar_aleatorio(0, ALTURA);
		}
	}

	void
	atualizar_ponto_especial(
		unsigned int (*get_mouse)(int*, int*)
	){
		/*
		Descrição:
			Responsável por verificar qual o ponto mais próximo do ponto
			de convergência, que será o mouse.
		*/

		get_mouse(ponto_de_convergencia, ponto_de_convergencia + 1);

		if( debug ){ fprintf(stderr, "\n\n\nConvergencia: (%d, %d).", ponto_de_convergencia[0], ponto_de_convergencia[1]); }

		int menor_dist_sq = INT_MAX;
		int dist_sq_medida = 0;
		int dx = 0;
		int dy = 0;
		for(
			int i = 0;
				i < 2 * QUANT_PONTOS;
				i += 2
		){
			dx = points[i] - ponto_de_convergencia[0];
			dy = points[i + 1] - ponto_de_convergencia[1];
			
			dist_sq_medida = dx * dx + dy * dy;

			if( debug ){ fprintf(stderr, "\nPonto ID-%d: (%d, %d)", i, points[i], points[i + 1]); }

			if( 
				dist_sq_medida < menor_dist_sq
			){

				menor_dist_sq = dist_sq_medida;
				indice_especial = i;
			}
		}

		if( debug ){ fprintf(stderr, "\nMelhor: ID-%d", indice_especial); }
	}

	void
	gerar_novo_conj(){
		/*
		Descrição:
			Responsável organizar o algoritmo de geração
			de novos pontos.

			Algoritmo Atual:
				- A partir do melhor, reaplicá-lo e 
				adicionar um ruído.
		*/

		if( indice_especial == -1 ){
			return;
		}

		int x_esp = points[indice_especial];
		int y_esp = points[indice_especial + 1];

		for(
			int i = 0;
				i < 2 * QUANT_PONTOS;
				i += 2
		){

			points[i    ] = x_esp + gerar_aleatorio( -mutation_ratio, mutation_ratio );
			points[i + 1] = y_esp + gerar_aleatorio( -mutation_ratio, mutation_ratio );
		}
	}
};

#endif // MOTHER_H