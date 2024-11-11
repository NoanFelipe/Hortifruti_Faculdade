#ifndef PRODUTO_H
#define PRODUTO_H
using namespace std;

struct produto {
    string nome;
    int tipo;
    double qtde_peso;
    double preco;
};

typedef struct produto Produto;

Produto lerProduto(string m);
Produto lerProdutoKg(string m);
Produto lerProdutoParaJson(string m, int tipo);
void printProduto(Produto prod);
void printProdutoCompleto(Produto prod);
#endif // PRODUTO_H