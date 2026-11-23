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

//T = transposta
void calculaInterseccaoCSR(const vector<double>& compras_values,
                           const vector<int>& compras_index,
                           const vector<int>& compras_row_ptr, 
                           vector<double>& interseccao_values,
                           vector<int>& interseccao_index,
                           vector<int>& interseccao_row_ptr
                           ){
    
    interseccao_row_ptr.push_back(0);
    int cont = 0;
    int n_linhas = compras_row_ptr.size() - 1;

    for (int i = 0; i < n_linhas - 1; i++){
        for (int j = 0; j < n_linhas; j++){

            int a = compras_row_ptr[i];
            int fimA = compras_row_ptr[i + 1];
            int aT = compras_row_ptr[j];
            int fimAT = compras_row_ptr[j + 1];
            double soma = 0;


            while (a < fimA && aT < fimAT){
                if (compras_index[a] == compras_index[aT]){

                    soma += compras_values[a] * compras_values[aT];
                    a++;
                    aT++;
                } else if (compras_index[a]  < compras_index[aT]){
                    a++;
                } else if (compras_index[a] > compras_index[aT]){
                    aT++;
                }
            }

            if (soma > 0){
                    interseccao_values.push_back(soma);
                    interseccao_index.push_back(j);
            }
        }
        interseccao_row_ptr.push_back(cont);
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

//S = similaridade
void calculaSimilaridadeCSR(const vector<double>& interseccao_values,
                            const vector<int>& interseccao_index,
                            const vector<int>& interseccao_row_ptr,
                            const vector<int>& compras_row_ptr,
                            vector<double>& similaridade_values,
                            vector<int>& similaridade_index,
                            vector<int>& similaridade_row_ptr
                            ){
    

    similaridade_row_ptr.push_back(0);
    int cont = 0;
    int n_linhas = interseccao_row_ptr.size() - 1;
    for (int i = 0; i < n_linhas; i++){
        int n_produtos_cliente = compras_row_ptr[i + 1] - compras_row_ptr [i];
        int n_interseccoes = interseccao_row_ptr[i + 1] - interseccao_row_ptr[i];

        for (int j = 0; j < n_interseccoes; j++){
            similaridade_values.push_back(calculaJaccard(interseccao_values[j], n_produtos_cliente));
            similaridade_index.push_back(interseccao_index[j]);
            cont++;
        }

        similaridade_row_ptr.push_back(cont);
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