#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>

string readFile(const string &filename) {
    ifstream inputFile(filename, ios::binary);
    if (!inputFile) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        exit(1);
    }

    ostringstream contentStream;
    contentStream << inputFile.rdbuf();
    inputFile.close();
    return contentStream.str();
}

void writeFile(const string &filename, const string &content) {
    ofstream outputFile(filename, ios::binary);
    if (!outputFile) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        exit(1);
    }

    outputFile << content;
    outputFile.close();
}

string textToBinary(const string &text) {
    string binary;
    for (const char &c : text) {
        binary += bitset<8>(c).to_string();
    }
    return binary;
}

string binaryToText(const string &binary) {
    string text;
    for (size_t i = 0; i < binary.size(); i += 8) {
        text += static_cast<char>(bitset<8>(binary.substr(i, 8)).to_ulong());
    }
    return text;
}
