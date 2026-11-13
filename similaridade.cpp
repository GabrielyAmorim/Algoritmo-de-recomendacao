#include "similaridade.h"
#include <stdio.h>
#include <stdlib.h>

void calculaInterseccao(Similaridade *sim, const ListaCompras *lista){
    int n_clientes = lista->codigoClientes.size();
    int n_produtos = lista->codigoProdutos.size();
    int matrizTransposta[n_produtos][n_clientes];

    sim->matrizInterseccao = (int**)malloc(n_clientes * sizeof(int*));
    if (sim->matrizInterseccao == NULL){
        printf("Erro ao alocar memoria.");
        return;
    }

    for (int i = 0; i < n_clientes; i++){
        sim->matrizInterseccao[i] = (int*)malloc(n_clientes * sizeof(int));

        if (sim->matrizInterseccao[i] == NULL){
            printf("Erro ao alocar memoria.");
            return;
        }

        for (int j = 0; j < n_clientes; j++){
            sim->matrizInterseccao[i][j] = 0;
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
                sim->matrizInterseccao[i][j] += lista->matrizCompras[i][k] * matrizTransposta[k][j];
            }
        }
    }
}

double calculaJaccard(double interseccao, double produtos_cliente){
    double similaridade = 1 - (interseccao/produtos_cliente);
    return similaridade;
}

void calculaSimilaridade(Similaridade *sim, const ListaCompras *lista){
    int n_clientes = lista->codigoClientes.size();

    sim->matrizSimilaridade = (double**)malloc(n_clientes * sizeof(double*));
    if (sim->matrizSimilaridade == NULL){
        printf("Erro ao alocar memoria.");
    }

    for (int i = 0; i < n_clientes; i++){
        sim->matrizSimilaridade[i] = (double*)malloc(n_clientes * sizeof(double));
        if (sim->matrizSimilaridade[i] == NULL){
            printf("Erro ao alocar memoria.");
        }
    }

    for (int i = 0; i < n_clientes; i++){
        for (int j = 0; j < n_clientes; j++){
            sim->matrizSimilaridade[i][j] = calculaJaccard(sim->matrizInterseccao[i][j], lista->compras[i].size()); 
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