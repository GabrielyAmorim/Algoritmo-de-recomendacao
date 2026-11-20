#include "similaridade.h"
#include <stdio.h>
#include <stdlib.h>

void calculaInterseccaoLenta(int*** matrizInterseccao, int** matrizCompras, int n_clientes, int n_produtos){
    int matrizTransposta[n_produtos][n_clientes];

    *matrizInterseccao = (int**)malloc(n_clientes * sizeof(int*));
    if (*matrizInterseccao == NULL){
        printf("Erro ao alocar memoria. 2");
        return;
    }

    for (int i = 0; i < n_clientes; i++){
        (*matrizInterseccao)[i] = (int*)malloc(n_clientes * sizeof(int));

        if ((*matrizInterseccao)[i] == NULL){
            printf("Erro ao alocar memoria. 2.1");
            return;
        }

        for (int j = 0; j < n_clientes; j++){
            (*matrizInterseccao)[i][j] = 0;
        }
    }

    for (int i = 0; i < n_clientes; i++){
        for (int j = 0; j < n_produtos; j++){
            matrizTransposta[j][i] = matrizCompras[i][j];
        }
    }

    for (int i = 0; i < n_clientes; i++){
        for (int j = 0; j < n_clientes; j++){
            for (int k = 0; k < n_produtos; k++) {
                (*matrizInterseccao)[i][j] += matrizCompras[i][k] * matrizTransposta[k][j];
            }
        }
    }
}

void calculaInterseccaoRapida(int*** matrizInterseccao, int** matrizCompras, int n_clientes, int n_produtos){

    *matrizInterseccao = (int**)malloc(n_clientes * sizeof(int*));
    
    if (*matrizInterseccao == NULL){
        printf("Erro ao alocar memoria. 2");
        return;
    }

    for (int i = 0; i < n_clientes; i++){
        (*matrizInterseccao)[i] = (int*)malloc(n_clientes * sizeof(int));

        if ((*matrizInterseccao)[i] == NULL){
            printf("Erro ao alocar memoria. 2.1");
            return;
        }

        for (int j = 0; j < n_clientes; j++){
            (*matrizInterseccao)[i][j] = 0;
        }
    }

    for(int i = 0; i < n_clientes; i++){
        for(int j = i; j < n_clientes; j++){
            int soma = 0;

            for(int k = 0; k < n_produtos; k++){
                soma += matrizCompras[i][k] * matrizCompras[j][k]; 
            }
            (*matrizInterseccao)[i][j] = soma;
            (*matrizInterseccao)[j][i] = soma;
        }
    }
}

double calculaJaccard(double interseccao, double produtos_cliente){
    double similaridade = 1 - (interseccao/produtos_cliente);
    return similaridade;
}

void calculaSimilaridade(double*** matrizSimilaridade, int** matrizInterseccao, const vector<list<int>>& compras, int n_clientes){

    *matrizSimilaridade = (double**)malloc(n_clientes * sizeof(double*));
    if (*matrizSimilaridade == NULL){
        printf("Erro ao alocar memoria. 3");
        return;
    }

    for (int i = 0; i < n_clientes; i++){
        (*matrizSimilaridade)[i] = (double*)malloc(n_clientes * sizeof(double));
        if ((*matrizSimilaridade)[i] == NULL){
            printf("Erro ao alocar memoria. 3.1");
            return;
        }
    }

    for (int i = 0; i < n_clientes; i++){
        for (int j = 0; j < n_clientes; j++){
            (*matrizSimilaridade)[i][j] = calculaJaccard(matrizInterseccao[i][j], compras[i].size()); 
        }
    }
}

void encontraSimilares(double** matrizSimilaridade, int n_clientes, int cliente){
 
    if(cliente < 0 || cliente >= n_clientes){
        printf("Cliente invalido.\n");
        return;
    }
 
    double menorValor = 1.0;
    int maisSimilar = -1;
 
    for(int i = 0; i < n_clientes; i++){
        if(i == cliente){
            continue;
        }

        if(matrizSimilaridade[cliente][i] < menorValor){
            menorValor = matrizSimilaridade[cliente][i];
            maisSimilar = i;
        }
    }
 
    if(maisSimilar == -1){
        printf("Nenhum cliente similar encontrado.\n");
    } else {
        printf("Vizinho mais similar: %d (s = %.3f)\n", maisSimilar, menorValor);
    }
}