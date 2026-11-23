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
    printf("modo 1 = Versao mais lenta\n");
    printf("modo 2 = Versao media\n");
    printf("modo 3 = Versão mais rapida (CSR)\n");
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

    clock_t inicio = clock();

    int n_clientes = lista.codigoClientes.size();
    int n_produtos = lista.nomeProdutos.size();
    Similaridade simi;

    if (atoi(argv[2]) != 3){
        criaMatrizCompras(lista.compras, n_clientes, n_produtos, &lista.matrizCompras);

        if(atoi(argv[2]) == 1){
            calculaInterseccaoLenta(&simi.matrizInterseccao, lista.matrizCompras, n_clientes, n_produtos);
        }
        else if(atoi(argv[2]) == 2){
            calculaInterseccaoRapida(&simi.matrizInterseccao, lista.matrizCompras, n_clientes, n_produtos);
        } 
        else{
            mostraUso(argv[0]);
            return 1;
        }

        calculaSimilaridade(&simi.matrizSimilaridade, simi.matrizInterseccao, lista.compras, n_clientes);
    }
    else if (atoi(argv[2]) == 3){
        criaCSRMatrizCompras(lista.compras, n_produtos, lista.matrizComprasCSR.values, lista.matrizComprasCSR.col_index,
                             lista.matrizComprasCSR.row_ptr);

        calculaInterseccaoCSR(lista.matrizComprasCSR.values, lista.matrizComprasCSR.col_index, lista.matrizComprasCSR.row_ptr,
                              simi.matrizInterseccaoCSR.values, simi.matrizInterseccaoCSR.col_index, simi.matrizInterseccaoCSR.row_ptr);

        calculaSimilaridadeCSR(simi.matrizInterseccaoCSR.values, simi.matrizInterseccaoCSR.col_index, simi.matrizInterseccaoCSR.row_ptr,
                               lista.matrizComprasCSR.row_ptr, simi.matrizSimilaridadeCSR.values, simi.matrizSimilaridadeCSR.col_index,
                               simi.matrizSimilaridadeCSR.row_ptr);
    }
    else{
        mostraUso(argv[0]);
        return 1;
    }
    
    clock_t fim = clock();
    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;

    switch(opcao){

        case 1:
            exibeLista(lista.codigoClientes, lista.compras, lista.nomeProdutos);
            break;

        case 2:
            encontraSimilares(simi.matrizSimilaridade, n_clientes, atoi(argv[4]));
            break;

        case 3:
            recomendarProduto(lista.nomeProdutos, lista.compras, simi.matrizSimilaridade, n_clientes, 
                n_produtos, atoi(argv[4]), atoi(argv[5]));
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