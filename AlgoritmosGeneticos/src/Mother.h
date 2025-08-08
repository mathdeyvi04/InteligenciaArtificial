#ifndef MOTHER_H
#define MOTHER_H

#include <time.h>  // Para o srand.
#include <cstdio>
#include <cstdlib>
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

	static void print_vector(int* vetor, int dim){

		int i = 0;
		while(True){

			if( i == 0 ){

				fprintf(stderr, "[");
			}
			else if( i == dim ){

				fprintf(stderr, "\b\b]");
				return;
			}

			fprintf(stderr, "%d, ", vetor[i]);
			i++;
		}
	}

	int DIMENSION;
	int QUANT_PONTOS;
	bool simulation = False;

	// Base da Aplicação
	int* points = nullptr;
	int* ponto_de_convergencia = nullptr;
	int* child = nullptr;
	int mutation_ratio;

	int indice_especial[5] = {-1, -1, -1, -1, -1};
	int quant_de_indices_a_serem_populados = 0;
	int algoritmo_escolhido = 0;

	bool debug = False;

	Mother(
		bool is_simulation,
		int  algoritmo_escolhido_,
		int  dimension,
		int  quant_de_pontos,
		bool is_debug,
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
		algoritmo_escolhido = algoritmo_escolhido_;
		quant_de_indices_a_serem_populados = (algoritmo_escolhido_ == 0) ? 1 : ( (algoritmo_escolhido_ == 1) ? 2 : 5 );

		DIMENSION = dimension;
		QUANT_PONTOS = quant_de_pontos;
		debug = is_debug;
		mutation_ratio = mutation_ratio_;

		// --------------------------------------------------------------------------

		srand(time(NULL));

		// Alocamos os números
		points = new int[DIMENSION * QUANT_PONTOS]; 
		ponto_de_convergencia = new int[DIMENSION];
		child = new int[DIMENSION];

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
	get_the_best(){
		/*
		Descrição:
			Responsável por popular a lista de índices com 
			os melhores pontos, vulgo os mais próximos do 
			ponto de convergência.
		*/

		int indices_populados = 0;
		while(
			indices_populados != quant_de_indices_a_serem_populados && indices_populados < QUANT_PONTOS
		){

			int menor_dist_sq = INT_MAX;
			for(
				int i = 0;
					i <  DIMENSION * QUANT_PONTOS;
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
					dist_sq < menor_dist_sq && !check_presence(i, indice_especial, indices_populados)
				){ 
					// Atualizamos nova menor distância
					menor_dist_sq = dist_sq; 

					// Populamos a lista com outro melhor
					indice_especial[indices_populados] = i; 
				}
			}

			indices_populados++;
		}
	}

	float
	get_sex(
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

		if(
			indice_especial[0] != -1
		){

			switch(algoritmo_escolhido){

				case 0: {
					// Devemos obter o melhor elemento, apenas.

					for(
						int j = 0;
							j < DIMENSION;
							j++
					){

						child[j] = points[ indice_especial[0] + j ];
					}

					break;
				}

				case 1: {
					// Devemos trocar os genes dos 2's melhores.

					for(
						int j = 0;
							j < DIMENSION;
							j++
					){

						child[j] = points[ indice_especial[ j % 2 ] + j ];
					}

					break;
				}

				case 2: {
					// Devemos selecionar aleatoriamente 2 dos 5 melhores.

					int idx_lista_melhores[2];

					// ------------------------------------------------
					// Apenas garantindo que serão genitores diferentes
					idx_lista_melhores[0] = rand() % 5;
					idx_lista_melhores[1] = rand() % 5;

					while(
						idx_lista_melhores[1] == idx_lista_melhores[0]
					){

						idx_lista_melhores[1] = rand() % 5;
					}

					// -------------------------------------------------
					// Realizando Sexo
					for(
						int j = 0;
							j < DIMENSION;
							j++
					){

						child[j] = points[ indice_especial[ idx_lista_melhores[ j % 2 ] ] + j ];
					}

					break;
				}

				default: {
					break;
				}
			}

			// Faremos uma análise detalhada do esquema.
			if(
				debug
			){

				fprintf(stderr, "\n---------------------------------------------------");
				fprintf(stderr, "\nMelhores: ");
				print_vector(indice_especial, 5);
				fprintf(stderr, "\nIndivíduos: ");
				for(
					int i = 0;
						i < QUANT_PONTOS * DIMENSION;
						i += DIMENSION
				){

					fprintf(stderr, "\n\tid: %d | ", i);
					print_vector(points + i, DIMENSION);
				}
				fprintf(stderr, "\nFilho: ");
				print_vector(child, DIMENSION);
				fprintf(stderr, "\n---------------------------------------------------");
			}
		}

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

		get_the_best();

		return (float)total_dist_sq / QUANT_PONTOS / (TAMANHO * TAMANHO);
	}

	void
	encerrar(){

		if( points ) { delete points; }
		if( ponto_de_convergencia ){ delete ponto_de_convergencia; }
		if( child ){ delete child; }
	}
};

#endif // MOTHER_H