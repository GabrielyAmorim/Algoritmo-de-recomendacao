from pathlib import Path
import pandas as pd
import nosso_solver


def ler_dados(caminho_arquivo: str):
    caminho = Path(caminho_arquivo)

    dados = pd.read_csv(caminho)

    registros = []

    for i in range(len(dados)):

        cliente = str(dados["COD_CLIENTE"][i])
        produto = str(dados["NOME_PRODUTO"][i])

        registros.append([cliente, produto])

    return registros 

def main():

    caminho_arquivo = "dados/dados/dados_venda_cluster_17.csv"

    dados = ler_dados(caminho_arquivo)

    nosso_solver.cria_lista_compras(dados)

    nosso_solver.exibir_lista_compras()

    nosso_solver.calcular_similaridades()

    indice_cliente = int(input("\nDigite o indice do cliente: "))

    nosso_solver.encontra_similares(indice_cliente)

if __name__ == "__main__":
    main()
