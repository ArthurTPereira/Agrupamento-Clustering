#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "euclidian_distance.h"

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

    // Definindo um vetor com os IDs dos pontos
    char** pontos = (char**) malloc(sizeof(char*));
    int v_max = 1; // tamanho maximo do vetor de pontos
    int nPontos = 0; // Numero de pontos atual

    long double vet1[m]; // usar esse aqui aninhado com o de baixo
    long double vet2[m];
    
    int i = 0;
    int j = 0;
    char* temp;

    // Volta o arquivo de entrada para o começo
    rewind(arquivoEntrada);

    // Le o arquivo de entrada
    while (getline(&buffer, &bufferSize, arquivoEntrada) != -1)  {
        i = 0;
        // Verifica se o vetor de pontos está sem espaco para armazenar mais um ponto
        if (nPontos >= v_max) {

            // Duplica o tamanho do vetor de pontos e realoca
            v_max *= 2;
            pontos = (char**) realloc(pontos, v_max* sizeof(char*));
        }

        // Inicia a leitura da linha
        pt = strtok(buffer,",");

        // Aloca memória para a ID do ponto, faz a copia e armazena no vetor de pontos
        temp = (char*) malloc(strlen(pt)+1);
        strcpy(temp,pt);
        pontos[nPontos] = temp;
        nPontos++;
        pt = strtok(NULL,",");

        // Coleta as coordenadas do ponto atual e armazena em um vetor
        while (pt && i < m) {
            vet1[i] = strtod(pt, NULL);
            i++;
            pt = strtok(NULL,",");
        }


        // !TODO: Implementar a leitura para as outras linhas do arquivo
        // Para cada linha do arquivo, calcula a distancia euclidiana entre os pontos
        // Criar a matriz antes disso
    }

    // Imprime o vetor do ponto lido no primeiro while
    for (int j = 0; j < m; j++)
    {
        printf("Vet1: %.14Lf\n", vet1[j]); // aqui ele imprime o ultimo ponto da lista, oq ta certo por enquanto
    }

    // Imprime o vetor com as IDs dos pontos
    for (int i = 0; i < nPontos; i++)
    {
        printf("%s\n", pontos[i]); // ta imprimindo certinho
    }
    
    // Libera a memoria alocada para os pontos no vetor de pontos
    for (int i = 0; i < nPontos; i++)
    {
        free(pontos[i]);
    }

    // Libera o vetor de pontos
    free(pontos);
    


    // Libera a memoria alocada para o buffer
    free(buffer);

    // Fecha o arquivo de entrada
    fclose(arquivoEntrada);

    return SUCCESS;
}