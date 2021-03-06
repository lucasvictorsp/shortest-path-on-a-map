## Encontrar o melhor caminho em um mapa 2D:

Um conjunto de mapas está disponível na pasta *maps*. Estes mapas são bidimensionais, representados por matrizes de caracteres. A formatação dos mapas é simples: células marcadas com um “.” estão livres e células marcadas com um “@” estão bloqueadas. Na implementação dos agentes assumiremos que eles poderão se mover nas seguintes direções: cima, baixo, direita, esquerda, todas com o custo de 1, além das diagonais, com o custo de 1,5 (≈√2). Movimentos diagonais não serão permitidos em cantos que estiverem bloqueados.<br/>

Na implementação dos algoritmos <font style="font-family: monaco">Uniform Cost Search (UCS)</font>, <font style="font-family: monaco">A\*</font> e <font style="font-family: monaco">WA\*</font> foi utilizado a linguagem *C++*, e algumas classes nativas, como:

- **iostream:** para tratamento de entrada e saída de dados.
- **fstream:** para tratamento de arquivo, neste caso arquivos de texto (*.map).
- **string:** para tratamento de cadeias de caracteres.
- **cstdlib:** para alguns tratamentos de erro como o *exit(1)*, caso a leitura do programa falhe.
- **cmath:** para trabalhar com conceitos matemáticos como criação de variáveis inteiras com custo infinito (através do *HUGE_VAL*)

E outras classes implemetadas neste trabalho, tais como:

- **PontoMap:** tem como atributos *private* quatro variáveis int's: x*, *y*, *xPai* e *Ypai*. As variáveis *x* e *y* definem o ponto que o agente se encontra no mapa (ponto corrente) e *xPai* e *Ypai* armazenam as coordenas do pai do ponto corrente (o ponto antecessor). Além de duas variáveis float: *costoP* e *valorHeuristico*. A variáveis *custoP* guarda o custo real para chegar do ponto inicial até o ponto corrente e *valorHeuristico* armazena o valor heurístico para chegar ao ponto meta. Esta classe é usada para manipular o agente na matriz de pontos (andar com o agente pelo mapa).

- **Lista.h:** esta classe foi criada pelo professor do departamento de informática da UFV Marcus Vinicius e edita em 20/03/15 por mim. Ela foi usada na *estrutura aberta* dos métodos.

- **Hash.h:** esta classe foi criada com base no algoritmo do professor Marcus Vinicius. Ela foi usada na criação da *estrutura fechada* dos métodos.

Todos os árquivos *.cpp e *.h estão comentados.<br/>
Todos os 3 métodos são baseados no pseudocódigo abaixo. A diferença entre eles está em como os métodos implementam a função de **custo**.<br/>
<br/>
*Inserir* o ponto inicial em *aberto*<br/>
**Enquanto** *aberto* não estiver vazio<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;C = Primeiro elemento de *aberto*<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Se C é M então retornar caminho<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Para cada** X filho de C<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Se** X ∈ *aberto* e (g(X) > g(C) + custo(C, X))<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Substitui (X, g(X)) por (X, g(C) + custo(C, X))<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Se** X ∉ aberto e X ∉ fechado<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Inserir X em aberto<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Inserir C em fechado<br/>

#### UCS:

No *UCS* a função de custo é dada pelo *custo real* que o agente levou para sair do ponto inicial até o ponto corrente.

#### A\*:

No método *A\** o custo de chegar até o ponto corrente é o *curto real* adicionado do *custo heurístico* (*valor Heurístico*).

#### WA\*:

O método *WA\** é apenas uma adaptação da função heurística, ou seja, ela é multiplicada pelo valor de **W**.<br/>

#### Principais características da implementação:

- **Aberto**: na criação da estrutura aberta a ideia foi implementa uma lista simplesmente encadeada que contém uma função *buscaBinaria* e outra *InsereOrdenado* que usufruirá da função *buscaBinaria*.Além disso, é usado como auxiliar um *hash* que verificaria em tempo constante (O(1)), se o PontoMap está contido ou não na lista aberta.

- **Fechado:** na criação da estrutura fechada foi utilizado uma *hash* com uma função de transformação perfeita (sem conflitos), dada por: K = (i * Largura + j), onde *i* é a linha e *j* é a coluna da matriz.

#### Compilar e Executar:

O algoritmo foi implementado e testado apenas no *SO Linux*. Entretanto, é provável que ele execute no Windows sem a necessidade de modificar os códigos fonte.<br/>

Para compilar basta entrar na pasta raiz do projeto e executar o **comando make**<br/>
Para executar o algoritmo basta, após o realizar com sucesso a eecução do comando make, utilizar o comando **./main**.<br/>

Um exemplo do algoritmo é apresentado abaixo:<br/>
**Obs.1:** Note que há um *custo computacional* no calculo da *função heurística*. Portanto, em alguns casos, *A\** levará um tempo maior para executar quando comparado ao método *UCS*, mesmo expandindo um número menor de nós.<br/> 
**Obs.2:** Repare no exemplo que dependendo do valor de W a função heurística utilizada se torna inadmissível e o método *WA\** não encontrado a **solução ótima**.
![alt text](https://github.com/lucasvictorsp/shortest-path-on-a-map/blob/main/example%20of%20running%20the%20algorithm.png)