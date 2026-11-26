from pathlib import Path
import pandas as pd
import nosso_solver


def ler_dados(caminho_arquivo: str):
    caminho = Path(caminho_arquivo)

    dados = pd.read_csv(caminho)

    registros = []

    for i in range(len(dados)):
        registros.append((str(dados["COD_CLIENTE"][i]), str(dados["NOME_PRODUTO"][i])))

    return registros 

def main():

    caminho_arquivo = "dados_vendas_cluster17.csv"

    dados = ler_dados(caminho_arquivo)


if __name__ == "__main__":
    main()
