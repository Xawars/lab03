#include "encryption.h"

using namespace std;

string stringToBinary(const string &input) {
    string binaryOutput;
    for (char c : input) {
        for (int i = 7; i >= 0; --i) {
            binaryOutput += (c & (1 << i)) ? '1' : '0';
        }
    }
    return binaryOutput;
}

string xorEncrypyDecrypt(const string &input, char key) {
    string output(input);
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ key;
    }
    return output;
}
