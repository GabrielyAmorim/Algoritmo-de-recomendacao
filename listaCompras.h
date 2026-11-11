#ifndef LISTACOMPRAS_H
#define LISTACOMPRAS_H

#include <map>
#include <vector>
#include <string>

using namespace std;

typedef struct{
    vector<string> codigoClientes;
    map<string, int> mapaClientes;
    vector<string> codigoProdutos;
    map<string, int> mapaProdutos;
    vector<vector<int>> compras;
} ListaCompras;

int lerArquivo(ListaCompras, const char *);
void exibeLista(const ListaCompras *);

#endif