#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include "listaCompras.h"
#include "similaridade.h"
#include <vector>

typedef struct{
    int produto;
    double score;
} Item;

vector<int> criaLista(double**, int, int);

vector<int> criaListaCSR(const vector<double>&, const vector<int>&, const vector<int>&, int);

vector<Item> criaRanqueamento(int);

bool ordenaPorScore(const Item&, const Item&);

void recomendarProduto(const vector<string>&, const vector<list<int>>&, double**, int, int, int, int);

void recomendarProdutoCSR(const vector<string>&, const vector<list<int>>&, const vector<double>&, const vector<int>&,
                         const vector<int>&, int, int, int, int);

#endif