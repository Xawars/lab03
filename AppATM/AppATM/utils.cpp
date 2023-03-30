#include <iostream>
#include <cstdlib>
#include "utils.h"

using namespace std;

void clearScreen() {
    system("clear");
}

void pauseScreen() {
    cout << "\nPresiona cualquier tecla para continuar...";
    getchar();
}
