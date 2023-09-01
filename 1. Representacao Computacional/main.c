#include "grafo.h"

int main(void){

    printf("Executado!\n");

    FILE *arq;

    arq = fopen("adjacencias.txt", "rt");

    // CRIANDO O MEU GRAFO
    Grafo gr;
    inicializaGrafo(&arq, &gr);
    
    imprime_grafo(&gr);

    return 0;
}

