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

int checa_vizinhos_correspondendes(Vertice *vertice1, Vertice *vertice2);

int em_ordem(Grafo *gr, Vertice *vertice_chegada, int start);

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
    
    int maior_grau = gr1->raiz[0].num_graus;
    int maior_grau_index = 0;

    for(j=1; j<gr1->num_vertices; j++){
        if(gr1->raiz[j].num_graus > maior_grau){
            maior_grau = gr1->raiz[j].num_graus;
            maior_grau_index = j;
        }
    }

    array_vizinhos[maior_grau_index] = 1;

    int valores1[maior_grau_index];
    int valores2[maior_grau_index];
    memset(valores1, 0, sizeof(valores1)); // Insere em todas as posições do vetor o valor zero
    memset(valores2, 0, sizeof(valores2)); // Insere em todas as posições do vetor o valor zero
    
    No *no_aux = gr1->raiz[maior_grau_index].lista_adjacentes;
    
    j=0;
    while(no_aux->prox_no != NULL){
        printf("Rotulo do vertice que bie quer saber: %s\n", no_aux->vertice->rotulo);
        valores1[j++] = em_ordem(gr1, &gr1->raiz[maior_grau_index], mapeando_vertices(no_aux->prox_no->vertice, gr1));
        no_aux = no_aux->prox_no;
    }

    for(j=0; j<maior_grau;j++){
        printf("%i - ", valores1[j]);
    }
    printf("\nUFA!\n");

    printf("start1: %d | rotulo: %s\n", maior_grau_index, gr1->raiz[maior_grau_index].rotulo );

    bubbleSort(valores1, maior_grau);

    int maior_grau2 = gr2->raiz[0].num_graus;
    maior_grau_index = 0;

    for(j=1; j<gr2->num_vertices; j++){
        if(gr2->raiz[j].num_graus > maior_grau2){
            maior_grau2 = gr2->raiz[j].num_graus;
            maior_grau_index = j;
        }
    }

    array_vizinhos2[maior_grau_index] = 1;

    /////////////////////////////////////////

    no_aux = gr2->raiz[maior_grau_index].lista_adjacentes;
    
    j=0;
    while(no_aux->prox_no != NULL){
        printf("Rotulo do vertice que bie quer saber: %s\n", no_aux->vertice->rotulo);
        valores2[j++] = em_ordem(gr2, &gr2->raiz[maior_grau_index], mapeando_vertices(no_aux->prox_no->vertice, gr2));
        no_aux = no_aux->prox_no;
    }
    
    if(maior_grau != maior_grau2)
        return FALSE;

    for(j=0; j<maior_grau;j++){
        printf("%i - ", valores2[j]);
    }
    printf("\nUFA!\n");

    printf("start2: %d | rotulo: %s\n", maior_grau_index, gr2->raiz[maior_grau_index].rotulo );

    bubbleSort(valores2, maior_grau);

    for(j=0; j<maior_grau; j++){
        if(valores1[j] != valores2[j])
            return FALSE;
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

int em_ordem(Grafo *gr, Vertice *vertice_chegada, int start){

    tp_fila fila;
    inicializa_fila(&fila);
    insere_fila(&fila, start);

    int array_vizinhos[gr->num_vertices];
    memset(array_vizinhos, 0, sizeof(array_vizinhos));

    int distancia[gr->num_vertices];
    memset(distancia, 0, sizeof(distancia));

    int count = 0;

    array_vizinhos[start] = 1;

    array_vizinhos[mapeando_vertices(vertice_chegada, gr)] = 1;

    while(!fila_vazia(&fila)){
        int start1;
        remove_fila(&fila, &start1);
        No *no_aux1;
        no_aux1 = gr->raiz[start1].lista_adjacentes;

        printf("--> s1: %d\n", start1);
        
        int p;
        for(p=0; p<gr->raiz[start1].num_aresta; p++){
            no_aux1 = no_aux1->prox_no;
            int v = mapeando_vertices(no_aux1->vertice, gr);
            printf("i: %i | start1: %d | P: %d\n", v, start1, p);

            if((array_vizinhos[v]) && (count != 0) && (no_aux1->vertice == vertice_chegada)){
                return distancia[start1];
            }
            if((!array_vizinhos[v])){
                distancia[v] = 1 + distancia[start1];
                insere_fila(&fila, v);
                array_vizinhos[v] = 1;
            }
        }

        count++;
    }
    return FALSE;
}

#endif