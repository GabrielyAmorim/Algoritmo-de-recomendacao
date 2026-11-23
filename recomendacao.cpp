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

        if(nivelSimilar < 1.0 && nivelSimilar >= 0.0){
            vizinhos.push_back(i);
        }
    }

    return vizinhos;
}

vector<int> criaListaCSR(const vector<double>& similaridade_values, const vector<int>& similaridade_index,
    const vector<int>& similaridade_row_ptr, int cliente){

    vector<int> vizinhos;

    int inicio = similaridade_row_ptr[cliente];
    int fim = similaridade_row_ptr[cliente + 1];

    for(int i = inicio; i < fim; i ++){
        
        if(similaridade_index[i] == cliente){
            continue;
        }

        double nivelSimilar = similaridade_values[i];

        if(nivelSimilar < 1.0 && nivelSimilar >= 0.0){
            vizinhos.push_back(similaridade_index[i]);
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
    for(int i = 0; i < n_produtos; i++){

        if(recomendacoes >= k){
            break;
        }

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

void recomendarProdutoCSR(const vector<string>& nomeProdutos, const vector<list<int>>& compras,
                         const vector<double>& similaridade_values, const vector<int>& similaridade_index,
                         const vector<int>& similaridade_row_ptr, int n_clientes, int n_produtos, int cliente, int k){

    if(k <= 0){
        printf("K invalido.");
        return;
    }

    if(cliente < 0 || cliente >= n_clientes){
        printf("Cliente invalido.\n");
        return;
    }

    vector<int> vizinhos = criaListaCSR(similaridade_values,similaridade_index, similaridade_row_ptr, cliente);

    vector<Item> R = criaRanqueamento(n_produtos);

    for(int i = 0; i < vizinhos.size(); i++){

        int inicio = similaridade_row_ptr[cliente];
        int fim = similaridade_row_ptr[cliente + 1];

        double nivelSimilar = 1.0;

        for(int j = inicio; j < fim; j++){
            if(similaridade_index[j] == vizinhos[i]){
                nivelSimilar = similaridade_values[j];
                break;
            }
        }

        for(int produto: compras[vizinhos[i]]){
            
            if(find(compras[cliente].begin(), compras[cliente].end(), produto) != compras[cliente].end()){
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