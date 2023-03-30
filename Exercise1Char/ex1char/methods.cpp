#include "methods.h"
#include "utils.h"

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

        // Invertir bits según el intervalo determinado usando encodedContent
        // (codificado)
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
                // El siguiente bit codificado corresponde al bit anterior
                // sin codificar
                encodedContent[i + j] = binaryContent[i + j - 1];
            }
        }
    }

    encodedContent[length] = '\0';
}


