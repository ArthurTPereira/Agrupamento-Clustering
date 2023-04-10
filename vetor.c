#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vetor.h"

#define ERROR -1

struct distancias {
    double distancia;
    int linha;
    int coluna;
};

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
            if (pontos == NULL) {
                printf("Erro ao realocar memoria para o vetor de pontos!\n");
                return NULL;
            }
        }
        // Aloca memória para a ID do ponto, faz a copia e armazena no vetor de pontos
        temp = (char*) malloc(strlen(buffer)+1);
        if (temp == NULL) {
            printf("Erro ao alocar memoria para o vetor de pontos!\n");
            return NULL;
        }
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

// funcao de comparacao para o qsort
// Entrada: a - ponteiro para o primeiro elemento a ser comparado
//          b - ponteiro para o segundo elemento a ser comparado
// Saida:   1 se a > b
//          -1 se a < b
//          0 se a = b
int comparaDistancia(const void* a, const void* b) {
    VetorDistancia** x = (VetorDistancia**) a;
    VetorDistancia** y = (VetorDistancia**) b;
    if ((*x)->distancia > (*y)->distancia) {
        return 1;
    } else if ((*x)->distancia < (*y)->distancia) {
        return -1;
    } else {
        return 0;
    }
}

// Aloca o vetor de distancias
// Entrada: n - numero de pontos
// Saida:   vetor de distancias
VetorDistancia** alocaVetorDistancia(int n) {
    VetorDistancia** vetorDistancias = (VetorDistancia**) malloc(n * sizeof(VetorDistancia*));
    if (vetorDistancias == NULL) {
        printf("Erro ao alocar memoria para o vetor de distancias");
        exit(ERROR);
    }
    for (int i = 0; i < n; i++) {
        vetorDistancias[i] = (VetorDistancia*) malloc(n * sizeof(VetorDistancia));
        if (vetorDistancias[i] == NULL) {
            printf("Erro ao alocar memoria para o vetor de distancias");
            exit(ERROR);
        }
    }
    return vetorDistancias;
}

// Libera a memoria alocada para o vetor de distancias
// Entrada: vetorDistancias - vetor de distancias
//          n - numero de pontos
// Saida: void
void liberaVetorDistancia(VetorDistancia** vetorDistancias, int n) {
    for (int i = 0; i < n; i++) {
        free(vetorDistancias[i]);
    }
    free(vetorDistancias);
}

// Atribui os valores da distancia, linha e coluna para o vetor de distancias
// Entrada: vetorDistancias - vetor de distancias
//          posicao - posicao do vetor de distancias
//          linha - valor da linha
//          coluna - valor da coluna
//          distancia - valor da distancia entre os pontos da linha e coluna
// Saida: void
void atribuiDistancia(VetorDistancia** vetorDistancias, int posicao, int linha, int coluna, double distancia) {
    vetorDistancias[posicao]->distancia = distancia;
    vetorDistancias[posicao]->linha = linha;
    vetorDistancias[posicao]->coluna = coluna;
}

// Aloca o vetor de nomes
// Entrada: n - numero de pontos
// Saida:   vetor de nomes
char** alocaVetorNomes(int n) {
    char** nomes = (char**) malloc(n * sizeof(char*));
    if (nomes == NULL) {
        printf("Erro ao alocar memoria para o vetor de nomes");
        exit(ERROR);
    }
    return nomes;
}

void liberaVetorNomes(char** nomes, int n) {
    for (int i = 0; i < n; i++) {
        free(nomes[i]);
    }
    free(nomes);
}