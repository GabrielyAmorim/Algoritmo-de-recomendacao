import nosso_solver
import leitura_arquivo as leitura
import click

#exemplo de execução: python main.py dados/dados/dados_venda_cluster_17.csv --modo 3 --opcao 3 --cliente 5 --numero-produtos 5


@click.command()
@click.argument('arquivo_csv', type=click.Path(exists=True))
@click.option('-m', '--modo',
              type=click.IntRange(1, 3),
              default=3,
              help='Modo de execução:\n\b\n1- Lenta\n2- Rápida\n3- CSR',
              )
@click.option('-o', '--opcao',
              type=click.IntRange(1, 3),
              default=1,
              help='Tipo de ação que deseja executar \n\b\n1- Exibir lista\n2- Procurar cliente mais similar\n3- Recomendar produtos.'
              )
@click.option('--cliente',
              type=int,
              default=-1,
              help='Índice do cliente (exclusivo para opcao 2/3)'
              )
@click.option('-p', '--numero-produtos',
              type=int,
              default=-1,
              help='Quantidade de produtos a serem exibidos (exclusivo para opcao 3)'
              )

def main(arquivo_csv, modo, opcao, cliente, numero_produtos):
    """Algorítmo que recebe um ARQUIVO_CSV e retorna recomendações de produtos baseado no histórico de compras."""
    #caminho_arquivo = "dados/dados/dados_venda_cluster_17.csv"

    codigo_clientes = []
    mapa_clientes = {}
    nome_produtos = []
    mapa_produtos = {}
    compras = []

    codigo_clientes, mapa_clientes, nome_produtos, mapa_produtos, compras = leitura.ler_dados(arquivo_csv)

    nosso_solver.recomendar(codigo_clientes, mapa_clientes, nome_produtos, mapa_produtos, compras, modo, opcao, cliente, numero_produtos)

if __name__ == "__main__":
    main()