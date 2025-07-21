# Definição
	* Mesmo que rede neural, entretanto, possuindo muito mais camadas escondidas.
	* Capaz de muito mais que a rede normal.

# Redes Convolucionais
	* Diversas matrizes realizando coisas que apenas matrizes são capazes de realizar.
	* Geralmente demoram muito para treinar devido à alta quantidade de parâmetros.
	* Como tudo é automático, não se sabe exatamente o que acontece ou o que a rede está aprendendo ou categorizando.
	
# Algumas Propriedades Matemáticas
	* Funcionam como filtros que trabalham em pequenos quadrados e percorrem a imagem total.
	* Convolução é uma operação linear que a partir de duas funções gera uma terceira, chamada de feature map.
	* Kernel é uma matriz usada para uma operação de multiplicação de matrizes. Após aplicar em diferentes regiões da imagem, a região é alterada por um parâmetro chamado _stride_.

# A Matemática por Trás

	* Pooling
		* Processo de downsamping, redução de dimensionalidade/featuremaps. Tente imaginar como um redimensionamento de uma imagem ou de parâmetros por exemplo.
		* Max Pooling
			* Retirar o maior elemento da região, depois feito deslizamento considerando um parâmetro de stride para aplicação de uma nova operação.
	* Dropout
		* Evitar que partes da rede neural fiquem com muita responsabilidade e sensibilidades a pequenas alterações.
		* Essa camada recebe um hyper parâmetro que define uma probabilidade de desligar determinada área da rede.

	* Flatten
		* Normalmente utilizada na divisão das 2 partes da CNN. Opera uma transformação na matriz, alterando seu formato para um array.





