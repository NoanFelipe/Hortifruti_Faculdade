#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <string>
#include <vector>
#include "json.hpp"
#include "produto.h"
using json = nlohmann::json;

using namespace std;

// Funcões para manipulacão de produtos em JSON
json produtoParaJson(const Produto& prod);
Produto jsonParaProduto(const json& j);
void criarArquivoSeNaoExistir(const string& nomeArquivo);
vector<Produto> lerProdutosDoArquivo(const string& nomeArquivo);
void adicionarProdutoNoArquivo(const string& nomeArquivo, const Produto& novoProduto);
void removerProdutoNoArquivo(const string& nomeArquivo, size_t posicao);

#endif // PRODUTOS_H