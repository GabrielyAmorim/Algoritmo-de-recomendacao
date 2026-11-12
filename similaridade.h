#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H
#include "listaCompras.h"

typedef struct{
    int** matrizInterseccao;
    double** matrizSimilaridade;
} Similaridade;

void calculaInterseccao(int**, int**);
void calculaJaccard(int**, int**);
void calculaSimilaridade(int**, int**);

#endif