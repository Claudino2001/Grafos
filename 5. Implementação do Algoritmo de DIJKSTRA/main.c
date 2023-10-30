#include "grafo.h"
#include "flooding.h"
#include "dijkstra.h"

int main(void) {
    FILE *arq;

    arq = fopen("input.txt", "rt");

    Grafo grafo;

    inicializaGrafo(&arq, &grafo);

    if(conta_conexo(&grafo) != 1){
        printf("Não existe um árvore geradora minima.\n");
        return 0;
    }else{
        dijkstra(&grafo, &grafo.raiz[3], &grafo.raiz[0]);
    }

    return 0;
}