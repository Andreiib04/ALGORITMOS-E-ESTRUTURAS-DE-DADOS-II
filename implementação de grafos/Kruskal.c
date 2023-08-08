// Andrei Bueno e Mauro Artur Gomes
#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 20

typedef struct
{
    int matriz[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Grafo;

typedef struct
{
    int origem;
    int destino;
    int peso;
} Aresta;

// Inicializa a estrutura do Grafo
void inicializarGrafo(Grafo *grafo)
{
    grafo->numVertices = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        for (int j = 0; j < MAX_VERTICES; j++)
        {
            grafo->matriz[i][j] = 0;  // Inicializa todas as células da matriz de adjacência com 0
        }
    }
}

// Adiciona um vértice ao grafo
void adicionarVertice(Grafo *grafo)
{
    if (grafo->numVertices < MAX_VERTICES)
    {
        grafo->numVertices++;  // Incrementa o número de vértices do grafo
    }
    else
    {
        printf("Limite máximo de vértices atingido.\n");  // Informa quando o limite de vértices é atingido
    }
}

// Adiciona uma aresta entre vértices com uma distância
void adicionarAresta(Grafo *grafo, int origem, int destino, int distancia)
{
    if (origem >= 0 && origem < grafo->numVertices && destino >= 0 && destino < grafo->numVertices)
    {
        grafo->matriz[origem][destino] = distancia;  // Adiciona a aresta na matriz de adjacência (grafo não direcionado)
        grafo->matriz[destino][origem] = distancia;  // Adiciona também a aresta no sentido contrário
        printf("Aresta adicionada com sucesso.\n");  // Mensagem de confirmação
    }
    else
    {
        printf("Vértice inválido.\n");  // Informa quando um vértice inválido é fornecido
    }
}

// Mostra a representação do grafo como matriz de adjacência
void mostrarGrafo(Grafo *grafo)
{
    printf("Grafo:\n");
    printf("   ");
    for (int i = 0; i < grafo->numVertices; i++)
    {
        printf("%2d ", i + 1);  // Imprime números dos vértices
    }
    printf("\n");
    for (int i = 0; i < grafo->numVertices; i++)
    {
        printf("%2d ", i + 1);  // Imprime número do vértice atual
        for (int j = 0; j < grafo->numVertices; j++)
        {
            printf("%2d ", grafo->matriz[i][j]);  // Imprime as células da matriz de adjacência
        }
        printf("\n");
    }
}

// Encontra o representante (raiz) de um conjunto usando o algoritmo Union-Find
int encontrarRepresentante(int representantes[], int vertice)
{
    if (representantes[vertice] != vertice)
    {
        representantes[vertice] = encontrarRepresentante(representantes, representantes[vertice]);
    }
    return representantes[vertice];  // Retorna o representante do conjunto
}

// Une dois conjuntos usando o algoritmo Union-Find
void unirConjuntos(int representantes[], int conjuntoA, int conjuntoB)
{
    int representanteA = encontrarRepresentante(representantes, conjuntoA);
    int representanteB = encontrarRepresentante(representantes, conjuntoB);
    representantes[representanteA] = representanteB;  // Une os conjuntos fazendo um representante ser pai do outro
}

// Função de comparação para ordenar as arestas pelo peso
int compararArestas(const void *a, const void *b)
{
    return ((Aresta *)a)->peso - ((Aresta *)b)->peso;  // Compara o peso de duas arestas para ordená-las
}

// Encontra a Árvore Geradora Mínima usando o algoritmo de Kruskal
void kruskalMST(Grafo *grafo)
{
    Aresta arestas[MAX_VERTICES * MAX_VERTICES];
    int numArestas = 0;

    // Preenche o array de arestas
    for (int i = 0; i < grafo->numVertices; i++)
    {
        for (int j = i + 1; j < grafo->numVertices; j++)
        {
            if (grafo->matriz[i][j] > 0)
            {
                arestas[numArestas].origem = i;
                arestas[numArestas].destino = j;
                arestas[numArestas].peso = grafo->matriz[i][j];
                numArestas++;  // Incrementa o número de arestas
            }
        }
    }

    // Ordena as arestas em ordem crescente de peso
    qsort(arestas, numArestas, sizeof(Aresta), compararArestas);

    int representantes[MAX_VERTICES];
    for (int i = 0; i < grafo->numVertices; i++)
    {
        representantes[i] = i;  // Cada vértice é inicialmente seu próprio representante
    }

    printf("\nArvore Geradora minima:\n");
    for (int i = 0; i < numArestas; i++)
    {
        int origem = arestas[i].origem;
        int destino = arestas[i].destino;
        int peso = arestas[i].peso;

        // Verifica se a inclusão da aresta não forma um ciclo
        if (encontrarRepresentante(representantes, origem) != encontrarRepresentante(representantes, destino))
        {
            printf("%2d - %2d (peso %d)", origem + 1, destino + 1, peso);
            printf("\t");
            printf("\n"); 
            unirConjuntos(representantes, origem, destino);  // Une os conjuntos dos vértices conectados pela aresta
        }
    }
    printf("\n");
}

// Função principal
int main()
{
    Grafo grafo;
    inicializarGrafo(&grafo);

    int numVertices;
    printf("Digite o numero de vertices (maximo %d): ", MAX_VERTICES);
    scanf("%d", &numVertices);

    if (numVertices > 0 && numVertices <= MAX_VERTICES)
    {
        for (int i = 0; i < numVertices; i++)
        {
            adicionarVertice(&grafo);  // Adiciona vértices ao grafo
        }

        int origem, destino, distancia;
        printf("Digite as informacoes das arestas:\n");
        printf("(Origem, Destino, Peso) - Digite '.' para finalizar:\n");
        while (scanf("%d %d %d", &origem, &destino, &distancia) == 3)
        {
            adicionarAresta(&grafo, origem - 1, destino - 1, distancia);  // Adiciona arestas ao grafo
        }

        // Limpa o buffer de entrada antes de prosseguir
        while (getchar() != '\n')
            ;

        mostrarGrafo(&grafo);  // Mostra a representação do grafo

        kruskalMST(&grafo);  // Aplica o algoritmo de Kruskal para encontrar a Árvore Geradora Mínima
    }

    return 0;  // Finaliza o programa
}
