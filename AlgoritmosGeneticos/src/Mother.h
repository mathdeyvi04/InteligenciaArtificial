#ifndef MOTHER_H
#define MOTHER_H

#include <time.h>  // Para o srand.
#include <cstdlib>
#include <climits>

#define TAMANHO 800

#define True true
#define False false

#define TAM 14

class Mother {
	/*
	Descrição:
		Responsável por gerenciar as gerações de pontos.
	*/
public:

	// Considera-se que o mínimo é 0.
	static int gerar_aleatorio(int min, int max){ return rand() % (max - min + 1) + min; } 

	int DIMENSION = 2;
	int QUANT_PONTOS = 20;

	int* points = nullptr;
	int* ponto_de_convergencia;

	int indice_especial = -1;
	int mutation_ratio = 0;

	bool simulation = False;

	Mother(bool is_simulation = False, int mutation_ratio_ = 20){
		/*
		Descrição:
			Responsável por inicializar o conjunto de pontos.
			Todos nascem de forma aleatória pelo cartesiano.
		*/

		srand(time(NULL));

		simulation = is_simulation;
		mutation_ratio = mutation_ratio_;

		// Alocamos os números
		points = (int*)malloc(DIMENSION * QUANT_PONTOS * sizeof(int));
		ponto_de_convergencia = (int*)calloc(DIMENSION, sizeof(int));

		if(simulation){
			
			// Aqui devemos sintetizar onde devemos colocar o ponto de convergência.
			ponto_de_convergencia[0] = TAMANHO - 10;
			ponto_de_convergencia[1] = TAMANHO - 10;		
		}

		for(
			int i = 0;
				i < DIMENSION * QUANT_PONTOS;
				i += 1 // -> Neste primeiro caso não importa
		){

			// Observe que para ambientes simulados, os pontos nascerão próximos do (0, ..., 0).
			points[i] = (simulation) ? 0 + 2 * gerar_aleatorio(-mutation_ratio, mutation_ratio) : gerar_aleatorio(0, TAMANHO);
		}
	}

	float
	gerar_novo_conj(
		unsigned int (*obter_convergencia)(int*, int*)
	){
		/*
		Descrição:
			Responsável por aglutinar o algoritmo de geração de novos 
			pontos e de escolha de melhor.

			Também realiza medidas de convergência.

		Retorno:
			Razão Entre Distância Quadrática Média dos Pontos e Área Total.
		*/

		// No caso bidimensional, faz sentido pensarmos no mouse.
		if( DIMENSION == 2 && !simulation ) { obter_convergencia(ponto_de_convergencia, ponto_de_convergencia + 1); }

		int delta = 0;
		int menor_dist_sq = INT_MAX;
		int dist_sq_medida = 0;
		int indice_especial_antigo = indice_especial;
		long int soma_total_dist_sq = 0;
		for(
			int i = 0;
				i < DIMENSION * QUANT_PONTOS;
				i += DIMENSION
		){

			// Gerando novos pontos
			if(
				indice_especial_antigo != -1
			){

				for(
					int j = 0;
						j < DIMENSION;
						j++
				){

					points[i + j] = points[indice_especial_antigo + j] + gerar_aleatorio( -mutation_ratio, mutation_ratio );
				}
			}

			// -------------------------------------------------------------------------------------------------

			// Escolhendo melhor
			for(
				int j = 0;
					j < DIMENSION;
					j++
			){

				delta = points[i + j] - ponto_de_convergencia[j];
				dist_sq_medida += delta * delta;
			}

			if( dist_sq_medida < menor_dist_sq ){ menor_dist_sq = dist_sq_medida; indice_especial = i; }

			// Iniciaremos outra busca
			soma_total_dist_sq += dist_sq_medida;
			dist_sq_medida = 0;
		}

		return (float)soma_total_dist_sq / (QUANT_PONTOS) / (TAMANHO * TAMANHO);
	}

	void
	encerrar(){

		if( points ) { free(points); }
		if( ponto_de_convergencia ){ free(ponto_de_convergencia); }
	}
};

#endif // MOTHER_H