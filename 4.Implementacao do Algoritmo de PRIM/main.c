#include "grafo.h"
#include "prim.h"

int main(void) {

    FILE *arq;

    arq = fopen("input.txt", "rt");
    
    Grafo grafo;

    inicializaGrafo(&arq, &grafo);
    //imprime_grafo(&grafo);

    prim(&grafo);

    return 0;
}