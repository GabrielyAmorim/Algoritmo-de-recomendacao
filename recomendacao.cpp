#include "recomendacao.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> criaLista(const Similaridade *simi, int n_clientes, int cliente){
    vector<int> vizinhos;

    for(int i = 0; i < n_clientes; i ++){
        
        if(i == cliente){
            continue;
        }

        double nivelSimilar = simi->matrizSimilaridade[cliente][i];

        if(nivelSimilar < 1.0 && nivelSimilar >= 0.0){
            vizinhos.push_back(i);
        }
    }

    return vizinhos;
}

vector<int> criaListaCSR(const Similaridade *simi, int cliente){

    vector<int> vizinhos;

    int inicio = simi->matrizSimilaridadeCSR.row_ptr[cliente];
    int fim = simi->matrizSimilaridadeCSR.row_ptr[cliente + 1];

    for(int i = inicio; i < fim; i ++){
        
        if(simi->matrizSimilaridadeCSR.col_index[i] == cliente){
            continue;
        }

        double nivelSimilar = simi->matrizSimilaridadeCSR.values[i];

        if(nivelSimilar < 1.0 && nivelSimilar >= 0.0){
            vizinhos.push_back(simi->matrizSimilaridadeCSR.col_index[i]);
        }
    }

    return vizinhos;
}

vector<Item> criaRanqueamento(int n_produtos){
    vector<Item> R(n_produtos);

    for(int i = 0; i < n_produtos; i++){
        R[i].produto = i;
        R[i].score   = 1.0;
    }

    return R;
}    

bool ordenaPorScore(const Item &a, const Item &b){
    if (a.score == b.score){
        return a.produto < b.produto;
    }
    
    return a.score < b.score;
}

void recomendarProduto(const ListaCompras *lista, const Similaridade *simi, 
                       int n_clientes, int n_produtos, int cliente, int k){

    if(k <= 0){
        printf("K invalido.");
        return;
    }

    if(cliente < 0 || cliente >= n_clientes){
        printf("Cliente invalido.\n");
        return;
    }

    vector<int> vizinhos = criaLista(simi, n_clientes, cliente);

    vector<Item> R = criaRanqueamento(n_produtos);

    for(int i = 0; i < vizinhos.size(); i++){

        for(int j : lista->compras[vizinhos[i]]){
            
            if(find(lista->compras[cliente].begin(), lista->compras[cliente].end(), j) != lista->compras[cliente].end()){
                continue;
            }    

            R[j].score *= simi->matrizSimilaridade[cliente][vizinhos[i]];
        }
    }

    sort(R.begin(), R.end(), ordenaPorScore);

    int recomendacoes = 0;
    for(int i = 0; i < n_produtos; i++){

        if(recomendacoes >= k){
            break;
        }

        int produto = R[i].produto;

        if(R[i].score == 1.0){
            continue;
        }

        if(find(lista->compras[cliente].begin(), lista->compras[cliente].end(), produto) != lista->compras[cliente].end()){
            continue;
        }

        cout << lista->nomeProdutos[produto] << endl;
        recomendacoes++;
    }

    if(recomendacoes == 0){
        cout << "Nenhuma recomendacao disponivel" << endl;
    }  
}

void recomendarProdutoCSR(const ListaCompras *lista, const Similaridade *simi,
                          int n_clientes, int n_produtos, int cliente, int k){

    if(k <= 0){
        printf("K invalido.");
        return;
    }

    if(cliente < 0 || cliente >= n_clientes){
        printf("Cliente invalido.\n");
        return;
    }

    vector<int> vizinhos = criaListaCSR(simi, cliente);

    vector<Item> R = criaRanqueamento(n_produtos);

    for(int i = 0; i < vizinhos.size(); i++){

        int inicio = simi->matrizSimilaridadeCSR.row_ptr[cliente];
        int fim = simi->matrizSimilaridadeCSR.row_ptr[cliente + 1];

        double nivelSimilar = 1.0;

        for(int j = inicio; j < fim; j++){
            if(simi->matrizSimilaridadeCSR.col_index[j] == vizinhos[i]){
                nivelSimilar = simi->matrizSimilaridadeCSR.values[j];
                break;
            }
        }

        for(int produto: lista->compras[vizinhos[i]]){
            
            if(find(lista->compras[cliente].begin(), lista->compras[cliente].end(), produto) != lista->compras[cliente].end()){
                continue;
            }    

            R[produto].score *= nivelSimilar;
        }
    }

    sort(R.begin(), R.end(), ordenaPorScore);

    int recomendacoes = 0;
    for(int i = 0; i < n_produtos; i++){

        if(recomendacoes >= k){
            break;
        }

        int produto = R[i].produto;

        if(R[i].score == 1.0){
            continue;
        }

        if(find(lista->compras[cliente].begin(), lista->compras[cliente].end(), produto) != lista->compras[cliente].end()){
            continue;
        }

        cout << lista->nomeProdutos[produto] << endl;
        recomendacoes++;
    }

    if(recomendacoes == 0){
        cout << "Nenhuma recomendacao disponivel" << endl;
    }  
}