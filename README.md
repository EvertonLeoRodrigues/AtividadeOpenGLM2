# Descrição da entrega

O objetivo do exercício é revisar o conteúdo sobre criação de buffers de geometria e envio de informações para o
programa de shader. Para isso, você vai fazer uma versão modificada do Exercício 3 da resposta ao desafio, que
atende os seguintes requisitos:

1. Ao clicar na tela, você agora estará criando apenas 1 vértice
2. A cada 3 vértices criados, você criará um triângulo
3. Para cada novo triângulo criado, você deve usar uma cor nova.

Dicas:

- Você pode criar um VAO único ou diversos VAOs
- Você pode alterar a estrutura Triângulo do Exercício 3, para armazenar não mais a posição, e sim a
  geometria (vértices) do triângulo.
- Para facilitar o mapeamento, utilize projeção paralela ortográfica e defina a janela do mundo com as
  mesmas dimensões da tela (por ex. 800 x 600 unidades). Assim cada unidade do mundo corresponderá a
  um pixel na tela.
- Utilize o GLFW Input Guide para tratar eventos do clique do mouse.
