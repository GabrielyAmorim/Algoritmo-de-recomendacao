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

        criaMatrizCompras(&lista, n_clientes, n_produtos);

        if(modo == 1){
            calculaInterseccaoLenta(&lista, &simi, n_clientes, n_produtos);
        }
        else{
            calculaInterseccaoRapida(&lista, &simi, n_clientes, n_produtos);
        }

        calculaSimilaridade(&lista, &simi, n_clientes);
    }

    else{

        criaCSRMatrizCompras(&lista);

        calculaInterseccaoCSR(&lista, &simi);

        calculaSimilaridadeCSR(&lista, &simi);
    }
    
    clock_t fim = clock();
    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;

    switch(opcao){

        case 1:

            exibeLista(&lista);
            break;

        case 2:

            if(modo == 3){
                encontraSimilaresCSR(&simi, n_clientes, atoi(argv[4]));
            }
            else{
                encontraSimilares(&simi, n_clientes, atoi(argv[4]));
            }
            
            break;

        case 3:

            if(modo == 3){
                recomendarProdutoCSR(&lista, &simi, n_clientes, n_produtos, atoi(argv[4]), atoi(argv[5]));
            }
            else{
                recomendarProduto(&lista, &simi, n_clientes, n_produtos, atoi(argv[4]), atoi(argv[5]));
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