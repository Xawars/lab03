#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

bool convertBinaryToText(const string &inputFileName,
                         const string &outputFileName) {
    ifstream inputFile(inputFileName, ios::in | ios::binary);
    ofstream outputFile(outputFileName, ios::out);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        return false;
    }

    // Leer el archivo binario en bloques
    const size_t bufferSize = 1024;
    char buffer[bufferSize];
    size_t bytesRead;

    inputFile.seekg(0, ios::end);
    size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, ios::beg);

    size_t totalBytesRead = 0;
    do {
        inputFile.read(buffer, bufferSize);
        bytesRead = inputFile.gcount();
        totalBytesRead += bytesRead;
        size_t bytesToWrite = bytesRead;
        // Evitar escribir el último byte (8 bits) si estamos en el último bloque
        // de lectura
        if (totalBytesRead == fileSize) {
            bytesToWrite -= 1;
        }

        for (size_t i = 0; i < bytesToWrite; ++i) {
            // Convierte cada byte a una secuencia de caracteres '0' y '1' y
            // escribe en el archivo de salida
            outputFile << bitset<8>(buffer[i]).to_string();
        }
    } while (inputFile);

    inputFile.close();
    outputFile.close();
    return true;
}

void processFilesConvertBinaryToText(const string &inputFileNameBinary,
                                     const string &outputFileNameText) {
    try {
        if (convertBinaryToText(inputFileNameBinary, outputFileNameText)) {
            cout << "Archivo convertido exitosamente de binario a texto." << endl;
        } else {
            throw runtime_error("Error al abrir los archivos.");
        }
    } catch (const exception &e) {
        cerr << "Excepción: " << e.what() << endl;
    }
}
