/*
Equipe:
    Arthur Sant'Anna
    Bernardo Resende
    Gabriel Claudino
*/

#include "grafo.h"
#include "flooding.h"
#include "prim.h"

int main(void) {

    FILE *arq;

    arq = fopen("input.txt", "rt");
    
    Grafo grafo;

    inicializaGrafo(&arq, &grafo);

    if(conta_conexo(&grafo) != 1){
        printf("Não existe um árvore geradora minima.\n");
        return 0;
    }else{
        prim(&grafo);
    }

    return 0;
}