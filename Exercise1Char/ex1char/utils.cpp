#include "utils.h"

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
