# Uma Questão de Arquitetura

Ao tentar construir a aplicação do joguinho do dinossauro em C++, a linha de desenvolvimento saiu um
pouco do controle... De fato, posso acusar minha responsabilidade, entretanto, ao utilizar o `valgrind`
para verificar erros de vazamentos, obtive:

HEAP SUMMARY:
- in use at exit: 519,131 bytes in 4,709 blocks
- total heap usage: 155,298 allocs, 150,589 frees, 131,262,694 bytes allocated


- 601 bytes in 1 blocks are definitely lost in loss record 2,562 of 2,590

at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
by 0x62F9843: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x62F9993: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x62FA229: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x62FAB62: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x62ECDB4: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x62EF86D: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x4973CFB: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.3000.0)
by 0x4975086: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.3000.0)
by 0x4949302: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.3000.0)
by 0x4947550: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.3000.0)
by 0x48DB0A6: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.3000.0)

- 102,144 (224 direct, 101,920 indirect) bytes in 1 blocks are definitely lost in loss record 2,588 of 2,590

at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
by 0x62F83DE: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x62F9954: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x62FA229: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x62FAB62: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x62ECDB4: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x62EF86D: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x4973CFB: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.3000.0)
by 0x4975086: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.3000.0)
by 0x4949302: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.3000.0)
by 0x4947550: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.3000.0)
by 0x48DB0A6: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.3000.0)

- 166,656 (224 direct, 166,432 indirect) bytes in 1 blocks are definitely lost in loss record 2,590 of 2,590

at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
by 0x62F83DE: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x62F9A06: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x62FA229: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x62FAB62: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x62ECDB4: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x62EF86D: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
by 0x4973CFB: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.3000.0)
by 0x4975086: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.3000.0)
by 0x4949302: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.3000.0)
by 0x4947550: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.3000.0)
by 0x48DB0A6: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.3000.0)

LEAK SUMMARY:

- definitely lost: 1,049 bytes in 3 blocks

- indirectly lost: 268,352 bytes in 1,198 blocks

- possibly lost: 0 bytes in 0 blocks

- still reachable: 249,730 bytes in 3,508 blocks

   suppressed: 0 bytes in 0 blocks
Reachable blocks (those to which a pointer was found) are not shown.
To see them, rerun with: --leak-check=full --show-leak-kinds=all

For lists of detected and suppressed errors, rerun with: -s
ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)

# Análise do Relatório Valgrind

## Resumo Geral

- Memória em uso ao sair: **519.131 bytes** em **4.709 blocos**
- Total de alocações: **155.298**  
- Total de liberações: **150.589**  
- Total alocado: **~131 MB**

## Erros Encontrados

1. **601 bytes em 1 bloco**
   - Alocado por `malloc`
   - Origem: biblioteca gráfica `libGLX_mesa.so` (OpenGL Mesa   - Uso indireto via SDL2

2. **102.144 bytes (224 diretos + 101.920 indiretos) em 1 bloco**
   - Alocado por `calloc`
   - Também originado em `libGLX_mesa.so`
   - Relacionado à alocação interna do driver OpenGL

3. **166.656 bytes (224 diretos + 166.432 indiretos) em 1 bloco**
   - Alocado por `calloc`
   - Origem semelhante às anteriores, dentro de `libGLX_mesa.so`

## Interpretação Objetiva

- Todos os vazamentos ocorrem dentro de bibliotecas do sistema gráfico, principalmente `libGLX_mesa.so` e indiretamene via SDL2.
- O código do usuário não apresenta vazamentos diretos, nem erros de acesso.
- Vazamentos em bibliotecas gráficas são comuns e geralmente não indicam problemas graves no código da aplicação.

---

## Conclusão

O programa não apresenta erros graves, mas possui vazamentos moderados originados nas bibliotecas
gráficas externas. Esses vazamentos podem ser considerados esperados em muitos casos, principalmente
em bibliotecas de drivers OpenGL e SDL2. 

Sendo assim, deduz-se que não havia erro em nosso desenvolvimento.























