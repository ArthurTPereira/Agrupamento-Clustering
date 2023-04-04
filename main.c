#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "euclidian_distance.h"
#include "ponto.h"

#define SUCCESS 0
#define ERROR -1

int main(int argc, char* argv[]) {

    // Verifica se o numero de argumentos eh valido
    if (argc != 4) {
        printf("Numero de argumentos invalido!\n");
        return ERROR;
    } 

    char* nomeArquivoEntrada = argv[1];
    char* nomeArquivoSaida = argv[3];
    int k = atoi(argv[2]);

    // Abre o arquivo de entrada
    FILE* arquivoEntrada = fopen(nomeArquivoEntrada, "r");
    
    // Verifica se o arquivo foi aberto corretamente
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        return ERROR;
    }

    size_t bufferSize = 64;
    char * buffer = (char*) malloc(bufferSize * sizeof(char));

    // Verifica se o buffer foi alocado corretamente
    if (buffer == NULL) {
        printf("Erro ao alocar memoria para o buffer!\n");
        return ERROR;
    }

    // Le o arquivo de entrada
    getline(&buffer, &bufferSize, arquivoEntrada);

    // Calcula a dimensao M dos pontos
    char* pt = strtok(buffer,",");
    int m = -1;
    while (pt) {
        m++;
        pt = strtok(NULL,",");
    }

    rewind(arquivoEntrada);
    while (getline(&buffer, &bufferSize, arquivoEntrada) != -1)  {

    }

    // Libera a memoria alocada para o buffer
    free(buffer);

    // Fecha o arquivo de entrada
    fclose(arquivoEntrada);

    return SUCCESS;
}