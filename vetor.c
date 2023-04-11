#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vetor.h"

#define ERROR -1

// Estrutura com o tamanho da aresta, o ponto de origem e o ponto de destino
struct distancias {
    double distancia;
    int origem;
    int destino;
};

// Libera a memoria alocada para o vetor de pontos
// Entrada: pontos - vetor de pontos
//          nPontos - numero de pontos
// Saida: void
void liberaVetorPontos(char** pontos, int nPontos) {

    // libera cada ponto
    for (int i = 0; i < nPontos; i++) {
        free(pontos[i]);
    }

    // libera o vetor
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
    
    // declara o vetor de pontos
    char** pontos = (char**) malloc(sizeof(char*));
    char* temp;

    // le o arquivo linha por linha
    while (getline(&buffer, &(*bufferSize), arquivoEntrada) != -1)  {
        // Verifica se o vetor de pontos esta cheio
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

    // separa a linha por virgulas
    char* pt = strtok(buffer,",");
    int m = -1; // m = -1 para ignorar a primeira coluna (ID)

    // enquanto houver virgulas, incrementa o M
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
    Ponto** x = (Ponto**) a;
    Ponto** y = (Ponto**) b;
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
Ponto** alocaVetorDistancia(int n) {
    // aloca o vetor
    Ponto** vetorDistancias = (Ponto**) malloc(n * sizeof(Ponto*));
    if (vetorDistancias == NULL) {
        printf("Erro ao alocar memoria para o vetor de distancias 01\n");
        exit(ERROR);
    }
    // aloca cada distancia do vetor
    for (int i = 0; i < n; i++) {
        vetorDistancias[i] = (Ponto*) malloc(sizeof(Ponto));
        if (vetorDistancias[i] == NULL) {
            printf("Erro ao alocar memoria para o vetor de distancias\n");
            exit(ERROR);
        }
    }
    return vetorDistancias;
}

// Libera a memoria alocada para o vetor de distancias
// Entrada: vetorDistancias - vetor de distancias
//          n - numero de pontos
// Saida: void
void liberaVetorDistancia(Ponto** vetorDistancias, int n) {
    // libera cada distancia
    for (int i = 0; i < n; i++) {
        free(vetorDistancias[i]);
    }
    // libera o vetor
    free(vetorDistancias);
}

// Atribui os valores da distancia, origem e coluna para o vetor de distancias
// Entrada: vetorDistancias - vetor de distancias
//          posicao - posicao do vetor de distancias
//          origem - valor da origem
//          coluna - valor da coluna
//          distancia - valor da distancia entre os pontos da origem e coluna
// Saida: void
void atribuiDistancia(Ponto** vetorDistancias, int posicao, int origem, int coluna, double distancia) {
    vetorDistancias[posicao]->distancia = distancia;
    vetorDistancias[posicao]->origem = origem;
    vetorDistancias[posicao]->destino = coluna;
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

// Libera a memoria alocada para o vetor de nomes
// Entrada: nomes - vetor de nomes
//          n - qtd de nomes
// Saida: void
void liberaVetorNomes(char** nomes, int n) {
    // libera cada nome
    for (int i = 0; i < n; i++) {
        free(nomes[i]);
    }
    // libera o vetor 
    free(nomes);
}

// retorna a distancia entre dois pontos
// Entrada: ponto que contem a origem, destino e distancia
// Saida:   distancia entre os pontos
double getDistancia(Ponto* ponto) {
    return ponto->distancia;
}

// retorna a origem do ponto
// Entrada: ponto que contem a origem, destino e distancia
// Saida:   origem do ponto
int getOrigem(Ponto* ponto) {
    return ponto->origem;
}

// retorna o destino do ponto
// Entrada: ponto que contem a origem, destino e distancia
// Saida:   destino do ponto
int getDestino(Ponto* ponto) {
    return ponto->destino;
}