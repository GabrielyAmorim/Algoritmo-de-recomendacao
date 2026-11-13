#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include "listaCompras.h"
#include "similaridade.h"
#include <vector>

typedef struct{
    int produto;
    double score;
} Item;

vector<int> criaLista(const Similaridade *, int, int);
vector<Item> criaRanqueamente(int);
bool ordenaPorScore(const Item &, const Item &);
void recomendarProduto(const ListaCompras*, const Similaridade*, int, int);



#endif