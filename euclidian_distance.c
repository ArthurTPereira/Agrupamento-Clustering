#include <stdio.h>
#include <math.h>

#include "euclidian_distance.h"

/* Algoritmo para calcular a distancia euclidiana entre dois pontos
* pontoA: vetor de long double com as coordenadas do ponto A
* pontoB: vetor de long double com as coordenadas do ponto B
* v_size: tamanho dos vetores pontoA e pontoB
* return: distancia euclidiana entre os pontos A e B
*/
long double euclidian_distance(long double* pontoA, long double* pontoB, int v_size) {
    long double soma = 0;
    // Calcula a soma dos quadrados das diferenças entre as coordenadas
    for (int i = 0; i < v_size; i++) {
        soma += pow(pontoA[i] - pontoB[i], 2);
    }
    
    // Retorna a raiz quadrada da soma
    return sqrtl(soma);
}
