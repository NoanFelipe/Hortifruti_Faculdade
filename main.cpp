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
    cout << " 3. Voltar\n";
    cout << "*******************************\n";
    cout << "Opção: ";
}

void lerProdutos(Produto compras[], int* pQtd) {
    int opcProd;
    do {
        exibirMenuProdutos();
        cin >> opcProd;

        switch (opcProd) {
        case 1:
            compras[*pQtd] = lerProduto("Produto cadastrado na compra...");
            (*pQtd)++;
            break;
        case 2: {
            compras[*pQtd] = lerProdutoKg("Produto cadastrado na compra...");
            (*pQtd)++;
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

void processarPagamento(double totalCompra) {
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
            cout << "Cancelando operação...\n";
            limparTela();
            break;
        default:
            cout << "Opção inválida!\n";
            break;
        }
    } while (opcPgto != 1 && opcPgto != 2 && opcPgto != 3);
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

void adicionarNovoProduto()
{
    int opcProd;
    do {
        exibirMenuProdutos();
        cin >> opcProd;

        switch (opcProd) {
        case 1:
            adicionarProdutoNoArquivo(JsonFileName, lerProduto("Produto adicionado ao banco de dados..."));
            break;
        case 2: {
            adicionarProdutoNoArquivo(JsonFileName, lerProdutoKg("Produto adicionado ao banco de dados..."));
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

int main() {
    Produto compras[MAX];
    int qtd = 0;
    double totalCompra = 0;

    setlocale(LC_ALL, "");
    criarArquivoSeNaoExistir(JsonFileName);

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
                processarPagamento(totalCompra);
                resetarVetorProdutos(compras);
                break;
            case 3:
                cout << "Compra Cancelada\n";
                break;
            case 4:
                limparTela();
                
            default:
                cout << "Opção Inválida!\n";
                break;
        }
    } while (opc != 3);

    cout << "Obrigado e Volte Sempre...\n";
    return 0;
}