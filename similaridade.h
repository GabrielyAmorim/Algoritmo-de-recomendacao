#define SIMILARIDADE_H
#ifndef SIMILARIDADE_H
#include "listaCompras.h"

typedef struct{
    int** compras_binario;
    int** compras_transposta;
    int** interseccao;
    int** similaridade;
} Similaridade;

void multiplicaMatriz(int**, int**);
void calculaTransposta(int**;);
void calculaInterseccao(int**, int**);
void calculaSimilaridade(int**, int**);

#endif