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
void calculaInterseccaoCSR(const vector<double>&, const vector<int>&, const vector<int>&, vector<double>&, vector<int>&, vector<int>&);
double calculaJaccard(double, double);
void calculaSimilaridade(double***, int**, const vector<list<int>>&, int);
void calculaSimilaridadeCSR(const vector<double>*, const vector<int>*, const vector<int>*, const vector<int>*, vector<double>*, vector<int>*, vector<int>* );
void encontraSimilares(double**, int, int);
// void encontraSimilaresCSR();

#endif