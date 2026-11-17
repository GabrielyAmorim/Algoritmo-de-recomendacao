#include "listaCompras.h"
#include "similaridade.h"
#include "recomendacao.h"
#include <stdio.h>
#include "stdlib.h"

void mostraUso(const char *programa){
    printf("Uso:\n");
    printf("  %s <arquivo.csv> 1                    -> lista de compras\n", programa);
    printf("  %s <arquivo.csv> 2 <cliente>          -> cliente mais similar\n", programa);
    printf("  %s <arquivo.csv> 3 <cliente> <k>      -> k recomendacoes\n", programa);
}

int main(int argc, char *argv[]) {

    if(argc < 3){
        mostraUso(argv[0]);
        return 1;
    }

    int opcao = atoi(argv[2]);

    if((opcao == 2 && argc != 4) || (opcao == 3 && argc != 5)){
        mostraUso(argv[0]);
        return 1;
    }

    ListaCompras lista;

    if(lerArquivo(&lista, argv[1]) != 0){
        return 1;
    }

    criaMatrizCompras(&lista);

    Similaridade simi;

    calculaInterseccao(&simi, &lista);
    calculaSimilaridade(&simi, &lista);

    switch(opcao){

        case 1:
            exibeLista(&lista);
            break;

        case 2:
            encontraSimilares(&simi, &lista, atoi(argv[3]));
            break;

        case 3:
            recomendarProduto(&lista, &simi, atoi(argv[3]), atoi(argv[4]));
            break;

        default:
            printf("Opcao invalida.\n");
            mostraUso(argv[0]);
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