# Objetivo

Este projeto demonstra o impacto crítico do uso eficiente do **Cache da CPU** ao manipular matrizes em C. Através de dois métodos de soma, evidenciamos como a ordem de iteração nos loops pode reduzir o tempo de execução.

## Comparativo de Performance

O código compara duas abordagens para percorrer uma matriz de $1024 \times 1024$ armazenada de forma linear (Row-Major Order), somando seus valores $1000$ vezes.

| Método            | Ordem de Loop  | Tempo Médio |
|:------------------|:---------------|:------------|
| `sum_mat_row_col` | Linha → Coluna | **~0.77s**  |
| `sum_mat_col_row` | Coluna → Linha | **~2.12s**  |

## Por que a diferença é tão grande?

A memória RAM é linear. Quando declaramos uma matriz, ela é mapeada na memória linha após linha. O processador não busca apenas um único `float` por vez, mas sim uma **Cache Line** inteira (geralmente 64 bytes).

### 1. Acesso por Linha (Row-Major)
Ao percorrer a matriz linha por linha (`row` no loop externo), acessamos os dados exatamente como eles estão dispostos na memória. Isso resulta em um alto índice de **Cache Hits**.

```text
Matriz Lógica (3x3):         Memória Física (Linear):
   Col 0  1  2               Index: 0  1  2  3  4  5  6  7  8
Row 0 [1][2][3]              Dados:[1][2][3][4][5][6][7][8][9]
Row 1 [4][5][6]                     |  |  |  |  |  |  |  |  |
Row 2 [7][8][9]                     +--+--+--+--+--+--+--+--+-->
                                    Acesso Sequencial (Rápido)
```


### 2. Acesso por Coluna (Strided Access)
Ao percorrer coluna por coluna (`col` no loop externo), a cada iteração do loop interno o programa "pula" uma linha inteira na memória. Isso força a CPU a buscar novas Cache Lines constantemente, gerando **Cache Misses** e forçando a busca de dados na memória RAM, que é muito mais lenta.

```text
Matriz Lógica (3x3):         Memória Física (Linear):
   Col 0  1  2                Index: 0  1  2  3  4  5  6  7  8
Row 0 [1][ ]                  Dados:[1][2][3][4][5][6][7][8][9]
Row 1 [4][ ]                        |        ^  |        ^
Row 2 [7][ ]                        |________|  |________|
                                       Pulo        Pulo
                                    (Strided Access / Lento)
```