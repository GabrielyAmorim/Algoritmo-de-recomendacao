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
    int produto;
    char nome[200];

    fscanf(arquivo, "%*[^\n]");

    int linhas = 1;
    while (fscanf(arquivo, " %8[^,],%19[^,],%d,%199[^\r\n]", data, cliente, &produto, nome) == 4){
        int indiceCliente;
    }
 
    fclose(arquivo);
    return 0;
}