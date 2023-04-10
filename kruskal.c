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
void Union(int* vetor, int a, int b, int tamanho);

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
    int temp;
    for (int i = 0; i < tamanhoVetor; i++) {
        a = find(vetor, pontos[i]->origem);
        b = find(vetor, getDestino(pontos[i]));

        if (a != b) {
            Union(vetor, a, b, nPontos);
        }
    }

    for (int i = 0; i < mst->nPontos; i++) {
        printf("%d %d %lf\n", getOrigem(mst->pontos[i]), getDestino(mst->pontos[i]), getDistancia(mst->pontos[i]));
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
    if ( vetor[i] == i) {
        return i;
    }
    return find(vetor, vetor[i]);
}

void Union(int* vetor, int a, int b, int tamanho) {
    int idA = find(vetor, a);
    int idB = find(vetor, b);
    vetor[idA] = idB;
}
