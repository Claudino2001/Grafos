#ifndef FLOODING
#define FLOODING

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "fila.h"
#include "grafo.h"
#include "grafo_struct.h"

void flooding(Grafo *gr, int *vizitados, int start);

int mapeando_vertices(Vertice *vertice, Grafo *gr);

void flooding(Grafo *gr, int *vizitados, int start){
    tp_fila fila;
    inicializa_fila(&fila);
    vizitados[start] = 1;
    insere_fila(&fila, start);
    while(!fila_vazia(&fila)){
        int s;
        remove_fila(&fila, &s);
        No *no_aux = gr->raiz[s].lista_adjacentes;
        int i;
        for(i=0; i<gr->raiz[s].num_aresta; i++){
            no_aux = no_aux->prox_no;
            int v = mapeando_vertices(no_aux->vertice, gr);
            if(!vizitados[v]){
                vizitados[v] = 1;
                insere_fila(&fila, v);
            }
        }
    }
}

int mapeando_vertices(Vertice *vertice, Grafo *gr){
    int i;
    for(i=0; i<gr->num_vertices; i++){
        if(vertice == &gr->raiz[i]){
            return i;
        }
    }
    return -1;
}

int conta_conexo(Grafo *gr){
    int i, count = 0;
    int vizitados[gr->num_vertices];
    memset(vizitados, 0, sizeof(vizitados));
    for(i=0; i<gr->num_vertices; i++){
        if(!vizitados[i]){
            flooding(gr, vizitados, i);
            count++;
        }
    }
    return count;
}

#endif