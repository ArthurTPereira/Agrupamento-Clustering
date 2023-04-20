#include <stdio.h>
#include <stdlib.h>

#include "euclidian_distance.h"
#include "vetor.h"
#include "kruskal.h"
#include "file.h"

// Codigos de retorno
#define SUCCESS 0
#define ERROR -1

int main(int argc, char* argv[]) {

    // Verifica se os argumentos sao validos
    verificaArgumentos(argc, argv);

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

    int v_max = 1; // tamanho maximo do vetor das linhas do arquivo de entrada (incrementado durante a leitura)
    int nPontos = 0; // Numero de pontos do arquivo de entrada (incrementado durante a leitura)

    // Coleta as linhas do arquivo de entrada e preenche em um vetor de strings
    char** pontos = preencheVetorLinhas(buffer, &bufferSize, arquivoEntrada, &nPontos, &v_max);

    // Fecha o arquivo de entrada
    fclose(arquivoEntrada);

    // Tamanho do vetor de distancias
    int tamanho = (nPontos)*(nPontos-1)/2;

    // vetor de distancia
    Ponto** distancias = alocaVetorDistancia(tamanho);
    
    // Vetor com os nomes dos pontos
    char** nomesPontos = alocaVetorNomes(nPontos);

    // preenche o vetor de distancias
    preencheVetorDistancias(nPontos,m,distancias,pontos,nomesPontos);

    // libera o vetor de pontos inicial que nao sera mais utilizado
    liberaVetorPontos(pontos, nPontos);
    
    // ordena o vetor de distancia
    qsort(distancias, tamanho, sizeof(Ponto*), comparaDistancia);

    // executa o algoritmo de kruskal e obtem a mst
    int* vetorArvore = kruskalAlgorithm(distancias,tamanho, k, nPontos);

    // libera o vetor de distancias que nao sera mais utilizado
    liberaVetorDistancia(distancias, tamanho);

    // Abre o arquivo de saida
    FILE* arquivoSaida = abreArquivoSaida(nomeArquivoSaida);

    // Escreve os grupos no arquivo de saida
    escreveGrupos(arquivoSaida, vetorArvore, nPontos, k, nomesPontos);

    // Libera os vetores alocados
    fclose(arquivoSaida);
    
    // Libera os vetores
    liberaVetorNomes(nomesPontos, nPontos);
    liberaVetorArvore(vetorArvore);

    return SUCCESS;
}