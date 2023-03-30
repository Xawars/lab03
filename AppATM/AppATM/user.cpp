#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include "user.h"
#include "encryption.h"
#include "utils.h"
#include "menu.h"

using namespace std;

bool checkAdminAccess(const string &inputKey, const string &encryptedKey) {
    string inputKeyBinary = stringToBinary(inputKey);
    return inputKeyBinary == encryptedKey;
}

bool isUserRegistered(const string &userID) {
    ifstream usersFile("users.txt");
    if (!usersFile) {
        cerr << "Error: No fue posible abrir el archivo users.txt!" << endl;
        return false;
    }

    string line;
    while (getline(usersFile, line)) {
        size_t idPos = line.find(',');
        if (userID == line.substr(0, idPos)) {
            usersFile.close();
            return true;
        }
    }

    usersFile.close();
    return false;
}

void registerUser() {
    string userID, password;
    double balance;

    cout << "Ingrese el ID del usuario: ";
    cin >> userID;

    if (!isUserIDValid(userID)) {
        cout << "\nEl ID de usuario solo puede contener números. "
                "Intente de nuevo!\n" << endl;
            return;
    }

    if (isUserRegistered(userID)) {
        cout << "\nEl usuario ya está registrado. Intente de nuevo!\n"
                 << endl;
        return;
    }

    cout << "Ingrese la contraseña del usuario: ";
            cin >> password;
    cout << "Ingrese el saldo inicial (en COP): ";
    cin >> balance;

    ofstream usersFile("users.txt", ios::app);

    if (!usersFile) {
        cerr << "Error: No fue posible abrir el archivo users.txt." << endl;
        return;
    }

    char key = 'Z';
    string encryptedPassword = xorEncrypyDecrypt(password, key);
    usersFile << fixed << setprecision(2);
    usersFile << userID << "," << encryptedPassword << "," << balance << endl;
    usersFile.close();

    clearScreen();
    cout << "\nUsuario registrado con éxito!.\n" << endl;
}

bool userAccess(string &userID) {
    string password, inputPassword;
    cout << "Ingrese el ID del usuario: ";
    cin >> userID;
    cout << "Ingrese la contraseña del usuario: ";
            cin >> inputPassword;

    ifstream usersFile("users.txt");
    if (!usersFile) {
        cerr << "Error: No fue posible abrir el archivo users.txt" << endl;
        return false;
    }

    string line;
    while (getline(usersFile, line)) {
        size_t idPos = line.find(',');
        size_t passPos = line.find(',', idPos + 1);
        char key = 'Z';
        string encryptedInputPassword = xorEncrypyDecrypt(inputPassword, key);
        if (userID == line.substr(0, idPos) &&
            encryptedInputPassword == line.substr(idPos + 1, passPos -
                                                                 idPos - 1)) {
            usersFile.close();
            return true;
        }
    }

    usersFile.close();
    return false;
}

void checkBalance(const string &userID) {
    map<string, double> userBalances;
    ifstream usersFile("users.txt");

    string line;
    while (getline(usersFile, line)) {
        size_t idPos = line.find(',');
        size_t passPos = line.find(',', idPos + 1);
        size_t balancePos = line.find(',', passPos + 1);
        userBalances[line.substr(0, idPos)] =
            stod(line.substr(passPos + 1, balancePos - passPos - 1));
    }

    clearScreen();
    cout << "\nSaldo actual: COP " << fixed << setprecision(2) <<
        userBalances[userID] << endl;

    applyOperationsCost(userID);
}

void withdrawMoney(const string &userID) {
    double amount;
    cout << "Ingrese la cantidad a retirar: ";
    cin >> amount;

    fstream usersFile("users.txt");
    ofstream tempFile("temp_users.txt");
    string line;
    bool success = false;

    while (getline(usersFile, line)) {
        size_t idPos = line.find(',');
        size_t passPos = line.find(',', idPos + 1);

        if (userID == line.substr(0, idPos)) {
            double currentBalance = stod
                (line.substr(passPos + 1));
            if (amount > currentBalance) {
                clearScreen();
                cout << "\nSaldo insuficiente. No se puede retirar COP " <<
                    fixed << setprecision(2) << amount << endl;
                tempFile << line << "\n" << endl;
            } else {
                currentBalance -= amount;
                string newLine = line.substr(0, passPos + 1) +
                                 to_string(currentBalance);
                tempFile << newLine << endl;
                usersFile << newLine;
                success = true;
                clearScreen();
                cout << "\nSe retiró COP " << fixed << setprecision(2) <<
                    amount << " exitosamente. Nuevo saldo: COP " <<
                        currentBalance << endl;
            }
        } else {
            tempFile << line << endl;
        }
    }
    usersFile.close();
    tempFile.close();

    if (success) {
        remove("users.txt");
        rename("temp_users.txt", "users.txt");
        applyOperationsCost(userID);
    } else {
        cout << "Error al retirar el dinero.\n" << endl;
    }
}

void userOperations(const string &userID) {
    int choice;
    do {
        showUserMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            checkBalance(userID);
            break;
        case 2:
            withdrawMoney(userID);
            break;
        case 3:
            clearScreen();
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente de nuevo." << endl;
                break;
        }
    } while (choice != 3);
}

void applyOperationsCost(const string &userID) {
    fstream usersFile("users.txt");
    ofstream tempFile("temp_users.txt");
    string line;

    while (getline(usersFile, line)) {
        size_t idPos = line.find(',');
        size_t passPos = line.find(',', idPos + 1);

        if (userID == line.substr(0, idPos)) {
            double currentBalance = stod(line.substr(passPos + 1));
            currentBalance -= 1000;
            string newLine = line.substr(0, passPos + 1) +
                             to_string(currentBalance);
            tempFile << newLine << endl;
        } else {
            tempFile << line << endl;
        }
    }

    usersFile.close();
    tempFile.close();

    remove("users.txt");
    rename("temp_users.txt", "users.txt");

    cout << "Se aplicó un costo de COP 1000 por la operación.\n" << endl;
}

bool isUserIDValid(const string &userID) {
    for (char c : userID) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
