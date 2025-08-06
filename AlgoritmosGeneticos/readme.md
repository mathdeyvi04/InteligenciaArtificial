# Objetivo

Analisar eficiência de algoritmos genéticos, os quais
serão utilizados puramente como estatística e probabilidade.

# [Um Pouco do Estudo](UmPoucoDoEstudo.md)

# Executando

Há duas opções principais de execução, ambas oferecidas pelo `Makefile`.

## Pelo C++

### `make`

Executará a aplicação base, que é uma simulação 2D de pontos progredindo
para atingir o mouse.

### `make create`

Criará o executável que será responsável por gerar uma simulação mais avançada e
profunda. Execute-o da seguinte forma:

- `./main N_1 N_2 N_3`

Retornará a quantidade mínima de gerações necessárias para uma quantidade de N_2 
pontos de dimensão N_1 atingir um limiar de convergência N_3.

### `make python`

Criará uma biblioteca `.so` dotada de duas funções: `apresentation_points`, que possui 
mesmo resultado de `make`, `simulation_points`, que é o mesmo resultado de `./main N_1 N_2 N_3`.
Há documentações aprofundadas em cada.
