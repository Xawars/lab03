#include <iostream>
#include "functions_ex1char.h"
#include <fstream>

using namespace std;

int main()
{
    const int maxFileNameLen = 100;
    char inputFileName[maxFileNameLen], outputFileName[maxFileNameLen];
    int n, encodingMethod;
    int ch;

    cout << "Ingrese el nombre de entrada del archivo: ";
    cin.getline(inputFileName, maxFileNameLen);

    cout << "Ingrese el nombre de salida del archivo: ";
    cin.getline(outputFileName, maxFileNameLen);

    cout << "Ingrese el número n de codificación para la semilla: ";
    cin >> n;

    cout << "Ingrese el método de codificación (1 o 2): ";
    cin >> encodingMethod;

    while ((ch = cin.get()) != '\n' && ch != EOF);

    try {
        ifstream inputFile(inputFileName, ios::binary | ios::ate);
        inputFile.exceptions(ifstream::failbit | ifstream::badbit);

        streamsize fileSize = inputFile.tellg();
        inputFile.seekg(0, ios::beg);

        char *content = new char[fileSize * 8 + 1];
        char buffer;
        int bitPos = 0;

        while (inputFile.read(&buffer, 1)) {
            for (int i = 7; i >= 0; i--) {
                content[bitPos++] = (buffer & (1 << i)) ? '1' : '0';
            }
        }
        content[bitPos] = '\0';

        inputFile.close();

        if (encodingMethod == 1) {
            encodeMethod1(content, n);
        } else if (encodingMethod == 2) {
            encodeMethod2(content, n);
        } else {
            cerr << "Invalid encoding method. Exiting." << endl;
            delete[] content;
            return 1;
        }

        ofstream outputFile(outputFileName, ios::binary);
        outputFile.exceptions(ofstream::failbit | ofstream::badbit);

        for (int i = 0; i < fileSize * 8; i += 8) {
            unsigned char byte = 0;
            for (int j = 0; j < 8; j++) {
                if (content[i + j] == '1') {
                    byte |= (1 << (7 - j));
                }
            }
            outputFile.write(reinterpret_cast<char *>(&byte), 1);
        }

        outputFile.close();
        delete[] content;

        cout << "Encoding completed successfully." << endl;

    } catch (const ifstream::failure &e) {
        cerr << "An error ocurred while processing the file: " << e.what() << endl;
        return 1;
    }

    return 0;
}
