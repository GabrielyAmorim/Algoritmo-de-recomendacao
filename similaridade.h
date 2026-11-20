#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H
#include "listaCompras.h"
#include "matrizEsparsa.h"

typedef struct{
    int** matrizInterseccao;
    double** matrizSimilaridade;
    CSR matrizInterseccaoCSR;
    CSR matrizSimilaridadeCSR;
} Similaridade;

void calculaInterseccaoLenta(int***, int**, int, int);
void calculaInterseccaoRapida(int***, int** , int, int);
double calculaJaccard(double, double);
void calculaSimilaridade(double***, int**, const vector<list<int>>&, int);
void encontraSimilares(double**, int, int);

#endif