#include "similaridade.h"
#include <stdio.h>
#include <stdlib.h>

void calculaInterseccaoLenta(Similaridade *simi, const ListaCompras *lista){
    int n_clientes = lista->codigoClientes.size();
    int n_produtos = lista->nomeProdutos.size();
    int matrizTransposta[n_produtos][n_clientes];

    simi->matrizInterseccao = (int**)malloc(n_clientes * sizeof(int*));
    if (simi->matrizInterseccao == NULL){
        printf("Erro ao alocar memoria. 2");
        return;
    }

    for (int i = 0; i < n_clientes; i++){
        simi->matrizInterseccao[i] = (int*)malloc(n_clientes * sizeof(int));

        if (simi->matrizInterseccao[i] == NULL){
            printf("Erro ao alocar memoria. 2.1");
            return;
        }

        for (int j = 0; j < n_clientes; j++){
            simi->matrizInterseccao[i][j] = 0;
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
                simi->matrizInterseccao[i][j] += lista->matrizCompras[i][k] * matrizTransposta[k][j];
            }
        }
    }
}

void calculaInterseccaoRapida(Similaridade *simi, const ListaCompras *lista){
    int n_clientes = lista->codigoClientes.size();
    int n_produtos = lista->nomeProdutos.size();

    simi->matrizInterseccao = (int**)malloc(n_clientes * sizeof(int*));
    
    if (simi->matrizInterseccao == NULL){
        printf("Erro ao alocar memoria. 2");
        return;
    }

    for (int i = 0; i < n_clientes; i++){
        simi->matrizInterseccao[i] = (int*)malloc(n_clientes * sizeof(int));

        if (simi->matrizInterseccao[i] == NULL){
            printf("Erro ao alocar memoria. 2.1");
            return;
        }

        for (int j = 0; j < n_clientes; j++){
            simi->matrizInterseccao[i][j] = 0;
        }
    }

    for(int i = 0; i < n_clientes; i++){
        for(int j = i; j < n_clientes; j++){
            int soma = 0;

            for(int k = 0; k < n_produtos; k++){
                soma += lista->matrizCompras[i][k] * lista->matrizCompras[j][k]; 
            }
            simi->matrizInterseccao[i][j] = soma;
            simi->matrizInterseccao[j][i] = soma;
        }
    }
}            

double calculaJaccard(double interseccao, double produtos_cliente){
    double similaridade = 1 - (interseccao/produtos_cliente);
    return similaridade;
}

void calculaSimilaridade(Similaridade *simi, const ListaCompras *lista){
    int n_clientes = lista->codigoClientes.size();

    simi->matrizSimilaridade = (double**)malloc(n_clientes * sizeof(double*));
    if (simi->matrizSimilaridade == NULL){
        printf("Erro ao alocar memoria. 3");
        return;
    }

    for (int i = 0; i < n_clientes; i++){
        simi->matrizSimilaridade[i] = (double*)malloc(n_clientes * sizeof(double));
        if (simi->matrizSimilaridade[i] == NULL){
            printf("Erro ao alocar memoria. 3.1");
            return;
        }
    }

    for (int i = 0; i < n_clientes; i++){
        for (int j = 0; j < n_clientes; j++){
            simi->matrizSimilaridade[i][j] = calculaJaccard(simi->matrizInterseccao[i][j], lista->compras[i].size()); 
        }
    }
}

void encontraSimilares(Similaridade * simi, const ListaCompras * lista, int cliente){
    int numClientes = lista->codigoClientes.size();
 
    if(cliente < 0 || cliente >= numClientes){
        printf("Cliente invalido.\n");
        return;
    }
 
    double menorValor = 1.0;
    int maisSimilar = -1;
 
    for(int i = 0; i < numClientes; i++){
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
    } else {
        printf("Vizinho mais similar: %d (s = %.3f)\n", maisSimilar, menorValor);
    }
}