# Algoritmos Genéticos

* Algoritmo que, a partir de uma população inicial,
utiliza uma função _fitness_ e obtém uma ordem de qualidade
para cada agente.

* A partir dos melhores, realiza um cruzamento entre o par e 
uma mutação no filho resultante. Verificando posteriormente se
o filho é melhor ou pior no objetivo.

* O processo se repete com a população sendo substituída diversas
vezes por mutações do filho.
 

# Métodos de Otimização Para Algoritmos Genéticos

* Gerar uma população inicial aleatória baseado em um intervalo foco.

* Definir uma função fitness que medirá o quanto bom cada agente é.

* Fará uma seleção de indivíduos para cruzamento:
	* Não necessariamente sendo o 01 e o 02.

* Recombinação de Indivíduos:
	* Tente imaginar uma forma de misturar a informação entre os 
  	dois genitores.

* Mutação:
	* Experimente adicionar um valor aleatório diferentes às entradas.
    * Não torne todos mutantes.

* Sobrevivência:
  * Dentro de cada iteração, devemos varrer a população instântanea, pegar
  conjunto de elementos aleatórios e realizar as operações mostrar acima. 
  De posse dos filhos, colocá-los na nova população até que esta tenha a 
  mesma quantidade de elementos que a população instântanea.

