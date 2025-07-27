#ifndef DINOSSAURO_H
#define DINOSSAURO_H

#include "Ambiente.h"

class Dino {
	/*
	Descrição:
		Representaremos a Rede Neural a partir desse garotão.

		Cada dinossauro será jogado por uma thread e sua respectiva Rede Neural.
		A simulação deve parar quando não houver mais dinossauros jogando.
	*/

public:

	class RedeNeural {
		/*
		Descrição:
			Representará nossa rede. Sendo responsável por todas as
			manipulações inerentes ao funcionamento.

			Faremos nossa rede com 3 entradas:
			
			1. Distância ao Próximo Obstáculo
			2. Altura do Obstáculo
			3. Velocidade do Ambiente

			E 2 saídas:

			1. Pular
			2. Agachar

			Manteremos apenas uma camada intermediária com 3 neurônios.
			Por perfomance, usaremos o estilo C de vetores.

			Do jeito que estamos construindo, cada neurônio possui um par 
			de peso e de bias. Logo, não há um peso para cada entrada.
		*/
	public:

		//////////////////////////////////////////////////////////////
		/*
		Definimos arquitetura:
		Sempre será apenas 2 saídas possíves.
		*/
		#define NEURONIOS_DE_ENTRADA 3
		#define CAMADAS_INTER 1

		//////////////////////////////////////////////////////////////
		/*
		Não inicializamos para não afetar performance.

		Note que, construindo assim, a rede é representada por uma matriz
		(CAMADAS_INTER + 1)x(NEURONIOS_DE_ENTRADA), entretanto, sabemos
		que a última camada possui apenas 2 neurônios de saída.
		Sendo assim, devemos fazer com que os neurônios fantasmas das linhas
		3 ... NEURONIOS_DE_ENTRADA devam ser zero sempre.
		Como há weights e bias, observe como a rede na verdade é um tensor.

		CAMADAS_INTER + 1 -> 1 de saída e CAMADAS_INTER escondidas.
		*/
		float weights[CAMADAS_INTER + 1][NEURONIOS_DE_ENTRADA];
		float bias[CAMADAS_INTER + 1][NEURONIOS_DE_ENTRADA];

		//////////////////////////////////////////////////////////////
		/*
		Definiremos outra característica tão importante quanto.
		*/
		float mutation_ratio = 1;
		int id_dino = 0;
		char nome_da_rede[30];

		//////////////////////////////////////////////////////////////

		static float gerar_numero_aleatorio(int min = - 100, int max = 100){ return min + rand() % (max - min + 1); }

		static int activate_function(float valor) { return (valor > 0) ? valor / 1000.0 : 0; }

		static float calcular_neuronio(float* vetor, float& peso, float& bias) { float sum = 0; for(int i = 0; i < 3; i++) { sum += vetor[i] * peso + bias; } return sum; }

		RedeNeural() {}

		RedeNeural( int id ) {
			/*
			Descrição:
				Sem qualquer parâmetro, inicializamos apenas com valores aleatórios.
			*/

			id_dino = id;
			int camada = 0;
			while(
				camada != (CAMADAS_INTER + 1)
			){
				int linha = 0;
				while(
					linha < NEURONIOS_DE_ENTRADA 
				){

					// Afinal, não há mais de 2 neurônios na camada de saída
					// Desde que nunca os toquemos, não haverá problema.
					if( linha == 2 && camada == 1){ break; } 

					weights[camada][linha] = gerar_numero_aleatorio();
					bias[camada][linha]    = gerar_numero_aleatorio();

					// fprintf(stderr, "\nW(%d, %d) = %f\t--\t", camada, linha, weights[camada][linha]);
					// fprintf(stderr, "B(%d, %d) = %f", camada, linha, bias[camada][linha]);

					linha++;
				}

				camada++;
			}
		}

		void
		salvar_rede(char opcao_de_salvamento = 'b'){
			/*
			Descrição:
				Responsável por salvar nossa rede.
				Há a opção de salvarmos em forma de texto, apenas para visualização.
			*/

			if(opcao_de_salvamento == 't') {snprintf(nome_da_rede, sizeof(nome_da_rede), "src/Redes/rede_%d.txt", id_dino);} else {snprintf(nome_da_rede, sizeof(nome_da_rede), "src/Redes/rede_%d.bin", id_dino);}
			FILE *arq = fopen(nome_da_rede, (opcao_de_salvamento == 't') ? "w" : "wb");
			if(!arq) { perror("\nCriação de arquivo de salvamento falhou:"); return; }

			if(
				opcao_de_salvamento == 't'
			){

				int linha = 0;
				while(
					linha != NEURONIOS_DE_ENTRADA
				){

					int camada = 0;
					while(
						camada != (CAMADAS_INTER + 1)
					){
						// Se estiver na última camada, saída.
						// Não deve apresentar demais neurônios dps de 2.
						if(camada == CAMADAS_INTER && linha >= 2) { break; }

						fprintf(arq, "%.2f/%.2f\t", weights[camada][linha], bias[camada][linha]);

						camada++;
					}

					fprintf(arq, "\n");

					linha++;
				}
			}
			else{

				float weights_como_vetor[(CAMADAS_INTER + 1) * NEURONIOS_DE_ENTRADA];
				float bias_como_vetor[(CAMADAS_INTER + 1) * NEURONIOS_DE_ENTRADA];

				int i = 0;
				int linha = 0;
				while(
					linha != NEURONIOS_DE_ENTRADA
				){

					int camada = 0;
					while(
						camada != (CAMADAS_INTER + 1)
					){
						// Se estiver na última camada, saída.
						// Não deve apresentar demais neurônios dps de 2.
						if(camada == CAMADAS_INTER && linha >= 2) { break; }

						weights_como_vetor[i] = weights[camada][linha];
						bias_como_vetor[i] = bias[camada][linha];
						i++;
						camada++;
					}

					linha++;
				}

				fwrite(weights_como_vetor, sizeof(weights_como_vetor), i, arq);
				fwrite(bias_como_vetor, sizeof(bias_como_vetor), i, arq);
			}

			fclose(arq);
		}

		void 
		carregar_rede(const char* nome){
		}

		void
		calcular_resultado(
			float* vetor_de_entrada,
			float* result_neuronios
		){
			/*
			Descrição:
				Responsável por permitir a tomada de decisão a partir da rede.
				O vetor de entrada está definido como na descrição da RedeNeural.
			*/

			int camada = 0;
			while(
				camada != (CAMADAS_INTER + 1)
			){
				int linha = 0;
				while(
					linha < NEURONIOS_DE_ENTRADA 
				){

					// Afinal, não há mais de 2 neurônios na camada de saída
					// Desde que nunca os toquemos, não haverá problema.
					if( linha == 2 && camada == 1 ){ break; } 

					result_neuronios[linha] = activate_function(
						calcular_neuronio(  
							(camada == 0) ? vetor_de_entrada : result_neuronios, 
							weights[camada][linha], 
							bias[camada][linha]
						)
					);

					// fprintf(stderr, "\nW(%d, %d) = %f\t--\t", camada, linha, weights[camada][linha]);
					// fprintf(stderr, "B(%d, %d) = %f", camada, linha, bias[camada][linha]);

					linha++;
				}

				camada++;
			}
		}
	};


	int vel_de_impulso = 400;
	Ambiente* ambiente = nullptr;
	Ambiente::Objeto* obj = nullptr;
	RedeNeural neural_network;

	Dino( Ambiente* ambiente_, int id) {
		/*
		Descrição:
			Responsável por inicializar características críticas do dinossauro.
		*/

		// Criando Dinossauro
		// Ambas threads não devem acessar este elemento simultaneamente.
		mtx.lock();
		ambiente_->conj_de_objetos.emplace_back(
			Ambiente::Objeto(
				&ambiente_->respectivos_cortes[ambiente_->conj_de_sprites[3]],
				0, // index não importa.
				3
			)
		);
		// Com o mutex, temos garantia de que este é realmente o último.
		obj = &ambiente_->conj_de_objetos.back();
		mtx.unlock();

		neural_network = RedeNeural(id);
		ambiente = ambiente_;
	}

	void
	think_and_act(){
		/*
		Descrição:
			Responsável por obter as entradas e gerar decisões.

			A saída será definida como:

			1. Pular
			2. Agachar
		*/

		float entrada[NEURONIOS_DE_ENTRADA];
		float saida[NEURONIOS_DE_ENTRADA]; // Sabemos o [2] não existe.

		entrada[0] = ambiente->obj_mais_proximo->pos[0];
		entrada[1] = obj->pos[1] - ambiente->obj_mais_proximo->pos[1];
		entrada[2] = ambiente->VEL_AMBIENTE;

		neural_network.calcular_resultado(entrada, saida);

		if( saida[0] > 0 && obj->vely == 0 ) { obj->vely = vel_de_impulso; obj->esta_agachado = 0; obj->index_de_sprite = 0; obj->ratio_img[0] = 60; obj->ratio_img[1] = 70; obj->alt_min_para_dino = 705; }
		if(
			saida[1] > 0
		){

			// Caso estejamos em voo
			if(
				obj->vely != 0
			){

				// Forçamos uma queda
				obj->vely -= 200;
			}
			else{

				// Caso já estejamos no chão
				if( !obj->esta_agachado ) { obj->esta_agachado = 1; obj->index_de_sprite = 2; obj->ratio_img[0] = 70; obj->ratio_img[1] = 60; obj->alt_min_para_dino = 715; }
			}
		}
		else{

			// if( obj->esta_agachado ) { obj->esta_agachado = 0; obj->index_de_sprite = 0; obj->ratio_img[0] = 60; obj->ratio_img[1]  = 70; obj->alt_min_para_dino = 705; }
		}
	}

	bool
	verificar_colisao(){
		/*
		Descrição:
			Verificará se houve colisão do dinossauro com o obstáculo mais perto.
		*/

		return 0;

		return (
	        obj->pos[0] < ambiente->obj_mais_proximo->pos[0] + ambiente->obj_mais_proximo->ratio_img[0] &&
	        obj->pos[0] + obj->ratio_img[0] > ambiente->obj_mais_proximo->pos[0] &&
	        obj->pos[1] < ambiente->obj_mais_proximo->pos[1] + ambiente->obj_mais_proximo->ratio_img[1] &&
	        obj->pos[1] + obj->ratio_img[1] > ambiente->obj_mais_proximo->pos[1]
	    );
	}


};

void
jogador( Ambiente* ambiente ){
	/*
	Descrição:
		Responsável por representar o fluxo do jogador.
	*/

	int i = rand() % 1000;

	fprintf(stderr, "\nThread %d entrou.", i);

	Dino dino(ambiente, i);

	while(ambiente->aplication->is_running){

		// Dino deve tomar uma decisão e aplicá-la.
		// Ambiente esperará por isso.
		if( !dino.obj->esta_morto ){ dino.think_and_act(); }
		sync_barrier.arrive_and_wait();

		// Dino deve esperar ambiente mover a todos e apresentá-los.
		sync_barrier.arrive_and_wait();

		if( dino.verificar_colisao() ){ dino.obj->esta_morto = 1; mtx.lock(); ambiente->quantidade_de_dinos_vivos -= 1; mtx.unlock(); }
	}
	
	fprintf(stderr, "\nThread %d saiu.", i);
}







#endif // DINOSSAURO_H	