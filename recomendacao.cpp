#include "recomendacao.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> criaLista(double** matrizSimilaridade, int n_clientes, int cliente){
    vector<int> vizinhos;

    for(int i = 0; i < n_clientes; i ++){
        
        if(i == cliente){
            continue;
        }

        double nivelSimilar = matrizSimilaridade[cliente][i];

        if(nivelSimilar < 1.0 && nivelSimilar > 0.0){
            vizinhos.push_back(i);
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
    return a.score < b.score;
}

void recomendarProduto(const vector<string>& nomeProdutos, const vector<list<int>>& compras, double** matrizSimilaridade,
    int n_clientes, int n_produtos, int cliente, int k){

    if(k <= 0){
        printf("K invalido.");
        return;
    }

    if(cliente < 0 || cliente >= n_clientes){
        printf("Cliente invalido.\n");
        return;
    }

    vector<int> vizinhos = criaLista(matrizSimilaridade, n_clientes, cliente);

    vector<Item> R = criaRanqueamento(n_produtos);

    for(int i = 0; i < vizinhos.size(); i++){

        for(int j : compras[vizinhos[i]]){
            
            if(find(compras[cliente].begin(), compras[cliente].end(), j) != compras[cliente].end()){
                continue;
            }    

            R[j].score *= matrizSimilaridade[cliente][vizinhos[i]];
        }
    }

    sort(R.begin(), R.end(), ordenaPorScore);

    int recomendacoes = 0;
    for(int i = 0; i < n_produtos && recomendacoes < k; i++){
        int produto = R[i].produto;

        if(R[i].score == 1.0){
            continue;
        }

        if(find(compras[cliente].begin(), compras[cliente].end(), produto) != compras[cliente].end()){
            continue;
        }

        cout << nomeProdutos[produto] << endl;
        recomendacoes++;
    }

    if(recomendacoes == 0){
        cout << "Nenhuma recomendacao disponivel" << endl;
    }  
}

void recomendarProdutoCSR(){
    
}