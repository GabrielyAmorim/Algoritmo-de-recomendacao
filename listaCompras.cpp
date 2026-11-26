#include "listaCompras.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>

using namespace std;

int lerArquivo(ListaCompras *lista, const char *nomeArquivo){

    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char data[9];
    char cliente[20];
    char codigo_produto[7];
    char produto[200];

    fscanf(arquivo, "%*[^\n]");

    while(fscanf(arquivo, " %8[^,],%19[^,],%6[^,],%199[^\r\n]", data, cliente, codigo_produto, produto) == 4){
        int indiceCliente;
        int indiceProduto;

        if(lista->mapaClientes.find(cliente) != lista->mapaClientes.end()){
            indiceCliente = lista->mapaClientes[cliente];
        } 
        else{
            indiceCliente = lista->codigoClientes.size();
            lista->codigoClientes.push_back(cliente);
            lista->mapaClientes[cliente] = indiceCliente;
            lista->compras.push_back(list<int>());
        }

        if(lista->mapaProdutos.find(produto) != lista->mapaProdutos.end()){
            indiceProduto = lista->mapaProdutos[produto];
        } 
        else{
            indiceProduto = lista->nomeProdutos.size();
            lista->nomeProdutos.push_back(produto);
            lista->mapaProdutos[produto] = indiceProduto;
        }

        int jaTem = 0;
        for(int k : lista->compras[indiceCliente]){
            if(k == indiceProduto){
                jaTem = 1;
                break;
            }    
        }

        if(jaTem == 0){
            lista->compras[indiceCliente].push_back(indiceProduto);
        }
    }    
 
    fclose(arquivo);
    return 0;
}

void criaMatrizCompras(ListaCompras *lista, const int n_clientes, const int n_produtos){

    lista->matrizCompras = (int**)malloc(n_clientes * sizeof(int*));
    if (lista->matrizCompras == NULL){
        printf("Erro ao alocar memoria. 1");
        return;
    }

    for(int i = 0; i < n_clientes; i++){
        (lista->matrizCompras)[i] = (int*)malloc(n_produtos * sizeof(int));
        if ((lista->matrizCompras)[i] == NULL){
        printf("Erro ao alocar memoria. 1.1");
        return;
    }

        for (int j = 0; j < n_produtos; j++){
            (lista->matrizCompras)[i][j] = 0;
        }
    }

    for(int i = 0; i < n_clientes; i++){
        for (int j : lista->compras[i]){
            (lista->matrizCompras)[i][j] = 1;
        }
    }
}

void criaCSRMatrizCompras(ListaCompras *lista){ 

    int count = 0;

    lista->matrizComprasCSR.row_ptr.push_back(0);

    for(int i = 0; i < lista->compras.size(); i ++){

        vector<int> produtos(lista->compras[i].begin(), lista->compras[i].end());

        sort(produtos.begin(), produtos.end());

        for(int j : produtos){

            lista->matrizComprasCSR.values.push_back(1);
            lista->matrizComprasCSR.col_index.push_back(j);

            count++;
        }

        lista->matrizComprasCSR.row_ptr.push_back(count);
    }
}            

void exibeLista(const ListaCompras *lista){

   for(int i = 0; i < lista->codigoClientes.size(); i++){
        cout << "Cliente: " << lista->codigoClientes[i] << endl;
        cout << "Itens:" << endl;

        for(int j : lista->compras[i]){
            cout << " " << lista->nomeProdutos[j] << endl;
        }

        cout << endl;
    }
}