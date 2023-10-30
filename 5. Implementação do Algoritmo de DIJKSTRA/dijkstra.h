#ifndef DIJKSTRA
#define DIJKSTRA

int mpv(Vertice *vertice, Grafo *gr);

void dijstra(Grafo *gr, Vertice *v_partida, Vertice *v_chegada){
    int i, j;
    int n = gr->num_vertices;
    
    int distancia[n];
    int caminho[n];
    int visitado[n];

    memset(distancia, 0x3f, sizeof(distancia));
    memset(caminho, -1, sizeof(caminho));
    memset(visitado, 0, sizeof(visitado));

    distancia[mpv(v_partida, gr)] = 0;

    for(i=0; i<n; i++){
        int vertice = -1;
        for(j=0; j<n; j++){
            if(!visitado[j] && (vertice == -1 || distancia[j] < distancia[vertice])){
                vertice = j;
            }
        }

        if(distancia[vertice] == 0x3f){
            printf("Não existe um caminho possível.\n");
            break;
        }
        visitado[vertice] = 1;
        No *no = gr->raiz[vertice].lista_adjacentes;
        
        while (no->prox_no != NULL) {
            No *no_aux = no->prox_no;
            if(distancia[vertice] + no->peso < distancia[mpv(no_aux->vertice, gr)]){
                distancia[mpv(no_aux->vertice, gr)] = distancia[vertice] + no->peso;
                caminho[mpv(no_aux->vertice, gr)] = vertice;
            }
            no = no->prox_no;
        }
        
    }

    int x = mpv(v_chegada, gr);
    while (caminho[x] != -1) {
        printf("%s <- ", gr->raiz[x].rotulo);
        x = caminho[x];
    }
    printf("%s", v_partida->rotulo);
    printf("\n");
}

int mpv(Vertice *vertice, Grafo *gr){ //mapeando vertices
    int i;
    for(i=0; i<gr->num_vertices; i++){
        if(vertice == &gr->raiz[i]){
            return i;
        }
    }
    return -1;
}

#endif