#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vetor.h"

#define ERROR -1

// Abre o arquivo de entrada
// Entrada: nomeArquivoEntrada - nome do arquivo de entrada
// Saida: arquivoEntrada - ponteiro para o arquivo de entrada


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

// Preenche o vetor de pontos com as linhas do arquivo de entrada
// Entrada: buffer - variavel do ponteiro da string
//          bufferSize - tamanho do buffer
//          arquivoEntrada - ponteiro para o arquivo de entrada
//          nPontos - numero de pontos
//          v_max - tamanho maximo do vetor de pontos
// Saida:   vetor de pontos
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