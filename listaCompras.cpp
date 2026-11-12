#include "listaCompras.h"
#include <stdio.h>

int lerArquivo(ListaCompras *lista, char *nomeArquivo){

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

    while(fscanf(arquivo, " %8[^,],%19[^,],d,%199[^\r\n]", data, cliente, &produto, nome) == 4){
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

        linhas ++;
    }
 
    fclose(arquivo);
    return 0;
}