#ifndef MOTHER_H
#define MOTHER_H

#include <time.h>  // Para o srand.
#include <cstdlib>
#include <cstdio>
#include <climits>

#define TAMANHO 800 // Janela
#define TAM 14 // Tamanho do Quadradinho

#define True true
#define False false


class Mother {
	/*
	Descrição:
		Responsável por gerenciar as gerações de pontos.
	*/
public:

	// Considera-se que o mínimo é 0.
	static int gerar_aleatorio(int min, int max){ return rand() % (max - min + 1) + min; } 

	static bool check_presence(int valor, int* lista, int length){ for( int i = 0; i < length; i++ ){ if(valor == lista[i]){ return True; } } return False; }

	int DIMENSION;
	int QUANT_PONTOS;
	bool simulation = False;

	// Base da Aplicação
	int* points = nullptr;
	int* ponto_de_convergencia;
	int mutation_ratio;

	int indice_especial[5] = {-1, -1, -1, -1, -1};
	int indices_populados = 0;

	Mother(
		bool is_simulation,
		int  dimension,
		int  quant_de_pontos,
		int  mutation_ratio_
	){
		/*
		Descrição:
			Responsável por inicializar o conjunto de pontos.

			Caso a flag de simulation seja inserida, uma inicialização
			diferente acontece:

			O ponto de convergência é fixo em (TAMANHO - 10, ...). Enquanto os 
			pontos são gerados próximos ao (0, ...).
		*/

		simulation = is_simulation;
		DIMENSION = dimension;
		QUANT_PONTOS = quant_de_pontos;
		mutation_ratio = mutation_ratio_;

		// --------------------------------------------------------------------------

		srand(time(NULL));

		// Alocamos os números
		points = new int[DIMENSION * QUANT_PONTOS]; 
		ponto_de_convergencia = new int[DIMENSION];

		for(
			int i = 0;
				i < DIMENSION * QUANT_PONTOS;
				i += 1 // -> Neste primeiro caso não importa
		){

			// Observe que para ambientes simulados, os pontos nascerão próximos do (0, ..., 0).
			points[i] = (simulation) ? gerar_aleatorio(-mutation_ratio, mutation_ratio) : gerar_aleatorio(0, TAMANHO);

			if( simulation && i < DIMENSION ){ ponto_de_convergencia[i] = TAMANHO - 10; }
		}
	}

	void
	get_the_best(
		int quant_de_melhores_a_serem_verificados
	){
		/*
		Descrição:
			Responsável por popular a lista de índices com 
			os melhores pontos, vulgo os mais próximos do 
			ponto de convergência.
		*/

		while(
			indices_populados != quant_de_melhores_a_serem_verificados
		){

			int menor_dist_sq = INT_MAX;
			for(
				int i = 0;
					i < DIMENSION * QUANT_PONTOS;
					i += DIMENSION
			){
				int dist_sq = 0;

				for(
					int j = 0;
						j < DIMENSION;
						j++
				){

					dist_sq += (points[i + j] - ponto_de_convergencia[j]) * (points[i + j] - ponto_de_convergencia[j]);
				}

				if( 
					dist_sq < menor_dist_sq && !check_presence(i, indice_especial, quant_de_melhores_a_serem_verificados)
				){ 
					// Atualizamos nova menor distância
					menor_dist_sq = dist_sq; 

					// Populamos a lista com outro melhor
					indice_especial[indices_populados] = i; 
				}
			}

			indices_populados++;
		}

		indices_populados = 0; // Zeramos para próximas execuções
	}

	float
	get_sex(
		int algoritmo_escolhido,
		unsigned int (*get_mouse)(int*, int*)
	){
		/*
		Descrição:
			Responsável pela obtenção da nova criança a ser reproduzida.
		
		Parâmetros:
			- algoritmo_escolhido (int)
				0 -> Assexual
				1 -> Sexual
				2 -> Sexual Aleatório
		*/

		// Vamos obter o ponto de convergência.
		if( DIMENSION == 2 && !simulation ){ get_mouse(ponto_de_convergencia, ponto_de_convergencia + 1); }

		int* child = new int[DIMENSION];

		if(
			indice_especial[0] != -1
		){

			switch(algoritmo_escolhido){

				case 0: {
					// Devemos obter o melhor elemento, apenas.

					child[0] = points[indice_especial[0]];
					child[1] = points[indice_especial[0] + 1];

					break;
				}

				case 1: {

				}

				case 2: {

				}

				default: {
					break;
				}
			}
		}

		// free(child);
		// fprintf(stderr, "\nMELHOR: %d", indice_especial[0]);
		// return 1.0f;
		return apply_mutation(child);
	}

	float
	apply_mutation(
		int* child
	){
		/*
		Descrição:
			Responsável por aplicar mutação ao filho e gerar uma nova
			população a partir disso.

			Adicionaremos a função de busca do melhor ponto.

		Retorno:
			Distância Quadrática Média do Conjunto
		*/

		long int total_dist_sq = 0;		
		if(
			indice_especial[0] != -1
		){

			int menor_dist_sq = INT_MAX;
			for(
				int i = 0;
					i < DIMENSION * QUANT_PONTOS;
					i += DIMENSION
			){
				int dist_sq = 0;

				for(
					int j = 0;
						j < DIMENSION;
						j++
				){

					points[i + j] = child[j] + gerar_aleatorio( -mutation_ratio, mutation_ratio );

					dist_sq += (points[i + j] - ponto_de_convergencia[j]) * (points[i + j] - ponto_de_convergencia[j]);
				}

				total_dist_sq += dist_sq;
			}
		}

		get_the_best(5);

		free(child);

		return (float)total_dist_sq / QUANT_PONTOS / (TAMANHO * TAMANHO);
	}

	/* 
	-------------------------------------------------------------------------
	O código a seguir trata do algoritmo assexual. 
	Note como é focado em perfomance.
	-------------------------------------------------------------------------
	*/
	// float
	// gerar_novo_conj(
	// 	unsigned int (*obter_convergencia)(int*, int*),

	// ){
	// 	/*
	// 	Descrição:
	// 		Responsável por aglutinar o algoritmo de geração de novos 
	// 		pontos e de escolha de melhor.

	// 		Também realiza medidas de convergência.

	// 	Retorno:
	// 		Razão Entre Distância Quadrática Média dos Pontos e Área Total.
	// 	*/

	// 	// No caso bidimensional, faz sentido pensarmos no mouse.
	// 	if( DIMENSION == 2 && !simulation ) { obter_convergencia(ponto_de_convergencia, ponto_de_convergencia + 1); }

	// 	int delta = 0;
	// 	int menor_dist_sq = INT_MAX;
	// 	int dist_sq_medida = 0;
	// 	int indice_especial_antigo = indice_especial;
	// 	long int soma_total_dist_sq = 0;
	// 	for(
	// 		int i = 0;
	// 			i < DIMENSION * QUANT_PONTOS;
	// 			i += DIMENSION
	// 	){

	// 		// Gerando novos pontos
	// 		if(
	// 			indice_especial_antigo != -1
	// 		){

	// 			for(
	// 				int j = 0;
	// 					j < DIMENSION;
	// 					j++
	// 			){

	// 				points[i + j] = points[indice_especial_antigo + j] + gerar_aleatorio( -mutation_ratio, mutation_ratio );
	// 			}
	// 		}

	// 		// -------------------------------------------------------------------------------------------------

	// 		// Escolhendo melhor
	// 		for(
	// 			int j = 0;
	// 				j < DIMENSION;
	// 				j++
	// 		){

	// 			delta = points[i + j] - ponto_de_convergencia[j];
	// 			dist_sq_medida += delta * delta;
	// 		}

	// 		if( dist_sq_medida < menor_dist_sq ){ menor_dist_sq = dist_sq_medida; indice_especial = i; }

	// 		// Iniciaremos outra busca
	// 		soma_total_dist_sq += dist_sq_medida;
	// 		dist_sq_medida = 0;
	// 	}

	// 	return (float)soma_total_dist_sq / (QUANT_PONTOS) / (TAMANHO * TAMANHO);
	// }

	void
	encerrar(){

		if( points ) { delete points; }
		if( ponto_de_convergencia ){ delete ponto_de_convergencia; }
	}
};

#endif // MOTHER_H