#ifndef GRAFO_ISOMORFO
#define GRAFO_ISOMORFO

#define TRUE 1
#define FALSE 0

#include "grafo.h"

// Verifica se os grafos fornecidos possuem o mesmo numero de vertices.
int same_vertices(Grafo *gr1, Grafo *gr2);

// Verifica se os grafos fornecidos possuem o mesmo numero de arestas.
int same_arestas(Grafo *gr1, Grafo *gr2);

int same_graus();

// *** Desenvolvendo as funções ***

int same_vertices(Grafo *gr1, Grafo *gr2){
    if(gr1->num_vertices == gr2->num_vertices)
        return TRUE;
    return FALSE;
}

int same_arestas(Grafo *gr1, Grafo *gr2){
    if(gr1->num_aresta == gr2->num_aresta)
        return TRUE;
    return FALSE;  
}

#endif