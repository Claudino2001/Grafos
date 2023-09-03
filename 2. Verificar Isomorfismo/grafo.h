#ifndef GRAPH_FUNC
#define GRAPH_FUNC

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "grafo_struct.h"

// Função para inicializar o Grafo
void inicializaGrafo(FILE **arq, Grafo *grafo);

// Alocar dinamicamente um No
No * aloca_no();

// Retorna o estado do Grafo (vazio ou não)
int grafo_vazio(Grafo *gr);

// Contando o numero de vertices
int contando_num_vertices(FILE **arq, Grafo *gr);

// Aloca todos os vertices do Grafo com base no retoro de "contando_num_vertices();"
void aloca_vertices_grafo(FILE **arq, Grafo *gr);

// Insere os Nós nos vértices 
void insere_vertice(Grafo *gr, char *linha, Vertice *vertice);

// Povoando a lista de adjacentes
void povoando_lista_adjacentes(FILE *arq, Grafo *gr, Vertice *vertices);

// Imprime o Grafo
void imprime_grafo(Grafo *gr);

int grafo_vazio(Grafo *gr){
	if(gr->raiz == NULL) return 1;
	return 0;
}

No * aloca_no(){
	No *novo_no;
	novo_no = (No*) malloc(sizeof(No));
	return novo_no;
}

void inicializaGrafo(FILE **arq, Grafo *grafo){
    (*grafo).num_vertices = 0;
    (*grafo).num_aresta = 0;
    (*grafo).raiz = NULL;

    if(!arq){
        printf("Houve um problema na leitura do arquivo.\n");
        exit(0);
    }

    // Lendo o cabeçalho
    // Contando o numero de vértices
    contando_num_vertices(arq, grafo);
    
    // Criando todos os Vertices presentes no Grafo
    // Somente aloca memória e insere os rotulos
    aloca_vertices_grafo(arq, grafo);
}

int contando_num_vertices(FILE **arq, Grafo *gr){
    rewind(*arq);
    int i, num_space = 0;
    
    char linha[100];
    char *result;
    result = fgets(linha, 100, *arq);
    
    if(!result){
        printf("Erro na leitura do cabeçalho.\n");
        return 0;
    }

    int tam_linha = strlen(linha);

    for(i=0; i < (tam_linha); i++){
        if(isspace(linha[i])){
            num_space ++;
        }
    }

    gr->num_vertices = num_space;
    //printf("Numero de vertices: %d\n", gr->num_vertices);

    return (gr->num_vertices);
}

void aloca_vertices_grafo(FILE **arq, Grafo *gr){
    
    gr->raiz = (Vertice *) malloc(sizeof(Vertice) * gr->num_vertices); // Criando um vetor do tipo vertice. Onde cada posição representa um vertice com sua estrutura.
    
    // GRAFO APONTA PARA O PRIMEIRO VERTICE
    // DEPOIS MELHORAR ESSA LÓGICA
    gr->raiz = &gr->raiz[0];
    rewind(*arq);
    char linha[100];
    char *result;
    result = fgets(linha, 100, *arq);
    int i;

    int flag = 0; // Marcando a primeira leitura.
    char *t;
    for(i=0; i < (gr->num_vertices) - 1; i++){
        gr->raiz[i].num_graus = 0; // Todos os vertices iniciam com grau zero
        gr->raiz[i].num_aresta = 0;
        if(flag == 0){
            t = strtok(linha, " ");
            strcpy(gr->raiz[i].rotulo, t); // Inserindo em cada vertice o seu nome
            flag++;
        } else{
            t = strtok(NULL, " ");
            strcpy(gr->raiz[i].rotulo, t); 
        }        
    }

    t = strtok(NULL, "\n"); // Tratando a leitura do "\n"
    strcpy(gr->raiz[i].rotulo, t);
    
    gr->raiz[i].num_graus = 0; // Todos os vertices iniciam com grau zero
    gr->raiz[i].num_aresta = 0;

    // Printando todos os vertice e seus rotulos.
            // for(i=0; i< gr->num_vertices; i++){
            //     printf("(%s)", gr->raiz[i].rotulo);
            // }
            // printf("\n");

    // Lendo a matriz e povoando a matriz de adjcs
    povoando_lista_adjacentes(*arq, gr, gr->raiz);
}

void povoando_lista_adjacentes(FILE *arq, Grafo *gr, Vertice *vertices){
    char linha[100];
    char *result;
    int i = 0;
    while (!feof(arq)) { // Lê uma linha (inclusive com o '\n')
        result = fgets(linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
        if (result){ // Se foi possível ler
            // printf("Linha %d : %s", i, linha);
            insere_vertice(gr, linha, &vertices[i++]); // Insere no vertice a sua adjc
        }
    }
    // printf("\n");
    gr->num_aresta /=2;
}

void insere_vertice(Grafo *gr, char *linha, Vertice *vertice){
    char *t;
    int flag = 0, i;
    vertice->lista_adjacentes = aloca_no();
    No *no = (*vertice).lista_adjacentes;

    no->vertice = vertice;

    for(i=0; i < (gr->num_vertices) - 1; i++){
        if(flag == 0){
            t = strtok(linha, " ");
            if(strcmp(t, "1") == 0){
                No *novo_no = aloca_no();
                novo_no->vertice = &gr->raiz[i];
                no->prox_no = novo_no;
                no = novo_no;
                vertice->num_aresta++;

                if(vertice != &gr->raiz[i]){
                    gr->raiz[i].num_graus++;
                    gr->num_aresta++;
                } else{
                    gr->raiz[i].num_graus += 2;
                    gr->num_aresta += 2;
                }
            }
            flag++;
        } else{
            t = strtok(NULL, " ");
            if(strcmp(t, "1") == 0){
                No *novo_no = aloca_no();
                novo_no->vertice = &gr->raiz[i];
                no->prox_no = novo_no;
                no = novo_no;

                vertice->num_aresta++;

                if(vertice != &gr->raiz[i]){
                    gr->raiz[i].num_graus++;
                    gr->num_aresta++;
                } else{
                    gr->raiz[i].num_graus += 2;
                    gr->num_aresta += 2;
                }
            }
        }        
    }

    t = strtok(NULL, "\n");
    if(strcmp(t, "1") == 0){
        No *novo_no = aloca_no();
        novo_no->vertice = &gr->raiz[i];
        no->prox_no = novo_no;
        no = novo_no;
        
        vertice->num_aresta++;

        if(vertice != &gr->raiz[i]){
            gr->raiz[i].num_graus++;
            gr->num_aresta++;
        } else{
            gr->raiz[i].num_graus += 2;
            gr->num_aresta += 2;
        }
    }

}

void imprime_grafo(Grafo *gr){
    // Vendo o resultado
    int i = 0;
    printf("Numero total de arestas: %d\n", gr->num_aresta);
    for(i=0; i<gr->num_vertices; i++){
        Vertice *vertice_aux = &gr->raiz[i];
        No *no = vertice_aux->lista_adjacentes;
        printf("Vertice: %s\n", vertice_aux->rotulo);
        while (no->prox_no != NULL) {
            printf("%s -> %s | Num Grau: %d | Num Arestas: %d\n", gr->raiz[i].rotulo, no->prox_no->vertice->rotulo, gr->raiz[i].num_graus, gr->raiz[i].num_aresta);
            no = no->prox_no;
        }
        printf("\n");
    }
}

#endif