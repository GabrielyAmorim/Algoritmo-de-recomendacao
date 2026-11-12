#include "similaridade.h"
#include <stdio.h>

void calculaInterseccao(int** matrizInterseccao, const ListaCompras *lista){
    int n_clientes = lista->codigoClientes.size();
    int n_produtos = lista->codigoProdutos.size();
    int matrizTransposta[n_produtos][n_clientes];

    matrizInterseccao = (int**)malloc(n_clientes * sizeof(int*));
    if (matrizInterseccao == NULL){
        printf("Erro ao alocar memoria.");
        return;
    }

    for (int i = 0; i < n_clientes; i++){
        matrizInterseccao[i] = (int*)malloc(n_clientes * sizeof(int));
        if (matrizInterseccao == NULL){
            printf("Erro ao alocar memoria.");
            return;
        }
    }

    for (int i = 0; i < n_clientes; i++){
        for (int j = 0; j < n_produtos; j++){
            matrizTransposta[j][i] = lista->matrizCompras[i][j];
        }
    }

    for (int i = 0; i < n_clientes; i++){
        for (int j = 0; j < n_clientes; j++){
            for (int k = 0; k < n_produtos; k++) {
                matrizInterseccao[i][j] += lista->matrizCompras[i][k] * matrizTransposta[k][j];
            }
        }
    }
}

double calcularJaccard(int interseccao, int produtos_cliente){
    double similaridade = 1 - (interseccao/produtos_cliente);
    
    return similaridade;
}

void calculaSimilartidade(Similaridade *sim, const ListaCompras *lista){
    int n_clientes = lista->codigoClientes.size();

    sim->matrizSimilaridade = (double**)malloc(n_clientes * sizeof(double*));
    if (sim->matrizSimilaridade == NULL){
        printf("Erro ao alocar memoria.");
        return;
    }

    for (int i = 0; i < n_clientes; i++){
        sim->matrizSimilaridade[i] = (double*)malloc(n_clientes * sizeof(double));
        if (sim->matrizSimilaridade[i] == NULL){
            printf("Erro ao alocar memoria.");
        }
    }

    for (int i = 0; i < n_clientes; i++){
        for (int j = 0; j < n_clientes; j++){
            sim->matrizSimilaridade[i][j] = calcularJaccard(sim->matrizInterseccao[i][j], lista->compras[i].size()); 
        }
    }

}