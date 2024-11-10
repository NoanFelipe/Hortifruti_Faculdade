#include <iostream>
#include <string>
#include "tipos.cpp"
#include "navegabilidade.h"
using namespace std;

produto lerProduto() {
    //lógica por unidade
    Produto prod;
    string nome;
    int qtde;
    double precoUnt;

    fflush(stdin);
    getline(cin, nome);
    cout << "Nome do produto: ";
    cin >> nome;

    while (true) {
        cout << "Quantidade:";
        cin >> qtde;
        if (qtde > 0) {
            break;
        }
        else {
            cout << "Leitura inválida!\n";
        }
    }
    while (true) {
        cout << "Preço unitário:";
        cin >> precoUnt;
        if (precoUnt > 0) {
            break;
        }
        else {
            cout << "Leitura inválida!\n";
        }
    }
    prod.nome = nome;
    prod.tipo = UNT;
    prod.qtde_peso = qtde;
    prod.preco = precoUnt;
    cout << "Produto cadastrado na compra...\n";
    limparTela();
    return prod;
}

produto lerProdutoKg()
{
    Produto prod;
    prod.tipo = PESO;

    fflush(stdin);
    getline(cin, prod.nome);

    cout << "Nome do produto: ";
    cin >> prod.nome;
    cout << "Peso: ";
    while (!(cin >> prod.qtde_peso) || prod.qtde_peso <= 0) {
        cout << "Leitura inválida! Tente novamente.\nPeso: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Preço por kilo: ";
    while (!(cin >> prod.preco) || prod.preco <= 0) {
        cout << "Leitura inválida! Tente novamente.\nPreço por kilo: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Produto cadastrado na compra...\n";
    limparTela();

    return prod;
}

void printProduto(Produto prod) {
    cout << "Produto cadastrado:\n";
    if (prod.tipo == UNT) {
        cout << "Nome:" << prod.nome << endl;
        cout << "Preço unitário" << prod.preco << endl;
        cout << "Qtde" << (int)prod.qtde_peso << endl;
    }
    else {
        cout << "Nome:" << prod.nome << endl;
        cout << "Preço por quilo:" << prod.preco << endl;
        cout << "Peso:" << (int)prod.qtde_peso << endl;
    }
}

