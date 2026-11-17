#include "recomendacao.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> criaLista(const Similaridade *simi, int numClientes, int cliente){
    vector<int> vizinhos;

    for(int i = 0; i < numClientes; i ++){
        
        if(i == cliente){
            continue;
        }

        double nivelSimilar = simi->matrizSimilaridade[cliente][i];

        if(nivelSimilar < 1.0 && nivelSimilar > 0.0){
            vizinhos.push_back(i);
        }
    }

    return vizinhos;
}

vector<Item> criaRanqueamento(int numProdutos){
    vector<Item> R(numProdutos);

    for(int i = 0; i < numProdutos; i++){
        R[i].produto = i;
        R[i].score   = 1.0;
    }

    return R;
}    

bool ordenaPorScore(const Item &a, const Item &b){
    return a.score < b.score;
}

void recomendarProduto(const ListaCompras *lista, const Similaridade *simi, int cliente, int k){

    int numClientes = lista->codigoClientes.size();
    int numProdutos = lista->nomeProdutos.size();
    
    if(k <= 0){
        printf("K invalido.");
        return;
    }

    if(cliente < 0 || cliente >= numClientes){
        printf("Cliente invalido.\n");
        return;
    }

    vector<int> vizinhos = criaLista(simi, numClientes, cliente);

    vector<Item> R = criaRanqueamento(numProdutos);

    for(int i = 0; i < vizinhos.size(); i++){

        for(int j = 0; j < lista->compras[vizinhos[i]].size(); j++){
            int produto = lista->compras[vizinhos[i]][j];

            if(find(lista->compras[cliente].begin(), lista->compras[cliente].end(), produto) != lista->compras[cliente].end()){
                continue;
            }    

            R[produto].score *= simi->matrizSimilaridade[cliente][vizinhos[i]];
        }
    }

    sort(R.begin(), R.end(), ordenaPorScore);

    int i;
    for(i = 0; i < numProdutos && i < k; i++){
        int produto = R[i].produto;

        if(R[i].score == 1.0){
            continue;
        }

        if(find(lista->compras[cliente].begin(), lista->compras[cliente].end(), produto) != lista->compras[cliente].end()){
            continue;
        }

        cout << lista->nomeProdutos[produto] << endl;

    }

    if(i == 0){
        cout << "Nenhuma recomendacao disponivel" << endl;
    }  
}