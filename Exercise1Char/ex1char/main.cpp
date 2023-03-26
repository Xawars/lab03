#include <iostream>
#include <fstream>

using namespace std;

void concatenate(char *destination, const char *source);
void characterToBinary(char c, char *binary);
int getLength(char *array);
void encodedMethod1(char *binaryContent, char *encodedContent, int n);
void encodedMethod2(char *binaryContent, char *encodedContent, int n);
void binaryStringtoBytes(const char *binaryString, unsigned char *bytes, int &byteCount);

// xxd -b file (Para ver el contenido del archivo binario)

int main()
{
    const int size = 256;
    char inputFileName[size];
    char outputFileName[size];

    cout << "Introduce el nombre del archivo fuente (.txt): ";
    cin.getline(inputFileName, size);

    cout << "Introduce el nombre del archivo de salida (.binary): ";
    cin.getline(outputFileName, size);

    int n;
    cout << "Introduce la semilla de codificación (n): ";
    cin >> n;

    int encodingMethod;
    cout << "Introduce el número de codificación (1 o 2): ";
    cin >> encodingMethod;
    cin.ignore(); //Limpiar el buffer después de leer un entero

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
        return 1;
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
        return 1;
    }

    int byteCount = 0;
    unsigned char *bytes = new unsigned char[getLength(encodedContent) / 8 + 1];
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
        return 1;
    }

    delete[] bytes;

    cout << "Archivo convertido a binario exitosamente." << endl;

    return 0;
}

void characterToBinary(char c, char *binary) {
    for (int i = 7; i >= 0; --i) {
        binary[7 - i] = (c & (1 << i)) ? '1' : '0';
    }
    binary[8] = '\0';
}

void concatenate(char *destination, const char *source) {
    while (*destination) {
        destination++;
    }

    while ((*destination++ = *source++)) {
    }
}

int getLength(char *array) {
    int length = 0;
    while (array[length] != '\0') {
        ++length;
    }
    return length;
}

void encodedMethod1(char *binaryContent, char *encodedContent, int n) {
    int length = getLength(binaryContent);

    // Copiar el contenido binario original a encodedContent
    for (int i = 0; i < length; ++i) {
        encodedContent[i] = binaryContent[i];
    }
    encodedContent[length] = '\0';

    // Invertir bits del primer bloque
    for (int i = 0; i < n && i < length; ++i) {
        encodedContent[i] = (encodedContent[i] == '1') ? '0' : '1';
    }

    int ones, zeros, interval;
    for (int i = n; i < length; i += n) {
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

        // Determinar intervalo de inversión
        if (ones == zeros) {
            interval = 1;
        } else if (zeros > ones) {
            interval = 2;
        } else {
            interval = 3;
        }

        // Invertir bits según el intervalo determinado usando encodedContent (codificado)
        for (int j = i; j < i + n && j < length; ++j) {
            if ((j - i + 1) % interval == 0) {
                encodedContent[j] = (encodedContent[j] == '1') ? '0' : '1';
            }
        }
    }
}

void encodedMethod2(char *binaryContent, char *encodedContent, int n) {
    int length = getLength(binaryContent);
    int i, j;

    for (i = 0; i < length; i += n) {
        for (j = 0; j < n && (i + j) < length; ++j) {
            if (j == 0) {
                // El primer bit codificado corresponde al último sin codificar
                encodedContent[i] = binaryContent[i + n - 1];
            } else {
                // El siguiente bit codificado corresponde al bit anterior sin codificar
                encodedContent[i + j] = binaryContent[i + j - 1];
            }
        }
    }

    encodedContent[length] = '\0';
}

void binaryStringtoBytes(const char *binaryString, unsigned char *bytes, int &byteCount) {
    int index = 0;
    byteCount = 0;
    while (binaryString[index] != '\0') {
        unsigned char byte = 0;
        for (int bit = 0; bit < 8 && binaryString[index] != '\0'; ++bit) {
            byte <<= 1;
            if (binaryString[index] == '1') {
                byte |= 1;
            }
            ++index;
        }
        bytes[byteCount++] = byte;
    }
}
