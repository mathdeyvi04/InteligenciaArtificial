# Ordem de Procedimentos
* Para detecção de um único objeto
	* Classificação 
	* Localização

* Para múltiplos objetos
	* Detecções
	* Segmentação de Objetos
	* Classificação
	* Localização

# Algoritmos de Classificação
	* Necessário muitos dados.
	* Exemplo: Inception V3
		 * Extrair Características
			* Input
			* Conv2D
			* MaxPooling2D
			* Conv2D
			*MaxPooling2D
		* Classificar
			* Flatten
			* Fully Connected
			* Softmax
			* Prediction
	* Diferente de Visão Computacional