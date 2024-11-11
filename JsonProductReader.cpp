#include "JsonProductReader.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

// Converte Produto para JSON
json produtoParaJson(const Produto& prod) {
    return json{ {"nome", prod.nome}, {"tipo", prod.tipo}, {"qtde_peso", prod.qtde_peso}, {"preco", prod.preco} };
}

// Converte JSON para Produto
Produto jsonParaProduto(const json& j) {
    return Produto{
        j.at("nome").get<string>(),
        j.at("tipo").get<int>(),
        j.at("qtde_peso").get<double>(),
        j.at("preco").get<double>()
    };
}

// Cria o arquivo JSON vazio caso ele não exista
void criarArquivoSeNaoExistir(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.good()) { // Verifica se o arquivo não existe ou não pode ser lido
        ofstream novoArquivo(nomeArquivo);
        novoArquivo << "[]"; // Escreve um array JSON vazio
        novoArquivo.close();
        cout << "Arquivo " << nomeArquivo << " criado com sucesso.\n";
    }
    arquivo.close();
}

// Lê produtos do arquivo JSON e os armazena em um vector<Produto>
vector<Produto> lerProdutosDoArquivo(const string& nomeArquivo)
{
    ifstream arquivo(nomeArquivo);
    vector<Produto> produtos;

    if (arquivo.is_open()) {
        json j;
        arquivo >> j;

        for (const auto& item : j) {
            produtos.push_back(jsonParaProduto(item));
        }
        arquivo.close();
    }
    else {
        cout << "Erro ao abrir o arquivo para leitura.\n";
    }
    return produtos;
}

// Adiciona um novo produto ao arquivo JSON
void adicionarProdutoNoArquivo(const string& nomeArquivo, const Produto& novoProduto) {
    vector<Produto> produtos = lerProdutosDoArquivo(nomeArquivo);
    produtos.push_back(novoProduto);

    ofstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        json j = json::array();

        for (const auto& prod : produtos) {
            j.push_back(produtoParaJson(prod));
        }

        arquivo << j.dump(4); // "4" define uma indentação para facilitar a leitura
        arquivo.close();
    }
    else {
        cout << "Erro ao abrir o arquivo para escrita.\n";
    }
}
