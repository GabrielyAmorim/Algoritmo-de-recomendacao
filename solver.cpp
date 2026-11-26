#include "listaCompras.h"
#include "similaridade.h"
#include "recomendacao.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <string>
#include <vector>

using namespace std;
namespace py = pybind11;

ListaCompras lista;
Similaridade similaridade;

void cria_lista_compras(const vector<vector<string>>& dados){
    int indiceCliente;
    int indiceProduto;
    
    for(int i = 0; i < dados.size(); i ++){
        string cliente = dados[i][0];
        string produto = dados[i][1];


        if(lista.mapaClientes.find(cliente) != lista.mapaClientes.end()){
            indiceCliente = lista.mapaClientes[cliente];
        } 
        else{
            indiceCliente = lista.codigoClientes.size();
            lista.codigoClientes.push_back(cliente);
            lista.mapaClientes[cliente] = indiceCliente;
            lista.compras.push_back(list<int>());
        }

        if(lista.mapaProdutos.find(produto) != lista.mapaProdutos.end()){
            indiceProduto = lista.mapaProdutos[produto];
        } 
        else{
            indiceProduto = lista.nomeProdutos.size();
            lista.nomeProdutos.push_back(produto);
            lista.mapaProdutos[produto] = indiceProduto;
        }

        int jaTem = 0;
        for(int k : lista.compras[indiceCliente]){
            if(k == indiceProduto){
                jaTem = 1;
                break;
            }    
        }

        if(jaTem == 0){
            lista.compras[indiceCliente].push_back(indiceProduto);
        }
    } 
}

PYBIND11_MODULE(nosso_solver, m){
    m.doc() = "Integração Python + C++ com pybind11";

    m.def(
        "cria_lista_compras",
        &cria_lista_compras,
        "Recebe um vetor de vetores que representam cada compra registrada."
    );
}    