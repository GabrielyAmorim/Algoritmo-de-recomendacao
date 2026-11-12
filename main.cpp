#include "listaCompras.h"
#include "similaridade.h"
#include "recomendacao.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

    if(argc != 2){
        printf("Uso: %s <arquivo.csv>\n", argv[0]);
        return 1;
    }

    ListaCompras lista;

    if(lerArquivo(&lista, argv[1]) != 0){
        return 1;
    }

    int opcao;

    printf("Escolha o modulo de interesse:\n");
    printf("1 - Lista de Compras\n");
    printf("2 - Similaridade\n");
    printf("3 - Recomendacao\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch(opcao){

        case 1:
            exibeLista(&lista);
            break;

        case 2:
            // NO PROCESSO
            break;

        case 3:
            // FALTA
            break;

        default:
            printf("Opcao invalida.\n");
    }

    return 0;
}