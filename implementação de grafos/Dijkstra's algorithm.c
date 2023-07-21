#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 20
#define INFINITO 9999

typedef struct
{
    int matriz[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Grafo;

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

void dijkstra(Grafo *grafo, int origem, int destino)
{
    int distancias[MAX_VERTICES];  // Armazena as distâncias mínimas
    bool visitado[MAX_VERTICES];   // Marca se um vértice foi visitado ou não
    int anterior[MAX_VERTICES];    // Armazena o vértice anterior no caminho mínimo

    // Inicializa as estruturas de dados
    for (int i = 0; i < grafo->numVertices; i++)
    {
        distancias[i] = INFINITO;
        visitado[i] = false;
        anterior[i] = -1;
    }

    // A distância da origem para ela mesma é zero
    distancias[origem] = 0;

    // Encontra o caminho mínimo
    for (int count = 0; count < grafo->numVertices - 1; count++)
    {
        // Encontra o vértice com a menor distância
        int minDistancia = INFINITO;
        int minVertice;

        for (int v = 0; v < grafo->numVertices; v++)
        {
            if (visitado[v] == false && distancias[v] <= minDistancia)
            {
                minDistancia = distancias[v];
               minVertice = v;
            }
        }

        // Marca o vértice como visitado
        visitado[minVertice] = true;

        // Atualiza as distâncias dos vértices adjacentes
        for (int v = 0; v < grafo->numVertices; v++)
        {
            if (visitado[v] == false && grafo->matriz[minVertice][v] != 0 && distancias[minVertice] + grafo->matriz[minVertice][v] < distancias[v])
            {
                distancias[v] = distancias[minVertice] + grafo->matriz[minVertice][v];
                anterior[v] = minVertice;
            }
        }
    }

    // Mostra o caminho mínimo
    printf("Caminho minimo entre %d e %d: ", origem + 1, destino + 1);
    int vertice = destino;
    printf("%d", vertice + 1);

    while (vertice != origem)
    {
        vertice = anterior[vertice];
        printf(" <- %d", vertice + 1);
    }

    printf("\nDistancia minima: %d\n", distancias[destino]);
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

        int verticeOrigem, verticeDestino;
        printf("Digite o vertice de origem: ");
        scanf("%d", &verticeOrigem);
        printf("Digite o vertice de destino: ");
        scanf("%d", &verticeDestino);

        dijkstra(&grafo, verticeOrigem - 1, verticeDestino - 1);
    }
    else
    {
        printf("Numero de vertices invalido.\n");
    }

    return 0;
}
