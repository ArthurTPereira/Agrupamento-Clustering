#include <stdio.h>
#include <stdlib.h>

#include "kruskal.h"
#include "vetor.h"

// Algoritmo de Kruskal para gerar a arvore geradora minima
// Entrada: arestas - vetor de arestas ja ordenado em ordem crescente de distancia
//          tamanhoVetor - tamanho do vetor de arestas
//          k - numero de grupos
//          nPontos - numero de pontos
// Saida:   vetor de inteiros com a arvore geradora minima
int* kruskalAlgorithm(Ponto** arestas, int tamanhoVetor, int k, int nPontos) {

    // vetor que representa a arvore geradora minima
    int* vetor = (int*) malloc(nPontos * sizeof(int));

    // vetor que armazena o tamanho de cada grupo, para o weighted quick union
    int* vetorSize = (int*) malloc(nPontos * sizeof(int));
    
    for (int i = 0; i < nPontos; i++) { // make set
        vetor[i] = i;
        vetorSize[i] = 1;
    }

    int a = 0;
    int b = 0;
    int count = 0;

    // inicio do algoritmo de Kruskal
    for (int i = 0; i < tamanhoVetor; i++) {

        // se o numero de arestas for igual ao numero de grupos - 1, para o algoritmo
        if (count == nPontos - 1 - (k - 1)) {
            break;
        }

        // find de cada vertice da aresta
        a = find(vetor, getOrigem(arestas[i]));
        b = find(vetor, getDestino(arestas[i]));

        // se forem de grupos diferentes, faz o weighted quick union
        if (a != b) {
            w_QuickUnion(vetor, vetorSize, a, b);
            count++;
        }
    }
    
    // libera o vetor de tamanho de cada grupo, pois nao sera mais utilizado
    free(vetorSize);

    // retorna o vetor com a mst
    return vetor;
}

// find
// Entrada: vetor - vetor que representa a arvore geradora minima
//          i - posicao
// Saida:   posicao raiz
int find(int* vetor, int i) {
    while (i != vetor[i]) {
        vetor[i] = vetor[vetor[i]]; // path compression
        i = vetor[i];
    }
    return i;
}

// weighted quick union
// Entrada: vetor - vetor que representa a arvore geradora minima
//          vetorSize - vetor que armazena o tamanho de cada grupo
//          a - vertice a
//          b - vertice b
// Saida:   void
void w_QuickUnion(int* vetor, int* vetorSize, int a, int b) {
    int idA = find(vetor, a);
    int idB = find(vetor, b);

    if (idA == idB) {
        return;
    }
    if (vetorSize[idA] < vetorSize[idB]) {
        vetor[idA] = idB;
        vetorSize[idB] += vetorSize[idA];
    } else {
        vetor[idB] = idA;
        vetorSize[idA] += vetorSize[idB];
    }
}

// libera o vetor da mst
// Entrada: vetor - vetor da mst
// Saida:   void
void liberaVetorArvore(int* vetor) {
    free(vetor);
}
