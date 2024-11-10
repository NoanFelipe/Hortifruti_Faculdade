#include <iostream>
#include <locale.h>
#include "navegabilidade.h"
#include "Tipos.cpp"
#include "Produto.h"

#define MAX 200;

using namespace std;

#define TRUE 1
#define FALSE 0

void lerProdutos(Produtos compras[], int* pQtd) {
    //l?gica para ler prox produto
    int opcProd;
    do {
        cout << "Digite a opção deseja:\n";
        cout << " 1. Por unidade\n";
        cout << " 2. por peso \n";
        cout << " 3. Voltar \n";

        cout << "*******************************\n";
        cout << "Opção:";
        cin >> opcProd;

        switch (opcProd) {
        case 1: {
            compras[*pQtd*] = lerProdUnt();
            (*pQtd)++;

            break;
        }case 2: {
            //l?gica por kg
            double peso;
            double precoKg;
            while (TRUE) {
                cout << "Peso:";
                cin >> peso;
                if (peso > 0) {
                    break;
                }
                else {
                    cout << "Leitura inv?lida!\n";
                }
            }
            while (TRUE) {
                cout << "Pre?o por kilo:";
                cin >> precoKg;
                if (precoKg > 0) {
                    break;
                }
                else {
                    cout << "Leitura inv?lida!\n";
                }
            }
            double custoProd;
            custoProd = peso * precoKg;
            totalCompra = totalCompra + custoProd;
            cout << "Total parcial: R$ " << totalCompra << "\n";
            cout << "Produto cadastrado na compra...\n";
            fflush(stdin);
            cout << "Digite 'ENTER' para continuar...\n";
            getchar();
            system("cls");
            break;
        }case 3: {
            cout << "cancelando operação...\n";
            fflush(stdin);
            cout << "Digite 'ENTER' para continuar...\n";
            getchar();
            system("cls");
            break;
        }default: {
            cout << "Opção inválida!";
        }
        }

    } while (opcProd != 1 && opcProd != 2 && opcProd != 3);
    limpaTela();

}

int main()
{
    Produtos compras[MAX];
    int qtd = 0;
    //ajusdar a acentuação
    setlocale(LC_ALL, "");
    //ler uma opção em loop at? que seja 3 (sai do programa)
    int opc;
    double totalCompra = 0;
    do {
        opc = lerOpc();

        switch (opc) {
        case 1: {
            lerProdutos(compras, &qtd);
            break;
        }case 2: {
            int opcPgto;
            do {
                cout << "Total da compra: R$" << totalCompra << "\n";
                cout << "Digite a opção deseja:\n";
                cout << " 1. Pagamento à vista (15% de desc.)\n";
                cout << " 2. Pagamento à prazo \n";
                cout << " 3. Voltar \n";
                cout << "*******************************\n";
                cout << "Opção:";
                cin >> opcPgto;

                switch (opcPgto) {
                case 1: {
                    cout << "Total à vista: R$ " << (totalCompra * 0.85) << "\n";
                    cout << "Compra finalizada! \n";
                    fflush(stdin);
                    cout << "Digite 'ENTER' para continuar...\n";
                    getchar();
                    system("cls");
                    opc = 3;
                    break;
                }case 2: {
                    int numParcelas;
                    while (TRUE) {
                        cout << "Número de parcelas:";
                        cin >> numParcelas;
                        if (numParcelas > 0) {
                            break;
                        }
                        else {
                            cout << "Leitura inválida!\n";
                        }
                    }
                    cout << "Total ? prazo: " << numParcelas << " x de R$ " << (totalCompra / numParcelas) << "\n";
                    cout << "Compra finalizada! \n";
                    fflush(stdin);
                    cout << "Digite 'ENTER' para continuar...\n";
                    getchar();
                    system("cls");
                    opc = 3;
                    break;
                }case 3: {
                    cout << "cancelando opera??o...\n";
                    fflush(stdin);
                    cout << "Digite 'ENTER' para continuar...\n";
                    getchar();
                    system("cls");
                    break;
                }default: {
                    cout << "Op??o inv?lida!\n";
                }
                }
            } while (opcPgto <= 0 || opcPgto >= 4);
            break;
        }case 3: {
            cout << "Cancelar compra\n";
            cout << "cancelando operação...\n";
            limpaTela();
            ;                break;
        }default: {
            cout << "Opção Inválida!\n";
        }
        }

    } while (opc != 3);
    cout << "Obrigado e Volte Sempre..." << endl;
    return 0;
}