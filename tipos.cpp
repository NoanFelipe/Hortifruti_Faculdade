#include <iostream>
using namespace std;
#define UNT 1
#define PESO 2

struct produto {
    string nome;
    int tipo;
    double qtde_peso;
    double preco;
};

typedef struct produto Produto;
