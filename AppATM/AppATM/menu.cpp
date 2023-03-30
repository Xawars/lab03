#include <iostream>
#include "menu.h"

using namespace std;

void showMainMenu() {
    cout << "======================================\n";
    cout << "========= ATM MANAGEMENT SYSTEM ======\n";
    cout << "======================================\n\n";
    cout << "1. Registrar usuario (Administrador)\n";
    cout << "2. Ingresar como usuario\n";
    cout << "3. Salir\n";
    cout << "\nSeleccione una opción: ";
}

void showUserMenu() {
    cout << "======================================\n";
    cout << "=========== USER OPERATIONS ==========\n";
    cout << "======================================\n\n";
    cout << "1. Consultar saldo\n";
    cout << "2. Retirar dinero\n";
    cout << "3. Salir\n";
    cout << "\nSeleccione una opción: ";
}
