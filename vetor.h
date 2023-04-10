#ifndef VETOR_H
#define VETOR_H

typedef struct distancias Ponto;

int calculaM(char* buffer);

void liberaVetorPontos(char** pontos, int nPontos);

char** preencheVetorLinhas(char* buffer, size_t* bufferSize, FILE* arquivoEntrada, int* nPontos, int* v_max);

Ponto** alocaVetorDistancia(int n);

void liberaVetorDistancia(Ponto** vetorDistancias, int n);

int comparaDistancia(const void* a, const void* b);

void atribuiDistancia(Ponto** vetorDistancias, int posicao, int origem, int coluna, double distancia);

char** alocaVetorNomes(int n);

void liberaVetorNomes(char** nomes, int n);

double getDistancia(Ponto* ponto);

int getOrigem(Ponto* ponto);

int getDestino(Ponto* ponto);

#endif