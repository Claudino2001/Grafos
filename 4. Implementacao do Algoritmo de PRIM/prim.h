/*
Nos atribuimos -1 como um caminho não existente e 0 como um caminho de custo zero.
*/

#include "grafo.h"
const int max = 1e5; // Referencia de valor alto

void prim(Grafo *gr){
    int visitados[gr->num_vertices]; // Criando o vetor dos vertices ja incluidos nas arvore geradora minima. 
    memset(visitados, 0, sizeof(visitados)); // Colocando zero em tudo
    visitados[0] = 1; // Escolhendo o primeiro vertice da árvore geradora minima para iniciar
    int i, j, n = gr->num_vertices;
    for(i=0; i<n-1; i++){ // vasculanho cada aresta da árvore
        No *s; // O nó
        int p_min = max, k = 0; // K variavel auxiliar. guardo o index de vertice escolhido.
        for(j=0; j<n; j++){ // percorrendo todos os nós da arvore minima e e selecionar o vertice mais leve.
            if (visitados[j]) { // so inclui os vertices inclusos na arvore. arestas acessiveis.
                No *no = gr->raiz[j].lista_adjacentes; 
                while(no->prox_no != NULL){ // percorre as arestas do vertice ate achar o mais leve
                    if(no->peso < p_min && !visitados[mapeando_vertices(no->prox_no->vertice, gr)]){ // ve se o nó em analise é o mais leve e se o vertice ja foi incluso ou não.
                        p_min = no->peso; // grava o peso minimo 
                        s = no; // grava a aresta
                        k = j;  // grava o indice de vertice de partida
                    }
                    no = no->prox_no; //passa para o proximo nó
                }
            }
        }
        visitados[mapeando_vertices(s->prox_no->vertice, gr)] = 1; // marca a aresta (no) escolhido mais leve
        printf("%s->%s\n",gr->raiz[k].rotulo ,s->prox_no->vertice->rotulo); // Printando os caminhos da Árvore. 
    }
}