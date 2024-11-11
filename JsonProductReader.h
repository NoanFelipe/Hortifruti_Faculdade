#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <string>
#include <vector>
#include "json.hpp"
#include "produto.h"
using json = nlohmann::json;

using namespace std;

// Fun��es para manipula��o de produtos em JSON
json produtoParaJson(const Produto& prod);
Produto jsonParaProduto(const json& j);
void criarArquivoSeNaoExistir(const string& nomeArquivo);
vector<Produto> lerProdutosDoArquivo(const string& nomeArquivo);
void adicionarProdutoNoArquivo(const string& nomeArquivo, const Produto& novoProduto);

#endif // PRODUTOS_H