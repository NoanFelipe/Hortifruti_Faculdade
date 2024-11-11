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
void printProduto(Produto prod);
#endif // PRODUTO_H