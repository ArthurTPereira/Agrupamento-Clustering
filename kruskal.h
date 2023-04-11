#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "vetor.h"

int* kruskalAlgorithm(Ponto** pontos, int tamanhoVetor, int k, int nPontos);

int find(int* vetor, int i);

void w_QuickUnion(int* vetor, int* vetorSize, int a, int b);

void liberaVetorArvore(int* vetor);

#endif