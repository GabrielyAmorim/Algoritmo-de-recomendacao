#include "listaCompras.h"
#include "similaridade.h"
#include "recomendacao.h"
#include <stdio.h>
#include <ctime>
#include "stdlib.h"
#include <vector>

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

    int modo = atoi(argv[2]);
    int opcao = atoi(argv[3]);

    if(modo < 1 || modo > 3){
        mostraUso(argv[0]);
        return 1;
    }

    if((opcao == 1 && argc != 4) || (opcao == 2 && argc != 5) || (opcao == 3 && argc != 6) || (opcao < 1 || opcao > 3)){
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

    if(modo != 3){

        criaMatrizCompras(lista.compras, n_clientes, n_produtos, &lista.matrizCompras);

        if(modo == 1){
            calculaInterseccaoLenta(&simi.matrizInterseccao, lista.matrizCompras, n_clientes, n_produtos);
        }
        else{
            calculaInterseccaoRapida(&simi.matrizInterseccao, lista.matrizCompras, n_clientes, n_produtos);
        }

        calculaSimilaridade(&simi.matrizSimilaridade, simi.matrizInterseccao, lista.compras, n_clientes);
    }

    else{

        criaCSRMatrizCompras(lista.compras, lista.matrizComprasCSR.values, lista.matrizComprasCSR.col_index,
                             lista.matrizComprasCSR.row_ptr);

        calculaInterseccaoCSR(lista.matrizComprasCSR.values, lista.matrizComprasCSR.col_index, lista.matrizComprasCSR.row_ptr,
                              simi.matrizInterseccaoCSR.values, simi.matrizInterseccaoCSR.col_index, simi.matrizInterseccaoCSR.row_ptr);

        calculaSimilaridadeCSR(simi.matrizInterseccaoCSR.values, simi.matrizInterseccaoCSR.col_index, simi.matrizInterseccaoCSR.row_ptr,
                               lista.matrizComprasCSR.row_ptr, simi.matrizSimilaridadeCSR.values, simi.matrizSimilaridadeCSR.col_index,
                               simi.matrizSimilaridadeCSR.row_ptr);
    }
    
    clock_t fim = clock();
    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;

    switch(opcao){

        case 1:

            exibeLista(lista.codigoClientes, lista.compras, lista.nomeProdutos);
            break;

        case 2:

            if(modo == 3){
                encontraSimilaresCSR(simi.matrizSimilaridadeCSR.values, simi.matrizSimilaridadeCSR.col_index,
                                    simi.matrizSimilaridadeCSR.row_ptr, n_clientes, atoi(argv[4]));
            }
            else{
                encontraSimilares(simi.matrizSimilaridade, n_clientes, atoi(argv[4]));
            }
            
            break;

        case 3:

            if(modo == 3){
                recomendarProdutoCSR(lista.nomeProdutos, lista.compras, simi.matrizSimilaridadeCSR.values,
                                    simi.matrizSimilaridadeCSR.col_index, simi.matrizSimilaridadeCSR.row_ptr, 
                                    n_clientes, n_produtos, atoi(argv[4]), atoi(argv[5]));
            }
            else{
                recomendarProduto(lista.nomeProdutos, lista.compras, simi.matrizSimilaridade, n_clientes, 
                                n_produtos, atoi(argv[4]), atoi(argv[5]));
            }

            break;
    }

    if(modo != 3){
        for(int i = 0; i < lista.codigoClientes.size(); i++){
            free(simi.matrizInterseccao[i]);
            free(simi.matrizSimilaridade[i]);
            free(lista.matrizCompras[i]);
        }
        free(simi.matrizInterseccao);
        free(simi.matrizSimilaridade);
        free(lista.matrizCompras);
    }    

    printf("%f", tempo);

    return 0;
}