#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "euclidian_distance.h"
#include "operations.h"

#define SUCCESS 0
#define ERROR -1

int main(int argc, char* argv[]) {

    // Verifica se o numero de argumentos eh valido
    if (argc != 4) {
        printf("Numero de argumentos invalido!\n");
        return ERROR;
    } 

    // Declara as variaveis que armazenam os argumentos
    char* nomeArquivoEntrada = argv[1];
    char* nomeArquivoSaida = argv[3];
    int k = atoi(argv[2]);

    // Abre o arquivo de entrada
    FILE* arquivoEntrada = abreArquivoEntrada(nomeArquivoEntrada);

    // Declara o buffer que armazena as linhas do arquivo de entrada
    size_t bufferSize = 64;
    char * buffer = (char*) malloc(bufferSize * sizeof(char));

    // Verifica se o buffer foi alocado corretamente
    if (buffer == NULL) {
        printf("Erro ao alocar memoria para o buffer!\n");
        return ERROR;
    }

    // Le o arquivo de entrada e calcula a dimensao M dos pontos
    getline(&buffer, &bufferSize, arquivoEntrada);
    int m = calculaM(buffer);

    // Volta o arquivo de entrada para o começo
    rewind(arquivoEntrada);

    int v_max = 1; // tamanho maximo do vetor das linhas do arquivo de entrada
    int nPontos = 0; // Numero de pontos atual

    // Coleta as linhas do arquivo de entrada e preenche em um vetor de strings
    char** pontos = preencheVetorLinhas(buffer, &bufferSize, arquivoEntrada, &nPontos, &v_max);

    // Imprime o vetor com as IDs dos pontos
    for (int i = 0; i < nPontos; i++) {
        printf("%s\n", pontos[i]); // ta imprimindo certinho
    }
    
    // Libera o vetor de pontos
    liberaVetorPontos(pontos, nPontos);

    // Fecha o arquivo de entrada
    fclose(arquivoEntrada);

    return SUCCESS;
}