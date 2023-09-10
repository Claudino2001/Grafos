#include "grafo.h"
#include "isomorfismo.h"

int main(void){

    printf("Executado!\n\n");

    FILE *arq1, *arq2;

    arq1 = fopen("matriz_um.txt", "rt");
    arq2 = fopen("matriz_dois.txt", "rt");

    Grafo gr1, gr2;

    inicializaGrafo(&arq1, &gr1);
    imprime_grafo(&gr1);

    printf("---------------------------\n");

    inicializaGrafo(&arq2, &gr2);
    imprime_grafo(&gr2);

    fclose(arq1);
    fclose(arq2);

    printf("\n*** ISOMORFO: %d ***\n", isIsomorfo(&gr1, &gr2));

    if(isIsomorfo(&gr1, &gr2)){
        printf("Sao isomorfos!\n");
        print_func_isomorfismo(&gr1, &gr2);
    }
    else
        printf("Nao sao isomorfos!\n");

    printf("\nFinalizado!\n");

    return 0;
}