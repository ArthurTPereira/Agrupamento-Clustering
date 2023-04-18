#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "kruskal.h"

#define ERROR -1

// Estrutura de um dicionario para facilitar a escrita dos dados no arquivo de saida
typedef struct dicionario {
    char* nome;
    int freq;
} Dicionario;

// verifica os argumentos de entrada para os arquivos
// Entrada: argc - numero de argumentos
//          argv - vetor de argumentos
// Saida:   void
void verificaArgumentos(int argc, char** argv) {
    if (argc != 4) {
        printf("Numero de argumentos invalido!\n");
        exit(ERROR);
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i] == NULL) {
            printf("Erro ao ler argumento!\n");
            exit(ERROR);
        }
    }
}

// Abre o arquivo de entrada
// Entrada: nomeArquivoEntrada - nome do arquivo de entrada
// Saida:   ponteiro para o arquivo de entrada
FILE* abreArquivoEntrada(char* nomeArquivoEntrada) {
    FILE* arquivoEntrada = fopen(nomeArquivoEntrada, "r");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        return NULL;
    }
    return arquivoEntrada;
}

// Abre o arquivo de saida
// Entrada: nomeArquivoSaida - nome do arquivo de saida
// Saida:   ponteiro para o arquivo de saida
FILE* abreArquivoSaida(char* nomeArquivoSaida) {
    FILE* arquivoSaida = fopen(nomeArquivoSaida, "w");
    if (arquivoSaida == NULL) {
        printf("Erro ao abrir o arquivo de saida!\n");
        return NULL;
    }
    return arquivoSaida;
}

// funcao de comparacao de nomes para o qsort
// Entrada: a - struct Dicionario
//          b - struct Dicionario
// Saida:   -1 se a < b
//          0 se a = b
//          1 se a > b
int comparaNomes(const void* a, const void* b) {
    Dicionario* x = (Dicionario*) a;
    Dicionario* y = (Dicionario*) b;
    char nome1[50];
    char nome2[50];
    strcpy(nome1, x->nome);
    strcpy(nome2, y->nome);
    int resultado = strcmp(nome1, nome2);
    if (resultado < 0) {
        return -1;
    } else if (resultado > 0) {
        return 1;
    } else {
        return 0;
    }
}

// funcao de comparacao de grupos para o qsort
// Entrada: a - struct Dicionario
//          b - struct Dicionario
// Saida:   -1 se a < b
//          0 se a = b
//          1 se a > b
int comparaGrupos(const void* a, const void* b) {
    Dicionario* x = *(Dicionario**) a;
    Dicionario* y = *(Dicionario**) b;
    char nome1[50];
    char nome2[50];
    strcpy(nome1, x->nome);
    strcpy(nome2, y->nome);
    int resultado = strcmp(nome1, nome2);
    if (resultado < 0) {
        return -1;
    } else if (resultado > 0) {
        return 1;
    } else {
        return 0;
    }
}

// Escreve os grupos no arquivo de saida
// Entrada: arquivoSaida - ponteiro para o arquivo de saida
//          mst - arvore geradora minima com os grupos montados
//          tamanho - tamanho da arvore geradora minima
//          k - numero de grupos
//          nomes - vetor com os nomes dos grupos
void escreveGrupos(FILE* arquivoSaida, int* mst, int tamanho, int k, char** nomes) {
    // Vetor de grupos que armazena quais grupos distintos
    int* grupos = (int*) malloc(k * sizeof(int));
    if (grupos == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(ERROR);
    }

    // Vetor de frequencia que armazena quantos pontos estao em um grupo
    int* freq = (int*) calloc(k, sizeof(int));
    if (freq == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(ERROR);
    }

    int qtdDistintos = 0;

    int found = 0;
    for (int i = 0; i < tamanho; i++) {
        found = 0;
        for (int j = 0; j < qtdDistintos; j++) {
            if (find(mst, mst[i]) == grupos[j]) {
                found = 1;
                freq[j]++;
                break;
            }
        }
        if (!found) {
            grupos[qtdDistintos] = find(mst, mst[i]);
            freq[qtdDistintos] = 1;
            qtdDistintos++;
        }
    }

    // Matriz com um "dicionario" para relacionar o id do nome com o indice
    Dicionario** agrupamentos = (Dicionario**) malloc(k * sizeof(Dicionario*));
    if (agrupamentos == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(ERROR);
    }
    for (int i = 0; i < k; i++) {
        agrupamentos[i] = (Dicionario*) malloc(freq[i] * sizeof(Dicionario));
        if (agrupamentos[i] == NULL) {
            printf("Erro ao alocar memoria!\n");
            exit(ERROR);
        }
    }

    int count = 0;
    // preenche a matriz com os ids e o indice, varrendo cada grupo
    for (int i = 0; i < k; i++) {
        count = 0;
        // Varre a mst
        for (int j = 0; j < tamanho; j++) {
            if (find(mst,mst[j]) == grupos[i]) {
                agrupamentos[i][count].nome = nomes[j];
                agrupamentos[i][count].freq = freq[i];
                count++;
            }
        }
    }

    // Ordena cada grupo alfabeticamente
    for (int i = 0; i < k; i++) {
        qsort(agrupamentos[i], freq[i], sizeof(Dicionario), comparaNomes);
    }

    // Ordena o vetor dos grupos
    qsort(agrupamentos, k, sizeof(Dicionario*),comparaGrupos);

    int teste = 0;
    // Escreve os grupos no arquivo de saida
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < agrupamentos[i][0].freq; j++) {
            fprintf(arquivoSaida, "%s", agrupamentos[i][j].nome);
                
            if (j != agrupamentos[i][0].freq - 1) { // atencao para nao colocar virgula no final
                fprintf(arquivoSaida,",");
            }
        }
        fprintf(arquivoSaida,"\n");

    }

    // // libera o vetor de frequencia, os grupos e a matriz de agrupamentos
    free(freq);
    free(grupos);
    for (int i = 0; i < k; i++) {
        free(agrupamentos[i]);
    }
    free(agrupamentos);
}