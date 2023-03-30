#include "methods.h"

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

        // Invertir bits según el intervalo determinado usando encodedContent
        // (codificado)
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
                // El siguiente bit codificado corresponde al bit anterior sin
                //codificar
                encodedContent.push_back(binaryContent[i + j - 1]);
            }
        }
    }

    return encodedContent;
}
