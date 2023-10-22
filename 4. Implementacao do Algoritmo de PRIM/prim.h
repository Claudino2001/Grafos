#include "grafo.h"
const int max = 1e5;

void prim(Grafo *gr){
    int visitados[gr->num_vertices];
    memset(visitados, 0, sizeof(visitados));
    visitados[0] = 1;
    Vertice *vertice = &gr->raiz[0];
    No *no = vertice->lista_adjacentes;
    int i, j, n = gr->num_vertices;
    for(i=0; i<n-1; i++){
        No *s;
        int p_min = max, k = 0;
        for(j=0; j<n; j++){
            if (visitados[j]) {
                No *no = gr->raiz[j].lista_adjacentes;
                while(no->prox_no != NULL){
                    if(no->peso < p_min && !visitados[mapeando_vertices(no->prox_no->vertice, gr)]){
                        p_min = no->peso;
                        s = no;
                        k = j;
                    }
                    no = no->prox_no;
                }
            }
        }
        visitados[mapeando_vertices(s->prox_no->vertice, gr)] = 1;
        printf("%s->%s\n",gr->raiz[k].rotulo ,s->prox_no->vertice->rotulo);
    }
}