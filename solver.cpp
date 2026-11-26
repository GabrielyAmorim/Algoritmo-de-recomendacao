#include "listaCompras.h"
#include "similaridade.h"
#include "recomendacao.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <string>
#include <vector>
#include <ctime>

using namespace std;
namespace py = pybind11;

void recomendar(vector<string> codigo_clientes, map<string, int> mapa_clientes, vector<string>nome_produtos,
                map<string, int> mapa_produtos, vector<list<int>> compras, 
                int modo, int opcao, int cliente, int k){

    ListaCompras lista;

    lista.codigoClientes = codigo_clientes;
    lista.mapaClientes = mapa_clientes;
    lista.nomeProdutos = nome_produtos;
    lista.mapaProdutos = mapa_produtos;
    lista.compras = compras;

    clock_t inicio = clock();

    int n_clientes = lista.codigoClientes.size();
    int n_produtos = lista.nomeProdutos.size();
    
    Similaridade simi;

    if(modo != 3){

        criaMatrizCompras(&lista, n_clientes, n_produtos);

        if(modo == 1){
            calculaInterseccaoLenta(&lista, &simi, n_clientes, n_produtos);
        }
        else{
            calculaInterseccaoRapida(&lista, &simi, n_clientes, n_produtos);
        }

        calculaSimilaridade(&lista, &simi, n_clientes);
    }

    else{

        criaCSRMatrizCompras(&lista);

        calculaInterseccaoCSR(&lista, &simi);

        calculaSimilaridadeCSR(&lista, &simi);
    }
    
    clock_t fim = clock();
    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;

    switch(opcao){

        case 1:

            exibeLista(&lista);
            break;

        case 2:

            if(modo == 3){
                encontraSimilaresCSR(&simi, n_clientes, cliente);
            }
            else{
                encontraSimilares(&simi, n_clientes, cliente);
            }
            
            break;

        case 3:

            if(modo == 3){
                recomendarProdutoCSR(&lista, &simi, n_clientes, n_produtos, cliente, k);
            }
            else{
                recomendarProduto(&lista, &simi, n_clientes, n_produtos, cliente, k);
            }

            break;
    }

    if(modo != 3){
        for(int i = 0; i < lista.codigoClientes.size(); i++){
            free(simi.matrizInterseccao[i]);
            free(simi.matrizSimilaridade[i]);
            free(lista.matrizCompras[i]);
        }
        free(simi.matrizInterseccao);
        free(simi.matrizSimilaridade);
        free(lista.matrizCompras);
    }    

    printf("%f", tempo);

    return;
}

PYBIND11_MODULE(nosso_solver, m){
    m.doc() = "Integração Python + C++ com pybind11";

     m.def(
        "recomendar",
        &recomendar,
        "Realiza todo o sistema de recomendação."
    );

}    