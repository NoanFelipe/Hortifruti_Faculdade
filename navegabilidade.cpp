#include <iostream>
using namespace std;

void limpaTela() {
    fflush(stdin);
    cout << "Digite 'ENTER' para continuar...\n";
    getchar();
    system("cls");
}

int lerOpc() {
    int opc;
    //imprimir menu
    cout << "\a";
    cout << "*****************************************\n";
    cout << "|        Quintandinha do seu Z�        |\n";
    cout << "*****************************************\n";
    cout << " Digite a op��o desejada:\n";
    cout << " 1. Ler pr�ximo produto\n";
    cout << " 2. Finalizar compra\n";
    cout << " 3. Cancelar compra\n";
    cout << "*****************************************\n";
    cout << "Op��o:";
    //ler op��o
    cin >> opc;
    return opc;
}
