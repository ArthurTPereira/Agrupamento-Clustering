#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "euclidian_distance.h"
#include "vetor.h"

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
    FILE* arquivoEntrada = fopen(nomeArquivoEntrada, "r");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        return ERROR;
    }

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

    // Fecha o arquivo de entrada
    fclose(arquivoEntrada);
    
    long double matrizDistancias[nPontos-1][nPontos-1];
    for (int i = 0; i < nPontos-1; i++)
    {
        for (int j = 0; j < nPontos-1; j++)
        {
            matrizDistancias[i][j] = 0;
        }
    }
    
    long double vet1[m];
    long double vet2[m];
    
    char* pt;
    int cont = 0;
    char temp[1000];
    for (int i = 0; i < nPontos-1; i++) {
        strcpy(temp, pontos[i]);
        pt = strtok(temp,",");
        pt = strtok(NULL,","); // pula o primeiro token
        while (pt) {
            vet1[cont] = strtold(pt, NULL);
            cont++;
            pt = strtok(NULL,",");
        }
        cont = 0;
        for (int j = i+1; j < nPontos-1; j++) {
            strcpy(temp, pontos[j]);
            pt = strtok(temp,",");
            pt = strtok(NULL,",");
            while (pt) {
                vet2[cont] = strtold(pt, NULL);
                cont++;
                pt = strtok(NULL,",");
            }
            cont = 0;
            matrizDistancias[i][j] = euclidian_distance(vet1, vet2, m);
        }
    }

    // Libera o vetor de pontos
    liberaVetorPontos(pontos, nPontos);


    return SUCCESS;
}