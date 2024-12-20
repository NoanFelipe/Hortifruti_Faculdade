﻿#include <iostream>
#include <string>
#include "produto.h"
#include "navegabilidade.h"
#include "tipos.cpp"

Produto lerProdutoParaJson(string m, int tipo) //int tipo só pode ser 1 ou 2
{
    Produto prod;
    string nome;
    double precoUnt;

    fflush(stdin);
    getline(cin, nome);
    cout << "Nome do produto (sem espaço): ";
    cin >> nome;

    while (true) {
        if (tipo == UNT)
        {
            cout << "Preco unitário: R$";
        }
        else if (tipo == PESO)
        {
            cout << "Preco por kilo: R$";
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
    limparTela(false);
    return prod;
}

void printProduto(Produto prod) {
    if (prod.tipo == UNT) {
        cout << "Nome: " << prod.nome << endl;
        cout << "Preco unitário: R$" << prod.preco << endl;
    }
    else {
        cout << "Nome: " << prod.nome << endl;
        cout << "Preco por quilo: R$" << prod.preco << endl;
    }
}

void printProdutoCompleto(Produto prod) 
{
    cout << "Nome: " << prod.nome << endl;
    if (prod.tipo == UNT) {
        cout << "Preco unitário: R$" << prod.preco << endl;
        cout << "Quantidade: " << prod.qtde_peso << endl;
    }
    else 
    {
        cout << "Preco por quilo: R$" << prod.preco << endl;
        cout << "Peso: " << prod.qtde_peso << endl;
    }
    cout << "Preco total: R$" << prod.qtde_peso * prod.preco << endl;
}

