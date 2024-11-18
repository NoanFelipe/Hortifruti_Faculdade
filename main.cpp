#include <iostream>
#include <locale.h>
#include "navegabilidade.h"
#include "tipos.cpp"
#include "produto.h"
#include "algorithm"
#include "JsonProductReader.h"
using namespace std;

#define MAX 200
#define JsonFileName "Produtos"

using namespace std;

void exibirMenuAlterarProdutos()
{
    cout << "Digite a opcão desejada:\n";
    cout << " 1. Adicionar produto à lista\n";
    cout << " 2. Remover produto da lista\n";
    cout << " 3. Voltar\n";
    cout << "*******************************\n";
    cout << "Opcão: ";
}

void exibirMenuProdutos() {
    cout << "Digite a opcão desejada:\n";
    cout << " 1. Por unidade\n";
    cout << " 2. Por peso\n";
    cout << " 3. Voltar\n";
    cout << "*******************************\n";
    cout << "Opcão: ";
}

void exibirMenuPagamento() {
    cout << "Digite a opcão desejada:\n";
    cout << " 1. Pagamento à vista (15% de desc.)\n";
    cout << " 2. Pagamento à prazo\n";
    cout << " 3. Ver produtos no carrinho\n";
    cout << " 4. Voltar\n";
    cout << "*******************************\n";
    cout << "Opcão: ";
}

void exibirMenuEscolhaProdutos()
{
    cout << "Digite a opcão desejada:\n";
    cout << " 1. Escolher produto:\n";
    cout << " 2. Voltar\n";
    cout << "*******************************\n";
    cout << "Opcão: ";
}

void printProdutos(vector<Produto>& produtos)
{
    for (int i = 0; i < produtos.size(); i++)
    {
        cout << "ID do produto: " << i << "\n";
        printProduto(produtos[i]);
        cout << endl;
    }
}

// Calcula o preco total da sua compra atual
// Faz isso loopando pelo array de produtos e adicionando ao total a multiplicacão do preco do produto e a quantidade ou peso do produto
double calcularPrecoTotal(Produto compras[], int* pQtd)
{
    double totalP = 0;
    for (int i = 0; i < *pQtd; i++)
    {
        totalP += compras[i].preco * compras[i].qtde_peso;
    }
    return totalP;
}

void printCompras(Produto(&compras)[MAX], int* pQtd)
{
    cout << "Produtos comprados: \n\n";
    cout << "Valor total: R$" << calcularPrecoTotal(compras, pQtd) << endl << endl;

    for (int i = 0; i < *pQtd; i++)
    {
        cout << "*******************************\n";
        printProdutoCompleto(compras[i]);
        cout << "*******************************\n";
        cout << endl;
    }
}

Produto escolherProduto(vector<Produto> produtos)
{
    int opt;
    Produto prod;
    double qtde_peso = 0;

    do 
    {
        cout << "Escolha o produto por id: ";
        cin >> opt;
    } while (!(opt >= 0 && opt < produtos.size()));
    prod = produtos[opt];
    
    while (true) {
        if (prod.tipo == UNT)
        {
            cout << "Quantidade: ";
        }
        else if (prod.tipo == PESO)
        {
            cout << "Peso: ";
        }
        cin >> qtde_peso;

        if (qtde_peso > 0) {
            break;
        }
        else {
            cout << "Leitura inválida!\n";
        }
    }
    
    prod.qtde_peso = qtde_peso;

    return prod;
}

void lerProdutos(Produto(&compras)[MAX], int* pQtd)
{
    Produto prod;
    vector<Produto> produtos = lerProdutosDoArquivo(JsonFileName);
    int opt = 0;

    do 
    {
        exibirMenuEscolhaProdutos();
        cin >> opt;
        if (opt == 1)
        {
            printProdutos(produtos);
            compras[*pQtd] = escolherProduto(produtos);
            (*pQtd)++;
        }
        limparTela(true);
    } 
    while (opt != 2);
}

// Anula todos os valores de um vetor de Produtos
// Para que quando o pagamento seja efetuado, os produtos que você adicionou na compra anterior não afetem o preço da sua próxima compra
// A função fill preenche o array com um novo produto vazio, o primeiro argumento é o primeiro valor do array, o segundo é o ultimo valor do array, e o terceiro é o valor que preencherá o array
void resetarVetorProdutos(Produto(&compras)[MAX], int* pQtd)
{
    fill(begin(compras), end(compras), Produto());
    (*pQtd) = 0;
}

void processarPagamento(Produto(&compras)[MAX], int *pQtd, double totalCompra) {
    int opcPgto;
    do {
        cout << "Total da compra: R$" << totalCompra << "\n";
        exibirMenuPagamento();
        cin >> opcPgto;

        switch (opcPgto)
        {
        case 1:
            cout << "Total à vista: R$ " << (totalCompra * 0.85) << "\n";
            cout << "Compra finalizada!\n";
            limparTela(false);
            resetarVetorProdutos(compras, pQtd);
            break;
        case 2: 
            int numParcelas;
            cout << "Número de parcelas: ";
            while (!(cin >> numParcelas) || numParcelas <= 0) {
                cout << "Leitura inválida! Tente novamente.\nNúmero de parcelas: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Total à prazo: " << numParcelas << " x de R$ " << (totalCompra / numParcelas) << "\n";
            cout << "Compra finalizada!\n";
            limparTela(false);
            resetarVetorProdutos(compras, pQtd);
            break;
        case 3:
            limparTela(true);
            printCompras(compras, pQtd);
            limparTela(true);
            break;
        case 4:
            cout << "Cancelando operação...\n";
            limparTela(true);
            break;
        default:
            cout << "Opcão inválida!\n";
            break;
        }
    } while (opcPgto != 1 && opcPgto != 2 && opcPgto != 4);
}

void adicionarProduto()
{
    limparTela(true);
    int opcProd;
    do {
        exibirMenuProdutos();
        cin >> opcProd;

        switch (opcProd) {
        case 1:
            adicionarProdutoNoArquivo(JsonFileName, lerProdutoParaJson("Produto adicionado ao banco de dados...", opcProd));
            break;
        case 2: {
            adicionarProdutoNoArquivo(JsonFileName, lerProdutoParaJson("Produto adicionado ao banco de dados...", opcProd));
            break;
        }
        case 3:
            cout << "Cancelando operacão...\n";
            break;
        default:
            cout << "Opcão inválida!\n";
            break;
        }
    } while (opcProd != 3);

    limparTela(true);
}

void removerProduto()
{
    int removeI = 0;
    vector<Produto> produtos;
    while (true)
    {
        limparTela(false);
        produtos = lerProdutosDoArquivo(JsonFileName);
        printProdutos(produtos);
        cout << "Informe o ID do produto à ser removido (-1 para voltar): ";
        cin >> removeI;
        if (removeI >= 0 && removeI < produtos.size())
            removerProdutoNoArquivo(JsonFileName, removeI);
        else if (removeI == -1) break;
        else
        {
            cout << "Opção inválida." << endl << endl;
        }
    }

    limparTela(true);
}

void alterarProdutos()
{
    int opt = 0;

    do
    {
        exibirMenuAlterarProdutos();
        cin >> opt;
        if (opt == 1)
        {
            adicionarProduto();
        }
        else if (opt == 2)
        {
            removerProduto();
        }
    } while (opt != 3);
    limparTela(true);
}

void Setup()
{
    setlocale(LC_ALL, "");
    criarArquivoSeNaoExistir(JsonFileName);
}

void MenuPrincipal()
{
    Setup();

    Produto compras[MAX];
    int qtd = 0;
    double totalCompra = 0;
    int opc;
    do {
        opc = lerOpc();

        switch (opc) {
        case 1:
            limparTela(false);
            lerProdutos(compras, &qtd);
            break;
        case 2:
            limparTela(true);
            totalCompra = calcularPrecoTotal(compras, &qtd);
            if (totalCompra > 0)
                processarPagamento(compras, &qtd, totalCompra);
            else
            {
                cout << "**********************************************************************************\n";
                cout << "Voce não tem nenhum produto no carrinho, a compra não pode ser finalizada!\n";
                cout << "**********************************************************************************\n";
                limparTela(false);
            }
            break;
        case 3:
            cout << "Compra Cancelada\n";
            break;
        case 4:
            alterarProdutos();
            break;
        default:
            cout << "Opcão Inválida!\n";
            break;
        }
    } while (opc != 3);

    cout << "Obrigado e Volte Sempre...\n";
}

int main() 
{
    MenuPrincipal();
    return 0;
}