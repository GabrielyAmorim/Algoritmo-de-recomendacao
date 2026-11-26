#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H
#include "listaCompras.h"
#include "matrizEsparsa.h"
#include <vector>

typedef struct{
    int** matrizInterseccao;
    double** matrizSimilaridade;
    CSR matrizInterseccaoCSR;
    CSR matrizSimilaridadeCSR;
} Similaridade;

void calculaInterseccaoLenta(const ListaCompras *, Similaridade *, int, int);

void calculaInterseccaoRapida(const ListaCompras *, Similaridade *, int, int);

void calculaInterseccaoCSR(const ListaCompras *, Similaridade *);

double calculaJaccard(double, double);

void calculaSimilaridade(const ListaCompras *, Similaridade *, int);

void calculaSimilaridadeCSR(const ListaCompras *, Similaridade *);
                            
void encontraSimilares(const Similaridade *, int, int);

void encontraSimilaresCSR(const Similaridade *, int, int);

#endif