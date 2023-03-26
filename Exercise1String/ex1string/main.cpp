#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void characterToBinary(char c, string &binary);
string encodedMethod1(const string &binaryContent, int n);
string encodedMethod2(const string &binaryContent, int n);

// xxd -b file (Para ver el contenido del archivo binario)

int main()
{
    string inputFileName;
    string outputFileName;

    cout << "Introduce el nombre del archivo fuente (.txt): ";
    getline(cin, inputFileName);

    cout << "Introduce el nombre del archivo de salida (.binary): ";
    getline(cin, outputFileName);

    int n;
    cout << "Introduce la semilla de codificación (n): ";
    cin >> n;

    int encodingMethod;
    cout << "Introduce el número de codificación (1 o 2): ";
    cin >> encodingMethod;
    cin.ignore(); // Limpiar el buffer después de leer un entero

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
        return 1;
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
        return 1;
    }

    try {
        ofstream output_file(outputFileName, ios::binary);

        if (!output_file.is_open()) {
            throw runtime_error("Error al abrir el archivo de salida.");
        }

        // Convertir el contenido codificado a valores binarios y escribirlos en el archivo
        for (int i = 0; i < encodedContent.size(); i += 8) {
            char byte = 0;
            for (int j = 0; j < 8 && i + j < encodedContent.size(); ++j) {
                byte |= (encodedContent[i + j] == '1') ? (1 << (7 - j)) : 0;
            }
            output_file.write(&byte, 1);
        }

        output_file.close();
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    cout << "Archivo convertido a binario exitosamente." << endl;

    return 0;
}

void characterToBinary(char c, string &binary) {
    binary.clear();
    for (int i = 7; i >= 0; --i) {
        binary += (c & (1 << i)) ? '1' : '0';
    }
}

string encodedMethod1(const string &binaryContent, int n) {
    string encodedContent(binaryContent);

    // Invertir bits del primer bloque
    for (int i = 0; i < n && i < binaryContent.size(); ++i) {
        encodedContent[i] = (encodedContent[i] == '1') ? '0' : '1';
    }

    int ones, zeros, interval;
    for (int i = n; i < binaryContent.size(); i += n) {
        ones = 0;
        zeros = 0;

        // Contar 1s y 0s en el bloque anterior
        for (int j = i - n; j < i; ++j) {
            if (binaryContent[j] == '1') {
                ones++;
            } else {
                zeros++;
            }
        }

        // Determine intervalo de inversión
        if (ones == zeros) {
            interval = 1;
        } else if (zeros > ones) {
            interval = 2;
        } else {
            interval = 3;
        }

        // Invertir bits según el intervalo determinado usando encodedContent (codificado)
        for (int j = i; j < i + n && j < binaryContent.size(); ++j) {
            if ((j - i + 1) % interval == 0) {
                encodedContent[j] = (encodedContent[j] == '1') ? '0' : '1';
            }
        }
    }

    return encodedContent;
}

string encodedMethod2(const string &binaryContent, int n) {
    string encodedContent;
    encodedContent.reserve(binaryContent.size());
    int i, j;

    for (i = 0; i < binaryContent.size(); i += n) {
        for (j = 0; j < n && (i + j) < binaryContent.size(); ++j) {
            if (j == 0) {
                // El primer bit codificado corresponde al último sin codificar
                encodedContent.push_back(binaryContent[i + n - 1]);
            } else {
                // El siguiente bit codificado corresponde al bit anterior sin codificar
                encodedContent.push_back(binaryContent[i + j - 1]);
            }
        }
    }

    return encodedContent;
}
