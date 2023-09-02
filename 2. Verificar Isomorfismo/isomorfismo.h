#ifndef GRAFO_ISOMORFO
#define GRAFO_ISOMORFO

#define TRUE 1
#define FALSE 0

#include "grafo.h"
#include "Bubble_Sort.h"

// Verifica se os grafos fornecidos possuem o mesmo numero de vertices.
int same_vertices(Grafo *gr1, Grafo *gr2);

// Verifica se os grafos fornecidos possuem o mesmo numero de arestas.
int same_arestas(Grafo *gr1, Grafo *gr2);

int same_graus(Grafo *gr1, Grafo *gr2);

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

int same_graus(Grafo *gr1, Grafo *gr2){
    int i = 0, j = 0;
    for(i=0; i<gr1->num_vertices; i++){
        Vertice *vertice_aux = &gr1->raiz[i];
        No *no_aux = vertice_aux->lista_adjacentes;
        
        int *lista_de_graus = (int*)malloc(((gr1->num_aresta*2)+gr1->num_vertices)*sizeof(int));

        while(no_aux->prox_no != NULL){
            //printf("%d/", no_aux->prox_no->vertice->num_graus);
            lista_de_graus[j++] = no_aux->prox_no->vertice->num_graus;
            printf("\n\t %d \n\n", no_aux->prox_no->vertice->num_graus);
            no_aux = no_aux->prox_no;
            printf("\n------>   J: %i\n", j);
        }
        printf("Vertice: %s | Grau: %d\n", vertice_aux->rotulo, vertice_aux->num_graus);
        
        int k;
        for(k=0; k < vertice_aux->num_graus; k++)
            printf("%i | ", lista_de_graus[k]);
        printf("\n\n");
    }
}

#endif