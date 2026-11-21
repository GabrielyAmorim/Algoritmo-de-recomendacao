#include "similaridade.h"
#include "matrizEsparsa.h"
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

void calculaInterseccaoCSR(vector<double>& compras_values,
                           vector<int>& compras_index,
                           vector<int>& compras_row_ptr,
                           vector<double>& interseccao_values,
                           vector<int>& interseccao_index,
                           vector<int>& interseccao_row_ptr
                           ){
    
    int cont = 0;

    for (int i = 0; i < compras_row_ptr.size() - 1; i++){
        int n_elementos = compras_row_ptr[i] - compras_row_ptr[i + 1];
        int soma = 0;
        int column;
        interseccao_row_ptr.push_back(0);

        int contT;
        for (int iT = 0; iT < compras_row_ptr.size() - 1; iT++){
            int n_elementosT = compras_row_ptr[iT] - compras_row_ptr[iT - 1];

            for (int j = 0; j < n_elementos; j++){
                for (int jT = 0; jT < n_elementosT; jT++){
                    if (compras_index[cont] == compras_index[contT]){

                        if ((compras_values[cont] * compras_values[contT]) != 0){
                            soma += compras_values[cont] * compras_values[contT];
                        }
                        contT++
                    }
                }
                if (soma != 0){
                    interseccao_values.push_back(soma);
                    interseccao_index.push_back(compras_index[cont]);
                cont++;
                }
            }
        }

        if (soma != 0){

            interseccao_row_ptr.push_back(cont);
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

void calculaSimilaridadeCSR(vector<double>& interseccao_values,
                            vector<int>& interseccao_index,
                            vector<int>& interseccao_row_ptr,
                            vector<double>& similaridade_values,
                            vector<int>& similaridade_index,
                            vector<int>& similaridade_row_ptr,
                            vector<int>& compras_row_ptr
                            ){
    
    int cont = 0;
    for (int i = 0; i < interseccao_values.size() - 1; i++){
        int n_elementos = interseccao_row_ptr[i] - interseccao_row_ptr[i + 1];
        int n_elementos_compras = compras_row_ptr[i] - compras_row_ptr[i + 1];

        for (int j = 0; j < n_elementos; j++){

            int similaridade = calculaJaccard(interseccao_values[i], n_elementos_compras);
            similaridade_values.push_back(similaridade);
            cont++;
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