#include <iostream>
#include <fstream>
#include "utils.h"
#include "methods.h"

using namespace std;

void processFile();

// xxd -b file (Para ver el contenido del archivo binario)

int main()
{
    processFile();
    return 0;
}

void processFile() {
    const int size = 256;
    char inputFileName[size];
    char outputFileName[size];
    char textOutputFileName[size];

    cout << "Introduce el nombre del archivo fuente (.txt): ";
    cin.getline(inputFileName, size);

    cout << "Introduce el nombre del archivo de salida (.binary): ";
    cin.getline(outputFileName, size);

    cout << "Introduce el nombre del archivo de salida en texto. (.txt): ";
    cin.getline(textOutputFileName, size);

    int n;
    cout << "Introduce la semilla de codificación (n): ";
    cin >> n;

    int encodingMethod;
    cout << "Introduce el número de codificación (1 o 2): ";
    cin >> encodingMethod;

    char line[size];
    char content[size * 2] = {0};

    try {
        ifstream input_file(inputFileName);

        if (!input_file.is_open()) {
            throw runtime_error("Error al abrir el archivo fuente.");
        }

        while (input_file.getline(line, size)) {
            concatenate(content, line);
            concatenate(content, "\n");
        }

        input_file.close();
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
        return;
    }

    char binaryContent[size * 16] = {0};
    // Arreglo para almacenar el contenido codificado
    char encodedContent[size * 16] = {0};
    char binary[9];

    for (int i = 0; content[i] != '\0'; ++i) {
        if (content[i] != '\n') {
            characterToBinary(content[i], binary);
            concatenate(binaryContent, binary);
        } else {
            concatenate(binaryContent, " ");
        }
    }

    if (encodingMethod == 1) {
        encodedMethod1(binaryContent, encodedContent, n);
    } else if (encodingMethod == 2) {
        encodedMethod2(binaryContent, encodedContent, n);
    } else {
        cerr << "Error: Método de codificación inválido." << endl;
        return;
    }

    int byteCount = 0;
    unsigned char *bytes = new unsigned char[getLength(encodedContent)
                                                 / 8 + 1];
    binaryStringtoBytes(encodedContent, bytes, byteCount);

    try {
        ofstream output_file(outputFileName, ios::binary);

        if (!output_file.is_open()) {
            throw runtime_error("Error al abrir el archivo de salida.");
        }

        for (int i = 0; encodedContent[i] != '\0'; ++i) {
            output_file.write(reinterpret_cast<const char*>(&bytes[i]), 1);
        }

        output_file.close();
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
        return;
    }

    // Escribir el contenido codificado en el archivo de texto de salida
    try {
        ofstream text_output_file(textOutputFileName);

        if (!text_output_file.is_open()) {
            throw runtime_error("Error al abrir el archivo de salida en "
                                "texto.");
        }

        text_output_file << encodedContent;

        text_output_file.close();
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
        return;
    }

    delete[] bytes;

    cout << "Archivo codificado exitosamente." << endl;
}

