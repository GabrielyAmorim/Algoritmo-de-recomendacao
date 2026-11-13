#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H
#include "listaCompras.h"

typedef struct{
    int** matrizInterseccao;
    double** matrizSimilaridade;
} Similaridade;

void calculaInterseccao(int**, const ListaCompras *);
double calculaJaccard(int*, int*);
void calculaSimilaridade(Similaridade*, const ListaCompras*);
void encontraSimilares(Similaridade *, const ListaCompras *, int);

#endif