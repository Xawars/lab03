#include "utils.h"

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

void characterToBinary(char c, char *binary) {
    for (int i = 7; i >= 0; --i) {
        binary[7 - i] = (c & (1 << i)) ? '1' : '0';
    }
    binary[8] = '\0';
}

void bytesToBinaryString(const unsigned char *bytes, int byteCount,
                         char *binaryString) {
    int index = 0;
    for (int i = 0; i < byteCount; ++i) {
        for (int bit = 7; bit >= 0; --bit) {
            binaryString[index++] = (bytes[i] & (1 << bit)) ? '1' : '0';
        }
    }
    binaryString[index] = '\0';
}
