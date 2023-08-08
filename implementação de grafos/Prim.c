// Trabalho implementação Grafos
// Andrei Bueno e Mauro Artur Gomes

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 20

// Definição da estrutura para representar o grafo
typedef struct
{
    int matriz[MAX_VERTICES][MAX_VERTICES]; //armazena a matriz de adjacência para representar as arestas
    int numVertices; // Número atual de vértices no grafo
} Grafo;

// Função para inicializar o grafo, configurando com 0 vértices e matriz de adjacência com zeros
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

// Função para adicionar um vértice ao grafo
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

// Função para adicionar uma aresta ao grafo
void adicionarAresta(Grafo *grafo, int origem, int destino, int distancia)
{
    if (origem >= 0 && origem < grafo->numVertices && destino >= 0 && destino < grafo->numVertices)
    {
        grafo->matriz[origem][destino] = distancia;
        grafo->matriz[destino][origem] = distancia; // Grafo não direcionado
        printf("Aresta adicionada com sucesso.\n");
    }
    else
    {
        printf("Vértice inválido.\n");
    }
}

// inicializarGrafo recebe um ponteiro para a estrutura Grafo e inicializa com 0 vértices e a matriz de adjacência com zeros.
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

// Encontra o vértice com menor chave no conjunto de vértices não incluídos
int encontrarMenorChave(int chaves[], bool incluido[], int numVertices)
{
    int menorChave = INT_MAX;
    int indiceMenorChave = -1;

    for (int v = 0; v < numVertices; v++)
    {
        if (!incluido[v] && chaves[v] < menorChave)
        {
            menorChave = chaves[v];
            indiceMenorChave = v;
        }
    }

    return indiceMenorChave;
}

// Função para imprimir a árvore geradora mínima
void imprimirArvoreGeradoraMinima(int arvoreGeradora[], Grafo *grafo)
{
    printf("Arestas da Arvore Geradora Minima:\n");
    for (int i = 1; i < grafo->numVertices; i++)
    {
        printf("%d - %d\n", arvoreGeradora[i], i);
    }
}

// Implementação do algoritmo de Prim para encontrar a Árvore Geradora Mínima
void prim(Grafo *grafo)
{
    int chave[grafo->numVertices];     // Guarda o valor da chave mínimo para cada vértice
    int arvoreGeradora[grafo->numVertices];  // Armazena a árvore geradora mínima resultante
    bool incluido[grafo->numVertices]; // Indica se o vértice já foi incluído na árvore geradora mínima

    // Inicializando todas as chaves como INT_MAX e incluído como falso
    for (int i = 0; i < grafo->numVertices; i++)
    {
        chave[i] = INT_MAX;
        incluido[i] = false;
    }

    // A raiz da árvore geradora mínima terá chave 0
    chave[0] = 0;
    arvoreGeradora[0] = -1; // O primeiro vértice é sempre a raiz da árvore geradora mínima

    // Construindo a árvore geradora mínima
    for (int count = 0; count < grafo->numVertices - 1; count++)
    {
        int u = encontrarMenorChave(chave, incluido, grafo->numVertices);
        incluido[u] = true;

        for (int v = 0; v < grafo->numVertices; v++)
        {
            // Verifica se o vértice v não está incluído na árvore geradora mínima e
            // se há uma aresta entre u e v com peso menor do que a chave atual de v
            if (!incluido[v] && grafo->matriz[u][v] && grafo->matriz[u][v] < chave[v])
            {
                arvoreGeradora[v] = u;
                chave[v] = grafo->matriz[u][v];
            }
        }
    }

    // Imprime a árvore geradora mínima
    imprimirArvoreGeradoraMinima(arvoreGeradora, grafo);
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

        prim(&grafo);
    }
    else
    {
        printf("Numero de vertices invalido.\n");
    }

    return 0;
}
