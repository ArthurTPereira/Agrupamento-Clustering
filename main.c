#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "euclidian_distance.h"
#include "vetor.h"
#include "kruskal.h"
#include "file.h"

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

    int v_max = 1; // tamanho maximo do vetor das linhas do arquivo de entrada
    int nPontos = 0; // Numero de pontos atual

    // Coleta as linhas do arquivo de entrada e preenche em um vetor de strings
    char** pontos = preencheVetorLinhas(buffer, &bufferSize, arquivoEntrada, &nPontos, &v_max);

    // Fecha o arquivo de entrada
    fclose(arquivoEntrada);

    // Tamanho do vetor de distancias
    int tamanho = (nPontos)*(nPontos-1)/2;

    // vetor de distancia
    Ponto** distancias = alocaVetorDistancia(tamanho);
    
    double vet1[m];
    double vet2[m];

    // Vetor com os nomes dos pontos
    char** nomesPontos = alocaVetorNomes(nPontos);

    int v = 0;
    char* pt;
    int cont = 0;
    char temp[1000];

    // preenche o vetor de distancias
    for (int i = 0; i < nPontos; i++) {
        // coleta o nome do ponto e insere no vetor de nomes
        strcpy(temp, pontos[i]);
        pt = strtok(temp,",");
        nomesPontos[i] = (char*) malloc((strlen(pt)+1) * sizeof(char));
        if (nomesPontos[i] == NULL) {
            printf("Erro ao alocar memoria para o nome!\n");
            return ERROR;
        }
        strcpy(nomesPontos[i], pt);
        pt = strtok(NULL,",");

        // coleta as coordenadas do ponto e insere em um vetor
        while (pt) {
            vet1[cont] = strtold(pt, NULL);
            cont++;
            pt = strtok(NULL,",");
        }
        cont = 0;

        // para cada ponto seguinte, calcula a distancia euclidiana e insere no vetor de distancias
        for (int j = i+1; j < nPontos; j++) {
            strcpy(temp, pontos[j]);
            pt = strtok(temp,",");
            pt = strtok(NULL,","); // ignora o nome do ponto

            // coleta as coordenadas do ponto e insere em outro vetor
            while (pt) {
                vet2[cont] = strtod(pt, NULL);
                cont++;
                pt = strtok(NULL,",");
            }
            cont = 0;

            // utiliza os vetores com as coordenadas para calcular a distancia euclidiana e insere no vetor de distancias
            atribuiDistancia(distancias,v,i,j,euclidian_distance(vet1, vet2, m));
            v++;
        }
    }

    // libera o vetor de pontos inicial que nao sera mais utilizado
    liberaVetorPontos(pontos, nPontos);

    // ordena o vetor de distancia
    qsort(distancias, tamanho, sizeof(Ponto*), comparaDistancia);

    // Abre o arquivo de saida
    FILE* arquivoSaida = abreArquivoSaida(nomeArquivoSaida);

    // executa o algoritmo de kruskal e obtem a mst
    int* vetorArvore = kruskalAlgorithm(distancias,tamanho, k, nPontos);

    // libera o vetor de distancias que nao sera mais utilizado
    liberaVetorDistancia(distancias, tamanho);

    printf("Iniciando escreveGrupos\n");
    // Escreve os grupos no arquivo de saida
    escreveGrupos(arquivoSaida, vetorArvore, nPontos, k, nomesPontos);
    printf("Finalizando escreveGrupos\n");

    // Libera os vetores alocados
    fclose(arquivoSaida);
    
    // Libera os vetores
    liberaVetorNomes(nomesPontos, nPontos);
    liberaVetorArvore(vetorArvore);

    return SUCCESS;
}