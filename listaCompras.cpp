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

    int linhas = 1;

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
        
        linhas ++;
    }
 
    fclose(arquivo);
    return 0;
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