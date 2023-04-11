#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

#define ERROR -1

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


int comparaNomes(const void* string1, const void* string2) {
    int resultado = strcmp(*(char**) string1, *(char**) string2);
    if (resultado < 0) {
        return -1;
    } else if (resultado > 0) {
        return 1;
    } else {
        return 0;
    }
}


void escreveGrupos(FILE* arquivoSaida, int* mst, int tamanho, int k, char** nomes) {
    
    int* freq = (int*) calloc(k,sizeof(int));
    for (int i = 0; i < tamanho; i++) {
        freq[mst[i]]++;
    }

    int d = 0;
    int diff = 0;
    int* grupos = (int*) malloc(k * sizeof(int));

    for (int i = 0; i < tamanho; i++) {
        d = 1;
        for (int j = 0; j < diff; j++) {
            if (mst[i] == grupos[j]) {
                d = 0;
                break;
            }
        }
        
        if (d == 1) {
            grupos[diff] = mst[i];
            diff++;
        }
    }

    int** agrupamentos = (int**) malloc(k * sizeof(int*));
    for (int i = 0; i < k; i++) {
        agrupamentos[i] = (int*) malloc(freq[i] * sizeof(int));
    }

    int count = 0;
    for (int i = 0; i < k; i++) {
        count = 0;
        for (int j = 0; j < tamanho; j++) {
            if (mst[j] == grupos[i]) {
                agrupamentos[i][count] = j;
                count++;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        
    }
    

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < freq[i]; j++) {
            printf("%s", nomes[agrupamentos[i][j]]);
            if (j != freq[i] - 1) {
                printf(",");
            }
        } 
        printf("\n");
    }

    return;
    //  for(int i = 0; i < k; i++) {
    //         int menor = i;
    //         for(int j = i+1; j < k; j++){
    //             if(strcmp(nomes[agrupamentos[j][0]], nomes[agrupamentos[menor][0]]) < 0){
    //                 menor = j;
    //             }
    //         }
    //         if(menor != i){
    //             int* aux = agrupamentos[i];
    //             agrupamentos[i] = agrupamentos[menor];
    //             agrupamentos[menor] = aux;
    //         }
    //     }
    //     for(int i = 0; i < k; i++){
    //         //qsort(agrupamentos[i], mst[i], sizeof(int*), comparaNomes);
    //         fprintf(arquivoSaida, "%s\n", nomes[agrupamentos[i][0]]);
    //         for(int j = 0; j < freq[i]; j++){
    //             fprintf(arquivoSaida, "%s,", nomes[agrupamentos[i][j]]);
    //         }
    //         fprintf(arquivoSaida, "\n");
    //     }
}