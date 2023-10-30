#ifndef DIJKSTRA
#define DIJKSTRA

void dijkstra(Grafo *gr, Vertice *v_partida, Vertice *v_chegada){
    int i, j;
    int n = gr->num_vertices;
    
    int distancia[n];   // Criando um vetor para armazenar as distancia entre os vertices
    int caminho[n];     // Criando um vetor para armazenar o caminho para os vertices
    int visitado[n];    // Criando um vetor para marcar os vertices que ja foram visitados

    memset(distancia, 0x3f, sizeof(distancia));     // Povoando o vertice com uma distancia infinita. 
    memset(caminho, -1, sizeof(caminho));           // Preenche os caminhos com -1 pq eu ainda n sei os valores
    memset(visitado, 0, sizeof(visitado));          // Marcando todos como não visitados

    distancia[mapeando_vertices(v_partida, gr)] = 0;    // O vertice de partida tem distancia ZERO

    for(i=0; i<n; i++){
        int vertice = -1;   // Para saber se ainda esxite vertices disponiveis para explorar
        for(j=0; j<n; j++){
            if(!visitado[j] && (vertice == -1 || distancia[j] < distancia[vertice])){   // Encontra o vertice cujo a distancia a partir do primeiro é a mais curta dos vertices ajds disponiveis.
                vertice = j;
            }
        }

        if(distancia[vertice] == 0x3f){     // Se o valor da distancia do até o vertice escolhido for infinito, quer dizer que não há caminho.
            printf("Não existe um caminho possível.\n");
            break;
        }
        visitado[vertice] = 1;      // Marca o cara como visitado.
        No *no = gr->raiz[vertice].lista_adjacentes;
        
        while (no->prox_no != NULL) {
            No *no_aux = no->prox_no;
            if(distancia[vertice] + no->peso < distancia[mapeando_vertices(no_aux->vertice, gr)]){  // Se a distancia do vertice escolhido + o peso da aresta para o proximo vertice adjc a ele for menor que a distancia desse proximo vertice. Executa o if.
                distancia[mapeando_vertices(no_aux->vertice, gr)] = distancia[vertice] + no->peso;  // Grava o valor do distancia do proximo vertice.
                caminho[mapeando_vertices(no_aux->vertice, gr)] = vertice;                          // Grava o caminho.
            }
            no = no->prox_no;
        }
        
    }

    // Imprime o caminhio minimo
    int x = mapeando_vertices(v_chegada, gr);
    while (caminho[x] != -1) {
        printf("%s <- ", gr->raiz[x].rotulo);
        x = caminho[x];
    }
    printf("%s", v_partida->rotulo);
    printf("\n");
}

#endif