#include "grafo.h"
#include "flooding.h"

int main(void) {

    FILE *arq;

    arq = fopen("texto.txt", "rt");
    
    Grafo grafo;

    inicializaGrafo(&arq, &grafo);
    //imprime_grafo(&grafo);

    printf("Resultado: %d\n", conta_conexo(&grafo));
    
    return 0;
}