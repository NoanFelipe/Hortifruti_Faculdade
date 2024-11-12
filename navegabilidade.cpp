#include <iostream>
using namespace std;

void limparTela(bool rapido) {
    cin.ignore();
    if (!rapido)
    {
        cout << "Digite 'ENTER' para continuar...\n";
        getchar();
    }
    system("cls");
}

int lerOpc() {
    int opc;
    //imprimir menu
    cout << "\a";
    cout << "*****************************************\n";
    cout << "|        Quintandinha do seu Zé        |\n";
    cout << "*****************************************\n";
    cout << " Digite a opção desejada:\n";
    cout << " 1. Ler próximo produto\n";
    cout << " 2. Finalizar compra\n";
    cout << " 3. Cancelar compra\n";
    cout << " 4. Modificar banco de produtos\n";
    cout << "*****************************************\n";
    cout << "Opção: ";
    //ler opção
    cin >> opc;
    cout << endl;
    return opc;
}
