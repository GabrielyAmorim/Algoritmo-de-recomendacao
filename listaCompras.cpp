#include "listaCompras.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int lerArquivo(ListaCompras *lista, const char *nomeArquivo){

    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char data[9];
    char cliente[20];
    char produto[7];
    char nome[200];

    fscanf(arquivo, "%*[^\n]");

    while(fscanf(arquivo, " %8[^,],%19[^,],%6[^,],%199[^\r\n]", data, cliente, produto, nome) == 4){
        int indiceCliente;
        int indiceProduto;

        if(lista->mapaClientes.find(cliente) != lista->mapaClientes.end()){
            indiceCliente = lista->mapaClientes[cliente];
        } 
        else{
            indiceCliente = lista->codigoClientes.size();
            lista->codigoClientes.push_back(cliente);
            lista->mapaClientes[cliente] = indiceCliente;
            lista->compras.push_back(vector<int>());
        }

        if(lista->mapaProdutos.find(produto) != lista->mapaProdutos.end()){
            indiceProduto = lista->mapaProdutos[produto];
        } 
        else{
            indiceProduto = lista->codigoProdutos.size();
            lista->codigoProdutos.push_back(produto);
            lista->mapaProdutos[produto] = indiceProduto;
        }

        int i;
        for(i = 0; i < lista->compras[indiceCliente].size(); i++){
            if(lista->compras[indiceCliente][i] == indiceProduto){
                break;
            }
        }
        if(i == lista->compras[indiceCliente].size()){
            lista->compras[indiceCliente].push_back(indiceProduto);
        }
    }
 
    fclose(arquivo);
    return 0;
}

void criaMatrizCompras(ListaCompras *lista){
    int n_clientes = lista->codigoClientes.size();
    int n_produtos = lista->codigoProdutos.size();

    lista->matrizCompras = (int**)malloc(n_clientes * sizeof(int*));
    if (lista->matrizCompras == NULL){
        printf("Erro ao alocar memoria.");
        return;
    }

    for(int i = 0; i < n_clientes; i++){
        lista->matrizCompras[i] = (int*)malloc(n_produtos * sizeof(int));
        if (lista->matrizCompras[i] == NULL){
        printf("Erro ao alocar memoria.");
        return;
    }

        for (int j = 0; j < n_produtos; j++){
            lista->matrizCompras[i][j] = 0;
        }
    }

    for(int i = 0; i < n_clientes; i++){
        for (int j = 0; j < lista->compras[i].size(); j++){
            lista->matrizCompras[i][lista->compras[i][j]] = 1;
        }

    }
}

void exibeLista(const ListaCompras * lista){

   for(int i = 0; i < lista->codigoClientes.size(); i++){
        cout << "Cliente: " << lista->codigoClientes[i] << endl;
        cout << "Itens:" << endl;

        for(int j = 0; j < lista->compras[i].size(); j++){
            cout << " " << lista->codigoProdutos[lista->compras[i][j]] << endl;
        }

        cout << endl;
    }
}