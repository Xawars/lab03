#include "methods.h"

using namespace std;

string decodedMethod1(const string &encodedContent, int n) {
    string decodedContent(encodedContent);

    // Invertir bits del primer bloque
    for (int i = 0; i < n && i < encodedContent.size(); ++i) {
        decodedContent[i] = (decodedContent[i] == '1') ? '0' : '1';
    }

    int ones, zeros, interval;
    for (int i = n; i < encodedContent.size(); i += n) {
        ones = 0;
        zeros = 0;

        // Contar 1s y 0s en el bloque anterior (en el contenido decodificado)
        for (int j = i - n; j < i; ++j) {
            if (decodedContent[j] == '1') {
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
        for (int j = i; j < i + n && j < encodedContent.size(); ++j) {
            if ((j - i + 1) % interval == 0) {
                decodedContent[j] = (encodedContent[j] == '1') ? '0' : '1';
            } else {
                decodedContent[j] = encodedContent[j];
            }
        }
    }

    return decodedContent;
}
