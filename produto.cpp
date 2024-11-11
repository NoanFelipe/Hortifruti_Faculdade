#include <iostream>
#include <string>
#include "produto.h"
#include "navegabilidade.h"
#include "tipos.cpp"

Produto lerProduto(string m) {
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
    cout << m << "\n";
    limparTela();
    return prod;
}

Produto lerProdutoKg(string m)
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

    cout << m << "\n";
    limparTela();

    return prod;
}

Produto lerProdutoParaJson(string m, int tipo) //int tipo só pode ser 1 ou 2
{
    Produto prod;
    string nome;
    double precoUnt;

    fflush(stdin);
    getline(cin, nome);
    cout << "Nome do produto: ";
    cin >> nome;

    while (true) {
        if (tipo == UNT)
        {
            cout << "Preço unitário: R$";
        }
        else if (tipo == PESO)
        {
            cout << "Preço por kilo: R$";
        }
        cin >> precoUnt;
        if (precoUnt > 0) {
            break;
        }
        else {
            cout << "Leitura inválida!\n";
        }
    }
    
    prod.nome = nome;
    prod.tipo = tipo;
    prod.preco = precoUnt;
    prod.qtde_peso = 0;
    cout << m << "\n";
    limparTela();
    return prod;
}

void printProduto(Produto prod) {
    if (prod.tipo == UNT) {
        cout << "Nome:" << prod.nome << endl;
        cout << "Preço unitário: R$" << prod.preco << endl;
    }
    else {
        cout << "Nome:" << prod.nome << endl;
        cout << "Preço por quilo: R$" << prod.preco << endl;
    }
}

void printProdutoCompleto(Produto prod) 
{
    cout << "Nome:" << prod.nome << endl;
    if (prod.tipo == UNT) {
        cout << "Preço unitário: R$" << prod.preco << endl;
        cout << "Quantidade: " << prod.qtde_peso << endl;
    }
    else 
    {
        cout << "Preço por quilo: R$" << prod.preco << endl;
        cout << "Peso: " << prod.qtde_peso << endl;
    }
    cout << "Preço total: R$" << prod.qtde_peso * prod.preco << endl;
}

