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

void exibir_lista_compras(){

    exibeLista(lista.codigoClientes, lista.compras, lista.nomeProdutos);

}

void calcular_similaridades(){

    criaCSRMatrizCompras(lista.compras, lista.matrizComprasCSR.values, lista.matrizComprasCSR.col_index, 
        lista.matrizComprasCSR.row_ptr);

    calculaInterseccaoCSR(lista.matrizComprasCSR.values, lista.matrizComprasCSR.col_index, lista.matrizComprasCSR.row_ptr,
        similaridade.matrizInterseccaoCSR.values, similaridade.matrizInterseccaoCSR.col_index, 
        similaridade.matrizInterseccaoCSR.row_ptr);

    calculaSimilaridadeCSR(similaridade.matrizInterseccaoCSR.values, similaridade.matrizInterseccaoCSR.col_index,
        similaridade.matrizInterseccaoCSR.row_ptr, lista.matrizComprasCSR.row_ptr, similaridade.matrizSimilaridadeCSR.values,
        similaridade.matrizSimilaridadeCSR.col_index, similaridade.matrizSimilaridadeCSR.row_ptr);

    printf("Matrizes CSR e similaridade calculadas com sucesso!");

}

void encontra_similares(int indiceCliente){

    encontraSimilaresCSR(similaridade.matrizSimilaridadeCSR.values, similaridade.matrizSimilaridadeCSR.col_index,
        similaridade.matrizSimilaridadeCSR.row_ptr, lista.codigoClientes.size(), indiceCliente);

}

PYBIND11_MODULE(nosso_solver, m){
    m.doc() = "Integração Python + C++ com pybind11";

    m.def(
        "cria_lista_compras",
        &cria_lista_compras,
        "Recebe um vetor de vetores que representam cada compra registrada."
    );

     m.def(
        "exibir_lista_compras",
        &exibir_lista_compras,
        "Exibe os produtos comprados por cada cliente."
    );

    m.def(
        "calcular_similaridades",
        &calcular_similaridades,
        "Constrói as matrizes CSR e calcula as similaridades."
    );

    m.def(
        "encontra_similares",
        &encontra_similares,
        "Encontra o cliente mais similar ao cliente informado."
    );


}    