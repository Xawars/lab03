#include <iostream>
#include <fstream>
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
    string inputFileName;
    string outputFileName;
    string textOutputFileName;

    cout << "Introduce el nombre del archivo fuente (.txt): ";
    getline(cin, inputFileName);

    cout << "Introduce el nombre del archivo de salida (.binary): ";
    getline(cin, outputFileName);

    cout << "Introduce el nombre del archivo de salida en texto (.txt): ";
    getline(cin, textOutputFileName);

    int n;
    cout << "Introduce la semilla de codificación (n): ";
    cin >> n;

    int encodingMethod;
    cout << "Introduce el número de codificación (1 o 2): ";
    cin >> encodingMethod;

    string line;
    string content;

    try {
        ifstream input_file(inputFileName);

        if (!input_file.is_open()) {
            throw runtime_error("Error al abrir el archivo fuente.");
        }

        while (getline(input_file, line)) {
            content += line + '\n';
        }

        input_file.close();
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
        return;
    }

    string binaryContent;
    string binary;
    for (char c : content) {
        if (c != '\n') {
            characterToBinary(c, binary);
            binaryContent += binary;
        } else {
            binaryContent += ' ';
        }
    }

    string encodedContent;

    if (encodingMethod == 1) {
        encodedContent = encodedMethod1(binaryContent, n);
    } else if (encodingMethod == 2) {
        encodedContent = encodedMethod2(binaryContent, n);
    } else {
        cerr << "Error: Método de codificación inválido." << endl;
        return;
    }

    try {
        ofstream output_file(outputFileName, ios::binary);
        ofstream text_output_file(textOutputFileName);

        if (!output_file.is_open()) {
            throw runtime_error("Error al abrir el archivo de salida.");
        }

        if (!text_output_file.is_open()) {
            throw runtime_error("Error al abrir el archivo de salida "
                                "en texto.");
        }

        // Convertir el contenido codificado a valores binarios y escribirlos
        // en el archivo
        for (int i = 0; i < encodedContent.size(); i += 8) {
            char byte = 0;
            for (int j = 0; j < 8 && i + j < encodedContent.size(); ++j) {
                byte |= (encodedContent[i + j] == '1') ? (1 << (7 - j)) : 0;
            }
            output_file.write(&byte, 1);
        }
        text_output_file << encodedContent;

        output_file.close();
        text_output_file.close();
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
        return;
    }

    cout << "Archivo codificado exitosamente." << endl;
}
