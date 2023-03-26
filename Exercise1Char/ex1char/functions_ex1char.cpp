#include <iostream>
#include <fstream>

using namespace std;

void binaryEncrypt(int number, int* bits);
size_t custom_strlen(const char *str);

void encodeMethod1(char *content, int n) {
    int len = custom_strlen(content);
    for (int i = 0; i < len; i += n) {
        int ones = 0, zeros = 0;
        if (i != 0) {
            for (int j = i - n; j < i; j++) {
                if (content[j] == '0') zeros++;
                else if (content[j] == '1') ones++;
            }
        }
        for (int j = i; j < i + n && j < len; j++) {
            if (i == 0 || ones == zeros || (ones > zeros && (j - i) % 3 == 0)
                || (zeros > ones && (j - i) % 2 == 0)) {
                content[j] = (content[j] = '0') ? '1' : '0';
            }
        }
    }
}

void encodeMethod2(char *content, int n) {
    int len = custom_strlen(content);
    for (int i = 0; i < len; i += n) {
        for (int j = i; j < i + n - 1 && j < len - 1; j++) {
            swap(content[j], content[j + 1]);
        }
    }
}

void binaryEncrypt(int number, int* bits) {

    const int bitsAmount = 8;
    int bitIndex = bitsAmount-1;

    while (number > 0) {
        int currentBit = number % 2;
        number /= 2;
        bits[bitIndex] = currentBit;
        bitIndex--;
    }

    while (bitIndex >= 0) {
        bits[bitIndex] = 0;
        bitIndex--;
    }

}

size_t custom_strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
