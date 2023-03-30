#include <iostream>
#include <fstream>
#include "user.h"
#include "menu.h"
#include "utils.h"

using namespace std;

void runATMManagementSystem();

int main() {
    runATMManagementSystem();
    return 0;
}

void runATMManagementSystem() {
    string encryptedKey;
    ifstream sudoFile("sudo.txt");

    if (!sudoFile) {
        cerr << "Error: No fue posible abrir el archivo sudo.txt." << endl;
        return;
    }

    getline(sudoFile, encryptedKey);
    sudoFile.close();

    int choice;
    do {
        showMainMenu();
        cin >> choice;

        if (choice == 1) {
            cout << "Ingrese la clave de administrador: ";
            string inputKey;
            cin >> inputKey;

            if (checkAdminAccess(inputKey, encryptedKey)) {
                clearScreen();
                cout << "Acceso concedido! Eres el administrador." << endl;
                registerUser();
            } else {
                clearScreen();
                cout << "\nAcceso denegado! La clave encriptada es inválida.\n"
                     << endl;
            }
        } else if (choice == 2) {
            string userID;
            if (userAccess(userID)) {
                clearScreen();
                cout << "\nAcceso concedido! Bienvenido, " << userID << ".\n"
                     << endl;
                userOperations(userID);
            } else {
                cout << "Acceso denegado! ID de usuario o contraseña "
                        "incorrectos." << endl;
            }
        } else if (choice == 3) {
            clearScreen();
            cout << "\nSaliendo..." << endl;
            pauseScreen();
        } else {
            cout << "Opción inválida. Intente de nuevo." << endl;
        }
    } while (choice != 3);
}
