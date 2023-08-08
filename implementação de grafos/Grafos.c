// Trabalho implementação Grafos
// Andrei Bueno e Mauro Artur Gomes

#include <stdio.h>

#define MAX_VERTICES 20

typedef struct
{
    int matriz[MAX_VERTICES][MAX_VERTICES]; // armazena a matriz de adjacência para representar as arestas
    int numVertices; // Número atual de vértices no grafo
} Grafo;

//Recebe um ponteiro para a estrutura Grafo e inicializa com 0 vértices e a matriz de adjacência com zeros.
void inicializarGrafo(Grafo *grafo)
{
    grafo->numVertices = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        for (int j = 0; j < MAX_VERTICES; j++)
        {
            grafo->matriz[i][j] = 0;
        }
    }
}

//recebe um ponteiro para a estrutura Grafo e vai adicionar um novo vértice ao grafo, aumentando o contador numVertices caso não tenha atingido o limite máximo.
void adicionarVertice(Grafo *grafo)
{
    if (grafo->numVertices < MAX_VERTICES)
    {
        grafo->numVertices++;
    }
    else
    {
        printf("Limite maximo de vertices atingido.\n");
    }
}

//verifica se os vértices de origem e destino são válidos e adiciona a aresta à matriz de adjacência com a distância fornecida.
void adicionarAresta(Grafo *grafo, int origem, int destino, int distancia)
{
    if (origem >= 0 && origem < grafo->numVertices && destino >= 0 && destino < grafo->numVertices)
    {
        grafo->matriz[origem][destino] = distancia;
        printf("Aresta adicionada com sucesso.\n");
    }
    else
    {
        printf("Vertice invalido.\n");
    }
}

//  imprime o conteúdo da matriz de adjacência, mostrando as conexões entre os vértices.
void mostrarGrafo(Grafo *grafo)
{
    printf("Grafo:\n");
    for (int i = 0; i < grafo->numVertices; i++)
    {
        for (int j = 0; j < grafo->numVertices; j++)
        {
            printf("%d ", grafo->matriz[i][j]);
        }
        printf("\n");
    }
}

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
            adicionarVertice(&grafo);
        }

        int origem, destino, distancia;
        printf("Digite as informacoes das arestas:\n");
        printf("(Origem, Destino, Peso) - Digite '.' para finalizar:\n");
        while (scanf("%d %d %d", &origem, &destino, &distancia) == 3)
        {
            adicionarAresta(&grafo, origem - 1, destino - 1, distancia);
        }

        // Limpar o buffer de entrada antes de prosseguir
        while (getchar() != '\n')
            ;

        mostrarGrafo(&grafo);
    }
    else
    {
        printf("Número de vértices invalido.\n");
    }

    return 0;
}
