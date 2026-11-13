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

    criaMatrizCompras(&lista);

    Similaridade simi;

    calculaInterseccao(simi.matrizInterseccao, &lista);
    calculaSimilaridade(&simi, &lista);
    int cliente;

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

            printf("Digite o cliente desejado: ");
            scanf("%d", &cliente);

            encontraSimilares(&simi, &lista, cliente);
            break;

        case 3:
            // FALTA
            break;

        default:
            printf("Opcao invalida.\n");
    }

    for(int i = 0; i < lista.codigoClientes.size(); i++){
        free(simi.matrizInterseccao[i]);
        free(simi.matrizSimilaridade[i]);
        free(lista.matrizCompras[i]);
    }
    free(simi.matrizInterseccao);
    free(simi.matrizSimilaridade);
    free(lista.matrizCompras);

    return 0;
}