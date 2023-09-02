#ifndef GRAFO_ISOMORFO
#define GRAFO_ISOMORFO

#define TRUE 1
#define FALSE 0

#include "grafo.h"
#include "fila.h"
#include "Bubble_Sort.h"

// Verifica se os grafos fornecidos possuem o mesmo numero de vertices.
int same_vertices(Grafo *gr1, Grafo *gr2);

// Verifica se os grafos fornecidos possuem o mesmo numero de arestas.
int same_arestas(Grafo *gr1, Grafo *gr2);

// Mapea o grafo retornando index referente a poisição d amatriz
int mapeando_vertices(Vertice *vertice, Grafo *gr);

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
    if(!same_vertices(gr1, gr2) && !same_arestas(gr1, gr2))
        return FALSE;

    int array_vizinhos[gr1->num_vertices];
    int array_vizinhos2[gr1->num_vertices];
    memset(array_vizinhos, 0, sizeof(array_vizinhos)); // Insere em todas as posições do vetor o valor zero
    memset(array_vizinhos2, 0, sizeof(array_vizinhos2));
    int i, j, flag = 1;
    tp_fila fila1, fila2;
    inicializa_fila(&fila1);
    inicializa_fila(&fila2);
        
    for(j=0; j<gr1->num_vertices; j++){
        if((gr1->raiz[0].num_graus == gr2->raiz[j].num_graus) && (gr1->raiz[0].num_aresta == gr2->raiz[j].num_aresta)){
            array_vizinhos[0] = 1;
            array_vizinhos2[j] = 1;
            insere_fila(&fila1, 0);
            insere_fila(&fila2, j);
            flag = 0;
            printf("\nrotulo0: %s | rotulo1: %s\n", gr1->raiz[0].rotulo, gr2->raiz[j].rotulo);
            break;
        }
    }

    if(flag)
        return FALSE;

    while(!fila_vazia(&fila1)){
        int start1, start2;
        remove_fila(&fila1, &start1);
        remove_fila(&fila2, &start2);
        
        printf("--> s1: %d | s2: %d\n", start1, start2);

        int p;
        for(p=0; p<gr1->raiz[start1].num_aresta; p++){
            int v = mapeando_vertices(&gr1->raiz[start1], gr1);
            if(!array_vizinhos[v]){
                insere_fila(&fila1, v);
                array_vizinhos[v] = 1;
            }
        }
        for(p=0; p<gr2->raiz[start2].num_aresta; p++){
            int v = mapeando_vertices(&gr2->raiz[start2], gr2);
            if(!array_vizinhos2[v]){
                insere_fila(&fila2, v);
                array_vizinhos2[v] = 1;
            }
        }
        if(tamanho_fila(&fila1) != tamanho_fila(&fila2)){
            return FALSE;
        }
    }

    return TRUE;

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


#endif