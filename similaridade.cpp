#include "similaridade.h"
#include "matrizEsparsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

void calculaInterseccaoLenta(const ListaCompras *lista, Similaridade *simi, int n_clientes, int n_produtos){
    int** matrizTransposta = (int**)malloc(n_produtos * sizeof(int*));
    if (matrizTransposta == NULL){
        printf("Erro ao alocar memoria.");
        return;
    }

    for (int i = 0; i < n_produtos; i++){
        matrizTransposta[i] = (int*)malloc(n_clientes * sizeof(int));

        if (matrizTransposta[i] == NULL){
            printf("Erro ao alocar memoria.");
        }
    }

    simi->matrizInterseccao = (int**)malloc(n_clientes * sizeof(int*));
    if (simi->matrizInterseccao == NULL){
        printf("Erro ao alocar memoria. 2");
        return;
    }

    for (int i = 0; i < n_clientes; i++){
        (simi->matrizInterseccao)[i] = (int*)malloc(n_clientes * sizeof(int));

        if ((simi->matrizInterseccao)[i] == NULL){
            printf("Erro ao alocar memoria. 2.1");
            return;
        }

        for (int j = 0; j < n_clientes; j++){
            (simi->matrizInterseccao)[i][j] = 0;
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
                (simi->matrizInterseccao)[i][j] += lista->matrizCompras[i][k] * matrizTransposta[k][j];
            }
        }
    }

    for (int i = 0; i < n_produtos; i++){
        free(matrizTransposta[i]);
    }
    free(matrizTransposta);
}

void calculaInterseccaoRapida(const ListaCompras *lista, Similaridade *simi, int n_clientes, int n_produtos){

    simi->matrizInterseccao = (int**)malloc(n_clientes * sizeof(int*));
    
    if (simi->matrizInterseccao == NULL){
        printf("Erro ao alocar memoria. 2");
        return;
    }

    for (int i = 0; i < n_clientes; i++){
        (simi->matrizInterseccao)[i] = (int*)malloc(n_clientes * sizeof(int));

        if ((simi->matrizInterseccao)[i] == NULL){
            printf("Erro ao alocar memoria. 2.1");
            return;
        }

        for (int j = 0; j < n_clientes; j++){
            (simi->matrizInterseccao)[i][j] = 0;
        }
    }

    for(int i = 0; i < n_clientes; i++){
        for(int j = i; j < n_clientes; j++){
            int soma = 0;

            for(int k = 0; k < n_produtos; k++){
                soma += lista->matrizCompras[i][k] * lista->matrizCompras[j][k]; 
            }
            (simi->matrizInterseccao)[i][j] = soma;
            (simi->matrizInterseccao)[j][i] = soma;
        }
    }
}

void calculaInterseccaoCSR(const ListaCompras *lista, Similaridade *simi){
    
    simi->matrizInterseccaoCSR.row_ptr.push_back(0);
    int cont = 0;
    int n_linhas = lista->matrizComprasCSR.row_ptr.size() - 1;

    for (int i = 0; i < n_linhas; i++){
        for (int j = 0; j < n_linhas; j++){

            int a = lista->matrizComprasCSR.row_ptr[i];
            int fimA = lista->matrizComprasCSR.row_ptr[i + 1];

            int b = lista->matrizComprasCSR.row_ptr[j];
            int fimB = lista->matrizComprasCSR.row_ptr[j + 1];

            double soma = 0;

            while(a < fimA && b < fimB){

                if (lista->matrizComprasCSR.col_index[a] == lista->matrizComprasCSR.col_index[b]){ 
                    soma += lista->matrizComprasCSR.values[a] * lista->matrizComprasCSR.values[b];
                    a++;
                    b++;
                }
                else if(lista->matrizComprasCSR.col_index[a]  < lista->matrizComprasCSR.col_index[b]){
                    a++;
                }
                else{
                    b++;
                }
            }

            if(soma > 0){
                    simi->matrizInterseccaoCSR.values.push_back(soma);
                    simi->matrizInterseccaoCSR.col_index.push_back(j);
                    cont ++;
            }
        }
        
        simi->matrizInterseccaoCSR.row_ptr.push_back(cont);
    }
}


double calculaJaccard(double interseccao, double produtos_cliente){
    double similaridade = 1 - (interseccao/produtos_cliente);
    return similaridade;
}

void calculaSimilaridade(const ListaCompras *lista, Similaridade *simi, int n_clientes){

    simi->matrizSimilaridade = (double**)malloc(n_clientes * sizeof(double*));
    if (simi->matrizSimilaridade == NULL){
        printf("Erro ao alocar memoria. 3");
        return;
    }

    for (int i = 0; i < n_clientes; i++){
        (simi->matrizSimilaridade)[i] = (double*)malloc(n_clientes * sizeof(double));
        if ((simi->matrizSimilaridade)[i] == NULL){
            printf("Erro ao alocar memoria. 3.1");
            return;
        }
    }

    for (int i = 0; i < n_clientes; i++){
        for (int j = 0; j < n_clientes; j++){
            (simi->matrizSimilaridade)[i][j] = calculaJaccard(simi->matrizInterseccao[i][j], lista->compras[i].size()); 
        }
    }
}

void calculaSimilaridadeCSR(const ListaCompras *lista, Similaridade *simi){

    simi->matrizSimilaridadeCSR.row_ptr.push_back(0);                            
    int cont = 0;
    int n_linhas = simi->matrizInterseccaoCSR.row_ptr.size() - 1;
    
    for (int i = 0; i < n_linhas; i++){
        int n_produtos_cliente = lista->matrizComprasCSR.row_ptr[i + 1] - lista->matrizComprasCSR.row_ptr [i];
        int inicio = simi->matrizInterseccaoCSR.row_ptr[i];
        int fim = simi->matrizInterseccaoCSR.row_ptr[i + 1];

        for (int j = inicio; j < fim; j++){
            simi->matrizSimilaridadeCSR.values.push_back(calculaJaccard(simi->matrizInterseccaoCSR.values[j], n_produtos_cliente));
            simi->matrizSimilaridadeCSR.col_index.push_back(simi->matrizInterseccaoCSR.col_index[j]);
            cont++;
        }

        simi->matrizSimilaridadeCSR.row_ptr.push_back(cont);
    }
}

void encontraSimilares(const Similaridade *simi, int n_clientes, int cliente){
 
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

        if(simi->matrizSimilaridade[cliente][i] < menorValor){
            menorValor = simi->matrizSimilaridade[cliente][i];
            maisSimilar = i;
        }
    }
 
    if(maisSimilar == -1){
        printf("Nenhum cliente similar encontrado.\n");
    }
    else{
        printf("Cliente mais similar: %d (s = %.3f)\n", maisSimilar, menorValor);
    }
}

void encontraSimilaresCSR(const Similaridade *simi, int n_clientes, int cliente){

    if(cliente < 0 || cliente >= n_clientes){
        printf("Cliente invalido.\n");
        return;
    }
 
    double menorValor = 1.0;
    int maisSimilar = -1;

    int inicio = simi->matrizSimilaridadeCSR.row_ptr[cliente];
    int fim = simi->matrizSimilaridadeCSR.row_ptr[cliente + 1];

    for(int i = inicio; i < fim; i++){
        if(simi->matrizSimilaridadeCSR.col_index[i] == cliente){
            continue;
        }

        if(simi->matrizSimilaridadeCSR.values[i] < menorValor){
            menorValor = simi->matrizSimilaridadeCSR.values[i];
            maisSimilar = simi->matrizSimilaridadeCSR.col_index[i];
        }
    }

    if(maisSimilar == -1){
        printf("Nenhum cliente similar encontrado.\n");
    } 
    else{
        printf("Cliente mais similar: %d (s = %.3f)\n", maisSimilar, menorValor);
    }
}