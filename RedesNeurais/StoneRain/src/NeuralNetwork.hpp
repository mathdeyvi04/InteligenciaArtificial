#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <fstream>
#include <string>
#include <Eigen/Dense>  ///< Assim, não reinventaremos a roda.
#define Matrix Eigen::MatrixXd ///< Apenas para não ficarmos escrevendo coisas desnecessárias.

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/array.hpp>

/**
 * @brief Representará nossa rede neural.
 * @details
 * 
 * Apenas definimos operações de salvamento e de carregamento
 * de matrizes, o restante é completamente obtido de MatrixXd.
 */
class NeuralNetwork {
private:

	friend class boost::serialization::access; ///< Assim, obtemos acesso a membros privados
	Matrix mat;

	int linhas  = 3;
	int colunas = 3;

public:

	/**
	 * @brief Construtor sem nenhum argumento, representará o desejo por um aleatório.	
	 */
	NeuralNetwork(){ mat.setRandom(linhas, colunas); }

	/**
	 * @brief Construtor com argumento de nome de arquivo, indica que desejamos carregar uma rede.	
	 * @param nome_do_arquivo Arquivo binário que desejamos carregar
	 */
	NeuralNetwork(
		const std::string& nome_do_arquivo
	){


	}

	Matrix& data() { return mat; }  ///< Getter da referência da matriz
	const Matrix& data() const { return mat; } ///< Getter da referência constante da matriz

	/**
	 * @brief Salvará a matriz de forma legível, apenas para curiosidade.
	 * @param nome_do_arquivo Arquivo Legível no qual salvaremos
	 */
	void
	salvar_como_legivel(
		const std::string& nome_do_arquivo
	) const {

		std::ofstream file(nome_do_arquivo);
		if( file.is_open() ){ file << mat << "\n"; }
	}

	/**
	 * @brief Responsável por salvar a matriz como arquivo binário.
	 */
	template<class Arquivo> 
	void
	save(
		Arquivo& ar,
		const unsigned int /*version*/
	){
		// O tamanho já é padronizado

		ar & boost::serialization::make_array(mat.data(), linhas * colunas);
	}

	/**
	 * @brief Responsável por carregar a matriz de um arquivo binário.	
	 */
	template<class Arquivo>
	void
	load(
		Arquivo& ar,
		const unsigned int /*version*/
	){
		// O tamanho já é padronizado

		ar & boost::serialization::make_array(mat.data(), linhas * colunas);
	}

	/**
	 * @brief Responsáve por prover à classe de serialização que
	 * a classe Matrix possui métodos responsáveis por serialização e deserialização.	
	 */
	template<class Arquivo>
	void
	serialize(
		Arquivo& ar,
		const unsigned int version
	){

		boost::serialization::split_free(
										ar,
										mat,
										version
			                            );
	}


};

#endif //NEURALNETWORK_HPP