#include <stdio.h>
#include <stdlib.h>

#include "kruskal.h"
#include "vetor.h"

struct distancias {
    double distancia;
    int origem;
    int destino;
};

struct raiz {
    Ponto** pontos;
    int nPontos;
};

int find(int* vetor, int i);
void Union(int* vetor, int a, int b);

void kruskalAlgorithm(Ponto** pontos, int tamanhoVetor, int k, int nPontos) {

    Arvore* mst = (Arvore*) malloc(sizeof(Arvore));
    mst->pontos = (Ponto**) malloc(nPontos * sizeof(Ponto*));
    mst->nPontos = 0;

    int* vetor = (int*) malloc(nPontos * sizeof(int));
    for (int i = 0; i < nPontos; i++) { // make set
        vetor[i] = i;
    }

    int a = 0;
    int b = 0;
    int count = 0;
    for (int i = 0; i < tamanhoVetor; i++) {
        if (count == nPontos - 1 - (k -1)) {
            break;
        }

        a = find(vetor, getOrigem(pontos[i]));
        b = find(vetor, getDestino(pontos[i]));

        if (a != b) {
            mst->pontos[i] = pontos[i];
            Union(vetor, a, b);
            count++;
        }
    }

    for (int i = 0; i < nPontos; i++)
    {
        printf("%d ", vetor[i]);
    }
    
    free(vetor);
    free(mst->pontos);
    free(mst);

}

int find(int* vetor, int i) {
    while (i != vetor[i]) {
        i = vetor[i];
    }
    return i;
}

void Union(int* vetor, int a, int b) {
    int idA = find(vetor, a);
    int idB = find(vetor, b);
    
    vetor[idA] = idB;
}
