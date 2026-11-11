#include "listaCompras.h"
#include <stdio.h>

int lerArquivo(int argc, char *argv[]){
   
    if (argc != 2) {
        printf("Uso: %s <arquivo.csv>\n", argv[0]);
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char data[9];
    char cliente[20];
    int produto;
    char nome[200];

    fscanf(arquivo, "%*[^\n]");

    fscanf(arquivo, " %8[^,],%19[^,],%d,%199[^\r\n]", data, cliente, &produto, nome);
 
    fclose(arquivo);
    return 0;
}