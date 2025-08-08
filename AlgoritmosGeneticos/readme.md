# Objetivo

Analisar eficiência de algoritmos genéticos.

Construimos o código de forma a realizar modificações dentro dele
e permitir o estudo de diferentes algoritmos. 

Neste repositório, há apenas o mais simples.

# Um Pouco da Análise dos Algoritmos

### Algoritmo Assexual

- A partir de um conjunto inicial de indivíduos, $C_i = [v_1, v_2, ..., v_n]$;
- Avalia-se o melhor indivíduo, $v_p$;
- Ele é multiplicado por toda uma população, $[v_p, ...]$;
- Adiciona-se uma taxa de mutação aleatória, $[v_p + \delta_1, ..., v_p + \delta_n]$;
- Então, cria-se uma nova população, $C_{i + 1} = [v'_1, v'_2, ..., v'_n]$.

### Algoritmo Sexual

- A partir de um conjunto inicial de indivíduso, $C_i = [v_1, v_2, ..., v_n]$;
- Seleciona-se os **dois melhores**, $v_p$ e $v_q$;
- Aplica-se uma troca de informação entre os indivíduos:
	- Neste caso, as suas componentes são unidas de forma a gerar o filho.
	- Exemplo: $v_p = [p_1, ...]$ e $v_q = [q_1, ...]$ geram $f_{pq} = [p_1, q_2, p_3, q_4, ...]$
- Este filho é multiplicado por toda uma população;
- Adiciona-se uma taxa de mutação aleatória;
- Então, cria-se uma nova população $C_{i + 1}$.

### Algoritmo Sexual Aleatório

- A partir de um conjunto inicial de indivíduso, $C_i = [v_1, v_2, ..., v_n]$;
- De posse de uma lista ordenada dos melhores indivíduos, seleciona-se dois aleatórios dela: $v_p$ e $v_q$;
- Aplica-se uma troca de informação entre os indivíduos:
	- Neste caso, as suas componentes são unidas de forma a gerar o filho.
	- Exemplo: $v_p = [p_1, ...]$ e $v_q = [q_1, ...]$ geram $f_{pq} = [p_1, q_2, p_3, q_4, ...]$
- Este filho é multiplicado por toda uma população;
- Adiciona-se uma taxa de mutação aleatória;
- Então, cria-se uma nova população $C_{i + 1}$.

É interessante verificar como o _algoritmo sexual_ diferencia pouco do _algoritmo sexual aleatório_, este último
leva em consideração a possibilidade de que o filho gerado pelos 2 primeiros não necessariamente é o melhor filho 
possível de ser gerado.


-----------------------------------------------------------------------------

# Executando

Há diferentes opções de execução, todas oferecidas pelo `Makefile`.

### Considerações

Definimos 3 números para representar os algoritmos genéticos estudados.
- Assexual: 0
- Sexual: 1
- Sexual Aleatório: 2

Além disso, definimos como configurações de simulação o fato de os pontos 
nascerem próximos de uma extremidade e buscarem ir para a diagonalmente oposta.

### `make`

Executará a aplicação base, que é uma simulação 2D de 20 pontos progredindo para o mouse,
utilizando o algoritmo 0.

### `make create`

Criará a aplicação geral, `./main`. Há duas formas de executar a aplicação.

- Desejando Apresentação Visual
	- `./main 1 N_1 N_2 N_3 N_4(?) N_5(?)`
	- N_1: Configurações de Simulação
	- N_2: Algoritmo Selecionado
	- N_3: Quantidade de Pontos
	- N_4(Opcional): Debugação
	- N_5(Opcional): Taxa de Mutação
- **Não** Desejando Apresentação Visual
	- `./main 0 N_1 N_2 N_3 N_4 N_5(?) N_6(?)`
	- N_1: Algoritmo Selecionado
	- N_2: Dimensão
	- N_3: Quantidade de Pontos
	- N_4: Quantidade de Gerações
	- N_5(Opcional): Debugação
	- N_6(Opcional): Taxa de Mutação

### `make python`

Criará uma biblioteca `.so` que pode ser utilizada em Python.
As funções presentes são as mesmas disponíveis em `./main`.