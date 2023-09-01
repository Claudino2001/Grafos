#include "grafo.h"
#include "isomorfismo.h"

int main(void){

    printf("Executado!\n\n");

    FILE *arq1, *arq2;

    arq1 = fopen("matriz_um.txt", "rt");
    arq2 = fopen("matriz_dois.txt", "rt");

    Grafo gr1, gr2;

    inicializaGrafo(&arq1, &gr1);
    //imprime_grafo(&gr1);

    inicializaGrafo(&arq2, &gr2);
    //imprime_grafo(&gr2);

    fclose(arq1);
    fclose(arq2);

    printf("V: %d | A: %d\n", same_vertices(&gr1, &gr2), same_arestas(&gr1, &gr2));

    printf("\nFinalizado!\n");

    return 0;
}

