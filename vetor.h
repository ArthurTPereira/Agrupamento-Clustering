#ifndef VETOR_H
#define VETOR_H

typedef struct distancias VetorDistancia;

int calculaM(char* buffer);

void liberaVetorPontos(char** pontos, int nPontos);

char** preencheVetorLinhas(char* buffer, size_t* bufferSize, FILE* arquivoEntrada, int* nPontos, int* v_max);

VetorDistancia** alocaVetorDistancia(int n);

void liberaVetorDistancia(VetorDistancia** vetorDistancias, int n);

int comparaDistancia(const void* a, const void* b);

void atribuiDistancia(VetorDistancia** vetorDistancias, int posicao, int linha, int coluna, double distancia);

char** alocaVetorNomes(int n);

void liberaVetorNomes(char** nomes, int n);
#endif