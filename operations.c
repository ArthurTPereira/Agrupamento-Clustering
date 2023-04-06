#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "operations.h"

#define ERROR -1

// Calcula a dimensao M dos pontos
// Entrada: buffer - string que contem a primeira linha do arquivo de entrada
// Saida: m - dimensao M dos pontos
int calculaM(char* buffer) {

    char* pt = strtok(buffer,",");
    int m = -1;
    while (pt) {
        m++;
        pt = strtok(NULL,",");
    }

    return m;
}

// Abre o arquivo de entrada
// Entrada: nomeArquivoEntrada - nome do arquivo de entrada
// Saida: arquivoEntrada - ponteiro para o arquivo de entrada
FILE* abreArquivoEntrada(char* nomeArquivoEntrada) {
    FILE* arquivoEntrada = fopen(nomeArquivoEntrada, "r");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        exit(ERROR);
    }
    return arquivoEntrada;
}

// Libera a memoria alocada para o vetor de pontos
// Entrada: pontos - vetor de pontos
//          nPontos - numero de pontos
// Saida: void
void liberaVetorPontos(char** pontos, int nPontos) {
    for (int i = 0; i < nPontos; i++) {
        free(pontos[i]);
    }
    free(pontos);
}

char** preencheVetorLinhas(char* buffer, size_t* bufferSize, FILE* arquivoEntrada, int* nPontos, int* v_max) {
    char** pontos = (char**) malloc(sizeof(char*));
    char* temp;
    while (getline(&buffer, &(*bufferSize), arquivoEntrada) != -1)  {
        if ((*nPontos) >= (*v_max)) {
            // Duplica o tamanho do vetor de pontos e realoca
            (*v_max) *= 2;
            pontos = (char**) realloc(pontos, (*v_max)* sizeof(char*));
        }
        // Aloca memória para a ID do ponto, faz a copia e armazena no vetor de pontos
        temp = (char*) malloc(strlen(buffer)+1);
        strcpy(temp,buffer);
        pontos[(*nPontos)] = temp;
        (*nPontos)++;
    }
    free(buffer);
    return pontos;
}