#ifndef VETOR_H
#define VETOR_H

int calculaM(char* buffer);

void liberaVetorPontos(char** pontos, int nPontos);

char** preencheVetorLinhas(char* buffer, size_t* bufferSize, FILE* arquivoEntrada, int* nPontos, int* v_max);

#endif