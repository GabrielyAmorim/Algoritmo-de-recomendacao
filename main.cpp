#include "listaCompras.h"
#include "similaridade.h"
#include "recomendacao.h"
#include <stdio.h>
#include <ctime>
#include "stdlib.h"

void mostraUso(const char *programa){
    printf("Uso:\n");
    printf("  %s <arquivo.csv> <modo> 1                    -> lista de compras\n", programa);
    printf("  %s <arquivo.csv> <modo> 2 <cliente>          -> cliente mais similar\n", programa);
    printf("  %s <arquivo.csv> <modo> 3 <cliente> <k>      -> k recomendacoes\n", programa);
}

int main(int argc, char *argv[]) {

    if(argc < 4){
        mostraUso(argv[0]);
        return 1;
    }

    int opcao = atoi(argv[3]);

    if((opcao == 2 && argc != 5) || (opcao == 3 && argc != 6)){
        mostraUso(argv[0]);
        return 1;
    }

    ListaCompras lista;

    if(lerArquivo(&lista, argv[1]) != 0){
        return 1;
    }

    criaMatrizCompras(&lista);

    clock_t inicio = clock();

    Similaridade simi;

    if(atoi(argv[2]) == 1){
        calculaInterseccaoLenta(&simi, &lista);
    }
    else if(atoi(argv[2]) == 2){
        calculaInterseccaoRapida(&simi, &lista);
    } else {
        mostraUso(argv[0]);
        return 1;
    }
    //else{
        //calculaIntersecHiperMegaRapido;
    //}
    
    calculaSimilaridade(&simi, &lista);

    
    clock_t fim = clock();
    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;

    switch(opcao){

        case 1:
            exibeLista(&lista);
            break;

        case 2:
            encontraSimilares(&simi, &lista, atoi(argv[4]));
            break;

        case 3:
            recomendarProduto(&lista, &simi, atoi(argv[4]), atoi(argv[5]));
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

    printf("%f", tempo);

    return 0;
}