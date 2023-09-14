#ifndef GRAPH_STRUCT
#define GRAPH_STRUCT

// Estrutura do Grafo
typedef struct No {
    struct Vertice* vertice;
    struct No* prox_no;
} No;

typedef struct Vertice{
    char rotulo[20];
    int num_graus;
    int num_aresta;
    No* lista_adjacentes;
} Vertice;

typedef struct {
    int num_vertices;
    int num_aresta;
    struct Vertice* raiz;
} Grafo;

#endif