#include <iostream>
#include <fstream>
#include "methods.h"
#include "utils.h"

using namespace std;

void processFile();

int main()
{
    processFile();
    return 0;
}

void processFile() {
    const int size = 256;
    char inputFileName[size];
    char outputFileName[size];

    cout << "Introduce el nombre del archivo fuente (.binary): ";
    cin.getline(inputFileName, size);

    cout << "Introduce el nombre del archivo de salida (.txt): ";
    cin.getline(outputFileName, size);

    int n;
    cout << "Introduce la semilla de codificación (n): ";
    cin >> n;

    int encodingMethod;
    cout << "Introduce el número de codificación (1 o 2): ";
    cin >> encodingMethod;

    ifstream input_file(inputFileName, ios::binary | ios::ate);
    if (!input_file.is_open()) {
        cerr << "Error al abrir el archivo fuente." << endl;
        return;
    }

    int byteCount = input_file.tellg();
    input_file.seekg(0, ios::beg);

    unsigned char *bytes = new unsigned char[byteCount];
    input_file.read(reinterpret_cast<char*>(bytes), byteCount);
    input_file.close();

    char binaryString[byteCount * 8 + 1]; // Declarar el arreglo sin
    //inicializar
    // Inicializar el arreglo con ceros usando un bucle for
    for (int i = 0; i < byteCount * 8 + 1; ++i) {
        binaryString[i] = 0;
    }
    bytesToBinaryString(bytes, byteCount, binaryString);

    delete[] bytes;

    char decodedContent[size * 16] = {0};

    if (encodingMethod == 1) {
        decodedMethod1(binaryString, decodedContent, n);
    } else if (encodingMethod == 2) {
        decodedMethod2(binaryString, decodedContent, n);
    } else {
        cerr << "Error: Método de codificación inválido." << endl;
        return;
    }

    try {
        ofstream output_file(outputFileName);

        if (!output_file.is_open()) {
            throw runtime_error("Error al abrir el archivo de salida.");
        }

        bool nullCharacterFound = false;
        for (int i = 0; i < getLength(decodedContent); i += 8) {
            int charValue = 0;
            for (int j = 0; j < 8; ++j) {
                if (decodedContent[i + j] == '\0') {
                    nullCharacterFound = true;
                    break;
                }
                charValue = charValue * 2 + (decodedContent[i + j] - '0');
            }
            if (nullCharacterFound) {
                break;
            }
            output_file.put(static_cast<char>(charValue));
        }

        output_file.close();
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
        return;
    }

    cout << "Archivo decodificado exitosamente." << endl;
}
