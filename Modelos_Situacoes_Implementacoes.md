# Estratégias de Modelos de IA e Implementações Matemáticas

Tipos de modelos e algoritmos, suas situações ideais de uso e suas respectivas implementações matemáticas, este último
permite a ampla aplicação e adaptabilidade.

---

## 1. Algoritmos Genéticos (GA)
- **Situação ideal**: quando há um objetivo definido, mas caminhos múltiplos e complexos para atingi-lo.
- **Exemplos**: otimização de trajetórias, design de estratégias.
- **Implementação (matemática)**:  
  - Um conjunto de **cromossomos** $C = \{c_1, c_2, ..., c_n\}$ representa soluções candidatas.
  - A cada geração:
    - Avalia-se a **função de aptidão** $f(c_i)$.
    - Selecionam-se os melhores indivíduos via **roleta, torneio, etc.**
    - Geram-se **filhos** por **crossover** e **mutação**:
      $$c' = \text{Mutação}( \text{Crossover}(c_i, c_j) )$$
    - Substituição gera nova população $C_{t+1}$.

---

## 2. Redes Neurais (ANN/DNN/CNN/RNN)
- **Situação ideal**: padrões complexos em dados massivos e rotulados.
- **Exemplos**: visão computacional, previsão de séries temporais.
- **Implementação (matemática)**:
  - Cada neurônio computa:
    $$y = \sigma\left( \sum_{i} w_i x_i + b \right)$$
  - A rede é uma composição de várias camadas:
    $$\mathbf{y} = f_L \circ f_{L-1} \circ \cdots \circ f_1(\mathbf{x})$$
  - Treinada por **backpropagation** e **descida do gradiente**:
    $$w \leftarrow w - \eta \cdot \frac{\partial \mathcal{L}}{\partial w}$$

---

## 3. Árvores de Decisão / Random Forest / XGBoost
- **Situação ideal**: dados estruturados com regras de decisão claras.
- **Exemplos**: classificação binária/tabular, ranking.
- **Implementação (matemática)**:
  - Divide o espaço de entrada recursivamente com base em atributos $x_j$:
    $$\text{Divisão ideal: } \arg\max_j \Delta \text{Ganho de Informação}(x_j)$$
  - **Random Forest**: média das previsões de várias árvores:
    $$\hat{y} = \frac{1}{T} \sum_{t=1}^{T} h_t(\mathbf{x})$$
  - **XGBoost**: ajusta árvores para minimizar o erro residual:
    $$\hat{y}^{(t)} = \hat{y}^{(t-1)} + \eta \cdot h_t(x)$$

---

## 4. Aprendizado por Reforço (RL)
- **Situação ideal**: decisões sequenciais com feedback indireto.
- **Exemplos**: navegação, jogos, robótica.
- **Implementação (matemática)**:
  - Define-se um processo de decisão de Markov (MDP): $(S, A, P, R, \gamma)$
  - A função de valor é atualizada via Q-learning:
    $$Q(s,a) \leftarrow Q(s,a) + \alpha \left[ r + \gamma \max_{a'} Q(s',a') - Q(s,a) \right]$$
  - O objetivo é maximizar a soma esperada de recompensas:
    $$\pi^* = \arg\max_\pi \mathbb{E}\left[ \sum_{t=0}^\infty \gamma^t r_t \right]$$

---

## 5. Clustering / Agrupamento
- **Situação ideal**: estrutura oculta em dados não rotulados.
- **Exemplos**: segmentação de clientes, agrupamento de documentos.
- **Implementação (matemática - K-Means)**:
  - Inicializa centros $\mu_1, ..., \mu_k$.
  - Alterna entre:
    - **Atribuição**:
      $$C_i = \{ x_j : \|x_j - \mu_i\|^2 \leq \|x_j - \mu_l\|^2, \forall l \}$$
    - **Atualização**:
      $$\mu_i = \frac{1}{|C_i|} \sum_{x \in C_i} x$$

---

## 6. Autoencoders
- **Situação ideal**: compressão de dados e redução de ruído.
- **Exemplos**: pré-processamento, visualização.
- **Implementação (matemática - PCA)**:
  - Centraliza os dados $X$.
  - Calcula a matriz de covariância:
    $$\Sigma = \frac{1}{n} X^T X$$
  - Extrai os autovetores $v_1, ..., v_k$ associados aos maiores autovalores.
  - Projeta os dados:
    $$X_{\text{proj}} = X V_k$$

---

## 7. Modelos Probabilísticos (Naive Bayes, HMM)
- **Situação ideal**: presença de incerteza e dependências estatísticas.
- **Exemplos**: classificação de texto, análise de sequência.
- **Implementação (matemática - Naive Bayes)**:
  - Baseado na regra de Bayes:
    $$P(C_k | \mathbf{x}) \propto P(C_k) \prod_{i} P(x_i | C_k)$$
  - Supõe independência condicional entre atributos $x_i$ dado a classe $C_k$.

---

## 8. Transformers (BERT, GPT, etc.)
- **Situação ideal**: linguagem natural com dependências contextuais longas.
- **Exemplos**: tradução, perguntas e respostas, resumo automático.
- **Implementação (matemática)**:
  - O mecanismo central é o **self-attention**:
    $$\text{Attention}(Q, K, V) = \text{softmax}\left( \frac{QK^T}{\sqrt{d_k}} \right)V$$
  - Onde $Q, K, V$ são matrizes derivadas da entrada.
  - Um transformer empilha camadas de attention + feedforward:
    $$x_{l+1} = \text{LayerNorm}(x_l + \text{Attention}(x_l))$$
---
