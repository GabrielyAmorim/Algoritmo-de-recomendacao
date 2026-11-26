import nosso_solver
import leitura_arquivo as leitura

def main():
    caminho_arquivo = "dados/dados/dados_venda_cluster_17.csv"

    codigo_clientes = []
    mapa_clientes = {}
    nome_produtos = []
    mapa_produtos = {}
    compras = []

    codigo_clientes, mapa_clientes, nome_produtos, mapa_produtos, compras = leitura.ler_dados(caminho_arquivo)

    nosso_solver.recomendar(codigo_clientes, mapa_clientes, nome_produtos, mapa_produtos, compras)
                            # modo, opcao, vizinhos, cliente, k)

if __name__ == "__main__":
    main()