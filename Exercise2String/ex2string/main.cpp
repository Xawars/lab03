#include <iostream>
#include "methods.h"
#include "utils.h"

using namespace std;

void processFile();

int main() {
    processFile();
    return 0;
}

void processFile() {
    int n, encodingMethod;
    string inputFile, outputFile;

    cout << "Ingrese la semilla de codificación: ";
    cin >> n;

    cout << "Ingrese el método de codificación (1 o 2): ";
    cin >> encodingMethod;

    cout << "Ingrese el nombre del archivo de entrada: ";
    cin >> inputFile;

    cout << "Ingrese el nombre del archivo de salida: ";
    cin >> outputFile;

    string inputContent = readFile(inputFile);
    string binaryContent = textToBinary(inputContent);
    string decodedBinaryContent;

    if (encodingMethod == 1) {
        decodedBinaryContent = decodedMethod1(binaryContent, n);
    } else if (encodingMethod == 2) {
        // decodedMethod2
    } else {
        cerr << "Método de codificación inválido" << endl;
        exit(1);
    }

    string decodedContent = binaryToText(decodedBinaryContent);
    writeFile(outputFile, decodedContent);

    cout << "Archivo decodificado exitosamente en: " << outputFile << endl;
}
