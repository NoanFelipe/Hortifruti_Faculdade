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
        cout << "Digite a op��o deseja:\n";
        cout << " 1. Por unidade\n";
        cout << " 2. por peso \n";
        cout << " 3. Voltar \n";

        cout << "*******************************\n";
        cout << "Op��o:";
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
            cout << "cancelando opera��o...\n";
            fflush(stdin);
            cout << "Digite 'ENTER' para continuar...\n";
            getchar();
            system("cls");
            break;
        }default: {
            cout << "Op��o inv�lida!";
        }
        }

    } while (opcProd != 1 && opcProd != 2 && opcProd != 3);
    limpaTela();

}

int main()
{
    Produtos compras[MAX];
    int qtd = 0;
    //ajusdar a acentua��o
    setlocale(LC_ALL, "");
    //ler uma op��o em loop at? que seja 3 (sai do programa)
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
                cout << "Digite a op��o deseja:\n";
                cout << " 1. Pagamento � vista (15% de desc.)\n";
                cout << " 2. Pagamento � prazo \n";
                cout << " 3. Voltar \n";
                cout << "*******************************\n";
                cout << "Op��o:";
                cin >> opcPgto;

                switch (opcPgto) {
                case 1: {
                    cout << "Total � vista: R$ " << (totalCompra * 0.85) << "\n";
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
                        cout << "N�mero de parcelas:";
                        cin >> numParcelas;
                        if (numParcelas > 0) {
                            break;
                        }
                        else {
                            cout << "Leitura inv�lida!\n";
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
            cout << "cancelando opera��o...\n";
            limpaTela();
            ;                break;
        }default: {
            cout << "Op��o Inv�lida!\n";
        }
        }

    } while (opc != 3);
    cout << "Obrigado e Volte Sempre..." << endl;
    return 0;
}