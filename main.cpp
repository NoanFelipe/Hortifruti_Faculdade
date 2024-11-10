#include <iostream>
#include <locale.h>
#include "navegabilidade.h"
#include "Tipos.cpp"
#include "Produto.h"

#define MAX 200

using namespace std;

void exibirMenuProdutos() {
    cout << "Digite a opção desejada:\n";
    cout << " 1. Por unidade\n";
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

void lerProdutos(Produto compras[], int* pQtd, double& totalCompra) {
    int opcProd;
    do {
        exibirMenuProdutos();
        cin >> opcProd;

        switch (opcProd) {
        case 1:
            compras[*pQtd] = lerProduto();
            (*pQtd)++;
            break;
        case 2: {
            compras[*pQtd] = lerProdutoKg();
            (*pQtd)++;
            break;
        }
        case 3:
            cout << "Cancelando operação...\n";
            cin.ignore();
            cout << "Digite 'ENTER' para continuar...\n";
            getchar();
            system("cls");
            break;
        default:
            cout << "Opção inválida!\n";
            break;
        }
    } while (opcProd != 3);
    limpaTela();
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
            cin.ignore();
            cout << "Digite 'ENTER' para continuar...\n";
            getchar();
            system("cls");
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
            cin.ignore();
            cout << "Digite 'ENTER' para continuar...\n";
            getchar();
            system("cls");
            break;
        }
        case 3:
            cout << "Cancelando operação...\n";
            cin.ignore();
            cout << "Digite 'ENTER' para continuar...\n";
            getchar();
            system("cls");
            break;
        default:
            cout << "Opção inválida!\n";
            break;
        }
    } while (opcPgto != 1 && opcPgto != 2 && opcPgto != 3);
}

int main() {
    Produto compras[MAX];
    int qtd = 0;
    double totalCompra = 0;

    setlocale(LC_ALL, "");

    int opc;
    do {
        opc = lerOpc();

        switch (opc) {
        case 1:
            lerProdutos(compras, &qtd, totalCompra);
            break;
        case 2:
            processarPagamento(totalCompra);
            break;
        case 3:
            cout << "Cancelar compra\n";
            limpaTela();
            break;
        default:
            cout << "Opção Inválida!\n";
            break;
        }
    } while (opc != 3);

    cout << "Obrigado e Volte Sempre...\n";
    return 0;
}