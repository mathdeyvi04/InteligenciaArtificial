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

### `make`

Executará a aplicação base, que é uma simulação 2D de pontos progredindo
para atingir o mouse.

### `make create`

... a ser definido.

### `make python`

Criará uma biblioteca `.so` que pode ser utilizada em Python.