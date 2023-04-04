#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUCCESS 0
#define ERROR -1

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Numero de argumentos invalido!\n");
        return ERROR;
    } 

    char* nomeArquivoEntrada = argv[1];
    char* nomeArquivoSaida = argv[3];
    int k = atoi(argv[2]);

    FILE* arquivoEntrada = fopen(nomeArquivoEntrada, "r");
    
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        return ERROR;
    }


    fclose(arquivoEntrada);

    return SUCCESS;
}