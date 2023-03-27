#include <iostream>
#include <fstream>

using namespace std;

void concatenate(char *destination, const char *source);
void characterToBinary(char c, char *binary);
int getLength(char *array);
void decodedMethod1(char *encodedContent, char *decodedContent, int n);
void decodedMethod2(char *encodedContent, char *decodedContent, int n);
void bytesToBinaryString(const unsigned char *bytes, int byteCount, char *binaryString);

int main()
{
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
    cin.ignore(); // Limpiar el buffer después de leer un entero

    ifstream input_file(inputFileName, ios::binary | ios::ate);
    if (!input_file.is_open()) {
        cerr << "Error al abrir el archivo fuente." << endl;
        return 1;
    }

    int byteCount = input_file.tellg();
    input_file.seekg(0, ios::beg);

    unsigned char *bytes = new unsigned char[byteCount];
    input_file.read(reinterpret_cast<char*>(bytes), byteCount);
    input_file.close();


    char binaryString[byteCount * 8 + 1]; // Declarar el arreglo sin inicializar
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
        return 1;
    }

    try {
        ofstream output_file(outputFileName);

        if (!output_file.is_open()) {
            throw runtime_error("Error al abrir el archivo de salida.");
        }

        for (int i = 0; i < getLength(decodedContent); i += 8) {
            int charValue = 0;
            for (int j = 0; j < 8; ++j) {
                if (decodedContent[i + j] == '\0') {
                    break;
                }
                charValue = charValue * 2 + (decodedContent[i + j] - '0');
            }
            if (charValue == 0) {
                break; // Si encuentra un valor de carácter nulo, detiene la escritura en el archivo
            }
            output_file.put(static_cast<char>(charValue));
        }

        output_file.close();
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    cout << "Archivo decodificado exitosamente." << endl;

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

// Funciones para la decodificación
void decodedMethod1(char *encodedContent, char *decodedContent, int n) {
    int length = getLength(encodedContent);

    // Copiar el contenido binario codificado a decodedContent
    for (int i = 0; i < length; ++i) {
        decodedContent[i] = encodedContent[i];
    }
    decodedContent[length - 1] = '\0';

    // Invertir bits del primer bloque
    for (int i = 0; i < n && i < length; ++i) {
        decodedContent[i] = (decodedContent[i] == '1') ? '0' : '1';
    }

    int ones, zeros, interval;
    for (int i = n; i < length; i += n) {
        ones = 0;
        zeros = 0;

        // Contar 1s y 0s en el bloque anterior
        for (int j = i - n; j < i; ++j) {
            if (decodedContent[j] == '1') {
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

        // Invertir bits según el intervalo determinado usando decodedContent (decodificado)
        for (int j = i; j < i + n && j < length; ++j) {
            if ((j - i + 1) % interval == 0) {
                decodedContent[j] = (decodedContent[j] == '1') ? '0' : '1';
            }
        }
    }
}

void decodedMethod2(char *encodedContent, char *decodedContent, int n) {
    int length = getLength(encodedContent);
    int i, j;

    for (i = 0; i < length; i += n) {
        for (j = 0; j < n && (i + j) < length; ++j) {
            if (j == 0) {
                // El primer bit decodificado corresponde al último sin decodificar
                decodedContent[i + n - 1] = encodedContent[i];
            } else {
                // El siguiente bit decodificado corresponde al bit anterior sin decodificar
                decodedContent[i + j - 1] = encodedContent[i + j];
            }
        }
    }

    decodedContent[length - 1] = '\0';
}

void bytesToBinaryString(const unsigned char *bytes, int byteCount, char *binaryString) {
    int index = 0;
    for (int i = 0; i < byteCount; ++i) {
        for (int bit = 7; bit >= 0; --bit) {
            binaryString[index++] = (bytes[i] & (1 << bit)) ? '1' : '0';
        }
    }
    binaryString[index] = '\0';
}
