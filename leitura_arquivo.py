from pathlib import Path
import pandas as pd
import nosso_solver


def ler_dados(caminho_arquivo: str):
    caminho = Path(caminho_arquivo)

    dados = pd.read_csv(caminho)

    codigo_clientes = []
    mapa_clientes = {}
    nome_produtos = []
    mapa_produtos = {}
    compras = []

    for i in range(len(dados)):

        cliente = str(dados["COD_CLIENTE"][i])
        produto = str(dados["NOME_PRODUTO"][i])

        if cliente in mapa_clientes:
            indice_cliente = mapa_clientes[cliente]

        else:
            indice_cliente = len(codigo_clientes)
            codigo_clientes.append(cliente)
            mapa_clientes[cliente] = indice_cliente
            compras.append([]) 

        if produto in mapa_produtos:
            indice_produto = mapa_produtos[produto] 

        else:
            indice_produto = len(nome_produtos)
            nome_produtos.append(produto) 
            mapa_produtos[produto] = indice_produto

        if indice_produto not in compras[indice_cliente]:
            compras[indice_cliente].append(indice_produto)

    return codigo_clientes, mapa_clientes, nome_produtos, mapa_produtos, compras                   