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

void exibirMenuProdutos() {
    cout << "Digite a opção desejada:\n";
    cout << " 1. Por unidade\n";
    cout << " 2. Por peso\n";
    cout << " 3. Voltar\n";
    cout << "*******************************\n";
    cout << "Opção: ";
}

void exibirMenuAdicionarProdutos()
{
    cout << "O novo produto deve ser:\n";
    cout << " 1. Por unidade:\n";
    cout << " 2. Por peso\n";
    cout << " 3. Voltar\n";
    cout << "*******************************\n";
    cout << "Opção: ";
}

void exibirMenuPagamento() {
    cout << "Digite a opção desejada:\n";
    cout << " 1. Pagamento à vista (15% de desc.)\n";
    cout << " 2. Pagamento à prazo\n";
    cout << " 3. Ver produtos no carrinho\n";
    cout << " 4. Voltar\n";
    cout << "*******************************\n";
    cout << "Opção: ";
}

void exibirMenuEscolhaProdutos()
{
    cout << "Digite a opção desejada:\n";
    cout << " 1. Escolher produto:\n";
    cout << " 2. Voltar\n";
    cout << "*******************************\n";
    cout << "Opção: ";
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

void printCompras(Produto(&compras)[MAX], int* pQtd)
{
    for (int i = 0; i < *pQtd; i++)
    {
        cout << "Produtos comprados: \n\n";
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
        limparTela();
    } 
    while (opt != 2);
}

void processarPagamento(Produto(&compras)[MAX], int *pQtd, double totalCompra) {
    int opcPgto;
    do {
        cout << "Total da compra: R$" << totalCompra << "\n";
        exibirMenuPagamento();
        cin >> opcPgto;

        switch (opcPgto) {
        case 1:
            cout << "Total à vista: R$ " << (totalCompra * 0.85) << "\n";
            cout << "Compra finalizada!\n";
            limparTela();
            break;
        case 2: {
            int numParcelas;
            cout << "Número de parcelas: ";
            while (!(cin >> numParcelas) || numParcelas <= 0) {
                cout << "Leitura inválida! Tente novamente.\nNúmero de parcelas: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Total à prazo: " << numParcelas << " x de R$ " << (totalCompra / numParcelas) << "\n";
            cout << "Compra finalizada!\n";
            limparTela();
            break;
        }
        case 3:
            limparTela();
            printCompras(compras, pQtd);
            limparTela();
            break;
        case 4:
            cout << "Cancelando operação...\n";
            limparTela();
            break;
        default:
            cout << "Opção inválida!\n";
            break;
        }
    } while (!(opcPgto != 1 && opcPgto != 2 && opcPgto != 3));
}

// Calcula o preço total da sua compra atual
// Faz isso loopando pelo array de produtos e adicionando ao total a multiplicação do preço do produto e a quantidade ou peso do produto
double calcularPrecoTotal(Produto compras[], int* pQtd)
{
    double totalP = 0;
    for (int i = 0; i < *pQtd; i++)
    {
        totalP += compras[i].preco * compras[i].qtde_peso;
    }
    return totalP;
}

// Anula todos os valores de um vetor de Produtos
// Para que quando o pagamento seja efetuado, os produtos que você adicionou na compra anterior não afetem o preço da sua próxima compra
// A função fill preenche o array com um novo produto vazio, o primeiro argumento é o primeiro valor do array, o segundo é o ultimo valor do array, e o terceiro é o valor que preencherá o array
void resetarVetorProdutos(Produto(&compras)[MAX])
{
    fill(begin(compras), end(compras), Produto());
}

void alterarProdutos()
{
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
            cout << "Cancelando operação...\n";
            break;
        default:
            cout << "Opção inválida!\n";
            break;
        }
    } while (opcProd != 3);

    limparTela();
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
            limparTela();
            lerProdutos(compras, &qtd);
            break;
        case 2:
            limparTela();
            totalCompra = calcularPrecoTotal(compras, &qtd);
            processarPagamento(compras, &qtd, totalCompra);
            resetarVetorProdutos(compras);
            break;
        case 3:
            cout << "Compra Cancelada\n";
            break;
        case 4:
            alterarProdutos();
        default:
            cout << "Opção Inválida!\n";
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