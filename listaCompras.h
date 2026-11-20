#ifndef LISTACOMPRAS_H
#define LISTACOMPRAS_H

#include <map>
#include <vector>
#include <string>
#include <list>
#include "matrizEsparsa.h"

using namespace std;

typedef struct{
    vector<string> codigoClientes;
    map<string, int> mapaClientes;
    vector<string> nomeProdutos;
    map<string, int> mapaProdutos;
    vector<list<int>> compras;
    int** matrizCompras;
    CSR matrizComprasCSR;
} ListaCompras;

int lerArquivo(ListaCompras *, const char *);
void criaMatrizCompras(const vector<list<int>>&, int, int, int***);
void criaCSRMatrizCompras(const vector<list<int>>&, int, vector<double>&, vector<int>&, vector<int>&);
void exibeLista(const vector<string>&, const vector<list<int>>&, const vector<string>&);

#endif