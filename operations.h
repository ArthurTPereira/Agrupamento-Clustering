#ifndef OPERATIONS_H
#define OPERATIONS_H


int calculaM(char* buffer);

FILE* abreArquivoEntrada(char* nomeArquivoEntrada);

void liberaVetorPontos(char** pontos, int nPontos);

char** preencheVetorLinhas(char* buffer, size_t* bufferSize, FILE* arquivoEntrada, int* nPontos, int* v_max);

#endif