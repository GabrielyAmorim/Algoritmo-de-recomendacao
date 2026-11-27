# Algoritmo de Recomendação

Projeto desenvolvido para a disciplina de **Programação Estruturada**, da Universidade Federal da Paraíba (UFPB), durante o período letivo 2026.2.

**Discentes:**

- Gabriely Medeiros Amorim
- Guilherme de Andrade Bronzeado

## Sobre o projeto

O projeto consiste no desenvolvimento de um sistema de recomendação de produtos a partir do histórico de compras de clientes.

A implementação utiliza estruturas de dados e algoritmos desenvolvidos em C e C++, além de ferramentas da linguagem Python para leitura e organização dos dados e execução do sistema.

## Tecnologias utilizadas

- C++
- Python
- Pandas
- Click
- pybind11

## Funcionalidades

- Leitura e organização dos dados de compras.
- Construção de matrizes de compras.
- Cálculo de similaridade entre clientes utilizando o índice de Jaccard.
- Identificação de clientes similares.
- Recomendação de produtos com base na similaridade entre clientes.
- Implementação de estruturas de matrizes esparsas no formato CSR.
- Integração entre Python e C++ por meio de uma biblioteca compilada.

## Modos de execução

O sistema disponibiliza três modos de execução para o cálculo das similaridades entre clientes:

- **Modo 1 — Lento:** utiliza a abordagem de cálculo de interseção lenta, com a realização de cópia da matriz.
- **Modo 2 — Rápido:** utiliza a abordagem de cálculo de interseção rápida, sem a realização de cópia da matriz.
- **Modo 3 — CSR:** utiliza matrizes esparsas no formato CSR para o cálculo das interseções e similaridades.

## Opções de uso

O sistema oferece três opções de execução:

- **Opção 1 — Exibir lista:** exibe a lista de compras dos clientes.
- **Opção 2 — Procurar cliente mais similar:** identifica o cliente mais similar ao cliente selecionado.
- **Opção 3 — Recomendar produtos:** gera recomendações de produtos para o cliente selecionado, com possibilidade de definir a quantidade de produtos exibidos.
