# KD-Tree

a) Construa uma k-d tree de duas dimensões (x, y) em que, para cada etapa, o ponto
selecionado para criar o plano de corte será a mediana dos pontos colocados na árvore, o
que respeita suas coordenadas no eixo que está sendo usado (primeiro x, depois y, depois
novamente x e y, e assim por diante). Dada uma quantidade de n pontos, o algoritmo deve
gerar aletoriamente os pontos para em seguida construir a k-d tree usando sempre o ponto
mediano do conjunto de pontos e dividindo o conjunto em duas metades. Cada metade
deve ser ordenada por x ou y (repeitando o eixo usado) e encontrado o novo ponto mediano,
a partir dai o processo se repete até que cada metade tenha tamanho 0. Exemplo:
Passo 1: ordena o conjunto de pontos pelo eixo x, pega o ponto mediano e insere na raiz da
árvore. Você agora tem 2 metades.
Passo 2: para a metade Esquerda (obtida no Passo 1), ordena pelo eixo y, pega o ponto
mediano e insere na ligação esquerda do nó atual (nesse caso é a raiz). Você terá duas
novas metades. Faça o mesmo com a metade da direita.
.... E o processo se repete para as novas metades, até que dodas as metades tenham
tamanho 1.

b) Faça uma busca que retorne os pontos mais próximos de uma dada coordenada e raio.
Utilize a distância euclidiana entre o ponto (coordenada fornecida) e os pontos inseridos na
árvore.
Exemplo de pontos gerados para n = 6: (30,40), (5,25), (10,12), (70,70), (50,30), (35,45).

c) Exiba a k-d tree no formato de árvore.
