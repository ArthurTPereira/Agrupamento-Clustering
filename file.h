#ifndef FILE_H
#define FILE_H

void verificaArgumentos(int argc, char** argv);

FILE* abreArquivoEntrada(char* nomeArquivoEntrada);

FILE* abreArquivoSaida(char* nomeArquivoSaida);

void escreveGrupos(FILE* arquivoSaida, int* mst, int tamanho, int k, char** nomes);


#endif