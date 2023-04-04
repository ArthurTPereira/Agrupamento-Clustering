#ifndef PONTO_H
#define PONTO_H

typedef struct ponto Ponto;

Ponto** iniciaVetorPonto();

void inserePonto(Ponto** vet, int* pTam, int count, char* nome, int pos);

#endif