#ifndef LISTACOMPRAS_H
#define LISTACOMPRAS_H

#include <map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

typedef struct{
    vector<string> codigoClientes;
    map<string, int> mapaClientes;
    vector<string> codigoProdutos;
    map<string, int> mapaProdutos;
    vector<vector<int>> compras;
} ListaCompras;

int lerArquivo(int, char *);
void registroCodigos();

#endif