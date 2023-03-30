#include "methods.h"
#include "utils.h"

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

        // Invertir bits según el intervalo determinado usando decodedContent
        // (decodificado)
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
                // El primer bit decodificado corresponde al último sin
                // decodificar
                decodedContent[i + n - 1] = encodedContent[i];
            } else {
                // El siguiente bit decodificado corresponde al bit anterior
                // sin decodificar
                decodedContent[i + j - 1] = encodedContent[i + j];
            }
        }
    }

    decodedContent[length - 1] = '\0';
}
